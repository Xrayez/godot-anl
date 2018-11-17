#ifndef ACCIDENTAL_NOISE_H
#define ACCIDENTAL_NOISE_H

#include "libs/anl/anl.h"

#include "core/resource.h"
#include "scene/resources/texture.h"

// Instruction index of the noise function
using Index = unsigned int;

class AccidentalNoise : public Resource {
    GDCLASS(AccidentalNoise, Resource);
    OBJ_SAVE_TYPE(AccidentalNoise);

protected:
    static void _bind_methods();

public:
    enum Format {
        FORMAT_NOISE,
        FORMAT_COLOR,
    };

    AccidentalNoise();

    void set_mode(anl::EMappingModes p_mode);
    anl::EMappingModes get_mode() const;

    void set_format(Format p_format);
    Format get_format() const;

    void set_ranges(const AABB &p_ranges);
    AABB get_ranges() const;

    void set_expression(const String &p_expression);
    String get_expression() const;

//------------------------------------------------------------------------------
// Kernel noise methods
//------------------------------------------------------------------------------
    // Scalar
    // --------------------------
    Index constant(double value);
    Index pi();
    Index e();
    Index one();
    Index zero();
    Index point5();
    Index sqrt2();

    // Seed
    // ---------------------------------
    Index seed(unsigned int value);
    Index seeder(Index seed, Index src);

    // Basis
    // ---------------------------------------------------------
    Index value_basis(Index interp, Index seed);
    Index gradient_basis(Index interp, Index seed);
    Index simplex_basis(Index seed);
    Index cellular_basis(Index f1, Index f2, Index f3, Index f4,
                        Index d1, Index d2, Index d3, Index d4,
                        Index distance, Index seed);

    // Scalar operations
    // ------------------------------------
    Index add(Index src1, Index src2);
    Index subtract(Index src1, Index src2);
    Index multiply(Index src1, Index src2);
    Index divide(Index src1, Index src2);
    Index maximum(Index src1, Index src2);
    Index minimum(Index src1, Index src2);
    Index pow(Index src1, Index src2);
    Index bias(Index src1, Index src2);
    Index gain(Index src1, Index src2);

    // Transform
    // -----------------------------------------------------------------
    Index scale(Index src, Index scale); // domain

    Index scale_x(Index src, Index scale);
    Index scale_y(Index src, Index scale);
    Index scale_z(Index src, Index scale);
    Index scale_w(Index src, Index scale);
    Index scale_u(Index src, Index scale);
    Index scale_v(Index src, Index scale);

    Index translate(Index src, Index translate); // domain

    Index translate_x(Index src, Index translate);
    Index translate_y(Index src, Index translate);
    Index translate_z(Index src, Index translate);
    Index translate_w(Index src, Index translate);
    Index translate_u(Index src, Index translate);
    Index translate_v(Index src, Index translate);

    Index rotate(Index src, Index angle, Index ax, Index ay, Index az); // domain

    // Sequence operations
    // --------------------------------------------------------------------------
    Index add_sequence(Index base, unsigned int number, unsigned int stride = 1);
    Index multiply_sequence(Index base, Index number, unsigned int stride = 1);
    Index max_sequence(Index base, unsigned int number, unsigned int stride = 1);
    Index min_sequence(Index base, unsigned int number, unsigned int stride = 1);

    // Filter
    // -----------------------------------------------
    Index mix(Index low, Index high, Index control);
    Index select(Index low, Index high, Index control,
                Index threshold, Index falloff);
    Index clamp(Index src, Index low, Index high);

    // Scalar functions
    // -------------------
    Index cos(Index src);
    Index sin(Index src);
    Index tan(Index src);
    Index acos(Index src);
    Index asin(Index src);
    Index atan(Index src);
    Index abs(Index src);
    Index sigmoid(Index src);

    // Tiers
    // --------------------------------------------
    Index tiers(Index src, Index num_tiers);
    Index smooth_tiers(Index src, Index num_tiers);

    // Gradients
    // ---------
    Index x();
    Index y();
    Index z();
    Index w();
    Index u();
    Index v();

    // Derivatives
    // --------------------------------
    Index dx(Index src, Index spacing);
    Index dy(Index src, Index spacing);
    Index dz(Index src, Index spacing);
    Index dw(Index src, Index spacing);
    Index du(Index src, Index spacing);
    Index dv(Index src, Index spacing);

    Index radial();
    Index randomize(Index seed, Index low, Index high);

    // Step
    // -------------------------------------------------------
    Index step(Index val, Index control);
    Index linear_step(Index low, Index high, Index control);
    Index smooth_step(Index low, Index high, Index control);
    Index smoother_step(Index low, Index high, Index control);

    Index curve_section(Index lowv,
                        Index t0, Index t1, Index v0, Index v1,
                        Index control);
    // Patterns
    // ------------------------
    Index hex_tile(Index seed);
    Index hex_bump();

    // Color
    // --------------------------------------------------------
    Index color(const Color& color);
    Index combine_rgba(Index r, Index g, Index b, Index a);
    Index combine_hsva(Index h, Index s, Index v, Index a);

    Index scale_offset(Index src, double scale, double offset);

    // Layers
    // ----------------------------------------------------------------------------------------
    Index fractal_layer(anl::BasisTypes basis, Index interp_type,
                        double scale, double frequency, unsigned int seed, bool rot = true,
                        double angle = 0.5, double ax = 0.0, double ay = 0.0, double az = 1.0);

    Index ridged_layer(anl::BasisTypes basis, Index interp_type,
                    double scale, double frequency, unsigned int seed, bool rot = true,
                    double angle = 0.5, double ax = 0.0, double ay = 0.0, double az = 1.0);

    Index billow_layer(anl::BasisTypes basis, Index interp_type,
                    double scale, double frequency, unsigned int seed, bool rot = true,
                    double angle = 0.5, double ax = 0.0, double ay = 0.0, double az = 1.0);

    // Fractals
    // ----------------------------------------------------------------------------------------------------
    Index fractal(Index seed, Index layer,
                Index persistence, Index lacunarity, Index numoctaves, Index frequency);

    Index fbm(anl::BasisTypes basis, anl::InterpolationTypes interp,
            unsigned int numoctaves, double frequency, unsigned int seed, bool rot = true);

    Index ridged_multifractal(anl::BasisTypes basis, anl::InterpolationTypes interp,
                            unsigned int numoctaves, double frequency, unsigned int seed, bool rot = true);

    Index billow(anl::BasisTypes basis, anl::InterpolationTypes interp,
                unsigned int numoctaves, double frequency, unsigned int seed, bool rot = true);

    // Kernel
    // --------------------
    void set_function(Index p_index);
    Index get_function();

    Index get_last_function();

    void clear();

//------------------------------------------------------------------------------
// NoiseExecutor methods
//------------------------------------------------------------------------------
    double get_noise_2d(double x, double y);
    double get_noise_3d(double x, double y, double z);
    double get_noise_4d(double x, double y, double z, double w);
    double get_noise_6d(double x, double y, double z, double w, double u, double v);

    Color get_color_2d(double x, double y);
    Color get_color_3d(double x, double y, double z);
    Color get_color_4d(double x, double y, double z, double w);
    Color get_color_6d(double x, double y, double z, double w, double u, double v);

    // Convenience

    _FORCE_INLINE_ double get_noise_2dv(const Vector2 &v) { return get_noise_2d(v.x, v.y); }
    _FORCE_INLINE_ double get_noise_3dv(const Vector3 &v) { return get_noise_3d(v.x, v.y, v.z); }

    _FORCE_INLINE_ Color get_color_2dv(const Vector2 &v) { return get_color_2d(v.x, v.y); }
    _FORCE_INLINE_ Color get_color_3dv(const Vector3 &v) { return get_color_3d(v.x, v.y, v.z); }

//------------------------------------------------------------------------------
// ExpressionBuilder methods
//------------------------------------------------------------------------------
    Index evaluate(const String& expression);

//------------------------------------------------------------------------------
// Image/texture methods
//------------------------------------------------------------------------------
    // 2D
    Ref<Image> get_image(int p_width, int p_height);
    Ref<Image> get_seamless_image(int p_width, int p_height);

    Ref<Texture> get_texture(int p_width, int p_height);

    // 3D
    Vector<Ref<Image>> get_image_3d(int p_width, int p_height, int p_depth);
    Vector<Ref<Image>> get_seamless_image_3d(int p_width, int p_height, int p_depth);

private:
    anl::CKernel kernel;
    anl::CNoiseExecutor vm;
    anl::CExpressionBuilder eb;

    Index function;
    Index prev_function;

    anl::EMappingModes mode;
    Format format;
    AABB ranges;
    String expression;

    Ref<Image> _map_to_image(int p_width, int p_height, Index p_index, anl::EMappingModes p_mode, Format p_format, const AABB &p_ranges);
    Vector<Ref<Image>> _map_to_image_3d(int p_width, int p_height, int p_depth, Index p_index, anl::EMappingModes p_mode, Format p_format, const AABB& p_ranges);
};

VARIANT_ENUM_CAST(anl::InterpolationTypes);
VARIANT_ENUM_CAST(anl::DistanceTypes);
VARIANT_ENUM_CAST(anl::BasisTypes);
VARIANT_ENUM_CAST(anl::EMappingModes);
VARIANT_ENUM_CAST(AccidentalNoise::Format);

#endif
