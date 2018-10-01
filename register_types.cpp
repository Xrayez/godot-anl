#include "register_types.h"
#include "anl_noise.h"
#include "plugin/anl_noise_editor_plugin.h"

void register_anl_types() {

    ClassDB::register_class<AnlNoise>();

    EditorNode *en = EditorNode::get_singleton();
    if(en) {
        memnew(AnlNoiseEditorPlugin(en));
    }
    // en->add_editor_plugin(memnew(AnlNoiseEditorPlugin(en)));
}

void unregister_anl_types() {

    // nothing to do here
}
