#ifndef VISUAL_ANL_NOISE_NODES_H
#define VISUAL_ANL_NOISE_NODES_H

#include "visual_anl_noise.h"

class VisualAnlNoiseNodeScalar : public VisualAnlNoiseNode {
	GDCLASS(VisualAnlNoiseNodeScalar, VisualAnlNoiseNode)

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

	virtual void evaluate(Ref<VisualAnlNoise> noise);

    VisualAnlNoiseNodeScalar();

protected:
    static void _bind_methods();

private:
	ScalarType type;
    real_t constant;
};

VARIANT_ENUM_CAST(VisualAnlNoiseNodeScalar::ScalarType);


class VisualAnlNoiseNodeSeed : public VisualAnlNoiseNode {
	GDCLASS(VisualAnlNoiseNodeSeed, VisualAnlNoiseNode)

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

	virtual void evaluate(Ref<VisualAnlNoise> noise);

    VisualAnlNoiseNodeSeed();

protected:
    static void _bind_methods();

private:
    unsigned int seed;
};


class VisualAnlNoiseNodeSeeder : public VisualAnlNoiseNode {
	GDCLASS(VisualAnlNoiseNodeSeeder, VisualAnlNoiseNode)

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

	virtual void evaluate(Ref<VisualAnlNoise> noise);

    VisualAnlNoiseNodeSeeder();

protected:
    static void _bind_methods();

private:
    Index seed;
	Index input;
};


class VisualAnlNoiseNodeScalarOp : public VisualAnlNoiseNode {
	GDCLASS(VisualAnlNoiseNodeScalarOp, VisualAnlNoiseNode)

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

	virtual void evaluate(Ref<VisualAnlNoise> noise);

    VisualAnlNoiseNodeScalarOp();

protected:
    static void _bind_methods();

private:
	Operator op;
	Index a, b;
};

VARIANT_ENUM_CAST(VisualAnlNoiseNodeScalarOp::Operator);


class VisualAnlNoiseNodeScalarFunc : public VisualAnlNoiseNode {
	GDCLASS(VisualAnlNoiseNodeScalarFunc, VisualAnlNoiseNode)

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

	virtual void evaluate(Ref<VisualAnlNoise> noise);

    VisualAnlNoiseNodeScalarFunc();

protected:
    static void _bind_methods();

private:
	Function func;
	Index input;
};

VARIANT_ENUM_CAST(VisualAnlNoiseNodeScalarFunc::Function);


class VisualAnlNoiseNodeValueBasis : public VisualAnlNoiseNode {
	GDCLASS(VisualAnlNoiseNodeValueBasis, VisualAnlNoiseNode)

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

	virtual void evaluate(Ref<VisualAnlNoise> noise);

    VisualAnlNoiseNodeValueBasis();

protected:
    static void _bind_methods();

private:
	Index interp;
	Index seed;
};


class VisualAnlNoiseNodeGradientBasis : public VisualAnlNoiseNode {
	GDCLASS(VisualAnlNoiseNodeGradientBasis, VisualAnlNoiseNode)

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

	virtual void evaluate(Ref<VisualAnlNoise> noise);

    VisualAnlNoiseNodeGradientBasis();

protected:
    static void _bind_methods();

private:
	Index interp;
	Index seed;
};


class VisualAnlNoiseNodeCellularBasis : public VisualAnlNoiseNode {
	GDCLASS(VisualAnlNoiseNodeCellularBasis, VisualAnlNoiseNode)

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

	virtual void evaluate(Ref<VisualAnlNoise> noise);

    VisualAnlNoiseNodeCellularBasis();

protected:
    static void _bind_methods();

private:
	Index f1, f2, f3, f4;
	Index d1, d2, d3, d4;
	Index distance, seed;
};


class VisualAnlNoiseNodeSimplexBasis : public VisualAnlNoiseNode {
	GDCLASS(VisualAnlNoiseNodeSimplexBasis, VisualAnlNoiseNode)

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

	virtual void evaluate(Ref<VisualAnlNoise> noise);

    VisualAnlNoiseNodeSimplexBasis();

protected:
    static void _bind_methods();

private:
	Index seed;
};


class VisualAnlNoiseNodeExpression : public VisualAnlNoiseNode {
	GDCLASS(VisualAnlNoiseNodeExpression, VisualAnlNoiseNode)

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

	virtual void evaluate(Ref<VisualAnlNoise> noise);

    VisualAnlNoiseNodeExpression();

protected:
    static void _bind_methods();

private:
	String expression;
};


class VisualAnlNoiseNodeTranslate : public VisualAnlNoiseNode {
	GDCLASS(VisualAnlNoiseNodeTranslate, VisualAnlNoiseNode)

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

	virtual void evaluate(Ref<VisualAnlNoise> noise);

    VisualAnlNoiseNodeTranslate();

protected:
    static void _bind_methods();

private:
	static const String method;

	Index input, by;
    Axis axis;
};


class VisualAnlNoiseNodeScale : public VisualAnlNoiseNode {
	GDCLASS(VisualAnlNoiseNodeScale, VisualAnlNoiseNode)

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

	virtual void evaluate(Ref<VisualAnlNoise> noise);

    VisualAnlNoiseNodeScale();

protected:
    static void _bind_methods();

private:
	static const String method;

	Index input, by;
    Axis axis;
};


class VisualAnlNoiseNodeRotate : public VisualAnlNoiseNode {
	GDCLASS(VisualAnlNoiseNodeRotate, VisualAnlNoiseNode)

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

	virtual void evaluate(Ref<VisualAnlNoise> noise);

    VisualAnlNoiseNodeRotate();

protected:
    static void _bind_methods();

private:
	Index input, angle;
	Index ax, ay, az;
};


class VisualAnlNoiseNodeClamp : public VisualAnlNoiseNode {
	GDCLASS(VisualAnlNoiseNodeClamp, VisualAnlNoiseNode)

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

	virtual void evaluate(Ref<VisualAnlNoise> noise);

    VisualAnlNoiseNodeClamp();

protected:
    static void _bind_methods();

private:
	Index input;
	Index low, high;
};


class VisualAnlNoiseNodeMix : public VisualAnlNoiseNode {
	GDCLASS(VisualAnlNoiseNodeMix, VisualAnlNoiseNode)

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

	virtual void evaluate(Ref<VisualAnlNoise> noise);

    VisualAnlNoiseNodeMix();

protected:
    static void _bind_methods();

private:
	Index low, high;
	Index control;
};


class VisualAnlNoiseNodeSelect : public VisualAnlNoiseNode {
	GDCLASS(VisualAnlNoiseNodeSelect, VisualAnlNoiseNode)

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

	virtual void evaluate(Ref<VisualAnlNoise> noise);

    VisualAnlNoiseNodeSelect();

protected:
    static void _bind_methods();

private:
	Index low, high;
	Index control;
	Index threshold;
	Index falloff;
};


class VisualAnlNoiseNodeTiers : public VisualAnlNoiseNode {
	GDCLASS(VisualAnlNoiseNodeTiers, VisualAnlNoiseNode)

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

	virtual void evaluate(Ref<VisualAnlNoise> noise);

    VisualAnlNoiseNodeTiers();

protected:
    static void _bind_methods();

private:
	Smoothness smooth;

	Index input;
	Index tiers;
};

VARIANT_ENUM_CAST(VisualAnlNoiseNodeTiers::Smoothness);


class VisualAnlNoiseNodeGradient : public VisualAnlNoiseNode {
	GDCLASS(VisualAnlNoiseNodeGradient, VisualAnlNoiseNode)

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

	virtual void evaluate(Ref<VisualAnlNoise> noise);

    VisualAnlNoiseNodeGradient();

protected:
    static void _bind_methods();

private:
	Axis axis;
};


class VisualAnlNoiseNodeDerivative : public VisualAnlNoiseNode {
	GDCLASS(VisualAnlNoiseNodeDerivative, VisualAnlNoiseNode)

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

	virtual void evaluate(Ref<VisualAnlNoise> noise);

    VisualAnlNoiseNodeDerivative();

protected:
    static void _bind_methods();

private:
	Axis axis;

	Index input;
	Index spacing;
};


class VisualAnlNoiseNodeRadial : public VisualAnlNoiseNode {
	GDCLASS(VisualAnlNoiseNodeRadial, VisualAnlNoiseNode)

public:
	virtual String get_caption() const;

	virtual int get_input_port_count() const;
	virtual PortType get_input_port_type(int p_port) const;
	virtual String get_input_port_name(int p_port) const;

	virtual int get_output_port_count() const;
	virtual PortType get_output_port_type(int p_port) const;
	virtual String get_output_port_name(int p_port) const;

	virtual void evaluate(Ref<VisualAnlNoise> noise);

    VisualAnlNoiseNodeRadial();

protected:
    static void _bind_methods();
};


class VisualAnlNoiseNodeRandomize : public VisualAnlNoiseNode {
	GDCLASS(VisualAnlNoiseNodeRandomize, VisualAnlNoiseNode)

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

	virtual void evaluate(Ref<VisualAnlNoise> noise);

    VisualAnlNoiseNodeRandomize();

protected:
    static void _bind_methods();

private:
	Index seed;
	Index low, high;
};


class VisualAnlNoiseNodeStep : public VisualAnlNoiseNode {
	GDCLASS(VisualAnlNoiseNodeStep, VisualAnlNoiseNode)

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

	virtual void evaluate(Ref<VisualAnlNoise> noise);

    VisualAnlNoiseNodeStep();

protected:
    static void _bind_methods();

private:
	StepType type;

	Index value;
	Index low, high;
	Index control;
};

VARIANT_ENUM_CAST(VisualAnlNoiseNodeStep::StepType);


class VisualAnlNoiseNodeCurveSection : public VisualAnlNoiseNode {
	GDCLASS(VisualAnlNoiseNodeCurveSection, VisualAnlNoiseNode)

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

	virtual void evaluate(Ref<VisualAnlNoise> noise);

    VisualAnlNoiseNodeCurveSection();

protected:
    static void _bind_methods();

private:
	Index lowv;
	Index t0, t1, v0, v1;
	Index control;
};


class VisualAnlNoiseNodeHex : public VisualAnlNoiseNode {
	GDCLASS(VisualAnlNoiseNodeHex, VisualAnlNoiseNode)

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

	virtual void evaluate(Ref<VisualAnlNoise> noise);

    VisualAnlNoiseNodeHex();

protected:
    static void _bind_methods();

private:
	HexType type;

	Index seed;
};

VARIANT_ENUM_CAST(VisualAnlNoiseNodeHex::HexType);


class VisualAnlNoiseNodeColor : public VisualAnlNoiseNode {
	GDCLASS(VisualAnlNoiseNodeColor, VisualAnlNoiseNode)

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

	virtual void evaluate(Ref<VisualAnlNoise> noise);

    VisualAnlNoiseNodeColor();

protected:
    static void _bind_methods();

private:
	Color color;
};


class VisualAnlNoiseNodeColorCombine : public VisualAnlNoiseNode {
	GDCLASS(VisualAnlNoiseNodeColorCombine, VisualAnlNoiseNode)

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

	virtual void evaluate(Ref<VisualAnlNoise> noise);

    VisualAnlNoiseNodeColorCombine();

protected:
    static void _bind_methods();

private:
	CombineMode type;

	Index c1, c2, c3, c4;
};

VARIANT_ENUM_CAST(VisualAnlNoiseNodeColorCombine::CombineMode);


class VisualAnlNoiseNodeScaleOffset : public VisualAnlNoiseNode {
	GDCLASS(VisualAnlNoiseNodeScaleOffset, VisualAnlNoiseNode)

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

	virtual void evaluate(Ref<VisualAnlNoise> noise);

    VisualAnlNoiseNodeScaleOffset();

protected:
    static void _bind_methods();

private:
    Index input;

	double scale;
	double offset;
};


class VisualAnlNoiseNodeFractalLayer : public VisualAnlNoiseNode {
	GDCLASS(VisualAnlNoiseNodeFractalLayer, VisualAnlNoiseNode)

public:
	enum LayerType {
		LAYER_FRACTAL,
		LAYER_RIDGED,
		LAYER_BILLOW,
	};

	void set_type(LayerType p_type);
	LayerType get_type() const;

	void set_basis(anl::BasisTypes p_basis);
	anl::BasisTypes get_basis() const;

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

	virtual void evaluate(Ref<VisualAnlNoise> noise);

    VisualAnlNoiseNodeFractalLayer();

protected:
    static void _bind_methods();

private:
	LayerType type;
	anl::BasisTypes basis;

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

VARIANT_ENUM_CAST(VisualAnlNoiseNodeFractalLayer::LayerType);


class VisualAnlNoiseNodeFractal : public VisualAnlNoiseNode {
	GDCLASS(VisualAnlNoiseNodeFractal, VisualAnlNoiseNode)

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

	virtual void evaluate(Ref<VisualAnlNoise> noise);

    VisualAnlNoiseNodeFractal();

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

#endif
