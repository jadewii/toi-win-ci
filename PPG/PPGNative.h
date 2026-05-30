// JW-PPG native faceplate (wavetable 8-voice poly) on the toi_faceplate.h kit.
// DISTINCT digital-wavetable look (Jade ref 2026-05-27, the "3rd Wave"): a deep COBALT-BLUE metal
// panel, thin-outlined section boxes with titles, black METAL knobs with white pointers, an AMBER
// CRT scope (real audio animation), and MOLDED square preset buttons (cream, PINK when pressed).
// No wood cheeks (full-width). No brand names.
#pragma once

#include "toi_faceplate.h"

struct PPG;

namespace ppg
{
    static const juce::Colour kBlue   { 0xff3157d4 };   // royal blue panel
    static const juce::Colour kBlueLo { 0xff2443ac };
    static const juce::Colour kFrame  { 0xff070b16 };
    static const juce::Colour kWhite  { 0xffeef1f6 };   // labels
    static const juce::Colour kDim    { 0xffaab6cf };
    static const juce::Colour kAmber  { 0xffffb43c };   // CRT + knob pointers/accents
    static const juce::Colour kPink   { 0xffff4f9d };   // pressed/active buttons + MODULE led
    static const juce::Colour kCream  { 0xffe9e7df };   // molded button base
    static const juce::Colour kBox    { 0x33ffffff };   // section-box outline (alpha white)
}

//==============================================================================
inline toi::Config ppgConfig()
{
    toi::Config c;
    c.model = "JW-PPG";
    auto& p = c.pal;
    p.bg = ppg::kBlue; p.bg2 = ppg::kBlueLo; p.frame = ppg::kFrame; p.ink = ppg::kFrame;
    p.accent = ppg::kAmber;   // knob pointers + SIZE led
    p.accent2 = ppg::kPink;   // MODULE led
    p.button = juce::Colour (0xff20305c); p.thumb = ppg::kWhite; p.text = ppg::kWhite;
    p.lcdBg = juce::Colour (0xff0a0e18); p.lcdInk = ppg::kAmber;
    p.noteStrip = ppg::kBlueLo;
    p.keyWhite = juce::Colour (0xffEDEDEA); p.keyWhitePr = juce::Colour (0xfff3c98a);
    p.keyBlack = juce::Colour (0xff10131c); p.keyBlackPr = ppg::kAmber;

    c.params = {
        { "waveA","WAVE" }, { "waveB","B-SCAN" }, { "waveEnv","W-ENV" }, { "waveLfo","W-LFO" },
        { "detune","DETUNE" }, { "mix","A/B" }, { "sub","SUB" }, { "noise","NOISE" }, { "grit","GRIT" },
        { "cutoff","CUTOFF" }, { "res","RESO" }, { "filtEnv","ENV" }, { "keytrk","KEY" },
        { "fA","A" }, { "fD","D" }, { "fS","S" }, { "fR","R" },
        { "aA","A" }, { "aD","D" }, { "aS","S" }, { "aR","R" },
        { "lfoRate","RATE" }, { "lfoShape","SHAPE" }, { "volume","VOLUME" }, { "tune","TUNE" },
    };

    // placeholder banks (final presets baked later via BAKE). P() = a few musical knobs; rest defaults.
    auto P = [] (const char* nm, float wave,float wenv,float wlfo,float grit,float cut,float reso,float fenv,float fd,float aa,float ar,float lfo)
    {
        return toi::FactoryPreset { nm, {
            wave,0.20f,wenv,wlfo, 0.18f,0.50f,0.0f,0.0f,grit,
            cut,reso,fenv,0.30f, 0.10f,fd,0.40f,0.40f,
            aa,0.50f,0.80f,ar, lfo,0.0f,0.80f,0.50f } };
    };
    c.factory = {
        P("GLASS PAD", 0.15,0.45,0.10,0.20,0.62,0.18,0.40,0.55,0.40,0.55,0.25),
        P("METAL BELL",0.55,0.60,0.05,0.45,0.70,0.22,0.55,0.35,0.02,0.45,0.10),
        P("WAVE SWEEP",0.05,0.85,0.15,0.30,0.45,0.30,0.70,0.60,0.30,0.50,0.30),
        P("DIGI BASS", 0.40,0.30,0.0, 0.55,0.55,0.30,0.50,0.30,0.02,0.25,0.10),
        P("CHOIR-OID", 0.20,0.40,0.20,0.18,0.55,0.20,0.35,0.50,0.45,0.60,0.35),
        P("SCAN LEAD", 0.30,0.55,0.10,0.35,0.72,0.35,0.50,0.30,0.04,0.30,0.25),
        P("COLD STR",  0.18,0.35,0.12,0.25,0.50,0.18,0.30,0.55,0.40,0.55,0.30),
        P("PPG BRASS", 0.35,0.50,0.05,0.30,0.60,0.22,0.55,0.30,0.06,0.30,0.10),
        P("HOLLOW",    0.50,0.30,0.18,0.40,0.55,0.25,0.40,0.45,0.20,0.50,0.40),
        P("WIND PAD",  0.10,0.70,0.25,0.20,0.42,0.28,0.60,0.60,0.55,0.65,0.45),
        P("RES SWEEP", 0.25,0.65,0.10,0.30,0.55,0.55,0.65,0.40,0.10,0.45,0.30),
        P("8-BIT",     0.45,0.40,0.0, 0.85,0.65,0.20,0.45,0.35,0.02,0.35,0.20),
        P("VOICES",    0.22,0.50,0.15,0.22,0.52,0.20,0.40,0.50,0.40,0.55,0.35),
        P("DARK PAD",  0.12,0.40,0.10,0.25,0.38,0.22,0.45,0.60,0.50,0.70,0.30),
        P("INIT",      0.15,0.45,0.10,0.25,0.70,0.18,0.40,0.45,0.06,0.40,0.30),
    };
    return c;
}

//==============================================================================
class PPGEditor  : public toi::PanelEditor
{
public:
    PPGEditor (juce::AudioProcessor& proc, juce::MidiKeyboardState& kb)
        : toi::PanelEditor (proc, kb, ppgConfig())
    {
        cheekInset = 0.0f;   // full-width blue panel (no wood)
        grain_ = makeGrain (110, 110);

        addKnobs (kWave, { {"waveA","WAVE"}, {"waveB","B-SCAN"}, {"waveEnv","W-ENV"}, {"waveLfo","W-LFO"} });
        addKnobs (kOsc,  { {"detune","DETUNE"}, {"mix","A/B"}, {"sub","SUB"}, {"noise","NOISE"}, {"grit","GRIT"} });
        addKnobs (kFilt, { {"cutoff","CUTOFF"}, {"res","RESO"}, {"filtEnv","ENV"}, {"keytrk","KEY"} });
        addKnobs (kFEnv, { {"fA","A"}, {"fD","D"}, {"fS","S"}, {"fR","R"} });
        addKnobs (kAEnv, { {"aA","A"}, {"aD","D"}, {"aS","S"}, {"aR","R"} });
        addKnobs (kLfo,  { {"lfoRate","RATE"}, {"lfoShape","SHAPE"} });
        addKnobs (kOut,  { {"volume","VOLUME"}, {"tune","TUNE"} });

        scope_ = std::make_unique<toi::Lcd> (pal());
        scope_->setLines ("", "");
        scope_->attachScope (audioTap());
        addAndMakeVisible (*scope_);

        for (int i = 0; i < 16; ++i)
        {
            auto b = std::make_unique<toi::MoldedButton> (ppg::kCream);
            b->setPink (ppg::kPink); b->setCircle (true);   // square with a 3D circular dome inside
            const int idx = i; b->onClick = [this, idx] { recallSlot (idx); };
            addAndMakeVisible (*b); slots.push_back (std::move (b));
        }
        rand_ = std::make_unique<toi::Button> ("RAND", pal());
        save_ = std::make_unique<toi::Button> ("SAVE", pal());
        rand_->onClick = [this] { doRandom(); };
        save_->onClick = [this] { saveSlot (activeSlot()); };
        addAndMakeVisible (*rand_); addAndMakeVisible (*save_);
        finishSetup();
    }

protected:
    void setPresetActiveVisual (int idx) override
    { for (int i = 0; i < (int) slots.size(); ++i) slots[(size_t) i]->setActive (i == idx); }

    static juce::Image makeGrain (int w, int h)
    {
        juce::Image img (juce::Image::ARGB, w, h, true);
        juce::Random r (517);
        for (int y = 0; y < h; ++y) for (int x = 0; x < w; ++x)
        { const float n = r.nextFloat(); if (n > 0.70f) { const float a = (n - 0.70f) / 0.30f * 0.05f; const bool light = r.nextBool();
            img.setPixelAt (x, y, (light ? juce::Colours::white : juce::Colours::black).withAlpha (a)); } }
        return img;
    }

    void box (juce::Graphics& g, juce::Rectangle<float> r, const juce::String& title, juce::Colour titleCol)
    {
        g.setColour (juce::Colours::black.withAlpha (0.18f)); g.fillRoundedRectangle (r, 5.0f);
        g.setColour (ppg::kBox); g.drawRoundedRectangle (r, 5.0f, 1.2f);
        g.setColour (juce::Colours::white.withAlpha (0.05f)); g.drawRoundedRectangle (r.reduced (1.2f), 4.0f, 1.0f);
        g.setColour (titleCol); g.setFont (toi::uiFont (8.0f, true).withExtraKerningFactor (0.14f));
        g.drawText (title, r.withHeight (14.0f).translated (0.0f, 2.0f), juce::Justification::centred);
    }

    void paintPanel (juce::Graphics& g, juce::Rectangle<float> panel) override
    {
        juce::ignoreUnused (panel);
        juce::ColourGradient pg (ppg::kBlue, rPanel.getCentreX(), rPanel.getY(), ppg::kBlueLo, rPanel.getCentreX(), rPanel.getBottom(), false);
        g.setGradientFill (pg); g.fillRoundedRectangle (rPanel, 5.0f);
        if (grain_.isValid()) { g.setFillType (juce::FillType (grain_, juce::AffineTransform::translation (rPanel.getX(), rPanel.getY()))); g.fillRoundedRectangle (rPanel, 5.0f); }
        g.setColour (juce::Colours::black); g.drawRoundedRectangle (rPanel, 5.0f, 1.5f);
        g.setColour (juce::Colours::white.withAlpha (0.06f)); g.drawRoundedRectangle (rPanel.reduced (1.5f), 4.0f, 1.0f);

        box (g, rWave, "WAVE",          ppg::kAmber);
        box (g, rOsc,  "OSCILLATORS",   ppg::kWhite);
        box (g, rFilt, "LOW-PASS FILTER",ppg::kWhite);
        box (g, rFEnv, "FILTER ENV",    ppg::kWhite);
        box (g, rAEnv, "AMP ENV",       ppg::kWhite);
        box (g, rLfo,  "LFO",           ppg::kWhite);
        box (g, rOut,  "OUTPUT",        ppg::kWhite);
        box (g, rPresets, "PRESETS",    ppg::kAmber);

        // CRT screen bezel (the amber scope component sits inside rScreen)
        g.setColour (juce::Colours::black); g.fillRoundedRectangle (rScreen.expanded (2.5f), 4.0f);
        g.setColour (ppg::kAmber.withAlpha (0.30f)); g.drawRoundedRectangle (rScreen.expanded (2.5f), 4.0f, 1.0f);

        // brand block (top-right): view LEDs + model
        auto bh = rBrandHdr;
        drawViewLeds (g, bh.removeFromLeft (108.0f));
        g.setColour (ppg::kWhite); g.setFont (toi::uiFont (20.0f, true).withExtraKerningFactor (0.04f));
        g.drawText ("JW-PPG", bh.withTrimmedBottom (7.0f), juce::Justification::centredRight);
        g.setColour (ppg::kAmber); g.setFont (toi::uiFont (6.0f, true).withExtraKerningFactor (0.26f));
        g.drawText ("WAVETABLE SYNTH - TOI", bh.removeFromBottom (8.0f), juce::Justification::centredRight);
    }

    void layoutPanel (juce::Rectangle<float> panel) override
    {
        rPanel = panel;   // cheekInset 0, taller panel via panelH()
        auto inner = rPanel.reduced (10.0f, 8.0f);

        // ---- RIGHT BLOCK: brand on top, AMBER screen, then a compact 4x4 preset grid ----
        auto right = inner.removeFromRight (250.0f);
        inner.removeFromRight (12.0f);
        rBrandHdr = right.removeFromTop (30.0f);
        right.removeFromTop (4.0f);
        rScreen = right.removeFromTop (62.0f).reduced (3.0f, 0.0f);
        placeInArtboard (*scope_, rScreen);
        right.removeFromTop (8.0f);
        rPresets = right;
        {
            auto pr = rPresets.reduced (8.0f, 5.0f);
            auto titleRow = pr.removeFromTop (14.0f);
            placeInArtboard (*save_, titleRow.removeFromRight (40.0f).reduced (1.0f, 0.0f));
            titleRow.removeFromRight (4.0f);
            placeInArtboard (*rand_, titleRow.removeFromRight (40.0f).reduced (1.0f, 0.0f));
            pr.removeFromTop (4.0f);
            const int cols = 4, rows = 4; const float gx = 6.0f, gy = 6.0f;
            const float cw = (pr.getWidth() - gx * (cols - 1)) / (float) cols;
            const float ch = (pr.getHeight() - gy * (rows - 1)) / (float) rows;
            for (int i = 0; i < 16; ++i)
            { const int cc = i % cols, rr = i / cols;
              placeInArtboard (*slots[(size_t) i], juce::Rectangle<float> (pr.getX() + cc * (cw + gx), pr.getY() + rr * (ch + gy), cw, ch)); }
        }

        // ---- LEFT: two rows of knob section boxes (taller panel = bigger numeral knobs) ----
        const float rowGap = 8.0f;
        const float rowH = (inner.getHeight() - rowGap) * 0.5f;
        auto rowA = inner.removeFromTop (rowH);
        auto rowB = inner.withTrimmedTop (rowGap);

        rWave = rowA.removeFromLeft (296.0f); rowA.removeFromLeft (8.0f);
        rOsc  = rowA.removeFromLeft (372.0f); rowA.removeFromLeft (8.0f);
        rFilt = rowA;                                       // remainder
        gridKnobs (kWave, rWave, 4);
        gridKnobs (kOsc,  rOsc,  5);
        gridKnobs (kFilt, rFilt, 4);

        rFEnv = rowB.removeFromLeft (300.0f); rowB.removeFromLeft (8.0f);
        rAEnv = rowB.removeFromLeft (300.0f); rowB.removeFromLeft (8.0f);
        rLfo  = rowB.removeFromLeft (170.0f); rowB.removeFromLeft (8.0f);
        rOut  = rowB;                                       // remainder
        gridKnobs (kFEnv, rFEnv, 4);
        gridKnobs (kAEnv, rAEnv, 4);
        gridKnobs (kLfo,  rLfo,  2);
        gridKnobs (kOut,  rOut,  2);
    }

private:
    struct KSpec { const char* id; const char* label; };
    void addKnobs (std::vector<std::unique_ptr<toi::StyledKnob>>& dst, std::initializer_list<KSpec> specs)
    {
        for (auto& s : specs)
        {
            auto k = std::make_unique<toi::StyledKnob> (s.label, pal(), (int) toi::StyledKnob::LineKnob);   // P5-style numeral ring
            if (auto* prm = findParam (s.id)) k->attach (*prm);
            addAndMakeVisible (*k); dst.push_back (std::move (k));
        }
    }
    void gridKnobs (std::vector<std::unique_ptr<toi::StyledKnob>>& v, juce::Rectangle<float> box, int cols)
    {
        auto r = box.reduced (6.0f, 4.0f).withTrimmedTop (14.0f);
        const int n = (int) v.size(); if (n == 0) return;
        const int rows = (n + cols - 1) / cols;
        const float cw = r.getWidth() / (float) cols, rh = r.getHeight() / (float) rows;
        for (int i = 0; i < n; ++i) { const int cc = i % cols, rr = i / cols;
            placeInArtboard (*v[(size_t) i], juce::Rectangle<float> (r.getX() + cc * cw, r.getY() + rr * rh, cw, rh).reduced (2.0f, 1.0f)); }
    }

    std::vector<std::unique_ptr<toi::StyledKnob>> kWave, kOsc, kFilt, kFEnv, kAEnv, kLfo, kOut;
    std::vector<std::unique_ptr<toi::MoldedButton>> slots;
    std::unique_ptr<toi::Button> rand_, save_;
    std::unique_ptr<toi::Lcd> scope_;
    juce::Image grain_;
    juce::Rectangle<float> rPanel, rWave, rOsc, rFilt, rFEnv, rAEnv, rLfo, rOut, rPresets, rScreen, rBrandHdr;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PPGEditor)
};

//==============================================================================
class PPGPlugin  : public cmaj::plugin::GeneratedPlugin<::PPG>,
                   public toi::AudioTapSource,
                   public toi::PresetStore
{
public:
    using Base = cmaj::plugin::GeneratedPlugin<::PPG>;
    PPGPlugin (std::shared_ptr<cmaj::Patch> p) : Base (std::move (p)) {}
    juce::AudioProcessorEditor* createEditor() override { return new PPGEditor (*this, keyboardState); }
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
