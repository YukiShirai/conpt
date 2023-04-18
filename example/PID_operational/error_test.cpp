#include <iostream>

using namespace std;

int main()
{
   int x = 0;
 
   // Some code
   cout << "Before try \n";
   try {
      cout << "Inside try \n";
      if (x < 0)
      {
         throw x;
         cout << "After throw (Never executed) \n";
      }
            if (x == 0)
      {
         throw "Hi";
         cout << "After throw  ZERO (Never executed) \n";
      }
   }
   catch (int x ) {
      cout << "Exception Caught \n";
   }

      catch (...) {
      cout << "default  \n";
   }
 
   cout << "After catch (Will be executed) \n";
   return 0;
}