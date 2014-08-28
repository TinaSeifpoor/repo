#ifndef LISTRANDOMSORTER_H
#define LISTRANDOMSORTER_H
#include <QList>
#include "vectorindexsorter.h"
template <typename T>
QList<T> randomlySortList(double ratio, const QList<T> list) {
    int listSize = list.size();
    std::vector<int> randomValuesToSort;
    randomValuesToSort.resize(listSize);
    std::generate(randomValuesToSort.begin(), randomValuesToSort.end(), [&]{ return rand(); });
    std::vector<int> idxSort = sort_indexes(randomValuesToSort);
    std::vector<int>::iterator idxSortIt = idxSort.begin();
    int samplesToTake = ratio*listSize;
    std::vector<int>::iterator idxSortEnd = idxSort.begin()+samplesToTake;

    QList<T> baggedList;
    for(;idxSortIt!=idxSortEnd;++idxSortIt) {
        baggedList.append(list.at(*(idxSortIt)));
    }
    return baggedList;

}
#endif // LISTRANDOMSORTER_H
