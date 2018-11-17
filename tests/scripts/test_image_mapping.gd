extends Node2D

func _init():
	var n = AccidentalNoise.new()

	var r = n.scale(n.simplex_basis(randi()), n.constant(5))
	r = n.clamp(r, n.constant(0.6) , n.constant(0.75))
	r = n.multiply(r, n.hex_bump())
	r = n.rotate(r, n.constant(45), n.one(), n.one(), n.zero())
	r = n.multiply(r, n.constant(0.85))

	var g = n.scale(n.mix(n.gradient_basis(n.constant(3), n.constant(randi())), n.constant(0.5), r), n.constant(10))
	g = n.clamp(g, n.constant(0.2), n.constant(0.5))
	g = n.multiply(g, n.constant(0.4))

	var b = n.simplex_basis(randi())

	var a = n.simplex_basis(randi())

	var combine = n.combine_rgba(r,g,b,a)
	n.function = n.scale(combine, n.constant(3))

	n.get_image(100, 100)
	n.get_texture(100, 100)
