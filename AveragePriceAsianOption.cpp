#include "AveragePriceAsianOption.h"
#include <algorithm>

AveragePriceAsianOption::AveragePriceAsianOption(double strikePrice, double expirationDate) : ExoticOption(strikePrice, expirationDate) {}

double AveragePriceAsianOption::calculatePayoff(const std::vector<double>& priceHistory) const {
    double sum = 0.0;
    for (double price : priceHistory) {
        sum += price;
    }
    double averagePrice = sum / priceHistory.size();
    return std::max(0.0, averagePrice - getStrikePrice());
}