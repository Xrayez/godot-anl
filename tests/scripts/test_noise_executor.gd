extends Node2D

func _init():
	var n = AccidentalNoise.new()

	var gradient = n.y()
	var fractal = n.fbm(AccidentalNoise.BASIS_SIMPLEX, n.constant(AccidentalNoise.INTERP_LINEAR), 3, 5, randi())
	var scale_offset = n.scale_offset(fractal, 0.5, 0)
	n.eval_index = n.translate(gradient, scale_offset)

	n.get_noise_2d(10.0, 15.0)
	n.get_noise_3d(10.0, 15.0, 5.5)
	n.get_noise_4d(10.0, 15.0, 5.5, 7.8)
	n.get_noise_6d(10.0, 15.0, 5.5, 7.8, 9.7, 14.3)

	n.get_color_2d(10.0, 15.0)
	n.get_color_3d(10.0, 15.0, 5.5)
	n.get_color_4d(10.0, 15.0, 5.5, 7.8)
	n.get_color_6d(10.0, 15.0, 5.5, 7.8, 9.7, 14.3)

	n.get_noise_2dv(Vector2(10.0, 15.0))
	n.get_noise_3dv(Vector3(10.0, 15.0, 5.5))

	n.get_color_2dv(Vector2(10.0, 15.0))
	n.get_color_3dv(Vector3(10.0, 15.0, 5.5))
