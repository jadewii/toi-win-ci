// JW-JUP native faceplate (luxury 8-voice analog poly) on the toi_faceplate.h kit.
// PHOTOREAL hardware style (Jade ref 2026-05-27): brushed-SILVER end-cheeks, a DARK TEXTURED
// panel, ORANGE section header bars, flat-BLACK-thumb sliders with labels ABOVE, and SELECTORS
// as rows of colour-coded beveled buttons with LED dots (tan waves / gold range / green slope /
// blue LFO waveforms w/ icons). Cream LED toggles, thin section dividers, RAND=yellow SAVE=green.
// TWO PAGES (OSC / FILTER) for long slider throw. NO brand names. EVERY param wired.
#pragma once

#include "toi_faceplate.h"

struct JUP;

namespace jup
{
    static const juce::Colour kSilver { 0xffb9bdc2 };   // brushed-silver end-cheeks
    static const juce::Colour kSilverLo{ 0xff8d9197 };  // darker silver (gradient)
    static const juce::Colour kPanel  { 0xff2a2725 };   // DARK warm textured panel
    static const juce::Colour kPanelLo{ 0xff211e1c };   // panel gradient bottom
    static const juce::Colour kFrame  { 0xff050506 };   // near-black frame + outlines
    static const juce::Colour kOrange { 0xffe0691c };   // the signature Roland orange (section bars)
    static const juce::Colour kOrangeHi{ 0xffff8a39 };
    static const juce::Colour kRed    { 0xffd8392b };   // lit LED dots
    static const juce::Colour kScope  { 0xffff3b2e };   // RED waveform scope
    static const juce::Colour kTan    { 0xffd6c194 };   // wave-select buttons
    static const juce::Colour kGold   { 0xffe0bc4e };   // range/octave buttons
    static const juce::Colour kGreen  { 0xff7ec850 };   // slope buttons
    static const juce::Colour kBlue   { 0xff6573c4 };   // LFO waveform buttons
    static const juce::Colour kCream  { 0xffe7e2d4 };   // toggle / preset buttons
    static const juce::Colour kBtnGrn { 0xff8cd645 };   // SAVE button
    static const juce::Colour kBtnYel { 0xfff3e863 };   // RAND button
    static const juce::Colour kWhite  { 0xffe9e6df };   // screened white labels
    static const juce::Colour kWhiteDim{ 0xff9a958c };

    // small waveform icon for the LFO selector (type: 0 sine, 1 square, 2 saw, 3 sample&hold)
    inline void waveIcon (juce::Graphics& g, juce::Rectangle<float> r, int type, juce::Colour c)
    {
        r = r.reduced (r.getWidth() * 0.18f, r.getHeight() * 0.28f);
        const float x0 = r.getX(), x1 = r.getRight(), y = r.getCentreY(), a = r.getHeight() * 0.5f;
        juce::Path p; g.setColour (c);
        if (type == 0) { const int N = 24; for (int i = 0; i <= N; ++i) { const float t = (float) i / N; const float px = x0 + t * (x1 - x0); const float py = y - std::sin (t * juce::MathConstants<float>::twoPi) * a; if (i == 0) p.startNewSubPath (px, py); else p.lineTo (px, py); } }
        else if (type == 1) { p.startNewSubPath (x0, y + a); p.lineTo (x0, y - a); p.lineTo (r.getCentreX(), y - a); p.lineTo (r.getCentreX(), y + a); p.lineTo (x1, y + a); p.lineTo (x1, y - a); }
        else if (type == 2) { p.startNewSubPath (x0, y + a); p.lineTo (x1, y - a); p.lineTo (x1, y + a); }
        else { const float s = (x1 - x0) / 4.0f; float yy[4] = { 0.4f, -0.7f, 0.1f, -0.3f }; for (int i = 0; i < 4; ++i) { p.startNewSubPath (x0 + i * s, y - yy[i] * a); p.lineTo (x0 + (i + 1) * s, y - yy[i] * a); } }
        g.strokePath (p, juce::PathStrokeType (1.4f, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
    }
}

//==============================================================================
// Slider with the label ABOVE, a thin dark recessed track, and a wide FLAT-BLACK thumb.
class StyleFader  : public juce::Component
{
public:
    StyleFader (const juce::String& labelText, const toi::Palette& palette) : label (labelText), pal (palette)
    {
        slider.setSliderStyle (juce::Slider::LinearVertical);
        slider.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
        slider.setLookAndFeel (&laf);
        slider.setRange (0.0, 1.0, 0.0);
        slider.setDoubleClickReturnValue (true, 0.5);
        addAndMakeVisible (slider);
    }
    ~StyleFader() override { slider.setLookAndFeel (nullptr); }
    void attach (juce::AudioProcessorParameter& p)
    { att = std::make_unique<toi::ParamKnobAttachment> (p, slider); slider.setDoubleClickReturnValue (true, p.getDefaultValue()); slider.onValueChange = [this] { repaint(); }; repaint(); }
    void resized() override { slider.setBounds (getLocalBounds().withTrimmedTop ((int) labelH)); }
    void paint (juce::Graphics& g) override
    {
        auto b = getLocalBounds().toFloat();
        auto la = b.removeFromTop (labelH);
        g.setColour (pal.text); g.setFont (toi::uiFont (8.0f, true).withExtraKerningFactor (0.04f));
        g.drawText (label, la, juce::Justification::centred);
        auto ta = b.reduced (0.0f, 5.0f);
        const float cx = ta.getCentreX(), top = ta.getY(), bot = ta.getBottom(), h = ta.getHeight();
        // thin LIGHT vertical track line (as on the hardware - ref image #20)
        g.setColour (juce::Colours::black.withAlpha (0.5f)); g.drawLine (cx, top, cx, bot, 3.0f);
        g.setColour (juce::Colour (0xffadb2ba)); g.drawLine (cx, top + 1.0f, cx, bot - 1.0f, 1.6f);

        const float v = juce::jlimit (0.0f, 1.0f, (float) slider.getValue());
        const float thumbH = 13.0f, thumbW = 26.0f, pad = thumbH * 0.5f;
        const float ty = top + pad + (1.0f - v) * (h - 2.0f * pad);
        juce::Rectangle<float> thumb (cx - thumbW * 0.5f, ty - thumbH * 0.5f, thumbW, thumbH);
        g.setColour (juce::Colours::black.withAlpha (0.5f)); g.fillRoundedRectangle (thumb.translated (0.0f, 2.0f), 2.5f);
        juce::ColourGradient tg (juce::Colour (0xff3d3d3f), cx, thumb.getY(), juce::Colour (0xff070708), cx, thumb.getBottom(), false);
        tg.addColour (0.5, juce::Colour (0xff19191b));
        g.setGradientFill (tg); g.fillRoundedRectangle (thumb, 2.5f);
        g.setColour (juce::Colour (0xff040405)); g.drawRoundedRectangle (thumb, 2.5f, 1.0f);
        g.setColour (juce::Colours::white.withAlpha (0.28f)); g.drawLine (thumb.getX() + 3.0f, thumb.getY() + 1.6f, thumb.getRight() - 3.0f, thumb.getY() + 1.6f, 1.0f);
        g.setColour (juce::Colours::white.withAlpha (0.92f)); g.drawLine (thumb.getX() + 3.5f, thumb.getCentreY(), thumb.getRight() - 3.5f, thumb.getCentreY(), 1.6f);   // WHITE centre line (ref image #19)
    }
    juce::Slider slider;
private:
    static constexpr float labelH = 13.0f;
    toi::InvisibleLinearLAF laf; juce::String label; toi::Palette pal;
    std::unique_ptr<toi::ParamKnobAttachment> att;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StyleFader)
};

//==============================================================================
// Single-select row of colour-coded beveled buttons with LED dots (the reference selector look).
// Bound to a 0..1 param mapped to N zones. iconSet 1 = draw LFO waveform icons instead of labels.
class OptRow  : public juce::Component
{
public:
    OptRow (juce::StringArray nm, juce::Colour base, juce::String grp, int iconSet, const toi::Palette& palette)
        : names (std::move (nm)), col (base), group (std::move (grp)), icons (iconSet), pal (palette) {}
    void bindTo (juce::AudioProcessorParameter* p)
    { param_ = p; if (! p) return; slider.setRange (0.0, 1.0, 0.0); attach = std::make_unique<toi::ParamKnobAttachment> (*p, slider); addChildComponent (slider); slider.setVisible (false); }
    int count() const { return names.size(); }
    int idx() const { const float v = param_ ? param_->getValue() : (float) slider.getValue(); return juce::jlimit (0, count() - 1, (int) (v * (float) count())); }
    juce::Rectangle<float> rowArea() const { auto b = getLocalBounds().toFloat(); b.removeFromTop (11.0f); return b; }
    void mouseDown (const juce::MouseEvent& e) override
    {
        auto row = rowArea(); const float cw = row.getWidth() / (float) count();
        const int i = juce::jlimit (0, count() - 1, (int) ((e.position.x - row.getX()) / cw));
        slider.setValue ((i + 0.5) / (double) count(), juce::sendNotificationSync); repaint();
    }
    void paint (juce::Graphics& g) override
    {
        auto b = getLocalBounds().toFloat();
        auto la = b.removeFromTop (11.0f);
        if (group.isNotEmpty()) { g.setColour (pal.text.withAlpha (0.75f)); g.setFont (toi::uiFont (7.0f, true).withExtraKerningFactor (0.10f)); g.drawText (group, la, juce::Justification::centred); }
        const int n = count(); const float cw = b.getWidth() / (float) n;
        const int sel = idx();
        for (int i = 0; i < n; ++i)
        {
            auto cell = juce::Rectangle<float> (b.getX() + i * cw, b.getY(), cw, b.getHeight()).reduced (1.5f, 1.0f);
            const bool on = (i == sel);
            auto base = on ? col.brighter (0.10f) : col.darker (0.30f);
            juce::ColourGradient bg (base.brighter (0.12f), cell.getCentreX(), cell.getY(), base.darker (0.18f), cell.getCentreX(), cell.getBottom(), false);
            g.setGradientFill (bg); g.fillRoundedRectangle (cell, 2.5f);
            g.setColour (juce::Colours::black.withAlpha (0.45f)); g.drawRoundedRectangle (cell, 2.5f, 1.0f);
            g.setColour (juce::Colours::white.withAlpha (on ? 0.32f : 0.16f)); g.drawLine (cell.getX() + 2.0f, cell.getY() + 1.2f, cell.getRight() - 2.0f, cell.getY() + 1.2f, 1.0f);
            // LED dot near the top
            const float d = 3.4f; auto led = juce::Rectangle<float> (0, 0, d, d).withCentre ({ cell.getCentreX(), cell.getY() + 5.0f });
            if (on) { g.setColour (jup::kRed.withAlpha (0.5f)); g.fillEllipse (led.expanded (1.6f)); }
            g.setColour (on ? jup::kRed.brighter (0.2f) : juce::Colour (0xff3a2a22)); g.fillEllipse (led);
            // icon or text below the LED
            auto body = cell.withTrimmedTop (8.0f);
            if (icons == 1) jup::waveIcon (g, body, i, juce::Colour (0xff201810));
            else { g.setColour (juce::Colour (0xff241c12)); g.setFont (toi::uiFont (juce::jmin (8.5f, body.getHeight() * 0.6f), true)); g.drawText (names[i], body, juce::Justification::centred); }
        }
    }
private:
    juce::StringArray names; juce::Colour col; juce::String group; int icons;
    toi::Palette pal;
    juce::Slider slider; std::unique_ptr<toi::ParamKnobAttachment> attach; juce::AudioProcessorParameter* param_ = nullptr;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OptRow)
};

//==============================================================================
// On/off beveled button with a label above + LED dot (lit when on). Cream like the JP-8 buttons.
class StyleToggle  : public juce::Component
{
public:
    StyleToggle (juce::String labelText, const toi::Palette& palette) : label (std::move (labelText)), pal (palette) {}
    void bindTo (juce::AudioProcessorParameter* p)
    { param_ = p; if (! p) return; slider.setRange (0.0, 1.0, 0.0); attach = std::make_unique<toi::ParamKnobAttachment> (*p, slider); addChildComponent (slider); slider.setVisible (false); }
    bool on() const { return (param_ ? param_->getValue() : (float) slider.getValue()) >= 0.5f; }
    void mouseDown (const juce::MouseEvent&) override { slider.setValue (on() ? 0.0 : 1.0, juce::sendNotificationSync); repaint(); }
    void paint (juce::Graphics& g) override
    {
        auto b = getLocalBounds().toFloat();
        auto la = b.removeFromTop (11.0f);
        g.setColour (pal.text.withAlpha (0.75f)); g.setFont (toi::uiFont (7.0f, true)); g.drawText (label, la, juce::Justification::centred);
        auto cell = b.reduced (1.5f, 1.0f);
        const bool o = on();
        auto base = o ? jup::kCream : jup::kCream.darker (0.30f);
        juce::ColourGradient bg (base.brighter (0.10f), cell.getCentreX(), cell.getY(), base.darker (0.16f), cell.getCentreX(), cell.getBottom(), false);
        g.setGradientFill (bg); g.fillRoundedRectangle (cell, 2.5f);
        g.setColour (juce::Colours::black.withAlpha (0.45f)); g.drawRoundedRectangle (cell, 2.5f, 1.0f);
        const float d = 4.0f; auto led = juce::Rectangle<float> (0, 0, d, d).withCentre ({ cell.getCentreX(), cell.getCentreY() });
        if (o) { g.setColour (jup::kRed.withAlpha (0.5f)); g.fillEllipse (led.expanded (2.0f)); }
        g.setColour (o ? jup::kRed.brighter (0.2f) : juce::Colour (0xff5a3a30)); g.fillEllipse (led);
        g.setColour (juce::Colours::black.withAlpha (0.4f)); g.drawEllipse (led, 0.6f);
    }
private:
    juce::String label; toi::Palette pal;
    juce::Slider slider; std::unique_ptr<toi::ParamKnobAttachment> attach; juce::AudioProcessorParameter* param_ = nullptr;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StyleToggle)
};

//==============================================================================
// Coloured function button (RAND yellow / SAVE green) with DARK text + flash.
class JupFuncButton  : public juce::Button
{
public:
    JupFuncButton (const juce::String& text, juce::Colour fill) : juce::Button (text), col (fill) { setButtonText (text); }
    void flash() { flashing = true; repaint(); juce::Timer::callAfterDelay (160, [s = juce::Component::SafePointer<JupFuncButton> (this)] { if (s) { s->flashing = false; s->repaint(); } }); }
    void paintButton (juce::Graphics& g, bool over, bool down) override
    {
        auto b = getLocalBounds().toFloat().reduced (1.0f);
        auto fill = flashing ? col.brighter (0.35f) : down ? col.darker (0.18f) : over ? col.brighter (0.08f) : col;
        g.setColour (fill); g.fillRoundedRectangle (b, 2.5f);
        g.setColour (juce::Colours::black.withAlpha (0.22f)); g.fillRect (b.withTop (b.getBottom() - 3.0f).reduced (2.0f, 0.0f));
        g.setColour (juce::Colours::black.withAlpha (0.4f)); g.drawRoundedRectangle (b, 2.5f, 1.2f);
        g.setColour (juce::Colour (0xff20160a)); g.setFont (toi::uiFont (juce::jmin (10.0f, b.getHeight() * 0.5f), true));
        g.drawText (getButtonText(), getLocalBounds(), juce::Justification::centred);
    }
private:
    juce::Colour col; bool flashing = false;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JupFuncButton)
};

//==============================================================================
// Programmer preset button: cream domed square with an orange LED.
class JupPreset  : public juce::Button
{
public:
    explicit JupPreset (const toi::Palette&) : juce::Button ("preset") {}
    void setActive (bool a) { if (active != a) { active = a; repaint(); } }
    void paintButton (juce::Graphics& g, bool over, bool down) override
    {
        auto b = getLocalBounds().toFloat().reduced (1.0f);
        const float base = over ? 0.08f : 0.0f;
        juce::ColourGradient cap (juce::Colour (0xffe7e2d4).brighter (base), b.getCentreX(), b.getY(), juce::Colour (0xffb9b4a6), b.getCentreX(), b.getBottom(), false);
        g.setGradientFill (cap); g.fillRoundedRectangle (b, 2.0f);
        if (down) { g.setColour (juce::Colours::black.withAlpha (0.16f)); g.fillRoundedRectangle (b, 2.0f); }
        g.setColour (juce::Colours::white.withAlpha (0.5f)); g.drawLine (b.getX() + 1.5f, b.getY() + 1.0f, b.getRight() - 1.5f, b.getY() + 1.0f, 1.0f);
        g.setColour (juce::Colours::black.withAlpha (0.4f)); g.drawRoundedRectangle (b, 2.0f, 1.0f);
        const float d = juce::jmin (b.getWidth(), b.getHeight()) * 0.30f;
        auto led = juce::Rectangle<float> (0, 0, d, d).withCentre ({ b.getCentreX(), b.getY() + d * 1.05f });
        g.setColour (active ? jup::kOrange.brighter (0.2f) : juce::Colour (0xff5a4632));
        g.fillEllipse (led);
        if (active) { g.setColour (jup::kOrangeHi.withAlpha (0.8f)); g.fillEllipse (led.reduced (d * 0.3f)); }
        g.setColour (juce::Colours::black.withAlpha (0.5f)); g.drawEllipse (led, 0.6f);
    }
private:
    bool active = false;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JupPreset)
};

//==============================================================================
inline toi::Config jupConfig()
{
    toi::Config c;
    c.model = "JW-JUP";
    auto& p = c.pal;
    p.bg = jup::kSilver; p.bg2 = jup::kSilverLo; p.frame = jup::kFrame; p.ink = jup::kFrame;
    p.accent = jup::kOrange; p.accent2 = jup::kOrange; p.button = juce::Colour (0xff1a1b1e);
    p.thumb = juce::Colour (0xff141416); p.text = jup::kWhite;
    p.lcdBg = juce::Colour (0xff0c0a08); p.lcdInk = jup::kScope;
    p.noteStrip = jup::kPanel;
    p.keyWhite = juce::Colour (0xffEDEDEA); p.keyWhitePr = juce::Colour (0xfff2cf9a);
    p.keyBlack = juce::Colour (0xff141210); p.keyBlackPr = jup::kOrange;

    c.params = {
        { "lfoRate","RATE" }, { "lfoDelay","DELAY" }, { "lfoShape","SHAPE" }, { "lfoDepth","DEPTH" },
        { "lfoPitch","PITCH" }, { "lfoPwm","PWM" }, { "lfoFilt","FILT" },
        { "o1Range","RANGE" }, { "o1Wave","WAVE" },
        { "o2Range","RANGE" }, { "o2Fine","DETUNE" }, { "o2Wave","WAVE" }, { "sync","SYNC" }, { "crossMod","X-MOD" },
        { "pwm","PW" }, { "pwmMode","MANUAL" },
        { "mix1","VCO1" }, { "mix2","VCO2" },
        { "hpf","HPF" },
        { "cutoff","CUTOFF" }, { "reso","RES" }, { "slope","SLOPE" }, { "filtEnv","ENV" }, { "filtPol","INV" }, { "filtKbd","KYBD" },
        { "fA","A" }, { "fD","D" }, { "fS","S" }, { "fR","R" },
        { "aA","A" }, { "aD","D" }, { "aS","S" }, { "aR","R" },
        { "detune","DETUNE" }, { "glide","GLIDE" }, { "volume","VOLUME" }, { "tune","TUNE" },
    };

    auto P = [] (const char* nm,
                 float lfoDepth,float lfoPitch,float lfoPwm,float lfoFilt,
                 float o1Wave, float o2Range,float o2Fine,float o2Wave,float sync,float crossMod,
                 float pwm,float pwmMode, float mix1,float mix2, float hpf,
                 float cut,float res,float slope,float fenv,float fpol,float fkbd,
                 float fA,float fD,float fS,float fR, float aA,float aD,float aS,float aR, float detune)
    {
        return toi::FactoryPreset { nm, {
            0.30f,0.0f,0.0f,lfoDepth,lfoPitch,lfoPwm,lfoFilt,
            0.5f,o1Wave, o2Range,o2Fine,o2Wave,sync,crossMod,
            pwm,pwmMode, mix1,mix2, hpf,
            cut,res,slope,fenv,fpol,fkbd,
            fA,fD,fS,fR, aA,aD,aS,aR, detune,0.0f,0.80f,0.50f } };
    };
    c.factory = {
        P("BRASS",     0.0,0.0,0.0,0.0, 0.0, 0.5,0.52,0.0,0.0,0.0, 0.5,1.0, 0.8,0.7, 0.0, 0.48,0.18,1.0,0.55,0.0,0.4, 0.06,0.45,0.5,0.35,0.04,0.4,0.85,0.3, 0.2),
        P("STRINGS",   0.3,0.0,1.0,0.0, 0.33,0.5,0.55,0.33,0.0,0.0,0.5,0.0, 0.7,0.7, 0.3, 0.52,0.14,0.0,0.30,0.0,0.5, 0.5,0.6,0.85,0.7, 0.45,0.6,0.85,0.7, 0.45),
        P("LUSH PAD",  0.25,0.0,1.0,0.0,0.33,0.5,0.56,0.33,0.0,0.0,0.5,0.0,0.7,0.7, 0.0, 0.45,0.18,0.0,0.40,0.0,0.5, 0.5,0.6,0.85,0.75,0.45,0.6,0.85,0.75,0.5),
        P("SYNC LEAD", 0.1,0.0,0.0,0.0, 0.0, 0.62,0.40,0.0,1.0,0.0,0.5,1.0,0.85,0.6,0.0,0.62,0.30,1.0,0.55,0.0,0.5, 0.02,0.4,0.7,0.3, 0.02,0.5,0.85,0.25,0.15),
        P("BELL XMOD", 0.0,0.0,0.0,0.0, 0.0, 0.7,0.62,0.0,0.0,0.6,0.5,1.0,0.7,0.6,0.2, 0.55,0.25,1.0,0.50,0.0,0.5, 0.02,0.5,0.2,0.4, 0.02,0.5,0.4,0.4,0.2),
        P("FUNK STAB", 0.0,0.0,0.0,0.0, 0.0, 0.5,0.51,0.33,0.0,0.0,0.5,1.0,0.8,0.7,0.33,0.42,0.30,1.0,0.65,0.0,0.4,0.02,0.3,0.2,0.2,0.02,0.32,0.6,0.2,0.18),
        P("DEEP BASS", 0.0,0.0,0.0,0.0, 0.0, 0.38,0.49,0.0,0.0,0.0,0.5,1.0,0.8,0.6,0.0, 0.36,0.25,1.0,0.55,0.0,0.4,0.02,0.3,0.1,0.2,0.02,0.34,0.2,0.2,0.1),
        P("PWM POLY",  0.35,0.0,1.0,0.0,0.33,0.5,0.52,0.33,0.0,0.0,0.5,0.0,0.75,0.7,0.0,0.50,0.16,0.0,0.35,0.0,0.5,0.3,0.5,0.7,0.6,0.25,0.5,0.8,0.6,0.4),
        P("AIRY 12dB", 0.2,0.0,1.0,0.0,0.0, 0.5,0.55,0.0,0.0,0.0,0.5,0.0,0.7,0.65,0.4,0.55,0.20,0.0,0.35,0.0,0.5,0.4,0.6,0.7,0.6,0.3,0.6,0.8,0.6,0.4),
        P("OCT BRASS", 0.0,0.0,0.0,0.0, 0.0, 0.75,0.52,0.0,0.0,0.0,0.5,1.0,0.8,0.7,0.0,0.48,0.20,1.0,0.55,0.0,0.4,0.05,0.45,0.6,0.35,0.04,0.45,0.8,0.3,0.3),
        P("SWEEP PAD", 0.2,0.0,0.0,1.0,0.33,0.5,0.55,0.33,0.0,0.0,0.5,0.0,0.7,0.7,0.0,0.30,0.40,0.0,0.70,0.0,0.5,0.4,0.7,0.4,0.5,0.3,0.6,0.7,0.6,0.5),
        P("LIQUID SYNC",0.1,0.0,0.0,0.0,0.0,0.55,0.42,0.0,1.0,0.2,0.5,1.0,0.85,0.5,0.0,0.58,0.35,0.0,0.55,0.0,0.5,0.02,0.5,0.6,0.4,0.02,0.6,0.7,0.4,0.2),
        P("SOFT KEYS", 0.1,0.0,1.0,0.0,0.33,0.5,0.53,0.33,0.0,0.0,0.5,0.0,0.75,0.6,0.0,0.50,0.18,1.0,0.45,0.0,0.5,0.02,0.45,0.4,0.4,0.02,0.45,0.4,0.4,0.3),
        P("NEG SWEEP", 0.0,0.0,0.0,0.0,0.0, 0.5,0.50,0.0,0.0,0.0,0.5,1.0,0.8,0.7,0.0,0.55,0.30,1.0,0.55,1.0,0.4,0.02,0.5,0.5,0.3,0.02,0.5,0.85,0.3,0.2),
        P("WIDE DREAM",0.3,0.0,1.0,1.0,0.33,0.5,0.57,0.33,0.0,0.0,0.5,0.0,0.7,0.7,0.0,0.44,0.20,0.0,0.45,0.0,0.5,0.6,0.7,0.85,0.8,0.6,0.7,0.85,0.8,0.6),
        P("SYNTH ORGAN",0.0,0.0,0.0,0.0,0.33,0.75,0.50,0.33,0.0,0.0,0.5,1.0,0.75,0.7,0.0,0.62,0.14,0.0,0.10,0.0,0.6,0.02,0.5,1.0,0.3,0.02,0.5,1.0,0.3,0.2),
    };
    return c;
}

//==============================================================================
class JupEditor  : public toi::PanelEditor
{
public:
    JupEditor (juce::AudioProcessor& proc, juce::MidiKeyboardState& kb)
        : toi::PanelEditor (proc, kb, jupConfig())
    {
        cheekInset = 18.0f;
        grain_ = makeGrain (96, 96);

        auto fader = [this] (const juce::String& id, const juce::String& label, std::vector<std::unique_ptr<StyleFader>>& dst)
        { auto f = std::make_unique<StyleFader> (label, pal()); if (auto* prm = findParam (id)) f->attach (*prm); addAndMakeVisible (*f); dst.push_back (std::move (f)); };
        auto opt = [this] (const juce::String& id, juce::StringArray nm, juce::Colour col, const juce::String& grp, int icons) -> OptRow*
        { auto o = std::make_unique<OptRow> (nm, col, grp, icons, pal()); o->bindTo (findParam (id)); addAndMakeVisible (*o); opts.push_back (std::move (o)); return opts.back().get(); };
        auto tog = [this] (const juce::String& id, const juce::String& label) -> StyleToggle*
        { auto t = std::make_unique<StyleToggle> (label, pal()); t->bindTo (findParam (id)); addAndMakeVisible (*t); toggles.push_back (std::move (t)); return toggles.back().get(); };

        // ---- page 0: OSC ----
        oLfoWave = opt ("lfoShape", { "","","","" }, jup::kBlue, "LFO WAVE", 1);
        fader ("lfoRate","RATE",fLfo); fader ("lfoDelay","DELAY",fLfo); fader ("lfoDepth","DEPTH",fLfo);
        tLfoP = tog ("lfoPitch","PITCH"); tLfoW = tog ("lfoPwm","PWM"); tLfoF = tog ("lfoFilt","FILT");

        o1Range_ = opt ("o1Range", { "LO","MID","HI" }, jup::kGold, "RANGE", 0);
        o1Wave_  = opt ("o1Wave",  { "SAW","PLS","TRI" }, jup::kTan, "WAVE", 0);
        fader ("pwm","PW",fVco1);
        tMan = tog ("pwmMode","MANUAL");

        o2Range_ = opt ("o2Range", { "LO","MID","HI" }, jup::kGold, "RANGE", 0);
        o2Wave_  = opt ("o2Wave",  { "SAW","PLS","TRI","NZE" }, jup::kTan, "WAVE", 0);
        fader ("o2Fine","DETUNE",fVco2); fader ("crossMod","X-MOD",fVco2);
        tSync = tog ("sync","SYNC");

        fader ("mix1","VCO1",fMix); fader ("mix2","VCO2",fMix); fader ("detune","DETUNE",fMix);

        // ---- page 1: FILTER ----
        fader ("hpf","HPF",fVcf); fader ("cutoff","CUTOFF",fVcf); fader ("reso","RES",fVcf); fader ("filtEnv","ENV",fVcf); fader ("filtKbd","KYBD",fVcf);
        slope_ = opt ("slope", { "12","24" }, jup::kGreen, "SLOPE", 0);
        tInv = tog ("filtPol","INVERT");

        fader ("fA","A",fE1); fader ("fD","D",fE1); fader ("fS","S",fE1); fader ("fR","R",fE1);
        fader ("aA","A",fE2); fader ("aD","D",fE2); fader ("aS","S",fE2); fader ("aR","R",fE2);

        fader ("volume","VOLUME",fOut); fader ("tune","TUNE",fOut); fader ("glide","GLIDE",fOut);

        scope_ = std::make_unique<toi::Lcd> (pal()); scope_->setLines ("", ""); scope_->attachScope (audioTap()); addAndMakeVisible (*scope_);

        for (int i = 0; i < 16; ++i)
        { auto b = std::make_unique<JupPreset> (pal()); const int idx = i; b->onClick = [this, idx] { recallSlot (idx); }; addAndMakeVisible (*b); slots.push_back (std::move (b)); }
        rand_ = std::make_unique<JupFuncButton> ("RAND", jup::kBtnYel);
        save_ = std::make_unique<JupFuncButton> ("SAVE", jup::kBtnGrn);
        rand_->onClick = [this] { doRandom(); rand_->flash(); };
        save_->onClick = [this] { saveSlot (activeSlot()); save_->flash(); };
        addAndMakeVisible (*rand_); addAndMakeVisible (*save_);
        finishSetup();
    }

protected:
    void setPresetActiveVisual (int idx) override { for (int i = 0; i < (int) slots.size(); ++i) slots[(size_t) i]->setActive (i == idx); }

    static juce::Image makeGrain (int w, int h)
    {
        juce::Image img (juce::Image::ARGB, w, h, true);
        juce::Random r (20260527);
        for (int y = 0; y < h; ++y)
            for (int x = 0; x < w; ++x)
            {
                const float n = r.nextFloat();
                if (n > 0.62f) { const float a = (n - 0.62f) / 0.38f * 0.09f; const bool light = r.nextBool();
                    img.setPixelAt (x, y, (light ? juce::Colours::white : juce::Colours::black).withAlpha (a)); }
            }
        return img;
    }

    void bar (juce::Graphics& g, juce::Rectangle<float> r, const juce::String& title)
    {
        auto b = r.withHeight (15.0f);
        juce::ColourGradient og (jup::kOrange.brighter (0.14f), b.getCentreX(), b.getY(), jup::kOrange.darker (0.20f), b.getCentreX(), b.getBottom(), false);
        g.setGradientFill (og); g.fillRoundedRectangle (b, 2.5f);
        g.setColour (juce::Colours::white.withAlpha (0.18f)); g.drawLine (b.getX() + 3.0f, b.getY() + 1.2f, b.getRight() - 3.0f, b.getY() + 1.2f, 1.0f);
        g.setColour (juce::Colours::black.withAlpha (0.3f)); g.drawRoundedRectangle (b, 2.5f, 0.8f);
        g.setColour (juce::Colours::white); g.setFont (toi::uiFont (9.0f, true).withExtraKerningFactor (0.12f));
        g.drawText (title, b, juce::Justification::centred);
    }
    void drawJupLeds (juce::Graphics& g, juce::Rectangle<float> row)
    {
        const float r = 5.5f, cy = row.getY() + r + 1.0f;
        const float cx1 = row.getCentreX() - row.getWidth() * 0.22f, cx2 = row.getCentreX() + row.getWidth() * 0.22f;
        auto led = [&] (float cx, const juce::String& lbl, bool active)
        {
            if (active) { g.setColour (jup::kOrange.withAlpha (0.5f)); g.fillEllipse (cx - r - 3.0f, cy - r - 3.0f, (r + 3.0f) * 2.0f, (r + 3.0f) * 2.0f); }
            g.setColour (active ? jup::kOrange : jup::kOrange.withAlpha (0.30f)); g.fillEllipse (cx - r, cy - r, r * 2.0f, r * 2.0f);
            g.setColour (jup::kFrame); g.drawEllipse (cx - r, cy - r, r * 2.0f, r * 2.0f, toi::STROKE);
            g.setColour (jup::kWhite); g.setFont (toi::uiFont (7.0f, true).withExtraKerningFactor (0.04f));
            g.drawText (lbl, juce::Rectangle<float> (cx - 30.0f, cy + r + 8.0f, 60.0f, 10.0f), juce::Justification::centredTop);
        };
        led (cx1, "MODULE", moduleMode_);
        led (cx2, "SIZE",   sizeStep_ != 0);
        ledRectModule_ = { cx1 - 22.0f, row.getY(), 44.0f, row.getHeight() + 12.0f };
        ledRectSize_   = { cx2 - 22.0f, row.getY(), 44.0f, row.getHeight() + 12.0f };
    }

    void paintPanel (juce::Graphics& g, juce::Rectangle<float> panel) override
    {
        juce::ignoreUnused (panel);
        // DARK warm panel + subtle grain texture
        juce::ColourGradient pg (jup::kPanel, rPanel.getCentreX(), rPanel.getY(), jup::kPanelLo, rPanel.getCentreX(), rPanel.getBottom(), false);
        g.setGradientFill (pg); g.fillRoundedRectangle (rPanel, 5.0f);
        if (grain_.isValid()) { g.setFillType (juce::FillType (grain_, juce::AffineTransform::translation (rPanel.getX(), rPanel.getY()))); g.fillRoundedRectangle (rPanel, 5.0f); }
        g.setColour (juce::Colours::black); g.drawRoundedRectangle (rPanel, 5.0f, 1.5f);
        g.setColour (juce::Colours::white.withAlpha (0.05f)); g.drawRoundedRectangle (rPanel.reduced (1.5f), 4.0f, 1.0f);

        // thin vertical section dividers (between all 8 sections)
        for (auto* s : { &rB, &rC, &rD, &rE, &rF, &rG, &rH })
        {
            g.setColour (juce::Colours::black.withAlpha (0.45f)); g.drawLine (s->getX() - 3.0f, rPanel.getY() + 6.0f, s->getX() - 3.0f, rProg.getY() - 4.0f, 1.0f);
            g.setColour (juce::Colours::white.withAlpha (0.05f)); g.drawLine (s->getX() - 2.0f, rPanel.getY() + 6.0f, s->getX() - 2.0f, rProg.getY() - 4.0f, 1.0f);
        }
        bar (g, rA, "LFO");  bar (g, rB, "VCO-1"); bar (g, rC, "VCO-2"); bar (g, rD, "MIXER");
        bar (g, rE, "VCF");  bar (g, rF, "ENV-1"); bar (g, rG, "ENV-2"); bar (g, rH, "OUTPUT");

        auto bh = rBrandHdr;
        drawJupLeds (g, bh.removeFromTop (28.0f));
        bh.removeFromTop (1.0f);
        g.setColour (jup::kWhite); g.setFont (toi::uiFont (14.0f, true));
        g.drawText ("JW-JUP", bh.removeFromTop (16.0f), juce::Justification::centred);
        g.setColour (jup::kWhiteDim); g.setFont (toi::uiFont (5.5f, true).withExtraKerningFactor (0.2f));
        g.drawText ("TOI - plugin corp", bh.removeFromTop (8.0f), juce::Justification::centred);

        g.setColour (jup::kWhiteDim); g.setFont (toi::uiFont (7.0f, true).withExtraKerningFactor (0.10f));
        g.drawText ("PROGRAMMER", rProgLbl, juce::Justification::centredLeft);
    }

    void layoutPanel (juce::Rectangle<float> panel) override
    {
        rPanel = juce::Rectangle<float> (panel.getX() + cheekInset, panel.getY(), panel.getWidth() - 2.0f * cheekInset, panel.getHeight());
        auto inner = rPanel.reduced (10.0f, 8.0f);

        rProg = inner.removeFromBottom (26.0f);
        inner.removeFromBottom (6.0f);
        {
            auto pr = rProg.reduced (6.0f, 4.0f);
            rProgLbl = pr.removeFromLeft (66.0f);
            auto rs = pr.removeFromRight (98.0f);
            placeInArtboard (*rand_, rs.removeFromLeft (44.0f).reduced (2.0f, 1.0f));
            placeInArtboard (*save_, rs.reduced (2.0f, 1.0f));
            pr.removeFromLeft (6.0f); pr.removeFromRight (6.0f);
            const float gap = 3.0f, cw = (pr.getWidth() - gap * 15.0f) / 16.0f;
            for (int i = 0; i < 16; ++i)
                placeInArtboard (*slots[(size_t) i], juce::Rectangle<float> (pr.getX() + i * (cw + gap), pr.getY(), cw, pr.getHeight()).reduced (0.0f, 1.0f));
        }

        // ---- ONE ROW of all 8 sections (tall, tightly-packed sliders - no pages) ----
        const float colGap = 5.0f;
        const float t = inner.getWidth() - colGap * 7.0f;
        const float fr[8] = { 0.135f, 0.105f, 0.135f, 0.09f, 0.145f, 0.11f, 0.11f, 0.17f };
        juce::Rectangle<float>* rr[8] = { &rA, &rB, &rC, &rD, &rE, &rF, &rG, &rH };
        float x = inner.getX();
        for (int i = 0; i < 8; ++i) { const float w = (i == 7) ? (inner.getRight() - x) : fr[i] * t; *rr[i] = juce::Rectangle<float> (x, inner.getY(), w, inner.getHeight()); x += w + colGap; }

        // LFO: WAVE icon-row | RATE/DELAY/DEPTH sliders | PITCH/PWM/FILT toggles
        { auto r = rA.reduced (6.0f, 4.0f).withTrimmedTop (17.0f);
          placeInArtboard (*oLfoWave, r.removeFromTop (30.0f)); r.removeFromTop (3.0f);
          togRow ({ tLfoP, tLfoW, tLfoF }, r.removeFromBottom (36.0f));
          faders (fLfo, r); }
        // VCO-1: RANGE row | WAVE row | PW slider + MANUAL toggle
        { auto r = rB.reduced (5.0f, 4.0f).withTrimmedTop (17.0f);
          placeInArtboard (*o1Range_, r.removeFromTop (30.0f)); r.removeFromTop (3.0f);
          placeInArtboard (*o1Wave_,  r.removeFromTop (30.0f)); r.removeFromTop (3.0f);
          togRow ({ tMan }, r.removeFromBottom (38.0f).withSizeKeepingCentre (juce::jmin (r.getWidth(), 66.0f), 38.0f));
          faders (fVco1, r); }
        // VCO-2: RANGE row | WAVE row | DETUNE/X-MOD sliders + SYNC toggle
        { auto r = rC.reduced (5.0f, 4.0f).withTrimmedTop (17.0f);
          placeInArtboard (*o2Range_, r.removeFromTop (30.0f)); r.removeFromTop (3.0f);
          placeInArtboard (*o2Wave_,  r.removeFromTop (30.0f)); r.removeFromTop (3.0f);
          togRow ({ tSync }, r.removeFromBottom (38.0f).withSizeKeepingCentre (juce::jmin (r.getWidth(), 66.0f), 38.0f));
          faders (fVco2, r); }
        // MIXER: VCO1/VCO2/DETUNE sliders (full height)
        faders (fMix, rD.reduced (5.0f, 4.0f).withTrimmedTop (17.0f));
        // VCF: HPF/CUTOFF/RES/ENV/KYBD sliders | SLOPE row + INVERT toggle
        { auto r = rE.reduced (5.0f, 4.0f).withTrimmedTop (17.0f);
          auto bot = r.removeFromBottom (38.0f);
          faders (fVcf, r);
          placeInArtboard (*slope_, bot.removeFromLeft (bot.getWidth() * 0.62f));
          togRow ({ tInv }, bot.withSizeKeepingCentre (juce::jmin (bot.getWidth(), 50.0f), 38.0f)); }
        // ENV-1 / ENV-2: A D S R sliders (full height)
        faders (fE1, rF.reduced (5.0f, 4.0f).withTrimmedTop (17.0f));
        faders (fE2, rG.reduced (5.0f, 4.0f).withTrimmedTop (17.0f));
        // OUTPUT: scope | VOLUME/TUNE/GLIDE sliders | brand
        { auto r = rH.reduced (6.0f, 4.0f).withTrimmedTop (17.0f);
          placeInArtboard (*scope_, r.removeFromTop (30.0f).reduced (1.0f, 0.0f)); r.removeFromTop (3.0f);
          rBrandHdr = r.removeFromBottom (46.0f);
          faders (fOut, r); }
    }

    template <class V> void setVis (V& vec, bool v) { for (auto& c : vec) c->setVisible (v); }
    // pack the sliders into a tight centered group (capped slot) - no wide empty gaps between them
    void faders (std::vector<std::unique_ptr<StyleFader>>& v, juce::Rectangle<float> r)
    { const int n = (int) v.size(); if (n == 0) return;
      const float slot = juce::jmin (r.getWidth() / (float) n, 40.0f), gw = slot * (float) n, x0 = r.getX() + (r.getWidth() - gw) * 0.5f;
      for (int i = 0; i < n; ++i) placeInArtboard (*v[(size_t) i], juce::Rectangle<float> (x0 + i * slot, r.getY(), slot, r.getHeight()).reduced (2.5f, 0.0f)); }
    void togRow (std::vector<StyleToggle*> tg, juce::Rectangle<float> row)
    { const int n = (int) tg.size(); if (n == 0) return; const float cw = row.getWidth() / (float) n;
      for (int i = 0; i < n; ++i) placeInArtboard (*tg[(size_t) i], juce::Rectangle<float> (row.getX() + i * cw, row.getY(), cw, row.getHeight()).reduced (3.0f, 1.0f)); }

    std::vector<std::unique_ptr<StyleFader>> fLfo, fVco1, fVco2, fMix, fVcf, fE1, fE2, fOut;
    std::vector<std::unique_ptr<OptRow>> opts;
    std::vector<std::unique_ptr<StyleToggle>> toggles;
    OptRow *oLfoWave = nullptr, *o1Range_ = nullptr, *o1Wave_ = nullptr, *o2Range_ = nullptr, *o2Wave_ = nullptr, *slope_ = nullptr;
    StyleToggle *tLfoP = nullptr, *tLfoW = nullptr, *tLfoF = nullptr, *tMan = nullptr, *tSync = nullptr, *tInv = nullptr;
    std::unique_ptr<toi::Lcd> scope_;
    std::vector<std::unique_ptr<JupPreset>> slots;
    std::unique_ptr<JupFuncButton> rand_, save_;
    juce::Image grain_;
    juce::Rectangle<float> rPanel, rA, rB, rC, rD, rE, rF, rG, rH, rBrandHdr, rProg, rProgLbl;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JupEditor)
};

//==============================================================================
class JupPlugin  : public cmaj::plugin::GeneratedPlugin<::JUP>,
                   public toi::AudioTapSource,
                   public toi::PresetStore
{
public:
    using Base = cmaj::plugin::GeneratedPlugin<::JUP>;
    JupPlugin (std::shared_ptr<cmaj::Patch> p) : Base (std::move (p)) {}
    juce::AudioProcessorEditor* createEditor() override { return new JupEditor (*this, keyboardState); }
    void processBlock (juce::AudioBuffer<float>& audio, juce::MidiBuffer& midi) override
    { keyboardState.processNextMidiBuffer (midi, 0, audio.getNumSamples(), true); Base::processBlock (audio, midi); tap.push (audio); }
    toi::AudioTap* getAudioTap() override { return &tap; }
    bool loadPreset (int idx, std::map<juce::String, float>& out) override
    { auto it = userPresets.find (idx); if (it == userPresets.end()) return false; out = it->second; return true; }
    void savePreset (int idx, const std::map<juce::String, float>& vals) override { userPresets[idx] = vals; }
    bool hasPreset (int idx) override { return userPresets.find (idx) != userPresets.end(); }
private:
    juce::MidiKeyboardState keyboardState;
    toi::AudioTap tap;
    std::map<int, std::map<juce::String, float>> userPresets;
};
