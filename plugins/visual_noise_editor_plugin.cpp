#include "visual_noise_editor_plugin.h"
#include "visual_noise_component_editor_plugin.h"

#include "core/io/resource_loader.h"
#include "core/os/input.h"
#include "core/os/keyboard.h"
#include "core/project_settings.h"
#include "editor/editor_properties.h"
#include "scene/gui/menu_button.h"
#include "scene/gui/panel.h"
#include "scene/main/viewport.h"

///////////////////////////////////

void VisualAccidentalNoiseEditor::edit(const Ref<VisualAccidentalNoise> &p_to_edit) {

	if (visual_anl_noise.is_valid()) {
		_disconnect_changed(visual_anl_noise);
	}
	if (p_to_edit.is_valid()) {
		visual_anl_noise = p_to_edit;
		_connect_changed(visual_anl_noise);
		edit_component();

	} else {
		visual_anl_noise.unref();
	}
}

void VisualAccidentalNoiseEditor::_connect_changed(Ref<VisualAccidentalNoise> p_visual_anl_noise) {

	if (!p_visual_anl_noise->is_connected("component_changed", this, "_on_component_changed")) {
		p_visual_anl_noise->connect("component_changed", this, "_on_component_changed");
	}
	if (!p_visual_anl_noise->is_connected("changed", this, "_on_changed")) {
		p_visual_anl_noise->connect("changed", this, "_on_changed", varray(p_visual_anl_noise), CONNECT_DEFERRED);
	}
}

void VisualAccidentalNoiseEditor::_disconnect_changed(Ref<VisualAccidentalNoise> p_visual_anl_noise) {

	if (p_visual_anl_noise->is_connected("component_changed", this, "_on_component_changed")) {
		p_visual_anl_noise->disconnect("component_changed", this, "_on_component_changed");
	}
	if (p_visual_anl_noise->is_connected("changed", this, "_on_changed")) {
		p_visual_anl_noise->disconnect("changed", this, "_on_changed");
	}
}

void VisualAccidentalNoiseEditor::_on_changed(Ref<VisualAccidentalNoise> p_visual_anl_noise) {

	p_visual_anl_noise->generate();

	Ref<VisualAccidentalNoiseNodeComponent> comp = p_visual_anl_noise->get_component();

	VisualAccidentalNoiseComponentEditor::get_singleton()->edit(comp);
}

void VisualAccidentalNoiseEditor::save_external_data() {

	if (visual_anl_noise.is_null())
		return;

	ResourceSaver::save(visual_anl_noise->get_path(), visual_anl_noise);
}

void VisualAccidentalNoiseEditor::add_plugin(VisualAccidentalNoiseComponentEditor *p_editor) {

	ERR_FAIL_COND(p_editor->get_parent());
	editor_base->add_child(p_editor);
	component_editor = p_editor;
	p_editor->set_h_size_flags(SIZE_EXPAND_FILL);
	p_editor->set_v_size_flags(SIZE_EXPAND_FILL);
	p_editor->hide();
}

void VisualAccidentalNoiseEditor::remove_plugin(VisualAccidentalNoiseComponentEditor *p_editor) {

	ERR_FAIL_COND(p_editor->get_parent() != editor_base);
	editor_base->remove_child(p_editor);
	component_editor = NULL;
}

void VisualAccidentalNoiseEditor::_update_path() {

	Ref<VisualAccidentalNoiseNodeComponent> node = visual_anl_noise->get_component();
	if (node.is_null()) {
		return;
	}

	while (path_hb->get_child_count() > 1) {
		memdelete(path_hb->get_child(1));
	}

	Ref<ButtonGroup> group;
	group.instance();

	Button *b = memnew(Button);
	b->set_text(node->get_component_name());
	b->set_toggle_mode(true);
	b->set_button_group(group);
	b->set_pressed(true);
	b->set_focus_mode(FOCUS_NONE);
	b->connect("pressed", this, "_path_button_pressed", varray(-1));
	b->set_icon(get_icon("Edit", "EditorIcons"));
	path_hb->add_child(b);

	Ref<VisualAccidentalNoiseNodeComponent> comp;

	for (int i = 0; i < button_path.size(); i++) {

		node = node->get_node(button_path[i]);

		b = memnew(Button);
		b->set_text(node->get_component_name());
		b->set_toggle_mode(true);
		b->set_button_group(group);
		path_hb->add_child(b);
		b->set_pressed(true);
		b->set_focus_mode(FOCUS_NONE);
		b->connect("pressed", this, "_path_button_pressed", varray(i));
	}
}

Ref<VisualAccidentalNoiseNodeComponent> VisualAccidentalNoiseEditor::_get_child_by_path(const Ref<VisualAccidentalNoiseNodeComponent> &p_node, Vector<int> &p_path) {

	Ref<VisualAccidentalNoiseNodeComponent> node = p_node;

	for (int i = 0; i < p_path.size(); i++) {

		Ref<VisualAccidentalNoiseNodeComponent> child = node->get_node(p_path[i]);
		ERR_BREAK(child.is_null());
		node = child;
	}
	return node;
}

void VisualAccidentalNoiseEditor::edit_path(const Vector<int> &p_path) {

	button_path.clear();

	Ref<VisualAccidentalNoiseNodeComponent> node = visual_anl_noise->get_component();

	if (node.is_valid()) {
		current_component = node->get_instance_id();

		for (int i = 0; i < p_path.size(); i++) {

			Ref<VisualAccidentalNoiseNodeComponent> child = node->get_node(p_path[i]);
			ERR_BREAK(child.is_null());
			node = child;
			button_path.push_back(p_path[i]);
		}
		edit_component(node);
	} else {
		current_component = 0;
	}

	edited_path = button_path;

	_update_path();
}

void VisualAccidentalNoiseEditor::_path_button_pressed(int p_path) {
	
	if (p_path == -1) {
		// Got root component, push edited noise instead
		Ref<VisualAccidentalNoise> noise = VisualAccidentalNoiseEditor::get_singleton()->get_noise();
		ERR_FAIL_COND(noise.is_null());

		EditorNode::get_singleton()->push_item(noise.ptr(), "", true);
	}
	edited_path.clear();

	for (int i = 0; i <= p_path; i++) {
		edited_path.push_back(button_path[i]);
	}
}

void VisualAccidentalNoiseEditor::edit_component(const Ref<VisualAccidentalNoiseNodeComponent> &p_component) {

	Ref<VisualAccidentalNoiseNodeComponent> component;

	if (p_component.is_null()) {
		component = visual_anl_noise->get_component();
	} else {
		component = p_component;
	}

	if (component.is_valid()) {

		if (component_editor->can_edit(component)) {
			component_editor->edit(component);
		} else {
			component_editor->edit(Ref<VisualAccidentalNoiseNode>());
		}
	}
}

void VisualAccidentalNoiseEditor::_on_component_changed() {

	edit_component();
}

void VisualAccidentalNoiseEditor::enter_editor(int p_which) {

	Vector<int> path = edited_path;
	path.push_back(p_which);
	edit_path(path);
}

Vector<int> VisualAccidentalNoiseEditor::get_edited_path() const {

	return button_path;
}

bool VisualAccidentalNoiseEditor::can_edit(const Ref<VisualAccidentalNoiseNode> &p_node) const {

	if (component_editor->can_edit(p_node)) {
		return true;
	}
	return false;
}

void VisualAccidentalNoiseEditor::_notification(int p_what) {

	if (p_what == NOTIFICATION_PROCESS) {
		ObjectID component = 0;
		if (visual_anl_noise.is_valid() && visual_anl_noise->get_component().is_valid()) {
			component = visual_anl_noise->get_component()->get_instance_id();
		}

		if (component != current_component) {
			edit_path(Vector<int>());
		}

		if (button_path.size() != edited_path.size()) {
			edit_path(edited_path);
		}
	}
}

void VisualAccidentalNoiseEditor::_bind_methods() {

	ClassDB::bind_method("_path_button_pressed", &VisualAccidentalNoiseEditor::_path_button_pressed);
	ClassDB::bind_method("_on_component_changed", &VisualAccidentalNoiseEditor::_on_component_changed);

	ClassDB::bind_method("_connect_changed", &VisualAccidentalNoiseEditor::_connect_changed);
	ClassDB::bind_method("_disconnect_changed", &VisualAccidentalNoiseEditor::_disconnect_changed);

	ClassDB::bind_method("_on_changed", &VisualAccidentalNoiseEditor::_on_changed);
}

VisualAccidentalNoiseEditor *VisualAccidentalNoiseEditor::singleton = NULL;

VisualAccidentalNoiseEditor::VisualAccidentalNoiseEditor() {

	path_edit = memnew(ScrollContainer);
	add_child(path_edit);
	path_edit->set_enable_h_scroll(true);
	path_edit->set_enable_v_scroll(false);
	path_hb = memnew(HBoxContainer);
	path_edit->add_child(path_hb);
	path_hb->add_child(memnew(Label(TTR("Path:"))));

	add_child(memnew(HSeparator));

	current_component = 0;
	singleton = this;
	editor_base = memnew(PanelContainer);
	editor_base->set_v_size_flags(SIZE_EXPAND_FILL);
	add_child(editor_base);

	add_plugin(memnew(VisualAccidentalNoiseComponentEditor));

	EDITOR_DEF("editors/visual_accidental_noise/preview_size", Vector2(100, 100));
	EDITOR_DEF("editors/visual_accidental_noise/output_preview_size", Vector2(200, 200));
	EDITOR_DEF("editors/visual_accidental_noise/preview_quality", 1.0); // can be used to speed up preview generation

	// EditorSettings::get_singleton()->connect("settings_changed", this, "_on_settings_changed");
}

///////////////////////////////////
// Plugin
///////////////////////////////////

void VisualAccidentalNoiseEditorPlugin::edit(Object *p_object) {

	visual_anl_noise_editor->edit(Object::cast_to<VisualAccidentalNoise>(p_object));
}

bool VisualAccidentalNoiseEditorPlugin::handles(Object *p_object) const {

	return p_object->is_class("VisualAccidentalNoise");
}

void VisualAccidentalNoiseEditorPlugin::make_visible(bool p_visible) {

	if (p_visible) {
		button->show();
		editor->make_bottom_panel_item_visible(visual_anl_noise_editor);

		visual_anl_noise_editor->set_process(true);
		visual_anl_noise_editor->set_process_input(true);
		VisualAccidentalNoiseComponentEditor::get_singleton()->set_process_input(true);
	} else {

		if (visual_anl_noise_editor->is_visible_in_tree())
			editor->hide_bottom_panel();
		button->hide();

		visual_anl_noise_editor->set_process(false);
		visual_anl_noise_editor->set_process_input(false);
		VisualAccidentalNoiseComponentEditor::get_singleton()->set_process_input(false);
	}
	Ref<VisualAccidentalNoiseNodeComponent> comp = VisualAccidentalNoiseEditor::get_singleton()->get_noise()->get_component();
	VisualAccidentalNoiseComponentEditor *component_editor = VisualAccidentalNoiseComponentEditor::get_singleton();

	if (comp.is_valid()) {
		component_editor->show();
	} else {
		component_editor->hide();
	}
}

void VisualAccidentalNoiseEditorPlugin::save_external_data() {

	visual_anl_noise_editor->save_external_data();
}

VisualAccidentalNoiseEditorPlugin::VisualAccidentalNoiseEditorPlugin(EditorNode *p_node) {

	editor = p_node;
	visual_anl_noise_editor = memnew(VisualAccidentalNoiseEditor);
	visual_anl_noise_editor->set_custom_minimum_size(Size2(0, 300));

	button = editor->add_bottom_panel_item(TTR("VisualAccidentalNoise"), visual_anl_noise_editor);
	button->hide();
}

VisualAccidentalNoiseEditorPlugin::~VisualAccidentalNoiseEditorPlugin() {
}
