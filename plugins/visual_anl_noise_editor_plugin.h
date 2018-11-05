#ifndef VISUAL_ANL_NOISE_EDITOR_PLUGIN_H
#define VISUAL_ANL_NOISE_EDITOR_PLUGIN_H

#include "../visual_anl_noise.h"
#include "visual_anl_noise_component_editor_plugin.h"

#include "editor/editor_node.h"
#include "editor/editor_plugin.h"
#include "scene/gui/button.h"
#include "scene/gui/graph_edit.h"
#include "scene/gui/popup.h"
#include "scene/gui/tree.h"

class VisualAnlNoiseEditor : public VBoxContainer {

	GDCLASS(VisualAnlNoiseEditor, VBoxContainer);

	static VisualAnlNoiseEditor *singleton;

	Ref<VisualAnlNoise> visual_anl_noise;

	ScrollContainer *path_edit;
	HBoxContainer *path_hb;
	PanelContainer *editor_base;

	Vector<int> button_path;
	Vector<int> edited_path;
	VisualAnlNoiseNodeComponentEditor *component_editor;

	ObjectID current_component;

	void _update_path();
	void _path_button_pressed(int path);

protected:
	void _notification(int p_what);
	static void _bind_methods();

public:
	static VisualAnlNoiseEditor *get_singleton() { return singleton; }
	Ref<VisualAnlNoise> get_noise() { return visual_anl_noise; }

	void add_plugin(VisualAnlNoiseNodeComponentEditor *p_editor);
	void remove_plugin(VisualAnlNoiseNodeComponentEditor *p_editor);

	bool can_edit(const Ref<VisualAnlNoiseNode> &p_node) const;

	void edit_component(const Ref<VisualAnlNoiseNodeComponent> &p_component = NULL);
	void _on_component_changed();

	Ref<VisualAnlNoiseNodeComponent> _get_child_by_path(const Ref<VisualAnlNoiseNodeComponent> &node, Vector<int> &p_path);

	void edit_path(const Vector<int> &p_path);
	Vector<int> get_edited_path() const;

	void enter_editor(int p_which);

	void edit(const Ref<VisualAnlNoise> &p_visual_anl_noise);

	void save_external_data();

	VisualAnlNoiseEditor();
};

class VisualAnlNoiseEditorPlugin : public EditorPlugin {

	GDCLASS(VisualAnlNoiseEditorPlugin, EditorPlugin);

	VisualAnlNoiseEditor *visual_anl_noise_editor;
	EditorNode *editor;
	Button *button;

public:
	virtual String get_name() const { return "VisualAnlNoise"; }
	bool has_main_screen() const { return false; }
	virtual void edit(Object *p_object);
	virtual bool handles(Object *p_object) const;
	virtual void make_visible(bool p_visible);

	virtual void save_external_data();

	VisualAnlNoiseEditorPlugin(EditorNode *p_node);
	~VisualAnlNoiseEditorPlugin();
};

#endif
