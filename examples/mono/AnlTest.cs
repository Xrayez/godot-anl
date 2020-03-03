using Godot;
using System;

public class AnlTest : Godot.Node2D
{
	public override void _Ready()
	{
		AccidentalNoise an = new Godot.AccidentalNoise();
		AccidentalNoise.InterpolationTypes interp = AccidentalNoise.InterpolationTypes.Linear;
		int seed = 37;
		an.Function = an.GradientBasis(an.Constant((double)interp), an.Constant(seed));
		an.Function = an.Scale(an.Function, an.Constant(5.0));
		an.Mode = AccidentalNoise.MappingModes.Xy;
		ImageTexture noise = an.GetTexture(128, 128) as ImageTexture;
		GetNode<TextureRect>("Noise").Texture = noise;
	}
}
