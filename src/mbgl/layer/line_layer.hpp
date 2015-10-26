#ifndef MBGL_LINE_LAYER
#define MBGL_LINE_LAYER

#include <mbgl/style/style_layer.hpp>
#include <mbgl/style/style_properties.hpp>
#include <mbgl/style/paint_properties_map.hpp>
#include <mbgl/style/class_properties.hpp>
#include <mbgl/style/function_properties.hpp>

#include <rapidjson/document.h>

namespace mbgl {

using JSVal = rapidjson::Value;

template <typename T>
class LayoutProperty {
public:
    LayoutProperty(T v) : value(v) {}

    void parse(const char * name, const JSVal& layout);
    T calculate(float z) const;

    operator T() const { return value; }

    mapbox::util::optional<Function<T>> parsedValue;
    T value;
};

class LineLayoutProperties {
public:
    LayoutProperty<CapType>  cap        = CapType::Butt;
    LayoutProperty<JoinType> join       = JoinType::Miter;
    LayoutProperty<float>    miterLimit = 2.0f;
    LayoutProperty<float>    roundLimit = 1.0f;

    void parse(const JSVal&);
    void calculate(LineLayoutProperties&, float z) const;
};

class LineLayer : public StyleLayer {
public:
    void parseLayout(const JSVal&) override;
    void parsePaints(const JSVal&) override;

    void cascade(const StyleCascadeParameters&) override;
    void recalculate(const StyleCalculationParameters&) override;

    std::unique_ptr<Bucket> createBucket(StyleBucketParameters&) const override;

    bool hasTransitions() const override;

    LineLayoutProperties layout;
    PaintPropertiesMap paints;

    LinePaintProperties properties;
};

}

#endif
