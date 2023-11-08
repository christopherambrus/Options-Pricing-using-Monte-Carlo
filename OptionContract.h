#ifndef OPTIONCONTRACT_H
#define OPTIONCONTRACT_H

class OptionContract {
public:
    
    OptionContract(double strikePrice, double expirationDate);

    virtual double calculatePayoff(double stockPrice) const;
    double getStrikePrice() const;
    double getExpirationDate() const;
    virtual bool isAmerican() const;

protected:
    double strikePrice;
    double expirationDate;
};

#endif