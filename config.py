
def can_build(env, platform):
    return True

def configure(env):
    pass

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
