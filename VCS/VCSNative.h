// JW-VCS native faceplate (British pin-matrix modular-in-a-box) on the toi_faceplate.h kit.
// Traces the EMS VCS3 "Putney": an L-shaped AFRORMOSIA wood console with a warm off-white /
// "duck-egg" cream laminate facing, BLACK silkscreen, and the iconic GLOSSY 3D concentric EMS knobs
// (a coloured translucent-bakelite outer dome + a raised ivory centre cap + a thin pointer; blue =
// frequency/cutoff, green = shape, red = envelope shaper, cream = everything else). Layout is a 2D
// GRID: the THREE OSCILLATORS are STACKED as three rows (each = FREQ + SHAPE + the rest + a RANGE
// toggle), with the FILTER / ENVELOPE SHAPER / REVERB / OUTPUT modules as compact boxes to the right.
// The lower-left holds the 2-axis JOYSTICK, a live VU METER and -- the whole point -- THE 16x16 PIN
// MATRIX you click to drop coloured pins (RED/WHITE = full level, GREEN = attenuating) which re-route
// the modular. NO brand names.
#pragma once

#include "toi_faceplate.h"

struct JWVCS;

namespace vcs
{
    static const juce::Colour kCream  { 0xffc8ccd2 };   // brushed SILVER panel (Jade: silver, not cream) - light
    static const juce::Colour kCreamLo{ 0xffa7abb2 };   // brushed silver - darker (vertical gradient bottom)
    static const juce::Colour kInk     { 0xff1a1813 };   // black silkscreen
    static const juce::Colour kDim     { 0xff595144 };
    static const juce::Colour kWood    { 0xff7a4a23 };   // afrormosia wood console
    static const juce::Colour kWoodD   { 0xff4f2e12 };
    static const juce::Colour kMatrix  { 0xff20201c };   // the dark matrix board recess
    static const juce::Colour kHole    { 0xff0e0e0a };   // empty pin hole
    static const juce::Colour kHoleRim { 0xff8c8470 };   // cream rim of the hole grid
    static const juce::Colour kPinRed  { 0xffc8392a };   // pin: full level
    static const juce::Colour kPinWhite{ 0xfff0ead8 };   // pin: full level (white variant)
    static const juce::Colour kPinGreen{ 0xff4f9a52 };   // pin: attenuating
    static const juce::Colour kJoyWell { 0xff211f1a };   // joystick well
}

//==============================================================================
// VcsPinMatrix - THE signature control. A 16x16 grid of holes. ROWS = sources, COLUMNS = dests.
// 15 of the cells are "live" -> each wired to one of the engine's matrix-coefficient params. Click a
// live hole to CYCLE the pin: empty -> RED(full ~1.0) -> WHITE(full ~1.0) -> GREEN(atten ~0.25) ->
// empty. Each pin SETS its routing param, so the matrix genuinely re-patches the modular (a column
// sums its pins in the engine). Non-wired holes are decorative dark holes (the real VCS3 has the
// full grid but only certain crosspoints make sense). This widget OWNS no value of its own - it
// reflects + drives the real params, so it stays in sync with presets / host automation.
class VcsPinMatrix  : public juce::Component,
                      private juce::AudioProcessorParameter::Listener,
                      private juce::AsyncUpdater
{
public:
    static constexpr int ROWS = 10, COLS = 16;   // 10 sources x 16 dests = 160 live crosspoints (dense real patchboard)

    struct Cell { int row, col; juce::AudioProcessorParameter* param; };

    VcsPinMatrix() = default;
    ~VcsPinMatrix() override { for (auto& c : cells_) if (c.param) c.param->removeListener (this); cancelPendingUpdate(); }

    // wire a live crosspoint (row,col) to a matrix param
    void addPin (int row, int col, juce::AudioProcessorParameter* p)
    {
        cells_.push_back ({ row, col, p });
        if (p) p->addListener (this);
        triggerAsyncUpdate();
    }

    // map a 0..1 coefficient to a pin colour state: 0=empty 1=red 2=white 3=green
    static int stateFor (float v)
    {
        if (v < 0.04f)  return 0;          // empty
        if (v > 0.55f)  return 1;          // RED (full)  -- the default "full level" colour
        return 3;                          // GREEN (attenuating ~0.1-0.3)
    }
    // value the engine should get for a pin state
    static float valueFor (int state)
    {
        switch (state)
        {
            case 1: return 1.00f;   // RED   = full
            case 2: return 0.85f;   // WHITE = full (slightly under to read distinct)
            case 3: return 0.22f;   // GREEN = attenuating
            default: return 0.0f;   // empty
        }
    }

    void resized() override { layout(); }

    void mouseDown (const juce::MouseEvent& e) override
    {
        // hit-test the live cells
        for (auto& c : cells_)
        {
            if (! c.param) continue;
            if (cellRect (c.row, c.col).contains (e.position))
            {
                const int cur = displayState (*c.param);
                const int nxt = (cur + 1) % 4;   // empty -> red -> white -> green -> empty
                c.param->beginChangeGesture();
                c.param->setValueNotifyingHost (valueFor (nxt));
                c.param->endChangeGesture();
                repaint();
                return;
            }
        }
    }

    // RAND: drop a fresh random patch into the matrix (clears, guarantees a sounding path, then random pins)
    void randomize()
    {
        juce::Random rng ((juce::int64) juce::Time::getHighResolutionTicks());
        auto setrc = [this] (int row, int col, float v)
        {
            for (auto& c : cells_)
                if (c.row == row && c.col == col && c.param)
                    c.param->setValueNotifyingHost (juce::jlimit (0.0f, 1.0f, v));
        };
        for (auto& c : cells_) if (c.param) c.param->setValueNotifyingHost (0.0f);   // clear all 160
        setrc (rng.nextInt (3), 4, valueFor (1));   // an oscillator -> FILTER-IN  (so it sounds)
        setrc (5, 7, valueFor (1));                 // FILTER -> OUTPUT
        const int extra = 6 + rng.nextInt (8);      // a handful of random pins = a real VCS3 random patch
        for (int i = 0; i < extra; ++i)
            setrc (rng.nextInt (ROWS), rng.nextInt (COLS), valueFor (1 + rng.nextInt (3)));
        repaint();
    }

    void paint (juce::Graphics& g) override
    {
        auto b = getLocalBounds().toFloat();
        // matrix board recess
        g.setColour (vcs::kMatrix); g.fillRoundedRectangle (b, 4.0f);
        g.setColour (juce::Colours::black.withAlpha (0.6f)); g.drawRoundedRectangle (b, 4.0f, 1.4f);

        layout();

        // all 10x8 holes - EVERY one is a live crosspoint now
        for (int r = 0; r < ROWS; ++r)
            for (int c = 0; c < COLS; ++c)
            {
                auto cr = cellRect (r, c);
                const float hr = juce::jmin (cr.getWidth(), cr.getHeight()) * 0.40f;
                auto centre = cr.getCentre();
                g.setColour (vcs::kHole);
                g.fillEllipse (centre.x - hr, centre.y - hr, hr * 2.0f, hr * 2.0f);
                g.setColour (vcs::kHoleRim.withAlpha (0.55f));
                g.drawEllipse (centre.x - hr, centre.y - hr, hr * 2.0f, hr * 2.0f, 0.9f);
            }

        // mark the LIVE (clickable) crosspoints with a bright rim even when empty, so the matrix reads
        // as a real patch bay you can plug into (not a dead decorative grid of holes)
        for (auto& c : cells_)
        {
            if (! c.param) continue;
            auto cr = cellRect (c.row, c.col); auto ctr = cr.getCentre();
            const float hr = juce::jmin (cr.getWidth(), cr.getHeight()) * 0.44f;
            g.setColour (vcs::kHoleRim.withAlpha (0.9f));
            g.drawEllipse (ctr.x - hr, ctr.y - hr, hr * 2.0f, hr * 2.0f, 1.2f);
        }

        // the LIVE pins on top (coloured peg + a little highlight)
        for (auto& c : cells_)
        {
            if (! c.param) continue;
            const int st = displayState (*c.param);
            if (st == 0) continue;
            auto cr = cellRect (c.row, c.col);
            auto centre = cr.getCentre();
            const float pr = juce::jmin (cr.getWidth(), cr.getHeight()) * 0.40f;
            const juce::Colour col = st == 1 ? vcs::kPinRed : st == 2 ? vcs::kPinWhite : vcs::kPinGreen;
            g.setColour (juce::Colours::black.withAlpha (0.45f));
            g.fillEllipse (centre.x - pr, centre.y - pr + 1.2f, pr * 2.0f, pr * 2.0f);
            juce::ColourGradient pg (col.brighter (0.35f), centre.x - pr * 0.4f, centre.y - pr * 0.5f,
                                     col.darker (0.25f), centre.x + pr, centre.y + pr, false);
            g.setGradientFill (pg);
            g.fillEllipse (centre.x - pr, centre.y - pr, pr * 2.0f, pr * 2.0f);
            g.setColour (juce::Colours::white.withAlpha (0.4f));
            g.fillEllipse (centre.x - pr * 0.4f, centre.y - pr * 0.5f, pr * 0.5f, pr * 0.5f);
        }
    }

    // expose cell geometry for the editor to draw row/col labels in the right margins
    juce::Rectangle<float> cellRect (int row, int col) const
    {
        return { x0_ + (float) col * stepX_, y0_ + (float) row * stepY_, stepX_, stepY_ };
    }
    float gridX0() const { return x0_; }
    float gridY0() const { return y0_; }
    float gridStepX() const { return stepX_; }
    float gridStepY() const { return stepY_; }

private:
    void layout()
    {
        // FILL the whole black box - separate x/y steps so the dots spread edge to edge, no dead space
        auto b = getLocalBounds().toFloat().reduced (5.0f);
        stepX_ = b.getWidth()  / (float) COLS;
        stepY_ = b.getHeight() / (float) ROWS;
        x0_ = b.getX();
        y0_ = b.getY();
    }
    int displayState (juce::AudioProcessorParameter& p) const { return stateFor (p.getValue()); }

    void parameterValueChanged (int, float) override { triggerAsyncUpdate(); }
    void parameterGestureChanged (int, bool) override {}
    void handleAsyncUpdate() override { repaint(); }

    std::vector<Cell> cells_;
    float x0_ = 0.0f, y0_ = 0.0f, stepX_ = 1.0f, stepY_ = 1.0f;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VcsPinMatrix)
};

//==============================================================================
// VcsJoystick - the VCS3 2-axis joystick in a square well. Drag the puck -> sets joyX (X) and
// joyY (Y), both 0..1 (centre = 0.5). Both axes are real matrix SOURCES in the engine.
class VcsJoystick  : public juce::Component,
                     private juce::AudioProcessorParameter::Listener,
                     private juce::AsyncUpdater
{
public:
    VcsJoystick() = default;
    ~VcsJoystick() override { if (px_) px_->removeListener (this); if (py_) py_->removeListener (this); cancelPendingUpdate(); }
    void setParams (juce::AudioProcessorParameter* x, juce::AudioProcessorParameter* y)
    { px_ = x; py_ = y; if (px_) px_->addListener (this); if (py_) py_->addListener (this); triggerAsyncUpdate(); }

    void mouseDown (const juce::MouseEvent& e) override { drag (e); }
    void mouseDrag (const juce::MouseEvent& e) override { drag (e); }

    void paint (juce::Graphics& g) override
    {
        auto b = getLocalBounds().toFloat();
        // square well
        g.setColour (vcs::kJoyWell); g.fillRoundedRectangle (b, 4.0f);
        g.setColour (juce::Colours::black.withAlpha (0.6f)); g.drawRoundedRectangle (b, 4.0f, 1.4f);
        auto a = pad();
        // cross-hairs
        g.setColour (vcs::kHoleRim.withAlpha (0.25f));
        g.drawLine (a.getCentreX(), a.getY(), a.getCentreX(), a.getBottom(), 0.8f);
        g.drawLine (a.getX(), a.getCentreY(), a.getRight(), a.getCentreY(), 0.8f);
        // puck at (x,y)
        const float vx = px_ ? px_->getValue() : 0.5f;
        const float vy = py_ ? py_->getValue() : 0.5f;
        const float cx = a.getX() + vx * a.getWidth();
        const float cy = a.getBottom() - vy * a.getHeight();   // y up = increasing
        // stick shaft
        g.setColour (juce::Colours::black.withAlpha (0.5f));
        g.drawLine (a.getCentreX(), a.getCentreY(), cx, cy, 2.0f);
        const float pr = juce::jmin (a.getWidth(), a.getHeight()) * 0.14f;
        g.setColour (juce::Colours::black.withAlpha (0.45f));
        g.fillEllipse (cx - pr, cy - pr + 1.5f, pr * 2.0f, pr * 2.0f);
        juce::ColourGradient pg (juce::Colour (0xff3b3a34), cx, cy - pr, juce::Colour (0xff141310), cx, cy + pr, false);
        g.setGradientFill (pg); g.fillEllipse (cx - pr, cy - pr, pr * 2.0f, pr * 2.0f);
        g.setColour (juce::Colour (0xffc8392a)); g.fillEllipse (cx - pr * 0.35f, cy - pr * 0.35f, pr * 0.7f, pr * 0.7f);
    }

private:
    juce::Rectangle<float> pad() const { return getLocalBounds().toFloat().reduced (10.0f); }
    void drag (const juce::MouseEvent& e)
    {
        auto a = pad();
        const float vx = juce::jlimit (0.0f, 1.0f, (e.position.x - a.getX()) / a.getWidth());
        const float vy = juce::jlimit (0.0f, 1.0f, (a.getBottom() - e.position.y) / a.getHeight());
        if (px_) { px_->beginChangeGesture(); px_->setValueNotifyingHost (vx); px_->endChangeGesture(); }
        if (py_) { py_->beginChangeGesture(); py_->setValueNotifyingHost (vy); py_->endChangeGesture(); }
        repaint();
    }
    void parameterValueChanged (int, float) override { triggerAsyncUpdate(); }
    void parameterGestureChanged (int, bool) override {}
    void handleAsyncUpdate() override { repaint(); }
    juce::AudioProcessorParameter* px_ = nullptr;
    juce::AudioProcessorParameter* py_ = nullptr;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VcsJoystick)
};

//==============================================================================
// VcsKnob - the iconic EMS concentric knob, rendered GLOSSY/3D. A COLORED outer ring (blue=freq,
// green=shape, red=envelope, cream=level) that reads as a translucent bakelite/glass DOME (vertical
// light->dark gradient of the ring colour + a bright top-left specular GLINT + a thin dark outline),
// a raised CREAM/IVORY domed centre cap (~55% radius) with its own light->dark gradient + soft
// highlight, and a thin dark POINTER line/notch from the cap out to the colored ring (0..1 over
// ~270deg, -135..+135). Bound to a 0..1 param via an invisible rotary slider.
class VcsKnob  : public juce::Component
{
public:
    explicit VcsKnob (juce::Colour ringColour) : ring_ (ringColour) {}
    void init()
    {
        slider_.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
        slider_.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
        slider_.setLookAndFeel (&laf_);
        slider_.setRange (0.0, 1.0, 0.0);
        slider_.setMouseDragSensitivity (110);   // less mouse travel to turn the knob
        addAndMakeVisible (slider_);
    }
    ~VcsKnob() override { slider_.setLookAndFeel (nullptr); }
    void attach (juce::AudioProcessorParameter& p)
    { att_ = std::make_unique<toi::ParamKnobAttachment> (p, slider_); slider_.setDoubleClickReturnValue (true, p.getDefaultValue()); slider_.onValueChange = [this] { repaint(); }; repaint(); }
    void resized() override { slider_.setBounds (getLocalBounds()); }
    void paint (juce::Graphics& g) override
    {
        auto b = getLocalBounds().toFloat();
        const float d = juce::jmin (b.getWidth(), b.getHeight());
        const float cx = b.getCentreX(), cy = b.getCentreY();
        const float R = d * 0.5f - 7.0f;   // BLACK knob body radius (leave room for the tick sunburst)

        // ---- engraved radial TICK sunburst on the panel around the knob ----
        g.setColour (juce::Colour (0xff6b6e74));   // cool grey ticks on the silver panel
        for (int i = 0; i <= 20; ++i)
        {
            const float a = juce::degreesToRadians (-135.0f + 270.0f * (float) i / 20.0f);
            const float s = std::sin (a), c = -std::cos (a);
            g.drawLine (cx + s * (R + 2.0f), cy + c * (R + 2.0f), cx + s * (R + 6.0f), cy + c * (R + 6.0f), 1.0f);
        }

        // ---- drop shadow ----
        g.setColour (juce::Colours::black.withAlpha (0.45f));
        g.fillEllipse (cx - R, cy - R + 2.0f, R * 2.0f, R * 2.0f);

        // ---- BLACK outer knob body (the whole outer circle is black) ----
        juce::ColourGradient bg (juce::Colour (0xff3c3c40), cx, cy - R, juce::Colour (0xff0e0e11), cx, cy + R, false);
        g.setGradientFill (bg); g.fillEllipse (cx - R, cy - R, R * 2.0f, R * 2.0f);
        g.setColour (juce::Colours::black); g.drawEllipse (cx - R, cy - R, R * 2.0f, R * 2.0f, 1.2f);

        // ---- COLORED inner circle: a BIG glossy domed bakelite cap (~76% of the body, thin black rim) ----
        const float ir = R * 0.76f;
        juce::ColourGradient cgr (ring_.brighter (0.62f), cx, cy - ir, ring_.darker (0.28f), cx, cy + ir, false);
        cgr.addColour (0.45, ring_);
        g.setGradientFill (cgr); g.fillEllipse (cx - ir, cy - ir, ir * 2.0f, ir * 2.0f);
        { const float gx = cx - ir * 0.30f, gy = cy - ir * 0.40f, gr = ir * 0.70f;   // strong glossy glint
          juce::ColourGradient glint (juce::Colours::white.withAlpha (0.85f), gx, gy, juce::Colours::white.withAlpha (0.0f), gx + gr, gy + gr, true);
          g.setGradientFill (glint); g.fillEllipse (gx - gr, gy - gr, gr * 2.0f, gr * 2.0f); }
        g.setColour (juce::Colours::black.withAlpha (0.5f)); g.drawEllipse (cx - ir, cy - ir, ir * 2.0f, ir * 2.0f, 0.9f);

        // ---- POINTER: a tiny WHITE DOT on the black ring (no line) ----
        const float v = juce::jlimit (0.0f, 1.0f, (float) slider_.getValue());
        const float ang = juce::degreesToRadians (-135.0f + 270.0f * v);
        const float s = std::sin (ang), c = -std::cos (ang);
        const float dr = ir + (R - ir) * 0.55f;            // sit in the black ring, between cap and rim
        const float dot = juce::jmax (1.6f, R * 0.085f);   // tiny dot
        const float dx = cx + s * dr, dy = cy + c * dr;
        g.setColour (juce::Colours::black.withAlpha (0.5f)); g.fillEllipse (dx - dot, dy - dot + 0.6f, dot * 2.0f, dot * 2.0f);
        g.setColour (juce::Colours::white);                g.fillEllipse (dx - dot, dy - dot, dot * 2.0f, dot * 2.0f);
    }
    juce::Slider slider_;
private:
    juce::Colour ring_;
    toi::InvisibleRotaryLAF laf_;
    std::unique_ptr<toi::ParamKnobAttachment> att_;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VcsKnob)
};

//==============================================================================
// VcsMeter - the live VU panel meter (audio-driven swinging needle off the AudioTap level).
class VcsMeter  : public juce::Component,
                  private juce::Timer
{
public:
    explicit VcsMeter (toi::AudioTap* t) : tap_ (t) { if (tap_) startTimerHz (30); }
    ~VcsMeter() override { stopTimer(); }
    void paint (juce::Graphics& g) override
    {
        auto b = getLocalBounds().toFloat();
        // cream meter face in a black bezel
        g.setColour (juce::Colour (0xff141310)); g.fillRoundedRectangle (b, 3.0f);
        auto face = b.reduced (3.0f);
        juce::ColourGradient fg (juce::Colour (0xfff3eeda), face.getCentreX(), face.getY(), juce::Colour (0xffe2d9c0), face.getCentreX(), face.getBottom(), false);
        g.setGradientFill (fg); g.fillRoundedRectangle (face, 2.0f);

        const float cx = face.getCentreX(), pivotY = face.getBottom() - 2.0f;
        const float rad = face.getHeight() * 0.86f;
        // arc + scale ticks
        for (int i = 0; i <= 8; ++i)
        {
            const float t = (float) i / 8.0f;
            const float a = juce::degreesToRadians (-52.0f + 104.0f * t);
            const float s = std::sin (a), c = -std::cos (a);
            g.setColour (i >= 6 ? juce::Colour (0xffc8392a) : vcs::kInk.withAlpha (0.7f));
            g.drawLine (cx + s * rad * 0.78f, pivotY + c * rad * 0.78f, cx + s * rad * 0.92f, pivotY + c * rad * 0.92f, 1.2f);
        }
        // needle
        const float lvl = juce::jlimit (0.0f, 1.0f, level_);
        const float a = juce::degreesToRadians (-52.0f + 104.0f * lvl);
        const float s = std::sin (a), c = -std::cos (a);
        g.setColour (juce::Colour (0xff1a1813));
        g.drawLine (cx, pivotY, cx + s * rad * 0.9f, pivotY + c * rad * 0.9f, 1.6f);
        g.setColour (juce::Colour (0xff2a2620)); g.fillEllipse (cx - 3.0f, pivotY - 3.0f, 6.0f, 6.0f);
        g.setColour (vcs::kDim); g.setFont (toi::uiFont (6.0f, true));
        g.drawText ("VU", face.removeFromBottom (8.0f), juce::Justification::centred);
    }
private:
    void timerCallback() override
    {
        const float raw = tap_ ? tap_->level.load (std::memory_order_relaxed) : 0.0f;
        const float target = juce::jlimit (0.0f, 1.0f, std::sqrt (raw) * 1.2f);   // VU-ish
        level_ += (target - level_) * 0.35f;                                       // ballistic smoothing
        repaint();
    }
    toi::AudioTap* tap_ = nullptr;
    float level_ = 0.0f;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VcsMeter)
};

//==============================================================================
// VcsToggle - small black slug switch (osc range bands etc) bound to a 0..1 param. Click cycles.
class VcsToggle  : public juce::Component,
                   private juce::AudioProcessorParameter::Listener,
                   private juce::AsyncUpdater
{
public:
    VcsToggle() = default;
    explicit VcsToggle (int positions) : N (positions) {}
    ~VcsToggle() override { if (param_) param_->removeListener (this); cancelPendingUpdate(); }
    void attach (juce::AudioProcessorParameter* p) { param_ = p; if (param_) param_->addListener (this); triggerAsyncUpdate(); }
    void mouseDown (const juce::MouseEvent&) override
    { if (! param_) return; int a = juce::roundToInt (param_->getValue() * (N - 1)); a = (a + 1) % N; param_->setValueNotifyingHost ((float) a / (float) (N - 1)); }
    void paint (juce::Graphics& g) override
    {
        auto b = getLocalBounds().toFloat().reduced (2.0f, 1.0f);
        const int a = param_ ? juce::jlimit (0, N - 1, juce::roundToInt (param_->getValue() * (N - 1))) : 0;
        g.setColour (juce::Colour (0xff242220)); g.fillRoundedRectangle (b, 2.0f);
        g.setColour (juce::Colours::black); g.drawRoundedRectangle (b, 2.0f, 0.8f);
        const float slugH = b.getHeight() / (float) N;
        auto slug = juce::Rectangle<float> (b.getX() + 1.5f, b.getY() + (float) a * slugH + 1.0f, b.getWidth() - 3.0f, slugH - 2.0f);
        g.setColour (vcs::kPinRed); g.fillRoundedRectangle (slug, 1.5f);
    }
private:
    void parameterValueChanged (int, float) override { triggerAsyncUpdate(); }
    void parameterGestureChanged (int, bool) override {}
    void handleAsyncUpdate() override { repaint(); }
    int N = 2; juce::AudioProcessorParameter* param_ = nullptr;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VcsToggle)
};

//==============================================================================
class VcsFunc  : public juce::Button
{
public:
    VcsFunc (const juce::String& t, juce::Colour fill) : juce::Button (t), col (fill) { setButtonText (t); }
    void flash() { flashing = true; repaint(); juce::Timer::callAfterDelay (150, [s = juce::Component::SafePointer<VcsFunc> (this)] { if (s) { s->flashing = false; s->repaint(); } }); }
    void paintButton (juce::Graphics& g, bool over, bool down) override
    {
        auto b = getLocalBounds().toFloat().reduced (1.0f);
        auto fill = flashing ? col.brighter (0.3f) : down ? col.darker (0.18f) : over ? col.brighter (0.08f) : col;
        g.setColour (fill); g.fillRoundedRectangle (b, 2.5f);
        g.setColour (juce::Colours::black.withAlpha (0.5f)); g.drawRoundedRectangle (b, 2.5f, 1.0f);
        g.setColour (fill.getPerceivedBrightness() > 0.6f ? juce::Colour (0xff1a1813) : juce::Colours::white.withAlpha (0.92f)); g.setFont (toi::uiFont (juce::jmin (10.0f, b.getHeight() * 0.5f), true));
        g.drawText (getButtonText(), getLocalBounds(), juce::Justification::centred);
    }
private:
    juce::Colour col; bool flashing = false;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VcsFunc)
};

//==============================================================================
inline toi::Config jwvcsConfig()
{
    toi::Config c;
    c.model = "JW-VCS";
    auto& p = c.pal;
    p.bg = vcs::kCream; p.bg2 = vcs::kCreamLo; p.frame = juce::Colour (0xff3a2410); p.ink = vcs::kInk;
    p.accent = vcs::kPinRed; p.accent2 = vcs::kPinGreen; p.button = juce::Colour (0xff242220);
    p.thumb = juce::Colour (0xff2a2620); p.text = vcs::kInk;
    p.noteStrip = vcs::kCreamLo;
    p.lcdBg = juce::Colour (0xff14140f); p.lcdInk = juce::Colour (0xff4f9a52);
    p.keyWhite = juce::Colour (0xfff1ecdc); p.keyWhitePr = vcs::kPinRed; p.keyBlack = juce::Colour (0xff242018); p.keyBlackPr = vcs::kPinGreen;

    // ids MUST match VCS.cmajor ParamsProcessor inputs exactly (and in that order).
    c.params = {
        { "o1Freq","FREQ" },{ "o1Range","RANGE" },{ "o1Sine","SINE" },{ "o1Saw","SAW" },
        { "o2Freq","FREQ" },{ "o2Range","RANGE" },{ "o2Shape","SHAPE" },{ "o2Pw","PW" },{ "o2Level","LEVEL" },
        { "o3Freq","FREQ" },{ "o3Range","RANGE" },{ "o3Shape","SHAPE" },{ "o3Pw","PW" },{ "o3Level","LEVEL" },
        { "drift","DRIFT" },{ "noise","NOISE" },
        { "cutoff","FREQ" },{ "reso","RES" },{ "fKeyTrack","KBD" },
        { "trapA","ATT" },{ "trapOn","ON" },{ "trapD","DEC" },{ "trapOff","OFF" },
        { "reverb","REVERB" },
        { "joyX","JOY X" },{ "joyY","JOY Y" },{ "volume","VOL" },{ "tune","TUNE" },
    };

    // init values mirroring the engine defaults
    std::vector<float> base = {
        0.40f,0.50f,0.30f,0.70f,
        0.42f,0.50f,0.60f,0.45f,0.60f,
        0.30f,0.18f,0.0f,0.50f,0.40f,
        0.28f,0.30f,
        0.58f,0.42f,0.40f,
        0.06f,0.30f,0.40f,1.0f,
        0.30f,
        0.50f,0.50f,0.80f,0.50f };

    auto P = [&] (const char* nm, std::initializer_list<std::pair<const char*,float>> ov)
    { auto v = base; for (auto& o : ov) for (size_t i = 0; i < c.params.size(); ++i) if (c.params[i].id == o.first) v[i] = o.second; return toi::FactoryPreset { nm, v }; };

    c.factory = {
        P("INIT", {}),
        P("SCI-FI DRONE",   {{"o1Range",0.5f},{"drift",0.55f},{"cutoff",0.5f},{"reso",0.55f},{"mO1Filt",1.0f},{"mO2Filt",0.7f},{"mFiltRev",0.6f},{"mRevOut",0.6f},{"reverb",0.55f}}),
        P("RING BLEEP",     {{"mO1Ring",1.0f},{"mO2Ring",1.0f},{"mRingFilt",1.0f},{"mO1Filt",0.2f},{"o2Freq",0.62f},{"cutoff",0.6f},{"reso",0.4f}}),
        P("SELF-OSC SINE",  {{"reso",0.95f},{"cutoff",0.55f},{"trapOff",1.0f}}),                 // one-shot (OFF maxed = no repeat)
        P("TRAP LFO PULSE", {{"trapOff",0.02f},{"trapA",0.1f},{"trapD",0.3f},{"cutoff",0.45f},{"reso",0.5f}}),   // deliberate LFO pulse (OFF near 0)
        P("NOISE WIND",     {{"noise",0.7f},{"mNzFilt",0.8f},{"mO1Filt",0.2f},{"cutoff",0.4f},{"reso",0.45f},{"mFiltRev",0.6f},{"mRevOut",0.6f},{"reverb",0.6f}}),
        P("JOY SWEEP",      {{"joyX",0.5f},{"joyY",0.5f},{"mJoyO2",0.8f},{"mJoyFiltCV",0.8f},{"o2Level",0.7f},{"cutoff",0.4f},{"reso",0.4f}}),
        P("OSC3 LFO FILT",  {{"o3Range",0.12f},{"mO3FiltCV",0.7f},{"cutoff",0.45f},{"reso",0.5f},{"mO1Filt",1.0f}}),
        P("SPRING SPACE",   {{"reverb",0.75f},{"mFiltRev",0.7f},{"mRevOut",0.75f},{"cutoff",0.55f},{"reso",0.4f},{"drift",0.4f}}),
        P("FAT SAW",        {{"o1Saw",0.9f},{"o1Sine",0.2f},{"mO1Filt",1.0f},{"mO2Filt",0.6f},{"cutoff",0.5f},{"reso",0.35f},{"drift",0.35f}}),
        P("PWM HOLLOW",     {{"o2Shape",1.0f},{"o2Pw",0.3f},{"o2Level",0.8f},{"mO2Filt",1.0f},{"mO1Filt",0.4f},{"cutoff",0.55f},{"reso",0.4f}}),
        P("HOWL FEEDBACK",  {{"reso",0.7f},{"mFiltRev",0.8f},{"mRevOut",0.7f},{"mRingFilt",0.4f},{"mO1Ring",0.6f},{"mO2Ring",0.6f},{"reverb",0.5f}}),
    };
    return c;
}

//==============================================================================
class JWVCSEditor  : public toi::PanelEditor
{
public:
    JWVCSEditor (juce::AudioProcessor& proc, juce::MidiKeyboardState& kb)
        : toi::PanelEditor (proc, kb, jwvcsConfig())
    {
        // ----- THE 2D GRID (matches the real VCS3): the THREE OSCILLATORS stacked as three
        //       vertical rows (OSC1 top / OSC2 mid / OSC3 bottom), each row = a FREQ knob (blue,
        //       larger) then SHAPE/wave (green) then the rest (cream) then a RANGE toggle. To the
        //       right, the module sections (FILTER / ENVELOPE SHAPER / REVERB / OUTPUT) as their
        //       own compact boxes. FREQ is now a normal blue concentric knob (no geared dial).
        oscRows_ = {
            { "OSCILLATOR 1", { "o1Freq","o1Range","o1Sine","o1Saw" }, "" },
            { "OSCILLATOR 2", { "o2Freq","o2Range","o2Shape","o2Pw","o2Level" }, "" },
            { "OSCILLATOR 3", { "o3Freq","o3Range","o3Shape","o3Pw","o3Level" }, "" },
        };
        modGroups_ = {
            { "FILTER",          { "cutoff","reso","fKeyTrack" } },
            { "ENVELOPE SHAPER", { "trapA","trapOn","trapD","trapOff" } },
            { "REVERB",          { "reverb" } },
            { "OUTPUT",          { "drift","noise","volume","tune" } },
        };
        for (auto& r : oscRows_)  for (auto& id : r.ids) addKnob (id);
        for (auto& grp : modGroups_) for (auto& id : grp.ids) addKnob (id);

        // RANGE is a KNOB now (Jade: only knobs on the panels) - it is one of the osc-row ids above, so
        // addKnob already created it. No toggle switches anywhere on the panel.

        // ----- THE PIN MATRIX (the instrument) - a REAL 10-source x 8-dest gain matrix, EVERY hole live -----
        // ROWS (sources):  0 OSC1  1 OSC2  2 OSC3  3 NOISE  4 RING  5 FILTER  6 REVERB  7 TRAP  8 JOY-X  9 JOY-Y
        // COLS (dests):    0 OSC1-FC 1 OSC2-FC 2 OSC3-FC 3 RING-IN 4 FILTER-IN 5 FILTER-FC 6 REVERB-IN 7 OUTPUT
        matrix_ = std::make_unique<VcsPinMatrix>();
        { static const char* H = "0123456789ABCDEF";
          for (int r = 0; r < 10; ++r)
              for (int c = 0; c < 16; ++c)
              { juce::String id ("mx"); id << r << H[c];
                matrix_->addPin (r, c, findParam (id)); } }
        addAndMakeVisible (*matrix_);

        // ----- the joystick -----
        joy_ = std::make_unique<VcsJoystick>();
        joy_->setParams (findParam ("joyX"), findParam ("joyY"));
        addAndMakeVisible (*joy_);

        // ----- live VU meter -----
        meter_ = std::make_unique<VcsMeter> (audioTap());
        addAndMakeVisible (*meter_);

        // ----- tiny real-audio SCOPE below the LEVEL meter (live signal only, house rule) -----
        scope_ = std::make_unique<toi::Lcd> (pal());
        scope_->attachScope (audioTap());
        addAndMakeVisible (*scope_);

        // ----- EDIT button: pages the oscillator area (OSC1 -> OSC2 -> OSC3) so the knobs stay big -----
        editBtn_ = std::make_unique<VcsFunc> ("EDIT", juce::Colour (0xff3f6bb6));
        editBtn_->onClick = [this] { oscPage_ = (oscPage_ + 1) % 3; resized(); repaint(); };
        addAndMakeVisible (*editBtn_);

        // ----- presets + RAND/SAVE -----
        for (int i = 0; i < 16; ++i)
        { auto b = std::make_unique<toi::MoldedButton> (juce::Colour (0xffe9e6df)); b->setLit (juce::Colour (0xff2f6fd0)); const int idx = i; b->onClick = [this, idx] { recallSlot (idx); }; addAndMakeVisible (*b); slots_.push_back (std::move (b)); }
        rand_ = std::make_unique<VcsFunc> ("RAND", vcs::kCream); save_ = std::make_unique<VcsFunc> ("SAVE", vcs::kCream);   // clear / panel-silver, dark text
        rand_->onClick = [this] { doRandom(); if (matrix_) matrix_->randomize(); rand_->flash(); };
        save_->onClick = [this] { saveSlot (activeSlot()); save_->flash(); };
        addAndMakeVisible (*rand_); addAndMakeVisible (*save_);

        finishSetup();
    }

protected:
    void setPresetActiveVisual (int idx) override { for (int i = 0; i < (int) slots_.size(); ++i) slots_[(size_t) i]->setActive (i == idx); }

    void drawCheek (juce::Graphics& g, juce::Rectangle<float> r)
    {
        juce::ColourGradient wg (vcs::kWood, r.getX(), r.getY(), vcs::kWoodD, r.getRight(), r.getY(), false);
        g.setGradientFill (wg); g.fillRect (r);
        juce::Random rr (515 + (int) r.getX());
        g.setColour (vcs::kWoodD.withAlpha (0.4f));
        for (int i = 0; i < 8; ++i) { const float gx = r.getX() + rr.nextFloat() * r.getWidth(); g.drawLine (gx, r.getY(), gx + 2.0f, r.getBottom(), 0.7f); }
    }

    void paintPanel (juce::Graphics& g, juce::Rectangle<float> panel) override
    {
        rPanel = panel;
        juce::ColourGradient pg (vcs::kCream, panel.getCentreX(), panel.getY(), vcs::kCreamLo, panel.getCentreX(), panel.getBottom(), false);
        g.setGradientFill (pg); g.fillRoundedRectangle (panel, 5.0f);

        // afrormosia wood end-cheeks (the L-shaped console edges)
        const float ch = 24.0f;
        drawCheek (g, juce::Rectangle<float> (panel.getX(), panel.getY(), ch, panel.getHeight()));
        drawCheek (g, juce::Rectangle<float> (panel.getRight() - ch, panel.getY(), ch, panel.getHeight()));
        g.setColour (juce::Colours::black); g.drawRoundedRectangle (panel, 5.0f, 1.5f);

        // ALL THREE oscillators stacked (matches the real VCS3 - every module visible at once) + modules
        for (auto& r : oscRows_) drawGroupBox (g, r.name, r.ids, r.rect);
        for (auto& grp : modGroups_) drawGroupBox (g, grp.name, grp.ids, grp.rect);

        // range-toggle labels
        for (auto& t : toggleRects_)
        { g.setColour (vcs::kDim); g.setFont (toi::uiFont (5.5f, true));
          g.drawText (t.first, juce::Rectangle<float> (t.second.getX() - 8.0f, t.second.getBottom() + 1.0f, t.second.getWidth() + 16.0f, 7.0f), juce::Justification::centred); }

        // matrix recess label + row/col index numerals
        g.setColour (vcs::kInk); g.setFont (toi::uiFont (7.0f, true).withExtraKerningFactor (0.1f));
        g.drawText ("PATCH MATRIX", juce::Rectangle<float> (rMatrix_.getX(), rMatrix_.getY() - 10.0f, 200.0f, 9.0f), juce::Justification::centredLeft);
        drawMatrixIndices (g);

        // joystick / meter / preset labels (NO scope)
        g.setColour (vcs::kInk); g.setFont (toi::uiFont (6.5f, true));
        g.drawText ("JOYSTICK",  juce::Rectangle<float> (rJoy_.getX(),   rJoy_.getY()   - 9.0f, 120.0f, 9.0f), juce::Justification::centredLeft);
        g.drawText ("LEVEL",     juce::Rectangle<float> (rMeter_.getX(), rMeter_.getY() - 9.0f, 120.0f, 9.0f), juce::Justification::centredLeft);
        g.drawText ("SCOPE",     juce::Rectangle<float> (rScope_.getX(), rScope_.getY() - 9.0f, 120.0f, 9.0f), juce::Justification::centredLeft);
        g.drawText ("PRESET",    juce::Rectangle<float> (rPreset_.getX(),rPreset_.getY()- 9.0f, 120.0f, 9.0f), juce::Justification::centredLeft);

        // pin legend (RED/WHITE = full, GREEN = atten)
        drawLegend (g);

        // brand in the TOP BAND: JW-VCS (left) + MODULE/SIZE right beside it - kept clear so the matrix never covers the words
        { auto bh = rBrand_;
          auto nameR = bh.removeFromLeft (108.0f);
          g.setColour (vcs::kInk); g.setFont (toi::uiFont (16.0f, true));
          g.drawText ("JW-VCS", nameR, juce::Justification::centredLeft);
          drawViewLeds (g, bh.removeFromLeft (104.0f)); }
    }

    void drawMatrixIndices (juce::Graphics& g)
    {
        if (matrix_ == nullptr) return;
        auto base = matrix_->getBounds().toFloat();
        const float x0 = base.getX() + matrix_->gridX0();
        const float y0 = base.getY() + matrix_->gridY0();
        const float stepX = matrix_->gridStepX(), stepY = matrix_->gridStepY();
        g.setColour (vcs::kDim); g.setFont (toi::uiFont (5.0f, true));
        const char* rowLab[10] = { "O1","O2","O3","NZ","RM","FL","RV","TR","JX","JY" };
        const char* colLab[16] = { "o1f","o2f","o3f","RNG","FIN","FfC","RVB","OUT",
                                   "o2P","o3P","RES","FfC","RVB","LVL","NZ","OUT" };
        for (int r = 0; r < 10; ++r)
            g.drawText (rowLab[r], juce::Rectangle<float> (x0 - 15.0f, y0 + (float) r * stepY, 13.0f, stepY), juce::Justification::centredRight);
        for (int col = 0; col < 16; ++col)
            g.drawText (colLab[col], juce::Rectangle<float> (x0 + (float) col * stepX, y0 - 8.0f, stepX, 8.0f), juce::Justification::centred);
    }

    void drawLegend (juce::Graphics& g)
    {
        auto r = rLegend_;
        struct L { juce::Colour c; const char* t; };
        const L items[3] = { { vcs::kPinRed, "FULL" }, { vcs::kPinWhite, "FULL" }, { vcs::kPinGreen, "ATTEN" } };
        float x = r.getX();
        g.setFont (toi::uiFont (5.5f, true));
        for (auto& it : items)
        {
            g.setColour (it.c); g.fillEllipse (x, r.getCentreY() - 3.0f, 6.0f, 6.0f);
            g.setColour (juce::Colours::black.withAlpha (0.4f)); g.drawEllipse (x, r.getCentreY() - 3.0f, 6.0f, 6.0f, 0.5f);
            g.setColour (vcs::kDim);
            g.drawText (it.t, juce::Rectangle<float> (x + 8.0f, r.getY(), 26.0f, r.getHeight()), juce::Justification::centredLeft);
            x += 40.0f;
        }
    }

    void layoutPanel (juce::Rectangle<float> panel) override
    {
        rPanel = panel;
        auto inner = panel.reduced (0.0f, 6.0f);
        inner.removeFromLeft (32.0f);    // clear the LEFT wood cheek (24px) - brand/matrix/presets must NOT sit on the wood
        inner.removeFromRight (32.0f);   // clear the RIGHT wood cheek

        // ===== TOP BAND (full width): JW-VCS brand + MODULE/SIZE - kept clear so NOTHING ever covers the words =====
        rBrand_ = inner.removeFromTop (22.0f);
        inner.removeFromTop (12.0f);   // gap below the words (the PATCH MATRIX label lives here, clear of the matrix)

        // ===== LEFT BLOCK: a COMPACT DENSE pin matrix (16x10 SQUARE cells = small tight holes like the
        //       real VCS3), 16 PRESETS directly BELOW it, JOYSTICK + VU beside it =====
        auto left = inner.removeFromLeft (340.0f);
        inner.removeFromLeft (16.0f);
        auto matrixCol = left.removeFromLeft (236.0f);
        left.removeFromLeft (12.0f);
        auto presetArea = matrixCol.removeFromBottom (34.0f);   // 16 presets (2x8) directly below the matrix
        matrixCol.removeFromBottom (10.0f);                     // PRESET label gap (clear of the matrix)
        { const float mh = matrixCol.getHeight();
          const float mw = juce::jmin (matrixCol.getWidth(), mh * 1.6f);   // COLS/ROWS = 16/10 -> SQUARE holes
          rMatrix_ = juce::Rectangle<float> (matrixCol.getX(), matrixCol.getY(), mw, mh);
          placeInArtboard (*matrix_, rMatrix_); }
        { auto rs = presetArea.removeFromRight (44.0f); presetArea.removeFromRight (6.0f);
          rPreset_ = presetArea;
          const int pc = 8; const float pgap = 2.5f;
          const float pw = (rPreset_.getWidth() - pgap * (pc - 1)) / (float) pc; const float ph = juce::jmin (14.0f, (rPreset_.getHeight() - pgap) * 0.5f);
          for (int i = 0; i < 16; ++i) { const int rr = i / pc, cc = i % pc; placeInArtboard (*slots_[(size_t) i], juce::Rectangle<float> (rPreset_.getX() + (float) cc * (pw + pgap), rPreset_.getY() + (float) rr * (ph + pgap), pw, ph)); }
          auto rsi = rs; const float bh = (rsi.getHeight() - 3.0f) * 0.5f;
          placeInArtboard (*rand_, rsi.removeFromTop (bh)); rsi.removeFromTop (3.0f); placeInArtboard (*save_, rsi.removeFromTop (bh)); }

        // ===== JOYSTICK + VU + tiny SCOPE column, beside the matrix =====
        auto jmCol = left;
        rJoy_   = jmCol.removeFromTop (80.0f).reduced (3.0f); placeInArtboard (*joy_, rJoy_);
        jmCol.removeFromTop (14.0f);
        rMeter_ = jmCol.removeFromTop (52.0f).reduced (3.0f); placeInArtboard (*meter_, rMeter_);
        jmCol.removeFromTop (12.0f);   // SCOPE label gap
        rScope_ = jmCol.removeFromTop (juce::jmin (42.0f, jmCol.getHeight() - 2.0f)).reduced (3.0f, 0.0f);
        placeInArtboard (*scope_, rScope_);

        // ===== RIGHT BLOCK: 3 oscillators stacked + module boxes - ALL KNOBS (no toggles, no paging) =====
        if (editBtn_) editBtn_->setVisible (false);
        for (auto& r : oscRows_) for (auto& id : r.ids) if (auto* k = knobFor (id)) k->setVisible (true);
        auto oscBlock = inner.removeFromLeft (300.0f);
        inner.removeFromLeft (12.0f);
        layoutOscRows (oscBlock);
        layoutModGroups (inner);
    }

    // the oscillator area shows ONE oscillator at a time at BIG knob size (same as the modules); the
    // EDIT button pages OSC1 -> OSC2 -> OSC3. (Big knobs won't all fit at once.)
    void layoutOscPaged (juce::Rectangle<float> block)
    {
        rOscBlock_ = block;
        toggleRects_.clear();
        for (int p = 0; p < (int) oscRows_.size(); ++p)
        {
            const bool vis = (p == oscPage_);
            for (auto& id : oscRows_[(size_t) p].ids) if (auto* k = knobFor (id)) k->setVisible (vis);
            if (auto* t = toggleFor (oscRows_[(size_t) p].rangeId)) t->setVisible (vis);
        }
        auto& r = oscRows_[(size_t) juce::jlimit (0, (int) oscRows_.size() - 1, oscPage_)];
        // header: EDIT button on the right of the osc box title row
        auto hdr = block.removeFromTop (22.0f);
        rEdit_ = hdr.removeFromRight (60.0f).reduced (2.0f, 2.0f);
        if (editBtn_) placeInArtboard (*editBtn_, rEdit_);
        // big knobs in one row + the RANGE toggle
        const int nCells = (int) r.ids.size() + 1;
        const float cw = block.getWidth() / (float) nCells;
        const float labelTop = 6.0f, labelBot = 9.0f;
        float ix = block.getX();
        for (auto& id : r.ids)
        {
            if (auto* k = knobFor (id))
            { auto cell = juce::Rectangle<float> (ix, block.getY() + labelTop, cw, block.getHeight() - labelTop - labelBot).reduced (4.0f, 0.0f);
              const float dd = juce::jmin (cell.getWidth(), cell.getHeight(), 56.0f);
              placeInArtboard (*k, juce::Rectangle<float> (0, 0, dd, dd).withCentre (cell.getCentre())); }
            ix += cw;
        }
        if (auto* t = toggleFor (r.rangeId))
        { auto tr = juce::Rectangle<float> (ix + 6.0f, block.getY() + 26.0f, cw * 0.4f, block.getHeight() - 50.0f);
          placeInArtboard (*t, tr); toggleRects_.push_back ({ "RANGE", tr }); }
    }

private:
    struct Group   { juce::String name; std::vector<juce::String> ids; juce::Rectangle<float> rect; };
    struct OscRow  { juce::String name; std::vector<juce::String> ids; juce::String rangeId; juce::Rectangle<float> rect; };

    static juce::Colour colorFor (const juce::String& id)
    {
        if (id.endsWith ("Freq") || id == "cutoff")        return juce::Colour (0xff2f8de8);   // bright glossy blue  = frequency / filter cutoff
        if (id.contains ("Shape") || id == "o1Saw")        return juce::Colour (0xff57b54f);   // vivid green = shape / wave
        if (id.startsWith ("trap"))                        return juce::Colour (0xffd83b2a);   // bright red   = envelope shaper
        return juce::Colour (0xffeee5cd);                                                       // warm ivory = level / PW / reverb / drift / noise / vol / tune / response
    }
    void addKnob (const juce::String& id)
    {
        auto k = std::make_unique<VcsKnob> (colorFor (id)); k->init();
        if (auto* prm = findParam (id)) k->attach (*prm);
        addAndMakeVisible (*k); knobMap_[id] = k.get(); knobs_.push_back (std::move (k));
    }
    void addToggle (const juce::String& id, int positions)
    {
        auto t = std::make_unique<VcsToggle> (positions);
        if (auto* prm = findParam (id)) t->attach (prm);
        addAndMakeVisible (*t); toggleMap_[id] = t.get(); toggles_.push_back (std::move (t));
    }
    VcsKnob* knobFor (const juce::String& id) const { auto it = knobMap_.find (id); return it == knobMap_.end() ? nullptr : it->second; }
    VcsToggle* toggleFor (const juce::String& id) const { auto it = toggleMap_.find (id); return it == toggleMap_.end() ? nullptr : it->second; }

    // ---- the THREE stacked oscillator rows (the dominant left-of-modules block) ----
    void layoutOscRows (juce::Rectangle<float> block)
    {
        toggleRects_.clear();
        const float rgap = 6.0f;
        const float rh = (block.getHeight() - rgap * (float) (oscRows_.size() - 1)) / (float) oscRows_.size();
        // widest row drives the per-cell width so every osc row aligns vertically; the FREQ knob is
        // slightly larger so it visually anchors each row. allow up to 5 cells + a toggle column.
        const float labelTop = 7.0f, labelBot = 6.0f;
        const float kw = block.getWidth() / 5.0f;     // 5 = widest osc row (FREQ RANGE SHAPE PW LEVEL): knobs shrink to FIT, never stick out of the box
        const float toggleW = rh * 0.30f;
        float y = block.getY();
        for (auto& r : oscRows_)
        {
            r.rect = juce::Rectangle<float> (block.getX(), y, block.getWidth(), rh);
            const float knobH = rh - labelTop - labelBot;
            float ix = block.getX();
            for (size_t i = 0; i < r.ids.size(); ++i)
            {
                if (auto* k = knobFor (r.ids[i]))
                {
                    auto cell = juce::Rectangle<float> (ix, y + labelTop, kw, knobH).reduced (4.0f, 0.0f);
                    const float dd = juce::jmin (cell.getWidth(), cell.getHeight(), 48.0f);   // fits 5 per block
                    placeInArtboard (*k, juce::Rectangle<float> (0, 0, dd, dd).withCentre (cell.getCentre()));
                }
                ix += kw;
            }
            // RANGE toggle slug right after the clustered knobs
            if (auto* t = toggleFor (r.rangeId))
            {
                auto tr = juce::Rectangle<float> (ix + 6.0f, y + labelTop + 6.0f, toggleW, knobH - 14.0f);
                placeInArtboard (*t, tr);
                toggleRects_.push_back ({ "RANGE", tr });
            }
            y += rh + rgap;
        }
    }

    // ---- the module section boxes (FILTER + ENVELOPE on top, REVERB + OUTPUT below) ----
    void layoutModGroups (juce::Rectangle<float> area)
    {
        // two stacked half-rows; top = FILTER + ENVELOPE SHAPER, bottom = REVERB + OUTPUT
        const float vgap = 8.0f;
        const float halfH = (area.getHeight() - vgap) * 0.5f;
        auto top = area.removeFromTop (halfH);
        area.removeFromTop (vgap);
        auto bot = area;

        auto boxRow = [this] (juce::Rectangle<float> row, std::initializer_list<int> idxWeights, std::initializer_list<int> which)
        {
            const float hgap = 8.0f;
            // total weight to share the width proportionally to each box's knob-count
            float total = 0.0f; for (int w : idxWeights) total += (float) w;
            const float usable = row.getWidth() - hgap * (float) (which.size() - 1);
            float x = row.getX();
            auto wi = idxWeights.begin();
            for (int gi : which)
            {
                const float bw = usable * ((float) *wi / total);
                placeModGroup (modGroups_[(size_t) gi], juce::Rectangle<float> (x, row.getY(), bw, row.getHeight()));
                x += bw + hgap;
                ++wi;
            }
        };
        // FILTER (3 knobs) | ENVELOPE SHAPER (4 knobs)
        boxRow (top, { 3, 4 }, { 0, 1 });
        // REVERB (1 knob) | OUTPUT (4 knobs)
        boxRow (bot, { 1, 4 }, { 2, 3 });
    }

    void placeModGroup (Group& grp, juce::Rectangle<float> box)
    {
        grp.rect = box;
        const float labelTop = 12.0f, labelBot = 9.0f;
        const int n = juce::jmax (1, (int) grp.ids.size());
        const float kw = box.getWidth() / (float) n;
        const float knobH = box.getHeight() - labelTop - labelBot;
        for (int i = 0; i < (int) grp.ids.size(); ++i)
        {
            if (auto* k = knobFor (grp.ids[(size_t) i]))
            {
                auto cell = juce::Rectangle<float> (box.getX() + (float) i * kw, box.getY() + labelTop, kw, knobH).reduced (3.0f, 0.0f);
                const float dd = juce::jmin (cell.getWidth(), cell.getHeight(), 62.0f);   // bigger module knobs (FILTER/ENVELOPE/REVERB/OUTPUT have the space)
                placeInArtboard (*k, juce::Rectangle<float> (0, 0, dd, dd).withCentre (cell.getCentre()));
            }
        }
    }

    // section box (thin black rounded-rect, name silk-screened top-left, per-knob caption below)
    void drawGroupBox (juce::Graphics& g, const juce::String& name, const std::vector<juce::String>& ids, juce::Rectangle<float> rect)
    {
        g.setColour (juce::Colour (0x16000000)); g.fillRoundedRectangle (rect, 3.0f);
        g.setColour (vcs::kInk.withAlpha (0.5f)); g.drawRoundedRectangle (rect, 3.0f, 1.0f);
        g.setColour (vcs::kInk); g.setFont (toi::uiFont (6.5f, true).withExtraKerningFactor (0.05f));
        g.drawText (name, rect.withHeight (10.0f).reduced (4.0f, 1.0f), juce::Justification::centredLeft);
        for (auto& id : ids)
        {
            if (auto* k = knobFor (id))
            {
                juce::String lbl; for (auto& sp : config().params) if (sp.id == id) { lbl = sp.label; break; }
                auto kr = k->getBounds().toFloat();
                g.setColour (vcs::kDim); g.setFont (toi::uiFont (5.5f, true));
                g.drawText (lbl, juce::Rectangle<float> (kr.getX() - 8.0f, rect.getBottom() - 9.0f, kr.getWidth() + 16.0f, 8.0f), juce::Justification::centred);
            }
        }
    }

    std::vector<std::unique_ptr<VcsKnob>> knobs_;
    std::map<juce::String, VcsKnob*> knobMap_;
    std::vector<std::unique_ptr<VcsToggle>> toggles_;
    std::map<juce::String, VcsToggle*> toggleMap_;
    std::vector<std::pair<juce::String, juce::Rectangle<float>>> toggleRects_;
    std::unique_ptr<VcsPinMatrix> matrix_;
    std::unique_ptr<VcsJoystick> joy_;
    std::unique_ptr<VcsMeter> meter_;
    std::unique_ptr<toi::Lcd> scope_;
    std::vector<std::unique_ptr<toi::MoldedButton>> slots_;
    std::unique_ptr<VcsFunc> rand_, save_, editBtn_;
    int oscPage_ = 0;
    std::vector<OscRow> oscRows_;
    std::vector<Group> modGroups_;
    juce::Rectangle<float> rPanel, rMatrix_, rJoy_, rMeter_, rScope_, rPreset_, rBrand_, rLegend_, rOscBlock_, rEdit_;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JWVCSEditor)
};

//==============================================================================
class JWVCSPlugin  : public cmaj::plugin::GeneratedPlugin<::JWVCS>,
                     public toi::AudioTapSource,
                     public toi::PresetStore
{
public:
    using Base = cmaj::plugin::GeneratedPlugin<::JWVCS>;
    JWVCSPlugin (std::shared_ptr<cmaj::Patch> p) : Base (std::move (p)) {}
    juce::AudioProcessorEditor* createEditor() override { return new JWVCSEditor (*this, keyboardState); }
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
