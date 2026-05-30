// JW-M1 native faceplate (PCM workstation tribute) on the toi_faceplate.h kit.
// Traces the late-80s best-selling AI-synthesis workstation: a matte BLACK shell wrapping a flat
// medium COOL-GREY control surface, a wide short character LCD in a muted YELLOW-GREEN reflective
// field with dark charcoal text, a left-side black JOYSTICK in a square well (L/R pitch, up=filter),
// a single VALUE SLIDER (not a wheel) + up/down buttons, a wall of small square grey-black soft
// buttons with white legends, and sparse red LEDs. The signature WORKFLOW: scroll the MULTISOUND
// families with the VALUE slider on the LCD, and swap the two FX live. NO brand names. Logo JW-M1.
#pragma once

#include "toi_faceplate.h"

struct JWM1;

namespace m1
{
    static const juce::Colour kShell   { 0xff0c0c0c };   // matte black outer shell
    static const juce::Colour kGrey     { 0xff3b3d40 };  // dark charcoal control surface (Jade: "more black")
    static const juce::Colour kGreyHi   { 0xff45474b };
    static const juce::Colour kGreyLo   { 0xff2e3033 };
    static const juce::Colour kInk      { 0xff0a0b0c };  // black silkscreen bezels / outlines
    static const juce::Colour kLegend   { 0xfff2f3f3 };  // white button legends
    static const juce::Colour kText     { 0xffe2e4e5 };  // light silkscreen TEXT on the dark surface
    static const juce::Colour kTextDim  { 0xff9a9c9e };  // dimmer light label text
    static const juce::Colour kDim      { 0xff9a9c9e };  // (kept = kTextDim for back-compat)
    static const juce::Colour kBtn      { 0xff34363a };  // dark grey-black soft button
    static const juce::Colour kBtnHi    { 0xff45474c };
    static const juce::Colour kLcdField { 0xff9fb07a };  // muted yellow-green reflective LCD field
    static const juce::Colour kLcdInk   { 0xff20251a };  // dark charcoal LCD text
    static const juce::Colour kRedLed   { 0xffd23b2c };  // sparse red status LEDs
    static const juce::Colour kAccent   { 0xff9fb07a };

    // the 8 synthesised multisound family names (mirror M1.cmajor buildMultisounds), generic - NO brand.
    static const char* const kMulti[8] = { "GRAND", "TINE", "DRAWBAR", "VOX", "GLASS", "BRASS", "BASS", "DIGITAL" };
    inline int famIndex (float v) { return juce::jlimit (0, 7, juce::roundToInt (v * 7.0f)); }

    // the dual-FX slot menus (mirror the FXBus: chorus + delay -> reverb, series/parallel)
    static const char* const kFxA[4] = { "CHORUS", "ENSEMBLE", "ROTARY", "EQ" };
    static const char* const kFxB[4] = { "DELAY", "HALL", "ROOM", "DRIVE" };
}

//==============================================================================
// M1Lcd - the signature wide character LCD: a muted yellow-green reflective field with a thin black
// bezel, dark charcoal text. Top line shows the live MULTISOUND family (driven by the VALUE slider =
// multi1) + the OSC mode (single / DOUBLE). Bottom line shows the live dual-FX routing (series /
// parallel) and the two FX slots. A faint real-audio scope rides behind the text (mirrors the engine
// output via the AudioTap). Everything redraws when the params it watches change = a REAL workflow LCD.
class M1Lcd  : public juce::Component,
               private juce::Timer,
               private juce::AudioProcessorParameter::Listener,
               private juce::AsyncUpdater
{
public:
    M1Lcd() = default;
    ~M1Lcd() override { stopTimer(); for (auto* p : watched_) if (p) p->removeListener (this); cancelPendingUpdate(); }

    void attachScope (toi::AudioTap* t) { tap_ = t; if (tap_) startTimerHz (24); }
    void watch (std::initializer_list<juce::AudioProcessorParameter*> ps)
    { for (auto* p : ps) { watched_.push_back (p); if (p) p->addListener (this); } triggerAsyncUpdate(); }
    void setSources (juce::AudioProcessorParameter* multi, juce::AudioProcessorParameter* dbl,
                     juce::AudioProcessorParameter* routing, juce::AudioProcessorParameter* chorus,
                     juce::AudioProcessorParameter* delay)
    { pMulti_ = multi; pDbl_ = dbl; pRouting_ = routing; pChorus_ = chorus; pDelay_ = delay; }

    void paint (juce::Graphics& g) override
    {
        auto b = getLocalBounds().toFloat();
        // reserve a thin strip BELOW the green field for the patch readout (kept OFF the screen per
        // the house rule: the LCD itself shows live audio only). This component watches the same
        // params + has a 24Hz timer, so the readout stays live without repainting the whole panel.
        auto readout = b.removeFromBottom (14.0f);
        auto bz = b.withTrimmedBottom (2.0f);

        // thin black low-contrast bezel around the GREEN FIELD only
        g.setColour (m1::kInk); g.fillRoundedRectangle (bz, 3.0f);
        auto field = bz.reduced (4.0f);
        juce::ColourGradient fg (m1::kLcdField.brighter (0.10f), field.getCentreX(), field.getY(),
                                 m1::kLcdField.darker (0.10f), field.getCentreX(), field.getBottom(), false);
        g.setGradientFill (fg); g.fillRoundedRectangle (field, 2.0f);

        // house rule: the screen shows LIVE AUDIO ONLY (no preset/patch text on the LCD).
        // faint dot-matrix grid for the M1 character, then the real-audio scope as the sole content.
        g.setColour (m1::kLcdInk.withAlpha (0.05f));
        for (float gy = field.getY() + 5.0f; gy < field.getBottom(); gy += 4.0f) g.drawHorizontalLine ((int) gy, field.getX() + 4.0f, field.getRight() - 4.0f);
        if (tap_ != nullptr) drawScope (g, field.reduced (8.0f, 6.0f));
        g.setColour (m1::kInk.withAlpha (0.7f)); g.drawRoundedRectangle (field, 2.0f, 1.0f);

        // patch readout strip on the PANEL (not the screen): MULTISOUND family + dual-FX, live
        const int fam = pMulti_ ? m1::famIndex (pMulti_->getValue()) : 0;
        const bool dbl = pDbl_ ? pDbl_->getValue() >= 0.5f : false;
        const bool parallel = pRouting_ ? pRouting_->getValue() >= 0.5f : false;
        const int fa = pChorus_ ? juce::jlimit (0, 3, juce::roundToInt (pChorus_->getValue() * 3.0f)) : 0;
        const int fb = pDelay_ ? juce::jlimit (0, 3, juce::roundToInt (pDelay_->getValue() * 3.0f)) : 0;
        juce::String rd = "MS:" + juce::String (m1::kMulti[fam]) + (dbl ? " [DBL]" : " [SGL]")
                        + "    FX:" + juce::String (m1::kFxA[fa]) + (parallel ? " || " : " > ") + juce::String (m1::kFxB[fb]);
        g.setColour (m1::kInk); g.setFont (juce::Font (juce::FontOptions (8.0f).withName ("Menlo")).boldened());
        g.drawText (rd, readout, juce::Justification::centredLeft);
    }

private:
    void timerCallback() override { repaint(); }
    void parameterValueChanged (int, float) override { triggerAsyncUpdate(); }
    void parameterGestureChanged (int, bool) override {}
    void handleAsyncUpdate() override { repaint(); }

    void drawScope (juce::Graphics& g, juce::Rectangle<float> r)
    {
        const int N = toi::AudioTap::kRing;
        const int wp = tap_->wpos.load (std::memory_order_relaxed);
        const float mid = r.getCentreY(), yScale = r.getHeight() * 0.42f;
        const int cols = juce::jmax (2, (int) r.getWidth());
        juce::Path p; bool started = false;
        for (int x = 0; x < cols; ++x)
        {
            const float u = (float) x / (float) (cols - 1);
            const int idx = (wp + (int) (u * (N - 1))) % N;
            const float s = tap_->ring[(size_t) idx].load (std::memory_order_relaxed);
            const float y = juce::jlimit (r.getY() + 1.0f, r.getBottom() - 1.0f, mid - s * yScale);
            const float px = r.getX() + u * r.getWidth();
            if (! started) { p.startNewSubPath (px, y); started = true; } else p.lineTo (px, y);
        }
        // baseline + the live trace, now the primary screen content (clearly visible)
        g.setColour (m1::kLcdInk.withAlpha (0.18f));
        g.drawHorizontalLine ((int) mid, r.getX(), r.getRight());
        g.setColour (m1::kLcdInk.withAlpha (0.85f));
        g.strokePath (p, juce::PathStrokeType (1.4f));
    }

    toi::AudioTap* tap_ = nullptr;
    std::vector<juce::AudioProcessorParameter*> watched_;
    juce::AudioProcessorParameter* pMulti_ = nullptr;
    juce::AudioProcessorParameter* pDbl_ = nullptr;
    juce::AudioProcessorParameter* pRouting_ = nullptr;
    juce::AudioProcessorParameter* pChorus_ = nullptr;
    juce::AudioProcessorParameter* pDelay_ = nullptr;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (M1Lcd)
};

//==============================================================================
// M1ValueSlider - the workstation's single VALUE control: a tall recessed grey channel with a wide
// dark grey-black thumb (NOT a pitch wheel). Bound to a 0..1 param (multi1 = the multisound scroll).
// This is the signature data-entry slider that scrolls the LCD multisound list.
class M1ValueSlider  : public juce::Component
{
public:
    M1ValueSlider()
    {
        slider.setSliderStyle (juce::Slider::LinearVertical);
        slider.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
        slider.setLookAndFeel (&laf);
        slider.setRange (0.0, 1.0, 0.0);
        addAndMakeVisible (slider);
    }
    ~M1ValueSlider() override { slider.setLookAndFeel (nullptr); }
    void attach (juce::AudioProcessorParameter& p)
    { att = std::make_unique<toi::ParamKnobAttachment> (p, slider); slider.setDoubleClickReturnValue (true, p.getDefaultValue()); slider.onValueChange = [this] { repaint(); }; repaint(); }
    void resized() override { slider.setBounds (getLocalBounds()); }
    void paint (juce::Graphics& g) override
    {
        auto b = getLocalBounds().toFloat().reduced (0.0f, 4.0f);
        const float cx = b.getCentreX(), top = b.getY(), h = b.getHeight();
        // recessed channel
        const float cw = 13.0f;
        juce::Rectangle<float> chan (cx - cw * 0.5f, top, cw, h);
        juce::ColourGradient cg (m1::kInk.darker (0.2f), cx, top, m1::kGreyLo, cx, b.getBottom(), false);
        g.setGradientFill (cg); g.fillRoundedRectangle (chan, cw * 0.5f);
        g.setColour (m1::kInk); g.drawRoundedRectangle (chan, cw * 0.5f, 1.0f);
        // wide dark grey-black thumb (data slider, not a wheel)
        const float v = juce::jlimit (0.0f, 1.0f, (float) slider.getValue());
        const float tW = 30.0f, tH = 16.0f, pad = tH * 0.5f + 2.0f;
        const float ty = top + pad + (1.0f - v) * (h - 2.0f * pad);
        juce::Rectangle<float> thumb (cx - tW * 0.5f, ty - tH * 0.5f, tW, tH);
        g.setColour (juce::Colours::black.withAlpha (0.4f)); g.fillRoundedRectangle (thumb.translated (0.0f, 1.8f), 3.0f);
        juce::ColourGradient tg (m1::kBtnHi, cx, thumb.getY(), m1::kBtn.darker (0.25f), cx, thumb.getBottom(), false);
        g.setGradientFill (tg); g.fillRoundedRectangle (thumb, 3.0f);
        g.setColour (m1::kInk); g.drawRoundedRectangle (thumb, 3.0f, 1.0f);
        g.setColour (m1::kLegend.withAlpha (0.55f));
        g.drawLine (thumb.getX() + 5.0f, thumb.getCentreY(), thumb.getRight() - 5.0f, thumb.getCentreY(), 1.4f);
    }
    juce::Slider slider;
private:
    toi::InvisibleLinearLAF laf;
    std::unique_ptr<toi::ParamKnobAttachment> att;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (M1ValueSlider)
};

//==============================================================================
// M1SoftButton - the small square grey-black soft button with a white legend. Used everywhere on the
// workstation (mode bank, cursor pad, FX swap, value up/down). Bound to a 0..1 param: click cycles
// through N discrete positions (or, with momentary mode, nudges a value up/down). A sparse red LED in
// the top-right corner lights when the current position is "on" (>= the lit threshold). REAL control.
class M1SoftButton  : public juce::Component,
                      private juce::AudioProcessorParameter::Listener,
                      private juce::AsyncUpdater
{
public:
    enum Mode { Cycle, NudgeUp, NudgeDown };
    M1SoftButton (const juce::String& legend, int positions = 2, Mode mode = Cycle)
        : text_ (legend), N_ (juce::jmax (2, positions)), mode_ (mode) {}
    ~M1SoftButton() override { if (param_) param_->removeListener (this); cancelPendingUpdate(); }

    void attach (juce::AudioProcessorParameter* p) { param_ = p; if (param_) param_->addListener (this); triggerAsyncUpdate(); }
    void setStep (float s) { step_ = s; }            // nudge step
    void setShowLed (bool s) { showLed_ = s; repaint(); }
    void setLedOnAny (bool s) { ledOnAny_ = s; }     // LED lit for any non-zero value (else only top position)

    void mouseDown (const juce::MouseEvent&) override
    {
        if (! param_) return;
        down_ = true; repaint();
        if (mode_ == Cycle)
        {
            int a = juce::roundToInt (param_->getValue() * (float) (N_ - 1));
            a = (a + 1) % N_;
            param_->setValueNotifyingHost ((float) a / (float) (N_ - 1));
        }
        else
        {
            const float d = (mode_ == NudgeUp) ? step_ : -step_;
            param_->setValueNotifyingHost (juce::jlimit (0.0f, 1.0f, param_->getValue() + d));
        }
    }
    void mouseUp (const juce::MouseEvent&) override { down_ = false; repaint(); }

    void paint (juce::Graphics& g) override
    {
        auto b = getLocalBounds().toFloat().reduced (1.0f);
        const auto base = down_ ? m1::kBtnHi : m1::kBtn;
        // contact shadow
        g.setColour (juce::Colours::black.withAlpha (0.4f)); g.fillRoundedRectangle (b.translated (0.0f, 1.2f), 2.5f);
        // moulded plastic body
        juce::ColourGradient cg (base.brighter (0.16f), b.getCentreX(), b.getY(), base.darker (0.22f), b.getCentreX(), b.getBottom(), false);
        g.setGradientFill (cg); g.fillRoundedRectangle (b, 2.5f);
        g.setColour (juce::Colours::white.withAlpha (down_ ? 0.10f : 0.18f));
        g.fillRoundedRectangle (b.withHeight (b.getHeight() * 0.4f).reduced (1.5f, 1.0f), 2.0f);
        g.setColour (m1::kInk); g.drawRoundedRectangle (b, 2.5f, 1.0f);

        // sparse red LED (top-right) shows state
        if (showLed_ && param_)
        {
            const float v = param_->getValue();
            const bool lit = ledOnAny_ ? v > 0.02f : v >= (1.0f - 0.5f / (float) (N_ - 1));
            const float lr = juce::jmin (3.0f, b.getHeight() * 0.18f);
            const float lx = b.getRight() - lr - 3.0f, ly = b.getY() + lr + 3.0f;
            if (lit) { g.setColour (m1::kRedLed.withAlpha (0.5f)); g.fillEllipse (lx - lr - 2.0f, ly - lr - 2.0f, (lr + 2.0f) * 2.0f, (lr + 2.0f) * 2.0f); }
            g.setColour (lit ? m1::kRedLed : m1::kRedLed.withAlpha (0.22f)); g.fillEllipse (lx - lr, ly - lr, lr * 2.0f, lr * 2.0f);
        }

        // white legend
        g.setColour (m1::kLegend); g.setFont (toi::uiFont (juce::jmin (8.5f, b.getHeight() * 0.42f), true));
        g.drawFittedText (text_, b.toNearestInt(), juce::Justification::centred, 2);
    }

private:
    void parameterValueChanged (int, float) override { triggerAsyncUpdate(); }
    void parameterGestureChanged (int, bool) override {}
    void handleAsyncUpdate() override { repaint(); }

    juce::String text_; int N_; Mode mode_; float step_ = 0.1f;
    bool showLed_ = true, ledOnAny_ = false, down_ = false;
    juce::AudioProcessorParameter* param_ = nullptr;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (M1SoftButton)
};

//==============================================================================
// M1Joystick - the signature left-side black JOYSTICK in a square well. Two axes, each driving a REAL
// engine param: X (left/right) -> LFO1 pitch depth (vibrato/pitch mod), Y (up) -> filter cutoff
// (up = brighter). The handle is drawn as a black domed stick; dragging moves both params. The well is
// a recessed dark square with a cross-hair. X auto-recenters on release (a spring-loaded pitch axis);
// Y holds (a filter offset). Bound to lfo1Pitch (X) + cutoff (Y).
class M1Joystick  : public juce::Component,
                    private juce::AudioProcessorParameter::Listener,
                    private juce::AsyncUpdater
{
public:
    M1Joystick() = default;
    ~M1Joystick() override { if (px_) px_->removeListener (this); if (py_) py_->removeListener (this); cancelPendingUpdate(); }
    void attach (juce::AudioProcessorParameter* x, juce::AudioProcessorParameter* y)
    { px_ = x; py_ = y; if (px_) px_->addListener (this); if (py_) py_->addListener (this); triggerAsyncUpdate(); }

    void mouseDown (const juce::MouseEvent& e) override { dragging_ = true; setFromPoint (e.position); }
    void mouseDrag (const juce::MouseEvent& e) override { setFromPoint (e.position); }
    void mouseUp   (const juce::MouseEvent&)   override
    {
        dragging_ = false;
        if (px_) px_->setValueNotifyingHost (0.0f);   // spring-load the pitch axis back to centre (no LFO1 pitch)
        repaint();
    }

    void paint (juce::Graphics& g) override
    {
        auto b = getLocalBounds().toFloat().reduced (2.0f);
        const float d = juce::jmin (b.getWidth(), b.getHeight());
        auto well = juce::Rectangle<float> (0, 0, d, d).withCentre (b.getCentre());
        // recessed dark square well
        juce::ColourGradient wg (m1::kInk.darker (0.4f), well.getCentreX(), well.getY(), m1::kInk.brighter (0.25f), well.getCentreX(), well.getBottom(), false);
        g.setGradientFill (wg); g.fillRoundedRectangle (well, 4.0f);
        g.setColour (juce::Colours::black); g.drawRoundedRectangle (well, 4.0f, 1.5f);
        // cross-hair
        g.setColour (m1::kGrey.withAlpha (0.25f));
        g.drawLine (well.getCentreX(), well.getY() + 4.0f, well.getCentreX(), well.getBottom() - 4.0f, 1.0f);
        g.drawLine (well.getX() + 4.0f, well.getCentreY(), well.getRight() - 4.0f, well.getCentreY(), 1.0f);

        // handle position from params: X = lfo1Pitch (0..1 -> centre..right; bipolar look around centre),
        // Y = cutoff (0..1; up = high). Map to the inner travel area.
        const float vx = px_ ? px_->getValue() : 0.0f;   // 0 = centre rest, 1 = full right
        const float vy = py_ ? py_->getValue() : 0.5f;
        auto travel = well.reduced (d * 0.18f);
        const float hx = travel.getX() + (0.5f + vx * 0.5f) * travel.getWidth();   // rest at centre, push right
        const float hy = travel.getBottom() - vy * travel.getHeight();             // up = brighter
        // shaft
        g.setColour (juce::Colours::black.withAlpha (0.6f));
        g.drawLine (well.getCentreX(), well.getCentreY(), hx, hy, 4.0f);
        // black domed stick top
        const float kr = d * 0.16f;
        g.setColour (juce::Colours::black.withAlpha (0.45f)); g.fillEllipse (hx - kr, hy - kr + 1.5f, kr * 2.0f, kr * 2.0f);
        juce::ColourGradient kg (juce::Colour (0xff2c2c30), hx - kr * 0.4f, hy - kr * 0.5f, juce::Colour (0xff050506), hx + kr * 0.4f, hy + kr * 0.5f, true);
        g.setGradientFill (kg); g.fillEllipse (hx - kr, hy - kr, kr * 2.0f, kr * 2.0f);
        g.setColour (juce::Colours::white.withAlpha (0.20f)); g.drawEllipse (hx - kr * 0.6f, hy - kr * 0.6f, kr * 1.2f, kr * 0.9f, 1.0f);
        g.setColour (juce::Colours::black); g.drawEllipse (hx - kr, hy - kr, kr * 2.0f, kr * 2.0f, 1.0f);
    }

private:
    void setFromPoint (juce::Point<float> p)
    {
        auto b = getLocalBounds().toFloat().reduced (2.0f);
        const float d = juce::jmin (b.getWidth(), b.getHeight());
        auto well = juce::Rectangle<float> (0, 0, d, d).withCentre (b.getCentre());
        auto travel = well.reduced (d * 0.18f);
        // X: centre..right -> 0..1 lfo1Pitch (push right adds vibrato depth)
        const float nx = juce::jlimit (0.0f, 1.0f, (p.x - travel.getCentreX()) / (travel.getWidth() * 0.5f));
        const float ny = juce::jlimit (0.0f, 1.0f, (travel.getBottom() - p.y) / travel.getHeight());
        if (px_) px_->setValueNotifyingHost (nx);
        if (py_) py_->setValueNotifyingHost (ny);
        repaint();
    }
    void parameterValueChanged (int, float) override { triggerAsyncUpdate(); }
    void parameterGestureChanged (int, bool) override {}
    void handleAsyncUpdate() override { repaint(); }

    bool dragging_ = false;
    juce::AudioProcessorParameter* px_ = nullptr;
    juce::AudioProcessorParameter* py_ = nullptr;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (M1Joystick)
};

//==============================================================================
// M1Func - a flat grey-black labelled function button (RAND / SAVE), matching the soft-button look.
class M1Func  : public juce::Button
{
public:
    M1Func (const juce::String& t, juce::Colour fill) : juce::Button (t), col (fill) { setButtonText (t); }
    void flash() { flashing = true; repaint(); juce::Timer::callAfterDelay (150, [s = juce::Component::SafePointer<M1Func> (this)] { if (s) { s->flashing = false; s->repaint(); } }); }
    void paintButton (juce::Graphics& g, bool over, bool down) override
    {
        auto b = getLocalBounds().toFloat().reduced (1.0f);
        auto fill = flashing ? col.brighter (0.3f) : down ? col.darker (0.18f) : over ? col.brighter (0.08f) : col;
        g.setColour (fill); g.fillRoundedRectangle (b, 2.5f);
        g.setColour (juce::Colours::black.withAlpha (0.5f)); g.drawRoundedRectangle (b, 2.5f, 1.0f);
        g.setColour (m1::kLegend); g.setFont (toi::uiFont (juce::jmin (juce::jmin (9.5f, b.getHeight() * 0.55f), b.getWidth() * 0.3f), true));
        g.drawText (getButtonText(), getLocalBounds(), juce::Justification::centred);
    }
private:
    juce::Colour col; bool flashing = false;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (M1Func)
};

//==============================================================================
// M1Knob - the hardware control for the workstation: a dark grey-black machined dial that matches the
// soft buttons + value slider (kBtn gradient, black bezel) with fine concentric turning grooves and a
// crisp white pointer notch. Cohesive with the M1's cool-grey/dark digital surface (no metal/silver).
class M1Knob  : public juce::Component
{
public:
    M1Knob()
    {
        slider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
        slider.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
        slider.setLookAndFeel (&laf); slider.setRange (0.0, 1.0, 0.0);
        addAndMakeVisible (slider);
    }
    ~M1Knob() override { slider.setLookAndFeel (nullptr); }
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
        // drop shadow
        g.setColour (juce::Colours::black.withAlpha (0.4f)); g.fillEllipse (cx - r, cy - r + 2.0f, r * 2.0f, r * 2.0f);
        // dark grey-black domed body (matches the value slider thumb / soft buttons)
        juce::ColourGradient body (m1::kBtnHi, cx, cy - r, m1::kBtn.darker (0.35f), cx, cy + r, false);
        g.setGradientFill (body); g.fillEllipse (cx - r, cy - r, r * 2.0f, r * 2.0f);
        // black bezel
        g.setColour (m1::kInk); g.drawEllipse (cx - r, cy - r, r * 2.0f, r * 2.0f, 1.4f);
        // fine concentric machined grooves on the cap
        g.setColour (juce::Colours::black.withAlpha (0.16f));
        for (float gr = r * 0.78f; gr > r * 0.30f; gr -= 2.4f) g.drawEllipse (cx - gr, cy - gr, gr * 2.0f, gr * 2.0f, 0.7f);
        // faint top sheen
        { const float sr = r * 0.62f, sx = cx - r * 0.22f, sy = cy - r * 0.30f;
          juce::ColourGradient gl (juce::Colours::white.withAlpha (0.16f), sx, sy, juce::Colours::white.withAlpha (0.0f), sx + sr, sy + sr, true);
          g.setGradientFill (gl); g.fillEllipse (sx - sr, sy - sr, sr * 2.0f, sr * 2.0f); }
        // crisp white pointer notch from the cap toward the rim
        g.setColour (m1::kLegend.withAlpha (0.95f));
        g.drawLine (cx + dx * r * 0.34f, cy + dy * r * 0.34f, cx + dx * (r - 2.5f), cy + dy * (r - 2.5f), juce::jmax (2.0f, r * 0.13f));
    }
    juce::Slider slider;
private:
    toi::InvisibleRotaryLAF laf;
    std::unique_ptr<toi::ParamKnobAttachment> att;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (M1Knob)
};

//==============================================================================
inline toi::Config jwm1Config()
{
    toi::Config c;
    c.model = "JW-M1";
    auto& p = c.pal;
    p.bg = m1::kGrey; p.bg2 = m1::kGreyLo; p.frame = m1::kShell; p.ink = m1::kInk;
    p.accent = m1::kAccent; p.accent2 = m1::kRedLed; p.button = m1::kBtn;
    p.thumb = m1::kBtnHi; p.text = m1::kInk;
    p.noteStrip = m1::kGreyLo;
    p.lcdBg = m1::kLcdField; p.lcdInk = m1::kLcdInk;
    p.keyWhite = juce::Colour (0xfff0f1f1); p.keyWhitePr = m1::kAccent; p.keyBlack = juce::Colour (0xff1c1d1e); p.keyBlackPr = m1::kRedLed;

    // EXACT engine param ids/order (M1.cmajor ParamsProcessor).
    c.params = {
        { "multi1","MULTI 1" },{ "multi2","MULTI 2" },{ "dbl","DOUBLE" },{ "detune","DETUNE" },{ "osc2Oct","OSC2 OCT" },{ "oscMix","OSC MIX" },
        { "cutoff","CUTOFF" },{ "reso","RESO" },{ "vdfEnv","VDF ENV" },{ "vdfKbd","VDF KBD" },
        { "aA","A" },{ "aD","D" },{ "aS","S" },{ "aR","R" },
        { "fA","A" },{ "fD","D" },{ "fS","S" },{ "fR","R" },
        { "pEnvAmt","P.ENV" },{ "pEnvDecay","P.DEC" },{ "glide","GLIDE" },
        { "lfo1Rate","LFO1 RT" },{ "lfo1Pitch","LFO1 PIT" },{ "lfo2Rate","LFO2 RT" },{ "lfo2Filter","LFO2 FLT" },
        { "grain","GRAIN" },{ "volume","VOLUME" },{ "tune","TUNE" },
        { "fxRouting","ROUTING" },{ "chorus","FX A" },{ "delay","FX B" },{ "delayTime","FX TIME" },{ "delayFb","FX FB" },{ "reverb","REVERB" },
    };

    // engine init defaults (mirrors M1.cmajor init: values are already 0..1 real units)
    std::vector<float> base = {
        0.0f,0.57f,0.0f,0.52f,0.50f,0.50f,
        0.72f,0.0f,0.40f,0.40f,
        0.02f,0.50f,0.70f,0.30f,
        0.04f,0.45f,0.40f,0.35f,
        0.50f,0.20f,0.0f,
        0.35f,0.0f,0.28f,0.0f,
        0.30f,0.80f,0.50f,
        0.0f,0.50f,0.30f,0.38f,0.35f,0.45f };

    enum { MULTI1,MULTI2,DBL,DETUNE,O2OCT,OMIX, CUT,RES,VENV,VKBD, AA,AD,AS,AR, FA,FD,FS,FR,
           PENV,PDEC,GLIDE, L1R,L1P,L2R,L2F, GRAIN,VOL,TUNE, ROUT,CHO,DLY,DTIME,DFB,REV };
    auto P = [&] (const char* nm, std::initializer_list<std::pair<int,float>> ov)
    { auto v = base; for (auto& o : ov) v[(size_t) o.first] = o.second; return toi::FactoryPreset { nm, v }; };

    c.factory = {
        P("INIT",          {}),
        P("HOUSE STAB",    {{MULTI1,0.0f},{CUT,0.85f},{VENV,0.5f},{AA,0.0f},{AD,0.32f},{AS,0.4f},{AR,0.18f},{CHO,0.33f},{REV,0.4f}}),
        P("UNIVERSE PAD",  {{MULTI1,0.57f},{DBL,1.0f},{MULTI2,0.0f},{DETUNE,0.6f},{AA,0.45f},{AS,0.85f},{AR,0.7f},{CUT,0.6f},{CHO,0.66f},{REV,0.7f},{DLY,0.4f}}),
        P("E.PIANO",       {{MULTI1,0.14f},{CUT,0.7f},{AA,0.0f},{AD,0.55f},{AS,0.45f},{AR,0.35f},{CHO,0.33f},{REV,0.35f}}),
        P("DRAWBAR ORG",   {{MULTI1,0.29f},{CUT,0.78f},{AA,0.02f},{AD,0.4f},{AS,0.85f},{AR,0.15f},{CHO,0.0f},{REV,0.3f}}),
        P("BELL UNIVERSE", {{MULTI1,0.57f},{DBL,1.0f},{MULTI2,0.57f},{O2OCT,0.75f},{AA,0.0f},{AD,0.6f},{AS,0.3f},{AR,0.5f},{REV,0.66f},{DLY,0.4f}}),
        P("VOX CHOIR",     {{MULTI1,0.43f},{AA,0.4f},{AS,0.8f},{AR,0.6f},{CUT,0.6f},{CHO,0.66f},{REV,0.66f}}),
        P("BRASS SECTION", {{MULTI1,0.71f},{CUT,0.62f},{VENV,0.6f},{AA,0.12f},{AD,0.4f},{AS,0.7f},{AR,0.3f},{CHO,0.33f}}),
        P("FINGER BASS",   {{MULTI1,0.86f},{CUT,0.5f},{AA,0.0f},{AD,0.35f},{AS,0.45f},{AR,0.2f},{CHO,0.0f},{REV,0.2f}}),
        P("DIGITAL SCAPE", {{MULTI1,1.0f},{DBL,1.0f},{MULTI2,1.0f},{DETUNE,0.6f},{AA,0.3f},{AS,0.7f},{AR,0.7f},{CUT,0.7f},{DLY,0.5f},{REV,0.7f}}),
        P("GLIDE LEAD",    {{MULTI1,0.86f},{GLIDE,0.3f},{CUT,0.7f},{RES,0.25f},{AA,0.02f},{AS,0.8f},{L1P,0.3f},{CHO,0.33f}}),
        P("RESO SWEEP",    {{MULTI1,0.71f},{CUT,0.45f},{RES,0.5f},{VENV,0.8f},{FA,0.04f},{FD,0.5f},{AS,0.7f},{REV,0.5f}}),
    };
    return c;
}

//==============================================================================
class JWM1Editor  : public toi::PanelEditor
{
public:
    JWM1Editor (juce::AudioProcessor& proc, juce::MidiKeyboardState& kb)
        : toi::PanelEditor (proc, kb, jwm1Config())
    {
        // ---- the small square grey-black soft-button KNOB-PANEL (every control drives a real param) ----
        // editing knobs are grouped; the M1's surface is mostly square buttons + the value slider, so we
        // use small soft buttons to step the values, plus a compact knob band for continuous controls.
        knobGroups_ = {
            { "OSC", { "multi2","detune","osc2Oct","oscMix" } },
            { "VDF", { "cutoff","reso","vdfEnv","vdfKbd" } },
            { "VDA EG", { "aA","aD","aS","aR" } },
            { "VDF EG", { "fA","fD","fS","fR" } },
            { "PITCH/LFO", { "pEnvAmt","pEnvDecay","glide","lfo1Rate","lfo2Rate","lfo2Filter" } },
            { "FX", { "delayTime","delayFb","reverb","grain","volume","tune" } },
        };
        for (auto& grp : knobGroups_) for (auto& id : grp.ids) addKnob (id);

        // ---- the signature wide character LCD (multisound + dual-FX workflow + live scope) ----
        lcd_ = std::make_unique<M1Lcd>();
        lcd_->attachScope (audioTap());
        lcd_->setSources (findParam ("multi1"), findParam ("dbl"), findParam ("fxRouting"), findParam ("chorus"), findParam ("delay"));
        lcd_->watch ({ findParam ("multi1"), findParam ("dbl"), findParam ("fxRouting"), findParam ("chorus"), findParam ("delay") });
        addAndMakeVisible (*lcd_);

        // ---- the VALUE slider (scrolls the multisound = multi1) + up/down nudge buttons ----
        value_ = std::make_unique<M1ValueSlider>();
        if (auto* prm = findParam ("multi1")) value_->attach (*prm);
        addAndMakeVisible (*value_);
        valUp_   = std::make_unique<M1SoftButton> ("\xe2\x96\xb2", 2, M1SoftButton::NudgeUp);
        valDown_ = std::make_unique<M1SoftButton> ("\xe2\x96\xbc", 2, M1SoftButton::NudgeDown);
        for (auto* nb : { valUp_.get(), valDown_.get() }) { nb->setStep (1.0f / 7.0f); nb->setShowLed (false); if (auto* prm = findParam ("multi1")) nb->attach (prm); }
        addAndMakeVisible (*valUp_); addAndMakeVisible (*valDown_);

        // ---- the left JOYSTICK well (X -> LFO1 pitch / vibrato, Y up -> filter cutoff) ----
        joystick_ = std::make_unique<M1Joystick>();
        joystick_->attach (findParam ("lfo1Pitch"), findParam ("cutoff"));
        addAndMakeVisible (*joystick_);

        // ---- mode bank (square soft buttons): the signature COMBI/PROG/SEQ/GLOBAL/EDIT/BANK row.
        // v1 = single PROGRAM (SEQ/COMBI stubbed) so these step real params that exist: DOUBLE + ROUTING
        // and a few that toggle the engine. We wire the two that ARE the workflow (DOUBLE, ROUTING) to
        // real params; the rest are inert mode labels (drawn but not bound) - kept sparse + honest.
        dblBtn_  = std::make_unique<M1SoftButton> ("DOUBLE", 2, M1SoftButton::Cycle);
        if (auto* prm = findParam ("dbl")) dblBtn_->attach (prm);
        dblBtn_->setLedOnAny (true);
        addAndMakeVisible (*dblBtn_);

        routBtn_ = std::make_unique<M1SoftButton> ("ROUTING", 2, M1SoftButton::Cycle);
        if (auto* prm = findParam ("fxRouting")) routBtn_->attach (prm);
        routBtn_->setLedOnAny (true);
        addAndMakeVisible (*routBtn_);

        // ---- the two FX-swap soft buttons (the OTHER half of the workflow): cycle FX A / FX B slots ----
        fxA_ = std::make_unique<M1SoftButton> ("FX A", 4, M1SoftButton::Cycle);
        if (auto* prm = findParam ("chorus")) fxA_->attach (prm);
        fxA_->setShowLed (false);
        addAndMakeVisible (*fxA_);
        fxB_ = std::make_unique<M1SoftButton> ("FX B", 4, M1SoftButton::Cycle);
        if (auto* prm = findParam ("delay")) fxB_->attach (prm);
        fxB_->setShowLed (false);
        addAndMakeVisible (*fxB_);

        // ---- preset slots (the bank pad) + RAND/SAVE ----
        for (int i = 0; i < 16; ++i)
        { auto b = std::make_unique<toi::MoldedButton> (juce::Colour (0xffe9e6df)); b->setLit (juce::Colour (0xff2f6fd0)); const int idx = i; b->onClick = [this, idx] { recallSlot (idx); }; addAndMakeVisible (*b); slots_.push_back (std::move (b)); }
        rand_ = std::make_unique<M1Func> ("RAND", m1::kBtn.brighter (0.1f)); save_ = std::make_unique<M1Func> ("SAVE", m1::kRedLed.darker (0.15f));
        rand_->onClick = [this] { doRandom(); rand_->flash(); };
        save_->onClick = [this] { saveSlot (activeSlot()); save_->flash(); };
        addAndMakeVisible (*rand_); addAndMakeVisible (*save_);

        finishSetup();
    }

protected:
    void setPresetActiveVisual (int idx) override { for (int i = 0; i < (int) slots_.size(); ++i) slots_[(size_t) i]->setActive (i == idx); }

    void paintPanel (juce::Graphics& g, juce::Rectangle<float> panel) override
    {
        rPanel_ = panel;
        // matte black shell border already drawn by the chassis; the cool-grey surface is the bg.
        // flat cool-grey control surface with a very faint top sheen (matte, no metal/wood)
        juce::ColourGradient pg (m1::kGreyHi, panel.getCentreX(), panel.getY(), m1::kGreyLo, panel.getCentreX(), panel.getBottom(), false);
        g.setGradientFill (pg); g.fillRoundedRectangle (panel, 5.0f);
        // subtle matte speckle noise overlay for a moulded-plastic feel
        if (grain_.isValid()) { g.setOpacity (1.0f); g.setFillType (juce::FillType (grain_, juce::AffineTransform::translation (panel.getX(), panel.getY()))); g.fillRoundedRectangle (panel, 5.0f); }
        g.setColour (m1::kInk); g.drawRoundedRectangle (panel, 5.0f, 1.5f);

        // section boxes + labels for the knob band
        for (auto& grp : knobGroups_) drawGroupBox (g, grp);

        // JOYSTICK well label + VOLUME area legend (left column)
        g.setColour (m1::kText); g.setFont (toi::uiFont (7.0f, true).withExtraKerningFactor (0.08f));
        g.drawText ("JOYSTICK", juce::Rectangle<float> (rJoy_.getX(), rJoy_.getBottom() + 1.0f, rJoy_.getWidth(), 9.0f), juce::Justification::centred);
        g.setColour (m1::kDim); g.setFont (toi::uiFont (5.5f, true));
        g.drawText ("X:PITCH  Y:FILTER", juce::Rectangle<float> (rJoy_.getX() - 6.0f, rJoy_.getBottom() + 9.0f, rJoy_.getWidth() + 12.0f, 8.0f), juce::Justification::centred);

        // LCD label
        g.setColour (m1::kText); g.setFont (toi::uiFont (7.0f, true).withExtraKerningFactor (0.1f));
        g.drawText ("MULTISOUND  /  DUAL  FX", juce::Rectangle<float> (rLcd_.getX(), rLcd_.getY() - 9.0f, rLcd_.getWidth(), 9.0f), juce::Justification::centredLeft);

        // VALUE slider label
        g.setColour (m1::kText); g.setFont (toi::uiFont (6.5f, true));
        g.drawText ("VALUE", juce::Rectangle<float> (rValue_.getX() - 8.0f, rValue_.getY() - 10.0f, rValue_.getWidth() + 16.0f, 9.0f), juce::Justification::centred);

        // mode bank legend + FX legends
        g.setColour (m1::kDim); g.setFont (toi::uiFont (5.5f, true));
        g.drawText ("MODE", juce::Rectangle<float> (rMode_.getX(), rMode_.getY() - 9.0f, 120.0f, 9.0f), juce::Justification::centredLeft);
        g.drawText ("FX  SWAP", juce::Rectangle<float> (rFx_.getX(), rFx_.getY() - 9.0f, 120.0f, 9.0f), juce::Justification::centredLeft);
        // PRESET label
        g.drawText ("PRESET", juce::Rectangle<float> (rPreset_.getX(), rPreset_.getY() - 9.0f, 120.0f, 9.0f), juce::Justification::centredLeft);

        // brand + view LEDs (top-right block, leave a gap under the LED row per toi-brand-block-spacing)
        auto bh = rBrand_;
        drawViewLeds (g, bh.removeFromTop (22.0f));
        bh.removeFromTop (4.0f);
        g.setColour (m1::kText); g.setFont (toi::uiFont (15.0f, true));
        g.drawText ("JW-M1", bh.removeFromTop (18.0f), juce::Justification::centred);
        g.setColour (m1::kDim); g.setFont (toi::uiFont (6.0f, true).withExtraKerningFactor (0.2f));
        g.drawText ("AI  WORKSTATION", bh, juce::Justification::centred);
    }

    void layoutPanel (juce::Rectangle<float> panel) override
    {
        rPanel_ = panel;
        if (! grain_.isValid()) grain_ = makeSpeckle (220, 160);
        auto inner = panel.reduced (12.0f, 8.0f);

        // ---- LEFT COLUMN: joystick well over the VALUE area separator ----
        auto left = inner.removeFromLeft (118.0f);
        inner.removeFromLeft (10.0f);
        {
            left.removeFromTop (4.0f);
            auto js = left.removeFromTop (108.0f).reduced (10.0f, 0.0f);
            rJoy_ = js;
            placeInArtboard (*joystick_, rJoy_);
        }

        // ---- TOP-RIGHT: brand block ----
        rBrand_ = juce::Rectangle<float> (inner.getRight() - 118.0f, inner.getY(), 118.0f, 64.0f);

        // ---- LCD + VALUE slider band (top of the main area, leaving room for the brand at right) ----
        auto top = inner.removeFromTop (64.0f);
        top.removeFromTop (10.0f);   // headroom under the LCD label
        top.removeFromRight (124.0f);   // brand block reservation
        // VALUE slider sits at the right edge of the LCD band with up/down nudge buttons
        auto valCol = top.removeFromRight (52.0f);
        rValue_ = valCol.removeFromTop (40.0f).reduced (10.0f, 0.0f);
        placeInArtboard (*value_, rValue_);
        // up/down under the slider
        {
            auto nb = valCol.reduced (4.0f, 0.0f);
            const float bw = (nb.getWidth() - 3.0f) * 0.5f;
            placeInArtboard (*valUp_,   juce::Rectangle<float> (nb.getX(), nb.getY(), bw, nb.getHeight()));
            placeInArtboard (*valDown_, juce::Rectangle<float> (nb.getX() + bw + 3.0f, nb.getY(), bw, nb.getHeight()));
        }
        top.removeFromRight (8.0f);
        rLcd_ = top;
        placeInArtboard (*lcd_, rLcd_);
        inner.removeFromTop (6.0f);

        // ---- KNOB BAND: two rows of compact knob groups ----
        const int nGroups = (int) knobGroups_.size();
        const int rowGroups = (nGroups + 1) / 2;
        auto knobArea = inner.removeFromTop (130.0f);
        auto rowTop = knobArea.removeFromTop (knobArea.getHeight() * 0.5f - 2.0f);
        knobArea.removeFromTop (4.0f);
        auto rowBot = knobArea;
        layoutGroupRow (rowTop, 0, rowGroups);
        layoutGroupRow (rowBot, rowGroups, nGroups);
        inner.removeFromTop (4.0f);

        // ---- BOTTOM STRIP (over the left column too): mode + FX swap | presets | RAND/SAVE ----
        auto strip = juce::Rectangle<float> (panel.getX() + 12.0f, inner.getY(), panel.getWidth() - 24.0f, panel.getBottom() - inner.getY() - 8.0f);
        strip.removeFromTop (10.0f);   // labels headroom

        // mode bank (DOUBLE + ROUTING) at far left
        rMode_ = strip.removeFromLeft (150.0f);
        {
            auto mb = rMode_; const float bw = (mb.getWidth() - 6.0f) * 0.5f;
            placeInArtboard (*dblBtn_,  juce::Rectangle<float> (mb.getX(), mb.getY(), bw, juce::jmin (28.0f, mb.getHeight())));
            placeInArtboard (*routBtn_, juce::Rectangle<float> (mb.getX() + bw + 6.0f, mb.getY(), bw, juce::jmin (28.0f, mb.getHeight())));
        }
        strip.removeFromLeft (10.0f);
        // FX swap pair
        rFx_ = strip.removeFromLeft (130.0f);
        {
            auto fb = rFx_; const float bw = (fb.getWidth() - 6.0f) * 0.5f;
            placeInArtboard (*fxA_, juce::Rectangle<float> (fb.getX(), fb.getY(), bw, juce::jmin (28.0f, fb.getHeight())));
            placeInArtboard (*fxB_, juce::Rectangle<float> (fb.getX() + bw + 6.0f, fb.getY(), bw, juce::jmin (28.0f, fb.getHeight())));
        }
        strip.removeFromLeft (14.0f);

        // RAND/SAVE at far right - two square buttons side by side (Jade)
        const float rsSq = juce::jmin (strip.getHeight(), 32.0f);
        auto rs = strip.removeFromRight (rsSq * 2.0f + 6.0f);
        {
            auto rsi = rs.withSizeKeepingCentre (rsSq * 2.0f + 6.0f, rsSq);
            placeInArtboard (*rand_, rsi.removeFromLeft (rsSq));
            rsi.removeFromLeft (6.0f);
            placeInArtboard (*save_, rsi.removeFromLeft (rsSq));
        }
        strip.removeFromRight (10.0f);
        // PRESET pad = ONE row of 16, spread evenly across the middle (no overlap)
        rPreset_ = strip;
        { const int pc = 16; const float pgap = 4.0f;
          const float pw = (rPreset_.getWidth() - pgap * (pc - 1)) / (float) pc;
          const float ph = juce::jmin (rPreset_.getHeight() - 2.0f, 18.0f);
          const float py = rPreset_.getY() + (rPreset_.getHeight() - ph) * 0.5f;
          for (int i = 0; i < 16; ++i) placeInArtboard (*slots_[(size_t) i], juce::Rectangle<float> (rPreset_.getX() + (float) i * (pw + pgap), py, pw, ph)); }
    }

private:
    struct Group { juce::String name; std::vector<juce::String> ids; juce::Rectangle<float> rect; };

    void addKnob (const juce::String& id)
    {
        // dark grey-black machined M1 dial (matches the soft buttons + value slider)
        auto k = std::make_unique<M1Knob>();
        if (auto* prm = findParam (id)) k->attach (*prm);
        addAndMakeVisible (*k); knobMap_[id] = k.get(); knobs_.push_back (std::move (k));
    }
    M1Knob* knobFor (const juce::String& id) const { auto it = knobMap_.find (id); return it == knobMap_.end() ? nullptr : it->second; }

    void layoutGroupRow (juce::Rectangle<float> row, int from, int to)
    {
        int n = 0; for (int gi = from; gi < to; ++gi) n += (int) knobGroups_[(size_t) gi].ids.size();
        if (n == 0) return;
        const float gap = 8.0f;
        const float usable = row.getWidth() - gap * (float) (to - from - 1);
        const float kw = usable / (float) n;
        float x = row.getX();
        for (int gi = from; gi < to; ++gi)
        {
            auto& grp = knobGroups_[(size_t) gi];
            const float gwidth = kw * (float) grp.ids.size();
            grp.rect = juce::Rectangle<float> (x, row.getY(), gwidth, row.getHeight());
            for (int i = 0; i < (int) grp.ids.size(); ++i)
                if (auto* k = knobFor (grp.ids[(size_t) i]))
                { auto cell = juce::Rectangle<float> (x + (float) i * kw, row.getY() + 11.0f, kw, row.getHeight() - 20.0f).reduced (2.0f, 0.0f);
                  placeInArtboard (*k, cell.withSizeKeepingCentre (juce::jmin (cell.getWidth(), cell.getHeight()), juce::jmin (cell.getWidth(), cell.getHeight()))); }
            x += gwidth + gap;
        }
    }

    void drawGroupBox (juce::Graphics& g, const Group& grp)
    {
        if (grp.rect.isEmpty()) return;
        g.setColour (juce::Colour (0x18000000)); g.fillRoundedRectangle (grp.rect, 3.0f);
        g.setColour (m1::kInk.withAlpha (0.5f)); g.drawRoundedRectangle (grp.rect, 3.0f, 1.0f);
        g.setColour (m1::kText); g.setFont (toi::uiFont (7.0f, true).withExtraKerningFactor (0.06f));
        g.drawText (grp.name, grp.rect.withHeight (10.0f).reduced (4.0f, 1.0f), juce::Justification::centredLeft);
        const float kw = grp.rect.getWidth() / (float) grp.ids.size();
        for (int i = 0; i < (int) grp.ids.size(); ++i)
        {
            juce::String lbl; for (auto& sp : config().params) if (sp.id == grp.ids[(size_t) i]) { lbl = sp.label; break; }
            g.setColour (m1::kDim); g.setFont (toi::uiFont (5.5f, true));
            g.drawText (lbl, juce::Rectangle<float> (grp.rect.getX() + (float) i * kw, grp.rect.getBottom() - 9.0f, kw, 8.0f), juce::Justification::centred);
        }
    }

    // matte moulded-plastic speckle (very subtle, dark + light grey flecks at low alpha)
    static juce::Image makeSpeckle (int w, int h)
    {
        juce::Image img (juce::Image::ARGB, w, h, true);
        juce::Random r (771);
        for (int y = 0; y < h; ++y) for (int x = 0; x < w; ++x)
        {
            const float n = r.nextFloat();
            if (n > 0.88f)      img.setPixelAt (x, y, juce::Colours::white.withAlpha ((n - 0.88f) / 0.12f * 0.06f));
            else if (n < 0.06f) img.setPixelAt (x, y, juce::Colours::black.withAlpha (0.05f));
        }
        return img;
    }

    std::vector<std::unique_ptr<M1Knob>> knobs_;
    std::map<juce::String, M1Knob*> knobMap_;
    std::unique_ptr<M1Lcd> lcd_;
    std::unique_ptr<M1ValueSlider> value_;
    std::unique_ptr<M1SoftButton> valUp_, valDown_, dblBtn_, routBtn_, fxA_, fxB_;
    std::unique_ptr<M1Joystick> joystick_;
    std::vector<std::unique_ptr<toi::MoldedButton>> slots_;
    std::unique_ptr<M1Func> rand_, save_;
    std::vector<Group> knobGroups_;
    juce::Image grain_;
    juce::Rectangle<float> rPanel_, rJoy_, rLcd_, rValue_, rMode_, rFx_, rPreset_, rBrand_;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JWM1Editor)
};

//==============================================================================
class JWM1Plugin  : public cmaj::plugin::GeneratedPlugin<::JWM1>,
                    public toi::AudioTapSource,
                    public toi::PresetStore
{
public:
    using Base = cmaj::plugin::GeneratedPlugin<::JWM1>;
    JWM1Plugin (std::shared_ptr<cmaj::Patch> p) : Base (std::move (p)) {}
    juce::AudioProcessorEditor* createEditor() override { return new JWM1Editor (*this, keyboardState); }
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
