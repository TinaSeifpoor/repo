#ifndef INITIALIZER_H
#define INITIALIZER_H

#include "source.h"
class Initializer
{
public:
    Initializer();
    Source getSource();
private:
    double getRand() const;
};

#endif // INITIALIZER_H
