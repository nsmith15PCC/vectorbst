#include <iostream>
#include <ctime>
#include <cstdlib>
#include <set>
#include "bst.h"

using namespace std;

int main ()
{
    bst<int> thetree;
    srand(time(NULL));

    for (unsigned int i = 0; i < 100000; ++i)
    {
        thetree.insert(rand()%20000);
    }
    for (int i = 0; i < 20000; ++i)
    {
        thetree.remove(i,1000);
    }

    cout<<"Success!"<<endl;

    return 0;
}
