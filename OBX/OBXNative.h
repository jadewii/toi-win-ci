// JW-OBI native faceplate (fat 8-voice analog poly) on the toi_faceplate.h kit.
// Built on toi::PanelEditor -> inherits 1300x477 size, single frame, 15-key keyboard,
// MODULE/SIZE, presets + snapshot. A DARK-TEAK WOOD cabinet framing a BLACK control panel
// scored with the signature BLUE PINSTRIPE lines, bespoke black-cap / blue-arc knobs (ObxKnob),
// black rocker switches with RED LEDs (ObxSwitch), the signature 12/24 dB slope switch
// (ObxModeSwitch), and a real-audio OUTPUT scope. Distinct from JW-P5 (light walnut, numeral
// knobs) and JW-SEM (cream). NO brand names (JW-OBI, not the original). EVERY param is wired.
#pragma once

#include "toi_faceplate.h"

struct OBX;

namespace obx
{
    static const juce::Colour kWood   { 0xff5c3a1f };   // dark teak/walnut cabinet face
    static const juce::Colour kWoodLo { 0xff3a2412 };   // darker (gradient toward edges)
    static const juce::Colour kPanel  { 0xff0b1626 };   // VERY dark blue control panel (Jade: not black - dark navy)
    static const juce::Colour kPanelHi{ 0xff132238 };   // panel highlight (slightly lighter navy)
    static const juce::Colour kFrame  { 0xff040506 };   // near-black frame + outlines
    static const juce::Colour kBlue   { 0xff3a5a7a };   // the synth's blue: value arcs + outlines (Jade's image-#7 steel blue)
    static const juce::Colour kStripe { 0xff46729c };   // pinstripes - same hue, a touch brighter so thin lines read on navy
    static const juce::Colour kBlueHi { 0xff6f97c0 };   // bright steel (highlights / pointer tip)
    static const juce::Colour kKeyPr  { 0xff314960 };   // pressed black key = the exact image-#7 blue (darker)
    static const juce::Colour kRed    { 0xffe23a2c };   // rocker / preset LEDs
    static const juce::Colour kScope  { 0xffff3b2e };   // RED waveform animation (Jade: scope = red, not blue)
    static const juce::Colour kWhite  { 0xffe9edf2 };   // screened white labels
    static const juce::Colour kWhiteDim{ 0xff9aa6b4 };  // dim labels
}

//==============================================================================
// Bespoke OBX knob: a black domed cap with a recessed face, a crisp WHITE POINTER line and a
// blue-tipped indicator, ringed by a grey track + BLUE value arc. Self-contained colours so it
// reads on the black panel (never borrows the wood bg). Hidden rotary slider = the drag surface.
class ObxKnob  : public juce::Component
{
public:
    ObxKnob (const juce::String& labelText, const toi::Palette& palette)
        : label (labelText), pal (palette)
    {
        slider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
        slider.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
        slider.setLookAndFeel (&laf);
        slider.setRange (0.0, 1.0, 0.0);
        slider.setDoubleClickReturnValue (true, 0.5);
        addAndMakeVisible (slider);
    }
    ~ObxKnob() override { slider.setLookAndFeel (nullptr); }
    void attach (juce::AudioProcessorParameter* p)
    {
        if (! p) return;
        attachment = std::make_unique<toi::ParamKnobAttachment> (*p, slider);
        slider.setDoubleClickReturnValue (true, p->getDefaultValue());
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
        const float R  = disc.getWidth() * 0.5f - 6.0f;
        const float v  = juce::jlimit (0.0f, 1.0f, (float) slider.getValue());
        const float ang = juce::degreesToRadians (-135.0f + 270.0f * v);
        const float dx = std::sin (ang), dy = -std::cos (ang);

        // value-arc: grey track + blue fill just outside the body
        { juce::Path tk; tk.addCentredArc (cx, cy, R + 4.0f, R + 4.0f, 0.0f,
            juce::degreesToRadians (-135.0f), juce::degreesToRadians (135.0f), true);
          g.setColour (juce::Colour (0xff31353b)); g.strokePath (tk, juce::PathStrokeType (2.2f)); }
        if (v > 0.001f) { juce::Path ap; ap.addCentredArc (cx, cy, R + 4.0f, R + 4.0f, 0.0f,
            juce::degreesToRadians (-135.0f), ang, true);
          g.setColour (obx::kBlue); g.strokePath (ap, juce::PathStrokeType (2.8f, juce::PathStrokeType::curved, juce::PathStrokeType::rounded)); }

        // drop shadow
        g.setColour (juce::Colours::black.withAlpha (0.5f)); g.fillEllipse (cx - R, cy - R + 2.5f, R * 2.0f, R * 2.0f);
        // black domed body (lit upper-left -> near black lower-right)
        juce::ColourGradient body (juce::Colour (0xff2c2f35), cx - R * 0.4f, cy - R * 0.5f,
                                   juce::Colour (0xff090a0c), cx + R * 0.45f, cy + R * 0.6f, false);
        body.addColour (0.5, juce::Colour (0xff15171b));
        g.setGradientFill (body); g.fillEllipse (cx - R, cy - R, R * 2.0f, R * 2.0f);
        g.setColour (juce::Colour (0xff050607)); g.drawEllipse (cx - R, cy - R, R * 2.0f, R * 2.0f, 1.4f);
        // upper-left rim sheen
        { juce::Path sh; sh.addCentredArc (cx, cy, R - 1.5f, R - 1.5f, 0.0f,
            juce::degreesToRadians (-120.0f), juce::degreesToRadians (-20.0f), true);
          g.setColour (juce::Colours::white.withAlpha (0.16f)); g.strokePath (sh, juce::PathStrokeType (1.6f)); }
        // recessed darker top face
        const float fr = R * 0.66f;
        juce::ColourGradient face (juce::Colour (0xff232529), cx, cy - fr, juce::Colour (0xff0b0c0f), cx, cy + fr, false);
        g.setGradientFill (face); g.fillEllipse (cx - fr, cy - fr, fr * 2.0f, fr * 2.0f);
        g.setColour (juce::Colours::black.withAlpha (0.6f)); g.drawEllipse (cx - fr, cy - fr, fr * 2.0f, fr * 2.0f, 1.0f);
        // crisp white pointer line from near the centre to the rim, blue tip dot
        g.setColour (juce::Colour (0xfff2f4f7));
        g.drawLine (cx + dx * fr * 0.12f, cy + dy * fr * 0.12f, cx + dx * (R - 2.0f), cy + dy * (R - 2.0f), 2.6f);
        const float pd = R * 0.085f;
        g.setColour (obx::kBlueHi); g.fillEllipse (cx + dx * (R - 2.0f) - pd, cy + dy * (R - 2.0f) - pd, pd * 2.0f, pd * 2.0f);

        if (showLabel)
        {
            g.setColour (pal.text); g.setFont (toi::uiFont (9.0f, true));
            g.drawText (label, getLocalBounds().toFloat().removeFromBottom (labelH), juce::Justification::centred);
        }
    }
    juce::Slider slider;
private:
    static constexpr float labelH = 13.0f;
    toi::InvisibleRotaryLAF laf; juce::String label; toi::Palette pal; bool showLabel = true;
    std::unique_ptr<toi::ParamKnobAttachment> attachment;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ObxKnob)
};

//==============================================================================
// Small black rocker switch with a RED LED that lights when ON (bound to a 0..1 param).
class ObxSwitch  : public juce::Component
{
public:
    explicit ObxSwitch (const toi::Palette&) {}
    void bindTo (juce::AudioProcessorParameter* p)
    { param_ = p; if (! p) return; slider.setRange (0.0, 1.0, 0.0); attach = std::make_unique<toi::ParamKnobAttachment> (*p, slider); addChildComponent (slider); slider.setVisible (false); }
    bool on() const { return (param_ ? param_->getValue() : (float) slider.getValue()) >= 0.5f; }
    void mouseDown (const juce::MouseEvent&) override { slider.setValue (on() ? 0.0 : 1.0, juce::sendNotificationSync); repaint(); }
    void paint (juce::Graphics& g) override
    {
        auto b = getLocalBounds().toFloat().reduced (1.0f);
        const bool o = on();
        juce::ColourGradient bg (juce::Colour (0xff2a2d33), b.getCentreX(), b.getY(),
                                 juce::Colour (0xff0b0c0e), b.getCentreX(), b.getBottom(), false);
        g.setGradientFill (bg); g.fillRoundedRectangle (b, 2.5f);
        g.setColour (obx::kFrame); g.drawRoundedRectangle (b, 2.5f, 1.0f);
        const float d = juce::jmin (b.getWidth(), b.getHeight()) * 0.42f;
        auto led = juce::Rectangle<float> (0, 0, d, d).withCentre ({ b.getCentreX(), b.getY() + d * 0.85f });
        g.setColour (o ? obx::kRed.brighter (0.25f) : juce::Colour (0xff3a1413));
        g.fillEllipse (led);
        if (o) { g.setColour (obx::kRed.brighter (0.7f).withAlpha (0.6f)); g.fillEllipse (led.reduced (d * 0.28f)); }
        g.setColour (juce::Colours::black.withAlpha (0.6f)); g.drawEllipse (led, 0.8f);
    }
private:
    juce::Slider slider; std::unique_ptr<toi::ParamKnobAttachment> attach; juce::AudioProcessorParameter* param_ = nullptr;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ObxSwitch)
};

//==============================================================================
// The SIGNATURE filter-slope switch: a two-cell pill [ 12 | 24 ] (dB/oct). The active slope
// glows blue. Bound to filtMode (<0.5 = 12 dB / 2-pole, else 24 dB / 4-pole). Click toggles.
class ObxModeSwitch  : public juce::Component
{
public:
    explicit ObxModeSwitch (const toi::Palette&) {}
    void bindTo (juce::AudioProcessorParameter* p)
    { param_ = p; if (! p) return; slider.setRange (0.0, 1.0, 0.0); attach = std::make_unique<toi::ParamKnobAttachment> (*p, slider); addChildComponent (slider); slider.setVisible (false); }
    bool is24() const { return (param_ ? param_->getValue() : (float) slider.getValue()) >= 0.5f; }
    void mouseDown (const juce::MouseEvent&) override { slider.setValue (is24() ? 0.0 : 1.0, juce::sendNotificationSync); repaint(); }
    void paint (juce::Graphics& g) override
    {
        auto b = getLocalBounds().toFloat().reduced (1.0f);
        g.setColour (juce::Colour (0xff0a0b0d)); g.fillRoundedRectangle (b, 3.0f);
        g.setColour (obx::kFrame); g.drawRoundedRectangle (b, 3.0f, 1.0f);
        auto cells = b.reduced (2.0f);
        auto c12 = cells.removeFromLeft (cells.getWidth() * 0.5f).reduced (1.0f, 0.0f);
        auto c24 = cells.reduced (1.0f, 0.0f);
        const bool on24 = is24();
        auto cell = [&] (juce::Rectangle<float> r, const juce::String& t, bool lit)
        {
            g.setColour (lit ? obx::kBlue : juce::Colour (0xff181b20)); g.fillRoundedRectangle (r, 2.0f);
            if (lit) { g.setColour (obx::kBlueHi.withAlpha (0.5f)); g.drawRoundedRectangle (r.reduced (0.8f), 1.8f, 1.0f); }
            g.setColour (lit ? juce::Colours::white : obx::kWhiteDim);
            g.setFont (toi::uiFont (juce::jmin (12.0f, r.getHeight() * 0.62f), true));
            g.drawText (t, r, juce::Justification::centred);
        };
        cell (c12, "12", ! on24);
        cell (c24, "24", on24);
    }
private:
    juce::Slider slider; std::unique_ptr<toi::ParamKnobAttachment> attach; juce::AudioProcessorParameter* param_ = nullptr;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ObxModeSwitch)
};

//==============================================================================
// Programmer preset button: dark domed square with a small RED LED (bright when this is the slot).
class ObxPreset  : public juce::Button
{
public:
    explicit ObxPreset (const toi::Palette&) : juce::Button ("preset") {}
    void setActive (bool a) { if (active != a) { active = a; repaint(); } }
    void paintButton (juce::Graphics& g, bool over, bool down) override
    {
        auto b = getLocalBounds().toFloat().reduced (1.0f);
        const float base = over ? 0.10f : 0.0f;
        juce::ColourGradient cap (juce::Colour (0xff34383f).brighter (base), b.getCentreX(), b.getY(),
                                  juce::Colour (0xff15171b), b.getCentreX(), b.getBottom(), false);
        g.setGradientFill (cap); g.fillRoundedRectangle (b, 2.2f);
        if (down) { g.setColour (juce::Colours::black.withAlpha (0.18f)); g.fillRoundedRectangle (b, 2.2f); }
        g.setColour (juce::Colours::white.withAlpha (0.18f)); g.drawLine (b.getX() + 1.5f, b.getY() + 1.0f, b.getRight() - 1.5f, b.getY() + 1.0f, 1.0f);
        g.setColour (juce::Colours::black.withAlpha (0.5f)); g.drawRoundedRectangle (b, 2.2f, 1.0f);
        const float d = juce::jmin (b.getWidth(), b.getHeight()) * 0.30f;
        auto led = juce::Rectangle<float> (0, 0, d, d).withCentre ({ b.getCentreX(), b.getY() + d * 1.05f });
        g.setColour (active ? obx::kRed.brighter (0.3f) : juce::Colour (0xff401a18));
        g.fillEllipse (led);
        if (active) { g.setColour (obx::kRed.brighter (0.8f).withAlpha (0.7f)); g.fillEllipse (led.reduced (d * 0.3f)); }
        g.setColour (juce::Colours::black.withAlpha (0.55f)); g.drawEllipse (led, 0.6f);
    }
private:
    bool active = false;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ObxPreset)
};

//==============================================================================
inline toi::Config obxConfig()
{
    toi::Config c;
    c.model = "JW-OBI";
    auto& p = c.pal;
    p.bg = obx::kWood; p.bg2 = obx::kWoodLo; p.frame = obx::kFrame; p.ink = obx::kFrame;
    p.accent = obx::kBlue; p.accent2 = obx::kRed; p.button = juce::Colour (0xff1a1d22);
    p.thumb = juce::Colour (0xfff0f2f5); p.text = obx::kWhite;
    p.lcdBg = juce::Colour (0xff0a0d11); p.lcdInk = obx::kScope;          // RED waveform on a near-black screen
    p.noteStrip = obx::kPanel;                                            // dark note band (no brown below the panel)
    p.keyWhite = juce::Colour (0xffEDEDEA); p.keyWhitePr = juce::Colour (0xffbcd6f0);
    p.keyBlack = juce::Colour (0xff111418); p.keyBlackPr = obx::kKeyPr;   // pressed black key = the darker image-#7 blue

    c.params = {
        { "lfoRate","RATE" }, { "lfoShape","SHAPE" }, { "lfoDepth","DEPTH" },
        { "lfoFreq","FREQ" }, { "lfoPwm","PWM" }, { "lfoFilt","FILT" },
        { "o1Freq","FREQ" }, { "o1PW","PW" }, { "o1Saw","SAW" }, { "o1Pulse","PULSE" },
        { "o2Freq","FREQ" }, { "o2Detune","DETUNE" }, { "o2PW","PW" }, { "o2Saw","SAW" }, { "o2Pulse","PULSE" },
        { "sync","SYNC" }, { "xmod","X-MOD" },
        { "mix1","VCO1" }, { "mix2","VCO2" },
        { "cutoff","CUTOFF" }, { "reso","RESONANCE" }, { "filtEnv","ENV" }, { "filtKbd","KBD" }, { "filtMode","MODE" },
        { "fA","A" }, { "fD","D" }, { "fS","S" }, { "fR","R" },
        { "aA","A" }, { "aD","D" }, { "aS","S" }, { "aR","R" },
        { "unison","UNISON" }, { "detune","DETUNE" }, { "glide","GLIDE" },
        { "volume","VOLUME" }, { "tune","TUNE" },
    };

    // 16 classic big-poly patches. P() builds the full param vector in c.params order;
    // fixed: lfoRate=.30, lfoShape=0, o1Freq=.5, mix1=.85, mix2=.72, filtKbd=.40, glide=0, vol=.8, tune=.5.
    auto P = [] (const char* nm,
                 float lfoDepth,float lfoFreq,float lfoPwm,float lfoFilt,
                 float o1Saw,float o1Pulse,float o1PW,
                 float o2Freq,float o2Detune,float o2Saw,float o2Pulse,float o2PW,
                 float sync,float xmod,
                 float cut,float res,float fenv,float fmode,
                 float fA,float fD,float fS,float fR,
                 float aA,float aD,float aS,float aR,
                 float unison,float detune)
    {
        return toi::FactoryPreset { nm, {
            0.30f, 0.0f, lfoDepth, lfoFreq, lfoPwm, lfoFilt,
            0.5f, o1PW, o1Saw, o1Pulse,
            o2Freq, o2Detune, o2PW, o2Saw, o2Pulse,
            sync, xmod,
            0.85f, 0.72f,
            cut, res, fenv, 0.40f, fmode,
            fA, fD, fS, fR,
            aA, aD, aS, aR,
            unison, detune, 0.0f,
            0.80f, 0.50f } };
    };
    c.factory = {
        //              lfD  lfF  lfP  lfFl o1S  o1P  o1PW o2F  o2Dt o2S  o2P  o2PW syn  xmd  cut  res  fenv fmod fA   fD   fS   fR   aA   aD   aS   aR   uni  det
        P("BIG BRASS",   0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 0.35,0.5, 0.53,1.0, 0.0, 0.5, 0.0, 0.0, 0.46,0.22,0.55,1.0, 0.06,0.45,0.6, 0.35,0.04,0.4, 0.85,0.35,0.0, 0.32),
        P("LUSH STRINGS",0.30,0.0, 1.0, 0.0, 1.0, 1.0, 0.40,0.5, 0.55,1.0, 0.0, 0.5, 0.0, 0.0, 0.52,0.16,0.30,0.0, 0.55,0.6, 0.85,0.7, 0.5, 0.6, 0.85,0.7, 1.0, 0.45),
        P("FAT PAD",     0.20,0.0, 1.0, 0.0, 1.0, 0.0, 0.5, 0.5, 0.56,1.0, 0.0, 0.5, 0.0, 0.0, 0.45,0.20,0.40,1.0, 0.5, 0.6, 0.85,0.75,0.45,0.6, 0.85,0.75,1.0, 0.5),
        P("SYNC LEAD",   0.10,0.0, 0.0, 0.0, 1.0, 0.0, 0.5, 0.62,0.40,1.0, 0.0, 0.5, 1.0, 0.0, 0.62,0.30,0.55,1.0, 0.02,0.4, 0.7, 0.3, 0.02,0.5, 0.85,0.25,0.0, 0.2),
        P("PWM POLY",    0.35,0.0, 1.0, 0.0, 0.0, 1.0, 0.55,0.5, 0.52,0.0, 1.0, 0.5, 0.0, 0.0, 0.50,0.18,0.35,0.0, 0.3, 0.5, 0.7, 0.6, 0.25,0.5, 0.8, 0.6, 1.0, 0.4),
        P("FUNK BRASS",  0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 0.30,0.5, 0.51,0.0, 1.0, 0.5, 0.0, 0.0, 0.40,0.28,0.65,1.0, 0.02,0.35,0.3, 0.25,0.02,0.35,0.7, 0.25,0.0, 0.25),
        P("DEEP BASS",   0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.5, 0.38,0.49,1.0, 0.0, 0.5, 0.0, 0.0, 0.36,0.30,0.55,1.0, 0.02,0.30,0.1, 0.2, 0.02,0.35,0.2, 0.2, 0.0, 0.12),
        P("OCTAVE BRASS",0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 0.35,0.75,0.52,1.0, 0.0, 0.5, 0.0, 0.0, 0.48,0.22,0.55,1.0, 0.05,0.45,0.6, 0.35,0.04,0.45,0.8, 0.3, 0.0, 0.3),
        P("SWEEP PAD",   0.20,0.0, 0.0, 1.0, 1.0, 0.0, 0.5, 0.5, 0.55,1.0, 0.0, 0.5, 0.0, 0.0, 0.30,0.42,0.70,1.0, 0.4, 0.7, 0.4, 0.5, 0.3, 0.6, 0.7, 0.6, 1.0, 0.5),
        P("UNISON STAB", 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 0.4, 0.5, 0.45,1.0, 0.0, 0.5, 0.0, 0.0, 0.55,0.25,0.60,1.0, 0.01,0.3, 0.0, 0.25,0.01,0.3, 0.5, 0.25,1.0, 0.7),
        P("CLANG BELL",  0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.5, 0.7, 0.62,1.0, 0.0, 0.5, 0.0, 0.6, 0.55,0.30,0.50,1.0, 0.02,0.5, 0.2, 0.4, 0.02,0.5, 0.4, 0.4, 0.0, 0.25),
        P("5TH POLY",    0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 0.35,0.66,0.52,1.0, 0.0, 0.5, 0.0, 0.0, 0.50,0.20,0.45,1.0, 0.04,0.45,0.6, 0.4, 0.04,0.45,0.8, 0.35,0.0, 0.35),
        P("SOFT KEYS",   0.10,0.0, 1.0, 0.0, 1.0, 0.0, 0.5, 0.5, 0.53,0.0, 1.0, 0.5, 0.0, 0.0, 0.50,0.18,0.45,0.0, 0.02,0.45,0.4, 0.4, 0.02,0.45,0.4, 0.4, 0.0, 0.3),
        P("AGGRO LEAD",  0.20,1.0, 0.0, 0.0, 1.0, 1.0, 0.4, 0.5, 0.42,1.0, 0.0, 0.5, 1.0, 0.0, 0.60,0.40,0.55,1.0, 0.02,0.4, 0.7, 0.3, 0.02,0.45,0.85,0.3, 1.0, 0.3),
        P("WIDE DREAM",  0.30,0.0, 1.0, 1.0, 1.0, 1.0, 0.45,0.5, 0.57,1.0, 0.0, 0.5, 0.0, 0.0, 0.44,0.22,0.45,0.0, 0.6, 0.7, 0.85,0.8, 0.6, 0.7, 0.85,0.8, 1.0, 0.6),
        P("SYNTH ORGAN", 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 0.3, 0.75,0.50,1.0, 0.0, 0.5, 0.0, 0.0, 0.62,0.15,0.10,0.0, 0.02,0.5, 1.0, 0.3, 0.02,0.5, 1.0, 0.3, 0.0, 0.2),
    };
    return c;
}

//==============================================================================
class ObxEditor  : public toi::PanelEditor
{
public:
    ObxEditor (juce::AudioProcessor& proc, juce::MidiKeyboardState& kb)
        : toi::PanelEditor (proc, kb, obxConfig())
    {
        cheekInset = 18.0f;   // wood end-cheeks on the LEFT/RIGHT only, full height (panel + keyboard)

        auto knob = [this] (const juce::String& id, const juce::String& label,
                            std::vector<std::unique_ptr<ObxKnob>>& dst)
        {
            auto k = std::make_unique<ObxKnob> (label, pal());
            k->attach (findParam (id));
            addAndMakeVisible (*k); dst.push_back (std::move (k));
        };
        auto sw = [this] (const juce::String& id) -> ObxSwitch*
        { auto s = std::make_unique<ObxSwitch> (pal()); s->bindTo (findParam (id)); addAndMakeVisible (*s); switches.push_back (std::move (s)); return switches.back().get(); };

        knob ("lfoRate","RATE",kLfo); knob ("lfoShape","SHAPE",kLfo); knob ("lfoDepth","DEPTH",kLfo);
        swLfoFreq = sw ("lfoFreq"); swLfoPwm = sw ("lfoPwm"); swLfoFilt = sw ("lfoFilt");

        knob ("o1Freq","FREQ",kOsc); knob ("o1PW","PW",kOsc);
        knob ("o2Freq","FREQ",kOsc); knob ("o2Detune","DETUNE",kOsc); knob ("o2PW","PW",kOsc);
        knob ("xmod","X-MOD",kOsc);
        swO1Saw = sw ("o1Saw"); swO1Pulse = sw ("o1Pulse"); swO2Saw = sw ("o2Saw"); swO2Pulse = sw ("o2Pulse"); swSync = sw ("sync");

        knob ("mix1","VCO1",kMix); knob ("mix2","VCO2",kMix);

        knob ("cutoff","CUTOFF",kFilt); knob ("reso","RESONANCE",kFilt); knob ("filtEnv","ENV",kFilt); knob ("filtKbd","KBD",kFilt);
        swMode = std::make_unique<ObxModeSwitch> (pal()); swMode->bindTo (findParam ("filtMode")); addAndMakeVisible (*swMode);

        knob ("fA","A",kFEnv); knob ("fD","D",kFEnv); knob ("fS","S",kFEnv); knob ("fR","R",kFEnv);
        knob ("aA","A",kAEnv); knob ("aD","D",kAEnv); knob ("aS","S",kAEnv); knob ("aR","R",kAEnv);

        knob ("detune","DETUNE",kVoice); knob ("glide","GLIDE",kVoice);
        swUnison = sw ("unison");

        knob ("volume","VOLUME",kMaster); knob ("tune","TUNE",kMaster);

        scope_ = std::make_unique<toi::Lcd> (pal());
        scope_->setLines ("", "");
        scope_->attachScope (audioTap());
        addAndMakeVisible (*scope_);

        for (int i = 0; i < 16; ++i)
        { auto b = std::make_unique<ObxPreset> (pal()); const int idx = i; b->onClick = [this, idx] { recallSlot (idx); }; addAndMakeVisible (*b); slots.push_back (std::move (b)); }
        rand_ = std::make_unique<toi::Button> ("RAND", pal());
        save_ = std::make_unique<toi::Button> ("SAVE", pal());
        rand_->setFill (obx::kBlue); save_->setFill (obx::kBlue);
        rand_->onClick = [this] { doRandom(); rand_->flash(); };
        save_->onClick = [this] { saveSlot (activeSlot()); save_->flash(); };
        addAndMakeVisible (*rand_); addAndMakeVisible (*save_);
        finishSetup();
    }

protected:
    void setPresetActiveVisual (int idx) override { for (int i = 0; i < (int) slots.size(); ++i) slots[(size_t) i]->setActive (i == idx); }

    // MODULE/SIZE LEDs with a WIDER gap between each dot and its label (Jade: labels too close to the buttons).
    // Own copy rather than the kit's drawViewLeds, so other engines' tight spacing is untouched.
    void drawObxLeds (juce::Graphics& g, juce::Rectangle<float> row)
    {
        const float r = 5.5f;
        const float cy = row.getY() + r + 1.0f;
        const float cx1 = row.getCentreX() - row.getWidth() * 0.22f;
        const float cx2 = row.getCentreX() + row.getWidth() * 0.22f;
        auto led = [&] (float cx, juce::Colour c, const juce::String& lbl, bool active)
        {
            if (active) { g.setColour (c.withAlpha (0.5f)); g.fillEllipse (cx - r - 3.0f, cy - r - 3.0f, (r + 3.0f) * 2.0f, (r + 3.0f) * 2.0f); }
            g.setColour (active ? c : c.withAlpha (0.30f)); g.fillEllipse (cx - r, cy - r, r * 2.0f, r * 2.0f);
            g.setColour (obx::kFrame); g.drawEllipse (cx - r, cy - r, r * 2.0f, r * 2.0f, toi::STROKE);
            g.setColour (obx::kWhite); g.setFont (toi::uiFont (7.0f, true).withExtraKerningFactor (0.04f));
            g.drawText (lbl, juce::Rectangle<float> (cx - 30.0f, cy + r + 8.0f, 60.0f, 10.0f), juce::Justification::centredTop);
        };
        led (cx1, obx::kRed,  "MODULE", moduleMode_);
        led (cx2, obx::kBlue, "SIZE",   sizeStep_ != 0);
        ledRectModule_ = { cx1 - 22.0f, row.getY(), 44.0f, row.getHeight() + 12.0f };
        ledRectSize_   = { cx2 - 22.0f, row.getY(), 44.0f, row.getHeight() + 12.0f };
    }

    // NO section boxes (Jade): the pinstripes run on a shared y-grid and simply BREAK between
    // sections (the colGap between section rects is the visual gap), exactly like the hardware.
    void drawSectionStripes (juce::Graphics& g, float yTop, float yBot, std::initializer_list<juce::Rectangle<float>> secs)
    {
        g.setColour (obx::kStripe.withAlpha (0.55f));
        const float y0 = rPanel.getY() + 9.0f;   // shared grid origin so lines align across all sections
        for (float y = y0; y < yBot; y += 12.0f)
            if (y >= yTop)
                for (auto& s : secs)
                    g.fillRect (juce::Rectangle<float> (s.getX(), y, s.getWidth(), 1.0f));
    }
    // centred section title at the top of its column; a small panel-coloured fill breaks the
    // pinstripe behind it (the "gap in the line" that names the section on the original).
    void sectionTitle (juce::Graphics& g, juce::Rectangle<float> r, const juce::String& title)
    {
        auto bg = juce::Rectangle<float> (0, 0, title.length() * 6.6f + 12.0f, 13.0f)
                    .withCentre ({ r.getCentreX(), r.getY() + 5.0f });
        g.setColour (obx::kPanel); g.fillRect (bg);
        g.setColour (obx::kWhite); g.setFont (toi::uiFont (8.5f, true).withExtraKerningFactor (0.10f));
        g.drawText (title, bg, juce::Justification::centred);
    }

    void paintPanel (juce::Graphics& g, juce::Rectangle<float> panel) override
    {
        juce::ignoreUnused (panel);
        // DARK NAVY control panel - FULL HEIGHT; wood shows only as the LEFT/RIGHT end-cheeks
        g.setColour (obx::kPanel); g.fillRoundedRectangle (rPanel, 5.0f);
        g.setColour (juce::Colours::black); g.drawRoundedRectangle (rPanel, 5.0f, 1.5f);
        g.setColour (juce::Colours::white.withAlpha (0.05f)); g.drawRoundedRectangle (rPanel.reduced (1.5f), 4.0f, 1.0f);

        // pinstripes on a shared grid that BREAK between sections (NO boxes). Top-row sections
        // above the toggle-band centre, bottom-row sections below it.
        const float split = rBand.getCentreY();
        drawSectionStripes (g, rPanel.getY() + 6.0f, split, { rLfo, rOsc, rFilt, rVoice });
        drawSectionStripes (g, split, rPanel.getBottom() - 5.0f, { rMix, rFEnv, rAEnv, rMaster });

        sectionTitle (g, rLfo,    "MODULATION");
        sectionTitle (g, rOsc,    "OSCILLATORS");
        sectionTitle (g, rFilt,   "FILTER");
        sectionTitle (g, rVoice,  "VOICE");
        sectionTitle (g, rMix,    "MIXER");
        sectionTitle (g, rFEnv,   "FILTER ENV");
        sectionTitle (g, rAEnv,   "AMP ENV");
        sectionTitle (g, rMaster, "OUTPUT");

        // toggle labels (band between the rows) - a small panel fill behind each breaks the stripe
        g.setFont (toi::uiFont (6.5f, true));
        auto tlbl = [&] (const juce::String& t, juce::Rectangle<float> r)
        { g.setColour (obx::kPanel); g.fillRect (r.reduced (1.0f, 0.0f)); g.setColour (obx::kWhite); g.drawText (t, r, juce::Justification::centred); };
        tlbl ("FREQ",  rLblLfoFreq); tlbl ("PWM",  rLblLfoPwm);  tlbl ("FILT", rLblLfoFilt);
        tlbl ("1 SAW", rLblO1Saw);   tlbl ("1 PLS", rLblO1Pulse); tlbl ("2 SAW", rLblO2Saw);
        tlbl ("2 PLS", rLblO2Pulse); tlbl ("SYNC", rLblSync);     tlbl ("UNISON", rLblUnison);
        tlbl ("SLOPE", rLblMode);

        // brand block + MODULE/SIZE leds (right of OUTPUT), with the wider label gap
        auto bh = rBrandHdr;
        drawObxLeds (g, bh.removeFromTop (30.0f));
        bh.removeFromTop (2.0f);
        g.setColour (obx::kWhite); g.setFont (toi::uiFont (15.0f, true));
        g.drawText ("JW-OBI", bh.removeFromTop (18.0f), juce::Justification::centred);
        g.setColour (obx::kWhiteDim); g.setFont (toi::uiFont (5.5f, true).withExtraKerningFactor (0.2f));
        g.drawText ("TOI - plugin corp", bh.removeFromTop (9.0f), juce::Justification::centred);

        // PROGRAMMER label (no box - sections are separated by gaps in the lines, not frames)
        g.setColour (obx::kWhiteDim); g.setFont (toi::uiFont (7.0f, true).withExtraKerningFactor (0.12f));
        g.drawText ("PROGRAMMER", rProgLbl, juce::Justification::centredLeft);
    }

    void layoutPanel (juce::Rectangle<float> panel) override
    {
        // BLACK panel - FULL HEIGHT, inset only on the L/R by cheekInset (the wood end-cheeks).
        rPanel = juce::Rectangle<float> (panel.getX() + cheekInset, panel.getY(),
                                         panel.getWidth() - 2.0f * cheekInset, panel.getHeight());
        auto inner = rPanel.reduced (10.0f, 8.0f);

        // bottom PROGRAMMER strip across the panel
        rProg = inner.removeFromBottom (26.0f);
        inner.removeFromBottom (5.0f);
        {
            auto pr = rProg.reduced (6.0f, 4.0f);
            rProgLbl = pr.removeFromLeft (66.0f);
            auto rs = pr.removeFromRight (104.0f);
            placeInArtboard (*rand_, rs.removeFromLeft (46.0f).reduced (2.0f, 2.0f));
            placeInArtboard (*save_, rs.reduced (2.0f, 2.0f));
            pr.removeFromLeft (6.0f); pr.removeFromRight (6.0f);
            const float gap = 3.0f, cw = (pr.getWidth() - gap * 15.0f) / 16.0f;
            for (int i = 0; i < 16; ++i)
                placeInArtboard (*slots[(size_t) i], juce::Rectangle<float> (pr.getX() + i * (cw + gap), pr.getY(), cw, pr.getHeight()).reduced (0.0f, 1.0f));
        }

        // TWO equal knob rows with a thin TOGGLE BAND between them -> knob rows never shrink,
        // so EVERY knob is the same big size (Jade: no tiny knobs).
        const float bandH = 24.0f, rowGap = 5.0f, colGap = 7.0f;
        const float rowH = (inner.getHeight() - bandH - 2.0f * rowGap) * 0.5f;
        auto rowA = inner.removeFromTop (rowH);
        inner.removeFromTop (rowGap);
        auto band = inner.removeFromTop (bandH);
        rBand = band;        // remembered so paintPanel can split the pinstripe grid at the band centre
        inner.removeFromTop (rowGap);
        auto rowB = inner;   // == rowH

        // ---- ROW A: MODULATION | OSCILLATORS | FILTER | VOICE (the toggle-bearing sections) ----
        { const float t = rowA.getWidth() - colGap * 3.0f;
          rLfo   = juce::Rectangle<float> (rowA.getX(), rowA.getY(), t * 0.18f, rowH);
          rOsc   = juce::Rectangle<float> (rLfo.getRight() + colGap, rowA.getY(), t * 0.40f, rowH);
          rFilt  = juce::Rectangle<float> (rOsc.getRight() + colGap, rowA.getY(), t * 0.26f, rowH);
          rVoice = juce::Rectangle<float> (rFilt.getRight() + colGap, rowA.getY(), rowA.getRight() - rFilt.getRight() - colGap, rowH); }

        gridKnobs (kLfo,   rLfo.reduced   (6.0f, 4.0f).withTrimmedTop (13.0f), 3);
        gridKnobs (kOsc,   rOsc.reduced   (6.0f, 4.0f).withTrimmedTop (13.0f), 6);
        gridKnobs (kFilt,  rFilt.reduced  (6.0f, 4.0f).withTrimmedTop (13.0f), 4);
        gridKnobs (kVoice, rVoice.reduced (6.0f, 4.0f).withTrimmedTop (13.0f), 2);

        // VCO sub-headers sit just under the OSCILLATORS title, over their knob groups
        { auto r = rOsc.reduced (6.0f, 4.0f);
          rVco1Hdr = juce::Rectangle<float> (r.getX(),                          r.getY(), r.getWidth() * (2.0f / 6.0f), 12.0f);
          rVco2Hdr = juce::Rectangle<float> (r.getX() + r.getWidth() * (2.0f/6.0f), r.getY(), r.getWidth() * (3.0f / 6.0f), 12.0f); }

        // ---- ROW B: MIXER | FILTER ENV | AMP ENV | OUTPUT (knobs only) ----
        { const float t = rowB.getWidth() - colGap * 3.0f;
          rMix    = juce::Rectangle<float> (rowB.getX(), rowB.getY(), t * 0.11f, rowH);
          rFEnv   = juce::Rectangle<float> (rMix.getRight() + colGap, rowB.getY(), t * 0.235f, rowH);
          rAEnv   = juce::Rectangle<float> (rFEnv.getRight() + colGap, rowB.getY(), t * 0.235f, rowH);
          rMaster = juce::Rectangle<float> (rAEnv.getRight() + colGap, rowB.getY(), rowB.getRight() - rAEnv.getRight() - colGap, rowH); }

        gridKnobs (kMix,  rMix.reduced  (5.0f, 4.0f).withTrimmedTop (13.0f), 2);
        gridKnobs (kFEnv, rFEnv.reduced (6.0f, 4.0f).withTrimmedTop (13.0f), 4);
        gridKnobs (kAEnv, rAEnv.reduced (6.0f, 4.0f).withTrimmedTop (13.0f), 4);

        // OUTPUT: scope | VOLUME | TUNE | brand  (all full height)
        { auto r = rMaster.reduced (7.0f, 4.0f).withTrimmedTop (13.0f);
          auto scopeR = r.removeFromLeft (r.getWidth() * 0.30f);
          r.removeFromLeft (6.0f);
          rBrandHdr = r.removeFromRight (r.getWidth() * 0.42f);
          r.removeFromRight (4.0f);
          placeInArtboard (*scope_, scopeR.withSizeKeepingCentre (scopeR.getWidth(), juce::jmin (scopeR.getHeight(), 48.0f)));
          gridKnobs (kMaster, r, 2); }

        // ---- TOGGLE BAND: sliced by each ROW A section's x-range ----
        auto bandFor = [&] (juce::Rectangle<float> sec)
        { return juce::Rectangle<float> (sec.getX() + 6.0f, band.getY(), sec.getWidth() - 12.0f, band.getHeight()); };
        placeToggles ({ swLfoFreq, swLfoPwm, swLfoFilt }, bandFor (rLfo),
                      { &rLblLfoFreq, &rLblLfoPwm, &rLblLfoFilt });
        placeToggles ({ swO1Saw, swO1Pulse, swO2Saw, swO2Pulse, swSync }, bandFor (rOsc),
                      { &rLblO1Saw, &rLblO1Pulse, &rLblO2Saw, &rLblO2Pulse, &rLblSync });
        { auto b = bandFor (rFilt); const float mw = 58.0f, mh = 15.0f;
          auto mc = b.withSizeKeepingCentre (mw, mh).withY (b.getY());
          placeInArtboard (*swMode, mc);
          rLblMode = juce::Rectangle<float> (b.getCentreX() - 40.0f, mc.getBottom() + 0.5f, 80.0f, 9.0f); }
        { auto b = bandFor (rVoice); placeToggles ({ swUnison }, b, { &rLblUnison }); }
    }

private:
    void gridKnobs (std::vector<std::unique_ptr<ObxKnob>>& v, juce::Rectangle<float> r, int cols)
    {
        const int n = (int) v.size(); if (n == 0) return;
        const int rows = (n + cols - 1) / cols;
        const float cw = r.getWidth() / (float) cols, rh = r.getHeight() / (float) rows;
        for (int i = 0; i < n; ++i) { const int col = i % cols, row = i / cols;
            placeInArtboard (*v[(size_t) i], juce::Rectangle<float> (r.getX() + col * cw, r.getY() + row * rh, cw, rh).reduced (2.0f, 1.0f)); }
    }
    // lay switches evenly across a row, with their label rects just below each switch
    void placeToggles (std::vector<ObxSwitch*> sws, juce::Rectangle<float> row, std::vector<juce::Rectangle<float>*> lbls)
    {
        const int n = (int) sws.size(); if (n == 0) return;
        const float cw = row.getWidth() / (float) n, sw = 15.0f, sh = 14.0f;
        for (int i = 0; i < n; ++i)
        {
            const float cellX = row.getX() + i * cw;
            placeInArtboard (*sws[(size_t) i], juce::Rectangle<float> (cellX + cw * 0.5f - sw * 0.5f, row.getY(), sw, sh));
            *lbls[(size_t) i] = juce::Rectangle<float> (cellX, row.getY() + sh + 0.5f, cw, 9.0f);
        }
    }

    std::vector<std::unique_ptr<ObxKnob>> kLfo, kOsc, kMix, kFilt, kVoice, kFEnv, kAEnv, kMaster;
    std::vector<std::unique_ptr<ObxSwitch>> switches;
    ObxSwitch *swLfoFreq = nullptr, *swLfoPwm = nullptr, *swLfoFilt = nullptr,
              *swO1Saw = nullptr, *swO1Pulse = nullptr, *swO2Saw = nullptr, *swO2Pulse = nullptr,
              *swSync = nullptr, *swUnison = nullptr;
    std::unique_ptr<ObxModeSwitch> swMode;
    std::unique_ptr<toi::Lcd> scope_;
    std::vector<std::unique_ptr<ObxPreset>> slots;
    std::unique_ptr<toi::Button> rand_, save_;
    juce::Rectangle<float> rPanel, rBand, rLfo, rOsc, rMix, rFilt, rVoice, rFEnv, rAEnv, rMaster, rBrandHdr,
                           rVco1Hdr, rVco2Hdr, rProg, rProgLbl,
                           rLblLfoFreq, rLblLfoPwm, rLblLfoFilt, rLblO1Saw, rLblO1Pulse, rLblO2Saw, rLblO2Pulse,
                           rLblSync, rLblUnison, rLblMode;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ObxEditor)
};

//==============================================================================
class ObxPlugin  : public cmaj::plugin::GeneratedPlugin<::OBX>,
                   public toi::AudioTapSource,
                   public toi::PresetStore
{
public:
    using Base = cmaj::plugin::GeneratedPlugin<::OBX>;
    ObxPlugin (std::shared_ptr<cmaj::Patch> p) : Base (std::move (p)) {}
    juce::AudioProcessorEditor* createEditor() override { return new ObxEditor (*this, keyboardState); }
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
