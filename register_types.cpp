#include "register_types.h"

#include "anl_noise.h"
#include "visual_anl_noise.h"
#include "visual_anl_noise_nodes.h"
#include "plugins/visual_anl_noise_editor_plugin.h"

void register_anl_types() {

    ClassDB::register_class<AnlNoise>();
    ClassDB::register_class<VisualAnlNoise>();

    ////// Component
    ClassDB::register_class<VisualAnlNoiseNodeComponent>();

    ////// Nodes
    ClassDB::register_class<VisualAnlNoiseNodeInput>();

    ClassDB::register_class<VisualAnlNoiseNodeScalar>();
    ClassDB::register_class<VisualAnlNoiseNodeScalarOp>();
    ClassDB::register_class<VisualAnlNoiseNodeScalarFunc>();

    // Transform
    ClassDB::register_class<VisualAnlNoiseNodeTranslate>();
    ClassDB::register_class<VisualAnlNoiseNodeScale>();
    ClassDB::register_class<VisualAnlNoiseNodeRotate>();

    // Basis
    ClassDB::register_class<VisualAnlNoiseNodeValueBasis>();
    ClassDB::register_class<VisualAnlNoiseNodeGradientBasis>();
    ClassDB::register_class<VisualAnlNoiseNodeSimplexBasis>();
    ClassDB::register_class<VisualAnlNoiseNodeCellularBasis>();

    // Filter
    ClassDB::register_class<VisualAnlNoiseNodeMix>();
    ClassDB::register_class<VisualAnlNoiseNodeSelect>();
    ClassDB::register_class<VisualAnlNoiseNodeClamp>();

    // Misc
    ClassDB::register_class<VisualAnlNoiseNodeExpression>();

#ifdef TOOLS_ENABLED
	EditorPlugins::add_by_type<VisualAnlNoiseEditorPlugin>();
#endif
}

void unregister_anl_types() {

    // nothing to do here
}
