#ifndef VISUAL_ANL_NOISE_NODES_H
#define VISUAL_ANL_NOISE_NODES_H

#include "../visual_anl_noise.h"

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

    VisualAnlNoiseNodeScalar();

protected:
    static void _bind_methods();

private:
	ScalarType type;
    real_t constant;
};

VARIANT_ENUM_CAST(VisualAnlNoiseNodeScalar::ScalarType);

#endif
