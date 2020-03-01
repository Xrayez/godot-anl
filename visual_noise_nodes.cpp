#include "visual_noise_nodes.h"

////////////// Scalar

String VisualAccidentalNoiseNodeScalar::get_caption() const {

	return "Scalar";
}

int VisualAccidentalNoiseNodeScalar::get_input_port_count() const {

	return 0;
}

VisualAccidentalNoiseNodeScalar::PortType VisualAccidentalNoiseNodeScalar::get_input_port_type(int p_port) const {

	return PORT_TYPE_SCALAR;
}

String VisualAccidentalNoiseNodeScalar::get_input_port_name(int p_port) const {

	return String();
}

int VisualAccidentalNoiseNodeScalar::get_output_port_count() const {

	return 1;
}

VisualAccidentalNoiseNodeScalar::PortType VisualAccidentalNoiseNodeScalar::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeScalar::get_output_port_name(int p_port) const {
	return "";
}

void VisualAccidentalNoiseNodeScalar::set_constant(real_t p_value) {

	constant = p_value;
	emit_changed();
}

real_t VisualAccidentalNoiseNodeScalar::get_constant() const {

	return constant;
}

void VisualAccidentalNoiseNodeScalar::set_type(ScalarType p_type) {

	type = p_type;
	emit_changed();
}

VisualAccidentalNoiseNodeScalar::ScalarType VisualAccidentalNoiseNodeScalar::get_type() const {

	return type;
}

Vector<StringName> VisualAccidentalNoiseNodeScalar::get_editable_properties() const {

	Vector<StringName> props;

	props.push_back("type");

	if (type == SCALAR_CONSTANT) {
		props.push_back("constant");
	}

	return props;
}

void VisualAccidentalNoiseNodeScalar::evaluate(Ref<VisualAccidentalNoise> noise) {

	switch (type) {

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

void VisualAccidentalNoiseNodeScalar::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_type", "type"), &VisualAccidentalNoiseNodeScalar::set_type);
	ClassDB::bind_method(D_METHOD("get_type"), &VisualAccidentalNoiseNodeScalar::get_type);

	ClassDB::bind_method(D_METHOD("set_constant", "value"), &VisualAccidentalNoiseNodeScalar::set_constant);
	ClassDB::bind_method(D_METHOD("get_constant"), &VisualAccidentalNoiseNodeScalar::get_constant);

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

VisualAccidentalNoiseNodeScalar::VisualAccidentalNoiseNodeScalar() {

	type = SCALAR_CONSTANT;
	constant = 0.0;
}

////////////// Seed

String VisualAccidentalNoiseNodeSeed::get_caption() const {

	return "Seed";
}

int VisualAccidentalNoiseNodeSeed::get_input_port_count() const {

	return 0;
}

VisualAccidentalNoiseNodeSeed::PortType VisualAccidentalNoiseNodeSeed::get_input_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeSeed::get_input_port_name(int p_port) const {

	return String();
}

int VisualAccidentalNoiseNodeSeed::get_output_port_count() const {

	return 1;
}

VisualAccidentalNoiseNodeSeed::PortType VisualAccidentalNoiseNodeSeed::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeSeed::get_output_port_name(int p_port) const {
	return "";
}

void VisualAccidentalNoiseNodeSeed::set_seed(unsigned int p_value) {

	seed = p_value;
	emit_changed();
}

unsigned int VisualAccidentalNoiseNodeSeed::get_seed() const {

	return seed;
}

Vector<StringName> VisualAccidentalNoiseNodeSeed::get_editable_properties() const {

	Vector<StringName> props;

	props.push_back("seed");

	return props;
}

void VisualAccidentalNoiseNodeSeed::evaluate(Ref<VisualAccidentalNoise> noise) {

	output_value = noise->seed(seed);
}

void VisualAccidentalNoiseNodeSeed::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_seed", "seed"), &VisualAccidentalNoiseNodeSeed::set_seed);
	ClassDB::bind_method(D_METHOD("get_seed"), &VisualAccidentalNoiseNodeSeed::get_seed);

	ADD_PROPERTY(PropertyInfo(Variant::REAL, "seed"), "set_seed", "get_seed"); // REAL: hack for editing
}

VisualAccidentalNoiseNodeSeed::VisualAccidentalNoiseNodeSeed() {

	seed = 0;
}

////////////// Seeder

String VisualAccidentalNoiseNodeSeeder::get_caption() const {

	return "Seeder";
}

int VisualAccidentalNoiseNodeSeeder::get_input_port_count() const {

	return 2;
}

void VisualAccidentalNoiseNodeSeeder::set_input_port_value(int p_port, const Variant &p_value) {

	p_port == 0 ? (seed = p_value) : (input = p_value);
}

Variant VisualAccidentalNoiseNodeSeeder::get_input_port_value(int p_port) const {

	return p_port == 0 ? seed : input;
}

VisualAccidentalNoiseNodeSeeder::PortType VisualAccidentalNoiseNodeSeeder::get_input_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeSeeder::get_input_port_name(int p_port) const {

	return p_port == 0 ? "seed" : "input";
}

int VisualAccidentalNoiseNodeSeeder::get_output_port_count() const {

	return 1;
}

VisualAccidentalNoiseNodeSeeder::PortType VisualAccidentalNoiseNodeSeeder::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeSeeder::get_output_port_name(int p_port) const {
	return "";
}

void VisualAccidentalNoiseNodeSeeder::evaluate(Ref<VisualAccidentalNoise> noise) {

	output_value = noise->seeder(seed, input);
}

void VisualAccidentalNoiseNodeSeeder::_bind_methods() {
}

VisualAccidentalNoiseNodeSeeder::VisualAccidentalNoiseNodeSeeder() {

	set_input_port_default_value(0, 0);
	set_input_port_default_value(1, 0);

	seed = 0;
	input = 0;
}

////////////// ScalarOp

String VisualAccidentalNoiseNodeScalarOp::get_caption() const {

	return "ScalarOp";
}

int VisualAccidentalNoiseNodeScalarOp::get_input_port_count() const {

	return 2;
}

void VisualAccidentalNoiseNodeScalarOp::set_input_port_value(int p_port, const Variant &p_value) {

	p_port == 0 ? (a = p_value) : (b = p_value);
}

Variant VisualAccidentalNoiseNodeScalarOp::get_input_port_value(int p_port) const {

	return p_port == 0 ? a : b;
}

VisualAccidentalNoiseNodeScalarOp::PortType VisualAccidentalNoiseNodeScalarOp::get_input_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeScalarOp::get_input_port_name(int p_port) const {

	return p_port == 0 ? "a" : "b";
}

int VisualAccidentalNoiseNodeScalarOp::get_output_port_count() const {

	return 1;
}

VisualAccidentalNoiseNodeScalarOp::PortType VisualAccidentalNoiseNodeScalarOp::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeScalarOp::get_output_port_name(int p_port) const {
	return "";
}

void VisualAccidentalNoiseNodeScalarOp::set_operator(Operator p_op) {

	op = p_op;
	emit_changed();
}

VisualAccidentalNoiseNodeScalarOp::Operator VisualAccidentalNoiseNodeScalarOp::get_operator() const {

	return op;
}

Vector<StringName> VisualAccidentalNoiseNodeScalarOp::get_editable_properties() const {

	Vector<StringName> props;
	props.push_back("operator");

	return props;
}

void VisualAccidentalNoiseNodeScalarOp::evaluate(Ref<VisualAccidentalNoise> noise) {

	switch (op) {

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

		case OP_BIAS:
			output_value = noise->bias(a, b);
			break;

		case OP_GAIN:
			output_value = noise->gain(a, b);
			break;
	}
}

void VisualAccidentalNoiseNodeScalarOp::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_operator", "operator"), &VisualAccidentalNoiseNodeScalarOp::set_operator);
	ClassDB::bind_method(D_METHOD("get_operator"), &VisualAccidentalNoiseNodeScalarOp::get_operator);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "operator", PROPERTY_HINT_ENUM, "Add,Sub,Multiply,Divide,Power,Max,Min,Bias,Gain"), "set_operator", "get_operator");

	BIND_ENUM_CONSTANT(OP_ADD);
	BIND_ENUM_CONSTANT(OP_SUB);
	BIND_ENUM_CONSTANT(OP_MUL);
	BIND_ENUM_CONSTANT(OP_DIV);
	BIND_ENUM_CONSTANT(OP_POW);
	BIND_ENUM_CONSTANT(OP_MAX);
	BIND_ENUM_CONSTANT(OP_MIN);
	BIND_ENUM_CONSTANT(OP_BIAS);
	BIND_ENUM_CONSTANT(OP_GAIN);
}

VisualAccidentalNoiseNodeScalarOp::VisualAccidentalNoiseNodeScalarOp() {

	set_input_port_default_value(0, 0);
	set_input_port_default_value(1, 0);

	a = b = 0;
	op = OP_ADD;
}

////////////// ScalarFunc

String VisualAccidentalNoiseNodeScalarFunc::get_caption() const {

	return "ScalarFunc";
}

int VisualAccidentalNoiseNodeScalarFunc::get_input_port_count() const {

	return 1;
}

void VisualAccidentalNoiseNodeScalarFunc::set_input_port_value(int p_port, const Variant &p_value) {

	input = p_value;
}

Variant VisualAccidentalNoiseNodeScalarFunc::get_input_port_value(int p_port) const {

	return input;
}

VisualAccidentalNoiseNodeScalarFunc::PortType VisualAccidentalNoiseNodeScalarFunc::get_input_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeScalarFunc::get_input_port_name(int p_port) const {

	return "input";
}

int VisualAccidentalNoiseNodeScalarFunc::get_output_port_count() const {

	return 1;
}

VisualAccidentalNoiseNodeScalarFunc::PortType VisualAccidentalNoiseNodeScalarFunc::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeScalarFunc::get_output_port_name(int p_port) const {
	return "";
}

void VisualAccidentalNoiseNodeScalarFunc::set_function(Function p_func) {

	func = p_func;
	emit_changed();
}

VisualAccidentalNoiseNodeScalarFunc::Function VisualAccidentalNoiseNodeScalarFunc::get_function() const {

	return func;
}

Vector<StringName> VisualAccidentalNoiseNodeScalarFunc::get_editable_properties() const {

	Vector<StringName> props;
	props.push_back("function");

	return props;
}

void VisualAccidentalNoiseNodeScalarFunc::evaluate(Ref<VisualAccidentalNoise> noise) {

	switch (func) {

		case FUNC_COS:
			output_value = noise->cos(input);
			break;

		case FUNC_SIN:
			output_value = noise->sin(input);
			break;

		case FUNC_TAN:
			output_value = noise->tan(input);
			break;

		case FUNC_ACOS:
			output_value = noise->acos(input);
			break;

		case FUNC_ASIN:
			output_value = noise->asin(input);
			break;

		case FUNC_ATAN:
			output_value = noise->atan(input);
			break;

		case FUNC_ABS:
			output_value = noise->abs(input);
			break;

		case FUNC_SIGMOID:
			output_value = noise->sigmoid(input);
			break;
	}
}

void VisualAccidentalNoiseNodeScalarFunc::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_function", "function"), &VisualAccidentalNoiseNodeScalarFunc::set_function);
	ClassDB::bind_method(D_METHOD("get_function"), &VisualAccidentalNoiseNodeScalarFunc::get_function);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "function", PROPERTY_HINT_ENUM, "Cos,Sin,Tan,Acos,Asin,Atan,Abs,Sigmoid"), "set_function", "get_function");

	BIND_ENUM_CONSTANT(FUNC_COS);
	BIND_ENUM_CONSTANT(FUNC_SIN);
	BIND_ENUM_CONSTANT(FUNC_TAN);
	BIND_ENUM_CONSTANT(FUNC_ACOS);
	BIND_ENUM_CONSTANT(FUNC_ASIN);
	BIND_ENUM_CONSTANT(FUNC_ATAN);
	BIND_ENUM_CONSTANT(FUNC_ABS);
	BIND_ENUM_CONSTANT(FUNC_SIGMOID);
}

VisualAccidentalNoiseNodeScalarFunc::VisualAccidentalNoiseNodeScalarFunc() {

	set_input_port_default_value(0, 0);

	func = FUNC_COS;
}

////////////// Value Basis

String VisualAccidentalNoiseNodeValueBasis::get_caption() const {

	return "ValueBasis";
}

int VisualAccidentalNoiseNodeValueBasis::get_input_port_count() const {

	return 2;
}

void VisualAccidentalNoiseNodeValueBasis::set_input_port_value(int p_port, const Variant &p_value) {

	p_port == 0 ? interp = p_value : seed = p_value;
}

Variant VisualAccidentalNoiseNodeValueBasis::get_input_port_value(int p_port) const {

	return p_port == 0 ? interp : seed;
}

VisualAccidentalNoiseNodeValueBasis::PortType VisualAccidentalNoiseNodeValueBasis::get_input_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeValueBasis::get_input_port_name(int p_port) const {

	return p_port == 0 ? "interp" : "seed";
}

int VisualAccidentalNoiseNodeValueBasis::get_output_port_count() const {

	return 1;
}

VisualAccidentalNoiseNodeValueBasis::PortType VisualAccidentalNoiseNodeValueBasis::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeValueBasis::get_output_port_name(int p_port) const {

	return "";
}

void VisualAccidentalNoiseNodeValueBasis::set_seed(Index p_seed) {

	seed = p_seed;
	emit_changed();
}

Index VisualAccidentalNoiseNodeValueBasis::get_seed() const {

	return seed;
}

void VisualAccidentalNoiseNodeValueBasis::set_interpolation(Index p_interp) {

	interp = p_interp;
	emit_changed();
}

Index VisualAccidentalNoiseNodeValueBasis::get_interpolation() const {

	return interp;
}

void VisualAccidentalNoiseNodeValueBasis::evaluate(Ref<VisualAccidentalNoise> noise) {

	output_value = noise->value_basis(interp, seed);
}

void VisualAccidentalNoiseNodeValueBasis::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_interpolation", "value"), &VisualAccidentalNoiseNodeValueBasis::set_interpolation);
	ClassDB::bind_method(D_METHOD("get_interpolation"), &VisualAccidentalNoiseNodeValueBasis::get_interpolation);

	ClassDB::bind_method(D_METHOD("set_seed", "value"), &VisualAccidentalNoiseNodeValueBasis::set_seed);
	ClassDB::bind_method(D_METHOD("get_seed"), &VisualAccidentalNoiseNodeValueBasis::get_seed);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "interpolation"), "set_interpolation", "get_interpolation");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "seed"), "set_seed", "get_seed");
}

VisualAccidentalNoiseNodeValueBasis::VisualAccidentalNoiseNodeValueBasis() {

	set_input_port_default_value(0, AccidentalNoise::INTERP_QUINTIC);
	set_input_port_default_value(1, 0);

	interp = 0;
	seed = 0;
}

////////////// Gradient Basis

String VisualAccidentalNoiseNodeGradientBasis::get_caption() const {

	return "GradientBasis";
}

int VisualAccidentalNoiseNodeGradientBasis::get_input_port_count() const {

	return 2;
}

void VisualAccidentalNoiseNodeGradientBasis::set_input_port_value(int p_port, const Variant &p_value) {

	p_port == 0 ? interp = p_value : seed = p_value;
}

Variant VisualAccidentalNoiseNodeGradientBasis::get_input_port_value(int p_port) const {

	return p_port == 0 ? interp : seed;
}

VisualAccidentalNoiseNodeGradientBasis::PortType VisualAccidentalNoiseNodeGradientBasis::get_input_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeGradientBasis::get_input_port_name(int p_port) const {

	return p_port == 0 ? "interp" : "seed";
}

int VisualAccidentalNoiseNodeGradientBasis::get_output_port_count() const {

	return 1;
}

VisualAccidentalNoiseNodeGradientBasis::PortType VisualAccidentalNoiseNodeGradientBasis::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeGradientBasis::get_output_port_name(int p_port) const {

	return "";
}

void VisualAccidentalNoiseNodeGradientBasis::set_seed(Index p_seed) {

	seed = p_seed;
	emit_changed();
}

Index VisualAccidentalNoiseNodeGradientBasis::get_seed() const {

	return seed;
}

void VisualAccidentalNoiseNodeGradientBasis::set_interpolation(Index p_interp) {

	interp = p_interp;
	emit_changed();
}

Index VisualAccidentalNoiseNodeGradientBasis::get_interpolation() const {

	return interp;
}

void VisualAccidentalNoiseNodeGradientBasis::evaluate(Ref<VisualAccidentalNoise> noise) {

	output_value = noise->gradient_basis(interp, seed);
}

void VisualAccidentalNoiseNodeGradientBasis::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_interpolation", "value"), &VisualAccidentalNoiseNodeGradientBasis::set_interpolation);
	ClassDB::bind_method(D_METHOD("get_interpolation"), &VisualAccidentalNoiseNodeGradientBasis::get_interpolation);

	ClassDB::bind_method(D_METHOD("set_seed", "value"), &VisualAccidentalNoiseNodeGradientBasis::set_seed);
	ClassDB::bind_method(D_METHOD("get_seed"), &VisualAccidentalNoiseNodeGradientBasis::get_seed);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "interpolation"), "set_interpolation", "get_interpolation");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "seed"), "set_seed", "get_seed");
}

VisualAccidentalNoiseNodeGradientBasis::VisualAccidentalNoiseNodeGradientBasis() {

	set_input_port_default_value(0, AccidentalNoise::INTERP_QUINTIC);
	set_input_port_default_value(1, 0);

	interp = 0;
	seed = 0;
}

////////////// Cellular Basis

String VisualAccidentalNoiseNodeCellularBasis::get_caption() const {

	return "CellularBasis";
}

int VisualAccidentalNoiseNodeCellularBasis::get_input_port_count() const {

	return 10;
}

void VisualAccidentalNoiseNodeCellularBasis::set_input_port_value(int p_port, const Variant &p_value) {

	switch (p_port) {
		case 0: f1 = p_value; break;
		case 1: f2 = p_value; break;
		case 2: f3 = p_value; break;
		case 3: f4 = p_value; break;
		case 4: d1 = p_value; break;
		case 5: d2 = p_value; break;
		case 6: d3 = p_value; break;
		case 7: d4 = p_value; break;
		case 8: distance = p_value; break;
		case 9: seed = p_value; break;
	}
}

Variant VisualAccidentalNoiseNodeCellularBasis::get_input_port_value(int p_port) const {

	switch (p_port) {
		case 0: return f1;
		case 1: return f2;
		case 2: return f3;
		case 3: return f4;
		case 4: return d1;
		case 5: return d2;
		case 6: return d3;
		case 7: return d4;
		case 8: return distance;
		case 9: return seed;
	}
	return Variant();
}

VisualAccidentalNoiseNodeCellularBasis::PortType VisualAccidentalNoiseNodeCellularBasis::get_input_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeCellularBasis::get_input_port_name(int p_port) const {

	switch (p_port) {
		case 0: return "f1";
		case 1: return "f2";
		case 2: return "f3";
		case 3: return "f4";
		case 4: return "d1";
		case 5: return "d2";
		case 6: return "d3";
		case 7: return "d4";
		case 8: return "distance";
		case 9: return "seed";
	}
	return "";
}

int VisualAccidentalNoiseNodeCellularBasis::get_output_port_count() const {

	return 1;
}

VisualAccidentalNoiseNodeCellularBasis::PortType VisualAccidentalNoiseNodeCellularBasis::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeCellularBasis::get_output_port_name(int p_port) const {

	return "";
}

void VisualAccidentalNoiseNodeCellularBasis::set_seed(Index p_seed) {

	seed = p_seed;
	emit_changed();
}

Index VisualAccidentalNoiseNodeCellularBasis::get_seed() const {

	return seed;
}

void VisualAccidentalNoiseNodeCellularBasis::set_distance(Index p_distance) {

	distance = p_distance;
	emit_changed();
}

Index VisualAccidentalNoiseNodeCellularBasis::get_distance() const {

	return distance;
}

void VisualAccidentalNoiseNodeCellularBasis::evaluate(Ref<VisualAccidentalNoise> noise) {

	output_value = noise->cellular_basis(f1, f2, f3, f4, d1, d2, d3, d4, distance, seed);
}

void VisualAccidentalNoiseNodeCellularBasis::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_distance", "value"), &VisualAccidentalNoiseNodeCellularBasis::set_distance);
	ClassDB::bind_method(D_METHOD("get_distance"), &VisualAccidentalNoiseNodeCellularBasis::get_distance);

	ClassDB::bind_method(D_METHOD("set_seed", "value"), &VisualAccidentalNoiseNodeCellularBasis::set_seed);
	ClassDB::bind_method(D_METHOD("get_seed"), &VisualAccidentalNoiseNodeCellularBasis::get_seed);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "distance"), "set_distance", "get_distance");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "seed"), "set_seed", "get_seed");
}

VisualAccidentalNoiseNodeCellularBasis::VisualAccidentalNoiseNodeCellularBasis() {

	set_input_port_default_value(0, -1);
	set_input_port_default_value(1, 1);
	set_input_port_default_value(2, 0);
	set_input_port_default_value(3, 0);

	set_input_port_default_value(4, 0);
	set_input_port_default_value(5, 0);
	set_input_port_default_value(6, 0);
	set_input_port_default_value(7, 0);

	set_input_port_default_value(8, AccidentalNoise::DISTANCE_EUCLID);
	set_input_port_default_value(9, 0);

	f1 = f2 = f3 = f4 = 0;
	d1 = d2 = d3 = d4 = 0;
	distance = 0;
	seed = 0;
}

////////////// Simplex Basis

String VisualAccidentalNoiseNodeSimplexBasis::get_caption() const {

	return "SimplexBasis";
}

int VisualAccidentalNoiseNodeSimplexBasis::get_input_port_count() const {

	return 1;
}

void VisualAccidentalNoiseNodeSimplexBasis::set_input_port_value(int p_port, const Variant &p_value) {

	seed = p_value;
}

Variant VisualAccidentalNoiseNodeSimplexBasis::get_input_port_value(int p_port) const {

	return seed;
}

VisualAccidentalNoiseNodeSimplexBasis::PortType VisualAccidentalNoiseNodeSimplexBasis::get_input_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeSimplexBasis::get_input_port_name(int p_port) const {

	return "seed";
}

int VisualAccidentalNoiseNodeSimplexBasis::get_output_port_count() const {

	return 1;
}

VisualAccidentalNoiseNodeSimplexBasis::PortType VisualAccidentalNoiseNodeSimplexBasis::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeSimplexBasis::get_output_port_name(int p_port) const {

	return "";
}

void VisualAccidentalNoiseNodeSimplexBasis::set_seed(Index p_seed) {

	seed = p_seed;
	emit_changed();
}

Index VisualAccidentalNoiseNodeSimplexBasis::get_seed() const {

	return seed;
}

void VisualAccidentalNoiseNodeSimplexBasis::evaluate(Ref<VisualAccidentalNoise> noise) {

	output_value = noise->simplex_basis(seed);
}

void VisualAccidentalNoiseNodeSimplexBasis::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_seed", "value"), &VisualAccidentalNoiseNodeSimplexBasis::set_seed);
	ClassDB::bind_method(D_METHOD("get_seed"), &VisualAccidentalNoiseNodeSimplexBasis::get_seed);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "seed"), "set_seed", "get_seed");
}

VisualAccidentalNoiseNodeSimplexBasis::VisualAccidentalNoiseNodeSimplexBasis() {

	set_input_port_default_value(0, 0);

	seed = 0;
}

////////////// Expression

String VisualAccidentalNoiseNodeExpression::get_caption() const {

	return "Expression";
}

int VisualAccidentalNoiseNodeExpression::get_input_port_count() const {

	return 0;
}

void VisualAccidentalNoiseNodeExpression::set_input_port_value(int p_port, const Variant &p_value) {

	expression = p_value;
}

Variant VisualAccidentalNoiseNodeExpression::get_input_port_value(int p_port) const {

	return expression;
}

VisualAccidentalNoiseNodeExpression::PortType VisualAccidentalNoiseNodeExpression::get_input_port_type(int p_port) const {

	return PORT_TYPE_SCALAR;
}

String VisualAccidentalNoiseNodeExpression::get_input_port_name(int p_port) const {

	return "";
}

int VisualAccidentalNoiseNodeExpression::get_output_port_count() const {

	return 1;
}

VisualAccidentalNoiseNodeExpression::PortType VisualAccidentalNoiseNodeExpression::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeExpression::get_output_port_name(int p_port) const {

	return "";
}

void VisualAccidentalNoiseNodeExpression::set_expression(const String &p_expression) {

	expression = p_expression;
	emit_changed();
}

String VisualAccidentalNoiseNodeExpression::get_expression() const {

	return expression;
}

Vector<StringName> VisualAccidentalNoiseNodeExpression::get_editable_properties() const {

	Vector<StringName> props;
	return props;
}

void VisualAccidentalNoiseNodeExpression::evaluate(Ref<VisualAccidentalNoise> noise) {

	output_value = noise->evaluate(expression);
}

void VisualAccidentalNoiseNodeExpression::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_expression", "value"), &VisualAccidentalNoiseNodeExpression::set_expression);
	ClassDB::bind_method(D_METHOD("get_expression"), &VisualAccidentalNoiseNodeExpression::get_expression);

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "expression", PROPERTY_HINT_MULTILINE_TEXT), "set_expression", "get_expression");
}

VisualAccidentalNoiseNodeExpression::VisualAccidentalNoiseNodeExpression() {

	expression = "";
}

//============ Transform

////////////// Translate

const String VisualAccidentalNoiseNodeTranslate::method = "translate";

String VisualAccidentalNoiseNodeTranslate::get_caption() const {

	return "Translate";
}

int VisualAccidentalNoiseNodeTranslate::get_input_port_count() const {

	return 2;
}

void VisualAccidentalNoiseNodeTranslate::set_input_port_value(int p_port, const Variant &p_value) {

	p_port == 0 ? input = p_value : by = p_value;
}

Variant VisualAccidentalNoiseNodeTranslate::get_input_port_value(int p_port) const {

	return p_port == 0 ? input : by;
}

VisualAccidentalNoiseNodeTranslate::PortType VisualAccidentalNoiseNodeTranslate::get_input_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeTranslate::get_input_port_name(int p_port) const {

	return p_port == 0 ? "input" : "by";
}

int VisualAccidentalNoiseNodeTranslate::get_output_port_count() const {

	return 1;
}

VisualAccidentalNoiseNodeTranslate::PortType VisualAccidentalNoiseNodeTranslate::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeTranslate::get_output_port_name(int p_port) const {
	return "";
}

void VisualAccidentalNoiseNodeTranslate::set_axis(Axis::AxisType p_axis) {

	axis.type = p_axis;
	emit_changed();
}

Axis::AxisType VisualAccidentalNoiseNodeTranslate::get_axis() const {

	return axis.type;
}

Vector<StringName> VisualAccidentalNoiseNodeTranslate::get_editable_properties() const {

	Vector<StringName> props;

	props.push_back("axis");

	return props;
}

void VisualAccidentalNoiseNodeTranslate::evaluate(Ref<VisualAccidentalNoise> noise) {

	String m = method;
	if (axis.type != Axis::AXIS_DOMAIN) {
		m = method + "_" + axis.as_alpha();
	}
	output_value = noise->call(m, input, by);
}

void VisualAccidentalNoiseNodeTranslate::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_axis", "axis"), &VisualAccidentalNoiseNodeTranslate::set_axis);
	ClassDB::bind_method(D_METHOD("get_axis"), &VisualAccidentalNoiseNodeTranslate::get_axis);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "axis", PROPERTY_HINT_ENUM, Axis::get_hints()), "set_axis", "get_axis");
}

VisualAccidentalNoiseNodeTranslate::VisualAccidentalNoiseNodeTranslate() {

	set_input_port_default_value(0, 0);
	set_input_port_default_value(1, 0);

	input = 0;
	by = 0;
}

////////////// Scale

const String VisualAccidentalNoiseNodeScale::method = "scale";

String VisualAccidentalNoiseNodeScale::get_caption() const {

	return "Scale";
}

int VisualAccidentalNoiseNodeScale::get_input_port_count() const {

	return 2;
}

void VisualAccidentalNoiseNodeScale::set_input_port_value(int p_port, const Variant &p_value) {

	p_port == 0 ? input = p_value : by = p_value;
}

Variant VisualAccidentalNoiseNodeScale::get_input_port_value(int p_port) const {

	return p_port == 0 ? input : by;
}

VisualAccidentalNoiseNodeScale::PortType VisualAccidentalNoiseNodeScale::get_input_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeScale::get_input_port_name(int p_port) const {

	return p_port == 0 ? "input" : "by";
}

int VisualAccidentalNoiseNodeScale::get_output_port_count() const {

	return 1;
}

VisualAccidentalNoiseNodeScale::PortType VisualAccidentalNoiseNodeScale::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeScale::get_output_port_name(int p_port) const {
	return "";
}

void VisualAccidentalNoiseNodeScale::set_axis(Axis::AxisType p_axis) {

	axis.type = p_axis;
	emit_changed();
}

Axis::AxisType VisualAccidentalNoiseNodeScale::get_axis() const {

	return axis.type;
}

Vector<StringName> VisualAccidentalNoiseNodeScale::get_editable_properties() const {

	Vector<StringName> props;

	props.push_back("axis");

	return props;
}

void VisualAccidentalNoiseNodeScale::evaluate(Ref<VisualAccidentalNoise> noise) {

	String m = method;
	if (axis.type != Axis::AXIS_DOMAIN) {
		m = method + "_" + axis.as_alpha();
	}
	output_value = noise->call(m, input, by);
}

void VisualAccidentalNoiseNodeScale::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_axis", "axis"), &VisualAccidentalNoiseNodeScale::set_axis);
	ClassDB::bind_method(D_METHOD("get_axis"), &VisualAccidentalNoiseNodeScale::get_axis);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "axis", PROPERTY_HINT_ENUM, Axis::get_hints()), "set_axis", "get_axis");
}

VisualAccidentalNoiseNodeScale::VisualAccidentalNoiseNodeScale() {

	set_input_port_default_value(0, 0);
	set_input_port_default_value(1, 1);

	input = 0;
	by = 0;
}

////////////// Rotate

String VisualAccidentalNoiseNodeRotate::get_caption() const {

	return "Rotate";
}

int VisualAccidentalNoiseNodeRotate::get_input_port_count() const {

	return 5;
}

void VisualAccidentalNoiseNodeRotate::set_input_port_value(int p_port, const Variant &p_value) {

	switch (p_port) {
		case 0: input = p_value; break;
		case 1: angle = p_value; break;
		case 2: ax = p_value; break;
		case 3: ay = p_value; break;
		case 4: az = p_value; break;
	}
}

Variant VisualAccidentalNoiseNodeRotate::get_input_port_value(int p_port) const {

	switch (p_port) {
		case 0: return input;
		case 1: return angle;
		case 2: return ax;
		case 3: return ay;
		case 4: return az;
	}
	return Variant();
}

VisualAccidentalNoiseNodeRotate::PortType VisualAccidentalNoiseNodeRotate::get_input_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeRotate::get_input_port_name(int p_port) const {

	switch (p_port) {
		case 0: return "input";
		case 1: return "angle";
		case 2: return "ax";
		case 3: return "ay";
		case 4: return "az";
	}
	return "";
}

int VisualAccidentalNoiseNodeRotate::get_output_port_count() const {

	return 1;
}

VisualAccidentalNoiseNodeRotate::PortType VisualAccidentalNoiseNodeRotate::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeRotate::get_output_port_name(int p_port) const {
	return "";
}

void VisualAccidentalNoiseNodeRotate::evaluate(Ref<VisualAccidentalNoise> noise) {

	output_value = noise->rotate(input, angle, ax, ay, az);
}

void VisualAccidentalNoiseNodeRotate::_bind_methods() {
}

VisualAccidentalNoiseNodeRotate::VisualAccidentalNoiseNodeRotate() {

	set_input_port_default_value(0, 0);
	set_input_port_default_value(1, 0);
	set_input_port_default_value(2, 0);
	set_input_port_default_value(3, 0);
	set_input_port_default_value(4, 1); // for 2D case

	input = 0;
	angle = 0;
	ax = ay = az = 0;
}

////////////// Clamp

String VisualAccidentalNoiseNodeClamp::get_caption() const {

	return "Clamp";
}

int VisualAccidentalNoiseNodeClamp::get_input_port_count() const {

	return 3;
}

void VisualAccidentalNoiseNodeClamp::set_input_port_value(int p_port, const Variant &p_value) {

	switch (p_port) {
		case 0: input = p_value; break;
		case 1: low = p_value; break;
		case 2: high = p_value; break;
	}
}

Variant VisualAccidentalNoiseNodeClamp::get_input_port_value(int p_port) const {

	switch (p_port) {
		case 0: return input;
		case 1: return low;
		case 2: return high;
	}
	return Variant();
}

VisualAccidentalNoiseNodeClamp::PortType VisualAccidentalNoiseNodeClamp::get_input_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeClamp::get_input_port_name(int p_port) const {

	switch (p_port) {
		case 0: return "input";
		case 1: return "low";
		case 2: return "high";
	}
	return "";
}

int VisualAccidentalNoiseNodeClamp::get_output_port_count() const {

	return 1;
}

VisualAccidentalNoiseNodeClamp::PortType VisualAccidentalNoiseNodeClamp::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeClamp::get_output_port_name(int p_port) const {
	return "";
}

void VisualAccidentalNoiseNodeClamp::evaluate(Ref<VisualAccidentalNoise> noise) {

	output_value = noise->clamp(input, low, high);
}

void VisualAccidentalNoiseNodeClamp::_bind_methods() {
}

VisualAccidentalNoiseNodeClamp::VisualAccidentalNoiseNodeClamp() {

	set_input_port_default_value(0, 0);
	set_input_port_default_value(1, 0);
	set_input_port_default_value(2, 1);

	input = 0;
	low = high = 0;
}

////////////// Mix

String VisualAccidentalNoiseNodeMix::get_caption() const {

	return "Mix";
}

int VisualAccidentalNoiseNodeMix::get_input_port_count() const {

	return 3;
}

void VisualAccidentalNoiseNodeMix::set_input_port_value(int p_port, const Variant &p_value) {

	switch (p_port) {
		case 0: low = p_value; break;
		case 1: high = p_value; break;
		case 2: control = p_value; break;
	}
}

Variant VisualAccidentalNoiseNodeMix::get_input_port_value(int p_port) const {

	switch (p_port) {
		case 0: return low;
		case 1: return high;
		case 2: return control;
	}
	return Variant();
}

VisualAccidentalNoiseNodeMix::PortType VisualAccidentalNoiseNodeMix::get_input_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeMix::get_input_port_name(int p_port) const {

	switch (p_port) {
		case 0: return "low";
		case 1: return "high";
		case 2: return "control";
	}
	return "";
}

int VisualAccidentalNoiseNodeMix::get_output_port_count() const {

	return 1;
}

VisualAccidentalNoiseNodeMix::PortType VisualAccidentalNoiseNodeMix::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeMix::get_output_port_name(int p_port) const {
	return "";
}

void VisualAccidentalNoiseNodeMix::evaluate(Ref<VisualAccidentalNoise> noise) {

	output_value = noise->mix(low, high, control);
}

void VisualAccidentalNoiseNodeMix::_bind_methods() {
}

VisualAccidentalNoiseNodeMix::VisualAccidentalNoiseNodeMix() {

	set_input_port_default_value(0, 0);
	set_input_port_default_value(1, 1);
	set_input_port_default_value(2, 0);

	low = high = 0;
	control = 0;
}

////////////// Select

String VisualAccidentalNoiseNodeSelect::get_caption() const {

	return "Select";
}

int VisualAccidentalNoiseNodeSelect::get_input_port_count() const {

	return 5;
}

void VisualAccidentalNoiseNodeSelect::set_input_port_value(int p_port, const Variant &p_value) {

	switch (p_port) {
		case 0: low = p_value; break;
		case 1: high = p_value; break;
		case 2: control = p_value; break;
		case 3: threshold = p_value; break;
		case 4: falloff = p_value; break;
	}
}

Variant VisualAccidentalNoiseNodeSelect::get_input_port_value(int p_port) const {

	switch (p_port) {
		case 0: return low;
		case 1: return high;
		case 2: return control;
		case 3: return threshold;
		case 4: return falloff;
	}
	return Variant();
}

VisualAccidentalNoiseNodeSelect::PortType VisualAccidentalNoiseNodeSelect::get_input_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeSelect::get_input_port_name(int p_port) const {

	switch (p_port) {
		case 0: return "low";
		case 1: return "high";
		case 2: return "control";
		case 3: return "threshold";
		case 4: return "falloff";
	}
	return "";
}

int VisualAccidentalNoiseNodeSelect::get_output_port_count() const {

	return 1;
}

VisualAccidentalNoiseNodeSelect::PortType VisualAccidentalNoiseNodeSelect::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeSelect::get_output_port_name(int p_port) const {
	return "";
}

void VisualAccidentalNoiseNodeSelect::evaluate(Ref<VisualAccidentalNoise> noise) {

	output_value = noise->select(low, high, control, threshold, falloff);
}

void VisualAccidentalNoiseNodeSelect::_bind_methods() {
}

VisualAccidentalNoiseNodeSelect::VisualAccidentalNoiseNodeSelect() {

	set_input_port_default_value(0, 0);
	set_input_port_default_value(1, 1);
	set_input_port_default_value(2, 0);
	set_input_port_default_value(3, 0.5);
	set_input_port_default_value(4, 0);

	low = high = 0;
	control = 0;
	threshold = 0;
	falloff = 0;
}

////////////// Tiers

String VisualAccidentalNoiseNodeTiers::get_caption() const {

	return "Tiers";
}

void VisualAccidentalNoiseNodeTiers::set_smooth(Smoothness p_smooth) {

	smooth = p_smooth;
	emit_changed();
}

VisualAccidentalNoiseNodeTiers::Smoothness VisualAccidentalNoiseNodeTiers::get_smooth() const {

	return smooth;
}

int VisualAccidentalNoiseNodeTiers::get_input_port_count() const {

	return 2;
}

void VisualAccidentalNoiseNodeTiers::set_input_port_value(int p_port, const Variant &p_value) {

	switch (p_port) {
		case 0: input = p_value; break;
		case 1: tiers = p_value; break;
	}
}

Variant VisualAccidentalNoiseNodeTiers::get_input_port_value(int p_port) const {

	switch (p_port) {
		case 0: return input;
		case 1: return tiers;
	}
	return Variant();
}

VisualAccidentalNoiseNodeTiers::PortType VisualAccidentalNoiseNodeTiers::get_input_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeTiers::get_input_port_name(int p_port) const {

	switch (p_port) {
		case 0: return "input";
		case 1: return "tiers";
	}
	return "";
}

int VisualAccidentalNoiseNodeTiers::get_output_port_count() const {

	return 1;
}

VisualAccidentalNoiseNodeTiers::PortType VisualAccidentalNoiseNodeTiers::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeTiers::get_output_port_name(int p_port) const {
	return "";
}

Vector<StringName> VisualAccidentalNoiseNodeTiers::get_editable_properties() const {

	Vector<StringName> props;
	props.push_back("smooth");

	return props;
}

void VisualAccidentalNoiseNodeTiers::evaluate(Ref<VisualAccidentalNoise> noise) {

	if (smooth) {
		output_value = noise->smooth_tiers(input, tiers);
	} else {
		output_value = noise->tiers(input, tiers);
	}
}

void VisualAccidentalNoiseNodeTiers::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_smooth", "smooth"), &VisualAccidentalNoiseNodeTiers::set_smooth);
	ClassDB::bind_method(D_METHOD("get_smooth"), &VisualAccidentalNoiseNodeTiers::get_smooth);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "smooth", PROPERTY_HINT_ENUM, "No smoothing, Smoothed"), "set_smooth", "get_smooth");
}

VisualAccidentalNoiseNodeTiers::VisualAccidentalNoiseNodeTiers() {

	set_input_port_default_value(0, 0);
	set_input_port_default_value(1, 5);

	smooth = SMOOTHING_DISABLED;

	input = 0;
	tiers = 0;
}

////////////// Gradient

String VisualAccidentalNoiseNodeGradient::get_caption() const {

	return "Gradient";
}

void VisualAccidentalNoiseNodeGradient::set_axis(Axis::AxisType p_axis) {

	axis.type = p_axis;
	emit_changed();
}

Axis::AxisType VisualAccidentalNoiseNodeGradient::get_axis() const {

	return axis.type;
}

int VisualAccidentalNoiseNodeGradient::get_input_port_count() const {

	return 0;
}

VisualAccidentalNoiseNodeGradient::PortType VisualAccidentalNoiseNodeGradient::get_input_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeGradient::get_input_port_name(int p_port) const {

	return "";
}

int VisualAccidentalNoiseNodeGradient::get_output_port_count() const {

	return 1;
}

VisualAccidentalNoiseNodeGradient::PortType VisualAccidentalNoiseNodeGradient::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeGradient::get_output_port_name(int p_port) const {
	return "";
}

Vector<StringName> VisualAccidentalNoiseNodeGradient::get_editable_properties() const {

	Vector<StringName> props;

	props.push_back("axis");

	return props;
}

void VisualAccidentalNoiseNodeGradient::evaluate(Ref<VisualAccidentalNoise> noise) {

	if (axis.type != Axis::AXIS_DOMAIN) {
		output_value = noise->call(axis.as_alpha());
	} else {
		output_value = noise->zero(); // a workaround to circumvent domain enum
	}
}

void VisualAccidentalNoiseNodeGradient::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_axis", "axis"), &VisualAccidentalNoiseNodeGradient::set_axis);
	ClassDB::bind_method(D_METHOD("get_axis"), &VisualAccidentalNoiseNodeGradient::get_axis);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "axis", PROPERTY_HINT_ENUM, Axis::get_hints()), "set_axis", "get_axis");
}

VisualAccidentalNoiseNodeGradient::VisualAccidentalNoiseNodeGradient() {

	axis.type = Axis::AXIS_X;
}

////////////// Derivative

String VisualAccidentalNoiseNodeDerivative::get_caption() const {

	return "Derivative";
}

void VisualAccidentalNoiseNodeDerivative::set_axis(Axis::AxisType p_axis) {

	axis.type = p_axis;
	emit_changed();
}

Axis::AxisType VisualAccidentalNoiseNodeDerivative::get_axis() const {

	return axis.type;
}

void VisualAccidentalNoiseNodeDerivative::set_input_port_value(int p_port, const Variant &p_value) {

	switch (p_port) {
		case 0: input = p_value; break;
		case 1: spacing = p_value; break;
	}
}

Variant VisualAccidentalNoiseNodeDerivative::get_input_port_value(int p_port) const {

	switch (p_port) {
		case 0: return input;
		case 1: return spacing;
	}
	return Variant();
}

int VisualAccidentalNoiseNodeDerivative::get_input_port_count() const {

	return 2;
}

VisualAccidentalNoiseNodeDerivative::PortType VisualAccidentalNoiseNodeDerivative::get_input_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeDerivative::get_input_port_name(int p_port) const {

	switch (p_port) {
		case 0: return "input";
		case 1: return "spacing";
	}
	return String();
}

int VisualAccidentalNoiseNodeDerivative::get_output_port_count() const {

	return 1;
}

VisualAccidentalNoiseNodeDerivative::PortType VisualAccidentalNoiseNodeDerivative::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeDerivative::get_output_port_name(int p_port) const {
	return "";
}

Vector<StringName> VisualAccidentalNoiseNodeDerivative::get_editable_properties() const {

	Vector<StringName> props;

	props.push_back("axis");

	return props;
}

void VisualAccidentalNoiseNodeDerivative::evaluate(Ref<VisualAccidentalNoise> noise) {

	if (axis.type != Axis::AXIS_DOMAIN) {
		output_value = noise->call("d" + axis.as_alpha(), input, spacing);
	} else {
		output_value = noise->zero(); // a workaround to circumvent domain enum
	}
}

void VisualAccidentalNoiseNodeDerivative::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_axis", "axis"), &VisualAccidentalNoiseNodeDerivative::set_axis);
	ClassDB::bind_method(D_METHOD("get_axis"), &VisualAccidentalNoiseNodeDerivative::get_axis);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "axis", PROPERTY_HINT_ENUM, Axis::get_hints()), "set_axis", "get_axis");
}

VisualAccidentalNoiseNodeDerivative::VisualAccidentalNoiseNodeDerivative() {

	set_input_port_default_value(0, 0);
	set_input_port_default_value(1, 1);

	axis.type = Axis::AXIS_X;

	input = 0;
	spacing = 0;
}

////////////// Radial

String VisualAccidentalNoiseNodeRadial::get_caption() const {

	return "Radial";
}

int VisualAccidentalNoiseNodeRadial::get_input_port_count() const {

	return 0;
}

VisualAccidentalNoiseNodeRadial::PortType VisualAccidentalNoiseNodeRadial::get_input_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeRadial::get_input_port_name(int p_port) const {

	return "";
}

int VisualAccidentalNoiseNodeRadial::get_output_port_count() const {

	return 1;
}

VisualAccidentalNoiseNodeRadial::PortType VisualAccidentalNoiseNodeRadial::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeRadial::get_output_port_name(int p_port) const {
	return "";
}

void VisualAccidentalNoiseNodeRadial::evaluate(Ref<VisualAccidentalNoise> noise) {

	output_value = noise->radial();
}

void VisualAccidentalNoiseNodeRadial::_bind_methods() {
}

VisualAccidentalNoiseNodeRadial::VisualAccidentalNoiseNodeRadial() {
}

////////////// Randomize

String VisualAccidentalNoiseNodeRandomize::get_caption() const {

	return "Randomize";
}

int VisualAccidentalNoiseNodeRandomize::get_input_port_count() const {

	return 3;
}

void VisualAccidentalNoiseNodeRandomize::set_input_port_value(int p_port, const Variant &p_value) {

	switch (p_port) {
		case 0: seed = p_value; break;
		case 1: low = p_value; break;
		case 2: high = p_value; break;
	}
}

Variant VisualAccidentalNoiseNodeRandomize::get_input_port_value(int p_port) const {

	switch (p_port) {
		case 0: return seed;
		case 1: return low;
		case 2: return high;
	}
	return Variant();
}

VisualAccidentalNoiseNodeRandomize::PortType VisualAccidentalNoiseNodeRandomize::get_input_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeRandomize::get_input_port_name(int p_port) const {

	switch (p_port) {
		case 0: return "seed";
		case 1: return "low";
		case 2: return "high";
	}
	return "";
}

int VisualAccidentalNoiseNodeRandomize::get_output_port_count() const {

	return 1;
}

VisualAccidentalNoiseNodeRandomize::PortType VisualAccidentalNoiseNodeRandomize::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeRandomize::get_output_port_name(int p_port) const {
	return "";
}

void VisualAccidentalNoiseNodeRandomize::evaluate(Ref<VisualAccidentalNoise> noise) {

	output_value = noise->randomize(seed, low, high);
}

void VisualAccidentalNoiseNodeRandomize::_bind_methods() {
}

VisualAccidentalNoiseNodeRandomize::VisualAccidentalNoiseNodeRandomize() {

	set_input_port_default_value(0, 0);
	set_input_port_default_value(1, 0);
	set_input_port_default_value(2, 1);

	seed = 0;
	low = high = 0;
}

////////////// Step

String VisualAccidentalNoiseNodeStep::get_caption() const {

	return "Step";
}

void VisualAccidentalNoiseNodeStep::set_type(StepType p_type) {

	type = p_type;
	emit_changed();
}

VisualAccidentalNoiseNodeStep::StepType VisualAccidentalNoiseNodeStep::get_type() const {

	return type;
}

int VisualAccidentalNoiseNodeStep::get_input_port_count() const {

	return 3; // hack be compatible with regular step
}

void VisualAccidentalNoiseNodeStep::set_input_port_value(int p_port, const Variant &p_value) {

	if (type != STEP_REGULAR) {
		switch (p_port) {
			case 0: low = p_value; break;
			case 1: high = p_value; break;
			case 2: control = p_value; break;
		}
	} else {
		switch (p_port) {
			case 0: value = p_value; break;
			case 1: control = p_value; break;
		}
	}
}

Variant VisualAccidentalNoiseNodeStep::get_input_port_value(int p_port) const {

	if (type != STEP_REGULAR) {
		switch (p_port) {
			case 0: return low;
			case 1: return high;
			case 2: return control;
		}
	} else {
		switch (p_port) {
			case 0: return value;
			case 1: return control;
		}
	}
	return Variant();
}

VisualAccidentalNoiseNodeStep::PortType VisualAccidentalNoiseNodeStep::get_input_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeStep::get_input_port_name(int p_port) const {

	if (type != STEP_REGULAR) {
		switch (p_port) {
			case 0: return "low";
			case 1: return "high";
			case 2: return "control";
		}
	} else {
		switch (p_port) {
			case 0: return "value";
			case 1: return "control";
		}
	}
	return "";
}

int VisualAccidentalNoiseNodeStep::get_output_port_count() const {

	return 1;
}

VisualAccidentalNoiseNodeStep::PortType VisualAccidentalNoiseNodeStep::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeStep::get_output_port_name(int p_port) const {
	return "";
}

Vector<StringName> VisualAccidentalNoiseNodeStep::get_editable_properties() const {

	Vector<StringName> props;

	props.push_back("type");

	return props;
}

void VisualAccidentalNoiseNodeStep::evaluate(Ref<VisualAccidentalNoise> noise) {

	switch (type) {
		case STEP_REGULAR: {
			output_value = noise->step(value, control);
		} break;

		case STEP_LINEAR: {
			output_value = noise->linear_step(low, high, control);
		} break;

		case STEP_SMOOTH: {
			output_value = noise->smooth_step(low, high, control);
		} break;

		case STEP_SMOOTHER: {
			output_value = noise->smoother_step(low, high, control);
		} break;
	}
}

void VisualAccidentalNoiseNodeStep::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_type", "type"), &VisualAccidentalNoiseNodeStep::set_type);
	ClassDB::bind_method(D_METHOD("get_type"), &VisualAccidentalNoiseNodeStep::get_type);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "type", PROPERTY_HINT_ENUM, "Regular,Linear,Smooth,Smoother"), "set_type", "get_type");

	BIND_ENUM_CONSTANT(STEP_REGULAR);
	BIND_ENUM_CONSTANT(STEP_LINEAR);
	BIND_ENUM_CONSTANT(STEP_SMOOTH);
	BIND_ENUM_CONSTANT(STEP_SMOOTHER);
}

VisualAccidentalNoiseNodeStep::VisualAccidentalNoiseNodeStep() {

	set_input_port_default_value(0, 0);
	set_input_port_default_value(1, 1);
	set_input_port_default_value(2, 0);

	type = STEP_REGULAR;

	value = 0;
	low = high = 0;
	control = 0;
}

////////////// Curve Section

String VisualAccidentalNoiseNodeCurveSection::get_caption() const {

	return "CurveSection";
}

int VisualAccidentalNoiseNodeCurveSection::get_input_port_count() const {

	return 6;
}

void VisualAccidentalNoiseNodeCurveSection::set_input_port_value(int p_port, const Variant &p_value) {

	switch (p_port) {
		case 0: lowv = p_value; break;
		case 1: t0 = p_value; break;
		case 2: t1 = p_value; break;
		case 3: v0 = p_value; break;
		case 4: v1 = p_value; break;
		case 5: control = p_value; break;
	}
}

Variant VisualAccidentalNoiseNodeCurveSection::get_input_port_value(int p_port) const {

	switch (p_port) {
		case 0: return lowv;
		case 1: return t0;
		case 2: return t1;
		case 3: return v0;
		case 4: return v1;
		case 5: return control;
	}
	return Variant();
}

VisualAccidentalNoiseNodeCurveSection::PortType VisualAccidentalNoiseNodeCurveSection::get_input_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeCurveSection::get_input_port_name(int p_port) const {

	switch (p_port) {
		case 0: return "lowv";
		case 1: return "t0";
		case 2: return "t1";
		case 3: return "v0";
		case 4: return "v1";
		case 5: return "control";
	}
	return "";
}

int VisualAccidentalNoiseNodeCurveSection::get_output_port_count() const {

	return 1;
}

VisualAccidentalNoiseNodeCurveSection::PortType VisualAccidentalNoiseNodeCurveSection::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeCurveSection::get_output_port_name(int p_port) const {

	return "";
}

void VisualAccidentalNoiseNodeCurveSection::evaluate(Ref<VisualAccidentalNoise> noise) {

	output_value = noise->curve_section(lowv, t0, t1, v0, v1, control);
}

void VisualAccidentalNoiseNodeCurveSection::_bind_methods() {
}

VisualAccidentalNoiseNodeCurveSection::VisualAccidentalNoiseNodeCurveSection() {

	set_input_port_default_value(0, 0);

	set_input_port_default_value(1, -1);
	set_input_port_default_value(2, 1);
	set_input_port_default_value(3, -1);
	set_input_port_default_value(4, 1);

	set_input_port_default_value(5, 0);

	lowv = 0;
	t0 = t1 = v0 = v1 = 0;
	control = 0;
}

////////////// Hex

String VisualAccidentalNoiseNodeHex::get_caption() const {

	return "Hex";
}

void VisualAccidentalNoiseNodeHex::set_input_port_value(int p_port, const Variant &p_value) {

	seed = p_value;
}

Variant VisualAccidentalNoiseNodeHex::get_input_port_value(int p_port) const {

	return seed;
}

int VisualAccidentalNoiseNodeHex::get_input_port_count() const {

	return 1; // hack to be compatible with hex tile
}

VisualAccidentalNoiseNodeHex::PortType VisualAccidentalNoiseNodeHex::get_input_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeHex::get_input_port_name(int p_port) const {

	return type == HEX_TILE ? "seed" : "";
}

int VisualAccidentalNoiseNodeHex::get_output_port_count() const {

	return 1;
}

VisualAccidentalNoiseNodeHex::PortType VisualAccidentalNoiseNodeHex::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeHex::get_output_port_name(int p_port) const {
	return "";
}

void VisualAccidentalNoiseNodeHex::set_type(HexType p_type) {

	type = p_type;
	emit_changed();
}

VisualAccidentalNoiseNodeHex::HexType VisualAccidentalNoiseNodeHex::get_type() const {

	return type;
}

Vector<StringName> VisualAccidentalNoiseNodeHex::get_editable_properties() const {

	Vector<StringName> props;
	props.push_back("type");

	return props;
}

void VisualAccidentalNoiseNodeHex::evaluate(Ref<VisualAccidentalNoise> noise) {

	switch (type) {

		case HEX_TILE:
			output_value = noise->hex_tile(seed);
			break;

		case HEX_BUMP:
			output_value = noise->hex_bump();
			break;
	}
}

void VisualAccidentalNoiseNodeHex::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_type", "type"), &VisualAccidentalNoiseNodeHex::set_type);
	ClassDB::bind_method(D_METHOD("get_type"), &VisualAccidentalNoiseNodeHex::get_type);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "type", PROPERTY_HINT_ENUM, "Tile,Bump"), "set_type", "get_type");

	BIND_ENUM_CONSTANT(HEX_TILE);
	BIND_ENUM_CONSTANT(HEX_BUMP);
}

VisualAccidentalNoiseNodeHex::VisualAccidentalNoiseNodeHex() {

	set_input_port_default_value(0, 0);

	type = HEX_TILE;
	seed = 0;
}

////////////// Color

String VisualAccidentalNoiseNodeColor::get_caption() const {

	return "Color";
}

int VisualAccidentalNoiseNodeColor::get_input_port_count() const {

	return 0;
}

VisualAccidentalNoiseNodeColor::PortType VisualAccidentalNoiseNodeColor::get_input_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeColor::get_input_port_name(int p_port) const {

	return "";
}

int VisualAccidentalNoiseNodeColor::get_output_port_count() const {

	return 1;
}

VisualAccidentalNoiseNodeColor::PortType VisualAccidentalNoiseNodeColor::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeColor::get_output_port_name(int p_port) const {
	return "";
}

void VisualAccidentalNoiseNodeColor::set_color(const Color &p_color) {

	color = p_color;
	emit_changed();
}

Color VisualAccidentalNoiseNodeColor::get_color() const {

	return color;
}

Vector<StringName> VisualAccidentalNoiseNodeColor::get_editable_properties() const {

	Vector<StringName> props;
	props.push_back("color");

	return props;
}

void VisualAccidentalNoiseNodeColor::evaluate(Ref<VisualAccidentalNoise> noise) {

	output_value = noise->color(color);
}

void VisualAccidentalNoiseNodeColor::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_color", "color"), &VisualAccidentalNoiseNodeColor::set_color);
	ClassDB::bind_method(D_METHOD("get_color"), &VisualAccidentalNoiseNodeColor::get_color);

	ADD_PROPERTY(PropertyInfo(Variant::COLOR, "color"), "set_color", "get_color");
}

VisualAccidentalNoiseNodeColor::VisualAccidentalNoiseNodeColor() {

	color = Color(1, 1, 1, 1);
}

////////////// ColorCombine

String VisualAccidentalNoiseNodeColorCombine::get_caption() const {

	return "ColorCombine";
}

void VisualAccidentalNoiseNodeColorCombine::set_input_port_value(int p_port, const Variant &p_value) {

	switch (p_port) {
		case 0: c1 = p_value; break;
		case 1: c2 = p_value; break;
		case 2: c3 = p_value; break;
		case 3: c4 = p_value; break;
	}
}

Variant VisualAccidentalNoiseNodeColorCombine::get_input_port_value(int p_port) const {

	switch (p_port) {
		case 0: return c1;
		case 1: return c2;
		case 2: return c3;
		case 3: return c4;
	}
	return Variant();
}

int VisualAccidentalNoiseNodeColorCombine::get_input_port_count() const {

	return 4;
}

VisualAccidentalNoiseNodeColorCombine::PortType VisualAccidentalNoiseNodeColorCombine::get_input_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeColorCombine::get_input_port_name(int p_port) const {

	switch (p_port) {
		case 0: return type == COMBINE_RGBA ? "r" : "h";
		case 1: return type == COMBINE_RGBA ? "g" : "s";
		case 2: return type == COMBINE_RGBA ? "b" : "v";
		case 3: return "a";
	}
	return String();
}

int VisualAccidentalNoiseNodeColorCombine::get_output_port_count() const {

	return 1;
}

VisualAccidentalNoiseNodeColorCombine::PortType VisualAccidentalNoiseNodeColorCombine::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeColorCombine::get_output_port_name(int p_port) const {
	return "";
}

void VisualAccidentalNoiseNodeColorCombine::set_type(CombineMode p_type) {

	type = p_type;
	emit_changed();
}

VisualAccidentalNoiseNodeColorCombine::CombineMode VisualAccidentalNoiseNodeColorCombine::get_type() const {

	return type;
}

Vector<StringName> VisualAccidentalNoiseNodeColorCombine::get_editable_properties() const {

	Vector<StringName> props;
	props.push_back("type");

	return props;
}

void VisualAccidentalNoiseNodeColorCombine::evaluate(Ref<VisualAccidentalNoise> noise) {

	switch (type) {

		case COMBINE_RGBA:
			output_value = noise->combine_rgba(c1, c2, c3, c4);
			break;

		case COMBINE_HSVA:
			output_value = noise->combine_hsva(c1, c2, c3, c4);
			break;
	}
}

void VisualAccidentalNoiseNodeColorCombine::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_type", "type"), &VisualAccidentalNoiseNodeColorCombine::set_type);
	ClassDB::bind_method(D_METHOD("get_type"), &VisualAccidentalNoiseNodeColorCombine::get_type);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "type", PROPERTY_HINT_ENUM, "RGBA,HSVA"), "set_type", "get_type");

	BIND_ENUM_CONSTANT(COMBINE_RGBA);
	BIND_ENUM_CONSTANT(COMBINE_HSVA);
}

VisualAccidentalNoiseNodeColorCombine::VisualAccidentalNoiseNodeColorCombine() {

	set_input_port_default_value(0, 0);
	set_input_port_default_value(1, 0);
	set_input_port_default_value(2, 0);
	set_input_port_default_value(3, 1);

	type = COMBINE_RGBA;
	c1 = c2 = c3 = c4 = 0;
}

////////////// ScaleOffset

String VisualAccidentalNoiseNodeScaleOffset::get_caption() const {

	return "ScaleOffset";
}

void VisualAccidentalNoiseNodeScaleOffset::set_scale(double p_scale) {

	scale = p_scale;
	emit_changed();
}

double VisualAccidentalNoiseNodeScaleOffset::get_scale() const {

	return scale;
}

void VisualAccidentalNoiseNodeScaleOffset::set_offset(double p_offset) {

	offset = p_offset;
	emit_changed();
}

double VisualAccidentalNoiseNodeScaleOffset::get_offset() const {

	return offset;
}

void VisualAccidentalNoiseNodeScaleOffset::set_input_port_value(int p_port, const Variant &p_value) {

	input = p_value;
}

Variant VisualAccidentalNoiseNodeScaleOffset::get_input_port_value(int p_port) const {

	return input;
}

int VisualAccidentalNoiseNodeScaleOffset::get_input_port_count() const {

	return 1;
}

VisualAccidentalNoiseNodeScaleOffset::PortType VisualAccidentalNoiseNodeScaleOffset::get_input_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeScaleOffset::get_input_port_name(int p_port) const {

	return "input";
}

int VisualAccidentalNoiseNodeScaleOffset::get_output_port_count() const {

	return 1;
}

VisualAccidentalNoiseNodeScaleOffset::PortType VisualAccidentalNoiseNodeScaleOffset::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeScaleOffset::get_output_port_name(int p_port) const {
	return "";
}

Vector<StringName> VisualAccidentalNoiseNodeScaleOffset::get_editable_properties() const {

	Vector<StringName> props;

	props.push_back("scale");
	props.push_back("offset");

	return props;
}

void VisualAccidentalNoiseNodeScaleOffset::evaluate(Ref<VisualAccidentalNoise> noise) {

	output_value = noise->scale_offset(input, scale, offset);
}

void VisualAccidentalNoiseNodeScaleOffset::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_scale", "scale"), &VisualAccidentalNoiseNodeScaleOffset::set_scale);
	ClassDB::bind_method(D_METHOD("get_scale"), &VisualAccidentalNoiseNodeScaleOffset::get_scale);

	ClassDB::bind_method(D_METHOD("set_offset", "offset"), &VisualAccidentalNoiseNodeScaleOffset::set_offset);
	ClassDB::bind_method(D_METHOD("get_offset"), &VisualAccidentalNoiseNodeScaleOffset::get_offset);

	ADD_PROPERTY(PropertyInfo(Variant::REAL, "scale"), "set_scale", "get_scale");
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "offset"), "set_offset", "get_offset");
}

VisualAccidentalNoiseNodeScaleOffset::VisualAccidentalNoiseNodeScaleOffset() {

	input = 0;
	scale = 1.0;
	offset = 0.0;
}

////////////// Layer

String VisualAccidentalNoiseNodeFractalLayer::get_caption() const {

	return "Layer";
}

void VisualAccidentalNoiseNodeFractalLayer::set_input_port_value(int p_port, const Variant &p_value) {

	switch (p_port) {
		case 0: interp = p_value; break;
		case 1: scale = p_value; break;
		case 2: frequency = p_value; break;
		case 3: seed = p_value; break;
		case 4: rot = p_value; break;
		case 5: angle = p_value; break;
		case 6: ax = p_value; break;
		case 7: ay = p_value; break;
		case 8: az = p_value; break;
	}
}

Variant VisualAccidentalNoiseNodeFractalLayer::get_input_port_value(int p_port) const {

	switch (p_port) {
		case 0: return interp;
		case 1: return scale;
		case 2: return frequency;
		case 3: return seed;
		case 4: return rot;
		case 5: return angle;
		case 6: return ax;
		case 7: return ay;
		case 8: return az;
	}
	return Variant();
}

int VisualAccidentalNoiseNodeFractalLayer::get_input_port_count() const {

	return 9;
}

VisualAccidentalNoiseNodeFractalLayer::PortType VisualAccidentalNoiseNodeFractalLayer::get_input_port_type(int p_port) const {

	return p_port != 0 ? PORT_TYPE_SCALAR : PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeFractalLayer::get_input_port_name(int p_port) const {

	switch (p_port) {
		case 0: return "interp";
		case 1: return "scale";
		case 2: return "frequency";
		case 3: return "seed";
		case 4: return "rot";
		case 5: return "angle";
		case 6: return "ax";
		case 7: return "ay";
		case 8: return "az";
	}
	return "";
}

int VisualAccidentalNoiseNodeFractalLayer::get_output_port_count() const {

	return 1;
}

VisualAccidentalNoiseNodeFractalLayer::PortType VisualAccidentalNoiseNodeFractalLayer::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeFractalLayer::get_output_port_name(int p_port) const {
	return "";
}

void VisualAccidentalNoiseNodeFractalLayer::set_type(LayerType p_type) {

	type = p_type;
	emit_changed();
}

VisualAccidentalNoiseNodeFractalLayer::LayerType VisualAccidentalNoiseNodeFractalLayer::get_type() const {

	return type;
}

void VisualAccidentalNoiseNodeFractalLayer::set_basis(AccidentalNoise::BasisTypes p_basis) {

	basis = p_basis;
	emit_changed();
}

AccidentalNoise::BasisTypes VisualAccidentalNoiseNodeFractalLayer::get_basis() const {

	return basis;
}

Vector<StringName> VisualAccidentalNoiseNodeFractalLayer::get_editable_properties() const {

	Vector<StringName> props;
	props.push_back("type");
	props.push_back("basis");

	return props;
}

void VisualAccidentalNoiseNodeFractalLayer::evaluate(Ref<VisualAccidentalNoise> noise) {

	switch (type) {

		case LAYER_FRACTAL:
			output_value = noise->fractal_layer(basis, interp, scale, frequency, seed, rot, angle, ax, ay, az);
			break;

		case LAYER_RIDGED:
			output_value = noise->ridged_layer(basis, interp, scale, frequency, seed, rot, angle, ax, ay, az);
			break;

		case LAYER_BILLOW:
			output_value = noise->billow_layer(basis, interp, scale, frequency, seed, rot, angle, ax, ay, az);
			break;
	}
}

void VisualAccidentalNoiseNodeFractalLayer::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_type", "type"), &VisualAccidentalNoiseNodeFractalLayer::set_type);
	ClassDB::bind_method(D_METHOD("get_type"), &VisualAccidentalNoiseNodeFractalLayer::get_type);

	ClassDB::bind_method(D_METHOD("set_basis", "basis"), &VisualAccidentalNoiseNodeFractalLayer::set_basis);
	ClassDB::bind_method(D_METHOD("get_basis"), &VisualAccidentalNoiseNodeFractalLayer::get_basis);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "type", PROPERTY_HINT_ENUM, "Fractal,Ridged,Billow"), "set_type", "get_type");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "basis", PROPERTY_HINT_ENUM, "Value,Gradient,Simplex"), "set_basis", "get_basis");

	BIND_ENUM_CONSTANT(LAYER_FRACTAL);
	BIND_ENUM_CONSTANT(LAYER_RIDGED);
	BIND_ENUM_CONSTANT(LAYER_BILLOW);
}

VisualAccidentalNoiseNodeFractalLayer::VisualAccidentalNoiseNodeFractalLayer() {

	type = LAYER_FRACTAL;
	basis = AccidentalNoise::BASIS_SIMPLEX;

	set_input_port_default_value(0, AccidentalNoise::INTERP_QUINTIC);
	set_input_port_default_value(1, 1.0);
	set_input_port_default_value(2, 1.0);
	set_input_port_default_value(3, 0);

	set_input_port_default_value(4, true);
	set_input_port_default_value(5, 0.5);
	set_input_port_default_value(6, 0.0);
	set_input_port_default_value(7, 0.0);
	set_input_port_default_value(8, 1.0);

	interp = 0;
	scale = 1.0;
	frequency = 1.0;
	seed = 0;

	rot = true;
	angle = 0.5;
	ax = 0.0;
	ay = 0.0;
	az = 1.0;
}

////////////// Fractal

String VisualAccidentalNoiseNodeFractal::get_caption() const {

	return "Fractal";
}

int VisualAccidentalNoiseNodeFractal::get_input_port_count() const {

	return 6;
}

void VisualAccidentalNoiseNodeFractal::set_input_port_value(int p_port, const Variant &p_value) {

	switch (p_port) {
		case 0: seed = p_value; break;
		case 1: layer = p_value; break;
		case 2: persistence = p_value; break;
		case 3: lacunarity = p_value; break;
		case 4: numoctaves = p_value; break;
		case 5: frequency = p_value; break;
	}
}

Variant VisualAccidentalNoiseNodeFractal::get_input_port_value(int p_port) const {

	switch (p_port) {
		case 0: return seed;
		case 1: return layer;
		case 2: return persistence;
		case 3: return lacunarity;
		case 4: return numoctaves;
		case 5: return frequency;
	}
	return Variant();
}

VisualAccidentalNoiseNodeFractal::PortType VisualAccidentalNoiseNodeFractal::get_input_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeFractal::get_input_port_name(int p_port) const {

	switch (p_port) {
		case 0: return "seed";
		case 1: return "layer";
		case 2: return "persistence";
		case 3: return "lacunarity";
		case 4: return "numoctaves";
		case 5: return "frequency";
	}
	return "";
}

int VisualAccidentalNoiseNodeFractal::get_output_port_count() const {

	return 1;
}

VisualAccidentalNoiseNodeFractal::PortType VisualAccidentalNoiseNodeFractal::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeFractal::get_output_port_name(int p_port) const {
	return "";
}

void VisualAccidentalNoiseNodeFractal::evaluate(Ref<VisualAccidentalNoise> noise) {

	output_value = noise->fractal(seed, layer, persistence, lacunarity, numoctaves, frequency);
}

void VisualAccidentalNoiseNodeFractal::_bind_methods() {
}

VisualAccidentalNoiseNodeFractal::VisualAccidentalNoiseNodeFractal() {

	set_input_port_default_value(0, 0);
	set_input_port_default_value(1, 0);
	set_input_port_default_value(2, 1.0);
	set_input_port_default_value(3, 1.0);
	set_input_port_default_value(4, 1);
	set_input_port_default_value(5, 1.0);

	seed = 0;
	layer = 0;
	persistence = 0;
	lacunarity = 0;
	numoctaves = 0;
	frequency = 0;
}

////////////// FractalVariant

String VisualAccidentalNoiseNodeFractalVariant::get_caption() const {

	return "FractalVariant";
}

void VisualAccidentalNoiseNodeFractalVariant::set_input_port_value(int p_port, const Variant &p_value) {

	switch (p_port) {
		case 0: numoctaves = p_value; break;
		case 1: frequency = p_value; break;
		case 2: seed = p_value; break;
		case 3: rot = p_value; break;
	}
}

Variant VisualAccidentalNoiseNodeFractalVariant::get_input_port_value(int p_port) const {

	switch (p_port) {
		case 0: return numoctaves;
		case 1: return frequency;
		case 2: return seed;
		case 3: return rot;
	}
	return Variant();
}

int VisualAccidentalNoiseNodeFractalVariant::get_input_port_count() const {

	return 4;
}

VisualAccidentalNoiseNodeFractalVariant::PortType VisualAccidentalNoiseNodeFractalVariant::get_input_port_type(int p_port) const {

	return PORT_TYPE_SCALAR;
}

String VisualAccidentalNoiseNodeFractalVariant::get_input_port_name(int p_port) const {

	switch (p_port) {
		case 0: return "numoctaves";
		case 1: return "frequency";
		case 2: return "seed";
		case 3: return "rot";
	}
	return "";
}

int VisualAccidentalNoiseNodeFractalVariant::get_output_port_count() const {

	return 1;
}

VisualAccidentalNoiseNodeFractalVariant::PortType VisualAccidentalNoiseNodeFractalVariant::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeFractalVariant::get_output_port_name(int p_port) const {
	return "";
}

void VisualAccidentalNoiseNodeFractalVariant::set_type(FractalType p_type) {

	type = p_type;
	emit_changed();
}

VisualAccidentalNoiseNodeFractalVariant::FractalType VisualAccidentalNoiseNodeFractalVariant::get_type() const {

	return type;
}

void VisualAccidentalNoiseNodeFractalVariant::set_basis(AccidentalNoise::BasisTypes p_basis) {

	basis = p_basis;
	emit_changed();
}

AccidentalNoise::BasisTypes VisualAccidentalNoiseNodeFractalVariant::get_basis() const {

	return basis;
}

void VisualAccidentalNoiseNodeFractalVariant::set_interpolation(AccidentalNoise::InterpolationTypes p_interpolation) {

	interpolation = p_interpolation;
	emit_changed();
}

AccidentalNoise::InterpolationTypes VisualAccidentalNoiseNodeFractalVariant::get_interpolation() const {

	return interpolation;
}

Vector<StringName> VisualAccidentalNoiseNodeFractalVariant::get_editable_properties() const {

	Vector<StringName> props;
	props.push_back("type");
	props.push_back("basis");
	props.push_back("interpolation");

	return props;
}

void VisualAccidentalNoiseNodeFractalVariant::evaluate(Ref<VisualAccidentalNoise> noise) {

	switch (type) {

		case TYPE_FBM:
			output_value = noise->fbm(basis, interpolation, numoctaves, frequency, seed, rot);
			break;

		case TYPE_RIDGED_MULTIFRACTAL:
			output_value = noise->ridged_multifractal(basis, interpolation, numoctaves, frequency, seed, rot);
			break;

		case TYPE_BILLOW:
			output_value = noise->billow(basis, interpolation, numoctaves, frequency, seed, rot);
			break;
	}
}

void VisualAccidentalNoiseNodeFractalVariant::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_type", "type"), &VisualAccidentalNoiseNodeFractalVariant::set_type);
	ClassDB::bind_method(D_METHOD("get_type"), &VisualAccidentalNoiseNodeFractalVariant::get_type);

	ClassDB::bind_method(D_METHOD("set_basis", "basis"), &VisualAccidentalNoiseNodeFractalVariant::set_basis);
	ClassDB::bind_method(D_METHOD("get_basis"), &VisualAccidentalNoiseNodeFractalVariant::get_basis);

	ClassDB::bind_method(D_METHOD("set_interpolation", "interpolation"), &VisualAccidentalNoiseNodeFractalVariant::set_interpolation);
	ClassDB::bind_method(D_METHOD("get_interpolation"), &VisualAccidentalNoiseNodeFractalVariant::get_interpolation);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "type", PROPERTY_HINT_ENUM, "Fractal,Ridged,Billow"), "set_type", "get_type");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "basis", PROPERTY_HINT_ENUM, "Value,Gradient,Simplex"), "set_basis", "get_basis");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "interpolation", PROPERTY_HINT_ENUM, "None,Linear,Hermite,Quintic"), "set_interpolation", "get_interpolation");

	BIND_ENUM_CONSTANT(TYPE_FBM);
	BIND_ENUM_CONSTANT(TYPE_RIDGED_MULTIFRACTAL);
	BIND_ENUM_CONSTANT(TYPE_BILLOW);
}

VisualAccidentalNoiseNodeFractalVariant::VisualAccidentalNoiseNodeFractalVariant() {

	type = TYPE_FBM;
	basis = AccidentalNoise::BASIS_SIMPLEX;
	interpolation = AccidentalNoise::INTERP_QUINTIC;

	set_input_port_default_value(0, 1);
	set_input_port_default_value(1, 1.0);
	set_input_port_default_value(2, 0);
	set_input_port_default_value(3, true);

	numoctaves = 1;
	frequency = 1.0;
	seed = 0;
	rot = true;
}

////////////// SetVar

String VisualAccidentalNoiseNodeSetVar::get_caption() const {

	return "SetVar";
}

void VisualAccidentalNoiseNodeSetVar::set_var(const String &p_var) {

	var = p_var;
	emit_changed();
}

String VisualAccidentalNoiseNodeSetVar::get_var() const {

	return var;
}

void VisualAccidentalNoiseNodeSetVar::set_value(double p_value) {

	value = p_value;
	emit_changed();
}

double VisualAccidentalNoiseNodeSetVar::get_value() const {

	return value;
}

void VisualAccidentalNoiseNodeSetVar::set_input_port_value(int p_port, const Variant &p_value) {

	value = p_value;
}

Variant VisualAccidentalNoiseNodeSetVar::get_input_port_value(int p_port) const {

	return value;
}

int VisualAccidentalNoiseNodeSetVar::get_input_port_count() const {

	return 0;
}

VisualAccidentalNoiseNodeSetVar::PortType VisualAccidentalNoiseNodeSetVar::get_input_port_type(int p_port) const {

	return PORT_TYPE_SCALAR;
}

String VisualAccidentalNoiseNodeSetVar::get_input_port_name(int p_port) const {

	return "value";
}

int VisualAccidentalNoiseNodeSetVar::get_output_port_count() const {

	return 0;
}

VisualAccidentalNoiseNodeSetVar::PortType VisualAccidentalNoiseNodeSetVar::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeSetVar::get_output_port_name(int p_port) const {
	return "";
}

Vector<StringName> VisualAccidentalNoiseNodeSetVar::get_editable_properties() const {

	Vector<StringName> props;

	props.push_back("value");

	return props;
}

void VisualAccidentalNoiseNodeSetVar::evaluate(Ref<VisualAccidentalNoise> noise) {

	noise->set_var(var, value);
}

void VisualAccidentalNoiseNodeSetVar::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_var", "var"), &VisualAccidentalNoiseNodeSetVar::set_var);
	ClassDB::bind_method(D_METHOD("get_var"), &VisualAccidentalNoiseNodeSetVar::get_var);

	ClassDB::bind_method(D_METHOD("set_value", "value"), &VisualAccidentalNoiseNodeSetVar::set_value);
	ClassDB::bind_method(D_METHOD("get_value"), &VisualAccidentalNoiseNodeSetVar::get_value);

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "var"), "set_var", "get_var");
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "value"), "set_value", "get_value");
}

VisualAccidentalNoiseNodeSetVar::VisualAccidentalNoiseNodeSetVar() {

	var = "name";
	value = 0.0;
}

////////////// GetVar

String VisualAccidentalNoiseNodeGetVar::get_caption() const {

	return "GetVar";
}

void VisualAccidentalNoiseNodeGetVar::set_var(const String &p_var) {

	var = p_var;
	emit_changed();
}

String VisualAccidentalNoiseNodeGetVar::get_var() const {

	return var;
}

int VisualAccidentalNoiseNodeGetVar::get_input_port_count() const {

	return 0;
}

VisualAccidentalNoiseNodeGetVar::PortType VisualAccidentalNoiseNodeGetVar::get_input_port_type(int p_port) const {

	return PORT_TYPE_SCALAR;
}

String VisualAccidentalNoiseNodeGetVar::get_input_port_name(int p_port) const {

	return "value";
}

int VisualAccidentalNoiseNodeGetVar::get_output_port_count() const {

	return 1;
}

VisualAccidentalNoiseNodeGetVar::PortType VisualAccidentalNoiseNodeGetVar::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeGetVar::get_output_port_name(int p_port) const {
	return "";
}

void VisualAccidentalNoiseNodeGetVar::evaluate(Ref<VisualAccidentalNoise> noise) {

	output_value = noise->get_var(var);
}

void VisualAccidentalNoiseNodeGetVar::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_var", "var"), &VisualAccidentalNoiseNodeGetVar::set_var);
	ClassDB::bind_method(D_METHOD("get_var"), &VisualAccidentalNoiseNodeGetVar::get_var);

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "var"), "set_var", "get_var");
}

VisualAccidentalNoiseNodeGetVar::VisualAccidentalNoiseNodeGetVar() {

	var = "name";
}

////////////// Reroute

String VisualAccidentalNoiseNodeReroute::get_caption() const {

	return "Reroute";
}

void VisualAccidentalNoiseNodeReroute::set_input_port_value(int p_port, const Variant &p_value) {

	input = p_value;
}

Variant VisualAccidentalNoiseNodeReroute::get_input_port_value(int p_port) const {

	return input;
}

int VisualAccidentalNoiseNodeReroute::get_input_port_count() const {

	return 1;
}

VisualAccidentalNoiseNodeReroute::PortType VisualAccidentalNoiseNodeReroute::get_input_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeReroute::get_input_port_name(int p_port) const {

	return "";
}

int VisualAccidentalNoiseNodeReroute::get_output_port_count() const {

	return 1;
}

VisualAccidentalNoiseNodeReroute::PortType VisualAccidentalNoiseNodeReroute::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeReroute::get_output_port_name(int p_port) const {
	return "";
}

void VisualAccidentalNoiseNodeReroute::evaluate(Ref<VisualAccidentalNoise> noise) {

	output_value = input;
}

void VisualAccidentalNoiseNodeReroute::_bind_methods() {
}

VisualAccidentalNoiseNodeReroute::VisualAccidentalNoiseNodeReroute() {

	input = 0;
}
////////////// Sequence

String VisualAccidentalNoiseNodeSequence::get_caption() const {

	return "Sequence";
}

void VisualAccidentalNoiseNodeSequence::set_operator(Operator p_op) {

	op = p_op;
	emit_changed();
}

VisualAccidentalNoiseNodeSequence::Operator VisualAccidentalNoiseNodeSequence::get_operator() const {

	return op;
}

void VisualAccidentalNoiseNodeSequence::set_input_count(int p_input_count) {

	input_count = CLAMP(p_input_count, MIN_INPUTS, MAX_INPUTS);
	emit_changed();
}

int VisualAccidentalNoiseNodeSequence::get_input_count() const {

	return input_count;
}

void VisualAccidentalNoiseNodeSequence::set_selected_input(int p_input) {

	selected_input = CLAMP(p_input, 1, input_count);
	emit_changed();
}

int VisualAccidentalNoiseNodeSequence::get_selected_input() {

	return selected_input;
}

void VisualAccidentalNoiseNodeSequence::set_input_port_value(int p_port, const Variant &p_value) {

	int idx = CLAMP(p_port, 0, MAX_INPUTS - 1);
	inputs[idx] = p_value;
}

Variant VisualAccidentalNoiseNodeSequence::get_input_port_value(int p_port) const {

	int idx = CLAMP(p_port, 0, MAX_INPUTS - 1);
	return inputs[idx];
}

int VisualAccidentalNoiseNodeSequence::get_input_port_count() const {

	return input_count;
}

VisualAccidentalNoiseNodeSequence::PortType VisualAccidentalNoiseNodeSequence::get_input_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeSequence::get_input_port_name(int p_port) const {

	return itos(p_port + 1);
}

int VisualAccidentalNoiseNodeSequence::get_output_port_count() const {

	return 1;
}

VisualAccidentalNoiseNodeSequence::PortType VisualAccidentalNoiseNodeSequence::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAccidentalNoiseNodeSequence::get_output_port_name(int p_port) const {

	String name;
	if (op == OP_SELECT) {
		name = itos(selected_input);
	}
	return name;
}

void VisualAccidentalNoiseNodeSequence::evaluate(Ref<VisualAccidentalNoise> noise) {

	String op_func;

	switch (op) {
		case OP_SELECT: output_value = inputs[selected_input - 1]; return; // no op
		case OP_ADD: op_func = "add"; break;
		case OP_SUB: op_func = "subtract"; break;
		case OP_MUL: op_func = "multiply"; break;
		case OP_DIV: op_func = "divide"; break;
		case OP_POW: op_func = "pow"; break;
		case OP_MAX: op_func = "max"; break;
		case OP_MIN: op_func = "min"; break;
		case OP_BIAS: op_func = "bias"; break;
		case OP_GAIN: op_func = "gain"; break;
	}

	if (input_count < 2) {
		output_value = 0;
		return;
	}
	output_value = inputs[0];

	for (int i = 1; i < input_count; i++) {
		Index next = inputs[i];
		output_value = noise->call(op_func, output_value, next);
	}
}

Vector<StringName> VisualAccidentalNoiseNodeSequence::get_editable_properties() const {

	Vector<StringName> props;

	props.push_back("operator");
	props.push_back("input_count");

	if (op == OP_SELECT && input_count > 1) {
		props.push_back("selected_input");
	}
	return props;
}

void VisualAccidentalNoiseNodeSequence::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_operator", "operator"), &VisualAccidentalNoiseNodeSequence::set_operator);
	ClassDB::bind_method(D_METHOD("get_operator"), &VisualAccidentalNoiseNodeSequence::get_operator);

	ClassDB::bind_method(D_METHOD("set_input_count", "input_count"), &VisualAccidentalNoiseNodeSequence::set_input_count);
	ClassDB::bind_method(D_METHOD("get_input_count"), &VisualAccidentalNoiseNodeSequence::get_input_count);

	ClassDB::bind_method(D_METHOD("set_selected_input", "selected_input"), &VisualAccidentalNoiseNodeSequence::set_selected_input);
	ClassDB::bind_method(D_METHOD("get_selected_input"), &VisualAccidentalNoiseNodeSequence::get_selected_input);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "operator", PROPERTY_HINT_ENUM, "Select,Add,Sub,Multiply,Divide,Power,Max,Min,Bias,Gain"), "set_operator", "get_operator");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "input_count"), "set_input_count", "get_input_count");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "selected_input"), "set_selected_input", "get_selected_input");
}

VisualAccidentalNoiseNodeSequence::VisualAccidentalNoiseNodeSequence() {

	op = OP_SELECT;
	input_count = MIN_INPUTS;
	selected_input = 1; // not based on zero index

	for (int i = 0; i < MAX_INPUTS; i++) {
		inputs[i] = 0;
		set_input_port_default_value(i, 0);
	}
}
