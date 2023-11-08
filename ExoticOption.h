#ifndef EXOTIC_OPTION_H
#define EXOTIC_OPTION_H

#include "OptionContract.h"
#include <vector>

class ExoticOption : public OptionContract {
public:
    ExoticOption(double strikePrice, double expirationDate);
    virtual double calculatePayoff(const std::vector<double>& priceHistory) const = 0;
};

#endif