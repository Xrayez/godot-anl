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

    VisualAnlNoiseNodeScalar();

protected:
    static void _bind_methods();

private:
	ScalarType type;
    real_t constant;
};

VARIANT_ENUM_CAST(VisualAnlNoiseNodeScalar::ScalarType);


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

	Index source, by;
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

	Index source, by;
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
	Index source, angle;
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
	Index source;
	Index low, high;
};

#endif
