#include "Company.h"
#include <random>
//DONE FOR NOW

//COMPLETE THE OTHER FILES

Company::Company(unsigned total_shares_p, char company_size_p, int company_type_p)
{
    /**
    * Ctor for class Company
    * all parameters will be picked from PRNGs
    * then used to init where applicable, else init'd to zero
    **/
    total_shares = total_shares_p;
    shares = total_shares_p;

    shares_outstanding = 0;

    company_size = company_size_p;
    company_type = company_type_p;

    delta_price = 0;
    delta_value = 0;

    value_trend = 0;

}

Company::~Company()
{
    //  delete this;
}

void Company::calcValues(){
    this->value_trend = this->delta_value;

    int val_temp = this->company_value;
    double price_temp = this->stock_price + 0.5;

    this->company_value = this->shares_outstanding * static_cast<int>(val_temp);

    this->stock_price += (this->daily_earnings / 240000.0) ;        //240000 was just an arbitrary value that was chosen because it made a nice number with a randomly-selected daily earning

    double wait = (this->stock_price - price_temp) + 0.5;
    if ( (wait < 1.0) && (wait >= 0.0) ){           //what is this for? It sets delta_price which is immediately re-defined
        this->delta_price = 1.0;
    }
    else if ( (wait > -1.0) && (wait <= 0.0) ){
        this->delta_price = -1.0;
    }
    else{
        this->delta_price = static_cast<int>( wait );
    }

    this->delta_value = ( this->company_value - val_temp ) * this->delta_price ;

    if (this->value_trend == 0){
        this->value_trend = this->delta_value;
    }
    else{
        int holder = this->value_trend + this->delta_value;
        double holderv2 = holder * 0.5;
        this->value_trend = static_cast<int>( (holderv2 + 0.5) );
    }

}

void Company::simulateEarnings(int market_conditions){
    //simulates earnings

    //possibly calculate delta_value, if the code remains light
    std::default_random_engine genny;

    if(this->company_type == TECH){
        switch(market_conditions){
            case 1:
                //good day
                if(this->company_size == 'S'){
                    std::uniform_real_distribution<double> earnings_distribution(-50000.0, 300000.0);
                    this->daily_earnings = earnings_distribution(genny);
                }
                else if(this->company_size == 'E'){
                    std::uniform_real_distribution<double> earnings_distribution(-25000.0, 750000.0);
                    this->daily_earnings = earnings_distribution(genny);
                }
                else if(this->company_size == 'R'){
                    std::uniform_real_distribution<double> earnings_distribution(-10000.0, 3000000.0);
                    this->daily_earnings = earnings_distribution(genny);
                }
                break;
            case 2:
                //bad day
                if(this->company_size == 'S'){
                    std::uniform_real_distribution<double> earnings_distribution(-300000.0, 50000.0);
                    this->daily_earnings = earnings_distribution(genny);
                }
                else if(this->company_size == 'E'){
                    std::uniform_real_distribution<double> earnings_distribution(-175000.0, 75000.0);
                    this->daily_earnings = earnings_distribution(genny);
                }
                else if(this->company_size == 'R'){
                    std::uniform_real_distribution<double> earnings_distribution(-80000.0, 2000000.0);
                    this->daily_earnings = earnings_distribution(genny);
                }
                break;
            default:
                if(this->company_size == 'S'){
                    std::normal_distribution<double> earnings_distribution(0.0, 200000.0);
                    this->daily_earnings = earnings_distribution(genny);
                }
                else if(this->company_size == 'E'){
                    std::uniform_real_distribution<double> earnings_distribution(-100000.0,450000.0);
                    this->daily_earnings = earnings_distribution(genny);
                }
                else if(this->company_size == 'R'){
                    std::uniform_real_distribution<double> earnings_distribution(-50000,2500000.0);
                    this->daily_earnings = earnings_distribution(genny);
                }
                break;
        }
    }

    else if(this->company_type == FOOD){
        switch(market_conditions){
            case 3:
                //std::cout << "Food stocks are trending high." << std::endl << std::endl;
                if(this->company_size == 'S'){
                    std::uniform_real_distribution<double> earnings_distribution(-50000.0, 300000.0);
                    this->daily_earnings = earnings_distribution(genny);
                }
                else if(this->company_size == 'E'){
                    std::uniform_real_distribution<double> earnings_distribution(-25000.0, 750000.0);
                    this->daily_earnings = earnings_distribution(genny);
                }
                else if(this->company_size == 'R'){
                    std::uniform_real_distribution<double> earnings_distribution(-10000.0, 3000000.0);
                    this->daily_earnings = earnings_distribution(genny);
                }
                break;
            case 4:
                //std::cout << "Food imports AND exports have been hit by inclement weather." << std::endl << std::endl;
                if(this->company_size == 'S'){
                    std::uniform_real_distribution<double> earnings_distribution(-300000.0, 50000.0);
                    this->daily_earnings = earnings_distribution(genny);
                }
                else if(this->company_size == 'E'){
                    std::uniform_real_distribution<double> earnings_distribution(-175000.0, 75000.0);
                    this->daily_earnings = earnings_distribution(genny);
                }
                else if(this->company_size == 'R'){
                    std::uniform_real_distribution<double> earnings_distribution(-80000.0, 2000000.0);
                    this->daily_earnings = earnings_distribution(genny);
                }
                break;
            default:
                if(this->company_size == 'S'){
                    std::normal_distribution<double> earnings_distribution(0.0, 200000.0);
                    this->daily_earnings = earnings_distribution(genny);
                }
                else if(this->company_size == 'E'){
                    std::uniform_real_distribution<double> earnings_distribution(-100000.0,450000.0);
                    this->daily_earnings = earnings_distribution(genny);
                }
                else if(this->company_size == 'R'){
                    std::uniform_real_distribution<double> earnings_distribution(-50000,2500000.0);
                    this->daily_earnings = earnings_distribution(genny);
                }
                break;
        }
    }

    else if(this->company_type == OIL){
        switch(market_conditions){
            case 5:
                // std::cout << "Oil prices are only going to rise for the foreseeable future." << std::endl << std::endl;
                if(this->company_size == 'S'){
                    std::uniform_real_distribution<double> earnings_distribution(-50000.0, 300000.0);
                    this->daily_earnings = earnings_distribution(genny);
                }
                else if(this->company_size == 'E'){
                    std::uniform_real_distribution<double> earnings_distribution(-25000.0, 750000.0);
                    this->daily_earnings = earnings_distribution(genny);
                }
                else if(this->company_size == 'R'){
                    std::uniform_real_distribution<double> earnings_distribution(-10000.0, 3000000.0);
                    this->daily_earnings = earnings_distribution(genny);
                }
                break;
            case 6:
                // std::cout << "New drilling spots have flooded the market with oil!" << std::endl << std::endl;
                if(this->company_size == 'S'){
                    std::uniform_real_distribution<double> earnings_distribution(-300000.0, 50000.0);
                    this->daily_earnings = earnings_distribution(genny);
                }
                else if(this->company_size == 'E'){
                    std::uniform_real_distribution<double> earnings_distribution(-175000.0, 75000.0);
                    this->daily_earnings = earnings_distribution(genny);
                }
                else if(this->company_size == 'R'){
                    std::uniform_real_distribution<double> earnings_distribution(-80000.0, 2000000.0);
                    this->daily_earnings = earnings_distribution(genny);
                }
                break;
            default:
                if(this->company_size == 'S'){
                    std::normal_distribution<double> earnings_distribution(0.0, 200000.0);
                    this->daily_earnings = earnings_distribution(genny);
                }
                else if(this->company_size == 'E'){
                    std::uniform_real_distribution<double> earnings_distribution(-100000.0,450000.0);
                    this->daily_earnings = earnings_distribution(genny);
                }
                else if(this->company_size == 'R'){
                    std::uniform_real_distribution<double> earnings_distribution(-50000,2500000.0);
                    this->daily_earnings = earnings_distribution(genny);
                }
                break;
        }
    }
    //End of Function
}
