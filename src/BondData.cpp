#include "BondData.h"
#include <cmath>

double BondData::calculateCurrentYield(double annualCouponPayment) const {
    std::lock_guard<std::mutex> lock(dataMutex);
    if (dataPoints.empty()) return 0.0;

    double currentPrice = dataPoints.back().price;
    return annualCouponPayment / currentPrice;
}

double BondData::calculateYTM(double faceValue, double annualCouponPayment, int yearsToMaturity) const {
    std::lock_guard<std::mutex> lock(dataMutex);
    if (dataPoints.empty()) return 0.0;

    double currentPrice = dataPoints.back().price;
    double ytm = (annualCouponPayment + (faceValue - currentPrice) / yearsToMaturity) / ((faceValue + currentPrice) / 2);
    return ytm;
}

double BondData::calculateDuration(double yieldToMaturity, double couponRate, int periods) const {
    std::lock_guard<std::mutex> lock(dataMutex);
    if (dataPoints.empty()) return 0.0;

    double duration = 0.0;
    for (int t = 1; t <= periods; ++t) {
        double cashFlow = (t == periods) ? 1 + couponRate : couponRate;
        duration += t * cashFlow / std::pow(1 + yieldToMaturity, t);
    }
    return duration / (1 + yieldToMaturity);
}
