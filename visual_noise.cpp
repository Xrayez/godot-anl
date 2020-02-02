#include "visual_noise.h"
#include "plugins/visual_noise_editor_plugin.h"
#include "visual_noise_nodes.h"

#include "core/vmap.h"

const int VisualAccidentalNoiseNode::OUTPUT_PORT = 0;

void VisualAccidentalNoiseNode::set_output_port_for_preview(int p_index) {

	port_preview = p_index;
}

int VisualAccidentalNoiseNode::get_output_port_for_preview() const {

	return port_preview;
}

void VisualAccidentalNoiseNode::set_input_port_value(int p_port, const Variant &p_value) {

	// nothing to set
}

Variant VisualAccidentalNoiseNode::get_input_port_value(int p_port) const {

	return Variant();
}

void VisualAccidentalNoiseNode::set_input_port_default_value(int p_port, const Variant &p_value) {

	default_input_values[p_port] = p_value;
	emit_changed();
}

Variant VisualAccidentalNoiseNode::get_input_port_default_value(int p_port) const {

	if (default_input_values.has(p_port)) {
		return default_input_values[p_port];
	}
	return Variant();
}

bool VisualAccidentalNoiseNode::is_port_separator(int p_index) const {

	return false;
}

Vector<StringName> VisualAccidentalNoiseNode::get_editable_properties() const {
	return Vector<StringName>();
}

Array VisualAccidentalNoiseNode::get_default_input_values() const {

	Array ret;
	for (Map<int, Variant>::Element *E = default_input_values.front(); E; E = E->next()) {
		ret.push_back(E->key());
		ret.push_back(E->get());
	}
	return ret;
}

void VisualAccidentalNoiseNode::set_default_input_values(const Array &p_values) {

	if (p_values.size() % 2 == 0) {
		for (int i = 0; i < p_values.size(); i += 2) {
			default_input_values[p_values[i + 0]] = p_values[i + 1];
		}
	}

	emit_changed();
}

String VisualAccidentalNoiseNode::get_warning() const {
	return String();
}

void VisualAccidentalNoiseNode::set_output_port_value(int p_port, const Variant &p_value) {

	// nothing to do
}

Variant VisualAccidentalNoiseNode::get_output_port_value(int p_port) const {

	return output_value;
}

void VisualAccidentalNoiseNode::evaluate(Ref<VisualAccidentalNoise> noise) {

	// nothing to do
}

void VisualAccidentalNoiseNode::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_output_port_for_preview", "port"), &VisualAccidentalNoiseNode::set_output_port_for_preview);
	ClassDB::bind_method(D_METHOD("get_output_port_for_preview"), &VisualAccidentalNoiseNode::get_output_port_for_preview);

	ClassDB::bind_method(D_METHOD("set_input_port_default_value", "port", "value"), &VisualAccidentalNoiseNode::set_input_port_default_value);
	ClassDB::bind_method(D_METHOD("get_input_port_default_value", "port"), &VisualAccidentalNoiseNode::get_input_port_default_value);

	ClassDB::bind_method(D_METHOD("set_default_input_values", "values"), &VisualAccidentalNoiseNode::set_default_input_values);
	ClassDB::bind_method(D_METHOD("get_default_input_values"), &VisualAccidentalNoiseNode::get_default_input_values);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "output_port_for_preview", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_NOEDITOR), "set_output_port_for_preview", "get_output_port_for_preview");
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "default_input_values", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_NOEDITOR | PROPERTY_USAGE_INTERNAL), "set_default_input_values", "get_default_input_values");
	ADD_SIGNAL(MethodInfo("editor_refresh_request"));

	BIND_ENUM_CONSTANT(Axis::AXIS_DOMAIN);
	BIND_ENUM_CONSTANT(Axis::AXIS_X);
	BIND_ENUM_CONSTANT(Axis::AXIS_Y);
	BIND_ENUM_CONSTANT(Axis::AXIS_Z);
	BIND_ENUM_CONSTANT(Axis::AXIS_W);
	BIND_ENUM_CONSTANT(Axis::AXIS_U);
	BIND_ENUM_CONSTANT(Axis::AXIS_V);
}

VisualAccidentalNoiseNode::VisualAccidentalNoiseNode() {

	port_preview = -1;
}

/////////////////////////////////////////////////////////

void VisualAccidentalNoiseNodeComponent::set_component_name(const String &p_name) {

	name = p_name;
}

String VisualAccidentalNoiseNodeComponent::get_component_name() const {

	return name;
}

void VisualAccidentalNoiseNodeComponent::add_node(const Ref<VisualAccidentalNoiseNode> &p_node, const Vector2 &p_position, int p_id) {

	ERR_FAIL_COND(p_node.is_null());
	ERR_FAIL_COND(p_id < 2);
	ERR_FAIL_COND(graph.nodes.has(p_id));

	Node n;
	n.node = p_node;
	n.position = p_position;

	if (!n.node->is_connected("changed", this, "_notify_changed")) {
		n.node->connect("changed", this, "_notify_changed");
	}

	Ref<VisualAccidentalNoiseNodeInput> input = n.node;
	if (input.is_valid()) {
		const int input_idx = get_input_port_count();
		if (get_input_port_default_value(input_idx).get_type() == Variant::NIL) {
			set_input_port_default_value(input_idx, 0);
		}
	}

	graph.nodes[p_id] = n;

	_notify_changed();
}

void VisualAccidentalNoiseNodeComponent::set_node_position(int p_id, const Vector2 &p_position) {

	ERR_FAIL_COND(!graph.nodes.has(p_id));

	graph.nodes[p_id].position = p_position;
}

Vector2 VisualAccidentalNoiseNodeComponent::get_node_position(int p_id) const {

	ERR_FAIL_COND_V(!graph.nodes.has(p_id), Vector2());

	return graph.nodes[p_id].position;
}

Ref<VisualAccidentalNoiseNode> VisualAccidentalNoiseNodeComponent::get_node(int p_id) const {

	ERR_FAIL_COND_V(!graph.nodes.has(p_id), Ref<VisualAccidentalNoiseNode>());

	return graph.nodes[p_id].node;
}

bool VisualAccidentalNoiseNodeComponent::has_node(int p_id) const {

	return graph.nodes.has(p_id);
}

Vector<int> VisualAccidentalNoiseNodeComponent::get_node_list() const {

	Vector<int> ret;
	for (Map<int, Node>::Element *E = graph.nodes.front(); E; E = E->next()) {
		ret.push_back(E->key());
	}

	return ret;
}

int VisualAccidentalNoiseNodeComponent::get_valid_node_id() const {

	return graph.nodes.size() ? MAX(2, graph.nodes.back()->key() + 1) : 2;
}

int VisualAccidentalNoiseNodeComponent::find_node_id(const Ref<VisualAccidentalNoiseNode> &p_node) const {

	for (const Map<int, Node>::Element *E = graph.nodes.front(); E; E = E->next()) {
		if (E->get().node == p_node)
			return E->key();
	}

	return NODE_ID_INVALID;
}

void VisualAccidentalNoiseNodeComponent::remove_node(int p_id) {

	ERR_FAIL_COND(p_id < 2);
	ERR_FAIL_COND(!graph.nodes.has(p_id));

	graph.nodes[p_id].node->disconnect("changed", this, "_notify_changed");
	graph.nodes.erase(p_id);

	for (List<Connection>::Element *E = graph.connections.front(); E;) {
		List<Connection>::Element *N = E->next();
		if (E->get().from_node == p_id || E->get().to_node == p_id) {
			graph.connections.erase(E);
		}
		E = N;
	}
	_notify_changed();
}

bool VisualAccidentalNoiseNodeComponent::is_node_connection(int p_from_node, int p_from_port, int p_to_node, int p_to_port) const {

	bool is_connected = false;

	for (const List<Connection>::Element *E = graph.connections.front(); E; E = E->next()) {

		const Connection &con = E->get();

		if (con.from_node == p_from_node && con.from_port == p_from_port && con.to_node == p_to_node && con.to_port == p_to_port) {
			is_connected = true;
		}
		if (is_connected) {

			Ref<VisualAccidentalNoiseNode> to_vanode = get_node(con.to_node);

			if (p_to_port > to_vanode->get_input_port_count() - 1) {
				is_connected = false;
			}
			break;
		}
	}
	return is_connected;
}

bool VisualAccidentalNoiseNodeComponent::can_connect_nodes(int p_from_node, int p_from_port, int p_to_node, int p_to_port) const {

	if (!graph.nodes.has(p_from_node))
		return false;

	if (p_from_port < 0 || p_from_port >= graph.nodes[p_from_node].node->get_output_port_count())
		return false;

	if (!graph.nodes.has(p_to_node))
		return false;

	if (p_to_port < 0 || p_to_port >= graph.nodes[p_to_node].node->get_input_port_count())
		return false;

	if (p_from_node == p_to_node)
		return false;

	VisualAccidentalNoiseNode::PortType from_port_type = graph.nodes[p_from_node].node->get_output_port_type(p_from_port);
	VisualAccidentalNoiseNode::PortType to_port_type = graph.nodes[p_to_node].node->get_input_port_type(p_to_port);

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

Error VisualAccidentalNoiseNodeComponent::connect_nodes(int p_from_node, int p_from_port, int p_to_node, int p_to_port) {

	ERR_FAIL_COND_V(!graph.nodes.has(p_from_node), ERR_INVALID_PARAMETER);
	ERR_FAIL_INDEX_V(p_from_port, graph.nodes[p_from_node].node->get_output_port_count(), ERR_INVALID_PARAMETER);
	ERR_FAIL_COND_V(!graph.nodes.has(p_to_node), ERR_INVALID_PARAMETER);
	ERR_FAIL_INDEX_V(p_to_port, graph.nodes[p_to_node].node->get_input_port_count(), ERR_INVALID_PARAMETER);

	VisualAccidentalNoiseNode::PortType from_port_type = graph.nodes[p_from_node].node->get_output_port_type(p_from_port);
	VisualAccidentalNoiseNode::PortType to_port_type = graph.nodes[p_to_node].node->get_input_port_type(p_to_port);

	if (MAX(0, from_port_type - 1) != (MAX(0, to_port_type - 1))) {
		ERR_FAIL_V_MSG(ERR_INVALID_PARAMETER, "Incompatible port types (scalar/index)");
	}

	for (List<Connection>::Element *E = graph.connections.front(); E; E = E->next()) {

		if (E->get().from_node == p_from_node && E->get().from_port == p_from_port && E->get().to_node == p_to_node && E->get().to_port == p_to_port) {
			return ERR_ALREADY_EXISTS;
		}
	}

	Connection c;
	c.from_node = p_from_node;
	c.from_port = p_from_port;
	c.to_node = p_to_node;
	c.to_port = p_to_port;
	graph.connections.push_back(c);

	_notify_changed();

	return OK;
}

void VisualAccidentalNoiseNodeComponent::disconnect_nodes(int p_from_node, int p_from_port, int p_to_node, int p_to_port) {

	for (List<Connection>::Element *E = graph.connections.front(); E; E = E->next()) {

		if (E->get().from_node == p_from_node && E->get().from_port == p_from_port && E->get().to_node == p_to_node && E->get().to_port == p_to_port) {
			graph.connections.erase(E);
			_notify_changed();
			return;
		}
	}
}

Array VisualAccidentalNoiseNodeComponent::_get_node_connections() const {

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

void VisualAccidentalNoiseNodeComponent::get_node_connections(List<Connection> *r_connections) const {

	for (const List<Connection>::Element *E = graph.connections.front(); E; E = E->next()) {
		r_connections->push_back(E->get());
	}
}

void VisualAccidentalNoiseNodeComponent::set_graph_offset(const Vector2 &p_offset) {

	graph_offset = p_offset;
}

Vector2 VisualAccidentalNoiseNodeComponent::get_graph_offset() const {

	return graph_offset;
}

void VisualAccidentalNoiseNodeComponent::evaluate(Ref<VisualAccidentalNoise> noise) {

	// Make it faster to go around through noise nodes
	Connections input_connections;
	Connections output_connections;

	for (const List<Connection>::Element *E = graph.connections.front(); E; E = E->next()) {

		ConnectionKey from_key;
		from_key.node = E->get().from_node;
		from_key.port = E->get().from_port;
		output_connections.insert(from_key, E);

		ConnectionKey to_key;
		to_key.node = E->get().to_node;
		to_key.port = E->get().to_port;
		input_connections.insert(to_key, E);
	}

	Set<int> processed;

	// First, lets evaluate nodes that aren't connected to output
	for (const Map<int, Node>::Element *E = graph.nodes.front(); E; E = E->next()) {

		ConnectionKey ck;
		ck.node = E->key();
		ck.port = OUTPUT_PORT;

		if (ck.node != NODE_ID_OUTPUT && !output_connections.has(ck)) {
			// Found node which output port is not connected
			evaluate_node(ck.node, noise, input_connections, output_connections, processed);
		}
	}

	// Second, evaluate the main output node
	evaluate_node(NODE_ID_OUTPUT, noise, input_connections, output_connections, processed);

	const Ref<VisualAccidentalNoiseNodeOutput> &output = graph.nodes[NODE_ID_OUTPUT].node;
	ERR_FAIL_COND(output.is_null());

	// Finally, get the last index of the noise function evaluated
	output_value = output->get_output_port_value(OUTPUT_PORT);
}

void VisualAccidentalNoiseNodeComponent::evaluate_node(int node, Ref<VisualAccidentalNoise> noise, Connections &input_connections, Connections &output_connections, Set<int> &processed) {

	Ref<VisualAccidentalNoiseNode> &vanode = graph.nodes[node].node;

	// Evaluate inputs recursively first to retrieve needed indexes/values
	int input_count = vanode->get_input_port_count();
	for (int i = 0; i < input_count; i++) {

		ConnectionKey ck;
		ck.node = node;
		ck.port = i;

		if (input_connections.has(ck)) {
			int from_node = input_connections[ck]->get().from_node;

			if (processed.has(from_node)) {
				// Ensure not to re-evaluate nodes
				// Instruction indexes can be reused by other nodes as input
				continue;
			}
			evaluate_node(from_node, noise, input_connections, output_connections, processed);
		}
	}
	// Pass evaluated indexes/values to this node
	for (int i = 0; i < input_count; i++) {

		ConnectionKey ck;
		ck.node = node;
		ck.port = i;

		if (input_connections.has(ck)) {
			int from_node = input_connections[ck]->get().from_node;
			int from_port = input_connections[ck]->get().from_port;

			const Ref<VisualAccidentalNoiseNode> &from_vanode = graph.nodes[from_node].node;

			// VisualAccidentalNoiseNode::PortType in_type = vanode->get_input_port_type(i);
			// VisualAccidentalNoiseNode::PortType out_type = from_vanode->get_output_port_type(from_port);

			vanode->set_input_port_value(i, from_vanode->get_output_port_value(from_port));
		} else {
			Variant default_value = vanode->get_input_port_default_value(i);
			VisualAccidentalNoiseNode::PortType in_type = vanode->get_input_port_type(i);

			if (default_value.get_type() != Variant::NIL) {

				if (in_type == PORT_TYPE_INDEX) {
					// Evaluate constant noise from default value
					switch (default_value.get_type()) {
						case Variant::INT:
						case Variant::REAL: {
							Index constant = noise->constant(default_value);
							vanode->set_input_port_value(i, constant);
						} break;
						default: {}
					}
				} else if (in_type == PORT_TYPE_SCALAR) {
					// Just set default value
					vanode->set_input_port_value(i, default_value);
				}
			}
		}
	}
	// Ready to evaluate this node with inputs set
	vanode->evaluate(noise); // sets output value

	processed.insert(node);
}

bool VisualAccidentalNoiseNodeComponent::_set(const StringName &p_name, const Variant &p_value) {

	String name = p_name;
	if (name.begins_with("nodes/")) {

		String index = name.get_slicec('/', 1);
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
		String what = name.get_slicec('/', 2);

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

bool VisualAccidentalNoiseNodeComponent::_get(const StringName &p_name, Variant &r_ret) const {

	String name = p_name;
	if (name.begins_with("nodes/")) {

		String index = name.get_slicec('/', 1);
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
		String what = name.get_slicec('/', 2);

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

void VisualAccidentalNoiseNodeComponent::_get_property_list(List<PropertyInfo> *p_list) const {

	for (Map<int, Node>::Element *E = graph.nodes.front(); E; E = E->next()) {

		String prop_name = "nodes/";
		prop_name += itos(E->key());

		if (E->key() != NODE_ID_OUTPUT) {

			p_list->push_back(PropertyInfo(Variant::OBJECT, prop_name + "/node", PROPERTY_HINT_RESOURCE_TYPE, "VisualAccidentalNoiseNode", PROPERTY_USAGE_NOEDITOR | PROPERTY_USAGE_DO_NOT_SHARE_ON_DUPLICATE));
		}
		p_list->push_back(PropertyInfo(Variant::VECTOR2, prop_name + "/position", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_NOEDITOR));
	}
	p_list->push_back(PropertyInfo(Variant::POOL_INT_ARRAY, "nodes/connections", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_NOEDITOR));
}

void VisualAccidentalNoiseNodeComponent::_notify_changed() {

	emit_changed();
}

void VisualAccidentalNoiseNodeComponent::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_component_name", "name"), &VisualAccidentalNoiseNodeComponent::set_component_name);
	ClassDB::bind_method(D_METHOD("get_component_name"), &VisualAccidentalNoiseNodeComponent::get_component_name);

	ClassDB::bind_method(D_METHOD("add_node", "node", "position", "id"), &VisualAccidentalNoiseNodeComponent::add_node);
	ClassDB::bind_method(D_METHOD("set_node_position", "id", "position"), &VisualAccidentalNoiseNodeComponent::set_node_position);

	ClassDB::bind_method(D_METHOD("get_node", "id"), &VisualAccidentalNoiseNodeComponent::get_node);
	ClassDB::bind_method(D_METHOD("get_node_position", "id"), &VisualAccidentalNoiseNodeComponent::get_node_position);

	ClassDB::bind_method(D_METHOD("get_node_list"), &VisualAccidentalNoiseNodeComponent::get_node_list);
	ClassDB::bind_method(D_METHOD("get_valid_node_id"), &VisualAccidentalNoiseNodeComponent::get_valid_node_id);

	ClassDB::bind_method(D_METHOD("remove_node", "id"), &VisualAccidentalNoiseNodeComponent::remove_node);

	ClassDB::bind_method(D_METHOD("is_node_connection", "from_node", "from_port", "to_node", "to_port"), &VisualAccidentalNoiseNodeComponent::is_node_connection);
	ClassDB::bind_method(D_METHOD("can_connect_nodes", "from_node", "from_port", "to_node", "to_port"), &VisualAccidentalNoiseNodeComponent::is_node_connection);

	ClassDB::bind_method(D_METHOD("connect_nodes", "from_node", "from_port", "to_node", "to_port"), &VisualAccidentalNoiseNodeComponent::connect_nodes);
	ClassDB::bind_method(D_METHOD("disconnect_nodes", "from_node", "from_port", "to_node", "to_port"), &VisualAccidentalNoiseNodeComponent::disconnect_nodes);

	ClassDB::bind_method(D_METHOD("get_node_connections"), &VisualAccidentalNoiseNodeComponent::_get_node_connections);

	ClassDB::bind_method(D_METHOD("set_graph_offset", "offset"), &VisualAccidentalNoiseNodeComponent::set_graph_offset);
	ClassDB::bind_method(D_METHOD("get_graph_offset"), &VisualAccidentalNoiseNodeComponent::get_graph_offset);

	ClassDB::bind_method(D_METHOD("evaluate", "noise"), &VisualAccidentalNoiseNodeComponent::evaluate);

	ClassDB::bind_method(D_METHOD("_notify_changed"), &VisualAccidentalNoiseNodeComponent::_notify_changed);

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "name"), "set_component_name", "get_component_name");
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "graph_offset", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_NOEDITOR), "set_graph_offset", "get_graph_offset");

	BIND_CONSTANT(NODE_ID_INVALID);
	BIND_CONSTANT(NODE_ID_OUTPUT);
}

VisualAccidentalNoise::VisualAccidentalNoise() :
		AccidentalNoise() {

	clamping_enabled = false;
	clamp_low = 0.0;
	clamp_high = 1.0;

	dirty = true;

	connect("changed", this, "_queue_update");
}

void VisualAccidentalNoise::generate() {

	dirty = true;
	_update_noise();
}

void VisualAccidentalNoise::_update_noise() {

	if (component.is_null()) {
		return;
	}

	if (!dirty)
		return;

	if (!get_expression().empty()) {
		return;
	}

	dirty = false;

	// Some nodes like fractal layer make use of previously created
	// instruction indexes that might not be connected, so be sure to clean up
	clear();

	component->evaluate(Ref<VisualAccidentalNoise>(this));

	Index output_value = component->get_output_port_value(VisualAccidentalNoiseNode::OUTPUT_PORT);

	if (clamping_enabled) {
		output_value = clamp(output_value, constant(clamp_low), constant(clamp_high));
	}

	set_function(output_value);
}

void VisualAccidentalNoise::_component_updated() {

	generate();
}

void VisualAccidentalNoise::_queue_update() {

	if (dirty) {
		return;
	}

	dirty = true;

	call_deferred("_update_noise");
}

void VisualAccidentalNoise::set_clamping_enabled(bool p_enable) {

	clamping_enabled = p_enable;
	emit_changed();
}

bool VisualAccidentalNoise::is_clamping_enabled() const {

	return clamping_enabled;
}

void VisualAccidentalNoise::set_clamp_low(double p_value) {

	clamp_low = p_value;
	emit_changed();
}

double VisualAccidentalNoise::get_clamp_low() const {

	return clamp_low;
}

void VisualAccidentalNoise::set_clamp_high(double p_value) {

	clamp_high = p_value;
	emit_changed();
}

double VisualAccidentalNoise::get_clamp_high() const {

	return clamp_high;
}

void VisualAccidentalNoise::_validate_property(PropertyInfo &property) const {

	AccidentalNoise::_validate_property(property);

	if (format == FORMAT_TEXTURE) {
		if (property.name.begins_with("clamp")) {
			// This will spoil color texture into grayscale, disallow it in editor at least
			property.usage = PROPERTY_USAGE_NOEDITOR;
		}
	}
}

void VisualAccidentalNoise::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_clamping_enabled", "enabled"), &VisualAccidentalNoise::set_clamping_enabled);
	ClassDB::bind_method(D_METHOD("is_clamping_enabled"), &VisualAccidentalNoise::is_clamping_enabled);

	ClassDB::bind_method(D_METHOD("set_clamp_low", "value"), &VisualAccidentalNoise::set_clamp_low);
	ClassDB::bind_method(D_METHOD("get_clamp_low"), &VisualAccidentalNoise::get_clamp_low);

	ClassDB::bind_method(D_METHOD("set_clamp_high", "value"), &VisualAccidentalNoise::set_clamp_high);
	ClassDB::bind_method(D_METHOD("get_clamp_high"), &VisualAccidentalNoise::get_clamp_high);

	// Clamping properties should be set before component is loaded
	ADD_GROUP("Clamp", "clamp_");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "clamp_output"), "set_clamping_enabled", "is_clamping_enabled");
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "clamp_low"), "set_clamp_low", "get_clamp_low");
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "clamp_high"), "set_clamp_high", "get_clamp_high");

	ClassDB::bind_method(D_METHOD("generate"), &VisualAccidentalNoise::generate);

	ClassDB::bind_method(D_METHOD("set_component", "component"), &VisualAccidentalNoise::set_component);
	ClassDB::bind_method(D_METHOD("get_component"), &VisualAccidentalNoise::get_component);

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "component", PROPERTY_HINT_RESOURCE_TYPE, "VisualAccidentalNoiseNodeComponent"), "set_component", "get_component");
	ADD_SIGNAL(MethodInfo("component_changed"));

	ClassDB::bind_method(D_METHOD("_queue_update"), &VisualAccidentalNoise::_queue_update);
	ClassDB::bind_method(D_METHOD("_update_noise"), &VisualAccidentalNoise::_update_noise);
	ClassDB::bind_method(D_METHOD("_component_updated"), &VisualAccidentalNoise::_component_updated);
}

void VisualAccidentalNoise::set_component(const Ref<VisualAccidentalNoiseNodeComponent> &p_component) {

	if (p_component.is_valid()) {

		if (component.is_valid() && component->is_connected("changed", this, "_component_updated")) {
			component->disconnect("changed", this, "_component_updated");
		}
		component = p_component;
		component->connect("changed", this, "_component_updated");

		generate();

		emit_signal("component_changed");
	}
}

Ref<VisualAccidentalNoiseNodeComponent> VisualAccidentalNoise::get_component() const {

	return component;
}

//////////////////
// Component node
//////////////////

VisualAccidentalNoiseNodeComponent::VisualAccidentalNoiseNodeComponent() {

	Ref<VisualAccidentalNoiseNodeOutput> output;
	output.instance();
	graph.nodes[NODE_ID_OUTPUT].node = output;
	graph.nodes[NODE_ID_OUTPUT].position = Vector2(400, 150);

	name = "component";
}

void VisualAccidentalNoiseNodeComponent::set_input_port_value(int p_port, const Variant &p_value) {

	int port = 0;

	for (Map<int, Node>::Element *E = graph.nodes.front(); E; E = E->next()) {
		Ref<VisualAccidentalNoiseNodeInput> input = E->get().node;
		if (input.is_valid()) {
			if (port == p_port) {
				return input->set_output_port_value(0, p_value);
			}
			++port;
		}
	}
}

int VisualAccidentalNoiseNodeComponent::get_input_port_count() const {

	int count = 0;

	for (Map<int, Node>::Element *E = graph.nodes.front(); E; E = E->next()) {
		Ref<VisualAccidentalNoiseNodeInput> input = E->get().node;
		if (input.is_valid()) {
			++count;
		}
	}
	return count;
}

VisualAccidentalNoiseNode::PortType VisualAccidentalNoiseNodeComponent::get_input_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeComponent::get_input_port_name(int p_port) const {

	String name;
	int port = 0;

	for (Map<int, Node>::Element *E = graph.nodes.front(); E; E = E->next()) {
		Ref<VisualAccidentalNoiseNodeInput> input = E->get().node;
		if (input.is_valid()) {
			if (port == p_port) {
				return input->get_input_name();
			}
			++port;
		}
	}
	return name;
}

int VisualAccidentalNoiseNodeComponent::get_output_port_count() const {

	return 1;
}

VisualAccidentalNoiseNode::PortType VisualAccidentalNoiseNodeComponent::get_output_port_type(int p_port) const {

	// Should always return index of the noise function evaluated
	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeComponent::get_output_port_name(int p_port) const {

	return "";
}

String VisualAccidentalNoiseNodeComponent::get_caption() const {

	return TTR("Component");
}

//////////////////
// Input node
//////////////////

int VisualAccidentalNoiseNodeInput::get_input_port_count() const {

	return 0;
}

VisualAccidentalNoiseNodeInput::PortType VisualAccidentalNoiseNodeInput::get_input_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeInput::get_input_port_name(int p_port) const {

	return String();
}

int VisualAccidentalNoiseNodeInput::get_output_port_count() const {

	return 1;
}

VisualAccidentalNoiseNodeInput::PortType VisualAccidentalNoiseNodeInput::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeInput::get_output_port_name(int p_port) const {

	return TTR("Index");
}

bool VisualAccidentalNoiseNodeInput::is_port_separator(int p_index) const {

	return false;
}

String VisualAccidentalNoiseNodeInput::get_caption() const {

	return TTR("Input");
}

void VisualAccidentalNoiseNodeInput::set_output_port_value(int p_port, const Variant &p_value) {

	output_value = p_value;
}

Variant VisualAccidentalNoiseNodeInput::get_output_port_value(int p_port) const {

	return output_value;
}

void VisualAccidentalNoiseNodeInput::set_input_name(const String &p_name) {

	input_name = p_name;
	emit_changed();
}

String VisualAccidentalNoiseNodeInput::get_input_name() const {

	return input_name;
}

void VisualAccidentalNoiseNodeInput::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_input_name", "name"), &VisualAccidentalNoiseNodeInput::set_input_name);
	ClassDB::bind_method(D_METHOD("get_input_name"), &VisualAccidentalNoiseNodeInput::get_input_name);

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "input_name"), "set_input_name", "get_input_name");
}

VisualAccidentalNoiseNodeInput::VisualAccidentalNoiseNodeInput() {

	input_name = String();
}

//////////////////
// Output node
//////////////////

int VisualAccidentalNoiseNodeOutput::get_input_port_count() const {

	return 1;
}

VisualAccidentalNoiseNodeOutput::PortType VisualAccidentalNoiseNodeOutput::get_input_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeOutput::get_input_port_name(int p_port) const {

	return TTR("Index");
}

int VisualAccidentalNoiseNodeOutput::get_output_port_count() const {

	return 0;
}

VisualAccidentalNoiseNodeOutput::PortType VisualAccidentalNoiseNodeOutput::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeOutput::get_output_port_name(int p_port) const {

	return String();
}

String VisualAccidentalNoiseNodeOutput::get_caption() const {

	return TTR("Output");
}

void VisualAccidentalNoiseNodeOutput::set_input_port_value(int p_port, const Variant &p_value) {

	output_value = p_value;
}

Variant VisualAccidentalNoiseNodeOutput::get_input_port_value(int p_port) const {

	return output_value;
}

VisualAccidentalNoiseNodeOutput::VisualAccidentalNoiseNodeOutput() {

	set_input_port_default_value(0, 0);
}
