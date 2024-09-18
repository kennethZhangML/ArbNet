#include <iostream>
#include <chrono>
#include <memory>
#include <vector> 
#include "EquityData.h"
#include "ForexData.h"
#include "MarketData.h"
#include "InstrumentDataFactory.h"

int main() {
    MarketData& marketData = MarketData::getInstance();

    std::cout << "Created MarketData Instance!" << std::endl;

    auto now = std::chrono::system_clock::now();
    auto earlier = now - std::chrono::hours(24);
    auto later = now + std::chrono::hours(24);

    std::cout << "Initialized now, earlier, later timestamps;" << std::endl;

    marketData.addInstrument("AAPL");
    std::cout << "Added AAPL Equity instrument to market data!" << std::endl;

    marketData.addDataPoint("AAPL", now, 150.0, 1000);
    marketData.addDataPoint("AAPL", earlier, 145.0, 1200);
    marketData.addDataPoint("AAPL", later, 155.0, 1100);

    std::shared_ptr<InstrumentData> equityInstrument = marketData.getInstrumentData("AAPL");
    double equityMovingAverage = equityInstrument->calculateMovingAverage(2);
    std::cout << "AAPL Simple Moving Average (2 periods): " << equityMovingAverage << std::endl;

    EquityData* aaplData = dynamic_cast<EquityData*>(equityInstrument.get());
    if (aaplData) {
        double dividendYield = aaplData->calculateDividendYield(3.0);
        std::cout << "AAPL Dividend Yield: " << dividendYield << std::endl;
    }

    marketData.addInstrument("EURUSD");
    std::cout << "Added EURUSD Forex instrument to market data!" << std::endl;

    marketData.addDataPoint("EURUSD", now, 1.2, 500000);
    marketData.addDataPoint("EURUSD", earlier, 1.19, 600000);
    marketData.addDataPoint("EURUSD", later, 1.21, 550000);

    std::shared_ptr<InstrumentData> forexInstrument = marketData.getInstrumentData("EURUSD");
    ForexData* eurusdData = dynamic_cast<ForexData*>(forexInstrument.get());
    if (eurusdData) {
        double pipValue = eurusdData->calculatePipValue(100000); 
        std::cout << "EUR/USD Pip Value for 100,000 lot size: " << pipValue << std::endl;

        double rsi = eurusdData->calculateRSI(2);
        std::cout << "EUR/USD RSI (2 periods): " << rsi << std::endl;
    }

    double equityEMA = equityInstrument->calculateExponentialMovingAverage(3);
    std::cout << "AAPL Exponential Moving Average (3 periods): " << equityEMA << std::endl;

    double forexEMA = forexInstrument->calculateExponentialMovingAverage(3);
    std::cout << "EUR/USD Exponential Moving Average (3 periods): " << forexEMA << std::endl;
    
    return 0;
}
