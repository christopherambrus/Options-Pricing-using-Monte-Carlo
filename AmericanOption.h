#ifndef AMERICAN_OPTION_H
#define AMERICAN_OPTION_H

#include "OptionContract.h"
#include <algorithm>

class AmericanOption : public OptionContract {
public:
    AmericanOption(double strikePrice, double expirationDate);
    double calculatePayoff(double stockPrice) const override;
    bool isAmerican() const override;
};

#endif