extends Node2D

func _init():
    var n = AccidentalNoise.new()

    var expression = String()

    expression = "select(0, 1, scaleY(scaleX(gradientBasis(2, 2), 5), 5), 0.15, 0)"
    n.evaluate(expression)
    n.get_color_2d(10.0, 20.0, n.index)

    expression = "select(0, 1, scaleY(scaleX(translate(gradientBasis(2, 2), simplexBasis(3)), 5), 5), valueBasis(2, 8), 0)"
    n.evaluate(expression)
    n.get_color_3d(10.0, 20.0, 30.0, n.index)

    expression = "select(0, 1, sin(cos(scale(gradientBasis(select(0, 1, translateY(translateX(radial, -0.885), -0.5), 0.4, 0.0), 10), 10))), 0.841, 0)"
    n.evaluate(expression)
    n.get_color_6d(15.0, 17.8, 46.35, 7.1, 65.3, 47.2, n.index)
