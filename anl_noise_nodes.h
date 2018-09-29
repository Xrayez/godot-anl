#ifndef ANL_NOISE_NODES_H
#define ANL_NOISE_NODES_H

#include "core/io/resource_loader.h"
#include "core/io/resource_saver.h"
#include "core/resource.h"

class AnlNoiseNode : public Resource {
    GDCLASS(AnlNoiseNode, Resource);

protected:
    static void _bind_methods();

public:
    AnlNoiseNode();

private:


};

#endif
