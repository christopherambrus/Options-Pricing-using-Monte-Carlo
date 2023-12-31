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
    // Creating options with strike 100
    EuropeanOption europeanOption(100.0, 1.0);
    AmericanOption americanOption(100.0, 1.0);
    AveragePriceAsianOption asianOption(100.0, 1.0);
    LookbackOption lookbackOption(100.0, 1.0);

    std::vector<double> priceHistory = {97.0, 101.0, 110.0, 90.0, 115.0, 120.0, 110.0, 122.0}; // Example price history
    double stockPrice = priceHistory.back(); // Current stock price at expiration

    // Calculating payoffs
    double europeanPayoff = europeanOption.calculatePayoff(stockPrice);
    double americanPayoff = americanOption.calculatePayoff(stockPrice);
    double asianPayoff = asianOption.calculatePayoff(priceHistory);
    double lookbackPayoff = lookbackOption.calculatePayoff(priceHistory);

    int numSimulations = 100000; // Number of Monte Carlo simulations
    double totalPayoff = 0.0;

    // Randomness generation
    random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> dist(0.0, 1.0);

    // Monte Carlo European Call
    for (int i = 0; i < numSimulations; ++i) {
        double simulatedPrice = stockPrice * exp(0.1 - 0.2 * 0.2 / 2 + 0.2
         * dist(gen)); //Geometric Brownian Motion = 0.2 / 2 + 0.2
        double payoff = europeanOption.calculatePayoff(simulatedPrice);
        totalPayoff += payoff;
    }

    double europeanOptionValue = (totalPayoff / numSimulations) * exp(-0.1 * europeanOption.getExpirationDate());

    std::cout << "Monte Carlo European Call Option Value: " << europeanOptionValue << std::endl;

    // European Put
    double totalPutPayoff = std::max(0.0, -totalPayoff / numSimulations);

    double europeanPutOptionValue = totalPutPayoff * exp(-0.1 * europeanOption.getExpirationDate());

    std::cout << "Monte Carlo European Put Option Value: " << europeanPutOptionValue << std::endl;

    // Monte Carlo Lookback call
    double lookbackOptionValue = 0.0;

    for (int i = 0; i < numSimulations; ++i) {
        vector<double> simulatedPrices;
        double discountedPayoff = 0.0;

        for (double t = 0; t < lookbackOption.getExpirationDate(); t += 1.0 / 252.0) {  //Number of trading days in a year = 252
            double currentPrice = priceHistory.back();
            double simulatedPrice = currentPrice * exp(0.1 - 0.2 * 0.2 / 2 + 0.2
             * dist(gen)); //Drift(riskfree rate) = 0.1, Volatility = 0.2
            simulatedPrices.push_back(simulatedPrice);
        }

        double optionPayoff = lookbackOption.calculatePayoff(simulatedPrices);
        lookbackOptionValue += optionPayoff * exp(-0.1 * lookbackOption.getExpirationDate());
    }

    lookbackOptionValue /= numSimulations;

    cout << "Monte Carlo Lookback Option Value: " << lookbackOptionValue << endl;

    // Monte Carlo Asian Call
    double asianOptionValue = 0.0;

    for (int i = 0; i < numSimulations; ++i) {
        vector<double> simulatedPrices;
        double discountedPayoff = 0.0;

        for (double t = 0; t < asianOption.getExpirationDate(); t += 1.0 / 252.0) {
            double currentPrice = priceHistory.back();
            double simulatedPrice = currentPrice * exp(0.1 - 0.2 * 0.2 / 2 + 0.2 * dist(gen));
            simulatedPrices.push_back(simulatedPrice);
        }

        double optionPayoff = asianOption.calculatePayoff(simulatedPrices);
        asianOptionValue += optionPayoff * exp(-0.1 * asianOption.getExpirationDate());
    }

    asianOptionValue /= numSimulations;

    cout << "Monte Carlo Asian Option Value: " << asianOptionValue << endl;

    //std::cout << "European Call Option Payoff: " << europeanPayoff << std::endl;
    //std::cout << "American Option Payoff: " << americanPayoff << std::endl;
    //std::cout << "Average Call Price Asian Option Payoff: " << asianPayoff << std::endl;
    //std::cout << "Lookback Call Option Payoff: " << lookbackPayoff << std::endl;

    return 0;
}