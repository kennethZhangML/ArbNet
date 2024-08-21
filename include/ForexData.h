#ifndef FOREXDATA_H
#define FOREXDATA_H

#include "InstrumentData.h"

class ForexData : public InstrumentData { 
public:
    ForexData(const std::string& id) : InstrumentData(id) {}
    double calculatePipValue(double lotsize) const;
    double calculateExchangeRateMovingAverage(int period) const;
    double calculateRSI(int period) const;
};

#endif // FOREXDATA_H