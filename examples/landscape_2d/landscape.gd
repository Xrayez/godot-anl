extends Node2D

export var height = 256
export var width = 512
export var noise_seed = 42

var image
var texture

func _ready():
	var noise = AccidentalNoise.new()
	
	var gradient = noise.y() # horizontal gradient function
	
	# Generate Fractal Brownian Motion noise
	var basis = AccidentalNoise.BASIS_GRADIENT
	var interp = AccidentalNoise.INTERP_QUINTIC
	var fbm = noise.fbm(basis, interp, 4, 3, noise_seed, false)
	
	var scale_offset = noise.scale_offset(fbm, 0.4, 0.0)
	
	# Randomly translate gradient noise coordinates with fbm
	var perturb = noise.translate(gradient, scale_offset)

	# Apply binary threshold
	var zero = noise.zero()
	var one = noise.one()
	var half = noise.point5()
	var select = noise.select(zero, one, perturb, half, zero)
	
	# Selects the function to be evaluated
	noise.function = select
	
	# Map noise to image manually
	image = Image.new()
	image.create(width, height, 0, Image.FORMAT_RGBA8)
	image.lock()
	
	# Respect aspect ratio when mapping noise
	var ratio = float(width) / height

	for y in height:
		for x in width:
			# Normalize to 0-1 ranges
			var dx = float(x) / width
			var dy = float(y) / height
			# Evaluate and set pixel
			var value = noise.get_color_2d(dx * ratio, dy)
			image.set_pixel(x, y, value)

	image.unlock() # done

func _draw():
	texture = ImageTexture.new()
	texture.create_from_image(image, 0)
	draw_texture(texture, Vector2())
	