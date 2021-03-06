#include "initializer.h"
#include <QList>

Initializer::Initializer()
{
}

Source Initializer::getSource()
{
    QList<Sample> samples;
    int classCount = 4;
    int sampleCount = 30;
    for (int i=0; i<classCount; ++i) {
        for (int j=0; j<sampleCount; ++j) {
            Sample s;
            s.sampleClass = i;
            s.sampleSource = i;
            samples << s;
        }
    }
    return Source(samples);
}
