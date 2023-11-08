#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <cmath>
#include "OptionContract.h"
#include "EuropeanOption.h"
#include "AmericanOption.h"
#include "ExoticOption.h"
#include "AveragePriceAsianOption.h"
#include "LookbackOption.h"

using namespace std;

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

    int numSimulations = 10000; // Number of Monte Carlo simulations
    double totalPayoff = 0.0;

    random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> dist(0.0, 1.0);

    for (int i = 0; i < numSimulations; ++i) {
        double simulatedPrice = stockPrice * exp(0.1 - 0.2 * 0.2 / 2 + 0.2 * dist(gen)); // Geometric Brownian Motion
        double payoff = europeanOption.calculatePayoff(simulatedPrice);
        totalPayoff += payoff;
    }

    double europeanOptionValue = (totalPayoff / numSimulations) * exp(-0.1 * europeanOption.getExpirationDate());

    std::cout << "Monte Carlo European Option Value: " << europeanOptionValue << std::endl;

    totalPayoff = 0.0;

    // Monte Carlo simulation for American Option using Longstaff-Schwartz
    for (int i = 0; i < numSimulations; ++i) {
        double currentPrice = stockPrice;
        double payoff = 0.0;

        for (double t = 0; t < americanOption.getExpirationDate(); t += 1.0 / 252.0) {
            double simulatedPrice = currentPrice * exp(0.1 - 0.2 * 0.2 / 2 + 0.2 * dist(gen));
            double optionPayoff = americanOption.calculatePayoff(simulatedPrice);
            
            if (americanOption.isAmerican()) {
                payoff = std::max(optionPayoff, payoff);
            } else {
                payoff = optionPayoff;
            }

            currentPrice = simulatedPrice;
        }

        totalPayoff += payoff;
    }

    double americanOptionValue = (totalPayoff / numSimulations) * exp(-0.1 * americanOption.getExpirationDate());

    std::cout << "Monte Carlo American Option Value: " << americanOptionValue << std::endl;

    //std::cout << "European Option Payoff: " << europeanPayoff << std::endl;
    //std::cout << "American Option Payoff: " << americanPayoff << std::endl;
    //std::cout << "Average Price Asian Option Payoff: " << asianPayoff << std::endl;
    //std::cout << "Lookback Option Payoff: " << lookbackPayoff << std::endl;

    return 0;
}