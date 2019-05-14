#include "visual_noise_component_editor_plugin.h"
#include "../visual_noise_nodes.h"
#include "visual_noise_editor_plugin.h"

#include "core/io/resource_loader.h"
#include "core/os/input.h"
#include "core/os/keyboard.h"
#include "core/project_settings.h"
#include "editor/editor_properties.h"
#include "scene/gui/menu_button.h"
#include "scene/gui/panel.h"
#include "scene/main/viewport.h"

///////////////////////////////////

bool VisualAccidentalNoiseComponentEditor::can_edit(const Ref<VisualAccidentalNoiseNodeComponent> &p_comp) {

	Ref<VisualAccidentalNoiseNodeComponent> comp = p_comp;

	return comp.is_valid();
}

void VisualAccidentalNoiseComponentEditor::edit(const Ref<VisualAccidentalNoiseNodeComponent> &p_component) {

	if (p_component.is_valid()) {

		component = p_component;
		_update_graph();

	} else {
		hide();
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

	String prev_category;

	add_node->get_popup()->clear();
	for (int i = 0; i < add_options.size(); i++) {
		if (prev_category != add_options[i].category) {
			add_node->get_popup()->add_separator(add_options[i].category);
		}
		add_node->get_popup()->add_item(add_options[i].name, i);
		prev_category = add_options[i].category;
	}

	add_component->get_popup()->clear();
	add_component->get_popup()->add_item(TTR("New Component"), MENU_CREATE_NEW);
	add_component->get_popup()->add_separator();
	add_component->get_popup()->add_item(TTR("Load Component..."), MENU_LOAD_FILE);
	add_component->get_popup()->add_item(TTR("Duplicate Component..."), MENU_DUPLICATE_FILE);
	add_component->get_popup()->add_separator();
	add_component->get_popup()->add_item(TTR("Make Component From Node(s)"), MENU_MAKE_FROM_NODES);
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

		// [TODO] BREAKS COMPAT (line 3)
		// if (EditorSettings::get_singleton()->get("interface/theme/use_graph_node_headers")) {
		// 	Ref<StyleBoxFlat> sb = node->get_stylebox("frame", "GraphNode");
		// 	Color c = sb->get_border_color();
		// 	Color mono_color = ((c.r + c.g + c.b) / 3) < 0.7 ? Color(1.0, 1.0, 1.0) : Color(0.0, 0.0, 0.0);
		// 	mono_color.a = 0.85;
		// 	c = mono_color;

		// 	node->add_color_override("title_color", c);
		// 	c.a = 0.7;
		// 	node->add_color_override("close_color", c);
		// }
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
	ERR_FAIL_COND(new_name == "" || new_name.find(".") != -1 || new_name.find("/") != -1)

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
	ERR_FAIL_COND(new_name == "" || new_name.find(".") != -1 || new_name.find("/") != -1)

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
		_add_component(MENU_LOAD_FILE_CONFIRM);
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

	Point2 position = (graph->get_scroll_ofs() + graph->get_size() * 0.5) / EDSCALE;

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

		case MENU_LOAD_FILE: {
			_popup_file_load();

		} break;

		case MENU_DUPLICATE_FILE: {
			load_file_duplicated = true;
			_popup_file_load();

		} break;

		case MENU_LOAD_FILE_CONFIRM: {

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
		EditorNode::get_singleton()->show_warning(TTR("Unable to connect, port may be in use or connection may be invalid."));
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

void VisualAccidentalNoiseComponentEditor::_input(const Ref<InputEvent> p_event) {

	if (!graph->has_focus())
		return;

	Ref<InputEventMouseButton> mb = p_event;

	if (mb.is_valid() && graph->has_point(mb->get_position())) {

		if (!mb->is_pressed())
			return;

		int mbi = mb->get_button_index();

		if (mbi == BUTTON_RIGHT) {

			add_component->get_popup()->set_position(get_viewport()->get_mouse_position());
			add_component->get_popup()->show_modal();

		} else if (mbi == BUTTON_LEFT) {

			Ref<VisualAccidentalNoise> noise = VisualAccidentalNoiseEditor::get_singleton()->get_noise();
			ERR_FAIL_COND(noise.is_null());

			Ref<VisualAccidentalNoiseNodeComponent> root_comp = noise->get_component();
			ERR_FAIL_COND(root_comp.is_null());

			if (component == root_comp) {
				EditorNode::get_singleton()->push_item(noise.ptr(), "", true);
			} else {
				EditorNode::get_singleton()->push_item(component.ptr(), "", true);
			}
		}
	}
}

void VisualAccidentalNoiseComponentEditor::_notification(int p_what) {

	if (p_what == NOTIFICATION_ENTER_TREE || p_what == NOTIFICATION_THEME_CHANGED) {

		error_panel->add_style_override("panel", get_stylebox("bg", "Tree"));
		error_label->add_color_override("font_color", get_color("error_color", "Editor"));

		if (p_what == NOTIFICATION_THEME_CHANGED && is_visible_in_tree()) {
			_update_graph();
		}
	}

	if (p_what == NOTIFICATION_PROCESS) {
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

void VisualAccidentalNoiseComponentEditor::_make_component_from_nodes(const Vector2 &p_ofs) {

	if (component.is_null()) {
		return;
	}
	List<int> nodes;

	for (int i = 0; i < graph->get_child_count(); i++) {

		GraphNode *gn = Object::cast_to<GraphNode>(graph->get_child(i));
		if (gn) {
			int id = String(gn->get_name()).to_int();

			Ref<VisualAccidentalNoiseNode> node = component->get_node(id);
			Ref<VisualAccidentalNoiseNodeOutput> output = node;
			if (output.is_valid()) { // can't duplicate output
				continue;
			}
			if (node.is_valid() && gn->is_selected()) {
				nodes.push_back(id);
			}
		}
	}
	if (nodes.empty())
		return;

	List<VisualAccidentalNoiseNodeComponent::Connection> conns;
	component->get_node_connections(&conns);

	if (nodes.size() == 1) {
		// Recursively fetch all the connected nodes to this one
		List<int> to_check;
		to_check.push_back(nodes[0]);

		while (!to_check.empty()) {

			int id = to_check.back()->get();
			to_check.pop_back();

			for (List<VisualAccidentalNoiseNodeComponent::Connection>::Element *E = conns.front(); E; E = E->next()) {
				if (id == E->get().to_node) {
					nodes.push_back(E->get().from_node);
					to_check.push_back(E->get().from_node);
				}
			}
		}
	}
	int base_id = component->get_valid_node_id();
	int id_from = base_id;
	Map<int, int> connection_remap;

	Ref<VisualAccidentalNoiseNodeComponent> comp;
	comp.instance();

	undo_redo->create_action("Make Component From Nodes");
	undo_redo->add_do_method(component.ptr(), "add_node", comp, p_ofs, id_from);
	undo_redo->add_undo_method(component.ptr(), "remove_node", id_from);
	id_from++;

	for (List<int>::Element *E = nodes.front(); E; E = E->next()) {

		connection_remap[E->get()] = id_from;
		Ref<VisualAccidentalNoiseNode> node = component->get_node(E->get());

		Ref<VisualAccidentalNoiseNode> dnode = node->duplicate();

		undo_redo->add_do_method(comp.ptr(), "add_node", dnode, component->get_node_position(E->get()), id_from);
		undo_redo->add_undo_method(comp.ptr(), "remove_node", id_from);

		id_from++;
	}
	// Connect duplicated nodes
	for (List<VisualAccidentalNoiseNodeComponent::Connection>::Element *E = conns.front(); E; E = E->next()) {
		if (connection_remap.has(E->get().from_node) && connection_remap.has(E->get().to_node)) {
			undo_redo->add_do_method(comp.ptr(), "connect_nodes", connection_remap[E->get().from_node], E->get().from_port, connection_remap[E->get().to_node], E->get().to_port);
		}
	}
	// Delete original nodes as they were moved to new component
	for (List<int>::Element *E = nodes.front(); E; E = E->next()) {

		Ref<VisualAccidentalNoiseNode> node = component->get_node(E->get());

		undo_redo->add_do_method(component.ptr(), "remove_node", E->get());
		undo_redo->add_undo_method(component.ptr(), "add_node", node, component->get_node_position(E->get()), E->get());

	}
	for (List<VisualAccidentalNoiseNodeComponent::Connection>::Element *F = conns.front(); F; F = F->next()) {
		undo_redo->add_undo_method(component.ptr(), "connect_nodes", F->get().from_node, F->get().from_port, F->get().to_node, F->get().to_port);
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
	ClassDB::bind_method("_add_node", &VisualAccidentalNoiseComponentEditor::_add_node);
	ClassDB::bind_method("_add_component", &VisualAccidentalNoiseComponentEditor::_add_component);
	ClassDB::bind_method("_node_dragged", &VisualAccidentalNoiseComponentEditor::_node_dragged);
	ClassDB::bind_method("_connection_request", &VisualAccidentalNoiseComponentEditor::_connection_request);
	ClassDB::bind_method("_disconnection_request", &VisualAccidentalNoiseComponentEditor::_disconnection_request);
	ClassDB::bind_method("_node_selected", &VisualAccidentalNoiseComponentEditor::_node_selected);
	ClassDB::bind_method("_open_in_editor", &VisualAccidentalNoiseComponentEditor::_open_in_editor);
	ClassDB::bind_method("_scroll_changed", &VisualAccidentalNoiseComponentEditor::_scroll_changed);
	ClassDB::bind_method("_delete_request", &VisualAccidentalNoiseComponentEditor::_delete_request);
	ClassDB::bind_method("_node_changed", &VisualAccidentalNoiseComponentEditor::_node_changed);
	ClassDB::bind_method("_edit_port_default_input", &VisualAccidentalNoiseComponentEditor::_edit_port_default_input);
	ClassDB::bind_method("_port_edited", &VisualAccidentalNoiseComponentEditor::_port_edited);
	ClassDB::bind_method("_connection_to_empty", &VisualAccidentalNoiseComponentEditor::_connection_to_empty);
	ClassDB::bind_method("_line_edit_focus_out", &VisualAccidentalNoiseComponentEditor::_line_edit_focus_out);
	ClassDB::bind_method("_line_edit_changed", &VisualAccidentalNoiseComponentEditor::_line_edit_changed);
	ClassDB::bind_method("_duplicate_nodes", &VisualAccidentalNoiseComponentEditor::_duplicate_nodes);
	ClassDB::bind_method("_preview_select_port", &VisualAccidentalNoiseComponentEditor::_preview_select_port);
	ClassDB::bind_method("_file_opened", &VisualAccidentalNoiseComponentEditor::_file_opened);
	ClassDB::bind_method("_input", &VisualAccidentalNoiseComponentEditor::_input);
}

VisualAccidentalNoiseComponentEditor *VisualAccidentalNoiseComponentEditor::singleton = NULL;

VisualAccidentalNoiseComponentEditor::VisualAccidentalNoiseComponentEditor() {

	singleton = this;
	updating = false;

	graph = memnew(GraphEdit);
	add_child(graph);

	graph->add_valid_right_disconnect_type(VisualAccidentalNoiseNode::PORT_TYPE_SCALAR);
	graph->add_valid_right_disconnect_type(VisualAccidentalNoiseNode::PORT_TYPE_INDEX);

	graph->set_v_size_flags(SIZE_EXPAND_FILL);

	graph->connect("connection_request", this, "_connection_request", varray(), CONNECT_DEFERRED);
	graph->connect("disconnection_request", this, "_disconnection_request", varray(), CONNECT_DEFERRED);
	graph->connect("node_selected", this, "_node_selected");
	graph->connect("scroll_offset_changed", this, "_scroll_changed");
	graph->connect("duplicate_nodes_request", this, "_duplicate_nodes");

	graph->add_valid_connection_type(VisualAccidentalNoiseNode::PORT_TYPE_SCALAR, VisualAccidentalNoiseNode::PORT_TYPE_SCALAR);
	graph->add_valid_connection_type(VisualAccidentalNoiseNode::PORT_TYPE_SCALAR, VisualAccidentalNoiseNode::PORT_TYPE_SCALAR);

	VSeparator *vs = memnew(VSeparator);
	graph->get_zoom_hbox()->add_child(vs);
	graph->get_zoom_hbox()->move_child(vs, 0);

	add_node = memnew(MenuButton);
	graph->get_zoom_hbox()->add_child(add_node);
	add_node->set_text(TTR("Add Node.."));
	graph->get_zoom_hbox()->move_child(add_node, 0);
	add_node->get_popup()->connect("id_pressed", this, "_add_node");

	add_component = memnew(MenuButton);
	graph->get_zoom_hbox()->add_child(add_component);
	add_component->set_text(TTR("Add Component.."));
	graph->get_zoom_hbox()->move_child(add_component, 1);
	add_component->get_popup()->connect("id_pressed", this, "_add_component");

	// Add node options
	add_options.push_back(AddOption("Input", "Inputs", "VisualAccidentalNoiseNodeInput"));
	add_options.push_back(AddOption("Seed", "Inputs", "VisualAccidentalNoiseNodeSeed"));
	add_options.push_back(AddOption("Seeder", "Inputs", "VisualAccidentalNoiseNodeSeeder"));
	add_options.push_back(AddOption("Randomize", "Inputs", "VisualAccidentalNoiseNodeRandomize"));

	add_options.push_back(AddOption("Scalar", "Scalar", "VisualAccidentalNoiseNodeScalar"));
	add_options.push_back(AddOption("ScalarOp", "Scalar", "VisualAccidentalNoiseNodeScalarOp"));
	add_options.push_back(AddOption("ScalarFunc", "Scalar", "VisualAccidentalNoiseNodeScalarFunc"));

	add_options.push_back(AddOption("Translate", "Transform", "VisualAccidentalNoiseNodeTranslate"));
	add_options.push_back(AddOption("Scale", "Transform", "VisualAccidentalNoiseNodeScale"));
	add_options.push_back(AddOption("Rotate", "Transform", "VisualAccidentalNoiseNodeRotate"));

	add_options.push_back(AddOption("Value", "Basis", "VisualAccidentalNoiseNodeValueBasis"));
	add_options.push_back(AddOption("Gradient", "Basis", "VisualAccidentalNoiseNodeGradientBasis"));
	add_options.push_back(AddOption("Simplex", "Basis", "VisualAccidentalNoiseNodeSimplexBasis"));
	add_options.push_back(AddOption("Cellular", "Basis", "VisualAccidentalNoiseNodeCellularBasis"));

	add_options.push_back(AddOption("Mix", "Filter", "VisualAccidentalNoiseNodeMix"));
	add_options.push_back(AddOption("Select", "Filter", "VisualAccidentalNoiseNodeSelect"));
	add_options.push_back(AddOption("Clamp", "Filter", "VisualAccidentalNoiseNodeClamp"));

	add_options.push_back(AddOption("Gradient", "Axis", "VisualAccidentalNoiseNodeGradient"));
	add_options.push_back(AddOption("Derivative", "Axis", "VisualAccidentalNoiseNodeDerivative"));

	add_options.push_back(AddOption("Hex", "Patterns", "VisualAccidentalNoiseNodeHex"));

	add_options.push_back(AddOption("Color", "Color", "VisualAccidentalNoiseNodeColor"));
	add_options.push_back(AddOption("ColorCombine", "Color", "VisualAccidentalNoiseNodeColorCombine"));

	add_options.push_back(AddOption("Fractal", "Fractal", "VisualAccidentalNoiseNodeFractal"));
	add_options.push_back(AddOption("FractalVariant", "Fractal", "VisualAccidentalNoiseNodeFractalVariant"));
	add_options.push_back(AddOption("Layer", "Fractal", "VisualAccidentalNoiseNodeFractalLayer"));

	add_options.push_back(AddOption("Tiers", "Other", "VisualAccidentalNoiseNodeTiers"));
	add_options.push_back(AddOption("Radial", "Other", "VisualAccidentalNoiseNodeRadial"));
	add_options.push_back(AddOption("Step", "Other", "VisualAccidentalNoiseNodeStep"));
	add_options.push_back(AddOption("CurveSection", "Other", "VisualAccidentalNoiseNodeCurveSection"));
	add_options.push_back(AddOption("ScaleOffset", "Other", "VisualAccidentalNoiseNodeScaleOffset"));
	add_options.push_back(AddOption("Sequence", "Other", "VisualAccidentalNoiseNodeSequence"));

	add_options.push_back(AddOption("SetVar", "Misc", "VisualAccidentalNoiseNodeSetVar"));
	add_options.push_back(AddOption("GetVar", "Misc", "VisualAccidentalNoiseNodeGetVar"));
	add_options.push_back(AddOption("Reroute", "Misc", "VisualAccidentalNoiseNodeReroute"));
	add_options.push_back(AddOption("Expression", "Misc", "VisualAccidentalNoiseNodeExpression"));

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
	GDCLASS(VisualAccidentalNoiseNodePluginDefaultEditor, VBoxContainer)
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
			ERR_EXPLAIN("Could not generate noise preview, please configure preview quality in editor settings.");
			ERR_FAIL();
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
