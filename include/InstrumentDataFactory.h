#ifndef INSTRUMENTDATAFACTORY_H
#define INSTRUMENTDATAFACTORY_H

#include "EquityData.h"
#include "ForexData.h"
#include "BondData.h"
#include <memory>
#include <string>

class InstrumentDataFactory {
public:
    static std::shared_ptr<InstrumentData> createInstrumentData(const std::string& instrumentType, const std::string& instrumentID) {
        if (instrumentType == "equity") {
            return std::make_shared<EquityData>(instrumentID);
        } else if (instrumentType == "forex") {
            return std::make_shared<ForexData>(instrumentID);
        } else if (instrumentType == "bond") {
            return std::make_shared<BondData>(instrumentID);
        }
        return nullptr;
    }
};

#endif // INSTRUMENTDATAFACTORY_H
