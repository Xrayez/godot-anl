#ifndef VISUAL_ANL_NOISE_H
#define VISUAL_ANL_NOISE_H

#include "anl_noise.h"

struct Axis {
	enum AxisType {
		AXIS_DOMAIN,
		AXIS_X,
		AXIS_Y,
		AXIS_Z,
		AXIS_W,
		AXIS_U,
		AXIS_V,
	};

	AxisType type;

	String as_alpha() const {
		switch (type) {
			case AXIS_DOMAIN: return "";
			case AXIS_X: return "x";
			case AXIS_Y: return "y";
			case AXIS_Z: return "z";
			case AXIS_W: return "w";
			case AXIS_U: return "u";
			case AXIS_V: return "v";
		}
		return "";
	}

	_FORCE_INLINE_ static String get_hints() {
		return "Domain,X,Y,Z,W,U,V";
	}

	Axis() { type = AXIS_DOMAIN; }
};

VARIANT_ENUM_CAST(Axis::AxisType);


class VisualAnlNoiseNode;
class VisualAnlNoiseNodeComponent;

class VisualAnlNoise : public AnlNoise {
    GDCLASS(VisualAnlNoise, AnlNoise);

	Ref<VisualAnlNoiseNodeComponent> component; // default, tree root

	void _update_noise();
	void _queue_update();
	void _component_updated();

	volatile mutable bool dirty;

protected:
	static void _bind_methods();

public:
	void generate();

	void set_component(const Ref<VisualAnlNoiseNodeComponent> &p_component);
	Ref<VisualAnlNoiseNodeComponent> get_component() const;

	VisualAnlNoise();
};


class VisualAnlNoiseNode : public Resource {
	GDCLASS(VisualAnlNoiseNode, Resource)

	int port_preview;

	Map<int, Variant> default_input_values;

	Array _get_default_input_values() const;
	void _set_default_input_values(const Array &p_values);

protected:
	Variant output_value;

	static void _bind_methods();

public:
	enum PortType {
		PORT_TYPE_SCALAR,
		PORT_TYPE_INDEX,
	};

	virtual String get_caption() const = 0;

	virtual int get_input_port_count() const = 0;
	virtual PortType get_input_port_type(int p_port) const = 0;
	virtual String get_input_port_name(int p_port) const = 0;

	virtual void set_input_port_value(int p_port, const Variant &p_value);
	virtual Variant get_input_port_value(int p_port) const;

	void set_input_port_default_value(int p_port, const Variant &p_value);
	Variant get_input_port_default_value(int p_port) const; // if NIL (default if node does not set anything) is returned, it means no default value is wanted if disconnected, thus no input var must be supplied (empty string will be supplied)

	virtual int get_output_port_count() const = 0;
	virtual PortType get_output_port_type(int p_port) const = 0;
	virtual String get_output_port_name(int p_port) const = 0;

	virtual void set_output_port_value(int p_port, const Variant &p_value);
	virtual Variant get_output_port_value(int p_port) const;

	void set_output_port_for_preview(int p_index);
	int get_output_port_for_preview() const;

	virtual bool is_port_separator(int p_index) const;

	virtual Vector<StringName> get_editable_properties() const;

	virtual String get_warning() const;

	virtual void evaluate(Ref<VisualAnlNoise> noise);

	VisualAnlNoiseNode();
};

VARIANT_ENUM_CAST(VisualAnlNoiseNode::PortType);


class VisualAnlNoiseNodeComponent : public VisualAnlNoiseNode {
	GDCLASS(VisualAnlNoiseNodeComponent, VisualAnlNoiseNode)

	friend class VisualAnlNoise;

public:
    struct Connection {
		int from_node;
		int from_port;
		int to_node;
		int to_port;
	};

private:
	String name;

	struct Node {
		Ref<VisualAnlNoiseNode> node;
		Vector2 position;
	};

    struct Graph {
		Map<int, Node> nodes;
		List<Connection> connections;
	} graph;

	union ConnectionKey {

		struct {
			uint64_t node : 32;
			uint64_t port : 32;
		};
		uint64_t key;
		bool operator<(const ConnectionKey &p_key) const {
			return key < p_key.key;
		}
	};

    Vector2 graph_offset;

	volatile mutable bool dirty;

    Array _get_node_connections() const;

	void _queue_update();
	void _notify_changed();

protected:
	static void _bind_methods();

	bool _set(const StringName &p_name, const Variant &p_value);
	bool _get(const StringName &p_name, Variant &r_ret) const;
	void _get_property_list(List<PropertyInfo> *p_list) const;

public:
	using Connections = VMap<ConnectionKey, const List<Connection>::Element *>;

	enum {
		NODE_ID_INVALID = -1,
		NODE_ID_OUTPUT = 0,
	};

	void set_component_name(const String &p_name);
	String get_component_name() const;

    void add_node(const Ref<VisualAnlNoiseNode> &p_node, const Vector2 &p_position, int p_id);
	void set_node_position(int p_id, const Vector2 &p_position);

	Vector2 get_node_position(int p_id) const;
	Ref<VisualAnlNoiseNode> get_node(int p_id) const;

	bool has_node(int p_id) const;

	Vector<int> get_node_list() const;
	int get_valid_node_id() const;

	int find_node_id(const Ref<VisualAnlNoiseNode> &p_node) const;
	void remove_node(int p_id);

	void evaluate_node(int p_id, Ref<VisualAnlNoise> noise, Connections &input_connections, Connections &output_connections, Set<int> &processed);

	bool is_node_connection(int p_from_node, int p_from_port, int p_to_node, int p_to_port) const;
	bool can_connect_nodes(int p_from_node, int p_from_port, int p_to_node, int p_to_port) const;
	Error connect_nodes(int p_from_node, int p_from_port, int p_to_node, int p_to_port);
	void disconnect_nodes(int p_from_node, int p_from_port, int p_to_node, int p_to_port);

	void get_node_connections(List<Connection> *r_connections) const;

	void set_graph_offset(const Vector2 &p_offset);
	Vector2 get_graph_offset() const;

	// String generate_preview_noise(int p_node, int p_port) const;

    VisualAnlNoiseNodeComponent();

public:
	virtual String get_caption() const;

	virtual void set_input_port_value(int p_port, const Variant &p_value);

	virtual int get_input_port_count() const;
	virtual PortType get_input_port_type(int p_port) const;
	virtual String get_input_port_name(int p_port) const;

	virtual int get_output_port_count() const;
	virtual PortType get_output_port_type(int p_port) const;
	virtual String get_output_port_name(int p_port) const;

	virtual void evaluate(Ref<VisualAnlNoise> p_noise);
};


class VisualAnlNoiseNodeInput : public VisualAnlNoiseNode {
	GDCLASS(VisualAnlNoiseNodeInput, VisualAnlNoiseNode)

private:
	String input_name;

protected:
	static void _bind_methods();

public:
	friend class VisualAnlNoise;

	virtual int get_input_port_count() const;
	virtual PortType get_input_port_type(int p_port) const;
	virtual String get_input_port_name(int p_port) const;

	virtual int get_output_port_count() const;
	virtual PortType get_output_port_type(int p_port) const;
	virtual String get_output_port_name(int p_port) const;

	virtual void set_output_port_value(int p_port, const Variant &p_value);
	virtual Variant get_output_port_value(int p_port) const;

	virtual bool is_port_separator(int p_index) const;

	virtual String get_caption() const;

public:
	void set_input_name(const String &p_input_name);
	String get_input_name() const;

	VisualAnlNoiseNodeInput();
};


class VisualAnlNoiseNodeOutput : public VisualAnlNoiseNode {
	GDCLASS(VisualAnlNoiseNodeOutput, VisualAnlNoiseNode)

public:
	friend class VisualAnlNoise;

public:
	virtual void set_input_port_value(int p_port, const Variant &p_value);
	virtual Variant get_input_port_value(int p_port) const;

	virtual int get_input_port_count() const;
	virtual PortType get_input_port_type(int p_port) const;
	virtual String get_input_port_name(int p_port) const;

	Variant get_input_port_default_value(int p_port) const;

	virtual int get_output_port_count() const;
	virtual PortType get_output_port_type(int p_port) const;
	virtual String get_output_port_name(int p_port) const;

	virtual void set_output_port_value(int p_port, const Variant &p_value);
	virtual Variant get_output_port_value(int p_port) const;

	virtual bool is_port_separator(int p_index) const;

	virtual String get_caption() const;

	VisualAnlNoiseNodeOutput();
};

#endif
