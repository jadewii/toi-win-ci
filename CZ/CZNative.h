// JW-CZ native faceplate (CZ-101 hardware look). Built on the Cmajor-free
// toi_faceplate.h kit. Included by cmajor_plugin.cpp AFTER the cmaj headers.
// EVERY control is functional - no cosmetic/pretend buttons.
#pragma once

#include "toi_faceplate.h"

//==============================================================================
inline toi::Config czConfig()
{
    toi::Config c;
    c.model = "JW-CZ";
    auto& p = c.pal;
    p.bg        = juce::Colour (0xff9aa2b4);   // cool blue-gray body
    p.bg2       = juce::Colour (0xff7e869a);
    p.frame     = juce::Colour (0xff20232c);
    p.ink       = juce::Colour (0xff20232c);
    p.accent    = juce::Colour (0xff5e78b6);   // blue
    p.accent2   = juce::Colour (0xffd8a436);   // gold (brand only)
    p.button    = juce::Colour (0xff8e8e8e);   // gray metal knob body
    p.thumb     = juce::Colour (0xffe2e6ee);
    p.text      = juce::Colour (0xffd8a436);
    p.keyWhite  = juce::Colour (0xffece9e2);
    p.keyWhitePr= juce::Colour (0xffbcd0f0);
    p.keyBlack  = juce::Colour (0xff5e78b6);   // no black keys
    p.keyBlackPr= juce::Colour (0xff93a8de);
    p.lcdBg     = juce::Colour (0xff14181a);
    p.lcdInk    = juce::Colour (0xff7a9ad8);

    // ids MUST match the CZ.cmajor endpoint names. (order = factory-preset value order)
    c.params = {
        { "dcw1", "DCW 1" }, { "dcw2", "DCW 2" }, { "resonance", "RESO" }, { "tone", "TONE" },
        { "wave1", "WAVE 1", 0.0f, 7.0f }, { "dcwAttack", "DCW A", 0.001f, 2.0f }, { "attack", "ATTACK", 0.001f, 2.0f },
        { "wave2", "WAVE 2", 0.0f, 7.0f }, { "dcwDecay", "DCW D", 0.01f, 8.0f },  { "decay", "DECAY", 0.01f, 8.0f },
        { "detune", "DETUNE" }, { "octave", "OCTAVE" }, { "mix", "MIX" }, { "dcwSustain", "DCW S" }, { "sustain", "SUSTAIN" }, { "release", "RELEASE", 0.01f, 4.0f },
        { "ring", "RING" }, { "noise", "NOISE" },
        // deep EDIT-page params (appended -> factory presets above load them at their cmajor init default)
        { "vibratoRate", "VIB RATE" }, { "vibratoDepth", "VIB DEPTH" }, { "vibratoDelay", "VIB DELAY" }, { "vibWave", "VIB WAVE" }, { "glide", "GLIDE" },
        { "dcwKey", "DCW KEY" }, { "velDcw", "VEL > DCW" }, { "velAmp", "VEL > AMP" },
    };

    // 16 factory voicings (real units, in c.params order). The preset buttons load these.
    // TIMBRE (wave + DCW + tone) was MEASURED from Jade's real CZ-101 recordings (full.wav)
    // by fitting each captured note to the phase-distortion model (median 0.99 cosine sim);
    // the envelope ROLE (bass/pluck/keys/pad/lead) is curated because the short captured notes
    // can't give reliable envelopes. The 3 reso patches are hand-set (the reso fit is weak).
    auto P = [] (const char* nm, float dcw1,float dcw2,float reso,float tone,float w1,float dcwA,float atk,
                 float w2,float dcwD,float dcy,float det,float oct,float mix,float dcwS,float sus,float rel,float ring,float noise)
    { return toi::FactoryPreset { nm, { dcw1,dcw2,reso,tone,w1,dcwA,atk,w2,dcwD,dcy,det,oct,mix,dcwS,sus,rel,ring,noise } }; };
    c.factory = {
        P("PULSE PAD", 0.97f,0.97f,0.25f,0.55f, 2, 0.008f,0.450f, 2, 1.50f,1.50f, 0.12f,0.500f,0.00f, 0.90f,0.85f,1.20f, 0,0),  // pulse sim=1.00
        P("SAW BASS", 0.88f,0.88f,0.25f,0.42f, 0, 0.008f,0.004f, 0, 0.55f,0.55f, 0.06f,0.375f,0.00f, 0.45f,0.35f,0.18f, 0,0),    // saw sim=1.00
        P("PULSE PLUCK", 0.84f,0.84f,0.25f,0.42f, 2, 0.008f,0.004f, 2, 0.45f,0.45f, 0.12f,0.500f,0.00f, 0.40f,0.12f,0.22f, 0,0), // pulse sim=1.00
        P("PULSE KEYS", 0.79f,0.79f,0.25f,0.42f, 2, 0.008f,0.010f, 2, 0.80f,0.80f, 0.12f,0.500f,0.00f, 0.80f,0.55f,0.45f, 0,0),  // pulse sim=1.00
        P("PULSE LEAD", 0.84f,0.84f,0.25f,0.42f, 2, 0.008f,0.020f, 2, 0.40f,0.40f, 0.12f,0.500f,0.00f, 0.85f,0.72f,0.30f, 0,0),  // pulse sim=1.00
        P("SQR PAD", 0.90f,0.90f,0.25f,0.66f, 1, 0.008f,0.450f, 1, 1.50f,1.50f, 0.12f,0.500f,0.00f, 0.90f,0.85f,1.20f, 0,0),     // square sim=1.00
        P("SAW PLUCK", 0.89f,0.89f,0.25f,0.42f, 0, 0.008f,0.004f, 0, 0.45f,0.45f, 0.12f,0.500f,0.00f, 0.40f,0.12f,0.22f, 0,0),   // saw sim=0.99
        P("SAW KEYS", 0.90f,0.90f,0.25f,0.45f, 0, 0.008f,0.010f, 0, 0.80f,0.80f, 0.12f,0.500f,0.00f, 0.80f,0.55f,0.45f, 0,0),    // saw sim=0.98
        P("SAW BASS 2", 0.89f,0.89f,0.25f,0.42f, 0, 0.008f,0.004f, 0, 0.55f,0.55f, 0.06f,0.375f,0.00f, 0.45f,0.35f,0.18f, 0,0),  // saw sim=0.98
        P("BELL PAD", 0.97f,0.97f,0.25f,0.42f, 3, 0.008f,0.450f, 3, 1.50f,1.50f, 0.12f,0.500f,0.00f, 0.90f,0.85f,1.20f, 0,0),    // dsine sim=1.00
        P("SINE LEAD", 0.06f,0.06f,0.25f,0.57f, 3, 0.008f,0.020f, 3, 0.40f,0.40f, 0.12f,0.500f,0.00f, 0.85f,0.72f,0.30f, 0,0),   // dsine sim=0.98
        P("BELL KEYS", 0.74f,0.74f,0.25f,0.42f, 3, 0.008f,0.010f, 3, 0.80f,0.80f, 0.12f,0.500f,0.00f, 0.80f,0.55f,0.45f, 0,0),   // dsine sim=0.97
        P("SINE PLUCK", 0.08f,0.08f,0.25f,0.42f, 3, 0.008f,0.004f, 3, 0.45f,0.45f, 0.12f,0.500f,0.00f, 0.40f,0.12f,0.22f, 0,0),  // dsine sim=1.00
        P("RESO BASS", 0.72f,0.72f,0.70f,0.50f, 5, 0.008f,0.004f, 5, 0.45f,0.45f, 0.06f,0.375f,0.00f, 0.30f,0.22f,0.22f, 0,0),   // hand-set (reso fit weak)
        P("RESO SWEEP", 0.88f,0.88f,0.62f,0.62f, 5, 0.008f,0.010f, 5, 2.20f,1.80f, 0.12f,0.500f,0.00f, 0.55f,0.62f,0.80f, 0,0),  // hand-set
        P("RESO LEAD", 0.80f,0.80f,0.70f,0.66f, 6, 0.008f,0.010f, 6, 0.40f,0.40f, 0.12f,0.500f,0.00f, 0.70f,0.72f,0.30f, 0,0),   // hand-set
    };
    return c;
}

//==============================================================================
// OG CZ-101 preset button: a longer tan rounded rectangle with a small red
// rectangle LED above it that lights when this slot is selected.
class CZPreset  : public juce::Button
{
public:
    explicit CZPreset (const toi::Palette& p) : juce::Button ("preset"), pal (p) {}
    void setActive (bool a) { if (active != a) { active = a; repaint(); } }
    void paintButton (juce::Graphics& g, bool over, bool down) override
    {
        auto b = getLocalBounds().toFloat().reduced (1.0f);
        // small red rectangle LED above
        auto led = b.removeFromTop (4.5f).withSizeKeepingCentre (b.getWidth() * 0.5f, 4.0f);
        if (active) { g.setColour (juce::Colour (0xffe05050).withAlpha (0.5f)); g.fillRoundedRectangle (led.expanded (2.0f, 1.5f), 2.5f); }
        g.setColour (active ? juce::Colour (0xffe05050) : juce::Colour (0xff4a4650)); g.fillRoundedRectangle (led, 1.5f);
        b.removeFromTop (1.5f);
        // gray chiclet - same look as the RING / NOISE buttons
        auto fill = down ? pal.button.darker (0.08f) : over ? pal.button.brighter (0.06f) : pal.button;
        g.setColour (fill); g.fillRoundedRectangle (b, 2.5f);
        g.setColour (juce::Colours::black.withAlpha (0.18f)); g.fillRect (b.withTop (b.getBottom() - 2.0f).reduced (2.0f, 0.0f));
        g.setColour (pal.ink); g.drawRoundedRectangle (b, 2.5f, 1.0f);
    }
private:
    toi::Palette pal; bool active = false;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CZPreset)
};

//==============================================================================
// Big draggable envelope editor for the EDIT page: drag the 3 handles to set
// attack / decay+sustain / release (release optional for the 3-stage DCW env).
class ADSREditor  : public juce::Component, private juce::Timer
{
public:
    ADSREditor (const juce::String& title, const toi::Palette& p) : title_ (title), pal (p) { startTimerHz (20); }
    ~ADSREditor() override { stopTimer(); }
    void setParams (juce::AudioProcessorParameter* a, juce::AudioProcessorParameter* d, juce::AudioProcessorParameter* s, juce::AudioProcessorParameter* r)
    { pa=a; pd=d; ps=s; pr=r; }

    void paint (juce::Graphics& g) override
    {
        auto b = getLocalBounds().toFloat();
        g.setColour (pal.lcdBg); g.fillRoundedRectangle (b, 4.0f);
        auto in = plot();
        const float top = in.getY(), bot = in.getBottom(), x0 = in.getX(), W = in.getWidth();
        // faint time / level grid so empty space reads as headroom, not blank
        g.setColour (pal.lcdInk.withAlpha (0.10f));
        for (int i = 1; i < 8; ++i) { const float gx = x0 + W * (float) i / 8.0f;          g.drawLine (gx, top, gx, bot, 0.6f); }
        for (int i = 1; i < 4; ++i) { const float gy = top + in.getHeight() * (float) i / 4.0f; g.drawLine (x0, gy, in.getRight(), gy, 0.6f); }
        const float a = pa?pa->getValue():0.2f, d = pd?pd->getValue():0.3f, s = ps?ps->getValue():0.6f, r = pr?pr->getValue():0.3f;
        const float right = x0 + W;
        hAx = x0 + a * segA (W);
        hDx = hAx + d * segD (W);
        hSy = bot - s * (bot - top);
        // sustain holds across the middle; release anchors at the RIGHT edge (DCW = no release -> holds to edge)
        hRx = pr ? juce::jmax (hDx + 4.0f, right - r * segR (W)) : right;
        juce::Path p; p.startNewSubPath (x0, bot); p.lineTo (hAx, top); p.lineTo (hDx, hSy); p.lineTo (hRx, hSy); if (pr) p.lineTo (right, bot);
        g.setColour (pal.accent.withAlpha (0.20f));
        { juce::Path fill = p; fill.lineTo (right, bot); fill.closeSubPath(); g.fillPath (fill); }
        g.setColour (pal.accent.withAlpha (0.35f)); g.strokePath (p, juce::PathStrokeType (4.0f));   // glow
        g.setColour (pal.lcdInk);                   g.strokePath (p, juce::PathStrokeType (2.0f));
        // stage letters along the base
        g.setColour (pal.text.withAlpha (0.65f)); g.setFont (toi::uiFont (7.0f, true));
        auto lab = [&] (float x, const char* t) { g.drawText (t, juce::Rectangle<float> (x-9.0f, bot+2.0f, 18.0f, 9.0f), juce::Justification::centred); };
        lab (hAx, "A"); lab (hDx, "D"); lab ((hDx + hRx) * 0.5f, "S"); if (pr) lab (hRx, "R");
        auto handle = [&] (float x, float y) { g.setColour (pal.thumb); g.fillEllipse (x-4,y-4,8,8); g.setColour (pal.ink); g.drawEllipse (x-4,y-4,8,8,1.5f); };
        handle (hAx, top); handle (hDx, hSy); if (pr) handle (hRx, hSy);
        g.setColour (pal.ink); g.drawRoundedRectangle (b.reduced (toi::STROKE*0.5f), 4.0f, toi::STROKE);
        g.setColour (pal.text); g.setFont (toi::uiFont (8.5f, true).withExtraKerningFactor (0.3f));
        g.drawText (title_, b.reduced (8,5).removeFromTop (12.0f), juce::Justification::topLeft);
    }
    void mouseDown (const juce::MouseEvent& e) override { drag = nearest (e.position); apply (e.position); }
    void mouseDrag (const juce::MouseEvent& e) override { apply (e.position); }
private:
    void timerCallback() override { repaint(); }
    juce::Rectangle<float> plot() const { return getLocalBounds().toFloat().reduced (10.0f, 14.0f).withTrimmedTop (4.0f); }
    // per-stage horizontal extents (attack/decay from the left, release from the right)
    float segA (float W) const { return W * (pr ? 0.22f : 0.30f); }
    float segD (float W) const { return W * (pr ? 0.26f : 0.34f); }
    float segR (float W) const { return W * 0.34f; }
    int nearest (juce::Point<float> pt)
    {
        auto in = plot();
        float dA=pt.getDistanceFrom({hAx,in.getY()});
        float dD=pt.getDistanceFrom({hDx,hSy}); float dR=pr?pt.getDistanceFrom({hRx,hSy}):1e9f;
        if (dA<=dD && dA<=dR) return 0; if (dD<=dR) return 1; return 2;
    }
    void setP (juce::AudioProcessorParameter* p, float v) { if (!p) return; v=juce::jlimit(0.0f,1.0f,v); p->beginChangeGesture(); p->setValueNotifyingHost(v); p->endChangeGesture(); }
    void apply (juce::Point<float> pt)
    {
        auto in = plot();
        const float right = in.getRight();
        if (drag==0) setP (pa, (pt.x - in.getX()) / segA (in.getWidth()));
        else if (drag==1) { setP (pd, (pt.x - hAx) / segD (in.getWidth())); setP (ps, (in.getBottom()-pt.y)/(in.getBottom()-in.getY())); }
        else if (pr) setP (pr, (right - pt.x) / segR (in.getWidth()));
    }
    juce::String title_; toi::Palette pal;
    juce::AudioProcessorParameter *pa=nullptr,*pd=nullptr,*ps=nullptr,*pr=nullptr;
    float hAx=0,hDx=0,hRx=0,hSy=0; int drag=0;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ADSREditor)
};

//==============================================================================
class CZEditor  : public toi::PanelEditor
{
public:
    CZEditor (juce::AudioProcessor& proc, juce::MidiKeyboardState& kb)
        : toi::PanelEditor (proc, kb, czConfig()), scope (pal())
    {
        auto knob = [this] (const juce::String& id, const juce::String& label)
        {
            auto k = std::make_unique<toi::StyledKnob> (label, pal(), toi::StyledKnob::Metal);
            if (auto* prm = findParam (id)) k->attach (*prm);
            addAndMakeVisible (*k); osc.push_back (std::move (k));
        };
        auto eslider = [this] (const juce::String& id, const juce::String& label, std::vector<std::unique_ptr<toi::StyledHSlider>>& dst)
        {
            auto h = std::make_unique<toi::StyledHSlider> (label, pal()); h->setShowLabel (true);
            if (auto* prm = findParam (id)) h->attach (*prm);
            addAndMakeVisible (*h); dst.push_back (std::move (h));
        };
        auto fader = [this] (const juce::String& id, const juce::String& label)
        {
            auto f = std::make_unique<toi::StyledFader> (label, pal());
            if (auto* prm = findParam (id)) f->attach (*prm);
            addAndMakeVisible (*f); faders.push_back (std::move (f));
        };
        fader ("dcw1","DCW 1"); fader ("dcw2","DCW 2"); fader ("resonance","RESO"); fader ("tone","TONE");
        knob ("wave1","WAVE 1"); knob ("wave2","WAVE 2"); knob ("detune","DETUNE"); knob ("octave","OCTAVE"); knob ("mix","MIX");
        eslider ("attack","ATTACK",ampEnv); eslider ("decay","DECAY",ampEnv); eslider ("sustain","SUSTAIN",ampEnv); eslider ("release","RELEASE",ampEnv);
        eslider ("dcwAttack","DCW A",dcwEnv); eslider ("dcwDecay","DCW D",dcwEnv); eslider ("dcwSustain","DCW S",dcwEnv);

        ring_  = std::make_unique<toi::Button> ("RING",  pal());
        noise_ = std::make_unique<toi::Button> ("NOISE", pal());
        ring_->onClick  = [this] { toggle ("ring");  ring_->flash(); };
        noise_->onClick = [this] { toggle ("noise"); noise_->flash(); };
        addAndMakeVisible (*ring_); addAndMakeVisible (*noise_);

        for (int i = 0; i < 16; ++i)   // 16 OG-style program buttons -> right column (load factory voicings)
        {
            auto b = std::make_unique<CZPreset> (pal());
            const int idx = i; b->onClick = [this, idx] { recallSlot (idx); };
            addAndMakeVisible (*b); slots.push_back (std::move (b));
        }
        rand_ = std::make_unique<toi::Button> ("RAND", pal());
        save_ = std::make_unique<toi::Button> ("SAVE", pal());
        rand_->onClick = [this] { doRandom(); rand_->flash(); };
        save_->onClick = [this] { saveSlot (activeSlot()); save_->flash(); };
        addAndMakeVisible (*rand_); addAndMakeVisible (*save_);
        addAndMakeVisible (scope); scope.attachScope (audioTap());
        ampEdit = std::make_unique<ADSREditor> ("AMP ENVELOPE", pal());
        ampEdit->setParams (findParam ("attack"), findParam ("decay"), findParam ("sustain"), findParam ("release"));
        dcwEdit = std::make_unique<ADSREditor> ("DCW ENVELOPE", pal());
        dcwEdit->setParams (findParam ("dcwAttack"), findParam ("dcwDecay"), findParam ("dcwSustain"), nullptr);
        addAndMakeVisible (*ampEdit); addAndMakeVisible (*dcwEdit);

        // EDIT-page deep controls: vibrato + glide as packed knobs, key/velocity response as h-sliders
        const char* dids[5] = { "vibratoRate", "vibratoDepth", "vibratoDelay", "vibWave", "glide" };
        const char* dlbl[5] = { "VIB RATE", "VIB DEPTH", "VIB DELAY", "VIB WAVE", "GLIDE" };
        for (int i = 0; i < 5; ++i)
        {
            auto k = std::make_unique<toi::StyledKnob> (dlbl[i], pal(), toi::StyledKnob::Metal);
            if (auto* prm = findParam (dids[i])) k->attach (*prm);
            addAndMakeVisible (*k); deep.push_back (std::move (k));
        }
        eslider ("dcwKey", "DCW KEY",  deepSliders);
        eslider ("velDcw", "VEL > DCW", deepSliders);
        eslider ("velAmp", "VEL > AMP", deepSliders);
        finishSetup();
    }

protected:
    int pageCount() const override { return 2; }   // PLAY + EDIT (deep envelope page)
    void setPresetActiveVisual (int idx) override
    { for (int i = 0; i < (int) slots.size(); ++i) slots[(size_t) i]->setActive (i == idx); }

    void paintPanel (juce::Graphics& g, juce::Rectangle<float> panel) override
    {
        auto charcoal = juce::Colour (0xff3a4150);
        auto sub = [&] (juce::Rectangle<float> r) { g.setColour (charcoal); g.fillRoundedRectangle (r, 5.0f); g.setColour (pal().ink); g.drawRoundedRectangle (r, 5.0f, toi::THIN_STROKE); };
        auto header = [&] (juce::Rectangle<float> r, const juce::String& t) { g.setColour (pal().accent); g.fillRoundedRectangle (r, 3.0f); g.setColour (juce::Colours::white); g.setFont (toi::uiFont (8.5f, true).withExtraKerningFactor (0.2f)); g.drawText (t, r, juce::Justification::centred); };

        sub (rRight);
        if (page() == 0)
        {
            sub (rMacro);  header (rMacro.reduced (7, 6).removeFromTop (15.0f), "MACROS");
            sub (rParam);  header (rParam.reduced (7, 6).removeFromTop (15.0f), "PARAMETER");
            g.setColour (juce::Colour (0xff9fb6e0)); g.setFont (toi::uiFont (8.0f, true).withExtraKerningFactor (0.6f));
            g.drawText ("OSC",     rOscHdr.withTrimmedLeft (4.0f), juce::Justification::centredLeft);
            g.drawText ("AMP ENV", rAmpHdr.withTrimmedLeft (4.0f), juce::Justification::centredLeft);
            g.drawText ("DCW ENV", rDcwHdr.withTrimmedLeft (4.0f), juce::Justification::centredLeft);
            g.setColour (pal().text); g.setFont (toi::uiFont (7.5f, true).withExtraKerningFactor (0.2f));
            g.drawText ("PHASE DISTORTION", rLcd.withTop (rLcd.getBottom() - 12.0f), juce::Justification::centred);
        }
        else
        {
            auto edit = juce::Rectangle<float> (rMacro.getX(), panel.getY() + 4, rParam.getRight() - rMacro.getX(), panel.getHeight() - 8);
            sub (edit); header (edit.reduced (7, 6).removeFromTop (15.0f), "ENVELOPES  -  DEEP EDIT");
            g.setColour (juce::Colour (0xff9fb6e0)); g.setFont (toi::uiFont (8.0f, true).withExtraKerningFactor (0.6f));
            g.drawText ("VIBRATO  /  GLIDE", rDeepHdr,  juce::Justification::centredLeft);
            g.drawText ("KEY  /  VELOCITY", rDeepHdr2, juce::Justification::centredLeft);
        }

        // compact brand: MODULE/SIZE toggle LEDs on top, then JW-CZ + TOI + plugin corp
        {
            auto bh = rBrandHdr;
            drawViewLeds (g, bh.removeFromTop (20.0f));
            g.setColour (pal().text); g.setFont (toi::uiFont (15.0f, true));
            g.drawText ("JW-CZ", bh.withHeight (16.0f), juce::Justification::centred);
            g.setColour (pal().text.withAlpha (0.8f)); g.setFont (toi::uiFont (7.0f, true).withExtraKerningFactor (0.3f));
            g.drawText ("TOI  -  plugin corp", bh.withTrimmedTop (15.0f).withHeight (10.0f), juce::Justification::centred);
        }
    }

    void layoutPanel (juce::Rectangle<float> panel) override
    {
        rMacro = juce::Rectangle<float> (panel.getX() + 6, panel.getY() + 4, panel.getWidth() * 0.15f, panel.getHeight() - 8);
        rLcd   = juce::Rectangle<float> (rMacro.getRight() + 7, panel.getY() + 16, panel.getWidth() * 0.24f, panel.getHeight() - 32);
        rParam = juce::Rectangle<float> (rLcd.getRight() + 7, panel.getY() + 4, panel.getWidth() * 0.42f, panel.getHeight() - 8);
        rRight = juce::Rectangle<float> (rParam.getRight() + 7, panel.getY() + 4, panel.getRight() - rParam.getRight() - 9, panel.getHeight() - 8);

        // MACROS: 4 faders
        {
            auto r = rMacro.reduced (10, 0).withTrimmedTop (26).withTrimmedBottom (8);
            const float fw = r.getWidth() / 4.0f;
            for (int i = 0; i < (int) faders.size(); ++i) placeInArtboard (*faders[(size_t) i], juce::Rectangle<float> (r.getX() + (float) i * fw, r.getY(), fw, r.getHeight()).reduced (3, 0));
        }
        placeInArtboard (scope, rLcd.reduced (4).withTrimmedBottom (12));

        // PARAMETER: OSC knob row (top) | AMP ENV (left) + DCW ENV (right) labelled slider groups
        {
            auto r = rParam.reduced (8, 0).withTrimmedTop (22);
            auto top = r.removeFromTop (r.getHeight() * 0.36f);
            rOscHdr = top.removeFromTop (11.0f);
            const float kw = top.getWidth() / 5.0f;
            for (int i = 0; i < (int) osc.size(); ++i) placeInArtboard (*osc[(size_t) i], juce::Rectangle<float> (top.getX() + (float) i * kw, top.getY(), kw, top.getHeight()).reduced (4, 2));
            auto amp = r.removeFromLeft (r.getWidth() * 0.56f);
            auto dcw = r;
            rAmpHdr = amp.removeFromTop (11.0f); rDcwHdr = dcw.removeFromTop (11.0f);
            { const float sh = amp.getHeight() / 4.0f; for (int i = 0; i < (int) ampEnv.size(); ++i) placeInArtboard (*ampEnv[(size_t) i], juce::Rectangle<float> (amp.getX(), amp.getY() + (float) i * sh, amp.getWidth(), sh).reduced (4, 1)); }
            auto dsl = dcw.removeFromTop (dcw.getHeight() * 0.66f);
            { const float sh = dsl.getHeight() / 3.0f; for (int i = 0; i < (int) dcwEnv.size(); ++i) placeInArtboard (*dcwEnv[(size_t) i], juce::Rectangle<float> (dsl.getX(), dsl.getY() + (float) i * sh, dsl.getWidth(), sh).reduced (4, 1)); }
            const float tw = dcw.getWidth() / 2.0f;
            placeInArtboard (*ring_,  juce::Rectangle<float> (dcw.getX(), dcw.getCentreY() - 9, tw, 18).reduced (3, 1));
            placeInArtboard (*noise_, juce::Rectangle<float> (dcw.getX() + tw, dcw.getCentreY() - 9, tw, 18).reduced (3, 1));
        }

        // RIGHT: page (EDIT/PLAY) button + brand header + 16 preset buttons + RAND/SAVE (always on)
        if (auto* pb = pageButton()) placeInArtboard (*pb, juce::Rectangle<float> (rRight.getCentreX() - 30, rRight.getY() + 3, 60, 15));
        rBrandHdr = rRight.withTrimmedTop (21).withHeight (46.0f).reduced (4, 0);
        {
            auto pr = rRight.withTrimmedTop (70).reduced (7, 2).withTrimmedBottom (26);
            const float gap = 3.0f, cw = (pr.getWidth() - gap) / 2.0f, rh = (pr.getHeight() - gap * 7.0f) / 8.0f;
            for (int i = 0; i < 16; ++i)
            {
                const int col = i % 2, row = i / 2;
                placeInArtboard (*slots[(size_t) i], juce::Rectangle<float> (pr.getX() + (float) col * (cw + gap), pr.getY() + (float) row * (rh + gap), cw, rh));
            }
            auto strip = rRight.reduced (8, 5).removeFromBottom (22.0f);
            placeInArtboard (*rand_, strip.removeFromLeft (strip.getWidth() * 0.5f).reduced (2, 0));
            placeInArtboard (*save_, strip.reduced (2, 0));
        }

        // EDIT page: two draggable envelope editors (top) + packed VIBRATO/GLIDE knobs (lower-left)
        // + KEY / VELOCITY response h-sliders (lower-right)
        {
            auto edit = juce::Rectangle<float> (rMacro.getX(), panel.getY() + 22, rParam.getRight() - rMacro.getX(), panel.getHeight() - 30);
            auto editors = edit.removeFromTop (edit.getHeight() * 0.58f);
            placeInArtboard (*ampEdit, editors.removeFromLeft (editors.getWidth() * 0.55f).reduced (6, 2));
            placeInArtboard (*dcwEdit, editors.reduced (6, 2));

            auto knobArea   = edit.removeFromLeft (edit.getWidth() * 0.58f);
            auto sliderArea = edit.withTrimmedLeft (10.0f);
            rDeepHdr  = knobArea.removeFromTop (13.0f).withTrimmedLeft (8.0f);
            rDeepHdr2 = sliderArea.removeFromTop (13.0f);
            const float kw = knobArea.getWidth() / (float) deep.size();
            for (int i = 0; i < (int) deep.size(); ++i)
                placeInArtboard (*deep[(size_t) i], juce::Rectangle<float> (knobArea.getX() + (float) i * kw, knobArea.getY(), kw, knobArea.getHeight()).reduced (4, 2));
            const float sh = sliderArea.getHeight() / (float) deepSliders.size();
            for (int i = 0; i < (int) deepSliders.size(); ++i)
                placeInArtboard (*deepSliders[(size_t) i], juce::Rectangle<float> (sliderArea.getX(), sliderArea.getY() + (float) i * sh, sliderArea.getWidth(), sh).reduced (6, 1));
        }
        // per-page visibility
        const bool play = (page() == 0);
        for (auto& f : faders) f->setVisible (play);
        for (auto& k : osc)    k->setVisible (play);
        for (auto& h : ampEnv) h->setVisible (play);
        for (auto& h : dcwEnv) h->setVisible (play);
        ring_->setVisible (play); noise_->setVisible (play); scope.setVisible (play);
        ampEdit->setVisible (! play); dcwEdit->setVisible (! play);
        for (auto& k : deep)        k->setVisible (! play);
        for (auto& h : deepSliders) h->setVisible (! play);
    }

private:
    void toggle (const juce::String& id) { if (auto* p = findParam (id)) { p->beginChangeGesture(); p->setValueNotifyingHost (p->getValue() > 0.5f ? 0.0f : 1.0f); p->endChangeGesture(); } }

    toi::Lcd scope;
    std::vector<std::unique_ptr<toi::StyledFader>>   faders;
    std::vector<std::unique_ptr<toi::StyledKnob>>    osc, deep;   // deep = EDIT-page vibrato/glide knobs
    std::vector<std::unique_ptr<toi::StyledHSlider>> ampEnv, dcwEnv, deepSliders;
    std::vector<std::unique_ptr<CZPreset>>           slots;
    std::unique_ptr<toi::Button> ring_, noise_, rand_, save_;
    std::unique_ptr<ADSREditor> ampEdit, dcwEdit;
    juce::Rectangle<float> rMacro, rLcd, rParam, rRight, rBrandHdr, rOscHdr, rAmpHdr, rDcwHdr, rDeepHdr, rDeepHdr2;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CZEditor)
};

//==============================================================================
class CZPlugin  : public cmaj::plugin::GeneratedPlugin<::CZ>,
                  public toi::AudioTapSource,
                  public toi::PresetStore
{
public:
    using Base = cmaj::plugin::GeneratedPlugin<::CZ>;
    CZPlugin (std::shared_ptr<cmaj::Patch> p) : Base (std::move (p)) {}

    juce::AudioProcessorEditor* createEditor() override { return new CZEditor (*this, keyboardState); }

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
