#include "EquityData.h"

double EquityData::calculateDividendYield(double dividendPerShare) const {
    std::lock_guard<std::mutex> lock(dataMutex);
    if (dataPoints.empty()) return 0.0;

    double currentPrice = dataPoints.back().price;
    return dividendPerShare / currentPrice;
}

double EquityData::calculatePERatio(double earningsPerShare) const {
    std::lock_guard<std::mutex> lock(dataMutex);
    if (dataPoints.empty()) return 0.0;

    double currentPrice = dataPoints.back().price;
    return currentPrice / earningsPerShare;
}

double EquityData::calculateSimpleMovingAverage(int period) const {
    return calculateMovingAverage(period);
}
