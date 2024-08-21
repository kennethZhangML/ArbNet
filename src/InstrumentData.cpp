#include "InstrumentData.h"
#include <numeric>
#include <cmath>
#include <algorithm>
#include <mutex>

InstrumentData::InstrumentData(const std::string& id) : instrumentID(id) {}

void InstrumentData::addDataPoint(const std::chrono::time_point<std::chrono::system_clock>& timestamp, double price, double volume) {
    std::lock_guard<std::mutex> lock(dataMutex);
    dataPoints.emplace_back(timestamp, price, volume);
}

std::vector<DataPoint> InstrumentData::getDataPoints() const {
    std::lock_guard<std::mutex> lock(dataMutex);
    return dataPoints;
}

double InstrumentData::calculateMovingAverage(int period) const {
    std::lock_guard<std::mutex> lock(dataMutex);
    if (dataPoints.size() < period) return 0.0;

    auto start = dataPoints.end() - period;
    double sum = std::accumulate(start, dataPoints.end(), 0.0, [](double acc, const DataPoint& dp) {
        return acc + dp.price;
    });

    return sum / period;
}

double InstrumentData::calculateStandardDeviation(int period) const {
    std::lock_guard<std::mutex> lock(dataMutex);
    if (dataPoints.size() < period) return 0.0;

    double mean = calculateMovingAverage(period);
    auto start = dataPoints.end() - period;
    double variance = std::accumulate(start, dataPoints.end(), 0.0, [mean](double acc, const DataPoint& dp) {
        return acc + std::pow(dp.price - mean, 2);
    });

    return std::sqrt(variance / period);
}

double InstrumentData::calculateExponentialMovingAverage(int period, double smoothingFactor) const {
    std::lock_guard<std::mutex> lock(dataMutex);
    if (dataPoints.size() < period) return 0.0;

    double ema = dataPoints[dataPoints.size() - period].price;
    double multiplier = smoothingFactor / (1.0 + period);

    for (size_t i = dataPoints.size() - period + 1; i < dataPoints.size(); ++i) {
        ema = ((dataPoints[i].price - ema) * multiplier) + ema;
    }

    return ema;
}

std::vector<DataPoint> InstrumentData::getDataPointsInRange(const std::chrono::time_point<std::chrono::system_clock>& start, 
                                                            const std::chrono::time_point<std::chrono::system_clock>& end) const {
    std::lock_guard<std::mutex> lock(dataMutex);
    std::vector<DataPoint> rangeData;

    std::copy_if(dataPoints.begin(), dataPoints.end(), std::back_inserter(rangeData),
                 [&start, &end](const DataPoint& dp) {
                     return dp.timestamp >= start && dp.timestamp <= end;
                 });

    return rangeData;
}

void InstrumentData::normalizePrices() {
    std::lock_guard<std::mutex> lock(dataMutex);
    if (dataPoints.empty()) return;

    double minPrice = std::min_element(dataPoints.begin(), dataPoints.end(), 
                                       [](const DataPoint& a, const DataPoint& b) {
                                           return a.price < b.price;
                                       })->price;
    double maxPrice = std::max_element(dataPoints.begin(), dataPoints.end(), 
                                       [](const DataPoint& a, const DataPoint& b) {
                                           return a.price > b.price;
                                       })->price;

    for (auto& dp : dataPoints) {
        dp.price = (dp.price - minPrice) / (maxPrice - minPrice);
    }
}

void InstrumentData::logTransformPrices() {
    std::lock_guard<std::mutex> lock(dataMutex);
    for (auto& dp : dataPoints) {
        dp.price = std::log(dp.price);
    }
}

const std::string& InstrumentData::getID() const {
    return instrumentID;
}
