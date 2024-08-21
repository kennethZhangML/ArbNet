#ifndef EQUITYDATA_H
#define EQUITYDATA_H

#include "InstrumentData.h"

class EquityData : public InstrumentData {
public:
    EquityData(const std::string& id) : InstrumentData(id) {}

    double calculateDividendYield(double dividendPerShare) const;
    double calculatePERatio(double earningsPerShare) const;
    double calculateSimpleMovingAverage(int period) const;
};

#endif // EQUITYDATA_H
