extends Node2D

func _init():
	var n = AccidentalNoise.new()

	var gradient = n.y()
	var fractal = n.fbm(AccidentalNoise.BASIS_SIMPLEX, n.constant(AccidentalNoise.INTERP_LINEAR), 3, 5, randi())
	var scale_offset = n.scale_offset(fractal, 0.5, 0)
	n.translate(gradient, scale_offset)

	n.get_scalar_2d(10.0, 15.0, n.index)
	n.get_scalar_3d(10.0, 15.0, 5.5, n.index)
	n.get_scalar_4d(10.0, 15.0, 5.5, 7.8, n.index)
	n.get_scalar_6d(10.0, 15.0, 5.5, 7.8, 9.7, 14.3, n.index)

	n.get_color_2d(10.0, 15.0, n.index)
	n.get_color_3d(10.0, 15.0, 5.5, n.index)
	n.get_color_4d(10.0, 15.0, 5.5, 7.8, n.index)
	n.get_color_6d(10.0, 15.0, 5.5, 7.8, 9.7, 14.3, n.index)
