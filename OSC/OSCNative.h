// JW-OSC native faceplate (snarling additive-hybrid mono) on the toi_faceplate.h kit.
// Traces the Oxford OSCar: a GOLD/champagne panel with BLACK fluted knobs in DARK recessed boxes.
// Both signatures real: the WAVEFORMS/HARMONICS editor (select a harmonic + set its LEVEL -> builds
// the additive wave, shown live) and the FILTER box with its SEPARATION knob. NO brand names.
#pragma once

#include "toi_faceplate.h"

struct JWOSC;

namespace osc
{
    static const juce::Colour kGold   { 0xffb39866 };   // champagne-gold panel
    static const juce::Colour kGoldLo { 0xff8c744a };
    static const juce::Colour kFrame  { 0xff0a0905 };
    static const juce::Colour kInk    { 0xff241f12 };   // dark text on the gold panel
    static const juce::Colour kCream  { 0xffe9dec2 };   // light text on the dark boxes
    static const juce::Colour kDim    { 0xff8a8169 };
    static const juce::Colour kArc    { 0xffd8b45a };   // gold knob value-arc / accent
    static const juce::Colour kRed    { 0xffd23a2c };   // OCTAVE LEDs
    static const juce::Colour kBoxFill{ 0xff201e17 };   // dark recessed section box
    static const juce::Colour kBoxHi  { 0xffd9c89c };   // box border (cream)
}

//==============================================================================
// OscWaveView - LIVE display of the additive wave built from the 16 harmonic params. Sums them and
// draws one cycle; listens to the params and redraws as you edit. (Not static art.)
class OscWaveView  : public juce::Component,
                     private juce::AudioProcessorParameter::Listener,
                     private juce::AsyncUpdater
{
public:
    OscWaveView() = default;
    ~OscWaveView() override { for (auto* p : params_) if (p) p->removeListener (this); cancelPendingUpdate(); }
    void setParams (std::vector<juce::AudioProcessorParameter*> ps)
    { for (auto* p : params_) if (p) p->removeListener (this); params_ = std::move (ps); for (auto* p : params_) if (p) p->addListener (this); triggerAsyncUpdate(); }
    void paint (juce::Graphics& g) override
    {
        auto r = getLocalBounds().toFloat();
        g.setColour (juce::Colour (0xff12100a)); g.fillRoundedRectangle (r, 3.0f);
        g.setColour (osc::kArc.withAlpha (0.6f)); g.drawRoundedRectangle (r, 3.0f, 1.0f);
        auto a = r.reduced (5.0f, 4.0f);
        const float midY = a.getCentreY(), amp = a.getHeight() * 0.46f;
        g.setColour (osc::kArc.withAlpha (0.18f)); g.drawLine (a.getX(), midY, a.getRight(), midY, 0.8f);
        const int N = 180;
        juce::Path p; bool started = false;
        for (int x = 0; x < N; ++x)
        {
            const float ph = (float) x / (float) (N - 1);
            float s = 0.0f, sum = 0.0001f;
            for (int h = 0; h < (int) params_.size(); ++h)
            { const float lvl = params_[(size_t) h] ? params_[(size_t) h]->getValue() : 0.0f; s += lvl * std::sin (juce::MathConstants<float>::twoPi * ph * (float) (h + 1)); sum += lvl; }
            const float y = midY - (s / juce::jmax (0.4f, sum)) * amp;
            const float px = a.getX() + ph * a.getWidth();
            if (! started) { p.startNewSubPath (px, y); started = true; } else p.lineTo (px, y);
        }
        g.setColour (osc::kArc); g.strokePath (p, juce::PathStrokeType (1.5f));
    }
private:
    void parameterValueChanged (int, float) override { triggerAsyncUpdate(); }
    void parameterGestureChanged (int, bool) override {}
    void handleAsyncUpdate() override { repaint(); }
    std::vector<juce::AudioProcessorParameter*> params_;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscWaveView)
};

//==============================================================================
// HarmSelect - the WAVEFORMS/HARMONICS picker (the hardware workflow): 16 cells, click one to select
// that harmonic; the LEVEL knob then edits its amplitude. The selected cell lights, and each cell
// shows a tiny bar of its current level so you can see the spectrum you're building.
class HarmSelect  : public juce::Component,
                    private juce::AudioProcessorParameter::Listener,
                    private juce::AsyncUpdater
{
public:
    HarmSelect() = default;
    ~HarmSelect() override { for (auto* p : params_) if (p) p->removeListener (this); cancelPendingUpdate(); }
    std::function<void (int)> onSelect;
    void setParams (std::vector<juce::AudioProcessorParameter*> ps)
    { for (auto* p : params_) if (p) p->removeListener (this); params_ = std::move (ps); for (auto* p : params_) if (p) p->addListener (this); triggerAsyncUpdate(); }
    void setActive (int i) { active_ = i; repaint(); }
    void mouseDown (const juce::MouseEvent& e) override
    {
        const int n = (int) params_.size(); if (n <= 0) return;
        int i = juce::jlimit (0, n - 1, (int) (e.position.x / (getWidth() / (float) n)));
        if (onSelect) onSelect (i);
    }
    void paint (juce::Graphics& g) override
    {
        const int n = (int) params_.size(); if (n <= 0) return;
        const float cw = (float) getWidth() / (float) n;
        for (int i = 0; i < n; ++i)
        {
            auto cell = juce::Rectangle<float> ((float) i * cw, 0.0f, cw, (float) getHeight()).reduced (1.4f, 1.0f);
            const bool on = (i == active_);
            g.setColour (juce::Colour (0xff15130d)); g.fillRoundedRectangle (cell, 2.0f);
            // level bar
            const float lvl = params_[(size_t) i] ? params_[(size_t) i]->getValue() : 0.0f;
            auto bar = cell.reduced (2.0f, 2.0f); bar = bar.withTop (bar.getBottom() - bar.getHeight() * juce::jlimit (0.03f, 1.0f, lvl));
            g.setColour (osc::kArc.withAlpha (on ? 0.95f : 0.6f)); g.fillRoundedRectangle (bar, 1.0f);
            g.setColour (on ? osc::kCream : juce::Colours::black.withAlpha (0.5f)); g.drawRoundedRectangle (cell, 2.0f, on ? 1.3f : 0.7f);
            g.setColour (on ? osc::kCream : osc::kDim); g.setFont (toi::uiFont (6.0f, true));
            g.drawText (juce::String (i + 1), cell.withHeight (8.0f), juce::Justification::centred);
        }
    }
private:
    void parameterValueChanged (int, float) override { triggerAsyncUpdate(); }
    void parameterGestureChanged (int, bool) override {}
    void handleAsyncUpdate() override { repaint(); }
    std::vector<juce::AudioProcessorParameter*> params_; int active_ = 0;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HarmSelect)
};

//==============================================================================
class OscFunc  : public juce::Button
{
public:
    OscFunc (const juce::String& t, juce::Colour fill) : juce::Button (t), col (fill) { setButtonText (t); }
    void flash() { flashing = true; repaint(); juce::Timer::callAfterDelay (150, [s = juce::Component::SafePointer<OscFunc> (this)] { if (s) { s->flashing = false; s->repaint(); } }); }
    void paintButton (juce::Graphics& g, bool over, bool down) override
    {
        auto b = getLocalBounds().toFloat().reduced (1.0f);
        auto fill = flashing ? col.brighter (0.3f) : down ? col.darker (0.18f) : over ? col.brighter (0.08f) : col;
        g.setColour (fill); g.fillRoundedRectangle (b, 2.5f);
        g.setColour (juce::Colours::black.withAlpha (0.5f)); g.drawRoundedRectangle (b, 2.5f, 1.0f);
        g.setColour (juce::Colour (0xff1a140a)); g.setFont (toi::uiFont (juce::jmin (10.0f, b.getHeight() * 0.5f), true));
        g.drawText (getButtonText(), getLocalBounds(), juce::Justification::centred);
    }
private:
    juce::Colour col; bool flashing = false;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscFunc)
};

//==============================================================================
// OscOctave - the OCTAVE footage selector (real, clickable). 5 LEDs = 32'/16'/8'/4'/2' bound to the
// o1Oct param (engine maps it to -2..+2 octaves). Click an LED to set the octave; the active LED lights
// and tracks the real param value. Not decoration - it sets the master oscillator octave.
class OscOctave  : public juce::Component,
                   private juce::AudioProcessorParameter::Listener,
                   private juce::AsyncUpdater
{
public:
    OscOctave() = default;
    ~OscOctave() override { if (param_) param_->removeListener (this); cancelPendingUpdate(); }
    void attach (juce::AudioProcessorParameter* p) { if (param_) param_->removeListener (this); param_ = p; if (param_) param_->addListener (this); triggerAsyncUpdate(); }
    void mouseDown (const juce::MouseEvent& e) override
    { if (! param_) return; const int i = juce::jlimit (0, N - 1, (int) (e.position.x / (getWidth() / (float) N))); param_->setValueNotifyingHost ((float) i / (float) (N - 1)); }
    void paint (juce::Graphics& g) override
    {
        const int active = param_ ? juce::jlimit (0, N - 1, juce::roundToInt (param_->getValue() * (N - 1))) : 2;
        const char* foot[N] = { "32", "16", "8", "4", "2" };
        const float cw = (float) getWidth() / (float) N;
        g.setColour (osc::kCream); g.setFont (toi::uiFont (6.0f, true)); g.drawText ("OCTAVE", juce::Rectangle<float> (0.0f, 0.0f, (float) getWidth(), 8.0f), juce::Justification::centred);
        for (int i = 0; i < N; ++i)
        {
            auto cell = juce::Rectangle<float> ((float) i * cw, 9.0f, cw, (float) getHeight() - 9.0f);
            const bool on = (i == active);
            auto led = cell.withTrimmedBottom (9.0f).withSizeKeepingCentre (8.0f, 8.0f);
            if (on) { g.setColour (osc::kRed.withAlpha (0.45f)); g.fillEllipse (led.expanded (2.0f)); }
            g.setColour (on ? osc::kRed : juce::Colour (0xff3a2a22)); g.fillEllipse (led);
            g.setColour (juce::Colours::black.withAlpha (0.5f)); g.drawEllipse (led, 0.8f);
            g.setColour (on ? osc::kCream : osc::kDim); g.setFont (toi::uiFont (6.0f, on));
            g.drawText (foot[i], cell.removeFromBottom (9.0f), juce::Justification::centred);
        }
    }
private:
    void parameterValueChanged (int, float) override { triggerAsyncUpdate(); }
    void parameterGestureChanged (int, bool) override {}
    void handleAsyncUpdate() override { repaint(); }
    static constexpr int N = 5;
    juce::AudioProcessorParameter* param_ = nullptr;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscOctave)
};

//==============================================================================
inline toi::Config jwoscConfig()
{
    toi::Config c;
    c.model = "JW-OSC";
    auto& p = c.pal;
    p.bg = osc::kGold; p.bg2 = osc::kGoldLo; p.frame = osc::kFrame; p.ink = osc::kFrame;
    p.accent = osc::kArc; p.accent2 = osc::kRed; p.button = juce::Colour (0xff2a2a2e);
    p.thumb = osc::kCream; p.text = osc::kCream;
    p.noteStrip = juce::Colour (0xff8c744a);
    p.lcdBg = juce::Colour (0xff14120a); p.lcdInk = osc::kArc;
    p.keyWhite = juce::Colour (0xffeae0c6); p.keyWhitePr = juce::Colour (0xffd8b45a); p.keyBlack = juce::Colour (0xff241f12); p.keyBlackPr = osc::kArc;

    c.params = {
        { "o1Shape","SHAPE" },{ "o1Oct","OCT" },{ "o2Shape","SHAPE" },{ "o2Oct","OCT" },{ "o2Tune","DETUNE" },{ "sync","SYNC" },{ "pw","PW" },{ "mix","MIX" },
        { "h1","1" },{ "h2","2" },{ "h3","3" },{ "h4","4" },{ "h5","5" },{ "h6","6" },{ "h7","7" },{ "h8","8" },
        { "h9","9" },{ "h10","10" },{ "h11","11" },{ "h12","12" },{ "h13","13" },{ "h14","14" },{ "h15","15" },{ "h16","16" },
        { "cutoff","CUTOFF" },{ "reso","RESO" },{ "fMode","MODE" },{ "sep","SEPARATION" },{ "fEnv","ENV" },{ "fKeyTrack","KBD" },{ "drive","DRIVE" },
        { "a1","A" },{ "d1","D" },{ "s1","S" },{ "r1","R" },{ "a2","A" },{ "d2","D" },{ "s2","S" },{ "r2","R" },
        { "lfoRate","RATE" },{ "lfoShape","SHAPE" },{ "lfoPitch","PITCH" },{ "lfoFilter","FILTER" },{ "glide","GLIDE" },{ "volume","VOL" },{ "tune","TUNE" },
    };

    std::vector<float> base = {
        1.0f,0.50f,0.0f,0.50f,0.50f,0.0f,0.50f,0.40f,
        1.0f,0.50f,0.33f,0.25f,0.20f,0.16f,0.13f,0.11f, 0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,
        0.62f,0.30f,0.0f,0.0f,0.45f,0.30f,0.30f,
        0.02f,0.50f,0.80f,0.25f, 0.02f,0.45f,0.35f,0.30f,
        0.30f,0.0f,0.0f,0.0f,0.0f,0.80f,0.50f };
    enum { O1S,O1O,O2S,O2O,O2T,SYNC,PW,MIX, H1,H2,H3,H4,H5,H6,H7,H8,H9,H10,H11,H12,H13,H14,H15,H16,
           CUT,RES,FMODE,SEP,FENV,FKBD,DRIVE, A1,D1,S1,R1,A2,D2,S2,R2,
           LR,LS,LP,LF,GLIDE,VOL,TUNE };
    auto P = [&] (const char* nm, std::initializer_list<std::pair<int,float>> ov)
    { auto v = base; for (auto& o : ov) v[(size_t) o.first] = o.second; return toi::FactoryPreset { nm, v }; };

    c.factory = {
        P("INIT",        {}),
        P("BITE BASS",   {{O1O,0.375f},{O2O,0.375f},{CUT,0.4f},{RES,0.4f},{DRIVE,0.6f},{H2,0.7f},{H3,0.5f},{H4,0.4f},{A1,0.0f},{D1,0.4f},{S1,0.3f}}),
        P("VOCAL LEAD",  {{SEP,0.55f},{FMODE,0.5f},{RES,0.55f},{CUT,0.55f},{H2,0.8f},{H3,0.6f},{H5,0.4f},{H7,0.3f}}),
        P("HOLLOW",      {{H1,1.0f},{H2,0.0f},{H3,0.7f},{H5,0.5f},{H7,0.35f},{H9,0.25f},{CUT,0.6f}}),
        P("FORMANT SWP", {{SEP,0.7f},{FMODE,0.5f},{RES,0.6f},{FENV,0.7f},{LF,0.5f},{LR,0.2f},{CUT,0.45f}}),
        P("RUBBER BASS", {{O1O,0.375f},{CUT,0.45f},{RES,0.35f},{DRIVE,0.45f},{SEP,0.3f},{H2,0.6f},{H4,0.4f},{D1,0.35f},{S1,0.4f}}),
        P("METALLIC",    {{H1,0.6f},{H4,0.7f},{H7,0.6f},{H11,0.5f},{H13,0.4f},{CUT,0.7f},{RES,0.4f}}),
        P("SYNC SCREAM", {{SYNC,1.0f},{O2T,0.62f},{CUT,0.6f},{RES,0.5f},{DRIVE,0.55f},{FENV,0.7f},{A1,0.02f},{D1,0.4f}}),
        P("SOFT REED",   {{H1,1.0f},{H2,0.55f},{H3,0.7f},{H4,0.3f},{H5,0.45f},{CUT,0.55f},{A1,0.15f},{R1,0.5f}}),
        P("WIDE SAW",    {{O1S,0.0f},{O2S,0.0f},{O2T,0.53f},{CUT,0.65f},{DRIVE,0.4f},{MIX,0.5f}}),
        P("TALK BP",     {{FMODE,0.5f},{SEP,0.6f},{RES,0.65f},{LF,0.4f},{LR,0.18f},{CUT,0.5f},{H2,0.7f},{H3,0.5f}}),
        P("DEEP DRONE",  {{O1O,0.375f},{O2O,0.375f},{O2T,0.49f},{CUT,0.35f},{RES,0.45f},{A1,0.4f},{R1,0.7f},{S1,0.8f},{H2,0.5f},{H3,0.3f}}),
    };
    return c;
}

//==============================================================================
class JWOSCEditor  : public toi::PanelEditor
{
public:
    JWOSCEditor (juce::AudioProcessor& proc, juce::MidiKeyboardState& kb)
        : toi::PanelEditor (proc, kb, jwoscConfig())
    {
        grain_ = makeGrain (130, 130);

        groupsA_ = { { "OSC 1", { "o1Shape","o1Oct" } }, { "OSC 2", { "o2Shape","o2Oct","o2Tune","sync" } },
                     { "MIXER", { "mix","pw","glide" } }, { "LFO", { "lfoRate","lfoShape","lfoPitch","lfoFilter" } } };
        groupsB_ = { { "FILTER", { "cutoff","reso","fMode","sep","fEnv","fKeyTrack","drive" } },
                     { "AMP  ENV", { "a1","d1","s1","r1" } }, { "FILTER  ENV", { "a2","d2","s2","r2" } }, { "MASTER", { "volume","tune" } } };
        for (auto& grp : groupsA_) for (auto& id : grp.ids) addCell (id);
        for (auto& grp : groupsB_) for (auto& id : grp.ids) addCell (id);

        // WAVEFORMS / HARMONICS: a select picker + one LEVEL knob (the OSCar workflow) + live wave view
        const char* hids[] = { "h1","h2","h3","h4","h5","h6","h7","h8","h9","h10","h11","h12","h13","h14","h15","h16" };
        std::vector<juce::AudioProcessorParameter*> hp; for (int i = 0; i < 16; ++i) hp.push_back (findParam (hids[i]));
        harmSel_ = std::make_unique<HarmSelect>(); harmSel_->setParams (hp);
        harmSel_->onSelect = [this] (int i) { selectHarm (i); };
        addAndMakeVisible (*harmSel_);
        level_ = std::make_unique<toi::StyledKnob> ("", pal(), toi::StyledKnob::FlutedDark); level_->setShowLabel (false); addAndMakeVisible (*level_);
        wave_ = std::make_unique<OscWaveView>(); wave_->setParams (hp); addAndMakeVisible (*wave_);

        scope_ = std::make_unique<toi::Lcd> (pal());
        scope_->attachScope (audioTap());
        addAndMakeVisible (*scope_);

        for (int i = 0; i < 16; ++i)
        { auto b = std::make_unique<toi::MoldedButton> (juce::Colour (0xff2a261a)); b->setLit (osc::kArc); const int idx = i; b->onClick = [this, idx] { recallSlot (idx); }; addAndMakeVisible (*b); slots_.push_back (std::move (b)); }
        rand_ = std::make_unique<OscFunc> ("RAND", osc::kArc); save_ = std::make_unique<OscFunc> ("SAVE", osc::kRed.brighter (0.15f));
        rand_->onClick = [this] { doRandom(); rand_->flash(); };
        save_->onClick = [this] { saveSlot (activeSlot()); save_->flash(); };
        addAndMakeVisible (*rand_); addAndMakeVisible (*save_);

        finishSetup();
        selectHarm (0);
    }

protected:
    void setPresetActiveVisual (int idx) override { for (int i = 0; i < (int) slots_.size(); ++i) slots_[(size_t) i]->setActive (i == idx); }

    static juce::Image makeGrain (int w, int h)
    {
        juce::Image img (juce::Image::ARGB, w, h, true);
        juce::Random r (1983);
        for (int y = 0; y < h; ++y) for (int x = 0; x < w; ++x)
        { const float n = r.nextFloat(); if (n > 0.62f) { const float a = (n - 0.62f) / 0.38f * 0.05f; const bool light = r.nextBool();
            img.setPixelAt (x, y, (light ? juce::Colours::white : juce::Colours::black).withAlpha (a)); } }
        return img;
    }

    void paintPanel (juce::Graphics& g, juce::Rectangle<float> panel) override
    {
        rPanel = panel;
        juce::ColourGradient pg (osc::kGold, rPanel.getCentreX(), rPanel.getY(), osc::kGoldLo, rPanel.getCentreX(), rPanel.getBottom(), false);
        g.setGradientFill (pg); g.fillRoundedRectangle (rPanel, 5.0f);
        if (grain_.isValid()) { g.setFillType (juce::FillType (grain_, juce::AffineTransform::translation (rPanel.getX(), rPanel.getY()))); g.fillRoundedRectangle (rPanel, 5.0f); }
        g.setColour (juce::Colours::black); g.drawRoundedRectangle (rPanel, 5.0f, 1.5f);

        for (auto& grp : groupsA_) drawGroupBox (g, grp);
        for (auto& grp : groupsB_) drawGroupBox (g, grp);

        // WAVEFORMS / HARMONICS box
        drawBox (g, rHarmBox_, "WAVEFORMS  /  HARMONICS");
        g.setColour (osc::kCream); g.setFont (toi::uiFont (6.0f, true));
        g.drawText ("HARMONIC " + juce::String (activeHarm_ + 1), juce::Rectangle<float> (rLevel_.getX() - 12.0f, rLevel_.getBottom() - 1.0f, rLevel_.getWidth() + 24.0f, 8.0f), juce::Justification::centred);
        g.drawText ("LEVEL", juce::Rectangle<float> (rLevel_.getX() - 12.0f, rLevel_.getY() - 8.0f, rLevel_.getWidth() + 24.0f, 8.0f), juce::Justification::centred);

        // bottom-strip labels
        g.setColour (osc::kInk); g.setFont (toi::uiFont (6.5f, true).withExtraKerningFactor (0.12f));
        g.drawText ("SCOPE",  juce::Rectangle<float> (rScope_.getX(), rScope_.getY() - 9.0f, 120.0f, 9.0f), juce::Justification::centredLeft);
        g.drawText ("STORE / RECALL", juce::Rectangle<float> (rPreset_.getX(), rPreset_.getY() - 9.0f, 160.0f, 9.0f), juce::Justification::centredLeft);

        // brand (dark text on gold)
        auto bh = rBrand_;
        drawViewLeds (g, bh.removeFromTop (22.0f));
        bh.removeFromTop (2.0f);
        g.setColour (osc::kInk); g.setFont (toi::uiFont (15.0f, true));
        g.drawText ("JW-OSC", bh, juce::Justification::centred);
    }

    void layoutPanel (juce::Rectangle<float> panel) override
    {
        rPanel = panel;
        auto inner = rPanel.reduced (12.0f, 8.0f);

        rowA_ = inner.removeFromTop (66.0f);
        inner.removeFromTop (3.0f);
        rowB_ = inner.removeFromTop (66.0f);
        inner.removeFromTop (4.0f);

        // WAVEFORMS / HARMONICS box: select picker (left) + LEVEL knob + wave display (right)
        rHarmBox_ = inner.removeFromTop (46.0f);
        {
            auto in = rHarmBox_.reduced (6.0f, 4.0f).withTrimmedTop (10.0f);
            auto wv = in.removeFromRight (210.0f); in.removeFromRight (8.0f);
            placeInArtboard (*wave_, wv);
            auto lk = in.removeFromRight (50.0f); in.removeFromRight (10.0f);
            rLevel_ = lk.withSizeKeepingCentre (juce::jmin (32.0f, lk.getWidth()), juce::jmin (24.0f, lk.getHeight()));
            placeInArtboard (*level_, rLevel_);
            placeInArtboard (*harmSel_, in);
        }
        inner.removeFromTop (5.0f);

        auto strip = inner;
        rBrand_ = strip.removeFromRight (150.0f); strip.removeFromRight (8.0f);
        auto rs = strip.removeFromRight (76.0f); strip.removeFromRight (10.0f);
        rScope_ = strip.removeFromLeft (250.0f); strip.removeFromLeft (12.0f);
        rPreset_ = strip;
        placeInArtboard (*scope_, rScope_);
        { auto pr = rPreset_; const int pc = 8; const float pgap = 3.0f;
          const float pw = (pr.getWidth() - pgap * (pc - 1)) / (float) pc;
          const float ph = (pr.getHeight() - pgap) * 0.5f;
          for (int i = 0; i < 16; ++i) { const int r = i / pc, cc = i % pc; placeInArtboard (*slots_[(size_t) i], juce::Rectangle<float> (pr.getX() + (float) cc * (pw + pgap), pr.getY() + (float) r * (ph + pgap), pw, ph)); } }
        { auto rsi = rs.reduced (0.0f, 4.0f); const float bh = (rsi.getHeight() - 4.0f) * 0.5f;
          placeInArtboard (*rand_, rsi.removeFromTop (bh)); rsi.removeFromTop (4.0f); placeInArtboard (*save_, rsi.removeFromTop (bh)); }

        layoutGroups (groupsA_, rowA_);
        layoutGroups (groupsB_, rowB_);
    }

private:
    struct Group { juce::String name; std::vector<juce::String> ids; juce::Rectangle<float> rect; };

    void selectHarm (int i)
    {
        activeHarm_ = juce::jlimit (0, 15, i);
        harmSel_->setActive (activeHarm_);
        if (auto* prm = findParam ("h" + juce::String (activeHarm_ + 1))) level_->attach (*prm);
    }

    void addCell (const juce::String& id)
    {
        if (id == "o1Oct")   // the OCTAVE selector replaces this knob (real footage buttons, not a knob)
        {
            octave_ = std::make_unique<OscOctave>();
            if (auto* prm = findParam (id)) octave_->attach (prm);
            addAndMakeVisible (*octave_); cellComp_[id] = octave_.get();
            return;
        }
        addKnob (id);
    }
    void addKnob (const juce::String& id)
    {
        auto k = std::make_unique<toi::StyledKnob> ("", pal(), toi::StyledKnob::FlutedDark); k->setShowLabel (false);
        if (auto* prm = findParam (id)) k->attach (*prm);
        addAndMakeVisible (*k); knobMap_[id] = k.get(); cellComp_[id] = k.get(); knobs_.push_back (std::move (k));
    }
    int totalKnobs (const std::vector<Group>& gs) const { int n = 0; for (auto& g : gs) n += (int) g.ids.size(); return n; }
    juce::Component* cellFor (const juce::String& id) const { auto it = cellComp_.find (id); return it == cellComp_.end() ? nullptr : it->second; }

    void layoutGroups (std::vector<Group>& gs, juce::Rectangle<float> row)
    {
        const int n = totalKnobs (gs);
        const float gap = 8.0f;
        const float usable = row.getWidth() - gap * (float) (gs.size() - 1);
        const float kw = usable / (float) n;
        float x = row.getX();
        for (auto& grp : gs)
        {
            const float gwidth = kw * (float) grp.ids.size();
            grp.rect = juce::Rectangle<float> (x, row.getY(), gwidth, row.getHeight());
            for (int i = 0; i < (int) grp.ids.size(); ++i)
                if (auto* comp = cellFor (grp.ids[(size_t) i]))
                    placeInArtboard (*comp, juce::Rectangle<float> (x + (float) i * kw, row.getY() + 11.0f, kw, row.getHeight() - 21.0f).reduced (2.5f, 0.0f));
            x += gwidth + gap;
        }
    }

    void drawBox (juce::Graphics& g, juce::Rectangle<float> r, const juce::String& name)
    {
        g.setColour (osc::kBoxFill); g.fillRoundedRectangle (r, 4.0f);
        g.setColour (osc::kBoxHi.withAlpha (0.5f)); g.drawRoundedRectangle (r, 4.0f, 1.0f);
        g.setColour (osc::kCream); g.setFont (toi::uiFont (7.5f, true).withExtraKerningFactor (0.1f));
        g.drawText (name, r.withHeight (11.0f).reduced (5.0f, 1.0f), juce::Justification::centredLeft);
    }

    void drawGroupBox (juce::Graphics& g, const Group& grp)
    {
        drawBox (g, grp.rect, grp.name);
        // knob labels (cream, under each knob inside the box)
        g.setColour (osc::kDim); g.setFont (toi::uiFont (6.0f, true));
        const float kw = grp.rect.getWidth() / (float) grp.ids.size();
        for (int i = 0; i < (int) grp.ids.size(); ++i)
        {
            if (grp.ids[(size_t) i] == "o1Oct") continue;   // the OCTAVE widget draws its own footage labels
            juce::String lbl; for (auto& sp : config().params) if (sp.id == grp.ids[(size_t) i]) { lbl = sp.label; break; }
            g.drawText (lbl, juce::Rectangle<float> (grp.rect.getX() + (float) i * kw, grp.rect.getBottom() - 10.0f, kw, 9.0f), juce::Justification::centred);
        }
    }

    std::vector<std::unique_ptr<toi::StyledKnob>> knobs_;
    std::map<juce::String, toi::StyledKnob*> knobMap_;
    std::map<juce::String, juce::Component*> cellComp_;
    std::unique_ptr<OscOctave> octave_;
    std::unique_ptr<HarmSelect> harmSel_;
    std::unique_ptr<toi::StyledKnob> level_;
    std::unique_ptr<OscWaveView> wave_;
    std::unique_ptr<toi::Lcd> scope_;
    std::vector<std::unique_ptr<toi::MoldedButton>> slots_;
    std::unique_ptr<OscFunc> rand_, save_;
    std::vector<Group> groupsA_, groupsB_;
    int activeHarm_ = 0;
    juce::Image grain_;
    juce::Rectangle<float> rPanel, rowA_, rowB_, rHarmBox_, rLevel_, rScope_, rPreset_, rBrand_;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JWOSCEditor)
};

//==============================================================================
class JWOSCPlugin  : public cmaj::plugin::GeneratedPlugin<::JWOSC>,
                     public toi::AudioTapSource,
                     public toi::PresetStore
{
public:
    using Base = cmaj::plugin::GeneratedPlugin<::JWOSC>;
    JWOSCPlugin (std::shared_ptr<cmaj::Patch> p) : Base (std::move (p)) {}
    juce::AudioProcessorEditor* createEditor() override { return new JWOSCEditor (*this, keyboardState); }
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
