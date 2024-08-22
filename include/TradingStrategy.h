#ifndef TRADINGSTRATEGY_H
#define TRADINGSTRATEGY_H

#include "InstrumentData.h"

class TradingStrategy {
public:
    virtual void execute(const std::shared_ptr<InstrumentData>& data) = 0;
    virtual ~TradingStrategy() = default;
};

#endif // TRADINGSTRATEGY_H
