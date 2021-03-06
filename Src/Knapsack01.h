#ifndef KNAPSACK01_H
#define KNAPSACK01_H

#include <vector>
#include <stack>

class Knapsack01
{
  public:

    inline void setCapacity ( int capacity  );
    inline void setItemNum  ( int itemNum   ); 
    inline void addItem     ( int profit,   int weight );

    int solve();

  private:

    struct NextDecision
    {
      std::size_t level;
      bool        value;
      int         upperBound;
    };

    int init      ();
    int upperbound( double profit, double capacity, std::size_t level );

    void addDecision( int profit, int capacity, std::size_t level );

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
