#include "Knapsack01.h"

#include <algorithm>

// public member functions
/*!
 *  Solve the knapsack 0/1 problem.
 *
 *  \return the max profit
 */
int Knapsack01::solve()
{
  int lowerbound = init();

  return lowerbound;
}
// end public member functions

// private member functions
/*!
 *  Initialize the solve.
 *
 *  \return initial lower bound of profit.
 */
int Knapsack01::init()
{
  int profit    = 0;
  int capacity  = mCapacity;

  sort( mItems.begin(), mItems.end(),
        []( const Item &front, const Item &back )
        {
          return ( static_cast<double>( front.profit ) / front.weight > static_cast<double>( back.profit ) / back.weight );
        }
      );

  for( const Item &item : mItems )
  {
     if( capacity - item.weight > 0 )
     {
       profit   += item.profit;
       capacity -= item.weight;
     }
  }
  return profit;
}

/*!
 *  Get the upper bound of the subproblem.
 */
int Knapsack01::upperbound( int profitCurrent, int level )
{
  return 0;
}
// private member functions
