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
void        constant(double value);
void        y();
            
//------------------------------------------------------------------------------
// NoiseExecutor methods
//------------------------------------------------------------------------------
double      evaluate_2d(double x, double y);

private:

anl::CKernel kernel;
anl::CNoiseExecutor vm;
anl::CExpressionBuilder eb;

};

VARIANT_ENUM_CAST(anl::InterpolationTypes);
VARIANT_ENUM_CAST(anl::DistanceTypes);
VARIANT_ENUM_CAST(anl::BasisTypes);

#endif
