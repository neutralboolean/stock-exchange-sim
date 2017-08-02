#include "stockAI.h"
#include <random>
#include "Company.h"

typedef std::shared_ptr<Company> CompanyPtr

static int CAUTIOUS_SELL_THRESHOLD = -20;   //if the trend of a stock is less than this CautiousAIs will sell shares.

//Invest-y stuff
//COMPLETED
InvestorAI::InvestorAI(double capital_p){
    CompanyPtr dcom_ptr = std::make_shared<Company>(this->desirable_company);

    this->capital = capital_p;
    dcom_ptr = nullptr;
}

/**
Searches for the company with the highest change in value (delta_value) AND trending value (value_trend).
Candidate company becomes desirable_company, set in the local, shared_ptr variable `dcom_ptr` ("desirable company pointer")
*/
void InvestorAI::searchExchange( std::vector<Company*> arg ) override {

    CompanyPtr dcom_ptr = std::make_shared<Company>(this->desirable_company);
    dcom_ptr = nullptr;

    for ( CompanyPtr step : arg){
        if( dcom_ptr == nullptr){
            dcom_ptr = arg[step];
        }
        else if( ( dcom_ptr->delta_value < arg[step]->delta_value )
                &&
                ( dcom_ptr->value_trend < arg[step]->value_trend ) ) {
            dcom_ptr = arg[step];
        }
    }
}

/**
Buys stock so as to have as little capital as possible at any one time
*/
void InvestorAI::buyStock() override{
    CompanyPtr dcom_ptr = std::make_shared<Company>(this->desirable_company);

    if (this->capital > 0){
        double stock_hold = this->capital/desirable_company->stock_price;
        int stock_buy_i = static_cast<int>(stock_hold + 0.5);
        if ( share_holdings[desirable_company] == dcom_ptr ){       //maybe return dcom_ptr here to this->desirable_company
            this->share_holdings[dcom_ptr] += stock_buy_i;
        }
        else{
            this->share_holdings[dcom_ptr] = stock_buy_i;
        }
    }

    dcom_ptr->setShares( (dcom_ptr->getShares() - stock_buy_i) ) ;
}

/**
Sells stock if the value_trend of any of the companies he has stock in goes below zero.
AI then sells 2/3rds of that company's stock.
*/
void InvestorAI::sellStock() override{
    CompanyPtr dcom_ptr = std::make_shared<Company>(this->desirable_company);

    for ( auto step : this->share_holdings){
        if ( step.first->value_trend < 0){
            int stock_sell_holder = static_cast<int>( (step.second * (2.0/3.0)) + 0.5) ;
            share_holdings[step.first] -= stock_sell_holder ;
            this->capital += ( stock_sell_holder * step.first->stock_price ) ;

            step.first->setShares ( (step.first->getShares() + stock_sell_holder) );    //gives the sold stock back to the company
        }
    }
}

//Cautious stuff
CautiousAI::CautiousAI(double capital_p){
    CompanyPtr dcom_ptr = std::make_shared<Company>(this->desirable_company);

    this->capital = capital_p;
    dcom_ptr = nullptr;
}

void CautiousAI::searchExchange( std::vector<Company*> arg ) override {
    CompanyPtr dcom_ptr = std::make_shared<Company>(this->desirable_company);
    dcom_ptr = nullptr;

    for (auto step : arg){
        if (dcom_ptr == nullptr){
            dcom_ptr = step;
        }
        else if ( (dcom_ptr->value_trend > -(CAUTIOUS_SELL_THRESHOLD) )
            &&
            ( dcom_ptr->stock_price < 15.00 ) ){
            dcom_ptr = step;
        }
    }

}

void CautiousAI::buyStock(  ) override{
    CompanyPtr dcom_ptr = std::make_shared<Company>(this->desirable_company);
    int capital_temp = 100 * (dcom_ptr->stock_price) ;
    this->capital -= capital_temp;
    dcom_ptr->setShares( dcom_ptr->getShares() - 100);
    this->share_holdings[dcom_ptr] = 100;

void CautiousAI::sellStock(  ) override{
    for (auto step : this->share_holdings){
        int trend_holder = step.first->getTrend();
        if (trend_holder < CAUTIOUS_SELL_THRESHOLD){
            if (step.second < 200){
                this->capital += ( (step.first->stock_price) * (step.second) );
                step->setShares( ( (step.first->getShares()) + (step.second) ));
                this->share_holdings.erase(step.first);
            }
            else {
                this->capital += ( (step.first->stock_price) * 200 );
                step->setShares( ( (step.first->getShares()) + 200 ));
                this->share_holdings[step.first] -= 200;
            }
        }
    }
}

//Random stuff excised but not entirely deleted
/*

RandomAI::RandomAI(double capital_p){
    this->capital = capital_p;
    this->desirable_company = nullptr;
}


void RandomAI::searchExchange( CompanyPtr arg[] ) {
    this->desirable_company = nullptr;
    arg[]
}

void RandomAI::buyStock() override{

}

void RandomAI::sellStock() override{

}
*/

//Rich Quick stuff
RichQuickAI::RichQuickAI(double capital_p){
    CompanyPtr dcom_ptr = std::make_shared<Company>(this->desirable_company);
    this->capital = capital_p;
    dcom_ptr = nullptr;
}

void RichQuickAI::searchExchange( std::vector<Company*> arg ) override {
    CompanyPtr dcom_ptr = std::make_shared<Company>(this->desirable_company);

    dcom_ptr = nullptr;

    for ( auto step : arg ){
        if( dcom_ptr == nullptr ){
            dcom_ptr = arg[step];
        }
        else if( ( ( dcom_ptr->daily_earnings ) < ( arg[step]->daily_earnings ) )
                 &&
                ( (dcom_ptr->getPrice() ) < ( arg[step]->stock_price ) ) )
        {
            dcom_ptr = arg[step];
        }
    }
}
/**
Buys based on each company's daily earning which is decided based on searchExchange()
*/
void RichQuickAI::buyStock() override{
    CompanyPtr dcom_ptr = std::make_shared<Company>(this->desirable_company);

    if ( this->capital > 200.0 ){
        double usable_cap = (this->capital * 3.0)/5.0 ;
        double stock_hold = usable_cap / (dcom_ptr->stock_price) ;

        int share_subtract = static_cast<int>( ( stock_hold / (dcom_ptr->getPrice();) ) + 0.5 );

        dcom_ptr->setShares( (dcom_ptr->getShares) - share_subtract );
    }

}

/**
Sells stock when the delta_value of the stocks in share_holdings is at least 2x greater than when the AI bought them.
The AI then sells 90% of the shares that it owns for that particular company
*/
void RichQuickAI::sellStock() override{
    CompanyPtr dcom_ptr = std::make_shared<Company>(this->desirable_company);
    for(auto iter : this->share_holdings){
        if ( (iter.first.value_trend) > ( (iter.first.delta_value) * 2) ){
            int stock_hold = static_cast<int>(iter.second * 0.9);
            this->captial += stock_hold/(1.0 * iter.first.stock_price) ;
            iter.first.setShares( (iter.first.getShares() + stock_hold) );
        }
    }
}
*/
