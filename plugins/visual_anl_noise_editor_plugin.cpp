#include "visual_anl_noise_editor_plugin.h"

#include "core/io/resource_loader.h"
#include "core/os/input.h"
#include "core/os/keyboard.h"
#include "core/project_settings.h"
#include "editor/editor_properties.h"
#include "scene/gui/menu_button.h"
#include "scene/gui/panel.h"
#include "scene/main/viewport.h"

///////////////////////////////////

void VisualAnlNoiseEditor::edit(const Ref<VisualAnlNoise> &p_visual_anl_noise) {

	if (p_visual_anl_noise.is_valid()) {
		visual_anl_noise = p_visual_anl_noise;
	} else {
		visual_anl_noise.unref();
	}

	if (visual_anl_noise.is_null()) {
		hide();
	}
}

void VisualAnlNoiseEditor::add_plugin(VisualAnlNoiseNodeComponentEditor *p_editor) {

	ERR_FAIL_COND(p_editor->get_parent());
	editor_base->add_child(p_editor);
	editors.push_back(p_editor);
	p_editor->set_h_size_flags(SIZE_EXPAND_FILL);
	p_editor->set_v_size_flags(SIZE_EXPAND_FILL);
	p_editor->hide();
}

void VisualAnlNoiseEditor::remove_plugin(VisualAnlNoiseNodeComponentEditor *p_editor) {

	ERR_FAIL_COND(p_editor->get_parent() != editor_base);
	editor_base->remove_child(p_editor);
	editors.erase(p_editor);
}

void VisualAnlNoiseEditor::edit_path(const Vector<String> &p_path) {

	// button_path.clear();

	// Ref<VisualAnlNoiseNode> node = tree->get_tree_root();

	// if (node.is_valid()) {
	// 	current_component = node->get_instance_id();

	// 	for (int i = 0; i < p_path.size(); i++) {

	// 		Ref<AnimationNode> child = node->get_child_by_name(p_path[i]);
	// 		ERR_BREAK(child.is_null());
	// 		node = child;
	// 		button_path.push_back(p_path[i]);
	// 	}

	// 	for (int i = 0; i < editors.size(); i++) {
	// 		if (editors[i]->can_edit(node)) {
	// 			editors[i]->edit(node);
	// 			editors[i]->show();
	// 		} else {
	// 			editors[i]->edit(Ref<AnimationNode>());
	// 			editors[i]->hide();
	// 		}
	// 	}
	// } else {
	// 	current_component = 0;
	// }

	// edited_path = button_path;

	// _update_path();
}

Vector<String> VisualAnlNoiseEditor::get_edited_path() const {

	return button_path;
}

bool VisualAnlNoiseEditor::can_edit(const Ref<VisualAnlNoiseNode> &p_node) const {

	for (int i = 0; i < editors.size(); i++) {
		if (editors[i]->can_edit(p_node)) {
			return true;
		}
	}
	return false;
}

void VisualAnlNoiseEditor::_notification(int p_what) {


}

void VisualAnlNoiseEditor::_bind_methods() {

	// ClassDB::bind_method("_path_button_pressed", &VisualAnlNoiseEditor::_path_button_pressed);
}

VisualAnlNoiseEditor *VisualAnlNoiseEditor::singleton = NULL;

VisualAnlNoiseEditor::VisualAnlNoiseEditor() {

	path_edit = memnew(ScrollContainer);
	add_child(path_edit);
	path_edit->set_enable_h_scroll(true);
	path_edit->set_enable_v_scroll(false);
	path_hb = memnew(HBoxContainer);
	path_edit->add_child(path_hb);

	current_component = 0;
	singleton = this;
	editor_base = memnew(PanelContainer);
	editor_base->set_v_size_flags(SIZE_EXPAND_FILL);
	add_child(editor_base);

	add_plugin(memnew(VisualAnlNoiseNodeComponentEditor));
}

///////////////////////////////////
// Plugin
///////////////////////////////////

void VisualAnlNoiseEditorPlugin::edit(Object *p_object) {

	visual_anl_noise_editor->edit(Object::cast_to<VisualAnlNoise>(p_object));
}

bool VisualAnlNoiseEditorPlugin::handles(Object *p_object) const {

	return p_object->is_class("VisualAnlNoise");
}

void VisualAnlNoiseEditorPlugin::make_visible(bool p_visible) {

	if (p_visible) {
		button->show();
		editor->make_bottom_panel_item_visible(visual_anl_noise_editor);
		visual_anl_noise_editor->set_process_input(true);
	} else {

		if (visual_anl_noise_editor->is_visible_in_tree())
			editor->hide_bottom_panel();
		button->hide();
		visual_anl_noise_editor->set_process_input(false);
	}
}

VisualAnlNoiseEditorPlugin::VisualAnlNoiseEditorPlugin(EditorNode *p_node) {

	editor = p_node;
	visual_anl_noise_editor = memnew(VisualAnlNoiseEditor);
	visual_anl_noise_editor->set_custom_minimum_size(Size2(0, 300));

	button = editor->add_bottom_panel_item(TTR("VisualAnlNoise"), visual_anl_noise_editor);
	button->hide();
}

VisualAnlNoiseEditorPlugin::~VisualAnlNoiseEditorPlugin() {
}
