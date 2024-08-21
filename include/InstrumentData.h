#ifndef INSTRUMENTDATA_H
#define INSTRUMENTDATA_H

#include "DataPoint.h"
#include <string>
#include <vector>
#include <mutex>

class InstrumentData {
private:
    std::string instrumentID;
    std::vector<DataPoint> dataPoints;
    mutable std::mutex dataMutex;

public:
    InstrumentData(const std::string& id);

    void addDataPoint(const std::chrono::time_point<std::chrono::system_clock>& timestamp, double price, double volume);
    std::vector<DataPoint> getDataPoints() const;

    double calculateMovingAverage(int period) const;
    double calculateStandardDeviation(int period) const;
    double calculateExponentialMovingAverage(int period, double smoothingFactor = 2.0) const;

    std::vector<DataPoint> getDataPointsInRange(const std::chrono::time_point<std::chrono::system_clock>& start, 
                                                const std::chrono::time_point<std::chrono::system_clock>& end) const;

    void normalizePrices();
    void logTransformPrices();

    const std::string& getID() const; 
};

#endif // INSTRUMENTDATA_H
