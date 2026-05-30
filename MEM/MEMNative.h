// JW-MEM native faceplate (monster-fat 6-voice analog poly) on the toi_faceplate.h kit.
// Late-Moog "Memorymoog" look: golden-oak end-cheeks + a near-black brushed panel, controls
// grouped into a FEW BIG RAISED-CHROME sections (engraved silver name-plates on each top rail).
// OCTAVE (32'/16'/8'/4'/2') + WAVE (saw/tri/pulse) per oscillator and SYNC / UNISON are SQUARE
// BUTTON BANKS (red LED on the active button). All continuous controls keep the vintage FLUTED
// knob with its printed numeral ring. Real-audio scope. NO brand names. Hyphens, not em-dashes.
#pragma once

#include "toi_faceplate.h"

struct JWMEM;

namespace mem
{
    static const juce::Colour kWood   { 0xff9a6a38 };   // lighter golden-oak end-cheeks
    static const juce::Colour kWoodLo { 0xff6e4824 };
    static const juce::Colour kPanel  { 0xff1a1a1d };   // near-black brushed panel
    static const juce::Colour kPanelLo{ 0xff111113 };
    static const juce::Colour kFrame  { 0xff050506 };
    static const juce::Colour kCream  { 0xffece6d8 };   // white legending
    static const juce::Colour kDim    { 0xff968f84 };
    static const juce::Colour kAmber  { 0xffe0a23a };   // warm gold accent
    static const juce::Colour kRed    { 0xffc4392b };   // Moog red (active-button LEDs)
    static const juce::Colour kRedHi  { 0xffff5a44 };
    // raised-CHROME section bezels + engraved name-plate rail
    static const juce::Colour kSilver  { 0xffb9bdc4 };
    static const juce::Colour kSilverHi{ 0xfff2f4f7 };
    static const juce::Colour kSilverLo{ 0xff5f636a };
    static const juce::Colour kEngrave { 0xff34373c };  // dark engraved text on the silver rail
    static const juce::Colour kBtn     { 0xff2a2a2e };  // un-lit molded square
}

//==============================================================================
// MemButtonBank - a radio group bound to ONE 0..1 param. N square molded buttons in a row; the
// active one is lit with a red Memorymoog LED. Click sets the param to that option's normalized
// value (option i -> i/(N-1)); the active index reads back as round(v*(N-1)). Two glyph kinds:
// TextLabels (octave footage 32'/16'/...) or WaveGlyphs (saw / triangle / pulse icons). A small
// title is engraved under the row.
class MemButtonBank  : public juce::Component,
                       private juce::AudioProcessorParameter::Listener,
                       private juce::AsyncUpdater
{
public:
    enum Kind { TextLabels, WaveGlyphs };
    MemButtonBank (juce::StringArray opts, juce::String titleText, Kind k, juce::Colour ledColour)
        : options (std::move (opts)), title (std::move (titleText)), kind (k), led (ledColour) {}
    ~MemButtonBank() override { if (param) param->removeListener (this); cancelPendingUpdate(); }

    void attach (juce::AudioProcessorParameter& p) { param = &p; param->addListener (this); triggerAsyncUpdate(); }

    int  count() const { return options.size(); }
    int  activeIndex() const
    {
        if (param == nullptr || count() <= 1) return 0;
        return juce::jlimit (0, count() - 1, (int) std::lround (param->getValue() * (float) (count() - 1)));
    }
    void setIndex (int i)
    {
        if (param == nullptr || count() <= 1) return;
        const float v = (float) i / (float) (count() - 1);
        param->beginChangeGesture(); param->setValueNotifyingHost (v); param->endChangeGesture();
    }

    void mouseDown (const juce::MouseEvent& e) override
    {
        const int n = count(); if (n <= 0) return;
        auto a = btnArea();
        int i = (int) ((e.position.x - a.getX()) / (a.getWidth() / (float) n));
        setIndex (juce::jlimit (0, n - 1, i));
    }

    void paint (juce::Graphics& g) override
    {
        auto a = btnArea();
        const int n = count(); if (n <= 0) return;
        const float bw = a.getWidth() / (float) n;
        const int act = activeIndex();
        for (int i = 0; i < n; ++i)
        {
            auto box = juce::Rectangle<float> (a.getX() + (float) i * bw, a.getY(), bw, a.getHeight()).reduced (1.4f, 1.2f);
            const bool on = (i == act);
            // contact shadow + molded square plate
            g.setColour (juce::Colours::black.withAlpha (0.5f)); g.fillRoundedRectangle (box.translated (0.0f, 1.0f), 2.6f);
            const juce::Colour bc = on ? mem::kBtn.brighter (0.16f) : mem::kBtn;
            juce::ColourGradient cg (bc.brighter (0.22f), box.getCentreX(), box.getY(), bc.darker (0.22f), box.getCentreX(), box.getBottom(), false);
            g.setGradientFill (cg); g.fillRoundedRectangle (box, 2.6f);
            g.setColour (juce::Colours::white.withAlpha (on ? 0.18f : 0.10f));
            g.fillRoundedRectangle (box.withHeight (box.getHeight() * 0.42f).reduced (1.5f, 0.0f), 2.0f);
            g.setColour (juce::Colours::black.withAlpha (0.7f)); g.drawRoundedRectangle (box, 2.6f, 1.0f);

            // red LED top-centre when active
            const float lr = 2.4f, lx = box.getCentreX(), ly = box.getY() + 4.6f;
            if (on) { g.setColour (mem::kRedHi.withAlpha (0.55f)); g.fillEllipse (lx - lr - 2.2f, ly - lr - 2.2f, (lr + 2.2f) * 2.0f, (lr + 2.2f) * 2.0f); }
            g.setColour (on ? mem::kRedHi : mem::kRed.withAlpha (0.22f)); g.fillEllipse (lx - lr, ly - lr, lr * 2.0f, lr * 2.0f);
            g.setColour (juce::Colours::black.withAlpha (0.6f)); g.drawEllipse (lx - lr, ly - lr, lr * 2.0f, lr * 2.0f, 0.7f);

            auto face = box.withTrimmedTop (8.0f);
            if (kind == WaveGlyphs) drawWave (g, i, face, on);
            else
            {
                g.setColour (on ? mem::kCream : mem::kDim);
                g.setFont (toi::uiFont (juce::jmin (9.5f, face.getHeight() * 0.62f), true));
                g.drawText (options[i], face, juce::Justification::centred);
            }
        }
        if (title.isNotEmpty())
        {
            g.setColour (mem::kSilverHi.withAlpha (0.85f));
            g.setFont (toi::uiFont (6.5f, true).withExtraKerningFactor (0.16f));
            g.drawText (title, getLocalBounds().toFloat().removeFromBottom (labelH), juce::Justification::centred);
        }
    }

private:
    static constexpr float labelH = 9.0f;
    juce::Rectangle<float> btnArea() const
    { auto b = getLocalBounds().toFloat(); if (title.isNotEmpty()) b.removeFromBottom (labelH); return b; }

    void drawWave (juce::Graphics& g, int i, juce::Rectangle<float> r, bool on)
    {
        auto a = r.reduced (r.getWidth() * 0.24f, r.getHeight() * 0.30f);
        const float x0 = a.getX(), x1 = a.getRight(), yT = a.getY(), yB = a.getBottom(), xm = a.getCentreX();
        juce::Path p;
        if      (i == 0) { p.startNewSubPath (x0, yB); p.lineTo (x1, yT); p.lineTo (x1, yB); }                                  // saw
        else if (i == 1) { p.startNewSubPath (x0, yB); p.lineTo (xm, yT); p.lineTo (x1, yB); }                                  // triangle
        else             { p.startNewSubPath (x0, yB); p.lineTo (x0, yT); p.lineTo (xm, yT); p.lineTo (xm, yB); p.lineTo (x1, yB); p.lineTo (x1, yT); } // pulse
        g.setColour (on ? mem::kCream : mem::kDim);
        g.strokePath (p, juce::PathStrokeType (1.5f, juce::PathStrokeType::mitered, juce::PathStrokeType::square));
    }

    void parameterValueChanged (int, float) override { triggerAsyncUpdate(); }
    void parameterGestureChanged (int, bool) override {}
    void handleAsyncUpdate() override { repaint(); }

    juce::StringArray options; juce::String title; Kind kind; juce::Colour led;
    juce::AudioProcessorParameter* param = nullptr;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MemButtonBank)
};

//==============================================================================
// MemSquareToggle - one big square Memorymoog button bound to a 0/1 param (SYNC / UNISON). Click
// toggles; the button lights (red LED + brighter plate) when on; the function name is printed on
// the face.
class MemSquareToggle  : public juce::Button,
                         private juce::AudioProcessorParameter::Listener,
                         private juce::AsyncUpdater
{
public:
    MemSquareToggle (juce::String titleText, juce::Colour ledColour)
        : juce::Button ("t"), title (std::move (titleText)), led (ledColour)
    { onClick = [this] { toggle(); }; }
    ~MemSquareToggle() override { if (param) param->removeListener (this); cancelPendingUpdate(); }
    void attach (juce::AudioProcessorParameter& p) { param = &p; param->addListener (this); triggerAsyncUpdate(); }
    bool on() const { return param != nullptr && param->getValue() >= 0.5f; }
    void toggle() { if (param) { param->beginChangeGesture(); param->setValueNotifyingHost (on() ? 0.0f : 1.0f); param->endChangeGesture(); } }

    void paintButton (juce::Graphics& g, bool over, bool down) override
    {
        auto box = getLocalBounds().toFloat().reduced (2.0f);
        const bool lit = on();
        if (lit) { g.setColour (led.withAlpha (0.40f)); g.fillRoundedRectangle (box.expanded (2.0f), 4.0f); }
        g.setColour (juce::Colours::black.withAlpha (0.5f)); g.fillRoundedRectangle (box.translated (0.0f, 1.4f), 3.0f);
        const juce::Colour bc = lit ? mem::kBtn.brighter (0.18f) : down ? mem::kBtn.darker (0.10f) : over ? mem::kBtn.brighter (0.06f) : mem::kBtn;
        juce::ColourGradient cg (bc.brighter (0.24f), box.getCentreX(), box.getY(), bc.darker (0.22f), box.getCentreX(), box.getBottom(), false);
        g.setGradientFill (cg); g.fillRoundedRectangle (box, 3.0f);
        g.setColour (juce::Colours::white.withAlpha (lit ? 0.20f : 0.12f));
        g.fillRoundedRectangle (box.withHeight (box.getHeight() * 0.40f).reduced (2.0f, 0.0f), 2.5f);
        g.setColour (juce::Colours::black.withAlpha (0.7f)); g.drawRoundedRectangle (box, 3.0f, 1.1f);

        const float lr = 3.0f, lx = box.getCentreX(), ly = box.getY() + 8.0f;
        if (lit) { g.setColour (mem::kRedHi.withAlpha (0.6f)); g.fillEllipse (lx - lr - 3.0f, ly - lr - 3.0f, (lr + 3.0f) * 2.0f, (lr + 3.0f) * 2.0f); }
        g.setColour (lit ? mem::kRedHi : mem::kRed.withAlpha (0.25f)); g.fillEllipse (lx - lr, ly - lr, lr * 2.0f, lr * 2.0f);
        g.setColour (juce::Colours::black.withAlpha (0.6f)); g.drawEllipse (lx - lr, ly - lr, lr * 2.0f, lr * 2.0f, 0.8f);

        g.setColour (lit ? mem::kCream : mem::kDim);
        g.setFont (toi::uiFont (juce::jmin (11.0f, box.getWidth() * 0.30f), true).withExtraKerningFactor (0.08f));
        g.drawText (title, box.withTrimmedTop (box.getHeight() * 0.42f), juce::Justification::centred);
    }
private:
    void parameterValueChanged (int, float) override { triggerAsyncUpdate(); }
    void parameterGestureChanged (int, bool) override {}
    void handleAsyncUpdate() override { repaint(); }
    juce::String title; juce::Colour led;
    juce::AudioProcessorParameter* param = nullptr;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MemSquareToggle)
};

//==============================================================================
class MemFuncButton  : public juce::Button
{
public:
    MemFuncButton (const juce::String& text, juce::Colour fill) : juce::Button (text), col (fill) { setButtonText (text); }
    void flash() { flashing = true; repaint(); juce::Timer::callAfterDelay (160, [s = juce::Component::SafePointer<MemFuncButton> (this)] { if (s) { s->flashing = false; s->repaint(); } }); }
    void paintButton (juce::Graphics& g, bool over, bool down) override
    {
        auto b = getLocalBounds().toFloat().reduced (1.0f);
        auto fill = flashing ? col.brighter (0.3f) : down ? col.darker (0.18f) : over ? col.brighter (0.08f) : col;
        g.setColour (fill); g.fillRoundedRectangle (b, 2.5f);
        g.setColour (juce::Colours::black.withAlpha (0.5f)); g.drawRoundedRectangle (b, 2.5f, 1.0f);
        g.setColour (juce::Colour (0xff2a1810)); g.setFont (toi::uiFont (juce::jmin (10.0f, b.getHeight() * 0.5f), true));
        g.drawText (getButtonText(), getLocalBounds(), juce::Justification::centred);
    }
private:
    juce::Colour col; bool flashing = false;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MemFuncButton)
};

//==============================================================================
inline toi::Config jwmemConfig()
{
    toi::Config c;
    c.model = "JW-MEM";
    auto& p = c.pal;
    p.bg = mem::kWood; p.bg2 = mem::kWoodLo; p.frame = mem::kFrame; p.ink = mem::kFrame;
    p.accent = mem::kAmber; p.accent2 = mem::kRed; p.button = juce::Colour (0xff2a2a2e);
    p.thumb = mem::kCream; p.text = mem::kCream;
    p.noteStrip = juce::Colour (0xff232326);
    p.lcdBg = juce::Colour (0xff0d0f08); p.lcdInk = juce::Colour (0xffe0b24a);   // amber scope
    p.keyWhite = juce::Colour (0xffe9e2cf); p.keyWhitePr = juce::Colour (0xfff0cf9a);
    p.keyBlack = juce::Colour (0xff14110d); p.keyBlackPr = mem::kAmber;

    // order MUST match the DSP Params struct / ParamsProcessor (factory presets zip by index)
    c.params = {
        { "o1Wave","WAVE" }, { "o1Oct","OCT" }, { "o1Lvl","LEVEL" },
        { "o2Wave","WAVE" }, { "o2Oct","OCT" }, { "o2Tune","TUNE" }, { "o2Lvl","LEVEL" }, { "sync","SYNC" },
        { "o3Wave","WAVE" }, { "o3Oct","OCT" }, { "o3Tune","TUNE" }, { "o3Lvl","LEVEL" },
        { "pw","PW" }, { "pwm","PWM" }, { "xmod","X-MOD" }, { "noiseLvl","NOISE" }, { "drift","DRIFT" }, { "drive","DRIVE" },
        { "unison","UNISON" }, { "uniDetune","DETUNE" }, { "glide","GLIDE" },
        { "cutoff","CUTOFF" }, { "reso","RESO" }, { "fEnv","ENV" }, { "fKeyTrack","KBD" },
        { "a1","A" }, { "d1","D" }, { "s1","S" }, { "r1","R" },
        { "a2","A" }, { "d2","D" }, { "s2","S" }, { "r2","R" },
        { "lfoRate","RATE" }, { "lfoShape","SHAPE" }, { "lfoPitch","PITCH" }, { "lfoFilter","FILTER" },
        { "volume","VOL" }, { "tune","TUNE" },
    };

    std::vector<float> base = {
        0.0f,0.50f,0.80f, 0.0f,0.50f,0.50f,0.70f,0.0f, 0.0f,0.50f,0.50f,0.50f,
        0.50f,0.0f,0.0f,0.0f,0.25f,0.30f, 0.0f,0.40f,0.0f,
        0.55f,0.18f,0.45f,0.30f, 0.02f,0.50f,0.40f,0.30f, 0.02f,0.50f,0.80f,0.35f,
        0.30f,0.0f,0.0f,0.0f, 0.80f,0.50f };
    enum { O1W,O1O,O1L, O2W,O2O,O2T,O2L,SYNC, O3W,O3O,O3T,O3L,
           PW,PWM,XMOD,NOISE,DRIFT,DRIVE, UNI,UDET,GLIDE,
           CUT,RES,FENV,KBD, A1,D1,S1,R1, A2,D2,S2,R2,
           LR,LS,LP,LF, VOL,TUNE };
    auto P = [&] (const char* nm, std::initializer_list<std::pair<int,float>> ov)
    { auto v = base; for (auto& o : ov) v[(size_t) o.first] = o.second; return toi::FactoryPreset { nm, v }; };

    c.factory = {
        P("INIT",        {}),
        P("MONSTER UNI", {{UNI,1.0f},{UDET,0.6f},{O3L,0.7f},{CUT,0.6f},{DRIFT,0.4f},{DRIVE,0.5f},{S2,0.9f}}),
        P("FAT BRASS",   {{O2T,0.515f},{O3O,0.625f},{CUT,0.5f},{FENV,0.65f},{A1,0.06f},{D1,0.5f},{S1,0.5f},{DRIVE,0.4f}}),
        P("HUGE BASS",   {{O3O,0.375f},{O3L,0.8f},{O2T,0.49f},{CUT,0.4f},{RES,0.3f},{FENV,0.5f},{D1,0.35f},{S2,0.6f},{R2,0.2f}}),
        P("DETUNE STAB", {{O2T,0.53f},{O3T,0.47f},{O3L,0.7f},{CUT,0.6f},{DRIFT,0.5f},{D2,0.3f},{S2,0.4f}}),
        P("SYNC LEAD",   {{SYNC,1.0f},{O2T,0.62f},{O2L,0.8f},{CUT,0.55f},{FENV,0.7f},{A1,0.04f},{D1,0.4f}}),
        P("SUB FIFTHS",  {{O2T,0.5417f},{O3O,0.375f},{O3L,0.7f},{CUT,0.5f},{S2,0.8f}}),
        P("WARM PAD",    {{O2T,0.508f},{O3T,0.492f},{O3L,0.6f},{CUT,0.45f},{DRIFT,0.4f},{A1,0.4f},{A2,0.45f},{D1,0.6f},{S1,0.6f},{R1,0.6f},{R2,0.6f}}),
        P("VOLCANIC",    {{DRIFT,1.0f},{DRIVE,0.7f},{O3L,0.7f},{CUT,0.5f},{RES,0.45f},{XMOD,0.3f},{S2,0.8f}}),
        P("X-MOD GROWL", {{XMOD,0.5f},{O3O,0.625f},{O3T,0.56f},{CUT,0.55f},{RES,0.4f},{DRIVE,0.5f}}),
        P("RESO SWEEP",  {{RES,0.8f},{CUT,0.3f},{FENV,0.85f},{A1,0.02f},{D1,0.55f},{S1,0.2f},{LF,0.0f}}),
        P("PWM STRINGS", {{O1W,1.0f},{O2W,1.0f},{PWM,0.6f},{LR,0.12f},{O2T,0.515f},{CUT,0.55f},{A1,0.4f},{A2,0.4f},{R2,0.6f}}),
        P("LFO WOBBLE",  {{LR,0.25f},{LF,0.6f},{CUT,0.45f},{RES,0.5f},{S2,0.9f}}),
        P("HARD KEYS",   {{CUT,0.6f},{FENV,0.6f},{A1,0.0f},{D1,0.3f},{S1,0.0f},{A2,0.0f},{D2,0.35f},{S2,0.0f},{R2,0.2f}}),
        P("BIG UNISON 5",{{UNI,1.0f},{UDET,0.45f},{O2T,0.5417f},{O3L,0.6f},{CUT,0.55f},{DRIVE,0.45f},{S2,0.85f}}),
        P("DARK DRONE",  {{O3O,0.375f},{O3L,0.7f},{CUT,0.32f},{RES,0.4f},{DRIFT,0.5f},{A1,0.5f},{A2,0.55f},{S1,0.8f},{S2,0.9f},{R1,0.7f},{R2,0.8f}}),
    };
    return c;
}

//==============================================================================
class JWMEMEditor  : public toi::PanelEditor
{
public:
    JWMEMEditor (juce::AudioProcessor& proc, juce::MidiKeyboardState& kb)
        : toi::PanelEditor (proc, kb, jwmemConfig())
    {
        cheekInset = 18.0f;
        grain_ = makeGrain (130, 130);

        // ---- continuous controls: vintage fluted knob + printed numeral ring ----
        const char* knobIds[] = {
            "o1Lvl","o2Lvl","o3Lvl","o2Tune","o3Tune","noiseLvl","pw",
            "drift","xmod","pwm","lfoRate","lfoShape","lfoPitch","lfoFilter",
            "cutoff","reso","fEnv","fKeyTrack","drive",
            "a1","d1","s1","r1", "a2","d2","s2","r2",
            "tune","volume","glide","uniDetune" };
        const char* knobLbl[] = {
            "OSC 1","OSC 2","OSC 3","TUNE 2","TUNE 3","NOISE","P.W.",
            "DRIFT","X-MOD","PWM","RATE","SHAPE","PITCH","FILTER",
            "CUTOFF","EMPH","CONTOUR","KBD","DRIVE",
            "A","D","S","R", "A","D","S","R",
            "TUNE","VOLUME","GLIDE","DETUNE" };
        for (int i = 0; i < (int) (sizeof (knobIds) / sizeof (knobIds[0])); ++i)
            addKnob (knobIds[i], knobLbl[i]);

        // ---- square button banks: octave (footage) + wave (glyph) per VCO ----
        for (int i = 0; i < 3; ++i)
        {
            octBank_[i] = std::make_unique<MemButtonBank> (juce::StringArray { "32","16","8","4","2" }, "OCTAVE", MemButtonBank::TextLabels, mem::kRed);
            waveBank_[i] = std::make_unique<MemButtonBank> (juce::StringArray { "S","T","P" }, "WAVE", MemButtonBank::WaveGlyphs, mem::kRed);
            if (auto* po = findParam (juce::String ("o") + juce::String (i + 1) + "Oct"))  octBank_[i]->attach (*po);
            if (auto* pw = findParam (juce::String ("o") + juce::String (i + 1) + "Wave")) waveBank_[i]->attach (*pw);
            addAndMakeVisible (*octBank_[i]); addAndMakeVisible (*waveBank_[i]);
        }

        // ---- SYNC / UNISON square buttons (red LED) ----
        sync_ = std::make_unique<MemSquareToggle> ("SYNC",   mem::kRed);
        uni_  = std::make_unique<MemSquareToggle> ("UNISON", mem::kRed);
        if (auto* prm = findParam ("sync"))   sync_->attach (*prm);
        if (auto* prm = findParam ("unison")) uni_->attach (*prm);
        addAndMakeVisible (*sync_); addAndMakeVisible (*uni_);

        // ---- real-audio scope ----
        scope_ = std::make_unique<toi::Lcd> (pal());
        scope_->attachScope (audioTap());
        addAndMakeVisible (*scope_);

        // ---- 16 molded presets + RAND / SAVE ----
        for (int i = 0; i < 16; ++i)
        { auto b = std::make_unique<toi::MoldedButton> (mem::kPanelLo.brighter (0.14f)); b->setLit (mem::kAmber); const int idx = i; b->onClick = [this, idx] { recallSlot (idx); }; addAndMakeVisible (*b); slots.push_back (std::move (b)); }
        rand_ = std::make_unique<MemFuncButton> ("RAND", mem::kAmber);
        save_ = std::make_unique<MemFuncButton> ("SAVE", mem::kRed.brighter (0.2f));
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
        juce::Random r (1976);
        for (int y = 0; y < h; ++y) for (int x = 0; x < w; ++x)
        { const float n = r.nextFloat(); if (n > 0.6f) { const float a = (n - 0.6f) / 0.4f * 0.06f; const bool light = r.nextBool();
            img.setPixelAt (x, y, (light ? juce::Colours::white : juce::Colours::black).withAlpha (a)); } }
        return img;
    }

    void paintPanel (juce::Graphics& g, juce::Rectangle<float> panel) override
    {
        juce::ignoreUnused (panel);
        // near-black brushed panel surface (oak cheeks show outside rPanel)
        juce::ColourGradient pg (mem::kPanel, rPanel.getCentreX(), rPanel.getY(), mem::kPanelLo, rPanel.getCentreX(), rPanel.getBottom(), false);
        g.setGradientFill (pg); g.fillRoundedRectangle (rPanel, 5.0f);
        if (grain_.isValid()) { g.setFillType (juce::FillType (grain_, juce::AffineTransform::translation (rPanel.getX(), rPanel.getY()))); g.fillRoundedRectangle (rPanel, 5.0f); }
        g.setColour (juce::Colours::black); g.drawRoundedRectangle (rPanel, 5.0f, 1.5f);
        g.setColour (juce::Colours::white.withAlpha (0.05f)); g.drawRoundedRectangle (rPanel.reduced (1.6f), 4.0f, 1.0f);

        // big raised-chrome sections with engraved name-plates
        drawSilverFrame (g, rOsc_,  "OSCILLATORS");
        drawSilverFrame (g, rMix_,  "MIXER");
        drawSilverFrame (g, rMod_,  "MODULATION");
        drawSilverFrame (g, rVcf_,  "VOLTAGE  CONTROLLED  FILTER");
        drawSilverFrame (g, rFEnv_, "FILTER  ENVELOPE");
        drawSilverFrame (g, rAEnv_, "AMPLIFIER  ENVELOPE");
        drawSilverFrame (g, rGlob_, "GLOBAL");
        drawSilverFrame (g, rVoice_,"VOICE");
        drawSilverFrame (g, rScopeF_, "SCOPE");
        drawSilverFrame (g, rPresF_,  "PRESETS");

        // VCO 1/2/3 sub-labels inside the OSCILLATORS frame
        g.setColour (mem::kAmber);
        g.setFont (toi::uiFont (8.5f, true).withExtraKerningFactor (0.12f));
        for (int i = 0; i < 3; ++i)
            g.drawText ("VCO " + juce::String (i + 1), vcoLbl_[i], juce::Justification::centred);

        // brand block (LED row + gap + name) - per toi-brand-block-spacing
        auto bh = rBrand_;
        drawViewLeds (g, bh.removeFromTop (26.0f));
        bh.removeFromTop (8.0f);
        g.setColour (mem::kCream); g.setFont (toi::uiFont (16.0f, true));
        g.drawText ("JW-MEM", bh.removeFromTop (17.0f), juce::Justification::centred);
        g.setColour (mem::kDim); g.setFont (toi::uiFont (5.5f, true).withExtraKerningFactor (0.2f));
        g.drawText ("TOI - plugin corp", bh.removeFromTop (8.0f), juce::Justification::centred);
    }

    void layoutPanel (juce::Rectangle<float> panel) override
    {
        rPanel = juce::Rectangle<float> (panel.getX() + cheekInset, panel.getY(), panel.getWidth() - 2.0f * cheekInset, panel.getHeight());
        auto inner = rPanel.reduced (12.0f, 8.0f);

        // three stacked regions: two section bands + a utility strip
        const float band1H = 88.0f, gap = 4.0f, band2H = 78.0f;
        auto band1 = inner.removeFromTop (band1H); inner.removeFromTop (gap);
        auto band2 = inner.removeFromTop (band2H); inner.removeFromTop (gap);
        auto strip = inner;                                        // ~56px

        // band 1: OSCILLATORS | MIXER | MODULATION
        rOsc_ = band1.removeFromLeft (560.0f); band1.removeFromLeft (8.0f);
        rMix_ = band1.removeFromLeft (360.0f); band1.removeFromLeft (8.0f);
        rMod_ = band1;
        // band 2: VCF | FILTER ENV | AMP ENV | GLOBAL | VOICE
        rVcf_  = band2.removeFromLeft (300.0f); band2.removeFromLeft (8.0f);
        rFEnv_ = band2.removeFromLeft (220.0f); band2.removeFromLeft (8.0f);
        rAEnv_ = band2.removeFromLeft (220.0f); band2.removeFromLeft (8.0f);
        rGlob_ = band2.removeFromLeft (180.0f); band2.removeFromLeft (8.0f);
        rVoice_= band2;
        // strip: SCOPE | PRESETS | RAND/SAVE | BRAND
        rBrand_ = strip.removeFromRight (160.0f); strip.removeFromRight (10.0f);
        auto rs = strip.removeFromRight (74.0f);  strip.removeFromRight (10.0f);
        rScopeF_ = strip.removeFromLeft (300.0f); strip.removeFromLeft (10.0f);
        rPresF_  = strip;

        // ---- place oscillator banks (octave row + wave row + VCO label per column) ----
        {
            auto oi = innerOf (rOsc_);
            const float colW = oi.getWidth() / 3.0f;
            for (int i = 0; i < 3; ++i)
            {
                auto col = juce::Rectangle<float> (oi.getX() + (float) i * colW, oi.getY(), colW, oi.getHeight()).reduced (6.0f, 0.0f);
                vcoLbl_[i] = juce::Rectangle<float> (col.getX(), col.getY() + 1.0f, col.getWidth(), 8.0f);
                placeInArtboard (*octBank_[i],  juce::Rectangle<float> (col.getX(), col.getY() + 10.0f, col.getWidth(), 27.0f));
                placeInArtboard (*waveBank_[i], juce::Rectangle<float> (col.getX() + col.getWidth() * 0.20f, col.getY() + 39.0f, col.getWidth() * 0.60f, 27.0f));
            }
        }
        // ---- place knob rows ----
        rowKnobs (innerOf (rMix_),  { "o1Lvl","o2Lvl","o3Lvl","o2Tune","o3Tune","noiseLvl","pw" });
        rowKnobs (innerOf (rMod_),  { "drift","xmod","pwm","lfoRate","lfoShape","lfoPitch","lfoFilter" });
        rowKnobs (innerOf (rVcf_),  { "cutoff","reso","fEnv","fKeyTrack","drive" });
        rowKnobs (innerOf (rFEnv_), { "a1","d1","s1","r1" });
        rowKnobs (innerOf (rAEnv_), { "a2","d2","s2","r2" });
        rowKnobs (innerOf (rGlob_), { "tune","volume","glide" });

        // ---- VOICE: SYNC | UNISON squares + DETUNE knob ----
        {
            auto vi = innerOf (rVoice_);
            const float sqW = 74.0f;
            placeInArtboard (*sync_, juce::Rectangle<float> (vi.getX(),               vi.getY(), sqW, vi.getHeight()).reduced (3.0f, 2.0f));
            placeInArtboard (*uni_,  juce::Rectangle<float> (vi.getX() + sqW + 6.0f,   vi.getY(), sqW, vi.getHeight()).reduced (3.0f, 2.0f));
            const float kx = vi.getX() + 2.0f * sqW + 14.0f;
            if (auto* k = knobFor ("uniDetune")) placeInArtboard (*k, juce::Rectangle<float> (kx, vi.getY(), vi.getRight() - kx, vi.getHeight()).reduced (2.0f, 0.0f));
        }

        // ---- scope + presets + rand/save in the utility strip ----
        placeInArtboard (*scope_, innerOf (rScopeF_));
        {
            auto pr = innerOf (rPresF_);
            const int pc = 8, prows = 2; const float pgap = 3.0f;
            const float pw = (pr.getWidth()  - pgap * (pc - 1)) / (float) pc;
            const float ph = (pr.getHeight() - pgap * (prows - 1)) / (float) prows;
            for (int i = 0; i < 16; ++i)
            { const int rr = i / pc, cc = i % pc; placeInArtboard (*slots[(size_t) i], juce::Rectangle<float> (pr.getX() + (float) cc * (pw + pgap), pr.getY() + (float) rr * (ph + pgap), pw, ph)); }
        }
        {
            auto rsi = rs.reduced (1.0f, 7.0f);
            const float bh = (rsi.getHeight() - 4.0f) * 0.5f;
            placeInArtboard (*rand_, rsi.removeFromTop (bh)); rsi.removeFromTop (4.0f); placeInArtboard (*save_, rsi.removeFromTop (bh));
        }
    }

private:
    void addKnob (const juce::String& id, const juce::String& label)
    {
        auto k = std::make_unique<toi::StyledKnob> (label, pal(), toi::StyledKnob::Fluted);
        k->setNumerals (true);                                     // printed 0..10 ring + line (Memorymoog look) - KEEP
        if (auto* prm = findParam (id)) k->attach (*prm);
        addAndMakeVisible (*k);
        knobMap_[id] = k.get();
        knobs.push_back (std::move (k));
    }
    toi::StyledKnob* knobFor (const juce::String& id) const { auto it = knobMap_.find (id); return it == knobMap_.end() ? nullptr : it->second; }

    void rowKnobs (juce::Rectangle<float> area, std::initializer_list<const char*> ids)
    {
        const int n = (int) ids.size(); if (n == 0) return;
        const float w = area.getWidth() / (float) n;
        int i = 0;
        for (auto* id : ids)
        {
            if (auto* k = knobFor (id))
                placeInArtboard (*k, juce::Rectangle<float> (area.getX() + (float) i * w, area.getY(), w, area.getHeight()).reduced (1.5f, 0.0f));
            ++i;
        }
    }

    // raised-chrome bezel + engraved name-plate rail; returns the recessed dark interior.
    static juce::Rectangle<float> innerOf (juce::Rectangle<float> r)
    { auto inner = r.reduced (6.0f, 5.0f); inner.removeFromTop (11.0f); return inner; }

    void drawSilverFrame (juce::Graphics& g, juce::Rectangle<float> r, const juce::String& name)
    {
        juce::ColourGradient bez (mem::kSilverHi, r.getX(), r.getY(), mem::kSilverLo, r.getX(), r.getBottom(), false);
        bez.addColour (0.45, mem::kSilver);
        g.setGradientFill (bez); g.fillRoundedRectangle (r, 6.0f);
        g.setColour (juce::Colours::white.withAlpha (0.5f));  g.drawRoundedRectangle (r.reduced (1.0f), 5.2f, 1.0f);
        g.setColour (juce::Colours::black.withAlpha (0.55f)); g.drawRoundedRectangle (r, 6.0f, 1.3f);
        // engraved section name on the silver top rail
        {
            auto rail = r.withHeight (14.0f).reduced (10.0f, 1.0f);
            g.setFont (toi::uiFont (8.5f, true).withExtraKerningFactor (0.16f));
            g.setColour (juce::Colours::white.withAlpha (0.5f)); g.drawText (name, rail.translated (0.0f, 1.0f), juce::Justification::centred);
            g.setColour (mem::kEngrave);                          g.drawText (name, rail, juce::Justification::centred);
        }
        // recessed dark interior
        auto inner = innerOf (r);
        juce::ColourGradient ig (mem::kPanelLo, inner.getCentreX(), inner.getY(), mem::kPanel.darker (0.2f), inner.getCentreX(), inner.getBottom(), false);
        g.setGradientFill (ig); g.fillRoundedRectangle (inner, 3.0f);
        if (grain_.isValid()) { g.setFillType (juce::FillType (grain_, juce::AffineTransform::translation (inner.getX(), inner.getY()))); g.fillRoundedRectangle (inner, 3.0f); }
        g.setColour (juce::Colours::black.withAlpha (0.7f));  g.drawRoundedRectangle (inner, 3.0f, 1.2f);
        g.setColour (juce::Colours::white.withAlpha (0.04f)); g.drawRoundedRectangle (inner.reduced (1.0f), 2.5f, 0.8f);
    }

    std::vector<std::unique_ptr<toi::StyledKnob>> knobs;
    std::map<juce::String, toi::StyledKnob*> knobMap_;
    std::unique_ptr<MemButtonBank> octBank_[3], waveBank_[3];
    std::unique_ptr<MemSquareToggle> sync_, uni_;
    std::unique_ptr<toi::Lcd> scope_;
    std::vector<std::unique_ptr<toi::MoldedButton>> slots;
    std::unique_ptr<MemFuncButton> rand_, save_;
    juce::Image grain_;
    juce::Rectangle<float> rPanel, rOsc_, rMix_, rMod_, rVcf_, rFEnv_, rAEnv_, rGlob_, rVoice_, rScopeF_, rPresF_, rBrand_;
    juce::Rectangle<float> vcoLbl_[3];
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JWMEMEditor)
};

//==============================================================================
class JWMEMPlugin  : public cmaj::plugin::GeneratedPlugin<::JWMEM>,
                     public toi::AudioTapSource,
                     public toi::PresetStore
{
public:
    using Base = cmaj::plugin::GeneratedPlugin<::JWMEM>;
    JWMEMPlugin (std::shared_ptr<cmaj::Patch> p) : Base (std::move (p)) {}
    juce::AudioProcessorEditor* createEditor() override { return new JWMEMEditor (*this, keyboardState); }
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
