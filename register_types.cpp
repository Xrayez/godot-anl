#include "register_types.h"

#include "anl_noise.h"
#include "visual_anl_noise.h"
#include "nodes/visual_anl_noise_nodes.h"
#include "plugin/visual_anl_noise_editor_plugin.h"

void register_anl_types() {

    ClassDB::register_class<AnlNoise>();
    ClassDB::register_class<VisualAnlNoise>();

    ClassDB::register_class<VisualAnlNoiseNodeScalar>();

#ifdef TOOLS_ENABLED
	EditorPlugins::add_by_type<VisualAnlNoiseEditorPlugin>();
#endif
}

void unregister_anl_types() {

    // nothing to do here
}
