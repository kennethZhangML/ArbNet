#ifndef MARKETDATA_H
#define MARKETDATA_H

#include "InstrumentData.h"
#include "MarketObserver.h"
#include <map>
#include <memory>
#include <mutex>
#include <vector>

class MarketData {
private:
    std::map<std::string, std::shared_ptr<InstrumentData>> instruments;
    mutable std::mutex marketDataMutex;
    std::vector<std::weak_ptr<MarketObserver>> observers;

    MarketData() = default;

public:
    MarketData(const MarketData&) = delete;
    MarketData& operator=(const MarketData&) = delete;

    static MarketData& getInstance() {
        static MarketData instance;
        return instance;
    }

    void addInstrument(const std::string& instrumentID);
    std::shared_ptr<InstrumentData> getInstrumentData(const std::string& instrumentID);
    void addDataPoint(const std::string& instrumentID, const std::chrono::time_point<std::chrono::system_clock>& timestamp, double price, double volume);
    std::map<std::string, std::shared_ptr<InstrumentData>> getAllInstruments() const;

    void addObserver(const std::shared_ptr<MarketObserver>& observer);
    void removeObserver(const std::shared_ptr<MarketObserver>& observer);
    void notifyObservers(const std::string& instrumentID);
};

#endif // MARKETDATA_H
