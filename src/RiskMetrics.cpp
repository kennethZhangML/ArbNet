#include "RiskMetrics.h"
#include <algorithm>
#include <numeric>
#include <cmath>

RiskMetrics::RiskMetrics(const std::vector<double>& portfolioReturns)
    : returns(portfolioReturns) {}

double RiskMetrics::calculateVaR(double confidenceLevel) {
    std::vector<double> sortedReturns = returns;
    std::sort(sortedReturns.begin(), sortedReturns.end());

    size_t index = static_cast<size_t>((1 - confidenceLevel) * sortedReturns.size());
    return -sortedReturns[index];
}

double RiskMetrics::calculateSharpeRatio(double riskFreeRate) {
    double meanReturn = std::accumulate(returns.begin(), returns.end(), 0.0) / returns.size();
    double excessReturn = meanReturn - riskFreeRate;

    double sumSquaredDiff = 0.0;
    for (double ret : returns) {
        sumSquaredDiff += std::pow(ret - meanReturn, 2);
    }
    double stdDev = std::sqrt(sumSquaredDiff / (returns.size() - 1));

    return excessReturn / stdDev;
}

double RiskMetrics::calculateMaxDrawdown() {
    double maxDrawdown = 0.0;
    double peak = returns[0];

    for (size_t i = 1; i < returns.size(); ++i) {
        if (returns[i] > peak) {
            peak = returns[i];
        }
        double drawdown = (peak - returns[i]) / peak;
        if (drawdown > maxDrawdown) {
            maxDrawdown = drawdown;
        }
    }

    return maxDrawdown;
}
