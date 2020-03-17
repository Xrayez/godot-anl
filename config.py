
def can_build(env, platform):
    return True


def configure(env):
    from SCons.Script import Variables, BoolVariable, Help

    opts = Variables()
    opts.Add(BoolVariable("anl_use_long_period",
                          "Use a long-period hash for noise (>256) to avoid having repeated patterns "
                          "in exchange of a slight decrease in performance.", False))

    opts.Add(BoolVariable('anl_use_expressions_camelcase',
                          "Use 'camelCase' by default over the 'snake_case' for noise expressions.", False))
    opts.Update(env)
    Help(opts.GenerateHelpText(env))


def get_doc_classes():
    return [
        "AccidentalNoise",
        "VisualAccidentalNoise",
        "VisualAccidentalNoiseNode",
        "VisualAccidentalNoiseNodeComponent",
        "VisualAccidentalNoiseNodeInput",
        "VisualAccidentalNoiseNodeOutput",
        "VisualAccidentalNoiseNodeSeed",
        "VisualAccidentalNoiseNodeSeeder",
        "VisualAccidentalNoiseNodeRandomize",
        "VisualAccidentalNoiseNodeScalar",
        "VisualAccidentalNoiseNodeScalarOp",
        "VisualAccidentalNoiseNodeScalarFunc",
        "VisualAccidentalNoiseNodeTranslate",
        "VisualAccidentalNoiseNodeScale",
        "VisualAccidentalNoiseNodeRotate",
        "VisualAccidentalNoiseNodeValueBasis",
        "VisualAccidentalNoiseNodeGradientBasis",
        "VisualAccidentalNoiseNodeSimplexBasis",
        "VisualAccidentalNoiseNodeCellularBasis",
        "VisualAccidentalNoiseNodeMix",
        "VisualAccidentalNoiseNodeSelect",
        "VisualAccidentalNoiseNodeClamp",
        "VisualAccidentalNoiseNodeGradient",
        "VisualAccidentalNoiseNodeDerivative",
        "VisualAccidentalNoiseNodeHex",
        "VisualAccidentalNoiseNodeColor",
        "VisualAccidentalNoiseNodeColorCombine",
        "VisualAccidentalNoiseNodeFractal",
        "VisualAccidentalNoiseNodeFractalVariant",
        "VisualAccidentalNoiseNodeFractalLayer",
        "VisualAccidentalNoiseNodeStep",
        "VisualAccidentalNoiseNodeTiers",
        "VisualAccidentalNoiseNodeRadial",
        "VisualAccidentalNoiseNodeCurveSection",
        "VisualAccidentalNoiseNodeScaleOffset",
        "VisualAccidentalNoiseNodeSetVar",
        "VisualAccidentalNoiseNodeGetVar",
        "VisualAccidentalNoiseNodeReroute",
        "VisualAccidentalNoiseNodeExpression",
    ]


def get_doc_path():
    return "doc_classes"
