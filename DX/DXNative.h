// JW-DX native faceplate (6-operator FM, 32 algorithms) on the toi_faceplate.h kit.
// Identity (DX7, rendered in TOI house style - reference informs, house style renders):
//   - dark espresso-brown slab, vivid "DX green" flat MEMBRANE buttons, a green LCD scope,
//     the iconic ribbed DATA-ENTRY slider, and orange accents.
//   - The HERO / signature interactive feature: a LIVE ALGORITHM diagram that draws the 6
//     operators as a routing stack (carriers filled green, modulators outlined, the feedback
//     loop marked) for the selected algorithm 1-32; click its halves (or the < > buttons) to
//     change algorithm and watch the routing redraw.
//   - Editing follows the DX7 workflow: pick an OPERATOR (OP1-OP6 membrane buttons), then the
//     RATIO / FINE / DETUNE / LEVEL + envelope A/D/S/R controls re-bind to that operator.
// Custom hardware-accurate controls (no generic reused kit knob): DxKnob (green-pointer dial),
// DxMembrane (flat green/orange membrane button), DataSlider (ribbed vertical slider), AlgoView.
// No brand names (JW-DX only).
#pragma once

#include "toi_faceplate.h"

struct DX;

namespace dx
{
    static const juce::Colour kBrownHi { 0xff2d2218 };   // espresso panel, top
    static const juce::Colour kBrownLo { 0xff16100a };   // espresso panel, bottom
    static const juce::Colour kFrame   { 0xff080604 };
    static const juce::Colour kGreen   { 0xff37b463 };   // DX green
    static const juce::Colour kGreenHi { 0xff63e58c };   // bright green (lit / active)
    static const juce::Colour kGreenLo { 0xff205c39 };   // dim green
    static const juce::Colour kOrange  { 0xffe06a26 };   // orange accent buttons
    static const juce::Colour kCream   { 0xffdcd2bd };   // pale warm silkscreen text
    static const juce::Colour kDim     { 0xff8a8068 };
    static const juce::Colour kBox     { 0xff120d08 };   // recessed section box
    static const juce::Colour kBoxEdge { 0xff4a3a26 };
    static const juce::Colour kLcdBg   { 0xff081710 };
    static const juce::Colour kLcdInk  { 0xff5fe58c };
    static const juce::Colour kPeri    { 0xff6f6db8 };   // periwinkle = the black-key colour (slider thumbs)
    static const juce::Colour kPeriHi  { 0xff9d9bea };
}

//==============================================================================
// DxKnob - a bespoke dark dial with a bright DX-green pointer + value arc, recessed bezel.
// Reuses the proven invisible-slider + ParamKnobAttachment mechanics for drag + host binding.
class DxKnob  : public juce::Component
{
public:
    DxKnob()
    {
        slider_.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
        slider_.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
        slider_.setLookAndFeel (&laf_);
        slider_.setRange (0.0, 1.0, 0.0);
        slider_.setMouseDragSensitivity (100);
        addAndMakeVisible (slider_);
    }
    ~DxKnob() override { slider_.setLookAndFeel (nullptr); }

    void attach (juce::AudioProcessorParameter& p)
    {
        att_ = std::make_unique<toi::ParamKnobAttachment> (p, slider_);
        slider_.setDoubleClickReturnValue (true, p.getDefaultValue());
        slider_.onValueChange = [this] { repaint(); };
        repaint();
    }
    void resized() override { slider_.setBounds (getLocalBounds()); }

    void paint (juce::Graphics& g) override
    {
        auto b = getLocalBounds().toFloat();
        const float d = std::min (b.getWidth(), b.getHeight());
        auto disc = juce::Rectangle<float> (0, 0, d, d).withCentre (b.getCentre());
        const float cx = disc.getCentreX(), cy = disc.getCentreY();
        const float r = d * 0.5f - 2.5f;
        const float v = juce::jlimit (0.0f, 1.0f, (float) slider_.getValue());
        const float ang = juce::degreesToRadians (-135.0f + 270.0f * v);

        // design 73: black knob body + white rim + a white dot indicator near the rim
        g.setColour (juce::Colours::black.withAlpha (0.45f)); g.fillEllipse (cx - r, cy - r + 1.5f, r * 2, r * 2);  // contact shadow
        g.setColour (juce::Colour (0xff060606)); g.fillEllipse (cx - r, cy - r, r * 2, r * 2);                       // black body
        g.setColour (juce::Colour (0xfff4f4f4)); g.drawEllipse (cx - r, cy - r, r * 2, r * 2, juce::jmax (1.4f, r * 0.07f));  // white rim

        const float dotR = r * 0.58f, ds = juce::jmax (2.2f, r * 0.15f);
        const float ux = std::sin (ang), uy = -std::cos (ang);
        g.setColour (juce::Colour (0xfff4f4f4)); g.fillEllipse (cx + ux * dotR - ds, cy + uy * dotR - ds, ds * 2, ds * 2);  // white dot
    }

private:
    juce::Slider slider_;
    toi::InvisibleRotaryLAF laf_;
    std::unique_ptr<toi::ParamKnobAttachment> att_;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DxKnob)
};

//==============================================================================
// DxFader - a vertical slider with a recessed groove + periwinkle fill and a periwinkle thumb cap
// (the thumb matches the black keys). Reuses the invisible-slider + ParamKnobAttachment mechanics.
class DxFader  : public juce::Component
{
public:
    DxFader()
    {
        slider_.setSliderStyle (juce::Slider::LinearVertical);
        slider_.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
        slider_.setLookAndFeel (&laf_);
        slider_.setRange (0.0, 1.0, 0.0);
        addAndMakeVisible (slider_);
    }
    ~DxFader() override { slider_.setLookAndFeel (nullptr); }
    void attach (juce::AudioProcessorParameter& p)
    {
        att_ = std::make_unique<toi::ParamKnobAttachment> (p, slider_);
        slider_.setDoubleClickReturnValue (true, p.getDefaultValue());
        slider_.onValueChange = [this] { repaint(); };
        repaint();
    }
    void resized() override { slider_.setBounds (getLocalBounds()); }
    void paint (juce::Graphics& g) override
    {
        auto b = getLocalBounds().toFloat();
        const float cx = b.getCentreX();
        auto track = juce::Rectangle<float> (cx - 3.0f, b.getY() + 7.0f, 6.0f, b.getHeight() - 14.0f);
        g.setColour (juce::Colour (0xff0a0805)); g.fillRoundedRectangle (track.expanded (2.0f, 2.0f), 3.0f);
        g.setColour (juce::Colour (0xff050403)); g.fillRoundedRectangle (track, 2.5f);
        const float v = juce::jlimit (0.0f, 1.0f, (float) slider_.getValue());
        const float ty = track.getBottom() - track.getHeight() * v;
        g.setColour (dx::kPeri.withAlpha (0.55f)); g.fillRoundedRectangle (track.withTop (ty), 2.5f);   // fill below thumb
        auto thumb = juce::Rectangle<float> (cx - 11.0f, ty - 6.5f, 22.0f, 13.0f);                       // periwinkle thumb cap
        juce::ColourGradient tg (dx::kPeriHi, thumb.getCentreX(), thumb.getY(), dx::kPeri.darker (0.25f), thumb.getCentreX(), thumb.getBottom(), false);
        g.setGradientFill (tg); g.fillRoundedRectangle (thumb, 2.5f);
        g.setColour (juce::Colours::black.withAlpha (0.5f)); g.drawRoundedRectangle (thumb, 2.5f, 1.0f);
        g.setColour (juce::Colours::white.withAlpha (0.45f)); g.drawLine (thumb.getX() + 3.0f, thumb.getCentreY(), thumb.getRight() - 3.0f, thumb.getCentreY(), 1.0f);
    }
private:
    juce::Slider slider_;
    toi::InvisibleLinearLAF laf_;
    std::unique_ptr<toi::ParamKnobAttachment> att_;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DxFader)
};

//==============================================================================
// DxMembrane - a flat DX7-style membrane button: a slightly-domed rounded rect, dark face that
// glows green (or orange) when lit/active, with a label. Used for operator-select, presets, and
// the algorithm < > steppers. Optionally shows a small "carrier" dot (operator buttons).
class DxMembrane  : public juce::Button
{
public:
    explicit DxMembrane (const juce::String& t, juce::Colour accent = dx::kGreen)
        : juce::Button (t), accent_ (accent) { setButtonText (t); }
    void setActive (bool a) { if (active_ != a) { active_ = a; repaint(); } }
    void setCarrier (bool c) { if (carrier_ != c) { carrier_ = c; repaint(); } }
    void setShowDot (bool s) { showDot_ = s; }
    void flash() { flashing_ = true; repaint(); juce::Timer::callAfterDelay (140,
        [s = juce::Component::SafePointer<DxMembrane> (this)] { if (s) { s->flashing_ = false; s->repaint(); } }); }

    void paintButton (juce::Graphics& g, bool over, bool down) override
    {
        auto b = getLocalBounds().toFloat().reduced (1.2f);
        const bool lit = active_ || down || flashing_;
        if (lit) { g.setColour (accent_.withAlpha (0.35f)); g.fillRoundedRectangle (b.expanded (2.0f), 3.5f); }
        // dark bezel
        g.setColour (juce::Colour (0xff0c0905)); g.fillRoundedRectangle (b, 3.0f);
        auto inner = b.reduced (1.6f);
        const juce::Colour face = lit ? accent_ : juce::Colour (0xff24190f);
        juce::ColourGradient cg (face.brighter (lit ? 0.25f : 0.10f), inner.getCentreX(), inner.getY(),
                                 face.darker (lit ? 0.05f : 0.30f), inner.getCentreX(), inner.getBottom(), false);
        g.setGradientFill (cg); g.fillRoundedRectangle (inner, 2.2f);
        g.setColour (juce::Colours::white.withAlpha (lit ? 0.30f : 0.12f));
        g.fillRoundedRectangle (inner.withHeight (inner.getHeight() * 0.4f).reduced (1.0f, 0.0f), 2.0f);
        if (over && ! lit) { g.setColour (juce::Colours::white.withAlpha (0.08f)); g.fillRoundedRectangle (inner, 2.2f); }
        g.setColour (juce::Colours::black.withAlpha (0.5f)); g.drawRoundedRectangle (b, 3.0f, 1.0f);
        if (carrier_) { g.setColour (lit ? juce::Colours::black.withAlpha (0.6f) : dx::kGreenHi);
            const float dd = 4.0f; g.fillEllipse (inner.getRight() - dd - 2.0f, inner.getY() + 2.0f, dd, dd); }

        g.setColour (lit ? juce::Colour (0xff10180f) : dx::kCream);
        g.setFont (toi::uiFont (juce::jmin (10.5f, inner.getHeight() * 0.5f), true));
        g.drawText (getButtonText(), getLocalBounds(), juce::Justification::centred);
    }
private:
    juce::Colour accent_;
    bool active_ = false, carrier_ = false, showDot_ = false, flashing_ = false;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DxMembrane)
};

//==============================================================================
// DataSlider - the iconic DX7 vertical DATA-ENTRY slider: a recessed track with a green fill from
// the bottom + a wide ribbed silver/charcoal thumb. Directly drives a host param (no kit knob).
class DataSlider  : public juce::Component,
                    private juce::AudioProcessorParameter::Listener,
                    private juce::AsyncUpdater
{
public:
    DataSlider() = default;
    ~DataSlider() override { if (param_) param_->removeListener (this); cancelPendingUpdate(); }
    void attach (juce::AudioProcessorParameter* p) { if (param_) param_->removeListener (this); param_ = p; if (param_) param_->addListener (this); triggerAsyncUpdate(); }

    void mouseDown (const juce::MouseEvent& e) override { drag (e); }
    void mouseDrag (const juce::MouseEvent& e) override { drag (e); }
    void drag (const juce::MouseEvent& e)
    {
        if (! param_) return;
        auto tr = trackArea();
        const float v = juce::jlimit (0.0f, 1.0f, 1.0f - (e.position.y - tr.getY()) / tr.getHeight());
        param_->setValueNotifyingHost (v);
    }

    juce::Rectangle<float> trackArea() const { return getLocalBounds().toFloat().reduced (getWidth() * 0.32f, 6.0f); }

    void paint (juce::Graphics& g) override
    {
        auto tr = trackArea();
        // recessed track
        g.setColour (juce::Colour (0xff0a0805)); g.fillRoundedRectangle (tr.expanded (3.0f, 2.0f), 3.0f);
        g.setColour (juce::Colour (0xff060403)); g.fillRoundedRectangle (tr, 2.0f);
        const float v = param_ ? param_->getValue() : 0.0f;
        // green fill from bottom
        auto fill = tr.withTop (tr.getBottom() - tr.getHeight() * juce::jlimit (0.0f, 1.0f, v));
        g.setColour (dx::kGreen.withAlpha (0.85f)); g.fillRoundedRectangle (fill, 2.0f);
        g.setColour (dx::kGreenHi); g.fillRect (juce::Rectangle<float> (fill.getX(), fill.getY(), fill.getWidth(), 1.5f));
        // wide ribbed thumb
        const float ty = tr.getBottom() - tr.getHeight() * juce::jlimit (0.0f, 1.0f, v);
        auto thumb = juce::Rectangle<float> (getWidth() * 0.5f - 14.0f, ty - 9.0f, 28.0f, 18.0f);
        juce::ColourGradient tg (juce::Colour (0xff45403a), thumb.getCentreX(), thumb.getY(),
                                 juce::Colour (0xff16130f), thumb.getCentreX(), thumb.getBottom(), false);
        g.setGradientFill (tg); g.fillRoundedRectangle (thumb, 2.5f);
        g.setColour (juce::Colours::black.withAlpha (0.6f)); g.drawRoundedRectangle (thumb, 2.5f, 1.0f);
        g.setColour (juce::Colours::black.withAlpha (0.45f));
        for (int i = 0; i < 3; ++i) { const float yy = thumb.getCentreY() - 4.0f + i * 4.0f; g.drawLine (thumb.getX() + 4.0f, yy, thumb.getRight() - 4.0f, yy, 1.0f); }
        g.setColour (dx::kGreenHi.withAlpha (0.8f)); g.drawLine (thumb.getX() + 4.0f, thumb.getCentreY(), thumb.getRight() - 4.0f, thumb.getCentreY(), 1.2f);
    }
private:
    void parameterValueChanged (int, float) override { triggerAsyncUpdate(); }
    void parameterGestureChanged (int, bool) override {}
    void handleAsyncUpdate() override { repaint(); }
    juce::AudioProcessorParameter* param_ = nullptr;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DataSlider)
};

//==============================================================================
// AlgoView - the LIVE algorithm-routing diagram (the hero / signature interactive feature). Reads
// the exact 32 DX7 algorithm table, lays the 6 operators into a stack (carriers on the OUTPUT bar,
// modulators above the operator they feed), draws the modulation lines + the feedback loop, and
// fills carriers solid green. Clicking the left/right half steps the algorithm; it redraws live.
class AlgoView  : public juce::Component,
                  private juce::AudioProcessorParameter::Listener,
                  private juce::AsyncUpdater
{
public:
    AlgoView() = default;
    ~AlgoView() override { if (param_) param_->removeListener (this); cancelPendingUpdate(); }
    void attach (juce::AudioProcessorParameter* p) { if (param_) param_->removeListener (this); param_ = p; if (param_) param_->addListener (this); triggerAsyncUpdate(); }

    int algoNum() const { return param_ ? juce::jlimit (1, 32, juce::roundToInt (param_->getValue() * 31.0f) + 1) : 1; }

    void step (int d)
    {
        if (! param_) return;
        int a = algoNum() + d; if (a < 1) a = 32; if (a > 32) a = 1;
        param_->setValueNotifyingHost ((float) (a - 1) / 31.0f);
    }
    void mouseDown (const juce::MouseEvent& e) override { step (e.position.x < getWidth() * 0.5f ? -1 : 1); }

    void paint (juce::Graphics& g) override
    {
        auto r = getLocalBounds().toFloat();
        g.setColour (dx::kBox); g.fillRoundedRectangle (r, 4.0f);
        g.setColour (dx::kBoxEdge.withAlpha (0.7f)); g.drawRoundedRectangle (r, 4.0f, 1.0f);

        const int alg = algoNum();
        const int base = (alg - 1) * 6;

        // ---- decode routing into a multi-parent graph (a modulator can feed several carriers) ----
        int   par[6][6]; int npar[6];   // par[op] = the ops/-2(OUTPUT) that op feeds INTO
        bool  carrier[6] = { false,false,false,false,false,false };
        int   feedbackOp = -1;
        for (int i = 0; i < 6; ++i) npar[i] = 0;

        int writersA[6], nA = 0, writersB[6], nB = 0;
        auto addPar = [&] (int child, int dest) { for (int k = 0; k < npar[child]; ++k) if (par[child][k] == dest) return; par[child][npar[child]++] = dest; };
        for (int j = 0; j < 6; ++j)
        {
            const int op = 5 - j;                       // DX7 processing order OP6..OP1 -> index OP1..OP6
            const int flags = kAlgo[base + j];
            const int inbus  = (flags >> 4) & 3;
            const int outbus = flags & 3;
            const bool add   = (flags & 0x04) != 0;
            const bool fb    = (flags & 0xc0) == 0xc0;
            if (fb) feedbackOp = op;
            if (inbus == 1) for (int k = 0; k < nA; ++k) addPar (writersA[k], op);   // every pending bus-A writer feeds this op
            if (inbus == 2) for (int k = 0; k < nB; ++k) addPar (writersB[k], op);
            if      (outbus == 1) { if (! add) nA = 0; writersA[nA++] = op; }
            else if (outbus == 2) { if (! add) nB = 0; writersB[nB++] = op; }
            else                  { carrier[op] = true; addPar (op, -2); }
        }

        // depth = 1 + max(parent depth); carriers = 0 (relaxation, DAG depth <= 6)
        int depth[6]; for (int i = 0; i < 6; ++i) depth[i] = carrier[i] ? 0 : -1;
        for (int pass = 0; pass < 6; ++pass)
            for (int i = 0; i < 6; ++i) if (! carrier[i])
            {
                int mx = -1; bool ready = true;
                for (int k = 0; k < npar[i]; ++k) { const int p = par[i][k]; if (p >= 0) { if (depth[p] < 0) ready = false; else mx = juce::jmax (mx, depth[p]); } }
                if (ready && mx >= 0) depth[i] = mx + 1;
            }
        int maxDepth = 0; for (int i = 0; i < 6; ++i) { if (depth[i] < 0) depth[i] = 1; maxDepth = juce::jmax (maxDepth, depth[i]); }

        int carriersOrder[6], nc = 0; for (int i = 0; i < 6; ++i) if (carrier[i]) carriersOrder[nc++] = i;
        if (nc == 0) { carriersOrder[nc++] = 0; }

        auto pmask = [&] (int i) { int m = 0; for (int k = 0; k < npar[i]; ++k) if (par[i][k] >= 0) m |= (1 << par[i][k]); return m; };
        juce::ignoreUnused (maxDepth);

        // CONSTANT geometry across all 32 algorithms (global worst case = 4 rows, up to 6 boxes wide),
        // so the box size NEVER changes when you step through algorithms.
        auto area = r.reduced (14.0f, 0.0f).withTrimmedTop (14.0f).withTrimmedBottom (8.0f);
        const int   ROWS = 4;
        const float GAP  = 1.18f;
        const float colW = area.getWidth() / (float) nc;
        const float rowH = area.getHeight() / (float) ROWS;
        const float boxS = juce::jmin (34.0f, juce::jmin (rowH * 0.84f, area.getWidth() / 6.0f * 0.66f));

        float px[6], py[6];
        for (int i = 0; i < 6; ++i) { px[i] = -1.0f; py[i] = area.getBottom() - (depth[i] + 0.5f) * rowH; }
        for (int c = 0; c < nc; ++c) px[carriersOrder[c]] = area.getX() + (c + 0.5f) * colW;   // carriers in columns

        for (int d = 1; d < ROWS; ++d)
            for (int i = 0; i < 6; ++i)
            {
                if (depth[i] != d || px[i] >= 0.0f) continue;
                const int mi = pmask (i);
                int sib[6], ns = 0;                       // siblings = same depth + identical parent set
                for (int k = 0; k < 6; ++k) if (depth[k] == d && px[k] < 0.0f && pmask (k) == mi) sib[ns++] = k;
                float sx = 0.0f; int cp = 0;              // centre the group over the average x of what it feeds
                for (int k = 0; k < npar[i]; ++k) { const int p = par[i][k]; if (p >= 0 && px[p] >= 0.0f) { sx += px[p]; ++cp; } }
                const float span = (float) (ns - 1) * boxS * GAP;
                float basex = cp ? sx / (float) cp : area.getCentreX();
                basex = juce::jlimit (area.getX() + boxS * 0.5f + span * 0.5f, area.getRight() - boxS * 0.5f - span * 0.5f, basex);
                for (int s = 0; s < ns; ++s) px[sib[s]] = basex + (ns > 1 ? (s / (float) (ns - 1) - 0.5f) * span : 0.0f);
            }

        // OUTPUT bar
        g.setColour (dx::kGreenLo); g.fillRect (juce::Rectangle<float> (area.getX(), area.getBottom() + 2.0f, area.getWidth(), 2.0f));

        // edges (green lines from each op DOWN to every op / OUTPUT it modulates)
        g.setColour (dx::kGreen.withAlpha (0.85f));
        for (int i = 0; i < 6; ++i)
            for (int k = 0; k < npar[i]; ++k)
            {
                const int p = par[i][k];
                if (p == -2) g.drawLine (px[i], py[i] + boxS * 0.5f, px[i], area.getBottom() + 2.0f, 1.6f);
                else if (p >= 0) g.drawLine (px[i], py[i] + boxS * 0.5f, px[p], py[p] - boxS * 0.5f, 1.6f);
            }

        // operator boxes
        for (int i = 0; i < 6; ++i)
        {
            auto bx = juce::Rectangle<float> (px[i] - boxS * 0.5f, py[i] - boxS * 0.5f, boxS, boxS);
            if (carrier[i]) { g.setColour (dx::kGreen); g.fillRoundedRectangle (bx, 3.0f); }
            else { g.setColour (juce::Colour (0xff1c1409)); g.fillRoundedRectangle (bx, 3.0f); }
            g.setColour (carrier[i] ? juce::Colour (0xff0c180e) : dx::kGreen); g.drawRoundedRectangle (bx, 3.0f, 1.4f);
            g.setColour (carrier[i] ? juce::Colour (0xff0c180e) : dx::kCream);
            g.setFont (toi::uiFont (boxS * 0.5f, true));
            g.drawText (juce::String (i + 1), bx, juce::Justification::centred);
        }
        juce::ignoreUnused (feedbackOp);

        // header
        g.setColour (dx::kCream); g.setFont (toi::uiFont (8.0f, true).withExtraKerningFactor (0.12f));
        g.drawText ("ALGORITHM", r.withHeight (12.0f).reduced (6.0f, 1.0f), juce::Justification::centredLeft);
        g.setColour (dx::kGreenHi); g.setFont (toi::uiFont (13.0f, true));
        g.drawText (juce::String (alg), r.withHeight (13.0f).reduced (6.0f, 0.0f), juce::Justification::centredRight);
    }

    static const int kAlgo[192];

private:
    void parameterValueChanged (int, float) override { triggerAsyncUpdate(); }
    void parameterGestureChanged (int, bool) override {}
    void handleAsyncUpdate() override { repaint(); }
    juce::AudioProcessorParameter* param_ = nullptr;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AlgoView)
};

// the exact DX7 32-algorithm routing table (mirrors the engine), op order = DX7 processing order OP6..OP1
inline const int AlgoView::kAlgo[192] = {
    0xc1,0x11,0x11,0x14,0x01,0x14,  0x01,0x11,0x11,0x14,0xc1,0x14,  0xc1,0x11,0x14,0x01,0x11,0x14,  0xc1,0x11,0x94,0x01,0x11,0x14,
    0xc1,0x14,0x01,0x14,0x01,0x14,  0xc1,0x94,0x01,0x14,0x01,0x14,  0xc1,0x11,0x05,0x14,0x01,0x14,  0x01,0x11,0xc5,0x14,0x01,0x14,
    0x01,0x11,0x05,0x14,0xc1,0x14,  0x01,0x05,0x14,0xc1,0x11,0x14,  0xc1,0x05,0x14,0x01,0x11,0x14,  0x01,0x05,0x05,0x14,0xc1,0x14,
    0xc1,0x05,0x05,0x14,0x01,0x14,  0xc1,0x05,0x11,0x14,0x01,0x14,  0x01,0x05,0x11,0x14,0xc1,0x14,  0xc1,0x11,0x02,0x25,0x05,0x14,
    0x01,0x11,0x02,0x25,0xc5,0x14,  0x01,0x11,0x11,0xc5,0x05,0x14,  0xc1,0x14,0x14,0x01,0x11,0x14,  0x01,0x05,0x14,0xc1,0x14,0x14,
    0x01,0x14,0x14,0xc1,0x14,0x14,  0xc1,0x14,0x14,0x14,0x01,0x14,  0xc1,0x14,0x14,0x01,0x14,0x04,  0xc1,0x14,0x14,0x14,0x04,0x04,
    0xc1,0x14,0x14,0x04,0x04,0x04,  0xc1,0x05,0x14,0x01,0x14,0x04,  0x01,0x05,0x14,0xc1,0x14,0x04,  0x04,0xc1,0x11,0x14,0x01,0x14,
    0xc1,0x14,0x01,0x14,0x04,0x04,  0x04,0xc1,0x11,0x14,0x04,0x04,  0xc1,0x14,0x04,0x04,0x04,0x04,  0xc4,0x04,0x04,0x04,0x04,0x04
};

//==============================================================================
inline toi::Config jwdxConfig()
{
    toi::Config c;
    c.model = "JW-DX";
    auto& p = c.pal;
    p.bg = dx::kBrownHi; p.bg2 = dx::kBrownLo; p.frame = dx::kFrame; p.ink = dx::kFrame;
    p.accent = dx::kGreen; p.accent2 = dx::kOrange; p.button = juce::Colour (0xff24190f);
    p.thumb = dx::kCream; p.text = dx::kCream;
    p.noteStrip = juce::Colour (0xff1c140c);
    p.lcdBg = dx::kLcdBg; p.lcdInk = dx::kLcdInk;
    p.keyWhite = juce::Colour (0xffe9e3d4); p.keyWhitePr = juce::Colour (0xffd6d4f2);
    p.keyBlack = juce::Colour (0xff6f6db8); p.keyBlackPr = juce::Colour (0xff9d9bea);   // periwinkle (Jade's pick)

    c.params = {
        { "r1","RATIO" },{ "r2","RATIO" },{ "r3","RATIO" },{ "r4","RATIO" },{ "r5","RATIO" },{ "r6","RATIO" },
        { "fn1","FINE" },{ "fn2","FINE" },{ "fn3","FINE" },{ "fn4","FINE" },{ "fn5","FINE" },{ "fn6","FINE" },
        { "dt1","DETUNE" },{ "dt2","DETUNE" },{ "dt3","DETUNE" },{ "dt4","DETUNE" },{ "dt5","DETUNE" },{ "dt6","DETUNE" },
        { "ol1","LEVEL" },{ "ol2","LEVEL" },{ "ol3","LEVEL" },{ "ol4","LEVEL" },{ "ol5","LEVEL" },{ "ol6","LEVEL" },
        { "ea1","A" },{ "ea2","A" },{ "ea3","A" },{ "ea4","A" },{ "ea5","A" },{ "ea6","A" },
        { "ed1","D" },{ "ed2","D" },{ "ed3","D" },{ "ed4","D" },{ "ed5","D" },{ "ed6","D" },
        { "es1","S" },{ "es2","S" },{ "es3","S" },{ "es4","S" },{ "es5","S" },{ "es6","S" },
        { "er1","R" },{ "er2","R" },{ "er3","R" },{ "er4","R" },{ "er5","R" },{ "er6","R" },
        { "algo","ALGO" },{ "feedback","FEEDBACK" },
        { "lfoRate","RATE" },{ "lfoPMD","PMD" },{ "lfoAMD","AMD" },{ "lfoWave","WAVE" },
        { "volume","VOLUME" },{ "tune","TUNE" },
    };

    // base value vector (REAL units, matching c.params order + the engine min/max)
    std::vector<float> base = {
        1,1,1,3,1,1,           // ratio
        0,0,0,0,0,0,           // fine
        0.5f,0.5f,0.5f,0.5f,0.5f,0.5f,  // detune
        1.0f,0.62f,0.80f,0.45f,0.30f,0.42f,  // level
        0.02f,0.02f,0.02f,0.02f,0.02f,0.02f, // A
        0.55f,0.50f,0.55f,0.45f,0.45f,0.45f, // D
        0.70f,0.55f,0.65f,0.45f,0.40f,0.45f, // S
        0.30f,0.28f,0.30f,0.28f,0.28f,0.28f, // R
        1.0f, 0.30f,           // algo, feedback
        0.35f, 0.0f, 0.0f, 0.0f, // lfo
        0.80f, 0.50f };        // volume, tune
    enum { R1,R2,R3,R4,R5,R6, F1,F2,F3,F4,F5,F6, D1,D2,D3,D4,D5,D6, L1,L2,L3,L4,L5,L6,
           A1,A2,A3,A4,A5,A6, DC1,DC2,DC3,DC4,DC5,DC6, S1,S2,S3,S4,S5,S6, RL1,RL2,RL3,RL4,RL5,RL6,
           ALG,FB, LR,LPM,LAM,LW, VOL,TUN };
    auto P = [&] (const char* nm, std::initializer_list<std::pair<int,float>> ov)
    { auto v = base; for (auto& o : ov) v[(size_t) o.first] = o.second; return toi::FactoryPreset { nm, v }; };

    // a starter bank of recognizable FM voice types (algorithm + ratios + levels + EGs). These set
    // the right ARCHITECTURE per patch type; Jade tunes the exact sound by ear in her DAW.
    c.factory = {
        P("E.PIANO",   {{ALG,5},{L1,1.0f},{L2,0.55f},{L3,0.85f},{L4,0.40f},{L5,0.78f},{L6,0.30f},{R2,14},{R4,1},{R6,1},{D1,0.45f},{S1,0.40f},{FB,0.32f}}),
        P("TINE EP",   {{ALG,5},{R2,14},{L2,0.42f},{R4,3},{L4,0.5f},{R6,1},{L6,0.34f},{D1,0.40f},{S1,0.35f},{D3,0.4f},{S3,0.3f},{FB,0.40f}}),
        P("GLASS BELL",{{ALG,1},{R2,3.5f+0.5f},{L2,0.7f},{R4,7},{L4,0.6f},{R6,11},{L6,0.5f},{D1,0.6f},{S1,0.0f},{D3,0.6f},{S3,0.0f},{FB,0.25f}}),
        P("TUB BELLS", {{ALG,1},{R2,3.0f},{L2,0.8f},{R4,2.0f},{L4,0.6f},{R6,5.0f},{L6,0.55f},{D1,0.7f},{S1,0.0f},{D3,0.7f},{S3,0.0f},{R1,0.5f},{R3,0.5f}}),
        P("MARIMBA",   {{ALG,16},{R2,4.0f},{L2,0.55f},{D1,0.35f},{S1,0.0f},{R1,0.2f},{FB,0.15f}}),
        P("DX BASS",   {{ALG,16},{R2,1.0f},{L2,0.62f},{R3,2.0f},{L3,0.4f},{D1,0.40f},{S1,0.25f},{FB,0.45f},{VOL,0.85f}}),
        P("SLAP BASS", {{ALG,16},{R2,2.0f},{L2,0.7f},{A2,0.0f},{D2,0.25f},{S2,0.15f},{D1,0.35f},{S1,0.3f},{FB,0.55f}}),
        P("BRASS",     {{ALG,18},{L1,1.0f},{R2,1.0f},{L2,0.55f},{A1,0.18f},{A2,0.22f},{D1,0.5f},{S1,0.75f},{FB,0.30f}}),
        P("HARP",      {{ALG,19},{R2,1.0f},{L2,0.5f},{R4,3.0f},{L4,0.4f},{D1,0.6f},{S1,0.0f},{R1,0.45f},{FB,0.2f}}),
        P("CLAV",      {{ALG,3},{R2,1.0f},{L2,0.6f},{R4,2.0f},{L4,0.5f},{D1,0.35f},{S1,0.2f},{FB,0.5f}}),
        P("FM ORGAN",  {{ALG,32},{L1,0.7f},{L2,0.5f},{L3,0.45f},{L4,0.4f},{L5,0.35f},{L6,0.3f},{R2,2},{R3,4},{R4,1},{R5,8},{S1,1.0f},{S2,1.0f},{S3,1.0f},{S4,1.0f},{A1,0.04f}}),
        P("DIGI PAD",  {{ALG,4},{R2,1.0f},{L2,0.4f},{R4,2.0f},{L4,0.35f},{A1,0.4f},{A3,0.4f},{D1,0.7f},{S1,0.7f},{R1,0.6f},{R3,0.6f},{FB,0.25f},{LPM,0.12f}}),
    };
    return c;
}

//==============================================================================
class JWDXEditor  : public toi::PanelEditor
{
public:
    JWDXEditor (juce::AudioProcessor& proc, juce::MidiKeyboardState& kb)
        : toi::PanelEditor (proc, kb, jwdxConfig())
    {
        grain_ = makeGrain (140, 140);

        // hero: algorithm diagram + < > steppers
        algo_ = std::make_unique<AlgoView>();
        if (auto* a = findParam ("algo")) algo_->attach (a);
        addAndMakeVisible (*algo_);
        prev_ = std::make_unique<DxMembrane> ("<"); next_ = std::make_unique<DxMembrane> (">");
        prev_->onClick = [this] { algo_->step (-1); }; next_->onClick = [this] { algo_->step (1); };
        addAndMakeVisible (*prev_); addAndMakeVisible (*next_);

        // operator-select membrane buttons (OP1..OP6)
        for (int i = 0; i < 6; ++i)
        {
            auto b = std::make_unique<DxMembrane> (juce::String (i + 1));
            const int idx = i; b->onClick = [this, idx] { selectOp (idx); };
            addAndMakeVisible (*b); opBtns_.push_back (std::move (b));
        }

        // operator EDIT sliders (re-bind to the selected op): RATIO FINE DETUNE LEVEL  A D S R
        for (int i = 0; i < 8; ++i) { auto k = std::make_unique<DxFader>(); addAndMakeVisible (*k); editKnobs_.push_back (std::move (k)); }

        // global sliders
        auto addG = [&] (const juce::String& id) { auto k = std::make_unique<DxFader>(); if (auto* pr = findParam (id)) k->attach (*pr); addAndMakeVisible (*k); gMap_[id] = k.get(); gKnobs_.push_back (std::move (k)); };
        addG ("feedback"); addG ("lfoRate"); addG ("lfoPMD"); addG ("lfoAMD"); addG ("lfoWave"); addG ("tune");

        // the iconic DATA / VOLUME slider
        data_ = std::make_unique<DataSlider>(); data_->attach (findParam ("volume")); addAndMakeVisible (*data_);

        // green LCD scope (real audio)
        scope_ = std::make_unique<toi::Lcd> (pal()); scope_->attachScope (audioTap()); addAndMakeVisible (*scope_);

        // presets + RAND/SAVE
        for (int i = 0; i < 16; ++i) { auto b = std::make_unique<DxMembrane> (juce::String (i + 1)); const int idx = i; b->onClick = [this, idx] { recallSlot (idx); }; addAndMakeVisible (*b); slots_.push_back (std::move (b)); }
        rand_ = std::make_unique<DxMembrane> ("RAND", dx::kOrange); save_ = std::make_unique<DxMembrane> ("SAVE", dx::kOrange);
        rand_->onClick = [this] { doRandom(); rand_->flash(); };
        save_->onClick = [this] { saveSlot (activeSlot()); save_->flash(); };
        addAndMakeVisible (*rand_); addAndMakeVisible (*save_);

        finishSetup();
        selectOp (0);
    }

protected:
    void setPresetActiveVisual (int idx) override { for (int i = 0; i < (int) slots_.size(); ++i) slots_[(size_t) i]->setActive (i == idx); }

    static juce::Image makeGrain (int w, int h)
    {
        juce::Image img (juce::Image::ARGB, w, h, true);
        juce::Random r (1983);
        for (int y = 0; y < h; ++y) for (int x = 0; x < w; ++x)
        { const float n = r.nextFloat(); if (n > 0.66f) { const float a = (n - 0.66f) / 0.34f * 0.05f; const bool light = r.nextBool();
            img.setPixelAt (x, y, (light ? juce::Colours::white : juce::Colours::black).withAlpha (a)); } }
        return img;
    }

    void paintPanel (juce::Graphics& g, juce::Rectangle<float> panel) override
    {
        rPanel = panel;
        juce::ColourGradient pg (dx::kBrownHi, rPanel.getCentreX(), rPanel.getY(), dx::kBrownLo, rPanel.getCentreX(), rPanel.getBottom(), false);
        g.setGradientFill (pg); g.fillRoundedRectangle (rPanel, 5.0f);
        if (grain_.isValid()) { g.setFillType (juce::FillType (grain_, juce::AffineTransform::translation (rPanel.getX(), rPanel.getY()))); g.fillRoundedRectangle (rPanel, 5.0f); }
        g.setColour (juce::Colours::black); g.drawRoundedRectangle (rPanel, 5.0f, 1.5f);

        // OPERATORS box
        drawBox (g, rOpBox_, "OPERATORS");
        g.setColour (dx::kGreenHi); g.setFont (toi::uiFont (7.0f, true).withExtraKerningFactor (0.1f));
        g.drawText ("EDIT  OP " + juce::String (activeOp_ + 1), juce::Rectangle<float> (rOpBox_.getX() + 6.0f, rEditRow_.getY() - 10.0f, 120.0f, 9.0f), juce::Justification::centredLeft);
        // edit-knob labels
        g.setColour (dx::kDim); g.setFont (toi::uiFont (6.0f, true));
        const char* el[8] = { "RATIO","FINE","DETUNE","LEVEL","A","D","S","R" };
        for (int i = 0; i < 8; ++i) g.drawText (el[i], juce::Rectangle<float> (rEdit_[i].getX() - 6.0f, rEdit_[i].getBottom(), rEdit_[i].getWidth() + 12.0f, 9.0f), juce::Justification::centred);

        // LFO + MASTER box
        drawBox (g, rLfoBox_, "LFO");
        drawBox (g, rMastBox_, "MASTER");
        g.setColour (dx::kDim); g.setFont (toi::uiFont (6.0f, true));
        const char* gl[6] = { "RATE","PMD","AMD","WAVE","FBACK","TUNE" };
        juce::Rectangle<float>* gr[6] = { &rG_[1], &rG_[2], &rG_[3], &rG_[4], &rG_[0], &rG_[5] };
        for (int i = 0; i < 6; ++i) g.drawText (gl[i], juce::Rectangle<float> (gr[i]->getX() - 6.0f, gr[i]->getBottom(), gr[i]->getWidth() + 12.0f, 9.0f), juce::Justification::centred);

        // FEEDBACK lives under the algorithm
        g.setColour (dx::kCream); g.setFont (toi::uiFont (6.0f, true));

        // DATA slider label
        g.setColour (dx::kCream); g.setFont (toi::uiFont (6.5f, true).withExtraKerningFactor (0.1f));
        g.drawText ("DATA", juce::Rectangle<float> (rData_.getX() - 4.0f, rData_.getY() - 10.0f, rData_.getWidth() + 8.0f, 9.0f), juce::Justification::centred);
        g.drawText ("VOL",  juce::Rectangle<float> (rData_.getX() - 4.0f, rData_.getBottom() + 1.0f, rData_.getWidth() + 8.0f, 9.0f), juce::Justification::centred);

        // bottom strip labels
        g.setColour (dx::kCream); g.setFont (toi::uiFont (6.5f, true).withExtraKerningFactor (0.12f));
        g.drawText ("SCOPE", juce::Rectangle<float> (rScope_.getX(), rScope_.getY() - 9.0f, 120.0f, 9.0f), juce::Justification::centredLeft);
        g.drawText ("MEMORY", juce::Rectangle<float> (rPreset_.getX(), rPreset_.getY() - 9.0f, 160.0f, 9.0f), juce::Justification::centredLeft);

        // brand block (pale text on brown) + view LEDs
        auto bh = rBrand_;
        drawViewLeds (g, bh.removeFromTop (22.0f));
        bh.removeFromTop (3.0f);
        g.setColour (dx::kCream); g.setFont (toi::uiFont (15.0f, true).withExtraKerningFactor (0.05f));
        g.drawText ("JW-DX", bh, juce::Justification::centred);
    }

    void layoutPanel (juce::Rectangle<float> panel) override
    {
        rPanel = panel;
        auto inner = rPanel.reduced (12.0f, 9.0f);

        // bottom strip: scope | presets | RAND-SAVE | brand
        auto strip = inner.removeFromBottom (46.0f);
        inner.removeFromBottom (8.0f);
        {
            auto s = strip;
            rBrand_ = s.removeFromRight (140.0f); s.removeFromRight (8.0f);
            auto rs = s.removeFromRight (66.0f); s.removeFromRight (10.0f);
            rScope_ = s.removeFromLeft (230.0f); s.removeFromLeft (12.0f);
            rPreset_ = s;
            placeInArtboard (*scope_, rScope_);
            { auto pr = rPreset_; const int pc = 8; const float gp = 3.0f;
              const float pw = (pr.getWidth() - gp * (pc - 1)) / (float) pc;
              const float ph = (pr.getHeight() - gp) * 0.5f;
              for (int i = 0; i < 16; ++i) { const int rr = i / pc, cc = i % pc;
                placeInArtboard (*slots_[(size_t) i], juce::Rectangle<float> (pr.getX() + cc * (pw + gp), pr.getY() + rr * (ph + gp), pw, ph)); } }
            { auto ri = rs.reduced (0.0f, 3.0f); const float bh = (ri.getHeight() - 4.0f) * 0.5f;
              placeInArtboard (*rand_, ri.removeFromTop (bh)); ri.removeFromTop (4.0f); placeInArtboard (*save_, ri.removeFromTop (bh)); }
        }

        // upper area: [ALGO col] [OPERATORS center] [LFO/MASTER right] [DATA slider]
        auto upper = inner;
        rData_ = upper.removeFromRight (54.0f).reduced (4.0f, 2.0f); upper.removeFromRight (12.0f);
        placeInArtboard (*data_, rData_);

        auto algoCol = upper.removeFromLeft (300.0f); upper.removeFromLeft (12.0f);
        auto rightCol = upper.removeFromRight (330.0f); upper.removeFromLeft (12.0f);
        auto centerCol = upper;

        // ALGO column: a BIG diagram (fills the column) + a thin < > stepper strip (FEEDBACK -> MASTER)
        rAlgo_ = algoCol.removeFromTop (algoCol.getHeight() - 32.0f);
        placeInArtboard (*algo_, rAlgo_);
        algoCol.removeFromTop (6.0f);
        {
            auto row = algoCol;
            const float bw = (row.getWidth() - 10.0f) * 0.5f;
            placeInArtboard (*prev_, juce::Rectangle<float> (row.getX(), row.getCentreY() - 13.0f, bw, 26.0f));
            placeInArtboard (*next_, juce::Rectangle<float> (row.getX() + bw + 10.0f, row.getCentreY() - 13.0f, bw, 26.0f));
        }

        // OPERATORS center: op-select row (top) + edit-knob row
        rOpBox_ = centerCol;
        {
            auto in = centerCol.reduced (8.0f, 6.0f).withTrimmedTop (8.0f);
            rOpSel_ = in.removeFromTop (26.0f);
            { const int n = 6; const float gp = 6.0f; const float bw = (rOpSel_.getWidth() - gp * (n - 1)) / (float) n;
              for (int i = 0; i < 6; ++i) placeInArtboard (*opBtns_[(size_t) i], juce::Rectangle<float> (rOpSel_.getX() + i * (bw + gp), rOpSel_.getY(), bw, rOpSel_.getHeight())); }
            in.removeFromTop (14.0f);
            rEditRow_ = in;
            const int n = 8; const float gp = 6.0f; const float kw = (rEditRow_.getWidth() - gp * (n - 1)) / (float) n;
            const float fw = juce::jmin (kw, 28.0f), fh = rEditRow_.getHeight() - 11.0f;   // tall faders, label below
            for (int i = 0; i < 8; ++i)
            { auto cell = juce::Rectangle<float> (rEditRow_.getX() + i * (kw + gp), rEditRow_.getY(), kw, rEditRow_.getHeight());
              rEdit_[i] = juce::Rectangle<float> (cell.getCentreX() - fw * 0.5f, cell.getY(), fw, fh);
              placeInArtboard (*editKnobs_[(size_t) i], rEdit_[i]); }
        }

        // RIGHT column: LFO box (RATE PMD AMD WAVE) + MASTER box (TUNE)
        rLfoBox_ = rightCol.removeFromTop (rightCol.getHeight() * 0.56f);
        rightCol.removeFromTop (6.0f);
        rMastBox_ = rightCol;
        {
            auto in = rLfoBox_.reduced (8.0f, 6.0f).withTrimmedTop (10.0f);
            const char* ids[4] = { "lfoRate","lfoPMD","lfoAMD","lfoWave" };
            const int n = 4; const float gp = 6.0f; const float kw = (in.getWidth() - gp * (n - 1)) / (float) n;
            const float fw = juce::jmin (kw, 28.0f), fh = in.getHeight() - 11.0f;
            for (int i = 0; i < 4; ++i)
            { auto cell = juce::Rectangle<float> (in.getX() + i * (kw + gp), in.getY(), kw, in.getHeight());
              rG_[1 + i] = juce::Rectangle<float> (cell.getCentreX() - fw * 0.5f, cell.getY(), fw, fh);
              placeInArtboard (*gMap_[ids[i]], rG_[1 + i]); }
        }
        {
            auto in = rMastBox_.reduced (8.0f, 6.0f).withTrimmedTop (10.0f);
            const float cw = in.getWidth() * 0.5f;
            auto c0 = in.removeFromLeft (cw); auto c1 = in;
            const float fw = juce::jmin (28.0f, cw - 6.0f), fh = c0.getHeight() - 11.0f;
            rG_[0] = juce::Rectangle<float> (c0.getCentreX() - fw * 0.5f, c0.getY(), fw, fh);   // FEEDBACK
            rG_[5] = juce::Rectangle<float> (c1.getCentreX() - fw * 0.5f, c1.getY(), fw, fh);   // TUNE
            placeInArtboard (*gMap_["feedback"], rG_[0]);
            placeInArtboard (*gMap_["tune"], rG_[5]);
        }

        refreshOpButtons();
    }

private:
    void drawBox (juce::Graphics& g, juce::Rectangle<float> r, const juce::String& name)
    {
        g.setColour (dx::kBox); g.fillRoundedRectangle (r, 4.0f);
        g.setColour (dx::kBoxEdge.withAlpha (0.6f)); g.drawRoundedRectangle (r, 4.0f, 1.0f);
        g.setColour (dx::kCream); g.setFont (toi::uiFont (7.5f, true).withExtraKerningFactor (0.1f));
        g.drawText (name, r.withHeight (11.0f).reduced (6.0f, 1.0f), juce::Justification::centredLeft);
    }

    void selectOp (int i)
    {
        activeOp_ = juce::jlimit (0, 5, i);
        const int n = activeOp_ + 1;
        const char* pre[8] = { "r","fn","dt","ol","ea","ed","es","er" };
        for (int k = 0; k < 8; ++k) if (auto* pr = findParam (juce::String (pre[k]) + juce::String (n))) editKnobs_[(size_t) k]->attach (*pr);
        refreshOpButtons();
        repaint();
    }

    void refreshOpButtons()
    {
        const int alg = algo_ ? algo_->algoNum() : 1;
        const int base = (alg - 1) * 6;
        bool carrier[6] = { false,false,false,false,false,false };
        for (int j = 0; j < 6; ++j) { const int op = 5 - j; if ((AlgoView::kAlgo[base + j] & 3) == 0) carrier[op] = true; }
        for (int i = 0; i < 6; ++i) { opBtns_[(size_t) i]->setActive (i == activeOp_); opBtns_[(size_t) i]->setCarrier (carrier[i]); }
    }

    std::unique_ptr<AlgoView> algo_;
    std::unique_ptr<DxMembrane> prev_, next_, rand_, save_;
    std::vector<std::unique_ptr<DxMembrane>> opBtns_, slots_;
    std::vector<std::unique_ptr<DxFader>> editKnobs_, gKnobs_;
    std::map<juce::String, DxFader*> gMap_;
    std::unique_ptr<DataSlider> data_;
    std::unique_ptr<toi::Lcd> scope_;
    int activeOp_ = 0;
    juce::Image grain_;
    juce::Rectangle<float> rPanel, rAlgo_, rOpBox_, rOpSel_, rEditRow_, rLfoBox_, rMastBox_, rData_, rScope_, rPreset_, rBrand_;
    juce::Rectangle<float> rEdit_[8], rG_[6];
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JWDXEditor)
};

//==============================================================================
class JWDXPlugin  : public cmaj::plugin::GeneratedPlugin<::DX>,
                    public toi::AudioTapSource,
                    public toi::PresetStore
{
public:
    using Base = cmaj::plugin::GeneratedPlugin<::DX>;
    JWDXPlugin (std::shared_ptr<cmaj::Patch> p) : Base (std::move (p)) {}
    juce::AudioProcessorEditor* createEditor() override { return new JWDXEditor (*this, keyboardState); }
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
