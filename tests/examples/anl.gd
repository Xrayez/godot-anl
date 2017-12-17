extends Node2D

var texture = ImageTexture.new()
var image = Image.new()

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

onready var size = get_viewport().size
onready var ratio = float(size.x) / size.y

onready var map_start = Vector2()
onready var map_end = Vector2(x * ratio, y)

func value_basis():
	var n = AnlNoise.new()
	n.value_basis( n.constant(AnlNoise.INTERP_HERMITE), n.seed(randi()) )
	map_to_image(n)

func gradient_basis():
	var n = AnlNoise.new()
	n.gradient_basis( n.constant(AnlNoise.INTERP_QUINTIC), n.seed(randi()) )
	map_to_image(n)

func simplex_basis():
	var n = AnlNoise.new()
	n.simplex_basis( n.seed(randi()) )
	map_to_image(n)
	
func cellular_basis():
	var n = AnlNoise.new()
	
	var basis = n.cellular_basis( [n.constant(-1), n.one(), n.zero(), n.zero()], 
									[n.zero(), n.zero(), n.zero(), n.zero()], 
									n.constant(AnlNoise.DISTANCE_MANHATTAN), n.seed(randi()) )
	n.gain(n.constant(0.5), basis)
	map_to_image(n)
	
func fractal():
	var n = AnlNoise.new()
	
	var layer = n.fractal_layer(AnlNoise.BASIS_GRADIENT, n.constant(AnlNoise.INTERP_QUINTIC),
								[1,0.5,randf(),0], [1,1,1,1])
	
	var persistence = n.constant(-0.5)
	var lacunarity = n.constant(4)
	var numoctaves = n.constant(2)
	var freq = n.constant(1)
	
	var s = n.seed(randi())
	n.fractal(s, layer, [persistence, lacunarity, numoctaves, freq])
	map_to_image(n)
	
func hex_tile():
	var n = AnlNoise.new()
	n.hex_tile( n.seed(randi()) )
	map_to_image(n)
	
func hex_bump():
	var n = AnlNoise.new()
	n.hex_bump()
	map_to_image(n)
	
func x():
	var n = AnlNoise.new()
	n.x()
	map_to_image(n)
	
func y():
	var n = AnlNoise.new()
	n.y()
	map_to_image(n)
	
func radial():
	var n = AnlNoise.new()
	n.radial()
	map_to_image(n)
	
func map_to_image(n):
	image = n.map_to_image(size, AnlNoise.SEAMLESS_NONE, n.get_last_index(), map_start, map_end)
	
func _ready():
	value_basis()
	for noise in noises:
		$noise.add_item(noise)
		
func _input(event):
	if event is InputEventMouseButton:
		if event.button_index == BUTTON_RIGHT and event.pressed:
			var id = $noise.selected
			_on_noise_item_selected(id)

func _on_noise_item_selected(id):
	var method = $noise.get_item_text(id)
	if has_method(method):
		call(method)
		update()

func _draw():
	texture.create_from_image(image, 0)
	draw_texture(texture, Vector2())
