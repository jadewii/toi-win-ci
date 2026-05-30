// JW-MINI native faceplate (Minimoog Model D look) on the toi_faceplate.h kit.
// Built on toi::PanelEditor -> inherits the 1300x477 size, single-frame chassis,
// 15-key keyboard, TOI brand + MODULE/SIZE, presets + snapshot (matches the JW-CZ series).
// WOOD cabinet + black control plate + silver Metal knobs + blue/orange rocker switches.
// Changed vs the real Minimoog so it's not identical: wood top band carries TOI brand +
// preset bank, our palette, our section grouping. EVERY control is functional.
#pragma once

#include "toi_faceplate.h"

struct Mini;

namespace mn   // JW-MINI palette
{
    static const juce::Colour kWood   { 0xff6f4a2c };   // walnut cabinet face
    static const juce::Colour kWoodLo { 0xff513620 };   // darker walnut (gradient / edges)
    static const juce::Colour kPlate  { 0xff1b1b1e };   // black control plate
    static const juce::Colour kInk    { 0xff111012 };   // outlines / frame edge
    static const juce::Colour kSilver { 0xffb8bcc1 };   // metal knob body
    static const juce::Colour kBlue   { 0xff4f93b3 };   // rocker (mixer / on)
    static const juce::Colour kOrange { 0xffd0531f };   // rocker (osc3 ctl / mod) + MODULE led
    static const juce::Colour kCream  { 0xffece7da };   // panel text
}

//==============================================================================
// Minimoog-style rocker switch: a coloured paddle in a recessed well, bound to a
// 0..1 param (>=0.5 = ON). Click toggles. Lit highlight shows the ON side.
class MiniSwitch  : public juce::Component
{
public:
    MiniSwitch (juce::Colour c, const toi::Palette& pal) : col (c), ink (pal.ink) {}
    void bindTo (juce::AudioProcessorParameter* p)
    {
        param_ = p; if (! p) return;
        slider.setRange (0.0, 1.0, 0.0);
        attach = std::make_unique<toi::ParamKnobAttachment> (*p, slider);
        addChildComponent (slider); slider.setVisible (false);
    }
    bool on() const { return (param_ ? param_->getValue() : (float) slider.getValue()) >= 0.5f; }
    void mouseDown (const juce::MouseEvent&) override
    { slider.setValue (on() ? 0.0 : 1.0, juce::sendNotificationSync); repaint(); }
    void paint (juce::Graphics& g) override
    {
        auto b = getLocalBounds().toFloat().reduced (1.0f);
        g.setColour (juce::Colour (0xff0c0c0d)); g.fillRoundedRectangle (b, 2.5f);          // recessed well
        g.setColour (ink); g.drawRoundedRectangle (b, 2.5f, 1.2f);
        auto pad = b.reduced (1.6f);
        const bool o = on();
        g.setColour (o ? col : col.darker (0.45f)); g.fillRoundedRectangle (pad, 2.0f);     // coloured paddle
        // lit sliver on the ON end (top) / dim notch (bottom) shows position
        auto lit = (o ? pad.removeFromTop (pad.getHeight() * 0.4f) : pad.removeFromBottom (pad.getHeight() * 0.4f));
        g.setColour (o ? col.brighter (0.5f) : juce::Colours::black.withAlpha (0.35f));
        g.fillRoundedRectangle (lit.reduced (1.0f, 0.5f), 1.5f);
    }
private:
    juce::Colour col, ink; juce::Slider slider;
    std::unique_ptr<toi::ParamKnobAttachment> attach;
    juce::AudioProcessorParameter* param_ = nullptr;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MiniSwitch)
};

//==============================================================================
// Compact preset chip for the top wood band (lit cream when active).
class MiniPreset  : public juce::Button
{
public:
    explicit MiniPreset (const toi::Palette& p) : juce::Button ("preset"), pal (p) {}
    void setActive (bool a) { if (active != a) { active = a; repaint(); } }
    void paintButton (juce::Graphics& g, bool over, bool down) override
    {
        auto b = getLocalBounds().toFloat().reduced (1.0f);
        juce::ignoreUnused (down);
        g.setColour (active ? mn::kCream : (over ? juce::Colour (0xff5a3f26) : juce::Colour (0xff3a2a1a)));
        g.fillRoundedRectangle (b, 2.0f);
        g.setColour (mn::kInk); g.drawRoundedRectangle (b, 2.0f, 1.0f);
        if (active) { g.setColour (mn::kOrange); g.fillRoundedRectangle (b.withSizeKeepingCentre (b.getWidth() * 0.5f, 2.5f).withY (b.getY() + 1.5f), 1.0f); }
    }
private:
    toi::Palette pal; bool active = false;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MiniPreset)
};

//==============================================================================
inline toi::Config miniConfig()
{
    toi::Config c;
    c.model = "JW-MINI";
    auto& p = c.pal;
    p.bg        = mn::kWood;
    p.bg2       = mn::kWoodLo;          // wood gradient
    p.frame     = mn::kInk;
    p.ink       = mn::kInk;
    p.accent    = mn::kBlue;            // knob value-arc (subtle)
    p.accent2   = mn::kOrange;          // MODULE led
    p.button    = mn::kSilver;          // Metal knob body
    p.thumb     = juce::Colour (0xfff4f4f4);   // bright knob pointer
    p.text      = mn::kCream;           // labels (on black plate)
    p.keyWhite  = juce::Colour (0xfff0ece0);
    p.keyWhitePr= juce::Colour (0xffbcd6ea);
    p.keyBlack  = juce::Colour (0xff1d1d1f);   // authentic black keys
    p.keyBlackPr= mn::kBlue;

    // ids MUST match Mini.cmajor endpoints. (this order = factory-preset value order)
    c.params = {
        { "o1Wave","O1 WAVE" }, { "o1Oct","O1 OCT" },
        { "o2Wave","O2 WAVE" }, { "o2Oct","O2 OCT" }, { "o2Det","O2 TUNE" },
        { "o3Wave","O3 WAVE" }, { "o3Oct","O3 OCT" }, { "o3Det","O3 TUNE" }, { "o3Lfo","O3 CTL" },
        { "lvl1","OSC 1" }, { "lvl2","OSC 2" }, { "lvl3","OSC 3" }, { "noise","NOISE" }, { "drive","DRIVE" },
        { "cutoff","CUTOFF" }, { "reso","EMPHASIS" }, { "envAmt","CONTOUR" }, { "kbd","KBD TRK" },
        { "fAtk","F ATK" }, { "fDec","F DEC" }, { "fSus","F SUS" },
        { "aAtk","A ATK" }, { "aDec","A DEC" }, { "aSus","A SUS" },
        { "glide","GLIDE" },
        { "on1","OSC1" }, { "on2","OSC2" }, { "on3","OSC3" }, { "noiseCol","W/P" }, { "volume","VOLUME" },
        { "filtModOn","F-MOD" }, { "filtModAmt","AMOUNT" },
    };

    // 16 factory patches. P() takes the musical params; the 5 structural ones
    // (on1,on2,on3,noiseCol,volume) default to {on,on,on,white,0.8}.
    auto P = [] (const char* nm,
                 float o1w,float o1o, float o2w,float o2o,float o2d, float o3w,float o3o,float o3d,float o3l,
                 float l1,float l2,float l3,float nz,float dr,
                 float cut,float res,float env,float kb, float fa,float fd,float fs, float aa,float ad,float as, float gl)
    { return toi::FactoryPreset { nm, { o1w,o1o, o2w,o2o,o2d, o3w,o3o,o3d,o3l, l1,l2,l3,nz,dr,
                                        cut,res,env,kb, fa,fd,fs, aa,ad,as, gl, 1.0f,1.0f,1.0f,0.0f,0.80f, 0.0f,0.30f } }; };
    c.factory = {
        //       o1w  o1o  o2w  o2o  o2d  o3w  o3o  o3d  o3l   l1   l2   l3   nz   dr   cut  res  env  kb   fa   fd   fs   aa   ad   as   gl
        P("FAT BASS",    0.25,0.30, 0.25,0.30,0.53, 0.25,0.10,0.47,0.0, 0.85,0.80,0.55,0.0,0.55, 0.42,0.30,0.55,0.40, 0.02,0.40,0.10, 0.02,0.45,0.30,0.0),
        P("MOOG LEAD",   0.25,0.50, 0.25,0.50,0.55, 0.58,0.50,0.47,0.0, 0.80,0.75,0.60,0.0,0.45, 0.60,0.35,0.45,0.70, 0.04,0.50,0.70, 0.02,0.60,0.85,0.10),
        P("SYNC-ish LD", 0.58,0.50, 0.25,0.70,0.58, 0.25,0.50,0.42,0.0, 0.85,0.70,0.50,0.0,0.55, 0.65,0.40,0.50,0.80, 0.02,0.40,0.60, 0.02,0.55,0.85,0.05),
        P("SUB BASS",    0.58,0.30, 0.25,0.30,0.50, 0.25,0.10,0.50,0.0, 0.90,0.20,0.85,0.0,0.40, 0.35,0.20,0.40,0.30, 0.02,0.35,0.05, 0.02,0.40,0.20,0.0),
        P("BRASS",       0.25,0.50, 0.25,0.50,0.54, 0.25,0.50,0.46,0.0, 0.80,0.75,0.55,0.0,0.40, 0.50,0.30,0.55,0.60, 0.10,0.55,0.55, 0.06,0.55,0.70,0.0),
        P("SQUARE LEAD", 0.58,0.50, 0.58,0.50,0.55, 0.58,0.50,0.47,0.0, 0.85,0.70,0.40,0.0,0.40, 0.62,0.30,0.45,0.70, 0.02,0.45,0.70, 0.02,0.55,0.85,0.0),
        P("GLIDE LEAD",  0.25,0.50, 0.25,0.50,0.55, 0.25,0.50,0.47,0.0, 0.85,0.75,0.55,0.0,0.45, 0.58,0.38,0.45,0.75, 0.03,0.50,0.75, 0.02,0.60,0.85,0.45),
        P("WOBBLE",      0.25,0.50, 0.25,0.30,0.53, 0.25,0.25,0.30,1.0, 0.85,0.80,0.55,0.0,0.50, 0.40,0.55,0.55,0.40, 0.02,0.45,0.40, 0.02,0.50,0.80,0.0),
        P("ACID-ish",    0.25,0.50, 0.0,0.50,0.50,  0.0,0.50,0.50,0.0,  0.90,0.0,0.0,0.0,0.55,   0.45,0.78,0.65,0.55, 0.01,0.30,0.0,  0.01,0.30,0.0, 0.0),
        P("NOISE PERC",  0.58,0.50, 0.58,0.50,0.55, 0.58,0.50,0.47,0.0, 0.30,0.30,0.0,0.85,0.40, 0.55,0.45,0.70,0.40, 0.01,0.20,0.0,  0.01,0.18,0.0, 0.0),
        P("HOLLOW PAD",  0.58,0.50, 0.58,0.30,0.56, 0.25,0.50,0.44,0.0, 0.75,0.70,0.65,0.0,0.35, 0.45,0.25,0.40,0.50, 0.45,0.60,0.70, 0.40,0.65,0.85,0.0),
        P("ORGAN-ish",   0.58,0.50, 0.58,0.70,0.50, 0.58,0.30,0.50,0.0, 0.80,0.75,0.75,0.0,0.30, 0.70,0.15,0.20,0.60, 0.01,0.30,0.95, 0.01,0.30,0.95,0.0),
        P("FUNK PLUCK",  0.25,0.50, 0.25,0.50,0.54, 0.58,0.50,0.46,0.0, 0.85,0.70,0.45,0.0,0.50, 0.55,0.50,0.65,0.65, 0.02,0.28,0.0,  0.02,0.32,0.15,0.0),
        P("RAW SAW",     0.25,0.50, 0.25,0.50,0.55, 0.25,0.50,0.45,0.0, 0.85,0.80,0.70,0.0,0.65, 0.75,0.20,0.35,0.70, 0.02,0.45,0.80, 0.02,0.55,0.90,0.0),
        P("DEEP DRONE",  0.08,0.30, 0.08,0.30,0.52, 0.08,0.10,0.50,0.0, 0.80,0.70,0.80,0.0,0.30, 0.40,0.30,0.30,0.30, 0.60,0.70,0.85, 0.60,0.75,0.90,0.0),
        P("SCREAM LEAD", 0.25,0.70, 0.58,0.50,0.57, 0.25,0.50,0.43,0.0, 0.85,0.80,0.60,0.0,0.70, 0.68,0.70,0.55,0.80, 0.02,0.45,0.75, 0.02,0.55,0.85,0.08),
    };
    return c;
}

//==============================================================================
class MiniEditor  : public toi::PanelEditor
{
public:
    MiniEditor (juce::AudioProcessor& proc, juce::MidiKeyboardState& kb)
        : toi::PanelEditor (proc, kb, miniConfig())
    {
        auto knob = [this] (const juce::String& id, const juce::String& label, std::vector<std::unique_ptr<toi::StyledKnob>>& dst)
        {
            auto k = std::make_unique<toi::StyledKnob> (label, pal(), toi::StyledKnob::Fluted);
            if (auto* prm = findParam (id)) k->attach (*prm);
            addAndMakeVisible (*k); dst.push_back (std::move (k));
        };
        auto sw = [this] (const juce::String& id, juce::Colour col)
        {
            auto s = std::make_unique<MiniSwitch> (col, pal()); s->bindTo (findParam (id));
            addAndMakeVisible (*s); switches.push_back (std::move (s)); return switches.back().get();
        };

        knob ("glide","GLIDE",kCtrl); knob ("drive","DRIVE",kCtrl);
        swO3 = sw ("o3Lfo", mn::kOrange);

        knob ("o1Oct","RANGE",kOsc); knob ("o1Wave","WAVE",kOsc);
        knob ("o2Oct","RANGE",kOsc); knob ("o2Wave","WAVE",kOsc); knob ("o2Det","TUNE",kOsc);
        knob ("o3Oct","RANGE",kOsc); knob ("o3Wave","WAVE",kOsc); knob ("o3Det","TUNE",kOsc);

        knob ("lvl1","OSC 1",kMix); knob ("lvl2","OSC 2",kMix); knob ("lvl3","OSC 3",kMix); knob ("noise","NOISE",kMix);
        sw ("on1", mn::kBlue); sw ("on2", mn::kBlue); sw ("on3", mn::kBlue); sw ("noiseCol", mn::kBlue);

        knob ("cutoff","CUTOFF",kMod); knob ("reso","EMPHASIS",kMod); knob ("envAmt","CONTOUR",kMod); knob ("kbd","KBD TRK",kMod);
        knob ("fAtk","ATTACK",kMod); knob ("fDec","DECAY",kMod); knob ("fSus","SUSTAIN",kMod);
        knob ("aAtk","ATTACK",kMod); knob ("aDec","DECAY",kMod); knob ("aSus","SUSTAIN",kMod);

        knob ("volume","VOLUME",kOut);

        // FILTER MODULATION (osc3/LFO -> cutoff) in the MODIFIERS open area
        knob ("filtModAmt","AMOUNT",kFmod);
        swFmod = sw ("filtModOn", mn::kOrange);

        for (int i = 0; i < 16; ++i)
        {
            auto b = std::make_unique<MiniPreset> (pal());
            const int idx = i; b->onClick = [this, idx] { recallSlot (idx); };
            addAndMakeVisible (*b); slots.push_back (std::move (b));
        }
        rand_ = std::make_unique<toi::Button> ("RAND", pal());
        save_ = std::make_unique<toi::Button> ("SAVE", pal());
        rand_->onClick = [this] { doRandom(); rand_->flash(); };
        save_->onClick = [this] { saveSlot (activeSlot()); save_->flash(); };
        addAndMakeVisible (*rand_); addAndMakeVisible (*save_);
        finishSetup();
    }

protected:
    void setPresetActiveVisual (int idx) override
    { for (int i = 0; i < (int) slots.size(); ++i) slots[(size_t) i]->setActive (i == idx); }

    void paintPanel (juce::Graphics& g, juce::Rectangle<float> panel) override
    {
        juce::ignoreUnused (panel);
        // black control plate
        g.setColour (mn::kPlate);  g.fillRoundedRectangle (rPlate, 6.0f);
        g.setColour (mn::kInk);    g.drawRoundedRectangle (rPlate, 6.0f, toi::THIN_STROKE);

        // section dividers + bottom labels (Minimoog style)
        const char* names[5] = { "CONTROLLERS", "OSCILLATOR BANK", "MIXER", "MODIFIERS", "OUTPUT" };
        g.setFont (toi::uiFont (9.0f, true).withExtraKerningFactor (0.12f));
        for (int i = 0; i < 5; ++i)
        {
            if (i > 0) { g.setColour (mn::kSilver.withAlpha (0.5f)); g.drawLine (secRect[i].getX(), rPlate.getY() + 6, secRect[i].getX(), rPlate.getBottom() - 6, 1.2f); }
            g.setColour (mn::kCream);
            g.drawText (names[i], secRect[i].withTop (rPlate.getBottom() - 18.0f).withTrimmedBottom (3.0f), juce::Justification::centred);
        }
        // small group labels on the plate
        g.setColour (mn::kCream.withAlpha (0.75f)); g.setFont (toi::uiFont (6.5f, true).withExtraKerningFactor (0.1f));
        g.drawText ("FILTER",     rFiltHdr,  juce::Justification::centred);
        g.drawText ("CONTOUR",    rEnvHdr,   juce::Justification::centred);
        g.drawText ("FILTER MOD", rFmodHdr,  juce::Justification::centred);

        // top wood band: TOI brand + MODULE/SIZE leds (left), presets are components on the right
        auto bh = rBrand;
        drawViewLeds (g, bh.removeFromTop (18.0f));
        g.setColour (mn::kCream); g.setFont (toi::uiFont (14.0f, true).withExtraKerningFactor (0.04f));
        g.drawText ("JW-MINI", bh.withHeight (15.0f), juce::Justification::centredLeft);
        g.setColour (mn::kCream.withAlpha (0.7f)); g.setFont (toi::uiFont (6.5f, true).withExtraKerningFactor (0.25f));
        g.drawText ("TOI - plugin corp", bh.withTrimmedTop (14.0f).withHeight (9.0f), juce::Justification::centredLeft);
    }

    void layoutPanel (juce::Rectangle<float> panel) override
    {
        // top wood band (brand + presets), then black plate below
        auto band = panel.withHeight (30.0f);
        rPlate = panel.withTrimmedTop (34.0f).reduced (8.0f, 0.0f).withTrimmedBottom (5.0f);

        rBrand = band.removeFromLeft (panel.getWidth() * 0.20f).reduced (8.0f, 2.0f);
        // preset bank (right of brand): 16 chips in 1 row + RAND/SAVE
        {
            auto pr = band.reduced (6.0f, 4.0f);
            auto rs = pr.removeFromRight (104.0f);
            placeInArtboard (*rand_, rs.removeFromLeft (50.0f).reduced (2.0f, 1.0f));
            placeInArtboard (*save_, rs.reduced (2.0f, 1.0f));
            const float gap = 3.0f, cw = (pr.getWidth() - gap * 15.0f) / 16.0f;
            for (int i = 0; i < 16; ++i)
                placeInArtboard (*slots[(size_t) i], juce::Rectangle<float> (pr.getX() + (float) i * (cw + gap), pr.getY(), cw, pr.getHeight()).reduced (0.0f, 1.0f));
        }

        // 5 sections across the plate
        const float frac[5] = { 0.13f, 0.27f, 0.17f, 0.31f, 0.12f };
        float x = rPlate.getX();
        for (int i = 0; i < 5; ++i) { secRect[i] = juce::Rectangle<float> (x, rPlate.getY(), rPlate.getWidth() * frac[i], rPlate.getHeight()); x += rPlate.getWidth() * frac[i]; }
        auto body = [] (juce::Rectangle<float> s) { return s.reduced (6.0f, 4.0f).withTrimmedBottom (16.0f); };   // leave room for bottom label

        // CONTROLLERS: GLIDE + DRIVE knobs (top), OSC3-CTL switch (bottom)
        {
            auto r = body (secRect[0]);
            auto top = r.removeFromTop (r.getHeight() * 0.62f);
            const float kw = top.getWidth() / 2.0f;
            placeInArtboard (*kCtrl[0], juce::Rectangle<float> (top.getX(), top.getY(), kw, top.getHeight()).reduced (3, 2));
            placeInArtboard (*kCtrl[1], juce::Rectangle<float> (top.getX() + kw, top.getY(), kw, top.getHeight()).reduced (3, 2));
            placeInArtboard (*swO3, juce::Rectangle<float> (r.getCentreX() - 9.0f, r.getY() + 2.0f, 18.0f, r.getHeight() - 4.0f));
        }
        // OSCILLATOR BANK: 3 rows (osc1: range/wave ; osc2/3: range/wave/tune)
        {
            auto r = body (secRect[1]);
            const float rh = r.getHeight() / 3.0f;
            placeRow (kOsc, 0, 2, juce::Rectangle<float> (r.getX(), r.getY(),            r.getWidth(), rh));
            placeRow (kOsc, 2, 3, juce::Rectangle<float> (r.getX(), r.getY() + rh,       r.getWidth(), rh));
            placeRow (kOsc, 5, 3, juce::Rectangle<float> (r.getX(), r.getY() + 2.0f*rh,  r.getWidth(), rh));
        }
        // MIXER: 4 level knobs (top), 4 switches (bottom)
        {
            auto r = body (secRect[2]);
            auto top = r.removeFromTop (r.getHeight() * 0.60f);
            placeRow (kMix, 0, 4, top);
            const float sw = r.getWidth() / 4.0f;
            for (int i = 0; i < 4; ++i)
                placeInArtboard (*switches[(size_t) (i + 1)], juce::Rectangle<float> (r.getX() + (float) i * sw + sw * 0.5f - 8.0f, r.getY() + 1.0f, 16.0f, r.getHeight() - 2.0f));
        }
        // MODIFIERS: FILTER row (cutoff/emphasis/contour/kbd) + 2 envelope rows
        {
            auto r = body (secRect[3]);
            const float rh = r.getHeight() / 3.0f;
            auto filt = juce::Rectangle<float> (r.getX(), r.getY(), r.getWidth(), rh);
            rFiltHdr = filt.withHeight (8.0f).translated (0, -1.0f);
            placeRow (kMod, 0, 4, filt.withTrimmedTop (7.0f));
            auto fe = juce::Rectangle<float> (r.getX(), r.getY() + rh, r.getWidth(), rh);
            rEnvHdr = fe.withHeight (8.0f).removeFromLeft (r.getWidth() * 0.55f);
            placeRow (kMod, 4, 3, fe.withTrimmedTop (7.0f).removeFromLeft (r.getWidth() * 0.55f));
            placeRow (kMod, 7, 3, juce::Rectangle<float> (r.getX(), r.getY() + 2.0f*rh, r.getWidth(), rh).removeFromLeft (r.getWidth() * 0.55f));
            // FILTER MOD group in the open right area (rows 1-2): bigger knob on the LEFT, switch to the RIGHT
            auto fm = juce::Rectangle<float> (r.getX() + r.getWidth() * 0.58f, r.getY() + rh, r.getWidth() * 0.42f, rh * 2.0f);
            rFmodHdr = fm.withHeight (9.0f);
            auto fi = fm.withTrimmedTop (12.0f);
            placeInArtboard (*kFmod[0], fi.removeFromLeft (fi.getWidth() * 0.62f).reduced (3.0f, 1.0f));   // bigger, left
            placeInArtboard (*swFmod, juce::Rectangle<float> (fi.getCentreX() - 9.0f, fi.getCentreY() - 16.0f, 18.0f, 32.0f));
        }
        // OUTPUT: VOLUME knob
        {
            auto r = body (secRect[4]);
            placeInArtboard (*kOut[0], r.removeFromTop (r.getHeight() * 0.6f).reduced (4, 2));
        }
    }

private:
    void placeRow (std::vector<std::unique_ptr<toi::StyledKnob>>& v, int first, int count, juce::Rectangle<float> r)
    {
        const float kw = r.getWidth() / (float) count;
        for (int i = 0; i < count && first + i < (int) v.size(); ++i)
            placeInArtboard (*v[(size_t) (first + i)], juce::Rectangle<float> (r.getX() + (float) i * kw, r.getY(), kw, r.getHeight()).reduced (3.0f, 2.0f));
    }

    std::vector<std::unique_ptr<toi::StyledKnob>> kCtrl, kOsc, kMix, kMod, kOut, kFmod;
    std::vector<std::unique_ptr<MiniSwitch>>      switches;
    MiniSwitch *swO3 = nullptr, *swFmod = nullptr;   // mixer on/wp placed via switches[]
    std::vector<std::unique_ptr<MiniPreset>>      slots;
    std::unique_ptr<toi::Button> rand_, save_;
    juce::Rectangle<float> rPlate, rBrand, secRect[5], rFiltHdr, rEnvHdr, rFmodHdr;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MiniEditor)
};

//==============================================================================
class MiniPlugin  : public cmaj::plugin::GeneratedPlugin<::Mini>,
                    public toi::AudioTapSource,
                    public toi::PresetStore
{
public:
    using Base = cmaj::plugin::GeneratedPlugin<::Mini>;
    MiniPlugin (std::shared_ptr<cmaj::Patch> p) : Base (std::move (p)) {}
    juce::AudioProcessorEditor* createEditor() override { return new MiniEditor (*this, keyboardState); }
    void processBlock (juce::AudioBuffer<float>& audio, juce::MidiBuffer& midi) override
    {
        keyboardState.processNextMidiBuffer (midi, 0, audio.getNumSamples(), true);
        Base::processBlock (audio, midi);
        tap.push (audio);
    }
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
