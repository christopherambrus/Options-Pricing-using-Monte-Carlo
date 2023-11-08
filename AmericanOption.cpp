#include "AmericanOption.h"

AmericanOption::AmericanOption(double strikePrice, double expirationDate) : OptionContract(strikePrice, expirationDate) {}

double AmericanOption::calculatePayoff(double stockPrice) const {
    return std::max(0.0, stockPrice - getStrikePrice());
}

bool AmericanOption::isAmerican() const {
    return true;
}