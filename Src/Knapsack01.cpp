#include "Knapsack01.h"

#include <algorithm>
#include <cmath>
#include <stack>
#include <tuple>

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
  mLowerBound = init();

  addDecision();

  while( !mNextDecisions.empty() )
  {
    NextDecision decision = mNextDecisions.top();

    mNextDecisions.pop();

    size_t  level       = get<0>( decision );
    bool    value       = get<1>( decision );
    int     upperBound  = get<2>( decision );
    Item    &item       = mItems[level];

    if( upperBound < mLowerBound ) continue;
    if( value && ( evalCapcity() < item.weight ) ) continue;

    for( size_t i = mDecisions.size() ; i > level ; --i )
       mDecisions.pop_back();

    mDecisions.push_back( value );

    if( mDecisions.size() == mItems.size() )
    {
      mLowerBound = max( evalProfit(), mLowerBound );
      continue;
    }
    addDecision();
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
  for( size_t i = level ; i < mItems.size() ; ++i )
  {
     Item &item = mItems[i];

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

void Knapsack01::addDecision()
{
  Item          &item     = mItems[mDecisions.size()];
  int           profit    = evalProfit();
  int           capacity  = evalCapcity();
  NextDecision  decision0 = make_tuple( mDecisions.size(), false,  upperbound( profit, capacity , mDecisions.size() + 1 ) );
  NextDecision  decision1 = make_tuple( mDecisions.size(), true,   upperbound( profit + item.profit, capacity - item.weight, mDecisions.size() + 1 ) );

  if( get<2>( decision0 ) > get<2>( decision1 ) )
  {
    if( get<2>( decision1 ) > mLowerBound ) mNextDecisions.push( decision1 );
    if( get<2>( decision0 ) > mLowerBound ) mNextDecisions.push( decision0 );
  }
  else
  {
    if( get<2>( decision0 ) > mLowerBound ) mNextDecisions.push( decision0 );
    if( get<2>( decision1 ) > mLowerBound ) mNextDecisions.push( decision1 );
  }
}

int Knapsack01::evalProfit()
{
  int profit = 0;

  for( size_t i = 0 ; i < mDecisions.size() ; ++i )
     if( mDecisions[i] )
       profit += mItems[i].profit;

  return profit;
}

int Knapsack01::evalCapcity()
{
  int capacity = mCapacity;

  for( size_t i = 0 ; i < mDecisions.size() ; ++i )
     if( mDecisions[i] )
       capacity -= mItems[i].weight;

  return capacity;
}
// private member functions
