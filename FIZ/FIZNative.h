// JW-FIZ native faceplate (psychedelic realtime transwave synth) on the toi_faceplate.h kit.
// Traces the Ensoniq Fizmo: a PURPLE->BLUE metalflake gradient panel, SILVER knobs (thin black
// pointer) each on a silver circle mount, and the signature F-I-Z-M-O macro strip across the bottom.
// Headline = the live TRANSWAVE morph display (mirrors the engine's frame math). NO brand names.
#pragma once

#include "toi_faceplate.h"

struct JWFIZ;

namespace fiz
{
    static const juce::Colour kBlue   { 0xff3a5cd6 };   // lower-left - vivid royal blue
    static const juce::Colour kViolet { 0xff7240b6 };   // mid - rich violet
    static const juce::Colour kPurple { 0xffb22f86 };   // upper-right - vivid magenta-purple
    static const juce::Colour kInk    { 0xfff0e9f4 };   // light label text on the dark panel
    static const juce::Colour kDim    { 0xffb9aec6 };
    static const juce::Colour kSilver { 0xffc7ccd4 };   // knob mount / chrome
    static const juce::Colour kSilverLo{ 0xff7e8490 };
    static const juce::Colour kStrip  { 0xff15121a };   // the black F-I-Z-M-O strip
    static const juce::Colour kBox    { 0x33120c1f };   // faint section box on the gradient
    static const juce::Colour kBoxHi  { 0x66e6dcf2 };
    static const juce::Colour kRed    { 0xffc83a24 };   // the red LCD
    static const juce::Colour kAccent { 0xffd9c6ec };   // knob value-arc (lavender chrome)

    // mirror of the engine's transwave frame math (FIZ.cmajor buildTranswaves) so the display shows
    // the REAL wave being built. ff = wave position 0..1; returns one cycle.
    inline float frameSample (int bank, float ff, float ph)
    {
        float s = 0.0f;
        if (bank == 0)            // VOX - formant sweeping up the harmonic series
        {
            const float center = 1.0f + ff * 16.0f, width = 2.6f;
            for (int k = 1; k <= 32; ++k)
            { const float g = std::exp (-0.5f * ((k - center) / width) * ((k - center) / width));
              s += (g + 0.28f / (float) k) * std::sin (juce::MathConstants<float>::twoPi * ph * (float) k); }
        }
        else if (bank == 1)       // SWEEP - harmonics grow in
        {
            const float maxK = 1.0f + ff * 31.0f;
            for (int k = 1; k <= 32; ++k)
            { const float roll = juce::jlimit (0.0f, 1.0f, maxK - (float) k + 1.0f);
              s += (1.0f / (float) k) * roll * std::sin (juce::MathConstants<float>::twoPi * ph * (float) k); }
        }
        else                      // GLASS - inharmonic partials stretch + a moving metal partial
        {
            for (int j = 1; j <= 8; ++j)
            { const float r = (float) j * (1.0f + ff * 0.6f * (float) (j - 1) / 7.0f);
              s += (1.0f / (float) j) * std::sin (juce::MathConstants<float>::twoPi * ph * r); }
            s += 0.3f * std::sin (juce::MathConstants<float>::twoPi * ph * (6.0f + ff * 11.0f));
        }
        return s;
    }
}

//==============================================================================
// FizWaveView - LIVE display of the transwave frame the user is building (reads Wave Select + Wave Pos,
// reconstructs the exact engine frame). Morphs as you turn the WAVE knobs. (Not static art.)
class FizWaveView  : public juce::Component,
                     private juce::AudioProcessorParameter::Listener,
                     private juce::AsyncUpdater
{
public:
    FizWaveView() = default;
    ~FizWaveView() override { for (auto* p : params_) if (p) p->removeListener (this); cancelPendingUpdate(); }
    void setParams (juce::AudioProcessorParameter* sel, juce::AudioProcessorParameter* pos)
    { params_ = { sel, pos }; for (auto* p : params_) if (p) p->addListener (this); triggerAsyncUpdate(); }
    void paint (juce::Graphics& g) override
    {
        auto r = getLocalBounds().toFloat();
        g.setColour (juce::Colour (0xff140d20)); g.fillRoundedRectangle (r, 4.0f);
        g.setColour (fiz::kAccent.withAlpha (0.55f)); g.drawRoundedRectangle (r, 4.0f, 1.0f);
        auto a = r.reduced (6.0f, 5.0f);
        const int bank = params_[0] ? juce::jlimit (0, 2, juce::roundToInt (params_[0]->getValue() * 2.0f)) : 0;
        const float ff = params_[1] ? params_[1]->getValue() : 0.15f;
        const float midY = a.getCentreY(), amp = a.getHeight() * 0.46f;
        g.setColour (fiz::kAccent.withAlpha (0.16f)); g.drawLine (a.getX(), midY, a.getRight(), midY, 0.8f);
        // normalise this frame
        float mx = 0.0001f;
        for (int x = 0; x < 64; ++x) { const float v = std::abs (fiz::frameSample (bank, ff, (float) x / 64.0f)); if (v > mx) mx = v; }
        const int N = 220; juce::Path p; bool started = false;
        for (int x = 0; x < N; ++x)
        {
            const float ph = (float) x / (float) (N - 1);
            const float y = midY - (fiz::frameSample (bank, ff, ph) / mx) * amp;
            const float px = a.getX() + ph * a.getWidth();
            if (! started) { p.startNewSubPath (px, y); started = true; } else p.lineTo (px, y);
        }
        g.setColour (fiz::kAccent); g.strokePath (p, juce::PathStrokeType (1.6f));
        g.setColour (fiz::kDim); g.setFont (toi::uiFont (6.5f, true));
        const char* nm[3] = { "VOX", "SWEEP", "GLASS" };
        g.drawText (nm[bank], a.removeFromTop (9.0f), juce::Justification::topRight);
    }
private:
    void parameterValueChanged (int, float) override { triggerAsyncUpdate(); }
    void parameterGestureChanged (int, bool) override {}
    void handleAsyncUpdate() override { repaint(); }
    std::vector<juce::AudioProcessorParameter*> params_;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FizWaveView)
};

//==============================================================================
class FizFunc  : public juce::Button
{
public:
    FizFunc (const juce::String& t, juce::Colour fill) : juce::Button (t), col (fill) { setButtonText (t); }
    void flash() { flashing = true; repaint(); juce::Timer::callAfterDelay (150, [s = juce::Component::SafePointer<FizFunc> (this)] { if (s) { s->flashing = false; s->repaint(); } }); }
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
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FizFunc)
};

//==============================================================================
// FizKnob - the Fizmo control (Jade's ref): a BLACK domed knob with a BIG SILVER centre cap + a
// pointer, sitting on the silver-circle mount (drawn behind it). Bound 0..1.
class FizKnob  : public juce::Component
{
public:
    FizKnob()
    {
        slider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
        slider.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
        slider.setLookAndFeel (&laf); slider.setRange (0.0, 1.0, 0.0);
        addAndMakeVisible (slider);
    }
    ~FizKnob() override { slider.setLookAndFeel (nullptr); }
    void attach (juce::AudioProcessorParameter& p)
    { att = std::make_unique<toi::ParamKnobAttachment> (p, slider); slider.setDoubleClickReturnValue (true, p.getDefaultValue()); slider.onValueChange = [this] { repaint(); }; repaint(); }
    void resized() override { slider.setBounds (getLocalBounds()); }
    void paint (juce::Graphics& g) override
    {
        auto b = getLocalBounds().toFloat();
        const float d = juce::jmin (b.getWidth(), b.getHeight());
        const float cx = b.getCentreX(), cy = b.getCentreY(), r = d * 0.5f - 2.0f;
        const float v = juce::jlimit (0.0f, 1.0f, (float) slider.getValue());
        const float ang = juce::degreesToRadians (-135.0f + 270.0f * v);
        const float dx = std::sin (ang), dy = -std::cos (ang);
        // BLACK domed knob body
        g.setColour (juce::Colours::black.withAlpha (0.45f)); g.fillEllipse (cx - r, cy - r + 2.0f, r * 2.0f, r * 2.0f);
        juce::ColourGradient body (juce::Colour (0xff3a3b44), cx, cy - r, juce::Colour (0xff09090d), cx, cy + r, false);
        g.setGradientFill (body); g.fillEllipse (cx - r, cy - r, r * 2.0f, r * 2.0f);
        g.setColour (juce::Colours::black); g.drawEllipse (cx - r, cy - r, r * 2.0f, r * 2.0f, 1.2f);
        // BIG SILVER centre cap (raised), ~58% radius
        const float ir = r * 0.58f;
        juce::ColourGradient cap (fiz::kSilver.brighter (0.25f), cx, cy - ir, fiz::kSilverLo, cx, cy + ir, false);
        cap.addColour (0.5, fiz::kSilver);
        g.setGradientFill (cap); g.fillEllipse (cx - ir, cy - ir, ir * 2.0f, ir * 2.0f);
        { const float gr = ir * 0.6f, gx = cx - ir * 0.3f, gy = cy - ir * 0.35f;
          juce::ColourGradient gl (juce::Colours::white.withAlpha (0.55f), gx, gy, juce::Colours::white.withAlpha (0.0f), gx + gr, gy + gr, true);
          g.setGradientFill (gl); g.fillEllipse (gx - gr, gy - gr, gr * 2.0f, gr * 2.0f); }
        g.setColour (juce::Colours::black.withAlpha (0.4f)); g.drawEllipse (cx - ir, cy - ir, ir * 2.0f, ir * 2.0f, 0.8f);
        // pointer: a light line from the silver cap edge across the black ring to the rim
        g.setColour (juce::Colours::white.withAlpha (0.9f));
        g.drawLine (cx + dx * ir * 0.7f, cy + dy * ir * 0.7f, cx + dx * (r - 2.0f), cy + dy * (r - 2.0f), juce::jmax (2.0f, r * 0.1f));
    }
    juce::Slider slider;
private:
    toi::InvisibleRotaryLAF laf;
    std::unique_ptr<toi::ParamKnobAttachment> att;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FizKnob)
};

//==============================================================================
inline toi::Config jwfizConfig()
{
    toi::Config c;
    c.model = "JW-FIZ";
    auto& p = c.pal;
    p.bg = fiz::kPurple; p.bg2 = fiz::kBlue; p.frame = juce::Colour (0xff0a0710); p.ink = juce::Colour (0xff0a0710);
    p.accent = fiz::kAccent; p.accent2 = fiz::kRed; p.button = juce::Colour (0xff2b2533);
    p.thumb = fiz::kSilver; p.text = fiz::kInk;
    p.noteStrip = fiz::kViolet;
    p.lcdBg = juce::Colour (0xff1c0a0a); p.lcdInk = fiz::kRed;
    p.keyWhite = juce::Colour (0xffe8e2ef); p.keyWhitePr = fiz::kAccent; p.keyBlack = juce::Colour (0xff241d30); p.keyBlackPr = fiz::kAccent;

    c.params = {
        { "waveSel","SELECT" },{ "wavePos","POS" },{ "o2Tune","DETUNE" },{ "oscMix","MIX" },
        { "mA","A" },{ "mD","D" },{ "mS","S" },{ "mR","R" },
        { "aA","A" },{ "aD","D" },{ "aS","S" },{ "aR","R" },{ "velAmt","VEL" },{ "pan","PAN" },
        { "waveMod","ENV" },{ "waveLfo","LFO" },
        { "cutoff","CUTOFF" },{ "reso","RESO" },{ "fMode","MODE" },{ "fKeyTrack","KBD" },{ "fEnvAmt","ENV" },
        { "lfoRate","RATE" },{ "lfoShape","SHAPE" },{ "lfoPitch","PITCH" },
        { "chorus","CHORUS" },{ "reverb","REVERB" },{ "delay","DELAY" },
        { "pEnvAmt","P.ENV" },{ "glide","GLIDE" },
        { "volume","VOL" },{ "tune","TUNE" },
        { "macF","F" },{ "macI","I" },{ "macZ","Z" },{ "macM","M" },{ "macO","O" },
    };

    std::vector<float> base = {
        0.0f,0.15f,0.50f,0.30f,0.50f,0.50f,
        0.50f,0.25f,0.0f,0.30f,0.45f,
        0.40f,0.60f,0.50f,0.60f,
        0.35f,0.50f,0.80f,0.60f,0.50f,0.50f,
        0.0f,0.50f,0.25f,0.0f,0.0f,
        0.50f,0.55f,0.25f,
        0.0f,0.0f,0.0f,0.0f,0.0f,
        0.80f,0.50f };
    // index helper into the engine param order (matches FIZ.cmajor Params struct order)
    enum { WSEL,WPOS,WMOD,WLFO,O2T,OMIX, CUT,RES,FMODE,FKBD,FENV, MA,MD,MS,MR, AA,AD,AS,AR,VEL,PAN,
           GLIDE,PENV, LR,LSH,LP, CHO,REV,DLY, MF,MI,MZ,MM,MO, VOL,TUNE };
    auto P = [&] (const char* nm, std::initializer_list<std::pair<int,float>> ov)
    { auto v = base; for (auto& o : ov) v[(size_t) o.first] = o.second; return toi::FactoryPreset { nm, v }; };

    c.factory = {
        P("INIT",         {}),
        P("LIQUID PAD",   {{WSEL,0.0f},{WMOD,0.7f},{WLFO,0.4f},{AA,0.5f},{AR,0.7f},{CUT,0.55f},{REV,0.7f},{CHO,0.6f}}),
        P("ALIEN VOX",    {{WSEL,0.0f},{WPOS,0.1f},{WMOD,0.85f},{MA,0.3f},{MD,0.7f},{CUT,0.6f},{RES,0.4f},{DLY,0.4f}}),
        P("GLASS BELLS",  {{WSEL,1.0f},{WPOS,0.4f},{WMOD,0.5f},{AA,0.0f},{AD,0.55f},{AS,0.3f},{CUT,0.7f},{REV,0.6f}}),
        P("MORPH SWEEP",  {{WSEL,0.5f},{WPOS,0.0f},{WMOD,0.95f},{MA,0.5f},{MD,0.8f},{CUT,0.5f},{LR,0.3f},{WLFO,0.5f}}),
        P("UNDERWATER",   {{WSEL,0.0f},{WMOD,0.6f},{WLFO,0.6f},{LR,0.15f},{CUT,0.4f},{RES,0.3f},{CHO,0.7f},{REV,0.75f},{DLY,0.5f}}),
        P("HAUNTED DRONE",{{WSEL,2.0f},{WPOS,0.3f},{WMOD,0.7f},{O2T,0.56f},{AA,0.6f},{AR,0.8f},{CUT,0.45f},{REV,0.8f}}),
        P("DREAM KEYS",   {{WSEL,1.0f},{WPOS,0.2f},{WMOD,0.4f},{AA,0.05f},{AD,0.5f},{AS,0.5f},{CUT,0.6f},{CHO,0.5f},{REV,0.5f}}),
        P("PSY MOTION",   {{WSEL,0.5f},{WMOD,0.8f},{WLFO,0.7f},{LR,0.45f},{CUT,0.55f},{RES,0.45f},{DLY,0.5f},{MO,0.0f}}),
        P("SOFT CHOIR",   {{WSEL,0.0f},{WPOS,0.05f},{WMOD,0.55f},{AA,0.45f},{AR,0.7f},{CUT,0.5f},{REV,0.7f}}),
        P("METAL SCAPE",  {{WSEL,2.0f},{WPOS,0.5f},{WMOD,0.85f},{WLFO,0.5f},{CUT,0.65f},{RES,0.5f},{DLY,0.45f},{REV,0.6f}}),
        P("BRIGHT LEAD",  {{WSEL,1.0f},{WPOS,0.6f},{WMOD,0.3f},{AA,0.02f},{AS,0.7f},{CUT,0.75f},{RES,0.4f},{CHO,0.4f}}),
    };
    return c;
}

//==============================================================================
class JWFIZEditor  : public toi::PanelEditor
{
public:
    JWFIZEditor (juce::AudioProcessor& proc, juce::MidiKeyboardState& kb)
        : toi::PanelEditor (proc, kb, jwfizConfig())
    {
        grain_ = makeFlake (160, 160);

        groupsA_ = { { "OSC", { "waveSel","wavePos","o2Tune","oscMix" } },
                     { "ENVELOPE", { "mA","mD","mS","mR" } },
                     { "AMPLITUDE", { "aA","aD","aS","aR","velAmt","pan" } } };
        groupsB_ = { { "WAVE", { "waveMod","waveLfo" } },
                     { "FILTER", { "cutoff","reso","fMode","fKeyTrack","fEnvAmt" } },
                     { "MODULATION", { "lfoRate","lfoShape","lfoPitch" } },
                     { "EFFECT BOX", { "chorus","reverb","delay" } },
                     { "PITCH", { "pEnvAmt","glide" } },
                     { "MASTER", { "volume","tune" } } };
        for (auto& grp : groupsA_) for (auto& id : grp.ids) addKnob (id, toi::StyledKnob::Metal);
        for (auto& grp : groupsB_) for (auto& id : grp.ids) addKnob (id, toi::StyledKnob::Metal);

        // live transwave morph display
        wave_ = std::make_unique<FizWaveView>();
        wave_->setParams (findParam ("waveSel"), findParam ("wavePos"));
        addAndMakeVisible (*wave_);

        // real-audio scope (the red LCD)
        scope_ = std::make_unique<toi::Lcd> (pal());
        scope_->attachScope (audioTap());
        addAndMakeVisible (*scope_);

        // the performance macros on the black strip - same FizKnob look as the top rows
        const char* macIds[5] = { "macF","macI","macZ","macM","macO" };
        for (int i = 0; i < 5; ++i)
        {
            auto k = std::make_unique<FizKnob>();
            if (auto* prm = findParam (macIds[i])) k->attach (*prm);
            addAndMakeVisible (*k); macros_.push_back (std::move (k));
        }

        for (int i = 0; i < 16; ++i)
        { auto b = std::make_unique<toi::MoldedButton> (juce::Colour (0xff2c2536)); b->setLit (fiz::kAccent); const int idx = i; b->onClick = [this, idx] { recallSlot (idx); }; addAndMakeVisible (*b); slots_.push_back (std::move (b)); }
        rand_ = std::make_unique<FizFunc> ("RAND", juce::Colour (0xff4a3d6b)); save_ = std::make_unique<FizFunc> ("SAVE", fiz::kRed.darker (0.1f));
        rand_->onClick = [this] { doRandom(); rand_->flash(); };
        save_->onClick = [this] { saveSlot (activeSlot()); save_->flash(); };
        addAndMakeVisible (*rand_); addAndMakeVisible (*save_);

        finishSetup();
    }

protected:
    void setPresetActiveVisual (int idx) override { for (int i = 0; i < (int) slots_.size(); ++i) slots_[(size_t) i]->setActive (i == idx); }

    // metalflake sparkle: dense fine specks (white + faint blue/violet) at low alpha = automotive flake
    static juce::Image makeFlake (int w, int h)
    {
        juce::Image img (juce::Image::ARGB, w, h, true);
        juce::Random r (4242);
        for (int y = 0; y < h; ++y) for (int x = 0; x < w; ++x)
        {
            const float n = r.nextFloat();
            if (n > 0.74f)
            {
                const float a = (n - 0.74f) / 0.26f * 0.16f;
                const int pick = r.nextInt (3);
                auto col = pick == 0 ? juce::Colours::white
                         : pick == 1 ? juce::Colour (0xff9fb6ff)   // blue flake
                                     : juce::Colour (0xffe2b6ff);  // violet flake
                img.setPixelAt (x, y, col.withAlpha (a));
            }
            else if (n < 0.06f) img.setPixelAt (x, y, juce::Colours::black.withAlpha (0.05f));
        }
        return img;
    }

    void paintPanel (juce::Graphics& g, juce::Rectangle<float> panel) override
    {
        rPanel = panel;
        // diagonal blue(lower-left) -> violet -> deep purple(upper-right) gradient
        juce::ColourGradient grad (fiz::kBlue, rPanel.getX(), rPanel.getBottom(), fiz::kPurple, rPanel.getRight(), rPanel.getY(), false);
        grad.addColour (0.5, fiz::kViolet);
        g.setGradientFill (grad); g.fillRoundedRectangle (rPanel, 5.0f);
        // soft radial colour clouds for organic mottling
        drawCloud (g, rPanel.getX() + rPanel.getWidth() * 0.26f, rPanel.getY() + rPanel.getHeight() * 0.32f, rPanel.getWidth() * 0.46f, juce::Colour (0x383f7cf0));
        drawCloud (g, rPanel.getX() + rPanel.getWidth() * 0.82f, rPanel.getY() + rPanel.getHeight() * 0.68f, rPanel.getWidth() * 0.42f, juce::Colour (0x38c43a96));
        // metalflake sparkle overlay
        if (grain_.isValid()) { g.setFillType (juce::FillType (grain_, juce::AffineTransform::translation (rPanel.getX(), rPanel.getY()))); g.fillRoundedRectangle (rPanel, 5.0f); }
        g.setColour (juce::Colours::black); g.drawRoundedRectangle (rPanel, 5.0f, 1.5f);

        for (auto& grp : groupsA_) drawGroupBox (g, grp);
        for (auto& grp : groupsB_) drawGroupBox (g, grp);

        // transwave display label
        g.setColour (fiz::kInk); g.setFont (toi::uiFont (7.0f, true).withExtraKerningFactor (0.1f));
        g.drawText ("TRANSWAVE", juce::Rectangle<float> (rWave_.getX(), rWave_.getY() - 9.0f, 120.0f, 9.0f), juce::Justification::centredLeft);

        // the black macro strip - same silver-mount FizKnobs as the top rows
        g.setColour (fiz::kStrip); g.fillRoundedRectangle (rStrip_, 4.0f);
        g.setColour (juce::Colours::black); g.drawRoundedRectangle (rStrip_, 4.0f, 1.0f);
        {
            const float mw = rMacro_.getWidth() / 5.0f;
            const char* ML[5] = { "M1","M2","M3","M4","M5" };
            for (int i = 0; i < 5; ++i)
            {
                auto kr = macros_[(size_t) i]->getBounds().toFloat();
                // silver mount disc behind each macro knob (matches drawGroupBox)
                auto c = kr.getCentre(); const float rad = kr.getWidth() * 0.50f;
                juce::ColourGradient ring (fiz::kSilver, c.x, c.y - rad, fiz::kSilverLo, c.x, c.y + rad, false);
                g.setGradientFill (ring); g.fillEllipse (c.x - rad, c.y - rad, rad * 2.0f, rad * 2.0f);
                g.setColour (juce::Colours::black.withAlpha (0.45f)); g.drawEllipse (c.x - rad, c.y - rad, rad * 2.0f, rad * 2.0f, 0.9f);
                // neutral macro label below (no branding)
                g.setColour (fiz::kDim); g.setFont (toi::uiFont (6.0f, true));
                g.drawText (ML[i], juce::Rectangle<float> (rMacro_.getX() + (float) i * mw, rMacro_.getBottom() - 8.0f, mw, 8.0f), juce::Justification::centred);
            }
        }

        // top-right tagline + brand
        g.setColour (fiz::kDim); g.setFont (toi::uiFont (7.0f, true).withExtraKerningFactor (0.22f));
        g.drawText ("REALTIME  TRANSWAVE  SYNTH", juce::Rectangle<float> (rPanel.getRight() - 280.0f, rPanel.getY() + 4.0f, 272.0f, 10.0f), juce::Justification::centredRight);
        auto bh = rBrand_;
        drawViewLeds (g, bh.removeFromTop (22.0f));
        bh.removeFromTop (2.0f);
        g.setColour (fiz::kInk); g.setFont (toi::uiFont (15.0f, true));
        g.drawText ("JW-FIZ", bh, juce::Justification::centred);
    }

    void drawCloud (juce::Graphics& g, float cx, float cy, float rad, juce::Colour col)
    {
        juce::ColourGradient cg (col, cx, cy, col.withAlpha (0.0f), cx + rad, cy, true);
        g.setGradientFill (cg); g.fillEllipse (cx - rad, cy - rad, rad * 2.0f, rad * 2.0f);
    }

    void layoutPanel (juce::Rectangle<float> panel) override
    {
        rPanel = panel;
        auto inner = rPanel.reduced (12.0f, 8.0f);
        inner.removeFromTop (6.0f);   // breathing room under the top tagline

        rowA_ = inner.removeFromTop (58.0f);
        inner.removeFromTop (3.0f);
        rowB_ = inner.removeFromTop (58.0f);
        inner.removeFromTop (4.0f);

        // display band: transwave morph (left) + red LCD scope (right) - bigger, it's a headline feature
        auto disp = inner.removeFromTop (38.0f);
        rWave_ = disp.removeFromLeft (disp.getWidth() * 0.62f).withTrimmedTop (6.0f);
        placeInArtboard (*wave_, rWave_);
        disp.removeFromLeft (12.0f);
        auto sc = disp.withTrimmedTop (10.0f);
        placeInArtboard (*scope_, sc);
        inner.removeFromTop (5.0f);

        // bottom: black strip with F-I-Z-M-O macros (left) + presets + RAND/SAVE + brand (right)
        rStrip_ = inner;
        auto strip = rStrip_.reduced (8.0f, 5.0f);
        rBrand_ = strip.removeFromRight (140.0f); strip.removeFromRight (8.0f);
        auto rs = strip.removeFromRight (70.0f); strip.removeFromRight (8.0f);
        rMacro_ = strip.removeFromLeft (360.0f); strip.removeFromLeft (10.0f);
        {
            const float mw = rMacro_.getWidth() / 5.0f;
            const float msz = rowA_.getHeight() - 22.0f;   // EXACT same diameter as the main knobs
            for (int i = 0; i < 5; ++i)
            { auto cell = juce::Rectangle<float> (rMacro_.getX() + (float) i * mw, rMacro_.getY(), mw, rMacro_.getHeight() - 9.0f);
              const float sz = juce::jmin (juce::jmin (mw - 6.0f, cell.getHeight()), msz);
              placeInArtboard (*macros_[(size_t) i], cell.withSizeKeepingCentre (sz, sz)); }
        }
        // presets (the middle remaining space): 2x8
        auto pr = strip;
        { const int pc = 8; const float pgap = 3.0f;
          const float pw = (pr.getWidth() - pgap * (pc - 1)) / (float) pc;
          const float ph = (pr.getHeight() - pgap) * 0.5f;
          for (int i = 0; i < 16; ++i) { const int rr = i / pc, cc = i % pc; placeInArtboard (*slots_[(size_t) i], juce::Rectangle<float> (pr.getX() + (float) cc * (pw + pgap), pr.getY() + (float) rr * (ph + pgap), pw, ph)); } }
        { auto rsi = rs.reduced (0.0f, 2.0f); const float bh = (rsi.getHeight() - 3.0f) * 0.5f;
          placeInArtboard (*rand_, rsi.removeFromTop (bh)); rsi.removeFromTop (3.0f); placeInArtboard (*save_, rsi.removeFromTop (bh)); }

        layoutGroups (groupsA_, rowA_);
        layoutGroups (groupsB_, rowB_);
    }

private:
    struct Group { juce::String name; std::vector<juce::String> ids; juce::Rectangle<float> rect; };

    void addKnob (const juce::String& id, int style)
    {
        juce::ignoreUnused (style);
        auto k = std::make_unique<FizKnob>();   // black knob + big silver centre cap (Jade's ref)
        if (auto* prm = findParam (id)) k->attach (*prm);
        addAndMakeVisible (*k); knobMap_[id] = k.get(); knobs_.push_back (std::move (k));
    }
    int totalKnobs (const std::vector<Group>& gs) const { int n = 0; for (auto& g : gs) n += (int) g.ids.size(); return n; }
    FizKnob* knobFor (const juce::String& id) const { auto it = knobMap_.find (id); return it == knobMap_.end() ? nullptr : it->second; }

    void layoutGroups (std::vector<Group>& gs, juce::Rectangle<float> row)
    {
        const int n = totalKnobs (gs);
        const float gap = 7.0f;
        const float usable = row.getWidth() - gap * (float) (gs.size() - 1);
        const float kw = usable / (float) n;
        float x = row.getX();
        for (auto& grp : gs)
        {
            const float gwidth = kw * (float) grp.ids.size();
            grp.rect = juce::Rectangle<float> (x, row.getY(), gwidth, row.getHeight());
            for (int i = 0; i < (int) grp.ids.size(); ++i)
                if (auto* k = knobFor (grp.ids[(size_t) i]))
                { auto cell = juce::Rectangle<float> (x + (float) i * kw, row.getY() + 11.0f, kw, row.getHeight() - 22.0f).reduced (2.0f, 0.0f);
                  placeInArtboard (*k, cell.withSizeKeepingCentre (juce::jmin (cell.getWidth(), cell.getHeight()), juce::jmin (cell.getWidth(), cell.getHeight()))); }
            x += gwidth + gap;
        }
    }

    void drawGroupBox (juce::Graphics& g, const Group& grp)
    {
        g.setColour (fiz::kBox); g.fillRoundedRectangle (grp.rect, 4.0f);
        g.setColour (fiz::kBoxHi.withAlpha (0.4f)); g.drawRoundedRectangle (grp.rect, 4.0f, 1.0f);
        g.setColour (fiz::kInk); g.setFont (toi::uiFont (7.0f, true).withExtraKerningFactor (0.08f));
        g.drawText (grp.name, grp.rect.withHeight (10.0f).reduced (5.0f, 1.0f), juce::Justification::centredLeft);
        // silver circle mounts behind each knob + the knob labels
        const float kw = grp.rect.getWidth() / (float) grp.ids.size();
        for (int i = 0; i < (int) grp.ids.size(); ++i)
        {
            if (auto* k = knobFor (grp.ids[(size_t) i]))
            {
                auto kr = k->getBounds().toFloat(); auto cc = kr.getCentre(); const float rad = kr.getWidth() * 0.50f;
                juce::ColourGradient mount (fiz::kSilver, cc.x, cc.y - rad, fiz::kSilverLo, cc.x, cc.y + rad, false);
                g.setGradientFill (mount); g.fillEllipse (cc.x - rad, cc.y - rad, rad * 2.0f, rad * 2.0f);
                g.setColour (juce::Colours::black.withAlpha (0.45f)); g.drawEllipse (cc.x - rad, cc.y - rad, rad * 2.0f, rad * 2.0f, 0.9f);
            }
            juce::String lbl; for (auto& sp : config().params) if (sp.id == grp.ids[(size_t) i]) { lbl = sp.label; break; }
            g.setColour (fiz::kDim); g.setFont (toi::uiFont (6.0f, true));
            g.drawText (lbl, juce::Rectangle<float> (grp.rect.getX() + (float) i * kw, grp.rect.getBottom() - 9.0f, kw, 8.0f), juce::Justification::centred);
        }
    }

    std::vector<std::unique_ptr<FizKnob>> knobs_;
    std::map<juce::String, FizKnob*> knobMap_;
    std::vector<std::unique_ptr<FizKnob>> macros_;
    std::unique_ptr<FizWaveView> wave_;
    std::unique_ptr<toi::Lcd> scope_;
    std::vector<std::unique_ptr<toi::MoldedButton>> slots_;
    std::unique_ptr<FizFunc> rand_, save_;
    std::vector<Group> groupsA_, groupsB_;
    juce::Image grain_;
    juce::Rectangle<float> rPanel, rowA_, rowB_, rWave_, rStrip_, rMacro_, rBrand_;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JWFIZEditor)
};

//==============================================================================
class JWFIZPlugin  : public cmaj::plugin::GeneratedPlugin<::JWFIZ>,
                     public toi::AudioTapSource,
                     public toi::PresetStore
{
public:
    using Base = cmaj::plugin::GeneratedPlugin<::JWFIZ>;
    JWFIZPlugin (std::shared_ptr<cmaj::Patch> p) : Base (std::move (p)) {}
    juce::AudioProcessorEditor* createEditor() override { return new JWFIZEditor (*this, keyboardState); }
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
