#ifndef MARKETOBSERVER_H
#define MARKETOBSERVER_H

#include <string>

class MarketObserver {
public:
    virtual void update(const std::string& instrumentID) = 0;
    virtual ~MarketObserver() = default;
};

#endif // MARKETOBSERVER_H
