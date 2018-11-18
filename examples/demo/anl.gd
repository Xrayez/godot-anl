extends Node2D

var texture = ImageTexture.new()

var noises = [
	"value_basis",
	"gradient_basis",
	"simplex_basis",
	"cellular_basis",
	"fractal",
	"hex_tile",
	"hex_bump",
	"x",
	"y",
	"radial",
]

var x = 10
var y = 10

var cur_method = noises[0]

onready var size = get_viewport().size
onready var ratio = float(size.x) / size.y

onready var mapping_ranges = AABB(Vector3(), Vector3(x * ratio, y, 1))

func _ready():
	value_basis()
	for noise in noises:
		$noise.add_item(noise)

func value_basis():
	var n = AccidentalNoise.new()
	n.value_basis( n.constant(AccidentalNoise.INTERP_HERMITE), n.seed(randi()) )
	get_texture(n)

func gradient_basis():
	var n = AccidentalNoise.new()
	n.gradient_basis( n.constant(AccidentalNoise.INTERP_QUINTIC), n.seed(randi()) )
	get_texture(n)

func simplex_basis():
	var n = AccidentalNoise.new()
	n.simplex_basis( n.seed(randi()) )
	get_texture(n)

func cellular_basis():
	var n = AccidentalNoise.new()

	var basis = n.cellular_basis( n.constant(-0.25), n.constant(-0.3), n.constant(0.8), n.constant(0),
								  n.zero(), n.zero(), n.zero(), n.zero(),
								  n.constant(AccidentalNoise.DISTANCE_EUCLID), n.seed(randi()) )
	n.clamp(basis, n.zero(), n.one())
	get_texture(n)

func fractal():
	var n = AccidentalNoise.new()

	var layer = n.fractal_layer(AccidentalNoise.BASIS_GRADIENT, n.constant(AccidentalNoise.INTERP_QUINTIC), 1, 1, randi())

	var persistence = n.constant(-0.5)
	var lacunarity = n.constant(4)
	var numoctaves = n.constant(2)
	var freq = n.constant(1)

	var s = n.seed(randi())
	n.fractal(s, layer, persistence, lacunarity, numoctaves, freq)
	get_texture(n)

func hex_tile():
	var n = AccidentalNoise.new()
	n.hex_tile( n.seed(randi()) )
	get_texture(n)

func hex_bump():
	var n = AccidentalNoise.new()
	n.hex_bump()
	get_texture(n)

func x():
	var n = AccidentalNoise.new()
	n.x()
	get_texture(n)

func y():
	var n = AccidentalNoise.new()
	n.y()
	get_texture(n)

func radial():
	var n = AccidentalNoise.new()
	n.radial()
	get_texture(n)

func get_texture(n):
	n.mode = AccidentalNoise.SEAMLESS_NONE
	n.format = AccidentalNoise.FORMAT_HEIGHTMAP
	n.ranges = mapping_ranges

	if not cur_method in ['x', 'y', 'radial']:
		n.function = n.clamp(n.last_function, n.zero(), n.one())
	else:
		n.function = n.last_function

	texture = n.get_texture(size.x, size.y)

func _input(event):
	if event is InputEventMouseButton:
		if event.button_index == BUTTON_RIGHT and event.pressed:
			var id = $noise.selected
			_on_noise_item_selected(id)

func _on_noise_item_selected(id):
	var method = $noise.get_item_text(id)
	cur_method = method
	if has_method(method):
		call(method)
		update()

func _draw():
	draw_texture(texture, Vector2())
