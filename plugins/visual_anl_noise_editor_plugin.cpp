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
	component_editor = p_editor;
	p_editor->set_h_size_flags(SIZE_EXPAND_FILL);
	p_editor->set_v_size_flags(SIZE_EXPAND_FILL);
	p_editor->hide();
}

void VisualAnlNoiseEditor::remove_plugin(VisualAnlNoiseNodeComponentEditor *p_editor) {

	ERR_FAIL_COND(p_editor->get_parent() != editor_base);
	editor_base->remove_child(p_editor);
	component_editor = NULL;
}

void VisualAnlNoiseEditor::_notification(int p_what) {


}

void VisualAnlNoiseEditor::_bind_methods() {

}

VisualAnlNoiseEditor *VisualAnlNoiseEditor::singleton = NULL;

VisualAnlNoiseEditor::VisualAnlNoiseEditor() {

	singleton = this;

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
