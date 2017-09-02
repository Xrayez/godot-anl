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

private:

anl::CKernel kernel;
anl::CNoiseExecutor vm;
anl::CExpressionBuilder eb;

};

#endif
