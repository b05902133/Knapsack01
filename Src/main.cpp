#include <iostream>
using namespace std;

#include "Knapsack01.h"

int main()
{
  Knapsack01  solver;
  int         capacity;
  int         itemNum;

  cin >> capacity >> itemNum;

  solver.setCapacity( capacity  );
  solver.setItemNum ( itemNum   );

  for( int i = 0 ; i < itemNum ; ++i )
  {
     int profit;
     int weight;

     cin >> profit >> weight;

     solver.addItem( profit, weight );
  }

  cout << solver.solve() << "\n";

  return 0;
}
