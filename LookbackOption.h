#ifndef LOOKBACK_OPTION_H
#define LOOKBACK_OPTION_H

#include "ExoticOption.h"
#include <vector>
#include <algorithm>

class LookbackOption : public ExoticOption {
public:
    LookbackOption(double strikePrice, double expirationDate);
    double calculatePayoff(const std::vector<double>& priceHistory) const override;
};

#endif