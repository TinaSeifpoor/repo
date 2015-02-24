#ifndef VECTORINDEXSORTER_H
#define VECTORINDEXSORTER_H
#include <vector>
#include <algorithm>
#include <cmath>
template <typename T>
std::vector<int> sort_indexes(const std::vector<T> &v) {

  // initialize original index locations
  std::vector<int> idx(v.size());
  for (int i = 0; i != idx.size(); ++i) idx[i] = i;

  // sort indexes based on comparing values in v
  std::sort(idx.begin(), idx.end(),
       [&v](int i1, int i2) {return v[i1] < v[i2];});

  return idx;
}


#endif // VECTORINDEXSORTER_H
