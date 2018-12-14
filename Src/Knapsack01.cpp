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
  using NextDecision = tuple<size_t,bool,int>; // level, value, upper bound

  stack<NextDecision> nextDecisions;
  vector<bool>        decisions;

  int profit      = 0;
  int capacity    = mCapacity;
  int lowerBound  = init();

  NextDecision decision0 = make_tuple( 0, false,  upperbound( profit, capacity , 1 ) );
  NextDecision decision1 = make_tuple( 0, true,   upperbound( profit + mItems.front().profit, capacity - mItems.front().weight, 1 ) );

  if( get<2>( decision0 ) > get<2>( decision1 ) )
  {
    if( get<2>( decision1 ) > lowerBound ) nextDecisions.push( decision1 );
    if( get<2>( decision0 ) > lowerBound ) nextDecisions.push( decision0 );
  }
  else
  {
    if( get<2>( decision0 ) > lowerBound ) nextDecisions.push( decision0 );
    if( get<2>( decision1 ) > lowerBound ) nextDecisions.push( decision1 );
  }

  while( !nextDecisions.empty() )
  {
    NextDecision decision = nextDecisions.top();

    nextDecisions.pop();

    size_t  level       = get<0>( decision );
    bool    value       = get<1>( decision );
    int     upperBound  = get<2>( decision );
    Item    &item       = mItems[level];

    if( upperBound < lowerBound ) continue;
    if( value && ( capacity < item.weight ) ) continue;

    for( size_t i = decisions.size() ; i > level ; --i )
       decisions.pop_back();

    decisions.push_back( value );

    profit = 0;

    for( size_t i = 0 ; i < decisions.size() ; ++i )
       if( decisions[i] ) profit += mItems[i].profit;

    if( decisions.size() == mItems.size() )
    {
      lowerBound = max( profit, lowerBound );
    }
    else
    {
      Item          &item     = mItems[decisions.size()];
      NextDecision  decision0 = make_tuple( decisions.size(), false,  upperbound( profit, capacity , decisions.size() + 1 ) );
      NextDecision  decision1 = make_tuple( decisions.size(), true,   upperbound( profit + item.profit, capacity - item.weight, decisions.size() + 1 ) );

      if( get<2>( decision0 ) > get<2>( decision1 ) )
      {
        if( get<2>( decision1 ) > lowerBound ) nextDecisions.push( decision1 );
        if( get<2>( decision0 ) > lowerBound ) nextDecisions.push( decision0 );
      }
      else
      {
        if( get<2>( decision0 ) > lowerBound ) nextDecisions.push( decision0 );
        if( get<2>( decision1 ) > lowerBound ) nextDecisions.push( decision1 );
      }
    }
  }
  return lowerBound;
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
// private member functions
