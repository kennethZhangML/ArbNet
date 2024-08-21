#ifndef BONDDATA_H
#define BONDDATA_H

#include "InstrumentData.h"

class BondData : public InstrumentData {
public:
    BondData(const std::string& id) : InstrumentData(id) {}
    double calculateCurrentYield(double annualCouponPayment) const;
    double calculateYTM(double faceValue, double annualCouponPayment, int yearsToMaturity) const;
    double calculateDuration(double yieldToMaturity, double couponRate, int periods) const;
};

#endif // BONDDATA_H