#ifndef KNAPSACK01_H
#define KNAPSACK01_H

#include <vector>
#include <stack>
#include <tuple>

class Knapsack01
{
  public:

    inline void setCapacity ( int capacity  );
    inline void setItemNum  ( int itemNum   ); 
    inline void addItem     ( int profit,   int weight );

    int solve();

  private:

    using NextDecision = std::tuple<size_t,bool,int>; // level, value, upper bound

    int init      ();
    int upperbound( double profit, double capacity, std::size_t level );

    void  addDecision ();
    int   evalProfit  ();
    int   evalCapcity ();

    struct Item
    {
      int profit;
      int weight;
    };

    int mCapacity;

    std::vector<Item> mItems;

    int mLowerBound;

    std::stack<NextDecision>  mNextDecisions;
    std::vector<bool>         mDecisions;
};

// public inline member functions
inline void Knapsack01::setCapacity ( int capacity )
{ mCapacity = capacity; }
inline void Knapsack01::setItemNum  ( int itemNum   )
{ mItems.reserve( itemNum ); }
inline void Knapsack01::addItem     ( int profit,   int weight )
{ mItems.push_back( Item{ profit, weight } ); }
// end public inline member functions

#endif
