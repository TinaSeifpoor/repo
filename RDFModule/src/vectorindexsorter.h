#ifndef VECTORINDEXSORTER_H
#define VECTORINDEXSORTER_H
#include <vector>
#include <algorithm>
#include <cmath>
template <typename T>
std::vector<unsigned int> sort_indexes(const std::vector<T> &v) {

  // initialize original index locations
  std::vector<unsigned int> idx(v.size());
  for (unsigned int i = 0; i != idx.size(); ++i) idx[i] = i;

  // sort indexes based on comparing values in v
  std::sort(idx.begin(), idx.end(),
       [&v](unsigned int i1, unsigned int i2) {return v[i1] < v[i2];});

  return idx;
}


#endif // VECTORINDEXSORTER_H
