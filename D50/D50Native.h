// JW-D50 native faceplate (glossy LA-synthesis digital workstation) on the toi_faceplate.h kit.
// A near-black D-50-style workstation, but EVERY control is REAL - no decorative buttons. PLAY page:
// a functional JOYSTICK XY mod pad (cutoff x LFO depth), the big blue-green LCD (patch name + real
// scope), real STRUCTURE + ATTACK WAVE selector banks, real INC/DEC preset steppers, WRITE/RAND, and
// the PATCH BANK / PATCH NUMBER rows (the 16 presets). EDIT page: the rest of the sound parameters.
#pragma once

#include "toi_faceplate.h"

struct JWD50;

namespace d50
{
    static const juce::Colour kPanel  { 0xff17181c };   // near-black workstation panel
    static const juce::Colour kPanelLo{ 0xff0d0e11 };
    static const juce::Colour kFrame  { 0xff050507 };
    static const juce::Colour kText   { 0xffe4e6ea };
    static const juce::Colour kDim    { 0xff8b8f97 };
    static const juce::Colour kScreen  { 0xff74c24a };  // LCD green - screen text + scope
    static const juce::Colour kTeal    { 0xff93b2f0 };  // light-blue accent (knobs, STRUCTURE/WAVE, joystick, WRITE)
    static const juce::Colour kBlueHi  { 0xffc3d4ff };  // lit light-blue LED / highlight
    static const juce::Colour kBlue    { 0xff6f9aee };
    static const juce::Colour kRed     { 0xffc23a2c };  // PRESET buttons ONLY (active/pressed)
    static const juce::Colour kRedHi   { 0xffff5a44 };  // lit red LED (presets)
    static const juce::Colour kBtn     { 0xff33363c };
    static const juce::Colour kBtnLo   { 0xff202227 };
}

//==============================================================================
// D50Func - a real membrane button (RAND / WRITE / INC / DEC).
class D50Func  : public juce::Button
{
public:
    D50Func (const juce::String& text, juce::Colour accent) : juce::Button (text), acc (accent) { setButtonText (text); }
    void flash() { flashing = true; repaint(); juce::Timer::callAfterDelay (140, [s = juce::Component::SafePointer<D50Func> (this)] { if (s) { s->flashing = false; s->repaint(); } }); }
    void paintButton (juce::Graphics& g, bool over, bool down) override
    {
        auto b = getLocalBounds().toFloat().reduced (1.0f);
        g.setColour (juce::Colours::black.withAlpha (0.5f)); g.fillRoundedRectangle (b.translated (0.0f, 1.0f), 2.5f);
        const auto base = down ? d50::kBtn.darker (0.2f) : over ? d50::kBtn.brighter (0.12f) : d50::kBtn;
        juce::ColourGradient cg (base.brighter (0.18f), b.getCentreX(), b.getY(), base.darker (0.22f), b.getCentreX(), b.getBottom(), false);
        g.setGradientFill (cg); g.fillRoundedRectangle (b, 2.5f);
        g.setColour (juce::Colours::white.withAlpha (0.10f)); g.fillRoundedRectangle (b.withHeight (b.getHeight() * 0.4f).reduced (1.0f, 0.0f), 1.8f);
        g.setColour (flashing ? d50::kBlueHi : acc.withAlpha (0.85f)); g.drawRoundedRectangle (b, 2.5f, flashing ? 1.6f : 1.0f);
        g.setColour (flashing ? d50::kBlueHi : acc); g.setFont (toi::uiFont (juce::jmin (9.0f, b.getHeight() * 0.5f), true));
        g.drawText (getButtonText(), getLocalBounds(), juce::Justification::centred);
    }
private:
    juce::Colour acc; bool flashing = false;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (D50Func)
};

//==============================================================================
// D50Bank - a REAL radio group bound to one 0..1 param (STRUCTURE / ATTACK WAVE). N labelled
// buttons; the active one lit teal. Click sets the param to i/(N-1); active = round(v*(N-1)).
class D50Bank  : public juce::Component,
                 private juce::AudioProcessorParameter::Listener,
                 private juce::AsyncUpdater
{
public:
    D50Bank (juce::StringArray opts, juce::String titleText) : options (std::move (opts)), title (std::move (titleText)) {}
    ~D50Bank() override { if (param) param->removeListener (this); cancelPendingUpdate(); }
    void attach (juce::AudioProcessorParameter& p) { param = &p; param->addListener (this); triggerAsyncUpdate(); }
    int count() const { return options.size(); }
    int activeIndex() const { return (param == nullptr || count() <= 1) ? 0 : juce::jlimit (0, count() - 1, (int) std::lround (param->getValue() * (float) (count() - 1))); }
    void mouseDown (const juce::MouseEvent& e) override
    {
        const int n = count(); if (n <= 0 || param == nullptr) return;
        auto a = btnArea();
        int i = juce::jlimit (0, n - 1, (int) ((e.position.x - a.getX()) / (a.getWidth() / (float) n)));
        param->beginChangeGesture(); param->setValueNotifyingHost ((float) i / (float) (n - 1)); param->endChangeGesture();
    }
    void paint (juce::Graphics& g) override
    {
        if (title.isNotEmpty())
        { g.setColour (d50::kDim); g.setFont (toi::uiFont (7.0f, true).withExtraKerningFactor (0.12f)); g.drawText (title, getLocalBounds().toFloat().removeFromTop (10.0f), juce::Justification::centredLeft); }
        auto a = btnArea(); const int n = count(); if (n <= 0) return;
        const float bw = a.getWidth() / (float) n; const int act = activeIndex();
        for (int i = 0; i < n; ++i)
        {
            auto box = juce::Rectangle<float> (a.getX() + (float) i * bw, a.getY(), bw, a.getHeight()).reduced (3.5f, 2.0f);
            const bool on = (i == act);
            g.setColour (juce::Colours::black.withAlpha (0.5f)); g.fillRoundedRectangle (box.translated (0.0f, 1.0f), 2.6f);
            const auto base = on ? d50::kBtn.brighter (0.12f) : d50::kBtn;
            juce::ColourGradient cg (base.brighter (0.18f), box.getCentreX(), box.getY(), base.darker (0.22f), box.getCentreX(), box.getBottom(), false);
            g.setGradientFill (cg); g.fillRoundedRectangle (box, 2.6f);
            g.setColour (juce::Colours::white.withAlpha (on ? 0.16f : 0.08f)); g.fillRoundedRectangle (box.withHeight (box.getHeight() * 0.40f).reduced (1.5f, 0.0f), 2.0f);
            g.setColour (on ? d50::kTeal : juce::Colours::black.withAlpha (0.6f)); g.drawRoundedRectangle (box, 2.6f, on ? 1.4f : 0.8f);
            // LED dot (D-50 style), lit light-blue when active
            const float lr = 2.2f, lx = box.getCentreX(), ly = box.getY() + 4.6f;
            if (on) { g.setColour (d50::kBlueHi.withAlpha (0.5f)); g.fillEllipse (lx - lr - 2.0f, ly - lr - 2.0f, (lr + 2.0f) * 2.0f, (lr + 2.0f) * 2.0f); }
            g.setColour (on ? d50::kBlueHi : d50::kTeal.withAlpha (0.22f)); g.fillEllipse (lx - lr, ly - lr, lr * 2.0f, lr * 2.0f);
            g.setColour (juce::Colours::black.withAlpha (0.55f)); g.drawEllipse (lx - lr, ly - lr, lr * 2.0f, lr * 2.0f, 0.6f);
            g.setColour (on ? d50::kText : d50::kDim); g.setFont (toi::uiFont (juce::jmin (8.5f, box.getHeight() * 0.40f), true));
            g.drawText (options[i], box.withTrimmedTop (5.0f), juce::Justification::centred);
        }
    }
private:
    juce::Rectangle<float> btnArea() const { auto b = getLocalBounds().toFloat(); if (title.isNotEmpty()) b.removeFromTop (11.0f); return b; }
    void parameterValueChanged (int, float) override { triggerAsyncUpdate(); }
    void parameterGestureChanged (int, bool) override {}
    void handleAsyncUpdate() override { repaint(); }
    juce::StringArray options; juce::String title;
    juce::AudioProcessorParameter* param = nullptr;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (D50Bank)
};

//==============================================================================
// D50XYPad - a REAL 2D performance pad (the D-50 joystick) bound to two params: X and Y. Drag to
// sweep both at once; the ball tracks the live param values. Here X = filter cutoff, Y = LFO depth.
class D50XYPad  : public juce::Component,
                  private juce::AudioProcessorParameter::Listener,
                  private juce::AsyncUpdater
{
public:
    D50XYPad() = default;
    ~D50XYPad() override { if (px) px->removeListener (this); if (py) py->removeListener (this); cancelPendingUpdate(); }
    void attach (juce::AudioProcessorParameter* x, juce::AudioProcessorParameter* y)
    { px = x; py = y; if (px) px->addListener (this); if (py) py->addListener (this); triggerAsyncUpdate(); }
    void mouseDown (const juce::MouseEvent& e) override { if (px) px->beginChangeGesture(); if (py) py->beginChangeGesture(); drag (e); }
    void mouseDrag (const juce::MouseEvent& e) override { drag (e); }
    void mouseUp   (const juce::MouseEvent&)   override { if (px) px->endChangeGesture(); if (py) py->endChangeGesture(); }
    void paint (juce::Graphics& g) override
    {
        auto r = padArea();
        g.setColour (juce::Colour (0xff0a0b0d)); g.fillRoundedRectangle (r, 6.0f);
        g.setColour (juce::Colours::black); g.drawRoundedRectangle (r, 6.0f, 1.5f);
        // crosshair guides
        g.setColour (d50::kDim.withAlpha (0.18f));
        g.drawLine (r.getCentreX(), r.getY() + 4.0f, r.getCentreX(), r.getBottom() - 4.0f, 0.8f);
        g.drawLine (r.getX() + 4.0f, r.getCentreY(), r.getRight() - 4.0f, r.getCentreY(), 0.8f);
        // arrows
        g.setColour (d50::kDim.withAlpha (0.5f));
        const auto c = r.getCentre(); const float ar = r.getWidth() * 0.40f;
        auto tri = [&] (float ang) { juce::Path p; const float dx = std::sin (ang), dy = -std::cos (ang), pxn = -dy, pyn = dx;
            p.startNewSubPath (c.x + dx * ar, c.y + dy * ar); p.lineTo (c.x + dx * (ar - 5.0f) + pxn * 3.5f, c.y + dy * (ar - 5.0f) + pyn * 3.5f);
            p.lineTo (c.x + dx * (ar - 5.0f) - pxn * 3.5f, c.y + dy * (ar - 5.0f) - pyn * 3.5f); p.closeSubPath(); g.fillPath (p); };
        tri (0.0f); tri (juce::MathConstants<float>::pi); tri (juce::MathConstants<float>::halfPi); tri (-juce::MathConstants<float>::halfPi);
        // ball at live param position
        const float vx = px ? px->getValue() : 0.5f, vy = py ? py->getValue() : 0.5f;
        const float bx = r.getX() + 8.0f + vx * (r.getWidth() - 16.0f);
        const float by = r.getBottom() - 8.0f - vy * (r.getHeight() - 16.0f);
        const float rad = r.getWidth() * 0.16f;
        g.setColour (juce::Colours::black.withAlpha (0.5f)); g.fillEllipse (bx - rad, by - rad + 2.0f, rad * 2.0f, rad * 2.0f);
        juce::ColourGradient ball (d50::kTeal.brighter (0.15f), bx - rad * 0.4f, by - rad * 0.45f, juce::Colour (0xff1a3252), bx + rad * 0.5f, by + rad * 0.6f, true);
        g.setGradientFill (ball); g.fillEllipse (bx - rad, by - rad, rad * 2.0f, rad * 2.0f);
        g.setColour (juce::Colours::white.withAlpha (0.35f)); g.fillEllipse (bx - rad * 0.45f, by - rad * 0.55f, rad * 0.55f, rad * 0.38f);
        g.setColour (juce::Colours::black); g.drawEllipse (bx - rad, by - rad, rad * 2.0f, rad * 2.0f, 1.0f);
        g.setColour (d50::kDim); g.setFont (toi::uiFont (6.0f, true).withExtraKerningFactor (0.08f));
        g.drawText ("BENDER  -  CUTOFF / LFO", getLocalBounds().toFloat().removeFromBottom (9.0f), juce::Justification::centred);
    }
private:
    juce::Rectangle<float> padArea() const { return getLocalBounds().toFloat().withTrimmedBottom (10.0f); }
    void drag (const juce::MouseEvent& e)
    {
        auto r = padArea();
        if (px) px->setValueNotifyingHost (juce::jlimit (0.0f, 1.0f, (e.position.x - (r.getX() + 8.0f)) / (r.getWidth()  - 16.0f)));
        if (py) py->setValueNotifyingHost (juce::jlimit (0.0f, 1.0f, ((r.getBottom() - 8.0f) - e.position.y) / (r.getHeight() - 16.0f)));
    }
    void parameterValueChanged (int, float) override { triggerAsyncUpdate(); }
    void parameterGestureChanged (int, bool) override {}
    void handleAsyncUpdate() override { repaint(); }
    juce::AudioProcessorParameter* px = nullptr; juce::AudioProcessorParameter* py = nullptr;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (D50XYPad)
};

//==============================================================================
// D50EnvView - a LIVE envelope display bound to real params (NOT a static drawing). It reads the
// current param values every repaint and redraws the curve, and listens to those params so it
// updates whenever they change (preset load / EDIT-page tweak). MultiStage = TVA/TVF shape (T1/T2/
// breakpoint/T3/sustain/release); Pitch = the attack pitch-env scoop (flat when P.ENV is centred).
class D50EnvView  : public juce::Component,
                    private juce::AudioProcessorParameter::Listener,
                    private juce::AsyncUpdater
{
public:
    enum Kind { MultiStage, Pitch };
    D50EnvView (juce::String title, Kind k) : title_ (std::move (title)), kind_ (k) {}
    ~D50EnvView() override { for (auto* p : params_) if (p) p->removeListener (this); cancelPendingUpdate(); }
    void setParams (std::vector<juce::AudioProcessorParameter*> ps)
    { for (auto* p : params_) if (p) p->removeListener (this); params_ = std::move (ps); for (auto* p : params_) if (p) p->addListener (this); triggerAsyncUpdate(); }

    void paint (juce::Graphics& g) override
    {
        auto r = getLocalBounds().toFloat();
        g.setColour (juce::Colour (0xff0e1014)); g.fillRoundedRectangle (r, 4.0f);
        g.setColour (d50::kDim.withAlpha (0.30f)); g.drawRoundedRectangle (r, 4.0f, 1.0f);
        g.setColour (d50::kDim); g.setFont (toi::uiFont (6.5f, true).withExtraKerningFactor (0.12f));
        g.drawText (title_, r.withHeight (11.0f).reduced (6.0f, 1.0f), juce::Justification::centredLeft);
        auto a = r.withTrimmedTop (11.0f).reduced (8.0f, 3.0f);
        if (kind_ == Pitch) drawPitch (g, a); else drawMulti (g, a);
    }
private:
    float v (int i) const { return (i < (int) params_.size() && params_[(size_t) i] != nullptr) ? params_[(size_t) i]->getValue() : 0.5f; }

    void drawMulti (juce::Graphics& g, juce::Rectangle<float> a)
    {
        const float t1 = v (0), t2 = v (1), lb = v (2), t3 = v (3), ls = v (4), rl = v (5);
        float wa = 0.04f + t1 * 0.22f, wd = 0.04f + t2 * 0.22f, ws = 0.04f + t3 * 0.18f, wh = 0.14f, wr = 0.04f + rl * 0.22f;
        const float sc = 0.96f / (wa + wd + ws + wh + wr);
        wa *= sc; wd *= sc; ws *= sc; wh *= sc; wr *= sc;
        const float baseY = a.getBottom() - 7.0f, topY = a.getY() + 1.0f, x0 = a.getX() + 2.0f, w = a.getWidth() - 4.0f;
        auto X = [&] (float t) { return x0 + w * t; };
        auto Y = [&] (float lvl) { return baseY - (baseY - topY) * lvl; };
        float c = 0.0f;
        juce::Path p; p.startNewSubPath (X (0.0f), Y (0.0f));
        c += wa; p.lineTo (X (c), Y (1.0f));
        c += wd; p.lineTo (X (c), Y (lb));
        c += ws; p.lineTo (X (c), Y (ls));
        const float offX = c + wh; p.lineTo (X (offX), Y (ls));
        p.lineTo (X (offX + wr), Y (0.0f));
        g.setColour (d50::kDim.withAlpha (0.4f)); g.drawLine (x0, baseY, a.getRight() - 2.0f, baseY, 0.6f);
        g.setColour (d50::kScreen.withAlpha (0.92f)); g.strokePath (p, juce::PathStrokeType (1.3f));
        g.setColour (d50::kDim); g.setFont (toi::uiFont (4.8f, true));
        g.drawText ("KEY ON", juce::Rectangle<float> (x0 - 1.0f, a.getBottom() - 6.5f, 32.0f, 6.5f), juce::Justification::centredLeft);
        g.drawText ("OFF",    juce::Rectangle<float> (X (offX) - 1.0f, a.getBottom() - 6.5f, 20.0f, 6.5f), juce::Justification::centredLeft);
    }
    void drawPitch (juce::Graphics& g, juce::Rectangle<float> a)
    {
        const float depth = (v (0) - 0.5f) * 2.0f;
        const float midY = a.getCentreY(), x0 = a.getX() + 22.0f, x1 = a.getRight() - 4.0f, amp = a.getHeight() * 0.5f - 2.0f;
        g.setColour (d50::kDim.withAlpha (0.5f)); g.drawLine (x0, midY, x1, midY, 0.8f);
        g.setColour (d50::kDim); g.setFont (toi::uiFont (4.8f, true));
        g.drawText ("CTR", juce::Rectangle<float> (a.getX() - 1.0f, midY - 4.0f, 22.0f, 8.0f), juce::Justification::centredLeft);
        juce::Path p; p.startNewSubPath (x0, midY);
        p.lineTo (x0 + (x1 - x0) * 0.10f, midY - depth * amp);
        p.lineTo (x0 + (x1 - x0) * 0.45f, midY);
        p.lineTo (x1, midY);
        g.setColour (d50::kScreen.withAlpha (0.92f)); g.strokePath (p, juce::PathStrokeType (1.3f));
        g.setColour (d50::kDim); g.drawText ("KEY ON", juce::Rectangle<float> (x0 - 4.0f, a.getBottom() - 7.0f, 34.0f, 7.0f), juce::Justification::centredLeft);
    }
    void parameterValueChanged (int, float) override { triggerAsyncUpdate(); }
    void parameterGestureChanged (int, bool) override {}
    void handleAsyncUpdate() override { repaint(); }
    juce::String title_; Kind kind_; std::vector<juce::AudioProcessorParameter*> params_;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (D50EnvView)
};

//==============================================================================
inline toi::Config jwd50Config()
{
    toi::Config c;
    c.model = "JW-D50";
    auto& p = c.pal;
    p.bg = d50::kPanel; p.bg2 = d50::kPanelLo; p.frame = d50::kFrame; p.ink = d50::kFrame;
    p.accent = d50::kTeal; p.accent2 = d50::kBlue; p.button = juce::Colour (0xff42464d);
    p.thumb = d50::kText; p.text = d50::kText;
    p.noteStrip = juce::Colour (0xff1d1f23);
    p.lcdBg = juce::Colour (0xff06240f); p.lcdInk = d50::kScreen;   // green D-50 screen
    p.keyWhite = juce::Colour (0xffeef0f2); p.keyWhitePr = juce::Colour (0xffc6d2f4);
    p.keyBlack = juce::Colour (0xff141518); p.keyBlackPr = d50::kTeal;

    c.params = {
        { "structure","STRUCT" }, { "attackType","TYPE" }, { "attackTime","TIME" }, { "attackLevel","LEVEL" },
        { "susWave","WAVE" }, { "susTune","TUNE" }, { "susFine","FINE" }, { "susLevel","LEVEL" },
        { "cutoff","CUTOFF" }, { "reso","RESO" }, { "tvfEnv","ENV" }, { "tvfKbd","KBD" },
        { "fT1","T1" }, { "fT2","T2" }, { "fLb","BRK" }, { "fT3","T3" }, { "fLs","SUS" }, { "fR","REL" },
        { "aT1","T1" }, { "aT2","T2" }, { "aLb","BRK" }, { "aT3","T3" }, { "aLs","SUS" }, { "aR","REL" },
        { "lfoRate","LFO" }, { "lfoDepth","DEPTH" }, { "grain","GRAIN" }, { "chorus","CHORUS" }, { "reverb","REVERB" },
        { "volume","VOL" }, { "tune","TUNE" }, { "pEnv","P.ENV" }, { "dual","DUAL" },
    };

    std::vector<float> base = {
        0.0f,0.43f,0.40f,0.60f,  0.20f,0.50f,0.52f,0.80f,  0.60f,0.20f,0.40f,0.40f,
        0.30f,0.50f,0.60f,0.50f,0.50f,0.40f,  0.18f,0.50f,0.80f,0.50f,0.70f,0.50f,
        0.30f,0.10f,0.30f,0.60f,0.50f,  0.80f,0.50f,  0.50f,0.0f };
    enum { STR,ATKT,ATKTM,ATKL, SUSW,SUST,SUSF,SUSL, CUT,RES,TVFE,TVFK,
           FT1,FT2,FLB,FT3,FLS,FR, AT1,AT2,ALB,AT3,ALS,AR,
           LR,LD,GR,CH,RV, VOL,TUNE, PENV,DUAL };
    auto P = [&] (const char* nm, std::initializer_list<std::pair<int,float>> ov)
    { auto v = base; for (auto& o : ov) v[(size_t) o.first] = o.second; return toi::FactoryPreset { nm, v }; };

    c.factory = {
        P("INIT",          {}),
        P("FANTASIA",      {{ATKT,0.429f},{ATKTM,0.5f},{ATKL,0.7f},{SUSW,0.75f},{SUSF,0.55f},{CUT,0.7f},{TVFE,0.5f},{AT1,0.45f},{AT3,0.6f},{ALS,0.75f},{AR,0.7f},{CH,0.8f},{RV,0.75f},{LD,0.15f},{DUAL,0.5f}}),
        P("DIGITAL DANCE", {{ATKT,0.714f},{ATKTM,0.25f},{ATKL,0.85f},{SUSW,0.4f},{CUT,0.7f},{RES,0.3f},{TVFE,0.6f},{AT1,0.02f},{AT2,0.35f},{ALB,0.4f},{AT3,0.4f},{ALS,0.25f},{AR,0.35f},{GR,0.4f},{CH,0.5f},{RV,0.4f}}),
        P("STACCATO HVN",  {{ATKT,0.0f},{ATKTM,0.3f},{ATKL,0.9f},{SUSW,0.7f},{CUT,0.75f},{AT1,0.02f},{AT2,0.25f},{ALB,0.1f},{AT3,0.2f},{ALS,0.0f},{AR,0.25f},{CH,0.6f},{RV,0.55f}}),
        P("GLASS PAD",     {{ATKT,0.286f},{SUSW,0.8f},{CUT,0.65f},{RES,0.35f},{AT1,0.5f},{ALS,0.8f},{AR,0.7f},{GR,0.2f},{CH,0.85f},{RV,0.8f}}),
        P("CRYSTAL BELL",  {{STR,0.5f},{ATKT,0.0f},{ATKTM,0.45f},{ATKL,0.8f},{SUSW,0.85f},{SUSF,0.6f},{CUT,0.8f},{AT1,0.05f},{AT2,0.5f},{ALB,0.5f},{ALS,0.4f},{AR,0.6f},{CH,0.7f},{RV,0.7f}}),
        P("SOUNDTRACK",    {{ATKT,0.429f},{SUSW,0.3f},{CUT,0.6f},{AT1,0.6f},{ALS,0.8f},{AR,0.8f},{LR,0.2f},{LD,0.25f},{CH,0.9f},{RV,0.85f},{PENV,0.34f},{DUAL,0.45f}}),
        P("NU CHOIR",      {{ATKT,0.429f},{ATKTM,0.6f},{SUSW,0.55f},{CUT,0.55f},{AT1,0.4f},{ALS,0.8f},{AR,0.7f},{CH,0.8f},{RV,0.75f}}),
        P("DIGITAL AIR",   {{ATKT,0.286f},{SUSW,0.7f},{CUT,0.7f},{AT1,0.45f},{ALS,0.7f},{AR,0.65f},{GR,0.5f},{CH,0.7f},{RV,0.7f}}),
        P("SHIMMER",       {{STR,0.5f},{ATKT,1.0f},{SUSW,0.85f},{CUT,0.8f},{AT1,0.3f},{ALS,0.7f},{AR,0.7f},{CH,0.85f},{RV,0.8f}}),
        P("MALLET KEYS",   {{ATKT,0.714f},{ATKTM,0.3f},{ATKL,0.9f},{SUSW,0.45f},{CUT,0.65f},{AT1,0.02f},{AT2,0.4f},{ALB,0.3f},{AT3,0.4f},{ALS,0.2f},{AR,0.4f},{CH,0.5f},{RV,0.45f}}),
        P("GHOST PAD",     {{STR,1.0f},{ATKT,0.286f},{SUSW,0.6f},{CUT,0.5f},{TVFE,0.6f},{AT1,0.55f},{ALS,0.75f},{AR,0.75f},{LR,0.25f},{LD,0.3f},{CH,0.85f},{RV,0.85f}}),
        P("HOLLOW BASS",   {{ATKT,0.571f},{ATKTM,0.2f},{ATKL,0.7f},{SUSW,0.5f},{SUST,0.25f},{CUT,0.5f},{RES,0.3f},{AT1,0.03f},{AT2,0.4f},{ALB,0.6f},{AT3,0.5f},{ALS,0.6f},{AR,0.3f},{CH,0.4f},{RV,0.3f}}),
        P("SPECTRA SWEEP", {{ATKT,1.0f},{SUSW,0.8f},{CUT,0.4f},{RES,0.45f},{TVFE,0.7f},{FT1,0.5f},{FLS,0.3f},{LR,0.3f},{LD,0.5f},{CH,0.7f},{RV,0.7f}}),
        P("BRASS STACK",   {{ATKT,0.143f},{ATKTM,0.25f},{SUSW,0.1f},{CUT,0.55f},{TVFE,0.6f},{AT1,0.1f},{AT2,0.45f},{ALB,0.6f},{ALS,0.7f},{AR,0.4f},{CH,0.5f},{RV,0.4f}}),
        P("DREAM VOX",     {{STR,1.0f},{ATKT,0.429f},{ATKTM,0.6f},{SUSW,0.65f},{CUT,0.6f},{AT1,0.55f},{ALS,0.8f},{AR,0.8f},{LD,0.2f},{CH,0.9f},{RV,0.9f},{DUAL,0.6f}}),
    };
    return c;
}

//==============================================================================
class JWD50Editor  : public toi::PanelEditor
{
public:
    JWD50Editor (juce::AudioProcessor& proc, juce::MidiKeyboardState& kb)
        : toi::PanelEditor (proc, kb, jwd50Config())
    {
        grain_ = makeGrain (130, 130);

        const char* ids[] = {
            "structure","attackType","attackTime","attackLevel", "susWave","susTune","susFine","susLevel",
            "cutoff","reso","tvfEnv","tvfKbd", "fT1","fT2","fLb","fT3","fLs","fR",
            "aT1","aT2","aLb","aT3","aLs","aR", "lfoRate","lfoDepth","grain","chorus","reverb", "volume","tune","pEnv","dual" };
        const char* lbl[] = {
            "STRUCT","TYPE","TIME","LEVEL", "WAVE","TUNE","FINE","LEVEL", "CUTOFF","RESO","ENV","KBD",
            "T1","T2","BRK","T3","SUS","REL", "T1","T2","BRK","T3","SUS","REL", "LFO","DEPTH","GRAIN","CHORUS","REVERB", "VOL","TUNE","P.ENV","DUAL" };
        for (int i = 0; i < (int) (sizeof (ids) / sizeof (ids[0])); ++i) addKnob (ids[i], lbl[i]);

        scope_ = std::make_unique<toi::Lcd> (pal());
        scope_->attachScope (audioTap());
        scope_->setLines ("", "");   // pure real-audio scope - no preset names
        addAndMakeVisible (*scope_);

        // REAL face controls
        structBank_ = std::make_unique<D50Bank> (juce::StringArray { "MIX","RING","XMOD" }, "STRUCTURE");
        waveBank_   = std::make_unique<D50Bank> (juce::StringArray { "BELL","PLUCK","BREATH","CHOIR","PICK","MLLT","BLOW","SPEC" }, "ATTACK WAVE");
        if (auto* prm = findParam ("structure"))  structBank_->attach (*prm);
        if (auto* prm = findParam ("attackType")) waveBank_->attach (*prm);
        addAndMakeVisible (*structBank_); addAndMakeVisible (*waveBank_);

        joy_ = std::make_unique<D50XYPad>();
        joy_->attach (findParam ("cutoff"), findParam ("lfoDepth"));
        addAndMakeVisible (*joy_);

        // LIVE envelope displays (redraw from the real params) - fill the middle band, not static art
        envPitch_ = std::make_unique<D50EnvView> ("PITCH  ENV", D50EnvView::Pitch);
        envPitch_->setParams ({ findParam ("pEnv") });
        envTva_ = std::make_unique<D50EnvView> ("TVA  ENVELOPE", D50EnvView::MultiStage);
        envTva_->setParams ({ findParam ("aT1"), findParam ("aT2"), findParam ("aLb"), findParam ("aT3"), findParam ("aLs"), findParam ("aR") });
        addAndMakeVisible (*envPitch_); addAndMakeVisible (*envTva_);

        for (int i = 0; i < 16; ++i)
        { auto b = std::make_unique<toi::MoldedButton> (juce::Colour (0xff2b2e34)); b->setLit (d50::kRed); const int idx = i; b->onClick = [this, idx] { recallSlot (idx); }; addAndMakeVisible (*b); slots.push_back (std::move (b)); }

        inc_  = std::make_unique<D50Func> ("INC",   d50::kDim);
        dec_  = std::make_unique<D50Func> ("DEC",   d50::kDim);
        rand_ = std::make_unique<D50Func> ("RAND",  d50::kDim);
        save_ = std::make_unique<D50Func> ("WRITE", d50::kTeal);
        inc_->onClick  = [this] { recallSlot (juce::jlimit (0, 15, activeSlot() + 1)); inc_->flash(); };
        dec_->onClick  = [this] { recallSlot (juce::jlimit (0, 15, activeSlot() - 1)); dec_->flash(); };
        rand_->onClick = [this] { doRandom(); rand_->flash(); };
        save_->onClick = [this] { saveSlot (activeSlot()); save_->flash(); };
        addAndMakeVisible (*inc_); addAndMakeVisible (*dec_); addAndMakeVisible (*rand_); addAndMakeVisible (*save_);

        finishSetup();
    }

protected:
    int pageCount() const override { return 2; }   // PLAY (D-50 face) + EDIT (parameters)

    void setPresetActiveVisual (int idx) override
    {
        for (int i = 0; i < (int) slots.size(); ++i) slots[(size_t) i]->setActive (i == idx);
    }

    static juce::Image makeGrain (int w, int h)
    {
        juce::Image img (juce::Image::ARGB, w, h, true);
        juce::Random r (1987);
        for (int y = 0; y < h; ++y) for (int x = 0; x < w; ++x)
        { const float n = r.nextFloat(); if (n > 0.66f) { const float a = (n - 0.66f) / 0.34f * 0.04f; const bool light = r.nextBool();
            img.setPixelAt (x, y, (light ? juce::Colours::white : juce::Colours::black).withAlpha (a)); } }
        return img;
    }

    void paintPanel (juce::Graphics& g, juce::Rectangle<float> panel) override
    {
        rPanel = panel;
        juce::ColourGradient pg (d50::kPanel, rPanel.getCentreX(), rPanel.getY(), d50::kPanelLo, rPanel.getCentreX(), rPanel.getBottom(), false);
        g.setGradientFill (pg); g.fillRoundedRectangle (rPanel, 5.0f);
        if (grain_.isValid()) { g.setFillType (juce::FillType (grain_, juce::AffineTransform::translation (rPanel.getX(), rPanel.getY()))); g.fillRoundedRectangle (rPanel, 5.0f); }
        g.setColour (juce::Colours::black); g.drawRoundedRectangle (rPanel, 5.0f, 1.5f);

        if (page() == 0) drawPlayFace (g); else drawEditPage (g);

        auto bh = rBrand_;
        drawViewLeds (g, bh.removeFromTop (24.0f));
        bh.removeFromTop (7.0f);
        g.setColour (d50::kText); g.setFont (toi::uiFont (15.0f, true));
        g.drawText ("JW-D50", bh.removeFromTop (16.0f), juce::Justification::centred);
        g.setColour (d50::kDim); g.setFont (toi::uiFont (5.5f, true).withExtraKerningFactor (0.2f));
        g.drawText ("TOI - plugin corp", bh.removeFromTop (8.0f), juce::Justification::centred);
    }

    void layoutPanel (juce::Rectangle<float> panel) override
    {
        rPanel = panel;
        auto inner = rPanel.reduced (12.0f, 8.0f);
        rBrand_ = juce::Rectangle<float> (inner.getRight() - 150.0f, inner.getBottom() - 82.0f, 150.0f, 82.0f);

        if (page() == 0) layoutPlay (inner); else layoutEdit (inner);

        if (auto* pb = pageButton())
            placeInArtboard (*pb, juce::Rectangle<float> (inner.getRight() - 78.0f, inner.getY() + 2.0f, 74.0f, 22.0f));

        for (auto& k : knobs) k->setVisible (page() == 1);
        for (auto& s : slots) s->setVisible (page() == 0);
        scope_->setVisible (page() == 0);
        structBank_->setVisible (page() == 0); waveBank_->setVisible (page() == 0); joy_->setVisible (page() == 0);
        envPitch_->setVisible (page() == 0); envTva_->setVisible (page() == 0);
        inc_->setVisible (page() == 0); dec_->setVisible (page() == 0);
        rand_->setVisible (page() == 0); save_->setVisible (page() == 0);
    }

private:
    //========================================================================
    // ---- PLAY page = the D-50 face, every control REAL ----
    juce::Rectangle<float> lcdRect (juce::Rectangle<float> in) const { return { in.getX() + 430.0f, in.getY() + 8.0f, 440.0f, 64.0f }; }
    juce::Rectangle<float> patchRect (juce::Rectangle<float> in, int i) const
    {
        const float x0 = in.getX() + 10.0f, gap = 3.0f;
        const float rowW = (rBrand_.getX() - 8.0f) - x0;          // one row, spanning up to the brand
        const float bw = (rowW - gap * 15.0f) / 16.0f;
        return { x0 + (float) i * (bw + gap), in.getBottom() - 52.0f, bw, 28.0f };
    }

    void layoutPlay (juce::Rectangle<float> in)
    {
        placeInArtboard (*joy_, juce::Rectangle<float> (in.getX() + 4.0f, in.getY() + 6.0f, 116.0f, 104.0f));
        placeInArtboard (*scope_, lcdRect (in));
        // DEC / INC / RAND / WRITE directly under the centred LCD
        auto u = juce::Rectangle<float> (in.getX() + 430.0f, in.getY() + 80.0f, 440.0f, 24.0f);
        const float uw = (u.getWidth() - 21.0f) / 4.0f;
        D50Func* fb[] = { dec_.get(), inc_.get(), rand_.get(), save_.get() };
        for (int i = 0; i < 4; ++i) placeInArtboard (*fb[i], juce::Rectangle<float> (u.getX() + (float) i * (uw + 7.0f), u.getY(), uw, u.getHeight()));
        // STRUCTURE left of the LCD, ATTACK WAVE right of it (the screen stays centred)
        placeInArtboard (*structBank_, juce::Rectangle<float> (in.getX() + 130.0f, in.getY() + 28.0f, 286.0f, 50.0f));
        placeInArtboard (*waveBank_,   juce::Rectangle<float> (in.getX() + 884.0f, in.getY() + 30.0f, 380.0f, 50.0f));
        for (int i = 0; i < 16; ++i) placeInArtboard (*slots[(size_t) i], patchRect (in, i));
        const float dy = in.getY() + 114.0f, dh = 46.0f;
        placeInArtboard (*envPitch_, juce::Rectangle<float> (in.getX() + 452.0f, dy, 334.0f, dh));
        placeInArtboard (*envTva_,   juce::Rectangle<float> (in.getX() + 798.0f, dy, 312.0f, dh));
    }

    void drawPlayFace (juce::Graphics& g)
    {
        auto in = rPanel.reduced (12.0f, 8.0f);
        // LCD bezel (scope sits inside)
        auto lcd = lcdRect (in);
        g.setColour (juce::Colour (0xff0a0c0a)); g.fillRoundedRectangle (lcd.expanded (5.0f), 4.0f);
        g.setColour (juce::Colours::black); g.drawRoundedRectangle (lcd.expanded (5.0f), 4.0f, 1.5f);
        // single PATCHES area: one label + numbers 1-16
        g.setColour (d50::kDim); g.setFont (toi::uiFont (7.0f, true).withExtraKerningFactor (0.12f));
        g.drawText ("PATCHES", juce::Rectangle<float> (in.getX() + 10.0f, in.getBottom() - 66.0f, 320.0f, 10.0f), juce::Justification::centredLeft);
        g.setFont (toi::uiFont (6.5f, true));
        for (int i = 0; i < 16; ++i)
        {
            auto bk = patchRect (in, i);
            g.drawText (juce::String (i + 1), bk.withY (bk.getBottom() + 1.0f).withHeight (9.0f), juce::Justification::centred);
        }

        // SIGNAL PATH = a static flow legend (documents the LA chain); the two envelope boxes to its
        // right are LIVE components (D50EnvView), not static art.
        drawSignalPathDiagram (g, { in.getX(), in.getY() + 114.0f, 440.0f, 46.0f });
    }

    juce::Rectangle<float> diagFrame (juce::Graphics& g, juce::Rectangle<float> r, const juce::String& title)
    {
        g.setColour (juce::Colour (0xff0e1014)); g.fillRoundedRectangle (r, 4.0f);
        g.setColour (d50::kDim.withAlpha (0.30f)); g.drawRoundedRectangle (r, 4.0f, 1.0f);
        g.setColour (d50::kDim); g.setFont (toi::uiFont (6.5f, true).withExtraKerningFactor (0.12f));
        g.drawText (title, r.withHeight (11.0f).reduced (6.0f, 1.0f), juce::Justification::centredLeft);
        return r.withTrimmedTop (11.0f).reduced (8.0f, 3.0f);
    }

    void drawSignalPathDiagram (juce::Graphics& g, juce::Rectangle<float> r)
    {
        auto a = diagFrame (g, r, "SIGNAL  PATH");
        const char* names[] = { "PARTIALS", "STRUCTURE", "TVF", "TVA", "OUT" };
        const int n = 5; const float aw = 11.0f;
        const float bw = (a.getWidth() - aw * (float) (n - 1)) / (float) n;
        const float bh = juce::jmin (16.0f, a.getHeight()), by = a.getCentreY() - bh * 0.5f;
        g.setFont (toi::uiFont (6.0f, true));
        for (int i = 0; i < n; ++i)
        {
            juce::Rectangle<float> b (a.getX() + (float) i * (bw + aw), by, bw, bh);
            g.setColour (juce::Colour (0xff262a31)); g.fillRoundedRectangle (b, 2.0f);
            g.setColour (d50::kTeal.withAlpha (0.55f)); g.drawRoundedRectangle (b, 2.0f, 0.8f);
            g.setColour (d50::kText); g.drawText (names[i], b, juce::Justification::centred);
            if (i < n - 1)
            {
                const float x0 = b.getRight(), x1 = x0 + aw, yy = b.getCentreY();
                g.setColour (d50::kDim); g.drawLine (x0 + 1.0f, yy, x1 - 1.0f, yy, 1.0f);
                juce::Path tp; tp.addTriangle (x1 - 1.0f, yy, x1 - 4.0f, yy - 2.4f, x1 - 4.0f, yy + 2.4f); g.fillPath (tp);
            }
        }
    }


    //========================================================================
    // ---- EDIT page = the rest of the sound parameters ----
    void layoutEdit (juce::Rectangle<float> inner)
    {
        inner.removeFromTop (4.0f);
        const float band1H = 92.0f, gap = 6.0f;
        auto band1 = inner.removeFromTop (band1H); inner.removeFromTop (gap);
        auto band2 = inner.removeFromTop (band1H);

        rStructAtk_ = band1.removeFromLeft (300.0f); band1.removeFromLeft (8.0f);
        rSustain_   = band1.removeFromLeft (300.0f); band1.removeFromLeft (8.0f);
        rTvf_       = band1.removeFromLeft (290.0f); band1.removeFromLeft (8.0f);
        rModFx_     = band1;
        rTvfEnv_ = band2.removeFromLeft (470.0f); band2.removeFromLeft (8.0f);
        rTvaEnv_ = band2.removeFromLeft (470.0f); band2.removeFromLeft (8.0f);
        rMaster_ = band2.removeFromLeft (130.0f);

        rowKnobs (contentOf (rStructAtk_), { "structure","attackType","attackTime","attackLevel","pEnv" });
        rowKnobs (contentOf (rSustain_),   { "susWave","susTune","susFine","susLevel","dual" });
        rowKnobs (contentOf (rTvf_),       { "cutoff","reso","tvfEnv","tvfKbd" });
        rowKnobs (contentOf (rModFx_),     { "lfoRate","lfoDepth","grain","chorus","reverb" });
        rowKnobs (contentOf (rTvfEnv_),    { "fT1","fT2","fLb","fT3","fLs","fR" });
        rowKnobs (contentOf (rTvaEnv_),    { "aT1","aT2","aLb","aT3","aLs","aR" });
        rowKnobs (contentOf (rMaster_),    { "volume","tune" });
    }

    void drawEditPage (juce::Graphics& g)
    {
        sectionHeader (g, rStructAtk_, "ATTACK  PARTIAL  /  STRUCTURE");
        sectionHeader (g, rSustain_,   "SUSTAIN  PARTIAL");
        sectionHeader (g, rTvf_,       "VARIABLE  FILTER  (TVF)");
        sectionHeader (g, rModFx_,     "MODULATION  /  EFFECTS");
        sectionHeader (g, rTvfEnv_,    "TVF  ENVELOPE");
        sectionHeader (g, rTvaEnv_,    "TVA  ENVELOPE");
        sectionHeader (g, rMaster_,    "MASTER");
    }

    void addKnob (const juce::String& id, const juce::String& label)
    {
        auto k = std::make_unique<toi::StyledKnob> (label, pal(), toi::StyledKnob::Ticks);
        if (auto* prm = findParam (id)) k->attach (*prm);
        addAndMakeVisible (*k); knobMap_[id] = k.get(); knobs.push_back (std::move (k));
    }
    toi::StyledKnob* knobFor (const juce::String& id) const { auto it = knobMap_.find (id); return it == knobMap_.end() ? nullptr : it->second; }

    void rowKnobs (juce::Rectangle<float> area, std::initializer_list<const char*> ids)
    {
        const int n = (int) ids.size(); if (n == 0) return;
        const float w = area.getWidth() / (float) n; int i = 0;
        for (auto* id : ids) { if (auto* k = knobFor (id)) placeInArtboard (*k, juce::Rectangle<float> (area.getX() + (float) i * w, area.getY(), w, area.getHeight()).reduced (1.5f, 0.0f)); ++i; }
    }

    static juce::Rectangle<float> contentOf (juce::Rectangle<float> r) { auto inner = r; inner.removeFromTop (13.0f); return inner.reduced (3.0f, 1.0f); }

    void sectionHeader (juce::Graphics& g, juce::Rectangle<float> r, const juce::String& name)
    {
        auto hdr = r.withHeight (12.0f);
        g.setColour (d50::kDim); g.setFont (toi::uiFont (7.5f, true).withExtraKerningFactor (0.14f));
        g.drawText (name, hdr.reduced (4.0f, 0.0f), juce::Justification::centredLeft);
        g.setColour (d50::kTeal.withAlpha (0.7f));
        g.fillRect (juce::Rectangle<float> (r.getX() + 3.0f, hdr.getBottom() - 0.5f, r.getWidth() - 6.0f, 1.2f));
    }

    std::vector<std::unique_ptr<toi::StyledKnob>> knobs;
    std::map<juce::String, toi::StyledKnob*> knobMap_;
    std::unique_ptr<toi::Lcd> scope_;
    std::unique_ptr<D50Bank> structBank_, waveBank_;
    std::unique_ptr<D50XYPad> joy_;
    std::unique_ptr<D50EnvView> envPitch_, envTva_;
    std::vector<std::unique_ptr<toi::MoldedButton>> slots;
    std::unique_ptr<D50Func> inc_, dec_, rand_, save_;
    juce::Image grain_;
    juce::Rectangle<float> rPanel, rBrand_, rStructAtk_, rSustain_, rTvf_, rModFx_, rTvfEnv_, rTvaEnv_, rMaster_;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JWD50Editor)
};

//==============================================================================
class JWD50Plugin  : public cmaj::plugin::GeneratedPlugin<::JWD50>,
                     public toi::AudioTapSource,
                     public toi::PresetStore
{
public:
    using Base = cmaj::plugin::GeneratedPlugin<::JWD50>;
    JWD50Plugin (std::shared_ptr<cmaj::Patch> p) : Base (std::move (p)) {}
    juce::AudioProcessorEditor* createEditor() override { return new JWD50Editor (*this, keyboardState); }
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
