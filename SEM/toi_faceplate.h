// =============================================================================
//  TOI faceplate kit (Cmajor-free)  -  toi_faceplate.h
//
//  The SAME beautiful TOI chassis as toi_native_ui.h, but with ZERO Cmajor/choc
//  dependency, for the pure-JUCE "sampled instruments" line (cello/violin/strings/
//  piano/sax/...). Preset storage is abstracted behind toi::PresetStore (the plugin
//  implements it) instead of cmaj::Patch; param lookup matches plain JUCE params too.
//
//  Primitives are copied from toi_native_ui.h so the look is identical. A plugin in
//  this line includes ONLY this header (never toi_native_ui.h) and subclasses
//  toi::PanelEditor, filling the unique panel via paintPanel/layoutPanel.
// =============================================================================

#pragma once

#include <JuceHeader.h>
#include <vector>
#include <memory>
#include <map>
#include <array>
#include <atomic>
#include <cmath>

namespace toi
{

//==============================================================================
constexpr float STROKE      = 3.5f;
constexpr float THIN_STROKE = 2.0f;
constexpr float ART_W  = 1300.0f;
constexpr float ART_H  = 477.0f;   // taller than the Cmajor line: room for a big 2-band panel
constexpr float TOP_H  = 250.0f;   // fits a full-size knob row + a scope/preset row
constexpr float NOTE_H = 22.0f;

inline juce::Font uiFont (float h, bool bold = false)
{
    auto f = juce::Font (juce::FontOptions (h).withName ("Helvetica Neue"));
    return bold ? f.boldened() : f;
}

struct Palette
{
    juce::Colour bg, frame, ink, accent, accent2, button, thumb,
                 keyWhite, keyWhitePr, keyBlack, keyBlackPr;
    juce::Colour text   = juce::Colour (0xff000000);
    juce::Colour panel2 = juce::Colour (0x00000000);
    juce::Colour bg2    = juce::Colour (0x00000000);   // gradient end (transparent = flat bg)
    juce::Colour lcdBg  = juce::Colour (0xff06122e);
    juce::Colour lcdInk = juce::Colour (0xff7da8ff);
};

struct ParamSpec
{
    juce::String id, label;
    float        min = 0.0f, max = 1.0f;
    bool         env = false;
};

struct FactoryPreset
{
    juce::String       name;
    std::vector<float> vals;   // real units, indexed to match Config::params
};

struct Config
{
    Palette                 pal;
    juce::String            model;
    std::vector<ParamSpec>  params;
    int kbLow = 53, kbHigh = 77;
    std::vector<FactoryPreset> factory;
};

//==============================================================================
// Lock-free audio tap (same as toi_native_ui.h) for real screen animation.
struct AudioTap
{
    static constexpr int kRing = 480;
    std::array<std::atomic<float>, kRing> ring {};
    std::atomic<int>   wpos { 0 };
    std::atomic<float> level { 0.0f };

    void push (const juce::AudioBuffer<float>& b) noexcept
    {
        const int n = b.getNumSamples();
        if (n <= 0 || b.getNumChannels() == 0) return;
        const float* L = b.getReadPointer (0);
        const float* R = b.getNumChannels() > 1 ? b.getReadPointer (1) : L;
        int w = wpos.load (std::memory_order_relaxed);
        float pk = level.load (std::memory_order_relaxed) * 0.90f;
        for (int i = 0; i < n; ++i)
        {
            const float m = 0.5f * (L[i] + R[i]);
            ring[(size_t) w].store (m, std::memory_order_relaxed);
            w = (w + 1) % kRing;
            const float a = std::abs (m);
            if (a > pk) pk = a;
        }
        wpos.store (w, std::memory_order_relaxed);
        level.store (pk, std::memory_order_relaxed);
    }
};

class AudioTapSource
{
public:
    virtual ~AudioTapSource() = default;
    virtual AudioTap* getAudioTap() = 0;
};

// Implemented by the plugin so the faceplate can save/recall the 16 preset slots
// without any Cmajor patch. Values are REAL units keyed by ParamSpec::id.
class PresetStore
{
public:
    virtual ~PresetStore() = default;
    virtual bool loadPreset (int idx, std::map<juce::String, float>& out) = 0;
    virtual void savePreset (int idx, const std::map<juce::String, float>& vals) = 0;
    virtual bool hasPreset  (int idx) = 0;
};

//==============================================================================
inline constexpr int   kNumWhite        = 15;
inline constexpr int   kWhiteMidi[15]   = { 53,55,57,59,60,62,64,65,67,69,71,72,74,76,77 };
inline constexpr int   kBlackOffsets[10]= { 0,1,2,4,5,7,8,9,11,12 };
inline constexpr float kBlackWFrac      = 0.62f;
inline constexpr float kBlackHFrac      = 0.62f;
inline const char* const kWhiteNames[15]= { "F","G","A","B","C","D","E","F","G","A","B","C","D","E","F" };

struct InvisibleLinearLAF  : public juce::LookAndFeel_V4
{
    void drawLinearSlider (juce::Graphics&, int, int, int, int, float, float, float,
                           juce::Slider::SliderStyle, juce::Slider&) override {}
};
struct InvisibleRotaryLAF  : public juce::LookAndFeel_V4
{
    void drawRotarySlider (juce::Graphics&, int, int, int, int, float, float, float, juce::Slider&) override {}
};

//==============================================================================
class ParamKnobAttachment  : private juce::Slider::Listener,
                             private juce::AudioProcessorParameter::Listener,
                             private juce::AsyncUpdater
{
public:
    ParamKnobAttachment (juce::AudioProcessorParameter& p, juce::Slider& s) : param (p), slider (s)
    {
        slider.setRange (0.0, 1.0, 0.0);
        slider.setValue (param.getValue(), juce::dontSendNotification);
        slider.addListener (this);
        param.addListener (this);
    }
    ~ParamKnobAttachment() override
    {
        cancelPendingUpdate();
        param.removeListener (this);
        slider.removeListener (this);
    }
private:
    void sliderValueChanged (juce::Slider* s) override { if (! selfChanging) param.setValueNotifyingHost ((float) s->getValue()); }
    void sliderDragStarted (juce::Slider*) override { param.beginChangeGesture(); }
    void sliderDragEnded   (juce::Slider*) override { param.endChangeGesture(); }
    void parameterValueChanged (int, float) override  { triggerAsyncUpdate(); }
    void parameterGestureChanged (int, bool) override {}
    void handleAsyncUpdate() override { selfChanging = true; slider.setValue (param.getValue(), juce::dontSendNotification); selfChanging = false; }
    juce::AudioProcessorParameter& param; juce::Slider& slider; bool selfChanging = false;
};

//==============================================================================
class Fader  : public juce::Component
{
public:
    Fader (const juce::String& labelText, bool envFader, const Palette& palette)
        : label (labelText), env (envFader), pal (palette)
    {
        slider.setSliderStyle (juce::Slider::LinearVertical);
        slider.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
        slider.setLookAndFeel (&laf);
        slider.setRange (0.0, 1.0, 0.0);
        slider.setDoubleClickReturnValue (true, 0.5);
        addAndMakeVisible (slider);
    }
    ~Fader() override { slider.setLookAndFeel (nullptr); }
    void attach (juce::AudioProcessorParameter& p)
    {
        attachment = std::make_unique<ParamKnobAttachment> (p, slider);
        slider.setDoubleClickReturnValue (true, p.getDefaultValue());
        slider.onValueChange = [this] { repaint(); };
        repaint();
    }
    juce::Rectangle<float> trackArea() const { return getLocalBounds().toFloat().withTrimmedBottom (labelH).reduced (0.0f, 7.0f); }
    void resized() override { slider.setBounds (trackArea().getSmallestIntegerContainer()); }
    void paint (juce::Graphics& g) override
    {
        auto area = trackArea();
        const float cx = area.getCentreX(), top = area.getY(), h = area.getHeight();
        const float tw = 8.0f;
        g.setColour (pal.ink);
        g.fillRoundedRectangle (juce::Rectangle<float> (cx - tw * 0.5f, top, tw, h), 1.5f);
        const float v = juce::jlimit (0.0f, 1.0f, (float) slider.getValue());
        const float tW = 22.0f, tH = 13.0f, pad = tH * 0.5f + STROKE * 0.5f;
        const float ty = top + pad + (1.0f - v) * (h - 2.0f * pad);
        juce::Rectangle<float> thumb (cx - tW * 0.5f, ty - tH * 0.5f, tW, tH);
        g.setColour (env ? pal.accent : pal.thumb);
        g.fillRoundedRectangle (thumb, 1.5f);
        g.setColour (pal.ink);
        g.drawRoundedRectangle (thumb, 1.5f, STROKE);
        g.fillRect (juce::Rectangle<float> (thumb.getX() + 2.0f, thumb.getCentreY() - STROKE * 0.5f, thumb.getWidth() - 4.0f, STROKE));
        g.setColour (pal.text);
        g.setFont (uiFont (9.5f, true));
        g.drawText (label, getLocalBounds().toFloat().removeFromBottom (labelH), juce::Justification::centred);
    }
    juce::Slider slider;
private:
    static constexpr float labelH = 13.0f;
    InvisibleLinearLAF laf; juce::String label; bool env; Palette pal;
    std::unique_ptr<ParamKnobAttachment> attachment;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Fader)
};

//==============================================================================
class Knob  : public juce::Component
{
public:
    Knob (const juce::String& labelText, const Palette& palette,
          juce::Colour ringColour = juce::Colour (0x00000000))
        : label (labelText), pal (palette), ring (ringColour)
    {
        slider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
        slider.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
        slider.setLookAndFeel (&laf);
        slider.setRange (0.0, 1.0, 0.0);
        slider.setDoubleClickReturnValue (true, 0.5);
        addAndMakeVisible (slider);
    }
    ~Knob() override { slider.setLookAndFeel (nullptr); }
    void attach (juce::AudioProcessorParameter& p)
    {
        attachment = std::make_unique<ParamKnobAttachment> (p, slider);
        slider.setDoubleClickReturnValue (true, p.getDefaultValue());
        slider.onValueChange = [this] { repaint(); };
        repaint();
    }
    void setShowLabel (bool s) { showLabel = s; }
    void setArc (juce::Colour c) { arcCol = c; }
    void setHub (juce::Colour c, float frac = 0.5f) { hubCol = c; hubFrac = frac; }
    void setTrianglePointer (juce::Colour fill) { triFill = fill; }

    juce::Rectangle<float> discArea() const
    {
        auto b = getLocalBounds().toFloat();
        if (showLabel) b.removeFromBottom (labelH);
        const float d = std::min (b.getWidth(), b.getHeight());
        return juce::Rectangle<float> (0, 0, d, d).withCentre ({ b.getCentreX(), b.getCentreY() });
    }
    void resized() override { slider.setBounds (discArea().getSmallestIntegerContainer()); }

    void paint (juce::Graphics& g) override
    {
        auto disc = discArea();
        const float cx = disc.getCentreX(), cy = disc.getCentreY();
        const float r  = disc.getWidth() * 0.5f - STROKE - 1.0f;
        g.setColour (pal.button);
        g.fillEllipse (cx - r, cy - r, r * 2.0f, r * 2.0f);
        g.setColour (pal.ink);
        g.drawEllipse (cx - r, cy - r, r * 2.0f, r * 2.0f, STROKE);
        if (! ring.isTransparent())
        {
            g.setColour (ring);
            g.drawEllipse (cx - (r - 4.0f), cy - (r - 4.0f), (r - 4.0f) * 2.0f, (r - 4.0f) * 2.0f, 2.5f);
        }
        if (! hubCol.isTransparent())
        {
            const float hr = r * hubFrac;
            g.setColour (hubCol); g.fillEllipse (cx - hr, cy - hr, hr * 2.0f, hr * 2.0f);
            g.setColour (pal.ink); g.drawEllipse (cx - hr, cy - hr, hr * 2.0f, hr * 2.0f, 1.5f);
        }
        const float v   = juce::jlimit (0.0f, 1.0f, (float) slider.getValue());
        if (! arcCol.isTransparent() && v > 0.001f)
        {
            juce::Path ap;
            const float ar = r + 1.0f;
            ap.addCentredArc (cx, cy, ar, ar, 0.0f, juce::degreesToRadians (-135.0f),
                              juce::degreesToRadians (-135.0f + 270.0f * v), true);
            g.setColour (arcCol);
            g.strokePath (ap, juce::PathStrokeType (3.5f, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
        }
        const float ang = juce::degreesToRadians (-135.0f + 270.0f * v);
        const float dx = std::sin (ang), dy = -std::cos (ang);
        if (triFill.isTransparent())
        {
            g.setColour (pal.text);
            g.drawLine (cx, cy, cx + dx * (r - 3.0f), cy + dy * (r - 3.0f), STROKE);
        }
        else
        {
            const float px = -dy, py = dx;
            juce::Path tri;
            tri.startNewSubPath (cx + px * 4.0f, cy + py * 4.0f);
            tri.lineTo (cx - px * 4.0f, cy - py * 4.0f);
            tri.lineTo (cx + dx * (r - 2.0f), cy + dy * (r - 2.0f));
            tri.closeSubPath();
            g.setColour (triFill); g.fillPath (tri);
            g.setColour (pal.ink);  g.strokePath (tri, juce::PathStrokeType (1.5f));
        }
        if (showLabel)
        {
            g.setColour (pal.text);
            g.setFont (uiFont (9.5f, true));
            g.drawText (label, getLocalBounds().toFloat().removeFromBottom (labelH), juce::Justification::centred);
        }
    }
    juce::Slider slider;
private:
    static constexpr float labelH = 13.0f;
    InvisibleRotaryLAF laf; juce::String label; Palette pal; juce::Colour ring, arcCol { 0x00000000 }, hubCol { 0x00000000 }, triFill { 0x00000000 }; bool showLabel = true; float hubFrac = 0.5f;
    std::unique_ptr<ParamKnobAttachment> attachment;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Knob)
};

//==============================================================================
// StyledKnob - refined line-art dials reimplemented from the TOI component library
// (115-design knob set). One `style` enum picks the look; the static ring uses the
// panel text colour and the moving indicator/arc uses the accent, so every instrument
// can wear a DIFFERENT knob and still match its palette. A hidden rotary slider is the
// drag surface; bound to a param via ParamKnobAttachment (0..1).
class StyledKnob  : public juce::Component
{
public:
    enum Style { Pointer = 0, RingDot, Lollipop, Target, Ticks, Arc, Metal, Fluted, FlutedDark, Pointed, Spike, NumStyles };

    StyledKnob (const juce::String& labelText, const Palette& palette, int knobStyle)
        : label (labelText), pal (palette), style (knobStyle % (int) NumStyles)
    {
        slider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
        slider.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
        slider.setLookAndFeel (&laf);
        slider.setRange (0.0, 1.0, 0.0);
        slider.setDoubleClickReturnValue (true, 0.5);
        addAndMakeVisible (slider);
    }
    ~StyledKnob() override { slider.setLookAndFeel (nullptr); }

    void attach (juce::AudioProcessorParameter& p)
    {
        attachment = std::make_unique<ParamKnobAttachment> (p, slider);
        slider.setDoubleClickReturnValue (true, p.getDefaultValue());
        slider.onValueChange = [this] { repaint(); };
        repaint();
    }
    void setShowLabel (bool s) { showLabel = s; }

    juce::Rectangle<float> discArea() const
    {
        auto b = getLocalBounds().toFloat();
        if (showLabel) b.removeFromBottom (labelH);
        const float d = std::min (b.getWidth(), b.getHeight());
        return juce::Rectangle<float> (0, 0, d, d).withCentre ({ b.getCentreX(), b.getCentreY() });
    }
    void resized() override { slider.setBounds (discArea().getSmallestIntegerContainer()); }

    void paint (juce::Graphics& g) override
    {
        auto disc = discArea();
        const float cx = disc.getCentreX(), cy = disc.getCentreY();
        const float r  = disc.getWidth() * 0.5f - 8.0f;   // leave room for the value-arc + tick ring outside the body
        const float v   = juce::jlimit (0.0f, 1.0f, (float) slider.getValue());
        const float ang = juce::degreesToRadians (-135.0f + 270.0f * v);
        const float dx = std::sin (ang), dy = -std::cos (ang);
        const juce::Colour ring = pal.text, acc = pal.accent;

        auto pointer = [&] (float from, float to, float w)
        { g.setColour (acc); g.drawLine (cx + dx * r * from, cy + dy * r * from, cx + dx * r * to, cy + dy * r * to, w); };

        switch (style)
        {
            case RingDot:
            {
                g.setColour (ring); g.drawEllipse (cx - r, cy - r, r * 2, r * 2, THIN_STROKE);
                const float ir = r * 0.60f;
                g.drawEllipse (cx - ir, cy - ir, ir * 2, ir * 2, THIN_STROKE);
                const float dr = r * 0.11f;
                g.setColour (acc); g.fillEllipse (cx + dx * ir - dr, cy + dy * ir - dr, dr * 2, dr * 2);
                break;
            }
            case Lollipop:
            {
                g.setColour (ring); g.drawEllipse (cx - r, cy - r, r * 2, r * 2, THIN_STROKE);
                pointer (0.0f, 0.58f, STROKE);
                const float dr = r * 0.15f;
                g.setColour (acc); g.fillEllipse (cx + dx * r * 0.58f - dr, cy + dy * r * 0.58f - dr, dr * 2, dr * 2);
                break;
            }
            case Target:
            {
                g.setColour (ring);
                g.drawEllipse (cx - r, cy - r, r * 2, r * 2, THIN_STROKE);
                const float r2 = r * 0.66f, r3 = r * 0.34f;
                g.drawEllipse (cx - r2, cy - r2, r2 * 2, r2 * 2, THIN_STROKE);
                g.drawEllipse (cx - r3, cy - r3, r3 * 2, r3 * 2, THIN_STROKE);
                pointer (0.34f, 0.96f, STROKE);
                break;
            }
            case Ticks:
            {
                const int N = 30;
                const float tr = r * 0.92f, dotR = juce::jmax (1.0f, r * 0.05f);
                for (int i = 0; i < N; ++i)
                {
                    const float t = (float) i / (float) (N - 1);
                    const float a = juce::degreesToRadians (-135.0f + 270.0f * t);
                    const float tx = cx + std::sin (a) * tr, ty = cy - std::cos (a) * tr;
                    g.setColour (t <= v + 0.001f ? acc : ring.withAlpha (0.28f));
                    g.fillEllipse (tx - dotR, ty - dotR, dotR * 2, dotR * 2);
                }
                g.setColour (ring); g.drawEllipse (cx - r * 0.6f, cy - r * 0.6f, r * 1.2f, r * 1.2f, THIN_STROKE);
                pointer (0.0f, 0.55f, STROKE);
                break;
            }
            case Arc:
            {
                g.setColour (ring.withAlpha (0.22f)); g.drawEllipse (cx - r, cy - r, r * 2, r * 2, THIN_STROKE);
                const float ar = r * 0.92f;
                juce::Path p;
                p.addCentredArc (cx, cy, ar, ar, 0.0f, juce::degreesToRadians (-135.0f), ang, true);
                g.setColour (acc); g.strokePath (p, juce::PathStrokeType (STROKE, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
                g.setColour (ring); pointer (0.0f, 0.72f, STROKE);
                g.setColour (acc); g.drawLine (cx + dx * r * 0.0f, cy + dy * r * 0.0f, cx + dx * r * 0.72f, cy + dy * r * 0.72f, THIN_STROKE);
                break;
            }
            case Metal:
            {
                // drop shadow
                g.setColour (juce::Colours::black.withAlpha (0.45f));
                g.fillEllipse (cx - r, cy - r + 4.0f, r * 2, r * 2);
                // metallic body (highlight top-left -> dark bottom)
                juce::ColourGradient body (pal.button.brighter (0.55f), cx - r * 0.35f, cy - r * 0.45f,
                                           pal.button.darker (0.55f),  cx + r * 0.40f, cy + r * 0.90f, false);
                body.addColour (0.5, pal.button);
                g.setGradientFill (body); g.fillEllipse (cx - r, cy - r, r * 2, r * 2);
                g.setColour (pal.ink); g.drawEllipse (cx - r, cy - r, r * 2, r * 2, 2.0f);
                // tick ring just outside
                const int N = 24; const float t0 = r + 3.0f, t1 = r + 6.0f;
                g.setColour (pal.text.withAlpha (0.32f));
                for (int i = 0; i < N; ++i)
                { const float a = juce::degreesToRadians (-135.0f + 270.0f * (float) i / (float) (N - 1));
                  g.drawLine (cx + std::sin (a) * t0, cy - std::cos (a) * t0, cx + std::sin (a) * t1, cy - std::cos (a) * t1, 1.0f); }
                // recessed inner cap
                const float ir = r * 0.60f;
                juce::ColourGradient cap (pal.bg.brighter (0.10f), cx, cy - ir, pal.button.darker (0.35f), cx, cy + ir, false);
                g.setGradientFill (cap); g.fillEllipse (cx - ir, cy - ir, ir * 2, ir * 2);
                g.setColour (pal.ink.withAlpha (0.7f)); g.drawEllipse (cx - ir, cy - ir, ir * 2, ir * 2, 1.0f);
                // accent value arc
                { juce::Path ap; ap.addCentredArc (cx, cy, r + 5.0f, r + 5.0f, 0.0f, juce::degreesToRadians (-135.0f), ang, true);
                  g.setColour (pal.accent); g.strokePath (ap, juce::PathStrokeType (2.5f, juce::PathStrokeType::curved, juce::PathStrokeType::rounded)); }
                // bright pointer
                g.setColour (pal.thumb);
                g.drawLine (cx + dx * ir * 0.25f, cy + dy * ir * 0.25f, cx + dx * r * 0.9f, cy + dy * r * 0.9f, STROKE);
                // glint
                g.setColour (juce::Colours::white.withAlpha (0.16f));
                g.fillEllipse (cx - r * 0.45f, cy - r * 0.55f, r * 0.5f, r * 0.35f);
                break;
            }
            case Fluted:
            {
                // Vintage Moog/Davies knob: scalloped black skirt + brushed-aluminium cap + pointer dot.
                const float R = disc.getWidth() * 0.5f - 2.0f;
                // drop shadow (so a black knob reads on a black panel)
                g.setColour (juce::Colours::black.withAlpha (0.5f));
                g.fillEllipse (cx - R, cy - R + 3.5f, R * 2.0f, R * 2.0f);
                // fluted skirt (scalloped rim path) - deeper, distinct lobes like the Davies knob
                const int N = 10; const float fd = 0.135f; const int steps = 220;
                juce::Path skirt;
                for (int i = 0; i <= steps; ++i)
                {
                    const float th = (float) i / (float) steps * juce::MathConstants<float>::twoPi;
                    const float rr = R * (1.0f - fd * 0.5f * (1.0f + std::cos ((float) N * th)));
                    const float px = cx + std::sin (th) * rr, py = cy - std::cos (th) * rr;
                    if (i == 0) skirt.startNewSubPath (px, py); else skirt.lineTo (px, py);
                }
                skirt.closeSubPath();
                juce::ColourGradient sg (juce::Colour (0xff5c5c60), cx - R * 0.45f, cy - R * 0.55f,
                                         juce::Colour (0xff070708), cx + R * 0.5f, cy + R * 0.65f, false);
                sg.addColour (0.5, juce::Colour (0xff242427));
                g.setGradientFill (sg); g.fillPath (skirt);
                g.setColour (juce::Colours::black.withAlpha (0.85f)); g.strokePath (skirt, juce::PathStrokeType (1.0f));
                // top-left rim sheen
                { juce::Path arc; arc.addCentredArc (cx, cy, R - 1.5f, R - 1.5f, 0.0f,
                    juce::degreesToRadians (-120.0f), juce::degreesToRadians (-15.0f), true);
                  g.setColour (juce::Colours::white.withAlpha (0.20f)); g.strokePath (arc, juce::PathStrokeType (2.0f)); }
                // dark groove + brushed-aluminium cap
                const float capR = R * 0.60f;
                g.setColour (juce::Colour (0xff0b0b0c)); g.fillEllipse (cx - capR - 2.5f, cy - capR - 2.5f, (capR + 2.5f) * 2.0f, (capR + 2.5f) * 2.0f);
                juce::ColourGradient cg (juce::Colour (0xfff6f6f8), cx - capR * 0.2f, cy - capR * 0.28f,
                                         juce::Colour (0xff8a8b8f), cx + capR * 0.45f, cy + capR * 0.65f, true);
                g.setGradientFill (cg); g.fillEllipse (cx - capR, cy - capR, capR * 2.0f, capR * 2.0f);
                // spun/concentric brushed texture
                for (int k = 1; k < 11; ++k)
                { const float rr = capR * (float) k / 11.0f;
                  g.setColour (juce::Colours::white.withAlpha (0.07f)); g.drawEllipse (cx - rr, cy - rr, rr * 2.0f, rr * 2.0f, 0.7f); }
                // soft directional highlight + cap rim
                g.setColour (juce::Colours::white.withAlpha (0.22f));
                g.fillEllipse (cx - capR * 0.55f, cy - capR * 0.62f, capR * 0.7f, capR * 0.45f);
                g.setColour (juce::Colour (0xff5e5e62)); g.drawEllipse (cx - capR, cy - capR, capR * 2.0f, capR * 2.0f, 1.0f);
                // pointer dot on the skirt at the value angle
                const float pr = (R + capR) * 0.5f, pd = R * 0.075f;
                g.setColour (juce::Colours::black.withAlpha (0.5f)); g.fillEllipse (cx + dx * pr - pd, cy + dy * pr - pd + 0.6f, pd * 2.0f, pd * 2.0f);
                g.setColour (juce::Colour (0xfff2f2f4)); g.fillEllipse (cx + dx * pr - pd, cy + dy * pr - pd, pd * 2.0f, pd * 2.0f);
                break;
            }
            case FlutedDark:
            {
                // Oberheim SEM knob: scalloped BLACK knob, dark recessed face, WHITE POINTER line + accent value-arc.
                const float R = disc.getWidth() * 0.5f - 4.0f;
                // value-arc track + fill (accent) just outside the skirt
                { juce::Path tk; tk.addCentredArc (cx, cy, R + 3.5f, R + 3.5f, 0.0f, juce::degreesToRadians (-135.0f), juce::degreesToRadians (135.0f), true);
                  g.setColour (ring.withAlpha (0.18f)); g.strokePath (tk, juce::PathStrokeType (2.0f)); }
                if (v > 0.001f) { juce::Path ap; ap.addCentredArc (cx, cy, R + 3.5f, R + 3.5f, 0.0f, juce::degreesToRadians (-135.0f), ang, true);
                  g.setColour (acc); g.strokePath (ap, juce::PathStrokeType (2.5f, juce::PathStrokeType::curved, juce::PathStrokeType::rounded)); }
                // drop shadow
                g.setColour (juce::Colours::black.withAlpha (0.4f)); g.fillEllipse (cx - R, cy - R + 3.0f, R * 2.0f, R * 2.0f);
                // scalloped black skirt
                const int N = 12; const float fd = 0.10f; const int steps = 220;
                juce::Path skirt;
                for (int i = 0; i <= steps; ++i)
                { const float th = (float) i / (float) steps * juce::MathConstants<float>::twoPi;
                  const float rr = R * (1.0f - fd * 0.5f * (1.0f + std::cos ((float) N * th)));
                  const float px = cx + std::sin (th) * rr, py = cy - std::cos (th) * rr;
                  if (i == 0) skirt.startNewSubPath (px, py); else skirt.lineTo (px, py); }
                skirt.closeSubPath();
                juce::ColourGradient sg (juce::Colour (0xff3c3c40), cx - R * 0.4f, cy - R * 0.5f,
                                         juce::Colour (0xff080809), cx + R * 0.45f, cy + R * 0.6f, false);
                g.setGradientFill (sg); g.fillPath (skirt);
                g.setColour (juce::Colours::black); g.strokePath (skirt, juce::PathStrokeType (1.0f));
                // dark recessed face
                const float fr = R * 0.66f;
                juce::ColourGradient fg (juce::Colour (0xff262629), cx, cy - fr, juce::Colour (0xff09090a), cx, cy + fr, false);
                g.setGradientFill (fg); g.fillEllipse (cx - fr, cy - fr, fr * 2.0f, fr * 2.0f);
                g.setColour (juce::Colours::black.withAlpha (0.6f)); g.drawEllipse (cx - fr, cy - fr, fr * 2.0f, fr * 2.0f, 1.0f);
                g.setColour (juce::Colours::white.withAlpha (0.10f)); g.drawEllipse (cx - fr + 1.5f, cy - fr + 1.5f, (fr - 1.5f) * 2.0f, (fr - 1.5f) * 2.0f, 1.0f);
                // white pointer line
                g.setColour (juce::Colour (0xfff2f2f4));
                g.drawLine (cx + dx * fr * 0.15f, cy + dy * fr * 0.15f, cx + dx * (R - 2.0f), cy + dy * (R - 2.0f), STROKE);
                break;
            }
            case Pointed:
            {
                // STYLE A - FOUR concentric layers (traced from the SEM reference 5.21.53):
                //   1. outer dark BEZEL RING (dark grey dish),
                //   2. a metal GEAR/COG toothed ring (~13 rounded teeth),
                //   3. a distinct BLACK RING / annulus between the cog teeth and the dome,
                //   4. a SMALLER glossy convex BLACK DOME at the centre (black ring visible AROUND it).
                //   Pointer: a small WHITE/silver triangle at the value angle pointing OUTWARD
                //            (tip toward the rim, wide base toward the centre); rotates with value.
                const float Ro  = disc.getWidth() * 0.5f - 2.0f;   // outer bezel radius
                const float pxp = -dy, pyp = dx;                   // perpendicular to pointer dir

                // ---- 1. OUTER DARK BEZEL RING / dish ----
                { juce::ColourGradient dish (juce::Colour (0xff45454a), cx, cy - Ro,
                                             juce::Colour (0xff09090b),  cx, cy + Ro, false);
                  dish.addColour (0.5, juce::Colour (0xff252528));
                  g.setGradientFill (dish); g.fillEllipse (cx - Ro, cy - Ro, Ro * 2.0f, Ro * 2.0f); }
                g.setColour (juce::Colour (0xff020203)); g.drawEllipse (cx - Ro, cy - Ro, Ro * 2.0f, Ro * 2.0f, 1.6f);
                { juce::Path sh; sh.addCentredArc (cx, cy, Ro - 1.5f, Ro - 1.5f, 0.0f,
                    juce::degreesToRadians (-120.0f), juce::degreesToRadians (-20.0f), true);
                  g.setColour (juce::Colours::white.withAlpha (0.10f)); g.strokePath (sh, juce::PathStrokeType (1.4f)); }

                // ---- 2. METAL GEAR / COG toothed ring (~13 rounded teeth) ----
                const float Rk = Ro * 0.84f;                       // cog ring outer radius
                g.setColour (juce::Colours::black.withAlpha (0.5f));
                g.fillEllipse (cx - Rk, cy - Rk + 2.0f, Rk * 2.0f, Rk * 2.0f);
                const int N = 13; const float fd = 0.10f; const int steps = 300;
                juce::Path cog;
                for (int i = 0; i <= steps; ++i)
                { const float th = (float) i / (float) steps * juce::MathConstants<float>::twoPi;
                  const float w  = std::cos ((float) N * th);
                  const float sq = w / std::sqrt (w * w + 0.16f);   // softened square -> flat-topped teeth
                  const float rr = Rk * (1.0f - fd * 0.5f * (1.0f - sq));
                  const float qx = cx + std::sin (th) * rr, qy = cy - std::cos (th) * rr;
                  if (i == 0) cog.startNewSubPath (qx, qy); else cog.lineTo (qx, qy); }
                cog.closeSubPath();
                juce::ColourGradient sg (juce::Colour (0xff4a4a50), cx - Rk * 0.45f, cy - Rk * 0.55f,
                                         juce::Colour (0xff111113), cx + Rk * 0.45f, cy + Rk * 0.6f, false);
                sg.addColour (0.55, juce::Colour (0xff2a2a2e));
                g.setGradientFill (sg); g.fillPath (cog);
                g.setColour (juce::Colours::black.withAlpha (0.85f)); g.strokePath (cog, juce::PathStrokeType (0.8f));
                { juce::Path arc; arc.addCentredArc (cx, cy, Rk - 1.2f, Rk - 1.2f, 0.0f,
                    juce::degreesToRadians (-120.0f), juce::degreesToRadians (-20.0f), true);
                  g.setColour (juce::Colours::white.withAlpha (0.18f)); g.strokePath (arc, juce::PathStrokeType (1.6f)); }

                // ---- 3. distinct BLACK RING / annulus (clearly visible between teeth and dome) ----
                const float Rb = Rk * 0.78f;                        // flat black disc that becomes the ring
                g.setColour (juce::Colour (0xff050506));
                g.fillEllipse (cx - Rb, cy - Rb, Rb * 2.0f, Rb * 2.0f);
                g.setColour (juce::Colours::black); g.drawEllipse (cx - Rb, cy - Rb, Rb * 2.0f, Rb * 2.0f, 1.2f);

                // ---- 4. SMALLER glossy convex BLACK DOME (black ring shows around it) ----
                const float fr = Rb * 0.64f;                        // small enough that ring (3) is visible around
                g.setColour (juce::Colour (0xff020203)); g.fillEllipse (cx - fr - 1.5f, cy - fr - 1.5f, (fr + 1.5f) * 2.0f, (fr + 1.5f) * 2.0f);
                juce::ColourGradient dome (juce::Colour (0xff3a3a41), cx - fr * 0.34f, cy - fr * 0.44f,
                                           juce::Colour (0xff030304), cx + fr * 0.28f, cy + fr * 0.5f, true);
                dome.addColour (0.5, juce::Colour (0xff121216));
                g.setGradientFill (dome); g.fillEllipse (cx - fr, cy - fr, fr * 2.0f, fr * 2.0f);
                { const float hx = cx + fr * 0.32f, hy = cy + fr * 0.40f, hr = fr * 0.40f;
                  juce::ColourGradient glow (juce::Colours::white.withAlpha (0.34f), hx, hy,
                                             juce::Colours::white.withAlpha (0.0f),  hx + hr, hy, true);
                  glow.addColour (0.55, juce::Colours::white.withAlpha (0.07f));
                  g.setGradientFill (glow); g.fillEllipse (hx - hr, hy - hr, hr * 2.0f, hr * 2.0f); }
                g.setColour (juce::Colours::black.withAlpha (0.5f)); g.drawEllipse (cx - fr, cy - fr, fr * 2.0f, fr * 2.0f, 1.0f);

                // ---- POINTER: small WHITE/silver triangle pointing OUTWARD ----
                // TIP toward the rim, wide BASE toward the centre; rotates with value.
                {
                    const float tipR  = Rk * 0.99f;           // tip out near the cog edge (toward rim)
                    const float baseR = Rk * 0.66f;           // wide base sits inward
                    const float halfW = Ro * 0.13f;           // base half-width
                    juce::Path tri;
                    tri.startNewSubPath (cx + dx * tipR, cy + dy * tipR);                     // outward tip
                    tri.lineTo (cx + dx * baseR + pxp * halfW, cy + dy * baseR + pyp * halfW); // base corner
                    tri.lineTo (cx + dx * baseR - pxp * halfW, cy + dy * baseR - pyp * halfW); // base corner
                    tri.closeSubPath();
                    g.setColour (juce::Colours::black.withAlpha (0.5f));
                    g.fillPath (tri, juce::AffineTransform::translation (0.0f, 1.4f));
                    g.setColour (juce::Colour (0xffe9e9ee)); g.fillPath (tri);   // white/silver marker
                    g.setColour (juce::Colour (0xff8d8d94)); g.strokePath (tri, juce::PathStrokeType (0.7f));
                }
                break;
            }
            case Spike:
            {
                // STYLE B (traced from reference 5.23.07):
                //   - a GEAR/COG ring with many fine teeth that ROTATES with the value,
                //   - a FLAT matte-black centre disc,
                //   - a LARGE BLACK triangular SPIKE locked ONTO the knob: drawn ON TOP with its base
                //     sitting on the gear rim (so it reads as moulded on, not floating behind), tip
                //     protruding past the rim. The whole knob turns as one unit with the spike.
                //   The body is shrunk to ~0.66 of the cell so the spike NEVER clips at any angle.
                const float half = disc.getWidth() * 0.5f;
                const float Rk   = half * 0.66f;                   // gear radius (leaves margin for the spike)
                const float pxp = -dy, pyp = dx;                   // perpendicular to pointer dir

                // ---- GEAR / COG ring with many fine teeth (whole gear rotates with the value) ----
                g.setColour (juce::Colours::black.withAlpha (0.4f));
                g.fillEllipse (cx - Rk, cy - Rk + 1.5f, Rk * 2.0f, Rk * 2.0f);
                const int N = 26; const float fd = 0.085f; const int steps = 400;
                juce::Path cog;
                for (int i = 0; i <= steps; ++i)
                { const float th = (float) i / (float) steps * juce::MathConstants<float>::twoPi;
                  const float w  = std::cos ((float) N * th);
                  const float sq = w / std::sqrt (w * w + 0.10f);   // fine flat-topped teeth
                  const float rr = Rk * (1.0f - fd * 0.5f * (1.0f - sq));
                  const float qx = cx + std::sin (th) * rr, qy = cy - std::cos (th) * rr;
                  if (i == 0) cog.startNewSubPath (qx, qy); else cog.lineTo (qx, qy); }
                cog.closeSubPath();
                cog.applyTransform (juce::AffineTransform::rotation (ang, cx, cy));   // turn the whole gear
                juce::ColourGradient sg (juce::Colour (0xff45454a), cx - Rk * 0.45f, cy - Rk * 0.55f,
                                         juce::Colour (0xff0c0c0e), cx + Rk * 0.45f, cy + Rk * 0.6f, false);
                sg.addColour (0.55, juce::Colour (0xff242428));
                g.setGradientFill (sg); g.fillPath (cog);
                g.setColour (juce::Colours::black.withAlpha (0.85f)); g.strokePath (cog, juce::PathStrokeType (0.7f));

                // ---- FLAT matte-black centre disc (minimal sheen) ----
                const float fr = Rk * 0.72f;
                g.setColour (juce::Colour (0xff020203)); g.drawEllipse (cx - fr - 1.0f, cy - fr - 1.0f, (fr + 1.0f) * 2.0f, (fr + 1.0f) * 2.0f, 1.2f);
                g.setColour (juce::Colour (0xff0d0d0f)); g.fillEllipse (cx - fr, cy - fr, fr * 2.0f, fr * 2.0f);
                g.setColour (juce::Colours::white.withAlpha (0.05f));
                g.drawEllipse (cx - fr + 2.0f, cy - fr + 2.0f, (fr - 2.0f) * 2.0f, (fr - 2.0f) * 2.0f, 1.0f);

                // ---- LARGE BLACK SPIKE locked ON TOP (base on the gear rim, tip beyond, never clipped) ----
                {
                    const float baseR = Rk * 0.66f;           // base sits ON the gear -> reads as moulded on
                    const float tipR  = Rk * 1.46f;           // = half*0.96 -> stays inside bounds at any angle
                    const float halfW = Rk * 0.40f;
                    juce::Path sp;
                    sp.startNewSubPath (cx + dx * tipR, cy + dy * tipR);                      // outward tip
                    sp.lineTo (cx + dx * baseR + pxp * halfW, cy + dy * baseR + pyp * halfW); // base corner
                    sp.lineTo (cx + dx * baseR - pxp * halfW, cy + dy * baseR - pyp * halfW); // base corner
                    sp.closeSubPath();
                    g.setColour (juce::Colours::black.withAlpha (0.4f));
                    g.fillPath (sp, juce::AffineTransform::translation (0.0f, 1.8f));
                    g.setColour (juce::Colour (0xff0a0a0c)); g.fillPath (sp);                 // black arrowhead
                    g.setColour (juce::Colour (0xff333338)); g.strokePath (sp, juce::PathStrokeType (0.7f));
                }
                break;
            }
            default: // Pointer
            {
                g.setColour (ring); g.drawEllipse (cx - r, cy - r, r * 2, r * 2, STROKE);
                pointer (0.12f, 0.84f, STROKE);
                break;
            }
        }

        if (showLabel)
        {
            g.setColour (pal.text);
            g.setFont (uiFont (9.5f, true));
            g.drawText (label, getLocalBounds().toFloat().removeFromBottom (labelH), juce::Justification::centred);
        }
    }
    juce::Slider slider;
private:
    static constexpr float labelH = 13.0f;
    InvisibleRotaryLAF laf; juce::String label; Palette pal; int style = 0; bool showLabel = true;
    std::unique_ptr<ParamKnobAttachment> attachment;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StyledKnob)
};

//==============================================================================
// StyledFader - premium vertical fader: recessed gradient track, glowing accent
// fill from the bottom to the thumb, and a beveled thumb with a centre groove.
class StyledFader  : public juce::Component
{
public:
    StyledFader (const juce::String& labelText, const Palette& palette) : label (labelText), pal (palette)
    {
        slider.setSliderStyle (juce::Slider::LinearVertical);
        slider.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
        slider.setLookAndFeel (&laf);
        slider.setRange (0.0, 1.0, 0.0);
        slider.setDoubleClickReturnValue (true, 0.5);
        addAndMakeVisible (slider);
    }
    ~StyledFader() override { slider.setLookAndFeel (nullptr); }
    void attach (juce::AudioProcessorParameter& p)
    {
        att = std::make_unique<ParamKnobAttachment> (p, slider);
        slider.setDoubleClickReturnValue (true, p.getDefaultValue());
        slider.onValueChange = [this] { repaint(); };
        repaint();
    }
    void setShowLabel (bool s) { showLabel = s; }
    juce::Rectangle<float> bodyArea() const
    {
        auto b = getLocalBounds().toFloat();
        if (showLabel) b.removeFromBottom (labelH);
        return b.reduced (0.0f, 8.0f);
    }
    void resized() override
    {
        auto b = getLocalBounds(); if (showLabel) b.removeFromBottom ((int) labelH);
        slider.setBounds (b);
    }
    void paint (juce::Graphics& g) override
    {
        auto ta = bodyArea();
        const float cx = ta.getCentreX(), top = ta.getY(), bot = ta.getBottom(), h = ta.getHeight();
        const float tw = 12.0f;
        juce::Rectangle<float> track (cx - tw * 0.5f, top, tw, h);
        juce::ColourGradient tg (pal.lcdBg.darker (0.2f), cx, top, pal.bg.brighter (0.06f), cx, bot, false);
        g.setGradientFill (tg); g.fillRoundedRectangle (track, tw * 0.5f);
        g.setColour (pal.ink); g.drawRoundedRectangle (track, tw * 0.5f, 1.5f);

        const float v = juce::jlimit (0.0f, 1.0f, (float) slider.getValue());
        const float thumbH = 18.0f, pad = thumbH * 0.5f;
        const float ty = top + pad + (1.0f - v) * (h - 2.0f * pad);
        if (v > 0.001f)
        {
            juce::Rectangle<float> fill (cx - tw * 0.5f, ty, tw, bot - ty);
            g.setColour (pal.accent.withAlpha (0.30f)); g.fillRoundedRectangle (fill.expanded (3.0f, 0.0f), tw * 0.5f + 2.0f);
            juce::ColourGradient fg (pal.accent.brighter (0.2f), cx, ty, pal.accent.darker (0.3f), cx, bot, false);
            g.setGradientFill (fg); g.fillRoundedRectangle (fill, tw * 0.5f);
        }
        const float thumbW = 34.0f;
        juce::Rectangle<float> thumb (cx - thumbW * 0.5f, ty - thumbH * 0.5f, thumbW, thumbH);
        g.setColour (juce::Colours::black.withAlpha (0.4f)); g.fillRoundedRectangle (thumb.translated (0.0f, 2.0f), 4.0f);
        juce::ColourGradient thg (pal.thumb.brighter (0.3f), cx, thumb.getY(), pal.thumb.darker (0.3f), cx, thumb.getBottom(), false);
        g.setGradientFill (thg); g.fillRoundedRectangle (thumb, 4.0f);
        g.setColour (pal.ink); g.drawRoundedRectangle (thumb, 4.0f, 1.5f);
        g.setColour (pal.ink.withAlpha (0.5f)); g.drawLine (thumb.getX() + 5.0f, thumb.getCentreY(), thumb.getRight() - 5.0f, thumb.getCentreY(), 2.0f);

        if (showLabel)
        {
            g.setColour (pal.text); g.setFont (uiFont (9.5f, true));
            g.drawText (label, getLocalBounds().toFloat().removeFromBottom (labelH), juce::Justification::centred);
        }
    }
    juce::Slider slider;
private:
    static constexpr float labelH = 13.0f;
    InvisibleLinearLAF laf; juce::String label; Palette pal; bool showLabel = true;
    std::unique_ptr<ParamKnobAttachment> att;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StyledFader)
};

//==============================================================================
// StyledHSlider - premium HORIZONTAL slider: recessed track, accent fill from the
// left to a beveled thumb. (Same look as StyledFader, rotated.)
class StyledHSlider  : public juce::Component
{
public:
    StyledHSlider (const juce::String& labelText, const Palette& palette) : label (labelText), pal (palette)
    {
        slider.setSliderStyle (juce::Slider::LinearHorizontal);
        slider.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
        slider.setLookAndFeel (&laf);
        slider.setRange (0.0, 1.0, 0.0);
        slider.setDoubleClickReturnValue (true, 0.5);
        addAndMakeVisible (slider);
    }
    ~StyledHSlider() override { slider.setLookAndFeel (nullptr); }
    void attach (juce::AudioProcessorParameter& p)
    {
        att = std::make_unique<ParamKnobAttachment> (p, slider);
        slider.setDoubleClickReturnValue (true, p.getDefaultValue());
        slider.onValueChange = [this] { repaint(); };
        repaint();
    }
    void setShowLabel (bool s) { showLabel = s; }
    void resized() override { slider.setBounds (getLocalBounds()); }
    void paint (juce::Graphics& g) override
    {
        auto b = getLocalBounds().toFloat();
        if (showLabel) g.setColour (pal.text), g.setFont (uiFont (8.5f, true)), g.drawText (label, b.removeFromLeft (44.0f), juce::Justification::centredRight);
        b = b.reduced (6.0f, 0.0f);
        const float cy = b.getCentreY(), th = 9.0f;
        juce::Rectangle<float> track (b.getX(), cy - th * 0.5f, b.getWidth(), th);
        juce::ColourGradient tg (pal.lcdBg.darker (0.2f), b.getX(), cy - th, pal.bg.brighter (0.06f), b.getX(), cy + th, false);
        g.setGradientFill (tg); g.fillRoundedRectangle (track, th * 0.5f);
        g.setColour (pal.ink); g.drawRoundedRectangle (track, th * 0.5f, 1.5f);

        const float v = juce::jlimit (0.0f, 1.0f, (float) slider.getValue());
        const float tw = 14.0f, pad = tw * 0.5f;
        const float tx = track.getX() + pad + v * (track.getWidth() - 2.0f * pad);
        if (v > 0.001f)
        {
            juce::Rectangle<float> fill (track.getX(), cy - th * 0.5f, tx - track.getX(), th);
            g.setColour (pal.accent.withAlpha (0.30f)); g.fillRoundedRectangle (fill.expanded (0.0f, 3.0f), th * 0.5f + 2.0f);
            juce::ColourGradient fg (pal.accent.brighter (0.2f), b.getX(), cy, pal.accent.darker (0.3f), tx, cy, false);
            g.setGradientFill (fg); g.fillRoundedRectangle (fill, th * 0.5f);
        }
        const float thh = 19.0f;
        juce::Rectangle<float> thumb (tx - tw * 0.5f, cy - thh * 0.5f, tw, thh);
        g.setColour (juce::Colours::black.withAlpha (0.4f)); g.fillRoundedRectangle (thumb.translated (1.0f, 1.5f), 3.0f);
        juce::ColourGradient thg (pal.thumb.brighter (0.3f), thumb.getX(), cy, pal.thumb.darker (0.3f), thumb.getRight(), cy, false);
        g.setGradientFill (thg); g.fillRoundedRectangle (thumb, 3.0f);
        g.setColour (pal.ink); g.drawRoundedRectangle (thumb, 3.0f, 1.5f);
        g.setColour (pal.ink.withAlpha (0.5f)); g.drawLine (thumb.getCentreX(), thumb.getY() + 4.0f, thumb.getCentreX(), thumb.getBottom() - 4.0f, 1.5f);
    }
    juce::Slider slider;
private:
    InvisibleLinearLAF laf; juce::String label; Palette pal; bool showLabel = true;
    std::unique_ptr<ParamKnobAttachment> att;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StyledHSlider)
};

//==============================================================================
class Button  : public juce::Button
{
public:
    Button (const juce::String& text, const Palette& palette) : juce::Button (text), pal (palette) { setButtonText (text); }
    void flash()
    {
        flashing = true; repaint();
        juce::Timer::callAfterDelay (160, [safe = juce::Component::SafePointer<Button> (this)]
        { if (safe != nullptr) { safe->flashing = false; safe->repaint(); } });
    }
    void paintButton (juce::Graphics& g, bool over, bool down) override
    {
        auto b = getLocalBounds().toFloat().reduced (1.0f);
        auto fill = flashing ? pal.accent : down ? pal.accent.withAlpha (0.6f) : over ? pal.button.brighter (0.05f) : pal.button;
        g.setColour (fill); g.fillRoundedRectangle (b, 2.0f);
        g.setColour (juce::Colours::black.withAlpha (0.18f)); g.fillRect (b.withTop (b.getBottom() - 3.0f).reduced (2.0f, 0.0f));
        g.setColour (pal.ink); g.drawRoundedRectangle (b, 2.0f, STROKE);
        g.setColour (pal.text); g.setFont (uiFont (juce::jmin (10.0f, b.getHeight() * 0.5f), true));
        g.drawText (getButtonText(), getLocalBounds(), juce::Justification::centred);
    }
private:
    bool flashing = false; Palette pal;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Button)
};

//==============================================================================
class PresetButton  : public juce::Button
{
public:
    enum Shape { Bar, Round };
    PresetButton (int idx, const Palette& palette, Shape sh) : juce::Button ("slot"), index (idx), pal (palette), shape (sh) {}
    void setActive (bool a) { if (active != a) { active = a; repaint(); } }
    void setCorner (float c) { corner = c; }
    void setActiveColour (juce::Colour c) { activeCol = c; }
    void paintButton (juce::Graphics& g, bool over, bool down) override
    {
        juce::ignoreUnused (index);
        auto b = getLocalBounds().toFloat().reduced (1.0f);
        const juce::Colour act = activeCol.isTransparent() ? pal.accent : activeCol;
        auto fill = active ? act : down ? act.withAlpha (0.5f) : over ? pal.button.brighter (0.06f) : pal.button;
        if (shape == Round)
        {
            const float d = std::min (b.getWidth(), b.getHeight()) - STROKE;
            auto c = juce::Rectangle<float> (0, 0, d, d).withCentre (b.getCentre());
            g.setColour (fill); g.fillEllipse (c);
            g.setColour (pal.ink); g.drawEllipse (c, STROKE);
        }
        else
        {
            g.setColour (fill); g.fillRoundedRectangle (b, corner);
            g.setColour (juce::Colours::black.withAlpha (0.18f)); g.fillRect (b.withTop (b.getBottom() - 3.0f).reduced (2.0f, 0.0f));
            g.setColour (pal.ink); g.drawRoundedRectangle (b, corner, STROKE);
        }
    }
private:
    int index; Palette pal; Shape shape; bool active = false; float corner = 1.5f; juce::Colour activeCol { 0x00000000 };
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PresetButton)
};

//==============================================================================
class Lcd  : public juce::Component,
             private juce::Timer
{
public:
    explicit Lcd (const Palette& palette) : pal (palette) {}
    ~Lcd() override { stopTimer(); }
    void setLines (juce::String a, juce::String b) { line1 = std::move (a); line2 = std::move (b); repaint(); }
    void attachScope (AudioTap* t) { tap = t; if (tap) startTimerHz (30); }
    void paint (juce::Graphics& g) override
    {
        auto b = getLocalBounds().toFloat();
        g.setColour (pal.lcdBg); g.fillRoundedRectangle (b, 3.0f);
        if (tap != nullptr) drawScope (g, b.reduced (STROKE));
        g.setColour (pal.ink);   g.drawRoundedRectangle (b.reduced (STROKE * 0.5f), 3.0f, STROKE);
        g.setColour (pal.lcdInk);
        g.setFont (juce::Font (juce::FontOptions (juce::jmin (16.0f, b.getHeight() * 0.42f)).withName ("Menlo")).boldened());
        g.drawText (line1, b.withTrimmedBottom (b.getHeight() * 0.4f), juce::Justification::centred);
        g.setFont (juce::Font (juce::FontOptions (9.0f).withName ("Menlo")));
        g.drawText (line2, b.withTrimmedTop (b.getHeight() * 0.6f), juce::Justification::centred);
    }
private:
    void timerCallback() override { repaint(); }
    void drawScope (juce::Graphics& g, juce::Rectangle<float> r)
    {
        const int N = AudioTap::kRing;
        const int wp = tap->wpos.load (std::memory_order_relaxed);
        const float mid = r.getCentreY();
        const float yScale = r.getHeight() * 0.46f;
        g.setColour (pal.lcdInk.withAlpha (0.16f));
        g.drawLine (r.getX(), mid, r.getRight(), mid, 1.0f);
        juce::Path p;
        const int cols = juce::jmax (2, (int) r.getWidth());
        bool started = false;
        for (int x = 0; x < cols; ++x)
        {
            const float u = (float) x / (float) (cols - 1);
            const int idx = (wp + (int) (u * (N - 1))) % N;
            const float s = tap->ring[(size_t) idx].load (std::memory_order_relaxed);
            const float y = juce::jlimit (r.getY() + 1.0f, r.getBottom() - 1.0f, mid - s * yScale);
            const float px = r.getX() + u * r.getWidth();
            if (! started) { p.startNewSubPath (px, y); started = true; }
            else            p.lineTo (px, y);
        }
        g.setColour (pal.lcdInk.withAlpha (0.85f));
        g.strokePath (p, juce::PathStrokeType (1.4f));
    }
    Palette pal; juce::String line1, line2;
    AudioTap* tap = nullptr;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Lcd)
};

//==============================================================================
class Keyboard  : public juce::Component,
                  private juce::MidiKeyboardState::Listener,
                  private juce::AsyncUpdater
{
public:
    Keyboard (juce::MidiKeyboardState& s, const Palette& palette) : state (s), pal (palette) { state.addListener (this); }
    ~Keyboard() override { state.removeListener (this); cancelPendingUpdate(); }
    void paint (juce::Graphics& g) override
    {
        auto b = getLocalBounds().toFloat();
        const float whiteW = b.getWidth() / (float) kNumWhite, whiteH = b.getHeight();
        const float blackW = whiteW * kBlackWFrac, blackH = whiteH * kBlackHFrac;
        for (int i = 0; i < kNumWhite; ++i)
        {
            const float x = b.getX() + (float) i * whiteW;
            juce::Rectangle<float> r (x, b.getY(), whiteW, whiteH);
            g.setColour (isDown (kWhiteMidi[i]) ? pal.keyWhitePr : pal.keyWhite); g.fillRect (r);
            g.setColour (juce::Colours::black.withAlpha (0.16f));
            g.fillRect (juce::Rectangle<float> (x + STROKE, r.getBottom() - 10.0f, whiteW - STROKE * 2.0f, 8.0f));
        }
        g.setColour (pal.ink); g.drawRect (b, STROKE);
        for (int i = 1; i < kNumWhite; ++i) { const float x = b.getX() + (float) i * whiteW; g.drawLine (x, b.getY(), x, b.getBottom(), STROKE); }
        for (int o : kBlackOffsets)
        {
            const float cx = b.getX() + (float) (o + 1) * whiteW;
            juce::Rectangle<float> r (cx - blackW * 0.5f, b.getY(), blackW, blackH);
            g.setColour (isDown (kWhiteMidi[o] + 1) ? pal.keyBlackPr : pal.keyBlack); g.fillRect (r);
            g.setColour (juce::Colours::black.withAlpha (0.30f));
            g.fillRect (juce::Rectangle<float> (r.getX() + STROKE, r.getBottom() - 7.0f, blackW - STROKE * 2.0f, 5.0f));
            g.setColour (pal.ink); g.drawRect (r, STROKE);
        }
    }
    void mouseDown (const juce::MouseEvent& e) override { setHeld (noteForPoint (e.position)); }
    void mouseDrag (const juce::MouseEvent& e) override { setHeld (noteForPoint (e.position)); }
    void mouseUp   (const juce::MouseEvent&)   override { setHeld (-1); }
private:
    bool isDown (int note) const { return state.isNoteOnForChannels (0xffff, note); }
    int noteForPoint (juce::Point<float> p) const
    {
        auto b = getLocalBounds().toFloat();
        const float whiteW = b.getWidth() / (float) kNumWhite, blackW = whiteW * kBlackWFrac, blackH = b.getHeight() * kBlackHFrac;
        if (p.y - b.getY() <= blackH)
            for (int o : kBlackOffsets) { const float cx = b.getX() + (float) (o + 1) * whiteW; if (std::abs (p.x - cx) <= blackW * 0.5f) return kWhiteMidi[o] + 1; }
        return kWhiteMidi[juce::jlimit (0, kNumWhite - 1, (int) ((p.x - b.getX()) / whiteW))];
    }
    void setHeld (int note)
    {
        if (note == heldNote) return;
        if (heldNote >= 0) state.noteOff (1, heldNote, 0.0f);
        heldNote = note;
        if (heldNote >= 0) state.noteOn (1, heldNote, 0.8f);
    }
    void handleNoteOn  (juce::MidiKeyboardState*, int, int, float) override { triggerAsyncUpdate(); }
    void handleNoteOff (juce::MidiKeyboardState*, int, int, float) override { triggerAsyncUpdate(); }
    void handleAsyncUpdate() override { repaint(); }
    juce::MidiKeyboardState& state; Palette pal; int heldNote = -1;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Keyboard)
};

//==============================================================================
// PanelEditor - the shared TOI frame (chassis, 2-octave keyboard, note strip,
// letterbox scaling, preset save/recall, snapshot) with NO Cmajor dependency.
// Engines subclass it and fill the panel via layoutPanel / paintPanel.
class PanelEditor  : public juce::AudioProcessorEditor
{
public:
    PanelEditor (juce::AudioProcessor& proc, juce::MidiKeyboardState& kb, Config c)
        : juce::AudioProcessorEditor (proc), keyboard (kb, c.pal), cfg (std::move (c))
    {
        store = dynamic_cast<PresetStore*> (&proc);
        addAndMakeVisible (keyboard);
    }

    void paint (juce::Graphics& g) override
    {
        computeGeom();
        g.fillAll (cfg.pal.frame);
        juce::Graphics::ScopedSaveState save (g);
        g.addTransform (juce::AffineTransform::scale (artScale).translated (artOffsetX, artOffsetY));
        drawChassis (g);
        paintPanel (g, panelRect());
        if (! moduleMode_) drawNoteStrip (g);
    }
    void resized() override
    {
        computeGeom();
        keyboard.setVisible (! moduleMode_);
        if (! moduleMode_)
            placeInArtboard (keyboard, juce::Rectangle<float> (innerL, noteStripBottom, innerR - innerL, ART_H - noteStripBottom - border));
        layoutPanel (panelRect());
    }

    // MODULE LED = hide keyboard (panel only); SIZE LED = cycle 100% -> 75% -> 50%.
    void mouseDown (const juce::MouseEvent& e) override
    {
        if (artScale <= 0.0f) return;
        const juce::Point<float> a ((e.position.x - artOffsetX) / artScale,
                                    (e.position.y - artOffsetY) / artScale);
        if      (ledRectModule_.contains (a)) { moduleMode_ = ! moduleMode_;       applyView(); }
        else if (ledRectSize_.contains   (a)) { sizeStep_   = (sizeStep_ + 1) % 3; applyView(); }
    }
    float effArtH()   const { return moduleMode_ ? (TOP_H + border) : ART_H; }
    float viewScale() const { return sizeStep_ == 1 ? 0.75f : sizeStep_ == 2 ? 0.5f : 1.0f; }
    void  applyView()
    {
        setSize (juce::roundToInt (ART_W * viewScale()), juce::roundToInt (effArtH() * viewScale()));
        resized();
        repaint();
    }

protected:
    virtual void layoutPanel (juce::Rectangle<float> panel) = 0;
    virtual void paintPanel  (juce::Graphics& g, juce::Rectangle<float> panel) = 0;
    virtual void setPresetActiveVisual (int) {}

    // ---- optional multi-page (PLAY / EDIT) support for deep editing (premium clones) ----
    virtual int pageCount() const { return 1; }              // >1 enables the page button
    int  page() const { return page_; }
    Button* pageButton() const { return pageBtn_.get(); }    // subclass positions it in layoutPanel

    void finishSetup()
    {
        loadStoredPresets();
        if (pageCount() > 1)
        {
            pageBtn_ = std::make_unique<Button> ("EDIT", cfg.pal);
            pageBtn_->onClick = [this] {
                page_ = (page_ + 1) % pageCount();
                pageBtn_->setButtonText (page_ == 0 ? "EDIT" : "PLAY");
                resized(); repaint();
            };
            addAndMakeVisible (*pageBtn_);
        }
        setSize ((int) ART_W, (int) ART_H);
        maybeArmSnapshot();
    }

    const Config& config() const { return cfg; }
    const Palette& pal() const { return cfg.pal; }
    juce::Rectangle<float> panelRect() const { return { innerL, panelTop, innerR - innerL, panelBottom - panelTop }; }
    int activeSlot() const { return activeSlot_; }

    juce::AudioProcessorParameter* findParam (const juce::String& id) const
    {
        for (auto* p : getAudioProcessor()->getParameters())
        {
            if (auto* hp = dynamic_cast<juce::HostedAudioProcessorParameter*> (p)) { if (hp->getParameterID() == id) return p; }
            else if (auto* wid = dynamic_cast<juce::AudioProcessorParameterWithID*> (p)) { if (wid->paramID == id) return p; }
        }
        return nullptr;
    }
    void bind (Fader& f, const juce::String& id) const { if (auto* p = findParam (id)) f.attach (*p); }
    void bind (Knob&  k, const juce::String& id) const { if (auto* p = findParam (id)) k.attach (*p); }

    void placeInArtboard (juce::Component& c, juce::Rectangle<float> rArt)
    {
        c.setBounds ({ juce::roundToInt (rArt.getX() * artScale + artOffsetX),
                       juce::roundToInt (rArt.getY() * artScale + artOffsetY),
                       juce::roundToInt (rArt.getWidth()  * artScale),
                       juce::roundToInt (rArt.getHeight() * artScale) });
    }

    void recallSlot (int idx)
    {
        std::map<juce::String, float> vals;
        if (store != nullptr && store->loadPreset (idx, vals))
        {
            for (auto& s : cfg.params)
            {
                auto it = vals.find (s.id);
                if (it != vals.end()) if (auto* p = findParam (s.id)) setRealValue (*p, s, it->second);
            }
        }
        else if (idx >= 0 && idx < (int) cfg.factory.size())
        {
            const auto& fp = cfg.factory[(size_t) idx];
            for (size_t i = 0; i < cfg.params.size() && i < fp.vals.size(); ++i)
                if (auto* p = findParam (cfg.params[i].id)) setRealValue (*p, cfg.params[i], fp.vals[i]);
        }
        markActive (idx);
    }
    juce::String presetName (int idx) const
    {
        if (idx >= 0 && idx < (int) cfg.factory.size() && cfg.factory[(size_t) idx].name.isNotEmpty())
            return cfg.factory[(size_t) idx].name;
        return "PRESET " + juce::String (idx + 1);
    }
    AudioTap* audioTap() const
    {
        if (auto* s = dynamic_cast<AudioTapSource*> (getAudioProcessor())) return s->getAudioTap();
        return nullptr;
    }
    void saveSlot (int idx)
    {
        if (store == nullptr) { markActive (idx); return; }
        std::map<juce::String, float> vals;
        for (auto& s : cfg.params)
            if (auto* p = findParam (s.id)) vals[s.id] = s.min + p->getValue() * (s.max - s.min);
        store->savePreset (idx, vals);
        markActive (idx);
    }
    void doRandom()
    {
        auto& rng = juce::Random::getSystemRandom();
        for (auto& s : cfg.params)
            if (auto* p = findParam (s.id))
            {
                const bool atk = s.id.containsIgnoreCase ("attack") || s.id.containsIgnoreCase ("atk")
                              || s.label.containsIgnoreCase ("attack") || s.label.containsIgnoreCase ("atk");
                p->beginChangeGesture();
                p->setValueNotifyingHost (atk ? rng.nextFloat() * 0.30f : rng.nextFloat());   // keep ATTACK snappy - no auto-pads
                p->endChangeGesture();
            }
    }

    void drawBrand (juce::Graphics& g, juce::Rectangle<float> region, bool withButtons,
                    juce::Colour led1 = {}, juce::String lbl1 = {},
                    juce::Colour led2 = {}, juce::String lbl2 = {})
    {
        juce::ignoreUnused (led1, lbl1, led2, lbl2);
        auto r = region.reduced (8.0f, 5.0f);
        if (withButtons) r.removeFromBottom (26.0f);
        auto ledRow = r.removeFromTop (juce::jlimit (22.0f, 32.0f, r.getHeight() * 0.30f));
        drawViewLeds (g, ledRow);
        g.setColour (cfg.pal.ink);
        g.drawLine (region.getX() + 6.0f, ledRow.getBottom(), region.getRight() - 6.0f, ledRow.getBottom(), STROKE);
        auto mark = r.reduced (2.0f, 2.0f);
        const float H = mark.getHeight();
        auto rowM = mark.removeFromTop (H * 0.48f);
        auto rowT = mark.removeFromTop (H * 0.28f);
        auto rowP = mark;
        g.setColour (cfg.pal.text);
        g.setFont (uiFont (juce::jlimit (11.0f, 26.0f, rowM.getHeight() * 0.92f), true));
        g.drawText (cfg.model, rowM, juce::Justification::centred);
        g.setFont (uiFont (juce::jlimit (8.0f, 13.0f, rowT.getHeight() * 0.7f), true).withExtraKerningFactor (0.35f));
        g.drawText ("TOI", rowT, juce::Justification::centred);
        g.setColour (cfg.pal.text.withAlpha (0.8f));
        g.setFont (uiFont (juce::jlimit (6.5f, 8.0f, rowP.getHeight() * 0.62f)).withExtraKerningFactor (0.1f));
        g.drawText ("plugin corp", rowP, juce::Justification::centred);
    }
    // MODULE + SIZE toggle LEDs (clickable) — shared by drawBrand on every faceplate synth.
    void drawViewLeds (juce::Graphics& g, juce::Rectangle<float> ledRow)
    {
        const float cx1 = ledRow.getCentreX() - ledRow.getWidth() * 0.22f;
        const float cx2 = ledRow.getCentreX() + ledRow.getWidth() * 0.22f;
        drawLED (g, cx1, ledRow, cfg.pal.accent2, "MODULE", moduleMode_);
        drawLED (g, cx2, ledRow, cfg.pal.accent,  "SIZE",   sizeStep_ != 0);
        ledRectModule_ = { cx1 - 22.0f, ledRow.getY(), 44.0f, ledRow.getHeight() + 12.0f };
        ledRectSize_   = { cx2 - 22.0f, ledRow.getY(), 44.0f, ledRow.getHeight() + 12.0f };
    }
    void drawLED (juce::Graphics& g, float cx, juce::Rectangle<float> row, juce::Colour c, const juce::String& lbl, bool active = true)
    {
        const float r = 5.5f;
        const float cy = row.getY() + r + 2.0f;
        if (active) { g.setColour (c.withAlpha (0.5f)); g.fillEllipse (cx - r - 3.0f, cy - r - 3.0f, (r + 3.0f) * 2.0f, (r + 3.0f) * 2.0f); }
        g.setColour (active ? c : c.withAlpha (0.28f)); g.fillEllipse (cx - r, cy - r, r * 2.0f, r * 2.0f);
        g.setColour (cfg.pal.ink);        g.drawEllipse (cx - r, cy - r, r * 2.0f, r * 2.0f, STROKE);
        g.setColour (cfg.pal.text);       g.setFont (uiFont (7.0f, true).withExtraKerningFactor (0.02f));
        g.drawText (lbl, juce::Rectangle<float> (cx - 28.0f, cy + r + 1.0f, 56.0f, juce::jmax (8.0f, row.getBottom() - (cy + r + 1.0f))), juce::Justification::centredTop);
    }

    float border = STROKE + 0.5f, panelTop = STROKE + 0.5f, panelBottom = TOP_H;
    float innerL = STROKE + 0.5f, innerR = ART_W - STROKE - 0.5f, noteStripBottom = TOP_H + NOTE_H;
    bool moduleMode_ = false;
    int  sizeStep_ = 0;   // 0=100% 1=75% 2=50%
    juce::Rectangle<float> ledRectModule_, ledRectSize_;

private:
    void computeGeom()
    {
        artScale   = juce::jmin ((float) getWidth() / ART_W, (float) getHeight() / effArtH());
        artOffsetX = (getWidth()  - ART_W * artScale) * 0.5f;
        artOffsetY = (getHeight() - effArtH() * artScale) * 0.5f;
        border = STROKE + 0.5f; panelTop = border; panelBottom = TOP_H;
        innerL = border; innerR = ART_W - border; noteStripBottom = panelBottom + NOTE_H;
    }
    void drawChassis (juce::Graphics& g)
    {
        juce::Rectangle<float> art (0.0f, 0.0f, ART_W, effArtH());
        g.setColour (cfg.pal.ink); g.fillRoundedRectangle (art, 10.0f);
        auto inner = art.reduced (border);
        if (! cfg.pal.bg2.isTransparent())
        {
            juce::ColourGradient grad (cfg.pal.bg, inner.getCentreX(), inner.getY(),
                                       cfg.pal.bg2, inner.getX(), inner.getBottom(), true);  // radial: top-centre highlight
            g.setGradientFill (grad);
        }
        else g.setColour (cfg.pal.bg);
        g.fillRoundedRectangle (inner, 6.5f);
    }
    void drawNoteStrip (juce::Graphics& g)
    {
        g.setColour (cfg.pal.ink);
        g.drawLine (0.0f, panelBottom, ART_W, panelBottom, STROKE);
        g.drawLine (0.0f, noteStripBottom, ART_W, noteStripBottom, STROKE);
        g.setColour (cfg.pal.text);
        g.setFont (uiFont (10.0f, true));
        const float whiteW = (innerR - innerL) / 15.0f;
        for (int i = 0; i < 15; ++i)
            g.drawText (kWhiteNames[i], juce::Rectangle<float> (innerL + (float) i * whiteW, panelBottom, whiteW, noteStripBottom - panelBottom), juce::Justification::centred);
    }
    void maybeArmSnapshot()
    {
        if (juce::SystemStats::getEnvironmentVariable ("TOI_SNAPSHOT_DIR", {}).isEmpty()) return;
        if (auto* p = getAudioProcessor())
            if (p->wrapperType == juce::AudioProcessor::wrapperType_Standalone)
            {
                juce::Component::SafePointer<PanelEditor> safe (this);
                juce::Timer::callAfterDelay (500, [safe]() mutable { if (safe != nullptr) safe->doSnapshot(); });
            }
    }
    void doSnapshot()
    {
        const auto dir = juce::SystemStats::getEnvironmentVariable ("TOI_SNAPSHOT_DIR", {});
        if (dir.isNotEmpty())
        {
            const auto view = juce::SystemStats::getEnvironmentVariable ("TOI_SNAPSHOT_VIEW", {});
            moduleMode_ = view.containsIgnoreCase ("module") || view.containsIgnoreCase ("both");
            sizeStep_   = view.containsIgnoreCase ("size75") ? 1
                        : (view.containsIgnoreCase ("size50") || view.containsIgnoreCase ("size") || view.containsIgnoreCase ("both")) ? 2 : 0;
            juce::File outDir (dir);
            outDir.createDirectory();
            for (int pg = 0; pg < pageCount(); ++pg)        // capture every page (PLAY, EDIT, ...)
            {
                page_ = pg;
                setSize (juce::roundToInt (ART_W * viewScale()), juce::roundToInt (effArtH() * viewScale()));
                resized();
                auto img = createComponentSnapshot (getLocalBounds(), false, 2.0f);
                juce::File out = outDir.getChildFile (cfg.model + (pg == 0 ? juce::String() : "-p" + juce::String (pg)) + ".png");
                out.deleteFile();
                if (auto fos = out.createOutputStream())
                    juce::PNGImageFormat().writeImageToStream (img, *fos);
            }
            page_ = 0;
        }
        juce::JUCEApplicationBase::quit();
    }

    void markActive (int idx) { activeSlot_ = idx; setPresetActiveVisual (idx); }
    void loadStoredPresets()
    {
        for (int i = 0; i < 16; ++i) if (store != nullptr && store->hasPreset (i)) { markActive (i); return; }
        markActive (0);
    }
    static void setRealValue (juce::AudioProcessorParameter& p, const ParamSpec& s, float real)
    {
        const float norm = (s.max > s.min) ? juce::jlimit (0.0f, 1.0f, (real - s.min) / (s.max - s.min)) : 0.0f;
        p.beginChangeGesture(); p.setValueNotifyingHost (norm); p.endChangeGesture();
    }

    Keyboard keyboard;
    PresetStore* store = nullptr;
    Config cfg;
    int activeSlot_ = 0;
    int page_ = 0;
    std::unique_ptr<Button> pageBtn_;
    float artScale = 1.0f, artOffsetX = 0.0f, artOffsetY = 0.0f;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PanelEditor)
};

} // namespace toi
