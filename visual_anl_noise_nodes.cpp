#include "visual_anl_noise_nodes.h"

////////////// Scalar

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

////////////// Seed

String VisualAnlNoiseNodeSeed::get_caption() const {

	return "Seed";
}

int VisualAnlNoiseNodeSeed::get_input_port_count() const {

	return 0;
}

VisualAnlNoiseNodeSeed::PortType VisualAnlNoiseNodeSeed::get_input_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAnlNoiseNodeSeed::get_input_port_name(int p_port) const {

	return String();
}

int VisualAnlNoiseNodeSeed::get_output_port_count() const {

	return 1;
}

VisualAnlNoiseNodeSeed::PortType VisualAnlNoiseNodeSeed::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAnlNoiseNodeSeed::get_output_port_name(int p_port) const {
	return "";
}

void VisualAnlNoiseNodeSeed::set_seed(unsigned int p_value) {

	seed = p_value;
	emit_changed();
}

unsigned int VisualAnlNoiseNodeSeed::get_seed() const {

	return seed;
}

Vector<StringName> VisualAnlNoiseNodeSeed::get_editable_properties() const {

	Vector<StringName> props;

	props.push_back("seed");

	return props;
}

void VisualAnlNoiseNodeSeed::evaluate(Ref<VisualAnlNoise> noise) {

	output_value = noise->seed(seed);
}

void VisualAnlNoiseNodeSeed::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_seed", "seed"), &VisualAnlNoiseNodeSeed::set_seed);
	ClassDB::bind_method(D_METHOD("get_seed"), &VisualAnlNoiseNodeSeed::get_seed);

	ADD_PROPERTY(PropertyInfo(Variant::REAL, "seed"), "set_seed", "get_seed"); // REAL: hack for editing
}

VisualAnlNoiseNodeSeed::VisualAnlNoiseNodeSeed() {

	seed = 0;
}

////////////// Seeder

String VisualAnlNoiseNodeSeeder::get_caption() const {

	return "Seeder";
}

int VisualAnlNoiseNodeSeeder::get_input_port_count() const {

	return 2;
}

void VisualAnlNoiseNodeSeeder::set_input_port_value(int p_port, const Variant &p_value) {

	p_port == 0 ? (seed = p_value) : (input = p_value);
}

Variant VisualAnlNoiseNodeSeeder::get_input_port_value(int p_port) const {

	return p_port == 0 ? seed : input;
}

VisualAnlNoiseNodeSeeder::PortType VisualAnlNoiseNodeSeeder::get_input_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAnlNoiseNodeSeeder::get_input_port_name(int p_port) const {

	return p_port == 0 ? "seed" : "input";
}

int VisualAnlNoiseNodeSeeder::get_output_port_count() const {

	return 1;
}

VisualAnlNoiseNodeSeeder::PortType VisualAnlNoiseNodeSeeder::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAnlNoiseNodeSeeder::get_output_port_name(int p_port) const {
	return "";
}

void VisualAnlNoiseNodeSeeder::evaluate(Ref<VisualAnlNoise> noise) {

	output_value = noise->seeder(seed, input);
}

void VisualAnlNoiseNodeSeeder::_bind_methods() {

}

VisualAnlNoiseNodeSeeder::VisualAnlNoiseNodeSeeder() {

	set_input_port_default_value(0, 0);
	set_input_port_default_value(1, 0);

	seed = 0;
	input = 0;
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

		case OP_BIAS:
			output_value = noise->bias(a, b);
			break;

		case OP_GAIN:
			output_value = noise->gain(a, b);
			break;
	}
}

void VisualAnlNoiseNodeScalarOp::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_operator", "operator"), &VisualAnlNoiseNodeScalarOp::set_operator);
	ClassDB::bind_method(D_METHOD("get_operator"), &VisualAnlNoiseNodeScalarOp::get_operator);

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

VisualAnlNoiseNodeScalarOp::VisualAnlNoiseNodeScalarOp() {

	set_input_port_default_value(0, 0);
	set_input_port_default_value(1, 0);

	a = b = 0;
	op = OP_ADD;
}

////////////// ScalarFunc

String VisualAnlNoiseNodeScalarFunc::get_caption() const {

	return "ScalarFunc";
}

int VisualAnlNoiseNodeScalarFunc::get_input_port_count() const {

	return 1;
}

void VisualAnlNoiseNodeScalarFunc::set_input_port_value(int p_port, const Variant &p_value) {

	input = p_value;
}

Variant VisualAnlNoiseNodeScalarFunc::get_input_port_value(int p_port) const {

	return input;
}

VisualAnlNoiseNodeScalarFunc::PortType VisualAnlNoiseNodeScalarFunc::get_input_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAnlNoiseNodeScalarFunc::get_input_port_name(int p_port) const {

	return "input";
}

int VisualAnlNoiseNodeScalarFunc::get_output_port_count() const {

	return 1;
}

VisualAnlNoiseNodeScalarFunc::PortType VisualAnlNoiseNodeScalarFunc::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAnlNoiseNodeScalarFunc::get_output_port_name(int p_port) const {
	return "";
}

void VisualAnlNoiseNodeScalarFunc::set_function(Function p_func) {

	func = p_func;
	emit_changed();
}

VisualAnlNoiseNodeScalarFunc::Function VisualAnlNoiseNodeScalarFunc::get_function() const {

	return func;
}

Vector<StringName> VisualAnlNoiseNodeScalarFunc::get_editable_properties() const {

	Vector<StringName> props;
	props.push_back("function");

	return props;
}

void VisualAnlNoiseNodeScalarFunc::evaluate(Ref<VisualAnlNoise> noise) {

	switch(func) {

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

void VisualAnlNoiseNodeScalarFunc::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_function", "function"), &VisualAnlNoiseNodeScalarFunc::set_function);
	ClassDB::bind_method(D_METHOD("get_function"), &VisualAnlNoiseNodeScalarFunc::get_function);

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

VisualAnlNoiseNodeScalarFunc::VisualAnlNoiseNodeScalarFunc() {

	set_input_port_default_value(0, 0);

	func = FUNC_COS;
}

////////////// Value Basis

String VisualAnlNoiseNodeValueBasis::get_caption() const {

	return "ValueBasis";
}

int VisualAnlNoiseNodeValueBasis::get_input_port_count() const {

	return 2;
}

void VisualAnlNoiseNodeValueBasis::set_input_port_value(int p_port, const Variant &p_value) {

	p_port == 0 ? interp = p_value : seed = p_value;
}

Variant VisualAnlNoiseNodeValueBasis::get_input_port_value(int p_port) const {

	return p_port == 0 ? interp : seed;
}

VisualAnlNoiseNodeValueBasis::PortType VisualAnlNoiseNodeValueBasis::get_input_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAnlNoiseNodeValueBasis::get_input_port_name(int p_port) const {

	return p_port == 0 ? "interp" : "seed";
}

int VisualAnlNoiseNodeValueBasis::get_output_port_count() const {

	return 1;
}

VisualAnlNoiseNodeValueBasis::PortType VisualAnlNoiseNodeValueBasis::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAnlNoiseNodeValueBasis::get_output_port_name(int p_port) const {

	return "";
}

void VisualAnlNoiseNodeValueBasis::set_seed(Index p_seed) {

	seed = p_seed;
	emit_changed();
}

Index VisualAnlNoiseNodeValueBasis::get_seed() const {

	return seed;
}

void VisualAnlNoiseNodeValueBasis::set_interpolation(Index p_interp) {

	interp = p_interp;
	emit_changed();
}

Index VisualAnlNoiseNodeValueBasis::get_interpolation() const {

	return interp;
}

void VisualAnlNoiseNodeValueBasis::evaluate(Ref<VisualAnlNoise> noise) {

	output_value = noise->value_basis(interp, seed);
}

void VisualAnlNoiseNodeValueBasis::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_interpolation", "value"), &VisualAnlNoiseNodeValueBasis::set_interpolation);
	ClassDB::bind_method(D_METHOD("get_interpolation"), &VisualAnlNoiseNodeValueBasis::get_interpolation);

	ClassDB::bind_method(D_METHOD("set_seed", "value"), &VisualAnlNoiseNodeValueBasis::set_seed);
	ClassDB::bind_method(D_METHOD("get_seed"), &VisualAnlNoiseNodeValueBasis::get_seed);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "interpolation"), "set_interpolation", "get_interpolation");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "seed"), "set_seed", "get_seed");
}

VisualAnlNoiseNodeValueBasis::VisualAnlNoiseNodeValueBasis() {

	set_input_port_default_value(0, anl::INTERP_QUINTIC);
	set_input_port_default_value(1, 0);

	interp = 0;
	seed = 0;
}

////////////// Gradient Basis

String VisualAnlNoiseNodeGradientBasis::get_caption() const {

	return "GradientBasis";
}

int VisualAnlNoiseNodeGradientBasis::get_input_port_count() const {

	return 2;
}

void VisualAnlNoiseNodeGradientBasis::set_input_port_value(int p_port, const Variant &p_value) {

	p_port == 0 ? interp = p_value : seed = p_value;
}

Variant VisualAnlNoiseNodeGradientBasis::get_input_port_value(int p_port) const {

	return p_port == 0 ? interp : seed;
}

VisualAnlNoiseNodeGradientBasis::PortType VisualAnlNoiseNodeGradientBasis::get_input_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAnlNoiseNodeGradientBasis::get_input_port_name(int p_port) const {

	return p_port == 0 ? "interp" : "seed";
}

int VisualAnlNoiseNodeGradientBasis::get_output_port_count() const {

	return 1;
}

VisualAnlNoiseNodeGradientBasis::PortType VisualAnlNoiseNodeGradientBasis::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAnlNoiseNodeGradientBasis::get_output_port_name(int p_port) const {

	return "";
}

void VisualAnlNoiseNodeGradientBasis::set_seed(Index p_seed) {

	seed = p_seed;
	emit_changed();
}

Index VisualAnlNoiseNodeGradientBasis::get_seed() const {

	return seed;
}

void VisualAnlNoiseNodeGradientBasis::set_interpolation(Index p_interp) {

	interp = p_interp;
	emit_changed();
}

Index VisualAnlNoiseNodeGradientBasis::get_interpolation() const {

	return interp;
}

void VisualAnlNoiseNodeGradientBasis::evaluate(Ref<VisualAnlNoise> noise) {

	output_value = noise->gradient_basis(interp, seed);
}

void VisualAnlNoiseNodeGradientBasis::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_interpolation", "value"), &VisualAnlNoiseNodeGradientBasis::set_interpolation);
	ClassDB::bind_method(D_METHOD("get_interpolation"), &VisualAnlNoiseNodeGradientBasis::get_interpolation);

	ClassDB::bind_method(D_METHOD("set_seed", "value"), &VisualAnlNoiseNodeGradientBasis::set_seed);
	ClassDB::bind_method(D_METHOD("get_seed"), &VisualAnlNoiseNodeGradientBasis::get_seed);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "interpolation"), "set_interpolation", "get_interpolation");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "seed"), "set_seed", "get_seed");
}

VisualAnlNoiseNodeGradientBasis::VisualAnlNoiseNodeGradientBasis() {

	set_input_port_default_value(0, anl::INTERP_QUINTIC);
	set_input_port_default_value(1, 0);

	interp = 0;
	seed = 0;
}

////////////// Cellular Basis

String VisualAnlNoiseNodeCellularBasis::get_caption() const {

	return "CellularBasis";
}

int VisualAnlNoiseNodeCellularBasis::get_input_port_count() const {

	return 10;
}

void VisualAnlNoiseNodeCellularBasis::set_input_port_value(int p_port, const Variant &p_value) {

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

Variant VisualAnlNoiseNodeCellularBasis::get_input_port_value(int p_port) const {

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

VisualAnlNoiseNodeCellularBasis::PortType VisualAnlNoiseNodeCellularBasis::get_input_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAnlNoiseNodeCellularBasis::get_input_port_name(int p_port) const {

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

int VisualAnlNoiseNodeCellularBasis::get_output_port_count() const {

	return 1;
}

VisualAnlNoiseNodeCellularBasis::PortType VisualAnlNoiseNodeCellularBasis::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAnlNoiseNodeCellularBasis::get_output_port_name(int p_port) const {

	return "";
}

void VisualAnlNoiseNodeCellularBasis::set_seed(Index p_seed) {

	seed = p_seed;
	emit_changed();
}

Index VisualAnlNoiseNodeCellularBasis::get_seed() const {

	return seed;
}

void VisualAnlNoiseNodeCellularBasis::set_distance(Index p_distance) {

	distance = p_distance;
	emit_changed();
}

Index VisualAnlNoiseNodeCellularBasis::get_distance() const {

	return distance;
}

void VisualAnlNoiseNodeCellularBasis::evaluate(Ref<VisualAnlNoise> noise) {

	output_value = noise->cellular_basis(f1, f2, f3, f4, d1, d2, d3, d4, distance, seed);
}

void VisualAnlNoiseNodeCellularBasis::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_distance", "value"), &VisualAnlNoiseNodeCellularBasis::set_distance);
	ClassDB::bind_method(D_METHOD("get_distance"), &VisualAnlNoiseNodeCellularBasis::get_distance);

	ClassDB::bind_method(D_METHOD("set_seed", "value"), &VisualAnlNoiseNodeCellularBasis::set_seed);
	ClassDB::bind_method(D_METHOD("get_seed"), &VisualAnlNoiseNodeCellularBasis::get_seed);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "distance"), "set_distance", "get_distance");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "seed"), "set_seed", "get_seed");
}

VisualAnlNoiseNodeCellularBasis::VisualAnlNoiseNodeCellularBasis() {

	set_input_port_default_value(0, -1);
	set_input_port_default_value(1, 1);
	set_input_port_default_value(2, 0);
	set_input_port_default_value(3, 0);

	set_input_port_default_value(4, 0);
	set_input_port_default_value(5, 0);
	set_input_port_default_value(6, 0);
	set_input_port_default_value(7, 0);

	set_input_port_default_value(8, anl::DISTANCE_EUCLID);
	set_input_port_default_value(9, 0);

	f1 = f2 = f3 = f4 = 0;
	d1 = d2 = d3 = d4 = 0;
	distance = 0;
	seed = 0;
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

	return "seed";
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

void VisualAnlNoiseNodeSimplexBasis::evaluate(Ref<VisualAnlNoise> noise) {

	output_value = noise->simplex_basis(seed);
}

void VisualAnlNoiseNodeSimplexBasis::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_seed", "value"), &VisualAnlNoiseNodeSimplexBasis::set_seed);
	ClassDB::bind_method(D_METHOD("get_seed"), &VisualAnlNoiseNodeSimplexBasis::get_seed);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "seed"), "set_seed", "get_seed");
}

VisualAnlNoiseNodeSimplexBasis::VisualAnlNoiseNodeSimplexBasis() {

	set_input_port_default_value(0, 0);

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

	p_port == 0 ? input = p_value : by = p_value;
}

Variant VisualAnlNoiseNodeTranslate::get_input_port_value(int p_port) const {

	return p_port == 0 ? input : by;
}

VisualAnlNoiseNodeTranslate::PortType VisualAnlNoiseNodeTranslate::get_input_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAnlNoiseNodeTranslate::get_input_port_name(int p_port) const {

	return p_port == 0 ? "input" : "by";
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
	output_value = noise->call(m, input, by);
}

void VisualAnlNoiseNodeTranslate::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_axis", "axis"), &VisualAnlNoiseNodeTranslate::set_axis);
	ClassDB::bind_method(D_METHOD("get_axis"), &VisualAnlNoiseNodeTranslate::get_axis);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "axis", PROPERTY_HINT_ENUM, Axis::get_hints()), "set_axis", "get_axis");
}

VisualAnlNoiseNodeTranslate::VisualAnlNoiseNodeTranslate() {

	set_input_port_default_value(0, 0);
	set_input_port_default_value(1, 0);

	input = 0;
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

	p_port == 0 ? input = p_value : by = p_value;
}

Variant VisualAnlNoiseNodeScale::get_input_port_value(int p_port) const {

	return p_port == 0 ? input : by;
}

VisualAnlNoiseNodeScale::PortType VisualAnlNoiseNodeScale::get_input_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAnlNoiseNodeScale::get_input_port_name(int p_port) const {

	return p_port == 0 ? "input" : "by";
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
	output_value = noise->call(m, input, by);
}

void VisualAnlNoiseNodeScale::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_axis", "axis"), &VisualAnlNoiseNodeScale::set_axis);
	ClassDB::bind_method(D_METHOD("get_axis"), &VisualAnlNoiseNodeScale::get_axis);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "axis", PROPERTY_HINT_ENUM, Axis::get_hints()), "set_axis", "get_axis");
}

VisualAnlNoiseNodeScale::VisualAnlNoiseNodeScale() {

	set_input_port_default_value(0, 0);
	set_input_port_default_value(1, 1);

	input = 0;
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
		case 0: input = p_value; break;
		case 1: angle = p_value; break;
		case 2: ax = p_value; break;
		case 3: ay = p_value; break;
		case 4: az = p_value; break;
	}
}

Variant VisualAnlNoiseNodeRotate::get_input_port_value(int p_port) const {

	switch (p_port) {
		case 0: return input;
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
		case 0: return "input";
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

	output_value = noise->rotate(input, angle, ax, ay, az);
}

void VisualAnlNoiseNodeRotate::_bind_methods() {

}

VisualAnlNoiseNodeRotate::VisualAnlNoiseNodeRotate() {

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

String VisualAnlNoiseNodeClamp::get_caption() const {

	return "Clamp";
}

int VisualAnlNoiseNodeClamp::get_input_port_count() const {

	return 3;
}

void VisualAnlNoiseNodeClamp::set_input_port_value(int p_port, const Variant &p_value) {

	switch (p_port) {
		case 0: input = p_value; break;
		case 1: low = p_value; break;
		case 2: high = p_value; break;
	}
}

Variant VisualAnlNoiseNodeClamp::get_input_port_value(int p_port) const {

	switch (p_port) {
		case 0: return input;
		case 1: return low;
		case 2: return high;
	}
	return Variant();
}

VisualAnlNoiseNodeClamp::PortType VisualAnlNoiseNodeClamp::get_input_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAnlNoiseNodeClamp::get_input_port_name(int p_port) const {

	switch (p_port) {
		case 0: return "input";
		case 1: return "low";
		case 2: return "high";
	}
	return "";
}

int VisualAnlNoiseNodeClamp::get_output_port_count() const {

	return 1;
}

VisualAnlNoiseNodeClamp::PortType VisualAnlNoiseNodeClamp::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAnlNoiseNodeClamp::get_output_port_name(int p_port) const {
	return "";
}

void VisualAnlNoiseNodeClamp::evaluate(Ref<VisualAnlNoise> noise) {

	output_value = noise->clamp(input, low, high);
}

void VisualAnlNoiseNodeClamp::_bind_methods() {

}

VisualAnlNoiseNodeClamp::VisualAnlNoiseNodeClamp() {

	set_input_port_default_value(0, 0);
	set_input_port_default_value(1, 0);
	set_input_port_default_value(2, 1);

	input = 0;
	low = high = 0;
}

////////////// Mix

String VisualAnlNoiseNodeMix::get_caption() const {

	return "Mix";
}

int VisualAnlNoiseNodeMix::get_input_port_count() const {

	return 3;
}

void VisualAnlNoiseNodeMix::set_input_port_value(int p_port, const Variant &p_value) {

	switch (p_port) {
		case 0: low = p_value; break;
		case 1: high = p_value; break;
		case 2: control = p_value; break;
	}
}

Variant VisualAnlNoiseNodeMix::get_input_port_value(int p_port) const {

	switch (p_port) {
		case 0: return low;
		case 1: return high;
		case 2: return control;
	}
	return Variant();
}

VisualAnlNoiseNodeMix::PortType VisualAnlNoiseNodeMix::get_input_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAnlNoiseNodeMix::get_input_port_name(int p_port) const {

	switch (p_port) {
		case 0: return "low";
		case 1: return "high";
		case 2: return "control";
	}
	return "";
}

int VisualAnlNoiseNodeMix::get_output_port_count() const {

	return 1;
}

VisualAnlNoiseNodeMix::PortType VisualAnlNoiseNodeMix::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAnlNoiseNodeMix::get_output_port_name(int p_port) const {
	return "";
}

void VisualAnlNoiseNodeMix::evaluate(Ref<VisualAnlNoise> noise) {

	output_value = noise->mix(low, high, control);
}

void VisualAnlNoiseNodeMix::_bind_methods() {

}

VisualAnlNoiseNodeMix::VisualAnlNoiseNodeMix() {

	set_input_port_default_value(0, 0);
	set_input_port_default_value(1, 1);
	set_input_port_default_value(2, 0);

	low = high = 0;
	control = 0;
}

////////////// Select

String VisualAnlNoiseNodeSelect::get_caption() const {

	return "Select";
}

int VisualAnlNoiseNodeSelect::get_input_port_count() const {

	return 5;
}

void VisualAnlNoiseNodeSelect::set_input_port_value(int p_port, const Variant &p_value) {

	switch (p_port) {
		case 0: low = p_value; break;
		case 1: high = p_value; break;
		case 2: control = p_value; break;
		case 3: threshold = p_value; break;
		case 4: falloff = p_value; break;
	}
}

Variant VisualAnlNoiseNodeSelect::get_input_port_value(int p_port) const {

	switch (p_port) {
		case 0: return low;
		case 1: return high;
		case 2: return control;
		case 3: return threshold;
		case 4: return falloff;
	}
	return Variant();
}

VisualAnlNoiseNodeSelect::PortType VisualAnlNoiseNodeSelect::get_input_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAnlNoiseNodeSelect::get_input_port_name(int p_port) const {

	switch (p_port) {
		case 0: return "low";
		case 1: return "high";
		case 2: return "control";
		case 3: return "threshold";
		case 4: return "falloff";
	}
	return "";
}

int VisualAnlNoiseNodeSelect::get_output_port_count() const {

	return 1;
}

VisualAnlNoiseNodeSelect::PortType VisualAnlNoiseNodeSelect::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAnlNoiseNodeSelect::get_output_port_name(int p_port) const {
	return "";
}

void VisualAnlNoiseNodeSelect::evaluate(Ref<VisualAnlNoise> noise) {

	output_value = noise->select(low, high, control, threshold, falloff);
}

void VisualAnlNoiseNodeSelect::_bind_methods() {

}

VisualAnlNoiseNodeSelect::VisualAnlNoiseNodeSelect() {

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

String VisualAnlNoiseNodeTiers::get_caption() const {

	return "Tiers";
}

void VisualAnlNoiseNodeTiers::set_smooth(Smoothness p_smooth) {

	smooth = p_smooth;
	emit_changed();
}

VisualAnlNoiseNodeTiers::Smoothness VisualAnlNoiseNodeTiers::get_smooth() const {

	return smooth;
}

int VisualAnlNoiseNodeTiers::get_input_port_count() const {

	return 2;
}

void VisualAnlNoiseNodeTiers::set_input_port_value(int p_port, const Variant &p_value) {

	switch (p_port) {
		case 0: input = p_value; break;
		case 1: tiers = p_value; break;
	}
}

Variant VisualAnlNoiseNodeTiers::get_input_port_value(int p_port) const {

	switch (p_port) {
		case 0: return input;
		case 1: return tiers;
	}
	return Variant();
}

VisualAnlNoiseNodeTiers::PortType VisualAnlNoiseNodeTiers::get_input_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAnlNoiseNodeTiers::get_input_port_name(int p_port) const {

	switch (p_port) {
		case 0: return "input";
		case 1: return "tiers";
	}
	return "";
}

int VisualAnlNoiseNodeTiers::get_output_port_count() const {

	return 1;
}

VisualAnlNoiseNodeTiers::PortType VisualAnlNoiseNodeTiers::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAnlNoiseNodeTiers::get_output_port_name(int p_port) const {
	return "";
}

Vector<StringName> VisualAnlNoiseNodeTiers::get_editable_properties() const {

	Vector<StringName> props;
	props.push_back("smooth");

	return props;
}

void VisualAnlNoiseNodeTiers::evaluate(Ref<VisualAnlNoise> noise) {

	if (smooth) {
		output_value = noise->smooth_tiers(input, tiers);
	} else {
		output_value = noise->tiers(input, tiers);
	}
}

void VisualAnlNoiseNodeTiers::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_smooth", "smooth"), &VisualAnlNoiseNodeTiers::set_smooth);
	ClassDB::bind_method(D_METHOD("get_smooth"), &VisualAnlNoiseNodeTiers::get_smooth);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "smooth", PROPERTY_HINT_ENUM, "No smoothing, Smoothed"), "set_smooth", "get_smooth");
}

VisualAnlNoiseNodeTiers::VisualAnlNoiseNodeTiers() {

	set_input_port_default_value(0, 0);
	set_input_port_default_value(1, 5);

	smooth = SMOOTHING_DISABLED;

	input = 0;
	tiers = 0;
}

////////////// Gradient

String VisualAnlNoiseNodeGradient::get_caption() const {

	return "Gradient";
}

void VisualAnlNoiseNodeGradient::set_axis(Axis::AxisType p_axis) {

	axis.type = p_axis;
	emit_changed();
}

Axis::AxisType VisualAnlNoiseNodeGradient::get_axis() const {

	return axis.type;
}

int VisualAnlNoiseNodeGradient::get_input_port_count() const {

	return 0;
}

VisualAnlNoiseNodeGradient::PortType VisualAnlNoiseNodeGradient::get_input_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAnlNoiseNodeGradient::get_input_port_name(int p_port) const {

	return "";
}

int VisualAnlNoiseNodeGradient::get_output_port_count() const {

	return 1;
}

VisualAnlNoiseNodeGradient::PortType VisualAnlNoiseNodeGradient::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAnlNoiseNodeGradient::get_output_port_name(int p_port) const {
	return "";
}

Vector<StringName> VisualAnlNoiseNodeGradient::get_editable_properties() const {

	Vector<StringName> props;

	props.push_back("axis");

	return props;
}

void VisualAnlNoiseNodeGradient::evaluate(Ref<VisualAnlNoise> noise) {

	if (axis.type != Axis::AXIS_DOMAIN) {
		output_value = noise->call(axis.as_alpha());
	} else {
		output_value = noise->zero(); // a workaround to circumvent domain enum
	}
}

void VisualAnlNoiseNodeGradient::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_axis", "axis"), &VisualAnlNoiseNodeGradient::set_axis);
	ClassDB::bind_method(D_METHOD("get_axis"), &VisualAnlNoiseNodeGradient::get_axis);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "axis", PROPERTY_HINT_ENUM, Axis::get_hints()), "set_axis", "get_axis");
}

VisualAnlNoiseNodeGradient::VisualAnlNoiseNodeGradient() {

	axis.type = Axis::AXIS_X;
}

////////////// Derivative

String VisualAnlNoiseNodeDerivative::get_caption() const {

	return "Derivative";
}

void VisualAnlNoiseNodeDerivative::set_axis(Axis::AxisType p_axis) {

	axis.type = p_axis;
	emit_changed();
}

Axis::AxisType VisualAnlNoiseNodeDerivative::get_axis() const {

	return axis.type;
}

void VisualAnlNoiseNodeDerivative::set_input_port_value(int p_port, const Variant &p_value) {

	switch (p_port) {
		case 0: input = p_value; break;
		case 1: spacing = p_value; break;
	}
}

Variant VisualAnlNoiseNodeDerivative::get_input_port_value(int p_port) const {

	switch (p_port) {
		case 0: return input;
		case 1: return spacing;
	}
	return Variant();
}

int VisualAnlNoiseNodeDerivative::get_input_port_count() const {

	return 2;
}

VisualAnlNoiseNodeDerivative::PortType VisualAnlNoiseNodeDerivative::get_input_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAnlNoiseNodeDerivative::get_input_port_name(int p_port) const {

	switch (p_port) {
		case 0: return "input";
		case 1: return "spacing";
	}
	return String();
}

int VisualAnlNoiseNodeDerivative::get_output_port_count() const {

	return 1;
}

VisualAnlNoiseNodeDerivative::PortType VisualAnlNoiseNodeDerivative::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAnlNoiseNodeDerivative::get_output_port_name(int p_port) const {
	return "";
}

Vector<StringName> VisualAnlNoiseNodeDerivative::get_editable_properties() const {

	Vector<StringName> props;

	props.push_back("axis");

	return props;
}

void VisualAnlNoiseNodeDerivative::evaluate(Ref<VisualAnlNoise> noise) {

	if (axis.type != Axis::AXIS_DOMAIN) {
		output_value = noise->call("d" + axis.as_alpha(), input, spacing);
	} else {
		output_value = noise->zero(); // a workaround to circumvent domain enum
	}
}

void VisualAnlNoiseNodeDerivative::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_axis", "axis"), &VisualAnlNoiseNodeDerivative::set_axis);
	ClassDB::bind_method(D_METHOD("get_axis"), &VisualAnlNoiseNodeDerivative::get_axis);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "axis", PROPERTY_HINT_ENUM, Axis::get_hints()), "set_axis", "get_axis");
}

VisualAnlNoiseNodeDerivative::VisualAnlNoiseNodeDerivative() {

	set_input_port_default_value(0, 0);
	set_input_port_default_value(1, 1);

	axis.type = Axis::AXIS_X;

	input = 0;
	spacing = 0;
}

////////////// Radial

String VisualAnlNoiseNodeRadial::get_caption() const {

	return "Radial";
}

int VisualAnlNoiseNodeRadial::get_input_port_count() const {

	return 0;
}

VisualAnlNoiseNodeRadial::PortType VisualAnlNoiseNodeRadial::get_input_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAnlNoiseNodeRadial::get_input_port_name(int p_port) const {

	return "";
}

int VisualAnlNoiseNodeRadial::get_output_port_count() const {

	return 1;
}

VisualAnlNoiseNodeRadial::PortType VisualAnlNoiseNodeRadial::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAnlNoiseNodeRadial::get_output_port_name(int p_port) const {
	return "";
}

void VisualAnlNoiseNodeRadial::evaluate(Ref<VisualAnlNoise> noise) {

	output_value = noise->radial();
}

void VisualAnlNoiseNodeRadial::_bind_methods() {

}

VisualAnlNoiseNodeRadial::VisualAnlNoiseNodeRadial() {

}

////////////// Randomize

String VisualAnlNoiseNodeRandomize::get_caption() const {

	return "Randomize";
}

int VisualAnlNoiseNodeRandomize::get_input_port_count() const {

	return 3;
}

void VisualAnlNoiseNodeRandomize::set_input_port_value(int p_port, const Variant &p_value) {

	switch (p_port) {
		case 0: seed = p_value; break;
		case 1: low = p_value; break;
		case 2: high = p_value; break;
	}
}

Variant VisualAnlNoiseNodeRandomize::get_input_port_value(int p_port) const {

	switch (p_port) {
		case 0: return seed;
		case 1: return low;
		case 2: return high;
	}
	return Variant();
}

VisualAnlNoiseNodeRandomize::PortType VisualAnlNoiseNodeRandomize::get_input_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAnlNoiseNodeRandomize::get_input_port_name(int p_port) const {

	switch (p_port) {
		case 0: return "seed";
		case 1: return "low";
		case 2: return "high";
	}
	return "";
}

int VisualAnlNoiseNodeRandomize::get_output_port_count() const {

	return 1;
}

VisualAnlNoiseNodeRandomize::PortType VisualAnlNoiseNodeRandomize::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAnlNoiseNodeRandomize::get_output_port_name(int p_port) const {
	return "";
}

void VisualAnlNoiseNodeRandomize::evaluate(Ref<VisualAnlNoise> noise) {

	output_value = noise->randomize(seed, low, high);
}

void VisualAnlNoiseNodeRandomize::_bind_methods() {

}

VisualAnlNoiseNodeRandomize::VisualAnlNoiseNodeRandomize() {

	set_input_port_default_value(0, 0);
	set_input_port_default_value(1, 0);
	set_input_port_default_value(2, 1);

	seed = 0;
	low = high = 0;
}

////////////// Step

String VisualAnlNoiseNodeStep::get_caption() const {

	return "Step";
}


void VisualAnlNoiseNodeStep::set_type(StepType p_type) {

	type = p_type;
	emit_changed();
}

VisualAnlNoiseNodeStep::StepType VisualAnlNoiseNodeStep::get_type() const {

	return type;
}


int VisualAnlNoiseNodeStep::get_input_port_count() const {

	return 3; // hack be compatible with regular step
}

void VisualAnlNoiseNodeStep::set_input_port_value(int p_port, const Variant &p_value) {

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

Variant VisualAnlNoiseNodeStep::get_input_port_value(int p_port) const {

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

VisualAnlNoiseNodeStep::PortType VisualAnlNoiseNodeStep::get_input_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAnlNoiseNodeStep::get_input_port_name(int p_port) const {

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

int VisualAnlNoiseNodeStep::get_output_port_count() const {

	return 1;
}

VisualAnlNoiseNodeStep::PortType VisualAnlNoiseNodeStep::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAnlNoiseNodeStep::get_output_port_name(int p_port) const {
	return "";
}

Vector<StringName> VisualAnlNoiseNodeStep::get_editable_properties() const {

	Vector<StringName> props;

	props.push_back("type");

	return props;
}

void VisualAnlNoiseNodeStep::evaluate(Ref<VisualAnlNoise> noise) {

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

void VisualAnlNoiseNodeStep::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_type", "type"), &VisualAnlNoiseNodeStep::set_type);
	ClassDB::bind_method(D_METHOD("get_type"), &VisualAnlNoiseNodeStep::get_type);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "type", PROPERTY_HINT_ENUM, "Regular,Linear,Smooth,Smoother"), "set_type", "get_type");

	BIND_ENUM_CONSTANT(STEP_REGULAR);
	BIND_ENUM_CONSTANT(STEP_LINEAR);
	BIND_ENUM_CONSTANT(STEP_SMOOTH);
	BIND_ENUM_CONSTANT(STEP_SMOOTHER);
}

VisualAnlNoiseNodeStep::VisualAnlNoiseNodeStep() {

	set_input_port_default_value(0, 0);
	set_input_port_default_value(1, 1);
	set_input_port_default_value(2, 0);

	type = STEP_REGULAR;

	value = 0;
	low = high = 0;
	control = 0;
}

////////////// Curve Section

String VisualAnlNoiseNodeCurveSection::get_caption() const {

	return "CurveSection";
}

int VisualAnlNoiseNodeCurveSection::get_input_port_count() const {

	return 6;
}

void VisualAnlNoiseNodeCurveSection::set_input_port_value(int p_port, const Variant &p_value) {

	switch (p_port) {
		case 0: lowv = p_value; break;
		case 1: t0 = p_value; break;
		case 2: t1 = p_value; break;
		case 3: v0 = p_value; break;
		case 4: v1 = p_value; break;
		case 5: control = p_value; break;
	}
}

Variant VisualAnlNoiseNodeCurveSection::get_input_port_value(int p_port) const {

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

VisualAnlNoiseNodeCurveSection::PortType VisualAnlNoiseNodeCurveSection::get_input_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAnlNoiseNodeCurveSection::get_input_port_name(int p_port) const {

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

int VisualAnlNoiseNodeCurveSection::get_output_port_count() const {

	return 1;
}

VisualAnlNoiseNodeCurveSection::PortType VisualAnlNoiseNodeCurveSection::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAnlNoiseNodeCurveSection::get_output_port_name(int p_port) const {

	return "";
}

void VisualAnlNoiseNodeCurveSection::evaluate(Ref<VisualAnlNoise> noise) {

	output_value = noise->curve_section(lowv, t0, t1, v0, v1, control);
}

void VisualAnlNoiseNodeCurveSection::_bind_methods() {

}

VisualAnlNoiseNodeCurveSection::VisualAnlNoiseNodeCurveSection() {

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

String VisualAnlNoiseNodeHex::get_caption() const {

	return "Hex";
}

void VisualAnlNoiseNodeHex::set_input_port_value(int p_port, const Variant &p_value) {

	seed = p_value;
}

Variant VisualAnlNoiseNodeHex::get_input_port_value(int p_port) const {

	return seed;
}

int VisualAnlNoiseNodeHex::get_input_port_count() const {

	return 1; // hack to be compatible with hex tile
}

VisualAnlNoiseNodeHex::PortType VisualAnlNoiseNodeHex::get_input_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAnlNoiseNodeHex::get_input_port_name(int p_port) const {

	return type == HEX_TILE ? "seed" : "";
}

int VisualAnlNoiseNodeHex::get_output_port_count() const {

	return 1;
}

VisualAnlNoiseNodeHex::PortType VisualAnlNoiseNodeHex::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAnlNoiseNodeHex::get_output_port_name(int p_port) const {
	return "";
}

void VisualAnlNoiseNodeHex::set_type(HexType p_type) {

	type = p_type;
	emit_changed();
}

VisualAnlNoiseNodeHex::HexType VisualAnlNoiseNodeHex::get_type() const {

	return type;
}

Vector<StringName> VisualAnlNoiseNodeHex::get_editable_properties() const {

	Vector<StringName> props;
	props.push_back("type");

	return props;
}

void VisualAnlNoiseNodeHex::evaluate(Ref<VisualAnlNoise> noise) {

	switch(type) {

		case HEX_TILE:
			output_value = noise->hex_tile(seed);
			break;

		case HEX_BUMP:
			output_value = noise->hex_bump();
			break;
	}
}

void VisualAnlNoiseNodeHex::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_type", "type"), &VisualAnlNoiseNodeHex::set_type);
	ClassDB::bind_method(D_METHOD("get_type"), &VisualAnlNoiseNodeHex::get_type);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "type", PROPERTY_HINT_ENUM, "Tile,Bump"), "set_type", "get_type");

	BIND_ENUM_CONSTANT(HEX_TILE);
	BIND_ENUM_CONSTANT(HEX_BUMP);
}

VisualAnlNoiseNodeHex::VisualAnlNoiseNodeHex() {

	set_input_port_default_value(0, 0);

	type = HEX_TILE;
	seed = 0;
}

////////////// Color

String VisualAnlNoiseNodeColor::get_caption() const {

	return "Color";
}

int VisualAnlNoiseNodeColor::get_input_port_count() const {

	return 0;
}

VisualAnlNoiseNodeColor::PortType VisualAnlNoiseNodeColor::get_input_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAnlNoiseNodeColor::get_input_port_name(int p_port) const {

	return "";
}

int VisualAnlNoiseNodeColor::get_output_port_count() const {

	return 1;
}

VisualAnlNoiseNodeColor::PortType VisualAnlNoiseNodeColor::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAnlNoiseNodeColor::get_output_port_name(int p_port) const {
	return "";
}

void VisualAnlNoiseNodeColor::set_color(const Color &p_color) {

	color = p_color;
	emit_changed();
}

Color VisualAnlNoiseNodeColor::get_color() const {

	return color;
}

Vector<StringName> VisualAnlNoiseNodeColor::get_editable_properties() const {

	Vector<StringName> props;
	props.push_back("color");

	return props;
}

void VisualAnlNoiseNodeColor::evaluate(Ref<VisualAnlNoise> noise) {

	output_value = noise->color(color);
}

void VisualAnlNoiseNodeColor::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_color", "color"), &VisualAnlNoiseNodeColor::set_color);
	ClassDB::bind_method(D_METHOD("get_color"), &VisualAnlNoiseNodeColor::get_color);

	ADD_PROPERTY(PropertyInfo(Variant::COLOR, "color"), "set_color", "get_color");
}

VisualAnlNoiseNodeColor::VisualAnlNoiseNodeColor() {

	color = Color(1, 1, 1, 1);
}



////////////// ColorCombine

String VisualAnlNoiseNodeColorCombine::get_caption() const {

	return "ColorCombine";
}

void VisualAnlNoiseNodeColorCombine::set_input_port_value(int p_port, const Variant &p_value) {

	switch (p_port) {
		case 0: c1 = p_value; break;
		case 1: c2 = p_value; break;
		case 2: c3 = p_value; break;
		case 3: c4 = p_value; break;
	}
}

Variant VisualAnlNoiseNodeColorCombine::get_input_port_value(int p_port) const {

	switch (p_port) {
		case 0: return c1;
		case 1: return c2;
		case 2: return c3;
		case 3: return c4;
	}
	return Variant();
}

int VisualAnlNoiseNodeColorCombine::get_input_port_count() const {

	return 4;
}

VisualAnlNoiseNodeColorCombine::PortType VisualAnlNoiseNodeColorCombine::get_input_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAnlNoiseNodeColorCombine::get_input_port_name(int p_port) const {

	switch (p_port) {
		case 0: return type == COMBINE_RGBA ? "r" : "h";
		case 1: return type == COMBINE_RGBA ? "g" : "s";
		case 2: return type == COMBINE_RGBA ? "b" : "v";
		case 3: return "a";
	}
	return String();
}

int VisualAnlNoiseNodeColorCombine::get_output_port_count() const {

	return 1;
}

VisualAnlNoiseNodeColorCombine::PortType VisualAnlNoiseNodeColorCombine::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAnlNoiseNodeColorCombine::get_output_port_name(int p_port) const {
	return "";
}

void VisualAnlNoiseNodeColorCombine::set_type(CombineMode p_type) {

	type = p_type;
	emit_changed();
}

VisualAnlNoiseNodeColorCombine::CombineMode VisualAnlNoiseNodeColorCombine::get_type() const {

	return type;
}

Vector<StringName> VisualAnlNoiseNodeColorCombine::get_editable_properties() const {

	Vector<StringName> props;
	props.push_back("type");

	return props;
}

void VisualAnlNoiseNodeColorCombine::evaluate(Ref<VisualAnlNoise> noise) {

	switch(type) {

		case COMBINE_RGBA:
			output_value = noise->combine_rgba(c1, c2, c3, c4);
			break;

		case COMBINE_HSVA:
			output_value = noise->combine_hsva(c1, c2, c3, c4);
			break;
	}
}

void VisualAnlNoiseNodeColorCombine::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_type", "type"), &VisualAnlNoiseNodeColorCombine::set_type);
	ClassDB::bind_method(D_METHOD("get_type"), &VisualAnlNoiseNodeColorCombine::get_type);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "type", PROPERTY_HINT_ENUM, "RGBA,HSVA"), "set_type", "get_type");

	BIND_ENUM_CONSTANT(COMBINE_RGBA);
	BIND_ENUM_CONSTANT(COMBINE_HSVA);
}

VisualAnlNoiseNodeColorCombine::VisualAnlNoiseNodeColorCombine() {

	set_input_port_default_value(0, 0);
	set_input_port_default_value(1, 0);
	set_input_port_default_value(2, 0);
	set_input_port_default_value(3, 1);

	type = COMBINE_RGBA;
	c1 = c2 = c3 = c4 = 0;
}

////////////// ScaleOffset

String VisualAnlNoiseNodeScaleOffset::get_caption() const {

	return "ScaleOffset";
}

void VisualAnlNoiseNodeScaleOffset::set_scale(double p_scale) {

	scale = p_scale;
	emit_changed();
}

double VisualAnlNoiseNodeScaleOffset::get_scale() const {

	return scale;
}

void VisualAnlNoiseNodeScaleOffset::set_offset(double p_offset) {

	offset = p_offset;
	emit_changed();
}

double VisualAnlNoiseNodeScaleOffset::get_offset() const {

	return offset;
}

void VisualAnlNoiseNodeScaleOffset::set_input_port_value(int p_port, const Variant &p_value) {

	input = p_value;
}

Variant VisualAnlNoiseNodeScaleOffset::get_input_port_value(int p_port) const {

	return input;
}

int VisualAnlNoiseNodeScaleOffset::get_input_port_count() const {

	return 1;
}

VisualAnlNoiseNodeScaleOffset::PortType VisualAnlNoiseNodeScaleOffset::get_input_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAnlNoiseNodeScaleOffset::get_input_port_name(int p_port) const {

	return "input";
}

int VisualAnlNoiseNodeScaleOffset::get_output_port_count() const {

	return 1;
}

VisualAnlNoiseNodeScaleOffset::PortType VisualAnlNoiseNodeScaleOffset::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAnlNoiseNodeScaleOffset::get_output_port_name(int p_port) const {
	return "";
}

Vector<StringName> VisualAnlNoiseNodeScaleOffset::get_editable_properties() const {

	Vector<StringName> props;

	props.push_back("scale");
	props.push_back("offset");

	return props;
}

void VisualAnlNoiseNodeScaleOffset::evaluate(Ref<VisualAnlNoise> noise) {

	output_value = noise->scale_offset(input, scale, offset);
}

void VisualAnlNoiseNodeScaleOffset::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_scale", "scale"), &VisualAnlNoiseNodeScaleOffset::set_scale);
	ClassDB::bind_method(D_METHOD("get_scale"), &VisualAnlNoiseNodeScaleOffset::get_scale);

	ClassDB::bind_method(D_METHOD("set_offset", "offset"), &VisualAnlNoiseNodeScaleOffset::set_offset);
	ClassDB::bind_method(D_METHOD("get_offset"), &VisualAnlNoiseNodeScaleOffset::get_offset);

	ADD_PROPERTY(PropertyInfo(Variant::REAL, "scale"), "set_scale", "get_scale");
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "offset"), "set_offset", "get_offset");
}

VisualAnlNoiseNodeScaleOffset::VisualAnlNoiseNodeScaleOffset() {

	input = 0;
	scale = 1.0;
	offset = 0.0;
}

////////////// Layer

String VisualAnlNoiseNodeFractalLayer::get_caption() const {

	return "Layer";
}

void VisualAnlNoiseNodeFractalLayer::set_input_port_value(int p_port, const Variant &p_value) {

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

Variant VisualAnlNoiseNodeFractalLayer::get_input_port_value(int p_port) const {

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

int VisualAnlNoiseNodeFractalLayer::get_input_port_count() const {

	return 9;
}

VisualAnlNoiseNodeFractalLayer::PortType VisualAnlNoiseNodeFractalLayer::get_input_port_type(int p_port) const {

	return p_port != 0 ? PORT_TYPE_SCALAR : PORT_TYPE_INDEX;
}

String VisualAnlNoiseNodeFractalLayer::get_input_port_name(int p_port) const {

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

int VisualAnlNoiseNodeFractalLayer::get_output_port_count() const {

	return 1;
}

VisualAnlNoiseNodeFractalLayer::PortType VisualAnlNoiseNodeFractalLayer::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAnlNoiseNodeFractalLayer::get_output_port_name(int p_port) const {
	return "";
}

void VisualAnlNoiseNodeFractalLayer::set_type(LayerType p_type) {

	type = p_type;
	emit_changed();
}

VisualAnlNoiseNodeFractalLayer::LayerType VisualAnlNoiseNodeFractalLayer::get_type() const {

	return type;
}

void VisualAnlNoiseNodeFractalLayer::set_basis(anl::BasisTypes p_basis) {

	basis = p_basis;
	emit_changed();
}

anl::BasisTypes VisualAnlNoiseNodeFractalLayer::get_basis() const {

	return basis;
}

Vector<StringName> VisualAnlNoiseNodeFractalLayer::get_editable_properties() const {

	Vector<StringName> props;
	props.push_back("type");
	props.push_back("basis");

	return props;
}

void VisualAnlNoiseNodeFractalLayer::evaluate(Ref<VisualAnlNoise> noise) {

	switch(type) {

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

void VisualAnlNoiseNodeFractalLayer::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_type", "type"), &VisualAnlNoiseNodeFractalLayer::set_type);
	ClassDB::bind_method(D_METHOD("get_type"), &VisualAnlNoiseNodeFractalLayer::get_type);

	ClassDB::bind_method(D_METHOD("set_basis", "basis"), &VisualAnlNoiseNodeFractalLayer::set_basis);
	ClassDB::bind_method(D_METHOD("get_basis"), &VisualAnlNoiseNodeFractalLayer::get_basis);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "type", PROPERTY_HINT_ENUM, "Fractal,Ridged,Billow"), "set_type", "get_type");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "basis", PROPERTY_HINT_ENUM, "Value,Gradient,Simplex"), "set_basis", "get_basis");

	BIND_ENUM_CONSTANT(LAYER_FRACTAL);
	BIND_ENUM_CONSTANT(LAYER_RIDGED);
	BIND_ENUM_CONSTANT(LAYER_BILLOW);
}

VisualAnlNoiseNodeFractalLayer::VisualAnlNoiseNodeFractalLayer() {

	type = LAYER_FRACTAL;
	basis = anl::BASIS_SIMPLEX;

	set_input_port_default_value(0, anl::INTERP_QUINTIC);
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

String VisualAnlNoiseNodeFractal::get_caption() const {

	return "Fractal";
}

int VisualAnlNoiseNodeFractal::get_input_port_count() const {

	return 6;
}

void VisualAnlNoiseNodeFractal::set_input_port_value(int p_port, const Variant &p_value) {

	switch (p_port) {
		case 0: seed = p_value; break;
		case 1: layer = p_value; break;
		case 2: persistence = p_value; break;
		case 3: lacunarity = p_value; break;
		case 4: numoctaves = p_value; break;
		case 5: frequency = p_value; break;
	}
}

Variant VisualAnlNoiseNodeFractal::get_input_port_value(int p_port) const {

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

VisualAnlNoiseNodeFractal::PortType VisualAnlNoiseNodeFractal::get_input_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAnlNoiseNodeFractal::get_input_port_name(int p_port) const {

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

int VisualAnlNoiseNodeFractal::get_output_port_count() const {

	return 1;
}

VisualAnlNoiseNodeFractal::PortType VisualAnlNoiseNodeFractal::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAnlNoiseNodeFractal::get_output_port_name(int p_port) const {
	return "";
}

void VisualAnlNoiseNodeFractal::evaluate(Ref<VisualAnlNoise> noise) {

	output_value = noise->fractal(seed, layer, persistence, lacunarity, numoctaves, frequency);
}

void VisualAnlNoiseNodeFractal::_bind_methods() {

}

VisualAnlNoiseNodeFractal::VisualAnlNoiseNodeFractal() {

	set_input_port_default_value(0, 0);
	set_input_port_default_value(1, 0);
	set_input_port_default_value(2, 0);
	set_input_port_default_value(3, 0);
	set_input_port_default_value(4, 0);
	set_input_port_default_value(5, 0);

	seed = 0;
	layer = 0;
	persistence = 0;
	lacunarity = 0;
	numoctaves = 0;
	frequency = 0;
}

////////////// FractalVariant

String VisualAnlNoiseNodeFractalVariant::get_caption() const {

	return "FractalVariant";
}

void VisualAnlNoiseNodeFractalVariant::set_input_port_value(int p_port, const Variant &p_value) {

	switch (p_port) {
		case 0: numoctaves = p_value; break;
		case 1: frequency = p_value; break;
		case 2: seed = p_value; break;
		case 3: rot = p_value; break;
	}
}

Variant VisualAnlNoiseNodeFractalVariant::get_input_port_value(int p_port) const {

	switch (p_port) {
		case 0: return numoctaves;
		case 1: return frequency;
		case 2: return seed;
		case 3: return rot;
	}
	return Variant();
}

int VisualAnlNoiseNodeFractalVariant::get_input_port_count() const {

	return 4;
}

VisualAnlNoiseNodeFractalVariant::PortType VisualAnlNoiseNodeFractalVariant::get_input_port_type(int p_port) const {

	return PORT_TYPE_SCALAR;
}

String VisualAnlNoiseNodeFractalVariant::get_input_port_name(int p_port) const {

	switch (p_port) {
		case 0: return "numoctaves";
		case 1: return "frequency";
		case 2: return "seed";
		case 3: return "rot";
	}
	return "";
}

int VisualAnlNoiseNodeFractalVariant::get_output_port_count() const {

	return 1;
}

VisualAnlNoiseNodeFractalVariant::PortType VisualAnlNoiseNodeFractalVariant::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualAnlNoiseNodeFractalVariant::get_output_port_name(int p_port) const {
	return "";
}

void VisualAnlNoiseNodeFractalVariant::set_type(FractalType p_type) {

	type = p_type;
	emit_changed();
}

VisualAnlNoiseNodeFractalVariant::FractalType VisualAnlNoiseNodeFractalVariant::get_type() const {

	return type;
}

void VisualAnlNoiseNodeFractalVariant::set_basis(anl::BasisTypes p_basis) {

	basis = p_basis;
	emit_changed();
}

anl::BasisTypes VisualAnlNoiseNodeFractalVariant::get_basis() const {

	return basis;
}

void VisualAnlNoiseNodeFractalVariant::set_interpolation(anl::InterpolationTypes p_interpolation) {

	interpolation = p_interpolation;
	emit_changed();
}

anl::InterpolationTypes VisualAnlNoiseNodeFractalVariant::get_interpolation() const {

	return interpolation;
}

Vector<StringName> VisualAnlNoiseNodeFractalVariant::get_editable_properties() const {

	Vector<StringName> props;
	props.push_back("type");
	props.push_back("basis");
	props.push_back("interpolation");

	return props;
}

void VisualAnlNoiseNodeFractalVariant::evaluate(Ref<VisualAnlNoise> noise) {

	switch(type) {

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

void VisualAnlNoiseNodeFractalVariant::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_type", "type"), &VisualAnlNoiseNodeFractalVariant::set_type);
	ClassDB::bind_method(D_METHOD("get_type"), &VisualAnlNoiseNodeFractalVariant::get_type);

	ClassDB::bind_method(D_METHOD("set_basis", "basis"), &VisualAnlNoiseNodeFractalVariant::set_basis);
	ClassDB::bind_method(D_METHOD("get_basis"), &VisualAnlNoiseNodeFractalVariant::get_basis);

	ClassDB::bind_method(D_METHOD("set_interpolation", "interpolation"), &VisualAnlNoiseNodeFractalVariant::set_interpolation);
	ClassDB::bind_method(D_METHOD("get_interpolation"), &VisualAnlNoiseNodeFractalVariant::get_interpolation);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "type", PROPERTY_HINT_ENUM, "Fractal,Ridged,Billow"), "set_type", "get_type");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "basis", PROPERTY_HINT_ENUM, "Value,Gradient,Simplex"), "set_basis", "get_basis");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "interpolation", PROPERTY_HINT_ENUM, "None,Linear,Hermite,Quintic"), "set_interpolation", "get_interpolation");

	BIND_ENUM_CONSTANT(TYPE_FBM);
	BIND_ENUM_CONSTANT(TYPE_RIDGED_MULTIFRACTAL);
	BIND_ENUM_CONSTANT(TYPE_BILLOW);
}

VisualAnlNoiseNodeFractalVariant::VisualAnlNoiseNodeFractalVariant() {

	type = TYPE_FBM;
	basis = anl::BASIS_SIMPLEX;
	interpolation = anl::INTERP_QUINTIC;

	set_input_port_default_value(0, 1);
	set_input_port_default_value(1, 1.0);
	set_input_port_default_value(2, 0);
	set_input_port_default_value(3, true);

	numoctaves = 1;
	frequency = 1.0;
	seed = 0;
	rot = true;
}
