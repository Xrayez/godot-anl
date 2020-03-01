#include "visual_noise_component_editor_plugin.h"
#include "../visual_noise_nodes.h"
#include "visual_noise_editor_plugin.h"

#include "core/io/resource_loader.h"
#include "core/os/input.h"
#include "core/os/keyboard.h"
#include "core/project_settings.h"
#include "editor/editor_properties.h"
#include "editor/editor_scale.h"
#include "scene/gui/menu_button.h"
#include "scene/gui/panel.h"
#include "scene/main/viewport.h"

///////////////////////////////////

bool VisualAccidentalNoiseComponentEditor::can_edit(const Ref<VisualAccidentalNoiseNodeComponent> &p_comp) {

	Ref<VisualAccidentalNoiseNodeComponent> comp = p_comp;

	return comp.is_valid();
}

void VisualAccidentalNoiseComponentEditor::edit(const Ref<VisualAccidentalNoiseNodeComponent> &p_component) {

	if (component == p_component) {
		return;
	}
	if (p_component.is_valid()) {
		component = p_component;
		_update_graph();
	}
}

void VisualAccidentalNoiseComponentEditor::add_plugin(const Ref<VisualAccidentalNoiseNodePlugin> &p_plugin) {

	if (plugins.find(p_plugin) != -1)
		return;

	plugins.push_back(p_plugin);
}

void VisualAccidentalNoiseComponentEditor::remove_plugin(const Ref<VisualAccidentalNoiseNodePlugin> &p_plugin) {

	plugins.erase(p_plugin);
}

void VisualAccidentalNoiseComponentEditor::add_custom_type(const String &p_name, const String &p_category, const Ref<Script> &p_script) {

	for (int i = 0; i < add_options.size(); i++) {
		ERR_FAIL_COND(add_options[i].script == p_script);
	}

	AddOption ao;
	ao.name = p_name;
	ao.script = p_script;
	ao.category = p_category;
	add_options.push_back(ao);

	_update_options_menu();
}

void VisualAccidentalNoiseComponentEditor::remove_custom_type(const Ref<Script> &p_script) {

	for (int i = 0; i < add_options.size(); i++) {
		if (add_options[i].script == p_script) {
			add_options.remove(i);
			return;
		}
	}
	_update_options_menu();
}

void VisualAccidentalNoiseComponentEditor::_update_options_menu() {

	node_desc->set_text("");
	members_dialog->get_ok()->set_disabled(true);

	String prev_category;

	members->clear();
	TreeItem *root = members->create_item();
	TreeItem *category = NULL;

	String filter = node_filter->get_text().strip_edges();
	bool use_filter = !filter.empty();

	Vector<String> categories;

	int item_count = 0;
	bool is_first_item = true;

	Control *gui_base = EditorNode::get_singleton()->get_gui_base();

	for (int i = 0; i < add_options.size() + 1; i++) {

		if (i == add_options.size()) {
			if (category != NULL && item_count == 0) {
				memdelete(category);
			}
			break;
		}
		if (!use_filter || add_options[i].name.findn(filter) != -1) {

			if (prev_category != add_options[i].category) {
				if (category != NULL && item_count == 0) {
					memdelete(category);
				}

				item_count = 0;
				category = members->create_item(root);
				category->set_text(0, add_options[i].category);
				category->set_selectable(0, false);
				if (!use_filter)
					category->set_collapsed(true);
			}
			if (category != NULL) {
				++item_count;
				TreeItem *item = members->create_item(category);
				item->set_text(0, add_options[i].name);
				item->set_icon(0, gui_base->get_icon("int", "EditorIcons"));
				item->set_meta("id", i);
			}
			prev_category = add_options[i].category;
		}
	}
	PopupMenu *menu = add_component->get_popup();
	menu->clear();
	menu->add_item(TTR("New Component"), MENU_CREATE_NEW);
	menu->add_separator();
	menu->add_item(TTR("Load Component..."), MENU_LOAD);
	menu->add_item(TTR("Load Component (Unique)..."), MENU_LOAD_UNIQUE);
	menu->add_separator();
	menu->add_item(TTR("Make Component From Node(s)"), MENU_MAKE_FROM_NODES);

	menu->set_item_icon(menu->get_item_index(MENU_CREATE_NEW), gui_base->get_icon("New", "EditorIcons"));
	menu->set_item_icon(menu->get_item_index(MENU_LOAD), gui_base->get_icon("Load", "EditorIcons"));
	menu->set_item_icon(menu->get_item_index(MENU_LOAD_UNIQUE), gui_base->get_icon("Load", "EditorIcons"));
	menu->set_item_icon(menu->get_item_index(MENU_MAKE_FROM_NODES), gui_base->get_icon("ReparentToNewNode", "EditorIcons"));
}

Size2 VisualAccidentalNoiseComponentEditor::get_minimum_size() const {

	return Size2(10, 200);
}

void VisualAccidentalNoiseComponentEditor::_draw_color_over_button(Object *obj, Color p_color) {

	Button *button = Object::cast_to<Button>(obj);

	if (!button)
		return;

	Ref<StyleBox> normal = get_stylebox("normal", "Button");
	button->draw_rect(Rect2(normal->get_offset(), button->get_size() - normal->get_minimum_size()), p_color);
}

static Ref<StyleBoxEmpty> make_empty_stylebox(float p_margin_left = -1, float p_margin_top = -1, float p_margin_right = -1, float p_margin_bottom = -1) {

	Ref<StyleBoxEmpty> style(memnew(StyleBoxEmpty));

	style->set_default_margin(MARGIN_LEFT, p_margin_left * EDSCALE);
	style->set_default_margin(MARGIN_RIGHT, p_margin_right * EDSCALE);
	style->set_default_margin(MARGIN_BOTTOM, p_margin_bottom * EDSCALE);
	style->set_default_margin(MARGIN_TOP, p_margin_top * EDSCALE);

	return style;
}

// [TODO] BREAKS COMPAT (line 3)
// void VisualAccidentalNoiseComponentEditor::_update_created_node(GraphNode *node) {

// 	if (EditorSettings::get_singleton()->get("interface/theme/use_graph_node_headers")) {
// 		Ref<StyleBoxFlat> sb = node->get_stylebox("frame", "GraphNode");
// 		Color c = sb->get_border_color();
// 		Color mono_color = ((c.r + c.g + c.b) / 3) < 0.7 ? Color(1.0, 1.0, 1.0) : Color(0.0, 0.0, 0.0);
// 		mono_color.a = 0.85;
// 		c = mono_color;

// 		node->add_color_override("title_color", c);
// 		c.a = 0.7;
// 		node->add_color_override("close_color", c);
// 	}
// }

const Color VisualAccidentalNoiseComponentEditor::type_color[2] = {
	Color::html("#2bc8ff"),
	Color::html("#d43700"),
};

void VisualAccidentalNoiseComponentEditor::_update_graph() {

	ERR_FAIL_COND(component.is_null());

	if (updating)
		return;

	graph->set_scroll_ofs(component->get_graph_offset() * EDSCALE);

	graph->clear_connections();
	//erase all nodes
	for (int i = 0; i < graph->get_child_count(); i++) {

		if (Object::cast_to<GraphNode>(graph->get_child(i))) {
			memdelete(graph->get_child(i));
			i--;
		}
	}

	List<VisualAccidentalNoiseNodeComponent::Connection> connections;
	component->get_node_connections(&connections);

	Ref<StyleBoxEmpty> label_style = make_empty_stylebox(2, 1, 2, 1);

	Vector<int> nodes = component->get_node_list();

	for (int n_i = 0; n_i < nodes.size(); n_i++) {

		Vector2 position = component->get_node_position(nodes[n_i]);
		Ref<VisualAccidentalNoiseNode> vanode = component->get_node(nodes[n_i]);

		// TODO: this probably needs refactoring
		Ref<VisualAccidentalNoiseNodeInput> input = vanode;
		Ref<VisualAccidentalNoiseNodeOutput> output = vanode;
		Ref<VisualAccidentalNoiseNodeComponent> comp = vanode;
		Ref<VisualAccidentalNoiseNodeSetVar> setvar = vanode;
		Ref<VisualAccidentalNoiseNodeGetVar> getvar = vanode;
		Ref<VisualAccidentalNoiseNodeSequence> seq = vanode;

		GraphNode *node = memnew(GraphNode);
		graph->add_child(node);

		node->set_offset(position);
		node->set_title(vanode->get_caption());
		node->set_name(itos(nodes[n_i]));

		int port_offset = 0;

		if (setvar.is_valid()) {

			LineEdit *var_name = memnew(LineEdit);
			var_name->set_text(setvar->get_var());
			node->add_child(var_name);
			var_name->connect("text_entered", this, "_line_edit_changed", varray(var_name, nodes[n_i]));
			var_name->connect("focus_exited", this, "_line_edit_focus_out", varray(var_name, nodes[n_i]));

			port_offset++;

		} else if (getvar.is_valid()) {

			LineEdit *var_name = memnew(LineEdit);
			var_name->set_text(getvar->get_var());
			node->add_child(var_name);
			var_name->connect("text_entered", this, "_line_edit_changed", varray(var_name, nodes[n_i]));
			var_name->connect("focus_exited", this, "_line_edit_focus_out", varray(var_name, nodes[n_i]));

			port_offset++;
		}

		if (nodes[n_i] >= 2) {
			node->set_show_close_button(true);
			node->connect("close_request", this, "_delete_request", varray(nodes[n_i]), CONNECT_DEFERRED);
		}

		node->connect("dragged", this, "_node_dragged", varray(nodes[n_i]));

		if (comp.is_valid()) {
			// Component's name
			LineEdit *name = memnew(LineEdit);
			name->set_text(comp->get_component_name());
			name->set_expand_to_text_length(true);

			node->add_child(name);
			name->connect("text_entered", this, "_component_renamed", varray(nodes[n_i]));
			name->connect("focus_exited", this, "_component_renamed_focus_out", varray(name, nodes[n_i]));
			port_offset++;

			node->add_child(memnew(HSeparator));
			port_offset++;

		} else if (input.is_valid()) {
			// Inputs's name
			LineEdit *name = memnew(LineEdit);
			name->set_text(input->get_input_name());
			name->set_expand_to_text_length(true);
			node->add_child(name);
			name->connect("text_entered", this, "_input_renamed", varray(nodes[n_i]));
			name->connect("focus_exited", this, "_input_renamed_focus_out", varray(name, nodes[n_i]));

			port_offset++;
		}

		Control *custom_editor = NULL;

		for (int i = 0; i < plugins.size(); i++) {
			custom_editor = plugins.write[i]->create_editor(vanode);
			if (custom_editor) {
				break;
			}
		}

		if (custom_editor && vanode->get_output_port_count() > 0 && vanode->get_output_port_name(0) == "" && (vanode->get_input_port_count() == 0 || vanode->get_input_port_name(0) == "")) {
			//will be embedded in first port
		} else if (custom_editor) {
			port_offset++;
			node->add_child(custom_editor);
			custom_editor = NULL;
		}

		for (int i = 0; i < MAX(vanode->get_input_port_count(), vanode->get_output_port_count()); i++) {

			// Slightly randomize port connection colors by port type
			Color cs = type_color[0];
			Color ci = type_color[1];

			float cs_h = cs.get_h() * (Math::randf() * 0.25 + 0.75);
			float ci_h = ci.get_h() * (Math::randf() * 0.25 + 0.75);

			float cs_s = 0.5 + Math::randf() * 0.5;
			float ci_s = 0.5 + Math::randf() * 0.5;

			cs.set_hsv(cs_h, cs_s, cs.get_v());
			ci.set_hsv(ci_h, ci_s, ci.get_v());

			const Color type_color_var[2] = { cs, ci };

			// Check left and right ports
			if (vanode->is_port_separator(i)) {
				node->add_child(memnew(HSeparator));
				port_offset++;
			}

			bool valid_left = i < vanode->get_input_port_count();
			VisualAccidentalNoiseNode::PortType port_left = VisualAccidentalNoiseNode::PORT_TYPE_SCALAR;
			bool port_left_used = false;
			String name_left;
			if (valid_left) {
				name_left = vanode->get_input_port_name(i);
				port_left = vanode->get_input_port_type(i);
				for (List<VisualAccidentalNoiseNodeComponent::Connection>::Element *E = connections.front(); E; E = E->next()) {
					if (E->get().to_node == nodes[n_i] && E->get().to_port == i) {
						port_left_used = true;
					}
				}
			}
			bool valid_right = i < vanode->get_output_port_count();
			VisualAccidentalNoiseNode::PortType port_right = VisualAccidentalNoiseNode::PORT_TYPE_SCALAR;
			String name_right;
			if (valid_right) {
				name_right = vanode->get_output_port_name(i);
				port_right = vanode->get_output_port_type(i);
			}

			Color port_left_color = type_color_var[port_left];
			Color port_right_color = type_color_var[port_right];

			if (seq.is_valid()) {
				int selected_port = seq->get_selected_input() - 1;
				VisualAccidentalNoiseNodeSequence::Operator op = seq->get_operator();
				if (i == selected_port && op == VisualAccidentalNoiseNodeSequence::OP_SELECT) {
					port_left_color = Color(1, 1, 0);
				}
			}

			HBoxContainer *hb = memnew(HBoxContainer);

			Variant default_value;

			if (valid_left && !port_left_used) {
				default_value = vanode->get_input_port_default_value(i);
			}

			if (default_value.get_type() != Variant::NIL) { // only a label
				Button *button = memnew(Button);
				hb->add_child(button);
				button->connect("pressed", this, "_edit_port_default_input", varray(button, nodes[n_i], i));

				switch (default_value.get_type()) {

					case Variant::INT:
					case Variant::REAL: {
						button->set_text(String::num(default_value, 4));
					} break;
					default: {}
				}
			}

			if (i == 0 && custom_editor && comp.is_null()) {

				hb->add_child(custom_editor);
				custom_editor->set_h_size_flags(SIZE_EXPAND_FILL);
			} else {

				if (valid_left) {

					Label *label = memnew(Label);
					label->set_text(name_left);
					label->add_style_override("normal", label_style); //more compact
					hb->add_child(label);
				}

				hb->add_spacer();

				if (valid_right) {

					Label *label = memnew(Label);
					label->set_text(name_right);
					label->set_align(Label::ALIGN_RIGHT);
					label->add_style_override("normal", label_style); //more compact
					hb->add_child(label);
				}
			}

			if (valid_right || output.is_valid()) {
				TextureButton *preview = memnew(TextureButton);
				preview->set_toggle_mode(true);
				preview->set_normal_texture(get_icon("GuiVisibilityHidden", "EditorIcons"));
				preview->set_pressed_texture(get_icon("GuiVisibilityVisible", "EditorIcons"));
				preview->set_v_size_flags(SIZE_SHRINK_CENTER);

				if (vanode->get_output_port_for_preview() == i) {
					preview->set_pressed(true);
				}

				preview->connect("pressed", this, "_preview_select_port", varray(nodes[n_i], i), CONNECT_DEFERRED);
				hb->add_child(preview);
			}

			node->add_child(hb);

			node->set_slot(i + port_offset, valid_left, port_left, port_left_color, valid_right, port_right, port_right_color);
		}

		if (comp.is_valid()) {
			// Open in editor button
			node->add_child(memnew(HSeparator));
			Button *open_in_editor = memnew(Button);
			open_in_editor->set_text(TTR("Open Editor"));
			open_in_editor->set_icon(get_icon("Edit", "EditorIcons"));
			node->add_child(open_in_editor);
			open_in_editor->connect("pressed", this, "_open_in_editor", varray(nodes[n_i]), CONNECT_DEFERRED);
			open_in_editor->set_h_size_flags(SIZE_SHRINK_CENTER);
		}

		if (vanode->get_output_port_for_preview() >= 0) {
			VisualAccidentalNoiseNodePortPreview *port_preview = memnew(VisualAccidentalNoiseNodePortPreview);

			const Ref<VisualAccidentalNoise> &noise = VisualAccidentalNoiseEditor::get_singleton()->get_noise();
			port_preview->setup(noise, nodes[n_i], vanode->get_output_port_for_preview());
			port_preview->set_h_size_flags(SIZE_SHRINK_CENTER);
			node->add_child(port_preview);
		}

		String error = vanode->get_warning();
		if (error != String()) {
			Label *error_label = memnew(Label);
			error_label->add_color_override("font_color", get_color("error_color", "Editor"));
			error_label->set_text(error);
			node->add_child(error_label);
		}
		// [TODO] BREAKS COMPAT
		// _update_created_node(node);
	}

	for (List<VisualAccidentalNoiseNodeComponent::Connection>::Element *E = connections.front(); E; E = E->next()) {

		int from = E->get().from_node;
		int from_idx = E->get().from_port;
		int to = E->get().to_node;
		int to_idx = E->get().to_port;

		if (component->is_node_connection(from, from_idx, to, to_idx)) {
			graph->connect_node(itos(from), from_idx, itos(to), to_idx);
		}
	}
}

void VisualAccidentalNoiseComponentEditor::_component_renamed(const String &p_text, int p_which) {

	Ref<VisualAccidentalNoiseNodeComponent> comp = component->get_node(p_which);
	ERR_FAIL_COND(comp.is_null());

	GraphNode *gn = Object::cast_to<GraphNode>(graph->get_node(itos(p_which)));

	String prev_name = comp->get_component_name();
	ERR_FAIL_COND(prev_name == String());

	String new_name = p_text;
	ERR_FAIL_COND(new_name == "" || new_name.find(".") != -1 || new_name.find("/") != -1);

	updating = true;
	undo_redo->create_action("Component Renamed");
	undo_redo->add_do_method(comp.ptr(), "set_component_name", new_name);
	undo_redo->add_undo_method(comp.ptr(), "set_component_name", prev_name);
	undo_redo->add_do_method(this, "_update_graph");
	undo_redo->add_undo_method(this, "_update_graph");
	undo_redo->commit_action();
	updating = false;

	gn->set_size(gn->get_minimum_size());
}

void VisualAccidentalNoiseComponentEditor::_component_renamed_focus_out(Node *le, int p_which) {

	_component_renamed(le->call("get_text"), p_which);
}

void VisualAccidentalNoiseComponentEditor::_input_renamed(const String &p_text, int p_which) {

	Ref<VisualAccidentalNoiseNodeInput> input = component->get_node(p_which);
	ERR_FAIL_COND(input.is_null());

	GraphNode *gn = Object::cast_to<GraphNode>(graph->get_node(itos(p_which)));

	String prev_name = input->get_input_name();

	String new_name = p_text;
	ERR_FAIL_COND(new_name == "" || new_name.find(".") != -1 || new_name.find("/") != -1);

	updating = true;
	undo_redo->create_action("Input Node Renamed");
	undo_redo->add_do_method(input.ptr(), "set_input_name", new_name);
	undo_redo->add_undo_method(input.ptr(), "set_input_name", prev_name);
	undo_redo->add_do_method(this, "_update_graph");
	undo_redo->add_undo_method(this, "_update_graph");
	undo_redo->commit_action();
	updating = false;

	gn->set_size(gn->get_minimum_size());
}

void VisualAccidentalNoiseComponentEditor::_input_renamed_focus_out(Node *le, int p_which) {

	_input_renamed(le->call("get_text"), p_which);
}

void VisualAccidentalNoiseComponentEditor::_preview_select_port(int p_node, int p_port) {

	if (component.is_null()) {
		return;
	}

	Ref<VisualAccidentalNoiseNode> node = component->get_node(p_node);

	if (node.is_null()) {
		return;
	}

	if (node->get_output_port_for_preview() == p_port) {
		p_port = -1; //toggle it
	}

	undo_redo->create_action("Set Output Port For Preview");
	undo_redo->add_do_method(node.ptr(), "set_output_port_for_preview", p_port);
	undo_redo->add_undo_method(node.ptr(), "set_output_port_for_preview", node->get_output_port_for_preview());
	undo_redo->add_do_method(this, "_update_graph");
	undo_redo->add_undo_method(this, "_update_graph");
	undo_redo->commit_action();
}

void VisualAccidentalNoiseComponentEditor::_file_opened(const String &p_file) {

	file_loaded = ResourceLoader::load(p_file);
	if (file_loaded.is_valid()) {
		_add_component(MENU_LOAD_CONFIRM);
	}
}

void VisualAccidentalNoiseComponentEditor::_line_edit_changed(const String &p_text, Object *line_edit, int p_node_id) {

	// TODO: better inherit from Var node...

	Ref<VisualAccidentalNoiseNode> vanode = component->get_node(p_node_id);
	Ref<VisualAccidentalNoiseNodeSetVar> setvar = vanode;
	Ref<VisualAccidentalNoiseNodeGetVar> getvar = vanode;

	String name = p_text; // may need to validate

	if (setvar.is_valid()) {

		updating = true;
		undo_redo->create_action("Set Var Name");
		undo_redo->add_do_method(setvar.ptr(), "set_var", name);
		undo_redo->add_undo_method(setvar.ptr(), "set_var", setvar->get_var());
		undo_redo->add_do_method(this, "_update_graph");
		undo_redo->add_undo_method(this, "_update_graph");
		undo_redo->commit_action();
		updating = false;

	} else if (getvar.is_valid()) {

		updating = true;
		undo_redo->create_action("Set Var Name");
		undo_redo->add_do_method(getvar.ptr(), "set_var", name);
		undo_redo->add_undo_method(getvar.ptr(), "set_var", getvar->get_var());
		undo_redo->add_do_method(this, "_update_graph");
		undo_redo->add_undo_method(this, "_update_graph");
		undo_redo->commit_action();
		updating = false;
	}
	Object::cast_to<LineEdit>(line_edit)->set_text(name);
}

void VisualAccidentalNoiseComponentEditor::_line_edit_focus_out(Object *line_edit, int p_node_id) {

	String text = Object::cast_to<LineEdit>(line_edit)->get_text();
	_line_edit_changed(text, line_edit, p_node_id);
}

void VisualAccidentalNoiseComponentEditor::_port_edited() {

	if (component.is_null()) {
		return;
	}

	Variant value = property_editor->get_variant();
	Ref<VisualAccidentalNoiseNode> van = component->get_node(editing_node);
	ERR_FAIL_COND(!van.is_valid());

	undo_redo->create_action("Set Input Default Port");
	undo_redo->add_do_method(van.ptr(), "set_input_port_default_value", editing_port, value);
	undo_redo->add_undo_method(van.ptr(), "set_input_port_default_value", editing_port, van->get_input_port_default_value(editing_port));
	undo_redo->add_do_method(this, "_update_graph");
	undo_redo->add_undo_method(this, "_update_graph");
	undo_redo->commit_action();

	property_editor->hide();
}

void VisualAccidentalNoiseComponentEditor::_edit_port_default_input(Object *p_button, int p_node, int p_port) {

	if (component.is_null()) {
		return;
	}

	Ref<VisualAccidentalNoiseNode> van = component->get_node(p_node);

	Button *button = Object::cast_to<Button>(p_button);
	ERR_FAIL_COND(!button);
	Variant value = van->get_input_port_default_value(p_port);
	property_editor->set_global_position(button->get_global_position() + Vector2(0, button->get_size().height));
	property_editor->edit(NULL, "", value.get_type(), value, 0, "");
	property_editor->popup();
	editing_node = p_node;
	editing_port = p_port;
}

void VisualAccidentalNoiseComponentEditor::_add_node(int p_idx) {

	ERR_FAIL_COND(component.is_null());
	ERR_FAIL_INDEX(p_idx, add_options.size());

	Ref<VisualAccidentalNoiseNode> vanode;

	if (add_options[p_idx].type != String()) {
		VisualAccidentalNoiseNode *van = Object::cast_to<VisualAccidentalNoiseNode>(ClassDB::instance(add_options[p_idx].type));
		ERR_FAIL_COND(!van);
		vanode = Ref<VisualAccidentalNoiseNode>(van);
	} else {
		ERR_FAIL_COND(add_options[p_idx].script.is_null());
		String base_type = add_options[p_idx].script->get_instance_base_type();
		VisualAccidentalNoiseNode *van = Object::cast_to<VisualAccidentalNoiseNode>(ClassDB::instance(base_type));
		ERR_FAIL_COND(!van);
		vanode = Ref<VisualAccidentalNoiseNode>(van);
		vanode->set_script(add_options[p_idx].script.get_ref_ptr());
	}

	Point2 position = graph->get_scroll_ofs();

	if (saved_node_pos_dirty) {
		position += saved_node_pos;
	} else {
		position += graph->get_size() * 0.5;
		position /= EDSCALE;
	}
	saved_node_pos_dirty = false;

	int id_to_use = component->get_valid_node_id();

	undo_redo->create_action("Add Node to Visual Accidental Noise");
	undo_redo->add_do_method(component.ptr(), "add_node", vanode, position, id_to_use);
	undo_redo->add_undo_method(component.ptr(), "remove_node", id_to_use);
	undo_redo->add_do_method(this, "_update_graph");
	undo_redo->add_undo_method(this, "_update_graph");
	undo_redo->commit_action();
}

void VisualAccidentalNoiseComponentEditor::_popup_file_load() {

	open_file->clear_filters();
	List<String> filters;
	ResourceLoader::get_recognized_extensions_for_type("VisualAccidentalNoiseNodeComponent", &filters);
	for (List<String>::Element *E = filters.front(); E; E = E->next()) {
		open_file->add_filter("*." + E->get());
	}
	open_file->popup_centered_ratio();
}

void VisualAccidentalNoiseComponentEditor::_add_component(int p_option) {

	ERR_FAIL_COND(component.is_null());

	Ref<VisualAccidentalNoiseNodeComponent> comp;
	Point2 position = (graph->get_scroll_ofs() + graph->get_size() * 0.5) / EDSCALE;

	switch (p_option) {
		case MENU_CREATE_NEW: {

			comp.instance();

		} break;

		case MENU_LOAD: {
			_popup_file_load();

		} break;

		case MENU_LOAD_UNIQUE: {
			load_file_duplicated = true;
			_popup_file_load();

		} break;

		case MENU_LOAD_CONFIRM: {

			if (load_file_duplicated) {
				comp = file_loaded->duplicate(true);
				load_file_duplicated = false;
			} else {
				comp = file_loaded;
			}
		} break;

		case MENU_MAKE_FROM_NODES: {
			_make_component_from_nodes(position);
		} break;
	}
	if (comp.is_null()) {
		return;
	}
	int id_to_use = component->get_valid_node_id();

	undo_redo->create_action("Add Component to Visual Accidental Noise");
	undo_redo->add_do_method(component.ptr(), "add_node", comp, position, id_to_use);
	undo_redo->add_undo_method(component.ptr(), "remove_node", id_to_use);
	undo_redo->add_do_method(this, "_update_graph");
	undo_redo->add_undo_method(this, "_update_graph");
	undo_redo->commit_action();
}

void VisualAccidentalNoiseComponentEditor::_node_dragged(const Vector2 &p_from, const Vector2 &p_to, int p_node) {

	if (component.is_null()) {
		return;
	}

	updating = true;
	undo_redo->create_action("Node Moved");
	undo_redo->add_do_method(component.ptr(), "set_node_position", p_node, p_to);
	undo_redo->add_undo_method(component.ptr(), "set_node_position", p_node, p_from);
	undo_redo->add_do_method(this, "_update_graph");
	undo_redo->add_undo_method(this, "_update_graph");
	undo_redo->commit_action();
	updating = false;
}

void VisualAccidentalNoiseComponentEditor::_connection_request(const String &p_from, int p_from_index, const String &p_to, int p_to_index) {

	if (component.is_null()) {
		return;
	}

	int from = p_from.to_int();
	int to = p_to.to_int();

	if (!component->can_connect_nodes(from, p_from_index, to, p_to_index)) {
		return;
	}

	undo_redo->create_action("Nodes Connected");

	List<VisualAccidentalNoiseNodeComponent::Connection> conns;
	component->get_node_connections(&conns);

	for (List<VisualAccidentalNoiseNodeComponent::Connection>::Element *E = conns.front(); E; E = E->next()) {
		if (E->get().to_node == to && E->get().to_port == p_to_index) {
			undo_redo->add_do_method(component.ptr(), "disconnect_nodes", E->get().from_node, E->get().from_port, E->get().to_node, E->get().to_port);
			undo_redo->add_undo_method(component.ptr(), "connect_nodes", E->get().from_node, E->get().from_port, E->get().to_node, E->get().to_port);
		}
	}

	undo_redo->add_do_method(component.ptr(), "connect_nodes", from, p_from_index, to, p_to_index);
	undo_redo->add_undo_method(component.ptr(), "disconnect_nodes", from, p_from_index, to, p_to_index);
	undo_redo->add_do_method(this, "_update_graph");
	undo_redo->add_undo_method(this, "_update_graph");
	undo_redo->commit_action();
}

void VisualAccidentalNoiseComponentEditor::_disconnection_request(const String &p_from, int p_from_index, const String &p_to, int p_to_index) {

	if (component.is_null()) {
		return;
	}

	graph->disconnect_node(p_from, p_from_index, p_to, p_to_index);

	int from = p_from.to_int();
	int to = p_to.to_int();

	//updating = true; seems graph edit can handle this, no need to protect
	undo_redo->create_action("Nodes Disconnected");
	undo_redo->add_do_method(component.ptr(), "disconnect_nodes", from, p_from_index, to, p_to_index);
	undo_redo->add_undo_method(component.ptr(), "connect_nodes", from, p_from_index, to, p_to_index);
	undo_redo->add_do_method(this, "_update_graph");
	undo_redo->add_undo_method(this, "_update_graph");
	undo_redo->commit_action();
	//updating = false;
}

void VisualAccidentalNoiseComponentEditor::_connection_to_empty(const String &p_from, int p_from_slot, const Vector2 &p_release_position) {
}

void VisualAccidentalNoiseComponentEditor::_delete_request(int which) {

	if (component.is_null()) {
		return;
	}

	undo_redo->create_action("Delete Node");
	undo_redo->add_do_method(component.ptr(), "remove_node", which);
	undo_redo->add_undo_method(component.ptr(), "add_node", component->get_node(which), component->get_node_position(which), which);

	List<VisualAccidentalNoiseNodeComponent::Connection> conns;
	component->get_node_connections(&conns);

	for (List<VisualAccidentalNoiseNodeComponent::Connection>::Element *E = conns.front(); E; E = E->next()) {
		if (E->get().from_node == which || E->get().to_node == which) {
			undo_redo->add_undo_method(component.ptr(), "connect_nodes", E->get().from_node, E->get().from_port, E->get().to_node, E->get().to_port);
		}
	}

	undo_redo->add_do_method(this, "_update_graph");
	undo_redo->add_undo_method(this, "_update_graph");
	undo_redo->commit_action();
}

void VisualAccidentalNoiseComponentEditor::_node_selected(Object *p_node) {

	if (component.is_null()) {
		return;
	}

	GraphNode *gn = Object::cast_to<GraphNode>(p_node);
	ERR_FAIL_COND(!gn);

	int id = String(gn->get_name()).to_int();

	Ref<VisualAccidentalNoiseNode> vanode = component->get_node(id);
	ERR_FAIL_COND(!vanode.is_valid());

	EditorNode::get_singleton()->push_item(vanode.ptr(), "", true);
}

void VisualAccidentalNoiseComponentEditor::_open_in_editor(int p_which) {

	Ref<VisualAccidentalNoiseNodeComponent> comp = component->get_node(p_which);
	ERR_FAIL_COND(!comp.is_valid());

	VisualAccidentalNoiseEditor::get_singleton()->enter_editor(p_which);
}

void VisualAccidentalNoiseComponentEditor::_graph_gui_input(const Ref<InputEvent> p_event) {

	if (!graph->has_focus())
		return;

	Ref<InputEventMouseButton> mb = p_event;

	if (mb.is_valid() && graph->has_point(mb->get_position())) {

		if (!mb->is_pressed())
			return;

		int mbi = mb->get_button_index();

		if (mbi == BUTTON_RIGHT) {
			// _show_members_dialog(true);

			add_component->get_popup()->set_position(get_viewport()->get_mouse_position());
			add_component->get_popup()->show_modal();
		}
	}
}

void VisualAccidentalNoiseComponentEditor::_show_members_dialog(bool at_mouse_pos) {

	members_dialog->popup();

	if (at_mouse_pos) {
		saved_node_pos_dirty = true;
		saved_node_pos = graph->get_local_mouse_position();

		Point2 gpos = Input::get_singleton()->get_mouse_position();
		members_dialog->popup();
		members_dialog->set_position(gpos);
	} else {
		saved_node_pos_dirty = false;
		members_dialog->set_position(graph->get_global_position() + Point2(5 * EDSCALE, 65 * EDSCALE));
	}

	// keep dialog within window bounds
	Size2 window_size = OS::get_singleton()->get_window_size();
	Rect2 dialog_rect = members_dialog->get_global_rect();
	if (dialog_rect.position.y + dialog_rect.size.y > window_size.y) {
		int difference = dialog_rect.position.y + dialog_rect.size.y - window_size.y;
		members_dialog->set_position(members_dialog->get_position() - Point2(0, difference));
	}
	if (dialog_rect.position.x + dialog_rect.size.x > window_size.x) {
		int difference = dialog_rect.position.x + dialog_rect.size.x - window_size.x;
		members_dialog->set_position(members_dialog->get_position() - Point2(difference, 0));
	}

	node_filter->call_deferred("grab_focus"); // still not visible
	node_filter->select_all();
}

void VisualAccidentalNoiseComponentEditor::_sbox_input(const Ref<InputEvent> &p_ie) {
	Ref<InputEventKey> ie = p_ie;
	if (ie.is_valid() && (ie->get_scancode() == KEY_UP ||
								 ie->get_scancode() == KEY_DOWN ||
								 ie->get_scancode() == KEY_ENTER ||
								 ie->get_scancode() == KEY_KP_ENTER)) {

		members->call("_gui_input", ie);
		node_filter->accept_event();
	}
}

void VisualAccidentalNoiseComponentEditor::_notification(int p_what) {

	if (p_what == NOTIFICATION_ENTER_TREE) {

		node_filter->set_clear_button_enabled(true);

		// collapse by default

		TreeItem *category = members->get_root()->get_children();
		while (category) {
			category->set_collapsed(true);
			category = category->get_next();
		}
	}

	if (p_what == NOTIFICATION_DRAG_BEGIN) {
		Dictionary dd = get_viewport()->gui_get_drag_data();
		if (members->is_visible_in_tree() && dd.has("id")) {
			members->set_drop_mode_flags(Tree::DROP_MODE_ON_ITEM);
		}
	} else if (p_what == NOTIFICATION_DRAG_END) {
		members->set_drop_mode_flags(0);
	}

	if (p_what == NOTIFICATION_ENTER_TREE || p_what == NOTIFICATION_THEME_CHANGED) {

		error_panel->add_style_override("panel", get_stylebox("bg", "Tree"));
		error_label->add_color_override("font_color", get_color("error_color", "Editor"));

		node_filter->set_right_icon(Control::get_icon("Search", "EditorIcons"));

		tools->set_icon(EditorNode::get_singleton()->get_gui_base()->get_icon("Tools", "EditorIcons"));

		add_node->set_icon(get_icon("Add", "EditorIcons"));
		add_component->set_icon(get_icon("Add", "EditorIcons"));

		if (p_what == NOTIFICATION_THEME_CHANGED && is_visible_in_tree()) {
			_update_graph();
		}
	}
}

void VisualAccidentalNoiseComponentEditor::_scroll_changed(const Vector2 &p_scroll) {

	if (component.is_null()) {
		return;
	}

	if (updating)
		return;

	updating = true;
	component->set_graph_offset(p_scroll / EDSCALE);
	updating = false;
}

void VisualAccidentalNoiseComponentEditor::_node_changed(int p_id) {

	if (updating)
		return;

	if (is_visible_in_tree()) {
		_update_graph();
	}
}

void VisualAccidentalNoiseComponentEditor::_duplicate_nodes() {

	if (component.is_null()) {
		return;
	}
	List<int> nodes;
	Set<int> excluded;

	for (int i = 0; i < graph->get_child_count(); i++) {

		GraphNode *gn = Object::cast_to<GraphNode>(graph->get_child(i));
		if (gn) {
			int id = String(gn->get_name()).to_int();

			Ref<VisualAccidentalNoiseNode> node = component->get_node(id);
			Ref<VisualAccidentalNoiseNodeOutput> output = node;
			if (output.is_valid()) { // can't duplicate output
				excluded.insert(id);
				continue;
			}
			if (node.is_valid() && gn->is_selected()) {
				nodes.push_back(id);
			}
			excluded.insert(id);
		}
	}
	if (nodes.empty())
		return;

	undo_redo->create_action("Duplicate Nodes");

	int base_id = component->get_valid_node_id();
	int id_from = base_id;
	Map<int, int> connection_remap;

	for (List<int>::Element *E = nodes.front(); E; E = E->next()) {

		connection_remap[E->get()] = id_from;
		Ref<VisualAccidentalNoiseNode> node = component->get_node(E->get());

		Ref<VisualAccidentalNoiseNode> dupli = node->duplicate();

		undo_redo->add_do_method(component.ptr(), "add_node", dupli, component->get_node_position(E->get()) + Vector2(10, 10) * EDSCALE, id_from);
		undo_redo->add_undo_method(component.ptr(), "remove_node", id_from);

		id_from++;
	}

	List<VisualAccidentalNoiseNodeComponent::Connection> conns;
	component->get_node_connections(&conns);

	for (List<VisualAccidentalNoiseNodeComponent::Connection>::Element *E = conns.front(); E; E = E->next()) {
		if (connection_remap.has(E->get().from_node) && connection_remap.has(E->get().to_node)) {
			undo_redo->add_do_method(component.ptr(), "connect_nodes", connection_remap[E->get().from_node], E->get().from_port, connection_remap[E->get().to_node], E->get().to_port);
		}
	}

	undo_redo->add_do_method(this, "_update_graph");
	undo_redo->add_undo_method(this, "_update_graph");
	undo_redo->commit_action();

	// reselect duplicated nodes by excluding the other ones
	for (int i = 0; i < graph->get_child_count(); i++) {

		GraphNode *gn = Object::cast_to<GraphNode>(graph->get_child(i));
		if (gn) {
			int id = String(gn->get_name()).to_int();
			if (!excluded.has(id)) {
				gn->set_selected(true);
			} else {
				gn->set_selected(false);
			}
		}
	}
}

void VisualAccidentalNoiseComponentEditor::_on_nodes_delete() {

	List<int> to_erase;

	for (int i = 0; i < graph->get_child_count(); i++) {
		GraphNode *gn = Object::cast_to<GraphNode>(graph->get_child(i));
		if (gn) {
			if (gn->is_selected() && gn->is_close_button_visible()) {
				to_erase.push_back(gn->get_name().operator String().to_int());
			}
		}
	}

	if (to_erase.empty())
		return;

	undo_redo->create_action(TTR("Delete Nodes"));

	for (List<int>::Element *F = to_erase.front(); F; F = F->next()) {
		undo_redo->add_do_method(component.ptr(), "remove_node", F->get());
		undo_redo->add_undo_method(component.ptr(), "add_node", component->get_node(F->get()), component->get_node_position(F->get()), F->get());
	}

	List<VisualAccidentalNoiseNodeComponent::Connection> conns;
	component->get_node_connections(&conns);

	List<VisualAccidentalNoiseNodeComponent::Connection> used_conns;
	for (List<int>::Element *F = to_erase.front(); F; F = F->next()) {
		for (List<VisualAccidentalNoiseNodeComponent::Connection>::Element *E = conns.front(); E; E = E->next()) {
			if (E->get().from_node == F->get() || E->get().to_node == F->get()) {

				bool cancel = false;
				for (List<VisualAccidentalNoiseNodeComponent::Connection>::Element *R = used_conns.front(); R; R = R->next()) {
					if (R->get().from_node == E->get().from_node && R->get().from_port == E->get().from_port && R->get().to_node == E->get().to_node && R->get().to_port == E->get().to_port) {
						cancel = true; // to avoid ERR_ALREADY_EXISTS warning
						break;
					}
				}
				if (!cancel) {
					undo_redo->add_undo_method(component.ptr(), "connect_nodes", E->get().from_node, E->get().from_port, E->get().to_node, E->get().to_port);
					used_conns.push_back(E->get());
				}
			}
		}
	}

	undo_redo->add_do_method(this, "_update_graph");
	undo_redo->add_undo_method(this, "_update_graph");
	undo_redo->commit_action();
}

void VisualAccidentalNoiseComponentEditor::_member_filter_changed(const String &p_text) {
	_update_options_menu();
}

void VisualAccidentalNoiseComponentEditor::_member_selected() {
	TreeItem *item = members->get_selected();

	if (item != NULL && item->has_meta("id")) {
		members_dialog->get_ok()->set_disabled(false);
		node_desc->set_text(add_options[item->get_meta("id")].description);
	} else {
		members_dialog->get_ok()->set_disabled(true);
		node_desc->set_text("");
	}
}

void VisualAccidentalNoiseComponentEditor::_member_unselected() {
}

void VisualAccidentalNoiseComponentEditor::_member_create() {
	TreeItem *item = members->get_selected();
	if (item != NULL && item->has_meta("id")) {
		int idx = members->get_selected()->get_meta("id");
		_add_node(idx);
		members_dialog->hide();
	}
}

void VisualAccidentalNoiseComponentEditor::_tools_menu_option(int p_idx) {

	TreeItem *category = members->get_root()->get_children();

	switch (p_idx) {
		case EXPAND_ALL:

			while (category) {
				category->set_collapsed(false);
				category = category->get_next();
			}
			break;

		case COLLAPSE_ALL:

			while (category) {
				category->set_collapsed(true);
				category = category->get_next();
			}
			break;
		default:
			break;
	}
}

Variant VisualAccidentalNoiseComponentEditor::get_drag_data_fw(const Point2 &p_point, Control *p_from) {

	if (p_from == members) {
		TreeItem *it = members->get_item_at_position(p_point);
		if (!it)
			return Variant();
		if (!it->has_meta("id"))
			return Variant();

		int id = it->get_meta("id");
		AddOption op = add_options[id];

		Dictionary d;
		d["id"] = id;

		Label *label = memnew(Label);
		label->set_text(it->get_text(0));
		set_drag_preview(label);
		return d;
	}
	return Variant();
}

bool VisualAccidentalNoiseComponentEditor::can_drop_data_fw(const Point2 &p_point, const Variant &p_data, Control *p_from) const {

	if (p_from == graph) {

		Dictionary d = p_data;

		if (d.has("id")) {
			return true;
		}
	}
	return false;
}

void VisualAccidentalNoiseComponentEditor::drop_data_fw(const Point2 &p_point, const Variant &p_data, Control *p_from) {

	if (p_from == graph) {

		Dictionary d = p_data;

		if (d.has("id")) {
			int idx = d["id"];
			saved_node_pos = p_point;
			saved_node_pos_dirty = true;
			_add_node(idx);
		}
	}
}

void VisualAccidentalNoiseComponentEditor::_make_component_from_nodes(const Vector2 &p_ofs) {

	if (component.is_null()) {
		return;
	}
	if (component->get_valid_node_id() <= 2) {
		EditorNode::get_singleton()->show_warning(TTR("Nothing to make a component from."));
		return;
	}
	List<int> selected;
	Set<int> excluded;

	int output_id = VisualAccidentalNoiseNodeComponent::NODE_ID_OUTPUT;

	for (int i = 0; i < graph->get_child_count(); i++) {

		GraphNode *gn = Object::cast_to<GraphNode>(graph->get_child(i));
		if (!gn)
			continue;

		int id = String(gn->get_name()).to_int();
		if (id == output_id)
			continue;

		if (gn->is_selected())
			selected.push_back(id);
		else
			excluded.insert(id);
	}
	List<VisualAccidentalNoiseNodeComponent::Connection> conns;
	component->get_node_connections(&conns);

	Ref<VisualAccidentalNoiseNode> base_node;
	int base_id = output_id;

	if (selected.size() <= 1) {
		// Recursively fetch all the connected nodes to this one
		if (selected.size() == 1) {
			base_id = selected[0];
			base_node = component->get_node(base_id);
		}
		Set<int> to_check;
		to_check.insert(base_id);
		excluded.erase(base_id);

		while (!to_check.empty()) {

			int id = to_check.back()->get();
			to_check.erase(id);

			for (List<VisualAccidentalNoiseNodeComponent::Connection>::Element *E = conns.front(); E; E = E->next()) {
				int from_id = E->get().from_node;

				if (id == E->get().to_node) {
					if (!to_check.has(from_id)) {
						selected.push_back(from_id);
						to_check.insert(from_id);
					}
				}
				if (excluded.has(id)) {
					excluded.erase(id);
				}
			}
		}
	}
	// Simply duplicate this component, as well as other component's properties
	Ref<VisualAccidentalNoiseNodeComponent> new_comp = component->duplicate();
	int new_comp_id = component->get_valid_node_id();

	// Add new component to this one
	undo_redo->create_action("Make Component From Nodes");

	Vector2 ofs = p_ofs;
	if (base_node.is_valid()) {
		ofs = component->get_node_position(base_id);
	}
	undo_redo->add_do_method(component.ptr(), "add_node", new_comp, ofs, new_comp_id);
	undo_redo->add_undo_method(component.ptr(), "remove_node", new_comp_id);

	// Remove unselected nodes from new component
	for (Set<int>::Element *E = excluded.front(); E; E = E->next()) {

		int id = E->get();
		Ref<VisualAccidentalNoiseNode> node = new_comp->get_node(id);

		undo_redo->add_do_method(new_comp.ptr(), "remove_node", id);
		undo_redo->add_undo_method(new_comp.ptr(), "add_node", node, new_comp->get_node_position(id), id);
	}
	// Restore possible output connections
	if (base_node.is_valid()) {
		int to_node = output_id;
		for (List<VisualAccidentalNoiseNodeComponent::Connection>::Element *E = conns.front(); E; E = E->next()) {
			if (base_id == E->get().from_node) {
				undo_redo->add_do_method(component.ptr(), "connect_nodes", new_comp_id, E->get().from_port, E->get().to_node, E->get().to_port);
				// Also connect duplicated node (from base one) to output in new component
				// The id should be the same because we cloned this component completely
				undo_redo->add_do_method(new_comp.ptr(), "connect_nodes", base_id, E->get().from_port, output_id, 0);
			}
		}
	}
	// Remove original nodes as they were "moved" into a new component
	for (List<int>::Element *E = selected.front(); E; E = E->next()) {

		int id = E->get();
		Ref<VisualAccidentalNoiseNode> node = component->get_node(id);

		undo_redo->add_do_method(component.ptr(), "remove_node", id);
		undo_redo->add_undo_method(component.ptr(), "add_node", node, component->get_node_position(id), id);
	}
	for (List<VisualAccidentalNoiseNodeComponent::Connection>::Element *E = conns.front(); E; E = E->next()) {
		undo_redo->add_undo_method(component.ptr(), "connect_nodes", E->get().from_node, E->get().from_port, E->get().to_node, E->get().to_port);
	}

	undo_redo->add_do_method(this, "_update_graph");
	undo_redo->add_undo_method(this, "_update_graph");

	undo_redo->commit_action();
}

void VisualAccidentalNoiseComponentEditor::_bind_methods() {

	ClassDB::bind_method("_component_renamed", &VisualAccidentalNoiseComponentEditor::_component_renamed);
	ClassDB::bind_method("_component_renamed_focus_out", &VisualAccidentalNoiseComponentEditor::_component_renamed_focus_out);
	ClassDB::bind_method("_input_renamed", &VisualAccidentalNoiseComponentEditor::_input_renamed);
	ClassDB::bind_method("_input_renamed_focus_out", &VisualAccidentalNoiseComponentEditor::_input_renamed_focus_out);
	ClassDB::bind_method("_update_graph", &VisualAccidentalNoiseComponentEditor::_update_graph);
	ClassDB::bind_method("_update_options_menu", &VisualAccidentalNoiseComponentEditor::_update_options_menu);
	ClassDB::bind_method("_add_node", &VisualAccidentalNoiseComponentEditor::_add_node);
	ClassDB::bind_method("_add_component", &VisualAccidentalNoiseComponentEditor::_add_component);
	ClassDB::bind_method("_node_dragged", &VisualAccidentalNoiseComponentEditor::_node_dragged);
	ClassDB::bind_method("_connection_request", &VisualAccidentalNoiseComponentEditor::_connection_request);
	ClassDB::bind_method("_disconnection_request", &VisualAccidentalNoiseComponentEditor::_disconnection_request);
	ClassDB::bind_method("_node_selected", &VisualAccidentalNoiseComponentEditor::_node_selected);
	ClassDB::bind_method("_open_in_editor", &VisualAccidentalNoiseComponentEditor::_open_in_editor);
	ClassDB::bind_method("_scroll_changed", &VisualAccidentalNoiseComponentEditor::_scroll_changed);
	ClassDB::bind_method("_delete_request", &VisualAccidentalNoiseComponentEditor::_delete_request);
	ClassDB::bind_method("_on_nodes_delete", &VisualAccidentalNoiseComponentEditor::_on_nodes_delete);
	ClassDB::bind_method("_node_changed", &VisualAccidentalNoiseComponentEditor::_node_changed);
	ClassDB::bind_method("_edit_port_default_input", &VisualAccidentalNoiseComponentEditor::_edit_port_default_input);
	ClassDB::bind_method("_port_edited", &VisualAccidentalNoiseComponentEditor::_port_edited);
	ClassDB::bind_method("_connection_to_empty", &VisualAccidentalNoiseComponentEditor::_connection_to_empty);
	ClassDB::bind_method("_line_edit_focus_out", &VisualAccidentalNoiseComponentEditor::_line_edit_focus_out);
	ClassDB::bind_method("_line_edit_changed", &VisualAccidentalNoiseComponentEditor::_line_edit_changed);
	ClassDB::bind_method("_duplicate_nodes", &VisualAccidentalNoiseComponentEditor::_duplicate_nodes);
	ClassDB::bind_method("_preview_select_port", &VisualAccidentalNoiseComponentEditor::_preview_select_port);
	ClassDB::bind_method("_file_opened", &VisualAccidentalNoiseComponentEditor::_file_opened);
	ClassDB::bind_method("_graph_gui_input", &VisualAccidentalNoiseComponentEditor::_graph_gui_input);

	ClassDB::bind_method(D_METHOD("get_drag_data_fw"), &VisualAccidentalNoiseComponentEditor::get_drag_data_fw);
	ClassDB::bind_method(D_METHOD("can_drop_data_fw"), &VisualAccidentalNoiseComponentEditor::can_drop_data_fw);
	ClassDB::bind_method(D_METHOD("drop_data_fw"), &VisualAccidentalNoiseComponentEditor::drop_data_fw);

	ClassDB::bind_method("_tools_menu_option", &VisualAccidentalNoiseComponentEditor::_tools_menu_option);
	ClassDB::bind_method("_show_members_dialog", &VisualAccidentalNoiseComponentEditor::_show_members_dialog);
	ClassDB::bind_method("_sbox_input", &VisualAccidentalNoiseComponentEditor::_sbox_input);
	ClassDB::bind_method("_member_filter_changed", &VisualAccidentalNoiseComponentEditor::_member_filter_changed);
	ClassDB::bind_method("_member_selected", &VisualAccidentalNoiseComponentEditor::_member_selected);
	ClassDB::bind_method("_member_unselected", &VisualAccidentalNoiseComponentEditor::_member_unselected);
	ClassDB::bind_method("_member_create", &VisualAccidentalNoiseComponentEditor::_member_create);
}

VisualAccidentalNoiseComponentEditor *VisualAccidentalNoiseComponentEditor::singleton = NULL;

VisualAccidentalNoiseComponentEditor::VisualAccidentalNoiseComponentEditor() {

	singleton = this;
	updating = false;

	saved_node_pos_dirty = false;
	saved_node_pos = Point2(0, 0);

	graph = memnew(GraphEdit);
	add_child(graph);
	graph->set_drag_forwarding(this);

	graph->add_valid_right_disconnect_type(VisualAccidentalNoiseNode::PORT_TYPE_SCALAR);
	graph->add_valid_right_disconnect_type(VisualAccidentalNoiseNode::PORT_TYPE_INDEX);

	graph->set_v_size_flags(SIZE_EXPAND_FILL);

	graph->connect("connection_request", this, "_connection_request", varray(), CONNECT_DEFERRED);
	graph->connect("disconnection_request", this, "_disconnection_request", varray(), CONNECT_DEFERRED);
	graph->connect("node_selected", this, "_node_selected");
	graph->connect("scroll_offset_changed", this, "_scroll_changed");
	graph->connect("duplicate_nodes_request", this, "_duplicate_nodes");
	graph->connect("delete_nodes_request", this, "_on_nodes_delete");
	graph->connect("gui_input", this, "_graph_gui_input");

	graph->add_valid_connection_type(VisualAccidentalNoiseNode::PORT_TYPE_SCALAR, VisualAccidentalNoiseNode::PORT_TYPE_SCALAR);
	graph->add_valid_connection_type(VisualAccidentalNoiseNode::PORT_TYPE_SCALAR, VisualAccidentalNoiseNode::PORT_TYPE_SCALAR);

	VSeparator *vs = memnew(VSeparator);
	graph->get_zoom_hbox()->add_child(vs);
	graph->get_zoom_hbox()->move_child(vs, 0);

	add_node = memnew(ToolButton);
	graph->get_zoom_hbox()->add_child(add_node);
	add_node->set_text(TTR("Add Node.."));
	graph->get_zoom_hbox()->move_child(add_node, 0);
	add_node->connect("pressed", this, "_show_members_dialog", varray(false));

	add_component = memnew(MenuButton);
	graph->get_zoom_hbox()->add_child(add_component);
	add_component->set_text(TTR("Add Component.."));
	graph->get_zoom_hbox()->move_child(add_component, 1);
	add_component->get_popup()->connect("id_pressed", this, "_add_component");

	///////////////////////////////////////
	// NOISE NODES TREE
	///////////////////////////////////////

	VBoxContainer *members_vb = memnew(VBoxContainer);
	members_vb->set_v_size_flags(SIZE_EXPAND_FILL);

	HBoxContainer *filter_hb = memnew(HBoxContainer);
	members_vb->add_child(filter_hb);

	node_filter = memnew(LineEdit);
	filter_hb->add_child(node_filter);
	node_filter->connect("text_changed", this, "_member_filter_changed");
	node_filter->connect("gui_input", this, "_sbox_input");
	node_filter->set_h_size_flags(SIZE_EXPAND_FILL);
	node_filter->set_placeholder(TTR("Search"));

	tools = memnew(MenuButton);
	filter_hb->add_child(tools);
	tools->set_tooltip(TTR("Options"));
	tools->get_popup()->connect("id_pressed", this, "_tools_menu_option");
	tools->get_popup()->add_item(TTR("Expand All"), EXPAND_ALL);
	tools->get_popup()->add_item(TTR("Collapse All"), COLLAPSE_ALL);

	members = memnew(Tree);
	members_vb->add_child(members);
	members->set_drag_forwarding(this);
	members->set_h_size_flags(SIZE_EXPAND_FILL);
	members->set_v_size_flags(SIZE_EXPAND_FILL);
	members->set_hide_root(true);
	members->set_allow_reselect(true);
	members->set_hide_folding(false);
	members->set_custom_minimum_size(Size2(180 * EDSCALE, 200 * EDSCALE));
	members->connect("item_activated", this, "_member_create");
	members->connect("item_selected", this, "_member_selected");
	members->connect("nothing_selected", this, "_member_unselected");

	Label *desc_label = memnew(Label);
	members_vb->add_child(desc_label);
	desc_label->set_text(TTR("Description:"));

	node_desc = memnew(RichTextLabel);
	members_vb->add_child(node_desc);
	node_desc->set_h_size_flags(SIZE_EXPAND_FILL);
	node_desc->set_v_size_flags(SIZE_FILL);
	node_desc->set_custom_minimum_size(Size2(0, 70 * EDSCALE));

	members_dialog = memnew(ConfirmationDialog);
	members_dialog->set_title(TTR("Create Noise Node"));
	members_dialog->add_child(members_vb);
	members_dialog->get_ok()->set_text(TTR("Create"));
	members_dialog->get_ok()->connect("pressed", this, "_member_create");
	members_dialog->get_ok()->set_disabled(true);
	members_dialog->set_resizable(true);
	members_dialog->set_as_minsize();
	add_child(members_dialog);

	alert = memnew(AcceptDialog);
	alert->set_as_minsize();
	alert->get_label()->set_autowrap(true);
	alert->get_label()->set_align(Label::ALIGN_CENTER);
	alert->get_label()->set_valign(Label::VALIGN_CENTER);
	alert->get_label()->set_custom_minimum_size(Size2(400, 60) * EDSCALE);
	add_child(alert);

	// Add node options
	add_options.push_back(AddOption("Input", "Inputs", "VisualAccidentalNoiseNodeInput", TTR("Adds a named input for a component node.")));
	add_options.push_back(AddOption("Seed", "Inputs", "VisualAccidentalNoiseNodeSeed", TTR("Initializes a seed value for nodes.")));
	add_options.push_back(AddOption("Seeder", "Inputs", "VisualAccidentalNoiseNodeSeeder", TTR("Initializes a seed value for nodes based on input.")));
	add_options.push_back(AddOption("Randomize", "Inputs", "VisualAccidentalNoiseNodeRandomize", TTR("Returns seeded random noise in range.")));

	add_options.push_back(AddOption("Scalar", "Scalar", "VisualAccidentalNoiseNodeScalar", TTR("Provides common math constants (PI, E, 1.0, 0.0, 0.5, Sqrt2).")));
	add_options.push_back(AddOption("ScalarOp", "Scalar", "VisualAccidentalNoiseNodeScalarOp", TTR("Performs common math operations (arithmetic, power, max/min, gain/bias).")));
	add_options.push_back(AddOption("ScalarFunc", "Scalar", "VisualAccidentalNoiseNodeScalarFunc", TTR("Applies math functions (trigonometric, abs, sigmoid).")));

	add_options.push_back(AddOption("Translate", "Transform", "VisualAccidentalNoiseNodeTranslate", TTR("Translates/shifts noise function coordinates.")));
	add_options.push_back(AddOption("Scale", "Transform", "VisualAccidentalNoiseNodeScale", TTR("Scales/resizes noise function coordinates.")));
	add_options.push_back(AddOption("Rotate", "Transform", "VisualAccidentalNoiseNodeRotate", TTR("Rotates/shears noise function coordinates")));

	add_options.push_back(AddOption("Value", "Basis", "VisualAccidentalNoiseNodeValueBasis", TTR("Generates value noise function.")));
	add_options.push_back(AddOption("Gradient", "Basis", "VisualAccidentalNoiseNodeGradientBasis", TTR("Generates gradient noise function.")));
	add_options.push_back(AddOption("Simplex", "Basis", "VisualAccidentalNoiseNodeSimplexBasis", TTR("Generates simplex noise function.")));
	add_options.push_back(AddOption("Cellular", "Basis", "VisualAccidentalNoiseNodeCellularBasis", TTR("Generates cellular (Worley) noise function.")));

	add_options.push_back(AddOption("Mix", "Filter", "VisualAccidentalNoiseNodeMix", TTR("Linearly interpolates noise functions.")));
	add_options.push_back(AddOption("Select", "Filter", "VisualAccidentalNoiseNodeSelect", TTR("Chooses between one function or another based on the output value of a third control function.")));
	add_options.push_back(AddOption("Clamp", "Filter", "VisualAccidentalNoiseNodeClamp", TTR("Constrains a noise function to specified range of other functions.")));

	add_options.push_back(AddOption("Gradient", "Axis", "VisualAccidentalNoiseNodeGradient", TTR("Generates smooth gradient in any dimension.")));
	add_options.push_back(AddOption("Derivative", "Axis", "VisualAccidentalNoiseNodeDerivative", TTR("Returns a derivative of a noise function.")));

	add_options.push_back(AddOption("Hex", "Patterns", "VisualAccidentalNoiseNodeHex", TTR("Generates a hex tile or hex bump pattern.")));

	add_options.push_back(AddOption("Color", "Color", "VisualAccidentalNoiseNodeColor", TTR("Produces a constant color.")));
	add_options.push_back(AddOption("ColorCombine", "Color", "VisualAccidentalNoiseNodeColorCombine", TTR("Combines VisualAccidentalNoiseNodeColor nodes to produces color noise function.")));

	add_options.push_back(AddOption("Fractal", "Fractal", "VisualAccidentalNoiseNodeFractal", TTR("Generates generic FBM function.")));
	add_options.push_back(AddOption("FractalVariant", "Fractal", "VisualAccidentalNoiseNodeFractalVariant", TTR("Generates several specific types of fractal noise (FBM, ridged, billow).")));
	add_options.push_back(AddOption("Layer", "Fractal", "VisualAccidentalNoiseNodeFractalLayer", TTR("Generates fractal noise from basis functions.")));

	add_options.push_back(AddOption("Tiers", "Other", "VisualAccidentalNoiseNodeTiers", TTR("Produces a number of distinct height tiers.")));
	add_options.push_back(AddOption("Radial", "Other", "VisualAccidentalNoiseNodeRadial", TTR("Generates radial gradient function.")));
	add_options.push_back(AddOption("Step", "Other", "VisualAccidentalNoiseNodeStep", TTR("Pushes noise function values to either end based on a threshold.")));
	add_options.push_back(AddOption("CurveSection", "Other", "VisualAccidentalNoiseNodeCurveSection", TTR("Selects curve ranges.")));
	add_options.push_back(AddOption("ScaleOffset", "Other", "VisualAccidentalNoiseNodeScaleOffset", TTR("Applies a scaling and translation factor to the output of its source function, as v*scale+offset.")));
	add_options.push_back(AddOption("Sequence", "Other", "VisualAccidentalNoiseNodeSequence", TTR("Select or perform operations on a sequence of noise functions.")));

	add_options.push_back(AddOption("SetVar", "Misc", "VisualAccidentalNoiseNodeSetVar", TTR("Sets a variable noise function to be used by other nodes via GetVar (or via code).")));
	add_options.push_back(AddOption("GetVar", "Misc", "VisualAccidentalNoiseNodeGetVar", TTR("Retrieves a variable noise functions previously set with SetVar (or via code).")));
	add_options.push_back(AddOption("Reroute", "Misc", "VisualAccidentalNoiseNodeReroute", TTR("Rearranges node connections for convenience.")));
	add_options.push_back(AddOption("Expression", "Misc", "VisualAccidentalNoiseNodeExpression", TTR("Evaluate noise function from expression (experimental).")));

	_update_options_menu();

	error_panel = memnew(PanelContainer);
	add_child(error_panel);
	error_label = memnew(Label);
	error_panel->add_child(error_label);
	error_label->set_text("eh");
	error_panel->hide();

	Ref<VisualAccidentalNoiseNodePluginDefault> default_plugin;
	default_plugin.instance();
	add_plugin(default_plugin);

	property_editor = memnew(CustomPropertyEditor);
	add_child(property_editor);
	property_editor->connect("variant_changed", this, "_port_edited");

	open_file = memnew(EditorFileDialog);
	add_child(open_file);
	open_file->set_title(TTR("Open Component Node"));
	open_file->set_mode(EditorFileDialog::MODE_OPEN_FILE);
	open_file->connect("file_selected", this, "_file_opened");

	load_file_duplicated = false;

	undo_redo = EditorNode::get_singleton()->get_undo_redo();
}

///////////////////////////////////
// Creates custom editors for nodes
///////////////////////////////////

Control *VisualAccidentalNoiseNodePlugin::create_editor(const Ref<VisualAccidentalNoiseNode> &p_node) {

	if (get_script_instance()) {
		return get_script_instance()->call("create_editor", p_node);
	}
	return NULL;
}

void VisualAccidentalNoiseNodePlugin::_bind_methods() {

	BIND_VMETHOD(MethodInfo(Variant::OBJECT, "create_editor", PropertyInfo(Variant::OBJECT, "for_node", PROPERTY_HINT_RESOURCE_TYPE, "VisualAccidentalNoiseNode")));
}

class VisualAccidentalNoiseNodePluginDefaultEditor : public VBoxContainer {
	GDCLASS(VisualAccidentalNoiseNodePluginDefaultEditor, VBoxContainer);
public:
	void _property_changed(const String &prop, const Variant &p_value, const String &p_field, bool p_changing = false) {

		if (p_changing)
			return;

		UndoRedo *undo_redo = EditorNode::get_singleton()->get_undo_redo();

		updating = true;
		undo_redo->create_action("Edit Visual Accidental Noise Property: " + prop, UndoRedo::MERGE_ENDS);
		undo_redo->add_do_property(node.ptr(), prop, p_value);
		undo_redo->add_undo_property(node.ptr(), prop, node->get(prop));
		undo_redo->commit_action();
		updating = false;

		_refresh_request();
	}

	void _node_changed() {
		if (updating)
			return;
		for (int i = 0; i < properties.size(); i++) {
			properties[i]->update_property();
		}
	}

	void _refresh_request() {
		VisualAccidentalNoiseComponentEditor::get_singleton()->call_deferred("_update_graph");
	}

	bool updating;
	Ref<VisualAccidentalNoiseNode> node;
	Vector<EditorProperty *> properties;

	void setup(Vector<EditorProperty *> p_properties, const Vector<StringName> &p_names, Ref<VisualAccidentalNoiseNode> p_node) {
		updating = false;
		node = p_node;
		properties = p_properties;

		for (int i = 0; i < p_properties.size(); i++) {

			add_child(p_properties[i]);

			properties[i]->connect("property_changed", this, "_property_changed");
			properties[i]->set_object_and_property(node.ptr(), p_names[i]);
			properties[i]->update_property();
			properties[i]->set_name_split_ratio(0);
		}
		node->connect("changed", this, "_node_changed");
		node->connect("editor_refresh_request", this, "_refresh_request", varray(), CONNECT_DEFERRED);
	}

	static void _bind_methods() {
		ClassDB::bind_method("_property_changed", &VisualAccidentalNoiseNodePluginDefaultEditor::_property_changed, DEFVAL(String()), DEFVAL(false));
		ClassDB::bind_method("_node_changed", &VisualAccidentalNoiseNodePluginDefaultEditor::_node_changed);
		ClassDB::bind_method("_refresh_request", &VisualAccidentalNoiseNodePluginDefaultEditor::_refresh_request);
	}
};

Control *VisualAccidentalNoiseNodePluginDefault::create_editor(const Ref<VisualAccidentalNoiseNode> &p_node) {

	Vector<StringName> properties = p_node->get_editable_properties();
	if (properties.size() == 0) {
		return NULL;
	}

	List<PropertyInfo> props;
	p_node->get_property_list(&props);

	Vector<PropertyInfo> pinfo;

	for (List<PropertyInfo>::Element *E = props.front(); E; E = E->next()) {

		for (int i = 0; i < properties.size(); i++) {
			if (E->get().name == String(properties[i])) {
				pinfo.push_back(E->get());
			}
		}
	}

	if (pinfo.size() == 0) {
		return NULL;
	}

	properties.clear();

	Ref<VisualAccidentalNoiseNode> node = p_node;
	Vector<EditorProperty *> editors;

	for (int i = 0; i < pinfo.size(); i++) {

		EditorProperty *prop = EditorInspector::instantiate_property_editor(node.ptr(), pinfo[i].type, pinfo[i].name, pinfo[i].hint, pinfo[i].hint_string, pinfo[i].usage);
		if (!prop) {
			return NULL;
		}

		if (Object::cast_to<EditorPropertyFloat>(prop)) {
			prop->set_custom_minimum_size(Size2(100 * EDSCALE, 0));

		} else if (Object::cast_to<EditorPropertyEnum>(prop)) {
			prop->set_custom_minimum_size(Size2(100 * EDSCALE, 0));
			Object::cast_to<EditorPropertyEnum>(prop)->set_option_button_clip(false);
		}

		editors.push_back(prop);
		properties.push_back(pinfo[i].name);
	}

	VisualAccidentalNoiseNodePluginDefaultEditor *editor = memnew(VisualAccidentalNoiseNodePluginDefaultEditor);
	editor->setup(editors, properties, p_node);

	return editor;
}

///////////////////////////////////
// Port preview
///////////////////////////////////

void VisualAccidentalNoiseNodePortPreview::_noise_changed() {

	if (noise.is_null()) {
		return;
	}
	noise->generate();
}

void VisualAccidentalNoiseNodePortPreview::setup(const Ref<VisualAccidentalNoise> &p_noise, int p_node, int p_port) {

	noise = p_noise;
	noise->connect("changed", this, "_noise_changed");

	port = p_port;
	node = p_node;

	update();
}

Size2 VisualAccidentalNoiseNodePortPreview::get_minimum_size() const {

	Size2 prev_size = EDITOR_GET("editors/visual_accidental_noise/preview_size");
	Size2 min_size = prev_size * EDSCALE;

	if (noise.is_null()) {
		return min_size;
	}

	const Ref<VisualAccidentalNoiseNodeComponent> &component = VisualAccidentalNoiseComponentEditor::get_singleton()->get_component();
	ERR_FAIL_COND_V(component.is_null(), min_size);

	if (!component->has_node(node)) {
		return min_size;
	}

	const Ref<VisualAccidentalNoiseNode> &vanode = component->get_node(node);
	ERR_FAIL_COND_V(vanode.is_null(), min_size);

	Ref<VisualAccidentalNoiseNodeOutput> output = vanode;
	if (output.is_valid()) {
		Size2 output_prev_size = EDITOR_GET("editors/visual_accidental_noise/output_preview_size");
		min_size = output_prev_size * EDSCALE;
	}

	return min_size;
}

void VisualAccidentalNoiseNodePortPreview::_notification(int p_what) {

	if (noise.is_null()) {
		return;
	}

	const Ref<VisualAccidentalNoiseNodeComponent> &edited_comp = VisualAccidentalNoiseComponentEditor::get_singleton()->get_component();
	ERR_FAIL_COND(edited_comp.is_null());

	const Ref<VisualAccidentalNoiseNodeComponent> &comp = VisualAccidentalNoiseEditor::get_singleton()->get_noise()->get_component();
	ERR_FAIL_COND(comp.is_null());

	if (!edited_comp->has_node(node)) {
		return;
	}

	const Ref<VisualAccidentalNoiseNode> &vanode = edited_comp->get_node(node);
	ERR_FAIL_COND(vanode.is_null());

	real_t quality = EDITOR_GET("editors/visual_accidental_noise/preview_quality");

	if (p_what == NOTIFICATION_DRAW) {

		Index prev_function;
		Size2 tex_size = get_minimum_size();
		Size2 map_size = tex_size * quality;

		if ((map_size.x * map_size.y) <= 0.0) {
			ERR_FAIL_MSG("Could not generate noise preview, please configure preview quality in editor settings.");
		}

		Ref<VisualAccidentalNoiseNodeOutput> output = vanode;

		if (edited_comp == comp && output.is_valid()) {
			// Make preview from noise directly for this output node (possibly clamped)
			preview_tex = noise->get_texture(map_size.x, map_size.y);
			draw_texture_rect(preview_tex, Rect2(Vector2(), tex_size), false);

		} else {
			// Generate preview for at each node chain
			prev_function = noise->get_function();
			noise->set_function(vanode->get_output_port_value(port));

			preview_tex = noise->get_texture(map_size.x, map_size.y);
			draw_texture_rect(preview_tex, Rect2(Vector2(), tex_size), false);

			noise->set_function(prev_function);
		}
	}
}

void VisualAccidentalNoiseNodePortPreview::_bind_methods() {
	ClassDB::bind_method("_noise_changed", &VisualAccidentalNoiseNodePortPreview::_noise_changed);
}

VisualAccidentalNoiseNodePortPreview::VisualAccidentalNoiseNodePortPreview() {
}
