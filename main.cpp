#include <iostream>
#include <random>
#include <chrono>
#include <numeric>
#include <vector>

#include "parallel_mean.hpp"

std::vector<double> generateData(size_t size = 1'000'000'000) {
    std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<double> dist(0.0, 100.0);

    std::vector<double> data(size);
    for (auto& n : data) {
        n = dist(gen);
    }
    return data;
}

template <typename T>
double linearMean(const std::vector<T>& data) {
    return std::accumulate(data.begin(), data.end(), double{}) / data.size();
}

int main() {
    using Clock = std::chrono::steady_clock;
    std::cout << "Generating data..\n\n";
    std::vector<double> data(generateData());

    std::cout << "parallelMean started..\n";
    auto parallelStart = Clock::now();
    std::cout << "  result: " << parallelMean(data) << '\n';
    auto parallelFinish = Clock::now();
    std::chrono::duration<double, std::milli> parallelElapsed = parallelFinish - parallelStart;
    std::cout << "  time:   " << parallelElapsed.count() << " ms\n\n";

    std::cout << "linearMean started..\n";
    auto linearStart = Clock::now();
    std::cout << "  result: " << linearMean(data) << '\n';
    auto linearFinish = Clock::now();
    std::chrono::duration<double, std::milli> linearElapsed = linearFinish - linearStart;
    std::cout << "  time:   " << linearElapsed.count() << " ms\n\n";

    std::cout << "parallelMean is " << static_cast<unsigned int>(linearElapsed.count() / parallelElapsed.count()) << " times faster\n";
}