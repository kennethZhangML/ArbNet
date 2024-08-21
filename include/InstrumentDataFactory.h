#ifndef INSTRUMENTDATAFACTORY_H
#define INSTRUMENTDATAFACTORY_H

#include "InstrumentData.h"
#include <memory>
#include <string>

class InstrumentDataFactory {
public:
    static std::shared_ptr<InstrumentData> createInstrumentData(const std::string& instrumentType, const std::string& instrumentID) {
        // Here we can extend the logic based on the instrument type
        if (instrumentType == "equity") {
            return std::make_shared<InstrumentData>(instrumentID);
        }
        // Additional types can be handled here, e.g., "forex", "bond", etc.
        return nullptr;
    }
};

#endif // INSTRUMENTDATAFACTORY_H
