#ifndef MARKETDATA_H
#define MARKETDATA_H

#include "InstrumentData.h"
#include <map>
#include <memory>
#include <mutex>

class MarketData {
private:
    std::map<std::string, std::shared_ptr<InstrumentData>> instruments;
    mutable std::mutex marketDataMutex;

public:
    void addInstrument(const std::string& instrumentID);
    std::shared_ptr<InstrumentData> getInstrumentData(const std::string& instrumentID);
    void addDataPoint(const std::string& instrumentID, const std::chrono::time_point<std::chrono::system_clock>& timestamp, double price, double volume);
    std::map<std::string, std::shared_ptr<InstrumentData>> getAllInstruments() const;
};

#endif // MARKETDATA_H
