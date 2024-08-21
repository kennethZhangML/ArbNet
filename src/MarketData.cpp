#include "MarketData.h"
#include <iostream>

void MarketData::addInstrument(const std::string& instrumentID) {
    std::lock_guard<std::mutex> lock(marketDataMutex);
    if (instruments.find(instrumentID) == instruments.end()) {
        instruments[instrumentID] = std::make_shared<InstrumentData>(instrumentID);
    }
}

std::shared_ptr<InstrumentData> MarketData::getInstrumentData(const std::string& instrumentID) {
    std::lock_guard<std::mutex> lock(marketDataMutex);
    auto it = instruments.find(instrumentID);
    if (it != instruments.end()) {
        return it->second;
    }
    return nullptr;
}

void MarketData::addDataPoint(const std::string& instrumentID, const std::chrono::time_point<std::chrono::system_clock>& timestamp, double price, double volume) {
    auto instrumentData = getInstrumentData(instrumentID);
    if (instrumentData) {
        instrumentData->addDataPoint(timestamp, price, volume);
    } else {
        std::cerr << "Instrument " << instrumentID << " not found!" << std::endl;
    }
}

std::map<std::string, std::shared_ptr<InstrumentData>> MarketData::getAllInstruments() const {
    std::lock_guard<std::mutex> lock(marketDataMutex);
    return instruments;
}
