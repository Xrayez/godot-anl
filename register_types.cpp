#include "register_types.h"

#include "anl_noise.h"
#include "visual_anl_noise.h"
#include "visual_anl_noise_nodes.h"
#include "plugins/visual_anl_noise_editor_plugin.h"
// #include "plugins/visual_anl_noise_component_editor_plugin.h"

void register_anl_types() {

    ClassDB::register_class<AnlNoise>();
    ClassDB::register_class<VisualAnlNoise>();

    // Component
    ClassDB::register_class<VisualAnlNoiseNodeComponent>();

    // Nodes
    ClassDB::register_class<VisualAnlNoiseNodeScalar>();

#ifdef TOOLS_ENABLED
	EditorPlugins::add_by_type<VisualAnlNoiseEditorPlugin>();
#endif
}

void unregister_anl_types() {

    // nothing to do here
}
