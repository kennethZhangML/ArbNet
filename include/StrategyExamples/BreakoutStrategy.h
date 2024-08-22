#ifndef BREAKOUTSTRATEGY_H
#define BREAKOUTSTRATEGY_H

#include "TradingStrategy.h"
#include <iostream>

class BreakoutStrategy : public TradingStrategy {
public:
    void execute(const std::shared_ptr<InstrumentData>& data) override {
        double recentHigh = getHighestHigh(data, 20); 
        double recentLow = getLowestLow(data, 20);    
        double price = data->getDataPoints().back().price;

        if (price > recentHigh) {
            std::cout << "Breakout: Buy signal for " << data->getID() << std::endl;
        } else if (price < recentLow) {
            std::cout << "Breakout: Sell signal for " << data->getID() << std::endl;
        }
    }

private:
    double getHighestHigh(const std::shared_ptr<InstrumentData>& data, int period) const {
        auto dataPoints = data->getDataPoints();
        auto start = dataPoints.size() > period ? dataPoints.end() - period : dataPoints.begin();
        double highestHigh = (*start).price;

        for (auto it = start; it != dataPoints.end(); ++it) {
            if (it->price > highestHigh) {
                highestHigh = it->price;
            }
        }

        return highestHigh;
    }

    double getLowestLow(const std::shared_ptr<InstrumentData>& data, int period) const {
        auto dataPoints = data->getDataPoints();
        auto start = dataPoints.size() > period ? dataPoints.end() - period : dataPoints.begin();
        double lowestLow = (*start).price;

        for (auto it = start; it != dataPoints.end(); ++it) {
            if (it->price < lowestLow) {
                lowestLow = it->price;
            }
        }

        return lowestLow;
    }
};

#endif // BREAKOUTSTRATEGY_H
