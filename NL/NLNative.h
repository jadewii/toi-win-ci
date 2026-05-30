// JW-NL native faceplate (the bright red virtual-analog tribute) on the toi_faceplate.h kit.
// Traces the Nord Lead 1/2: a SATURATED fire-engine RED satin metal body with honey-OAK wood
// end-cheeks (the red+wood contrast IS the identity), WHITE silkscreen text, GREEN (yellow-green)
// LEDs, and a 3-digit green 7-seg PROGRAM display. The knob-per-function wall is small BLACK
// pointer knobs; the discrete selectors are a button + a vertical GREEN LED COLUMN. Left = a
// stubby spring PITCH STICK (no centre dead-zone) + a mod WHEEL that drives the headline MORPH.
// Every control drives a real engine param. NO brand names.
#pragma once

#include "toi_faceplate.h"

struct JWNL;

namespace nl
{
    static const juce::Colour kRed    { 0xffc8102e };   // fire-engine red body (~#C8102E, satin)
    static const juce::Colour kRedHi  { 0xffe2253f };   // body highlight (top-centre)
    static const juce::Colour kRedLo  { 0xff8e0a1f };   // body shadow (lower)
    static const juce::Colour kInk    { 0xff15060a };   // dark seam / frame ink (near-black red)
    static const juce::Colour kWhite  { 0xfff4eee6 };   // white silkscreen
    static const juce::Colour kDim    { 0xffc4ccd6 };   // dim label (cool grey on the slate)
    static const juce::Colour kOak    { 0xff8e0a1f };   // (was oak) NO wood - dark-red frame edge
    static const juce::Colour kOakD   { 0xff560713 };   // darker red frame edge
    static const juce::Colour kGreen  { 0xffe53a2a };   // RED LED (bright/lit) - Nord Lead 2 uses red LEDs
    static const juce::Colour kGreenD { 0xff401612 };   // LED off (dark red)
    static const juce::Colour kSegOff { 0xff2c0f0b };   // 7-seg unlit segment (dark red)
    static const juce::Colour kBlack  { 0xff0e0e10 };   // small black knob/button body
    static const juce::Colour kBox    { 0xff7c8794 };   // SLATE grey-blue section panel (Jade's ref - not red)
    static const juce::Colour kBoxHi  { 0x44f4eee6 };
}

//==============================================================================
// NlKnob - the JW-NL control: a SMALL glossy BLACK pointer knob with a thin WHITE pointer line and
// a GREEN value-arc just outside the body (the bright green LED accent of the panel). Bound 0..1.
class NlKnob  : public juce::Component
{
public:
    NlKnob()
    {
        slider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
        slider.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
        slider.setLookAndFeel (&laf);
        slider.setRange (0.0, 1.0, 0.0);
        slider.setDoubleClickReturnValue (true, 0.5);
        addAndMakeVisible (slider);
    }
    ~NlKnob() override { slider.setLookAndFeel (nullptr); }
    void attach (juce::AudioProcessorParameter& p)
    { att = std::make_unique<toi::ParamKnobAttachment> (p, slider); slider.setDoubleClickReturnValue (true, p.getDefaultValue()); slider.onValueChange = [this] { repaint(); }; repaint(); }
    void resized() override { slider.setBounds (getLocalBounds()); }
    void paint (juce::Graphics& g) override
    {
        auto b = getLocalBounds().toFloat();
        const float d = std::min (b.getWidth(), b.getHeight());
        const float cx = b.getCentreX(), cy = b.getCentreY();
        const float r = d * 0.5f - 5.0f;
        const float v = juce::jlimit (0.0f, 1.0f, (float) slider.getValue());
        const float ang = juce::degreesToRadians (-135.0f + 270.0f * v);
        const float dx = std::sin (ang), dy = -std::cos (ang);

        // (no value-arc - the real Nord Lead 2 knobs are plain black with a white pointer)
        // drop shadow
        g.setColour (juce::Colours::black.withAlpha (0.45f)); g.fillEllipse (cx - r, cy - r + 2.0f, r * 2.0f, r * 2.0f);
        // glossy black cap (lit from upper-left)
        juce::ColourGradient body (juce::Colour (0xff32323a), cx - r * 0.45f, cy - r * 0.55f,
                                   juce::Colour (0xff050507), cx + r * 0.45f, cy + r * 0.7f, false);
        body.addColour (0.5, juce::Colour (0xff161619));
        g.setGradientFill (body); g.fillEllipse (cx - r, cy - r, r * 2.0f, r * 2.0f);
        g.setColour (juce::Colours::black); g.drawEllipse (cx - r, cy - r, r * 2.0f, r * 2.0f, 1.0f);
        // upper-left sheen
        { juce::Path sh; sh.addCentredArc (cx, cy, r - 1.5f, r - 1.5f, 0.0f, juce::degreesToRadians (-120.0f), juce::degreesToRadians (-20.0f), true);
          g.setColour (juce::Colours::white.withAlpha (0.18f)); g.strokePath (sh, juce::PathStrokeType (1.6f)); }
        // crisp WHITE pointer line from centre to rim
        g.setColour (nl::kWhite);
        g.drawLine (cx + dx * r * 0.18f, cy + dy * r * 0.18f, cx + dx * (r - 1.5f), cy + dy * (r - 1.5f), 2.2f);
    }
    juce::Slider slider;
private:
    toi::InvisibleRotaryLAF laf;
    std::unique_ptr<toi::ParamKnobAttachment> att;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NlKnob)
};

//==============================================================================
// NlSelector - the Nord-style discrete selector: a small square black BUTTON + a vertical column of
// N GREEN LEDs. Clicking the button steps to the next position; the lit LED shows the selection.
// Drives a 0..1 param quantised into N steps. (The signature green-LED selector column.)
class NlSelector  : public juce::Component,
                    private juce::AudioProcessorParameter::Listener,
                    private juce::AsyncUpdater
{
public:
    explicit NlSelector (int positions) : N (juce::jmax (2, positions)) {}
    ~NlSelector() override { if (param_) param_->removeListener (this); cancelPendingUpdate(); }
    void attach (juce::AudioProcessorParameter* p) { param_ = p; if (param_) param_->addListener (this); triggerAsyncUpdate(); }
    void setLabels (juce::StringArray l) { labels_ = std::move (l); repaint(); }
    int  index() const { return param_ ? juce::jlimit (0, N - 1, juce::roundToInt (param_->getValue() * (N - 1))) : 0; }

    void mouseDown (const juce::MouseEvent&) override
    {
        if (! param_) return;
        int a = (index() + 1) % N;
        param_->beginChangeGesture();
        param_->setValueNotifyingHost ((float) a / (float) (N - 1));
        param_->endChangeGesture();
    }
    void paint (juce::Graphics& g) override
    {
        auto b = getLocalBounds().toFloat();
        const int cur = index();
        // square black step BUTTON at the top
        const float btn = juce::jmin (b.getWidth(), 14.0f);
        auto br = juce::Rectangle<float> (b.getCentreX() - btn * 0.5f, b.getY(), btn, btn);
        g.setColour (nl::kBlack.darker (0.4f)); g.fillRoundedRectangle (br, 2.0f);
        juce::ColourGradient bg (juce::Colour (0xff2a2a30), br.getCentreX(), br.getY(), juce::Colour (0xff0a0a0c), br.getCentreX(), br.getBottom(), false);
        g.setGradientFill (bg); g.fillRoundedRectangle (br.reduced (1.2f), 1.6f);
        g.setColour (juce::Colours::white.withAlpha (0.22f)); g.fillRoundedRectangle (br.reduced (1.2f).withHeight (br.getHeight() * 0.4f), 1.6f);
        g.setColour (juce::Colours::black.withAlpha (0.6f)); g.drawRoundedRectangle (br, 2.0f, 0.8f);

        // vertical column of N green LEDs below the button (top = last position, bottom = first)
        auto col = b.withTrimmedTop (btn + 3.0f);
        const float lh = col.getHeight() / (float) N;
        const float lr = juce::jmin (3.4f, lh * 0.32f);
        for (int i = 0; i < N; ++i)
        {
            const int pos = N - 1 - i;                 // draw top-to-bottom, highest value at top
            const float ly = col.getY() + (float) i * lh + lh * 0.5f;
            const float lx = col.getX() + 8.0f;
            const bool on = (pos == cur);
            if (on) { g.setColour (nl::kGreen.withAlpha (0.45f)); g.fillEllipse (lx - lr - 2.0f, ly - lr - 2.0f, (lr + 2.0f) * 2.0f, (lr + 2.0f) * 2.0f); }
            g.setColour (on ? nl::kGreen : nl::kGreenD); g.fillEllipse (lx - lr, ly - lr, lr * 2.0f, lr * 2.0f);
            g.setColour (juce::Colours::black.withAlpha (0.5f)); g.drawEllipse (lx - lr, ly - lr, lr * 2.0f, lr * 2.0f, 0.6f);
            if (pos < labels_.size())
            {
                g.setColour (on ? nl::kWhite : nl::kDim.withAlpha (0.65f));
                g.setFont (toi::uiFont (5.6f, true));
                g.drawText (labels_[pos], juce::Rectangle<float> (lx + lr + 2.0f, ly - 5.0f, col.getWidth() - (lx + lr + 2.0f - col.getX()), 10.0f), juce::Justification::centredLeft);
            }
        }
    }
private:
    void parameterValueChanged (int, float) override { triggerAsyncUpdate(); }
    void parameterGestureChanged (int, bool) override {}
    void handleAsyncUpdate() override { repaint(); }
    int N; juce::AudioProcessorParameter* param_ = nullptr; juce::StringArray labels_;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NlSelector)
};

//==============================================================================
// NlToggle - small SQUARE black momentary/latch button + a single GREEN LED that lights when the
// 0..1 param is on (>= 0.5). Click toggles. Used for SYNC, RING and the MORPH-arm button.
class NlToggle  : public juce::Component,
                  private juce::AudioProcessorParameter::Listener,
                  private juce::AsyncUpdater
{
public:
    NlToggle() = default;
    ~NlToggle() override { if (param_) param_->removeListener (this); cancelPendingUpdate(); }
    void attach (juce::AudioProcessorParameter* p) { param_ = p; if (param_) param_->addListener (this); triggerAsyncUpdate(); }
    bool on() const { return param_ && param_->getValue() >= 0.5f; }
    void mouseDown (const juce::MouseEvent&) override
    { if (! param_) return; param_->beginChangeGesture(); param_->setValueNotifyingHost (on() ? 0.0f : 1.0f); param_->endChangeGesture(); }
    void paint (juce::Graphics& g) override
    {
        auto b = getLocalBounds().toFloat();
        const bool lit = on();
        // single green LED on the left
        const float lr = 3.4f, lx = b.getX() + lr + 2.0f, ly = b.getCentreY();
        if (lit) { g.setColour (nl::kGreen.withAlpha (0.5f)); g.fillEllipse (lx - lr - 2.5f, ly - lr - 2.5f, (lr + 2.5f) * 2.0f, (lr + 2.5f) * 2.0f); }
        g.setColour (lit ? nl::kGreen : nl::kGreenD); g.fillEllipse (lx - lr, ly - lr, lr * 2.0f, lr * 2.0f);
        g.setColour (juce::Colours::black.withAlpha (0.5f)); g.drawEllipse (lx - lr, ly - lr, lr * 2.0f, lr * 2.0f, 0.6f);
        // square black button on the right
        auto br = b.withTrimmedLeft (lr * 2.0f + 6.0f);
        const float s = juce::jmin (br.getWidth(), br.getHeight()) - 1.0f;
        auto sq = juce::Rectangle<float> (0, 0, s, s).withCentre ({ br.getX() + s * 0.5f + 1.0f, br.getCentreY() });
        g.setColour (nl::kBlack.darker (0.4f)); g.fillRoundedRectangle (sq, 2.0f);
        juce::ColourGradient bg (juce::Colour (0xff2a2a30), sq.getCentreX(), sq.getY(), juce::Colour (0xff0a0a0c), sq.getCentreX(), sq.getBottom(), false);
        g.setGradientFill (bg); g.fillRoundedRectangle (sq.reduced (1.2f), 1.6f);
        g.setColour (juce::Colours::white.withAlpha (0.2f)); g.fillRoundedRectangle (sq.reduced (1.2f).withHeight (sq.getHeight() * 0.4f), 1.6f);
        g.setColour (juce::Colours::black.withAlpha (0.6f)); g.drawRoundedRectangle (sq, 2.0f, 0.8f);
    }
private:
    void parameterValueChanged (int, float) override { triggerAsyncUpdate(); }
    void parameterGestureChanged (int, bool) override {}
    void handleAsyncUpdate() override { repaint(); }
    juce::AudioProcessorParameter* param_ = nullptr;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NlToggle)
};

//==============================================================================
// NlSevenSeg - a 3-digit GREEN 7-segment PROGRAM display showing the active preset slot (A.1..D.4
// style) plus a live amber-green peak bar fed by the audio tap (real animation, never pretend).
class NlSevenSeg  : public juce::Component,
                    private juce::Timer
{
public:
    explicit NlSevenSeg (toi::AudioTap* t) : tap (t) { if (tap) startTimerHz (30); }
    ~NlSevenSeg() override { stopTimer(); }
    void setSlot (int slot) { slot_ = slot; repaint(); }
    void paint (juce::Graphics& g) override
    {
        auto b = getLocalBounds().toFloat();
        // recessed dark green LCD-ish window
        g.setColour (juce::Colour (0xff071205)); g.fillRoundedRectangle (b, 3.0f);
        g.setColour (nl::kGreenD); g.drawRoundedRectangle (b.reduced (0.6f), 3.0f, 1.4f);

        auto digits = b.reduced (6.0f, 5.0f);
        // bank letter A-D + dot + program number (slot 0..15 -> A.1 .. D.4)
        const int bank = (slot_ / 4) % 4;       // 0..3
        const int prog = (slot_ % 4) + 1;       // 1..4
        const char letters[4] = { 'A', 'B', 'C', 'D' };
        const float dw = digits.getWidth() / 3.0f;
        drawDigitChar (g, juce::Rectangle<float> (digits.getX(), digits.getY(), dw, digits.getHeight()), letters[bank]);
        // dot
        { auto dr = juce::Rectangle<float> (digits.getX() + dw, digits.getBottom() - 5.0f, 4.0f, 4.0f);
          g.setColour (nl::kGreen); g.fillEllipse (dr); }
        drawDigitChar (g, juce::Rectangle<float> (digits.getX() + dw * 2.0f, digits.getY(), dw, digits.getHeight()), (char) ('0' + prog));

        // live peak bar across the bottom (audio-driven)
        if (tap)
        {
            const float lvl = juce::jlimit (0.0f, 1.0f, tap->level.load (std::memory_order_relaxed) * 1.8f);
            auto bar = juce::Rectangle<float> (b.getX() + 3.0f, b.getBottom() - 3.0f, (b.getWidth() - 6.0f) * lvl, 2.0f);
            g.setColour (nl::kGreen.withAlpha (0.85f)); g.fillRect (bar);
        }
    }
private:
    void timerCallback() override { if (tap) repaint(); }
    // seven-seg layout: segments a,b,c,d,e,f,g
    void drawDigitChar (juce::Graphics& g, juce::Rectangle<float> r, char ch)
    {
        r = r.reduced (r.getWidth() * 0.14f, 2.0f);
        const bool segOn = segMap (ch).get();
        juce::ignoreUnused (segOn);
        auto S = segMap (ch);
        const float x = r.getX(), y = r.getY(), w = r.getWidth(), h = r.getHeight(), t = juce::jmax (1.6f, w * 0.16f);
        auto hseg = [&] (float sx, float sy, bool on)
        { juce::Path p; p.startNewSubPath (sx, sy); p.lineTo (sx + t, sy - t * 0.5f); p.lineTo (sx + w - t, sy - t * 0.5f); p.lineTo (sx + w, sy);
          p.lineTo (sx + w - t, sy + t * 0.5f); p.lineTo (sx + t, sy + t * 0.5f); p.closeSubPath();
          g.setColour (on ? nl::kGreen : nl::kSegOff); g.fillPath (p); };
        auto vseg = [&] (float sx, float sy, bool on)
        { juce::Path p; p.startNewSubPath (sx, sy); p.lineTo (sx + t * 0.5f, sy + t); p.lineTo (sx + t * 0.5f, sy + h * 0.5f - t); p.lineTo (sx, sy + h * 0.5f);
          p.lineTo (sx - t * 0.5f, sy + h * 0.5f - t); p.lineTo (sx - t * 0.5f, sy + t); p.closeSubPath();
          g.setColour (on ? nl::kGreen : nl::kSegOff); g.fillPath (p); };
        hseg (x, y, S.a);                         // a (top)
        vseg (x + w, y, S.b);                      // b (top-right)
        vseg (x + w, y + h * 0.5f, S.c);           // c (bottom-right)
        hseg (x, y + h, S.d);                      // d (bottom)
        vseg (x, y + h * 0.5f, S.e);               // e (bottom-left)
        vseg (x, y, S.f);                          // f (top-left)
        hseg (x, y + h * 0.5f, S.g);               // g (middle)
    }
    struct Seg { bool a=false,b=false,c=false,d=false,e=false,f=false,g=false; bool get() const { return a||b||c||d||e||f||g; } };
    static Seg segMap (char ch)
    {
        switch (ch)
        {
            case '0': return { 1,1,1,1,1,1,0 };
            case '1': return { 0,1,1,0,0,0,0 };
            case '2': return { 1,1,0,1,1,0,1 };
            case '3': return { 1,1,1,1,0,0,1 };
            case '4': return { 0,1,1,0,0,1,1 };
            case 'A': return { 1,1,1,0,1,1,1 };
            case 'B': return { 0,0,1,1,1,1,1 };   // 'b'
            case 'C': return { 1,0,0,1,1,1,0 };
            case 'D': return { 0,1,1,1,1,0,1 };   // 'd'
            default:  return {};
        }
    }
    toi::AudioTap* tap = nullptr; int slot_ = 0;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NlSevenSeg)
};

//==============================================================================
// NlPitchStick - the Nord PITCH STICK: a stubby vertical spring lever (no centre dead-zone) that
// bends pitch as you push it left/right, then SPRINGS BACK to centre on release. It drives the
// Master Tune param around its 0.5 centre (a real, audible bend). Spring-return on mouse-up.
class NlPitchStick  : public juce::Component
{
public:
    NlPitchStick() = default;
    void attach (juce::AudioProcessorParameter* p) { param_ = p; }
    void mouseDown (const juce::MouseEvent& e) override { if (param_) param_->beginChangeGesture(); drag (e); }
    void mouseDrag (const juce::MouseEvent& e) override { drag (e); }
    void mouseUp   (const juce::MouseEvent&)   override
    { pos_ = 0.0f; if (param_) { param_->setValueNotifyingHost (0.5f); param_->endChangeGesture(); } repaint(); }
    void paint (juce::Graphics& g) override
    {
        auto b = getLocalBounds().toFloat();
        // recessed black well the stick travels in
        auto well = b.reduced (b.getWidth() * 0.28f, 6.0f);
        g.setColour (juce::Colour (0xff140609)); g.fillRoundedRectangle (well, 5.0f);
        g.setColour (nl::kInk); g.drawRoundedRectangle (well, 5.0f, 1.2f);
        // L / R bend markers
        g.setColour (nl::kDim.withAlpha (0.7f)); g.setFont (toi::uiFont (6.0f, true));
        g.drawText ("-", juce::Rectangle<float> (b.getX(), well.getY() - 1.0f, b.getWidth(), 8.0f), juce::Justification::centredTop);
        // the stubby spring lever: pivots at the BOTTOM, tip swings left/right with pos_
        const float pivX = b.getCentreX(), pivY = well.getBottom() - 4.0f;
        const float reach = well.getHeight() - 10.0f;
        const float tipX = pivX + pos_ * (well.getWidth() * 0.42f);
        const float tipY = pivY - reach;
        // shaft
        g.setColour (juce::Colours::black.withAlpha (0.5f)); g.drawLine (pivX, pivY, tipX, tipY, 6.5f);
        juce::ColourGradient sg (juce::Colour (0xff3a3a40), pivX, pivY, juce::Colour (0xff0c0c0e), tipX, tipY, false);
        g.setGradientFill (sg);
        juce::Path shaft; shaft.startNewSubPath (pivX, pivY); shaft.lineTo (tipX, tipY);
        g.strokePath (shaft, juce::PathStrokeType (5.0f, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
        // pivot base
        g.setColour (juce::Colour (0xff202024)); g.fillEllipse (pivX - 6.0f, pivY - 6.0f, 12.0f, 12.0f);
        g.setColour (juce::Colours::black); g.drawEllipse (pivX - 6.0f, pivY - 6.0f, 12.0f, 12.0f, 1.0f);
        // rubber knob tip (red to echo the body)
        const float kr = 7.0f;
        g.setColour (juce::Colours::black.withAlpha (0.4f)); g.fillEllipse (tipX - kr, tipY - kr + 1.5f, kr * 2.0f, kr * 2.0f);
        juce::ColourGradient kg (nl::kRedHi, tipX - kr * 0.4f, tipY - kr * 0.5f, nl::kRedLo, tipX + kr * 0.4f, tipY + kr * 0.6f, true);
        g.setGradientFill (kg); g.fillEllipse (tipX - kr, tipY - kr, kr * 2.0f, kr * 2.0f);
        g.setColour (juce::Colours::black.withAlpha (0.5f)); g.drawEllipse (tipX - kr, tipY - kr, kr * 2.0f, kr * 2.0f, 1.0f);
    }
private:
    void drag (const juce::MouseEvent& e)
    {
        auto b = getLocalBounds().toFloat();
        pos_ = juce::jlimit (-1.0f, 1.0f, (e.position.x - b.getCentreX()) / (b.getWidth() * 0.42f));
        if (param_) param_->setValueNotifyingHost (juce::jlimit (0.0f, 1.0f, 0.5f + pos_ * 0.5f));   // bend around centre, no dead-zone
        repaint();
    }
    juce::AudioProcessorParameter* param_ = nullptr; float pos_ = 0.0f;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NlPitchStick)
};

//==============================================================================
// NlModWheel - the single mod WHEEL (not two wheels). A tall ribbed black wheel; dragging it moves
// the MORPH position 0..1, which the engine uses to sweep the A-set -> B-set of the morphable knobs
// in one gesture (the headline feature). Stays where you leave it (no spring).
class NlModWheel  : public juce::Component,
                    private juce::AudioProcessorParameter::Listener,
                    private juce::AsyncUpdater
{
public:
    NlModWheel() = default;
    ~NlModWheel() override { if (param_) param_->removeListener (this); cancelPendingUpdate(); }
    void attach (juce::AudioProcessorParameter* p) { param_ = p; if (param_) param_->addListener (this); triggerAsyncUpdate(); }
    float value() const { return param_ ? param_->getValue() : 0.0f; }
    void mouseDown (const juce::MouseEvent& e) override { if (param_) param_->beginChangeGesture(); drag (e); }
    void mouseDrag (const juce::MouseEvent& e) override { drag (e); }
    void mouseUp   (const juce::MouseEvent&)   override { if (param_) param_->endChangeGesture(); }
    void paint (juce::Graphics& g) override
    {
        auto b = getLocalBounds().toFloat();
        auto well = b.reduced (b.getWidth() * 0.18f, 3.0f);
        g.setColour (juce::Colour (0xff140609)); g.fillRoundedRectangle (well, 4.0f);
        g.setColour (nl::kInk); g.drawRoundedRectangle (well, 4.0f, 1.0f);
        // ribbed wheel face; the bright rib sits at the current value (top = 1, bottom = 0)
        const float v = value();
        auto face = well.reduced (2.0f, 4.0f);
        const int ribs = 16;
        for (int i = 0; i < ribs; ++i)
        {
            const float t = (float) i / (float) (ribs - 1);
            const float ry = face.getBottom() - t * face.getHeight();
            const float near = 1.0f - std::abs (t - v) * 2.0f;
            const float bright = juce::jlimit (0.0f, 1.0f, near);
            g.setColour (juce::Colour (0xff202024).brighter (bright * 0.7f));
            g.fillRect (juce::Rectangle<float> (face.getX(), ry - 1.4f, face.getWidth(), 2.8f));
        }
        // current-position green tick on the right rail
        const float ty = face.getBottom() - v * face.getHeight();
        g.setColour (nl::kGreen); g.fillRect (juce::Rectangle<float> (well.getRight() - 2.5f, ty - 1.5f, 3.0f, 3.0f));
        g.setColour (juce::Colours::black.withAlpha (0.5f)); g.drawRoundedRectangle (face, 3.0f, 0.8f);
    }
private:
    void drag (const juce::MouseEvent& e)
    {
        auto b = getLocalBounds().toFloat();
        const float v = juce::jlimit (0.0f, 1.0f, (b.getBottom() - e.position.y) / b.getHeight());
        if (param_) param_->setValueNotifyingHost (v);
    }
    void parameterValueChanged (int, float) override { triggerAsyncUpdate(); }
    void parameterGestureChanged (int, bool) override {}
    void handleAsyncUpdate() override { repaint(); }
    juce::AudioProcessorParameter* param_ = nullptr;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NlModWheel)
};

//==============================================================================
class NlFunc  : public juce::Button
{
public:
    NlFunc (const juce::String& t, juce::Colour fill) : juce::Button (t), col (fill) { setButtonText (t); }
    void flash() { flashing = true; repaint(); juce::Timer::callAfterDelay (150, [s = juce::Component::SafePointer<NlFunc> (this)] { if (s) { s->flashing = false; s->repaint(); } }); }
    void paintButton (juce::Graphics& g, bool over, bool down) override
    {
        auto b = getLocalBounds().toFloat().reduced (1.0f);
        auto fill = flashing ? col.brighter (0.3f) : down ? col.darker (0.18f) : over ? col.brighter (0.08f) : col;
        g.setColour (fill); g.fillRoundedRectangle (b, 2.5f);
        g.setColour (juce::Colours::black.withAlpha (0.5f)); g.drawRoundedRectangle (b, 2.5f, 1.0f);
        g.setColour (nl::kWhite); g.setFont (toi::uiFont (juce::jmin (10.0f, b.getHeight() * 0.5f), true));
        g.drawText (getButtonText(), getLocalBounds(), juce::Justification::centred);
    }
private:
    juce::Colour col; bool flashing = false;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NlFunc)
};

//==============================================================================
inline toi::Config jwnlConfig()
{
    toi::Config c;
    c.model = "JW-NL";
    auto& p = c.pal;
    p.bg = nl::kRedHi; p.bg2 = nl::kRedLo; p.frame = nl::kInk; p.ink = nl::kInk;
    p.accent = nl::kGreen; p.accent2 = nl::kGreen; p.button = nl::kBlack;
    p.thumb = nl::kWhite; p.text = nl::kWhite;
    p.noteStrip = nl::kRedLo;
    p.lcdBg = juce::Colour (0xff071205); p.lcdInk = nl::kGreen;
    p.keyWhite = juce::Colour (0xfff2efe6); p.keyWhitePr = nl::kGreen; p.keyBlack = juce::Colour (0xff1a1416); p.keyBlackPr = nl::kRed;

    // param list - ids MUST match plugins/nl/NL.cmajor exactly (ParamsProcessor event names)
    c.params = {
        { "o1Wave","WAVE" },{ "o1Oct","OCT" },
        { "o2Wave","WAVE" },{ "o2Oct","OCT" },{ "o2Semi","SEMI" },{ "o2Fine","FINE" },{ "sync","SYNC" },{ "fmAmt","FM" },{ "ringAmt","RING" },{ "noise","NOISE" },
        { "oscMix","MIX" },
        { "cutoff","CUTOFF" },{ "reso","RESO" },{ "fMode","TYPE" },{ "fEnvAmt","ENV" },{ "fKeyTrack","KBD" },{ "drive","DRIVE" },
        { "a1","A" },{ "d1","D" },{ "s1","S" },{ "r1","R" },
        { "a2","A" },{ "d2","D" },{ "s2","S" },{ "r2","R" },
        { "mAtk","A" },{ "mDec","D" },{ "mDest","DEST" },{ "mAmt","AMT" },
        { "lfo1Rate","RATE" },{ "lfo1Wave","WAVE" },{ "lfo1Dest","DEST" },{ "lfo1Amt","AMT" },
        { "lfo2Rate","RATE" },{ "lfo2Wave","WAVE" },{ "lfo2Dest","DEST" },{ "lfo2Amt","AMT" },
        { "glide","GLIDE" },{ "volume","GAIN" },{ "tune","TUNE" },
        { "morph","MORPH" },
        { "mOscMix","MIX" },{ "mO2Semi","SEMI" },{ "mO2Fine","FINE" },{ "mFmAmt","FM" },{ "mRingAmt","RING" },{ "mCutoff","CUTOFF" },{ "mReso","RESO" },
    };

    // engine init order (matches the NL.cmajor Params constructor + event inits)
    std::vector<float> base = {
        0.66f,0.50f,
        0.66f,0.50f,0.50f,0.53f,0.0f,0.0f,0.0f,0.0f,
        0.40f,
        0.65f,0.30f,0.0f,0.45f,0.30f,0.20f,
        0.01f,0.40f,0.85f,0.20f,
        0.01f,0.45f,0.30f,0.25f,
        0.05f,0.40f,0.0f,0.0f,
        0.30f,0.0f,0.0f,0.0f,
        0.20f,0.0f,1.0f,0.0f,
        0.0f,0.80f,0.50f,
        0.0f,
        0.85f,0.65f,0.60f,0.55f,0.40f,0.95f,0.70f };

    auto set = [&] (const char* id, float v) { for (size_t i = 0; i < c.params.size(); ++i) if (c.params[i].id == id) base[i] = v; };
    auto P = [&] (const char* nm, std::initializer_list<std::pair<const char*,float>> ov)
    { auto v = base; for (auto& o : ov) for (size_t i = 0; i < c.params.size(); ++i) if (c.params[i].id == o.first) v[i] = o.second; return toi::FactoryPreset { nm, v }; };
    juce::ignoreUnused (set);

    c.factory = {
        P("INIT", {}),
        P("RED LEAD",     {{"o1Wave",0.66f},{"oscMix",0.4f},{"cutoff",0.72f},{"reso",0.35f},{"drive",0.3f},{"fEnvAmt",0.45f},{"a1",0.01f},{"d1",0.35f},{"s1",0.8f}}),
        P("SYNC SCREAM",  {{"sync",1.0f},{"o2Semi",0.66f},{"oscMix",0.8f},{"cutoff",0.85f},{"reso",0.45f},{"drive",0.45f},{"fEnvAmt",0.55f}}),
        P("FAT BASS",     {{"o1Oct",0.25f},{"o2Oct",0.25f},{"o2Fine",0.56f},{"oscMix",0.5f},{"cutoff",0.42f},{"reso",0.4f},{"drive",0.4f},{"d1",0.3f},{"s1",0.5f}}),
        P("RING CLANG",   {{"ringAmt",0.8f},{"o2Semi",0.7f},{"oscMix",0.55f},{"cutoff",0.7f},{"reso",0.4f},{"drive",0.3f}}),
        P("FM METAL",     {{"fmAmt",0.6f},{"o2Semi",0.62f},{"oscMix",0.6f},{"cutoff",0.65f},{"reso",0.35f},{"a1",0.0f},{"d1",0.4f},{"s1",0.3f}}),
        P("NOISE SYNC",   {{"sync",1.0f},{"noise",0.7f},{"oscMix",0.7f},{"cutoff",0.7f},{"reso",0.5f},{"fEnvAmt",0.6f}}),
        P("HP SWEEP",     {{"fMode",0.5f},{"cutoff",0.4f},{"reso",0.55f},{"fEnvAmt",0.7f},{"lfo1Rate",0.2f},{"lfo1Dest",0.5f},{"lfo1Amt",0.4f}}),
        P("MORPH PAD",    {{"oscMix",0.4f},{"cutoff",0.45f},{"reso",0.3f},{"a1",0.4f},{"r1",0.6f},{"morph",0.0f},{"mCutoff",0.9f},{"mReso",0.6f},{"mOscMix",0.8f}}),
        P("ACID 24",      {{"fMode",0.25f},{"cutoff",0.5f},{"reso",0.7f},{"drive",0.5f},{"fEnvAmt",0.6f},{"d2",0.35f},{"glide",0.2f}}),
        P("BP VOX",       {{"fMode",0.75f},{"cutoff",0.55f},{"reso",0.55f},{"oscMix",0.5f},{"lfo1Dest",0.5f},{"lfo1Rate",0.25f},{"lfo1Amt",0.3f}}),
        P("BRIGHT KEYS",  {{"o1Wave",0.66f},{"oscMix",0.45f},{"cutoff",0.7f},{"reso",0.25f},{"a1",0.01f},{"d1",0.5f},{"s1",0.5f},{"r1",0.4f}}),
    };
    return c;
}

//==============================================================================
class JWNLEditor  : public toi::PanelEditor
{
public:
    JWNLEditor (juce::AudioProcessor& proc, juce::MidiKeyboardState& kb)
        : toi::PanelEditor (proc, kb, jwnlConfig())
    {
        // ---- the knob-per-function wall, grouped L->R like the real panel ----
        groups_ = {
            { "OSC 1",   { "o1Oct","o1Wave" } },
            { "OSC 2",   { "o2Oct","o2Wave","o2Semi","o2Fine","fmAmt","ringAmt","noise" } },
            { "OSC MIX", { "oscMix" } },
            { "MOD ENV", { "mAtk","mDec","mAmt","mDest" } },
            { "FILTER",  { "cutoff","reso","fEnvAmt","fKeyTrack","drive","fMode" } },
            { "FILTER ENV", { "a2","d2","s2","r2" } },
            { "AMP ENV", { "a1","d1","s1","r1" } },
            { "AMP",     { "volume","glide" } },
            { "LFO 1",   { "lfo1Rate","lfo1Amt","lfo1Wave","lfo1Dest" } },
            { "LFO 2",   { "lfo2Rate","lfo2Amt","lfo2Wave","lfo2Dest" } },
        };
        for (auto& grp : groups_) for (auto& id : grp.ids) addKnob (id);

        // ---- green-LED selector columns (the discrete switches) ----
        addSelector ("o1Wave",  4, { "SIN","TRI","SAW","PUL" });
        addSelector ("o2Wave",  4, { "SIN","TRI","SAW","PUL" });
        addSelector ("o1Oct",   5, { "-2","-1","0","+1","+2" });
        addSelector ("o2Oct",   5, { "-2","-1","0","+1","+2" });
        addSelector ("fMode",   5, { "12L","24L","HP","BP","NCH" });
        addSelector ("mDest",   3, { "PIT","FM","FLT" });
        addSelector ("lfo1Wave",3, { "TRI","SAW","SQR" });
        addSelector ("lfo1Dest",3, { "PIT","FLT","FM" });
        addSelector ("lfo2Wave",3, { "TRI","SAW","SQR" });
        addSelector ("lfo2Dest",3, { "PIT","FLT","FM" });

        // ---- toggle buttons (single green LED) ----
        sync_ = std::make_unique<NlToggle>(); if (auto* prm = findParam ("sync")) sync_->attach (prm); addAndMakeVisible (*sync_);

        // ---- MORPH arm + the morph B-set knobs (the signature) ----
        for (const char* id : { "mOscMix","mO2Semi","mO2Fine","mFmAmt","mRingAmt","mCutoff","mReso" })
            addMorphKnob (id);

        // ---- left controllers: pitch STICK + mod WHEEL (drives MORPH) ----
        stick_ = std::make_unique<NlPitchStick>(); stick_->attach (findParam ("tune")); addAndMakeVisible (*stick_);
        wheel_ = std::make_unique<NlModWheel>();    wheel_->attach (findParam ("morph")); addAndMakeVisible (*wheel_);

        // ---- 3-digit green 7-seg program display (live peak-bar) ----
        seg_ = std::make_unique<NlSevenSeg> (audioTap()); addAndMakeVisible (*seg_);

        // ---- preset slots + RAND / SAVE ----
        for (int i = 0; i < 16; ++i)
        { auto b = std::make_unique<toi::MoldedButton> (juce::Colour (0xffe9e6df)); b->setLit (juce::Colour (0xff2f6fd0)); const int idx = i; b->onClick = [this, idx] { recallSlot (idx); }; addAndMakeVisible (*b); slots_.push_back (std::move (b)); }
        rand_ = std::make_unique<NlFunc> ("RAND", nl::kRedLo); save_ = std::make_unique<NlFunc> ("SAVE", juce::Colour (0xff2f6fd0));
        rand_->onClick = [this] { doRandom(); rand_->flash(); };
        save_->onClick = [this] { saveSlot (activeSlot()); save_->flash(); };
        addAndMakeVisible (*rand_); addAndMakeVisible (*save_);

        finishSetup();
    }

protected:
    void setPresetActiveVisual (int idx) override
    { for (int i = 0; i < (int) slots_.size(); ++i) slots_[(size_t) i]->setActive (i == idx); if (seg_) seg_->setSlot (idx); }

    void paintPanel (juce::Graphics& g, juce::Rectangle<float> panel) override
    {
        rPanel = panel;
        // saturated red satin body (top-centre highlight -> lower shadow)
        juce::ColourGradient pg (juce::Colour (0xff1c2029), panel.getCentreX(), panel.getY(), juce::Colour (0xff0d0f15), panel.getCentreX(), panel.getBottom(), false);
        g.setGradientFill (pg); g.fillRoundedRectangle (panel, 5.0f);
        // faint horizontal satin brushing
        g.setColour (juce::Colours::black.withAlpha (0.04f));
        for (float y = panel.getY() + 3.0f; y < panel.getBottom(); y += 3.0f) g.drawLine (panel.getX(), y, panel.getRight(), y, 0.5f);

        // honey-oak end-cheeks (the red+wood contrast = the identity)
        const float ch = 26.0f;
        drawCheek (g, juce::Rectangle<float> (panel.getX(), panel.getY(), ch, panel.getHeight()));
        drawCheek (g, juce::Rectangle<float> (panel.getRight() - ch, panel.getY(), ch, panel.getHeight()));
        g.setColour (nl::kInk); g.drawRoundedRectangle (panel, 5.0f, 1.5f);

        for (auto& grp : groups_) drawGroupBox (g, grp);

        // selector + toggle labels
        for (auto& sr : selRects_)
        { g.setColour (nl::kWhite); g.setFont (toi::uiFont (6.0f, true));
          g.drawText (sr.first, juce::Rectangle<float> (sr.second.getX() - 6.0f, sr.second.getY() - 8.5f, sr.second.getWidth() + 12.0f, 8.0f), juce::Justification::centred); }

        // SYNC label
        g.setColour (nl::kWhite); g.setFont (toi::uiFont (6.0f, true));
        g.drawText ("SYNC", juce::Rectangle<float> (rSync_.getX() - 4.0f, rSync_.getY() - 8.5f, rSync_.getWidth() + 8.0f, 8.0f), juce::Justification::centred);

        // MORPH vertical box (the B-set knobs) - far-left, where the wheels used to be
        g.setColour (juce::Colour (0xff10131a)); g.fillRoundedRectangle (rMorph_, 4.0f);
        g.setColour (nl::kGreen.withAlpha (0.7f)); g.drawRoundedRectangle (rMorph_, 4.0f, 1.2f);
        g.setColour (nl::kGreen); g.setFont (toi::uiFont (7.0f, true).withExtraKerningFactor (0.08f));
        g.drawText ("MORPH", rMorph_.withHeight (11.0f).reduced (4.0f, 1.0f), juce::Justification::centred);
        g.setColour (nl::kDim); g.setFont (toi::uiFont (5.0f, true));
        g.drawText ("B SET", juce::Rectangle<float> (rMorph_.getX() + 2.0f, rMorph_.getBottom() - 9.0f, rMorph_.getWidth() - 4.0f, 8.0f), juce::Justification::centred);

        // PROGRAM display label
        g.setColour (nl::kWhite); g.setFont (toi::uiFont (6.5f, true).withExtraKerningFactor (0.1f));
        g.drawText ("PROGRAM", juce::Rectangle<float> (rSeg_.getX(), rSeg_.getY() - 9.0f, 120.0f, 9.0f), juce::Justification::centredLeft);
        g.drawText ("PRESET",  juce::Rectangle<float> (rPreset_.getX(), rPreset_.getY() - 9.0f, 120.0f, 9.0f), juce::Justification::centredLeft);

        // brand top-left over the oak cheek area + view LEDs
        auto bh = rBrand_;
        drawViewLeds (g, bh.removeFromTop (22.0f));
        bh.removeFromTop (4.0f);
        g.setColour (nl::kWhite); g.setFont (toi::uiFont (16.0f, true));
        g.drawText ("JW-NL", bh, juce::Justification::centred);
    }

    void drawCheek (juce::Graphics& g, juce::Rectangle<float> r)
    {
        juce::ColourGradient wg (nl::kOak, r.getX(), r.getY(), nl::kOakD, r.getRight(), r.getY(), false);
        g.setGradientFill (wg); g.fillRect (r);
        juce::Random rr (770 + (int) r.getX());
        g.setColour (nl::kOakD.withAlpha (0.35f));
        for (int i = 0; i < 7; ++i) { const float gx = r.getX() + rr.nextFloat() * r.getWidth(); g.drawLine (gx, r.getY(), gx + 2.0f, r.getBottom(), 0.7f); }
    }

    void layoutPanel (juce::Rectangle<float> panel) override
    {
        rPanel = panel;
        auto inner = panel.reduced (28.0f, 8.0f);

        // rBrand_ is set inside the LEFT column below (centred there, clear of the wood)
        // wheels REMOVED (Jade) - morph goes in a vertical box where they were
        if (stick_) stick_->setVisible (false);
        if (wheel_) wheel_->setVisible (false);

        // ===== BOTTOM strip: PROGRAM display + ONE row of 16 presets + small RAND/SAVE =====
        auto strip = inner.removeFromBottom (30.0f);
        inner.removeFromBottom (10.0f);
        {
            rSeg_ = strip.removeFromLeft (74.0f).withSizeKeepingCentre (70.0f, 26.0f); placeInArtboard (*seg_, rSeg_);
            strip.removeFromLeft (12.0f);
            auto rs = strip.removeFromRight (108.0f); strip.removeFromRight (8.0f);
            rPreset_ = strip;
            const int pc = 16; const float pgap = 3.0f;
            const float pw = (rPreset_.getWidth() - pgap * (pc - 1)) / (float) pc;
            const float ph = juce::jmin (16.0f, rPreset_.getHeight());
            const float py = rPreset_.getY() + (rPreset_.getHeight() - ph) * 0.5f;
            for (int i = 0; i < 16; ++i) placeInArtboard (*slots_[(size_t) i], juce::Rectangle<float> (rPreset_.getX() + (float) i * (pw + pgap), py, pw, ph));
            const float bw = (rs.getWidth() - 4.0f) * 0.5f;   // small RAND/SAVE, preset-sized
            placeInArtboard (*rand_, juce::Rectangle<float> (rs.getX(), py, bw, ph));
            placeInArtboard (*save_, juce::Rectangle<float> (rs.getX() + bw + 4.0f, py, bw, ph));
        }

        // ===== LEFT column: brand (CENTRED at top, clear of the wood) + MORPH vertical box =====
        inner.removeFromTop (10.0f);
        auto leftCol = inner.removeFromLeft (106.0f);   // wide enough for MODULE/SIZE + JW-NL to centre
        inner.removeFromLeft (12.0f);
        rBrand_ = leftCol.removeFromTop (48.0f);        // MODULE/SIZE + JW-NL centred IN the left column
        leftCol.removeFromTop (2.0f);
        rMorph_ = leftCol;
        {
            auto mb = rMorph_.reduced (5.0f, 0.0f).withTrimmedTop (13.0f).withTrimmedBottom (11.0f);
            const int mc = (int) morphKnobs_.size();              // 7
            const int cols = 2, rows = (mc + cols - 1) / cols;    // 2 x 4
            const float cw = mb.getWidth() / (float) cols, rh = mb.getHeight() / (float) rows;
            for (int i = 0; i < mc; ++i)
            { const int rr = i / cols, cc = i % cols;
              auto cell = juce::Rectangle<float> (mb.getX() + (float) cc * cw, mb.getY() + (float) rr * rh, cw, rh);
              const float d = juce::jmin (cw, rh) - 3.0f;
              placeInArtboard (*morphKnobs_[(size_t) i], cell.withSizeKeepingCentre (d, d)); }
        }

        // ===== MAIN: sections fill the whole remaining (tall) area -> BIG knobs, no empty space =====
        layoutGroups (inner);
    }

private:
    struct Group { juce::String name; std::vector<juce::String> ids; juce::Rectangle<float> rect; };

    void addKnob (const juce::String& id)
    {
        auto k = std::make_unique<NlKnob>();
        if (auto* prm = findParam (id)) k->attach (*prm);
        addAndMakeVisible (*k); knobMap_[id] = k.get(); knobs_.push_back (std::move (k));
    }
    void addMorphKnob (const juce::String& id)
    {
        auto k = std::make_unique<NlKnob>();
        if (auto* prm = findParam (id)) k->attach (*prm);
        addAndMakeVisible (*k); knobMap_[id] = k.get(); morphKnobs_.push_back (k.get()); knobs_.push_back (std::move (k));
    }
    void addSelector (const juce::String& id, int positions, juce::StringArray labels)
    {
        auto s = std::make_unique<NlSelector> (positions);
        if (auto* prm = findParam (id)) s->attach (prm);
        s->setLabels (std::move (labels));
        addAndMakeVisible (*s); selMap_[id] = s.get(); selectors_.push_back (std::move (s));
    }
    NlKnob* knobFor (const juce::String& id) const { auto it = knobMap_.find (id); return it == knobMap_.end() ? nullptr : it->second; }
    NlSelector* selFor (const juce::String& id) const { auto it = selMap_.find (id); return it == selMap_.end() ? nullptr : it->second; }

    int totalKnobs() const { int n = 0; for (auto& g : groups_) n += (int) g.ids.size(); return n; }

    void layoutGroups (juce::Rectangle<float> band)
    {
        selRects_.clear();
        const int n = juce::jmax (1, totalKnobs());   // total items across all sections
        const float gap = 6.0f;
        const float usable = band.getWidth() - gap * (float) (groups_.size() - 1);
        float x = band.getX();
        for (auto& grp : groups_)
        {
            const int N = juce::jmax (1, (int) grp.ids.size());
            const float gw = usable * (float) N / (float) n;
            grp.rect = juce::Rectangle<float> (x, band.getY(), gw, band.getHeight());
            // a grid that MAXIMISES item size while filling the section (knobs/selectors spread evenly,
            // big enough to fill - a 2-item section stacks 1 above the other, etc.)
            auto area = grp.rect.reduced (5.0f, 0.0f).withTrimmedTop (14.0f).withTrimmedBottom (3.0f);
            int bestC = 1; float bestD = 0.0f;
            for (int c = 1; c <= N; ++c) { const int r = (N + c - 1) / c; const float d = juce::jmin (area.getWidth() / (float) c, area.getHeight() / (float) r); if (d > bestD) { bestD = d; bestC = c; } }
            const int cols = bestC, rows = (N + cols - 1) / cols;
            const float cw = area.getWidth() / (float) cols, ch = area.getHeight() / (float) rows;
            for (int i = 0; i < N; ++i)
            {
                const int rr = i / cols, cc = i % cols;
                auto cell = juce::Rectangle<float> (area.getX() + (float) cc * cw, area.getY() + (float) rr * ch, cw, ch);
                const auto& id = grp.ids[(size_t) i];
                if (auto* s = selFor (id))   // SELECTOR (oct/wave/dest/type = red LED column) takes priority
                {
                    if (auto* k = knobFor (id)) k->setVisible (false);   // these ids also got a knob in the add-loop - hide it
                    auto sr = cell.reduced (4.0f, 3.0f).withTrimmedBottom (8.0f);
                    placeInArtboard (*s, sr);
                    selRects_.push_back ({ labelFor (id), sr });
                }
                else if (auto* k = knobFor (id))
                {
                    k->setVisible (true);
                    const float d = juce::jmax (16.0f, juce::jmin (cw - 4.0f, ch - 11.0f));   // leave room for the label below
                    placeInArtboard (*k, juce::Rectangle<float> (0, 0, d, d).withCentre ({ cell.getCentreX(), cell.getY() + (ch - 9.0f) * 0.5f }));
                }
            }
            x += gw + gap;
        }
        // SYNC toggle, tucked top-right of OSC 2
        if (auto* g2 = groupRect ("OSC 2"))
        {
            rSync_ = juce::Rectangle<float> (g2->getRight() - 27.0f, g2->getY() + 13.0f, 23.0f, 12.0f);
            placeInArtboard (*sync_, rSync_);
        }
    }

    // place selectors whose id is NOT a knob (oct selectors, mod/lfo dest+wave) into the sel row
    // above their owning group, spread evenly.
    void placeLeftoverSelectors (juce::Rectangle<float> selRow)
    {
        struct Place { const char* id; const char* group; float frac; };
        const Place places[] = {
            { "o1Oct",   "OSC 1", 0.5f },
            { "o2Oct",   "OSC 2", 0.10f },
            { "fMode",   "FILTER", 0.5f },
            { "mDest",   "MOD ENV", 0.85f },
            { "lfo1Wave","LFO 1", 0.30f },
            { "lfo1Dest","LFO 1", 0.72f },
            { "lfo2Wave","LFO 2", 0.30f },
            { "lfo2Dest","LFO 2", 0.72f },
        };
        for (auto& pl : places)
        {
            auto* s = selFor (pl.id); auto* gr = groupRect (pl.group);
            if (! s || ! gr) continue;
            const float cx = gr->getX() + gr->getWidth() * pl.frac;
            auto sr = juce::Rectangle<float> (cx - 17.0f, selRow.getY() + 9.0f, 34.0f, selRow.getHeight() - 10.0f);
            placeInArtboard (*s, sr);
            selRects_.push_back ({ labelFor (pl.id), sr });
        }
    }

    juce::Rectangle<float>* groupRect (const juce::String& nm)
    { for (auto& g : groups_) if (g.name == nm) return &g.rect; return nullptr; }

    juce::String labelFor (const juce::String& id) const
    { for (auto& sp : config().params) if (sp.id == id) return sp.label; return id; }

    void drawGroupBox (juce::Graphics& g, const Group& grp)
    {
        g.setColour (nl::kBox); g.fillRoundedRectangle (grp.rect, 3.0f);
        g.setColour (nl::kBoxHi.withAlpha (0.35f)); g.drawRoundedRectangle (grp.rect, 3.0f, 1.0f);
        g.setColour (nl::kWhite); g.setFont (toi::uiFont (7.0f, true).withExtraKerningFactor (0.06f));
        g.drawText (grp.name, grp.rect.withHeight (10.0f).reduced (4.0f, 1.0f), juce::Justification::centredLeft);
        // knob labels under each (selector params are labelled via selRects_, skip them)
        for (auto& id : grp.ids)
            if (selFor (id) == nullptr)
            if (auto* k = knobFor (id))
            {
                auto kr = k->getBounds().toFloat();
                g.setColour (nl::kDim); g.setFont (toi::uiFont (5.6f, true));
                g.drawText (labelFor (id), juce::Rectangle<float> (kr.getCentreX() - 26.0f, kr.getBottom() - 1.0f, 52.0f, 8.0f), juce::Justification::centred);
            }
    }

    std::vector<std::unique_ptr<NlKnob>> knobs_;
    std::map<juce::String, NlKnob*> knobMap_;
    std::vector<NlKnob*> morphKnobs_;
    std::vector<std::unique_ptr<NlSelector>> selectors_;
    std::map<juce::String, NlSelector*> selMap_;
    std::unique_ptr<NlToggle> sync_;
    std::unique_ptr<NlPitchStick> stick_;
    std::unique_ptr<NlModWheel> wheel_;
    std::unique_ptr<NlSevenSeg> seg_;
    std::vector<std::unique_ptr<toi::MoldedButton>> slots_;
    std::unique_ptr<NlFunc> rand_, save_;
    std::vector<Group> groups_;
    std::vector<std::pair<juce::String, juce::Rectangle<float>>> selRects_;
    juce::Rectangle<float> rPanel, rBrand_, rMorph_, rStick_, rWheel_, rSeg_, rPreset_, rSync_;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JWNLEditor)
};

//==============================================================================
class JWNLPlugin  : public cmaj::plugin::GeneratedPlugin<::JWNL>,
                    public toi::AudioTapSource,
                    public toi::PresetStore
{
public:
    using Base = cmaj::plugin::GeneratedPlugin<::JWNL>;
    JWNLPlugin (std::shared_ptr<cmaj::Patch> p) : Base (std::move (p)) {}
    juce::AudioProcessorEditor* createEditor() override { return new JWNLEditor (*this, keyboardState); }
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
