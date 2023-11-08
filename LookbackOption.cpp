#include "LookbackOption.h"

LookbackOption::LookbackOption(double strikePrice, double expirationDate) : ExoticOption(strikePrice, expirationDate) {}

double LookbackOption::calculatePayoff(const std::vector<double>& priceHistory) const {
    double minPrice = *std::min_element(priceHistory.begin(), priceHistory.end());
    double maxPrice = *std::max_element(priceHistory.begin(), priceHistory.end());
    return std::max(maxPrice - minPrice, 0.0);
}