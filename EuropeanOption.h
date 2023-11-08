#ifndef EUROPEAN_OPTION_H
#define EUROPEAN_OPTION_H

#include "OptionContract.h"
#include <algorithm>

class EuropeanOption : public OptionContract {
public:
    EuropeanOption(double strikePrice, double expirationDate);
    double calculatePayoff(double stockPrice) const override;
};

#endif