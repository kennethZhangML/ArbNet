#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>

struct MarketDataLevel {
    int32_t Quantity;
    double Price;
};

struct TradeEntity {
    int32_t Quantity;
    double RiskPerUnit;
};

std::vector<MarketDataLevel> ParseMarketData(const std::string& line) {
    std::stringstream ss(line);
    int32_t quantity1, quantity2, quantity3;
    double price1, price2, price3;
    ss >> quantity1 >> price1 >> quantity2 >> price2 >> quantity3 >> price3;
    return {{quantity1, price1}, {quantity2, price2}, {quantity3, price3}};
}

TradeEntity ParseTradeEntity(const std::string& line) {
    std::stringstream ss(line);
    int32_t quantity;
    double riskPerUnit;
    ss >> quantity >> riskPerUnit;
    return TradeEntity{quantity, riskPerUnit};
}

void OutputTrade(int32_t quantityTraded, double avgFillPrice) {
    std::cout << std::fixed << std::setprecision(2) << quantityTraded << " " << avgFillPrice << std::endl;
}

int main() {
    std::string line;
    
    std::getline(std::cin, line);
    auto buyPrices = ParseMarketData(line);
    std::getline(std::cin, line);
    auto sellPrices = ParseMarketData(line);
    double remainingRisk = 0.0;

    while (std::getline(std::cin, line)) {
        auto trade = ParseTradeEntity(line);
        double totalRisk = trade.Quantity * trade.RiskPerUnit + remainingRisk;

        if (totalRisk > 0) {
            int sellQuantity = static_cast<int>(totalRisk);
            remainingRisk = totalRisk - sellQuantity;  

            int32_t quantitySold = 0;
            double totalValue = 0.0;
            for (auto& level : sellPrices) {
                if (sellQuantity == 0) break;
                
                int toSell = std::min(sellQuantity, level.Quantity);
                quantitySold += toSell;
                totalValue += toSell * level.Price;
                sellQuantity -= toSell;
                level.Quantity -= toSell;
            }

            double avgFillPrice = totalValue / quantitySold;
            OutputTrade(-quantitySold, avgFillPrice);
        } else if (totalRisk < 0) {
            int buyQuantity = static_cast<int>(-totalRisk);
            remainingRisk = totalRisk + buyQuantity;  

            int32_t quantityBought = 0;
            double totalValue = 0.0;
            for (auto& level : buyPrices) {
                if (buyQuantity == 0) break;
                
                int toBuy = std::min(buyQuantity, level.Quantity);
                quantityBought += toBuy;
                totalValue += toBuy * level.Price;
                buyQuantity -= toBuy;
                level.Quantity -= toBuy;
            }

            double avgFillPrice = totalValue / quantityBought;
            OutputTrade(quantityBought, avgFillPrice);
        }
    }

    return 0;
}
