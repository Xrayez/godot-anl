#ifndef VISUAL_ANL_NOISE_NODES_H
#define VISUAL_ANL_NOISE_NODES_H

#include "../visual_anl_noise.h"

class VisualAnlNoiseNodeConstant : public VisualAnlNoiseNode {
	GDCLASS(VisualAnlNoiseNodeConstant, VisualAnlNoiseNode)

    real_t constant;

protected:
    static void _bind_methods();

public:
	virtual String get_caption() const;

	virtual int get_input_port_count() const;
	virtual PortType get_input_port_type(int p_port) const;
	virtual String get_input_port_name(int p_port) const;

	virtual int get_output_port_count() const;
	virtual PortType get_output_port_type(int p_port) const;
	virtual String get_output_port_name(int p_port) const;

	void set_constant(real_t p_value);
	real_t get_constant() const;

	virtual Vector<StringName> get_editable_properties() const;

    VisualAnlNoiseNodeConstant();
};

#endif
