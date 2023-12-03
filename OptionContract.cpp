#include "OptionContract.h"

OptionContract::OptionContract(double strikePrice, double expirationDate) : strikePrice(strikePrice), expirationDate(expirationDate) {}

double OptionContract::calculatePayoff(double stockPrice) const { return 0;}

double OptionContract::calculatePutPayoff(double stockPrice) const { return 0;}

double OptionContract::getStrikePrice() const {
    return strikePrice;
}

double OptionContract::getExpirationDate() const {
    return expirationDate;
}

bool OptionContract::isAmerican() const { return false; }