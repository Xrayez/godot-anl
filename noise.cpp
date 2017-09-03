#include "noise.h"

AnlNoise::AnlNoise(): vm(kernel), eb(kernel) {}
//------------------------------------------------------------------------------
// Kernel methods
//------------------------------------------------------------------------------
Index AnlNoise::pi() {

    auto pi = kernel.pi();
    return pi.getIndex();
}

Index AnlNoise::e() {

    auto e = kernel.e();
    return e.getIndex();
}

Index AnlNoise::one() {

    auto one = kernel.one();
    return one.getIndex();
}

Index AnlNoise::zero() {

    auto zero = kernel.zero();
    return zero.getIndex();
}

Index AnlNoise::point5() {

    auto point5 = kernel.point5();
    return point5.getIndex();
}

Index AnlNoise::sqrt2() {

    auto sqrt2 = kernel.sqrt2();
    return sqrt2.getIndex();
}

Index AnlNoise::constant(double value) {

    auto constant = kernel.constant(value);
    return constant.getIndex();
}

Index AnlNoise::seed(unsigned int value) {

    auto seed = kernel.seed(value);
    return seed.getIndex();
}

Index AnlNoise::value_basis(Index interp, Index seed) {

    auto value_basis = kernel.valueBasis(kernel[interp], kernel[seed]);
    return value_basis.getIndex();
}

Index AnlNoise::gradient_basis(Index interp, Index seed) {

    auto gradient_basis = kernel.gradientBasis(kernel[interp], kernel[seed]);
    return gradient_basis.getIndex();
}

Index AnlNoise::simplex_basis(Index seed) {

    auto simplex_basis = kernel.simplexBasis(kernel[seed]);
    return simplex_basis.getIndex();
}

Index AnlNoise::cellular_basis(const PoolVector<int>& f,
                               const PoolVector<int>& d,
                               Index distance, Index seed) {

    ERR_FAIL_COND_V(f.size() < 4, 0);
    ERR_FAIL_COND_V(d.size() < 4, 0);

    auto cellular_basis = kernel.cellularBasis(
        kernel[ f[0] ], kernel[ f[1] ], kernel[ f[2] ], kernel[ f[3] ],
        kernel[ d[0] ], kernel[ d[1] ], kernel[ d[2] ], kernel[ d[3] ],
        kernel[distance], kernel[seed]
    );
    return cellular_basis.getIndex();
}

Index AnlNoise::add(Index src1, Index src2) {

    auto add = kernel.add(kernel[src1], kernel[src2]);
    return add.getIndex();
}

Index AnlNoise::subtract(Index src1, Index src2) {

    auto subtract = kernel.subtract(kernel[src1], kernel[src2]);
    return subtract.getIndex();
}

Index AnlNoise::multiply(Index src1, Index src2) {

    auto multiply = kernel.multiply(kernel[src1], kernel[src2]);
    return multiply.getIndex();
}

Index AnlNoise::divide(Index src1, Index src2) {

    auto divide = kernel.divide(kernel[src1], kernel[src2]);
    return divide.getIndex();
}

Index AnlNoise::maximum(Index src1, Index src2) {

    auto maximum = kernel.maximum(kernel[src1], kernel[src2]);
    return maximum.getIndex();
}

Index AnlNoise::minimum(Index src1, Index src2) {

    auto minimum = kernel.minimum(kernel[src1], kernel[src2]);
    return minimum.getIndex();
}

Index AnlNoise::abs(Index src) {

    auto abs = kernel.abs(kernel[src]);
    return abs.getIndex();
}

Index AnlNoise::pow(Index src1, Index src2) {

    auto pow = kernel.pow(kernel[src1], kernel[src2]);
    return pow.getIndex();
}

Index AnlNoise::bias(Index src1, Index src2) {

    auto bias = kernel.bias(kernel[src1], kernel[src2]);
    return bias.getIndex();
}

Index AnlNoise::gain(Index src1, Index src2) {

    auto gain = kernel.gain(kernel[src1], kernel[src2]);
    return gain.getIndex();
}

Index AnlNoise::scale(Index src, Index p_scale) {

    auto scale = kernel.scaleDomain(kernel[src], kernel[p_scale]);
    return scale.getIndex();
}

Index AnlNoise::scale_x(Index src, Index scale) {

    auto scale_x = kernel.scaleX(kernel[src], kernel[scale]);
    return scale_x.getIndex();
}

Index AnlNoise::scale_y(Index src, Index scale) {

    auto scale_y = kernel.scaleY(kernel[src], kernel[scale]);
    return scale_y.getIndex();
}

Index AnlNoise::scale_z(Index src, Index scale) {

    auto scale_z = kernel.scaleZ(kernel[src], kernel[scale]);
    return scale_z.getIndex();
}

Index AnlNoise::scale_w(Index src, Index scale) {

    auto scale_w = kernel.scaleW(kernel[src], kernel[scale]);
    return scale_w.getIndex();
}

Index AnlNoise::scale_u(Index src, Index scale) {

    auto scale_u = kernel.scaleU(kernel[src], kernel[scale]);
    return scale_u.getIndex();
}

Index AnlNoise::scale_v(Index src, Index scale) {

    auto scale_v = kernel.scaleV(kernel[src], kernel[scale]);
    return scale_v.getIndex();
}

Index AnlNoise::translate(Index src, Index p_translate) {

    auto translate = kernel.translateDomain(kernel[src], kernel[p_translate]);
    return translate.getIndex();
}

Index AnlNoise::translate_x(Index src, Index translate) {

    auto translate_x = kernel.translateX(kernel[src], kernel[translate]);
    return translate_x.getIndex();
}

Index AnlNoise::translate_y(Index src, Index translate) {

    auto translate_y = kernel.translateY(kernel[src], kernel[translate]);
    return translate_y.getIndex();
}

Index AnlNoise::translate_z(Index src, Index translate) {

    auto translate_z = kernel.translateZ(kernel[src], kernel[translate]);
    return translate_z.getIndex();
}

Index AnlNoise::translate_w(Index src, Index translate) {

    auto translate_w = kernel.translateW(kernel[src], kernel[translate]);
    return translate_w.getIndex();
}

Index AnlNoise::translate_u(Index src, Index translate) {

    auto translate_u = kernel.translateU(kernel[src], kernel[translate]);
    return translate_u.getIndex();
}

Index AnlNoise::translate_v(Index src, Index translate) {

    auto translate_v = kernel.translateV(kernel[src], kernel[translate]);
    return translate_v.getIndex();
}

Index AnlNoise::rotate(Index src, Index angle, Index ax, Index ay, Index az) {

    auto rotate = kernel.rotateDomain(
        kernel[src], kernel[angle], kernel[ax], kernel[ay], kernel[az]
    );
    return rotate.getIndex();
}

Index AnlNoise::add_sequence(Index base, unsigned int number, unsigned int stride) {

    auto add_sequence = kernel.addSequence(
        kernel[base], number, stride
    );
    return add_sequence.getIndex();
}

Index AnlNoise::multiply_sequence(Index base, unsigned int number, unsigned int stride) {

    auto multiply_sequence = kernel.multiplySequence(
        kernel[base], number, stride
    );
    return multiply_sequence.getIndex();
}

Index AnlNoise::max_sequence(Index base, unsigned int number, unsigned int stride) {

    auto max_sequence = kernel.maxSequence(
        kernel[base], number, stride
    );
    return max_sequence.getIndex();
}

Index AnlNoise::min_sequence(Index base, unsigned int number, unsigned int stride) {

    auto min_sequence = kernel.minSequence(
        kernel[base], number, stride
    );
    return min_sequence.getIndex();
}

Index AnlNoise::blend(Index low, Index high, Index control) {

    auto blend = kernel.blend(kernel[low], kernel[high], kernel[control]);
    return blend.getIndex();
}

Index AnlNoise::select(Index low, Index high, Index control,
                       Index threshold, Index falloff) {

    auto select = kernel.select(
        kernel[low], kernel[high], kernel[control],
        kernel[threshold], kernel[falloff]
    );
    return select.getIndex();
}

Index AnlNoise::clamp(Index src, Index low, Index high) {

    auto clamp = kernel.clamp(kernel[src], kernel[low], kernel[high]);
    return clamp.getIndex();
}

Index AnlNoise::cos(Index src) {

    auto cos = kernel.cos(kernel[src]);
    return cos.getIndex();
}

Index AnlNoise::sin(Index src) {

    auto sin = kernel.sin(kernel[src]);
    return sin.getIndex();
}

Index AnlNoise::tan(Index src) {

    auto tan = kernel.tan(kernel[src]);
    return tan.getIndex();
}

Index AnlNoise::acos(Index src) {

    auto acos = kernel.acos(kernel[src]);
    return acos.getIndex();
}

Index AnlNoise::asin(Index src) {

    auto asin = kernel.asin(kernel[src]);
    return asin.getIndex();
}

Index AnlNoise::atan(Index src) {

    auto atan = kernel.atan(kernel[src]);
    return atan.getIndex();
}

Index AnlNoise::tiers(Index src, Index num_tiers) {

    auto tiers = kernel.tiers(kernel[src], kernel[num_tiers]);
    return tiers.getIndex();
}

Index AnlNoise::smooth_tiers(Index src, Index num_tiers) {

    auto smooth_tiers = kernel.smoothTiers(kernel[src], kernel[num_tiers]);
    return smooth_tiers.getIndex();
}

Index AnlNoise::x() {

    auto x = kernel.x();
    return x.getIndex();
}

Index AnlNoise::y() {

    auto y = kernel.y();
    return y.getIndex();
}

Index AnlNoise::z() {

    auto z = kernel.z();
    return z.getIndex();
}

Index AnlNoise::w() {

    auto w = kernel.w();
    return w.getIndex();
}

Index AnlNoise::u() {

    auto u = kernel.u();
    return u.getIndex();
}

Index AnlNoise::v() {

    auto v = kernel.v();
    return v.getIndex();
}

Index AnlNoise::dx(Index src, Index spacing) {

    auto dx = kernel.dx(kernel[src], kernel[spacing]);
    return dx.getIndex();
}

Index AnlNoise::dy(Index src, Index spacing) {

    auto dy = kernel.dy(kernel[src], kernel[spacing]);
    return dy.getIndex();
}

Index AnlNoise::dz(Index src, Index spacing) {

    auto dz = kernel.dz(kernel[src], kernel[spacing]);
    return dz.getIndex();
}

Index AnlNoise::dw(Index src, Index spacing) {

    auto dw = kernel.dw(kernel[src], kernel[spacing]);
    return dw.getIndex();
}

Index AnlNoise::du(Index src, Index spacing) {

    auto du = kernel.du(kernel[src], kernel[spacing]);
    return du.getIndex();
}

Index AnlNoise::dv(Index src, Index spacing) {

    auto dv = kernel.dv(kernel[src], kernel[spacing]);
    return dv.getIndex();
}

Index AnlNoise::sigmoid(Index src, Index center, Index ramp) {

    auto sigmoid = kernel.sigmoid(kernel[src], kernel[center], kernel[ramp]);
    return sigmoid.getIndex();
}

Index AnlNoise::radial() {

    auto radial = kernel.radial();
    return radial.getIndex();
}

// Patterns

Index AnlNoise::hex_tile(Index seed) {

    auto hex_tile = kernel.hexTile(kernel[seed]);
    return hex_tile.getIndex();
}

Index AnlNoise::hex_bump() {

    auto hex_bump = kernel.hexBump();
    return hex_bump.getIndex();
}

Index AnlNoise::color(const Color& c) {

    auto color = kernel.color(anl::SRGBA(c.r, c.g, c.b, c.a));
    return color.getIndex();
}

Index AnlNoise::combine_rgba(Index r, Index g, Index b, Index a) {

    auto combine_rgba = kernel.combineRGBA(
        kernel[r], kernel[g], kernel[b], kernel[a]
    );
    return combine_rgba.getIndex();
}

//------------------------------------------------------------------------------
// NoiseExecutor methods
//------------------------------------------------------------------------------
double AnlNoise::scalar_2d(double x, double y, Index index) {

    return vm.evaluateScalar(x, y, index);
}

Color AnlNoise::color_2d(double x, double y, Index index) {

    anl::SRGBA c = vm.evaluateColor(x, y, index);
    return Color(c.r, c.g, c.b, c.a);
}

void AnlNoise::_bind_methods() {

    ClassDB::bind_method(D_METHOD("pi"),&AnlNoise::pi);
    ClassDB::bind_method(D_METHOD("e"),&AnlNoise::e);
    ClassDB::bind_method(D_METHOD("one"),&AnlNoise::one);
    ClassDB::bind_method(D_METHOD("zero"),&AnlNoise::zero);
    ClassDB::bind_method(D_METHOD("point5"),&AnlNoise::point5);
    ClassDB::bind_method(D_METHOD("sqrt2"),&AnlNoise::sqrt2);

    ClassDB::bind_method(D_METHOD("constant", "value"),&AnlNoise::constant);
    ClassDB::bind_method(D_METHOD("seed", "value"),&AnlNoise::seed);

    ClassDB::bind_method(D_METHOD("value_basis", "interp_index", "seed_index"),&AnlNoise::value_basis);
    ClassDB::bind_method(D_METHOD("gradient_basis", "interp_index", "seed_index"),&AnlNoise::gradient_basis);
    ClassDB::bind_method(D_METHOD("simplex_basis", "seed_index"),&AnlNoise::simplex_basis);
    ClassDB::bind_method(D_METHOD("cellular_basis", "f4_indexes", "d4_indexes", "distance_index", "seed_index"),&AnlNoise::cellular_basis);

    ClassDB::bind_method(D_METHOD("add", "src1_index", "src2_index"),&AnlNoise::add);
    ClassDB::bind_method(D_METHOD("subtract", "src1_index", "src2_index"),&AnlNoise::subtract);
    ClassDB::bind_method(D_METHOD("multiply", "src1_index", "src2_index"),&AnlNoise::multiply);
    ClassDB::bind_method(D_METHOD("divide", "src1_index", "src2_index"),&AnlNoise::divide);
    ClassDB::bind_method(D_METHOD("maximum", "src1_index", "src2_index"),&AnlNoise::maximum);
    ClassDB::bind_method(D_METHOD("minimum", "src1_index", "src2_index"),&AnlNoise::minimum);
    ClassDB::bind_method(D_METHOD("abs", "src_index"),&AnlNoise::abs);
    ClassDB::bind_method(D_METHOD("pow", "src1_index", "src2_index"),&AnlNoise::pow);
    ClassDB::bind_method(D_METHOD("bias", "src1_index", "src2_index"),&AnlNoise::bias);
    ClassDB::bind_method(D_METHOD("gain", "src1_index", "src2_index"),&AnlNoise::gain);

    ClassDB::bind_method(D_METHOD("scale", "src_index", "scale_index"),&AnlNoise::scale);

    ClassDB::bind_method(D_METHOD("scale_x", "src_index", "scale_index"),&AnlNoise::scale_x);
    ClassDB::bind_method(D_METHOD("scale_y", "src_index", "scale_index"),&AnlNoise::scale_y);
    ClassDB::bind_method(D_METHOD("scale_z", "src_index", "scale_index"),&AnlNoise::scale_z);
    ClassDB::bind_method(D_METHOD("scale_w", "src_index", "scale_index"),&AnlNoise::scale_w);
    ClassDB::bind_method(D_METHOD("scale_u", "src_index", "scale_index"),&AnlNoise::scale_u);
    ClassDB::bind_method(D_METHOD("scale_v", "src_index", "scale_index"),&AnlNoise::scale_v);

    ClassDB::bind_method(D_METHOD("translate", "src_index", "translate_index"),&AnlNoise::translate);

    ClassDB::bind_method(D_METHOD("translate_x", "src_index", "translate_index"),&AnlNoise::translate_x);
    ClassDB::bind_method(D_METHOD("translate_y", "src_index", "translate_index"),&AnlNoise::translate_y);
    ClassDB::bind_method(D_METHOD("translate_z", "src_index", "translate_index"),&AnlNoise::translate_z);
    ClassDB::bind_method(D_METHOD("translate_w", "src_index", "translate_index"),&AnlNoise::translate_w);
    ClassDB::bind_method(D_METHOD("translate_u", "src_index", "translate_index"),&AnlNoise::translate_u);
    ClassDB::bind_method(D_METHOD("translate_v", "src_index", "translate_index"),&AnlNoise::translate_v);

    ClassDB::bind_method(D_METHOD("rotate", "src_index", "angle_index", "ax_index", "ay_index", "az_index"),&AnlNoise::rotate);

    ClassDB::bind_method(D_METHOD("add_sequence", "base_index", "number", "stride"),AnlNoise::add_sequence, DEFVAL(1));
    ClassDB::bind_method(D_METHOD("multiply_sequence", "base_index", "number", "stride"),AnlNoise::multiply_sequence, DEFVAL(1));
    ClassDB::bind_method(D_METHOD("max_sequence", "base_index", "number", "stride"),AnlNoise::max_sequence, DEFVAL(1));
    ClassDB::bind_method(D_METHOD("min_sequence", "base_index", "number", "stride"),AnlNoise::min_sequence, DEFVAL(1));

    ClassDB::bind_method(D_METHOD("blend", "low_index", "high_index", "control_index"),&AnlNoise::blend);
    ClassDB::bind_method(D_METHOD("select", "low_index", "high_index", "control_index", "threshold_index", "falloff_index"),&AnlNoise::select);
    ClassDB::bind_method(D_METHOD("clamp", "src_index", "low_index", "high_index"),&AnlNoise::clamp);

    ClassDB::bind_method(D_METHOD("cos", "src_index"),&AnlNoise::cos);
    ClassDB::bind_method(D_METHOD("sin", "src_index"),&AnlNoise::sin);
    ClassDB::bind_method(D_METHOD("tan", "src_index"),&AnlNoise::tan);
    ClassDB::bind_method(D_METHOD("acos", "src_index"),&AnlNoise::acos);
    ClassDB::bind_method(D_METHOD("asin", "src_index"),&AnlNoise::asin);
    ClassDB::bind_method(D_METHOD("atan", "src_index"),&AnlNoise::atan);

    ClassDB::bind_method(D_METHOD("tiers", "src_index", "num_tiers_index"),&AnlNoise::tiers);
    ClassDB::bind_method(D_METHOD("smooth_tiers", "src_index", "num_tiers_index"),&AnlNoise::smooth_tiers);

    ClassDB::bind_method(D_METHOD("x"),&AnlNoise::x);
    ClassDB::bind_method(D_METHOD("y"),&AnlNoise::y);
    ClassDB::bind_method(D_METHOD("z"),&AnlNoise::z);
    ClassDB::bind_method(D_METHOD("w"),&AnlNoise::w);
    ClassDB::bind_method(D_METHOD("u"),&AnlNoise::u);
    ClassDB::bind_method(D_METHOD("v"),&AnlNoise::v);

    ClassDB::bind_method(D_METHOD("dx", "src_index", "spacing_index"),&AnlNoise::dx);
    ClassDB::bind_method(D_METHOD("dy", "src_index", "spacing_index"),&AnlNoise::dy);
    ClassDB::bind_method(D_METHOD("dz", "src_index", "spacing_index"),&AnlNoise::dz);
    ClassDB::bind_method(D_METHOD("dw", "src_index", "spacing_index"),&AnlNoise::dw);
    ClassDB::bind_method(D_METHOD("du", "src_index", "spacing_index"),&AnlNoise::du);
    ClassDB::bind_method(D_METHOD("dv", "src_index", "spacing_index"),&AnlNoise::dv);

    ClassDB::bind_method(D_METHOD("sigmoid", "src_index", "center_index", "ramp_index"),&AnlNoise::sigmoid);
    ClassDB::bind_method(D_METHOD("radial"),&AnlNoise::radial);

    ClassDB::bind_method(D_METHOD("hex_tile", "seed_index"),&AnlNoise::hex_tile);
    ClassDB::bind_method(D_METHOD("hex_bump"),&AnlNoise::hex_bump);

    ClassDB::bind_method(D_METHOD("color", "color"),&AnlNoise::color);
    ClassDB::bind_method(D_METHOD("combine_rgba", "r_index", "g_index", "b_index", "a_index"),&AnlNoise::combine_rgba);


    ClassDB::bind_method(D_METHOD("scalar_2d", "x", "y", "index"),&AnlNoise::scalar_2d);

    ClassDB::bind_method(D_METHOD("color_2d", "x", "y", "index"),&AnlNoise::color_2d);

    using namespace anl;
    // Use namespace declaration to avoid having
    // prepended namespace name in enum constants
    BIND_ENUM_CONSTANT(INTERP_NONE);
    BIND_ENUM_CONSTANT(INTERP_LINEAR);
    BIND_ENUM_CONSTANT(INTERP_HERMITE);
    BIND_ENUM_CONSTANT(INTERP_QUINTIC);

    BIND_ENUM_CONSTANT(DISTANCE_EUCLID);
    BIND_ENUM_CONSTANT(DISTANCE_MANHATTAN);
    BIND_ENUM_CONSTANT(DISTANCE_LEASTAXIS);
    BIND_ENUM_CONSTANT(DISTANCE_GREATESTAXIS);

    BIND_ENUM_CONSTANT(BASIS_VALUE);
    BIND_ENUM_CONSTANT(BASIS_GRADIENT);
    BIND_ENUM_CONSTANT(BASIS_SIMPLEX);
}