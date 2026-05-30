// JW-2600 native faceplate (semi-modular MONO synthesizer) on the toi_faceplate.h kit.
// Its OWN distinct look: a near-BLACK metal panel with vivid-orange engraving, a WALL of
// vintage slider modules (VCO1/2/3, MOD, SOURCE, FILTER, ADSR, AR, S&H, OUTPUT), and a
// REAL FUNCTIONAL PATCHBAY - drag cables between labelled source/dest jacks and they route
// modulation in the DSP (a true 4-cord mod matrix). Real-audio scope. NO brand names.
#pragma once

#include "toi_faceplate.h"

struct JW2600;

namespace arp
{
    static const juce::Colour kPanel  { 0xff202227 };   // near-black charcoal metal
    static const juce::Colour kPanelLo{ 0xff141619 };
    static const juce::Colour kBg      { 0xff0c0d0f };
    static const juce::Colour kFrame  { 0xff050607 };
    static const juce::Colour kSlot   { 0xff0b0d10 };   // recessed slider slot
    static const juce::Colour kCream  { 0xffe9e2cf };   // labels + most slider caps
    static const juce::Colour kDim    { 0xff8b929b };
    static const juce::Colour kOrange { 0xffec6b2d };   // vivid 2600 orange (Jade's swatch)
    static const juce::Colour kAmber  { 0xffd9983e };
    static const juce::Colour kRed    { 0xffcf4a2c };
    static const juce::Colour kJack   { 0xff070a0d };   // jack socket holes
    // 4 patch-cord colours (one per mod-cord) - they pop on the black panel
    static const juce::Colour kCord[4] = { juce::Colour (0xffec6b2d), juce::Colour (0xff34c2d6),
                                           juce::Colour (0xff63c057), juce::Colour (0xffd05bb0) };
}

//==============================================================================
// ArpFader - vintage slider: recessed dark slot + a graduated tick scale + a flat
// colour cap with a crisp white index line + label below. Binds a param 0..1.
class ArpFader  : public juce::Component
{
public:
    ArpFader (const juce::String& labelText, juce::Colour cap, const toi::Palette& palette)
        : label (labelText), capCol (cap), pal (palette)
    {
        slider.setSliderStyle (juce::Slider::LinearVertical);
        slider.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
        slider.setLookAndFeel (&laf);
        slider.setRange (0.0, 1.0, 0.0);
        slider.setDoubleClickReturnValue (true, 0.5);
        addAndMakeVisible (slider);
    }
    ~ArpFader() override { slider.setLookAndFeel (nullptr); }
    void attach (juce::AudioProcessorParameter& p)
    { att = std::make_unique<toi::ParamKnobAttachment> (p, slider); slider.setDoubleClickReturnValue (true, p.getDefaultValue()); slider.onValueChange = [this] { repaint(); }; repaint(); }
    void resized() override { slider.setBounds (getLocalBounds().withTrimmedBottom ((int) labelH)); }
    void paint (juce::Graphics& g) override
    {
        auto b = getLocalBounds().toFloat();
        auto la = b.removeFromBottom (labelH);
        g.setColour (pal.text); g.setFont (toi::uiFont (7.5f, true)); g.drawText (label, la, juce::Justification::centred);
        auto ta = b.reduced (0.0f, 2.0f);
        const float cx = ta.getCentreX(), top = ta.getY(), h = ta.getHeight();
        const float capW = 24.0f, capH = 13.0f, pad = capH * 0.5f + 1.0f;
        // graduated tick scale (engraved) on both sides of the slot
        const int nT = juce::jmax (6, (int) std::round (h / 12.0f));
        for (int i = 0; i < nT; ++i)
        {
            const float ry = top + (h - 1.0f) * (float) i / (float) (nT - 1);
            const float len = (i % 2 == 0) ? 9.0f : 5.0f;
            g.setColour (arp::kCream.withAlpha (0.30f));
            g.drawLine (cx - capW * 0.5f - len, ry, cx - capW * 0.5f - 2.0f, ry, 1.0f);
            g.drawLine (cx + capW * 0.5f + 2.0f, ry, cx + capW * 0.5f + len, ry, 1.0f);
        }
        // recessed slot
        juce::Rectangle<float> slot (cx - 2.6f, top, 5.2f, h);
        g.setColour (arp::kSlot); g.fillRoundedRectangle (slot, 2.0f);
        g.setColour (juce::Colours::black.withAlpha (0.7f)); g.drawRoundedRectangle (slot, 2.0f, 1.0f);
        g.setColour (juce::Colours::white.withAlpha (0.05f)); g.drawVerticalLine ((int) (cx + 2.0f), top, top + h);
        // flat colour cap with bevel + white index line
        const float v = juce::jlimit (0.0f, 1.0f, (float) slider.getValue());
        const float ty = top + pad + (1.0f - v) * (h - 2.0f * pad);
        juce::Rectangle<float> cap (cx - capW * 0.5f, ty - capH * 0.5f, capW, capH);
        g.setColour (juce::Colours::black.withAlpha (0.55f)); g.fillRoundedRectangle (cap.translated (0.0f, 1.6f), 2.0f);
        juce::ColourGradient cg (capCol.brighter (0.25f), cx, cap.getY(), capCol.darker (0.30f), cx, cap.getBottom(), false);
        g.setGradientFill (cg); g.fillRoundedRectangle (cap, 2.0f);
        g.setColour (juce::Colours::white.withAlpha (0.32f)); g.drawLine (cap.getX() + 2.0f, cap.getY() + 1.2f, cap.getRight() - 2.0f, cap.getY() + 1.2f, 1.0f);
        g.setColour (juce::Colours::black.withAlpha (0.7f)); g.drawRoundedRectangle (cap, 2.0f, 1.0f);
        g.setColour (juce::Colours::white.withAlpha (0.9f)); g.drawLine (cap.getX() + 3.0f, cap.getCentreY(), cap.getRight() - 3.0f, cap.getCentreY(), 1.6f);
    }
    juce::Slider slider;
private:
    static constexpr float labelH = 12.0f;
    toi::InvisibleLinearLAF laf; juce::String label; juce::Colour capCol; toi::Palette pal;
    std::unique_ptr<toi::ParamKnobAttachment> att;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ArpFader)
};

//==============================================================================
// ArpSwitch - a multi-state rocker bound directly to a param (sync 2-state, VCO3 mode
// 2-state, filter mode 4-state). Click cycles; shows the active option + an LED + a title.
class ArpSwitch  : public juce::Button,
                   private juce::AudioProcessorParameter::Listener,
                   private juce::AsyncUpdater
{
public:
    ArpSwitch (juce::StringArray opts, juce::String titleText, const toi::Palette& palette, juce::Colour ledColour)
        : juce::Button ("sw"), options (std::move (opts)), title (std::move (titleText)), pal (palette), led (ledColour)
    { onClick = [this] { advance(); }; }
    ~ArpSwitch() override { if (param != nullptr) param->removeListener (this); cancelPendingUpdate(); }

    void attach (juce::AudioProcessorParameter& p) { param = &p; param->addListener (this); triggerAsyncUpdate(); }
    int  count() const { return juce::jmax (2, options.size()); }
    int  state() const { return param != nullptr ? juce::jlimit (0, count() - 1, juce::roundToInt (param->getValue() * (float) (count() - 1))) : 0; }
    void advance()
    {
        if (param == nullptr) return;
        const int n = (state() + 1) % count();
        param->beginChangeGesture(); param->setValueNotifyingHost ((float) n / (float) (count() - 1)); param->endChangeGesture();
    }
    void paintButton (juce::Graphics& g, bool over, bool down) override
    {
        auto b = getLocalBounds().toFloat();
        auto la = b.removeFromBottom (10.0f);
        auto body = b.reduced (1.0f);
        const int st = state();
        const bool lit = (count() == 2) ? (st == 1) : true;
        auto base = down ? pal.button.darker (0.15f) : over ? pal.button.brighter (0.07f) : pal.button;
        g.setColour (base); g.fillRoundedRectangle (body, 3.0f);
        g.setColour (juce::Colours::black.withAlpha (0.6f)); g.drawRoundedRectangle (body, 3.0f, 1.3f);
        const float lr = 3.2f, lx = body.getX() + 7.0f, ly = body.getY() + 7.0f;
        if (lit) { g.setColour (led.withAlpha (0.5f)); g.fillEllipse (lx - lr - 2.0f, ly - lr - 2.0f, (lr + 2.0f) * 2.0f, (lr + 2.0f) * 2.0f); }
        g.setColour (lit ? led : led.withAlpha (0.3f)); g.fillEllipse (lx - lr, ly - lr, lr * 2.0f, lr * 2.0f);
        g.setColour (juce::Colours::black); g.drawEllipse (lx - lr, ly - lr, lr * 2.0f, lr * 2.0f, 0.8f);
        g.setColour (lit ? arp::kCream : arp::kDim);
        g.setFont (toi::uiFont (juce::jmin (9.0f, body.getHeight() * 0.42f), true));
        g.drawText (options[st], body.withTrimmedLeft (4.0f), juce::Justification::centred);
        g.setColour (pal.text.withAlpha (0.85f)); g.setFont (toi::uiFont (7.0f, true));
        g.drawText (title, la, juce::Justification::centred);
    }
private:
    void parameterValueChanged (int, float) override { triggerAsyncUpdate(); }
    void parameterGestureChanged (int, bool) override {}
    void handleAsyncUpdate() override { repaint(); }
    juce::StringArray options; juce::String title; toi::Palette pal; juce::Colour led;
    juce::AudioProcessorParameter* param = nullptr;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ArpSwitch)
};

//==============================================================================
class ArpFuncButton  : public juce::Button
{
public:
    ArpFuncButton (const juce::String& text, juce::Colour fill) : juce::Button (text), col (fill) { setButtonText (text); }
    void flash() { flashing = true; repaint(); juce::Timer::callAfterDelay (160, [s = juce::Component::SafePointer<ArpFuncButton> (this)] { if (s) { s->flashing = false; s->repaint(); } }); }
    void paintButton (juce::Graphics& g, bool over, bool down) override
    {
        auto b = getLocalBounds().toFloat().reduced (1.0f);
        auto fill = flashing ? col.brighter (0.3f) : down ? col.darker (0.18f) : over ? col.brighter (0.08f) : col;
        g.setColour (fill); g.fillRoundedRectangle (b, 2.5f);
        g.setColour (juce::Colours::black.withAlpha (0.5f)); g.drawRoundedRectangle (b, 2.5f, 1.0f);
        g.setColour (juce::Colour (0xff201810)); g.setFont (toi::uiFont (juce::jmin (10.0f, b.getHeight() * 0.5f), true));
        g.drawText (getButtonText(), getLocalBounds(), juce::Justification::centred);
    }
private:
    juce::Colour col; bool flashing = false;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ArpFuncButton)
};

//==============================================================================
// Patchbay - a REAL, functional semi-modular patch panel. Six labelled SOURCE jacks and
// six labelled DEST jacks; click a source then a dest to drop a cable (it sets the DSP's
// mod-matrix params so it actually routes); click a cable (or a dest with nothing armed)
// to unplug. Four cords, four colours. The depth of each cord is the matching amount knob.
class Patchbay  : public juce::Component,
                  private juce::AudioProcessorParameter::Listener,
                  private juce::AsyncUpdater
{
public:
    static constexpr int kN = 6;          // sources / dests
    static constexpr int kCords = 4;

    Patchbay (const toi::Palette& palette) : pal (palette) {}
    ~Patchbay() override
    {
        for (int i = 0; i < kCords; ++i) { if (src[i]) src[i]->removeListener (this); if (dst[i]) dst[i]->removeListener (this); if (amt[i]) amt[i]->removeListener (this); }
        cancelPendingUpdate();
    }

    void setLabels (juce::StringArray s, juce::StringArray d) { srcLbl = std::move (s); dstLbl = std::move (d); }
    void setCord (int i, juce::AudioProcessorParameter* s, juce::AudioProcessorParameter* d, juce::AudioProcessorParameter* a)
    {
        src[i] = s; dst[i] = d; amt[i] = a;
        if (s) s->addListener (this); if (d) d->addListener (this); if (a) a->addListener (this);
    }

    void resized() override { computeJacks(); }
    void paint (juce::Graphics& g) override
    {
        auto b = getLocalBounds().toFloat();
        g.setColour (juce::Colours::black.withAlpha (0.55f)); g.fillRoundedRectangle (b, 4.0f);
        g.setColour (juce::Colours::white.withAlpha (0.05f)); g.drawRoundedRectangle (b.reduced (1.0f), 3.0f, 1.0f);

        // jack labels
        g.setFont (toi::uiFont (6.5f, true));
        for (int i = 0; i < kN; ++i)
        {
            g.setColour (arp::kDim);
            g.drawText (i < srcLbl.size() ? srcLbl[i] : "", juce::Rectangle<float> (srcX[i] - 28.0f, b.getY() + 1.0f, 56.0f, 9.0f), juce::Justification::centred);
            g.drawText (i < dstLbl.size() ? dstLbl[i] : "", juce::Rectangle<float> (dstX[i] - 28.0f, b.getBottom() - 9.0f, 56.0f, 9.0f), juce::Justification::centred);
        }
        // jacks (lit in a cord colour if used)
        for (int i = 0; i < kN; ++i)
        {
            drawJack (g, srcX[i], srcY, jackColourForSource (i + 1), armed == i);
            drawJack (g, dstX[i], dstY, jackColourForDest (i + 1), false);
        }
        // cables
        for (int c = 0; c < kCords; ++c)
        {
            const int s = srcIdx (c), d = dstIdx (c);
            if (s >= 1 && s <= kN && d >= 1 && d <= kN)
            {
                auto a = juce::Point<float> (srcX[s - 1], srcY + jackR + 1.0f);
                auto e = juce::Point<float> (dstX[d - 1], dstY - jackR - 1.0f);
                juce::Path p; p.startNewSubPath (a);
                const float sag = 14.0f + (e.y - a.y) * 0.18f;
                p.cubicTo (a.x, a.y + sag, e.x, e.y - sag, e.x, e.y);
                g.setColour (juce::Colours::black.withAlpha (0.5f)); g.strokePath (p, juce::PathStrokeType (4.2f), juce::AffineTransform::translation (0.0f, 1.4f));
                g.setColour (arp::kCord[c]); g.strokePath (p, juce::PathStrokeType (2.8f));
                g.setColour (arp::kCord[c].brighter (0.45f)); g.fillEllipse (a.x - 2.6f, a.y - 2.6f, 5.2f, 5.2f); g.fillEllipse (e.x - 2.6f, e.y - 2.6f, 5.2f, 5.2f);
            }
        }
    }

    void mouseDown (const juce::MouseEvent& ev) override
    {
        const auto pos = ev.position;
        // 1) source jack -> arm / unarm
        for (int i = 0; i < kN; ++i)
            if (pos.getDistanceFrom ({ srcX[i], srcY }) < jackR + 4.0f) { armed = (armed == i ? -1 : i); repaint(); return; }
        // 2) dest jack -> connect (if a source is armed) or remove cords ending here
        for (int i = 0; i < kN; ++i)
            if (pos.getDistanceFrom ({ dstX[i], dstY }) < jackR + 4.0f)
            {
                if (armed >= 0) { createCord (armed + 1, i + 1); armed = -1; }
                else            { for (int c = 0; c < kCords; ++c) if (dstIdx (c) == i + 1) clearCord (c); }
                repaint(); return;
            }
        // 3) click on a cable -> unplug that cord
        for (int c = 0; c < kCords; ++c)
        {
            const int s = srcIdx (c), d = dstIdx (c);
            if (s >= 1 && s <= kN && d >= 1 && d <= kN)
                if (distToSeg (pos, { srcX[s - 1], srcY }, { dstX[d - 1], dstY }) < 6.0f) { clearCord (c); armed = -1; repaint(); return; }
        }
        armed = -1; repaint();
    }

private:
    void parameterValueChanged (int, float) override { triggerAsyncUpdate(); }
    void parameterGestureChanged (int, bool) override {}
    void handleAsyncUpdate() override { repaint(); }

    int  srcIdx (int c) const { return src[c] ? juce::roundToInt (src[c]->getValue() * (float) kN) : 0; }
    int  dstIdx (int c) const { return dst[c] ? juce::roundToInt (dst[c]->getValue() * (float) kN) : 0; }
    void setIdx (juce::AudioProcessorParameter* p, int idx) { if (p) { p->beginChangeGesture(); p->setValueNotifyingHost ((float) idx / (float) kN); p->endChangeGesture(); } }
    void setAmt (juce::AudioProcessorParameter* p, float v) { if (p) { p->beginChangeGesture(); p->setValueNotifyingHost (v); p->endChangeGesture(); } }

    void createCord (int s, int d)
    {
        int slot = -1;
        for (int c = 0; c < kCords; ++c) if (srcIdx (c) == 0 || dstIdx (c) == 0) { slot = c; break; }   // first empty
        if (slot < 0) { slot = last; last = (last + 1) % kCords; }                                       // else recycle
        setIdx (src[slot], s); setIdx (dst[slot], d);
        if (amt[slot] && amt[slot]->getValue() < 0.02f) setAmt (amt[slot], 0.5f);                         // give a new cord a useful default depth
        last = slot;
    }
    void clearCord (int c) { setIdx (src[c], 0); setIdx (dst[c], 0); setAmt (amt[c], 0.0f); }

    juce::Colour jackColourForSource (int idx) const { for (int c = 0; c < kCords; ++c) if (srcIdx (c) == idx && dstIdx (c) >= 1) return arp::kCord[c]; return {}; }
    juce::Colour jackColourForDest   (int idx) const { for (int c = 0; c < kCords; ++c) if (dstIdx (c) == idx && srcIdx (c) >= 1) return arp::kCord[c]; return {}; }

    void drawJack (juce::Graphics& g, float x, float y, juce::Colour lit, bool armd)
    {
        if (armd) { g.setColour (arp::kCream.withAlpha (0.55f)); g.fillEllipse (x - jackR - 4.0f, y - jackR - 4.0f, (jackR + 4.0f) * 2.0f, (jackR + 4.0f) * 2.0f); }
        else if (! lit.isTransparent()) { g.setColour (lit.withAlpha (0.45f)); g.fillEllipse (x - jackR - 3.0f, y - jackR - 3.0f, (jackR + 3.0f) * 2.0f, (jackR + 3.0f) * 2.0f); }
        g.setColour (arp::kPanelLo.brighter (0.18f)); g.fillEllipse (x - jackR, y - jackR, jackR * 2.0f, jackR * 2.0f);              // metal collar
        g.setColour (juce::Colours::black.withAlpha (0.6f)); g.drawEllipse (x - jackR, y - jackR, jackR * 2.0f, jackR * 2.0f, 1.0f);
        g.setColour (arp::kJack); g.fillEllipse (x - jackR * 0.55f, y - jackR * 0.55f, jackR * 1.1f, jackR * 1.1f);                  // hole
        g.setColour ((lit.isTransparent() ? juce::Colours::white : lit).withAlpha (0.18f)); g.drawEllipse (x - jackR * 0.55f, y - jackR * 0.55f, jackR * 1.1f, jackR * 1.1f, 0.8f);
    }

    void computeJacks()
    {
        auto b = getLocalBounds().toFloat();
        srcY = b.getY() + 10.0f + jackR + 2.0f;
        dstY = b.getBottom() - 10.0f - jackR - 2.0f;
        for (int i = 0; i < kN; ++i) { const float x = b.getX() + ((float) i + 0.5f) * b.getWidth() / (float) kN; srcX[i] = x; dstX[i] = x; }
    }
    static float distToSeg (juce::Point<float> p, juce::Point<float> a, juce::Point<float> b)
    {
        const float abx = b.x - a.x, aby = b.y - a.y;
        float t = ((p.x - a.x) * abx + (p.y - a.y) * aby) / (abx * abx + aby * aby + 1.0e-6f);
        t = juce::jlimit (0.0f, 1.0f, t);
        return p.getDistanceFrom ({ a.x + abx * t, a.y + aby * t });
    }

    toi::Palette pal;
    juce::StringArray srcLbl, dstLbl;
    juce::AudioProcessorParameter* src[kCords] = {}; juce::AudioProcessorParameter* dst[kCords] = {}; juce::AudioProcessorParameter* amt[kCords] = {};
    float srcX[kN] = {}, dstX[kN] = {}, srcY = 0.0f, dstY = 0.0f; const float jackR = 6.0f;
    int armed = -1, last = 0;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Patchbay)
};

//==============================================================================
inline toi::Config jw2600Config()
{
    toi::Config c;
    c.model = "JW-2600";
    auto& p = c.pal;
    p.bg = arp::kBg; p.bg2 = juce::Colour (0x00000000); p.frame = arp::kFrame; p.ink = arp::kFrame;
    p.accent = arp::kOrange; p.accent2 = arp::kAmber; p.button = juce::Colour (0xff2a2d33);
    p.thumb = arp::kCream; p.text = arp::kCream;
    p.noteStrip = juce::Colour (0xff202227);
    p.lcdBg = juce::Colour (0xff0e1009); p.lcdInk = juce::Colour (0xffec9a3a);   // amber scope
    p.keyWhite = juce::Colour (0xffe9e2cf); p.keyWhitePr = juce::Colour (0xfff0c089);
    p.keyBlack = juce::Colour (0xff131210); p.keyBlackPr = arp::kOrange;

    // order MUST match the DSP Params struct / ParamsProcessor
    c.params = {
        { "vco1Tune","TUNE" }, { "vco1Wave","WAVE" }, { "vco1PW","PW" }, { "vco1Lvl","LEVEL" },
        { "vco2Tune","TUNE" }, { "vco2Wave","WAVE" }, { "vco2PW","PW" }, { "vco2Lvl","LEVEL" }, { "vco2Sync","SYNC" },
        { "vco3Mode","MODE" }, { "vco3Rate","RATE" }, { "vco3Wave","WAVE" }, { "vco3Lvl","LEVEL" },
        { "modDepth","FM" }, { "pwmDepth","PWM" },
        { "ringLvl","RING" }, { "noiseLvl","NOISE" }, { "noiseColor","COLOR" },
        { "cutoff","CUTOFF" }, { "reso","RESO" }, { "fMode","MODE" }, { "fEnv","ENV" }, { "fKeyTrack","KBD" },
        { "aA","A" }, { "aD","D" }, { "aS","S" }, { "aR","R" },
        { "arA","ATK" }, { "arR","REL" },
        { "shAmt","AMT" }, { "shRate","RATE" }, { "followAmt","FOLLOW" }, { "glide","GLIDE" },
        { "reverb","SPRING" }, { "volume","VOL" }, { "tune","TUNE" },
        { "p1Src","P1S" }, { "p1Dst","P1D" }, { "p1Amt","P1A" },
        { "p2Src","P2S" }, { "p2Dst","P2D" }, { "p2Amt","P2A" },
        { "p3Src","P3S" }, { "p3Dst","P3D" }, { "p3Amt","P3A" },
        { "p4Src","P4S" }, { "p4Dst","P4D" }, { "p4Amt","P4A" },
    };

    // 16 distinct semi-modular patches. base = defaults; override by index.
    std::vector<float> base = {
        0.50f,0.0f,0.50f,0.80f, 0.50f,0.0f,0.50f,0.45f,0.0f, 0.0f,0.30f,0.0f,0.0f, 0.0f,0.0f,
        0.0f,0.0f,0.0f, 0.60f,0.20f,0.0f,0.40f,0.30f, 0.05f,0.40f,0.70f,0.30f, 0.10f,0.40f,
        0.0f,0.30f,0.0f,0.0f, 0.20f,0.80f,0.50f,
        0.0f,0.0f,0.0f, 0.0f,0.0f,0.0f, 0.0f,0.0f,0.0f, 0.0f,0.0f,0.0f };
    enum { V1T,V1W,V1PW,V1L, V2T,V2W,V2PW,V2L,V2SY, V3M,V3R,V3W,V3L, FM,PWM,
           RING,NOISE,NCOL, CUT,RES,FMODE,FENV,KBD, AA,AD,AS,AR, ARA,ARR,
           SH,SHR,FOL,GL, REV,VOL,TUNE,
           P1S,P1D,P1A, P2S,P2D,P2A, P3S,P3D,P3A, P4S,P4D,P4A };
    // patch source/dest index helpers (value = index/6): src 1=LFO 2=S&H 3=ENV 4=AR 5=FOLLOW 6=NOISE; dst 1=PITCH 2=VCO2 3=PW 4=CUTOFF 5=RES 6=AMP
    auto J = [] (int idx) { return (float) idx / 6.0f; };
    auto P = [&] (const char* nm, std::initializer_list<std::pair<int,float>> ov)
    { auto v = base; for (auto& o : ov) v[(size_t) o.first] = o.second; return toi::FactoryPreset { nm, v }; };

    c.factory = {
        P("INIT LEAD",   {}),
        P("BRASS",       {{V1W,0.85f},{V2L,0.6f},{V2T,0.52f},{CUT,0.45f},{FENV,0.65f},{ARA,0.2f},{AD,0.5f},{AS,0.6f}}),
        P("FAT SAW",     {{V2L,0.7f},{V2T,0.515f},{V1T,0.485f},{CUT,0.7f},{RES,0.25f},{AS,0.8f}}),
        P("SYNC LEAD",   {{V2SY,1.0f},{V2T,0.62f},{V2L,0.8f},{V1W,0.95f},{CUT,0.55f},{FENV,0.7f},{ARA,0.05f},{ARR,0.5f}}),
        P("RING BELL",   {{RING,0.8f},{V2T,0.66f},{V1L,0.4f},{V2L,0.0f},{CUT,0.8f},{AD,0.6f},{AS,0.0f},{AR,0.5f}}),
        P("S&H RANDOM",  {{SHR,0.45f},{CUT,0.3f},{RES,0.5f},{AS,0.9f}, {P1S,J(2)},{P1D,J(4)},{P1A,0.6f}}),       // cord: S&H -> CUTOFF
        P("PWM STRINGS", {{V1W,1.0f},{V2W,1.0f},{PWM,0.7f},{V3R,0.12f},{V2L,0.6f},{V2T,0.515f},{CUT,0.6f},{AA,0.4f},{AR,0.6f},{REV,0.4f}}),
        P("SUB BASS",    {{V2T,0.375f},{V2L,0.8f},{CUT,0.35f},{RES,0.3f},{FENV,0.5f},{AD,0.35f},{AS,0.4f},{AR,0.15f}}),
        P("RESO ZAP",    {{RES,0.9f},{CUT,0.25f},{FENV,0.85f},{ARA,0.02f},{ARR,0.25f},{AD,0.2f},{AS,0.0f}}),
        P("NOISE SWEEP", {{NOISE,0.7f},{NCOL,0.4f},{V1L,0.4f},{CUT,0.2f},{RES,0.4f},{FENV,0.8f},{ARA,0.6f},{AA,0.5f},{AR,0.7f}}),
        P("FM GROWL",    {{V3M,1.0f},{V3R,0.7f},{FM,0.45f},{CUT,0.5f},{RES,0.35f},{AS,0.7f}}),
        P("SPACE DRONE", {{V3R,0.08f},{CUT,0.4f},{RES,0.45f},{AA,0.6f},{AR,0.85f},{AS,0.9f},{REV,0.6f}, {P1S,J(1)},{P1D,J(4)},{P1A,0.4f}}),  // cord: LFO -> CUTOFF
        P("WIND",        {{NOISE,0.85f},{NCOL,0.6f},{V1L,0.0f},{FMODE,0.67f},{CUT,0.45f},{RES,0.55f},{AA,0.5f},{AR,0.7f},{REV,0.5f}, {P1S,J(5)},{P1D,J(4)},{P1A,0.6f}}),  // cord: FOLLOW -> CUTOFF
        P("PERC PLUCK",  {{CUT,0.6f},{RES,0.4f},{FENV,0.6f},{ARA,0.02f},{ARR,0.15f},{AA,0.0f},{AD,0.2f},{AS,0.0f},{AR,0.18f}}),
        P("SPRING DUB",  {{CUT,0.45f},{RES,0.3f},{REV,0.85f},{AD,0.3f},{AS,0.2f},{AR,0.3f}}),
        P("LFO WOBBLE",  {{V3R,0.22f},{CUT,0.4f},{RES,0.5f},{AS,0.9f},{ARR,0.4f}, {P1S,J(1)},{P1D,J(1)},{P1A,0.25f}}),  // cord: LFO -> PITCH (vibrato)
    };
    return c;
}

//==============================================================================
class JW2600Editor  : public toi::PanelEditor
{
public:
    JW2600Editor (juce::AudioProcessor& proc, juce::MidiKeyboardState& kb)
        : toi::PanelEditor (proc, kb, jw2600Config())
    {
        grain_ = makeGrain (110, 110);

        // ---- module / column layout (faders interleaved with switches) ----
        // every slider cap is the WAVE colour (vivid orange), per Jade. AM = the VCO3 switch LED only.
        const auto OR = arp::kOrange, AM = arp::kAmber;

        sync_  = std::make_unique<ArpSwitch> (juce::StringArray { "OFF", "ON" },             "SYNC", pal(), OR);
        v3mode_= std::make_unique<ArpSwitch> (juce::StringArray { "LFO", "OSC" },            "MODE", pal(), AM);
        fmode_ = std::make_unique<ArpSwitch> (juce::StringArray { "LP24","HP","BP","NOTCH" },"MODE", pal(), OR);
        if (auto* prm = findParam ("vco2Sync")) sync_->attach (*prm);
        if (auto* prm = findParam ("vco3Mode")) v3mode_->attach (*prm);
        if (auto* prm = findParam ("fMode"))    fmode_->attach (*prm);
        addAndMakeVisible (*sync_); addAndMakeVisible (*v3mode_); addAndMakeVisible (*fmode_);
        auto SW = [&] (ArpSwitch* s) { columns.push_back (s); };

        auto beginMod = [&] (const char* name) { ModRange mr; mr.name = name; mr.startCol = (int) columns.size(); mods.push_back (mr); };
        auto endMod = [&] { mods.back().endCol = (int) columns.size() - 1; };

        beginMod ("VCO 1"); addFader ("vco1Tune","TUNE",OR); addFader ("vco1Wave","WAVE",OR); addFader ("vco1PW","PW",OR); addFader ("vco1Lvl","LEVEL",OR); endMod();
        beginMod ("VCO 2"); addFader ("vco2Tune","TUNE",OR); addFader ("vco2Wave","WAVE",OR); addFader ("vco2PW","PW",OR); addFader ("vco2Lvl","LEVEL",OR); SW (sync_.get()); endMod();
        beginMod ("VCO 3"); addFader ("vco3Rate","RATE",OR); addFader ("vco3Wave","WAVE",OR); addFader ("vco3Lvl","LEVEL",OR); SW (v3mode_.get()); endMod();
        beginMod ("MOD");   addFader ("modDepth","FM",OR); addFader ("pwmDepth","PWM",OR); endMod();
        beginMod ("SOURCE");addFader ("ringLvl","RING",OR); addFader ("noiseLvl","NOISE",OR); addFader ("noiseColor","COLOR",OR); endMod();
        beginMod ("FILTER");addFader ("cutoff","CUTOFF",OR); addFader ("reso","RESO",OR); addFader ("fEnv","ENV",OR); addFader ("fKeyTrack","KBD",OR); SW (fmode_.get()); endMod();
        beginMod ("ADSR");  addFader ("aA","A",OR); addFader ("aD","D",OR); addFader ("aS","S",OR); addFader ("aR","R",OR); endMod();
        beginMod ("AR");    addFader ("arA","ATK",OR); addFader ("arR","REL",OR); endMod();
        beginMod ("S&H");   addFader ("shAmt","AMT",OR); addFader ("shRate","RATE",OR); addFader ("followAmt","FOLLOW",OR); endMod();
        beginMod ("OUTPUT");addFader ("glide","GLIDE",OR); addFader ("reverb","SPRING",OR); addFader ("volume","VOL",OR); addFader ("tune","TUNE",OR); endMod();

        // scope (real audio)
        scope_ = std::make_unique<toi::Lcd> (pal());
        scope_->attachScope (audioTap());
        addAndMakeVisible (*scope_);

        // FUNCTIONAL patchbay + the 4 cord-amount knobs
        patch_ = std::make_unique<Patchbay> (pal());
        patch_->setLabels ({ "LFO","S&H","ENV","AR","FOLL","NOISE" }, { "PITCH","VCO2","PW","CUTOFF","RES","AMP" });
        for (int i = 0; i < 4; ++i)
            patch_->setCord (i, findParam ("p" + juce::String (i + 1) + "Src"), findParam ("p" + juce::String (i + 1) + "Dst"), findParam ("p" + juce::String (i + 1) + "Amt"));
        addAndMakeVisible (*patch_);
        for (int i = 0; i < 4; ++i)
        {
            auto k = std::make_unique<toi::Knob> (juce::String (i + 1), pal(), arp::kCord[i].withAlpha (0.5f));
            k->setArc (arp::kCord[i]);
            if (auto* prm = findParam ("p" + juce::String (i + 1) + "Amt")) k->attach (*prm);
            addAndMakeVisible (*k); amtKnobs.push_back (std::move (k));
        }

        // preset row (16 molded square buttons) + RAND/SAVE
        for (int i = 0; i < 16; ++i)
        { auto b = std::make_unique<toi::MoldedButton> (arp::kPanelLo.brighter (0.12f)); b->setLit (arp::kOrange); const int idx = i; b->onClick = [this, idx] { recallSlot (idx); }; addAndMakeVisible (*b); slots.push_back (std::move (b)); }
        rand_ = std::make_unique<ArpFuncButton> ("RAND", arp::kAmber);
        save_ = std::make_unique<ArpFuncButton> ("SAVE", arp::kOrange);
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
        juce::Random r (2600);
        for (int y = 0; y < h; ++y) for (int x = 0; x < w; ++x)
        { const float n = r.nextFloat(); if (n > 0.62f) { const float a = (n - 0.62f) / 0.38f * 0.06f; const bool light = r.nextBool();
            img.setPixelAt (x, y, (light ? juce::Colours::white : juce::Colours::black).withAlpha (a)); } }
        return img;
    }

    void paintPanel (juce::Graphics& g, juce::Rectangle<float> panel) override
    {
        juce::ignoreUnused (panel);
        juce::ColourGradient pg (arp::kPanel, rPanel.getCentreX(), rPanel.getY(), arp::kPanelLo, rPanel.getCentreX(), rPanel.getBottom(), false);
        g.setGradientFill (pg); g.fillRoundedRectangle (rPanel, 5.0f);
        if (grain_.isValid()) { g.setFillType (juce::FillType (grain_, juce::AffineTransform::translation (rPanel.getX(), rPanel.getY()))); g.fillRoundedRectangle (rPanel, 5.0f); }
        g.setColour (juce::Colours::black); g.drawRoundedRectangle (rPanel, 5.0f, 1.5f);
        g.setColour (juce::Colours::white.withAlpha (0.05f)); g.drawRoundedRectangle (rPanel.reduced (1.6f), 4.0f, 1.0f);

        // module header titles + thin dividers between modules
        g.setFont (toi::uiFont (8.0f, true).withExtraKerningFactor (0.12f));
        for (size_t i = 0; i < mods.size(); ++i)
        {
            const auto& m = mods[i];
            const float x0 = colX (m.startCol), x1 = colX (m.endCol + 1);
            g.setColour (m.name == "FILTER" ? arp::kOrange : arp::kAmber);
            g.drawText (m.name, juce::Rectangle<float> (x0, rHdr.getY(), x1 - x0, rHdr.getHeight()), juce::Justification::centred);
            if (i > 0)
            {
                g.setColour (juce::Colours::black.withAlpha (0.5f)); g.drawLine (x0 - 1.0f, rRow.getY(), x0 - 1.0f, rRow.getBottom(), 1.1f);
                g.setColour (juce::Colours::white.withAlpha (0.05f)); g.drawLine (x0, rRow.getY(), x0, rRow.getBottom(), 1.0f);
            }
        }

        // bottom-strip section labels
        auto sectionLabel = [&] (const juce::String& t, juce::Rectangle<float> r)
        { g.setColour (arp::kDim); g.setFont (toi::uiFont (6.5f, true).withExtraKerningFactor (0.12f)); g.drawText (t, juce::Rectangle<float> (r.getX(), r.getY() - 9.0f, 160.0f, 9.0f), juce::Justification::centredLeft); };
        g.setColour (juce::Colours::black); g.fillRoundedRectangle (rScope.expanded (2.0f), 4.0f);
        sectionLabel ("SCOPE", rScope);
        sectionLabel ("PATCH BAY  (click a source, then a destination - click a cable to unplug)", rPatch);
        sectionLabel ("PATCH AMOUNT", rAmt);
        sectionLabel ("PRESETS", rPreset);

        // brand block (MODULE / SIZE LEDs, then a clear gap, then the model mark)
        auto bh = rBrandHdr;
        drawViewLeds (g, bh.removeFromTop (28.0f));   // dot + "MODULE"/"SIZE" label, with room
        bh.removeFromTop (10.0f);                      // breathing room so the name isn't crammed under the buttons
        g.setColour (arp::kCream); g.setFont (toi::uiFont (16.0f, true));
        g.drawText ("JW-2600", bh.removeFromTop (18.0f), juce::Justification::centred);
        g.setColour (arp::kDim); g.setFont (toi::uiFont (5.5f, true).withExtraKerningFactor (0.2f));
        g.drawText ("TOI - plugin corp", bh.removeFromTop (9.0f), juce::Justification::centred);
    }

    void layoutPanel (juce::Rectangle<float> panel) override
    {
        rPanel = juce::Rectangle<float> (panel.getX() + cheekInset, panel.getY(), panel.getWidth() - 2.0f * cheekInset, panel.getHeight());
        auto inner = rPanel.reduced (9.0f, 6.0f);

        // bottom strip: scope | patchbay | patch-amount | presets | rand/save | brand
        auto strip = inner.removeFromBottom (96.0f);
        inner.removeFromBottom (4.0f);
        {
            auto s = strip.reduced (2.0f, 4.0f);
            rBrandHdr = s.removeFromRight (146.0f);
            s.removeFromRight (8.0f);
            auto rs = s.removeFromRight (82.0f).reduced (2.0f, 14.0f);
            const float bh = (rs.getHeight() - 4.0f) * 0.5f;
            placeInArtboard (*rand_, rs.removeFromTop (bh)); rs.removeFromTop (4.0f); placeInArtboard (*save_, rs.removeFromTop (bh));
            s.removeFromRight (10.0f);
            rScope = s.removeFromLeft (160.0f).reduced (2.0f, 9.0f);
            s.removeFromLeft (12.0f);
            rPreset = s.removeFromRight (186.0f).reduced (0.0f, 4.0f);
            s.removeFromRight (12.0f);
            rAmt = s.removeFromRight (120.0f);
            s.removeFromRight (12.0f);
            rPatch = s.reduced (0.0f, 2.0f);

            placeInArtboard (*scope_, rScope);
            placeInArtboard (*patch_, rPatch);

            // 4 amount knobs (2x2) under a title band
            auto ak = rAmt; ak.removeFromTop (10.0f);
            const float kw = ak.getWidth() * 0.5f, kh = ak.getHeight() * 0.5f;
            for (int i = 0; i < 4; ++i)
            { const int rr = i / 2, cc = i % 2; placeInArtboard (*amtKnobs[(size_t) i], juce::Rectangle<float> (ak.getX() + cc * kw, ak.getY() + rr * kh, kw, kh).reduced (3.0f)); }

            // presets 2x8
            auto pr = rPreset; const int pc = 8, prows = 2; const float pgap = 3.0f;
            const float pw = (pr.getWidth() - pgap * (pc - 1)) / (float) pc;
            const float ph = (pr.getHeight() - pgap * (prows - 1)) / (float) prows;
            for (int i = 0; i < 16; ++i)
            { const int rr = i / pc, cc = i % pc; placeInArtboard (*slots[(size_t) i], juce::Rectangle<float> (pr.getX() + cc * (pw + pgap), pr.getY() + rr * (ph + pgap), pw, ph)); }
        }

        // header band + fader/switch row
        rHdr = inner.removeFromTop (13.0f);
        inner.removeFromTop (2.0f);
        rRow = inner;

        nCols = (int) columns.size();
        colPitch = rRow.getWidth() / (float) nCols;
        rowX0 = rRow.getX();
        for (int i = 0; i < nCols; ++i)
        {
            auto* comp = columns[(size_t) i];
            juce::Rectangle<float> cell (colX (i), rRow.getY(), colPitch, rRow.getHeight());
            if (dynamic_cast<ArpSwitch*> (comp) != nullptr)
                placeInArtboard (*comp, cell.reduced (2.0f, 0.0f).withSizeKeepingCentre (juce::jmin (44.0f, colPitch - 2.0f), 30.0f));
            else
                placeInArtboard (*comp, cell.reduced (1.0f, 0.0f));
        }
    }

private:
    struct ModRange { juce::String name; int startCol = 0, endCol = 0; };
    float colX (int i) const { return rowX0 + colPitch * (float) i; }

    void addFader (const juce::String& id, const juce::String& label, juce::Colour cap)
    {
        auto f = std::make_unique<ArpFader> (label, cap, pal());
        if (auto* prm = findParam (id)) f->attach (*prm);
        addAndMakeVisible (*f); columns.push_back (f.get()); faders.push_back (std::move (f));
    }

    std::vector<std::unique_ptr<ArpFader>> faders;
    std::vector<juce::Component*> columns;          // faders + switches in layout order
    std::vector<ModRange> mods;
    std::unique_ptr<ArpSwitch> sync_, v3mode_, fmode_;
    std::unique_ptr<toi::Lcd> scope_;
    std::unique_ptr<Patchbay> patch_;
    std::vector<std::unique_ptr<toi::Knob>> amtKnobs;
    std::vector<std::unique_ptr<toi::MoldedButton>> slots;
    std::unique_ptr<ArpFuncButton> rand_, save_;
    juce::Image grain_;
    float colPitch = 1.0f, rowX0 = 0.0f; int nCols = 0;
    juce::Rectangle<float> rPanel, rRow, rHdr, rScope, rPatch, rAmt, rPreset, rBrandHdr;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JW2600Editor)
};

//==============================================================================
class JW2600Plugin  : public cmaj::plugin::GeneratedPlugin<::JW2600>,
                      public toi::AudioTapSource,
                      public toi::PresetStore
{
public:
    using Base = cmaj::plugin::GeneratedPlugin<::JW2600>;
    JW2600Plugin (std::shared_ptr<cmaj::Patch> p) : Base (std::move (p)) {}
    juce::AudioProcessorEditor* createEditor() override { return new JW2600Editor (*this, keyboardState); }
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
