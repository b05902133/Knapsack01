#include "Knapsack01.h"

#include <algorithm>
#include <cmath>
#include <stack>

#ifndef NDEBUG
#include <iostream>
#endif

using namespace std;

// public member functions
/*!
 *  Solve the knapsack 0/1 problem.
 *
 *  \return the max profit
 */
int Knapsack01::solve()
{
  int profit    = 0;
  int capacity  = mCapacity;

  mLowerBound = init();

  addDecision( profit, capacity, 0 );

  while( !mNextDecisions.empty() )
  {
    NextDecision  decision  = mNextDecisions.top();
    Item          &item     = mItems[decision.level];

    mNextDecisions.pop();

    if( decision.upperBound < mLowerBound ) continue;

    for( size_t i = mDecisions.size() ; i > decision.level ; --i )
    {
       const Item &item = mItems[i-1];

       if( mDecisions.back() )
       {
         profit   -= item.profit;
         capacity += item.weight;
       }
       mDecisions.pop_back();
    }

    if( decision.value && ( capacity < item.weight ) ) continue;

    if( decision.value )
    {
      profit   += item.profit;
      capacity -= item.weight;
    }
    mDecisions.push_back( decision.value );

    if( mDecisions.size() == mItems.size() )
    {
      mLowerBound = max( profit, mLowerBound );
      continue;
    }
    addDecision( profit, capacity, mDecisions.size() );
  }
  return mLowerBound;
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
  vector<Item>  items     = mItems;
  int           profit    = 0;
  int           capacity  = mCapacity;

  sort( items.begin(), items.end(),
        []( const Item &front, const Item &back )
        {
          return ( static_cast<double>( front.profit ) / front.weight > static_cast<double>( back.profit ) / back.weight );
        }
      );

  for( const Item &item : items )
  {
     if( capacity > item.weight )
     {
       profit   += item.profit;
       capacity -= item.weight;
     }
  }
  return profit;
}

/*!
 *  Get the upper bound of the subproblem.
 *  The subproblem has lower bound profit **profit** and capacity **capacity**,
 *  and start from level **level**.
 *
 *  \return the upper bound of the subrpoblem.
 */
int Knapsack01::upperbound( double profit, double capacity, size_t level )
{
  vector<Item> items{ mItems.begin() + level, mItems.end() };

  sort( items.begin(), items.end(),
        []( const Item &front, const Item &back )
        {
          return ( static_cast<double>( front.profit ) / front.weight > static_cast<double>( back.profit ) / back.weight );
        }
      );

  for( const Item &item : items )
  {
     if( capacity > item.weight )
     {
       profit   += item.profit;
       capacity -= item.weight;
     }
     else
     {
       profit += static_cast<double>( item.profit ) / item.weight * capacity;
       break;
     }
  }
  return ceil( profit );
}

void Knapsack01::addDecision( int profit, int capacity, std::size_t level )
{
  Item          &item     = mItems[level];
  NextDecision  decision0 = NextDecision{ level, false,  upperbound( profit, capacity , level + 1 ) };
  NextDecision  decision1 = NextDecision{ level, true,   upperbound( profit + item.profit, capacity - item.weight, level + 1 ) };

  if( decision0.upperBound < decision1.upperBound )
    swap( decision0, decision1 );

  if( decision1.upperBound > mLowerBound ) mNextDecisions.push( decision1 );
  if( decision0.upperBound > mLowerBound ) mNextDecisions.push( decision0 );
}
// private member functions
