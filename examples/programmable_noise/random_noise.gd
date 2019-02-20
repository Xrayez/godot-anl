extends Node2D

var texture
var image

func _ready():
	var an = AccidentalNoise.new()

	an.set_var("random_turbulence", 0.0)
	
	var basis = an.simplex_basis(0)
	var trans = an.scale(an.simplex_basis(1), an.get_var("random_turbulence"))
	var translate = an.translate(basis, trans)
	
	an.function = an.scale(translate, an.constant(0.02))
	
	image = Image.new()
	image.create(256, 256, 0, Image.FORMAT_RGBA8)
	image.lock()
	
	for y in range(256):
		for x in range(256):
			if x % 64 == 0 and y % 64 == 0:
				# Specify noise parameters on the fly
				an.set_var("random_turbulence", rand_range(0, 4.0))
			var value = an.get_color_2d(x, y)
			image.set_pixel(x, y, value)
	
	image.unlock()
	
func _draw():
	texture = ImageTexture.new()
	texture.create_from_image(image, 0)
	draw_texture(texture, Vector2())
	