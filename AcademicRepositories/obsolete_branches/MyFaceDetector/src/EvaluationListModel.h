#ifndef EVALUATIONLISTMODEL_H
#define EVALUATIONLISTMODEL_H

#include <QAbstractItemModel>
#include <MyBBEvaluator.h>
#include <QModelIndex>

class EvaluationListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit EvaluationListModel(QObject *parent = 0);
    bool setData(const QModelIndex &index, const QVariant &value, int role);
private:
    QVector<EvaluationModel> allData;
signals:
    
public slots:
    
};

#endif // EVALUATIONLISTMODEL_H
