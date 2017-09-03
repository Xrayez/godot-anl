#ifndef ANL_NOISE_H
#define ANL_NOISE_H

#include "reference.h"
#include "libs/anl/anl.h"

using Index = unsigned int;

class AnlNoise : public Reference {
    GDCLASS(AnlNoise, Reference);

protected:
    static void _bind_methods();

public:
      AnlNoise();
//------------------------------------------------------------------------------
// Kernel methods
//------------------------------------------------------------------------------
Index pi();
Index e();
Index one();
Index zero();
Index point5();
Index sqrt2();

Index constant(double value);
Index seed(unsigned int value);

Index value_basis(Index interp, Index seed);
Index gradient_basis(Index interp, Index seed);
Index simplex_basis(Index seed);
Index cellular_basis(const PoolVector<int>& f,
                     const PoolVector<int>& d,
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

Index blend(Index low, Index high, Index control);
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

// Patterns

Index hex_tile(Index seed);
Index hex_bump();

Index color(const Color& color);
Index combine_rgba(Index r, Index g, Index b, Index a);

Index scale_offset(Index src, double scale, double offset);

Index fractal_layer(anl::BasisTypes basis, Index interp_type,
                    const PoolVector<real_t>& layer_params,// scale,freq,seed,angle
                    const PoolVector<real_t>& axis_params, // ax, ay, az
                    bool rot = true);

Index ridged_layer(anl::BasisTypes basis, Index interp_type,
                   const PoolVector<real_t>& layer_params,// scale,freq,seed,angle
                   const PoolVector<real_t>& axis_params, // ax, ay, az
                   bool rot = true);

Index billow_layer(anl::BasisTypes basis, Index interp_type,
                   const PoolVector<real_t>& layer_params,// scale,freq,seed,angle
                   const PoolVector<real_t>& axis_params, // ax, ay, az
                   bool rot = true);

Index fbm(anl::BasisTypes basis, anl::InterpolationTypes interp,
          const PoolVector<real_t>& params, // octaves, frequency, seed
          bool rot = true);

Index ridged_multifractal(anl::BasisTypes basis, anl::InterpolationTypes interp,
                          const PoolVector<real_t>& params, // octaves, frequency, seed
                          bool rot = true);

Index billow(anl::BasisTypes basis, anl::InterpolationTypes interp,
             const PoolVector<real_t>& params, // octaves, frequency, seed
             bool rot = true);

// Kernel
Index last_index();

//------------------------------------------------------------------------------
// NoiseExecutor methods
//------------------------------------------------------------------------------
double scalar_2d(double x, double y, Index);
double scalar_3d(double x, double y, double z, Index);
double scalar_4d(double x, double y, double z, double w, Index);
double scalar_6d(const PoolVector<real_t>& axis, Index);

Color color_2d(double x, double y, Index);
Color color_3d(double x, double y, double z, Index);
Color color_4d(double x, double y, double z, double w, Index);
Color color_6d(const PoolVector<real_t>& axis, Index);

//------------------------------------------------------------------------------
// ExpressionBuilder methods
//------------------------------------------------------------------------------
Index eval_expression(const String& expression);

private:

anl::CKernel kernel;
anl::CNoiseExecutor vm;
anl::CExpressionBuilder eb;

};

VARIANT_ENUM_CAST(anl::InterpolationTypes);
VARIANT_ENUM_CAST(anl::DistanceTypes);
VARIANT_ENUM_CAST(anl::BasisTypes);

#endif
