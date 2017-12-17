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

Index AnlNoise::seeder(Index seed, Index src) {

    auto seeder = kernel.seeder(kernel[seed], kernel[src]);
    return seeder.getIndex();
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

Index AnlNoise::mix(Index low, Index high, Index control) {

    auto mix = kernel.mix(kernel[low], kernel[high], kernel[control]);
    return mix.getIndex();
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

Index AnlNoise::fractal(Index seed, Index layer, const PoolVector<int>& params) {

    ERR_FAIL_COND_V(params.size() < 4, 0);

    Index persistence = params[0];
    Index lacunarity = params[1];
    Index numoctaves = params[2];
    Index freq = params[3];

    auto fractal = kernel.fractal(
        kernel[seed], kernel[layer],
        kernel[persistence], kernel[lacunarity], kernel[numoctaves], kernel[freq]
    );
    return fractal.getIndex();
}

Index AnlNoise::randomize(Index seed, Index low, Index high) {

    auto randomize = kernel.randomize(kernel[seed], kernel[low], kernel[high]);
    return randomize.getIndex();
}

Index AnlNoise::step(Index val, Index control) {

    auto step = kernel.step(kernel[val], kernel[control]);
    return step.getIndex();
}

Index AnlNoise::linear_step(Index low, Index high, Index control) {

    auto linear_step = kernel.linearStep(kernel[low], kernel[high], kernel[control]);
    return linear_step.getIndex();
}

Index AnlNoise::smooth_step(Index low, Index high, Index control) {

    auto smooth_step = kernel.smoothStep(kernel[low], kernel[high], kernel[control]);
    return smooth_step.getIndex();
}

Index AnlNoise::smoother_step(Index low, Index high, Index control) {

    auto smoother_step = kernel.smootherStep(kernel[low], kernel[high], kernel[control]);
    return smoother_step.getIndex();
}

Index AnlNoise::curve_section(Index lowv,
                              const PoolVector<int>& t,
                              const PoolVector<int>& v,
                              Index control) {

    ERR_FAIL_COND_V(t.size() < 2, 0);
    ERR_FAIL_COND_V(v.size() < 2, 0);

    auto curve_section = kernel.curveSection(
        kernel[lowv],
        kernel[ t[0] ], kernel[ t[1] ], kernel[ v[0] ] , kernel[ v[1] ],
        kernel[control]
    );
    return curve_section.getIndex();
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

Index AnlNoise::combine_hsva(Index h, Index s, Index v, Index a) {

    auto combine_hsva = kernel.combineHSVA(
        kernel[h], kernel[s], kernel[v], kernel[a]
    );
    return combine_hsva.getIndex();
}

Index AnlNoise::scale_offset(Index src, double scale, double offset) {

    auto scale_offset = kernel.scaleOffset(
        kernel[src], scale, offset
    );
    return scale_offset.getIndex();
}

Index AnlNoise::fractal_layer(anl::BasisTypes basis, Index interp_type,
                              const PoolVector<real_t>& layer_params,
                              const PoolVector<real_t>& axis_params,
                              bool rot) {

    ERR_FAIL_COND_V(layer_params.size() < 4, 0);
    ERR_FAIL_COND_V(axis_params.size() < 3, 0);

    // layer_params: scale, freq, seed, angle
    // axis_params:  ax, ay, az

    auto fractal_layer = kernel.simpleFractalLayer(
        basis, kernel[interp_type],
        layer_params[0], layer_params[1], layer_params[2],
        rot, layer_params[3],
        axis_params[0], axis_params[1], axis_params[2]
    );
    return fractal_layer.getIndex();
}

Index AnlNoise::ridged_layer(anl::BasisTypes basis, Index interp_type,
                              const PoolVector<real_t>& layer_params,
                              const PoolVector<real_t>& axis_params,
                              bool rot) {

    ERR_FAIL_COND_V(layer_params.size() < 4, 0);
    ERR_FAIL_COND_V(axis_params.size() < 3, 0);

    // layer_params: scale, freq, seed, angle
    // axis_params:  ax, ay, az

    auto ridged_layer = kernel.simpleRidgedLayer(
        basis, kernel[interp_type],
        layer_params[0], layer_params[1], layer_params[2],
        rot, layer_params[3],
        axis_params[0], axis_params[1], axis_params[2]
    );
    return ridged_layer.getIndex();
}

Index AnlNoise::billow_layer(anl::BasisTypes basis, Index interp_type,
                              const PoolVector<real_t>& layer_params,
                              const PoolVector<real_t>& axis_params,
                              bool rot) {

    ERR_FAIL_COND_V(layer_params.size() < 4, 0);
    ERR_FAIL_COND_V(axis_params.size() < 3, 0);

    // layer_params: scale, freq, seed, angle
    // axis_params:  ax, ay, az

    auto billow_layer = kernel.simpleBillowLayer(
        basis, kernel[interp_type],
        layer_params[0], layer_params[1], layer_params[2],
        rot, layer_params[3],
        axis_params[0], axis_params[1], axis_params[2]
    );
    return billow_layer.getIndex();
}

Index AnlNoise::fbm(anl::BasisTypes basis, anl::InterpolationTypes interp,
          const PoolVector<real_t>& params,
          bool rot) {

    ERR_FAIL_COND_V(params.size() < 3, 0);

    // params: octaves, frequency, seed

    auto fbm = kernel.simplefBm(
        basis, interp,
        params[0], params[1], params[2],
        rot
    );
    return fbm.getIndex();
}

Index AnlNoise::ridged_multifractal(anl::BasisTypes basis, anl::InterpolationTypes interp,
                                    const PoolVector<real_t>& params,
                                    bool rot) {

    ERR_FAIL_COND_V(params.size() < 3, 0);

    // params: octaves, frequency, seed

    auto ridged_multifractal = kernel.simpleRidgedMultifractal(
        basis, interp,
        params[0], params[1], params[2],
        rot
    );
    return ridged_multifractal.getIndex();
}

Index AnlNoise::billow(anl::BasisTypes basis, anl::InterpolationTypes interp,
                       const PoolVector<real_t>& params,
                       bool rot) {

    ERR_FAIL_COND_V(params.size() < 3, 0);

    // params: octaves, frequency, seed

    auto billow = kernel.simpleBillow(
        basis, interp,
        params[0], params[1], params[2],
        rot
    );
    return billow.getIndex();
}

// Kernel

Index AnlNoise::get_last_index() {

    return kernel.lastIndex().getIndex();
}

//------------------------------------------------------------------------------
// NoiseExecutor methods
//------------------------------------------------------------------------------
double AnlNoise::get_scalar_2d(double x, double y, Index index) {

    return vm.evaluateScalar(x, y, index);
}

double AnlNoise::get_scalar_3d(double x, double y, double z, Index index) {

    return vm.evaluateScalar(x, y, z, index);
}

double AnlNoise::get_scalar_4d(double x, double y, double z, double w, Index index) {

    return vm.evaluateScalar(x, y, z, w, index);
}

double AnlNoise::get_scalar_6d(const PoolVector<real_t>& axis, Index index) {

    return vm.evaluateScalar(axis[0], axis[1], axis[2],
                             axis[3], axis[4], axis[5], index);
}

Color AnlNoise::get_color_2d(double x, double y, Index index) {

    anl::SRGBA c = vm.evaluateColor(x, y, index);
    return Color(c.r, c.g, c.b, c.a);
}

Color AnlNoise::get_color_3d(double x, double y, double z, Index index) {

    anl::SRGBA c = vm.evaluateColor(x, y, z, index);
    return Color(c.r, c.g, c.b, c.a);
}

Color AnlNoise::get_color_4d(double x, double y, double z, double w, Index index) {

    anl::SRGBA c = vm.evaluateColor(x, y, z, w, index);
    return Color(c.r, c.g, c.b, c.a);
}

Color AnlNoise::get_color_6d(const PoolVector<real_t>& axis, Index index) {

    anl::SRGBA c = vm.evaluateColor(axis[0], axis[1], axis[2],
                                    axis[3], axis[4], axis[5], index);
    return Color(c.r, c.g, c.b, c.a);
}
//------------------------------------------------------------------------------
// ExpressionBuilder methods
//------------------------------------------------------------------------------
Index AnlNoise::evaluate(const String& expression) {

    auto function = eb.eval(expression.utf8().get_data());
    return function.getIndex();
}

//------------------------------------------------------------------------------
// Image methods
//------------------------------------------------------------------------------
Ref<Image> AnlNoise::map_to_image(const Vector2& size,
                                  anl::EMappingModes mode,
                                  Index index,
                                  const Vector2& map_start,
                                  const Vector2& map_end) {

    anl::CArray2Drgba img(size.x, size.y);
    anl::SMappingRanges ranges(map_start.x, map_end.x, map_start.y, map_end.y);
    anl::mapRGBA2DNoZ(mode, img, kernel, ranges, index);

    PoolVector<uint8_t> data;
    const int SIZE = size.x * size.y;
    data.resize(SIZE * 4);
    PoolVector<uint8_t>::Write w = data.write();
    anl::SRGBA* src_data = img.getData();

    for(int i = 0, j = 0; j < SIZE; i += 4, ++j) {
        w[i + 0] = static_cast<uint8_t>(src_data[j].r * 255);
        w[i + 1] = static_cast<uint8_t>(src_data[j].g * 255);
        w[i + 2] = static_cast<uint8_t>(src_data[j].b * 255);
        w[i + 3] = static_cast<uint8_t>(src_data[j].a * 255);
    }
    Ref<Image> noise = memnew(Image);
    noise->create(size.x, size.y, 0, Image::FORMAT_RGBA8, data);
    return noise;
}

void AnlNoise::gen_texture(const Vector2& size, anl::EMappingModes mode,
                           Index index, const String& filename) {

    // Experimental
    anl::CArray2Drgba img(size.x, size.y);
    anl::mapRGBA2DNoZ(mode, img, kernel, anl::SMappingRanges(), index);
    anl::saveRGBAArray(filename.utf8().get_data(), &img);
}

void AnlNoise::_bind_methods() {

    // Kernel methods

    ClassDB::bind_method(D_METHOD("pi"),&AnlNoise::pi);
    ClassDB::bind_method(D_METHOD("e"),&AnlNoise::e);
    ClassDB::bind_method(D_METHOD("one"),&AnlNoise::one);
    ClassDB::bind_method(D_METHOD("zero"),&AnlNoise::zero);
    ClassDB::bind_method(D_METHOD("point5"),&AnlNoise::point5);
    ClassDB::bind_method(D_METHOD("sqrt2"),&AnlNoise::sqrt2);

    ClassDB::bind_method(D_METHOD("constant", "value"),&AnlNoise::constant);
    ClassDB::bind_method(D_METHOD("seed", "value"),&AnlNoise::seed);
    ClassDB::bind_method(D_METHOD("seeder", "seed_index", "src_index"),&AnlNoise::seeder);

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

    ClassDB::bind_method(D_METHOD("mix", "low_index", "high_index", "control_index"),&AnlNoise::mix);
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

    ClassDB::bind_method(D_METHOD("fractal", "seed_index", "layer_index", "params"),&AnlNoise::fractal);
    ClassDB::bind_method(D_METHOD("randomize", "seed_index", "low_index", "high_index"),&AnlNoise::randomize);
    ClassDB::bind_method(D_METHOD("step", "val_index", "control_index"),&AnlNoise::step);
    ClassDB::bind_method(D_METHOD("linear_step", "low_index", "high_index", "control_index"),&AnlNoise::linear_step);
    ClassDB::bind_method(D_METHOD("smooth_step", "low_index", "high_index", "control_index"),&AnlNoise::smooth_step);
    ClassDB::bind_method(D_METHOD("smoother_step", "low_index", "high_index", "control_index"),&AnlNoise::smoother_step);

    ClassDB::bind_method(D_METHOD("curve_section", "lowv_index", "t_indexes", "v_indexes", "control_index"),&AnlNoise::curve_section);

    // Patterns

    ClassDB::bind_method(D_METHOD("hex_tile", "seed_index"),&AnlNoise::hex_tile);
    ClassDB::bind_method(D_METHOD("hex_bump"),&AnlNoise::hex_bump);

    ClassDB::bind_method(D_METHOD("color", "color"),&AnlNoise::color);
    ClassDB::bind_method(D_METHOD("combine_rgba", "r_index", "g_index", "b_index", "a_index"),&AnlNoise::combine_rgba);
    ClassDB::bind_method(D_METHOD("combine_hsva", "h_index", "s_index", "v_index", "a_index"),&AnlNoise::combine_hsva);

    ClassDB::bind_method(D_METHOD("scale_offset", "src_index", "scale", "offset"),&AnlNoise::scale_offset);

    ClassDB::bind_method(D_METHOD("fractal_layer", "basis_type", "interp_type_index",
                                  "layer_params",
                                  "axis_params",
                                  "rot"),&AnlNoise::fractal_layer, DEFVAL(true));

    ClassDB::bind_method(D_METHOD("ridged_layer", "basis_type", "interp_type_index",
                                  "layer_params",
                                  "axis_params",
                                  "rot"),&AnlNoise::ridged_layer, DEFVAL(true));

    ClassDB::bind_method(D_METHOD("billow_layer", "basis_type", "interp_type_index",
                                  "layer_params",
                                  "axis_params",
                                  "rot"),&AnlNoise::billow_layer, DEFVAL(true));

    ClassDB::bind_method(D_METHOD("fbm", "basis_type", "interp_type",
                                  "params",
                                  "rot"),&AnlNoise::fbm, DEFVAL(true));

    ClassDB::bind_method(D_METHOD("ridged_multifractal", "basis_type", "interp_type",
                                  "params",
                                  "rot"),&AnlNoise::ridged_multifractal, DEFVAL(true));

    ClassDB::bind_method(D_METHOD("billow", "basis_type", "interp_type",
                                  "params",
                                  "rot"),&AnlNoise::billow, DEFVAL(true));

    ClassDB::bind_method(D_METHOD("get_last_index"),&AnlNoise::get_last_index);

    // NoiseExecutor methods

    ClassDB::bind_method(D_METHOD("get_scalar_2d", "x", "y", "index"),&AnlNoise::get_scalar_2d);
    ClassDB::bind_method(D_METHOD("get_scalar_3d", "x", "y", "z" "index"),&AnlNoise::get_scalar_3d);
    ClassDB::bind_method(D_METHOD("get_scalar_4d", "x", "y", "z", "w" "index"),&AnlNoise::get_scalar_4d);
    ClassDB::bind_method(D_METHOD("get_scalar_6d", "6_axis", "index"),&AnlNoise::get_scalar_6d);

    ClassDB::bind_method(D_METHOD("get_color_2d", "x", "y", "index"),&AnlNoise::get_color_2d);
    ClassDB::bind_method(D_METHOD("get_color_3d", "x", "y", "z", "index"),&AnlNoise::get_color_3d);
    ClassDB::bind_method(D_METHOD("get_color_4d", "x", "y", "z", "w", "index"),&AnlNoise::get_color_4d);
    ClassDB::bind_method(D_METHOD("get_color_6d", "6_axis", "index"),&AnlNoise::get_color_6d);

    // ExpressionBuilder methods

    ClassDB::bind_method(D_METHOD("evaluate", "expression"),&AnlNoise::evaluate);

    // Image methods

    ClassDB::bind_method(D_METHOD("map_to_image", "size", "mode", "index", "map_start", "map_end"),&AnlNoise::map_to_image, DEFVAL(Vector2(-1, -1)), DEFVAL(Vector2(1, 1)));
    ClassDB::bind_method(D_METHOD("gen_texture", "size", "mode", "index", "filename"),&AnlNoise::gen_texture);


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

    BIND_ENUM_CONSTANT(SEAMLESS_NONE);
    BIND_ENUM_CONSTANT(SEAMLESS_X);
    BIND_ENUM_CONSTANT(SEAMLESS_Y);
    BIND_ENUM_CONSTANT(SEAMLESS_Z);
    BIND_ENUM_CONSTANT(SEAMLESS_XY);
    BIND_ENUM_CONSTANT(SEAMLESS_XZ);
    BIND_ENUM_CONSTANT(SEAMLESS_YZ);
    BIND_ENUM_CONSTANT(SEAMLESS_XYZ);
}
