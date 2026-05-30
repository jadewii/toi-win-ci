// JW-MX12 native faceplate (deep 8-voice analog poly + mod matrix) on the toi_faceplate.h kit.
// Traces the real Oberheim Matrix-12: near-black panel, BLUE divider bars, GREEN VFD, black fluted
// knobs, square preset buttons with a big domed circle (no text). PAGE EDITOR (the authentic
// workflow) - page buttons re-bind the 6 controls to that page; AMP/ENV2/ENV3/LFO pages use
// horizontal SLIDERS, the rest use knobs; the mod matrix lives on its own pages. All functional. No
// brand names.
#pragma once

#include "toi_faceplate.h"

struct JWMX12;

namespace mx12
{
    static const juce::Colour kPanel  { 0xff1a1b1f };
    static const juce::Colour kPanelLo{ 0xff101115 };
    static const juce::Colour kFrame  { 0xff050507 };
    static const juce::Colour kText   { 0xffe7e9ec };
    static const juce::Colour kDim    { 0xff8c9098 };
    static const juce::Colour kBlue    { 0xff2f6fd0 };  // Matrix-12 blue divider bars / accent
    static const juce::Colour kGreen   { 0xff4cd07a };  // green VFD ink
    static const juce::Colour kRed     { 0xffd0463a };  // STORE / red LEDs
    static const juce::Colour kRedHi   { 0xffff5a44 };
    static const juce::Colour kBtn     { 0xff2c2f35 };
}

//==============================================================================
// MxSquare - the Oberheim preset/page button: a dark square with a big DOMED CIRCLE inside, no text.
// Active = lit (blue ring + brighter dome). Label is printed on the panel (not on the button).
class MxSquare  : public juce::Button
{
public:
    MxSquare() : juce::Button ("sq") {}
    void setActive (bool a) { if (active != a) { active = a; repaint(); } }
    void setLit (juce::Colour c) { litCol = c; }
    void setCircle (bool c) { circle_ = c; }   // true = PRESET button (square + domed circle, no number); false = PLAIN square page button
    void flash() { flashing = true; repaint(); juce::Timer::callAfterDelay (140, [s = juce::Component::SafePointer<MxSquare> (this)] { if (s) { s->flashing = false; s->repaint(); } }); }
    void paintButton (juce::Graphics& g, bool over, bool down) override
    {
        auto b = getLocalBounds().toFloat().reduced (1.5f);
        const bool lit = active || down || flashing;
        if (lit) { g.setColour (litCol.withAlpha (0.40f)); g.fillRoundedRectangle (b.expanded (1.5f), 3.5f); }
        // square plate + top sheen (a plain page button looks like this on its own)
        g.setColour (juce::Colours::black.withAlpha (0.6f)); g.fillRoundedRectangle (b.translated (0.0f, 1.0f), 3.0f);
        juce::ColourGradient pgg (juce::Colour (0xff2a2d33), b.getCentreX(), b.getY(), juce::Colour (0xff1b1d22), b.getCentreX(), b.getBottom(), false);
        g.setGradientFill (pgg); g.fillRoundedRectangle (b, 3.0f);
        g.setColour (juce::Colours::white.withAlpha (lit ? 0.12f : 0.07f)); g.fillRoundedRectangle (b.withHeight (b.getHeight() * 0.4f).reduced (2.0f, 0.0f), 2.5f);
        g.setColour (juce::Colours::black.withAlpha (0.6f)); g.drawRoundedRectangle (b, 3.0f, 0.9f);
        if (lit) { g.setColour (litCol.withAlpha (0.95f)); g.drawRoundedRectangle (b, 3.0f, 1.3f); }
        if (circle_)
        {
            const float d = juce::jmin (b.getWidth(), b.getHeight()) - 6.0f;
            auto c = juce::Rectangle<float> (0, 0, d, d).withCentre (b.getCentre());
            g.setColour (juce::Colours::black.withAlpha (0.5f)); g.fillEllipse (c.translated (0.0f, 1.2f));
            const auto face = lit ? mx12::kBtn.brighter (0.24f) : juce::Colour (0xff202329);
            juce::ColourGradient dome (face.brighter (0.5f), c.getCentreX() - d * 0.24f, c.getCentreY() - d * 0.24f,
                                       face.darker (0.4f), c.getCentreX() + d * 0.22f, c.getCentreY() + d * 0.3f, true);
            dome.addColour (0.55, face);
            g.setGradientFill (dome); g.fillEllipse (c);
            g.setColour (juce::Colours::white.withAlpha (lit ? 0.30f : 0.16f)); g.drawEllipse (c.reduced (d * 0.16f).translated (-d * 0.05f, -d * 0.05f), 1.0f);
            g.setColour (juce::Colours::black.withAlpha (0.55f)); g.drawEllipse (c, 0.9f);
        }
    }
private:
    juce::Colour litCol { mx12::kBlue }; bool active = false, flashing = false, circle_ = true;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MxSquare)
};

//==============================================================================
// MxKey - the numeric keypad key (square membrane with its digit).
class MxKey  : public juce::Button
{
public:
    MxKey (const juce::String& t, juce::Colour c) : juce::Button (t), col (c) { setButtonText (t); }
    void flash() { flashing = true; repaint(); juce::Timer::callAfterDelay (130, [s = juce::Component::SafePointer<MxKey> (this)] { if (s) { s->flashing = false; s->repaint(); } }); }
    void paintButton (juce::Graphics& g, bool over, bool down) override
    {
        auto b = getLocalBounds().toFloat().reduced (1.0f);
        g.setColour (juce::Colours::black.withAlpha (0.55f)); g.fillRoundedRectangle (b.translated (0.0f, 1.0f), 2.5f);
        const auto base = (down || flashing) ? mx12::kBtn.brighter (0.2f) : over ? mx12::kBtn.brighter (0.08f) : mx12::kBtn;
        juce::ColourGradient cg (base.brighter (0.22f), b.getCentreX(), b.getY(), base.darker (0.22f), b.getCentreX(), b.getBottom(), false);
        g.setGradientFill (cg); g.fillRoundedRectangle (b, 2.5f);
        g.setColour (juce::Colours::black.withAlpha (0.55f)); g.drawRoundedRectangle (b, 2.5f, 0.8f);
        g.setColour ((down || flashing) ? mx12::kGreen : mx12::kText); g.setFont (toi::uiFont (juce::jmin (10.0f, b.getHeight() * 0.55f), true));
        g.drawText (getButtonText(), getLocalBounds(), juce::Justification::centred);
    }
private:
    juce::Colour col; bool flashing = false;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MxKey)
};

//==============================================================================
inline toi::Config jwmx12Config()
{
    toi::Config c;
    c.model = "JW-MX12";
    auto& p = c.pal;
    p.bg = mx12::kPanel; p.bg2 = mx12::kPanelLo; p.frame = mx12::kFrame; p.ink = mx12::kFrame;
    p.accent = mx12::kBlue; p.accent2 = mx12::kRed; p.button = juce::Colour (0xff3a3e45);
    p.thumb = mx12::kText; p.text = mx12::kText;
    p.noteStrip = juce::Colour (0xff1f2024);
    p.lcdBg = juce::Colour (0xff04220f); p.lcdInk = mx12::kGreen;
    p.keyWhite = juce::Colour (0xffeef0f2); p.keyWhitePr = juce::Colour (0xffbfe9cf);
    p.keyBlack = juce::Colour (0xff141518); p.keyBlackPr = mx12::kGreen;

    c.params = {
        { "o1Wave","WAVE" },{ "o1Oct","OCT" },{ "o2Wave","WAVE" },{ "o2Oct","OCT" },{ "o2Tune","DETUNE" },{ "sync","SYNC" },{ "fmAmt","FM" },{ "pw","PW" },{ "mix","MIX" },{ "noiseLvl","NOISE" },
        { "cutoff","CUTOFF" },{ "reso","RESO" },{ "fMode","MODE" },{ "fSlope","SLOPE" },{ "fKeyTrack","KBD" },
        { "a1","ATTACK" },{ "d1","DECAY" },{ "s1","SUSTAIN" },{ "r1","RELEASE" },
        { "a2","ATTACK" },{ "d2","DECAY" },{ "s2","SUSTAIN" },{ "r2","RELEASE" },
        { "a3","ATTACK" },{ "d3","DECAY" },{ "s3","SUSTAIN" },{ "r3","RELEASE" },
        { "lfo1Rate","LFO1 RATE" },{ "lfo1Shape","LFO1 SHAPE" },{ "lfo2Rate","LFO2 RATE" },{ "lfo2Shape","LFO2 SHAPE" },{ "glide","GLIDE" },{ "volume","VOL" },{ "tune","TUNE" },
        { "m1Src","SRC" },{ "m1Dst","DST" },{ "m1Amt","AMT" },{ "m2Src","SRC" },{ "m2Dst","DST" },{ "m2Amt","AMT" },
        { "m3Src","SRC" },{ "m3Dst","DST" },{ "m3Amt","AMT" },{ "m4Src","SRC" },{ "m4Dst","DST" },{ "m4Amt","AMT" },
        { "m5Src","SRC" },{ "m5Dst","DST" },{ "m5Amt","AMT" },{ "m6Src","SRC" },{ "m6Dst","DST" },{ "m6Amt","AMT" },
    };

    std::vector<float> base = {
        0.0f,0.50f,0.0f,0.50f,0.50f,0.0f,0.0f,0.50f,0.50f,0.0f,
        0.60f,0.22f,0.0f,0.60f,0.30f,
        0.02f,0.50f,0.80f,0.30f,
        0.02f,0.50f,0.30f,0.30f,
        0.10f,0.50f,0.50f,0.40f,
        0.30f,0.0f,0.18f,0.0f,0.0f,0.80f,0.50f,
        0.50f,0.571f,0.82f, 0.0f,0.0f,0.50f, 0.0f,0.0f,0.50f, 0.0f,0.0f,0.50f, 0.0f,0.0f,0.50f, 0.0f,0.0f,0.50f };
    enum { O1W,O1O,O2W,O2O,O2T,SYNC,FM,PW,MIX,NZ, CUT,RES,FMODE,FSLP,FKBD,
           A1,D1,S1,R1, A2,D2,S2,R2, A3,D3,S3,R3,
           L1R,L1S,L2R,L2S,GLIDE,VOL,TUNE,
           M1S,M1D,M1A,M2S,M2D,M2A,M3S,M3D,M3A,M4S,M4D,M4A,M5S,M5D,M5A,M6S,M6D,M6A };
    auto P = [&] (const char* nm, std::initializer_list<std::pair<int,float>> ov)
    { auto v = base; for (auto& o : ov) v[(size_t) o.first] = o.second; return toi::FactoryPreset { nm, v }; };

    c.factory = {
        P("INIT",        {}),
        P("SILK PAD",    {{FMODE,0.0f},{FSLP,0.7f},{CUT,0.5f},{A1,0.4f},{R1,0.6f},{A2,0.4f},{M2S,0.167f},{M2D,0.143f},{M2A,0.54f},{L1R,0.18f}}),
        P("CINEMATIC",   {{CUT,0.45f},{RES,0.35f},{A1,0.6f},{R1,0.7f},{M2S,0.333f},{M2D,0.571f},{M2A,0.62f},{L2R,0.08f}}),
        P("BRASS STACK", {{O2T,0.515f},{CUT,0.5f},{M1A,0.7f},{A1,0.06f},{D1,0.5f},{S1,0.5f},{A2,0.04f},{D2,0.4f}}),
        P("GLASS BELL",  {{FMODE,0.5f},{FM,0.3f},{O2O,0.625f},{CUT,0.7f},{A1,0.0f},{D1,0.5f},{S1,0.2f},{M1A,0.6f}}),
        P("HUGE SAW",    {{MIX,0.5f},{O2T,0.53f},{CUT,0.6f},{RES,0.3f},{FSLP,0.8f},{M1A,0.78f}}),
        P("NOTCH PHASER",{{FMODE,1.0f},{RES,0.5f},{M3S,0.167f},{M3D,0.571f},{M3A,0.7f},{L1R,0.12f},{CUT,0.55f}}),
        P("VELO SWELL",  {{A1,0.3f},{M4S,0.833f},{M4D,0.857f},{M4A,0.85f},{CUT,0.5f}}),
        P("KEY OPEN",    {{FKBD,0.6f},{M5S,1.0f},{M5D,0.571f},{M5A,0.75f},{CUT,0.4f}}),
        P("WOBBLE BASS", {{O1O,0.375f},{O2O,0.375f},{CUT,0.4f},{RES,0.45f},{M2S,0.167f},{M2D,0.571f},{M2A,0.78f},{L1R,0.4f}}),
        P("SYNC LEAD",   {{SYNC,1.0f},{O2T,0.62f},{CUT,0.6f},{M1A,0.7f},{A1,0.02f},{D1,0.4f}}),
        P("AIRY KEYS",   {{FMODE,0.0f},{CUT,0.65f},{A1,0.01f},{D1,0.45f},{S1,0.3f},{R1,0.5f},{M1A,0.65f}}),
    };
    return c;
}

//==============================================================================
class JWMX12Editor  : public toi::PanelEditor
{
public:
    JWMX12Editor (juce::AudioProcessor& proc, juce::MidiKeyboardState& kb)
        : toi::PanelEditor (proc, kb, jwmx12Config())
    {
        grain_ = makeGrain (130, 130);
        buildPages();

        for (int i = 0; i < 6; ++i)
        {
            auto k = std::make_unique<toi::StyledKnob> ("", pal(), toi::StyledKnob::FlutedDark); k->setShowLabel (false); addAndMakeVisible (*k); knobs_.push_back (std::move (k));
            auto sl = std::make_unique<toi::StyledHSlider> ("", pal()); sl->setShowLabel (false); addChildComponent (*sl); sliders_.push_back (std::move (sl));
        }
        const char* mids[] = { "volume", "tune" };
        for (int i = 0; i < 2; ++i)
        { auto k = std::make_unique<toi::StyledKnob> ("", pal(), toi::StyledKnob::FlutedDark); k->setShowLabel (false); if (auto* prm = findParam (mids[i])) k->attach (*prm); addAndMakeVisible (*k); knobMaster_[i] = std::move (k); }

        for (int i = 0; i < (int) pages_.size(); ++i)
        { auto b = std::make_unique<MxSquare>(); b->setCircle (false); b->setLit (mx12::kBlue); const int pg = i; b->onClick = [this, pg] { selectPage (pg); }; addAndMakeVisible (*b); pageBtns_.push_back (std::move (b)); }

        // PRESET buttons: square + domed circle, NO numbers - recall a patch (name shows on the screen)
        for (int i = 0; i < 16; ++i)
        { auto b = std::make_unique<MxSquare>(); b->setCircle (true); b->setLit (mx12::kGreen); const int idx = i; b->onClick = [this, idx] { recallSlot (idx); }; addAndMakeVisible (*b); presetBtns_.push_back (std::move (b)); }

        store_ = std::make_unique<MxKey> ("STORE", mx12::kRed);
        rand_  = std::make_unique<MxKey> ("RAND",  mx12::kBlue);
        store_->onClick = [this] { saveSlot (activeSlot()); store_->flash(); };
        rand_->onClick  = [this] { doRandom(); rand_->flash(); };
        addAndMakeVisible (*store_); addAndMakeVisible (*rand_);

        scope_ = std::make_unique<toi::Lcd> (pal());
        scope_->attachScope (audioTap());
        scope_->setLines ("", "");   // pure real-audio scope - no preset names
        addAndMakeVisible (*scope_);

        finishSetup();
        selectPage (0);
    }

protected:
    void setPresetActiveVisual (int idx) override
    {
        for (int i = 0; i < (int) presetBtns_.size(); ++i) presetBtns_[(size_t) i]->setActive (i == idx);
    }

    static juce::Image makeGrain (int w, int h)
    {
        juce::Image img (juce::Image::ARGB, w, h, true);
        juce::Random r (12);
        for (int y = 0; y < h; ++y) for (int x = 0; x < w; ++x)
        { const float n = r.nextFloat(); if (n > 0.66f) { const float a = (n - 0.66f) / 0.34f * 0.045f; const bool light = r.nextBool();
            img.setPixelAt (x, y, (light ? juce::Colours::white : juce::Colours::black).withAlpha (a)); } }
        return img;
    }

    void paintPanel (juce::Graphics& g, juce::Rectangle<float> panel) override
    {
        rPanel = panel;
        juce::ColourGradient pg (mx12::kPanel, rPanel.getCentreX(), rPanel.getY(), mx12::kPanelLo, rPanel.getCentreX(), rPanel.getBottom(), false);
        g.setGradientFill (pg); g.fillRoundedRectangle (rPanel, 5.0f);
        if (grain_.isValid()) { g.setFillType (juce::FillType (grain_, juce::AffineTransform::translation (rPanel.getX(), rPanel.getY()))); g.fillRoundedRectangle (rPanel, 5.0f); }
        g.setColour (juce::Colours::black); g.drawRoundedRectangle (rPanel, 5.0f, 1.5f);

        sectionLabel (g, rMaster_, "MASTER");
        sectionLabel (g, rProg_,   "PROGRAMMER");
        sectionLabel (g, rPageSel_,"MODULATION  SOURCE  /  PAGE  SELECT");
        sectionLabel (g, rPageMod_,"PAGE  MODIFIER");

        g.setColour (mx12::kDim); g.setFont (toi::uiFont (7.0f, true));
        g.drawText ("VOLUME", rVol_.withY (rVol_.getBottom() + 1.0f).withHeight (10.0f), juce::Justification::centred);
        g.drawText ("TUNE",   rTune_.withY (rTune_.getBottom() + 1.0f).withHeight (10.0f), juce::Justification::centred);

        // LCD bezel (scope sits inside, top row)
        g.setColour (juce::Colour (0xff04220f)); g.fillRoundedRectangle (rScope_.expanded (3.0f), 3.0f);
        g.setColour (juce::Colours::black); g.drawRoundedRectangle (rScope_.expanded (3.0f), 3.0f, 1.2f);

        // page-button legends (printed on the panel, below each square button)
        g.setFont (toi::uiFont (6.5f, true));
        const int n = (int) pageBtns_.size();
        const float pw = rPageRow_.getWidth() / (float) n;
        for (int i = 0; i < n; ++i)
        {
            g.setColour (i == curPage_ ? mx12::kBlue.brighter (0.2f) : mx12::kDim);
            g.drawText (pages_[(size_t) i].name, juce::Rectangle<float> (rPageRow_.getX() + (float) i * pw, rPageRow_.getBottom() + 1.0f, pw, 10.0f), juce::Justification::centred);
        }

        // PAGE MODIFIER green readout + control labels
        g.setColour (mx12::kGreen); g.setFont (juce::Font (juce::FontOptions (11.0f).withName ("Menlo")).boldened());
        g.drawText ("PAGE:  " + pages_[(size_t) curPage_].name, juce::Rectangle<float> (rPageMod_.getX(), rPageMod_.getY() - 1.0f, 200.0f, 12.0f), juce::Justification::centredLeft);

        const auto& page = pages_[(size_t) curPage_];
        const bool sp = isSliderPage (curPage_);
        g.setFont (toi::uiFont (7.5f, true));
        for (int i = 0; i < 6; ++i)
        {
            if (page.ids[(size_t) i].isEmpty()) continue;
            g.setColour (mx12::kDim);
            if (sp) g.drawText (page.labels[(size_t) i], ctrlRect_[i].withHeight (11.0f), juce::Justification::centred);                                  // label ABOVE the horizontal slider
            else    g.drawText (page.labels[(size_t) i], ctrlRect_[i].withY (ctrlRect_[i].getBottom() - 11.0f).withHeight (11.0f), juce::Justification::centred);
        }

        // brand (bottom-left, one row: name + TOI + the MODULE/SIZE LEDs)
        g.setColour (mx12::kText); g.setFont (toi::uiFont (14.0f, true));
        g.drawText ("JW-MX12", juce::Rectangle<float> (rBrand_.getX(), rBrand_.getY(), 88.0f, rBrand_.getHeight()), juce::Justification::centredLeft);
        g.setColour (mx12::kDim); g.setFont (toi::uiFont (6.0f, true).withExtraKerningFactor (0.14f));
        g.drawText ("TOI - plugin corp", juce::Rectangle<float> (rBrand_.getX() + 90.0f, rBrand_.getY(), 110.0f, rBrand_.getHeight()), juce::Justification::centredLeft);
        drawViewLeds (g, juce::Rectangle<float> (rBrand_.getRight() - 96.0f, rBrand_.getY(), 96.0f, rBrand_.getHeight()));
    }

    void layoutPanel (juce::Rectangle<float> panel) override
    {
        rPanel = panel;
        auto inner = rPanel.reduced (12.0f, 8.0f);
        const float midX = inner.getX() + 405.0f;

        // ---- top row: MASTER knobs + the (smaller) screen beside them ----
        rMaster_ = juce::Rectangle<float> (inner.getX(), inner.getY(), midX - inner.getX() - 10.0f, 22.0f);
        rVol_  = juce::Rectangle<float> (inner.getX() + 8.0f,  inner.getY() + 26.0f, 50.0f, 50.0f);
        rTune_ = juce::Rectangle<float> (inner.getX() + 66.0f, inner.getY() + 26.0f, 50.0f, 50.0f);
        placeInArtboard (*knobMaster_[0], rVol_);
        placeInArtboard (*knobMaster_[1], rTune_);
        rScope_ = juce::Rectangle<float> (inner.getX() + 134.0f, inner.getY() + 30.0f, 256.0f, 44.0f);
        placeInArtboard (*scope_, rScope_);

        // ---- left: PROGRAMMER (keypad + store/rand + brand) ----
        rProg_ = juce::Rectangle<float> (inner.getX(), inner.getY() + 92.0f, midX - inner.getX() - 10.0f, 22.0f);
        {
            placeInArtboard (*store_, juce::Rectangle<float> (inner.getX() + 6.0f,  inner.getY() + 118.0f, 84.0f, 22.0f));
            placeInArtboard (*rand_,  juce::Rectangle<float> (inner.getX() + 94.0f, inner.getY() + 118.0f, 84.0f, 22.0f));
            // 16 PRESET buttons, 8 x 2
            const float gx = inner.getX() + 6.0f, gy = inner.getY() + 146.0f, bw = 44.0f, bh = 26.0f, sx = 4.0f, sy = 4.0f;
            for (int i = 0; i < 16; ++i)
            { const int r = i / 8, cc = i % 8; placeInArtboard (*presetBtns_[(size_t) i], juce::Rectangle<float> (gx + (float) cc * (bw + sx), gy + (float) r * (bh + sy), bw, bh)); }
        }
        rBrand_ = juce::Rectangle<float> (inner.getX() + 6.0f, inner.getBottom() - 26.0f, midX - inner.getX() - 16.0f, 26.0f);

        // ---- right: PAGE SELECT row + PAGE MODIFIER controls ----
        rPageSel_ = juce::Rectangle<float> (midX, inner.getY(), inner.getRight() - midX, 22.0f);
        rPageRow_ = juce::Rectangle<float> (midX, inner.getY() + 26.0f, inner.getRight() - midX, 30.0f);
        {
            const int n = (int) pageBtns_.size();
            const float pw = rPageRow_.getWidth() / (float) n;
            for (int i = 0; i < n; ++i)
                placeInArtboard (*pageBtns_[(size_t) i], juce::Rectangle<float> (rPageRow_.getX() + (float) i * pw, rPageRow_.getY(), pw, rPageRow_.getHeight()).reduced (3.0f, 0.0f));
        }
        rPageMod_ = juce::Rectangle<float> (midX, inner.getY() + 92.0f, inner.getRight() - midX, 22.0f);
        rCtrls_   = juce::Rectangle<float> (midX, inner.getY() + 118.0f, inner.getRight() - midX, inner.getBottom() - (inner.getY() + 118.0f));
        placePageControls();
    }

private:
    struct Page { juce::String name; std::array<juce::String,6> ids; std::array<juce::String,6> labels; };

    void buildPages()
    {
        auto pg = [] (juce::String nm, std::array<juce::String,6> ids) { Page p; p.name = nm; p.ids = ids; return p; };
        pages_ = {
            pg ("OSC",   { "o1Wave","o1Oct","o2Wave","o2Oct","o2Tune","mix" }),
            pg ("MIX",   { "pw","fmAmt","sync","noiseLvl","glide","" }),
            pg ("FILTER",{ "cutoff","reso","fMode","fSlope","fKeyTrack","" }),
            pg ("AMP",   { "a1","d1","s1","r1","","" }),
            pg ("ENV2",  { "a2","d2","s2","r2","","" }),
            pg ("ENV3",  { "a3","d3","s3","r3","","" }),
            pg ("LFO",   { "lfo1Rate","lfo1Shape","lfo2Rate","lfo2Shape","","" }),
            pg ("MTX1",  { "m1Src","m1Dst","m1Amt","m2Src","m2Dst","m2Amt" }),
            pg ("MTX2",  { "m3Src","m3Dst","m3Amt","m4Src","m4Dst","m4Amt" }),
            pg ("MTX3",  { "m5Src","m5Dst","m5Amt","m6Src","m6Dst","m6Amt" }),
            pg ("MAST",  { "volume","tune","","","","" }),
        };
        for (auto& page : pages_)
            for (int i = 0; i < 6; ++i)
            { page.labels[(size_t) i] = ""; for (auto& sp : config().params) if (sp.id == page.ids[(size_t) i]) { page.labels[(size_t) i] = sp.label; break; } }
    }

    bool isSliderPage (int pg) const
    { const auto& n = pages_[(size_t) pg].name; return n == "AMP" || n == "ENV2" || n == "ENV3" || n == "LFO"; }
    int activeCount (int pg) const
    { int c = 0; for (int i = 0; i < 6; ++i) if (pages_[(size_t) pg].ids[(size_t) i].isNotEmpty()) ++c; return c; }

    void placePageControls()
    {
        const auto& page = pages_[(size_t) curPage_];
        const bool sp = isSliderPage (curPage_);
        const int n = juce::jmax (1, activeCount (curPage_));
        const float cw = rCtrls_.getWidth() / (float) n;   // N equal columns, controls NEXT TO EACH OTHER
        int col = 0;
        for (int i = 0; i < 6; ++i)
        {
            const bool has = page.ids[(size_t) i].isNotEmpty();
            knobs_[(size_t) i]->setVisible (! sp && has);
            sliders_[(size_t) i]->setVisible (sp && has);
            if (! has) continue;
            auto cell = juce::Rectangle<float> (rCtrls_.getX() + (float) col * cw, rCtrls_.getY(), cw, rCtrls_.getHeight()).reduced (5.0f, 2.0f);
            ctrlRect_[i] = cell;
            if (sp)   // horizontal slider, side by side, label ABOVE
            {
                auto sr = cell.withTrimmedTop (13.0f);
                sr = sr.withSizeKeepingCentre (sr.getWidth(), juce::jmin (24.0f, sr.getHeight()));
                placeInArtboard (*sliders_[(size_t) i], sr);
                if (auto* prm = findParam (page.ids[(size_t) i])) sliders_[(size_t) i]->attach (*prm);
            }
            else      // knob (capped so it's not huge), label BELOW
            {
                const float kd = juce::jmin (cell.getWidth(), cell.getHeight() - 12.0f, 54.0f);
                auto kr = juce::Rectangle<float> (0, 0, kd, kd).withCentre ({ cell.getCentreX(), cell.getY() + (cell.getHeight() - 12.0f) * 0.5f });
                placeInArtboard (*knobs_[(size_t) i], kr);
                if (auto* prm = findParam (page.ids[(size_t) i])) knobs_[(size_t) i]->attach (*prm);
            }
            ++col;
        }
    }

    void selectPage (int pg)
    {
        curPage_ = juce::jlimit (0, (int) pages_.size() - 1, pg);
        for (int i = 0; i < (int) pageBtns_.size(); ++i) pageBtns_[(size_t) i]->setActive (i == curPage_);
        placePageControls();
        repaint();
    }

    void sectionLabel (juce::Graphics& g, juce::Rectangle<float> r, const juce::String& name)
    {
        g.setColour (mx12::kText); g.setFont (toi::uiFont (8.5f, true).withExtraKerningFactor (0.14f));
        g.drawText (name, r.withHeight (11.0f), juce::Justification::centredLeft);
        g.setColour (mx12::kBlue);
        g.fillRect (juce::Rectangle<float> (r.getX(), r.getY() + 13.0f, r.getWidth(), 2.4f));
    }

    std::vector<std::unique_ptr<toi::StyledKnob>> knobs_;
    std::vector<std::unique_ptr<toi::StyledHSlider>> sliders_;
    std::unique_ptr<toi::StyledKnob> knobMaster_[2];
    std::vector<std::unique_ptr<MxSquare>> pageBtns_, presetBtns_;
    std::unique_ptr<MxKey> store_, rand_;
    std::unique_ptr<toi::Lcd> scope_;
    std::vector<Page> pages_;
    int curPage_ = 0;
    juce::Image grain_;
    juce::Rectangle<float> rPanel, rMaster_, rProg_, rPageSel_, rPageMod_, rPageRow_, rVol_, rTune_, rScope_, rCtrls_, rBrand_;
    juce::Rectangle<float> ctrlRect_[6];
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JWMX12Editor)
};

//==============================================================================
class JWMX12Plugin  : public cmaj::plugin::GeneratedPlugin<::JWMX12>,
                      public toi::AudioTapSource,
                      public toi::PresetStore
{
public:
    using Base = cmaj::plugin::GeneratedPlugin<::JWMX12>;
    JWMX12Plugin (std::shared_ptr<cmaj::Patch> p) : Base (std::move (p)) {}
    juce::AudioProcessorEditor* createEditor() override { return new JWMX12Editor (*this, keyboardState); }
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
