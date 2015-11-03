#include "genderizerdata.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>
const char* male = "male";
const char* female = "female";
GenderizerData::GenderizerData(QString filepath)
{
    QFile file(filepath);
    if (!file.open(QFile::ReadOnly)) {
        qCritical("GenderizerData:: Can't read file: %s", filepath.toLatin1().constData());
    } else {
        QTextStream stream(&file);
        while(!stream.atEnd()) {
            QString entryText = stream.readLine();
            QStringList entryTextList = entryText.split("\t", QString::SkipEmptyParts);
            if (entryTextList.count()!=2) {
                qWarning("File %s contains unrecognized entry: %s", filepath.toLatin1().constData(), entryText.toLatin1().constData());
                qWarning("Expected format: \"Filepath\\t\tGender\" in each line. Gender should be either male or female");
                continue;
            }
            QString filepath   = entryTextList.takeFirst();
            QString genderText = entryTextList.takeFirst();
            Gender gender;
            if (genderText.contains(female, Qt::CaseInsensitive)) {
                gender = Female;
            } else if (genderText.contains(male, Qt::CaseInsensitive)) {
                gender = Male;
            } else {
                qWarning("File %s contains unrecognized entry: %s", filepath.toLatin1().constData(), entryText.toLatin1().constData());
                qWarning("Expected format: \"Filepath\\t\tGender\" in each line. Gender should be either male or female");
                continue;
            }
            __keys << filepath;
            __genders << gender;
        }
    }
}

Gender GenderizerData::query(QString filename, Gender defaultValue) const
{
    int idx = __keys.indexOf(filename);
    if (idx==-1)
        return defaultValue;
    else
        return __genders.value(idx);
}

Gender GenderizerData::queryPath(QString filepath, Gender defaultValue) const
{
    for (int i=0; i<__keys.count(); ++i) {
        QString key = __keys.value(i);
        if (filepath.contains(key)) {
            return __genders.value(i);
        }
    }
    return defaultValue;
}

QStringList GenderizerData::query(Gender gender) const
{
    QStringList list;
    for (int i=0; i<__genders.count(); ++i) {
        if (__genders.value(i)==gender)
            list << __keys.value(i);
    }
    return list;
}

int GenderizerData::count(Gender gender) const
{
    return __genders.count(gender);
}

int GenderizerData::count() const
{
    return __genders.count();
}

