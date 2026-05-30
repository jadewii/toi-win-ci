// JW-SEM native faceplate (Oberheim SEM "Synthesizer Expander Module" look) on the
// toi_faceplate.h kit. Built on toi::PanelEditor -> inherits 1300x477 size, single frame,
// 15-key keyboard, MODULE/SIZE, presets + snapshot. WARM PARCHMENT panel, dark-brown frame,
// BLACK scalloped knobs (StyledKnob::FlutedDark) w/ white pointer + blue value arc.
// Layout mirrors the SEM: left control column | VCO1 | VCO2 | VCF(+MIXER) top, ENV1/LFO/ENV2
// bottom. TOI name JW-SEM (not Oberheim). EVERY control is functional.
#pragma once

#include "toi_faceplate.h"

struct SEM;

namespace sm
{
    static const juce::Colour kCream  { 0xffE0D8C0 };   // parchment panel
    static const juce::Colour kCreamLo{ 0xffd2c9ad };   // darker (left column / box fills)
    static const juce::Colour kBrown  { 0xff4A3528 };   // frame + outlines
    static const juce::Colour kBlue   { 0xff5E78B6 };   // value arcs (the SEM VCF blue)
    static const juce::Colour kRed    { 0xffB23A2E };   // brand LED
    static const juce::Colour kText   { 0xff42321f };   // dark labels on cream
}

//==============================================================================
// Small dark rocker switch (orange-lit when ON). Bound to a 0..1 param.
class SemSwitch  : public juce::Component
{
public:
    SemSwitch (const toi::Palette&) {}
    void bindTo (juce::AudioProcessorParameter* p)
    { param_ = p; if (! p) return; slider.setRange (0.0, 1.0, 0.0); attach = std::make_unique<toi::ParamKnobAttachment> (*p, slider); addChildComponent (slider); slider.setVisible (false); }
    bool on() const { return (param_ ? param_->getValue() : (float) slider.getValue()) >= 0.5f; }
    void mouseDown (const juce::MouseEvent&) override { slider.setValue (on() ? 0.0 : 1.0, juce::sendNotificationSync); repaint(); }
    void paint (juce::Graphics& g) override
    {
        auto b = getLocalBounds().toFloat().reduced (1.0f);
        g.setColour (juce::Colour (0xff1a1a1c)); g.fillRoundedRectangle (b, 2.5f);
        g.setColour (sm::kBrown);                g.drawRoundedRectangle (b, 2.5f, 1.0f);
        const bool o = on();
        auto pad = b.reduced (1.6f);
        auto half = o ? pad.removeFromTop (pad.getHeight() * 0.5f) : pad.removeFromBottom (pad.getHeight() * 0.5f);
        g.setColour (o ? sm::kBlue.brighter (0.2f) : juce::Colour (0xff3a3a3d)); g.fillRoundedRectangle (half, 1.5f);
    }
private:
    juce::Slider slider; std::unique_ptr<toi::ParamKnobAttachment> attach; juce::AudioProcessorParameter* param_ = nullptr;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SemSwitch)
};

//==============================================================================
class SemPreset  : public juce::Button
{
public:
    explicit SemPreset (const toi::Palette&) : juce::Button ("preset") {}
    void setActive (bool a) { if (active != a) { active = a; repaint(); } }
    void paintButton (juce::Graphics& g, bool over, bool down) override
    {
        juce::ignoreUnused (down);
        auto b = getLocalBounds().toFloat().reduced (1.0f);
        g.setColour (active ? juce::Colour (0xff555a66) : (over ? juce::Colour (0xff2c2c2c) : juce::Colour (0xff161616)));   // black; active = pressed-black-key colour
        g.fillRoundedRectangle (b, 2.0f);
        g.setColour (juce::Colours::black); g.drawRoundedRectangle (b, 2.0f, 1.0f);
    }
private:
    bool active = false;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SemPreset)
};

//==============================================================================
inline toi::Config semConfig()
{
    toi::Config c;
    c.model = "JW-SEM";
    auto& p = c.pal;
    p.bg = sm::kCream; p.bg2 = juce::Colour (0x00000000); p.frame = sm::kBrown; p.ink = sm::kBrown;
    p.accent = juce::Colour (0xff1c1c1c); p.accent2 = sm::kRed; p.button = juce::Colour (0xff222225);   // knob value-arc BLACK (was blue)
    p.thumb = juce::Colour (0xfff2f2f4); p.text = sm::kText;
    p.keyWhite = juce::Colour (0xffF7F7F4); p.keyWhitePr = juce::Colour (0xffd7dded);
    p.keyBlack = juce::Colour (0xff161616); p.keyBlackPr = juce::Colour (0xff555a66);

    c.params = {
        { "v1tune","FREQUENCY" }, { "v1wave","WAVE" }, { "v1mod","MOD 1" }, { "v1pw","PULSE WIDTH" },
        { "v2tune","FREQUENCY" }, { "v2wave","WAVE" }, { "v2mod","MOD 2" }, { "v2pw","PULSE WIDTH" }, { "sync","SYNC" },
        { "cutoff","FREQUENCY" }, { "reso","RESONANCE" }, { "lfoCut","MOD" }, { "mode","NOTCH" }, { "filtEnv","ENV" }, { "kbd","KBD" }, { "bp","BP" },
        { "mix1","VCO 1" }, { "mix2","VCO 2" }, { "noise","NOISE" },
        { "a1","ATTACK" }, { "d1","DECAY" }, { "s1","SUSTAIN" },
        { "lfoRate","RATE" }, { "lfoWave","WAVE" },
        { "a2","ATTACK" }, { "d2","DECAY" }, { "s2","SUSTAIN" },
        { "glide","PORTA" }, { "vibRate","RATE" }, { "vibAmt","AMOUNT" }, { "volume","MASTER" },
    };

    // 16 SEM patches. P() musical params; structural appended: v1tune=.5,v1wave,v1mod=0,v1pw=.5,
    // v2tune,v2wave,v2mod=0,v2pw=.5,sync,mix1,mix2,noise,cutoff,reso,lfoCut=0,mode,filtEnv,kbd=.5,bp,
    // a1,d1,s1,lfoRate,lfoWave,a2,d2,s2, glide=0,vibRate=.35,vibAmt=0,volume=.8.
    auto P = [] (const char* nm, float v1w,float v2w,float v2t,float sync, float m1,float m2,float nz,
                 float cut,float res,float mode,float fenv,float bp,
                 float a1,float d1,float s1, float lr, float a2,float d2,float s2)
    {
        return toi::FactoryPreset { nm, { 0.5f,v1w,0.0f,0.5f, v2t,v2w,0.0f,0.5f,sync, m1,m2,nz,
                                          cut,res,0.0f,mode,fenv,0.5f,bp, a1,d1,s1, lr,0.0f, a2,d2,s2,
                                          0.0f,0.35f,0.0f,0.8f } };
    };
    c.factory = {
        //         v1w  v2w  v2t  sync m1   m2   nz   cut  res  mode fenv bp   a1   d1   s1   lr   a2   d2   s2
        P("CREAM PAD",   0.0,0.0,0.53,0.0, 0.7,0.7,0.0, 0.55,0.25,0.0,0.40,0.0, 0.40,0.6,0.85, 0.20, 0.45,0.6,0.6),
        P("SYNC LEAD",   0.6,0.6,0.40,1.0, 0.8,0.7,0.0, 0.70,0.30,0.0,0.55,0.0, 0.02,0.4,0.8,  0.25, 0.02,0.5,0.7),
        P("FAT BASS",    0.0,0.0,0.49,0.0, 0.8,0.75,0.0,0.42,0.30,0.0,0.55,0.0, 0.02,0.35,0.1, 0.20, 0.02,0.4,0.2),
        P("PWM STRINGS", 0.8,0.8,0.54,0.0, 0.7,0.7,0.0, 0.55,0.20,0.0,0.35,0.0, 0.45,0.6,0.85, 0.18, 0.40,0.6,0.7),
        P("NOTCH SWEEP", 0.0,0.0,0.52,0.0, 0.7,0.7,0.0, 0.50,0.45,0.5,0.60,0.0, 0.10,0.5,0.7,  0.30, 0.05,0.6,0.4),
        P("HP SPARKLE",  0.0,0.0,0.51,0.0, 0.7,0.6,0.0, 0.60,0.30,1.0,0.40,0.0, 0.05,0.4,0.7,  0.25, 0.05,0.5,0.5),
        P("BP VOX",      0.7,0.7,0.52,0.0, 0.7,0.7,0.0, 0.55,0.55,0.5,0.45,1.0, 0.20,0.5,0.7,  0.22, 0.10,0.5,0.5),
        P("SOFT KEYS",   0.0,0.0,0.52,0.0, 0.75,0.6,0.0,0.55,0.20,0.0,0.45,0.0, 0.02,0.45,0.4, 0.20, 0.02,0.4,0.3),
        P("RESO PLUCK",  0.0,0.0,0.50,0.0, 0.85,0.0,0.0,0.45,0.65,0.0,0.70,0.0, 0.01,0.3,0.0,  0.20, 0.01,0.3,0.0),
        P("WOBBLE PAD",  0.8,0.0,0.53,0.0, 0.7,0.6,0.0, 0.50,0.25,0.0,0.40,0.0, 0.40,0.6,0.85, 0.10, 0.40,0.6,0.6),
        P("SYNC SWEEP",  0.6,0.6,0.46,1.0, 0.85,0.5,0.0,0.55,0.35,0.0,0.70,0.0, 0.02,0.5,0.6,  0.18, 0.02,0.7,0.3),
        P("HOLLOW",      1.0,1.0,0.54,0.0, 0.7,0.7,0.0, 0.50,0.25,0.5,0.40,0.0, 0.30,0.5,0.7,  0.20, 0.30,0.5,0.6),
        P("WIND",        0.0,0.0,0.52,0.0, 0.0,0.0,0.9, 0.55,0.40,0.5,0.50,1.0, 0.30,0.6,0.6,  0.30, 0.20,0.5,0.4),
        P("BRASS",       0.0,0.0,0.53,0.0, 0.75,0.7,0.0,0.55,0.25,0.0,0.55,0.0, 0.10,0.5,0.6,  0.20, 0.06,0.5,0.6),
        P("SQUARE LEAD", 0.7,0.7,0.50,0.0, 0.8,0.7,0.0, 0.62,0.30,0.0,0.45,0.0, 0.02,0.45,0.7, 0.25, 0.02,0.5,0.7),
        P("DRONE",       0.0,0.0,0.55,0.0, 0.75,0.7,0.0,0.45,0.30,0.0,0.30,0.0, 0.6,0.7,0.85,  0.10, 0.6,0.7,0.85),
    };
    return c;
}

//==============================================================================
class SEMEditor  : public toi::PanelEditor
{
public:
    SEMEditor (juce::AudioProcessor& proc, juce::MidiKeyboardState& kb)
        : toi::PanelEditor (proc, kb, semConfig())
    {
        auto mk = [this] (const juce::String& id, const juce::String& label, std::vector<std::unique_ptr<toi::StyledKnob>>& dst, int style)
        {
            auto k = std::make_unique<toi::StyledKnob> (label, pal(), style);
            if (auto* prm = findParam (id)) k->attach (*prm);
            addAndMakeVisible (*k); dst.push_back (std::move (k));
        };
        // Style A (Pointed: bezel + cog + black ring + dome + outward WHITE TRIANGLE) = the MAJORITY:
        //   VCF (all 6), VCO FREQUENCY, MIXER, ENV 1, ENV 2, and the left column.
        // Style B (Spike: fine gear + flat black disc + large outward BLACK SPIKE) = ONLY
        //   the VCO WAVE/MOD/PULSE-WIDTH knobs and the LFO knobs.
        auto knob    = [&mk] (const juce::String& id, const juce::String& label, std::vector<std::unique_ptr<toi::StyledKnob>>& dst) { mk (id, label, dst, toi::StyledKnob::Pointed); };
        auto bigKnob = [&mk] (const juce::String& id, const juce::String& label, std::vector<std::unique_ptr<toi::StyledKnob>>& dst) { mk (id, label, dst, toi::StyledKnob::Pointed); };   // FREQUENCY/RESONANCE = larger via layout
        auto spike   = [&mk] (const juce::String& id, const juce::String& label, std::vector<std::unique_ptr<toi::StyledKnob>>& dst) { mk (id, label, dst, toi::StyledKnob::Spike); };
        auto sw = [this] (const juce::String& id) -> SemSwitch*
        { auto s = std::make_unique<SemSwitch> (pal()); s->bindTo (findParam (id)); addAndMakeVisible (*s); switches.push_back (std::move (s)); return switches.back().get(); };

        bigKnob ("v1tune","FREQUENCY",kV1); spike ("v1wave","WAVE",kV1); spike ("v1mod","MOD 1",kV1); spike ("v1pw","PULSE WIDTH",kV1);
        bigKnob ("v2tune","FREQUENCY",kV2); spike ("v2wave","WAVE",kV2); spike ("v2mod","MOD 2",kV2); spike ("v2pw","PULSE WIDTH",kV2);
        swSync = sw ("sync");
        bigKnob ("cutoff","FREQUENCY",kVcf); bigKnob ("reso","RESONANCE",kVcf);
        knob ("lfoCut","MOD",kVcf); knob ("mode","NOTCH",kVcf); knob ("filtEnv","ENV",kVcf); knob ("kbd","KBD",kVcf);
        swBp = sw ("bp");
        knob ("mix1","VCO 1",kMix); knob ("mix2","VCO 2",kMix); knob ("noise","NOISE",kMix);
        knob ("a1","ATTACK",kE1); knob ("d1","DECAY",kE1); knob ("s1","SUSTAIN",kE1);
        spike ("lfoRate","RATE",kLfo); spike ("lfoWave","WAVE",kLfo);
        knob ("a2","ATTACK",kE2); knob ("d2","DECAY",kE2); knob ("s2","SUSTAIN",kE2);
        knob ("glide","PORTAMENTO",kLeft); knob ("vibRate","VIB RATE",kLeft); knob ("vibAmt","VIB AMT",kLeft); knob ("volume","MASTER",kLeft);

        for (int i = 0; i < 16; ++i)
        { auto b = std::make_unique<SemPreset> (pal()); const int idx = i; b->onClick = [this, idx] { recallSlot (idx); }; addAndMakeVisible (*b); slots.push_back (std::move (b)); }
        rand_ = std::make_unique<toi::Button> ("RAND", pal());
        save_ = std::make_unique<toi::Button> ("SAVE", pal());
        rand_->onClick = [this] { doRandom(); rand_->flash(); };
        save_->onClick = [this] { saveSlot (activeSlot()); save_->flash(); };
        addAndMakeVisible (*rand_); addAndMakeVisible (*save_);
        finishSetup();
    }

protected:
    void setPresetActiveVisual (int idx) override { for (int i = 0; i < (int) slots.size(); ++i) slots[(size_t) i]->setActive (i == idx); }

    void box (juce::Graphics& g, juce::Rectangle<float> r, const juce::String& title, bool dashed = true)
    {
        g.setColour (sm::kCreamLo); g.fillRoundedRectangle (r, 5.0f);
        g.setColour (sm::kBrown.withAlpha (dashed ? 0.55f : 1.0f)); g.drawRoundedRectangle (r, 5.0f, 1.4f);
        g.setColour (sm::kText); g.setFont (toi::uiFont (9.5f, true).withExtraKerningFactor (0.04f));
        g.drawText (title, r.withTrimmedTop (3.0f).withHeight (13.0f), juce::Justification::centred);
    }

    void paintPanel (juce::Graphics& g, juce::Rectangle<float> panel) override
    {
        juce::ignoreUnused (panel);
        // left control column (darker cream block)
        g.setColour (sm::kCreamLo.darker (0.05f)); g.fillRoundedRectangle (rLeft, 6.0f);
        g.setColour (sm::kBrown); g.drawRoundedRectangle (rLeft, 6.0f, toi::THIN_STROKE);

        box (g, rV1, "VCO 1"); box (g, rV2, "VCO 2"); box (g, rVcf, "VCF");
        box (g, rMix, "MIXER"); box (g, rE1, "ENV 1  (VCA)"); box (g, rE2, "ENV 2");
        // LFO mini box
        g.setColour (sm::kText); g.setFont (toi::uiFont (8.0f, true)); g.drawText ("LFO", rLfoHdr, juce::Justification::centred);
        // left column group labels
        g.setColour (sm::kText); g.setFont (toi::uiFont (7.5f, true).withExtraKerningFactor (0.05f));
        g.drawText ("PORTAMENTO", rPortaHdr, juce::Justification::centred);
        g.drawText ("VIBRATO",    rVibHdr,   juce::Justification::centred);
        // switch labels
        g.setColour (sm::kText); g.setFont (toi::uiFont (6.5f, true));
        g.drawText ("SYNC", rSyncLbl, juce::Justification::centredTop);
        g.drawText ("BP",   rBpLbl,   juce::Justification::centredLeft);
        g.setColour (sm::kText.withAlpha (0.7f)); g.setFont (toi::uiFont (6.0f, true));
        g.drawText ("LP        HP", rNotchLbl, juce::Justification::centred);

        // brand + MODULE/SIZE in the left column header
        auto bh = rBrandHdr;
        drawViewLeds (g, bh.removeFromTop (18.0f));
        g.setColour (sm::kText); g.setFont (toi::uiFont (13.0f, true));
        g.drawText ("JW-SEM", bh.withHeight (15.0f), juce::Justification::centred);
        g.setColour (sm::kText.withAlpha (0.65f)); g.setFont (toi::uiFont (5.5f, true).withExtraKerningFactor (0.2f));
        g.drawText ("TOI - plugin corp", bh.withTrimmedTop (14.0f).withHeight (8.0f), juce::Justification::centred);
    }

    void layoutPanel (juce::Rectangle<float> panel) override
    {
        rLeft = juce::Rectangle<float> (panel.getX(), panel.getY(), panel.getWidth() * 0.155f, panel.getHeight());
        auto main = juce::Rectangle<float> (rLeft.getRight() + 6.0f, panel.getY(), panel.getRight() - rLeft.getRight() - 6.0f, panel.getHeight());
        auto wordStrip = main.removeFromBottom (20.0f);
        // preset row + RAND/SAVE across the full bottom strip
        { auto pr = wordStrip.reduced (2.0f, 2.0f); auto rs = pr.removeFromRight (104.0f);
          placeInArtboard (*rand_, rs.removeFromLeft (46.0f).reduced (2.0f, 1.0f)); placeInArtboard (*save_, rs.reduced (2.0f, 1.0f));
          const float gap = 2.0f, cw = (pr.getWidth() - gap * 15.0f) / 16.0f;
          for (int i = 0; i < 16; ++i) placeInArtboard (*slots[(size_t) i], juce::Rectangle<float> (pr.getX() + i * (cw + gap), pr.getY(), cw, pr.getHeight()).reduced (0.0f, 1.0f)); }

        // VCF = full-height HERO section on the right; big knobs fill the space
        rVcf = main.removeFromRight (main.getWidth() * 0.40f);
        auto center = main;   // remaining left area
        {
            auto r = rVcf.reduced (12.0f, 0.0f).withTrimmedTop (20.0f).withTrimmedBottom (8.0f);
            auto t = r.removeFromTop (r.getHeight() * 0.5f);
            placeInArtboard (*kVcf[0], t.removeFromLeft (t.getWidth() * 0.5f).reduced (8.0f, 2.0f));   // FREQUENCY (big)
            placeInArtboard (*kVcf[1], t.reduced (8.0f, 2.0f));                                        // RESONANCE (big)
            const float kw = r.getWidth() / 4.0f;
            for (int i = 0; i < 4; ++i) placeInArtboard (*kVcf[(size_t) (2 + i)], juce::Rectangle<float> (r.getX() + i * kw, r.getY(), kw, r.getHeight()).reduced (4.0f, 2.0f));
            rNotchLbl = juce::Rectangle<float> (rVcf.getX() + 10.0f, r.getBottom() - 1.0f, kw - 6.0f, 8.0f);
            placeInArtboard (*swBp, juce::Rectangle<float> (rVcf.getRight() - 24.0f, rVcf.getY() + 20.0f, 16.0f, 24.0f));
            rBpLbl = juce::Rectangle<float> (rVcf.getRight() - 46.0f, rVcf.getY() + 26.0f, 18.0f, 9.0f);
        }

        // CENTER: VCO1 | VCO2 (top), MIXER | ENV1 | LFO | ENV2 (bottom)
        const float ctopH = (center.getHeight() - 6.0f) * 0.54f;
        auto ctop = center.withHeight (ctopH);
        auto cbot = center.withTrimmedTop (ctopH + 6.0f);
        rV1 = juce::Rectangle<float> (ctop.getX(), ctop.getY(), ctop.getWidth() * 0.46f, ctop.getHeight());
        rV2 = juce::Rectangle<float> (rV1.getRight() + 20.0f, ctop.getY(), ctop.getRight() - rV1.getRight() - 20.0f, ctop.getHeight());
        placeInArtboard (*swSync, juce::Rectangle<float> (rV1.getRight() + 3.0f, ctop.getCentreY() - 12.0f, 15.0f, 24.0f));
        rSyncLbl = juce::Rectangle<float> (rV1.getRight() - 4.0f, ctop.getCentreY() - 23.0f, 26.0f, 9.0f);
        layoutVco (kV1, rV1);
        layoutVco (kV2, rV2);

        rMix = juce::Rectangle<float> (cbot.getX(), cbot.getY(), cbot.getWidth() * 0.24f, cbot.getHeight());
        rE1  = juce::Rectangle<float> (rMix.getRight() + 5.0f, cbot.getY(), cbot.getWidth() * 0.30f, cbot.getHeight());
        auto lfoCol = juce::Rectangle<float> (rE1.getRight() + 5.0f, cbot.getY(), cbot.getWidth() * 0.14f, cbot.getHeight());
        rE2  = juce::Rectangle<float> (lfoCol.getRight() + 5.0f, cbot.getY(), cbot.getRight() - lfoCol.getRight() - 5.0f, cbot.getHeight());
        gridRow (kMix, rMix.reduced (6,4).withTrimmedTop (15.0f), 3);
        gridRow (kE1,  rE1.reduced (6,4).withTrimmedTop (15.0f), 3);
        gridRow (kE2,  rE2.reduced (6,4).withTrimmedTop (15.0f), 3);
        rLfoHdr = lfoCol.withHeight (12.0f);
        gridRow (kLfo, lfoCol.reduced (4,4).withTrimmedTop (13.0f), 1);

        // LEFT column: brand header + PORTAMENTO + VIBRATO(rate/amt) + MASTER
        rBrandHdr = rLeft.withTrimmedTop (5.0f).withHeight (40.0f).reduced (4.0f, 0.0f);
        auto col = rLeft.withTrimmedTop (48.0f).reduced (8.0f, 2.0f);
        const float ch = col.getHeight() / 3.0f;
        rPortaHdr = col.withHeight (10.0f);
        placeInArtboard (*kLeft[0], juce::Rectangle<float> (col.getX(), col.getY() + 9.0f, col.getWidth(), ch - 12.0f).reduced (col.getWidth() * 0.18f, 0.0f));
        auto vibR = juce::Rectangle<float> (col.getX(), col.getY() + ch, col.getWidth(), ch);
        rVibHdr = vibR.withHeight (10.0f);
        placeInArtboard (*kLeft[1], juce::Rectangle<float> (vibR.getX(), vibR.getY() + 9.0f, vibR.getWidth() * 0.5f, vibR.getHeight() - 11.0f).reduced (2.0f, 0.0f));
        placeInArtboard (*kLeft[2], juce::Rectangle<float> (vibR.getCentreX(), vibR.getY() + 9.0f, vibR.getWidth() * 0.5f, vibR.getHeight() - 11.0f).reduced (2.0f, 0.0f));
        placeInArtboard (*kLeft[3], juce::Rectangle<float> (col.getX(), col.getY() + 2.0f * ch + 2.0f, col.getWidth(), ch - 4.0f).reduced (col.getWidth() * 0.18f, 0.0f));
    }

private:
    void layoutVco (std::vector<std::unique_ptr<toi::StyledKnob>>& v, juce::Rectangle<float> sec)
    {
        auto r = sec.reduced (6.0f, 0.0f).withTrimmedTop (16.0f).withTrimmedBottom (4.0f);
        auto freq = r.removeFromTop (r.getHeight() * 0.46f);
        placeInArtboard (*v[0], freq.reduced (freq.getWidth() * 0.22f, 2.0f));   // FREQUENCY (big)
        const float kw = r.getWidth() / 3.0f;
        for (int i = 0; i < 3; ++i) placeInArtboard (*v[(size_t) (1 + i)], juce::Rectangle<float> (r.getX() + i * kw, r.getY(), kw, r.getHeight()).reduced (3.0f, 2.0f));
    }
    void gridRow (std::vector<std::unique_ptr<toi::StyledKnob>>& v, juce::Rectangle<float> r, int cols)
    {
        const int n = (int) v.size(); if (n == 0) return;
        const int rows = (n + cols - 1) / cols;
        const float cw = r.getWidth() / (float) cols, rh = r.getHeight() / (float) rows;
        for (int i = 0; i < n; ++i) { const int col = i % cols, row = i / cols;
            placeInArtboard (*v[(size_t) i], juce::Rectangle<float> (r.getX() + col * cw, r.getY() + row * rh, cw, rh).reduced (3.0f, 2.0f)); }
    }

    std::vector<std::unique_ptr<toi::StyledKnob>> kV1, kV2, kVcf, kMix, kE1, kLfo, kE2, kLeft;
    std::vector<std::unique_ptr<SemSwitch>>       switches;
    SemSwitch *swSync = nullptr, *swBp = nullptr;
    std::vector<std::unique_ptr<SemPreset>>       slots;
    std::unique_ptr<toi::Button> rand_, save_;
    juce::Rectangle<float> rLeft, rV1, rV2, rVcf, rMix, rE1, rE2, rBrandHdr,
                           rLfoHdr, rPortaHdr, rVibHdr, rSyncLbl, rBpLbl, rNotchLbl;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SEMEditor)
};

//==============================================================================
class SemPlugin  : public cmaj::plugin::GeneratedPlugin<::SEM>,
                   public toi::AudioTapSource,
                   public toi::PresetStore
{
public:
    using Base = cmaj::plugin::GeneratedPlugin<::SEM>;
    SemPlugin (std::shared_ptr<cmaj::Patch> p) : Base (std::move (p)) {}
    juce::AudioProcessorEditor* createEditor() override { return new SEMEditor (*this, keyboardState); }
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
