#ifndef CSVLOADER_H
#define CSVLOADER_H

#include "MarketData.h"
#include <string>
#include <chrono>

class CSVLoader {
public:
    CSVLoader(const std::string& filePath, MarketData& marketData);

    void load();

private:
    std::string filePath;
    MarketData& marketData;

    std::chrono::time_point<std::chrono::system_clock> parseDate(const std::string& dateStr);
};

#endif // CSVLOADER_H
