// JW-5P native faceplate (vintage 5-voice analog poly look) on the toi_faceplate.h kit.
// Built on toi::PanelEditor -> inherits 1300x477 size, single frame, 15-key keyboard,
// MODULE/SIZE, presets + snapshot. LIGHT-WALNUT WOOD cabinet framing a BLACK inner control
// panel: white section outlines + white labels, RED-LED rocker switches, BLACK line-pointer
// knobs (StyledKnob::LineKnob) with a printed 0..10 numeral ring, and two brushed-SILVER knobs
// (MASTER TUNE + VOLUME). Bottom PROGRAMMER strip = grey domed preset buttons (red LED when
// active) + RAND/SAVE. NO colour inside the panel. TOI name JW-5P (no brand names).
// EVERY control is functional (incl. the new MASTER TUNE param).
#pragma once

#include "toi_faceplate.h"

struct P5;

namespace p5
{
    static const juce::Colour kWood   { 0xff9c6a3c };   // light walnut cabinet face (lighter than JW-MINI)
    static const juce::Colour kWoodLo { 0xff7a4f2a };   // darker walnut (gradient toward edges)
    static const juce::Colour kPanel  { 0xff121214 };   // black inner control panel
    static const juce::Colour kBox    { 0xff161618 };   // section box fill (a touch above panel)
    static const juce::Colour kFrame  { 0xff050506 };   // near-black frame + outlines
    static const juce::Colour kInk    { 0xff050506 };   // outline ink
    static const juce::Colour kWhite  { 0xfff0f0f2 };   // screened white labels / outlines
    static const juce::Colour kWhiteDim{ 0xffbdbdc0 };
    static const juce::Colour kRed    { 0xffd23b2e };   // red rocker / preset LED
}

//==============================================================================
// Small black rocker switch with a RED LED that lights when ON (bound to a 0..1 param).
class P5Switch  : public juce::Component
{
public:
    explicit P5Switch (const toi::Palette&) {}
    void bindTo (juce::AudioProcessorParameter* p)
    { param_ = p; if (! p) return; slider.setRange (0.0, 1.0, 0.0); attach = std::make_unique<toi::ParamKnobAttachment> (*p, slider); addChildComponent (slider); slider.setVisible (false); }
    bool on() const { return (param_ ? param_->getValue() : (float) slider.getValue()) >= 0.5f; }
    void mouseDown (const juce::MouseEvent&) override { slider.setValue (on() ? 0.0 : 1.0, juce::sendNotificationSync); repaint(); }
    void paint (juce::Graphics& g) override
    {
        auto b = getLocalBounds().toFloat().reduced (1.0f);
        const bool o = on();
        // black rocker body
        juce::ColourGradient bg (juce::Colour (0xff2a2a2d), b.getCentreX(), b.getY(),
                                 juce::Colour (0xff0c0c0e), b.getCentreX(), b.getBottom(), false);
        g.setGradientFill (bg); g.fillRoundedRectangle (b, 2.5f);
        g.setColour (p5::kFrame); g.drawRoundedRectangle (b, 2.5f, 1.0f);
        // red LED near the top, lit when ON
        const float d = juce::jmin (b.getWidth(), b.getHeight()) * 0.42f;
        auto led = juce::Rectangle<float> (0, 0, d, d).withCentre ({ b.getCentreX(), b.getY() + d * 0.85f });
        g.setColour (o ? p5::kRed.brighter (0.25f) : juce::Colour (0xff3a1413));
        g.fillEllipse (led);
        if (o) { g.setColour (p5::kRed.brighter (0.7f).withAlpha (0.6f)); g.fillEllipse (led.reduced (d * 0.28f)); }
        g.setColour (juce::Colours::black.withAlpha (0.6f)); g.drawEllipse (led, 0.8f);
    }
private:
    juce::Slider slider; std::unique_ptr<toi::ParamKnobAttachment> attach; juce::AudioProcessorParameter* param_ = nullptr;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (P5Switch)
};

//==============================================================================
// Programmer preset button: grey, slightly-domed square with a small RED LED near the top
// (LED lit/bright when this preset is the active slot).
class P5Preset  : public juce::Button
{
public:
    explicit P5Preset (const toi::Palette&) : juce::Button ("preset") {}
    void setActive (bool a) { if (active != a) { active = a; repaint(); } }
    void paintButton (juce::Graphics& g, bool over, bool down) override
    {
        auto b = getLocalBounds().toFloat().reduced (1.0f);
        // grey domed cap (brighter top-left -> darker bottom)
        const float base = over ? 0.10f : 0.0f;
        juce::ColourGradient cap (juce::Colour (0xff9a9a9e).brighter (base), b.getCentreX(), b.getY(),
                                  juce::Colour (0xff5c5c60), b.getCentreX(), b.getBottom(), false);
        g.setGradientFill (cap); g.fillRoundedRectangle (b, 2.2f);
        if (down) { g.setColour (juce::Colours::black.withAlpha (0.18f)); g.fillRoundedRectangle (b, 2.2f); }
        // bevel: light top edge, dark bottom edge
        g.setColour (juce::Colours::white.withAlpha (0.30f)); g.drawLine (b.getX() + 1.5f, b.getY() + 1.0f, b.getRight() - 1.5f, b.getY() + 1.0f, 1.0f);
        g.setColour (juce::Colours::black.withAlpha (0.45f)); g.drawRoundedRectangle (b, 2.2f, 1.0f);
        // small red LED dot near the top
        const float d = juce::jmin (b.getWidth(), b.getHeight()) * 0.30f;
        auto led = juce::Rectangle<float> (0, 0, d, d).withCentre ({ b.getCentreX(), b.getY() + d * 1.05f });
        g.setColour (active ? p5::kRed.brighter (0.3f) : juce::Colour (0xff401a18));
        g.fillEllipse (led);
        if (active) { g.setColour (p5::kRed.brighter (0.8f).withAlpha (0.7f)); g.fillEllipse (led.reduced (d * 0.3f)); }
        g.setColour (juce::Colours::black.withAlpha (0.55f)); g.drawEllipse (led, 0.6f);
    }
private:
    bool active = false;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (P5Preset)
};

//==============================================================================
inline toi::Config p5Config()
{
    toi::Config c;
    c.model = "JW-5P";
    auto& p = c.pal;
    p.bg = p5::kWood; p.bg2 = p5::kWoodLo; p.frame = p5::kFrame; p.ink = p5::kInk;
    p.accent = p5::kWhite; p.accent2 = p5::kRed; p.button = juce::Colour (0xff1a1b1e);
    p.thumb = juce::Colour (0xfff2f2f4); p.text = p5::kWhite;
    p.keyWhite = juce::Colour (0xffEDEDEA); p.keyWhitePr = juce::Colour (0xffc6d2ec);
    p.keyBlack = juce::Colour (0xff131316); p.keyBlackPr = juce::Colour (0xff3a4a6a);

    c.params = {
        { "lfoRate","RATE" }, { "lfoShape","SHAPE" }, { "lfoAmt","AMOUNT" },
        { "aFreq","FREQ" }, { "aShape","SHAPE" }, { "aPW","PULSE WIDTH" }, { "sync","SYNC" },
        { "bFreq","FREQ" }, { "bFine","FINE" }, { "bShape","SHAPE" }, { "bPW","PULSE WIDTH" }, { "bKbd","KBD" },
        { "pmEnv","FILT ENV" }, { "pmOscB","OSC B" }, { "pmFreqA","FREQ A" }, { "pmPwA","PW A" }, { "pmFilt","FILTER" },
        { "mixA","OSC A" }, { "mixB","OSC B" },
        { "cutoff","CUTOFF" }, { "reso","RESONANCE" }, { "filtEnvAmt","ENV AMT" }, { "kbdTrack","KBD" },
        { "fA","ATTACK" }, { "fD","DECAY" }, { "fS","SUSTAIN" }, { "fR","RELEASE" },
        { "aA","ATTACK" }, { "aD","DECAY" }, { "aS","SUSTAIN" }, { "aR","RELEASE" },
        { "glide","GLIDE" }, { "volume","VOLUME" }, { "tune","MASTER TUNE" },
    };

    // 16 classic poly patches. P() takes musical params; the order matches c.params above.
    // Param order: lfoRate,lfoShape,lfoAmt, aFreq,aShape,aPW,sync, bFreq,bFine,bShape,bPW,bKbd,
    //              pmEnv,pmOscB,pmFreqA,pmPwA,pmFilt, mixA,mixB, cutoff,reso,filtEnvAmt,kbdTrack,
    //              fA,fD,fS,fR, aA,aD,aS,aR, glide,volume,tune.  (tune stays centred at 0.5)
    auto P = [] (const char* nm,
                 float aShape,float aPW, float bFine,float bShape,float sync,
                 float pmEnv,float pmFreqA,float pmFilt,
                 float mixA,float mixB,
                 float cut,float res,float fenv,float kbd,
                 float fA,float fD,float fS,float fR,
                 float aA,float aD,float aS,float aR)
    {
        return toi::FactoryPreset { nm, { 0.30f,0.0f,0.0f,
                                          0.5f,aShape,aPW,sync, 0.5f,bFine,bShape,0.5f,1.0f,
                                          pmEnv,0.0f,pmFreqA,0.0f,pmFilt, mixA,mixB,
                                          cut,res,fenv,kbd, fA,fD,fS,fR, aA,aD,aS,aR, 0.0f,0.80f, 0.50f } };
    };
    c.factory = {
        //          aShp aPW  bFine bShp sync pmEnv pmFA pmFlt mixA mixB cut  res  fenv kbd  fA   fD   fS   fR   aA   aD   aS   aR
        P("BRASS",       0.0,0.5, 0.52,0.0,0.0, 0.0,0.0,0.0, 0.8,0.7, 0.45,0.25,0.55,0.5, 0.10,0.5,0.5,0.4, 0.06,0.5,0.7,0.4),
        P("STRINGS",     1.0,0.5, 0.54,1.0,0.0, 0.0,0.0,0.0, 0.7,0.7, 0.55,0.20,0.30,0.5, 0.45,0.6,0.85,0.6, 0.40,0.6,0.8,0.6),
        P("SYNC LEAD",   0.6,0.5, 0.40,0.0,1.0, 0.0,0.0,0.0, 0.85,0.6,0.70,0.30,0.55,0.6, 0.02,0.4,0.7,0.3, 0.02,0.5,0.8,0.25),
        P("POLY-MOD CLANG",0.0,0.5,0.46,0.0,0.0,0.6,1.0,0.0, 0.7,0.7, 0.55,0.35,0.50,0.5, 0.05,0.45,0.4,0.3,0.02,0.4,0.6,0.3),
        P("FAT BASS",    0.0,0.5, 0.49,0.0,0.0, 0.0,0.0,0.0, 0.8,0.75,0.40,0.30,0.55,0.4, 0.02,0.35,0.1,0.2,0.02,0.4,0.2,0.2),
        P("WARM PAD",    0.0,0.5, 0.53,0.5,0.0, 0.0,0.0,0.0, 0.7,0.7, 0.50,0.20,0.35,0.5, 0.50,0.6,0.85,0.7, 0.45,0.6,0.85,0.7),
        P("PWM ORGAN",   1.0,0.5, 0.50,1.0,0.0, 0.0,0.0,0.0, 0.7,0.7, 0.60,0.18,0.20,0.6, 0.02,0.45,0.85,0.3,0.02,0.45,0.85,0.3),
        P("SOFT KEYS",   0.0,0.5, 0.52,0.5,0.0, 0.0,0.0,0.0, 0.75,0.6,0.55,0.20,0.45,0.5, 0.02,0.45,0.4,0.4,0.02,0.45,0.4,0.4),
        P("RESO PLUCK",  0.0,0.5, 0.50,0.0,0.0, 0.0,0.0,0.0, 0.85,0.0,0.45,0.65,0.70,0.5, 0.01,0.3,0.0,0.2,0.01,0.3,0.0,0.2),
        P("OCTAVE LEAD", 0.7,0.5, 0.50,0.0,0.0, 0.0,0.0,0.0, 0.8,0.7, 0.62,0.30,0.45,0.7, 0.02,0.45,0.7,0.3,0.02,0.5,0.75,0.3),
        P("PM SWEEP",    0.0,0.5, 0.50,0.0,0.0, 0.8,0.0,1.0, 0.75,0.5,0.45,0.40,0.60,0.5, 0.10,0.7,0.4,0.4,0.05,0.5,0.7,0.5),
        P("HOLLOW",      1.0,0.5, 0.54,1.0,0.0, 0.0,0.0,0.0, 0.7,0.7, 0.50,0.25,0.40,0.5, 0.30,0.5,0.7,0.5,0.30,0.5,0.7,0.5),
        P("SYNC SWEEP",  0.6,0.5, 0.46,0.0,1.0, 0.0,0.0,0.0, 0.85,0.5,0.55,0.35,0.70,0.6, 0.02,0.6,0.6,0.4,0.02,0.7,0.5,0.4),
        P("BIG POLY",    0.0,0.5, 0.53,0.5,0.0, 0.0,0.0,0.0, 0.78,0.72,0.55,0.22,0.45,0.5,0.30,0.6,0.8,0.6,0.25,0.6,0.85,0.6),
        P("SQUARE LEAD", 0.7,0.5, 0.50,1.0,0.0, 0.0,0.0,0.0, 0.8,0.7, 0.62,0.30,0.45,0.6, 0.02,0.45,0.7,0.3,0.02,0.5,0.8,0.3),
        P("DRONE",       0.0,0.5, 0.55,0.0,0.0, 0.0,0.0,0.0, 0.75,0.7,0.45,0.30,0.30,0.5, 0.6,0.7,0.85,0.8,0.6,0.7,0.85,0.8),
    };
    return c;
}

//==============================================================================
class P5Editor  : public toi::PanelEditor
{
public:
    P5Editor (juce::AudioProcessor& proc, juce::MidiKeyboardState& kb)
        : toi::PanelEditor (proc, kb, p5Config())
    {
        // black line-pointer knob with a printed numeral ring (silver=metal cap for tune/volume).
        auto knob = [this] (const juce::String& id, const juce::String& label,
                            std::vector<std::unique_ptr<toi::StyledKnob>>& dst, bool silver = false, bool bipolar = false)
        {
            auto k = std::make_unique<toi::StyledKnob> (label, pal(), toi::StyledKnob::LineKnob);
            k->setSilver (silver); k->setBipolar (bipolar);
            if (auto* prm = findParam (id)) k->attach (*prm);
            addAndMakeVisible (*k); dst.push_back (std::move (k));
        };
        auto sw = [this] (const juce::String& id) -> P5Switch*
        { auto s = std::make_unique<P5Switch> (pal()); s->bindTo (findParam (id)); addAndMakeVisible (*s); switches.push_back (std::move (s)); return switches.back().get(); };

        knob ("lfoRate","RATE",kLfo); knob ("lfoShape","SHAPE",kLfo); knob ("lfoAmt","AMOUNT",kLfo);
        knob ("aFreq","FREQ",kOscA); knob ("aShape","SHAPE",kOscA); knob ("aPW","PULSE WIDTH",kOscA);
        swSync = sw ("sync");
        knob ("bFreq","FREQ",kOscB); knob ("bFine","FINE",kOscB); knob ("bShape","SHAPE",kOscB); knob ("bPW","PULSE WIDTH",kOscB);
        swKbd = sw ("bKbd");
        knob ("pmEnv","FILT ENV",kPoly); knob ("pmOscB","OSC B",kPoly);
        swFreqA = sw ("pmFreqA"); swPwA = sw ("pmPwA"); swFilt = sw ("pmFilt");
        knob ("mixA","OSC A",kMix); knob ("mixB","OSC B",kMix);
        knob ("cutoff","CUTOFF",kFilt); knob ("reso","RESONANCE",kFilt); knob ("filtEnvAmt","ENV AMT",kFilt); knob ("kbdTrack","KBD",kFilt);
        knob ("fA","ATTACK",kFEnv); knob ("fD","DECAY",kFEnv); knob ("fS","SUSTAIN",kFEnv); knob ("fR","RELEASE",kFEnv);
        knob ("aA","ATTACK",kAEnv); knob ("aD","DECAY",kAEnv); knob ("aS","SUSTAIN",kAEnv); knob ("aR","RELEASE",kAEnv);
        knob ("glide","GLIDE",kLeft);
        knob ("tune","MASTER TUNE",kLeft, /*silver*/ true, /*bipolar*/ true);   // silver bipolar 5..0..5
        knob ("volume","VOLUME",kLeft, /*silver*/ true);                         // silver 0..10
        for (auto& k : kLeft) k->setShowLabel (false);   // the group headers name these (no duplicate label)

        for (int i = 0; i < 16; ++i)
        { auto b = std::make_unique<P5Preset> (pal()); const int idx = i; b->onClick = [this, idx] { recallSlot (idx); }; addAndMakeVisible (*b); slots.push_back (std::move (b)); }
        rand_ = std::make_unique<toi::Button> ("RAND", pal());
        save_ = std::make_unique<toi::Button> ("SAVE", pal());
        rand_->onClick = [this] { doRandom(); rand_->flash(); };
        save_->onClick = [this] { saveSlot (activeSlot()); save_->flash(); };
        addAndMakeVisible (*rand_); addAndMakeVisible (*save_);
        finishSetup();
    }

protected:
    void setPresetActiveVisual (int idx) override { for (int i = 0; i < (int) slots.size(); ++i) slots[(size_t) i]->setActive (i == idx); }

    // white-outlined section box with a centred white title near the top edge
    void box (juce::Graphics& g, juce::Rectangle<float> r, const juce::String& title)
    {
        g.setColour (p5::kBox);    g.fillRoundedRectangle (r, 3.0f);
        g.setColour (p5::kWhite);  g.drawRoundedRectangle (r.reduced (0.5f), 3.0f, 1.2f);
        g.setColour (p5::kWhite);
        g.setFont (toi::uiFont (9.0f, true).withExtraKerningFactor (0.10f));
        g.drawText (title, r.withHeight (13.0f).withTrimmedTop (2.0f), juce::Justification::centred);
    }

    void paintPanel (juce::Graphics& g, juce::Rectangle<float> panel) override
    {
        // BLACK inner control panel inset within the wood cabinet (wood frames it on all sides)
        g.setColour (p5::kPanel); g.fillRoundedRectangle (rPanel, 6.0f);
        g.setColour (juce::Colours::black); g.drawRoundedRectangle (rPanel, 6.0f, 1.5f);
        // subtle inner highlight line so the black panel reads as inset metal
        g.setColour (juce::Colours::white.withAlpha (0.05f)); g.drawRoundedRectangle (rPanel.reduced (1.5f), 5.0f, 1.0f);
        juce::ignoreUnused (panel);

        box (g, rLfo,  "LFO");
        box (g, rOscA, "OSCILLATOR A");
        box (g, rOscB, "OSCILLATOR B");
        box (g, rPoly, "POLY-MOD");
        box (g, rMix,  "MIXER");
        box (g, rFilt, "FILTER");
        box (g, rFEnv, "FILTER ENVELOPE");
        box (g, rAEnv, "AMPLIFIER ENVELOPE");
        box (g, rGlob, "");

        // global-block group labels
        g.setColour (p5::kWhite); g.setFont (toi::uiFont (8.0f, true).withExtraKerningFactor (0.06f));
        g.drawText ("PORTAMENTO", rGlideHdr, juce::Justification::centred);
        g.drawText ("MASTER TUNE", rTuneHdr, juce::Justification::centred);
        g.drawText ("VOLUME",      rVolHdr,  juce::Justification::centred);

        // switch labels (white)
        g.setColour (p5::kWhite); g.setFont (toi::uiFont (6.5f, true));
        g.drawText ("SYNC",   rSyncLbl, juce::Justification::centred);
        g.drawText ("KBD",    rKbdLbl,  juce::Justification::centred);
        g.drawText ("FREQ A", rFreqALbl, juce::Justification::centred);
        g.drawText ("PW A",   rPwALbl,  juce::Justification::centred);
        g.drawText ("FILTER", rFiltLbl, juce::Justification::centred);
        g.setColour (p5::kWhiteDim); g.setFont (toi::uiFont (6.5f, true).withExtraKerningFactor (0.08f));
        g.drawText ("DESTINATIONS", rDestHdr, juce::Justification::centred);

        // PROGRAMMER strip label + frame
        g.setColour (p5::kWhite); g.drawRoundedRectangle (rProg, 3.0f, 1.0f);
        g.setColour (p5::kWhiteDim); g.setFont (toi::uiFont (7.0f, true).withExtraKerningFactor (0.12f));
        g.drawText ("PROGRAMMER", rProgLbl, juce::Justification::centredLeft);

        // brand on the wood, lower-right of the panel (like the cabinet badge), + MODULE/SIZE leds
        auto bh = rBrandHdr;
        drawViewLeds (g, bh.removeFromTop (18.0f));
        g.setColour (p5::kWhite); g.setFont (toi::uiFont (15.0f, true));
        g.drawText ("JW-5P", bh.withHeight (17.0f), juce::Justification::centred);
        g.setColour (p5::kWhiteDim); g.setFont (toi::uiFont (5.5f, true).withExtraKerningFactor (0.2f));
        g.drawText ("TOI - plugin corp", bh.withTrimmedTop (16.0f).withHeight (8.0f), juce::Justification::centred);
    }

    void layoutPanel (juce::Rectangle<float> panel) override
    {
        // black panel inset inside the wood cabinet: leave a wood margin on all four sides.
        rPanel = panel.reduced (16.0f, 10.0f);
        auto inner = rPanel.reduced (8.0f, 8.0f);

        // left global column (brand + portamento + master tune + volume), then main grid.
        rGlob = inner.removeFromLeft (inner.getWidth() * 0.125f);
        inner.removeFromLeft (8.0f);
        auto main = inner;

        // bottom PROGRAMMER strip across the main area
        rProg = main.removeFromBottom (30.0f);
        main.removeFromBottom (6.0f);
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

        // top row: LFO | OSC A | OSC B | POLY-MOD.  bottom row: MIXER | FILTER | FILTER ENV | AMP ENV.
        const float rowGap = 6.0f;
        const float topH = (main.getHeight() - rowGap) * 0.50f;
        auto top = main.withHeight (topH);
        auto bot = main.withTrimmedTop (topH + rowGap);

        const float colGap = 6.0f;
        const float twTotal = top.getWidth() - colGap * 3.0f;
        rLfo  = juce::Rectangle<float> (top.getX(), top.getY(), twTotal * 0.18f, top.getHeight());
        rOscA = juce::Rectangle<float> (rLfo.getRight() + colGap, top.getY(), twTotal * 0.26f, top.getHeight());
        rOscB = juce::Rectangle<float> (rOscA.getRight() + colGap, top.getY(), twTotal * 0.30f, top.getHeight());
        rPoly = juce::Rectangle<float> (rOscB.getRight() + colGap, top.getY(), top.getRight() - rOscB.getRight() - colGap, top.getHeight());

        gridRow (kLfo, rLfo.reduced (6.0f, 4.0f).withTrimmedTop (16.0f), 3);

        // OSC A: 3 knobs + SYNC rocker
        { auto r = rOscA.reduced (6.0f, 4.0f).withTrimmedTop (16.0f);
          auto swCol = r.removeFromRight (24.0f);
          gridRow (kOscA, r, 3);
          placeInArtboard (*swSync, juce::Rectangle<float> (swCol.getCentreX() - 8.0f, swCol.getCentreY() - 14.0f, 16.0f, 24.0f));
          rSyncLbl = juce::Rectangle<float> (swCol.getX() - 4.0f, swCol.getCentreY() + 11.0f, swCol.getWidth() + 8.0f, 9.0f); }

        // OSC B: 4 knobs + KBD rocker
        { auto r = rOscB.reduced (6.0f, 4.0f).withTrimmedTop (16.0f);
          auto swCol = r.removeFromRight (24.0f);
          gridRow (kOscB, r, 4);
          placeInArtboard (*swKbd, juce::Rectangle<float> (swCol.getCentreX() - 8.0f, swCol.getCentreY() - 14.0f, 16.0f, 24.0f));
          rKbdLbl = juce::Rectangle<float> (swCol.getX() - 4.0f, swCol.getCentreY() + 11.0f, swCol.getWidth() + 8.0f, 9.0f); }

        // POLY-MOD: 2 source knobs (top) + 3 destination rockers (bottom)
        { auto r = rPoly.reduced (6.0f, 4.0f).withTrimmedTop (16.0f);
          auto kr = r.removeFromTop (r.getHeight() * 0.58f);
          gridRow (kPoly, kr, 2);
          rDestHdr = juce::Rectangle<float> (r.getX(), r.getY() - 1.0f, r.getWidth(), 9.0f);
          auto dr = r.withTrimmedTop (10.0f).withTrimmedBottom (2.0f);
          const float dw = dr.getWidth() / 3.0f;
          const float swH = 18.0f;
          placeInArtboard (*swFreqA, juce::Rectangle<float> (dr.getX() + dw * 0.5f - 8.0f, dr.getY(), 16.0f, swH));
          placeInArtboard (*swPwA,   juce::Rectangle<float> (dr.getX() + dw * 1.5f - 8.0f, dr.getY(), 16.0f, swH));
          placeInArtboard (*swFilt,  juce::Rectangle<float> (dr.getX() + dw * 2.5f - 8.0f, dr.getY(), 16.0f, swH));
          const float lblY = dr.getY() + swH + 1.0f;
          rFreqALbl = juce::Rectangle<float> (dr.getX(),            lblY, dw, 9.0f);
          rPwALbl   = juce::Rectangle<float> (dr.getX() + dw,       lblY, dw, 9.0f);
          rFiltLbl  = juce::Rectangle<float> (dr.getX() + dw * 2.0f,lblY, dw, 9.0f); }

        // ---- bottom row widths ----
        const float bwTotal = bot.getWidth() - colGap * 3.0f;
        rMix  = juce::Rectangle<float> (bot.getX(), bot.getY(), bwTotal * 0.14f, bot.getHeight());
        rFilt = juce::Rectangle<float> (rMix.getRight() + colGap, bot.getY(), bwTotal * 0.30f, bot.getHeight());
        rFEnv = juce::Rectangle<float> (rFilt.getRight() + colGap, bot.getY(), bwTotal * 0.28f, bot.getHeight());
        rAEnv = juce::Rectangle<float> (rFEnv.getRight() + colGap, bot.getY(), bot.getRight() - rFEnv.getRight() - colGap, bot.getHeight());

        gridRow (kMix,  rMix.reduced (6.0f, 4.0f).withTrimmedTop (16.0f), 1);
        gridRow (kFilt, rFilt.reduced (6.0f, 4.0f).withTrimmedTop (16.0f), 4);
        gridRow (kFEnv, rFEnv.reduced (6.0f, 4.0f).withTrimmedTop (16.0f), 4);
        gridRow (kAEnv, rAEnv.reduced (6.0f, 4.0f).withTrimmedTop (16.0f), 4);

        // LEFT global column: brand badge + PORTAMENTO + MASTER TUNE + VOLUME knobs
        rBrandHdr = rGlob.withHeight (40.0f).reduced (4.0f, 2.0f);
        auto col = rGlob.withTrimmedTop (44.0f).reduced (4.0f, 2.0f);
        const float ch = col.getHeight() / 3.0f;
        rGlideHdr = col.withHeight (11.0f);
        placeInArtboard (*kLeft[0], juce::Rectangle<float> (col.getX(), col.getY() + 10.0f, col.getWidth(), ch - 12.0f).reduced (col.getWidth() * 0.06f, 0.0f));
        rTuneHdr = juce::Rectangle<float> (col.getX(), col.getY() + ch, col.getWidth(), 11.0f);
        placeInArtboard (*kLeft[1], juce::Rectangle<float> (col.getX(), col.getY() + ch + 10.0f, col.getWidth(), ch - 12.0f).reduced (col.getWidth() * 0.06f, 0.0f));
        rVolHdr = juce::Rectangle<float> (col.getX(), col.getY() + 2.0f * ch, col.getWidth(), 11.0f);
        placeInArtboard (*kLeft[2], juce::Rectangle<float> (col.getX(), col.getY() + 2.0f * ch + 10.0f, col.getWidth(), ch - 12.0f).reduced (col.getWidth() * 0.06f, 0.0f));
    }

private:
    void gridRow (std::vector<std::unique_ptr<toi::StyledKnob>>& v, juce::Rectangle<float> r, int cols)
    {
        const int n = (int) v.size(); if (n == 0) return;
        const int rows = (n + cols - 1) / cols;
        const float cw = r.getWidth() / (float) cols, rh = r.getHeight() / (float) rows;
        for (int i = 0; i < n; ++i) { const int col = i % cols, row = i / cols;
            placeInArtboard (*v[(size_t) i], juce::Rectangle<float> (r.getX() + col * cw, r.getY() + row * rh, cw, rh).reduced (2.0f, 1.0f)); }
    }

    std::vector<std::unique_ptr<toi::StyledKnob>> kLfo, kOscA, kOscB, kPoly, kMix, kFilt, kFEnv, kAEnv, kLeft;
    std::vector<std::unique_ptr<P5Switch>>        switches;
    P5Switch *swSync = nullptr, *swKbd = nullptr, *swFreqA = nullptr, *swPwA = nullptr, *swFilt = nullptr;
    std::vector<std::unique_ptr<P5Preset>>        slots;
    std::unique_ptr<toi::Button> rand_, save_;
    juce::Rectangle<float> rPanel, rGlob, rLfo, rOscA, rOscB, rPoly, rMix, rFilt, rFEnv, rAEnv, rBrandHdr,
                           rGlideHdr, rTuneHdr, rVolHdr, rSyncLbl, rKbdLbl, rFreqALbl, rPwALbl, rFiltLbl, rDestHdr,
                           rProg, rProgLbl;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (P5Editor)
};

//==============================================================================
class P5Plugin  : public cmaj::plugin::GeneratedPlugin<::P5>,
                  public toi::AudioTapSource,
                  public toi::PresetStore
{
public:
    using Base = cmaj::plugin::GeneratedPlugin<::P5>;
    P5Plugin (std::shared_ptr<cmaj::Patch> p) : Base (std::move (p)) {}
    juce::AudioProcessorEditor* createEditor() override { return new P5Editor (*this, keyboardState); }
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
