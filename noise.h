#ifndef ANL_NOISE_H
#define ANL_NOISE_H

#include "reference.h"
#include "libs/anl/anl.h"

class AnlNoise : public Reference {
    GDCLASS(AnlNoise, Reference);
    
protected:
static void _bind_methods();

public:
            AnlNoise();
//------------------------------------------------------------------------------
// Kernel methods
//------------------------------------------------------------------------------
uint32_t pi();
uint32_t e();
uint32_t one();
uint32_t zero();
uint32_t half();
uint32_t sqrt2();

uint32_t constant(double value);
uint32_t seed();
uint32_t value_basis();
uint32_t gradient_basis();
uint32_t simplex_basis();
uint32_t cellular_basis();
uint32_t add();
uint32_t substract();
uint32_t multiply();
uint32_t divide();
uint32_t maximum();
uint32_t minimum();
uint32_t abs();
uint32_t pow();
uint32_t bias();
uint32_t gain();

uint32_t scale();
uint32_t scale_x();
uint32_t scale_y();
uint32_t scale_z();
uint32_t scale_w();
uint32_t scale_u();
uint32_t scale_v();

uint32_t translate();
uint32_t translate_x();
uint32_t translate_y();
uint32_t translate_z();
uint32_t translate_w();
uint32_t translate_u();
uint32_t translate_v();

uint32_t rotate();

uint32_t add_sequence();
uint32_t multiply_sequence();
uint32_t max_sequence();
uint32_t min_sequence();

uint32_t blend();
uint32_t select(uint32_t low, uint32_t high, uint32_t control, 
                uint32_t threshold, uint32_t falloff);
uint32_t clamp();

uint32_t cos();
uint32_t sin();
uint32_t tan();
uint32_t acos();
uint32_t asin();
uint32_t atan();

uint32_t tiers();
uint32_t smooth_tiers();

uint32_t x();
uint32_t y();
uint32_t z();
uint32_t w();
uint32_t u();
uint32_t v();

uint32_t dx();
uint32_t dy();
uint32_t dz();
uint32_t dw();
uint32_t du();
uint32_t dv();

uint32_t sigmoid();

uint32_t radial();

// Patterns

uint32_t hex_tile();
uint32_t hex_bump();

uint32_t color();

uint32_t combine_rgba();

uint32_t scale_offset();

uint32_t fractal_layer();
uint32_t ridged_layer();
uint32_t billow_layer();

uint32_t fbm();
uint32_t ridged_multifractal();
uint32_t billow();

// Kernel
uint32_t last_index();

//------------------------------------------------------------------------------
// NoiseExecutor methods
//------------------------------------------------------------------------------
double scalar_2d(double x, double y, uint32_t index);
double scalar_3d(double x, double y, double z, uint32_t index);
double scalar_4d(double x, double y, double z, double w, uint32_t index);
double scalar_6d(double x, double y, double z, double w, double u, double v, uint32_t index);

double color_2d(double x, double y, uint32_t index);
double color_3d(double x, double y, double z, uint32_t index);
double color_4d(double x, double y, double z, double w, uint32_t index);
double color_6d(double x, double y, double z, double w, double u, double v, uint32_t index);

private:

anl::CKernel kernel;
anl::CNoiseExecutor vm;
anl::CExpressionBuilder eb;

};

VARIANT_ENUM_CAST(anl::InterpolationTypes);
VARIANT_ENUM_CAST(anl::DistanceTypes);
VARIANT_ENUM_CAST(anl::BasisTypes);

#endif
