#ifndef FOREST_H
#define FOREST_H
#include "common.h"
class Source;
class Features;
class Node;
struct ForestProperties;
struct ForestPrivate;
class QString;
class Forest
{
public:
    static Forest *train(const Source *source, const Features *features, const ForestProperties properties);
    QString text() const;
    bool writeForest(QString path) const;
    static Forest *fromText(QString text);
    static Forest *readForest(QString path);
    QList<QHash<QString, QHash<QString, ClassID> > > ret();
    TestResult test(const Source* source, const Features* features);
    ~Forest();

private:
    Forest();
    ForestPrivate *d;
};

#endif // FOREST_H
