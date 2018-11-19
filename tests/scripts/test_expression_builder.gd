extends Node2D

func _init():
	var n = AccidentalNoise.new()

	var expression = String()

	expression = "select(0, 1, scale_y(scale_x(gradient_basis(2, 2), 5), 5), 0.15, 0)"
	n.function = n.evaluate(expression)

	n.get_color_2d(10.0, 20.0)

	expression = "select(0, 1, scale_y(scale_x(translate(gradient_basis(2, 2), simplex_basis(3)), 5), 5), value_basis(2, 8), 0)"
	n.function = n.evaluate(expression)
	n.get_color_3d(10.0, 20.0, 30.0)

	expression = "select(0, 1, sin(cos(scale(gradient_basis(select(0, 1, translate_y(translate_x(radial, -0.885), -0.5), 0.4, 0.0), 10), 10))), 0.841, 0)"
	n.function = n.evaluate(expression)
	n.get_color_6d(15.0, 17.8, 46.35, 7.1, 65.3, 47.2)

	n.expression = "x"
	n.expression = ""
