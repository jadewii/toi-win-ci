// JW-JX native faceplate (6-voice DCO polysynth tribute) on the toi_faceplate.h kit.
// Traces the PG-800 PROGRAMMER for the Roland JX-8P (NOT the membrane-button face): a DARK
// charcoal-black panel with thin blue + green accent hairlines, slim graphite end-caps, and
// rows of small light-grey slider caps in COLOR-GROUPED columns - the DCO half tinted blue,
// the VCF/VCA/ENV half tinted green. A small membrane-button + character-LCD pod lower-right
// is the nod to the JX's own front panel; the LCD runs the live CROSS-MOD scope (the signature
// clean-DCO -> metallic morph). Every control drives a real engine param. NO brand names.
#pragma once

#include "toi_faceplate.h"

struct JWJX;

namespace jx
{
    static const juce::Colour kPanel   { 0xff44484e };   // GUNMETAL GREY (Roland JX-08 body)
    static const juce::Colour kPanelLo { 0xff34373d };
    static const juce::Colour kGraphite{ 0xff2a2c31 };   // darker section edges
    static const juce::Colour kGraphLo { 0xff1d1f23 };
    static const juce::Colour kInk     { 0xffeceef2 };   // white silkscreen
    static const juce::Colour kDim     { 0xffb7bcc4 };
    static const juce::Colour kBlue    { 0xff5a6470 };   // neutral slate section accent (JX-08 is uniform grey)
    static const juce::Colour kGreen   { 0xff5a6470 };
    static const juce::Colour kRed     { 0xffd5402f };   // JX-08 red: indicators, ARPEGGIO/ENV-SELECT buttons, LED
    static const juce::Colour kBoxLine { 0x3affffff };
    static const juce::Colour kBox     { 0x221a1c20 };   // darker recessed section box on the grey
    static const juce::Colour kCapGrey { 0xff202226 };   // DARK slider/knob cap (JX-08 caps are dark on grey)
}

//==============================================================================
// JxSlider - the PG-800 control: a thin recessed dark SLOT + a small light-grey slider CAP with a
// COLOURED stripe (blue for DCO columns, green for VCF/VCA columns). Bound to a 0..1 param. The
// color-grouped cap wall is the signature programmer look.
class JxSlider  : public juce::Component
{
public:
    explicit JxSlider (juce::Colour stripeColour) : stripe (stripeColour)
    {
        slider.setSliderStyle (juce::Slider::LinearVertical);
        slider.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
        slider.setLookAndFeel (&laf);
        slider.setRange (0.0, 1.0, 0.0);
        addAndMakeVisible (slider);
    }
    ~JxSlider() override { slider.setLookAndFeel (nullptr); }
    void attach (juce::AudioProcessorParameter& p)
    {
        att = std::make_unique<toi::ParamKnobAttachment> (p, slider);
        slider.setDoubleClickReturnValue (true, p.getDefaultValue());
        slider.onValueChange = [this] { repaint(); };
        repaint();
    }
    void resized() override { slider.setBounds (getLocalBounds()); }
    void paint (juce::Graphics& g) override
    {
        auto b = getLocalBounds().toFloat().reduced (0.0f, 5.0f);
        const float cx = b.getCentreX(), top = b.getY(), h = b.getHeight();
        // THICK recessed track (JX-08)
        juce::Rectangle<float> slot (cx - 3.5f, top, 7.0f, h);
        g.setColour (juce::Colour (0xff111316)); g.fillRoundedRectangle (slot, 2.5f);
        g.setColour (juce::Colours::black.withAlpha (0.55f)); g.drawRoundedRectangle (slot, 2.5f, 0.9f);
        // white scale tick marks down the right of the track
        g.setColour (jx::kDim.withAlpha (0.55f));
        for (int i = 0; i <= 5; ++i) { const float tyk = top + 5.0f + (h - 10.0f) * (float) i / 5.0f; g.drawLine (cx + 5.5f, tyk, cx + 8.5f, tyk, 0.9f); }

        const float v = juce::jlimit (0.0f, 1.0f, (float) slider.getValue());
        const float capH = 14.0f, capW = 22.0f, pad = capH * 0.5f + 1.0f;
        const float ty = top + pad + (1.0f - v) * (h - 2.0f * pad);
        juce::Rectangle<float> cap (cx - capW * 0.5f, ty - capH * 0.5f, capW, capH);
        // contact shadow
        g.setColour (juce::Colours::black.withAlpha (0.5f)); g.fillRoundedRectangle (cap.translated (0.0f, 1.8f), 3.0f);
        // chunky SILVER 3D cap with a recessed horizontal GROOVE across the middle (the JX-08 thumb)
        juce::ColourGradient cg (juce::Colour (0xfff3f4f7), cx, cap.getY(), juce::Colour (0xff8f939b), cx, cap.getBottom(), false);
        cg.addColour (0.5, juce::Colour (0xffc9ccd2));
        g.setGradientFill (cg); g.fillRoundedRectangle (cap, 3.0f);
        g.setColour (juce::Colours::black.withAlpha (0.6f)); g.drawRoundedRectangle (cap, 3.0f, 0.9f);
        g.setColour (juce::Colours::black.withAlpha (0.45f)); g.fillRect (cap.getX() + 2.5f, cap.getCentreY() - 1.3f, cap.getWidth() - 5.0f, 2.2f);   // recessed groove
        g.setColour (juce::Colours::white.withAlpha (0.4f));  g.fillRect (cap.getX() + 2.5f, cap.getCentreY() + 1.0f, cap.getWidth() - 5.0f, 0.8f);   // groove highlight
        juce::ignoreUnused (stripe);
    }
    juce::Slider slider;
private:
    toi::InvisibleLinearLAF laf; juce::Colour stripe;
    std::unique_ptr<toi::ParamKnobAttachment> att;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JxSlider)
};

//==============================================================================
// JxKnob - the JX-08 rotary: a dark round knob with a RED pointer line + a tick ring (for TUNE/FINE/
// RATE/DELAY/ENV-amount, which are knobs on the real JX-08, not sliders).
class JxKnob  : public juce::Component
{
public:
    JxKnob()
    {
        slider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
        slider.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
        slider.setLookAndFeel (&laf); slider.setRange (0.0, 1.0, 0.0);
        addAndMakeVisible (slider);
    }
    ~JxKnob() override { slider.setLookAndFeel (nullptr); }
    void attach (juce::AudioProcessorParameter& p)
    { att = std::make_unique<toi::ParamKnobAttachment> (p, slider); slider.setDoubleClickReturnValue (true, p.getDefaultValue()); slider.onValueChange = [this] { repaint(); }; repaint(); }
    void resized() override { slider.setBounds (getLocalBounds()); }
    void paint (juce::Graphics& g) override
    {
        auto b = getLocalBounds().toFloat();
        const float d = juce::jmin (b.getWidth(), b.getHeight());
        const float cx = b.getCentreX(), cy = b.getCentreY(), r = d * 0.5f - 4.0f;
        const float v = juce::jlimit (0.0f, 1.0f, (float) slider.getValue());
        const float ang = juce::degreesToRadians (-135.0f + 270.0f * v);
        const float dx = std::sin (ang), dy = -std::cos (ang);
        g.setColour (jx::kDim.withAlpha (0.45f));
        for (int i = 0; i <= 10; ++i) { const float a = juce::degreesToRadians (-135.0f + 270.0f * (float) i / 10.0f); const float s = std::sin (a), c = -std::cos (a); g.drawLine (cx + s * (r + 1.5f), cy + c * (r + 1.5f), cx + s * (r + 4.0f), cy + c * (r + 4.0f), 0.8f); }
        g.setColour (juce::Colours::black.withAlpha (0.4f)); g.fillEllipse (cx - r, cy - r + 1.5f, r * 2.0f, r * 2.0f);
        juce::ColourGradient cg (juce::Colour (0xff3a3d43), cx, cy - r, juce::Colour (0xff141518), cx, cy + r, false);
        g.setGradientFill (cg); g.fillEllipse (cx - r, cy - r, r * 2.0f, r * 2.0f);
        g.setColour (juce::Colours::black); g.drawEllipse (cx - r, cy - r, r * 2.0f, r * 2.0f, 1.0f);
        g.setColour (jx::kRed); g.drawLine (cx + dx * r * 0.22f, cy + dy * r * 0.22f, cx + dx * (r - 2.0f), cy + dy * (r - 2.0f), 2.4f);
    }
    juce::Slider slider;
private:
    toi::InvisibleRotaryLAF laf;
    std::unique_ptr<toi::ParamKnobAttachment> att;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JxKnob)
};

//==============================================================================
// JxSwitch - a small dark membrane selector (2..4 positions) bound to a 0..1 param. Click cycles.
// A coloured lit slug marks the active position (the PG-800's small block selectors). Optionally
// shows tiny position legends to the right.
class JxSwitch  : public juce::Component,
                  private juce::AudioProcessorParameter::Listener,
                  private juce::AsyncUpdater
{
public:
    JxSwitch (int positions, juce::Colour litColour) : N (positions), lit (litColour) {}
    ~JxSwitch() override { if (param_) param_->removeListener (this); cancelPendingUpdate(); }
    void attach (juce::AudioProcessorParameter* p) { param_ = p; if (param_) param_->addListener (this); triggerAsyncUpdate(); }
    void setLegends (juce::StringArray l) { legends = std::move (l); }
    void mouseDown (const juce::MouseEvent&) override
    {
        if (! param_) return;
        int a = juce::roundToInt (param_->getValue() * (float) (N - 1));
        a = (a + 1) % N;
        param_->setValueNotifyingHost ((float) a / (float) (N - 1));
    }
    void paint (juce::Graphics& g) override
    {
        auto b = getLocalBounds().toFloat();
        auto sw = b;
        if (! legends.isEmpty()) sw = b.removeFromLeft (b.getWidth() * 0.42f);
        sw = sw.reduced (1.0f);
        const int a = param_ ? juce::jlimit (0, N - 1, juce::roundToInt (param_->getValue() * (float) (N - 1))) : 0;
        // dark recessed membrane block
        g.setColour (juce::Colour (0xff0e0e10)); g.fillRoundedRectangle (sw, 2.5f);
        g.setColour (jx::kBoxLine.withAlpha (0.30f)); g.drawRoundedRectangle (sw, 2.5f, 0.8f);
        // lit slug shows the active position
        const float slugH = (sw.getHeight() - 2.0f) / (float) N;
        auto slug = juce::Rectangle<float> (sw.getX() + 1.5f, sw.getY() + 1.0f + (float) a * slugH, sw.getWidth() - 3.0f, slugH - 1.5f);
        g.setColour (lit.withAlpha (0.45f)); g.fillRoundedRectangle (slug.expanded (1.0f), 1.5f);
        juce::ColourGradient sg (lit.brighter (0.2f), slug.getCentreX(), slug.getY(), lit.darker (0.25f), slug.getCentreX(), slug.getBottom(), false);
        g.setGradientFill (sg); g.fillRoundedRectangle (slug, 1.5f);
        // position legends down the right side
        if (! legends.isEmpty())
        {
            g.setFont (toi::uiFont (5.0f, true));
            for (int i = 0; i < N && i < legends.size(); ++i)
            {
                auto lr = juce::Rectangle<float> (b.getX() + 2.0f, sw.getY() + (float) i * slugH, b.getWidth() - 2.0f, slugH);
                g.setColour (i == a ? jx::kInk : jx::kDim.withAlpha (0.65f));
                g.drawText (legends[i], lr, juce::Justification::centredLeft);
            }
        }
    }
private:
    void parameterValueChanged (int, float) override { triggerAsyncUpdate(); }
    void parameterGestureChanged (int, bool) override {}
    void handleAsyncUpdate() override { repaint(); }
    int N; juce::Colour lit; juce::AudioProcessorParameter* param_ = nullptr;
    juce::StringArray legends;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JxSwitch)
};

//==============================================================================
// JxFunc - the RAND / SAVE / BAKE labelled buttons (membrane look).
class JxFunc  : public juce::Button
{
public:
    JxFunc (const juce::String& t, juce::Colour fill) : juce::Button (t), col (fill) { setButtonText (t); }
    void flash() { flashing = true; repaint(); juce::Timer::callAfterDelay (150, [s = juce::Component::SafePointer<JxFunc> (this)] { if (s) { s->flashing = false; s->repaint(); } }); }
    void paintButton (juce::Graphics& g, bool over, bool down) override
    {
        auto b = getLocalBounds().toFloat().reduced (1.0f);
        auto fill = flashing ? col.brighter (0.3f) : down ? col.darker (0.18f) : over ? col.brighter (0.08f) : col;
        g.setColour (fill); g.fillRoundedRectangle (b, 2.5f);
        g.setColour (juce::Colours::black.withAlpha (0.5f)); g.drawRoundedRectangle (b, 2.5f, 1.0f);
        g.setColour (fill.getPerceivedBrightness() > 0.55f ? juce::Colour (0xff1a1c20) : juce::Colours::white.withAlpha (0.92f)); g.setFont (toi::uiFont (juce::jmin (10.0f, b.getHeight() * 0.5f), true));
        g.drawText (getButtonText(), getLocalBounds(), juce::Justification::centred);
    }
private:
    juce::Colour col; bool flashing = false;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JxFunc)
};

//==============================================================================
inline toi::Config jwjxConfig()
{
    toi::Config c;
    c.model = "JW-JX";
    auto& p = c.pal;
    p.bg = jx::kPanel; p.bg2 = jx::kPanelLo; p.frame = juce::Colour (0xff0a0a0c); p.ink = juce::Colour (0xff1a1c20);   // DARK key outlines (panel text uses jx::kInk constant, stays white)
    p.accent = jx::kGreen; p.accent2 = jx::kBlue; p.button = juce::Colour (0xff26262b);
    p.thumb = jx::kCapGrey; p.text = jx::kInk;
    p.noteStrip = jx::kPanelLo;
    p.lcdBg = juce::Colour (0xff04140c); p.lcdInk = jx::kGreen;
    p.keyWhite = juce::Colour (0xffe8e8ec); p.keyWhitePr = jx::kBlue; p.keyBlack = juce::Colour (0xff202024); p.keyBlackPr = jx::kGreen;

    // ids MUST match JX.cmajor ParamsProcessor inputs (and the engine's order)
    c.params = {
        // DCO1
        { "o1Range","RANGE" },{ "o1Wave","WAVE" },{ "o1Tune","TUNE" },{ "o1Lfo","LFO" },{ "o1Env","ENV" },{ "o1EnvSel","E-SEL" },
        // DCO2 + cross-mod
        { "o2Range","RANGE" },{ "o2Wave","WAVE" },{ "o2Tune","TUNE" },{ "o2Fine","FINE" },{ "xMod","X-MOD" },{ "xDepth","DEPTH" },
        // mixer
        { "mix","MIX" },{ "pwm","PW" },
        // VCF
        { "hpf","HPF" },{ "cutoff","CUTOFF" },{ "reso","RESO" },{ "fLfo","LFO" },{ "fEnv","ENV" },{ "fEnvSel","E-SEL" },{ "fKey","KEY" },
        // VCA
        { "dynamics","DYN" },
        // ENV1
        { "a1","A" },{ "d1","D" },{ "s1","S" },{ "r1","R" },{ "inv1","INV" },
        // ENV2
        { "a2","A" },{ "d2","D" },{ "s2","S" },{ "r2","R" },{ "inv2","INV" },
        // LFO
        { "lfoRate","RATE" },{ "lfoShape","SHAPE" },{ "lfoDelay","DELAY" },
        // aftertouch + global
        { "atVib","AT VIB" },{ "atBri","AT BRI" },{ "chorus","CHORUS" },{ "volume","VOL" },{ "tune","TUNE" },
    };

    // engine init values (mirror JX.cmajor ParamsProcessor inits, same order as c.params)
    std::vector<float> base = {
        0.50f, 0.0f,  0.50f, 0.0f,  0.0f,  0.0f,    // DCO1
        0.50f, 0.0f,  0.50f, 0.52f, 0.0f,  0.50f,   // DCO2 + xmod
        0.50f, 0.50f,                               // mixer
        0.0f,  0.60f, 0.25f, 0.0f,  0.45f, 0.0f, 0.35f,  // VCF
        0.50f,                                      // VCA
        0.05f, 0.45f, 0.40f, 0.35f, 0.0f,           // ENV1
        0.06f, 0.50f, 0.75f, 0.40f, 0.0f,           // ENV2
        0.35f, 0.0f,  0.20f,                        // LFO
        0.30f, 0.25f, 0.60f, 0.80f, 0.50f };        // AT + global

    // index helper into c.params order
    enum { O1R,O1W,O1T,O1L,O1E,O1ES, O2R,O2W,O2T,O2F,XM,XD, MIX,PWM,
           HPF,CUT,RES,FL,FE,FES,FK, DYN, A1,D1,S1,R1,INV1, A2,D2,S2,R2,INV2,
           LR,LSH,LD, ATV,ATB,CHO,VOL,TUN };
    auto P = [&] (const char* nm, std::initializer_list<std::pair<int,float>> ov)
    { auto v = base; for (auto& o : ov) v[(size_t) o.first] = o.second; return toi::FactoryPreset { nm, v }; };

    c.factory = {
        P("INIT", {}),
        P("GLASS PAD",    {{O1W,0.0f},{O2W,0.0f},{XM,1.0f},{XD,0.55f},{CUT,0.55f},{RES,0.2f},{FE,0.5f},{A2,0.4f},{R2,0.6f},{CHO,1.0f}}),
        P("HOLLOW EP",    {{O1W,0.66f},{O2W,0.0f},{XM,1.0f},{XD,0.7f},{MIX,0.4f},{CUT,0.5f},{RES,0.3f},{FE,0.55f},{A2,0.0f},{D2,0.5f},{S2,0.25f},{CHO,0.55f}}),
        P("METAL BELL",   {{O1W,1.0f},{O2W,1.0f},{XM,1.0f},{XD,0.9f},{O2T,0.62f},{CUT,0.65f},{RES,0.35f},{FE,0.6f},{A2,0.0f},{D2,0.45f},{S2,0.1f}}),
        P("SYNC LEAD",    {{XM,0.33f},{XD,0.6f},{O2T,0.6f},{MIX,0.6f},{CUT,0.6f},{RES,0.45f},{FE,0.55f},{A2,0.02f},{D2,0.4f},{S2,0.6f}}),
        P("FAT DCO BASS", {{O1R,0.33f},{O2R,0.33f},{O2F,0.55f},{MIX,0.5f},{CUT,0.42f},{RES,0.35f},{FE,0.5f},{D2,0.35f},{S2,0.4f},{R2,0.3f}}),
        P("BRIGHT PLUCK", {{O1W,0.0f},{MIX,0.4f},{CUT,0.7f},{RES,0.4f},{FE,0.7f},{D1,0.3f},{S1,0.1f},{A2,0.0f},{D2,0.35f},{S2,0.2f}}),
        P("PWM STRINGS",  {{O1W,0.66f},{O2W,0.66f},{PWM,0.4f},{O1L,0.4f},{LR,0.2f},{MIX,0.5f},{CUT,0.55f},{A2,0.35f},{R2,0.6f},{CHO,1.0f}}),
        P("SOFT KEYS",    {{O1W,0.0f},{MIX,0.45f},{CUT,0.52f},{RES,0.2f},{FE,0.4f},{A2,0.04f},{D2,0.5f},{S2,0.45f},{R2,0.4f},{CHO,0.55f}}),
        P("RESO SWEEP",   {{CUT,0.4f},{RES,0.6f},{FE,0.75f},{FL,0.4f},{LR,0.18f},{D1,0.4f},{S1,0.0f},{MIX,0.4f}}),
        P("AIR PAD",      {{O1W,0.0f},{O2W,0.0f},{O2F,0.56f},{HPF,0.33f},{CUT,0.5f},{A2,0.5f},{R2,0.75f},{ATB,0.5f},{CHO,1.0f}}),
        P("CLAV STAB",    {{O1W,0.66f},{PWM,0.3f},{MIX,0.45f},{CUT,0.6f},{RES,0.5f},{FE,0.6f},{D1,0.25f},{S1,0.0f},{D2,0.3f},{S2,0.15f}}),
    };
    return c;
}

//==============================================================================
class JWJXEditor  : public toi::PanelEditor
{
public:
    JWJXEditor (juce::AudioProcessor& proc, juce::MidiKeyboardState& kb)
        : toi::PanelEditor (proc, kb, jwjxConfig())
    {
        // PG-800 sections, left-to-right. blue = DCO half, green = VCF/VCA/ENV half.
        // each group lists its slider ids (continuous params only); selector switches are added separately.
        groups_ = {
            { "DCO 1",   { "o1Tune","o1Lfo","o1Env" },        jx::kBlue },
            { "DCO 2",   { "o2Tune","o2Fine","xDepth" },      jx::kBlue },
            { "MIXER",   { "mix","pwm" },                     jx::kBlue },
            { "VCF",     { "cutoff","reso","fLfo","fEnv","fKey" }, jx::kGreen },
            { "VCA",     { "dynamics" },                      jx::kGreen },
            { "ENV 1",   { "a1","d1","s1","r1" },             jx::kGreen },
            { "ENV 2",   { "a2","d2","s2","r2" },             jx::kGreen },
            { "LFO",     { "lfoRate","lfoDelay" },            jx::kGreen },
            { "AFTER",   { "atVib","atBri" },                 jx::kGreen },
            { "MASTER",  { "volume","tune" },                 jx::kGreen },
        };
        for (auto& grp : groups_)
            for (auto& id : grp.ids) { if (isKnob (id)) addKnob (id); else addSlider (id, grp.accent); }

        // selector switches (the PG-800 discrete blocks), each attached to a real param
        addSwitch ("o1Range", 4, jx::kBlue,  { "16","8","4","2" });
        addSwitch ("o1Wave",  4, jx::kBlue,  { "S","Q","P","N" });
        addSwitch ("o1EnvSel",2, jx::kBlue,  { "1","2" });
        addSwitch ("o2Range", 4, jx::kBlue,  { "16","8","4","2" });
        addSwitch ("o2Wave",  4, jx::kBlue,  { "S","Q","P","N" });
        addSwitch ("xMod",    4, jx::kBlue,  { "OFF","SY1","SY2","MTL" });
        addSwitch ("hpf",     4, jx::kGreen, { "0","1","2","3" });
        addSwitch ("fEnvSel", 2, jx::kGreen, { "1","2" });
        addSwitch ("inv1",    2, jx::kGreen, { "+","-" });
        addSwitch ("inv2",    2, jx::kGreen, { "+","-" });
        addSwitch ("lfoShape",3, jx::kGreen, { "SIN","SQR","RND" });
        addSwitch ("chorus",  3, jx::kGreen, { "OFF","I","II" });

        // the signature scope: live X-MOD/sync clean->metallic morph (real audio)
        scope_ = std::make_unique<toi::Lcd> (pal());
        scope_->attachScope (audioTap());
        addAndMakeVisible (*scope_);

        // 16 preset membrane buttons + RAND/SAVE
        for (int i = 0; i < 16; ++i)
        { auto b = std::make_unique<toi::MoldedButton> (juce::Colour (0xffe9e6df)); b->setLit (juce::Colour (0xff2f6fd0)); const int idx = i; b->onClick = [this, idx] { recallSlot (idx); }; addAndMakeVisible (*b); slots_.push_back (std::move (b)); }
        rand_ = std::make_unique<JxFunc> ("RAND", juce::Colour (0xffe0a91e)); save_ = std::make_unique<JxFunc> ("SAVE", juce::Colour (0xffc8392a));   // RAND=yellow, SAVE=red
        rand_->onClick = [this] { doRandom(); rand_->flash(); };
        save_->onClick = [this] { saveSlot (activeSlot()); save_->flash(); };
        addAndMakeVisible (*rand_); addAndMakeVisible (*save_);

        finishSetup();
    }

protected:
    void setPresetActiveVisual (int idx) override { for (int i = 0; i < (int) slots_.size(); ++i) slots_[(size_t) i]->setActive (i == idx); }

    void paintPanel (juce::Graphics& g, juce::Rectangle<float> panel) override
    {
        rPanel = panel;
        // dark charcoal panel with a subtle vertical gradient
        juce::ColourGradient pg (jx::kPanel, panel.getCentreX(), panel.getY(), jx::kPanelLo, panel.getCentreX(), panel.getBottom(), false);
        g.setGradientFill (pg); g.fillRoundedRectangle (panel, 5.0f);

        // slim graphite end-caps
        const float ch = 18.0f;
        drawCap (g, juce::Rectangle<float> (panel.getX(), panel.getY(), ch, panel.getHeight()));
        drawCap (g, juce::Rectangle<float> (panel.getRight() - ch, panel.getY(), ch, panel.getHeight()));
        g.setColour (juce::Colours::black); g.drawRoundedRectangle (panel, 5.0f, 1.5f);

        // thin blue + green accent hairlines dividing the DCO half from the VCF/VCA half
        if (rDivX_ > 0.0f)
        {
            g.setColour (jx::kBlue.withAlpha (0.7f));  g.drawLine (rDivX_ - 1.6f, panel.getY() + 16.0f, rDivX_ - 1.6f, panel.getBottom() - 60.0f, 1.2f);
            g.setColour (jx::kGreen.withAlpha (0.7f)); g.drawLine (rDivX_ + 1.6f, panel.getY() + 16.0f, rDivX_ + 1.6f, panel.getBottom() - 60.0f, 1.2f);
        }

        // section boxes + labels + slider/switch legends
        for (auto& grp : groups_) drawGroupBox (g, grp);

        // switch labels (drawn under each selector)
        for (auto& sr : switchRects_)
        { g.setColour (jx::kDim); g.setFont (toi::uiFont (5.5f, true));
          g.drawText (sr.first, juce::Rectangle<float> (sr.second.getX() - 6.0f, sr.second.getBottom(), sr.second.getWidth() + 12.0f, 7.0f), juce::Justification::centred); }

        // the LCD pod label + membrane nod
        g.setColour (jx::kInk); g.setFont (toi::uiFont (6.5f, true).withExtraKerningFactor (0.1f));
        g.drawText ("X-MOD  SCOPE", juce::Rectangle<float> (rScope_.getX(), rScope_.getY() - 9.0f, 160.0f, 9.0f), juce::Justification::centredLeft);
        g.drawText ("PRESET", juce::Rectangle<float> (rPreset_.getX(), rPreset_.getY() - 9.0f, 120.0f, 9.0f), juce::Justification::centredLeft);

        // top tagline + brand on the right
        g.setColour (jx::kDim); g.setFont (toi::uiFont (6.5f, true).withExtraKerningFactor (0.2f));
        g.drawText ("PG  PROGRAMMER", juce::Rectangle<float> (rPanel.getX() + 26.0f, rPanel.getY() + 5.0f, 200.0f, 10.0f), juce::Justification::centredLeft);
        auto bh = rBrand_;
        drawViewLeds (g, bh.removeFromTop (22.0f));
        bh.removeFromTop (2.0f);
        g.setColour (jx::kInk); g.setFont (toi::uiFont (15.0f, true));
        g.drawText ("JW-JX", bh, juce::Justification::centred);
    }

    void drawCap (juce::Graphics& g, juce::Rectangle<float> r)
    {
        juce::ColourGradient cg (jx::kGraphite, r.getX(), r.getY(), jx::kGraphLo, r.getRight(), r.getY(), false);
        g.setGradientFill (cg); g.fillRect (r);
        g.setColour (juce::Colours::black.withAlpha (0.4f)); g.drawLine (r.getRight(), r.getY(), r.getRight(), r.getBottom(), 0.8f);
    }

    void layoutPanel (juce::Rectangle<float> panel) override
    {
        rPanel = panel;
        auto inner = panel.reduced (24.0f, 8.0f);   // leave room for graphite end-caps

        rBrand_ = juce::Rectangle<float> (panel.getRight() - 112.0f, panel.getY() + 6.0f, 100.0f, 40.0f);
        inner.removeFromTop (16.0f);

        // ===== thin BOTTOM strip: small scope (left) + ONE row of 16 presets + small RAND/SAVE =====
        auto strip = inner.removeFromBottom (38.0f);
        inner.removeFromBottom (9.0f);
        {
            rScope_ = strip.removeFromLeft (150.0f).reduced (0.0f, 2.0f); placeInArtboard (*scope_, rScope_);
            strip.removeFromLeft (12.0f);
            auto rs = strip.removeFromRight (84.0f); strip.removeFromRight (10.0f);
            rPreset_ = strip;
            const int pc = 16;
            const float sq = juce::jmin (rPreset_.getHeight() - 2.0f, 30.0f);     // SQUARE preset buttons
            const float pitch = rPreset_.getWidth() / (float) pc;
            const float py = rPreset_.getY() + (rPreset_.getHeight() - sq) * 0.5f;
            for (int i = 0; i < 16; ++i)
                placeInArtboard (*slots_[(size_t) i], juce::Rectangle<float> (rPreset_.getX() + (float) i * pitch + (pitch - sq) * 0.5f, py, sq, sq));
            const float bw = (rs.getWidth() - 4.0f) * 0.5f, bh = juce::jmin (rs.getHeight() - 2.0f, 30.0f);
            const float by = rs.getY() + (rs.getHeight() - bh) * 0.5f;
            placeInArtboard (*rand_, juce::Rectangle<float> (rs.getX(), by, bw, bh));            // yellow
            placeInArtboard (*save_, juce::Rectangle<float> (rs.getX() + bw + 4.0f, by, bw, bh)); // red
        }

        // ===== sections fill ALL the remaining (tall) space -> big controls, NO dead space =====
        rowSliders_ = inner;
        layoutGroups (rowSliders_);
    }

private:
    struct Group { juce::String name; std::vector<juce::String> ids; juce::Colour accent; juce::Rectangle<float> rect; };

    // the rotary params that are KNOBS on the real JX-08 (everything else is a slider)
    static bool isKnob (const juce::String& id)
    { return id == "lfoRate" || id == "lfoDelay" || id == "o1Tune" || id == "o1Env"
          || id == "o2Tune"  || id == "o2Fine"  || id == "xDepth" || id == "fEnv"; }
    void addSlider (const juce::String& id, juce::Colour stripe)
    {
        auto s = std::make_unique<JxSlider> (stripe);
        if (auto* prm = findParam (id)) s->attach (*prm);
        addAndMakeVisible (*s); sliderMap_[id] = s.get(); sliders_.push_back (std::move (s));
    }
    void addKnob (const juce::String& id)
    {
        auto k = std::make_unique<JxKnob>();
        if (auto* prm = findParam (id)) k->attach (*prm);
        addAndMakeVisible (*k); knobMap_[id] = k.get(); knobs_.push_back (std::move (k));
    }
    JxKnob* knobFor (const juce::String& id) const { auto it = knobMap_.find (id); return it == knobMap_.end() ? nullptr : it->second; }
    void addSwitch (const juce::String& id, int positions, juce::Colour litCol, juce::StringArray legends)
    {
        auto t = std::make_unique<JxSwitch> (positions, litCol);
        t->setLegends (std::move (legends));
        if (auto* prm = findParam (id)) t->attach (prm);
        addAndMakeVisible (*t); switchMap_[id] = t.get(); switches_.push_back (std::move (t));
    }
    JxSlider* sliderFor (const juce::String& id) const { auto it = sliderMap_.find (id); return it == sliderMap_.end() ? nullptr : it->second; }

    int totalSliders() const { int n = 0; for (auto& g : groups_) n += (int) g.ids.size(); return n; }

    void layoutGroups (juce::Rectangle<float> row)
    {
        switchRects_.clear();
        const int n = totalSliders();
        const float gap = 7.0f;
        // the switch columns that belong to each group (the PG-800 selector blocks)
        auto switchesFor = [&] (const juce::String& name) -> std::vector<std::pair<juce::String,JxSwitch*>>
        {
            if (name == "DCO 1") return { { "RANGE", switchMap_["o1Range"] }, { "WAVE", switchMap_["o1Wave"] }, { "E-SEL", switchMap_["o1EnvSel"] } };
            if (name == "DCO 2") return { { "RANGE", switchMap_["o2Range"] }, { "WAVE", switchMap_["o2Wave"] }, { "X-MOD", switchMap_["xMod"] } };
            if (name == "VCF")   return { { "HPF", switchMap_["hpf"] }, { "E-SEL", switchMap_["fEnvSel"] } };
            if (name == "ENV 1") return { { "INV", switchMap_["inv1"] } };
            if (name == "ENV 2") return { { "INV", switchMap_["inv2"] } };
            if (name == "LFO")   return { { "SHAPE", switchMap_["lfoShape"] }, { "CHORUS", switchMap_["chorus"] } };
            return {};
        };

        // columns: each SLIDER = 1 col, each SWITCH = 1 col, and ALL of a section's KNOBS stack into ONE col
        int cols = 0;
        for (auto& grp : groups_)
        { int nk = 0, ns = 0; for (auto& id : grp.ids) { if (knobFor (id)) ++nk; else ++ns; }
          cols += ns + (int) switchesFor (grp.name).size() + (nk > 0 ? 1 : 0); }
        juce::ignoreUnused (n);
        const float usable = row.getWidth() - gap * (float) (groups_.size() - 1);
        const float cw = usable / (float) cols;

        const float labelTop = 12.0f, labelBot = 9.0f;
        float x = row.getX();
        rDivX_ = -1.0f;
        for (auto& grp : groups_)
        {
            std::vector<juce::String> gk, gs;
            for (auto& id : grp.ids) { if (knobFor (id)) gk.push_back (id); else gs.push_back (id); }
            auto sws = switchesFor (grp.name);
            const int nCol = (int) gs.size() + (int) sws.size() + (gk.empty() ? 0 : 1);
            const float gw = cw * (float) nCol;
            grp.rect = juce::Rectangle<float> (x, row.getY(), gw, row.getHeight());
            float ix = x;
            // KNOB STACK: the section's knobs stacked vertically in one column = BIG knobs, no dead space
            if (! gk.empty())
            {
                auto col = juce::Rectangle<float> (ix, row.getY() + labelTop, cw, row.getHeight() - labelTop - labelBot);
                const int nk = (int) gk.size();
                const float chh = col.getHeight() / (float) nk;
                for (int i = 0; i < nk; ++i)
                { auto cell = juce::Rectangle<float> (col.getX(), col.getY() + (float) i * chh, col.getWidth(), chh);
                  const float dd = juce::jmax (24.0f, juce::jmin (col.getWidth() - 2.0f, chh - 10.0f));
                  if (auto* k = knobFor (gk[(size_t) i])) placeInArtboard (*k, juce::Rectangle<float> (0, 0, dd, dd).withCentre ({ cell.getCentreX(), cell.getY() + (chh - 9.0f) * 0.5f })); }
                ix += cw;
            }
            for (auto& id : gs)
            {
                if (auto* s = sliderFor (id))
                    placeInArtboard (*s, juce::Rectangle<float> (ix, row.getY() + labelTop, cw, row.getHeight() - labelTop - labelBot).reduced (2.0f, 0.0f));
                ix += cw;
            }
            for (auto& sw : sws)
            {
                auto sr = juce::Rectangle<float> (ix + 2.0f, row.getY() + labelTop + 6.0f, cw - 4.0f, row.getHeight() - labelTop - labelBot - 14.0f);
                if (sw.second) placeInArtboard (*sw.second, sr);
                switchRects_.push_back ({ sw.first, sr });
                ix += cw;
            }
            if (grp.name == "MIXER") rDivX_ = x + gw + gap * 0.5f;
            x += gw + gap;
        }
    }

    void drawGroupBox (juce::Graphics& g, const Group& grp)
    {
        g.setColour (jx::kBox); g.fillRoundedRectangle (grp.rect, 3.0f);
        g.setColour (grp.accent.withAlpha (0.45f)); g.drawRoundedRectangle (grp.rect, 3.0f, 1.0f);
        g.setColour (grp.accent); g.setFont (toi::uiFont (7.0f, true).withExtraKerningFactor (0.06f));
        g.drawText (grp.name, grp.rect.withHeight (11.0f).reduced (4.0f, 1.0f), juce::Justification::centredLeft);
        // labels: KNOBS labelled under each (they're stacked, so different Y); SLIDERS at the section bottom
        g.setColour (jx::kDim); g.setFont (toi::uiFont (5.5f, true));
        for (auto& id : grp.ids)
        {
            juce::String lbl; for (auto& sp : config().params) if (sp.id == id) { lbl = sp.label; break; }
            if (auto* k = knobFor (id))
            { auto kr = k->getBounds().toFloat(); g.drawText (lbl, juce::Rectangle<float> (kr.getCentreX() - 26.0f, kr.getBottom() - 1.0f, 52.0f, 8.0f), juce::Justification::centred); }
            else if (auto* s = sliderFor (id))
            { auto sr = s->getBounds().toFloat(); g.drawText (lbl, juce::Rectangle<float> (sr.getCentreX() - 26.0f, grp.rect.getBottom() - 9.0f, 52.0f, 8.0f), juce::Justification::centred); }
        }
    }

    std::vector<std::unique_ptr<JxSlider>> sliders_;
    std::map<juce::String, JxSlider*> sliderMap_;
    std::vector<std::unique_ptr<JxKnob>> knobs_;
    std::map<juce::String, JxKnob*> knobMap_;
    std::vector<std::unique_ptr<JxSwitch>> switches_;
    std::map<juce::String, JxSwitch*> switchMap_;
    std::vector<std::pair<juce::String, juce::Rectangle<float>>> switchRects_;
    std::unique_ptr<toi::Lcd> scope_;
    std::vector<std::unique_ptr<toi::MoldedButton>> slots_;
    std::unique_ptr<JxFunc> rand_, save_;
    std::vector<Group> groups_;
    float rDivX_ = -1.0f;
    juce::Rectangle<float> rPanel, rowSliders_, rScope_, rPreset_, rBrand_;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JWJXEditor)
};

//==============================================================================
class JWJXPlugin  : public cmaj::plugin::GeneratedPlugin<::JWJX>,
                    public toi::AudioTapSource,
                    public toi::PresetStore
{
public:
    using Base = cmaj::plugin::GeneratedPlugin<::JWJX>;
    JWJXPlugin (std::shared_ptr<cmaj::Patch> p) : Base (std::move (p)) {}
    juce::AudioProcessorEditor* createEditor() override { return new JWJXEditor (*this, keyboardState); }
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
