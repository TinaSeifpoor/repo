#ifndef LISTRANDOMSORTER_H
#define LISTRANDOMSORTER_H
#include <QList>
#include "../../RDFModule/src/vectorindexsorter.h"
template <typename T>
QList<T> randomlySortList(double ratio, const QList<T> list) {
    unsigned int listSize = list.size();
    std::vector<unsigned int> randomValuesToSort;
    randomValuesToSort.resize(listSize);
    std::generate(randomValuesToSort.begin(), randomValuesToSort.end(), [&]{ return rand(); });
    std::vector<unsigned int> idxSort = sort_indexes(randomValuesToSort);
    std::vector<unsigned int>::iterator idxSortIt = idxSort.begin();
    unsigned int samplesToTake = ratio*listSize;
    std::vector<unsigned int>::iterator idxSortEnd = idxSort.begin()+samplesToTake;

    QList<T> baggedList;
    for(;idxSortIt!=idxSortEnd;++idxSortIt) {
        baggedList.append(list.at(*(idxSortIt)));
    }
    return baggedList;

}
#endif // LISTRANDOMSORTER_H
