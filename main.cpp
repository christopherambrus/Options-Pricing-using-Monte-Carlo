#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class OptionContract {
public:
    OptionContract(double strikePrice, double expirationDate) : strikePrice_(strikePrice), expirationDate_(expirationDate) {}

    virtual double calculatePayoff(double stockPrice) const { return 0;}

    double getStrikePrice() const {
        return strikePrice_;
    }

    double getExpirationDate() const {
        return expirationDate_;
    }

protected:
    double strikePrice_;
    double expirationDate_;
};

class EuropeanOption : public OptionContract {
public:
    EuropeanOption(double strikePrice, double expirationDate) : OptionContract(strikePrice, expirationDate) {}

    double calculatePayoff(double stockPrice) const override {
        return std::max(0.0, stockPrice - getStrikePrice());
    }
};

class AmericanOption : public OptionContract {
public:
    AmericanOption(double strikePrice, double expirationDate) : OptionContract(strikePrice, expirationDate) {}

    double calculatePayoff(double stockPrice) const override {
        return std::max(0.0, stockPrice - getStrikePrice());
    }
};

class ExoticOption : public OptionContract {
public:
    ExoticOption(double strikePrice, double expirationDate) : OptionContract(strikePrice, expirationDate) {}

    virtual double calculatePayoff(const std::vector<double>& priceHistory) const = 0;
    
};

class AveragePriceAsianOption : public ExoticOption {
public:
    AveragePriceAsianOption(double strikePrice, double expirationDate) : ExoticOption(strikePrice, expirationDate) {}

    double calculatePayoff(const std::vector<double>& priceHistory) const override {
        double sum = 0.0;
        for (double price : priceHistory) {
            sum += price;
        }
        double averagePrice = sum / priceHistory.size();
        return std::max(0.0, averagePrice - getStrikePrice());
    }
};

class LookbackOption : public ExoticOption {
public:
    LookbackOption(double strikePrice, double expirationDate) : ExoticOption(strikePrice, expirationDate) {}

    double calculatePayoff(const std::vector<double>& priceHistory) const override {
        double minPrice = *std::min_element(priceHistory.begin(), priceHistory.end());
        double maxPrice = *std::max_element(priceHistory.begin(), priceHistory.end());
        return std::max(maxPrice - minPrice, 0.0);
    }
};

int main() {
    EuropeanOption europeanOption(100.0, 1.0);
    AmericanOption americanOption(100.0, 1.0);
    AveragePriceAsianOption asianOption(100.0, 1.0);
    LookbackOption lookbackOption(100.0, 1.0);

    std::vector<double> priceHistory = {95.0, 105.0, 110.0, 90.0, 115.0}; // Example price history
    double stockPrice = priceHistory.back(); // Current stock price at expiration

    double europeanPayoff = europeanOption.calculatePayoff(stockPrice);
    double americanPayoff = americanOption.calculatePayoff(stockPrice);
    double asianPayoff = asianOption.calculatePayoff(priceHistory);
    double lookbackPayoff = lookbackOption.calculatePayoff(priceHistory);

    std::cout << "European Option Payoff: " << europeanPayoff << std::endl;
    std::cout << "American Option Payoff: " << americanPayoff << std::endl;
    std::cout << "Average Price Asian Option Payoff: " << asianPayoff << std::endl;
    std::cout << "Lookback Option Payoff: " << lookbackPayoff << std::endl;

    return 0;
}