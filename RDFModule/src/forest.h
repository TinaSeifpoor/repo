#ifndef FOREST_H
#define FOREST_H
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
    ~Forest();

private:
    Forest();
    ForestPrivate *d;
};

#endif // FOREST_H
