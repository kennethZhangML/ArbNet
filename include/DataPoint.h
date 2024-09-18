#ifndef DATAPOINT_H
#define DATAPOINT_H

#include <chrono>
#include <iostream>

struct DataPoint {
    std::chrono::time_point<std::chrono::system_clock> timestamp;
    double price;
    double volume;

    DataPoint(std::chrono::time_point<std::chrono::system_clock> ts, double p, double v)
        : timestamp(ts), price(p), volume(v) {}

    friend std::ostream& operator<<(std::ostream& os, const DataPoint& dp) {
        os << std::chrono::duration_cast<std::chrono::seconds>(dp.timestamp.time_since_epoch()).count() << " "
            << dp.price << " " << dp.volume;
    }

    friend std::istream& operator>>(std::istream& is, DataPoint& dp) {
        std::time_t time;
        is >> time >> dp.price >> dp.volume;
        dp.timestamp = std::chrono::system_clock::from_time_t(time);
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const DataPoint& dp) {
        if (dp.price != 0 && dp.volume != 0) {
            os << std::chrono::duration_cast<std::chrono::seconds>(dp.timestamp.time_since_epoch()).count() << " "
            << dp.price << " " << dp.volume;
        } else {
            os << "Invalid DataPoint";
        }
        return os;
    }

};

#endif // DATAPOINT_H

