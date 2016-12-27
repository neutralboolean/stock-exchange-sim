#ifndef COMPANY_H
#define COMPANY_H

//DONE FOR NOW

//COMPLETE THE OTHER FILES

enum company_t {FOOD = 424, TECH = 420, OIL = 324};

class Company
{
    public:
        Company(unsigned total_shares, char company_size, int company_type);

        ~Company();

        unsigned getShares() { return shares; }
        void setShares(unsigned value) { this->shares = value; }
/*
        unsigned getPreferred() {return preferred_shares;}
        void setPreferred(unsigned value) { preferred_shares = value; }
*/
        unsigned getValue() {return company_value;}

        int getSupply() { return delta_value; }

        int getTrend() { return value_trend; }

        double getPrice() { return stock_price;}

        void simulateEarnings(int market_conditions);

        void calcValues();

        double daily_earnings;  //calculated by a weird system of random number generators
                                //and used to calculate company_value

    private:

        char company_size; //size of the company which dictates the range of their possible earnings
                           //only three settings: "S" for startup, "E" for established, and "R" for renowned

        int company_type;   //one of three variables from the enum company_t

        unsigned shares; //is set everytime an AI buys stock in the company
        unsigned total_shares; //does not change after it is set

        //unsigned preferred_shares;
        //unsigned total_preferred;

        unsigned shares_outstanding; //`shares_outstanding` is equal to `total_shares` - `shares`

        int company_value; //is equal to `shares_outstanding` * `stock_price`
        int delta_value;   //difference between this iteration's and last's company_value
        int value_trend;   //holds the previous `delta_value` to indicate a very basic, limited kind of trend

        double stock_price;
        int delta_price;

};

#endif // COMPANY_H
