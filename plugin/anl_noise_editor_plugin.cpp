#include "anl_noise_editor_plugin.h"

Size2 AnlNoiseEditor::get_minimum_size() const {

	return Size2(10, 200);
}

void AnlNoiseEditorPlugin::edit(Object *p_object) {

    return;
}

bool AnlNoiseEditorPlugin::handles(Object *p_object) const {

    return false;
}

void AnlNoiseEditorPlugin::make_visible(bool p_visible) {

    if(p_visible) {
        return;
    }
}

AnlNoiseEditor *AnlNoiseEditor::singleton = NULL;

AnlNoiseEditor::AnlNoiseEditor() {

	singleton = this;

	graph = memnew(GraphEdit);
	add_child(graph);

    graph->set_v_size_flags(SIZE_EXPAND_FILL);
	// graph->connect("connection_request", this, "_connection_request", varray(), CONNECT_DEFERRED);
	// graph->connect("disconnection_request", this, "_disconnection_request", varray(), CONNECT_DEFERRED);
	// graph->connect("node_selected", this, "_node_selected");
	// graph->connect("scroll_offset_changed", this, "_scroll_changed");
	// graph->connect("duplicate_nodes_request", this, "_duplicate_nodes");

    undo_redo = EditorNode::get_singleton()->get_undo_redo();
}

AnlNoiseEditorPlugin::AnlNoiseEditorPlugin(EditorNode *p_node) {

	editor = p_node;
	anl_noise_editor = memnew(AnlNoiseEditor);
	anl_noise_editor->set_custom_minimum_size(Size2(0, 300));

	button = editor->add_bottom_panel_item(TTR("AnlNoise"), anl_noise_editor);
	// button->hide();
}

AnlNoiseEditorPlugin::~AnlNoiseEditorPlugin() {
}