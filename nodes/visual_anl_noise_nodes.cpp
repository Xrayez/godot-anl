#include "visual_anl_noise_nodes.h"

////////////// Constant

String VisualAnlNoiseNodeConstant::get_caption() const {

	return "Constant";
}

int VisualAnlNoiseNodeConstant::get_input_port_count() const {

	return 0;
}

VisualAnlNoiseNodeConstant::PortType VisualAnlNoiseNodeConstant::get_input_port_type(int p_port) const {

	return PORT_TYPE_SCALAR;
}

String VisualAnlNoiseNodeConstant::get_input_port_name(int p_port) const {

	return String();
}

int VisualAnlNoiseNodeConstant::get_output_port_count() const {

	return 1;
}

VisualAnlNoiseNodeConstant::PortType VisualAnlNoiseNodeConstant::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAnlNoiseNodeConstant::get_output_port_name(int p_port) const {
	return ""; //no output port means the editor will be used as port
}

void VisualAnlNoiseNodeConstant::set_constant(float p_value) {

	constant = p_value;
	emit_changed();
}

float VisualAnlNoiseNodeConstant::get_constant() const {

	return constant;
}

Vector<StringName> VisualAnlNoiseNodeConstant::get_editable_properties() const {
	Vector<StringName> props;
	props.push_back("constant");
	return props;
}

void VisualAnlNoiseNodeConstant::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_constant", "value"), &VisualAnlNoiseNodeConstant::set_constant);
	ClassDB::bind_method(D_METHOD("get_constant"), &VisualAnlNoiseNodeConstant::get_constant);

	ADD_PROPERTY(PropertyInfo(Variant::REAL, "constant"), "set_constant", "get_constant");
}

VisualAnlNoiseNodeConstant::VisualAnlNoiseNodeConstant() {

	constant = 0.0;
}
