#pragma once

#include <tbb/parallel_reduce.h>
#include <tbb/blocked_range.h>
#include <vector>
#include <sstream>
#include <string>

template <typename T>
class ParallelSum {
    const T* data_;
public:
    T obj_sum;

    ParallelSum(T* data) :
        data_(data), obj_sum(0) {}
    ParallelSum(ParallelSum& other, tbb::split) :
        data_(other.data_), obj_sum(0) {}

    void operator() (tbb::blocked_range<size_t> range) {
        T sum = obj_sum;
        for (size_t it = range.begin(); it != range.end(); it++)
            sum += data_[it];
        obj_sum = sum;
    }

    void join(ParallelSum& other) {
        obj_sum += other.obj_sum;
    }
};

template <typename T>
double parallelMean (std::vector<T>& data) {
    ParallelSum<T> ps(data.data());
    tbb::parallel_reduce(tbb::blocked_range<size_t>(0, data.size()), ps);
    return static_cast<double>(ps.obj_sum / data.size());
}