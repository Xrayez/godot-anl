#include "noise.h"

AnlNoise::AnlNoise(): vm(kernel), eb(kernel) {}
//------------------------------------------------------------------------------
// Kernel methods
//------------------------------------------------------------------------------
uint32_t AnlNoise::constant(double value) {

    anl::CInstructionIndex constant = kernel.constant(value);
    return constant.getIndex();
}

uint32_t AnlNoise::y() {

    anl::CInstructionIndex y = kernel.y();
    return y.getIndex();
}

uint32_t AnlNoise::select(uint32_t low, uint32_t high, uint32_t control, 
                          uint32_t threshold, uint32_t falloff) {
    
    anl::CInstructionIndex select = kernel.select(       
        kernel[low], kernel[high], kernel[control],
        kernel[threshold], kernel[falloff]
    );
    return select.getIndex();
}
//------------------------------------------------------------------------------
// NoiseExecutor methods
//------------------------------------------------------------------------------
double AnlNoise::scalar_2d(double x, double y, uint32_t index) {

    return vm.evaluateScalar(x, y, index);
}

void AnlNoise::_bind_methods() {

    ClassDB::bind_method(D_METHOD("constant", "value"),&AnlNoise::constant);
    ClassDB::bind_method(D_METHOD("y"),&AnlNoise::y);
    ClassDB::bind_method(D_METHOD("select", "low", "high", "control", "threshold", "falloff"),&AnlNoise::select);

    ClassDB::bind_method(D_METHOD("scalar_2d", "x", "y", "index"),&AnlNoise::scalar_2d);        

    using namespace anl;
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