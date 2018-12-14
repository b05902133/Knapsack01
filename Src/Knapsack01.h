#ifndef KNAPSACK01_H
#define KNAPSACK01_H

#include <vector>

class Knapsack01
{
  public:

    inline void setCapacity ( int capacity  );
    inline void setItemNum  ( int itemNum   ); 
    inline void addItem     ( int profit,   int weight );

    int solve();

  private:

    int init      ();
    int upperbound( double profit, double capacity, std::size_t level );

    struct Item
    {
      int profit;
      int weight;
    };

    int mCapacity;

    std::vector<Item> mItems;
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
