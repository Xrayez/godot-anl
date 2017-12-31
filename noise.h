#ifndef ANL_NOISE_H
#define ANL_NOISE_H

#include "reference.h"
#include "libs/anl/anl.h"
#include "scene/resources/texture.h"

// Index of the noise function
using Index = unsigned int;

class AnlNoise : public Reference {
    GDCLASS(AnlNoise, Reference);

protected:
    static void _bind_methods();

public:
      AnlNoise();
//------------------------------------------------------------------------------
// Kernel noise methods
//------------------------------------------------------------------------------
Index pi();
Index e();
Index one();
Index zero();
Index point5();
Index sqrt2();

Index constant(double value);
Index seed(unsigned int value);
Index seeder(Index seed, Index src);

Index value_basis(Index interp, Index seed);
Index gradient_basis(Index interp, Index seed);
Index simplex_basis(Index seed);
Index cellular_basis(const Vector<int>& f, // Indexes
                     const Vector<int>& d, // Indexes
                     Index distance, Index seed);

Index add(Index src1, Index src2);
Index subtract(Index src1, Index src2);
Index multiply(Index src1, Index src2);
Index divide(Index src1, Index src2);
Index maximum(Index src1, Index src2);
Index minimum(Index src1, Index src2);
Index abs(Index src);
Index pow(Index src1, Index src2);
Index bias(Index src1, Index src2);
Index gain(Index src1, Index src2);

Index scale(Index src, Index scale);

Index scale_x(Index src, Index scale);
Index scale_y(Index src, Index scale);
Index scale_z(Index src, Index scale);
Index scale_w(Index src, Index scale);
Index scale_u(Index src, Index scale);
Index scale_v(Index src, Index scale);

Index translate(Index src, Index translate);

Index translate_x(Index src, Index translate);
Index translate_y(Index src, Index translate);
Index translate_z(Index src, Index translate);
Index translate_w(Index src, Index translate);
Index translate_u(Index src, Index translate);
Index translate_v(Index src, Index translate);

Index rotate(Index src, Index angle, Index ax, Index ay, Index az);

Index add_sequence(Index base, unsigned int number, unsigned int stride = 1);
Index multiply_sequence(Index base, Index number, unsigned int stride = 1);
Index max_sequence(Index base, unsigned int number, unsigned int stride = 1);
Index min_sequence(Index base, unsigned int number, unsigned int stride = 1);

Index mix(Index low, Index high, Index control);
Index select(Index low, Index high, Index control,
             Index threshold, Index falloff);
Index clamp(Index src, Index low, Index high);

Index cos(Index src);
Index sin(Index src);
Index tan(Index src);
Index acos(Index src);
Index asin(Index src);
Index atan(Index src);

Index tiers(Index src, Index num_tiers);
Index smooth_tiers(Index src, Index num_tiers);

Index x();
Index y();
Index z();
Index w();
Index u();
Index v();

Index dx(Index src, Index spacing);
Index dy(Index src, Index spacing);
Index dz(Index src, Index spacing);
Index dw(Index src, Index spacing);
Index du(Index src, Index spacing);
Index dv(Index src, Index spacing);

Index sigmoid(Index src, Index center, Index ramp);

Index radial();

Index fractal(Index seed, Index layer, const Vector<int>& params);
           // Index params: persistence, lacunarity, numoctaves, freq
Index randomize(Index seed, Index low, Index high);
Index step(Index val, Index control);
Index linear_step(Index low, Index high, Index control);
Index smooth_step(Index low, Index high, Index control);
Index smoother_step(Index low, Index high, Index control);

Index curve_section(Index lowv,
                    const Vector<int>& t, // Index: t0, t1
                    const Vector<int>& v, // Index: v0, v1
                    Index control);
// Patterns

Index hex_tile(Index seed);
Index hex_bump();

Index color(const Color& color);
Index combine_rgba(Index r, Index g, Index b, Index a);
Index combine_hsva(Index h, Index s, Index v, Index a);

Index scale_offset(Index src, double scale, double offset);

Index fractal_layer(anl::BasisTypes basis, Index interp_type,
                    const Vector<real_t>& layer_params,// scale,freq,seed,angle
                    const Vector<real_t>& axis_params, // ax, ay, az
                    bool rot = true);

Index ridged_layer(anl::BasisTypes basis, Index interp_type,
                   const Vector<real_t>& layer_params,// scale,freq,seed,angle
                   const Vector<real_t>& axis_params, // ax, ay, az
                   bool rot = true);

Index billow_layer(anl::BasisTypes basis, Index interp_type,
                   const Vector<real_t>& layer_params,// scale,freq,seed,angle
                   const Vector<real_t>& axis_params, // ax, ay, az
                   bool rot = true);

Index fbm(anl::BasisTypes basis, anl::InterpolationTypes interp,
          const Vector<real_t>& params, // octaves, frequency, seed
          bool rot = true);

Index ridged_multifractal(anl::BasisTypes basis, anl::InterpolationTypes interp,
                          const Vector<real_t>& params, // octaves, frequency, seed
                          bool rot = true);

Index billow(anl::BasisTypes basis, anl::InterpolationTypes interp,
             const Vector<real_t>& params, // octaves, frequency, seed
             bool rot = true);

// Kernel

Index get_last_index();

//------------------------------------------------------------------------------
// NoiseExecutor methods
//------------------------------------------------------------------------------
double get_scalar_2d(double x, double y, Index);
double get_scalar_3d(double x, double y, double z, Index);
double get_scalar_4d(double x, double y, double z, double w, Index);
double get_scalar_6d(const Vector<real_t>& axis, Index);

Color get_color_2d(double x, double y, Index);
Color get_color_3d(double x, double y, double z, Index);
Color get_color_4d(double x, double y, double z, double w, Index);
Color get_color_6d(const Vector<real_t>& axis, Index);

//------------------------------------------------------------------------------
// ExpressionBuilder methods
//------------------------------------------------------------------------------
Index evaluate(const String& expression);

//------------------------------------------------------------------------------
// Image methods
//------------------------------------------------------------------------------
Ref<Image> map_to_image(const Vector2& image_size,
                        Index index,
                        anl::EMappingModes mode = anl::EMappingModes::SEAMLESS_NONE,
                        const Rect2& mapping_ranges = Rect2(-1, -1, 2, 2),
                        Image::Format format = Image::Format::FORMAT_RGBA8);

Ref<Texture> map_to_texture(const Vector2& texture_size,
                            Index index,
                            anl::EMappingModes mode = anl::EMappingModes::SEAMLESS_NONE,
                            const Rect2& ranges = Rect2(-1, -1, 2, 2),
                            int flags = Texture::FLAGS_DEFAULT);

void gen_texture(const Vector2& size, anl::EMappingModes mode,
                 Index index, const String& filename);

private:

anl::CKernel kernel;
anl::CNoiseExecutor vm;
anl::CExpressionBuilder eb;

};

VARIANT_ENUM_CAST(anl::InterpolationTypes);
VARIANT_ENUM_CAST(anl::DistanceTypes);
VARIANT_ENUM_CAST(anl::BasisTypes);
VARIANT_ENUM_CAST(anl::EMappingModes);

#endif
