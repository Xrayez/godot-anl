#include "visual_anl_noise_nodes.h"

////////////// Scalar

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

////////////// Simplex Basis

String VisualAnlNoiseNodeSimplexBasis::get_caption() const {

	return "SimplexBasis";
}

int VisualAnlNoiseNodeSimplexBasis::get_input_port_count() const {

	return 1;
}

void VisualAnlNoiseNodeSimplexBasis::set_input_port_value(int p_port, const Variant &p_value) {

	seed = p_value;
}

Variant VisualAnlNoiseNodeSimplexBasis::get_input_port_value(int p_port) const {

	return seed;
}

VisualAnlNoiseNodeSimplexBasis::PortType VisualAnlNoiseNodeSimplexBasis::get_input_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAnlNoiseNodeSimplexBasis::get_input_port_name(int p_port) const {

	return "Seed";
}

int VisualAnlNoiseNodeSimplexBasis::get_output_port_count() const {

	return 1;
}

VisualAnlNoiseNodeSimplexBasis::PortType VisualAnlNoiseNodeSimplexBasis::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAnlNoiseNodeSimplexBasis::get_output_port_name(int p_port) const {

	return "";
}

void VisualAnlNoiseNodeSimplexBasis::set_seed(Index p_seed) {

	seed = p_seed;
	emit_changed();
}

Index VisualAnlNoiseNodeSimplexBasis::get_seed() const {

	return seed;
}

Vector<StringName> VisualAnlNoiseNodeSimplexBasis::get_editable_properties() const {

	Vector<StringName> props;

	// props.push_back("seed");

	return props;
}

void VisualAnlNoiseNodeSimplexBasis::evaluate(Ref<VisualAnlNoise> noise) {

	output_value = noise->simplex_basis(seed);
}

void VisualAnlNoiseNodeSimplexBasis::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_seed", "value"), &VisualAnlNoiseNodeSimplexBasis::set_seed);
	ClassDB::bind_method(D_METHOD("get_seed"), &VisualAnlNoiseNodeSimplexBasis::get_seed);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "seed"), "set_seed", "get_seed");
}

VisualAnlNoiseNodeSimplexBasis::VisualAnlNoiseNodeSimplexBasis() {

	seed = 0;
}

////////////// Expression

String VisualAnlNoiseNodeExpression::get_caption() const {

	return "Expression";
}

int VisualAnlNoiseNodeExpression::get_input_port_count() const {

	return 0;
}

void VisualAnlNoiseNodeExpression::set_input_port_value(int p_port, const Variant &p_value) {

	expression = p_value;
}

Variant VisualAnlNoiseNodeExpression::get_input_port_value(int p_port) const {

	return expression;
}

VisualAnlNoiseNodeExpression::PortType VisualAnlNoiseNodeExpression::get_input_port_type(int p_port) const {

	return PORT_TYPE_SCALAR;
}

String VisualAnlNoiseNodeExpression::get_input_port_name(int p_port) const {

	return "";
}

int VisualAnlNoiseNodeExpression::get_output_port_count() const {

	return 1;
}

VisualAnlNoiseNodeExpression::PortType VisualAnlNoiseNodeExpression::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAnlNoiseNodeExpression::get_output_port_name(int p_port) const {

	return "";
}

void VisualAnlNoiseNodeExpression::set_expression(const String &p_expression) {

	expression = p_expression;
	emit_changed();
}

String VisualAnlNoiseNodeExpression::get_expression() const {

	return expression;
}

Vector<StringName> VisualAnlNoiseNodeExpression::get_editable_properties() const {

	Vector<StringName> props;

	props.push_back("expression");

	return props;
}

void VisualAnlNoiseNodeExpression::evaluate(Ref<VisualAnlNoise> noise) {

	output_value = noise->evaluate(expression);
}

void VisualAnlNoiseNodeExpression::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_expression", "value"), &VisualAnlNoiseNodeExpression::set_expression);
	ClassDB::bind_method(D_METHOD("get_expression"), &VisualAnlNoiseNodeExpression::get_expression);

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "expression"), "set_expression", "get_expression");
}

VisualAnlNoiseNodeExpression::VisualAnlNoiseNodeExpression() {

	expression = "";
}
