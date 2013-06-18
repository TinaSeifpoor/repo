#include "EvaluationListModel.h"

EvaluationListModel::EvaluationListModel(QObject *parent) :
    QAbstractListModel(parent)
{
}

bool EvaluationListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.row() > this->allData.count())
    {
        return false;
    }
//    allData[index.row()] = value.value< EvaluationModel >();
    return true;
}
