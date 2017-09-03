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

Index AnlNoise::y() {

    auto y = kernel.y();
    return y.getIndex();
}

Index AnlNoise::select(Index low, Index high, Index control, 
                       Index threshold, Index falloff) {
    
    auto select = kernel.select(       
        kernel[low], kernel[high], kernel[control],
        kernel[threshold], kernel[falloff]
    );
    return select.getIndex();
}
//------------------------------------------------------------------------------
// NoiseExecutor methods
//------------------------------------------------------------------------------
double AnlNoise::scalar_2d(double x, double y, Index index) {

    return vm.evaluateScalar(x, y, index);
}

void AnlNoise::_bind_methods() {

    ClassDB::bind_method(D_METHOD("pi"),&AnlNoise::pi);
    ClassDB::bind_method(D_METHOD("e"),&AnlNoise::e);
    ClassDB::bind_method(D_METHOD("one"),&AnlNoise::one);
    ClassDB::bind_method(D_METHOD("zero"),&AnlNoise::zero);
    ClassDB::bind_method(D_METHOD("point5"),&AnlNoise::point5);
    ClassDB::bind_method(D_METHOD("sqrt2"),&AnlNoise::sqrt2);

    ClassDB::bind_method(D_METHOD("constant", "value"),&AnlNoise::constant);
    ClassDB::bind_method(D_METHOD("y"),&AnlNoise::y);
    ClassDB::bind_method(D_METHOD("select", "low", "high", "control", "threshold", "falloff"),&AnlNoise::select);

    ClassDB::bind_method(D_METHOD("scalar_2d", "x", "y", "index"),&AnlNoise::scalar_2d);        

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