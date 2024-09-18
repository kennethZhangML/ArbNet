#include "CSVLoader.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>

CSVLoader::CSVLoader(const std::string& filePath, MarketData& marketData)
    : filePath(filePath), marketData(marketData) {}

void CSVLoader::load() {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open the CSV file!" << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line);  

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string dateStr, openStr, highStr, lowStr, closeStr, adjCloseStr, volumeStr;

        std::getline(ss, dateStr, ',');
        std::getline(ss, openStr, ',');
        std::getline(ss, highStr, ',');
        std::getline(ss, lowStr, ',');
        std::getline(ss, closeStr, ',');
        std::getline(ss, adjCloseStr, ',');
        std::getline(ss, volumeStr, ',');

        auto timestamp = parseDate(dateStr);
        double price = std::stod(closeStr);  
        double volume = std::stod(volumeStr);

        marketData.addDataPoint("stock", timestamp, price, volume);
    }
}

std::chrono::time_point<std::chrono::system_clock> CSVLoader::parseDate(const std::string& dateStr) {
    std::tm tm = {};
    std::istringstream ss(dateStr);
    ss >> std::get_time(&tm, "%Y-%m-%d");
    return std::chrono::system_clock::from_time_t(std::mktime(&tm));
}
