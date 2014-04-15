#include "node.h"

Node::Node()
{
}

void Node::train(Source *samples, TreeProperties properties, Source *samplesTrue, Source *samplesFalse)
{
    Source* samplesForNode = samples->baggedSamples(properties.baggingFactorSamples, properties.baggingFactorFeatures);

}
