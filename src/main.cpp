#include "MarketData.h"
#include "InstrumentDataFactory.h"
#include "MeanReversionStrategy.h"
#include "MomentumStrategy.h"
#include "BreakoutStrategy.h"
#include "RSIStrategy.h"

int main() {
    MarketData& marketData = MarketData::getInstance();

    auto instrument = InstrumentDataFactory::createInstrumentData("equity", "AAPL");
    marketData.addInstrument(instrument->getID());

    marketData.addDataPoint("AAPL", std::chrono::system_clock::now(), 150.0, 1000);
    marketData.addDataPoint("AAPL", std::chrono::system_clock::now(), 151.0, 2000);

    std::shared_ptr<TradingStrategy> meanReversionStrategy = std::make_shared<MeanReversionStrategy>();
    std::shared_ptr<TradingStrategy> momentumStrategy = std::make_shared<MomentumStrategy>();
    std::shared_ptr<TradingStrategy> breakoutStrategy = std::make_shared<BreakoutStrategy>();
    std::shared_ptr<TradingStrategy> rsiStrategy = std::make_shared<RSIStrategy>();

    meanReversionStrategy->execute(marketData.getInstrumentData("AAPL"));
    momentumStrategy->execute(marketData.getInstrumentData("AAPL"));
    breakoutStrategy->execute(marketData.getInstrumentData("AAPL"));
    rsiStrategy->execute(marketData.getInstrumentData("AAPL"));

    return 0;
}
