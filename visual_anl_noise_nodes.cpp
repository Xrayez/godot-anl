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
			break;

		case SCALAR_PI:
			output_value = noise->pi();
			break;

		case SCALAR_E:
			output_value = noise->e();
			break;

		case SCALAR_ONE:
			output_value = noise->one();
			break;

		case SCALAR_ZERO:
			output_value = noise->zero();
			break;

		case SCALAR_POINT5:
			output_value = noise->point5();
			break;

		case SCALAR_SQRT2:
			output_value = noise->sqrt2();
			break;
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
}

////////////// ScalarOp

String VisualAnlNoiseNodeScalarOp::get_caption() const {

	return "ScalarOp";
}

int VisualAnlNoiseNodeScalarOp::get_input_port_count() const {

	return 2;
}

void VisualAnlNoiseNodeScalarOp::set_input_port_value(int p_port, const Variant &p_value) {

	p_port == 0 ? (a = p_value) : (b = p_value);
}

Variant VisualAnlNoiseNodeScalarOp::get_input_port_value(int p_port) const {

	return p_port == 0 ? a : b;
}

VisualAnlNoiseNodeScalarOp::PortType VisualAnlNoiseNodeScalarOp::get_input_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAnlNoiseNodeScalarOp::get_input_port_name(int p_port) const {

	return p_port == 0 ? "a" : "b";
}

int VisualAnlNoiseNodeScalarOp::get_output_port_count() const {

	return 1;
}

VisualAnlNoiseNodeScalarOp::PortType VisualAnlNoiseNodeScalarOp::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAnlNoiseNodeScalarOp::get_output_port_name(int p_port) const {
	return "";
}

void VisualAnlNoiseNodeScalarOp::set_operator(Operator p_op) {

	op = p_op;
	emit_changed();
}

VisualAnlNoiseNodeScalarOp::Operator VisualAnlNoiseNodeScalarOp::get_operator() const {

	return op;
}

Vector<StringName> VisualAnlNoiseNodeScalarOp::get_editable_properties() const {

	Vector<StringName> props;
	props.push_back("operator");

	return props;
}

void VisualAnlNoiseNodeScalarOp::evaluate(Ref<VisualAnlNoise> noise) {

	switch(op) {

		case OP_ADD:
			output_value = noise->add(a, b);
			break;

		case OP_SUB:
			output_value = noise->subtract(a, b);
			break;

		case OP_MUL:
			output_value = noise->multiply(a, b);
			break;

		case OP_DIV:
			output_value = noise->divide(a, b);
			break;

		case OP_POW:
			output_value = noise->pow(a, b);
			break;

		case OP_MAX:
			output_value = noise->maximum(a, b);
			break;

		case OP_MIN:
			output_value = noise->minimum(a, b);
			break;
	}
}

void VisualAnlNoiseNodeScalarOp::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_operator", "operator"), &VisualAnlNoiseNodeScalarOp::set_operator);
	ClassDB::bind_method(D_METHOD("get_operator"), &VisualAnlNoiseNodeScalarOp::get_operator);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "operator", PROPERTY_HINT_ENUM, "Add,Sub,Multiply,Divide,Power,Max,Min"), "set_operator", "get_operator");

	BIND_ENUM_CONSTANT(OP_ADD);
	BIND_ENUM_CONSTANT(OP_SUB);
	BIND_ENUM_CONSTANT(OP_MUL);
	BIND_ENUM_CONSTANT(OP_DIV);
	BIND_ENUM_CONSTANT(OP_POW);
	BIND_ENUM_CONSTANT(OP_MAX);
	BIND_ENUM_CONSTANT(OP_MIN);
}

VisualAnlNoiseNodeScalarOp::VisualAnlNoiseNodeScalarOp() {

	op = OP_ADD;
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
	return props;
}

void VisualAnlNoiseNodeExpression::evaluate(Ref<VisualAnlNoise> noise) {

	output_value = noise->evaluate(expression);
}

void VisualAnlNoiseNodeExpression::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_expression", "value"), &VisualAnlNoiseNodeExpression::set_expression);
	ClassDB::bind_method(D_METHOD("get_expression"), &VisualAnlNoiseNodeExpression::get_expression);

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "expression", PROPERTY_HINT_MULTILINE_TEXT), "set_expression", "get_expression");
}

VisualAnlNoiseNodeExpression::VisualAnlNoiseNodeExpression() {

	expression = "";
}

//============ Transform

////////////// Translate

const String VisualAnlNoiseNodeTranslate::method = "translate";

String VisualAnlNoiseNodeTranslate::get_caption() const {

	return "Translate";
}

int VisualAnlNoiseNodeTranslate::get_input_port_count() const {

	return 2;
}

void VisualAnlNoiseNodeTranslate::set_input_port_value(int p_port, const Variant &p_value) {

	p_port == 0 ? source = p_value : by = p_value;
}

Variant VisualAnlNoiseNodeTranslate::get_input_port_value(int p_port) const {

	return p_port == 0 ? source : by;
}

VisualAnlNoiseNodeTranslate::PortType VisualAnlNoiseNodeTranslate::get_input_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAnlNoiseNodeTranslate::get_input_port_name(int p_port) const {

	return p_port == 0 ? "source" : "by";
}

int VisualAnlNoiseNodeTranslate::get_output_port_count() const {

	return 1;
}

VisualAnlNoiseNodeTranslate::PortType VisualAnlNoiseNodeTranslate::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAnlNoiseNodeTranslate::get_output_port_name(int p_port) const {
	return "";
}

void VisualAnlNoiseNodeTranslate::set_axis(Axis::AxisType p_axis) {

	axis.type = p_axis;
	emit_changed();
}

Axis::AxisType VisualAnlNoiseNodeTranslate::get_axis() const {

	return axis.type;
}

Vector<StringName> VisualAnlNoiseNodeTranslate::get_editable_properties() const {

	Vector<StringName> props;

	props.push_back("axis");

	return props;
}

void VisualAnlNoiseNodeTranslate::evaluate(Ref<VisualAnlNoise> noise) {

	String m = method;
	if (axis.type != Axis::AXIS_DOMAIN) {
		m = method + "_" + axis.as_alpha();
	}
	output_value = noise->call(m, source, by);
}

void VisualAnlNoiseNodeTranslate::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_axis", "axis"), &VisualAnlNoiseNodeTranslate::set_axis);
	ClassDB::bind_method(D_METHOD("get_axis"), &VisualAnlNoiseNodeTranslate::get_axis);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "axis", PROPERTY_HINT_ENUM, Axis::get_hints()), "set_axis", "get_axis");
}

VisualAnlNoiseNodeTranslate::VisualAnlNoiseNodeTranslate() {

	source = 0;
	by = 0;
}

////////////// Scale

const String VisualAnlNoiseNodeScale::method = "scale";

String VisualAnlNoiseNodeScale::get_caption() const {

	return "Scale";
}

int VisualAnlNoiseNodeScale::get_input_port_count() const {

	return 2;
}

void VisualAnlNoiseNodeScale::set_input_port_value(int p_port, const Variant &p_value) {

	p_port == 0 ? source = p_value : by = p_value;
}

Variant VisualAnlNoiseNodeScale::get_input_port_value(int p_port) const {

	return p_port == 0 ? source : by;
}

VisualAnlNoiseNodeScale::PortType VisualAnlNoiseNodeScale::get_input_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAnlNoiseNodeScale::get_input_port_name(int p_port) const {

	return p_port == 0 ? "source" : "by";
}

int VisualAnlNoiseNodeScale::get_output_port_count() const {

	return 1;
}

VisualAnlNoiseNodeScale::PortType VisualAnlNoiseNodeScale::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAnlNoiseNodeScale::get_output_port_name(int p_port) const {
	return "";
}

void VisualAnlNoiseNodeScale::set_axis(Axis::AxisType p_axis) {

	axis.type = p_axis;
	emit_changed();
}

Axis::AxisType VisualAnlNoiseNodeScale::get_axis() const {

	return axis.type;
}

Vector<StringName> VisualAnlNoiseNodeScale::get_editable_properties() const {

	Vector<StringName> props;

	props.push_back("axis");

	return props;
}

void VisualAnlNoiseNodeScale::evaluate(Ref<VisualAnlNoise> noise) {

	String m = method;
	if (axis.type != Axis::AXIS_DOMAIN) {
		m = method + "_" + axis.as_alpha();
	}
	output_value = noise->call(m, source, by);
}

void VisualAnlNoiseNodeScale::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_axis", "axis"), &VisualAnlNoiseNodeScale::set_axis);
	ClassDB::bind_method(D_METHOD("get_axis"), &VisualAnlNoiseNodeScale::get_axis);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "axis", PROPERTY_HINT_ENUM, Axis::get_hints()), "set_axis", "get_axis");
}

VisualAnlNoiseNodeScale::VisualAnlNoiseNodeScale() {

	source = 0;
	by = 0;
}

////////////// Rotate

String VisualAnlNoiseNodeRotate::get_caption() const {

	return "Rotate";
}

int VisualAnlNoiseNodeRotate::get_input_port_count() const {

	return 5;
}

void VisualAnlNoiseNodeRotate::set_input_port_value(int p_port, const Variant &p_value) {

	switch (p_port) {
		case 0: source = p_value; break;
		case 1: angle = p_value; break;
		case 2: ax = p_value; break;
		case 3: ay = p_value; break;
		case 4: az = p_value; break;
	}
}

Variant VisualAnlNoiseNodeRotate::get_input_port_value(int p_port) const {

	switch (p_port) {
		case 0: return source;
		case 1: return angle;
		case 2: return ax;
		case 3: return ay;
		case 4: return az;
	}
	return Variant();
}

VisualAnlNoiseNodeRotate::PortType VisualAnlNoiseNodeRotate::get_input_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAnlNoiseNodeRotate::get_input_port_name(int p_port) const {

	switch (p_port) {
		case 0: return "source";
		case 1: return "angle";
		case 2: return "ax";
		case 3: return "ay";
		case 4: return "az";
	}
	return "";
}

int VisualAnlNoiseNodeRotate::get_output_port_count() const {

	return 1;
}

VisualAnlNoiseNodeRotate::PortType VisualAnlNoiseNodeRotate::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAnlNoiseNodeRotate::get_output_port_name(int p_port) const {
	return "";
}

void VisualAnlNoiseNodeRotate::evaluate(Ref<VisualAnlNoise> noise) {

	output_value = noise->rotate(source, angle, ax, ay, az);
}

void VisualAnlNoiseNodeRotate::_bind_methods() {

}

VisualAnlNoiseNodeRotate::VisualAnlNoiseNodeRotate() {

	source = 0;
	angle = 0;
	ax = ay = az = 0;
}
