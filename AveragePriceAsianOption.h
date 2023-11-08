#ifndef AVERAGE_PRICE_ASIAN_OPTION_H
#define AVERAGE_PRICE_ASIAN_OPTION_H

#include "ExoticOption.h"
#include <vector>
#include <algorithm>

class AveragePriceAsianOption : public ExoticOption {
public:
    AveragePriceAsianOption(double strikePrice, double expirationDate);
    double calculatePayoff(const std::vector<double>& priceHistory) const override;
};

#endif