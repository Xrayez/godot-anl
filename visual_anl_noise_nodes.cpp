#include "visual_anl_noise_nodes.h"

////////////// Scalar noise

String VisualAnlNoiseNodeScalar::get_caption() const {

	return "Scalar";
}

int VisualAnlNoiseNodeScalar::get_input_port_count() const {

	return 0;
}

void VisualAnlNoiseNodeScalar::set_input_port_value(int p_port, const Variant &p_value) {

	constant = p_value;
}

Variant VisualAnlNoiseNodeScalar::get_input_port_value(int p_port) const {

	return constant;
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
	return "";
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

void VisualAnlNoiseNodeScalar::evaluate(Ref<VisualAnlNoise> noise) {

	switch(type) {

		case SCALAR_CONSTANT:
			output_value = noise->constant(constant);

		case SCALAR_PI:
			output_value = noise->pi();

		case SCALAR_E:
			output_value = noise->e();

		case SCALAR_ONE:
			output_value = noise->one();

		case SCALAR_ZERO:
			output_value = noise->zero();

		case SCALAR_POINT5:
			output_value = noise->point5();

		case SCALAR_SQRT2:
			output_value = noise->sqrt2();
	}
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
