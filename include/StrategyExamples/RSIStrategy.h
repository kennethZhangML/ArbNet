#ifndef RSISTRATEGY_H
#define RSISTRATEGY_H

#include "TradingStrategy.h"
#include <iostream>

class RSIStrategy : public TradingStrategy {
public:
    void execute(const std::shared_ptr<InstrumentData>& data) override {
        double rsi = calculateRSI(data, 14); 

        if (rsi < 30) {
            std::cout << "RSI: Buy signal for " << data->getID() << std::endl;
        } else if (rsi > 70) {
            std::cout << "RSI: Sell signal for " << data->getID() << std::endl;
        }
    }

private:
    double calculateRSI(const std::shared_ptr<InstrumentData>& data, int period) const {
        auto dataPoints = data->getDataPoints();
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
};

#endif // RSISTRATEGY_H
