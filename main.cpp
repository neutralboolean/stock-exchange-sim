#include <iostream>
#include <random>
#include "stockAI.h"
#include "Company.h"
#include <vector>

void simulateConditions(int& market_conditions);

void simulateMarket( std::vector<Company*>& arg, std::vector<StockAI*>& arg2, int market_conditions);

Company* foundCompany();

int main()
{
    bool running = true;
    int market_conditions;

    const int tech_good = 1; const int tech_bad = 2;
    const int food_good = 3; const int food_bad = 4;
    const int oil_good = 5; const int oil_bad = 6;


    std::cout << "How many companies in the market?" << std::endl;

    int answer;
    std::cin >> answer;

    std::vector<Company*> company_vector;

    for(int looper = 0; looper < answer; ++looper)
        {
        company_vector.push_back( foundCompany() );
        }

    std::vector<StockAI*> ai_vector;
    ai_vector.push_back( new InvestorAI(20000.0) );
    ai_vector.push_back( new CautiousAI(7500.0) );
    ai_vector.push_back( new RichQuickAI(10000.0) );

    while ( running )
        {

        /*
        Simulates the conditions at the start of every week, then runs on a 7-increment for-loop timer
        where each iteration simulates a day.

        -Daily simulation starts with an opening calculation of values for companies in the array, then lets the AIs buy and sell 3 times,
        and then it closes with another company-value calculation
                --decide after preliminary tests, if the opening company simulations can be excised
        */

        market_conditions = simulateConditions();
        for(int timer = 0; timer < 7; timer++)
            {
            simulateMarket(company_vector, ai_vector, market_conditions);
            }
        }
    return 0;
}

int simulateConditions(){
    // good/bad day for: [1,2]tech, [3,4]food, [5,6] oil
    // [7]nothing special

    std::default_random_engine generator;
    std::bernoulli_distribution bi_distribution(0.4);
    std::uniform_int_distribution<int> distribution(1,6);
    int market_conditions

    bool luck = bi_distribution(generator);

    if (luck == true){
        std::cout << "Nothing special this week. " << 7 << std::endl << std::endl ;
    }
    else if (luck == false){
        market_conditions = distribution(generator);
        switch(market_conditions){
            case 1:
                std::cout << "Good luck for tech companies." << std::endl << std::endl;
                break;
            case 2:
                std::cout << "Bad news for technology shareholders." << std::endl << std::endl;
                break;
            case 3:
                std::cout << "Food stocks are trending high." << std::endl << std::endl;
                break;
            case 4:
                std::cout << "Food imports AND exports have been hit by inclement weather." << std::endl << std::endl;
                break;
            case 5:
                std::cout << "Oil prices are only going to rise for the foreseeable future." << std::endl << std::endl;
                break;
            case 6:
                std::cout << "New drilling spots have flooded the market with oil!" << std::endl << std::endl;
                break;
        }
    }

    return market_conditions;

}

/**

*/
void simulateMarket( std::vector<Company*>& company, std::vector<StockAI*>& stock_ai, int market_conditions) {

    for (auto comp : company){                       //simulates opening of the market
        comp->simulateEarnings(market_conditions);//calculates ... stuff ... brain hurts, reconsider later
    }

    for (int timer = 0; timer < 3; timer++){        //runs the AI buying and selling 3 times to simulate 3 sessions during a day
        for ( auto ai : stock_ai){
            ai->searchExchange(company);
            ai->buyStock();//buys stocks, then sells stock for each AI
            ai->sellStock();
        }
    }

    for (auto comp : company){                    //simulates closing of the market
        comp->calcValues();
    }

}

/**
Takes no input.
Is a factory function to churn out any number of randomly-generated `Company`-class objects.
Randomly generates the size, type, and number of shares of the Company object.
*/
Company* foundCompany(){

    int shares_inp; char size_inp; int type_inp;
    std::default_random_engine seeder;
    std::uniform_int_distribution<int> size_generator(1,3);

    int go = size_generator(seeder);

    switch(go){     //uses the PRNG to determine the size of the company: "S"mall, "E"stablished, or "R"enowned.
        case 1:
            size_inp = 'S';
            std::uniform_int_distribution<int> share_generator(10000, 150000);
            shares_inp = share_generator(seeder);
            break;
        case 2:
            size_inp = 'E';
            std::uniform_int_distribution<int> share_generator(250000, 750000);
            shares_inp = share_generator(seeder);
            break;
        case 3:
            size_inp = 'R';
            std::uniform_int_distribution<int> share_generator(10000000, 20000000);
            shares_inp = share_generator(seeder);
            break;
    }

    int go_again = size_generator(seeder);

    switch(go_again){   //same PRNG but used to decide what type of company is being created
        case 1:
           type_inp = FOOD;
           break;
        case 2:
            type_inp = TECH;
            break;
        case 3:
            type_inp = OIL;
            break;
    }

    return new Company(shares_inp, size_inp, type_inp);
}
