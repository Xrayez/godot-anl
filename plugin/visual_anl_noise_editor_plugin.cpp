#include "visual_anl_noise_editor_plugin.h"

#include "core/io/resource_loader.h"
#include "core/os/input.h"
#include "core/os/keyboard.h"
#include "core/project_settings.h"
#include "editor/editor_properties.h"
#include "scene/gui/menu_button.h"
#include "scene/gui/panel.h"
#include "scene/main/viewport.h"

Control *VisualAnlNoiseNodePlugin::create_editor(const Ref<VisualAnlNoiseNode> &p_node) {

	if (get_script_instance()) {
		return get_script_instance()->call("create_editor", p_node);
	}
	return NULL;
}

void VisualAnlNoiseNodePlugin::_bind_methods() {

	BIND_VMETHOD(MethodInfo(Variant::OBJECT, "create_editor", PropertyInfo(Variant::OBJECT, "for_node", PROPERTY_HINT_RESOURCE_TYPE, "VisualAnlNoiseNode")));
}

///////////////////

void VisualAnlNoiseEditor::edit(VisualAnlNoise *p_visual_anl_noise) {

	if (p_visual_anl_noise) {
		visual_anl_noise = Ref<VisualAnlNoise>(p_visual_anl_noise);
	} else {
		visual_anl_noise.unref();
	}

	if (visual_anl_noise.is_null()) {
		hide();
	} else {
		_update_graph();
	}
}

void VisualAnlNoiseEditor::add_plugin(const Ref<VisualAnlNoiseNodePlugin> &p_plugin) {

	if (plugins.find(p_plugin) != -1)
		return;

	plugins.push_back(p_plugin);
}

void VisualAnlNoiseEditor::remove_plugin(const Ref<VisualAnlNoiseNodePlugin> &p_plugin) {

	plugins.erase(p_plugin);
}

void VisualAnlNoiseEditor::add_custom_type(const String &p_name, const String &p_category, const Ref<Script> &p_script) {

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

void VisualAnlNoiseEditor::remove_custom_type(const Ref<Script> &p_script) {

	for (int i = 0; i < add_options.size(); i++) {
		if (add_options[i].script == p_script) {
			add_options.remove(i);
			return;
		}
	}

	_update_options_menu();
}

void VisualAnlNoiseEditor::_update_options_menu() {

	String prev_category;
	add_node->get_popup()->clear();
	for (int i = 0; i < add_options.size(); i++) {
		if (prev_category != add_options[i].category) {
			add_node->get_popup()->add_separator(add_options[i].category);
		}
		add_node->get_popup()->add_item(add_options[i].name, i);
		prev_category = add_options[i].category;
	}
}

Size2 VisualAnlNoiseEditor::get_minimum_size() const {

	return Size2(10, 200);
}

void VisualAnlNoiseEditor::_draw_color_over_button(Object *obj, Color p_color) {

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

void VisualAnlNoiseEditor::_update_graph() {

	if (updating)
		return;

	if (visual_anl_noise.is_null())
		return;

	graph->set_scroll_ofs(visual_anl_noise->get_component()->get_graph_offset() * EDSCALE);

	graph->clear_connections();
	//erase all nodes
	for (int i = 0; i < graph->get_child_count(); i++) {

		if (Object::cast_to<GraphNode>(graph->get_child(i))) {
			memdelete(graph->get_child(i));
			i--;
		}
	}

	static const Color type_color[3] = {
		Color::html("#61daf4"),
		Color::html("#d67dee"),
		Color::html("#f6a86e")
	};

	List<VisualAnlNoiseNodeComponent::Connection> connections;
	visual_anl_noise->get_component()->get_node_connections(&connections);

	Ref<StyleBoxEmpty> label_style = make_empty_stylebox(2, 1, 2, 1);

	Vector<int> nodes = visual_anl_noise->get_component()->get_node_list();

	for (int n_i = 0; n_i < nodes.size(); n_i++) {

		Vector2 position = visual_anl_noise->get_component()->get_node_position(nodes[n_i]);
		Ref<VisualAnlNoiseNode> vanode = visual_anl_noise->get_component()->get_node(nodes[n_i]);

		GraphNode *node = memnew(GraphNode);
		graph->add_child(node);

		/*if (!vanode->is_connected("changed", this, "_node_changed")) {
			vanode->connect("changed", this, "_node_changed", varray(vanode->get_instance_id()), CONNECT_DEFERRED);
		}*/

		node->set_offset(position);

		node->set_title(vanode->get_caption());
		node->set_name(itos(nodes[n_i]));

		if (nodes[n_i] >= 2) {
			node->set_show_close_button(true);
			node->connect("close_request", this, "_delete_request", varray(nodes[n_i]), CONNECT_DEFERRED);
		}

		node->connect("dragged", this, "_node_dragged", varray(nodes[n_i]));

		Control *custom_editor = NULL;
		int port_offset = 0;

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

			if (vanode->is_port_separator(i)) {
				node->add_child(memnew(HSeparator));
				port_offset++;
			}

			bool valid_left = i < vanode->get_input_port_count();
			VisualAnlNoiseNode::PortType port_left = VisualAnlNoiseNode::PORT_TYPE_SCALAR;
			bool port_left_used = false;
			String name_left;
			if (valid_left) {
				name_left = vanode->get_input_port_name(i);
				port_left = vanode->get_input_port_type(i);
				for (List<VisualAnlNoiseNodeComponent::Connection>::Element *E = connections.front(); E; E = E->next()) {
					if (E->get().to_node == nodes[n_i] && E->get().to_port == i) {
						port_left_used = true;
					}
				}
			}

			bool valid_right = i < vanode->get_output_port_count();
			VisualAnlNoiseNode::PortType port_right = VisualAnlNoiseNode::PORT_TYPE_SCALAR;
			String name_right;
			if (valid_right) {
				name_right = vanode->get_output_port_name(i);
				port_right = vanode->get_output_port_type(i);
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

					case Variant::COLOR: {
						button->set_custom_minimum_size(Size2(30, 0) * EDSCALE);
						button->connect("draw", this, "_draw_color_over_button", varray(button, default_value));
					} break;
					case Variant::INT:
					case Variant::REAL: {
						button->set_text(String::num(default_value, 4));
					} break;
					case Variant::VECTOR3: {
						Vector3 v = default_value;
						button->set_text(String::num(v.x, 3) + "," + String::num(v.y, 3) + "," + String::num(v.z, 3));
					} break;
					default: {}
				}
			}

			if (i == 0 && custom_editor) {

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

			node->add_child(hb);

			node->set_slot(i + port_offset, valid_left, port_left, type_color[port_left], valid_right, port_right, type_color[port_right]);
		}

		// if (vanode->get_output_port_for_preview() >= 0) {
		// 	VisualAnlNoiseNodePortPreview *port_preview = memnew(VisualAnlNoiseNodePortPreview);
		// 	port_preview->setup(visual_anl_noise, nodes[n_i], vanode->get_output_port_for_preview());
		// 	port_preview->set_h_size_flags(SIZE_SHRINK_CENTER);
		// 	node->add_child(port_preview);
		// }

		String error = vanode->get_warning();
		if (error != String()) {
			Label *error_label = memnew(Label);
			error_label->add_color_override("font_color", get_color("error_color", "Editor"));
			error_label->set_text(error);
			node->add_child(error_label);
		}
	}

	for (List<VisualAnlNoiseNodeComponent::Connection>::Element *E = connections.front(); E; E = E->next()) {

		int from = E->get().from_node;
		int from_idx = E->get().from_port;
		int to = E->get().to_node;
		int to_idx = E->get().to_port;

		graph->connect_node(itos(from), from_idx, itos(to), to_idx);
	}
}

void VisualAnlNoiseEditor::_preview_select_port(int p_node, int p_port) {

	Ref<VisualAnlNoiseNode> node = visual_anl_noise->get_component()->get_node(p_node);

	if (node.is_null()) {
		return;
	}

	if (node->get_output_port_for_preview() == p_port) {
		p_port = -1; //toggle it
	}
	undo_redo->create_action("Set Uniform Name");
	undo_redo->add_do_method(node.ptr(), "set_output_port_for_preview", p_port);
	undo_redo->add_undo_method(node.ptr(), "set_output_port_for_preview", node->get_output_port_for_preview());
	undo_redo->add_do_method(this, "_update_graph");
	undo_redo->add_undo_method(this, "_update_graph");
	undo_redo->commit_action();
}

void VisualAnlNoiseEditor::_line_edit_changed(const String &p_text, Object *line_edit, int p_node_id) {

}

void VisualAnlNoiseEditor::_line_edit_focus_out(Object *line_edit, int p_node_id) {

}

void VisualAnlNoiseEditor::_port_edited() {

	Variant value = property_editor->get_variant();
	Ref<VisualAnlNoiseNode> van = visual_anl_noise->get_component()->get_node(editing_node);
	ERR_FAIL_COND(!van.is_valid());

	undo_redo->create_action("Set Input Default Port");
	undo_redo->add_do_method(van.ptr(), "set_input_port_default_value", editing_port, value);
	undo_redo->add_undo_method(van.ptr(), "set_input_port_default_value", editing_port, van->get_input_port_default_value(editing_port));
	undo_redo->add_do_method(this, "_update_graph");
	undo_redo->add_undo_method(this, "_update_graph");
	undo_redo->commit_action();

	property_editor->hide();
}

void VisualAnlNoiseEditor::_edit_port_default_input(Object *p_button, int p_node, int p_port) {

	Ref<VisualAnlNoiseNode> van = visual_anl_noise->get_component()->get_node(p_node);

	Button *button = Object::cast_to<Button>(p_button);
	ERR_FAIL_COND(!button);
	Variant value = van->get_input_port_default_value(p_port);
	property_editor->set_global_position(button->get_global_position() + Vector2(0, button->get_size().height));
	property_editor->edit(NULL, "", value.get_type(), value, 0, "");
	property_editor->popup();
	editing_node = p_node;
	editing_port = p_port;
}

void VisualAnlNoiseEditor::_add_node(int p_idx) {

	ERR_FAIL_INDEX(p_idx, add_options.size());

	Ref<VisualAnlNoiseNode> vanode;

	if (add_options[p_idx].type != String()) {
		VisualAnlNoiseNode *van = Object::cast_to<VisualAnlNoiseNode>(ClassDB::instance(add_options[p_idx].type));
		ERR_FAIL_COND(!van);
		vanode = Ref<VisualAnlNoiseNode>(van);
	} else {
		ERR_FAIL_COND(add_options[p_idx].script.is_null());
		String base_type = add_options[p_idx].script->get_instance_base_type();
		VisualAnlNoiseNode *van = Object::cast_to<VisualAnlNoiseNode>(ClassDB::instance(base_type));
		ERR_FAIL_COND(!van);
		vanode = Ref<VisualAnlNoiseNode>(van);
		vanode->set_script(add_options[p_idx].script.get_ref_ptr());
	}

	Point2 position = (graph->get_scroll_ofs() + graph->get_size() * 0.5) / EDSCALE;

	int id_to_use = visual_anl_noise->get_component()->get_valid_node_id();

	undo_redo->create_action("Add Node to Visual AnlNoise");
	undo_redo->add_do_method(visual_anl_noise->get_component().ptr(), "add_node", vanode, position, id_to_use);
	undo_redo->add_undo_method(visual_anl_noise->get_component().ptr(), "remove_node", id_to_use);
	undo_redo->add_do_method(this, "_update_graph");
	undo_redo->add_undo_method(this, "_update_graph");
	undo_redo->commit_action();
}

void VisualAnlNoiseEditor::_node_dragged(const Vector2 &p_from, const Vector2 &p_to, int p_node) {

	updating = true;
	undo_redo->create_action("Node Moved");
	undo_redo->add_do_method(visual_anl_noise->get_component().ptr(), "set_node_position", p_node, p_to);
	undo_redo->add_undo_method(visual_anl_noise->get_component().ptr(), "set_node_position", p_node, p_from);
	undo_redo->add_do_method(this, "_update_graph");
	undo_redo->add_undo_method(this, "_update_graph");
	undo_redo->commit_action();
	updating = false;
}

void VisualAnlNoiseEditor::_connection_request(const String &p_from, int p_from_index, const String &p_to, int p_to_index) {

	int from = p_from.to_int();
	int to = p_to.to_int();

	if (!visual_anl_noise->get_component()->can_connect_nodes(from, p_from_index, to, p_to_index)) {
		EditorNode::get_singleton()->show_warning(TTR("Unable to connect, port may be in use or connection may be invalid."));
		return;
	}

	undo_redo->create_action("Nodes Connected");

	List<VisualAnlNoiseNodeComponent::Connection> conns;
	visual_anl_noise->get_component()->get_node_connections(&conns);

	for (List<VisualAnlNoiseNodeComponent::Connection>::Element *E = conns.front(); E; E = E->next()) {
		if (E->get().to_node == to && E->get().to_port == p_to_index) {
			undo_redo->add_do_method(visual_anl_noise->get_component().ptr(), "disconnect_nodes", E->get().from_node, E->get().from_port, E->get().to_node, E->get().to_port);
			undo_redo->add_undo_method(visual_anl_noise->get_component().ptr(), "connect_nodes", E->get().from_node, E->get().from_port, E->get().to_node, E->get().to_port);
		}
	}

	undo_redo->add_do_method(visual_anl_noise->get_component().ptr(), "connect_nodes", from, p_from_index, to, p_to_index);
	undo_redo->add_undo_method(visual_anl_noise->get_component().ptr(), "disconnect_nodes", from, p_from_index, to, p_to_index);
	undo_redo->add_do_method(this, "_update_graph");
	undo_redo->add_undo_method(this, "_update_graph");
	undo_redo->commit_action();
}

void VisualAnlNoiseEditor::_disconnection_request(const String &p_from, int p_from_index, const String &p_to, int p_to_index) {

	graph->disconnect_node(p_from, p_from_index, p_to, p_to_index);

	int from = p_from.to_int();
	int to = p_to.to_int();

	//updating = true; seems graph edit can handle this, no need to protect
	undo_redo->create_action("Nodes Disconnected");
	undo_redo->add_do_method(visual_anl_noise->get_component().ptr(), "disconnect_nodes", from, p_from_index, to, p_to_index);
	undo_redo->add_undo_method(visual_anl_noise->get_component().ptr(), "connect_nodes", from, p_from_index, to, p_to_index);
	undo_redo->add_do_method(this, "_update_graph");
	undo_redo->add_undo_method(this, "_update_graph");
	undo_redo->commit_action();
	//updating = false;
}

void VisualAnlNoiseEditor::_connection_to_empty(const String &p_from, int p_from_slot, const Vector2 &p_release_position) {
}

void VisualAnlNoiseEditor::_delete_request(int which) {

	undo_redo->create_action("Delete Node");
	undo_redo->add_do_method(visual_anl_noise->get_component().ptr(), "remove_node", which);
	undo_redo->add_undo_method(visual_anl_noise->get_component().ptr(), "add_node", visual_anl_noise->get_component()->get_node(which), visual_anl_noise->get_component()->get_node_position(which), which);

	List<VisualAnlNoiseNodeComponent::Connection> conns;
	visual_anl_noise->get_component()->get_node_connections(&conns);

	for (List<VisualAnlNoiseNodeComponent::Connection>::Element *E = conns.front(); E; E = E->next()) {
		if (E->get().from_node == which || E->get().to_node == which) {
			undo_redo->add_undo_method(visual_anl_noise->get_component().ptr(), "connect_nodes", E->get().from_node, E->get().from_port, E->get().to_node, E->get().to_port);
		}
	}

	undo_redo->add_do_method(this, "_update_graph");
	undo_redo->add_undo_method(this, "_update_graph");
	undo_redo->commit_action();
}

void VisualAnlNoiseEditor::_node_selected(Object *p_node) {

	GraphNode *gn = Object::cast_to<GraphNode>(p_node);
	ERR_FAIL_COND(!gn);

	int id = String(gn->get_name()).to_int();

	Ref<VisualAnlNoiseNode> vanode = visual_anl_noise->get_component()->get_node(id);
	ERR_FAIL_COND(!vanode.is_valid());

	//do not rely on this, makes editor more complex
	//EditorNode::get_singleton()->push_item(vanode.ptr(), "", true);
}

void VisualAnlNoiseEditor::_input(const Ref<InputEvent> p_event) {
	if (graph->has_focus()) {
		Ref<InputEventMouseButton> mb = p_event;

		if (mb.is_valid() && mb->is_pressed() && mb->get_button_index() == BUTTON_RIGHT) {
			// add_node->get_popup()->set_position(get_viewport()->get_mouse_position());
			add_node->get_popup()->show_modal();
		}
	}
}

void VisualAnlNoiseEditor::_notification(int p_what) {

	if (p_what == NOTIFICATION_ENTER_TREE || p_what == NOTIFICATION_THEME_CHANGED) {

		error_panel->add_style_override("panel", get_stylebox("bg", "Tree"));
		error_label->add_color_override("font_color", get_color("error_color", "Editor"));
	}

	if (p_what == NOTIFICATION_PROCESS) {
	}
}

void VisualAnlNoiseEditor::_scroll_changed(const Vector2 &p_scroll) {
	if (updating)
		return;
	updating = true;
	visual_anl_noise->get_component()->set_graph_offset(p_scroll / EDSCALE);
	updating = false;
}

void VisualAnlNoiseEditor::_node_changed(int p_id) {
	if (updating)
		return;

	if (is_visible_in_tree()) {
		_update_graph();
	}
}

void VisualAnlNoiseEditor::_duplicate_nodes() {

	List<int> nodes;

	for (int i = 0; i < graph->get_child_count(); i++) {

		if (Object::cast_to<GraphNode>(graph->get_child(i))) {
			int id = String(graph->get_child(i)->get_name()).to_int();
			Ref<VisualAnlNoiseNode> node = visual_anl_noise->get_component()->get_node(id);
			Ref<VisualAnlNoiseNodeOutput> output = node;
			if (output.is_valid()) //can't duplicate output
				continue;
			if (node.is_valid()) {
				nodes.push_back(id);
			}
		}
	}

	if (nodes.empty())
		return;

	undo_redo->create_action("Duplicate Nodes");

	int base_id = visual_anl_noise->get_component()->get_valid_node_id();
	int id_from = base_id;
	Map<int, int> connection_remap;

	for (List<int>::Element *E = nodes.front(); E; E = E->next()) {

		connection_remap[E->get()] = id_from;
		Ref<VisualAnlNoiseNode> node = visual_anl_noise->get_component()->get_node(E->get());

		Ref<VisualAnlNoiseNode> dupli = node->duplicate();

		undo_redo->add_do_method(visual_anl_noise->get_component().ptr(), "add_node", dupli, visual_anl_noise->get_component()->get_node_position(E->get()) + Vector2(10, 10) * EDSCALE, id_from);
		undo_redo->add_undo_method(visual_anl_noise->get_component().ptr(), "remove_node", id_from);

		id_from++;
	}

	List<VisualAnlNoiseNodeComponent::Connection> conns;
	visual_anl_noise->get_component()->get_node_connections(&conns);

	for (List<VisualAnlNoiseNodeComponent::Connection>::Element *E = conns.front(); E; E = E->next()) {
		if (connection_remap.has(E->get().from_node) && connection_remap.has(E->get().to_node)) {
			undo_redo->add_do_method(visual_anl_noise->get_component().ptr(), "connect_nodes", connection_remap[E->get().from_node], E->get().from_port, connection_remap[E->get().to_node], E->get().to_port);
		}
	}

	undo_redo->add_do_method(this, "_update_graph");
	undo_redo->add_undo_method(this, "_update_graph");
	undo_redo->commit_action();

	//reselect
	for (int i = 0; i < graph->get_child_count(); i++) {

		if (Object::cast_to<GraphNode>(graph->get_child(i))) {
			int id = String(graph->get_child(i)->get_name()).to_int();
			if (nodes.find(id)) {
				Object::cast_to<GraphNode>(graph->get_child(i))->set_selected(true);
			} else {
				Object::cast_to<GraphNode>(graph->get_child(i))->set_selected(false);
			}
		}
	}
}

// void VisualAnlNoiseEditor::_input_select_item(Ref<VisualAnlNoiseNodeInput> input, String name) {

// 	String prev_name = input->get_input_name();

// 	if (name == prev_name)
// 		return;

// 	UndoRedo *undo_redo = EditorNode::get_singleton()->get_undo_redo();
// 	undo_redo->create_action("Visual AnlNoise Input Type Changed");

// 	undo_redo->add_do_method(input.ptr(), "set_input_name", name);
// 	undo_redo->add_undo_method(input.ptr(), "set_input_name", prev_name);

// 	undo_redo->add_do_method(VisualAnlNoiseEditor::get_singleton(), "_update_graph");
// 	undo_redo->add_undo_method(VisualAnlNoiseEditor::get_singleton(), "_update_graph");

// 	undo_redo->commit_action();
// }

void VisualAnlNoiseEditor::_bind_methods() {

	ClassDB::bind_method("_update_graph", &VisualAnlNoiseEditor::_update_graph);
	ClassDB::bind_method("_add_node", &VisualAnlNoiseEditor::_add_node);
	ClassDB::bind_method("_node_dragged", &VisualAnlNoiseEditor::_node_dragged);
	ClassDB::bind_method("_connection_request", &VisualAnlNoiseEditor::_connection_request);
	ClassDB::bind_method("_disconnection_request", &VisualAnlNoiseEditor::_disconnection_request);
	ClassDB::bind_method("_node_selected", &VisualAnlNoiseEditor::_node_selected);
	ClassDB::bind_method("_scroll_changed", &VisualAnlNoiseEditor::_scroll_changed);
	ClassDB::bind_method("_delete_request", &VisualAnlNoiseEditor::_delete_request);
	ClassDB::bind_method("_node_changed", &VisualAnlNoiseEditor::_node_changed);
	ClassDB::bind_method("_edit_port_default_input", &VisualAnlNoiseEditor::_edit_port_default_input);
	ClassDB::bind_method("_port_edited", &VisualAnlNoiseEditor::_port_edited);
	ClassDB::bind_method("_connection_to_empty", &VisualAnlNoiseEditor::_connection_to_empty);
	ClassDB::bind_method("_line_edit_focus_out", &VisualAnlNoiseEditor::_line_edit_focus_out);
	ClassDB::bind_method("_line_edit_changed", &VisualAnlNoiseEditor::_line_edit_changed);
	ClassDB::bind_method("_duplicate_nodes", &VisualAnlNoiseEditor::_duplicate_nodes);
	// ClassDB::bind_method("_input_select_item", &VisualAnlNoiseEditor::_input_select_item);
	ClassDB::bind_method("_preview_select_port", &VisualAnlNoiseEditor::_preview_select_port);
	ClassDB::bind_method("_input", &VisualAnlNoiseEditor::_input);
}

VisualAnlNoiseEditor *VisualAnlNoiseEditor::singleton = NULL;

VisualAnlNoiseEditor::VisualAnlNoiseEditor() {

	singleton = this;
	updating = false;

	graph = memnew(GraphEdit);
	add_child(graph);

	graph->add_valid_right_disconnect_type(VisualAnlNoiseNode::PORT_TYPE_SCALAR);
	graph->add_valid_right_disconnect_type(VisualAnlNoiseNode::PORT_TYPE_INDEX);

	graph->set_v_size_flags(SIZE_EXPAND_FILL);

	graph->connect("connection_request", this, "_connection_request", varray(), CONNECT_DEFERRED);
	graph->connect("disconnection_request", this, "_disconnection_request", varray(), CONNECT_DEFERRED);
	graph->connect("node_selected", this, "_node_selected");
	graph->connect("scroll_offset_changed", this, "_scroll_changed");
	graph->connect("duplicate_nodes_request", this, "_duplicate_nodes");

	graph->add_valid_connection_type(VisualAnlNoiseNode::PORT_TYPE_SCALAR, VisualAnlNoiseNode::PORT_TYPE_SCALAR);
	graph->add_valid_connection_type(VisualAnlNoiseNode::PORT_TYPE_SCALAR, VisualAnlNoiseNode::PORT_TYPE_SCALAR);

	VSeparator *vs = memnew(VSeparator);
	graph->get_zoom_hbox()->add_child(vs);
	graph->get_zoom_hbox()->move_child(vs, 0);

	add_node = memnew(MenuButton);
	graph->get_zoom_hbox()->add_child(add_node);
	add_node->set_text(TTR("Add Node.."));
	graph->get_zoom_hbox()->move_child(add_node, 0);
	add_node->get_popup()->connect("id_pressed", this, "_add_node");

	add_options.push_back(AddOption("Constant", "Functions", "VisualAnlNoiseNodeConstant"));
	add_options.push_back(AddOption("Input", "Inputs", "VisualAnlNoiseNodeInput"));

	_update_options_menu();

	error_panel = memnew(PanelContainer);
	add_child(error_panel);
	error_label = memnew(Label);
	error_panel->add_child(error_label);
	error_label->set_text("eh");
	error_panel->hide();

	undo_redo = EditorNode::get_singleton()->get_undo_redo();

	Ref<VisualAnlNoiseNodePluginDefault> default_plugin;
	default_plugin.instance();
	add_plugin(default_plugin);

	property_editor = memnew(CustomPropertyEditor);
	add_child(property_editor);

	property_editor->connect("variant_changed", this, "_port_edited");
}

void VisualAnlNoiseEditorPlugin::edit(Object *p_object) {

	visual_anl_noise_editor->edit(Object::cast_to<VisualAnlNoise>(p_object));
}

bool VisualAnlNoiseEditorPlugin::handles(Object *p_object) const {

	return p_object->is_class("VisualAnlNoise");
}

void VisualAnlNoiseEditorPlugin::make_visible(bool p_visible) {

	if (p_visible) {
		//editor->hide_animation_player_editors();
		//editor->animation_panel_make_visible(true);
		button->show();
		editor->make_bottom_panel_item_visible(visual_anl_noise_editor);
		visual_anl_noise_editor->set_process_input(true);
		//visual_anl_noise_editor->set_process(true);
	} else {

		if (visual_anl_noise_editor->is_visible_in_tree())
			editor->hide_bottom_panel();
		button->hide();
		visual_anl_noise_editor->set_process_input(false);
		//visual_anl_noise_editor->set_process(false);
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

////////////////

class VisualAnlNoiseNodePluginInputEditor : public OptionButton {
	GDCLASS(VisualAnlNoiseNodePluginInputEditor, OptionButton)

	Ref<VisualAnlNoiseNodeInput> input;

protected:
	static void _bind_methods() {
		ClassDB::bind_method("_item_selected", &VisualAnlNoiseNodePluginInputEditor::_item_selected);
	}

public:
	void _notification(int p_what) {
		if (p_what == NOTIFICATION_READY) {
			connect("item_selected", this, "_item_selected");
		}
	}

	void _item_selected(int p_item) {
		VisualAnlNoiseEditor::get_singleton()->call_deferred("_input_select_item", input, get_item_text(p_item));
	}

	void setup(const Ref<VisualAnlNoiseNodeInput> &p_input) {
		input = p_input;
		Ref<Texture> type_icon[3] = {
			EditorNode::get_singleton()->get_gui_base()->get_icon("float", "EditorIcons"),
			EditorNode::get_singleton()->get_gui_base()->get_icon("Vector3", "EditorIcons"),
			EditorNode::get_singleton()->get_gui_base()->get_icon("Transform", "EditorIcons"),
		};

		add_item("[None]");
		int to_select = -1;
		for (int i = 0; i < input->get_input_index_count(); i++) {
			if (input->get_input_name() == input->get_input_index_name(i)) {
				to_select = i + 1;
			}
			add_icon_item(type_icon[input->get_input_index_type(i)], input->get_input_index_name(i));
		}

		if (to_select >= 0) {
			select(to_select);
		}
	}
};

class VisualAnlNoiseNodePluginDefaultEditor : public VBoxContainer {
	GDCLASS(VisualAnlNoiseNodePluginDefaultEditor, VBoxContainer)
public:
	void _property_changed(const String &prop, const Variant &p_value, bool p_changing = false) {

		if (p_changing)
			return;

		UndoRedo *undo_redo = EditorNode::get_singleton()->get_undo_redo();

		updating = true;
		undo_redo->create_action("Edit Visual Property: " + prop, UndoRedo::MERGE_ENDS);
		undo_redo->add_do_property(node.ptr(), prop, p_value);
		undo_redo->add_undo_property(node.ptr(), prop, node->get(prop));
		undo_redo->commit_action();
		updating = false;
	}

	void _node_changed() {
		if (updating)
			return;
		for (int i = 0; i < properties.size(); i++) {
			properties[i]->update_property();
		}
	}

	void _refresh_request() {
		VisualAnlNoiseEditor::get_singleton()->call_deferred("_update_graph");
	}

	bool updating;
	Ref<VisualAnlNoiseNode> node;
	Vector<EditorProperty *> properties;

	void setup(Vector<EditorProperty *> p_properties, const Vector<StringName> &p_names, Ref<VisualAnlNoiseNode> p_node) {
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
		ClassDB::bind_method("_property_changed", &VisualAnlNoiseNodePluginDefaultEditor::_property_changed, DEFVAL(false));
		ClassDB::bind_method("_node_changed", &VisualAnlNoiseNodePluginDefaultEditor::_node_changed);
		ClassDB::bind_method("_refresh_request", &VisualAnlNoiseNodePluginDefaultEditor::_refresh_request);
	}
};

Control *VisualAnlNoiseNodePluginDefault::create_editor(const Ref<VisualAnlNoiseNode> &p_node) {

	if (p_node->is_class("VisualAnlNoiseNodeInput")) {
		//create input
		VisualAnlNoiseNodePluginInputEditor *input_editor = memnew(VisualAnlNoiseNodePluginInputEditor);
		input_editor->setup(p_node);
		return input_editor;
	}

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

	if (pinfo.size() == 0)
		return NULL;

	properties.clear();

	Ref<VisualAnlNoiseNode> node = p_node;
	Vector<EditorProperty *> editors;

	for (int i = 0; i < pinfo.size(); i++) {

		EditorProperty *prop = EditorInspector::instantiate_property_editor(node.ptr(), pinfo[i].type, pinfo[i].name, pinfo[i].hint, pinfo[i].hint_string, pinfo[i].usage);
		if (!prop)
			return NULL;

		if (Object::cast_to<EditorPropertyResource>(prop)) {
			Object::cast_to<EditorPropertyResource>(prop)->set_use_sub_inspector(false);
			prop->set_custom_minimum_size(Size2(100 * EDSCALE, 0));
		} else if (Object::cast_to<EditorPropertyTransform>(prop)) {
			prop->set_custom_minimum_size(Size2(250 * EDSCALE, 0));
		} else if (Object::cast_to<EditorPropertyFloat>(prop) || Object::cast_to<EditorPropertyVector3>(prop)) {
			prop->set_custom_minimum_size(Size2(100 * EDSCALE, 0));
		} else if (Object::cast_to<EditorPropertyEnum>(prop)) {
			prop->set_custom_minimum_size(Size2(100 * EDSCALE, 0));
			Object::cast_to<EditorPropertyEnum>(prop)->set_option_button_clip(false);
		}

		editors.push_back(prop);
		properties.push_back(pinfo[i].name);
	}

	VisualAnlNoiseNodePluginDefaultEditor *editor = memnew(VisualAnlNoiseNodePluginDefaultEditor);
	editor->setup(editors, properties, p_node);

	return editor;
}

// void EditorPropertyAnlNoiseMode::_option_selected(int p_which) {

// 	//will not use this, instead will do all the logic setting manually
// 	//emit_signal("property_changed", get_edited_property(), p_which);

// 	Ref<VisualAnlNoise> visual_anl_noise(Object::cast_to<VisualAnlNoise>(get_edited_object()));

// 	if (visual_anl_noise->get_component()->get_mode() == p_which)
// 		return;

// 	UndoRedo *undo_redo = EditorNode::get_singleton()->get_undo_redo();
// 	undo_redo->create_action("Visual AnlNoise Mode Changed");
// 	//do is easy
// 	undo_redo->add_do_method(visual_anl_noise->get_component().ptr(), "set_mode", p_which);
// 	undo_redo->add_undo_method(visual_anl_noise->get_component().ptr(), "set_mode", visual_anl_noise->get_component()->get_mode());
// 	//now undo is hell

// 	//1. restore connections to output
// 	for (int i = 0; i < VisualAnlNoise::TYPE_MAX; i++) {

// 		VisualAnlNoise::Type type = VisualAnlNoise::Type(i);
// 		List<VisualAnlNoiseNodeComponent::Connection> conns;
// 		visual_anl_noise->get_component()->get_node_connections(&conns);
// 		for (List<VisualAnlNoiseNodeComponent::Connection>::Element *E = conns.front(); E; E = E->next()) {
// 			if (E->get().to_node == VisualAnlNoise::NODE_ID_OUTPUT) {
// 				undo_redo->add_undo_method(visual_anl_noise->get_component().ptr(), "connect_nodes", E->get().from_node, E->get().from_port, E->get().to_node, E->get().to_port);
// 			}
// 		}
// 	}
// 	//2. restore input indices
// 	for (int i = 0; i < VisualAnlNoise::TYPE_MAX; i++) {

// 		VisualAnlNoise::Type type = VisualAnlNoise::Type(i);
// 		Vector<int> nodes = visual_anl_noise->get_component()->get_node_list(type);
// 		for (int i = 0; i < nodes.size(); i++) {
// 			Ref<VisualAnlNoiseNodeInput> input = visual_anl_noise->get_component()->get_node(nodes[i]);
// 			if (!input.is_valid()) {
// 				continue;
// 			}

// 			undo_redo->add_undo_method(input.ptr(), "set_input_name", input->get_input_name());
// 		}
// 	}

// 	//3. restore enums and flags
// 	List<PropertyInfo> props;
// 	visual_anl_noise->get_component()->get_property_list(&props);

// 	for (List<PropertyInfo>::Element *E = props.front(); E; E = E->next()) {

// 		if (E->get().name.begins_with("flags/") || E->get().name.begins_with("modes/")) {
// 			undo_redo->add_undo_property(visual_anl_noise->get_component().ptr(), E->get().name, visual_anl_noise->get_component()->get(E->get().name));
// 		}
// 	}

// 	//update graph
// 	undo_redo->add_do_method(VisualAnlNoiseEditor::get_singleton(), "_update_graph");
// 	undo_redo->add_undo_method(VisualAnlNoiseEditor::get_singleton(), "_update_graph");

// 	undo_redo->commit_action();
// }

// void EditorPropertyAnlNoiseMode::update_property() {

// 	int which = get_edited_object()->get(get_edited_property());
// 	options->select(which);
// }

// void EditorPropertyAnlNoiseMode::setup(const Vector<String> &p_options) {
// 	for (int i = 0; i < p_options.size(); i++) {
// 		options->add_item(p_options[i], i);
// 	}
// }

// void EditorPropertyAnlNoiseMode::set_option_button_clip(bool p_enable) {
// 	options->set_clip_text(p_enable);
// }

// void EditorPropertyAnlNoiseMode::_bind_methods() {

// 	ClassDB::bind_method(D_METHOD("_option_selected"), &EditorPropertyAnlNoiseMode::_option_selected);
// }

// EditorPropertyAnlNoiseMode::EditorPropertyAnlNoiseMode() {
// 	options = memnew(OptionButton);
// 	options->set_clip_text(true);
// 	add_child(options);
// 	add_focusable(options);
// 	options->connect("item_selected", this, "_option_selected");
// }

// bool EditorInspectorAnlNoiseModePlugin::can_handle(Object *p_object) {
// 	return true; //can handle everything
// }

// void EditorInspectorAnlNoiseModePlugin::parse_begin(Object *p_object) {
// 	//do none
// }

// bool EditorInspectorAnlNoiseModePlugin::parse_property(Object *p_object, Variant::Type p_type, const String &p_path, PropertyHint p_hint, const String &p_hint_text, int p_usage) {

// 	if (p_path == "mode" && p_object->is_class("VisualAnlNoise") && p_type == Variant::INT) {

// 		EditorPropertyAnlNoiseMode *editor = memnew(EditorPropertyAnlNoiseMode);
// 		Vector<String> options = p_hint_text.split(",");
// 		editor->setup(options);
// 		add_property_editor(p_path, editor);

// 		return true;
// 	}

// 	return false; //can be overridden, although it will most likely be last anyway
// }

// void EditorInspectorAnlNoiseModePlugin::parse_end() {
// 	//do none
// }
//////////////////////////////////

// void VisualAnlNoiseNodePortPreview::_noise_changed() {

// }

// void VisualAnlNoiseNodePortPreview::setup(const Ref<VisualAnlNoise> &p_anl_noise, VisualAnlNoise::Type p_type, int p_node, int p_port) {

// 	anl_noise = p_anl_noise;
// 	anl_noise->connect("changed", this, "_anl_noise_changed");
// 	type = p_type;
// 	port = p_port;
// 	node = p_node;
// 	update();
// 	_anl_noise_changed();
// }

// Size2 VisualAnlNoiseNodePortPreview::get_minimum_size() const {
// 	return Size2(100, 100) * EDSCALE;
// }

// void VisualAnlNoiseNodePortPreview::_notification(int p_what) {
// 	if (p_what == NOTIFICATION_DRAW) {
// 		Vector<Vector2> points;
// 		Vector<Vector2> uvs;
// 		Vector<Color> colors;
// 		points.push_back(Vector2());
// 		uvs.push_back(Vector2(0, 0));
// 		colors.push_back(Color(1, 1, 1, 1));
// 		points.push_back(Vector2(get_size().width, 0));
// 		uvs.push_back(Vector2(1, 0));
// 		colors.push_back(Color(1, 1, 1, 1));
// 		points.push_back(get_size());
// 		uvs.push_back(Vector2(1, 1));
// 		colors.push_back(Color(1, 1, 1, 1));
// 		points.push_back(Vector2(0, get_size().height));
// 		uvs.push_back(Vector2(0, 1));
// 		colors.push_back(Color(1, 1, 1, 1));

// 		draw_primitive(points, colors, uvs);
// 	}
// }

// void VisualAnlNoiseNodePortPreview::_bind_methods() {
// 	ClassDB::bind_method("_noise_changed", &VisualAnlNoiseNodePortPreview::_noise_changed);
// }

// VisualAnlNoiseNodePortPreview::VisualAnlNoiseNodePortPreview() {
// }
