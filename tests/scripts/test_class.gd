extends Node2D

func _init():
	var n = AccidentalNoise.new()

	n.mode = AccidentalNoise.SEAMLESS_XY;
	n.ranges = AABB(Vector3(-2, -2, -2), Vector3(4, 4, 4))
	n.format = AccidentalNoise.FORMAT_COLOR
