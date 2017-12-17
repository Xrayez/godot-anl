extends Node2D

func _init():
	var n = AnlNoise.new()

	var gradient = n.y()
	var fractal = n.fbm(AnlNoise.BASIS_SIMPLEX, n.constant(AnlNoise.INTERP_LINEAR),[3, 5, randi()])
	var scale_offset = n.scale_offset(fractal, 0.5, 0)
	var perturb = n.translate(gradient, scale_offset)

	var scalar
	scalar = n.get_scalar_2d(10.0, 15.0, n.get_last_index())
	scalar = n.get_scalar_3d(10.0, 15.0, 5.5, n.get_last_index())
	scalar = n.get_scalar_4d(10.0, 15.0, 5.5, 7.8, n.get_last_index())
	scalar = n.get_scalar_6d([10.0, 15.0, 5.5, 7.8, 9.7, 14.3], n.get_last_index())

	var color
	color = n.get_color_2d(10.0, 15.0, n.get_last_index())
	color = n.get_color_3d(10.0, 15.0, 5.5, n.get_last_index())
	color = n.get_color_4d(10.0, 15.0, 5.5, 7.8, n.get_last_index())
	color = n.get_color_6d([10.0, 15.0, 5.5, 7.8, 9.7, 14.3], n.get_last_index())
