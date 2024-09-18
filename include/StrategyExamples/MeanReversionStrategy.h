#ifndef MEANREVERSIONSTRATEGY_H
#define MEANREVERSIONSTRATEGY_H

#include "TradingStrategy.h"
#include <iostream>

class MeanReversionStrategy : public TradingStrategy {
public:
    void execute(const std::shared_ptr<InstrumentData>& data) override {
        double avg = data->calculateMovingAverage(20); 
        double price = data->getDataPoints().back().price;

        if (price < avg) {
            std::cout << "Mean Reversion: Buy signal for " << data->getID() << std::endl;
        } else {
            std::cout << "Mean Reversion: Sell signal for " << data->getID() << std::endl;
        }
    }
};

#endif // MEANREVERSIONSTRATEGY_H
