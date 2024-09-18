#ifndef RISKMETRICS_H
#define RISKMETRICS_H

#include <vector>
#include <string>

class RiskMetrics {
public:
    RiskMetrics(const std::vector<double>& portfolioReturns);
    double calculateVaR(double confidenceLevel);
    double calculateSharpeRatio(double riskFreeRate);
    double calculateMaxDrawdown();

private:
    std::vector<double> returns;
};

#endif // RISK_METRICS_H