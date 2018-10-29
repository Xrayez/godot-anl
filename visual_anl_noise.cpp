#include "visual_anl_noise.h"
#include "core/vmap.h"

void VisualAnlNoiseNode::set_output_port_for_preview(int p_index) {

	port_preview = p_index;
}

int VisualAnlNoiseNode::get_output_port_for_preview() const {

	return port_preview;
}

void VisualAnlNoiseNode::set_input_port_default_value(int p_port, const Variant &p_value) {
	default_input_values[p_port] = p_value;
	emit_changed();
}

Variant VisualAnlNoiseNode::get_input_port_default_value(int p_port) const {
	if (default_input_values.has(p_port)) {
		return default_input_values[p_port];
	}

	return Variant();
}

bool VisualAnlNoiseNode::is_port_separator(int p_index) const {
	return false;
}

Vector<StringName> VisualAnlNoiseNode::get_editable_properties() const {
	return Vector<StringName>();
}

Array VisualAnlNoiseNode::_get_default_input_values() const {

	Array ret;
	for (Map<int, Variant>::Element *E = default_input_values.front(); E; E = E->next()) {
		ret.push_back(E->key());
		ret.push_back(E->get());
	}
	return ret;
}

void VisualAnlNoiseNode::_set_default_input_values(const Array &p_values) {

	if (p_values.size() % 2 == 0) {
		for (int i = 0; i < p_values.size(); i += 2) {
			default_input_values[p_values[i + 0]] = p_values[i + 1];
		}
	}

	emit_changed();
}

String VisualAnlNoiseNode::get_warning() const {
	return String();
}

void VisualAnlNoiseNode::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_output_port_for_preview", "port"), &VisualAnlNoiseNode::set_output_port_for_preview);
	ClassDB::bind_method(D_METHOD("get_output_port_for_preview"), &VisualAnlNoiseNode::get_output_port_for_preview);

	ClassDB::bind_method(D_METHOD("set_input_port_default_value", "port", "value"), &VisualAnlNoiseNode::set_input_port_default_value);
	ClassDB::bind_method(D_METHOD("get_input_port_default_value", "port"), &VisualAnlNoiseNode::get_input_port_default_value);

	ClassDB::bind_method(D_METHOD("_set_default_input_values", "values"), &VisualAnlNoiseNode::_set_default_input_values);
	ClassDB::bind_method(D_METHOD("_get_default_input_values"), &VisualAnlNoiseNode::_get_default_input_values);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "output_port_for_preview"), "set_output_port_for_preview", "get_output_port_for_preview");
	ADD_PROPERTYNZ(PropertyInfo(Variant::ARRAY, "default_input_values", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_NOEDITOR), "_set_default_input_values", "_get_default_input_values");
	ADD_SIGNAL(MethodInfo("editor_refresh_request"));
}

VisualAnlNoiseNode::VisualAnlNoiseNode() {

	port_preview = -1;
}

/////////////////////////////////////////////////////////

void VisualAnlNoiseNodeComponent::add_node(const Ref<VisualAnlNoiseNode> &p_node, const Vector2 &p_position, int p_id) {

	ERR_FAIL_COND(p_node.is_null());
	ERR_FAIL_COND(p_id < 2);
	ERR_FAIL_COND(graph.nodes.has(p_id));

	Node n;
	n.node = p_node;
	n.position = p_position;

	Ref<VisualAnlNoiseNodeInput> input = n.node;

	if (input.is_valid()) {
		input->connect("input_type_changed", this, "_input_type_changed", varray(p_id));
	}

	n.node->connect("changed", this, "_queue_update");

	graph.nodes[p_id] = n;

	print_line("added_node");

	_queue_update();
}

void VisualAnlNoiseNodeComponent::set_node_position(int p_id, const Vector2 &p_position) {

	ERR_FAIL_COND(!graph.nodes.has(p_id));

	graph.nodes[p_id].position = p_position;
}

Vector2 VisualAnlNoiseNodeComponent::get_node_position(int p_id) const {

	ERR_FAIL_COND_V(!graph.nodes.has(p_id), Vector2());

	return graph.nodes[p_id].position;
}

Ref<VisualAnlNoiseNode> VisualAnlNoiseNodeComponent::get_node(int p_id) const {

	ERR_FAIL_COND_V(!graph.nodes.has(p_id), Ref<VisualAnlNoiseNode>());

	return graph.nodes[p_id].node;
}

Vector<int> VisualAnlNoiseNodeComponent::get_node_list() const {

	Vector<int> ret;
	for (Map<int, Node>::Element *E = graph.nodes.front(); E; E = E->next()) {
		ret.push_back(E->key());
	}

	return ret;
}

int VisualAnlNoiseNodeComponent::get_valid_node_id() const {

	return graph.nodes.size() ? MAX(2, graph.nodes.back()->key() + 1) : 2;
}

int VisualAnlNoiseNodeComponent::find_node_id(const Ref<VisualAnlNoiseNode> &p_node) const {

	for (const Map<int, Node>::Element *E = graph.nodes.front(); E; E = E->next()) {
		if (E->get().node == p_node)
			return E->key();
	}

	return NODE_ID_INVALID;
}

void VisualAnlNoiseNodeComponent::remove_node(int p_id) {

	ERR_FAIL_COND(p_id < 2);

	ERR_FAIL_COND(!graph.nodes.has(p_id));

	Ref<VisualAnlNoiseNodeInput> input = graph.nodes[p_id].node;

	if (input.is_valid()) {
		input->disconnect("input_type_changed", this, "_input_type_changed");
	}

	graph.nodes[p_id].node->disconnect("changed", this, "_queue_update");

	graph.nodes.erase(p_id);

	for (List<Connection>::Element *E = graph.connections.front(); E;) {
		List<Connection>::Element *N = E->next();
		if (E->get().from_node == p_id || E->get().to_node == p_id) {
			graph.connections.erase(E);
		}
		E = N;
	}

	_queue_update();
}

bool VisualAnlNoiseNodeComponent::is_node_connection(int p_from_node, int p_from_port, int p_to_node, int p_to_port) const {

	for (const List<Connection>::Element *E = graph.connections.front(); E; E = E->next()) {

		if (E->get().from_node == p_from_node && E->get().from_port == p_from_port && E->get().to_node == p_to_node && E->get().to_port == p_to_port) {
			return true;
		}
	}

	return false;
}

bool VisualAnlNoiseNodeComponent::can_connect_nodes(int p_from_node, int p_from_port, int p_to_node, int p_to_port) const {

	if (!graph.nodes.has(p_from_node))
		return false;

	if (p_from_port < 0 || p_from_port >= graph.nodes[p_from_node].node->get_output_port_count())
		return false;

	if (!graph.nodes.has(p_to_node))
		return false;

	if (p_to_port < 0 || p_to_port >= graph.nodes[p_to_node].node->get_input_port_count())
		return false;

	VisualAnlNoiseNode::PortType from_port_type = graph.nodes[p_from_node].node->get_output_port_type(p_from_port);
	VisualAnlNoiseNode::PortType to_port_type = graph.nodes[p_to_node].node->get_input_port_type(p_to_port);

	if (MAX(0, from_port_type - 1) != (MAX(0, to_port_type - 1))) {
		return false;
	}

	for (const List<Connection>::Element *E = graph.connections.front(); E; E = E->next()) {

		if (E->get().from_node == p_from_node && E->get().from_port == p_from_port && E->get().to_node == p_to_node && E->get().to_port == p_to_port) {
			return false;
		}
	}

	return true;
}

Error VisualAnlNoiseNodeComponent::connect_nodes(int p_from_node, int p_from_port, int p_to_node, int p_to_port) {

	ERR_FAIL_COND_V(!graph.nodes.has(p_from_node), ERR_INVALID_PARAMETER);
	ERR_FAIL_INDEX_V(p_from_port, graph.nodes[p_from_node].node->get_output_port_count(), ERR_INVALID_PARAMETER);
	ERR_FAIL_COND_V(!graph.nodes.has(p_to_node), ERR_INVALID_PARAMETER);
	ERR_FAIL_INDEX_V(p_to_port, graph.nodes[p_to_node].node->get_input_port_count(), ERR_INVALID_PARAMETER);

	VisualAnlNoiseNode::PortType from_port_type = graph.nodes[p_from_node].node->get_output_port_type(p_from_port);
	VisualAnlNoiseNode::PortType to_port_type = graph.nodes[p_to_node].node->get_input_port_type(p_to_port);

	if (MAX(0, from_port_type - 1) != (MAX(0, to_port_type - 1))) {
		ERR_EXPLAIN("Incompatible port types (scalar/index");
		ERR_FAIL_V(ERR_INVALID_PARAMETER)
		return ERR_INVALID_PARAMETER;
	}

	for (List<Connection>::Element *E = graph.connections.front(); E; E = E->next()) {

		if (E->get().from_node == p_from_node && E->get().from_port == p_from_port && E->get().to_node == p_to_node && E->get().to_port == p_to_port) {
			ERR_FAIL_V(ERR_ALREADY_EXISTS);
		}
	}

	Connection c;
	c.from_node = p_from_node;
	c.from_port = p_from_port;
	c.to_node = p_to_node;
	c.to_port = p_to_port;
	graph.connections.push_back(c);

	_queue_update();

	return OK;
}

void VisualAnlNoiseNodeComponent::disconnect_nodes(int p_from_node, int p_from_port, int p_to_node, int p_to_port) {

	for (List<Connection>::Element *E = graph.connections.front(); E; E = E->next()) {

		if (E->get().from_node == p_from_node && E->get().from_port == p_from_port && E->get().to_node == p_to_node && E->get().to_port == p_to_port) {
			graph.connections.erase(E);
			_queue_update();
			return;
		}
	}
}

Array VisualAnlNoiseNodeComponent::_get_node_connections() const {

	Array ret;

	for (const List<Connection>::Element *E = graph.connections.front(); E; E = E->next()) {
		Dictionary d;
		d["from_node"] = E->get().from_node;
		d["from_port"] = E->get().from_port;
		d["to_node"] = E->get().to_node;
		d["to_port"] = E->get().to_port;
		ret.push_back(d);
	}
	return ret;
}

void VisualAnlNoiseNodeComponent::get_node_connections(List<Connection> *r_connections) const {

	for (const List<Connection>::Element *E = graph.connections.front(); E; E = E->next()) {
		r_connections->push_back(E->get());
	}
}

void VisualAnlNoiseNodeComponent::set_graph_offset(const Vector2 &p_offset) {

	graph_offset = p_offset;
}

Vector2 VisualAnlNoiseNodeComponent::get_graph_offset() const {

	return graph_offset;
}

String VisualAnlNoiseNodeComponent::generate_preview_noise(int p_node, int p_port) const {

	Ref<VisualAnlNoiseNode> node = get_node(p_node);

	ERR_FAIL_COND_V(!node.is_valid(), String());
	ERR_FAIL_COND_V(p_port < 0 || p_port >= node->get_output_port_count(), String());

    return String();
}

bool VisualAnlNoiseNodeComponent::_set(const StringName &p_name, const Variant &p_value) {

	String name = p_name;
	if (name.begins_with("nodes/")) {

		String index = name.get_slicec('/', 2);
		if (index == "connections") {

			Vector<int> conns = p_value;
			if (conns.size() % 4 == 0) {
				for (int i = 0; i < conns.size(); i += 4) {
					connect_nodes(conns[i + 0], conns[i + 1], conns[i + 2], conns[i + 3]);
				}
			}
			return true;
		}

		int id = index.to_int();
		String what = name.get_slicec('/', 3);

		if (what == "node") {
			add_node(p_value, Vector2(), id);
			return true;
		} else if (what == "position") {
			set_node_position(id, p_value);
			return true;
		}
	}
	return false;
}

bool VisualAnlNoiseNodeComponent::_get(const StringName &p_name, Variant &r_ret) const {

	String name = p_name;
	if (name.begins_with("nodes/")) {

		String index = name.get_slicec('/', 2);
		if (index == "connections") {

			Vector<int> conns;
			for (const List<Connection>::Element *E = graph.connections.front(); E; E = E->next()) {
				conns.push_back(E->get().from_node);
				conns.push_back(E->get().from_port);
				conns.push_back(E->get().to_node);
				conns.push_back(E->get().to_port);
			}

			r_ret = conns;
			return true;
		}

		int id = index.to_int();
		String what = name.get_slicec('/', 3);

		if (what == "node") {
			r_ret = get_node(id);
			return true;
		} else if (what == "position") {
			r_ret = get_node_position(id);
			return true;
		}
	}
	return false;
}

void VisualAnlNoiseNodeComponent::_get_property_list(List<PropertyInfo> *p_list) const {

    for (Map<int, Node>::Element *E = graph.nodes.front(); E; E = E->next()) {

        String prop_name = "nodes/";
        prop_name += "/" + itos(E->key());

        if (E->key() != NODE_ID_OUTPUT) {

            p_list->push_back(PropertyInfo(Variant::OBJECT, prop_name + "/node", PROPERTY_HINT_RESOURCE_TYPE, "VisualAnlNoiseNode", PROPERTY_USAGE_NOEDITOR | PROPERTY_USAGE_DO_NOT_SHARE_ON_DUPLICATE));
        }
        p_list->push_back(PropertyInfo(Variant::VECTOR2, prop_name + "/position", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_NOEDITOR));
    }
    p_list->push_back(PropertyInfo(Variant::POOL_INT_ARRAY, "nodes/connections", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_NOEDITOR));
}

void VisualAnlNoiseNodeComponent::_update_noise() const {

	if (!dirty)
		return;

	dirty = false;
}

void VisualAnlNoiseNodeComponent::_queue_update() {

	if (dirty) {
		return;
	}

	dirty = true;

	call_deferred("_update_noise");
}


void VisualAnlNoiseNodeComponent::_bind_methods() {

	ClassDB::bind_method(D_METHOD("add_node", "node", "position", "id"), &VisualAnlNoiseNodeComponent::add_node);
	ClassDB::bind_method(D_METHOD("set_node_position", "id", "position"), &VisualAnlNoiseNodeComponent::set_node_position);

	ClassDB::bind_method(D_METHOD("get_node", "id"), &VisualAnlNoiseNodeComponent::get_node);
	ClassDB::bind_method(D_METHOD("get_node_position", "id"), &VisualAnlNoiseNodeComponent::get_node_position);

	ClassDB::bind_method(D_METHOD("get_node_list"), &VisualAnlNoiseNodeComponent::get_node_list);
	ClassDB::bind_method(D_METHOD("get_valid_node_id"), &VisualAnlNoiseNodeComponent::get_valid_node_id);

	ClassDB::bind_method(D_METHOD("remove_node", "id"), &VisualAnlNoiseNodeComponent::remove_node);

	ClassDB::bind_method(D_METHOD("is_node_connection", "from_node", "from_port", "to_node", "to_port"), &VisualAnlNoiseNodeComponent::is_node_connection);
	ClassDB::bind_method(D_METHOD("can_connect_nodes", "from_node", "from_port", "to_node", "to_port"), &VisualAnlNoiseNodeComponent::is_node_connection);

	ClassDB::bind_method(D_METHOD("connect_nodes", "from_node", "from_port", "to_node", "to_port"), &VisualAnlNoiseNodeComponent::connect_nodes);
	ClassDB::bind_method(D_METHOD("disconnect_nodes", "from_node", "from_port", "to_node", "to_port"), &VisualAnlNoiseNodeComponent::disconnect_nodes);

	ClassDB::bind_method(D_METHOD("get_node_connections"), &VisualAnlNoiseNodeComponent::_get_node_connections);

	ClassDB::bind_method(D_METHOD("set_graph_offset", "offset"), &VisualAnlNoiseNodeComponent::set_graph_offset);
	ClassDB::bind_method(D_METHOD("get_graph_offset"), &VisualAnlNoiseNodeComponent::get_graph_offset);

	ClassDB::bind_method(D_METHOD("_queue_update"), &VisualAnlNoiseNodeComponent::_queue_update);
	ClassDB::bind_method(D_METHOD("_update_noise"), &VisualAnlNoiseNodeComponent::_update_noise);

	ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "graph_offset", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_NOEDITOR), "set_graph_offset", "get_graph_offset");

	BIND_CONSTANT(NODE_ID_INVALID);
	BIND_CONSTANT(NODE_ID_OUTPUT);
}


VisualAnlNoise::VisualAnlNoise() : AnlNoise() {

	component.instance();
}


void VisualAnlNoise::_bind_methods() {

	ClassDB::bind_method(D_METHOD("get_component"), &VisualAnlNoise::get_component);
	ClassDB::bind_method(D_METHOD("set_component", "component"), &VisualAnlNoise::set_component);
}

void VisualAnlNoise::set_component(const Ref<VisualAnlNoiseNodeComponent> p_component) {

	if(p_component.is_valid()) {
		component = p_component;
	}
}


Ref<VisualAnlNoiseNodeComponent> VisualAnlNoise::get_component() const {

	return component;
}

VisualAnlNoiseNodeComponent::VisualAnlNoiseNodeComponent() {

    Ref<VisualAnlNoiseNodeOutput> output;
    output.instance();
    graph.nodes[NODE_ID_OUTPUT].node = output;
    graph.nodes[NODE_ID_OUTPUT].position = Vector2(400, 150);

	dirty = true;
}

int VisualAnlNoiseNodeComponent::get_input_port_count() const {

	return 0;
}

VisualAnlNoiseNode::PortType VisualAnlNoiseNodeComponent::get_input_port_type(int p_port) const {

	return PORT_TYPE_SCALAR;
}

String VisualAnlNoiseNodeComponent::get_input_port_name(int p_port) const {

	return "";
}

int VisualAnlNoiseNodeComponent::get_output_port_count() const {

	return 1;
}

VisualAnlNoiseNode::PortType VisualAnlNoiseNodeComponent::get_output_port_type(int p_port) const {

	return PORT_TYPE_SCALAR;
}

String VisualAnlNoiseNodeComponent::get_output_port_name(int p_port) const {
	return "";
}

String VisualAnlNoiseNodeComponent::get_caption() const {
	return TTR("Component");
}

int VisualAnlNoiseNodeInput::get_input_port_count() const {

	return 0;
}

VisualAnlNoiseNodeInput::PortType VisualAnlNoiseNodeInput::get_input_port_type(int p_port) const {

	return PORT_TYPE_SCALAR;
}

String VisualAnlNoiseNodeInput::get_input_port_name(int p_port) const {

	return "";
}

int VisualAnlNoiseNodeInput::get_output_port_count() const {

	return 1;
}

VisualAnlNoiseNodeInput::PortType VisualAnlNoiseNodeInput::get_output_port_type(int p_port) const {

	return get_input_type_by_name(input_name);
}

String VisualAnlNoiseNodeInput::get_output_port_name(int p_port) const {
	return "";
}

String VisualAnlNoiseNodeInput::get_caption() const {
	return TTR("Input");
}

void VisualAnlNoiseNodeInput::set_input_name(String p_name) {

	PortType prev_type = get_input_type_by_name(input_name);
	input_name = p_name;
	emit_changed();
	if (get_input_type_by_name(input_name) != prev_type) {
		emit_signal("input_type_changed");
	}
}

String VisualAnlNoiseNodeInput::get_input_name() const {

	return input_name;
}

VisualAnlNoiseNodeInput::PortType VisualAnlNoiseNodeInput::get_input_type_by_name(String p_name) const {

	return PORT_TYPE_SCALAR;
}

int VisualAnlNoiseNodeInput::get_input_index_count() const {

	int count = 0;

	return count;
}

VisualAnlNoiseNodeInput::PortType VisualAnlNoiseNodeInput::get_input_index_type(int p_index) const {

	return PORT_TYPE_SCALAR;
}

String VisualAnlNoiseNodeInput::get_input_index_name(int p_index) const {

	return String();
}

void VisualAnlNoiseNodeInput::_validate_property(PropertyInfo &property) const {

}

Vector<StringName> VisualAnlNoiseNodeInput::get_editable_properties() const {

	Vector<StringName> props;
	props.push_back("input_name");
	return props;
}

void VisualAnlNoiseNodeInput::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_input_name", "name"), &VisualAnlNoiseNodeInput::set_input_name);
	ClassDB::bind_method(D_METHOD("get_input_name"), &VisualAnlNoiseNodeInput::get_input_name);

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "input_name", PROPERTY_HINT_ENUM, ""), "set_input_name", "get_input_name");
	ADD_SIGNAL(MethodInfo("input_type_changed"));
}

VisualAnlNoiseNodeInput::VisualAnlNoiseNodeInput() {
	input_name = "[None]";
	// changed when set
}

int VisualAnlNoiseNodeOutput::get_input_port_count() const {

	return 1;
}

VisualAnlNoiseNodeOutput::PortType VisualAnlNoiseNodeOutput::get_input_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAnlNoiseNodeOutput::get_input_port_name(int p_port) const {

	return TTR("Index");
}

Variant VisualAnlNoiseNodeOutput::get_input_port_default_value(int p_port) const {

	return Variant();
}

int VisualAnlNoiseNodeOutput::get_output_port_count() const {

	return 0;
}

VisualAnlNoiseNodeOutput::PortType VisualAnlNoiseNodeOutput::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAnlNoiseNodeOutput::get_output_port_name(int p_port) const {
	return String();
}

bool VisualAnlNoiseNodeOutput::is_port_separator(int p_index) const {

	return false;
}

String VisualAnlNoiseNodeOutput::get_caption() const {
	return TTR("Output");
}

VisualAnlNoiseNodeOutput::VisualAnlNoiseNodeOutput() {
}
