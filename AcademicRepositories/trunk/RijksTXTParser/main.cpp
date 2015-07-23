#include <QApplication>
#include <QDir>
#include <QTableWidget>
#include <QHeaderView>
#include "metadata.h"
#include "tablefilterdialog.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Q_ASSERT (argc>1);
    Metadata* meta = Metadata::generate(QString(argv[1]));

    QTableWidget widget;

    QStringList headers = meta->headers();
    int nRows = meta->count();

    widget.setRowCount(nRows);
    widget.setColumnCount(headers.count());

    for (int i=0; i<meta->count(); ++i)  {
        for (int j=0; j<headers.count(); ++j) {
            QTableWidgetItem *t=new QTableWidgetItem(meta->at(i,headers.value(j)));
            widget.setItem(i,j,t);
        }
    }
    widget.show();


    TableFilterDialog dialog(&widget, headers);
    dialog.show();

#if defined(WriteReport)||defined(WriteIndividualFiles)||defined(PrependDate)
    parseXMLFiles(); // outputs hasher
#endif
#ifdef WriteReport
    reportHasher();
#endif
    //    QDir baseDir = QDir::current();
    //    baseDir.cdUp();
    //    AddDataToImages adti(hasher, baseDir.filePath("jpg2"),baseDir.filePath("typeDate2"));
    //    adti.justDoIt(QStringList()<<"date"<<"type");
    return a.exec();
}
