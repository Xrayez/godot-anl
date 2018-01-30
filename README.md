# Godot Accidental Noise Library module

This is a wrapper for the new version of
[Accidental Noise Library](https://github.com/JTippetts/accidental-noise-library)
originally written by
[Joshua Tippetts](https://sourceforge.net/u/tippettsj/profile/), modified
to be properly compiled for [Godot 3.0+](https://github.com/godotengine/godot)
and be used freely in GDScript.

## Installation

```bash
# 1. Change directory to `modules` subfolder of Godot repository
cd godot/modules/
# 2. Clone the module under directory named `anl`
git clone https://github.com/Xrayez/godot-anl.git anl
cd ..
# 3. Compile the engine manually, for instance:
scons platform=windows target=release_debug bits=64
```

## Overview

The AnlNoise class encapsulates the two main classes required for noise
generation: CKernel, CNoiseExecutor

The kernel holds any amount of noise functions together creating compound noise
function. The noise executor then evaluates the function chain at any point of
the "pipeline"

The library is full of features compared to other noise generation libraries with
a drawback of poorer performance.

## Usage example

```gdscript
var n = AnlNoise.new()

var gradient = n.y()

var fractal = n.fbm(AnlNoise.BASIS_GRADIENT, AnlNoise.INTERP_QUINTIC, [4, 3, randi()])
var scale_offset = n.scale_offset(fractal, 0.5, 0)

var perturb = n.translate(gradient, scale_offset)

var select = n.select(
	n.zero(), n.one(),
	perturb, n.constant(0.5), n.zero()
)

var image = Image.new()
image.lock()

# Draw evaluated function
for y in range(HEIGHT):
	for x in range(WIDTH):
		var value = n.get_color_2d(x, y, n.get_last_index())
		image.set_pixel(x, y, value)

image.unlock()
```
You can also map the noise to an image with dedicated method instead:
```gdscript
image = n.map_to_image(size, noise.get_last_index())
```
... or even tiled texture!
```gdscript
texture = n.map_to_texture(size, noise.get_last_index(), AnlNoise.SEAMLESS_XY)
```

### Result
![Simple terrain](examples/images/terrain_binary.png)

You can also use the expression builder to simplify the process of chaining
functions together to one-liners, something like this:

```gdscript
var n = AnlNoise.new()

var expression = "translate(select(0, 1, (x + y), 0.5, 0), 10)"
var function = n.evaluate(expression)
var value = n.color_2d(x, y, function)
```

But please note that the expression builder feature is a work in progress as
stated by original author. Some functions work, some don't and will hang the
engine in the endless loop...

Here's some more examples of image/texture generation:

![Water or Smoke?](examples/images/water_smoke.png)
![Stones with moss?](examples/images/stone_moss.png)
![Lapis lazuli?](examples/images/stone_lapis.png)

## Legal considerations

The original Accidental Noise Library uses Simplex noise for some of the noise
generation methods, implementation of which might be patented for uses in 3D and
higher for textured image synthesis. I'm not a lawyer, but I think using 2D
implementation of Simplex noise should be safe. I need to find that out someday.
I might look into integrating OpenSimplex noise instead, if this is the case.
