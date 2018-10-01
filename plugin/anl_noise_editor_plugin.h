#ifndef ANL_NOISE_EDITOR_PLUGIN_H
#define ANL_NOISE_EDITOR_PLUGIN_H

#include "editor/editor_node.h"
#include "editor/editor_plugin.h"
#include "scene/gui/button.h"
#include "scene/gui/graph_edit.h"
#include "scene/gui/popup.h"
#include "scene/gui/tree.h"

class AnlNoiseEditor : public VBoxContainer {

	GDCLASS(AnlNoiseEditor, VBoxContainer);

private:
    GraphEdit *graph;
	MenuButton *add_node;

    UndoRedo *undo_redo;

    static AnlNoiseEditor *singleton;

// protected:
// 	void _notification(int p_what);
// 	static void _bind_methods();

public:
	static AnlNoiseEditor *get_singleton() { return singleton; }

	virtual Size2 get_minimum_size() const;
	AnlNoiseEditor();
};

class AnlNoiseEditorPlugin : public EditorPlugin {

	GDCLASS(AnlNoiseEditorPlugin, EditorPlugin);

	AnlNoiseEditor *anl_noise_editor;
	EditorNode *editor;
	Button *button;

public:
	virtual String get_name() const { return "AnlNoise"; }
	bool has_main_screen() const { return false; }
	virtual void edit(Object *p_object);
	virtual bool handles(Object *p_object) const;
	virtual void make_visible(bool p_visible);

	AnlNoiseEditorPlugin(EditorNode *p_node);
	~AnlNoiseEditorPlugin();
};

#endif
