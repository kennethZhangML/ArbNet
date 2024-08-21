#include "ForexData.h"

#include <algorithm>

double ForexData::calculatePipValue(double lotSize) const {
    std::lock_guard<std::mutex> lock(dataMutex);
    if (dataPoints.empty()) return 0.0;

    double currentPrice = dataPoints.back().price;
    return lotSize * 0.0001 / currentPrice;
}

double ForexData::calculateExchangeRateMovingAverage(int period) const {
    return calculateMovingAverage(period);
}

double ForexData::calculateRSI(int period) const {
    std::lock_guard<std::mutex> lock(dataMutex);

    if (dataPoints.size() < period + 1) return 0.0;
    double gain = 0.0, loss = 0.0;

    for (size_t i = dataPoints.size() - period; i < dataPoints.size(); ++i) {
        double change = dataPoints[i].price - dataPoints[i - 1].price;
        if (change > 0) {
            gain += change;
        } else {
            loss -= change;
        }
    }

    if (loss == 0) return 100.0;
    double rs = gain / loss;
    return 100.0 - (100.0 / (1.0 + rs));
}