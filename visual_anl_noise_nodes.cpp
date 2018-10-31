#include "visual_anl_noise_nodes.h"

////////////// Scalar noise

String VisualAnlNoiseNodeScalar::get_caption() const {

	return "Scalar";
}

int VisualAnlNoiseNodeScalar::get_input_port_count() const {

	return 0;
}

VisualAnlNoiseNodeScalar::PortType VisualAnlNoiseNodeScalar::get_input_port_type(int p_port) const {

	return PORT_TYPE_SCALAR;
}

String VisualAnlNoiseNodeScalar::get_input_port_name(int p_port) const {

	return String();
}

int VisualAnlNoiseNodeScalar::get_output_port_count() const {

	return 1;
}

VisualAnlNoiseNodeScalar::PortType VisualAnlNoiseNodeScalar::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAnlNoiseNodeScalar::get_output_port_name(int p_port) const {
	return ""; //no output port means the editor will be used as port
}

void VisualAnlNoiseNodeScalar::set_constant(real_t p_value) {

	constant = p_value;
	emit_changed();
}

real_t VisualAnlNoiseNodeScalar::get_constant() const {

	return constant;
}

void VisualAnlNoiseNodeScalar::set_type(ScalarType p_type) {

	type = p_type;
	emit_changed();
}

VisualAnlNoiseNodeScalar::ScalarType VisualAnlNoiseNodeScalar::get_type() const {

	return type;
}

Vector<StringName> VisualAnlNoiseNodeScalar::get_editable_properties() const {

	Vector<StringName> props;

	props.push_back("type");

	if(type == SCALAR_CONSTANT) {
		props.push_back("constant");
	}

	return props;
}

void VisualAnlNoiseNodeScalar::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_type", "type"), &VisualAnlNoiseNodeScalar::set_type);
	ClassDB::bind_method(D_METHOD("get_type"), &VisualAnlNoiseNodeScalar::get_type);

	ClassDB::bind_method(D_METHOD("set_constant", "value"), &VisualAnlNoiseNodeScalar::set_constant);
	ClassDB::bind_method(D_METHOD("get_constant"), &VisualAnlNoiseNodeScalar::get_constant);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "type", PROPERTY_HINT_ENUM, "Constant,Pi,E,One,Zero,Point5,Sqrt2"), "set_type", "get_type");
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "constant"), "set_constant", "get_constant");

	BIND_ENUM_CONSTANT(SCALAR_CONSTANT);
	BIND_ENUM_CONSTANT(SCALAR_PI);
	BIND_ENUM_CONSTANT(SCALAR_E);
	BIND_ENUM_CONSTANT(SCALAR_ONE);
	BIND_ENUM_CONSTANT(SCALAR_ZERO);
	BIND_ENUM_CONSTANT(SCALAR_POINT5);
	BIND_ENUM_CONSTANT(SCALAR_SQRT2);
}

VisualAnlNoiseNodeScalar::VisualAnlNoiseNodeScalar() {

	type = SCALAR_CONSTANT;
	constant = 0.0;
	// set_input_port_default_value(0, 0.0);
}
