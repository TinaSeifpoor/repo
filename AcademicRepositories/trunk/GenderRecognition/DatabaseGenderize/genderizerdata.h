#ifndef GENDERIZERDATA_H
#define GENDERIZERDATA_H
#include <QVector>
#include <QString>

enum Gender
{
    Male,
    Female,
    Other
};

class GenderizerData
{
public:
    GenderizerData(QString filepath);
    Gender query(QString filename, Gender defaultValue=Other) const;
    Gender queryPath(QString filepath, Gender defaultValue=Other) const;
    QStringList query(Gender gender) const;
    int count(Gender gender) const;
    int count() const;

private:
    QVector<QString> __keys;
    QVector<Gender>  __genders;
};

#endif // GENDERIZERDATA_H
