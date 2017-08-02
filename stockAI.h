#ifndef STOCKAI_H_INCLUDED
#define STOCKAI_H_INCLUDED

#include <map>
#include <memory>
#include "Company.h"

class StockAI {
    public:
        virtual void buyStock() = 0;
        virtual void sellStock() = 0;
        virtual void searchExchange( std::vector<Company*> arg ) = 0;
        std::weak_ptr<Company> desirable_company;
    protected:
        double capital;
    private:
        std::map<std::weak_ptr<Company>, int> share_holdings;     //Company is the key, int is the number of shares


};

class InvestorAI : public StockAI {
    private:
        InvestorAI(double capital_p);

        virtual void searchExchange( std::vector<Company*> arg ) override;

        virtual void buyStock() override;

        virtual void sellStock() override;

        std::string name = "Investor";
};

class CautiousAI : public StockAI {
    //buys stock
    private:
        CautiousAI(double capital_p);

        virtual void searchExchange( std::vector<Company*> arg ) override;

        virtual void buyStock() override;

        virtual void sellStock() override;

};

//RandomAI excised but not entirely deleted

/*
class RandomAI : public StockAI {
    //buys and sells randomly
    //the bounds of the randomness NEED to be defined later [or not]
    public:
        RandomAI(double capital_p);

        virtual void buyStock() override;

        virtual void sellStock() override;
};
*/

//buys stock at a some arbitrarily low price and sells at some later arbitrarily high price
//goal is to have as much capital as possible
//will not have their capital below 200$ and will not spend more than 3/5 of their entire capital in one go

//sells when
class RichQuickAI : public StockAI {

    private:
        RichQuickAI(double capital_p);

        virtual void searchExchange( std::vector<Company*> arg ) override;

        virtual void buyStock() override;

        virtual void sellStock() override;
};


#endif // STOCKAI_H_INCLUDED
