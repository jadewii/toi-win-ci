// JW-CS80 native faceplate (expressive dual-layer 8-voice poly) on the toi_faceplate.h kit.
// FAITHFUL CS-80 look (Jade ref 2026-05-27): WOOD end-cheeks, a DARK SILVER-GRAY textured panel,
// two CHANNEL rows (I / II) of COLOUR-CAPPED sliders (white/green/red/yellow like the real CS-80),
// a global strip, and the CS-80 SQUARE COLOUR tone-buttons as the preset row. NO brand names.
#pragma once

#include "toi_faceplate.h"

struct CS80;

namespace cs80
{
    static const juce::Colour kWood   { 0xff7a4a28 };   // warm wood end-cheeks
    static const juce::Colour kWoodLo { 0xff4a2c16 };
    static const juce::Colour kPanel  { 0xff3c3e43 };   // dark silver-gray panel
    static const juce::Colour kPanelLo{ 0xff303237 };
    static const juce::Colour kFrame  { 0xff0a0b0d };
    static const juce::Colour kTrack  { 0xff1c1d20 };   // recessed slider track
    static const juce::Colour kWhite  { 0xffe7e9ec };   // labels + white caps
    static const juce::Colour kWhiteDim{ 0xffa6a9ae };
    static const juce::Colour kOrange { 0xffe0691c };   // I/II tabs + accents
    static const juce::Colour kGreen  { 0xff1f8a4e };   // cutoff caps - DEEP emerald (not lime)
    static const juce::Colour kRed    { 0xffc63a2e };   // resonance caps - brick red
    static const juce::Colour kYellow { 0xffe8c441 };   // release caps / tone buttons
    static const juce::Colour kCream  { 0xffe7e2d4 };   // tone buttons
}

//==============================================================================
// CS-80 slider: COLOUR-CODED cap with a white centre line, thin dark track, label above.
class CS80Fader  : public juce::Component
{
public:
    CS80Fader (const juce::String& labelText, juce::Colour cap, const toi::Palette& palette)
        : label (labelText), capCol (cap), pal (palette)
    {
        slider.setSliderStyle (juce::Slider::LinearVertical);
        slider.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
        slider.setLookAndFeel (&laf);
        slider.setRange (0.0, 1.0, 0.0);
        slider.setDoubleClickReturnValue (true, 0.5);
        addAndMakeVisible (slider);
    }
    ~CS80Fader() override { slider.setLookAndFeel (nullptr); }
    void attach (juce::AudioProcessorParameter& p)
    { att = std::make_unique<toi::ParamKnobAttachment> (p, slider); slider.setDoubleClickReturnValue (true, p.getDefaultValue()); slider.onValueChange = [this] { repaint(); }; repaint(); }
    void resized() override { slider.setBounds (getLocalBounds().withTrimmedBottom ((int) labelH)); }
    void paint (juce::Graphics& g) override
    {
        auto b = getLocalBounds().toFloat();
        auto la = b.removeFromBottom (labelH);
        g.setColour (pal.text); g.setFont (toi::uiFont (7.0f, true)); g.drawText (label, la, juce::Justification::centred);
        auto ta = b.reduced (0.0f, 2.0f);
        const float cx = ta.getCentreX(), top = ta.getY(), h = ta.getHeight();
        // THIN slider: narrow cap riding a visible slot; the ladder scale stays BEHIND it.
        const float rungHalf = 12.0f, thumbW = 19.0f, thumbH = 18.0f, pad = thumbH * 0.5f + 1.0f;
        // 1) ladder rungs FIRST (behind everything) - the CS-80 graduated scale
        const int nT = juce::jmax (5, (int) std::round (h / 13.0f));
        for (int i = 0; i < nT; ++i)
        {
            const float ry = top + (h - 1.0f) * (float) i / (float) (nT - 1);
            g.setColour (juce::Colours::black.withAlpha (0.5f));  g.drawLine (cx - rungHalf, ry + 0.8f, cx + rungHalf, ry + 0.8f, 1.3f);
            g.setColour (cs80::kWhiteDim.withAlpha (0.5f));       g.drawLine (cx - rungHalf, ry,        cx + rungHalf, ry,        1.1f);
        }
        // 2) the slider line (vertical slot) ON TOP of the rungs
        g.setColour (juce::Colours::black.withAlpha (0.85f)); g.fillRect (juce::Rectangle<float> (cx - 1.3f, top, 2.6f, h));
        g.setColour (juce::Colours::white.withAlpha (0.10f)); g.drawVerticalLine ((int) (cx + 1.5f), top, top + h);
        // 3) the narrow colour cap (molded, dark centre groove)
        const float v = juce::jlimit (0.0f, 1.0f, (float) slider.getValue());
        const float ty = top + pad + (1.0f - v) * (h - 2.0f * pad);
        juce::Rectangle<float> cap (cx - thumbW * 0.5f, ty - thumbH * 0.5f, thumbW, thumbH);
        g.setColour (juce::Colours::black.withAlpha (0.5f)); g.fillRoundedRectangle (cap.translated (0.0f, 1.5f), 2.0f);
        juce::ColourGradient cg (capCol.brighter (0.22f), cx, cap.getY(), capCol.darker (0.26f), cx, cap.getBottom(), false);
        g.setGradientFill (cg); g.fillRoundedRectangle (cap, 2.0f);
        g.setColour (juce::Colours::white.withAlpha (0.32f)); g.drawLine (cap.getX() + 2.0f, cap.getY() + 1.3f, cap.getRight() - 2.0f, cap.getY() + 1.3f, 1.0f);
        g.setColour (juce::Colours::black.withAlpha (0.6f));  g.drawRoundedRectangle (cap, 2.0f, 1.0f);
        g.setColour (juce::Colours::black.withAlpha (0.45f)); g.drawLine (cap.getX() + 3.0f, cap.getCentreY(), cap.getRight() - 3.0f, cap.getCentreY(), 1.4f);
    }
    juce::Slider slider;
private:
    static constexpr float labelH = 11.0f;
    toi::InvisibleLinearLAF laf; juce::String label; juce::Colour capCol; toi::Palette pal;
    std::unique_ptr<toi::ParamKnobAttachment> att;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CS80Fader)
};


//==============================================================================
class CS80FuncButton  : public juce::Button
{
public:
    CS80FuncButton (const juce::String& text, juce::Colour fill) : juce::Button (text), col (fill) { setButtonText (text); }
    void flash() { flashing = true; repaint(); juce::Timer::callAfterDelay (160, [s = juce::Component::SafePointer<CS80FuncButton> (this)] { if (s) { s->flashing = false; s->repaint(); } }); }
    void paintButton (juce::Graphics& g, bool over, bool down) override
    {
        auto b = getLocalBounds().toFloat().reduced (1.0f);
        auto fill = flashing ? col.brighter (0.3f) : down ? col.darker (0.18f) : over ? col.brighter (0.08f) : col;
        g.setColour (fill); g.fillRoundedRectangle (b, 2.5f);
        g.setColour (juce::Colours::black.withAlpha (0.4f)); g.drawRoundedRectangle (b, 2.5f, 1.0f);
        g.setColour (juce::Colour (0xff201810)); g.setFont (toi::uiFont (juce::jmin (10.0f, b.getHeight() * 0.5f), true));
        g.drawText (getButtonText(), getLocalBounds(), juce::Justification::centred);
    }
private:
    juce::Colour col; bool flashing = false;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CS80FuncButton)
};

//==============================================================================
inline toi::Config cs80Config()
{
    toi::Config c;
    c.model = "JW-CS80";
    auto& p = c.pal;
    p.bg = cs80::kWood; p.bg2 = cs80::kWoodLo; p.frame = cs80::kFrame; p.ink = cs80::kFrame;
    p.accent = cs80::kOrange; p.accent2 = cs80::kOrange; p.button = juce::Colour (0xff26282c);
    p.thumb = cs80::kWhite; p.text = cs80::kWhite;
    p.noteStrip = cs80::kPanel;
    p.keyWhite = juce::Colour (0xffEDEDEA); p.keyWhitePr = juce::Colour (0xfff2cf9a);
    p.keyBlack = juce::Colour (0xff14110d); p.keyBlackPr = cs80::kOrange;

    c.params = {
        { "lfoRate","RATE" }, { "lfoShape","SHAPE" },
        { "c1Wave","WAVE" }, { "c1PW","PW" }, { "c1Hpf","HPF" }, { "c1HpfR","RES" }, { "c1Lpf","LPF" }, { "c1LpfR","RES" }, { "c1FEnv","F-ENV" }, { "c1A","A" }, { "c1D","D" }, { "c1S","S" }, { "c1R","R" }, { "c1Brill","BRILL" }, { "c1Level","LEVEL" },
        { "c2Wave","WAVE" }, { "c2PW","PW" }, { "c2Hpf","HPF" }, { "c2HpfR","RES" }, { "c2Lpf","LPF" }, { "c2LpfR","RES" }, { "c2FEnv","F-ENV" }, { "c2A","A" }, { "c2D","D" }, { "c2S","S" }, { "c2R","R" }, { "c2Brill","BRILL" }, { "c2Level","LEVEL" },
        { "detune","DETUNE" }, { "mix","MIX" }, { "ring","RING" }, { "sub","SUB" }, { "touchBrill","TOUCH" }, { "volume","VOLUME" }, { "tune","TUNE" },
    };

    // placeholder banks (final presets baked later via the BAKE button). P() = a few musical knobs,
    // the rest from the smooth-pad defaults. Order matches c.params.
    auto P = [] (const char* nm, float c1w,float c1lpf,float c1lr,float c1fe,float c1a,float c1r,float c1br,
                 float c2w,float c2lpf,float c2a,float detune,float mix,float ring,float sub)
    {
        return toi::FactoryPreset { nm, {
            0.25f,0.0f,
            c1w,0.5f,0.0f,0.1f,c1lpf,c1lr,c1fe,c1a,0.5f,0.75f,c1r,c1br,0.80f,
            c2w,0.5f,0.0f,0.1f,c2lpf,0.2f,0.35f,c2a,0.5f,0.75f,0.55f,0.50f,0.75f,
            detune,mix,ring,sub,0.30f,0.80f,0.50f } };
    };
    c.factory = {
        P("STRINGS",  0.0,0.50,0.18,0.30,0.40,0.55,0.55, 0.0,0.48,0.45,0.35,0.5,0.0,0.0),
        P("BRASS",    0.0,0.55,0.25,0.55,0.10,0.30,0.55, 0.0,0.52,0.12,0.20,0.5,0.0,0.0),
        P("CHOIR",    0.0,0.45,0.18,0.25,0.55,0.65,0.50, 0.0,0.44,0.55,0.45,0.5,0.0,0.0),
        P("VOX LEAD", 1.0,0.62,0.35,0.45,0.06,0.30,0.60, 0.0,0.55,0.06,0.15,0.4,0.0,0.0),
        P("BIG PAD",  0.0,0.42,0.20,0.30,0.60,0.75,0.50, 1.0,0.40,0.60,0.55,0.5,0.0,0.0),
        P("RING BELL",0.0,0.55,0.30,0.40,0.02,0.50,0.55, 0.0,0.62,0.02,0.30,0.5,0.6,0.0),
        P("SUB BRASS",0.0,0.48,0.25,0.55,0.05,0.35,0.55, 0.0,0.40,0.05,0.18,0.5,0.0,0.6),
        P("SOFT KEYS",0.0,0.52,0.18,0.40,0.02,0.40,0.50, 1.0,0.50,0.02,0.20,0.5,0.0,0.0),
        P("CINEMATIC",0.0,0.38,0.22,0.35,0.70,0.80,0.45, 0.0,0.36,0.70,0.6,0.5,0.0,0.0),
        P("DETUNE STK",0.0,0.55,0.20,0.30,0.20,0.50,0.55, 0.0,0.53,0.20,0.7,0.5,0.0,0.0),
        P("HOLLOW",   1.0,0.50,0.20,0.30,0.30,0.50,0.50, 1.0,0.48,0.30,0.30,0.5,0.0,0.0),
        P("SWEEP",    0.0,0.30,0.40,0.70,0.40,0.60,0.45, 0.0,0.30,0.40,0.4,0.5,0.0,0.0),
        P("RESO LEAD",0.0,0.60,0.55,0.55,0.02,0.35,0.60, 0.0,0.58,0.02,0.15,0.4,0.0,0.0),
        P("WARM STR", 0.0,0.46,0.18,0.28,0.45,0.65,0.50, 0.0,0.44,0.50,0.45,0.5,0.0,0.0),
        P("ALIEN",    1.0,0.55,0.30,0.40,0.10,0.50,0.55, 1.0,0.60,0.10,0.50,0.5,0.7,0.0),
    };
    return c;
}

//==============================================================================
class CS80Editor  : public toi::PanelEditor
{
public:
    CS80Editor (juce::AudioProcessor& proc, juce::MidiKeyboardState& kb)
        : toi::PanelEditor (proc, kb, cs80Config())
    {
        cheekInset = 18.0f;
        grain_ = makeGrain (96, 96);
        // colour scheme per slider role
        auto W = cs80::kWhite, GR = cs80::kGreen, RD = cs80::kRed, YL = cs80::kYellow;
        // Channel I + II banks (13 each): WAVE PW HPF RES LPF RES F-ENV A D S R BRILL LEVEL
        const juce::Colour caps[13] = { W, W, GR, RD, GR, RD, W, W, W, W, YL, GR, W };
        const char* ids1[13] = { "c1Wave","c1PW","c1Hpf","c1HpfR","c1Lpf","c1LpfR","c1FEnv","c1A","c1D","c1S","c1R","c1Brill","c1Level" };
        const char* ids2[13] = { "c2Wave","c2PW","c2Hpf","c2HpfR","c2Lpf","c2LpfR","c2FEnv","c2A","c2D","c2S","c2R","c2Brill","c2Level" };
        const char* lbls[13] = { "WAVE","PW","HPF","RES","LPF","RES","ENV","A","D","S","R","BRIL","LVL" };
        for (int i = 0; i < 13; ++i) { addFader (ids1[i], lbls[i], caps[i], fCh1); addFader (ids2[i], lbls[i], caps[i], fCh2); }

        // global strip
        const char* gid[9]  = { "lfoRate","lfoShape","detune","mix","ring","sub","touchBrill","volume","tune" };
        const char* glb[9]  = { "LFO","SHAPE","DETUNE","MIX","RING","SUB","TOUCH","VOL","TUNE" };
        const juce::Colour gc[9] = { W, W, GR, GR, RD, W, YL, W, W };
        for (int i = 0; i < 9; ++i) addFader (gid[i], glb[i], gc[i], fGlob);

        // 16 molded square CS-80 colour tone-buttons (just the colour boxes; lit brighter when selected)
        const juce::Colour tone[5] = { cs80::kYellow, cs80::kOrange, cs80::kRed, cs80::kGreen, cs80::kCream };
        for (int i = 0; i < 16; ++i)
        { auto col = tone[i % 5]; auto b = std::make_unique<toi::MoldedButton> (col); b->setLit (col.brighter (0.45f)); const int idx = i; b->onClick = [this, idx] { recallSlot (idx); }; addAndMakeVisible (*b); slots.push_back (std::move (b)); }
        rand_ = std::make_unique<CS80FuncButton> ("RAND", cs80::kYellow);
        save_ = std::make_unique<CS80FuncButton> ("SAVE", cs80::kGreen);
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
        juce::Random r (820);
        for (int y = 0; y < h; ++y) for (int x = 0; x < w; ++x)
        { const float n = r.nextFloat(); if (n > 0.66f) { const float a = (n - 0.66f) / 0.34f * 0.06f; const bool light = r.nextBool();
            img.setPixelAt (x, y, (light ? juce::Colours::white : juce::Colours::black).withAlpha (a)); } }
        return img;
    }
    void paintPanel (juce::Graphics& g, juce::Rectangle<float> panel) override
    {
        juce::ignoreUnused (panel);
        juce::ColourGradient pg (cs80::kPanel, rPanel.getCentreX(), rPanel.getY(), cs80::kPanelLo, rPanel.getCentreX(), rPanel.getBottom(), false);
        g.setGradientFill (pg); g.fillRoundedRectangle (rPanel, 5.0f);
        if (grain_.isValid()) { g.setFillType (juce::FillType (grain_, juce::AffineTransform::translation (rPanel.getX(), rPanel.getY()))); g.fillRoundedRectangle (rPanel, 5.0f); }
        g.setColour (juce::Colours::black); g.drawRoundedRectangle (rPanel, 5.0f, 1.5f);
        g.setColour (juce::Colours::white.withAlpha (0.05f)); g.drawRoundedRectangle (rPanel.reduced (1.5f), 4.0f, 1.0f);

        // group headers + thin dividers between Channel I / Channel II / Global
        g.setColour (cs80::kOrange); g.setFont (toi::uiFont (8.5f, true).withExtraKerningFactor (0.18f));
        g.drawText ("CHANNEL I",  rHdrI,  juce::Justification::centred);
        g.drawText ("CHANNEL II", rHdrII, juce::Justification::centred);
        g.setColour (cs80::kWhiteDim);
        g.drawText ("GLOBAL", rHdrG, juce::Justification::centred);
        g.setColour (juce::Colours::black.withAlpha (0.45f));
        g.drawLine (divX1, rRow.getY() + 2.0f, divX1, rRow.getBottom() - 2.0f, 1.2f);
        g.drawLine (divX2, rRow.getY() + 2.0f, divX2, rRow.getBottom() - 2.0f, 1.2f);
        g.setColour (juce::Colours::white.withAlpha (0.06f));
        g.drawLine (divX1 + 1.0f, rRow.getY() + 2.0f, divX1 + 1.0f, rRow.getBottom() - 2.0f, 1.0f);
        g.drawLine (divX2 + 1.0f, rRow.getY() + 2.0f, divX2 + 1.0f, rRow.getBottom() - 2.0f, 1.0f);

        g.setColour (cs80::kWhiteDim); g.setFont (toi::uiFont (7.0f, true).withExtraKerningFactor (0.10f));
        g.drawText ("TONE", rProgLbl, juce::Justification::centredLeft);

        // brand block (MODULE / SIZE view LEDs on top, then the model mark)
        auto bh = rBrandHdr;
        drawViewLeds (g, bh.removeFromTop (18.0f));
        g.setColour (cs80::kWhite); g.setFont (toi::uiFont (15.0f, true));
        g.drawText ("JW-CS80", bh.removeFromTop (16.0f), juce::Justification::centred);
        g.setColour (cs80::kWhiteDim); g.setFont (toi::uiFont (5.5f, true).withExtraKerningFactor (0.2f));
        g.drawText ("TOI - plugin corp", bh.removeFromTop (8.0f), juce::Justification::centred);
    }

    void layoutPanel (juce::Rectangle<float> panel) override
    {
        rPanel = juce::Rectangle<float> (panel.getX() + cheekInset, panel.getY(), panel.getWidth() - 2.0f * cheekInset, panel.getHeight());
        auto inner = rPanel.reduced (8.0f, 5.0f);

        // bottom strip: TONE label + 16 colour tone-buttons + RAND/SAVE + brand (with view LEDs)
        rProg = inner.removeFromBottom (44.0f);
        inner.removeFromBottom (3.0f);
        {
            auto pr = rProg.reduced (3.0f, 2.0f);
            rBrandHdr = pr.removeFromRight (150.0f);
            pr.removeFromRight (8.0f);
            auto rs = pr.removeFromRight (92.0f).reduced (0.0f, 8.0f);
            placeInArtboard (*rand_, rs.removeFromLeft (44.0f).reduced (2.0f, 0.0f));
            placeInArtboard (*save_, rs.reduced (2.0f, 0.0f));
            pr.removeFromRight (8.0f);
            rProgLbl = pr.removeFromLeft (34.0f);
            pr.removeFromLeft (3.0f);
            auto tb = pr.reduced (0.0f, 3.0f);
            const float gap = 3.0f, cw = (tb.getWidth() - gap * 15.0f) / 16.0f;
            for (int i = 0; i < 16; ++i)
                placeInArtboard (*slots[(size_t) i], juce::Rectangle<float> (tb.getX() + i * (cw + gap), tb.getY(), cw, tb.getHeight()));
        }

        // group-header band (CHANNEL I / CHANNEL II / GLOBAL) above the single fader row
        auto header = inner.removeFromTop (11.0f);
        inner.removeFromTop (2.0f);

        // ONE tall row of ALL 35 thin sliders: Channel I (13) | Channel II (13) | Global (9)
        rRow = inner;
        const int total = (int) (fCh1.size() + fCh2.size() + fGlob.size());
        const float pitch = rRow.getWidth() / (float) total;
        int col = 0;
        auto placeRow = [&] (std::vector<std::unique_ptr<CS80Fader>>& v)
        { for (auto& f : v) { placeInArtboard (*f, juce::Rectangle<float> (rRow.getX() + col * pitch, rRow.getY(), pitch, rRow.getHeight())); ++col; } };
        placeRow (fCh1); placeRow (fCh2); placeRow (fGlob);

        const int n1 = (int) fCh1.size(), n2 = (int) fCh2.size();
        divX1 = rRow.getX() + n1 * pitch;
        divX2 = rRow.getX() + (n1 + n2) * pitch;
        rHdrI  = juce::Rectangle<float> (rRow.getX(),               header.getY(), n1 * pitch, header.getHeight());
        rHdrII = juce::Rectangle<float> (divX1,                     header.getY(), n2 * pitch, header.getHeight());
        rHdrG  = juce::Rectangle<float> (divX2,                     header.getY(), rRow.getRight() - divX2, header.getHeight());
    }

private:
    void addFader (const juce::String& id, const juce::String& label, juce::Colour cap, std::vector<std::unique_ptr<CS80Fader>>& dst)
    { auto f = std::make_unique<CS80Fader> (label, cap, pal()); if (auto* prm = findParam (id)) f->attach (*prm); addAndMakeVisible (*f); dst.push_back (std::move (f)); }

    std::vector<std::unique_ptr<CS80Fader>> fCh1, fCh2, fGlob;
    std::vector<std::unique_ptr<toi::MoldedButton>> slots;
    std::unique_ptr<CS80FuncButton> rand_, save_;
    juce::Image grain_;
    float divX1 = 0.0f, divX2 = 0.0f;
    juce::Rectangle<float> rPanel, rRow, rHdrI, rHdrII, rHdrG, rProg, rProgLbl, rBrandHdr;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CS80Editor)
};

//==============================================================================
class CS80Plugin  : public cmaj::plugin::GeneratedPlugin<::CS80>,
                    public toi::AudioTapSource,
                    public toi::PresetStore
{
public:
    using Base = cmaj::plugin::GeneratedPlugin<::CS80>;
    CS80Plugin (std::shared_ptr<cmaj::Patch> p) : Base (std::move (p)) {}
    juce::AudioProcessorEditor* createEditor() override { return new CS80Editor (*this, keyboardState); }
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
