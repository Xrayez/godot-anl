#include "register_types.h"

#include "noise.h"
#include "plugins/visual_noise_editor_plugin.h"
#include "visual_noise.h"
#include "visual_noise_nodes.h"

Ref<VisualAccidentalNoiseResourceLoader> resource_loader_vacn;
Ref<VisualAccidentalNoiseResourceSaver> resource_saver_vacn;

void register_anl_types() {

	ClassDB::register_class<AccidentalNoise>();
	ClassDB::register_class<VisualAccidentalNoise>();

	////// Component
	ClassDB::register_class<VisualAccidentalNoiseNodeComponent>();

	////// Nodes

	// Input/Output
	ClassDB::register_class<VisualAccidentalNoiseNodeInput>();
	ClassDB::register_virtual_class<VisualAccidentalNoiseNodeOutput>();

	// Seed
	ClassDB::register_class<VisualAccidentalNoiseNodeSeed>();
	ClassDB::register_class<VisualAccidentalNoiseNodeSeeder>();
	ClassDB::register_class<VisualAccidentalNoiseNodeRandomize>();

	// Scalar
	ClassDB::register_class<VisualAccidentalNoiseNodeScalar>();
	ClassDB::register_class<VisualAccidentalNoiseNodeScalarOp>();
	ClassDB::register_class<VisualAccidentalNoiseNodeScalarFunc>();

	// Transform
	ClassDB::register_class<VisualAccidentalNoiseNodeTranslate>();
	ClassDB::register_class<VisualAccidentalNoiseNodeScale>();
	ClassDB::register_class<VisualAccidentalNoiseNodeRotate>();

	// Basis
	ClassDB::register_class<VisualAccidentalNoiseNodeValueBasis>();
	ClassDB::register_class<VisualAccidentalNoiseNodeGradientBasis>();
	ClassDB::register_class<VisualAccidentalNoiseNodeSimplexBasis>();
	ClassDB::register_class<VisualAccidentalNoiseNodeCellularBasis>();

	// Filter
	ClassDB::register_class<VisualAccidentalNoiseNodeMix>();
	ClassDB::register_class<VisualAccidentalNoiseNodeSelect>();
	ClassDB::register_class<VisualAccidentalNoiseNodeClamp>();

	// Axis
	ClassDB::register_class<VisualAccidentalNoiseNodeGradient>();
	ClassDB::register_class<VisualAccidentalNoiseNodeDerivative>();

	// Patterns
	ClassDB::register_class<VisualAccidentalNoiseNodeHex>();

	// Color
	ClassDB::register_class<VisualAccidentalNoiseNodeColor>();
	ClassDB::register_class<VisualAccidentalNoiseNodeColorCombine>();

	// Fractal
	ClassDB::register_class<VisualAccidentalNoiseNodeFractal>();
	ClassDB::register_class<VisualAccidentalNoiseNodeFractalVariant>();
	ClassDB::register_class<VisualAccidentalNoiseNodeFractalLayer>();

	// Other
	ClassDB::register_class<VisualAccidentalNoiseNodeStep>();
	ClassDB::register_class<VisualAccidentalNoiseNodeTiers>();
	ClassDB::register_class<VisualAccidentalNoiseNodeRadial>();
	ClassDB::register_class<VisualAccidentalNoiseNodeCurveSection>();
	ClassDB::register_class<VisualAccidentalNoiseNodeScaleOffset>();

	// Misc
	ClassDB::register_class<VisualAccidentalNoiseNodeSetVar>();
	ClassDB::register_class<VisualAccidentalNoiseNodeGetVar>();
	ClassDB::register_class<VisualAccidentalNoiseNodeExpression>();

	// Register loaders/savers
	resource_loader_vacn.instance();
	ResourceLoader::add_resource_format_loader(resource_loader_vacn);

	resource_saver_vacn.instance();
	ResourceSaver::add_resource_format_saver(resource_saver_vacn);

#ifdef TOOLS_ENABLED
	EditorPlugins::add_by_type<VisualAccidentalNoiseEditorPlugin>();
#endif
}

void unregister_anl_types() {

	ResourceLoader::remove_resource_format_loader(resource_loader_vacn);
	resource_loader_vacn.unref();

	ResourceSaver::remove_resource_format_saver(resource_saver_vacn);
	resource_saver_vacn.unref();
}
