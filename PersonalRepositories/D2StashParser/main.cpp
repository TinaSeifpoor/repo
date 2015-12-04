#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QTextStream>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QList<QFileInfo> files = QDir::current().entryInfoList(QStringList()<<"*.txt",QDir::Files);
    QFile out(QDir::current().filePath("mergedResults.txt"));
    out.open(QFile::WriteOnly);
    QTextStream stream(&out);
    foreach (QFileInfo fileInfo, files) {
        QFile file(fileInfo.filePath());
        file.open(QFile::ReadOnly);
        stream << file.readAll();
        file.close();
    }

    return 1;
}
