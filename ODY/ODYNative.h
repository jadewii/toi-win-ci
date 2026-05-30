// JW-ODY native faceplate (duophonic whiteface tribute) on the toi_faceplate.h kit.
// Traces the early white-face ARP Odyssey: an off-white panel with WALNUT end-cheeks, black
// silkscreen, and the signature WALL OF SLIDERS with scattered MULTICOLORED square caps. The lone
// rotary PITCH-BEND knob lower-left (Mk I has no wheels/PPC pads). NO brand names.
#pragma once

#include "toi_faceplate.h"

struct JWODY;

namespace ody
{
    static const juce::Colour kPaper { 0xffe9e5d8 };   // off-white / warm light-grey panel
    static const juce::Colour kPaperLo{ 0xffd9d4c4 };
    static const juce::Colour kInk    { 0xff1c1b17 };   // black silkscreen
    static const juce::Colour kDim    { 0xff5d594e };
    static const juce::Colour kWalnut { 0xff6f4a2c };   // wood end-cheeks
    static const juce::Colour kWalnutD{ 0xff4a2f18 };
}

namespace ody
{
    // scattered slider-cap colors (roughly the real distribution: lots of red, some black/pink/blue/yellow/green, rare white)
    static const juce::Colour CAPS[] = {
        juce::Colour (0xffc23529), juce::Colour (0xffd8b03a), juce::Colour (0xff3f6bb6), juce::Colour (0xff2c2c2c),
        juce::Colour (0xff3f9a5a), juce::Colour (0xffcf7aa1), juce::Colour (0xffc23529), juce::Colour (0xffe9e5d8),
        juce::Colour (0xff3f6bb6), juce::Colour (0xffd8b03a), juce::Colour (0xffc23529), juce::Colour (0xff3f9a5a),
        juce::Colour (0xffcf7aa1), juce::Colour (0xff2c2c2c), juce::Colour (0xffc23529), juce::Colour (0xff3f6bb6),
        juce::Colour (0xffd8b03a), juce::Colour (0xff3f9a5a), juce::Colour (0xffc23529), juce::Colour (0xffcf7aa1),
        juce::Colour (0xff2c2c2c), juce::Colour (0xff3f6bb6), juce::Colour (0xffc23529), juce::Colour (0xffd8b03a),
        juce::Colour (0xff3f9a5a), juce::Colour (0xffe9e5d8), juce::Colour (0xffc23529), juce::Colour (0xffcf7aa1),
        juce::Colour (0xff3f6bb6), juce::Colour (0xff2c2c2c), juce::Colour (0xffc23529), juce::Colour (0xff3f9a5a),
        juce::Colour (0xffd8b03a), juce::Colour (0xff3f6bb6), juce::Colour (0xffc23529), juce::Colour (0xffcf7aa1),
        juce::Colour (0xff3f9a5a), juce::Colour (0xff2c2c2c), juce::Colour (0xffc23529), juce::Colour (0xff3f6bb6),
        juce::Colour (0xffd8b03a), juce::Colour (0xff3f9a5a), juce::Colour (0xffcf7aa1), juce::Colour (0xff3f6bb6),
    };
    inline juce::Colour cap (int i) { return CAPS[(i % (int) (sizeof (CAPS) / sizeof (CAPS[0]))) ]; }
}

//==============================================================================
// OdySlider - the Odyssey control: a thin dark recessed SLOT + a small SQUARE plastic cap in a
// scattered color. Bound to a 0..1 param. (The rainbow cap wall is the signature look.)
class OdySlider  : public juce::Component
{
public:
    OdySlider (juce::Colour capColour) : capCol (capColour)
    {
        slider.setSliderStyle (juce::Slider::LinearVertical);
        slider.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
        slider.setLookAndFeel (&laf);
        slider.setRange (0.0, 1.0, 0.0);
        addAndMakeVisible (slider);
    }
    ~OdySlider() override { slider.setLookAndFeel (nullptr); }
    void attach (juce::AudioProcessorParameter& p)
    { att = std::make_unique<toi::ParamKnobAttachment> (p, slider); slider.setDoubleClickReturnValue (true, p.getDefaultValue()); slider.onValueChange = [this] { repaint(); }; repaint(); }
    void resized() override { slider.setBounds (getLocalBounds()); }
    void paint (juce::Graphics& g) override
    {
        auto b = getLocalBounds().toFloat().reduced (0.0f, 2.0f);
        const float cx = b.getCentreX(), top = b.getY(), h = b.getHeight();
        juce::Rectangle<float> slot (cx - 1.5f, top, 3.0f, h);   // thin long travel like a real ARP Odyssey
        g.setColour (juce::Colour (0xff2a2620)); g.fillRoundedRectangle (slot, 1.5f);
        g.setColour (juce::Colours::black.withAlpha (0.45f)); g.drawRoundedRectangle (slot, 1.5f, 0.7f);
        const float v = juce::jlimit (0.0f, 1.0f, (float) slider.getValue());
        const float capH = 17.0f, capW = 9.0f, pad = capH * 0.5f + 1.0f;   // VERTICAL OVAL thumb (real ARP Odyssey)
        const float ty = top + pad + (1.0f - v) * (h - 2.0f * pad);
        juce::Rectangle<float> cap (cx - capW * 0.5f, ty - capH * 0.5f, capW, capH);
        g.setColour (juce::Colours::black.withAlpha (0.35f)); g.fillEllipse (cap.translated (0.0f, 1.6f));
        juce::ColourGradient cg (capCol.brighter (0.28f), cx, cap.getY(), capCol.darker (0.22f), cx, cap.getBottom(), false);
        g.setGradientFill (cg); g.fillEllipse (cap);
        g.setColour (juce::Colours::black.withAlpha (0.6f)); g.drawEllipse (cap, 0.9f);
        g.setColour (juce::Colours::white.withAlpha (0.5f)); g.fillEllipse (cap.getX() + capW * 0.28f, cap.getY() + 2.0f, capW * 0.3f, capH * 0.28f);
    }
    juce::Slider slider;
private:
    toi::InvisibleLinearLAF laf; juce::Colour capCol;
    std::unique_ptr<toi::ParamKnobAttachment> att;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OdySlider)
};

//==============================================================================
// OdyToggle - small black rocker switch (2 or 3 position) bound to a 0..1 param. Click cycles.
class OdyToggle  : public juce::Component,
                   private juce::AudioProcessorParameter::Listener,
                   private juce::AsyncUpdater
{
public:
    OdyToggle (int positions) : N (positions) {}
    ~OdyToggle() override { if (param_) param_->removeListener (this); cancelPendingUpdate(); }
    void attach (juce::AudioProcessorParameter* p) { param_ = p; if (param_) param_->addListener (this); triggerAsyncUpdate(); }
    void mouseDown (const juce::MouseEvent&) override
    { if (! param_) return; int a = juce::roundToInt (param_->getValue() * (N - 1)); a = (a + 1) % N; param_->setValueNotifyingHost ((float) a / (float) (N - 1)); }
    void paint (juce::Graphics& g) override
    {
        auto b = getLocalBounds().toFloat().reduced (3.0f, 1.0f);
        const int a = param_ ? juce::jlimit (0, N - 1, juce::roundToInt (param_->getValue() * (N - 1))) : 0;
        // dark recessed switch housing
        g.setColour (juce::Colour (0xff141210)); g.fillRoundedRectangle (b, 2.5f);
        g.setColour (juce::Colours::black); g.drawRoundedRectangle (b, 2.5f, 0.9f);
        // the raised toggle lever, sitting at the active position (top..bottom)
        const float segH = b.getHeight() / (float) N;
        auto lever = juce::Rectangle<float> (b.getX() + 1.5f, b.getY() + (float) a * segH + 1.5f, b.getWidth() - 3.0f, segH - 3.0f);
        g.setColour (juce::Colours::black.withAlpha (0.4f)); g.fillRoundedRectangle (lever.translated (0.0f, 1.2f), 2.0f);
        juce::ColourGradient lg (juce::Colour (0xffe6e0d2), lever.getCentreX(), lever.getY(), juce::Colour (0xff86806f), lever.getCentreX(), lever.getBottom(), false);
        g.setGradientFill (lg); g.fillRoundedRectangle (lever, 2.0f);
        g.setColour (juce::Colours::white.withAlpha (0.5f)); g.drawLine (lever.getX() + 2.0f, lever.getY() + 1.4f, lever.getRight() - 2.0f, lever.getY() + 1.4f, 0.8f);
        g.setColour (juce::Colours::black.withAlpha (0.5f)); g.drawRoundedRectangle (lever, 2.0f, 0.7f);
    }
private:
    void parameterValueChanged (int, float) override { triggerAsyncUpdate(); }
    void parameterGestureChanged (int, bool) override {}
    void handleAsyncUpdate() override { repaint(); }
    int N; juce::AudioProcessorParameter* param_ = nullptr;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OdyToggle)
};

//==============================================================================
class OdyFunc  : public juce::Button
{
public:
    OdyFunc (const juce::String& t, juce::Colour fill) : juce::Button (t), col (fill) { setButtonText (t); }
    void flash() { flashing = true; repaint(); juce::Timer::callAfterDelay (150, [s = juce::Component::SafePointer<OdyFunc> (this)] { if (s) { s->flashing = false; s->repaint(); } }); }
    void paintButton (juce::Graphics& g, bool over, bool down) override
    {
        auto b = getLocalBounds().toFloat().reduced (1.0f);
        auto fill = flashing ? col.brighter (0.3f) : down ? col.darker (0.18f) : over ? col.brighter (0.08f) : col;
        g.setColour (fill); g.fillRoundedRectangle (b, 2.5f);
        g.setColour (juce::Colours::black.withAlpha (0.5f)); g.drawRoundedRectangle (b, 2.5f, 1.0f);
        g.setColour (juce::Colours::white.withAlpha (0.92f)); g.setFont (toi::uiFont (juce::jmin (10.0f, b.getHeight() * 0.5f), true));
        g.drawText (getButtonText(), getLocalBounds(), juce::Justification::centred);
    }
private:
    juce::Colour col; bool flashing = false;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OdyFunc)
};

//==============================================================================
inline toi::Config jwodyConfig()
{
    toi::Config c;
    c.model = "JW-ODY";
    auto& p = c.pal;
    p.bg = ody::kPaper; p.bg2 = ody::kPaperLo; p.frame = juce::Colour (0xff2a2018); p.ink = ody::kInk;
    p.accent = juce::Colour (0xffc23529); p.accent2 = juce::Colour (0xff3f6bb6); p.button = juce::Colour (0xff262524);
    p.thumb = juce::Colour (0xffd8b03a); p.text = ody::kInk;
    p.noteStrip = ody::kPaperLo;
    p.lcdBg = juce::Colour (0xff14140f); p.lcdInk = juce::Colour (0xff3f9a5a);
    p.keyWhite = juce::Colour (0xfff2efe6); p.keyWhitePr = juce::Colour (0xffd8b03a); p.keyBlack = juce::Colour (0xff262420); p.keyBlackPr = juce::Colour (0xffc23529);

    c.params = {
        { "portamento","PORT" },{ "transpose","TRANSP" },
        { "o1Freq","FREQ" },{ "o1Fine","FINE" },{ "o1Wave","WAVE" },{ "o1PW","PW" },{ "o1Fm","FM" },
        { "o2Freq","FREQ" },{ "o2Fine","FINE" },{ "o2Wave","WAVE" },{ "o2PW","PW" },{ "o2Fm","FM" },{ "sync","SYNC" },
        { "lfoRate","RATE" },{ "lfoShape","SHAPE" },{ "lfoPitch","PITCH" },{ "lfoPwm","PWM" },{ "lfoFilter","FILT" },
        { "shRate","RATE" },{ "shSource","SRC" },{ "shPitch","PITCH" },{ "shFilter","FILT" },
        { "mixRing","RING" },{ "mixVco1","VCO1" },{ "mixVco2","VCO2" },{ "mixSh","S/H" },{ "mixNoise","NOISE" },
        { "cutoff","FREQ" },{ "reso","RES" },{ "fEnv","ENV" },{ "fKeyTrack","KBD" },{ "hpf","HPF" },
        { "aA","A" },{ "aD","D" },{ "aS","S" },{ "aR","R" },{ "arA","AR-A" },{ "arR","AR-R" },{ "envSel","ENV" },{ "fEnvSel","F-ENV" },
        { "volume","VOL" },{ "tune","TUNE" },{ "bend","BEND" },
    };

    std::vector<float> base (c.params.size(), 0.5f);
    // a sane init - mostly mid, mixers up, envelopes snappy
    auto set = [&] (const char* id, float v) { for (size_t i = 0; i < c.params.size(); ++i) if (c.params[i].id == id) base[i] = v; };
    set ("portamento", 0.0f); set ("o1Wave", 0.0f); set ("o2Wave", 0.0f); set ("sync", 0.0f);
    set ("o1PW", 0.5f); set ("o2PW", 0.5f); set ("mixVco1", 0.8f); set ("mixVco2", 0.0f); set ("mixRing", 0.0f); set ("mixSh", 0.0f); set ("mixNoise", 0.0f);
    set ("cutoff", 0.62f); set ("reso", 0.2f); set ("fEnv", 0.45f); set ("hpf", 0.0f);
    set ("aA", 0.02f); set ("aD", 0.4f); set ("aS", 0.7f); set ("aR", 0.25f); set ("arA", 0.02f); set ("arR", 0.3f);
    set ("envSel", 0.0f); set ("fEnvSel", 0.0f); set ("volume", 0.8f); set ("shSource", 0.0f);

    auto P = [&] (const char* nm, std::initializer_list<std::pair<const char*,float>> ov)
    { auto v = base; for (auto& o : ov) for (size_t i = 0; i < c.params.size(); ++i) if (c.params[i].id == o.first) v[i] = o.second; return toi::FactoryPreset { nm, v }; };

    c.factory = {
        P("INIT", {}),
        P("SYNC LEAD",   {{"sync",1.0f},{"o2Freq",0.62f},{"mixVco1",0.9f},{"cutoff",0.6f},{"reso",0.4f},{"fEnv",0.6f},{"aA",0.02f},{"aD",0.4f}}),
        P("FAT BASS",    {{"o1Freq",0.38f},{"o2Freq",0.39f},{"mixVco1",0.7f},{"mixVco2",0.7f},{"cutoff",0.42f},{"reso",0.35f},{"aD",0.3f},{"aS",0.4f}}),
        P("S&H RANDOM",  {{"shRate",0.4f},{"shPitch",0.5f},{"mixVco1",0.8f},{"cutoff",0.55f},{"reso",0.3f}}),
        P("RING CLANG",  {{"mixRing",0.8f},{"mixVco1",0.3f},{"o2Freq",0.66f},{"cutoff",0.6f},{"reso",0.4f}}),
        P("BRIGHT LEAD", {{"o1Wave",0.0f},{"mixVco1",0.9f},{"cutoff",0.75f},{"reso",0.45f},{"fEnv",0.5f},{"aA",0.02f}}),
        P("PWM PAD",     {{"o1Wave",0.5f},{"o1PW",0.4f},{"lfoPwm",0.5f},{"lfoRate",0.2f},{"mixVco1",0.7f},{"mixVco2",0.6f},{"cutoff",0.5f},{"aA",0.3f},{"aR",0.5f}}),
        P("NOISE SWEEP", {{"mixNoise",0.7f},{"mixVco1",0.3f},{"cutoff",0.4f},{"reso",0.5f},{"fEnv",0.7f},{"lfoFilter",0.4f},{"lfoRate",0.15f}}),
        P("DUO INTERVAL",{{"o2Freq",0.66f},{"mixVco1",0.7f},{"mixVco2",0.7f},{"cutoff",0.6f},{"reso",0.3f}}),
        P("RESO ZAP",    {{"cutoff",0.5f},{"reso",0.7f},{"fEnv",0.8f},{"aD",0.2f},{"aS",0.2f},{"mixVco1",0.8f}}),
        P("HOLLOW PWM",  {{"o1Wave",0.5f},{"o1PW",0.25f},{"mixVco1",0.85f},{"cutoff",0.55f},{"reso",0.4f}}),
        P("SOFT KEYS",   {{"o1Wave",0.0f},{"mixVco1",0.8f},{"cutoff",0.5f},{"aA",0.06f},{"aD",0.5f},{"aS",0.4f},{"aR",0.4f}}),
    };
    return c;
}

//==============================================================================
class JWODYEditor  : public toi::PanelEditor
{
public:
    JWODYEditor (juce::AudioProcessor& proc, juce::MidiKeyboardState& kb)
        : toi::PanelEditor (proc, kb, jwodyConfig())
    {
        groups_ = {
            { "VCO 1", { "o1Freq","o1Fine","o1PW","o1Fm" } },
            { "VCO 2", { "o2Freq","o2Fine","o2PW","o2Fm" } },
            { "LFO", { "lfoRate","lfoShape","lfoPitch","lfoPwm","lfoFilter" } },
            { "SAMPLE & HOLD", { "shRate","shPitch","shFilter" } },
            { "MIXER", { "mixRing","mixVco1","mixVco2","mixSh","mixNoise" } },
            { "FILTER", { "cutoff","reso","fEnv","fKeyTrack","hpf" } },
            { "VCA / ENV", { "aA","aD","aS","aR","arA","arR","volume","tune" } },
        };
        int ci = 0;
        for (auto& grp : groups_) for (auto& id : grp.ids) addSlider (id, ci++);
        addSlider ("portamento", 1);   // CONTROL-column slider (placed manually, not in the wall)

        // toggles (the discrete switches the real Odyssey has)
        addToggle ("o1Wave", 3); addToggle ("o2Wave", 3); addToggle ("sync", 2);
        addToggle ("shSource", 2); addToggle ("envSel", 2); addToggle ("fEnvSel", 2); addToggle ("transpose", 3);

        // the lone Mk I pitch-bend rotary knob
        bend_ = std::make_unique<toi::StyledKnob> ("", pal(), toi::StyledKnob::Pointer); bend_->setShowLabel (false);
        if (auto* prm = findParam ("bend")) bend_->attach (*prm);
        addAndMakeVisible (*bend_);

        for (int i = 0; i < 16; ++i)
        { auto b = std::make_unique<toi::MoldedButton> (juce::Colour (0xffe9e6df)); b->setLit (juce::Colour (0xff2f6fd0)); const int idx = i; b->onClick = [this, idx] { recallSlot (idx); }; addAndMakeVisible (*b); slots_.push_back (std::move (b)); }
        rand_ = std::make_unique<OdyFunc> ("RAND", juce::Colour (0xff6f4a2c)); save_ = std::make_unique<OdyFunc> ("SAVE", juce::Colour (0xffc23529));
        rand_->onClick = [this] { doRandom(); rand_->flash(); };
        save_->onClick = [this] { saveSlot (activeSlot()); save_->flash(); };
        addAndMakeVisible (*rand_); addAndMakeVisible (*save_);

        finishSetup();
    }

protected:
    void setPresetActiveVisual (int idx) override { for (int i = 0; i < (int) slots_.size(); ++i) slots_[(size_t) i]->setActive (i == idx); }

    void paintPanel (juce::Graphics& g, juce::Rectangle<float> panel) override
    {
        rPanel = panel;
        juce::ColourGradient pg (ody::kPaper, panel.getCentreX(), panel.getY(), ody::kPaperLo, panel.getCentreX(), panel.getBottom(), false);
        g.setGradientFill (pg); g.fillRoundedRectangle (panel, 5.0f);

        // NO wood cheeks (Jade) - just a thin dark frame
        g.setColour (juce::Colours::black); g.drawRoundedRectangle (panel, 5.0f, 1.5f);

        // CONTROL column box (own space, top-left) + its labels
        g.setColour (juce::Colour (0x18000000)); g.fillRoundedRectangle (rCtrl_, 3.0f);
        g.setColour (ody::kInk.withAlpha (0.55f)); g.drawRoundedRectangle (rCtrl_, 3.0f, 1.0f);
        g.setColour (ody::kDim); g.setFont (toi::uiFont (5.5f, true));
        g.drawText ("PORT", juce::Rectangle<float> (rPort_.getX() - 4.0f, rCtrl_.getBottom() - 9.0f, rPort_.getWidth() + 8.0f, 8.0f), juce::Justification::centred);

        // section boxes + labels + slider labels
        for (auto& grp : groups_) drawGroupBox (g, grp);

        // toggle labels
        for (auto& t : toggleRects_)
        { g.setColour (ody::kDim); g.setFont (toi::uiFont (5.5f, true));
          g.drawText (t.first, juce::Rectangle<float> (t.second.getX() - 4.0f, t.second.getBottom(), t.second.getWidth() + 8.0f, 7.0f), juce::Justification::centred); }

        // bend knob label
        g.setColour (ody::kDim); g.setFont (toi::uiFont (6.0f, true));
        g.drawText ("PITCH BEND", juce::Rectangle<float> (rBend_.getX() - 10.0f, rBend_.getBottom() + 1.0f, rBend_.getWidth() + 20.0f, 8.0f), juce::Justification::centred);

        // PRESET label
        g.setColour (ody::kInk); g.setFont (toi::uiFont (6.5f, true).withExtraKerningFactor (0.1f));
        g.drawText ("PRESET", juce::Rectangle<float> (rPreset_.getX(), rPreset_.getY() - 9.0f, 120.0f, 9.0f), juce::Justification::centredLeft);

        // brand text + MODULE/SIZE LEDs in SEPARATE bands (no overlap)
        g.setColour (ody::kInk); g.setFont (toi::uiFont (13.0f, true));
        g.drawText ("JW-ODY", rBrand_, juce::Justification::centredLeft);
        drawViewLeds (g, rViewLeds_);
    }

    void drawCheek (juce::Graphics& g, juce::Rectangle<float> r)
    {
        juce::ColourGradient wg (ody::kWalnut, r.getX(), r.getY(), ody::kWalnutD, r.getRight(), r.getY(), false);
        g.setGradientFill (wg); g.fillRect (r);
        juce::Random rr (910 + (int) r.getX());
        g.setColour (ody::kWalnutD.withAlpha (0.35f));
        for (int i = 0; i < 7; ++i) { const float gx = r.getX() + rr.nextFloat() * r.getWidth(); g.drawLine (gx, r.getY(), gx + 2.0f, r.getBottom(), 0.7f); }
    }

    void layoutPanel (juce::Rectangle<float> panel) override
    {
        rPanel = panel;
        auto inner = panel.reduced (14.0f, 8.0f);   // no wood cheeks
        inner.removeFromTop (4.0f);

        // the slider wall
        rowSliders_ = inner.removeFromTop (152.0f);
        inner.removeFromTop (6.0f);

        // LEFT CONTROL COLUMN (own space, clear of the slider wall): brand + view LEDs up top,
        // then the PORT slider + PITCH BEND knob. Fixes the top-left overlap mess.
        rCtrl_ = rowSliders_.removeFromLeft (94.0f); rowSliders_.removeFromLeft (8.0f);
        { auto cc = rCtrl_.reduced (5.0f, 4.0f);
          rBrand_   = cc.removeFromTop (16.0f);                // "JW-ODY" text only
          cc.removeFromTop (3.0f);
          rViewLeds_ = cc.removeFromTop (18.0f);               // MODULE + SIZE LEDs (own band)
          cc.removeFromTop (5.0f);
          rPort_ = cc.removeFromLeft (cc.getWidth() * 0.42f).withTrimmedBottom (10.0f);
          if (auto* ps = sliderFor ("portamento")) placeInArtboard (*ps, rPort_);
          rBend_ = cc.withSizeKeepingCentre (juce::jmin (34.0f, cc.getWidth()), 34.0f).withY (cc.getBottom() - 44.0f);
          placeInArtboard (*bend_, rBend_); }

        // the slider wall (sliders only)
        layoutGroups (rowSliders_);

        // bottom: ONE line, all the SAME HEIGHT - presets (left) + toggle SWITCHES + RAND + SAVE (right)
        auto strip = inner;
        strip.removeFromTop (9.0f);                              // PRESET label room above the line
        strip.removeFromBottom (9.0f);                           // switch labels sit just below the line
        auto band = strip;                                       // the single button line
        const float bh = juce::jmin (30.0f, band.getHeight());   // common button height for everything
        const float by = band.getY() + (band.getHeight() - bh) * 0.5f;
        // RAND + SAVE on the right, switch-sized
        const float fw = 46.0f, fgap = 6.0f;
        auto saveR = band.removeFromRight (fw); band.removeFromRight (fgap);
        auto randR = band.removeFromRight (fw); band.removeFromRight (14.0f);
        placeInArtboard (*save_, juce::Rectangle<float> (saveR.getX(), by, fw, bh));
        placeInArtboard (*rand_, juce::Rectangle<float> (randR.getX(), by, fw, bh));
        // the toggle switches (same height)
        toggleRects_.clear();
        { const char* tg[7] = { "o1Wave","o2Wave","sync","shSource","envSel","fEnvSel","transpose" };
          const int nt = 7; const float tgap = 7.0f, tw = 28.0f;
          auto sw = band.removeFromRight ((float) nt * tw + (float) (nt - 1) * tgap); band.removeFromRight (16.0f);
          float tx = sw.getX();
          for (int i = 0; i < nt; ++i)
          { auto tr = juce::Rectangle<float> (tx, by, tw, bh);
            if (auto* tog = toggleMap_[juce::String (tg[i])]) placeInArtboard (*tog, tr);
            toggleRects_.push_back ({ juce::String (tg[i]), tr }); tx += tw + tgap; } }
        // presets fill the rest of the line, SAME HEIGHT as the switches
        rPreset_ = band;
        { const int pc = 16; const float pgap = 3.0f;
          const float pw = (band.getWidth() - pgap * (pc - 1)) / (float) pc;
          for (int i = 0; i < 16; ++i) placeInArtboard (*slots_[(size_t) i], juce::Rectangle<float> (band.getX() + (float) i * (pw + pgap), by, pw, bh)); }
    }

private:
    struct Group { juce::String name; std::vector<juce::String> ids; juce::Rectangle<float> rect; };

    void addSlider (const juce::String& id, int colorIdx)
    {
        auto s = std::make_unique<OdySlider> (ody::cap (colorIdx));
        if (auto* prm = findParam (id)) s->attach (*prm);
        addAndMakeVisible (*s); sliderMap_[id] = s.get(); sliders_.push_back (std::move (s));
    }
    void addToggle (const juce::String& id, int positions)
    {
        auto t = std::make_unique<OdyToggle> (positions);
        if (auto* prm = findParam (id)) t->attach (prm);
        addAndMakeVisible (*t); toggleMap_[id] = t.get(); toggles_.push_back (std::move (t));
    }
    OdySlider* sliderFor (const juce::String& id) const { auto it = sliderMap_.find (id); return it == sliderMap_.end() ? nullptr : it->second; }

    int totalSliders() const { int n = 0; for (auto& g : groups_) n += (int) g.ids.size(); return n; }

    void layoutGroups (juce::Rectangle<float> row)
    {
        // SLIDERS ONLY (toggles live in the bottom row; CONTROL column is placed separately)
        const int n = totalSliders();
        const float gap = 8.0f;
        const float usable = row.getWidth() - gap * (float) (groups_.size() - 1);
        const float sw = usable / (float) n;
        float x = row.getX();
        const float labelTop = 11.0f, labelBot = 9.0f;
        for (auto& grp : groups_)
        {
            const float gw = sw * (float) grp.ids.size();
            grp.rect = juce::Rectangle<float> (x, row.getY(), gw, row.getHeight());
            for (int i = 0; i < (int) grp.ids.size(); ++i)
                if (auto* s = sliderFor (grp.ids[(size_t) i]))
                    placeInArtboard (*s, juce::Rectangle<float> (x + (float) i * sw, row.getY() + labelTop, sw, row.getHeight() - labelTop - labelBot).reduced (2.0f, 0.0f));
            x += gw + gap;
        }
    }

    void drawGroupBox (juce::Graphics& g, const Group& grp)
    {
        g.setColour (juce::Colour (0x18000000)); g.fillRoundedRectangle (grp.rect, 3.0f);
        g.setColour (ody::kInk.withAlpha (0.55f)); g.drawRoundedRectangle (grp.rect, 3.0f, 1.0f);
        g.setColour (ody::kInk); g.setFont (toi::uiFont (7.0f, true).withExtraKerningFactor (0.06f));
        g.drawText (grp.name, grp.rect.withHeight (10.0f).reduced (4.0f, 1.0f), juce::Justification::centredLeft);
        // slider labels under each cap
        const float sw = (grp.ids.empty() ? grp.rect.getWidth() : 0.0f);
        juce::ignoreUnused (sw);
        for (int i = 0; i < (int) grp.ids.size(); ++i)
        {
            if (auto* s = sliderFor (grp.ids[(size_t) i]))
            {
                juce::String lbl; for (auto& sp : config().params) if (sp.id == grp.ids[(size_t) i]) { lbl = sp.label; break; }
                auto sr = s->getBounds().toFloat();
                g.setColour (ody::kDim); g.setFont (toi::uiFont (5.5f, true));
                g.drawText (lbl, juce::Rectangle<float> (sr.getX() - 4.0f, grp.rect.getBottom() - 9.0f, sr.getWidth() + 8.0f, 8.0f), juce::Justification::centred);
            }
        }
    }

    std::vector<std::unique_ptr<OdySlider>> sliders_;
    std::map<juce::String, OdySlider*> sliderMap_;
    std::vector<std::unique_ptr<OdyToggle>> toggles_;
    std::map<juce::String, OdyToggle*> toggleMap_;
    std::vector<std::pair<juce::String, juce::Rectangle<float>>> toggleRects_;
    std::unique_ptr<toi::StyledKnob> bend_;
    std::unique_ptr<toi::Lcd> scope_;
    std::vector<std::unique_ptr<toi::MoldedButton>> slots_;
    std::unique_ptr<OdyFunc> rand_, save_;
    std::vector<Group> groups_;
    juce::Rectangle<float> rPanel, rowSliders_, rBend_, rScope_, rPreset_, rBrand_, rCtrl_, rPort_, rViewLeds_;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JWODYEditor)
};

//==============================================================================
class JWODYPlugin  : public cmaj::plugin::GeneratedPlugin<::JWODY>,
                     public toi::AudioTapSource,
                     public toi::PresetStore
{
public:
    using Base = cmaj::plugin::GeneratedPlugin<::JWODY>;
    JWODYPlugin (std::shared_ptr<cmaj::Patch> p) : Base (std::move (p)) {}
    juce::AudioProcessorEditor* createEditor() override { return new JWODYEditor (*this, keyboardState); }
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
