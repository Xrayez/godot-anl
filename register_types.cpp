#include "register_types.h"

#include "anl_noise.h"
#include "visual_anl_noise.h"

#include "plugin/anl_noise_editor_plugin.h"

void register_anl_types() {

    ClassDB::register_class<AnlNoise>();
    ClassDB::register_class<VisualAnlNoise>();

#ifdef TOOLS_ENABLED
	EditorPlugins::add_by_type<AnlNoiseEditorPlugin>();
#endif
}

void unregister_anl_types() {

    // nothing to do here
}
