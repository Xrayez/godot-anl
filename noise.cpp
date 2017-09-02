#include "noise.h"

AnlNoise::AnlNoise(): vm(kernel), eb(kernel) {}

void AnlNoise::constant(double value) {

    kernel.constant(value);
}

void AnlNoise::y() {

    kernel.y();
}

double AnlNoise::evaluate_2d(double x, double y) {

    return vm.evaluateScalar(x, y, kernel.lastIndex());
}

void AnlNoise::_bind_methods() {

    ClassDB::bind_method(D_METHOD("constant", "value"),&AnlNoise::constant);
    ClassDB::bind_method(D_METHOD("y"),&AnlNoise::y);

    ClassDB::bind_method(D_METHOD("evaluate_2d", "x", "y"),&AnlNoise::evaluate_2d);        

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