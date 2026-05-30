// JW-JUNO native faceplate (6-voice DCO poly with stereo chorus) on the toi_faceplate.h kit.
// Built on toi::PanelEditor -> inherits 1300x477 size, single frame, 15-key keyboard,
// MODULE/SIZE, presets + snapshot. A flat DARK CHARCOAL / slate-grey metal panel with crisp
// WHITE screened labels and a tasteful accent stripe. SLIDERS (toi::StyledFader) are the primary
// control - the Juno signature look. Toggles = small rocker switches (JunoSwitch); a 3-position
// RANGE rocker (JunoRange); the CHORUS = two lit buttons (I / II, JunoChorusBtn). Programmer
// strip = grey domed preset buttons + RAND/SAVE. NO brand names (JW-JUNO, not the original).
// EVERY param is wired to a real control.
#pragma once

#include "toi_faceplate.h"

struct JUNO;

namespace juno_ui
{
    static const juce::Colour kPanel  { 0xff9a9b9e };   // medium GREY panel (Juno-106 emulation grey)
    static const juce::Colour kPanelLo{ 0xff84868a };   // darker grey (gradient toward edges)
    static const juce::Colour kBox     { 0xff8e9094 };  // section area (same grey family)
    static const juce::Colour kBoxLo   { 0xff7d7f83 };  // box gradient bottom
    static const juce::Colour kFrame  { 0xff202225 };   // dark frame + outlines
    static const juce::Colour kInk    { 0xff1b1c1e };   // DARK labels/ink on the grey body
    static const juce::Colour kWhite  { 0xfff4f5f6 };   // white text on the RED section bars
    static const juce::Colour kWhiteDim{ 0xff45474b };  // dim label (mid-dark on grey)
    static const juce::Colour kAccent { 0xff4a8fd6 };   // BLUE: slider fills + LEDs + note strip
    static const juce::Colour kBarRed { 0xffbe2330 };   // RED: the section header bars (top part)
    static const juce::Colour kThumb  { 0xff1c1d20 };   // dark slider thumb cap
    static const juce::Colour kOrange { 0xfff3991f };   // RAND / SAVE buttons
    static const juce::Colour kSage   { 0xffcdd0c1 };   // preset buttons (light sage)
}

//==============================================================================
// Small dark rocker switch with an AMBER LED that lights when ON (bound to a 0..1 param).
class JunoSwitch  : public juce::Component
{
public:
    explicit JunoSwitch (const toi::Palette&) {}
    void bindTo (juce::AudioProcessorParameter* p)
    { param_ = p; if (! p) return; slider.setRange (0.0, 1.0, 0.0); attach = std::make_unique<toi::ParamKnobAttachment> (*p, slider); addChildComponent (slider); slider.setVisible (false); }
    bool on() const { return (param_ ? param_->getValue() : (float) slider.getValue()) >= 0.5f; }
    void mouseDown (const juce::MouseEvent&) override { slider.setValue (on() ? 0.0 : 1.0, juce::sendNotificationSync); repaint(); }
    void paint (juce::Graphics& g) override
    {
        auto b = getLocalBounds().toFloat().reduced (1.0f);
        const bool o = on();
        juce::ColourGradient bg (juce::Colour (0xff3a3e44), b.getCentreX(), b.getY(),
                                 juce::Colour (0xff141518), b.getCentreX(), b.getBottom(), false);
        g.setGradientFill (bg); g.fillRoundedRectangle (b, 2.5f);
        g.setColour (juno_ui::kFrame); g.drawRoundedRectangle (b, 2.5f, 1.0f);
        // amber LED near the top, lit when ON
        const float d = juce::jmin (b.getWidth(), b.getHeight()) * 0.42f;
        auto led = juce::Rectangle<float> (0, 0, d, d).withCentre ({ b.getCentreX(), b.getY() + d * 0.85f });
        g.setColour (o ? juno_ui::kAccent.brighter (0.15f) : juce::Colour (0xff3a2a14));
        g.fillEllipse (led);
        if (o) { g.setColour (juno_ui::kAccent.brighter (0.6f).withAlpha (0.6f)); g.fillEllipse (led.reduced (d * 0.28f)); }
        g.setColour (juce::Colours::black.withAlpha (0.6f)); g.drawEllipse (led, 0.8f);
    }
private:
    juce::Slider slider; std::unique_ptr<toi::ParamKnobAttachment> attach; juce::AudioProcessorParameter* param_ = nullptr;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JunoSwitch)
};

//==============================================================================
// 3-position RANGE rocker (16' / 8' / 4'). Clicking cycles down<-normal->up (maps to <0.33 / mid / >0.66).
class JunoRange  : public juce::Component
{
public:
    explicit JunoRange (const toi::Palette&) {}
    void bindTo (juce::AudioProcessorParameter* p)
    { param_ = p; if (! p) return; slider.setRange (0.0, 1.0, 0.0); attach = std::make_unique<toi::ParamKnobAttachment> (*p, slider); addChildComponent (slider); slider.setVisible (false); }
    int pos() const { const float v = param_ ? param_->getValue() : (float) slider.getValue(); return v < 0.33f ? 0 : (v > 0.66f ? 2 : 1); }   // 0=16' 1=8' 2=4'
    void mouseDown (const juce::MouseEvent&) override { const int n = (pos() + 1) % 3; slider.setValue (n == 0 ? 0.0 : n == 1 ? 0.5 : 1.0, juce::sendNotificationSync); repaint(); }
    void paint (juce::Graphics& g) override
    {
        auto b = getLocalBounds().toFloat().reduced (1.0f);
        juce::ColourGradient bg (juce::Colour (0xff3a3e44), b.getCentreX(), b.getY(),
                                 juce::Colour (0xff141518), b.getCentreX(), b.getBottom(), false);
        g.setGradientFill (bg); g.fillRoundedRectangle (b, 2.5f);
        g.setColour (juno_ui::kFrame); g.drawRoundedRectangle (b, 2.5f, 1.0f);
        // three stacked cells, the active one amber-lit (top=4', mid=8', bottom=16')
        const int p = pos();   // 0=16'(bottom) 1=8'(mid) 2=4'(top)
        auto inner = b.reduced (2.0f);
        const float ch = inner.getHeight() / 3.0f;
        for (int row = 0; row < 3; ++row)   // row 0=top(4'), 1=mid(8'), 2=bottom(16')
        {
            auto cell = juce::Rectangle<float> (inner.getX(), inner.getY() + row * ch, inner.getWidth(), ch).reduced (0.0f, 0.8f);
            const bool lit = (row == 0 && p == 2) || (row == 1 && p == 1) || (row == 2 && p == 0);
            g.setColour (lit ? juno_ui::kAccent.brighter (0.1f) : juce::Colour (0xff2a2d32));
            g.fillRoundedRectangle (cell, 1.2f);
        }
    }
private:
    juce::Slider slider; std::unique_ptr<toi::ParamKnobAttachment> attach; juce::AudioProcessorParameter* param_ = nullptr;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JunoRange)
};

//==============================================================================
// CHORUS button (I or II): a rectangular switch that LIGHTS amber when on (bound to a 0..1 param).
class JunoChorusBtn  : public juce::Component
{
public:
    JunoChorusBtn (const juce::String& text, const toi::Palette&) : label (text) {}
    void bindTo (juce::AudioProcessorParameter* p)
    { param_ = p; if (! p) return; slider.setRange (0.0, 1.0, 0.0); attach = std::make_unique<toi::ParamKnobAttachment> (*p, slider); addChildComponent (slider); slider.setVisible (false); }
    bool on() const { return (param_ ? param_->getValue() : (float) slider.getValue()) >= 0.5f; }
    void mouseDown (const juce::MouseEvent&) override { slider.setValue (on() ? 0.0 : 1.0, juce::sendNotificationSync); repaint(); }
    void paint (juce::Graphics& g) override
    {
        auto b = getLocalBounds().toFloat().reduced (1.0f);
        const bool o = on();
        juce::ColourGradient bg (o ? juno_ui::kAccent.brighter (0.05f) : juce::Colour (0xff3a3e44), b.getCentreX(), b.getY(),
                                 o ? juno_ui::kAccent.darker (0.25f)   : juce::Colour (0xff181a1d), b.getCentreX(), b.getBottom(), false);
        g.setGradientFill (bg); g.fillRoundedRectangle (b, 3.0f);
        if (o) { g.setColour (juno_ui::kAccent.brighter (0.5f).withAlpha (0.5f)); g.drawRoundedRectangle (b.reduced (1.0f), 2.5f, 1.4f); }
        g.setColour (juno_ui::kFrame); g.drawRoundedRectangle (b, 3.0f, 1.2f);
        g.setColour (o ? juce::Colour (0xff201405) : juno_ui::kWhite); g.setFont (toi::uiFont (juce::jmin (13.0f, b.getHeight() * 0.6f), true));
        g.drawText (label, getLocalBounds(), juce::Justification::centred);
    }
private:
    juce::String label;
    juce::Slider slider; std::unique_ptr<toi::ParamKnobAttachment> attach; juce::AudioProcessorParameter* param_ = nullptr;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JunoChorusBtn)
};

//==============================================================================
// Programmer preset button: grey, slightly-domed square with a small AMBER LED near the top.
class JunoPreset  : public juce::Button
{
public:
    explicit JunoPreset (const toi::Palette&) : juce::Button ("preset") {}
    void setActive (bool a) { if (active != a) { active = a; repaint(); } }
    void paintButton (juce::Graphics& g, bool over, bool down) override
    {
        auto b = getLocalBounds().toFloat().reduced (1.0f);
        const float base = over ? 0.06f : 0.0f;
        // light SAGE preset button; brighter when active, with a red LED
        auto capTop = (active ? juno_ui::kSage.brighter (0.10f) : juno_ui::kSage).brighter (base);
        juce::ColourGradient cap (capTop, b.getCentreX(), b.getY(),
                                  juno_ui::kSage.darker (active ? 0.06f : 0.22f), b.getCentreX(), b.getBottom(), false);
        g.setGradientFill (cap); g.fillRoundedRectangle (b, 2.2f);
        if (down) { g.setColour (juce::Colours::black.withAlpha (0.16f)); g.fillRoundedRectangle (b, 2.2f); }
        g.setColour (juce::Colours::white.withAlpha (0.45f)); g.drawLine (b.getX() + 1.5f, b.getY() + 1.0f, b.getRight() - 1.5f, b.getY() + 1.0f, 1.0f);
        g.setColour (juce::Colours::black.withAlpha (0.40f)); g.drawRoundedRectangle (b, 2.2f, 1.0f);
        const float d = juce::jmin (b.getWidth(), b.getHeight()) * 0.30f;
        auto led = juce::Rectangle<float> (0, 0, d, d).withCentre ({ b.getCentreX(), b.getY() + d * 1.05f });
        g.setColour (active ? juno_ui::kBarRed.brighter (0.15f) : juce::Colour (0xff6a6f60));
        g.fillEllipse (led);
        if (active) { g.setColour (juno_ui::kBarRed.brighter (0.6f).withAlpha (0.7f)); g.fillEllipse (led.reduced (d * 0.3f)); }
        g.setColour (juce::Colours::black.withAlpha (0.5f)); g.drawEllipse (led, 0.6f);
    }
private:
    bool active = false;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JunoPreset)
};

//==============================================================================
inline toi::Config junoConfig()
{
    toi::Config c;
    c.model = "JW-JUN";
    auto& p = c.pal;
    p.bg = juno_ui::kPanel; p.bg2 = juno_ui::kPanelLo; p.frame = juno_ui::kFrame; p.ink = juno_ui::kInk;
    p.accent = juno_ui::kAccent; p.accent2 = juno_ui::kAccent; p.button = juce::Colour (0xff26292e);
    p.thumb = juce::Colour (0xff2a2c30); p.text = juno_ui::kInk;   // dark fader caps + dark labels on grey
    p.lcdBg = juce::Colour (0xff5f6165);   // recessed slider track on the grey body
    p.noteStrip = juno_ui::kAccent;        // BLUE note-name band above the keyboard
    p.keyWhite = juce::Colour (0xffEDEDEA); p.keyWhitePr = juce::Colour (0xfff2cf9a);
    p.keyBlack = juce::Colour (0xff6d8a90); p.keyBlackPr = juce::Colour (0xff90b1b7);   // teal/slate black keys

    c.params = {
        { "lfoRate","RATE" }, { "lfoDelay","DELAY" },
        { "dcoLfo","LFO" }, { "pwm","PWM" }, { "pwmMode","PWM MODE" }, { "pulse","PULSE" }, { "saw","SAW" },
        { "subLevel","SUB" }, { "noiseLevel","NOISE" }, { "range","RANGE" },
        { "hpf","HPF" },
        { "cutoff","FREQ" }, { "reso","RES" }, { "vcfEnv","ENV" }, { "vcfEnvPol","POL" }, { "vcfLfo","LFO" }, { "vcfKbd","KYBD" },
        { "vcaLevel","LEVEL" }, { "vcaMode","GATE" },
        { "attack","A" }, { "decay","D" }, { "sustain","S" }, { "release","R" },
        { "chorusI","I" }, { "chorusII","II" },
        { "volume","VOLUME" }, { "tune","TUNE" },
    };

    // 16 classic Juno patches. P() takes musical params; structural ones are appended in c.params order.
    // Order: lfoRate,lfoDelay, dcoLfo,pwm,pwmMode,pulse,saw,subLevel,noiseLevel,range, hpf,
    //        cutoff,reso,vcfEnv,vcfEnvPol,vcfLfo,vcfKbd, vcaLevel,vcaMode, attack,decay,sustain,release,
    //        chorusI,chorusII, volume,tune.   (volume=.8, tune=.5 fixed)
    auto P = [] (const char* nm,
                 float dcoLfo,float pwm,float pwmMode,float pulse,float saw,float sub,float noise,float range,float hpf,
                 float cut,float res,float fenv,float pol,float flfo,float kbd,
                 float vcaMode, float a,float d,float s,float r,
                 float chI,float chII)
    {
        return toi::FactoryPreset { nm, { 0.30f,0.0f,
                                          dcoLfo,pwm,pwmMode,pulse,saw,sub,noise,range, hpf,
                                          cut,res,fenv,pol,flfo,kbd, 0.80f,vcaMode,
                                          a,d,s,r, chI,chII, 0.80f,0.50f } };
    };
    c.factory = {
        //              dLfo pwm  pwmM pls  saw  sub  nz   rng  hpf  cut  res  fenv pol  flfo kbd  vcaM a    d    s    r    chI  chII
        P("LUSH PAD",     0.10,0.40,0.0, 1.0,1.0, 0.0,0.0, 0.50,0.0, 0.42,0.18,0.30,0.0, 0.0, 0.4, 0.0, 0.45,0.6,0.85,0.6, 1.0, 0.0),
        P("BRASS",        0.0, 0.30,1.0, 1.0,1.0, 0.0,0.0, 0.50,0.0, 0.48,0.25,0.55,0.0, 0.0, 0.5, 0.0, 0.08,0.5,0.7, 0.4, 1.0, 0.0),
        P("FAT BASS",     0.0, 0.30,1.0, 1.0,1.0, 0.6,0.0, 0.17,0.0, 0.40,0.30,0.55,0.0, 0.0, 0.3, 0.0, 0.02,0.35,0.1,0.2, 0.0, 0.0),
        P("SYNTH PLUCK",  0.0, 0.30,1.0, 1.0,1.0, 0.0,0.0, 0.50,0.0, 0.50,0.40,0.65,0.0, 0.0, 0.5, 0.0, 0.01,0.30,0.0,0.2, 0.0, 1.0),
        P("STRINGS",      0.10,0.45,0.0, 1.0,1.0, 0.0,0.0, 0.50,0.33,0.50,0.18,0.30,0.0, 0.0, 0.5, 0.0, 0.50,0.6,0.85,0.7, 1.0, 1.0),
        P("ORGAN",        0.0, 0.30,1.0, 1.0,1.0, 0.8,0.0, 0.50,0.0, 0.62,0.15,0.10,0.0, 0.0, 0.6, 1.0, 0.0, 0.5,1.0, 0.0, 1.0, 0.0),
        P("SYNC-Y LEAD",  0.20,0.30,1.0, 1.0,1.0, 0.0,0.0, 0.85,0.0, 0.55,0.55,0.55,0.0, 0.0, 0.6, 0.0, 0.02,0.4,0.7, 0.3, 0.0, 1.0),
        P("PWM PAD",      0.0, 0.55,0.0, 1.0,0.0, 0.0,0.0, 0.50,0.0, 0.45,0.20,0.30,0.0, 0.0, 0.5, 0.0, 0.45,0.6,0.85,0.7, 1.0, 0.0),
        P("OCTAVE BASS",  0.0, 0.30,1.0, 0.0,1.0, 0.9,0.0, 0.17,0.0, 0.42,0.25,0.55,0.0, 0.0, 0.4, 0.0, 0.02,0.4,0.2, 0.2, 0.0, 0.0),
        P("SWEEP",        0.0, 0.30,0.0, 1.0,1.0, 0.0,0.0, 0.50,0.0, 0.35,0.45,0.70,0.0, 0.0, 0.5, 0.0, 0.10,0.7,0.4, 0.5, 1.0, 0.0),
        P("HOLLOW PWM",   0.30,0.60,0.0, 1.0,0.0, 0.0,0.0, 0.50,0.0, 0.50,0.20,0.30,0.0, 0.0, 0.5, 0.0, 0.30,0.5,0.7, 0.5, 1.0, 1.0),
        P("BELL CHORUS",  0.0, 0.30,1.0, 1.0,0.0, 0.0,0.0, 0.85,0.0, 0.55,0.30,0.60,0.0, 0.0, 0.6, 0.0, 0.01,0.4,0.0, 0.4, 1.0, 1.0),
        P("SOFT KEYS",    0.10,0.40,0.0, 1.0,1.0, 0.0,0.0, 0.50,0.0, 0.52,0.18,0.45,0.0, 0.0, 0.5, 0.0, 0.02,0.45,0.4,0.4, 1.0, 0.0),
        P("WIND NOISE",   0.0, 0.30,0.0, 0.0,0.0, 0.0,0.9, 0.50,0.66,0.45,0.40,0.50,0.0, 0.3, 0.5, 0.0, 0.30,0.6,0.6, 0.5, 1.0, 1.0),
        P("NEG-ENV WAH",  0.0, 0.30,1.0, 1.0,1.0, 0.0,0.0, 0.50,0.0, 0.55,0.50,0.55,1.0, 0.0, 0.5, 0.0, 0.02,0.5,0.5, 0.3, 0.0, 1.0),
        P("BIG POLY",     0.08,0.42,0.0, 1.0,1.0, 0.3,0.0, 0.50,0.0, 0.52,0.20,0.40,0.0, 0.0, 0.5, 0.0, 0.25,0.6,0.85,0.6, 1.0, 1.0),
    };
    return c;
}

//==============================================================================
class JunoEditor  : public toi::PanelEditor
{
public:
    JunoEditor (juce::AudioProcessor& proc, juce::MidiKeyboardState& kb)
        : toi::PanelEditor (proc, kb, junoConfig())
    {
        auto fader = [this] (const juce::String& id, const juce::String& label, std::vector<std::unique_ptr<toi::StyledFader>>& dst)
        {
            auto f = std::make_unique<toi::StyledFader> (label, pal());
            if (auto* prm = findParam (id)) f->attach (*prm);
            addAndMakeVisible (*f); dst.push_back (std::move (f));
        };
        auto sw = [this] (const juce::String& id) -> JunoSwitch*
        { auto s = std::make_unique<JunoSwitch> (pal()); s->bindTo (findParam (id)); addAndMakeVisible (*s); switches.push_back (std::move (s)); return switches.back().get(); };

        fader ("lfoRate","RATE",kLfo); fader ("lfoDelay","DELAY",kLfo);
        fader ("dcoLfo","LFO",kDco); fader ("pwm","PWM",kDco); fader ("subLevel","SUB",kDco); fader ("noiseLevel","NOISE",kDco);
        swRange = std::make_unique<JunoRange> (pal()); swRange->bindTo (findParam ("range")); addAndMakeVisible (*swRange);
        swPulse = sw ("pulse"); swSaw = sw ("saw"); swPwmMode = sw ("pwmMode");
        fader ("hpf","HPF",kHpf);
        fader ("cutoff","FREQ",kVcf); fader ("reso","RES",kVcf); fader ("vcfEnv","ENV",kVcf); fader ("vcfLfo","LFO",kVcf); fader ("vcfKbd","KYBD",kVcf);
        swEnvPol = sw ("vcfEnvPol");
        fader ("vcaLevel","LEVEL",kVca);
        swVcaMode = sw ("vcaMode");
        fader ("attack","A",kEnv); fader ("decay","D",kEnv); fader ("sustain","S",kEnv); fader ("release","R",kEnv);
        fader ("volume","VOL",kMaster); fader ("tune","TUNE",kMaster);

        chI_  = std::make_unique<JunoChorusBtn> ("I",  pal());  chI_->bindTo  (findParam ("chorusI"));  addAndMakeVisible (*chI_);
        chII_ = std::make_unique<JunoChorusBtn> ("II", pal());  chII_->bindTo (findParam ("chorusII")); addAndMakeVisible (*chII_);

        for (int i = 0; i < 16; ++i)
        { auto b = std::make_unique<JunoPreset> (pal()); const int idx = i; b->onClick = [this, idx] { recallSlot (idx); }; addAndMakeVisible (*b); slots.push_back (std::move (b)); }
        rand_ = std::make_unique<toi::Button> ("RAND", pal());
        save_ = std::make_unique<toi::Button> ("SAVE", pal());
        rand_->setFill (juno_ui::kOrange); save_->setFill (juno_ui::kOrange);   // orange function buttons
        rand_->onClick = [this] { doRandom(); rand_->flash(); };
        save_->onClick = [this] { saveSlot (activeSlot()); save_->flash(); };
        addAndMakeVisible (*rand_); addAndMakeVisible (*save_);
        finishSetup();
    }

protected:
    void setPresetActiveVisual (int idx) override { for (int i = 0; i < (int) slots.size(); ++i) slots[(size_t) i]->setActive (i == idx); }

    // dark-metal section box with a centred white title near the top edge
    void box (juce::Graphics& g, juce::Rectangle<float> r, const juce::String& title)
    {
        juce::ColourGradient bg (juno_ui::kBox, r.getCentreX(), r.getY(), juno_ui::kBoxLo, r.getCentreX(), r.getBottom(), false);
        g.setGradientFill (bg); g.fillRoundedRectangle (r, 3.0f);
        g.setColour (juno_ui::kFrame); g.drawRoundedRectangle (r.reduced (0.5f), 3.0f, 1.0f);
        // solid RED header bar (rounded top corners) with the white section title - the Juno look
        auto bar = r.withHeight (15.0f);
        juce::Path bp; bp.addRoundedRectangle (bar.getX(), bar.getY(), bar.getWidth(), bar.getHeight(),
                                                3.0f, 3.0f, true, true, false, false);
        g.setColour (juno_ui::kBarRed); g.fillPath (bp);
        g.setColour (juno_ui::kFrame.withAlpha (0.55f));
        g.fillRect (juce::Rectangle<float> (bar.getX(), bar.getBottom() - 0.7f, bar.getWidth(), 0.9f));
        g.setColour (juno_ui::kWhite);
        g.setFont (toi::uiFont (9.0f, true).withExtraKerningFactor (0.12f));
        g.drawText (title, bar, juce::Justification::centred);
    }

    void paintPanel (juce::Graphics& g, juce::Rectangle<float> panel) override
    {
        juce::ignoreUnused (panel);
        // red stripe across the very top of the panel (matches the section bars)
        g.setColour (juno_ui::kBarRed);
        g.fillRect (juce::Rectangle<float> (rPanelTop.getX(), rPanelTop.getY(), rPanelTop.getWidth(), 4.0f));

        box (g, rLfo,  "LFO");
        box (g, rDco,  "DCO");
        box (g, rHpf,  "HPF");
        box (g, rVcf,  "VCF");
        box (g, rVca,  "VCA");
        box (g, rEnv,  "ENV");
        box (g, rChorus,"CHORUS");
        box (g, rMaster,"");

        // DCO toggle labels (dark on grey)
        g.setColour (juno_ui::kInk); g.setFont (toi::uiFont (6.5f, true));
        g.drawText ("RANGE",    rRangeLbl, juce::Justification::centred);
        g.drawText ("PULSE",    rPulseLbl, juce::Justification::centred);
        g.drawText ("SAW",      rSawLbl,   juce::Justification::centred);
        g.drawText ("MANUAL",   rPwmModeLbl, juce::Justification::centred);
        g.drawText ("INV",      rEnvPolLbl, juce::Justification::centred);
        g.drawText ("GATE",     rVcaModeLbl, juce::Justification::centred);

        // MASTER group label
        g.setColour (juno_ui::kInk); g.setFont (toi::uiFont (8.0f, true).withExtraKerningFactor (0.08f));
        g.drawText ("MASTER", rMasterHdr, juce::Justification::centred);

        // PROGRAMMER strip label + frame
        g.setColour (juno_ui::kInk.withAlpha (0.5f)); g.drawRoundedRectangle (rProg, 3.0f, 1.0f);
        g.setColour (juno_ui::kWhiteDim); g.setFont (toi::uiFont (7.0f, true).withExtraKerningFactor (0.12f));
        g.drawText ("PROGRAMMER", rProgLbl, juce::Justification::centredLeft);

        // brand + MODULE/SIZE leds (lower-right within MASTER block area, below the knobs)
        auto bh = rBrandHdr;
        drawViewLeds (g, bh.removeFromTop (18.0f));
        g.setColour (juno_ui::kInk); g.setFont (toi::uiFont (15.0f, true));
        g.drawText ("JW-JUN", bh.withHeight (17.0f), juce::Justification::centred);
        g.setColour (juno_ui::kWhiteDim); g.setFont (toi::uiFont (5.5f, true).withExtraKerningFactor (0.2f));
        g.drawText ("TOI - plugin corp", bh.withTrimmedTop (16.0f).withHeight (8.0f), juce::Justification::centred);
    }

    void layoutPanel (juce::Rectangle<float> panel) override
    {
        rPanelTop = panel;
        auto inner = panel.reduced (10.0f, 8.0f);
        inner.removeFromTop (6.0f);   // leave room for the accent stripe

        // bottom PROGRAMMER strip across the full panel
        rProg = inner.removeFromBottom (28.0f);
        inner.removeFromBottom (6.0f);
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

        // ---- left-to-right Juno order: LFO | DCO | HPF | VCF | VCA | ENV | (CHORUS + MASTER) ----
        auto main = inner;
        const float colGap = 6.0f;
        const float totalW = main.getWidth() - colGap * 7.0f;
        // proportional widths (DCO + VCF are widest; HPF + VCA are thin single-fader columns)
        const float wLfo = totalW * 0.085f, wDco = totalW * 0.215f, wHpf = totalW * 0.055f,
                    wVcf = totalW * 0.235f, wVca = totalW * 0.055f, wEnv = totalW * 0.155f,
                    wChorus = totalW * 0.085f;
        rLfo    = juce::Rectangle<float> (main.getX(), main.getY(), wLfo, main.getHeight());
        rDco    = juce::Rectangle<float> (rLfo.getRight() + colGap, main.getY(), wDco, main.getHeight());
        rHpf    = juce::Rectangle<float> (rDco.getRight() + colGap, main.getY(), wHpf, main.getHeight());
        rVcf    = juce::Rectangle<float> (rHpf.getRight() + colGap, main.getY(), wVcf, main.getHeight());
        rVca    = juce::Rectangle<float> (rVcf.getRight() + colGap, main.getY(), wVca, main.getHeight());
        rEnv    = juce::Rectangle<float> (rVca.getRight() + colGap, main.getY(), wEnv, main.getHeight());
        rChorus = juce::Rectangle<float> (rEnv.getRight() + colGap, main.getY(), wChorus, main.getHeight());
        rMaster = juce::Rectangle<float> (rChorus.getRight() + colGap, main.getY(), main.getRight() - rChorus.getRight() - colGap, main.getHeight());

        faderRow (kLfo, rLfo.reduced (4.0f, 4.0f).withTrimmedTop (18.0f));

        // DCO: 4 faders on top, toggles row at the bottom (RANGE, PULSE, SAW, MANUAL)
        { auto r = rDco.reduced (4.0f, 4.0f).withTrimmedTop (18.0f);
          auto togRow = r.removeFromBottom (40.0f);
          faderRow (kDco, r);
          const float tw = togRow.getWidth() / 4.0f;
          auto place = [&] (juce::Component* comp, int i, float w, float h, juce::Rectangle<float>& lbl)
          { auto cell = juce::Rectangle<float> (togRow.getX() + i * tw, togRow.getY(), tw, togRow.getHeight());
            placeInArtboard (*comp, juce::Rectangle<float> (cell.getCentreX() - w * 0.5f, cell.getY() + 2.0f, w, h));
            lbl = juce::Rectangle<float> (cell.getX(), cell.getY() + h + 3.0f, cell.getWidth(), 9.0f); };
          place (swRange.get(),   0, 16.0f, 26.0f, rRangeLbl);
          place (swPulse,         1, 16.0f, 22.0f, rPulseLbl);
          place (swSaw,           2, 16.0f, 22.0f, rSawLbl);
          place (swPwmMode,       3, 16.0f, 22.0f, rPwmModeLbl); }

        faderRow (kHpf, rHpf.reduced (3.0f, 4.0f).withTrimmedTop (18.0f));

        // VCF: 5 faders + INV(env-pol) toggle at the bottom
        { auto r = rVcf.reduced (4.0f, 4.0f).withTrimmedTop (18.0f);
          auto togRow = r.removeFromBottom (34.0f);
          faderRow (kVcf, r);
          placeInArtboard (*swEnvPol, juce::Rectangle<float> (togRow.getCentreX() - 8.0f, togRow.getY() + 2.0f, 16.0f, 20.0f));
          rEnvPolLbl = juce::Rectangle<float> (togRow.getCentreX() - 24.0f, togRow.getY() + 23.0f, 48.0f, 9.0f); }

        // VCA: 1 fader + GATE toggle at the bottom
        { auto r = rVca.reduced (3.0f, 4.0f).withTrimmedTop (18.0f);
          auto togRow = r.removeFromBottom (34.0f);
          faderRow (kVca, r);
          placeInArtboard (*swVcaMode, juce::Rectangle<float> (togRow.getCentreX() - 8.0f, togRow.getY() + 2.0f, 16.0f, 20.0f));
          rVcaModeLbl = juce::Rectangle<float> (togRow.getCentreX() - 24.0f, togRow.getY() + 23.0f, 48.0f, 9.0f); }

        faderRow (kEnv, rEnv.reduced (4.0f, 4.0f).withTrimmedTop (18.0f));

        // CHORUS: two SMALL lit buttons (I / II), centred in the section (not huge)
        { auto r = rChorus.reduced (8.0f, 6.0f).withTrimmedTop (20.0f);
          const float bw = juce::jmin (r.getWidth(), 40.0f), bh = 24.0f, gap = 9.0f;
          auto cen = r.withSizeKeepingCentre (bw, bh * 2.0f + gap);
          placeInArtboard (*chI_,  cen.removeFromTop (bh));
          cen.removeFromTop (gap);
          placeInArtboard (*chII_, cen.removeFromTop (bh)); }

        // MASTER: brand badge + VOLUME + TUNE faders
        { auto r = rMaster.reduced (6.0f, 4.0f).withTrimmedTop (16.0f);
          rMasterHdr = r.removeFromTop (10.0f);
          auto fr = r.removeFromTop (r.getHeight() * 0.62f);
          faderRow (kMaster, fr);
          rBrandHdr = r.withTrimmedTop (4.0f).reduced (2.0f, 0.0f); }
    }

private:
    void faderRow (std::vector<std::unique_ptr<toi::StyledFader>>& v, juce::Rectangle<float> r)
    {
        const int n = (int) v.size(); if (n == 0) return;
        const float cw = r.getWidth() / (float) n;
        for (int i = 0; i < n; ++i)
            placeInArtboard (*v[(size_t) i], juce::Rectangle<float> (r.getX() + i * cw, r.getY(), cw, r.getHeight()).reduced (2.0f, 1.0f));
    }

    std::vector<std::unique_ptr<toi::StyledFader>> kLfo, kDco, kHpf, kVcf, kVca, kEnv, kMaster;
    std::vector<std::unique_ptr<JunoSwitch>>       switches;
    JunoSwitch *swPulse = nullptr, *swSaw = nullptr, *swPwmMode = nullptr, *swEnvPol = nullptr, *swVcaMode = nullptr;
    std::unique_ptr<JunoRange>     swRange;
    std::unique_ptr<JunoChorusBtn> chI_, chII_;
    std::vector<std::unique_ptr<JunoPreset>> slots;
    std::unique_ptr<toi::Button> rand_, save_;
    juce::Rectangle<float> rPanelTop, rLfo, rDco, rHpf, rVcf, rVca, rEnv, rChorus, rMaster, rMasterHdr, rBrandHdr,
                           rRangeLbl, rPulseLbl, rSawLbl, rPwmModeLbl, rEnvPolLbl, rVcaModeLbl, rProg, rProgLbl;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JunoEditor)
};

//==============================================================================
class JunoPlugin  : public cmaj::plugin::GeneratedPlugin<::JUNO>,
                    public toi::AudioTapSource,
                    public toi::PresetStore
{
public:
    using Base = cmaj::plugin::GeneratedPlugin<::JUNO>;
    JunoPlugin (std::shared_ptr<cmaj::Patch> p) : Base (std::move (p)) {}
    juce::AudioProcessorEditor* createEditor() override { return new JunoEditor (*this, keyboardState); }
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
