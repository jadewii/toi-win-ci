// JW-20M native faceplate (screaming semi-modular mono) on the toi_faceplate.h kit.
// FAITHFUL MS-20 look (Jade ref 2026-05-27): ALL KNOBS (no sliders) - numeral-ring dials with a
// white pointer, grouped into thin-bordered sections with white titles, on a matte-BLACK panel.
// (A white-panel variant is a quick palette swap.) NO brand names. EVERY param wired.
#pragma once

#include "toi_faceplate.h"

struct MS20;

namespace ms20
{
    static const juce::Colour kCheek  { 0xff34343a };   // black-metal end-cheeks
    static const juce::Colour kCheekLo{ 0xff1e1e22 };
    static const juce::Colour kPanel  { 0xff19191b };   // matte black panel
    static const juce::Colour kPanelLo{ 0xff131315 };
    static const juce::Colour kFrame  { 0xff050505 };
    static const juce::Colour kBorder { 0xff6c6e74 };   // thin grey section outlines
    static const juce::Colour kRed    { 0xffd8392b };   // the little red LEDs
    static const juce::Colour kBtnGrn { 0xff8cd645 };   // SAVE
    static const juce::Colour kBtnYel { 0xfff3e863 };   // RAND
    static const juce::Colour kWhite  { 0xffe6e6e9 };
    static const juce::Colour kWhiteDim{ 0xff9a9a9e };
}

//==============================================================================
class Ms20FuncButton  : public juce::Button
{
public:
    Ms20FuncButton (const juce::String& text, juce::Colour fill) : juce::Button (text), col (fill) { setButtonText (text); }
    void flash() { flashing = true; repaint(); juce::Timer::callAfterDelay (160, [s = juce::Component::SafePointer<Ms20FuncButton> (this)] { if (s) { s->flashing = false; s->repaint(); } }); }
    void paintButton (juce::Graphics& g, bool over, bool down) override
    {
        auto b = getLocalBounds().toFloat().reduced (1.0f);
        auto fill = flashing ? col.brighter (0.35f) : down ? col.darker (0.18f) : over ? col.brighter (0.08f) : col;
        g.setColour (fill); g.fillRoundedRectangle (b, 2.5f);
        g.setColour (juce::Colours::black.withAlpha (0.4f)); g.drawRoundedRectangle (b, 2.5f, 1.2f);
        g.setColour (juce::Colour (0xff20160a)); g.setFont (toi::uiFont (juce::jmin (10.0f, b.getHeight() * 0.5f), true));
        g.drawText (getButtonText(), getLocalBounds(), juce::Justification::centred);
    }
private:
    juce::Colour col; bool flashing = false;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Ms20FuncButton)
};

//==============================================================================
class Ms20Preset  : public juce::Button
{
public:
    explicit Ms20Preset (const toi::Palette&) : juce::Button ("preset") {}
    void setActive (bool a) { if (active != a) { active = a; repaint(); } }
    void paintButton (juce::Graphics& g, bool over, bool down) override
    {
        auto b = getLocalBounds().toFloat().reduced (1.0f);
        const float base = over ? 0.08f : 0.0f;
        juce::ColourGradient cap (juce::Colour (0xff303034).brighter (base), b.getCentreX(), b.getY(), juce::Colour (0xff161618), b.getCentreX(), b.getBottom(), false);
        g.setGradientFill (cap); g.fillRoundedRectangle (b, 2.0f);
        if (down) { g.setColour (juce::Colours::black.withAlpha (0.18f)); g.fillRoundedRectangle (b, 2.0f); }
        g.setColour (juce::Colours::white.withAlpha (0.14f)); g.drawLine (b.getX() + 1.5f, b.getY() + 1.0f, b.getRight() - 1.5f, b.getY() + 1.0f, 1.0f);
        g.setColour (juce::Colours::black.withAlpha (0.5f)); g.drawRoundedRectangle (b, 2.0f, 1.0f);
        const float d = juce::jmin (b.getWidth(), b.getHeight()) * 0.30f;
        auto led = juce::Rectangle<float> (0, 0, d, d).withCentre ({ b.getCentreX(), b.getY() + d * 1.05f });
        g.setColour (active ? ms20::kRed.brighter (0.2f) : juce::Colour (0xff431f1a));
        g.fillEllipse (led);
        if (active) { g.setColour (ms20::kRed.brighter (0.7f).withAlpha (0.8f)); g.fillEllipse (led.reduced (d * 0.3f)); }
        g.setColour (juce::Colours::black.withAlpha (0.5f)); g.drawEllipse (led, 0.6f);
    }
private:
    bool active = false;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Ms20Preset)
};

//==============================================================================
inline toi::Config ms20Config()
{
    toi::Config c;
    c.model = "JW-20M";
    auto& p = c.pal;
    p.bg = ms20::kCheek; p.bg2 = ms20::kCheekLo; p.frame = ms20::kFrame; p.ink = ms20::kFrame;
    p.accent = ms20::kRed; p.accent2 = ms20::kRed; p.button = juce::Colour (0xff141416);
    p.thumb = juce::Colour (0xfff0f0f2); p.text = ms20::kWhite;
    p.noteStrip = ms20::kPanel;
    p.keyWhite = juce::Colour (0xffEDEDEA); p.keyWhitePr = juce::Colour (0xffd6d6d8);
    p.keyBlack = juce::Colour (0xff121214); p.keyBlackPr = juce::Colour (0xffb0524a);   // muted red press

    c.params = {
        { "mgRate","FREQ" }, { "mgWave","WAVE" }, { "mgPitch","-> PITCH" }, { "mgFilt","-> FILT" },
        { "o1Wave","WAVE" }, { "o1PW","PW" },
        { "o2Wave","WAVE" }, { "o2Pitch","PITCH" }, { "o2PW","PW" }, { "sync","SYNC" },
        { "mix1","VCO1" }, { "mix2","VCO2" }, { "noise","NOISE" }, { "ring","RING" }, { "drive","DRIVE" },
        { "hpfCut","CUTOFF" }, { "hpfPeak","PEAK" },
        { "lpfCut","CUTOFF" }, { "lpfPeak","PEAK" }, { "egFilt","EG AMT" },
        { "e1A","ATTACK" }, { "e1R","RELEASE" }, { "e1Pitch","-> PITCH" },
        { "aA","ATTACK" }, { "aD","DECAY" }, { "aS","SUSTAIN" }, { "aR","RELEASE" },
        { "volume","VOLUME" }, { "tune","TUNE" }, { "porta","PORTA" },
    };

    auto P = [] (const char* nm,
                 float mgRate,float mgWave,float mgPitch,float mgFilt,
                 float o1Wave,float o1PW, float o2Wave,float o2Pitch,float o2PW,float sync,
                 float mix1,float mix2,float noise,float ring,float drive,
                 float hpfCut,float hpfPeak, float lpfCut,float lpfPeak,float egFilt,
                 float e1A,float e1R,float e1Pitch, float aA,float aD,float aS,float aR, float porta)
    {
        return toi::FactoryPreset { nm, {
            mgRate,mgWave,mgPitch,mgFilt, o1Wave,o1PW, o2Wave,o2Pitch,o2PW,sync,
            mix1,mix2,noise,ring,drive, hpfCut,hpfPeak, lpfCut,lpfPeak,egFilt,
            e1A,e1R,e1Pitch, aA,aD,aS,aR, 0.80f,0.50f,porta } };
    };
    c.factory = {
        P("ACID BASS",  0.30,0.0,0.0,0.0, 0.34,0.5, 0.0,0.5,0.5,0.0, 0.85,0.0,0.0,0.0,0.45, 0.0,0.20, 0.40,0.55,0.55, 0.02,0.3,0.0, 0.02,0.35,0.1,0.2, 0.0),
        P("SCREAM LEAD",0.30,1.0,0.0,0.0, 0.34,0.5, 0.0,0.5,0.5,0.0, 0.8,0.6,0.0,0.0,0.55, 0.2,0.55, 0.6,0.7,0.45, 0.02,0.4,0.0, 0.02,0.4,0.8,0.25, 0.1),
        P("RING METAL", 0.40,0.0,0.0,0.0, 0.34,0.5, 0.5,0.62,0.5,0.0, 0.5,0.5,0.0,0.8,0.5, 0.1,0.4, 0.55,0.45,0.4, 0.02,0.5,0.0, 0.02,0.5,0.5,0.4, 0.0),
        P("SYNC TEAR",  0.30,0.0,0.0,0.0, 0.34,0.5, 0.0,0.66,0.5,1.0, 0.5,0.85,0.0,0.0,0.55, 0.0,0.35, 0.62,0.5,0.55, 0.02,0.4,0.3, 0.02,0.45,0.7,0.3, 0.0),
        P("NOISE SWEEP",0.20,1.0,0.0,1.0, 0.34,0.5, 0.0,0.5,0.5,0.0, 0.3,0.0,0.9,0.0,0.4, 0.3,0.5, 0.4,0.6,0.5, 0.1,0.6,0.0, 0.1,0.6,0.4,0.5, 0.0),
        P("HOLLOW PWM", 0.30,0.0,0.0,0.0, 0.66,0.6, 0.66,0.5,0.6,0.0, 0.7,0.6,0.0,0.0,0.4, 0.2,0.3, 0.5,0.4,0.4, 0.02,0.45,0.0, 0.02,0.45,0.6,0.4, 0.0),
        P("SUB BASS",   0.30,0.0,0.0,0.0, 0.0,0.5, 0.0,0.38,0.5,0.0, 0.85,0.0,0.0,0.0,0.5, 0.0,0.25, 0.36,0.4,0.5, 0.02,0.3,0.0, 0.02,0.35,0.2,0.2, 0.0),
        P("LASER ZAP",  0.30,0.0,0.0,0.0, 0.34,0.5, 0.0,0.5,0.5,0.0, 0.8,0.0,0.0,0.0,0.55, 0.0,0.6, 0.6,0.75,0.7, 0.02,0.25,0.9, 0.02,0.2,0.0,0.15, 0.0),
        P("VOWEL SWEEP",0.40,0.0,0.0,1.0, 0.34,0.5, 0.0,0.5,0.5,0.0, 0.8,0.5,0.0,0.0,0.45, 0.5,0.6, 0.45,0.6,0.4, 0.1,0.5,0.0, 0.1,0.5,0.6,0.5, 0.0),
        P("FAT SAW",    0.30,0.0,0.0,0.0, 0.34,0.5, 0.0,0.49,0.5,0.0, 0.85,0.8,0.0,0.0,0.45, 0.0,0.3, 0.5,0.45,0.5, 0.02,0.4,0.0, 0.02,0.45,0.7,0.3, 0.05),
        P("ROBOT FM",   0.5,1.0,0.4,0.0, 0.34,0.5, 0.5,0.6,0.5,1.0, 0.6,0.7,0.0,0.4,0.55, 0.1,0.5, 0.55,0.55,0.45, 0.02,0.4,0.0, 0.02,0.4,0.5,0.3, 0.0),
        P("DRONE",      0.10,0.0,0.0,0.3, 0.0,0.5, 0.0,0.5,0.5,0.0, 0.8,0.7,0.0,0.0,0.5, 0.2,0.55, 0.5,0.65,0.3, 0.5,0.7,0.0, 0.6,0.7,0.85,0.8, 0.0),
        P("PERC STAB",  0.30,0.0,0.0,0.0, 0.34,0.5, 0.0,0.5,0.5,0.0, 0.8,0.5,0.2,0.0,0.55, 0.1,0.5, 0.55,0.6,0.6, 0.02,0.2,0.0, 0.02,0.18,0.0,0.15, 0.0),
        P("WHISTLE",    0.30,0.0,0.0,0.0, 0.34,0.5, 0.0,0.5,0.5,0.0, 0.0,0.0,0.0,0.0,0.3, 0.3,0.95, 0.6,0.95,0.3, 0.02,0.4,0.0, 0.1,0.5,0.8,0.5, 0.0),
        P("TECHNO BASS",0.30,0.0,0.0,0.0, 0.34,0.5, 0.0,0.5,0.5,0.0, 0.85,0.0,0.0,0.0,0.6, 0.0,0.4, 0.42,0.6,0.6, 0.02,0.3,0.0, 0.02,0.3,0.0,0.2, 0.0),
        P("DIRTY PWM",  0.40,1.0,0.0,0.0, 0.66,0.4, 0.66,0.5,0.4,0.0, 0.8,0.6,0.0,0.0,0.6, 0.1,0.45, 0.5,0.55,0.5, 0.02,0.45,0.0, 0.02,0.5,0.7,0.4, 0.0),
    };
    return c;
}

//==============================================================================
class Ms20Editor  : public toi::PanelEditor
{
public:
    Ms20Editor (juce::AudioProcessor& proc, juce::MidiKeyboardState& kb)
        : toi::PanelEditor (proc, kb, ms20Config())
    {
        cheekInset = 18.0f;
        grain_ = makeGrain (96, 96);

        auto knob = [this] (const juce::String& id, const juce::String& label, std::vector<std::unique_ptr<toi::StyledKnob>>& dst, bool bip = false)
        {
            auto k = std::make_unique<toi::StyledKnob> (label, pal(), toi::StyledKnob::LineKnob);
            k->setBipolar (bip);
            if (auto* prm = findParam (id)) k->attach (*prm);
            addAndMakeVisible (*k); dst.push_back (std::move (k));
        };

        knob ("o1Wave","WAVE",kVco1); knob ("o1PW","PW",kVco1);
        knob ("o2Wave","WAVE",kVco2); knob ("o2Pitch","PITCH",kVco2,true); knob ("o2PW","PW",kVco2); knob ("sync","SYNC",kVco2);
        knob ("mix1","VCO1",kMix); knob ("mix2","VCO2",kMix); knob ("noise","NOISE",kMix); knob ("ring","RING",kMix);
        knob ("hpfCut","CUTOFF",kHpf); knob ("hpfPeak","PEAK",kHpf);
        knob ("lpfCut","CUTOFF",kLpf); knob ("lpfPeak","PEAK",kLpf);
        knob ("mgRate","FREQ",kMg); knob ("mgWave","WAVE",kMg); knob ("mgPitch","PITCH",kMg,true); knob ("mgFilt","FILT",kMg);
        knob ("e1A","ATTACK",kEg1); knob ("e1R","RELEASE",kEg1); knob ("e1Pitch","PITCH",kEg1);
        knob ("aA","ATTACK",kEg2); knob ("aD","DECAY",kEg2); knob ("aS","SUSTAIN",kEg2); knob ("aR","RELEASE",kEg2); knob ("egFilt","EG AMT",kEg2);
        knob ("drive","DRIVE",kOut); knob ("volume","VOLUME",kOut); knob ("tune","TUNE",kOut,true); knob ("porta","PORTA",kOut);

        for (int i = 0; i < 16; ++i)
        { auto b = std::make_unique<Ms20Preset> (pal()); const int idx = i; b->onClick = [this, idx] { recallSlot (idx); }; addAndMakeVisible (*b); slots.push_back (std::move (b)); }
        rand_ = std::make_unique<Ms20FuncButton> ("RAND", ms20::kBtnYel);
        save_ = std::make_unique<Ms20FuncButton> ("SAVE", ms20::kBtnGrn);
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
        for (int y = 0; y < h; ++y) for (int x = 0; x < w; ++x)
        { const float n = r.nextFloat();
          if (n > 0.66f) { const float a = (n - 0.66f) / 0.34f * 0.07f; const bool light = r.nextBool();
              img.setPixelAt (x, y, (light ? juce::Colours::white : juce::Colours::black).withAlpha (a)); } }
        return img;
    }
    // thin-bordered MS-20 section box with a white title at the top
    void section (juce::Graphics& g, juce::Rectangle<float> r, const juce::String& title)
    {
        g.setColour (ms20::kBorder.withAlpha (0.85f)); g.drawRoundedRectangle (r.reduced (0.5f), 3.0f, 1.0f);
        auto t = r.withHeight (12.0f).withY (r.getY() + 3.0f);
        g.setColour (ms20::kPanel); g.fillRect (t.withSizeKeepingCentre (juce::jmin (r.getWidth() - 6.0f, title.length() * 5.6f + 8.0f), 11.0f));
        g.setColour (ms20::kWhite); g.setFont (toi::uiFont (7.5f, true).withExtraKerningFactor (0.06f));
        g.drawText (title, t, juce::Justification::centred);
    }

    void paintPanel (juce::Graphics& g, juce::Rectangle<float> panel) override
    {
        juce::ignoreUnused (panel);
        juce::ColourGradient pg (ms20::kPanel, rPanel.getCentreX(), rPanel.getY(), ms20::kPanelLo, rPanel.getCentreX(), rPanel.getBottom(), false);
        g.setGradientFill (pg); g.fillRoundedRectangle (rPanel, 5.0f);
        if (grain_.isValid()) { g.setFillType (juce::FillType (grain_, juce::AffineTransform::translation (rPanel.getX(), rPanel.getY()))); g.fillRoundedRectangle (rPanel, 5.0f); }
        g.setColour (juce::Colours::black); g.drawRoundedRectangle (rPanel, 5.0f, 1.5f);

        section (g, rVco1, "VCO-1");  section (g, rVco2, "VCO-2"); section (g, rMix, "VCO MIXER");
        section (g, rHpf,  "HPF");    section (g, rLpf,  "LPF");
        section (g, rMg,   "MOD GEN");section (g, rEg1,  "EG-1");   section (g, rEg2, "EG-2");
        section (g, rOut,  "OUTPUT");

        // little red LEDs (MG + EG-1), like the hardware
        auto dot = [&] (float cx, float cy) { g.setColour (ms20::kRed.withAlpha (0.5f)); g.fillEllipse (cx - 5.0f, cy - 5.0f, 10.0f, 10.0f); g.setColour (ms20::kRed.brighter (0.2f)); g.fillEllipse (cx - 3.0f, cy - 3.0f, 6.0f, 6.0f); };
        dot (rMg.getCentreX(), rMg.getY() + 22.0f);
        dot (rEg1.getCentreX(), rEg1.getY() + 22.0f);

        auto bh = rBrandHdr;
        drawViewLeds (g, bh.removeFromTop (18.0f));
        g.setColour (ms20::kWhite); g.setFont (toi::uiFont (13.0f, true));
        g.drawText ("JW-20M", bh.removeFromTop (15.0f), juce::Justification::centred);
        g.setColour (ms20::kWhiteDim); g.setFont (toi::uiFont (5.5f, true).withExtraKerningFactor (0.2f));
        g.drawText ("TOI - plugin corp", bh.removeFromTop (8.0f), juce::Justification::centred);

        g.setColour (ms20::kWhiteDim); g.setFont (toi::uiFont (7.0f, true).withExtraKerningFactor (0.10f));
        g.drawText ("PROGRAMMER", rProgLbl, juce::Justification::centredLeft);
    }

    void layoutPanel (juce::Rectangle<float> panel) override
    {
        rPanel = juce::Rectangle<float> (panel.getX() + cheekInset, panel.getY(), panel.getWidth() - 2.0f * cheekInset, panel.getHeight());
        auto inner = rPanel.reduced (9.0f, 7.0f);

        rProg = inner.removeFromBottom (26.0f);
        inner.removeFromBottom (5.0f);
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

        // 9 bordered sections in one row (all knobs)
        const float colGap = 5.0f;
        const float t = inner.getWidth() - colGap * 8.0f;
        const float fr[9] = { 0.085f, 0.13f, 0.13f, 0.075f, 0.075f, 0.13f, 0.085f, 0.155f, 0.135f };
        juce::Rectangle<float>* rr[9] = { &rVco1, &rVco2, &rMix, &rHpf, &rLpf, &rMg, &rEg1, &rEg2, &rOut };
        float x = inner.getX();
        for (int i = 0; i < 9; ++i) { const float w = (i == 8) ? (inner.getRight() - x) : fr[i] * t; *rr[i] = juce::Rectangle<float> (x, inner.getY(), w, inner.getHeight()); x += w + colGap; }

        gridKnobs (kVco1, rVco1, 1);   // WAVE, PW (stacked)
        gridKnobs (kVco2, rVco2, 2);   // WAVE,PITCH / PW,SYNC
        gridKnobs (kMix,  rMix,  2);   // VCO1,VCO2 / NOISE,RING
        gridKnobs (kHpf,  rHpf,  1);   // CUTOFF, PEAK
        gridKnobs (kLpf,  rLpf,  1);   // CUTOFF, PEAK
        gridKnobs (kMg,   rMg,   2);   // FREQ,WAVE / PITCH,FILT
        gridKnobs (kEg1,  rEg1,  1);   // ATK,REL,PITCH
        gridKnobs (kEg2,  rEg2,  2);   // A,D / S,R / EGAMT
        { auto r = rOut.reduced (5.0f, 4.0f).withTrimmedTop (16.0f);
          rBrandHdr = r.removeFromBottom (40.0f);
          gridKnobs2 (kOut, r, 2); }
    }

private:
    void gridKnobs (std::vector<std::unique_ptr<toi::StyledKnob>>& v, juce::Rectangle<float> sec, int cols)
    { gridKnobs2 (v, sec.reduced (5.0f, 4.0f).withTrimmedTop (16.0f), cols); }
    void gridKnobs2 (std::vector<std::unique_ptr<toi::StyledKnob>>& v, juce::Rectangle<float> r, int cols)
    {
        const int n = (int) v.size(); if (n == 0) return;
        const int rows = (n + cols - 1) / cols;
        const float cw = r.getWidth() / (float) cols, rh = r.getHeight() / (float) rows;
        for (int i = 0; i < n; ++i) { const int col = i % cols, row = i / cols;
            placeInArtboard (*v[(size_t) i], juce::Rectangle<float> (r.getX() + col * cw, r.getY() + row * rh, cw, rh).reduced (2.0f, 1.0f)); }
    }

    std::vector<std::unique_ptr<toi::StyledKnob>> kVco1, kVco2, kMix, kHpf, kLpf, kMg, kEg1, kEg2, kOut;
    std::vector<std::unique_ptr<Ms20Preset>> slots;
    std::unique_ptr<Ms20FuncButton> rand_, save_;
    juce::Image grain_;
    juce::Rectangle<float> rPanel, rVco1, rVco2, rMix, rHpf, rLpf, rMg, rEg1, rEg2, rOut, rBrandHdr, rProg, rProgLbl;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Ms20Editor)
};

//==============================================================================
class Ms20Plugin  : public cmaj::plugin::GeneratedPlugin<::MS20>,
                    public toi::AudioTapSource,
                    public toi::PresetStore
{
public:
    using Base = cmaj::plugin::GeneratedPlugin<::MS20>;
    Ms20Plugin (std::shared_ptr<cmaj::Patch> p) : Base (std::move (p)) {}
    juce::AudioProcessorEditor* createEditor() override { return new Ms20Editor (*this, keyboardState); }
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
