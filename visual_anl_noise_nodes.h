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

	virtual Vector<StringName> get_editable_properties() const;

	virtual void evaluate(Ref<VisualAnlNoise> noise);

    VisualAnlNoiseNodeSimplexBasis();

protected:
    static void _bind_methods();

private:
	Index seed;
};

VARIANT_ENUM_CAST(VisualAnlNoiseNodeScalar::ScalarType);

#endif
