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

	Vector<String> button_path;
	Vector<String> edited_path;
	Vector<VisualAnlNoiseNodeComponentEditor *> editors;

	void _update_path();
	void _about_to_show_component();
	ObjectID current_component;

	void _path_button_pressed(int p_path);

	VisualAnlNoiseNodeComponentEditor *component_editor;

protected:
	void _notification(int p_what);
	static void _bind_methods();

public:
	static VisualAnlNoiseEditor *get_singleton() { return singleton; }

	void add_plugin(VisualAnlNoiseNodeComponentEditor *p_editor);
	void remove_plugin(VisualAnlNoiseNodeComponentEditor *p_editor);

	bool can_edit(const Ref<VisualAnlNoiseNode> &p_node) const;

	void edit_path(const Vector<String> &p_path);
	Vector<String> get_edited_path() const;

	void enter_editor(const String &p_path = "");

	void edit(const Ref<VisualAnlNoise> &p_visual_anl_noise);

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

	VisualAnlNoiseEditorPlugin(EditorNode *p_node);
	~VisualAnlNoiseEditorPlugin();
};

#endif
