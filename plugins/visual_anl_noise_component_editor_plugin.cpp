#include "visual_anl_noise_editor_plugin.h"
#include "visual_anl_noise_component_editor_plugin.h"

#include "core/io/resource_loader.h"
#include "core/os/input.h"
#include "core/os/keyboard.h"
#include "core/project_settings.h"
#include "editor/editor_properties.h"
#include "scene/gui/menu_button.h"
#include "scene/gui/panel.h"
#include "scene/main/viewport.h"

///////////////////////////////////

bool VisualAnlNoiseNodeComponentEditor::can_edit(const Ref<VisualAnlNoiseNodeComponent> &p_comp) {

	Ref<VisualAnlNoiseNodeComponent> comp = p_comp;

	return comp.is_valid();
}

void VisualAnlNoiseNodeComponentEditor::edit(const Ref<VisualAnlNoiseNodeComponent> &p_component) {

	if (p_component.is_valid()) {

		component = p_component;
		_update_graph();

	} else {
		hide();
	}
}

void VisualAnlNoiseNodeComponentEditor::add_plugin(const Ref<VisualAnlNoiseNodePlugin> &p_plugin) {

	if (plugins.find(p_plugin) != -1)
		return;

	plugins.push_back(p_plugin);
}

void VisualAnlNoiseNodeComponentEditor::remove_plugin(const Ref<VisualAnlNoiseNodePlugin> &p_plugin) {

	plugins.erase(p_plugin);
}

void VisualAnlNoiseNodeComponentEditor::add_custom_type(const String &p_name, const String &p_category, const Ref<Script> &p_script) {

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

void VisualAnlNoiseNodeComponentEditor::remove_custom_type(const Ref<Script> &p_script) {

	for (int i = 0; i < add_options.size(); i++) {
		if (add_options[i].script == p_script) {
			add_options.remove(i);
			return;
		}
	}

	_update_options_menu();
}

void VisualAnlNoiseNodeComponentEditor::_update_options_menu() {

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

Size2 VisualAnlNoiseNodeComponentEditor::get_minimum_size() const {

	return Size2(10, 200);
}

void VisualAnlNoiseNodeComponentEditor::_draw_color_over_button(Object *obj, Color p_color) {

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

void VisualAnlNoiseNodeComponentEditor::_update_graph() {

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

	static const Color type_color[3] = {
		Color::html("#61daf4"),
		Color::html("#d67dee"),
		Color::html("#f6a86e")
	};

	List<VisualAnlNoiseNodeComponent::Connection> connections;
	component->get_node_connections(&connections);

	Ref<StyleBoxEmpty> label_style = make_empty_stylebox(2, 1, 2, 1);

	Vector<int> nodes = component->get_node_list();

	for (int n_i = 0; n_i < nodes.size(); n_i++) {

		Vector2 position = component->get_node_position(nodes[n_i]);
		Ref<VisualAnlNoiseNode> vanode = component->get_node(nodes[n_i]);

		GraphNode *node = memnew(GraphNode);
		graph->add_child(node);

		/*if (!vanode->is_connected("changed", this, "_node_changed")) {
			vanode->connect("changed", this, "_node_changed", varray(vanode->get_instance_id()), CONNECT_DEFERRED);
		}*/

		node->set_offset(position);

		node->set_title(vanode->get_caption());
		node->set_name(itos(nodes[n_i]));

		int port_offset = 0;

		if (nodes[n_i] >= 2) {
			node->set_show_close_button(true);
			node->connect("close_request", this, "_delete_request", varray(nodes[n_i]), CONNECT_DEFERRED);
		}

		node->connect("dragged", this, "_node_dragged", varray(nodes[n_i]));

		if (VisualAnlNoiseEditor::get_singleton()->can_edit(vanode)) { // it's a component

			Ref<VisualAnlNoiseNodeComponent> comp = vanode;

			// Component's name
			LineEdit *name = memnew(LineEdit);
			name->set_text(comp->get_component_name());
			name->set_expand_to_text_length(true);
			node->add_child(name);
			name->connect("text_entered", this, "_component_renamed", varray(nodes[n_i]));
			name->connect("focus_exited", this, "_component_renamed_focus_out", varray(name, nodes[n_i]));

			// Open in editor button
			node->add_child(memnew(HSeparator));
			Button *open_in_editor = memnew(Button);
			open_in_editor->set_text(TTR("Open Editor"));
			open_in_editor->set_icon(get_icon("Edit", "EditorIcons"));
			node->add_child(open_in_editor);
			open_in_editor->connect("pressed", this, "_open_in_editor", varray(nodes[n_i]), CONNECT_DEFERRED);
			open_in_editor->set_h_size_flags(SIZE_SHRINK_CENTER);
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

void VisualAnlNoiseNodeComponentEditor::_component_renamed(const String &p_text, int p_which) {

	Ref<VisualAnlNoiseNodeComponent> comp = component->get_node(p_which);
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
	undo_redo->add_do_method(VisualAnlNoiseEditor::get_singleton(), "_update_path"); // FIXME: should update button path
	undo_redo->add_undo_method(VisualAnlNoiseEditor::get_singleton(), "_update_path");
	undo_redo->commit_action();
	updating = false;

	gn->set_name(new_name);
	gn->set_size(gn->get_minimum_size());
}

void VisualAnlNoiseNodeComponentEditor::_component_renamed_focus_out(Node *le, int p_which) {

	_component_renamed(le->call("get_text"), p_which);
}

void VisualAnlNoiseNodeComponentEditor::_preview_select_port(int p_node, int p_port) {

	if (component.is_null()) {
		return;
	}

	Ref<VisualAnlNoiseNode> node = component->get_node(p_node);

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

void VisualAnlNoiseNodeComponentEditor::_line_edit_changed(const String &p_text, Object *line_edit, int p_node_id) {

}

void VisualAnlNoiseNodeComponentEditor::_line_edit_focus_out(Object *line_edit, int p_node_id) {

}

void VisualAnlNoiseNodeComponentEditor::_port_edited() {

	if (component.is_null()) {
		return;
	}

	Variant value = property_editor->get_variant();
	Ref<VisualAnlNoiseNode> van = component->get_node(editing_node);
	ERR_FAIL_COND(!van.is_valid());

	undo_redo->create_action("Set Input Default Port");
	undo_redo->add_do_method(van.ptr(), "set_input_port_default_value", editing_port, value);
	undo_redo->add_undo_method(van.ptr(), "set_input_port_default_value", editing_port, van->get_input_port_default_value(editing_port));
	undo_redo->add_do_method(this, "_update_graph");
	undo_redo->add_undo_method(this, "_update_graph");
	undo_redo->commit_action();

	property_editor->hide();
}

void VisualAnlNoiseNodeComponentEditor::_edit_port_default_input(Object *p_button, int p_node, int p_port) {

	if (component.is_null()) {
		return;
	}

	Ref<VisualAnlNoiseNode> van = component->get_node(p_node);

	Button *button = Object::cast_to<Button>(p_button);
	ERR_FAIL_COND(!button);
	Variant value = van->get_input_port_default_value(p_port);
	property_editor->set_global_position(button->get_global_position() + Vector2(0, button->get_size().height));
	property_editor->edit(NULL, "", value.get_type(), value, 0, "");
	property_editor->popup();
	editing_node = p_node;
	editing_port = p_port;
}

void VisualAnlNoiseNodeComponentEditor::_add_node(int p_idx) {

	if (component.is_null()) {
		return;
	}

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

	int id_to_use = component->get_valid_node_id();

	undo_redo->create_action("Add Node to Visual AnlNoise");
	undo_redo->add_do_method(component.ptr(), "add_node", vanode, position, id_to_use);
	undo_redo->add_undo_method(component.ptr(), "remove_node", id_to_use);
	undo_redo->add_do_method(this, "_update_graph");
	undo_redo->add_undo_method(this, "_update_graph");
	undo_redo->commit_action();
}

void VisualAnlNoiseNodeComponentEditor::_node_dragged(const Vector2 &p_from, const Vector2 &p_to, int p_node) {

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

void VisualAnlNoiseNodeComponentEditor::_connection_request(const String &p_from, int p_from_index, const String &p_to, int p_to_index) {

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

	List<VisualAnlNoiseNodeComponent::Connection> conns;
	component->get_node_connections(&conns);

	for (List<VisualAnlNoiseNodeComponent::Connection>::Element *E = conns.front(); E; E = E->next()) {
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

void VisualAnlNoiseNodeComponentEditor::_disconnection_request(const String &p_from, int p_from_index, const String &p_to, int p_to_index) {

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

void VisualAnlNoiseNodeComponentEditor::_connection_to_empty(const String &p_from, int p_from_slot, const Vector2 &p_release_position) {
}

void VisualAnlNoiseNodeComponentEditor::_delete_request(int which) {

	if (component.is_null()) {
		return;
	}

	undo_redo->create_action("Delete Node");
	undo_redo->add_do_method(component.ptr(), "remove_node", which);
	undo_redo->add_undo_method(component.ptr(), "add_node", component->get_node(which), component->get_node_position(which), which);

	List<VisualAnlNoiseNodeComponent::Connection> conns;
	component->get_node_connections(&conns);

	for (List<VisualAnlNoiseNodeComponent::Connection>::Element *E = conns.front(); E; E = E->next()) {
		if (E->get().from_node == which || E->get().to_node == which) {
			undo_redo->add_undo_method(component.ptr(), "connect_nodes", E->get().from_node, E->get().from_port, E->get().to_node, E->get().to_port);
		}
	}

	undo_redo->add_do_method(this, "_update_graph");
	undo_redo->add_undo_method(this, "_update_graph");
	undo_redo->commit_action();
}

void VisualAnlNoiseNodeComponentEditor::_node_selected(Object *p_node) {

	if (component.is_null()) {
		return;
	}

	GraphNode *gn = Object::cast_to<GraphNode>(p_node);
	ERR_FAIL_COND(!gn);

	int id = String(gn->get_name()).to_int();

	Ref<VisualAnlNoiseNode> vanode = component->get_node(id);
	ERR_FAIL_COND(!vanode.is_valid());
}

void VisualAnlNoiseNodeComponentEditor::_open_in_editor(int p_which) {

	Ref<VisualAnlNoiseNodeComponent> comp = component->get_node(p_which);
	ERR_FAIL_COND(!comp.is_valid());

	VisualAnlNoiseEditor::get_singleton()->enter_editor(p_which);
}

void VisualAnlNoiseNodeComponentEditor::_input(const Ref<InputEvent> p_event) {

	if (graph->has_focus()) {
		Ref<InputEventMouseButton> mb = p_event;

		if (mb.is_valid() && mb->is_pressed() && mb->get_button_index() == BUTTON_RIGHT) {
			add_node->get_popup()->set_position(get_viewport()->get_mouse_position());
			add_node->get_popup()->show_modal();
		}
	}
}

void VisualAnlNoiseNodeComponentEditor::_notification(int p_what) {

	if (p_what == NOTIFICATION_ENTER_TREE || p_what == NOTIFICATION_THEME_CHANGED) {

		error_panel->add_style_override("panel", get_stylebox("bg", "Tree"));
		error_label->add_color_override("font_color", get_color("error_color", "Editor"));
	}

	if (p_what == NOTIFICATION_PROCESS) {
	}
}

void VisualAnlNoiseNodeComponentEditor::_scroll_changed(const Vector2 &p_scroll) {

	if (component.is_null()) {
		return;
	}

	if (updating)
		return;

	updating = true;
	component->set_graph_offset(p_scroll / EDSCALE);
	updating = false;
}

void VisualAnlNoiseNodeComponentEditor::_node_changed(int p_id) {

	if (updating)
		return;

	if (is_visible_in_tree()) {
		_update_graph();
	}
}

void VisualAnlNoiseNodeComponentEditor::_duplicate_nodes() {

	if (component.is_null()) {
		return;
	}

	List<int> nodes;

	for (int i = 0; i < graph->get_child_count(); i++) {

		if (Object::cast_to<GraphNode>(graph->get_child(i))) {
			int id = String(graph->get_child(i)->get_name()).to_int();
			Ref<VisualAnlNoiseNode> node = component->get_node(id);
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

	int base_id = component->get_valid_node_id();
	int id_from = base_id;
	Map<int, int> connection_remap;

	for (List<int>::Element *E = nodes.front(); E; E = E->next()) {

		connection_remap[E->get()] = id_from;
		Ref<VisualAnlNoiseNode> node = component->get_node(E->get());

		Ref<VisualAnlNoiseNode> dupli = node->duplicate();

		undo_redo->add_do_method(component.ptr(), "add_node", dupli, component->get_node_position(E->get()) + Vector2(10, 10) * EDSCALE, id_from);
		undo_redo->add_undo_method(component.ptr(), "remove_node", id_from);

		id_from++;
	}

	List<VisualAnlNoiseNodeComponent::Connection> conns;
	component->get_node_connections(&conns);

	for (List<VisualAnlNoiseNodeComponent::Connection>::Element *E = conns.front(); E; E = E->next()) {
		if (connection_remap.has(E->get().from_node) && connection_remap.has(E->get().to_node)) {
			undo_redo->add_do_method(component.ptr(), "connect_nodes", connection_remap[E->get().from_node], E->get().from_port, connection_remap[E->get().to_node], E->get().to_port);
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

void VisualAnlNoiseNodeComponentEditor::_bind_methods() {

	ClassDB::bind_method("_component_renamed", &VisualAnlNoiseNodeComponentEditor::_component_renamed);
	ClassDB::bind_method("_component_renamed_focus_out", &VisualAnlNoiseNodeComponentEditor::_component_renamed_focus_out);
	ClassDB::bind_method("_update_graph", &VisualAnlNoiseNodeComponentEditor::_update_graph);
	ClassDB::bind_method("_add_node", &VisualAnlNoiseNodeComponentEditor::_add_node);
	ClassDB::bind_method("_node_dragged", &VisualAnlNoiseNodeComponentEditor::_node_dragged);
	ClassDB::bind_method("_connection_request", &VisualAnlNoiseNodeComponentEditor::_connection_request);
	ClassDB::bind_method("_disconnection_request", &VisualAnlNoiseNodeComponentEditor::_disconnection_request);
	ClassDB::bind_method("_node_selected", &VisualAnlNoiseNodeComponentEditor::_node_selected);
	ClassDB::bind_method("_open_in_editor", &VisualAnlNoiseNodeComponentEditor::_open_in_editor);
	ClassDB::bind_method("_scroll_changed", &VisualAnlNoiseNodeComponentEditor::_scroll_changed);
	ClassDB::bind_method("_delete_request", &VisualAnlNoiseNodeComponentEditor::_delete_request);
	ClassDB::bind_method("_node_changed", &VisualAnlNoiseNodeComponentEditor::_node_changed);
	ClassDB::bind_method("_edit_port_default_input", &VisualAnlNoiseNodeComponentEditor::_edit_port_default_input);
	ClassDB::bind_method("_port_edited", &VisualAnlNoiseNodeComponentEditor::_port_edited);
	ClassDB::bind_method("_connection_to_empty", &VisualAnlNoiseNodeComponentEditor::_connection_to_empty);
	ClassDB::bind_method("_line_edit_focus_out", &VisualAnlNoiseNodeComponentEditor::_line_edit_focus_out);
	ClassDB::bind_method("_line_edit_changed", &VisualAnlNoiseNodeComponentEditor::_line_edit_changed);
	ClassDB::bind_method("_duplicate_nodes", &VisualAnlNoiseNodeComponentEditor::_duplicate_nodes);
	ClassDB::bind_method("_preview_select_port", &VisualAnlNoiseNodeComponentEditor::_preview_select_port);
	ClassDB::bind_method("_input", &VisualAnlNoiseNodeComponentEditor::_input);
}

VisualAnlNoiseNodeComponentEditor *VisualAnlNoiseNodeComponentEditor::singleton = NULL;

VisualAnlNoiseNodeComponentEditor::VisualAnlNoiseNodeComponentEditor() {

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

	add_options.push_back(AddOption("Scalar", "Constants", "VisualAnlNoiseNodeScalar"));
	add_options.push_back(AddOption("Simplex", "Basis", "VisualAnlNoiseNodeSimplexBasis"));
	add_options.push_back(AddOption("Component", "Component", "VisualAnlNoiseNodeComponent"));

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

///////////////////////////////////
// Creates custom editors for nodes
///////////////////////////////////

Control *VisualAnlNoiseNodePlugin::create_editor(const Ref<VisualAnlNoiseNode> &p_node) {

	if (get_script_instance()) {
		return get_script_instance()->call("create_editor", p_node);
	}
	return NULL;
}

void VisualAnlNoiseNodePlugin::_bind_methods() {

	BIND_VMETHOD(MethodInfo(Variant::OBJECT, "create_editor", PropertyInfo(Variant::OBJECT, "for_node", PROPERTY_HINT_RESOURCE_TYPE, "VisualAnlNoiseNode")));
}


class VisualAnlNoiseNodePluginDefaultEditor : public VBoxContainer {
	GDCLASS(VisualAnlNoiseNodePluginDefaultEditor, VBoxContainer)
public:
	void _property_changed(const String &prop, const Variant &p_value, bool p_changing = false) {

		if (p_changing)
			return;

		UndoRedo *undo_redo = EditorNode::get_singleton()->get_undo_redo();

		updating = true;
		undo_redo->create_action("Edit Visual AnlNoise Property: " + prop, UndoRedo::MERGE_ENDS);
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
		VisualAnlNoiseNodeComponentEditor::get_singleton()->call_deferred("_update_graph");
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

// void VisualAnlNoiseNodeComponentEditor::_on_noise_changed() {

// 	Ref<VisualAnlNoiseNodeComponent> component = visual_anl_noise->get_component();

// 	if (component.is_valid()) {
// 		component = component;
// 		_update_graph();
// 	}
// }