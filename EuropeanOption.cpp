#include "EuropeanOption.h"

EuropeanOption::EuropeanOption(double strikePrice, double expirationDate) : OptionContract(strikePrice, expirationDate) {}

double EuropeanOption::calculatePayoff(double stockPrice) const {
    return std::max(0.0, stockPrice - getStrikePrice());

}

double EuropeanOption::calculatePutPayoff(double stockPrice) const {
    return std::max(0.0, getStrikePrice() - stockPrice);
}