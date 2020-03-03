#include "noise.h"
#include "core/method_bind_ext.gen.inc"

AccidentalNoise::AccidentalNoise() :
		vm(kernel),
		eb(kernel) {

	function = 0;
	prev_function = 0;

	mode = SEAMLESS_NONE;
	format = FORMAT_HEIGHTMAP;
	ranges = AABB(Vector3(-1, -1, -1), Vector3(2, 2, 2));

	normalmap_spacing = 1.0;
	normalmap_wrapped = true;
	normalmap_normalized = true;

	bumpmap_spacing = 1.0;
	bumpmap_wrapped = true;
	bumpmap_light = Vector3(1.0, 1.0, 1.0);
}

void AccidentalNoise::set_mode(MappingModes p_mode) {

	mode = p_mode;
	emit_changed();
}

AccidentalNoise::MappingModes AccidentalNoise::get_mode() const {

	return mode;
}

void AccidentalNoise::set_format(Format p_format) {

	format = p_format;
	emit_changed();
	_change_notify();
}

AccidentalNoise::Format AccidentalNoise::get_format() const {

	return format;
}

void AccidentalNoise::set_ranges(const AABB &p_ranges) {

	ranges = p_ranges;
	emit_changed();
}

AABB AccidentalNoise::get_ranges() const {

	return ranges;
}

void AccidentalNoise::set_expression(const String &p_expression) {

	if (expression.empty() && p_expression.empty()) {
		return;
	}
	expression = p_expression;

	if (!expression.empty()) {
		Index exp_index = evaluate(expression);
		prev_function = function;
		function = exp_index;
	} else {
		// Resume
		function = prev_function;
	}

	emit_changed();
}

String AccidentalNoise::get_expression() const {

	return expression;
}

//------------------------------------------------------------------------------
// Normal/bump map
//------------------------------------------------------------------------------
void AccidentalNoise::set_normalmap_spacing(double p_spacing) {

	normalmap_spacing = p_spacing;

	if (format == FORMAT_NORMALMAP) {
		emit_changed();
	}
}

double AccidentalNoise::get_normalmap_spacing() const {

	return normalmap_spacing;
}

void AccidentalNoise::set_normalmap_wrapped(bool p_wrapped) {

	normalmap_wrapped = p_wrapped;

	if (format == FORMAT_NORMALMAP) {
		emit_changed();
	}
}

bool AccidentalNoise::is_normalmap_wrapped() const {

	return normalmap_wrapped;
}

void AccidentalNoise::set_normalmap_normalized(bool p_normalized) {

	normalmap_normalized = p_normalized;

	if (format == FORMAT_NORMALMAP) {
		emit_changed();
	}
}

bool AccidentalNoise::is_normalmap_normalized() const {

	return normalmap_normalized;
}

void AccidentalNoise::set_bumpmap_spacing(double p_spacing) {

	bumpmap_spacing = p_spacing;

	if (format == FORMAT_BUMPMAP) {
		emit_changed();
	}
}

double AccidentalNoise::get_bumpmap_spacing() const {

	return bumpmap_spacing;
}

void AccidentalNoise::set_bumpmap_wrapped(bool p_wrapped) {

	bumpmap_wrapped = p_wrapped;

	if (format == FORMAT_BUMPMAP) {
		emit_changed();
	}
}

bool AccidentalNoise::is_bumpmap_wrapped() const {

	return bumpmap_wrapped;
}

void AccidentalNoise::set_bumpmap_light(const Vector3 &p_light) {

	bumpmap_light = p_light;

	if (format == FORMAT_BUMPMAP) {
		emit_changed();
	}
}

Vector3 AccidentalNoise::get_bumpmap_light() const {

	return bumpmap_light;
}

//------------------------------------------------------------------------------
// Kernel methods
//------------------------------------------------------------------------------
Index AccidentalNoise::pi() {

	auto pi = kernel.pi();
	return pi.getIndex();
}

Index AccidentalNoise::e() {

	auto e = kernel.e();
	return e.getIndex();
}

Index AccidentalNoise::one() {

	auto one = kernel.one();
	return one.getIndex();
}

Index AccidentalNoise::zero() {

	auto zero = kernel.zero();
	return zero.getIndex();
}

Index AccidentalNoise::point5() {

	auto point5 = kernel.point5();
	return point5.getIndex();
}

Index AccidentalNoise::sqrt2() {

	auto sqrt2 = kernel.sqrt2();
	return sqrt2.getIndex();
}

Index AccidentalNoise::constant(double value) {

	auto constant = kernel.constant(value);
	return constant.getIndex();
}

Index AccidentalNoise::seed(unsigned int value) {

	auto seed = kernel.seed(value);
	return seed.getIndex();
}

Index AccidentalNoise::seeder(Index seed, Index src) {

	auto seeder = kernel.seeder(kernel[seed], kernel[src]);
	return seeder.getIndex();
}

Index AccidentalNoise::value_basis(Index interp, Index seed) {

	auto value_basis = kernel.valueBasis(kernel[interp], kernel[seed]);
	return value_basis.getIndex();
}

Index AccidentalNoise::gradient_basis(Index interp, Index seed) {

	auto gradient_basis = kernel.gradientBasis(kernel[interp], kernel[seed]);
	return gradient_basis.getIndex();
}

Index AccidentalNoise::simplex_basis(Index seed) {

	auto simplex_basis = kernel.simplexBasis(kernel[seed]);
	return simplex_basis.getIndex();
}

Index AccidentalNoise::cellular_basis(Index f1, Index f2, Index f3, Index f4,
		Index d1, Index d2, Index d3, Index d4,
		Index distance, Index seed) {

	auto cellular_basis = kernel.cellularBasis(
			kernel[f1], kernel[f2], kernel[f3], kernel[f4],
			kernel[d1], kernel[d2], kernel[d3], kernel[d4],
			kernel[distance], kernel[seed]);
	return cellular_basis.getIndex();
}

Index AccidentalNoise::add(Index src1, Index src2) {

	auto add = kernel.add(kernel[src1], kernel[src2]);
	return add.getIndex();
}

Index AccidentalNoise::subtract(Index src1, Index src2) {

	auto subtract = kernel.subtract(kernel[src1], kernel[src2]);
	return subtract.getIndex();
}

Index AccidentalNoise::multiply(Index src1, Index src2) {

	auto multiply = kernel.multiply(kernel[src1], kernel[src2]);
	return multiply.getIndex();
}

Index AccidentalNoise::divide(Index src1, Index src2) {

	auto divide = kernel.divide(kernel[src1], kernel[src2]);
	return divide.getIndex();
}

Index AccidentalNoise::maximum(Index src1, Index src2) {

	auto maximum = kernel.maximum(kernel[src1], kernel[src2]);
	return maximum.getIndex();
}

Index AccidentalNoise::minimum(Index src1, Index src2) {

	auto minimum = kernel.minimum(kernel[src1], kernel[src2]);
	return minimum.getIndex();
}

Index AccidentalNoise::abs(Index src) {

	auto abs = kernel.abs(kernel[src]);
	return abs.getIndex();
}

Index AccidentalNoise::pow(Index src1, Index src2) {

	auto pow = kernel.pow(kernel[src1], kernel[src2]);
	return pow.getIndex();
}

Index AccidentalNoise::bias(Index src1, Index src2) {

	auto bias = kernel.bias(kernel[src1], kernel[src2]);
	return bias.getIndex();
}

Index AccidentalNoise::gain(Index src1, Index src2) {

	auto gain = kernel.gain(kernel[src1], kernel[src2]);
	return gain.getIndex();
}

Index AccidentalNoise::scale(Index src, Index p_scale) {

	auto scale = kernel.scaleDomain(kernel[src], kernel[p_scale]);
	return scale.getIndex();
}

Index AccidentalNoise::scale_x(Index src, Index scale) {

	auto scale_x = kernel.scaleX(kernel[src], kernel[scale]);
	return scale_x.getIndex();
}

Index AccidentalNoise::scale_y(Index src, Index scale) {

	auto scale_y = kernel.scaleY(kernel[src], kernel[scale]);
	return scale_y.getIndex();
}

Index AccidentalNoise::scale_z(Index src, Index scale) {

	auto scale_z = kernel.scaleZ(kernel[src], kernel[scale]);
	return scale_z.getIndex();
}

Index AccidentalNoise::scale_w(Index src, Index scale) {

	auto scale_w = kernel.scaleW(kernel[src], kernel[scale]);
	return scale_w.getIndex();
}

Index AccidentalNoise::scale_u(Index src, Index scale) {

	auto scale_u = kernel.scaleU(kernel[src], kernel[scale]);
	return scale_u.getIndex();
}

Index AccidentalNoise::scale_v(Index src, Index scale) {

	auto scale_v = kernel.scaleV(kernel[src], kernel[scale]);
	return scale_v.getIndex();
}

Index AccidentalNoise::translate(Index src, Index p_translate) {

	auto translate = kernel.translateDomain(kernel[src], kernel[p_translate]);
	return translate.getIndex();
}

Index AccidentalNoise::translate_x(Index src, Index translate) {

	auto translate_x = kernel.translateX(kernel[src], kernel[translate]);
	return translate_x.getIndex();
}

Index AccidentalNoise::translate_y(Index src, Index translate) {

	auto translate_y = kernel.translateY(kernel[src], kernel[translate]);
	return translate_y.getIndex();
}

Index AccidentalNoise::translate_z(Index src, Index translate) {

	auto translate_z = kernel.translateZ(kernel[src], kernel[translate]);
	return translate_z.getIndex();
}

Index AccidentalNoise::translate_w(Index src, Index translate) {

	auto translate_w = kernel.translateW(kernel[src], kernel[translate]);
	return translate_w.getIndex();
}

Index AccidentalNoise::translate_u(Index src, Index translate) {

	auto translate_u = kernel.translateU(kernel[src], kernel[translate]);
	return translate_u.getIndex();
}

Index AccidentalNoise::translate_v(Index src, Index translate) {

	auto translate_v = kernel.translateV(kernel[src], kernel[translate]);
	return translate_v.getIndex();
}

Index AccidentalNoise::rotate(Index src, Index angle, Index ax, Index ay, Index az) {

	auto rotate = kernel.rotateDomain(
			kernel[src], kernel[angle], kernel[ax], kernel[ay], kernel[az]);
	return rotate.getIndex();
}

Index AccidentalNoise::add_sequence(Index base, unsigned int number, unsigned int stride) {

	auto add_sequence = kernel.addSequence(
			kernel[base], number, stride);
	return add_sequence.getIndex();
}

Index AccidentalNoise::multiply_sequence(Index base, unsigned int number, unsigned int stride) {

	auto multiply_sequence = kernel.multiplySequence(
			kernel[base], number, stride);
	return multiply_sequence.getIndex();
}

Index AccidentalNoise::max_sequence(Index base, unsigned int number, unsigned int stride) {

	auto max_sequence = kernel.maxSequence(
			kernel[base], number, stride);
	return max_sequence.getIndex();
}

Index AccidentalNoise::min_sequence(Index base, unsigned int number, unsigned int stride) {

	auto min_sequence = kernel.minSequence(
			kernel[base], number, stride);
	return min_sequence.getIndex();
}

Index AccidentalNoise::mix(Index low, Index high, Index control) {

	auto mix = kernel.mix(kernel[low], kernel[high], kernel[control]);
	return mix.getIndex();
}

Index AccidentalNoise::select(Index low, Index high, Index control,
		Index threshold, Index falloff) {

	auto select = kernel.select(
			kernel[low], kernel[high], kernel[control],
			kernel[threshold], kernel[falloff]);
	return select.getIndex();
}

Index AccidentalNoise::clamp(Index src, Index low, Index high) {

	auto clamp = kernel.clamp(kernel[src], kernel[low], kernel[high]);
	return clamp.getIndex();
}

Index AccidentalNoise::cos(Index src) {

	auto cos = kernel.cos(kernel[src]);
	return cos.getIndex();
}

Index AccidentalNoise::sin(Index src) {

	auto sin = kernel.sin(kernel[src]);
	return sin.getIndex();
}

Index AccidentalNoise::tan(Index src) {

	auto tan = kernel.tan(kernel[src]);
	return tan.getIndex();
}

Index AccidentalNoise::acos(Index src) {

	auto acos = kernel.acos(kernel[src]);
	return acos.getIndex();
}

Index AccidentalNoise::asin(Index src) {

	auto asin = kernel.asin(kernel[src]);
	return asin.getIndex();
}

Index AccidentalNoise::atan(Index src) {

	auto atan = kernel.atan(kernel[src]);
	return atan.getIndex();
}

Index AccidentalNoise::tiers(Index src, Index num_tiers) {

	auto tiers = kernel.tiers(kernel[src], kernel[num_tiers]);
	return tiers.getIndex();
}

Index AccidentalNoise::smooth_tiers(Index src, Index num_tiers) {

	auto smooth_tiers = kernel.smoothTiers(kernel[src], kernel[num_tiers]);
	return smooth_tiers.getIndex();
}

Index AccidentalNoise::x() {

	auto x = kernel.x();
	return x.getIndex();
}

Index AccidentalNoise::y() {

	auto y = kernel.y();
	return y.getIndex();
}

Index AccidentalNoise::z() {

	auto z = kernel.z();
	return z.getIndex();
}

Index AccidentalNoise::w() {

	auto w = kernel.w();
	return w.getIndex();
}

Index AccidentalNoise::u() {

	auto u = kernel.u();
	return u.getIndex();
}

Index AccidentalNoise::v() {

	auto v = kernel.v();
	return v.getIndex();
}

Index AccidentalNoise::dx(Index src, Index spacing) {

	auto dx = kernel.dx(kernel[src], kernel[spacing]);
	return dx.getIndex();
}

Index AccidentalNoise::dy(Index src, Index spacing) {

	auto dy = kernel.dy(kernel[src], kernel[spacing]);
	return dy.getIndex();
}

Index AccidentalNoise::dz(Index src, Index spacing) {

	auto dz = kernel.dz(kernel[src], kernel[spacing]);
	return dz.getIndex();
}

Index AccidentalNoise::dw(Index src, Index spacing) {

	auto dw = kernel.dw(kernel[src], kernel[spacing]);
	return dw.getIndex();
}

Index AccidentalNoise::du(Index src, Index spacing) {

	auto du = kernel.du(kernel[src], kernel[spacing]);
	return du.getIndex();
}

Index AccidentalNoise::dv(Index src, Index spacing) {

	auto dv = kernel.dv(kernel[src], kernel[spacing]);
	return dv.getIndex();
}

Index AccidentalNoise::sigmoid(Index src) {

	auto sigmoid = kernel.sigmoid(kernel[src]);
	return sigmoid.getIndex();
}

Index AccidentalNoise::radial() {

	auto radial = kernel.radial();
	return radial.getIndex();
}

Index AccidentalNoise::fractal(Index seed, Index layer,
		Index persistence, Index lacunarity, Index numoctaves, Index frequency) {

	auto fractal = kernel.fractal(
			kernel[seed], kernel[layer],
			kernel[persistence], kernel[lacunarity], kernel[numoctaves], kernel[frequency]);
	return fractal.getIndex();
}

Index AccidentalNoise::randomize(Index seed, Index low, Index high) {

	auto randomize = kernel.randomize(kernel[seed], kernel[low], kernel[high]);
	return randomize.getIndex();
}

Index AccidentalNoise::step(Index val, Index control) {

	auto step = kernel.step(kernel[val], kernel[control]);
	return step.getIndex();
}

Index AccidentalNoise::linear_step(Index low, Index high, Index control) {

	auto linear_step = kernel.linearStep(kernel[low], kernel[high], kernel[control]);
	return linear_step.getIndex();
}

Index AccidentalNoise::smooth_step(Index low, Index high, Index control) {

	auto smooth_step = kernel.smoothStep(kernel[low], kernel[high], kernel[control]);
	return smooth_step.getIndex();
}

Index AccidentalNoise::smoother_step(Index low, Index high, Index control) {

	auto smoother_step = kernel.smootherStep(kernel[low], kernel[high], kernel[control]);
	return smoother_step.getIndex();
}

Index AccidentalNoise::curve_section(Index lowv,
		Index t0, Index t1, Index v0, Index v1,
		Index control) {

	auto curve_section = kernel.curveSection(
			kernel[lowv],
			kernel[t0], kernel[t1], kernel[v0], kernel[v1],
			kernel[control]);
	return curve_section.getIndex();
}

// Patterns

Index AccidentalNoise::hex_tile(Index seed) {

	auto hex_tile = kernel.hexTile(kernel[seed]);
	return hex_tile.getIndex();
}

Index AccidentalNoise::hex_bump() {

	auto hex_bump = kernel.hexBump();
	return hex_bump.getIndex();
}

Index AccidentalNoise::color(const Color &c) {

	auto color = kernel.color(anl::SRGBA(c.r, c.g, c.b, c.a));
	return color.getIndex();
}

Index AccidentalNoise::combine_rgba(Index r, Index g, Index b, Index a) {

	auto combine_rgba = kernel.combineRGBA(
			kernel[r], kernel[g], kernel[b], kernel[a]);
	return combine_rgba.getIndex();
}

Index AccidentalNoise::combine_hsva(Index h, Index s, Index v, Index a) {

	auto combine_hsva = kernel.combineHSVA(
			kernel[h], kernel[s], kernel[v], kernel[a]);
	return combine_hsva.getIndex();
}

Index AccidentalNoise::scale_offset(Index src, double scale, double offset) {

	auto scale_offset = kernel.scaleOffset(
			kernel[src], scale, offset);
	return scale_offset.getIndex();
}

Index AccidentalNoise::fractal_layer(BasisTypes basis, Index interp_type,
		double scale, double frequency, unsigned int seed, bool rot,
		double angle, double ax, double ay, double az) {

	auto fractal_layer = kernel.simpleFractalLayer(
			basis, kernel[interp_type],
			scale, frequency, seed, rot,
			angle, ax, ay, az);
	return fractal_layer.getIndex();
}

Index AccidentalNoise::ridged_layer(BasisTypes basis, Index interp_type,
		double scale, double frequency, unsigned int seed, bool rot,
		double angle, double ax, double ay, double az) {

	auto ridged_layer = kernel.simpleRidgedLayer(
			basis, kernel[interp_type],
			scale, frequency, seed, rot,
			angle, ax, ay, az);
	return ridged_layer.getIndex();
}

Index AccidentalNoise::billow_layer(BasisTypes basis, Index interp_type,
		double scale, double frequency, unsigned int seed, bool rot,
		double angle, double ax, double ay, double az) {

	auto billow_layer = kernel.simpleBillowLayer(
			basis, kernel[interp_type],
			scale, frequency, seed, rot,
			angle, ax, ay, az);
	return billow_layer.getIndex();
}

Index AccidentalNoise::fbm(BasisTypes basis, InterpolationTypes interp,
		unsigned int numoctaves, double frequency, unsigned int seed, bool rot) {

	auto fbm = kernel.simplefBm(
			basis, interp,
			numoctaves, frequency, seed, rot);
	return fbm.getIndex();
}

Index AccidentalNoise::ridged_multifractal(BasisTypes basis, InterpolationTypes interp,
		unsigned int numoctaves, double frequency, unsigned int seed, bool rot) {

	auto ridged_multifractal = kernel.simpleRidgedMultifractal(
			basis, interp,
			numoctaves, frequency, seed, rot);
	return ridged_multifractal.getIndex();
}

Index AccidentalNoise::billow(BasisTypes basis, InterpolationTypes interp,
		unsigned int numoctaves, double frequency, unsigned int seed, bool rot) {

	auto billow = kernel.simpleBillow(
			basis, interp,
			numoctaves, frequency, seed, rot);
	return billow.getIndex();
}

void AccidentalNoise::set_var(const String &p_name, double p_value) {

	kernel.setVar(p_name.utf8().get_data(), p_value);
}

Index AccidentalNoise::get_var(const String &p_name) {

	return kernel.getVar(p_name.utf8().get_data()).getIndex();
}

// Kernel

void AccidentalNoise::set_function(Index p_index) {

	// ERR_FAIL_INDEX(p_index, kernel.getKernel()->size());

	if (!expression.empty()) {
		return;
	}
	prev_function = function;
	function = p_index;
}

Index AccidentalNoise::get_function() {

	return function;
}

Index AccidentalNoise::get_last_function() {

	return kernel.lastIndex().getIndex();
}

void AccidentalNoise::clear() {

	function = 0;
	prev_function = 0;

	expression = String();

	kernel.clear();
}

//------------------------------------------------------------------------------
// NoiseExecutor methods
//------------------------------------------------------------------------------
double AccidentalNoise::get_noise_2d(double x, double y) {

	return vm.evaluateScalar(x, y, function);
}

double AccidentalNoise::get_noise_3d(double x, double y, double z) {

	return vm.evaluateScalar(x, y, z, function);
}

double AccidentalNoise::get_noise_4d(double x, double y, double z, double w) {

	return vm.evaluateScalar(x, y, z, w, function);
}

double AccidentalNoise::get_noise_6d(double x, double y, double z, double w, double u, double v) {

	return vm.evaluateScalar(x, y, z, w, u, v, function);
}

Color AccidentalNoise::get_color_2d(double x, double y) {

	anl::SRGBA c = vm.evaluateColor(x, y, function);
	return Color(c.r, c.g, c.b, c.a);
}

Color AccidentalNoise::get_color_3d(double x, double y, double z) {

	anl::SRGBA c = vm.evaluateColor(x, y, z, function);
	return Color(c.r, c.g, c.b, c.a);
}

Color AccidentalNoise::get_color_4d(double x, double y, double z, double w) {

	anl::SRGBA c = vm.evaluateColor(x, y, z, w, function);
	return Color(c.r, c.g, c.b, c.a);
}

Color AccidentalNoise::get_color_6d(double x, double y, double z, double w, double u, double v) {

	anl::SRGBA c = vm.evaluateColor(x, y, z, w, u, v, function);
	return Color(c.r, c.g, c.b, c.a);
}
//------------------------------------------------------------------------------
// ExpressionBuilder methods
//------------------------------------------------------------------------------
Index AccidentalNoise::evaluate(const String &expression) {

	WARN_PRINT("ExpressionBuilder is unstable, use at your own discretion.");

	auto function = eb.eval(expression.utf8().get_data());
	return function.getIndex();
}

//------------------------------------------------------------------------------
// Image methods
//------------------------------------------------------------------------------
Ref<Image> AccidentalNoise::get_image(int p_width, int p_height) {

	return _map_to_image(p_width, p_height, function, mode, format, ranges);
}

Ref<Image> AccidentalNoise::get_seamless_image(int p_width, int p_height) {

	// Returns seamless image regardless of mapping mode
	return _map_to_image(p_width, p_height, function, SEAMLESS_XY, format, ranges);
}

Ref<Texture> AccidentalNoise::get_texture(int p_width, int p_height) {

	const Ref<Image> &image = get_image(p_width, p_height);

	Ref<ImageTexture> texture = memnew(ImageTexture);
	texture->create_from_image(image);

	return texture;
}

Vector<Ref<Image> > AccidentalNoise::get_image_3d(int p_width, int p_height, int p_depth) {

	return _map_to_image_3d(p_width, p_height, p_depth, function, mode, format, ranges);
}

Vector<Ref<Image> > AccidentalNoise::get_seamless_image_3d(int p_width, int p_height, int p_depth) {

	// Returns seamless 3D image regardless of mapping mode
	return _map_to_image_3d(p_width, p_height, p_depth, function, SEAMLESS_XY, format, ranges);
}

Ref<Image> AccidentalNoise::_map_to_image(int p_width, int p_height, Index p_index, MappingModes p_mode, Format p_format, const AABB &p_ranges) {

	anl::SMappingRanges ranges(
			p_ranges.position.x, p_ranges.position.x + p_ranges.size.x,
			p_ranges.position.y, p_ranges.position.y + p_ranges.size.y,
			p_ranges.position.z, p_ranges.position.z + p_ranges.size.z);

	PoolVector<uint8_t> dest_data;
	const int SIZE = p_width * p_height;

	Image::Format image_format = Image::Format::FORMAT_L8;

	switch (p_format) {

		case FORMAT_HEIGHTMAP: {
			image_format = Image::Format::FORMAT_L8;

			anl::CArray2Dd img(p_width, p_height);
			anl::map2DNoZ(p_mode, img, kernel, ranges, p_index);

			auto src_data = img.getData();

			dest_data.resize(SIZE);
			PoolVector<uint8_t>::Write w = dest_data.write();

			for (int i = 0; i < SIZE; ++i) {
				w[i] = (uint8_t)(src_data[i] * 255);
			}
		} break;

		case FORMAT_NORMALMAP: {
			image_format = Image::Format::FORMAT_RGBA8;

			anl::CArray2Dd img(p_width, p_height);
			anl::map2DNoZ(p_mode, img, kernel, ranges, p_index);

			anl::CArray2Drgba normal_img(p_width, p_height);
			anl::calcNormalMap(&img, &normal_img, normalmap_spacing, normalmap_normalized, normalmap_wrapped);

			auto src_data = normal_img.getData();

			dest_data.resize(SIZE * 4);
			PoolVector<uint8_t>::Write w = dest_data.write();

			for (int i = 0; i < SIZE; ++i) {
				w[i * 4 + 0] = (uint8_t)(src_data[i].r * 255);
				w[i * 4 + 1] = (uint8_t)(src_data[i].g * 255);
				w[i * 4 + 2] = (uint8_t)(src_data[i].b * 255);
				w[i * 4 + 3] = 255;
			}
		} break;

		case FORMAT_BUMPMAP: {
			image_format = Image::Format::FORMAT_L8;

			anl::CArray2Dd img(p_width, p_height);
			anl::map2DNoZ(p_mode, img, kernel, ranges, p_index);

			anl::CArray2Dd bump_img(p_width, p_height);
			float light[3] = { bumpmap_light.x, bumpmap_light.y, bumpmap_light.z };
			anl::calcBumpMap(&img, &bump_img, light, bumpmap_spacing, bumpmap_wrapped);

			auto src_data = bump_img.getData();

			dest_data.resize(SIZE);
			PoolVector<uint8_t>::Write w = dest_data.write();

			for (int i = 0; i < SIZE; ++i) {
				w[i] = (uint8_t)(src_data[i] * 255);
			}
		} break;

		case FORMAT_TEXTURE: {
			image_format = Image::Format::FORMAT_RGBA8;

			anl::CArray2Drgba img(p_width, p_height);
			anl::mapRGBA2DNoZ(p_mode, img, kernel, ranges, p_index);
			auto src_data = img.getData();

			dest_data.resize(SIZE * 4);
			PoolVector<uint8_t>::Write w = dest_data.write();

			for (int i = 0; i < SIZE; ++i) {
				w[i * 4 + 0] = (uint8_t)(src_data[i].r * 255);
				w[i * 4 + 1] = (uint8_t)(src_data[i].g * 255);
				w[i * 4 + 2] = (uint8_t)(src_data[i].b * 255);
				w[i * 4 + 3] = (uint8_t)(src_data[i].a * 255);
			}
		} break;
	}

	Ref<Image> noise = memnew(Image);
	noise->create(p_width, p_height, 0, image_format, dest_data);

	return noise;
}

Vector<Ref<Image> > AccidentalNoise::_map_to_image_3d(int p_width, int p_height, int p_depth, Index p_index, MappingModes p_mode, Format p_format, const AABB &p_ranges) {

	anl::SMappingRanges ranges(
			p_ranges.position.x, p_ranges.position.x + p_ranges.size.x,
			p_ranges.position.y, p_ranges.position.y + p_ranges.size.y,
			p_ranges.position.z, p_ranges.position.z + p_ranges.size.z);

	Vector<PoolVector<uint8_t> > dest_data;
	const int SIZE = p_width * p_height;

	Image::Format image_format = Image::Format::FORMAT_L8;

	switch (p_format) {

		case FORMAT_HEIGHTMAP: { // more like depth map?
			image_format = Image::Format::FORMAT_L8;

			anl::CArray3Dd img(p_width, p_height, p_depth);
			anl::map3D(p_mode, img, kernel, ranges, p_index);

			for (int k = 0; k < p_depth; k++) {

				PoolVector<uint8_t> dest_data_image;
				dest_data_image.resize(SIZE);
				PoolVector<uint8_t>::Write w = dest_data_image.write();

				auto src_data = img.getData();

				for (int i = SIZE * k; i < SIZE * (k + 1); i++) {
					w[i] = (uint8_t)(src_data[i] * 255);
				}
				dest_data.push_back(dest_data_image);
			}
		} break;

		case FORMAT_NORMALMAP:
		case FORMAT_BUMPMAP: {
			ERR_FAIL_V_MSG(Vector<Ref<Image> >(), "Normal/bump 3D image mapping is not supported.");
		} break;

		case FORMAT_TEXTURE: {
			image_format = Image::Format::FORMAT_RGBA8;

			anl::CArray3Drgba img(p_width, p_height, p_depth);
			anl::mapRGBA3D(p_mode, img, kernel, ranges, p_index);

			for (int k = 0; k < p_depth; ++k) {

				PoolVector<uint8_t> dest_data_image;
				dest_data_image.resize(SIZE * 4);
				PoolVector<uint8_t>::Write w = dest_data_image.write();

				auto src_data = img.getData();

				for (int dest = 0, src = SIZE * k; src < SIZE * (k + 1); dest += 4, ++src) { // TODO: optimize (like 2D)?
					w[dest + 0] = (uint8_t)(src_data[src].r * 255);
					w[dest + 1] = (uint8_t)(src_data[src].g * 255);
					w[dest + 2] = (uint8_t)(src_data[src].b * 255);
					w[dest + 3] = (uint8_t)(src_data[src].a * 255);
				}
				dest_data.push_back(dest_data_image);
			}
		} break;
	}

	Vector<Ref<Image> > noise;
	for (int i = 0; i < dest_data.size(); i++) {
		Ref<Image> noise_image = memnew(Image);
		noise_image->create(p_width, p_height, 0, image_format, dest_data[i]);
		noise.push_back(noise_image);
	}

	return noise;
}

void AccidentalNoise::_validate_property(PropertyInfo &property) const {

	if (property.name.begins_with("normalmap") && format != FORMAT_NORMALMAP) {
		property.usage = PROPERTY_USAGE_NOEDITOR;
	}
	if (property.name.begins_with("bumpmap") && format != FORMAT_BUMPMAP) {
		property.usage = PROPERTY_USAGE_NOEDITOR;
	}
	if (property.name == "function" || property.name == "last_function") {
		property.usage = PROPERTY_USAGE_NOEDITOR;
	}
}

void AccidentalNoise::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_mode", "mode"), &AccidentalNoise::set_mode);
	ClassDB::bind_method(D_METHOD("get_mode"), &AccidentalNoise::get_mode);

	ClassDB::bind_method(D_METHOD("set_format", "format"), &AccidentalNoise::set_format);
	ClassDB::bind_method(D_METHOD("get_format"), &AccidentalNoise::get_format);

	ClassDB::bind_method(D_METHOD("set_ranges", "ranges"), &AccidentalNoise::set_ranges);
	ClassDB::bind_method(D_METHOD("get_ranges"), &AccidentalNoise::get_ranges);

	ClassDB::bind_method(D_METHOD("set_expression", "expression"), &AccidentalNoise::set_expression);
	ClassDB::bind_method(D_METHOD("get_expression"), &AccidentalNoise::get_expression);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "mode", PROPERTY_HINT_ENUM, "Seamless none,Seamless X,Seamless Y,Seamless Z,Seamless XY,Seamless XZ,Seamless YZ,Seamless XYZ"), "set_mode", "get_mode");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "format", PROPERTY_HINT_ENUM, "Height Map,Normal Map,Bump Map,Texture"), "set_format", "get_format");
	ADD_PROPERTY(PropertyInfo(Variant::AABB, "ranges"), "set_ranges", "get_ranges");
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "expression", PROPERTY_HINT_MULTILINE_TEXT), "set_expression", "get_expression");

	// Normalmap / Bumpmap -----------------------------------------------------
	ClassDB::bind_method(D_METHOD("set_normalmap_spacing", "normalmap_spacing"), &AccidentalNoise::set_normalmap_spacing);
	ClassDB::bind_method(D_METHOD("get_normalmap_spacing"), &AccidentalNoise::get_normalmap_spacing);

	ClassDB::bind_method(D_METHOD("set_normalmap_wrapped", "normalmap_wrapped"), &AccidentalNoise::set_normalmap_wrapped);
	ClassDB::bind_method(D_METHOD("is_normalmap_wrapped"), &AccidentalNoise::is_normalmap_wrapped);

	ClassDB::bind_method(D_METHOD("set_normalmap_normalized", "normalmap_normalized"), &AccidentalNoise::set_normalmap_normalized);
	ClassDB::bind_method(D_METHOD("is_normalmap_normalized"), &AccidentalNoise::is_normalmap_normalized);

	ADD_GROUP("Normal Map", "normalmap_");
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "normalmap_spacing"), "set_normalmap_spacing", "get_normalmap_spacing");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "normalmap_wrapped"), "set_normalmap_wrapped", "is_normalmap_wrapped");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "normalmap_normalized"), "set_normalmap_normalized", "is_normalmap_normalized");

	ClassDB::bind_method(D_METHOD("set_bumpmap_spacing", "bumpmap_spacing"), &AccidentalNoise::set_bumpmap_spacing);
	ClassDB::bind_method(D_METHOD("get_bumpmap_spacing"), &AccidentalNoise::get_bumpmap_spacing);

	ClassDB::bind_method(D_METHOD("set_bumpmap_wrapped", "bumpmap_wrapped"), &AccidentalNoise::set_bumpmap_wrapped);
	ClassDB::bind_method(D_METHOD("is_bumpmap_wrapped"), &AccidentalNoise::is_bumpmap_wrapped);

	ClassDB::bind_method(D_METHOD("set_bumpmap_light", "bumpmap_light"), &AccidentalNoise::set_bumpmap_light);
	ClassDB::bind_method(D_METHOD("get_bumpmap_light"), &AccidentalNoise::get_bumpmap_light);

	ADD_GROUP("Bump Map", "bumpmap_");
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "bumpmap_spacing"), "set_bumpmap_spacing", "get_bumpmap_spacing");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "bumpmap_wrapped"), "set_bumpmap_wrapped", "is_bumpmap_wrapped");
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "bumpmap_light"), "set_bumpmap_light", "get_bumpmap_light");
	//--------------------------------------------------------------------------

	BIND_ENUM_CONSTANT(FORMAT_HEIGHTMAP);
	BIND_ENUM_CONSTANT(FORMAT_NORMALMAP);
	BIND_ENUM_CONSTANT(FORMAT_BUMPMAP);
	BIND_ENUM_CONSTANT(FORMAT_TEXTURE);

	// Kernel methods

	ClassDB::bind_method(D_METHOD("pi"), &AccidentalNoise::pi);
	ClassDB::bind_method(D_METHOD("e"), &AccidentalNoise::e);
	ClassDB::bind_method(D_METHOD("one"), &AccidentalNoise::one);
	ClassDB::bind_method(D_METHOD("zero"), &AccidentalNoise::zero);
	ClassDB::bind_method(D_METHOD("point5"), &AccidentalNoise::point5);
	ClassDB::bind_method(D_METHOD("sqrt2"), &AccidentalNoise::sqrt2);

	ClassDB::bind_method(D_METHOD("constant", "value"), &AccidentalNoise::constant);
	ClassDB::bind_method(D_METHOD("seed", "value"), &AccidentalNoise::seed);
	ClassDB::bind_method(D_METHOD("seeder", "seed_index", "src_index"), &AccidentalNoise::seeder);

	ClassDB::bind_method(D_METHOD("value_basis", "interp_index", "seed_index"), &AccidentalNoise::value_basis);
	ClassDB::bind_method(D_METHOD("gradient_basis", "interp_index", "seed_index"), &AccidentalNoise::gradient_basis);
	ClassDB::bind_method(D_METHOD("simplex_basis", "seed_index"), &AccidentalNoise::simplex_basis);
	ClassDB::bind_method(D_METHOD("cellular_basis", "f1", "f2", "f3", "f4", "d1", "d2", "d3", "d4", "distance_index", "seed_index"), &AccidentalNoise::cellular_basis);

	ClassDB::bind_method(D_METHOD("add", "src1_index", "src2_index"), &AccidentalNoise::add);
	ClassDB::bind_method(D_METHOD("subtract", "src1_index", "src2_index"), &AccidentalNoise::subtract);
	ClassDB::bind_method(D_METHOD("multiply", "src1_index", "src2_index"), &AccidentalNoise::multiply);
	ClassDB::bind_method(D_METHOD("divide", "src1_index", "src2_index"), &AccidentalNoise::divide);
	ClassDB::bind_method(D_METHOD("maximum", "src1_index", "src2_index"), &AccidentalNoise::maximum);
	ClassDB::bind_method(D_METHOD("minimum", "src1_index", "src2_index"), &AccidentalNoise::minimum);
	ClassDB::bind_method(D_METHOD("abs", "src_index"), &AccidentalNoise::abs);
	ClassDB::bind_method(D_METHOD("pow", "src1_index", "src2_index"), &AccidentalNoise::pow);
	ClassDB::bind_method(D_METHOD("bias", "src1_index", "src2_index"), &AccidentalNoise::bias);
	ClassDB::bind_method(D_METHOD("gain", "src1_index", "src2_index"), &AccidentalNoise::gain);

	ClassDB::bind_method(D_METHOD("scale", "src_index", "scale_index"), &AccidentalNoise::scale);

	ClassDB::bind_method(D_METHOD("scale_x", "src_index", "scale_index"), &AccidentalNoise::scale_x);
	ClassDB::bind_method(D_METHOD("scale_y", "src_index", "scale_index"), &AccidentalNoise::scale_y);
	ClassDB::bind_method(D_METHOD("scale_z", "src_index", "scale_index"), &AccidentalNoise::scale_z);
	ClassDB::bind_method(D_METHOD("scale_w", "src_index", "scale_index"), &AccidentalNoise::scale_w);
	ClassDB::bind_method(D_METHOD("scale_u", "src_index", "scale_index"), &AccidentalNoise::scale_u);
	ClassDB::bind_method(D_METHOD("scale_v", "src_index", "scale_index"), &AccidentalNoise::scale_v);

	ClassDB::bind_method(D_METHOD("translate", "src_index", "translate_index"), &AccidentalNoise::translate);

	ClassDB::bind_method(D_METHOD("translate_x", "src_index", "translate_index"), &AccidentalNoise::translate_x);
	ClassDB::bind_method(D_METHOD("translate_y", "src_index", "translate_index"), &AccidentalNoise::translate_y);
	ClassDB::bind_method(D_METHOD("translate_z", "src_index", "translate_index"), &AccidentalNoise::translate_z);
	ClassDB::bind_method(D_METHOD("translate_w", "src_index", "translate_index"), &AccidentalNoise::translate_w);
	ClassDB::bind_method(D_METHOD("translate_u", "src_index", "translate_index"), &AccidentalNoise::translate_u);
	ClassDB::bind_method(D_METHOD("translate_v", "src_index", "translate_index"), &AccidentalNoise::translate_v);

	ClassDB::bind_method(D_METHOD("rotate", "src_index", "angle_index", "ax_index", "ay_index", "az_index"), &AccidentalNoise::rotate);

	ClassDB::bind_method(D_METHOD("add_sequence", "base_index", "number", "stride"), &AccidentalNoise::add_sequence, DEFVAL(1));
	ClassDB::bind_method(D_METHOD("multiply_sequence", "base_index", "number", "stride"), &AccidentalNoise::multiply_sequence, DEFVAL(1));
	ClassDB::bind_method(D_METHOD("max_sequence", "base_index", "number", "stride"), &AccidentalNoise::max_sequence, DEFVAL(1));
	ClassDB::bind_method(D_METHOD("min_sequence", "base_index", "number", "stride"), &AccidentalNoise::min_sequence, DEFVAL(1));

	ClassDB::bind_method(D_METHOD("mix", "low_index", "high_index", "control_index"), &AccidentalNoise::mix);
	ClassDB::bind_method(D_METHOD("select", "low_index", "high_index", "control_index", "threshold_index", "falloff_index"), &AccidentalNoise::select);
	ClassDB::bind_method(D_METHOD("clamp", "src_index", "low_index", "high_index"), &AccidentalNoise::clamp);

	ClassDB::bind_method(D_METHOD("cos", "src_index"), &AccidentalNoise::cos);
	ClassDB::bind_method(D_METHOD("sin", "src_index"), &AccidentalNoise::sin);
	ClassDB::bind_method(D_METHOD("tan", "src_index"), &AccidentalNoise::tan);
	ClassDB::bind_method(D_METHOD("acos", "src_index"), &AccidentalNoise::acos);
	ClassDB::bind_method(D_METHOD("asin", "src_index"), &AccidentalNoise::asin);
	ClassDB::bind_method(D_METHOD("atan", "src_index"), &AccidentalNoise::atan);

	ClassDB::bind_method(D_METHOD("tiers", "src_index", "num_tiers_index"), &AccidentalNoise::tiers);
	ClassDB::bind_method(D_METHOD("smooth_tiers", "src_index", "num_tiers_index"), &AccidentalNoise::smooth_tiers);

	ClassDB::bind_method(D_METHOD("x"), &AccidentalNoise::x);
	ClassDB::bind_method(D_METHOD("y"), &AccidentalNoise::y);
	ClassDB::bind_method(D_METHOD("z"), &AccidentalNoise::z);
	ClassDB::bind_method(D_METHOD("w"), &AccidentalNoise::w);
	ClassDB::bind_method(D_METHOD("u"), &AccidentalNoise::u);
	ClassDB::bind_method(D_METHOD("v"), &AccidentalNoise::v);

	ClassDB::bind_method(D_METHOD("dx", "src_index", "spacing_index"), &AccidentalNoise::dx);
	ClassDB::bind_method(D_METHOD("dy", "src_index", "spacing_index"), &AccidentalNoise::dy);
	ClassDB::bind_method(D_METHOD("dz", "src_index", "spacing_index"), &AccidentalNoise::dz);
	ClassDB::bind_method(D_METHOD("dw", "src_index", "spacing_index"), &AccidentalNoise::dw);
	ClassDB::bind_method(D_METHOD("du", "src_index", "spacing_index"), &AccidentalNoise::du);
	ClassDB::bind_method(D_METHOD("dv", "src_index", "spacing_index"), &AccidentalNoise::dv);

	ClassDB::bind_method(D_METHOD("sigmoid", "src_index"), &AccidentalNoise::sigmoid);

	ClassDB::bind_method(D_METHOD("radial"), &AccidentalNoise::radial);

	ClassDB::bind_method(D_METHOD("fractal", "seed_index", "layer_index", "persistence_index", "lacunarity_index", "numoctaves_index", "frequency_index"), &AccidentalNoise::fractal);
	ClassDB::bind_method(D_METHOD("randomize", "seed_index", "low_index", "high_index"), &AccidentalNoise::randomize);
	ClassDB::bind_method(D_METHOD("step", "val_index", "control_index"), &AccidentalNoise::step);
	ClassDB::bind_method(D_METHOD("linear_step", "low_index", "high_index", "control_index"), &AccidentalNoise::linear_step);
	ClassDB::bind_method(D_METHOD("smooth_step", "low_index", "high_index", "control_index"), &AccidentalNoise::smooth_step);
	ClassDB::bind_method(D_METHOD("smoother_step", "low_index", "high_index", "control_index"), &AccidentalNoise::smoother_step);

	ClassDB::bind_method(D_METHOD("curve_section", "lowv_index", "t0_index", "t1_index", "v0_index", "v1_index", "control_index"), &AccidentalNoise::curve_section);

	// Patterns

	ClassDB::bind_method(D_METHOD("hex_tile", "seed_index"), &AccidentalNoise::hex_tile);
	ClassDB::bind_method(D_METHOD("hex_bump"), &AccidentalNoise::hex_bump);

	ClassDB::bind_method(D_METHOD("color", "color"), &AccidentalNoise::color);
	ClassDB::bind_method(D_METHOD("combine_rgba", "r_index", "g_index", "b_index", "a_index"), &AccidentalNoise::combine_rgba);
	ClassDB::bind_method(D_METHOD("combine_hsva", "h_index", "s_index", "v_index", "a_index"), &AccidentalNoise::combine_hsva);

	ClassDB::bind_method(D_METHOD("scale_offset", "src_index", "scale", "offset"), &AccidentalNoise::scale_offset);

	ClassDB::bind_method(D_METHOD("fractal_layer", "basis_type", "interp_type_index",
								 "scale", "frequency", "seed", "rotation",
								 "angle", "ax", "ay", "az"),
			&AccidentalNoise::fractal_layer, DEFVAL(true), DEFVAL(0.5), DEFVAL(0.0), DEFVAL(0.0), DEFVAL(1.0));

	ClassDB::bind_method(D_METHOD("ridged_layer", "basis_type", "interp_type_index",
								 "scale", "frequency", "seed", "rotation",
								 "angle", "ax", "ay", "az"),
			&AccidentalNoise::ridged_layer, DEFVAL(true), DEFVAL(0.5), DEFVAL(0.0), DEFVAL(0.0), DEFVAL(1.0));

	ClassDB::bind_method(D_METHOD("billow_layer", "basis_type", "interp_type_index",
								 "scale", "frequency", "seed", "rotation",
								 "angle", "ax", "ay", "az"),
			&AccidentalNoise::billow_layer, DEFVAL(true), DEFVAL(0.5), DEFVAL(0.0), DEFVAL(0.0), DEFVAL(1.0));

	ClassDB::bind_method(D_METHOD("fbm", "basis_type", "interp_type",
								 "numoctaves", "frequency", "seed", "rotation"),
			&AccidentalNoise::fbm, DEFVAL(true));

	ClassDB::bind_method(D_METHOD("ridged_multifractal", "basis_type", "interp_type",
								 "numoctaves", "frequency", "seed", "rotation"),
			&AccidentalNoise::ridged_multifractal, DEFVAL(true));

	ClassDB::bind_method(D_METHOD("billow", "basis_type", "interp_type",
								 "numoctaves", "frequency", "seed", "rotation"),
			&AccidentalNoise::billow, DEFVAL(true));

	ClassDB::bind_method(D_METHOD("set_var", "name", "value"), &AccidentalNoise::set_var);
	ClassDB::bind_method(D_METHOD("get_var", "name"), &AccidentalNoise::get_var);

	// Kernel

	ClassDB::bind_method(D_METHOD("set_function"), &AccidentalNoise::set_function);
	ClassDB::bind_method(D_METHOD("get_function"), &AccidentalNoise::get_function);

	ClassDB::bind_method(D_METHOD("get_last_function"), &AccidentalNoise::get_last_function);

	ClassDB::bind_method(D_METHOD("clear"), &AccidentalNoise::clear);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "function"), "set_function", "get_function");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "last_function"), "", "get_last_function");

	// NoiseExecutor methods

	ClassDB::bind_method(D_METHOD("get_noise_2d", "x", "y"), &AccidentalNoise::get_noise_2d);
	ClassDB::bind_method(D_METHOD("get_noise_3d", "x", "y", "z"), &AccidentalNoise::get_noise_3d);
	ClassDB::bind_method(D_METHOD("get_noise_4d", "x", "y", "z", "w"), &AccidentalNoise::get_noise_4d);
	ClassDB::bind_method(D_METHOD("get_noise_6d", "x", "y", "z", "w", "u", "v"), &AccidentalNoise::get_noise_6d);

	ClassDB::bind_method(D_METHOD("get_color_2d", "x", "y"), &AccidentalNoise::get_color_2d);
	ClassDB::bind_method(D_METHOD("get_color_3d", "x", "y", "z"), &AccidentalNoise::get_color_3d);
	ClassDB::bind_method(D_METHOD("get_color_4d", "x", "y", "z", "w"), &AccidentalNoise::get_color_4d);
	ClassDB::bind_method(D_METHOD("get_color_6d", "x", "y", "z", "w", "u", "v"), &AccidentalNoise::get_color_6d);

	ClassDB::bind_method(D_METHOD("get_noise_2dv", "pos"), &AccidentalNoise::get_noise_2dv);
	ClassDB::bind_method(D_METHOD("get_noise_3dv", "pos"), &AccidentalNoise::get_noise_3dv);

	ClassDB::bind_method(D_METHOD("get_color_2dv", "pos"), &AccidentalNoise::get_color_2dv);
	ClassDB::bind_method(D_METHOD("get_color_3dv", "pos"), &AccidentalNoise::get_color_3dv);

	// ExpressionBuilder methods

	ClassDB::bind_method(D_METHOD("evaluate", "expression"), &AccidentalNoise::evaluate);

	// Image/texture methods

	ClassDB::bind_method(D_METHOD("get_image", "width", "height"), &AccidentalNoise::get_image);
	ClassDB::bind_method(D_METHOD("get_seamless_image", "width", "height"), &AccidentalNoise::get_seamless_image);

	ClassDB::bind_method(D_METHOD("get_texture", "width", "height"), &AccidentalNoise::get_texture);

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
