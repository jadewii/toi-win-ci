// JW-VS native faceplate - AUTHENTIC Prophet VS button-grid (dark navy + blue) per Jade's reference.
// Almost everything is a small membrane SELECT button grouped under blue label boxes; you SELECT a
// parameter, then change it with the DATA ENTRY slider (the red LED shows its value / the program no.).
// The diamond VECTOR pad (the VS signature) stays on the left. NO brand names.
#pragma once

#include "toi_faceplate.h"

struct JWVS;

namespace vs
{
    static const juce::Colour kPanel   { 0xff0d0f14 };   // near-black navy panel (the real VS)
    static const juce::Colour kPanelLo { 0xff070809 };
    static const juce::Colour kSub     { 0xff14171e };   // section sub-panel
    static const juce::Colour kBlue    { 0xff2f6fe0 };   // blue label box / accent
    static const juce::Colour kBlueLo  { 0xff1b3f8e };
    static const juce::Colour kBlueTxt { 0xff6aa6ff };   // blue silkscreen text
    static const juce::Colour kBtn     { 0xff1b212c };   // membrane button (unselected)
    static const juce::Colour kBtnSel  { 0xff3f86e8 };   // selected button (lit blue)
    static const juce::Colour kLed     { 0xffe23b2a };   // red LED display
    static const juce::Colour kLedDim  { 0xff3a1410 };   // unlit LED segment bg
    static const juce::Colour kInk     { 0xff04060a };
    static const juce::Colour kWhite   { 0xffe6ebf2 };
    static const juce::Colour kDim     { 0xff707d90 };
    static const juce::Colour kOrange  { 0xffe07a22 };
    static const juce::Colour kLcdBg   { 0xff081026 };
    static const juce::Colour kLcdBlue { 0xff5fa8ff };

    static const char* const kFamilies[8] = { "SINE", "SAW", "SQR", "VOX", "BELL", "PULSE", "DIGI", "SCAN" };
}

//==============================================================================
// VecPad - the signature vector joystick. A 45-degree DIAMOND whose corners are the 4 oscillators
// (top=B, right=C, bottom=D, left=A). Drag the puck -> Vector X / Vector Y. A faint orange trail shows
// the 5-point vector-envelope orbit. Clicking drives the real vecX/vecY params.
class VecPad  : public juce::Component,
                private juce::AudioProcessorParameter::Listener,
                private juce::AsyncUpdater
{
public:
    VecPad() = default;
    ~VecPad() override { for (auto* p : listened_) if (p) p->removeListener (this); cancelPendingUpdate(); }

    void setParams (juce::AudioProcessorParameter* x, juce::AudioProcessorParameter* y,
                    std::array<juce::AudioProcessorParameter*, 4> wave,
                    std::array<juce::AudioProcessorParameter*, 10> env)
    {
        px_ = x; py_ = y; wave_ = wave; env_ = env;
        listened_ = { px_, py_ };
        for (auto* p : env_) listened_.push_back (p);
        for (auto* p : listened_) if (p) p->addListener (this);
        triggerAsyncUpdate();
    }

    void mouseDown (const juce::MouseEvent& e) override { dragTo (e.position); }
    void mouseDrag (const juce::MouseEvent& e) override { dragTo (e.position); }

    void paint (juce::Graphics& g) override
    {
        auto b = getLocalBounds().toFloat();
        g.setColour (vs::kInk); g.fillRoundedRectangle (b, 5.0f);
        g.setColour (vs::kBlue.withAlpha (0.5f)); g.drawRoundedRectangle (b.reduced (1.0f), 5.0f, 1.2f);

        const auto c = b.getCentre();
        const float rad = juce::jmin (b.getWidth(), b.getHeight()) * 0.5f - 16.0f;
        if (rad < 2.0f) return;
        const juce::Point<float> top (c.x, c.y - rad), right (c.x + rad, c.y), bot (c.x, c.y + rad), left (c.x - rad, c.y);
        juce::Path dia; dia.startNewSubPath (top); dia.lineTo (right); dia.lineTo (bot); dia.lineTo (left); dia.closeSubPath();
        g.setColour (vs::kPanelLo); g.fillPath (dia);
        g.setColour (vs::kBlue.withAlpha (0.4f)); g.strokePath (dia, juce::PathStrokeType (1.2f));
        g.setColour (vs::kBlue.withAlpha (0.15f));
        g.drawLine (left.x, c.y, right.x, c.y, 0.8f); g.drawLine (c.x, top.y, c.x, bot.y, 0.8f);

        // env orbit trail
        bool haveEnv = true; for (auto* p : env_) if (! p) haveEnv = false;
        if (haveEnv)
        {
            juce::Path trail; bool started = false; juce::Point<float> first;
            for (int i = 0; i < 5; ++i)
            {
                auto pt = vecToPoint (env_[(size_t) (i*2)]->getValue(), env_[(size_t) (i*2+1)]->getValue(), c, rad);
                if (! started) { trail.startNewSubPath (pt); first = pt; started = true; } else trail.lineTo (pt);
            }
            trail.lineTo (first);
            g.setColour (vs::kOrange.withAlpha (0.5f)); g.strokePath (trail, juce::PathStrokeType (1.3f, juce::PathStrokeType::curved));
        }
        // live puck
        const float vx = px_ ? px_->getValue() : 0.5f, vy = py_ ? py_->getValue() : 0.5f;
        auto puck = vecToPoint (vx, vy, c, rad);
        g.setColour (vs::kBlue.withAlpha (0.35f)); g.fillEllipse (puck.x - 9.0f, puck.y - 9.0f, 18.0f, 18.0f);
        g.setColour (vs::kLcdBlue); g.fillEllipse (puck.x - 5.0f, puck.y - 5.0f, 10.0f, 10.0f);
        g.setColour (juce::Colours::white.withAlpha (0.9f)); g.fillEllipse (puck.x - 2.0f, puck.y - 2.0f, 4.0f, 4.0f);
        // corner letters
        g.setColour (vs::kDim); g.setFont (toi::uiFont (7.0f, true));
        g.drawText ("B", juce::Rectangle<float> (c.x - 10.0f, top.y - 11.0f, 20.0f, 9.0f), juce::Justification::centred);
        g.drawText ("D", juce::Rectangle<float> (c.x - 10.0f, bot.y + 2.0f, 20.0f, 9.0f), juce::Justification::centred);
        g.drawText ("A", juce::Rectangle<float> (left.x - 16.0f, c.y - 4.0f, 14.0f, 9.0f), juce::Justification::centredRight);
        g.drawText ("C", juce::Rectangle<float> (right.x + 2.0f, c.y - 4.0f, 14.0f, 9.0f), juce::Justification::centredLeft);
    }

private:
    static juce::Point<float> vecToPoint (float vx, float vy, juce::Point<float> c, float rad)
    { return { c.x + (vx - 0.5f) * 2.0f * rad * 0.5f - (vy - 0.5f) * 2.0f * rad * 0.5f * 0.0f,
               c.y + (vy - 0.5f) * 2.0f * rad }; }
    void dragTo (juce::Point<float> p)
    {
        auto b = getLocalBounds().toFloat(); const auto c = b.getCentre();
        const float rad = juce::jmin (b.getWidth(), b.getHeight()) * 0.5f - 16.0f; if (rad <= 1.0f) return;
        float vx = juce::jlimit (0.0f, 1.0f, 0.5f + (p.x - c.x) / (2.0f * rad));
        float vy = juce::jlimit (0.0f, 1.0f, 0.5f + (p.y - c.y) / (2.0f * rad));
        if (px_) { px_->beginChangeGesture(); px_->setValueNotifyingHost (vx); px_->endChangeGesture(); }
        if (py_) { py_->beginChangeGesture(); py_->setValueNotifyingHost (vy); py_->endChangeGesture(); }
    }
    void parameterValueChanged (int, float) override { triggerAsyncUpdate(); }
    void parameterGestureChanged (int, bool) override {}
    void handleAsyncUpdate() override { repaint(); }
    juce::AudioProcessorParameter* px_ = nullptr; juce::AudioProcessorParameter* py_ = nullptr;
    std::array<juce::AudioProcessorParameter*, 4> wave_ { nullptr, nullptr, nullptr, nullptr };
    std::array<juce::AudioProcessorParameter*, 10> env_ {};
    std::vector<juce::AudioProcessorParameter*> listened_;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VecPad)
};

//==============================================================================
// VsSelButton - a small flat membrane SELECT button: a dark cap with a label + a tiny LED. Click =
// SELECT this parameter for editing (highlights blue + binds the DATA ENTRY). The LED lights when the
// param is above its default (engaged). Authentic VS button-grid editing.
class VsSelButton  : public juce::Component,
                     private juce::AudioProcessorParameter::Listener,
                     private juce::AsyncUpdater
{
public:
    VsSelButton (juce::String id, juce::String label) : id_ (std::move (id)), label_ (std::move (label)) {}
    ~VsSelButton() override { if (param_) param_->removeListener (this); cancelPendingUpdate(); }
    void attach (juce::AudioProcessorParameter* p) { param_ = p; if (param_) param_->addListener (this); triggerAsyncUpdate(); }
    void setSelected (bool s) { if (sel_ != s) { sel_ = s; repaint(); } }
    const juce::String& id() const { return id_; }
    std::function<void (const juce::String&)> onSelect;

    void mouseDown (const juce::MouseEvent&) override { if (onSelect) onSelect (id_); }

    void setCap (juce::Colour c) { cap_ = c; repaint(); }
    void paint (juce::Graphics& g) override
    {
        auto area = getLocalBounds().toFloat();
        const bool engaged = param_ ? std::abs (param_->getValue() - param_->getDefaultValue()) > 0.02f : false;
        // silkscreen label BELOW the cap (on the panel) - like the real hardware
        auto labelR = area.removeFromBottom (8.0f);
        // small SQUARE pushbutton cap (Omron B3J style), centred
        const float sz = juce::jmax (10.0f, juce::jmin (area.getWidth() - 4.0f, area.getHeight() - 2.0f, 26.0f));
        auto sq = juce::Rectangle<float> (0.0f, 0.0f, sz, sz).withCentre ({ area.getCentreX(), area.getCentreY() });
        const juce::Colour cap = sel_ ? cap_.brighter (0.28f) : cap_;
        juce::ColourGradient cg (cap.brighter (0.32f), sq.getX(), sq.getY(), cap.darker (0.5f), sq.getX(), sq.getBottom(), false);
        g.setGradientFill (cg); g.fillRoundedRectangle (sq, 2.4f);                                  // domed cap
        g.setColour (juce::Colours::white.withAlpha (0.13f)); g.fillRoundedRectangle (sq.withHeight (sz * 0.38f).reduced (1.6f, 1.2f), 1.8f);   // top sheen
        g.setColour (sel_ ? vs::kLed : juce::Colours::black.withAlpha (0.7f)); g.drawRoundedRectangle (sq, 2.4f, sel_ ? 1.1f : 0.8f);
        // RED LED top-right ON the cap (bright when SELECTED, dim when the param is engaged) - the VS signature
        const float lr = juce::jmax (1.3f, sz * 0.12f);
        const float lx = sq.getRight() - lr - 2.0f, ly = sq.getY() + lr + 2.0f;
        if (sel_) { g.setColour (vs::kLed.withAlpha (0.55f)); g.fillEllipse (lx - lr - 1.6f, ly - lr - 1.6f, (lr + 1.6f) * 2.0f, (lr + 1.6f) * 2.0f); }
        g.setColour (sel_ ? vs::kLed : (engaged ? vs::kLed.darker (0.15f) : juce::Colour (0xff3a201c))); g.fillEllipse (lx - lr, ly - lr, lr * 2.0f, lr * 2.0f);
        // silkscreen label
        g.setColour (vs::kWhite.withAlpha (0.82f)); g.setFont (toi::uiFont (juce::jmin (6.0f, labelR.getHeight() + 1.0f), false));
        g.drawText (label_, labelR, juce::Justification::centred);
    }
private:
    void parameterValueChanged (int, float) override { triggerAsyncUpdate(); }
    void parameterGestureChanged (int, bool) override {}
    void handleAsyncUpdate() override { repaint(); }
    juce::String id_, label_; bool sel_ = false;
    juce::Colour cap_ { 0xff15181e };   // black B3J cap by default
    juce::AudioProcessorParameter* param_ = nullptr;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VsSelButton)
};

//==============================================================================
// VsDataEntry - the DATA ENTRY: a vertical slider that edits whatever parameter is currently SELECTED.
// Drag to set 0..1; calls onChange so the LED updates. Authentic "select then data-enter" workflow.
class VsDataEntry  : public juce::Component,
                     private juce::AudioProcessorParameter::Listener,
                     private juce::AsyncUpdater
{
public:
    VsDataEntry() = default;
    std::function<void()> onChange;
    void setTarget (juce::AudioProcessorParameter* p)
    {
        if (target_) target_->removeListener (this);
        target_ = p; if (target_) target_->addListener (this);
        triggerAsyncUpdate();
    }
    ~VsDataEntry() override { if (target_) target_->removeListener (this); cancelPendingUpdate(); }

    void mouseDown (const juce::MouseEvent& e) override { dragTo (e.position); }
    void mouseDrag (const juce::MouseEvent& e) override { dragTo (e.position); }

    void paint (juce::Graphics& g) override
    {
        auto b = getLocalBounds().toFloat();
        auto track = b.reduced (b.getWidth() * 0.28f, 4.0f);
        g.setColour (vs::kInk); g.fillRoundedRectangle (track, 3.0f);
        g.setColour (vs::kBlue.withAlpha (0.4f)); g.drawRoundedRectangle (track, 3.0f, 1.0f);
        const float v = target_ ? target_->getValue() : 0.0f;
        auto fill = track.reduced (2.0f); fill = fill.withTrimmedTop (fill.getHeight() * (1.0f - v));
        g.setColour (target_ ? vs::kBlue : vs::kDim.withAlpha (0.3f)); g.fillRoundedRectangle (fill, 2.0f);
        // thumb
        const float ty = track.getBottom() - 3.0f - v * (track.getHeight() - 6.0f);
        g.setColour (vs::kLcdBlue); g.fillRoundedRectangle (track.getX() - 2.0f, ty - 3.0f, track.getWidth() + 4.0f, 6.0f, 2.0f);
    }
private:
    void dragTo (juce::Point<float> p)
    {
        if (! target_) return;
        auto track = getLocalBounds().toFloat().reduced (getWidth() * 0.28f, 4.0f);
        float v = juce::jlimit (0.0f, 1.0f, 1.0f - (p.y - track.getY()) / juce::jmax (1.0f, track.getHeight()));
        target_->beginChangeGesture(); target_->setValueNotifyingHost (v); target_->endChangeGesture();
        if (onChange) onChange();
        repaint();
    }
    void parameterValueChanged (int, float) override { triggerAsyncUpdate(); }
    void parameterGestureChanged (int, bool) override {}
    void handleAsyncUpdate() override { repaint(); if (onChange) onChange(); }
    juce::AudioProcessorParameter* target_ = nullptr;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VsDataEntry)
};

//==============================================================================
// VsLed - a red 2-character LED display: shows the SELECTED parameter's value (00-99) while editing,
// or the program number otherwise.
class VsLed  : public juce::Component
{
public:
    VsLed() = default;
    void setText (juce::String t) { if (t != text_) { text_ = std::move (t); repaint(); } }
    void paint (juce::Graphics& g) override
    {
        auto b = getLocalBounds().toFloat();
        g.setColour (juce::Colours::black); g.fillRoundedRectangle (b, 3.0f);
        g.setColour (vs::kLed.withAlpha (0.25f)); g.drawRoundedRectangle (b.reduced (1.0f), 3.0f, 1.0f);
        g.setColour (vs::kLed);
        g.setFont (juce::Font (juce::FontOptions (b.getHeight() * 0.7f).withName ("Menlo")).boldened());
        g.drawText (text_, b, juce::Justification::centred);
    }
private:
    juce::String text_ { "00" };
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VsLed)
};

//==============================================================================
// VsEnvGraph - the little vector-ENVELOPE diagram icon (the real VS shows this in the Env group): draws
// the 5-point vector-env orbit. Live (reads the env XY params).
class VsEnvGraph  : public juce::Component,
                    private juce::AudioProcessorParameter::Listener,
                    private juce::AsyncUpdater
{
public:
    VsEnvGraph() = default;
    void setParams (std::array<juce::AudioProcessorParameter*, 10> e) { env_ = e; for (auto* p : env_) if (p) p->addListener (this); triggerAsyncUpdate(); }
    ~VsEnvGraph() override { for (auto* p : env_) if (p) p->removeListener (this); cancelPendingUpdate(); }
    void paint (juce::Graphics& g) override
    {
        auto b = getLocalBounds().toFloat();
        g.setColour (vs::kLcdBg); g.fillRoundedRectangle (b, 2.0f);
        g.setColour (vs::kBlue.withAlpha (0.4f)); g.drawRoundedRectangle (b.reduced (0.5f), 2.0f, 0.8f);
        bool ok = true; for (auto* p : env_) if (! p) ok = false; if (! ok) return;
        auto a = b.reduced (3.0f);
        juce::Path path; bool started = false;
        for (int i = 0; i < 5; ++i)
        {
            const float x = a.getX() + env_[(size_t)(i*2)]->getValue() * a.getWidth();
            const float y = a.getBottom() - env_[(size_t)(i*2+1)]->getValue() * a.getHeight();
            if (! started) { path.startNewSubPath (x, y); started = true; } else path.lineTo (x, y);
        }
        g.setColour (vs::kLcdBlue); g.strokePath (path, juce::PathStrokeType (1.0f, juce::PathStrokeType::curved));
    }
private:
    void parameterValueChanged (int, float) override { triggerAsyncUpdate(); }
    void parameterGestureChanged (int, bool) override {}
    void handleAsyncUpdate() override { repaint(); }
    std::array<juce::AudioProcessorParameter*, 10> env_ {};
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VsEnvGraph)
};

//==============================================================================
class VSFunc  : public juce::Button
{
public:
    VSFunc (const juce::String& t, juce::Colour fill) : juce::Button (t), col (fill) { setButtonText (t); }
    void flash() { flashing = true; repaint(); juce::Timer::callAfterDelay (150, [s = juce::Component::SafePointer<VSFunc> (this)] { if (s) { s->flashing = false; s->repaint(); } }); }
    void paintButton (juce::Graphics& g, bool over, bool down) override
    {
        auto b = getLocalBounds().toFloat().reduced (1.0f);
        auto fill = flashing ? col.brighter (0.3f) : down ? col.darker (0.18f) : over ? col.brighter (0.08f) : col;
        g.setColour (fill); g.fillRoundedRectangle (b, 2.5f);
        g.setColour (juce::Colours::black.withAlpha (0.5f)); g.drawRoundedRectangle (b, 2.5f, 1.0f);
        g.setColour (fill.getPerceivedBrightness() > 0.6f ? vs::kInk : juce::Colours::white.withAlpha (0.92f));
        g.setFont (toi::uiFont (juce::jmin (9.0f, b.getHeight() * 0.5f), true));
        g.drawText (getButtonText(), getLocalBounds(), juce::Justification::centred);
    }
private:
    juce::Colour col; bool flashing = false;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VSFunc)
};

//==============================================================================
inline toi::Config jwvsConfig()
{
    toi::Config c;
    c.model = "JW-VS";
    auto& p = c.pal;
    p.bg = vs::kPanel; p.bg2 = vs::kPanelLo; p.frame = juce::Colour (0xff05070b); p.ink = vs::kInk;
    p.accent = vs::kBlue; p.accent2 = vs::kOrange; p.button = vs::kBtn;
    p.thumb = vs::kBlue; p.text = vs::kWhite;
    p.noteStrip = vs::kPanelLo;
    p.lcdBg = vs::kLcdBg; p.lcdInk = vs::kLcdBlue;
    p.keyWhite = juce::Colour (0xffe9ebee); p.keyWhitePr = vs::kBlue; p.keyBlack = juce::Colour (0xff14171d); p.keyBlackPr = vs::kBlue;

    c.params = {
        { "waveA","WAVE A" },{ "waveB","WAVE B" },{ "waveC","WAVE C" },{ "waveD","WAVE D" },{ "detune","DETUNE" },
        { "vecX","VEC X" },{ "vecY","VEC Y" },
        { "vRate1","R1" },{ "vRate2","R2" },{ "vRate3","R3" },{ "vRate4","R4" },{ "vRate5","R5" },
        { "vX0","X0" },{ "vY0","Y0" },{ "vX1","X1" },{ "vY1","Y1" },{ "vX2","X2" },{ "vY2","Y2" },
        { "vX3","X3" },{ "vY3","Y3" },{ "vX4","X4" },{ "vY4","Y4" },
        { "vLoop","LOOP" },{ "vDepth","DEPTH" },
        { "cutoff","CUTOFF" },{ "reso","RESO" },{ "fEnv","ENV" },{ "fKeyTrack","KBD" },{ "drive","DRIVE" },
        { "fR1","R1" },{ "fR2","R2" },{ "fR3","R3" },{ "fR4","R4" },{ "fR5","R5" },{ "fL1","L1" },{ "fL2","L2" },{ "fL3","L3" },
        { "aR1","R1" },{ "aR2","R2" },{ "aR3","R3" },{ "aR4","R4" },{ "aR5","R5" },{ "aL1","L1" },{ "aL2","L2" },{ "aL3","L3" },
        { "lfo1Rate","RATE" },{ "lfo1Shape","SHAPE" },{ "lfo1Pitch","PIT" },{ "lfo1Filt","FLT" },{ "lfo1VecX","VX" },{ "lfo1VecY","VY" },
        { "lfo2Rate","RATE" },{ "lfo2Shape","SHAPE" },{ "lfo2Pitch","PIT" },{ "lfo2Filt","FLT" },{ "lfo2VecX","VX" },{ "lfo2VecY","VY" },
        { "glide","GLIDE" },{ "volume","VOL" },{ "tune","TUNE" },
    };
    return c;
}

//==============================================================================
class JWVSEditor  : public toi::PanelEditor
{
public:
    struct Sec { juce::String name; std::vector<std::pair<juce::String, juce::String>> ids; bool envIcon = false; juce::Rectangle<float> rect {}; };

    JWVSEditor (juce::AudioProcessor& proc, juce::MidiKeyboardState& kb)
        : toi::PanelEditor (proc, kb, jwvsConfig())
    {
        pad_ = std::make_unique<VecPad>();
        pad_->setParams (findParam ("vecX"), findParam ("vecY"),
                         { findParam ("waveA"), findParam ("waveB"), findParam ("waveC"), findParam ("waveD") },
                         envArr());
        addAndMakeVisible (*pad_);

        // ---- the sectioned button-grid (each section = a blue label box + a row of SELECT buttons) ----
        secs_ = {
            { "OSCILLATORS", { {"waveA","A"},{"waveB","B"},{"waveC","C"},{"waveD","D"},{"detune","DET"} } },
            { "VECTOR",      { {"vecX","X"},{"vecY","Y"},{"vDepth","DEP"},{"vLoop","LOOP"} } },
            { "VECTOR ENV",  { {"vRate1","R1"},{"vRate2","R2"},{"vRate3","R3"},{"vRate4","R4"},{"vRate5","R5"} }, true },
            { "FILTER",      { {"cutoff","FRQ"},{"reso","RES"},{"fEnv","ENV"},{"fKeyTrack","KBD"},{"drive","DRV"} } },
            { "FILTER ENV",  { {"fR1","R1"},{"fR2","R2"},{"fR3","R3"},{"fR4","R4"},{"fR5","R5"},{"fL1","L1"},{"fL2","L2"},{"fL3","L3"} } },
            { "AMP ENV",     { {"aR1","R1"},{"aR2","R2"},{"aR3","R3"},{"aR4","R4"},{"aR5","R5"},{"aL1","L1"},{"aL2","L2"},{"aL3","L3"} } },
            { "LFO 1",       { {"lfo1Rate","RAT"},{"lfo1Shape","SHP"},{"lfo1Pitch","PIT"},{"lfo1Filt","FLT"},{"lfo1VecX","VX"},{"lfo1VecY","VY"} } },
            { "LFO 2",       { {"lfo2Rate","RAT"},{"lfo2Shape","SHP"},{"lfo2Pitch","PIT"},{"lfo2Filt","FLT"},{"lfo2VecX","VX"},{"lfo2VecY","VY"} } },
            { "VOICE",       { {"glide","GLI"},{"volume","VOL"},{"tune","TUN"} } },
        };
        for (auto& s : secs_)
            for (auto& pr : s.ids)
            {
                auto btn = std::make_unique<VsSelButton> (pr.first, pr.second);
                btn->attach (findParam (pr.first));
                btn->onSelect = [this] (const juce::String& id) { selectParam (id); };
                addAndMakeVisible (*btn); selMap_[pr.first] = btn.get(); selBtns_.push_back (std::move (btn));
            }

        // env graph icon (lives in the VECTOR ENV box)
        envGraph_ = std::make_unique<VsEnvGraph>(); envGraph_->setParams (envArr()); addAndMakeVisible (*envGraph_);

        // DATA ENTRY + LED
        data_ = std::make_unique<VsDataEntry>(); data_->onChange = [this] { updateLed(); }; addAndMakeVisible (*data_);
        led_  = std::make_unique<VsLed>(); addAndMakeVisible (*led_);

        // small real-audio scope (the VS LCD)
        scope_ = std::make_unique<toi::Lcd> (pal()); scope_->attachScope (audioTap()); addAndMakeVisible (*scope_);

        // PROGRAM SELECT row (16) + RAND/SAVE
        for (int i = 0; i < 16; ++i)
        { auto b = std::make_unique<toi::MoldedButton> (juce::Colour (0xff10141c)); b->setLit (vs::kBlue); const int idx = i; b->onClick = [this, idx] { recallSlot (idx); }; addAndMakeVisible (*b); slots_.push_back (std::move (b)); }
        rand_ = std::make_unique<VSFunc> ("RAND", vs::kBlueLo); save_ = std::make_unique<VSFunc> ("SAVE", vs::kOrange.darker (0.1f));
        rand_->onClick = [this] { doRandom(); rand_->flash(); }; save_->onClick = [this] { saveSlot (activeSlot()); save_->flash(); };
        addAndMakeVisible (*rand_); addAndMakeVisible (*save_);

        selectParam ("cutoff");
        finishSetup();
    }

protected:
    void setPresetActiveVisual (int idx) override { for (int i = 0; i < (int) slots_.size(); ++i) slots_[(size_t) i]->setActive (i == idx); }

    void selectParam (const juce::String& id)
    {
        selectedId_ = id;
        for (auto& b : selBtns_) b->setSelected (b->id() == id);
        if (data_) data_->setTarget (findParam (id));
        updateLed();
    }
    void updateLed()
    {
        if (! led_) return;
        if (auto* p = findParam (selectedId_)) { int v = juce::roundToInt (p->getValue() * 99.0f); led_->setText (juce::String (v).paddedLeft ('0', 2)); }
    }
    std::array<juce::AudioProcessorParameter*, 10> envArr()
    {
        return { findParam ("vX0"), findParam ("vY0"), findParam ("vX1"), findParam ("vY1"),
                 findParam ("vX2"), findParam ("vY2"), findParam ("vX3"), findParam ("vY3"),
                 findParam ("vX4"), findParam ("vY4") };
    }

    void paintPanel (juce::Graphics& g, juce::Rectangle<float> panel) override
    {
        rPanel = panel;
        // flat dark navy panel
        juce::ColourGradient bg (vs::kPanel, panel.getCentreX(), panel.getY(), vs::kPanelLo, panel.getCentreX(), panel.getBottom(), false);
        g.setGradientFill (bg); g.fillRoundedRectangle (panel, 5.0f);
        g.setColour (juce::Colours::black); g.drawRoundedRectangle (panel, 5.0f, 1.2f);

        // brand top-right
        { auto bh = rBrand_;
          drawViewLeds (g, bh.removeFromRight (96.0f));
          g.setColour (vs::kBlueTxt); g.setFont (toi::uiFont (15.0f, true));
          g.drawText ("JW-VS", bh, juce::Justification::centredRight); }

        // VECTOR + DATA ENTRY labels
        g.setColour (vs::kBlueTxt); g.setFont (toi::uiFont (6.5f, true).withExtraKerningFactor (0.1f));
        g.drawText ("VECTOR", juce::Rectangle<float> (rPad_.getX(), rPad_.getY() - 9.0f, rPad_.getWidth(), 8.0f), juce::Justification::centred);
        g.drawText ("DATA ENTRY", juce::Rectangle<float> (rData_.getX() - 6.0f, rData_.getY() - 9.0f, rData_.getWidth() + 60.0f, 8.0f), juce::Justification::centredLeft);

        // each section: blue label box + sub-panel
        for (auto& s : secs_) drawSection (g, s);

        // program-select label
        g.setColour (vs::kBlueTxt); g.setFont (toi::uiFont (6.5f, true).withExtraKerningFactor (0.1f));
        g.drawText ("PROGRAM  SELECT", juce::Rectangle<float> (rPreset_.getX(), rPreset_.getY() - 9.0f, 200.0f, 8.0f), juce::Justification::centredLeft);
    }

    void drawSection (juce::Graphics& g, const Sec& s)
    {
        auto r = s.rect;
        // sub-panel
        g.setColour (vs::kSub); g.fillRoundedRectangle (r, 3.0f);
        g.setColour (juce::Colours::black.withAlpha (0.5f)); g.drawRoundedRectangle (r, 3.0f, 0.8f);
        // blue label box across the top
        auto lbl = r.withHeight (12.0f).reduced (3.0f, 2.0f);
        g.setColour (vs::kBlue); g.fillRoundedRectangle (lbl, 2.0f);
        g.setColour (juce::Colours::white); g.setFont (toi::uiFont (6.5f, true).withExtraKerningFactor (0.06f));
        g.drawText (s.name, lbl.reduced (4.0f, 0.0f), juce::Justification::centredLeft);
    }

    void layoutPanel (juce::Rectangle<float> panel) override
    {
        rPanel = panel;
        auto inner = panel.reduced (0.0f, 5.0f);
        inner.removeFromLeft (10.0f); inner.removeFromRight (10.0f);

        rBrand_ = inner.removeFromTop (18.0f);
        inner.removeFromTop (4.0f);

        // ===== LEFT column: VECTOR pad + DATA ENTRY + LED + small scope =====
        auto left = inner.removeFromLeft (158.0f);
        inner.removeFromLeft (10.0f);
        left.removeFromTop (9.0f);                       // VECTOR label gap
        rPad_ = left.removeFromTop (118.0f).reduced (2.0f, 0.0f); placeInArtboard (*pad_, rPad_);
        left.removeFromTop (12.0f);                      // DATA ENTRY label gap
        auto de = left.removeFromTop (78.0f);
        rData_ = de.removeFromLeft (34.0f); placeInArtboard (*data_, rData_);
        de.removeFromLeft (8.0f);
        auto rLed = de.removeFromTop (40.0f); placeInArtboard (*led_, rLed.reduced (0.0f, 2.0f));
        de.removeFromTop (4.0f);
        rScope_ = de; placeInArtboard (*scope_, rScope_);

        // ===== bottom strip: PROGRAM SELECT (16) + RAND/SAVE =====
        auto bottom = inner.removeFromBottom (40.0f);
        inner.removeFromBottom (6.0f);
        { auto rs = bottom.removeFromRight (96.0f); bottom.removeFromRight (8.0f);
          rPreset_ = bottom.withTrimmedTop (9.0f);
          const int pc = 16; const float pgap = 3.0f;
          const float pw = (rPreset_.getWidth() - pgap * (pc - 1)) / (float) pc;
          for (int i = 0; i < 16; ++i) placeInArtboard (*slots_[(size_t) i], juce::Rectangle<float> (rPreset_.getX() + (float) i * (pw + pgap), rPreset_.getY(), pw, rPreset_.getHeight()));
          auto ra = rs.withTrimmedTop (9.0f); const float bw = (ra.getWidth() - 6.0f) * 0.5f;
          placeInArtboard (*rand_, ra.removeFromLeft (bw)); ra.removeFromLeft (6.0f); placeInArtboard (*save_, ra); }

        // ===== section grid: 3 rows =====
        const float rgap = 6.0f;
        auto gridArea = inner;
        const float rowH = (gridArea.getHeight() - rgap * 2.0f) / 3.0f;
        auto row1 = gridArea.removeFromTop (rowH); gridArea.removeFromTop (rgap);
        auto row2 = gridArea.removeFromTop (rowH); gridArea.removeFromTop (rgap);
        auto row3 = gridArea;
        // row1: OSCILLATORS, VECTOR, VECTOR ENV, FILTER
        layoutSecRow (row1, { 0, 1, 2, 3 }, { 5, 4, 6, 5 });
        // row2: FILTER ENV, AMP ENV
        layoutSecRow (row2, { 4, 5 }, { 8, 8 });
        // row3: LFO 1, LFO 2, VOICE
        layoutSecRow (row3, { 6, 7, 8 }, { 6, 6, 3 });
    }

    // place a row of sections, widths proportional to their button counts (weights)
    void layoutSecRow (juce::Rectangle<float> row, std::initializer_list<int> idx, std::initializer_list<int> weights)
    {
        const float hgap = 6.0f;
        float total = 0.0f; for (int w : weights) total += (float) w;
        const float usable = row.getWidth() - hgap * (float) (weights.size() - 1);
        float x = row.getX();
        auto wi = weights.begin();
        for (int si : idx)
        {
            const float w = usable * ((float) *wi / total);
            placeSection (secs_[(size_t) si], juce::Rectangle<float> (x, row.getY(), w, row.getHeight()));
            x += w + hgap; ++wi;
        }
    }

    void placeSection (Sec& s, juce::Rectangle<float> box)
    {
        s.rect = box;
        auto a = box.reduced (4.0f, 0.0f).withTrimmedTop (14.0f).withTrimmedBottom (3.0f);
        const int n = (int) s.ids.size();
        // env-icon sections reserve a strip on the right for the graph
        if (s.envIcon && envGraph_) { auto gr = a.removeFromRight (a.getWidth() * 0.34f).reduced (2.0f); placeInArtboard (*envGraph_, gr); a.removeFromRight (3.0f); }
        // all buttons in ONE row, same size as the oscillator buttons (no stacking)
        const int perRow = n;
        const int rows = 1;
        const float bgap = 2.5f;
        const float bw = (a.getWidth() - bgap * (perRow - 1)) / (float) perRow;
        const float bh = (a.getHeight() - bgap * (rows - 1)) / (float) rows;
        for (int i = 0; i < n; ++i)
        {
            const int rr = i / perRow, cc = i % perRow;
            if (auto* b = selFor (s.ids[(size_t) i].first))
                placeInArtboard (*b, juce::Rectangle<float> (a.getX() + (float) cc * (bw + bgap), a.getY() + (float) rr * (bh + bgap), bw, bh));
        }
    }

    VsSelButton* selFor (const juce::String& id) const { auto it = selMap_.find (id); return it == selMap_.end() ? nullptr : it->second; }

    std::unique_ptr<VecPad> pad_;
    std::vector<std::unique_ptr<VsSelButton>> selBtns_;
    std::map<juce::String, VsSelButton*> selMap_;
    std::unique_ptr<VsDataEntry> data_;
    std::unique_ptr<VsLed> led_;
    std::unique_ptr<VsEnvGraph> envGraph_;
    std::unique_ptr<toi::Lcd> scope_;
    std::vector<std::unique_ptr<toi::MoldedButton>> slots_;
    std::unique_ptr<VSFunc> rand_, save_;
    std::vector<Sec> secs_;
    juce::String selectedId_;
    juce::Rectangle<float> rPanel, rPad_, rData_, rScope_, rPreset_, rBrand_;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JWVSEditor)
};

//==============================================================================
class JWVSPlugin  : public cmaj::plugin::GeneratedPlugin<::JWVS>,
                    public toi::AudioTapSource,
                    public toi::PresetStore
{
public:
    using Base = cmaj::plugin::GeneratedPlugin<::JWVS>;
    JWVSPlugin (std::shared_ptr<cmaj::Patch> p) : Base (std::move (p)) {}
    juce::AudioProcessorEditor* createEditor() override { return new JWVSEditor (*this, keyboardState); }
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
