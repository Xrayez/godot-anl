#ifndef VISUAL_ACCIDENTAL_NOISE_NODES_H
#define VISUAL_ACCIDENTAL_NOISE_NODES_H

#include "visual_noise.h"

class VisualAccidentalNoiseNodeScalar : public VisualAccidentalNoiseNode {
	GDCLASS(VisualAccidentalNoiseNodeScalar, VisualAccidentalNoiseNode);

public:
	enum ScalarType {
		SCALAR_CONSTANT,
		SCALAR_PI,
		SCALAR_E,
		SCALAR_ONE,
		SCALAR_ZERO,
		SCALAR_POINT5,
		SCALAR_SQRT2,
	};

	void set_type(ScalarType p_type);
	ScalarType get_type() const;

	void set_constant(real_t p_value);
	real_t get_constant() const;

public:
	virtual String get_caption() const;

	virtual int get_input_port_count() const;
	virtual PortType get_input_port_type(int p_port) const;
	virtual String get_input_port_name(int p_port) const;

	virtual int get_output_port_count() const;
	virtual PortType get_output_port_type(int p_port) const;
	virtual String get_output_port_name(int p_port) const;

	virtual Vector<StringName> get_editable_properties() const;

	virtual void evaluate(Ref<VisualAccidentalNoise> noise);

	VisualAccidentalNoiseNodeScalar();

protected:
	static void _bind_methods();

private:
	ScalarType type;
	real_t constant;
};

VARIANT_ENUM_CAST(VisualAccidentalNoiseNodeScalar::ScalarType);

class VisualAccidentalNoiseNodeSeed : public VisualAccidentalNoiseNode {
	GDCLASS(VisualAccidentalNoiseNodeSeed, VisualAccidentalNoiseNode);

public:
	void set_seed(unsigned int p_value);
	unsigned int get_seed() const;

public:
	virtual String get_caption() const;

	virtual int get_input_port_count() const;
	virtual PortType get_input_port_type(int p_port) const;
	virtual String get_input_port_name(int p_port) const;

	virtual int get_output_port_count() const;
	virtual PortType get_output_port_type(int p_port) const;
	virtual String get_output_port_name(int p_port) const;

	virtual Vector<StringName> get_editable_properties() const;

	virtual void evaluate(Ref<VisualAccidentalNoise> noise);

	VisualAccidentalNoiseNodeSeed();

protected:
	static void _bind_methods();

private:
	unsigned int seed;
};

class VisualAccidentalNoiseNodeSeeder : public VisualAccidentalNoiseNode {
	GDCLASS(VisualAccidentalNoiseNodeSeeder, VisualAccidentalNoiseNode);

public:
	virtual String get_caption() const;

	virtual void set_input_port_value(int p_port, const Variant &p_value);
	virtual Variant get_input_port_value(int p_port) const;
	virtual int get_input_port_count() const;
	virtual PortType get_input_port_type(int p_port) const;
	virtual String get_input_port_name(int p_port) const;

	virtual int get_output_port_count() const;
	virtual PortType get_output_port_type(int p_port) const;
	virtual String get_output_port_name(int p_port) const;

	virtual void evaluate(Ref<VisualAccidentalNoise> noise);

	VisualAccidentalNoiseNodeSeeder();

protected:
	static void _bind_methods();

private:
	Index seed;
	Index input;
};

class VisualAccidentalNoiseNodeScalarOp : public VisualAccidentalNoiseNode {
	GDCLASS(VisualAccidentalNoiseNodeScalarOp, VisualAccidentalNoiseNode);

public:
	enum Operator {
		OP_ADD,
		OP_SUB,
		OP_MUL,
		OP_DIV,
		OP_POW,
		OP_MAX,
		OP_MIN,
		OP_BIAS,
		OP_GAIN,
	};

	void set_operator(Operator p_op);
	Operator get_operator() const;

public:
	virtual String get_caption() const;

	virtual void set_input_port_value(int p_port, const Variant &p_value);
	virtual Variant get_input_port_value(int p_port) const;
	virtual int get_input_port_count() const;
	virtual PortType get_input_port_type(int p_port) const;
	virtual String get_input_port_name(int p_port) const;

	virtual int get_output_port_count() const;
	virtual PortType get_output_port_type(int p_port) const;
	virtual String get_output_port_name(int p_port) const;

	virtual Vector<StringName> get_editable_properties() const;

	virtual void evaluate(Ref<VisualAccidentalNoise> noise);

	VisualAccidentalNoiseNodeScalarOp();

protected:
	static void _bind_methods();

private:
	Operator op;
	Index a, b;
};

VARIANT_ENUM_CAST(VisualAccidentalNoiseNodeScalarOp::Operator);

class VisualAccidentalNoiseNodeScalarFunc : public VisualAccidentalNoiseNode {
	GDCLASS(VisualAccidentalNoiseNodeScalarFunc, VisualAccidentalNoiseNode);

public:
	enum Function {
		FUNC_COS,
		FUNC_SIN,
		FUNC_TAN,
		FUNC_ACOS,
		FUNC_ASIN,
		FUNC_ATAN,
		FUNC_ABS,
		FUNC_SIGMOID,
	};

	void set_function(Function p_op);
	Function get_function() const;

public:
	virtual String get_caption() const;

	virtual void set_input_port_value(int p_port, const Variant &p_value);
	virtual Variant get_input_port_value(int p_port) const;
	virtual int get_input_port_count() const;
	virtual PortType get_input_port_type(int p_port) const;
	virtual String get_input_port_name(int p_port) const;

	virtual int get_output_port_count() const;
	virtual PortType get_output_port_type(int p_port) const;
	virtual String get_output_port_name(int p_port) const;

	virtual Vector<StringName> get_editable_properties() const;

	virtual void evaluate(Ref<VisualAccidentalNoise> noise);

	VisualAccidentalNoiseNodeScalarFunc();

protected:
	static void _bind_methods();

private:
	Function func;
	Index input;
};

VARIANT_ENUM_CAST(VisualAccidentalNoiseNodeScalarFunc::Function);

class VisualAccidentalNoiseNodeValueBasis : public VisualAccidentalNoiseNode {
	GDCLASS(VisualAccidentalNoiseNodeValueBasis, VisualAccidentalNoiseNode);

public:
	void set_interpolation(Index p_idx);
	Index get_interpolation() const;

	void set_seed(Index p_idx);
	Index get_seed() const;

public:
	virtual String get_caption() const;

	virtual void set_input_port_value(int p_port, const Variant &p_value);
	virtual Variant get_input_port_value(int p_port) const;
	virtual int get_input_port_count() const;
	virtual PortType get_input_port_type(int p_port) const;
	virtual String get_input_port_name(int p_port) const;

	virtual int get_output_port_count() const;
	virtual PortType get_output_port_type(int p_port) const;
	virtual String get_output_port_name(int p_port) const;

	virtual void evaluate(Ref<VisualAccidentalNoise> noise);

	VisualAccidentalNoiseNodeValueBasis();

protected:
	static void _bind_methods();

private:
	Index interp;
	Index seed;
};

class VisualAccidentalNoiseNodeGradientBasis : public VisualAccidentalNoiseNode {
	GDCLASS(VisualAccidentalNoiseNodeGradientBasis, VisualAccidentalNoiseNode);

public:
	void set_interpolation(Index p_idx);
	Index get_interpolation() const;

	void set_seed(Index p_idx);
	Index get_seed() const;

public:
	virtual String get_caption() const;

	virtual void set_input_port_value(int p_port, const Variant &p_value);
	virtual Variant get_input_port_value(int p_port) const;
	virtual int get_input_port_count() const;
	virtual PortType get_input_port_type(int p_port) const;
	virtual String get_input_port_name(int p_port) const;

	virtual int get_output_port_count() const;
	virtual PortType get_output_port_type(int p_port) const;
	virtual String get_output_port_name(int p_port) const;

	virtual void evaluate(Ref<VisualAccidentalNoise> noise);

	VisualAccidentalNoiseNodeGradientBasis();

protected:
	static void _bind_methods();

private:
	Index interp;
	Index seed;
};

class VisualAccidentalNoiseNodeCellularBasis : public VisualAccidentalNoiseNode {
	GDCLASS(VisualAccidentalNoiseNodeCellularBasis, VisualAccidentalNoiseNode);

public:
	void set_distance(Index p_idx);
	Index get_distance() const;

	void set_seed(Index p_idx);
	Index get_seed() const;

public:
	virtual String get_caption() const;

	virtual void set_input_port_value(int p_port, const Variant &p_value);
	virtual Variant get_input_port_value(int p_port) const;
	virtual int get_input_port_count() const;
	virtual PortType get_input_port_type(int p_port) const;
	virtual String get_input_port_name(int p_port) const;

	virtual int get_output_port_count() const;
	virtual PortType get_output_port_type(int p_port) const;
	virtual String get_output_port_name(int p_port) const;

	virtual void evaluate(Ref<VisualAccidentalNoise> noise);

	VisualAccidentalNoiseNodeCellularBasis();

protected:
	static void _bind_methods();

private:
	Index f1, f2, f3, f4;
	Index d1, d2, d3, d4;
	Index distance, seed;
};

class VisualAccidentalNoiseNodeSimplexBasis : public VisualAccidentalNoiseNode {
	GDCLASS(VisualAccidentalNoiseNodeSimplexBasis, VisualAccidentalNoiseNode);

public:
	void set_seed(Index p_idx);
	Index get_seed() const;

public:
	virtual String get_caption() const;

	virtual void set_input_port_value(int p_port, const Variant &p_value);
	virtual Variant get_input_port_value(int p_port) const;
	virtual int get_input_port_count() const;
	virtual PortType get_input_port_type(int p_port) const;
	virtual String get_input_port_name(int p_port) const;

	virtual int get_output_port_count() const;
	virtual PortType get_output_port_type(int p_port) const;
	virtual String get_output_port_name(int p_port) const;

	virtual void evaluate(Ref<VisualAccidentalNoise> noise);

	VisualAccidentalNoiseNodeSimplexBasis();

protected:
	static void _bind_methods();

private:
	Index seed;
};

class VisualAccidentalNoiseNodeExpression : public VisualAccidentalNoiseNode {
	GDCLASS(VisualAccidentalNoiseNodeExpression, VisualAccidentalNoiseNode);

public:
	void set_expression(const String &p_expression);
	String get_expression() const;

public:
	virtual String get_caption() const;

	virtual void set_input_port_value(int p_port, const Variant &p_value);
	virtual Variant get_input_port_value(int p_port) const;
	virtual int get_input_port_count() const;
	virtual PortType get_input_port_type(int p_port) const;
	virtual String get_input_port_name(int p_port) const;

	virtual int get_output_port_count() const;
	virtual PortType get_output_port_type(int p_port) const;
	virtual String get_output_port_name(int p_port) const;

	virtual Vector<StringName> get_editable_properties() const;

	virtual void evaluate(Ref<VisualAccidentalNoise> noise);

	VisualAccidentalNoiseNodeExpression();

protected:
	static void _bind_methods();

private:
	String expression;
};

class VisualAccidentalNoiseNodeTranslate : public VisualAccidentalNoiseNode {
	GDCLASS(VisualAccidentalNoiseNodeTranslate, VisualAccidentalNoiseNode);

public:
	void set_axis(Axis::AxisType p_type);
	Axis::AxisType get_axis() const;

public:
	virtual String get_caption() const;

	virtual void set_input_port_value(int p_port, const Variant &p_value);
	virtual Variant get_input_port_value(int p_port) const;
	virtual int get_input_port_count() const;
	virtual PortType get_input_port_type(int p_port) const;
	virtual String get_input_port_name(int p_port) const;

	virtual int get_output_port_count() const;
	virtual PortType get_output_port_type(int p_port) const;
	virtual String get_output_port_name(int p_port) const;

	virtual Vector<StringName> get_editable_properties() const;

	virtual void evaluate(Ref<VisualAccidentalNoise> noise);

	VisualAccidentalNoiseNodeTranslate();

protected:
	static void _bind_methods();

private:
	static const String method;

	Index input, by;
	Axis axis;
};

class VisualAccidentalNoiseNodeScale : public VisualAccidentalNoiseNode {
	GDCLASS(VisualAccidentalNoiseNodeScale, VisualAccidentalNoiseNode);

public:
	void set_axis(Axis::AxisType p_type);
	Axis::AxisType get_axis() const;

public:
	virtual String get_caption() const;

	virtual void set_input_port_value(int p_port, const Variant &p_value);
	virtual Variant get_input_port_value(int p_port) const;
	virtual int get_input_port_count() const;
	virtual PortType get_input_port_type(int p_port) const;
	virtual String get_input_port_name(int p_port) const;

	virtual int get_output_port_count() const;
	virtual PortType get_output_port_type(int p_port) const;
	virtual String get_output_port_name(int p_port) const;

	virtual Vector<StringName> get_editable_properties() const;

	virtual void evaluate(Ref<VisualAccidentalNoise> noise);

	VisualAccidentalNoiseNodeScale();

protected:
	static void _bind_methods();

private:
	static const String method;

	Index input, by;
	Axis axis;
};

class VisualAccidentalNoiseNodeRotate : public VisualAccidentalNoiseNode {
	GDCLASS(VisualAccidentalNoiseNodeRotate, VisualAccidentalNoiseNode);

public:
	virtual String get_caption() const;

	virtual void set_input_port_value(int p_port, const Variant &p_value);
	virtual Variant get_input_port_value(int p_port) const;
	virtual int get_input_port_count() const;
	virtual PortType get_input_port_type(int p_port) const;
	virtual String get_input_port_name(int p_port) const;

	virtual int get_output_port_count() const;
	virtual PortType get_output_port_type(int p_port) const;
	virtual String get_output_port_name(int p_port) const;

	virtual void evaluate(Ref<VisualAccidentalNoise> noise);

	VisualAccidentalNoiseNodeRotate();

protected:
	static void _bind_methods();

private:
	Index input, angle;
	Index ax, ay, az;
};

class VisualAccidentalNoiseNodeClamp : public VisualAccidentalNoiseNode {
	GDCLASS(VisualAccidentalNoiseNodeClamp, VisualAccidentalNoiseNode);

public:
	virtual String get_caption() const;

	virtual void set_input_port_value(int p_port, const Variant &p_value);
	virtual Variant get_input_port_value(int p_port) const;
	virtual int get_input_port_count() const;
	virtual PortType get_input_port_type(int p_port) const;
	virtual String get_input_port_name(int p_port) const;

	virtual int get_output_port_count() const;
	virtual PortType get_output_port_type(int p_port) const;
	virtual String get_output_port_name(int p_port) const;

	virtual void evaluate(Ref<VisualAccidentalNoise> noise);

	VisualAccidentalNoiseNodeClamp();

protected:
	static void _bind_methods();

private:
	Index input;
	Index low, high;
};

class VisualAccidentalNoiseNodeMix : public VisualAccidentalNoiseNode {
	GDCLASS(VisualAccidentalNoiseNodeMix, VisualAccidentalNoiseNode);

public:
	virtual String get_caption() const;

	virtual void set_input_port_value(int p_port, const Variant &p_value);
	virtual Variant get_input_port_value(int p_port) const;
	virtual int get_input_port_count() const;
	virtual PortType get_input_port_type(int p_port) const;
	virtual String get_input_port_name(int p_port) const;

	virtual int get_output_port_count() const;
	virtual PortType get_output_port_type(int p_port) const;
	virtual String get_output_port_name(int p_port) const;

	virtual void evaluate(Ref<VisualAccidentalNoise> noise);

	VisualAccidentalNoiseNodeMix();

protected:
	static void _bind_methods();

private:
	Index low, high;
	Index control;
};

class VisualAccidentalNoiseNodeSelect : public VisualAccidentalNoiseNode {
	GDCLASS(VisualAccidentalNoiseNodeSelect, VisualAccidentalNoiseNode);

public:
	virtual String get_caption() const;

	virtual void set_input_port_value(int p_port, const Variant &p_value);
	virtual Variant get_input_port_value(int p_port) const;
	virtual int get_input_port_count() const;
	virtual PortType get_input_port_type(int p_port) const;
	virtual String get_input_port_name(int p_port) const;

	virtual int get_output_port_count() const;
	virtual PortType get_output_port_type(int p_port) const;
	virtual String get_output_port_name(int p_port) const;

	virtual void evaluate(Ref<VisualAccidentalNoise> noise);

	VisualAccidentalNoiseNodeSelect();

protected:
	static void _bind_methods();

private:
	Index low, high;
	Index control;
	Index threshold;
	Index falloff;
};

class VisualAccidentalNoiseNodeTiers : public VisualAccidentalNoiseNode {
	GDCLASS(VisualAccidentalNoiseNodeTiers, VisualAccidentalNoiseNode);

public:
	enum Smoothness {
		SMOOTHING_DISABLED,
		SMOOTHING_ENABLED
	};

	void set_smooth(Smoothness p_smooth);
	Smoothness get_smooth() const;

public:
	virtual String get_caption() const;

	virtual void set_input_port_value(int p_port, const Variant &p_value);
	virtual Variant get_input_port_value(int p_port) const;
	virtual int get_input_port_count() const;
	virtual PortType get_input_port_type(int p_port) const;
	virtual String get_input_port_name(int p_port) const;

	virtual int get_output_port_count() const;
	virtual PortType get_output_port_type(int p_port) const;
	virtual String get_output_port_name(int p_port) const;

	virtual Vector<StringName> get_editable_properties() const;

	virtual void evaluate(Ref<VisualAccidentalNoise> noise);

	VisualAccidentalNoiseNodeTiers();

protected:
	static void _bind_methods();

private:
	Smoothness smooth;

	Index input;
	Index tiers;
};

VARIANT_ENUM_CAST(VisualAccidentalNoiseNodeTiers::Smoothness);

class VisualAccidentalNoiseNodeGradient : public VisualAccidentalNoiseNode {
	GDCLASS(VisualAccidentalNoiseNodeGradient, VisualAccidentalNoiseNode);

public:
	void set_axis(Axis::AxisType p_type);
	Axis::AxisType get_axis() const;

public:
	virtual String get_caption() const;

	virtual int get_input_port_count() const;
	virtual PortType get_input_port_type(int p_port) const;
	virtual String get_input_port_name(int p_port) const;

	virtual int get_output_port_count() const;
	virtual PortType get_output_port_type(int p_port) const;
	virtual String get_output_port_name(int p_port) const;

	virtual Vector<StringName> get_editable_properties() const;

	virtual void evaluate(Ref<VisualAccidentalNoise> noise);

	VisualAccidentalNoiseNodeGradient();

protected:
	static void _bind_methods();

private:
	Axis axis;
};

class VisualAccidentalNoiseNodeDerivative : public VisualAccidentalNoiseNode {
	GDCLASS(VisualAccidentalNoiseNodeDerivative, VisualAccidentalNoiseNode);

public:
	void set_axis(Axis::AxisType p_type);
	Axis::AxisType get_axis() const;

public:
	virtual String get_caption() const;

	virtual void set_input_port_value(int p_port, const Variant &p_value);
	virtual Variant get_input_port_value(int p_port) const;
	virtual int get_input_port_count() const;
	virtual PortType get_input_port_type(int p_port) const;
	virtual String get_input_port_name(int p_port) const;

	virtual int get_output_port_count() const;
	virtual PortType get_output_port_type(int p_port) const;
	virtual String get_output_port_name(int p_port) const;

	virtual Vector<StringName> get_editable_properties() const;

	virtual void evaluate(Ref<VisualAccidentalNoise> noise);

	VisualAccidentalNoiseNodeDerivative();

protected:
	static void _bind_methods();

private:
	Axis axis;

	Index input;
	Index spacing;
};

class VisualAccidentalNoiseNodeRadial : public VisualAccidentalNoiseNode {
	GDCLASS(VisualAccidentalNoiseNodeRadial, VisualAccidentalNoiseNode);

public:
	virtual String get_caption() const;

	virtual int get_input_port_count() const;
	virtual PortType get_input_port_type(int p_port) const;
	virtual String get_input_port_name(int p_port) const;

	virtual int get_output_port_count() const;
	virtual PortType get_output_port_type(int p_port) const;
	virtual String get_output_port_name(int p_port) const;

	virtual void evaluate(Ref<VisualAccidentalNoise> noise);

	VisualAccidentalNoiseNodeRadial();

protected:
	static void _bind_methods();
};

class VisualAccidentalNoiseNodeRandomize : public VisualAccidentalNoiseNode {
	GDCLASS(VisualAccidentalNoiseNodeRandomize, VisualAccidentalNoiseNode);

public:
	virtual String get_caption() const;

	virtual void set_input_port_value(int p_port, const Variant &p_value);
	virtual Variant get_input_port_value(int p_port) const;
	virtual int get_input_port_count() const;
	virtual PortType get_input_port_type(int p_port) const;
	virtual String get_input_port_name(int p_port) const;

	virtual int get_output_port_count() const;
	virtual PortType get_output_port_type(int p_port) const;
	virtual String get_output_port_name(int p_port) const;

	virtual void evaluate(Ref<VisualAccidentalNoise> noise);

	VisualAccidentalNoiseNodeRandomize();

protected:
	static void _bind_methods();

private:
	Index seed;
	Index low, high;
};

class VisualAccidentalNoiseNodeStep : public VisualAccidentalNoiseNode {
	GDCLASS(VisualAccidentalNoiseNodeStep, VisualAccidentalNoiseNode);

public:
	enum StepType {
		STEP_REGULAR,
		STEP_LINEAR,
		STEP_SMOOTH,
		STEP_SMOOTHER,
	};

	void set_type(StepType p_type);
	StepType get_type() const;

public:
	virtual String get_caption() const;

	virtual void set_input_port_value(int p_port, const Variant &p_value);
	virtual Variant get_input_port_value(int p_port) const;
	virtual int get_input_port_count() const;
	virtual PortType get_input_port_type(int p_port) const;
	virtual String get_input_port_name(int p_port) const;

	virtual int get_output_port_count() const;
	virtual PortType get_output_port_type(int p_port) const;
	virtual String get_output_port_name(int p_port) const;

	virtual Vector<StringName> get_editable_properties() const;

	virtual void evaluate(Ref<VisualAccidentalNoise> noise);

	VisualAccidentalNoiseNodeStep();

protected:
	static void _bind_methods();

private:
	StepType type;

	Index value;
	Index low, high;
	Index control;
};

VARIANT_ENUM_CAST(VisualAccidentalNoiseNodeStep::StepType);

class VisualAccidentalNoiseNodeCurveSection : public VisualAccidentalNoiseNode {
	GDCLASS(VisualAccidentalNoiseNodeCurveSection, VisualAccidentalNoiseNode);

public:
	virtual String get_caption() const;

	virtual void set_input_port_value(int p_port, const Variant &p_value);
	virtual Variant get_input_port_value(int p_port) const;
	virtual int get_input_port_count() const;
	virtual PortType get_input_port_type(int p_port) const;
	virtual String get_input_port_name(int p_port) const;

	virtual int get_output_port_count() const;
	virtual PortType get_output_port_type(int p_port) const;
	virtual String get_output_port_name(int p_port) const;

	virtual void evaluate(Ref<VisualAccidentalNoise> noise);

	VisualAccidentalNoiseNodeCurveSection();

protected:
	static void _bind_methods();

private:
	Index lowv;
	Index t0, t1, v0, v1;
	Index control;
};

class VisualAccidentalNoiseNodeHex : public VisualAccidentalNoiseNode {
	GDCLASS(VisualAccidentalNoiseNodeHex, VisualAccidentalNoiseNode);

public:
	enum HexType {
		HEX_TILE,
		HEX_BUMP,
	};

	void set_type(HexType p_type);
	HexType get_type() const;

public:
	virtual String get_caption() const;

	virtual void set_input_port_value(int p_port, const Variant &p_value);
	virtual Variant get_input_port_value(int p_port) const;
	virtual int get_input_port_count() const;
	virtual PortType get_input_port_type(int p_port) const;
	virtual String get_input_port_name(int p_port) const;

	virtual int get_output_port_count() const;
	virtual PortType get_output_port_type(int p_port) const;
	virtual String get_output_port_name(int p_port) const;

	virtual Vector<StringName> get_editable_properties() const;

	virtual void evaluate(Ref<VisualAccidentalNoise> noise);

	VisualAccidentalNoiseNodeHex();

protected:
	static void _bind_methods();

private:
	HexType type;

	Index seed;
};

VARIANT_ENUM_CAST(VisualAccidentalNoiseNodeHex::HexType);

class VisualAccidentalNoiseNodeColor : public VisualAccidentalNoiseNode {
	GDCLASS(VisualAccidentalNoiseNodeColor, VisualAccidentalNoiseNode);

public:
	void set_color(const Color &p_color);
	Color get_color() const;

public:
	virtual String get_caption() const;

	virtual int get_input_port_count() const;
	virtual PortType get_input_port_type(int p_port) const;
	virtual String get_input_port_name(int p_port) const;

	virtual int get_output_port_count() const;
	virtual PortType get_output_port_type(int p_port) const;
	virtual String get_output_port_name(int p_port) const;

	virtual Vector<StringName> get_editable_properties() const;

	virtual void evaluate(Ref<VisualAccidentalNoise> noise);

	VisualAccidentalNoiseNodeColor();

protected:
	static void _bind_methods();

private:
	Color color;
};

class VisualAccidentalNoiseNodeColorCombine : public VisualAccidentalNoiseNode {
	GDCLASS(VisualAccidentalNoiseNodeColorCombine, VisualAccidentalNoiseNode);

public:
	enum CombineMode {
		COMBINE_RGBA,
		COMBINE_HSVA,
	};

	void set_type(CombineMode p_type);
	CombineMode get_type() const;

public:
	virtual String get_caption() const;

	virtual void set_input_port_value(int p_port, const Variant &p_value);
	virtual Variant get_input_port_value(int p_port) const;
	virtual int get_input_port_count() const;
	virtual PortType get_input_port_type(int p_port) const;
	virtual String get_input_port_name(int p_port) const;

	virtual int get_output_port_count() const;
	virtual PortType get_output_port_type(int p_port) const;
	virtual String get_output_port_name(int p_port) const;

	virtual Vector<StringName> get_editable_properties() const;

	virtual void evaluate(Ref<VisualAccidentalNoise> noise);

	VisualAccidentalNoiseNodeColorCombine();

protected:
	static void _bind_methods();

private:
	CombineMode type;

	Index c1, c2, c3, c4;
};

VARIANT_ENUM_CAST(VisualAccidentalNoiseNodeColorCombine::CombineMode);

class VisualAccidentalNoiseNodeScaleOffset : public VisualAccidentalNoiseNode {
	GDCLASS(VisualAccidentalNoiseNodeScaleOffset, VisualAccidentalNoiseNode);

public:
	void set_scale(double p_value);
	double get_scale() const;

	void set_offset(double p_value);
	double get_offset() const;

public:
	virtual String get_caption() const;

	virtual void set_input_port_value(int p_port, const Variant &p_value);
	virtual Variant get_input_port_value(int p_port) const;
	virtual int get_input_port_count() const;
	virtual PortType get_input_port_type(int p_port) const;
	virtual String get_input_port_name(int p_port) const;

	virtual int get_output_port_count() const;
	virtual PortType get_output_port_type(int p_port) const;
	virtual String get_output_port_name(int p_port) const;

	virtual Vector<StringName> get_editable_properties() const;

	virtual void evaluate(Ref<VisualAccidentalNoise> noise);

	VisualAccidentalNoiseNodeScaleOffset();

protected:
	static void _bind_methods();

private:
	Index input;

	double scale;
	double offset;
};

class VisualAccidentalNoiseNodeFractalLayer : public VisualAccidentalNoiseNode {
	GDCLASS(VisualAccidentalNoiseNodeFractalLayer, VisualAccidentalNoiseNode);

public:
	enum LayerType {
		LAYER_FRACTAL,
		LAYER_RIDGED,
		LAYER_BILLOW,
	};

	void set_type(LayerType p_type);
	LayerType get_type() const;

	void set_basis(AccidentalNoise::BasisTypes p_basis);
	AccidentalNoise::BasisTypes get_basis() const;

public:
	virtual String get_caption() const;

	virtual void set_input_port_value(int p_port, const Variant &p_value);
	virtual Variant get_input_port_value(int p_port) const;
	virtual int get_input_port_count() const;
	virtual PortType get_input_port_type(int p_port) const;
	virtual String get_input_port_name(int p_port) const;

	virtual int get_output_port_count() const;
	virtual PortType get_output_port_type(int p_port) const;
	virtual String get_output_port_name(int p_port) const;

	virtual Vector<StringName> get_editable_properties() const;

	virtual void evaluate(Ref<VisualAccidentalNoise> noise);

	VisualAccidentalNoiseNodeFractalLayer();

protected:
	static void _bind_methods();

private:
	LayerType type;
	AccidentalNoise::BasisTypes basis;

	Index interp;
	double scale;
	double frequency;
	unsigned int seed;
	bool rot;
	double angle = 0.5;
	double ax = 0.0;
	double ay = 0.0;
	double az = 1.0;
};

VARIANT_ENUM_CAST(VisualAccidentalNoiseNodeFractalLayer::LayerType);

class VisualAccidentalNoiseNodeFractal : public VisualAccidentalNoiseNode {
	GDCLASS(VisualAccidentalNoiseNodeFractal, VisualAccidentalNoiseNode);

public:
	virtual String get_caption() const;

	virtual void set_input_port_value(int p_port, const Variant &p_value);
	virtual Variant get_input_port_value(int p_port) const;
	virtual int get_input_port_count() const;
	virtual PortType get_input_port_type(int p_port) const;
	virtual String get_input_port_name(int p_port) const;

	virtual int get_output_port_count() const;
	virtual PortType get_output_port_type(int p_port) const;
	virtual String get_output_port_name(int p_port) const;

	virtual void evaluate(Ref<VisualAccidentalNoise> noise);

	VisualAccidentalNoiseNodeFractal();

protected:
	static void _bind_methods();

private:
	Index seed;
	Index layer;
	Index persistence;
	Index lacunarity;
	Index numoctaves;
	Index frequency;
};

class VisualAccidentalNoiseNodeFractalVariant : public VisualAccidentalNoiseNode {
	GDCLASS(VisualAccidentalNoiseNodeFractalVariant, VisualAccidentalNoiseNode);

public:
	enum FractalType {
		TYPE_FBM,
		TYPE_RIDGED_MULTIFRACTAL,
		TYPE_BILLOW,
	};

	void set_type(FractalType p_type);
	FractalType get_type() const;

	void set_basis(AccidentalNoise::BasisTypes p_basis);
	AccidentalNoise::BasisTypes get_basis() const;

	void set_interpolation(AccidentalNoise::InterpolationTypes p_interpolation);
	AccidentalNoise::InterpolationTypes get_interpolation() const;

public:
	virtual String get_caption() const;

	virtual void set_input_port_value(int p_port, const Variant &p_value);
	virtual Variant get_input_port_value(int p_port) const;
	virtual int get_input_port_count() const;
	virtual PortType get_input_port_type(int p_port) const;
	virtual String get_input_port_name(int p_port) const;

	virtual int get_output_port_count() const;
	virtual PortType get_output_port_type(int p_port) const;
	virtual String get_output_port_name(int p_port) const;

	virtual Vector<StringName> get_editable_properties() const;

	virtual void evaluate(Ref<VisualAccidentalNoise> noise);

	VisualAccidentalNoiseNodeFractalVariant();

protected:
	static void _bind_methods();

private:
	FractalType type;
	AccidentalNoise::BasisTypes basis;
	AccidentalNoise::InterpolationTypes interpolation;

	unsigned int numoctaves;
	double frequency = 1.0;
	unsigned int seed = 0;
	bool rot = true;
};

VARIANT_ENUM_CAST(VisualAccidentalNoiseNodeFractalVariant::FractalType);

class VisualAccidentalNoiseNodeSetVar : public VisualAccidentalNoiseNode {
	GDCLASS(VisualAccidentalNoiseNodeSetVar, VisualAccidentalNoiseNode);

public:
	void set_var(const String &p_var);
	String get_var() const;

	void set_value(double p_value);
	double get_value() const;

public:
	virtual String get_caption() const;

	virtual void set_input_port_value(int p_port, const Variant &p_value);
	virtual Variant get_input_port_value(int p_port) const;
	virtual int get_input_port_count() const;
	virtual PortType get_input_port_type(int p_port) const;
	virtual String get_input_port_name(int p_port) const;

	virtual int get_output_port_count() const;
	virtual PortType get_output_port_type(int p_port) const;
	virtual String get_output_port_name(int p_port) const;

	virtual Vector<StringName> get_editable_properties() const;

	virtual void evaluate(Ref<VisualAccidentalNoise> noise);

	VisualAccidentalNoiseNodeSetVar();

protected:
	static void _bind_methods();

private:
	String var;
	double value;
};

class VisualAccidentalNoiseNodeGetVar : public VisualAccidentalNoiseNode {
	GDCLASS(VisualAccidentalNoiseNodeGetVar, VisualAccidentalNoiseNode);

public:
	void set_var(const String &p_var);
	String get_var() const;

public:
	virtual String get_caption() const;

	virtual int get_input_port_count() const;
	virtual PortType get_input_port_type(int p_port) const;
	virtual String get_input_port_name(int p_port) const;

	virtual int get_output_port_count() const;
	virtual PortType get_output_port_type(int p_port) const;
	virtual String get_output_port_name(int p_port) const;

	virtual void evaluate(Ref<VisualAccidentalNoise> noise);

	VisualAccidentalNoiseNodeGetVar();

protected:
	static void _bind_methods();

private:
	String var;
};

class VisualAccidentalNoiseNodeReroute : public VisualAccidentalNoiseNode {
	GDCLASS(VisualAccidentalNoiseNodeReroute, VisualAccidentalNoiseNode);

public:
	virtual String get_caption() const;

	virtual void set_input_port_value(int p_port, const Variant &p_value);
	virtual Variant get_input_port_value(int p_port) const;
	virtual int get_input_port_count() const;
	virtual PortType get_input_port_type(int p_port) const;
	virtual String get_input_port_name(int p_port) const;

	virtual int get_output_port_count() const;
	virtual PortType get_output_port_type(int p_port) const;
	virtual String get_output_port_name(int p_port) const;

	virtual void evaluate(Ref<VisualAccidentalNoise> noise);

	VisualAccidentalNoiseNodeReroute();

protected:
	static void _bind_methods();

private:
	Index input;
};

class VisualAccidentalNoiseNodeSequence : public VisualAccidentalNoiseNode {
	GDCLASS(VisualAccidentalNoiseNodeSequence, VisualAccidentalNoiseNode);

public:
	enum Operator {
		OP_SELECT, // acts like selector
		OP_ADD,
		OP_SUB,
		OP_MUL,
		OP_DIV,
		OP_POW,
		OP_MAX,
		OP_MIN,
		OP_BIAS,
		OP_GAIN,
	};

	void set_operator(Operator p_op);
	Operator get_operator() const;

	enum {
		MIN_INPUTS = 2,
		MAX_INPUTS = 32
	};
	void set_input_count(int p_input_count);
	int get_input_count() const;

	void set_selected_input(int p_input);
	int get_selected_input();

public:
	virtual String get_caption() const;

	virtual void set_input_port_value(int p_port, const Variant &p_value);
	virtual Variant get_input_port_value(int p_port) const;
	virtual int get_input_port_count() const;
	virtual PortType get_input_port_type(int p_port) const;
	virtual String get_input_port_name(int p_port) const;

	virtual int get_output_port_count() const;
	virtual PortType get_output_port_type(int p_port) const;
	virtual String get_output_port_name(int p_port) const;

	virtual Vector<StringName> get_editable_properties() const;

	virtual void evaluate(Ref<VisualAccidentalNoise> noise);

	VisualAccidentalNoiseNodeSequence();

protected:
	static void _bind_methods();

private:
	Operator op;
	Index inputs[MAX_INPUTS];
	int input_count;
	int selected_input;
};

VARIANT_ENUM_CAST(VisualAccidentalNoiseNodeSequence::Operator);

#endif
