#ifndef MOMENTUMSTRATEGY_H
#define MOMENTUMSTRATEGY_H

#include "TradingStrategy.h"
#include <iostream>

class MomentumStrategy : public TradingStrategy {
public:
    void execute(const std::shared_ptr<InstrumentData>& data) override {
        double shortEMA = data->calculateExponentialMovingAverage(10); 
        double longEMA = data->calculateExponentialMovingAverage(50); 

        if (shortEMA > longEMA) {
            std::cout << "Momentum: Buy signal for " << data->getID() << std::endl;
        } else {
            std::cout << "Momentum: Sell signal for " << data->getID() << std::endl;
        }
    }
};

#endif // MOMENTUMSTRATEGY_H
