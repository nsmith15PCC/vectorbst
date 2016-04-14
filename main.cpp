#include <iostream>
#include <ctime>
#include <cstdlib>
#include "bst.h"

using namespace std;

int main ()
{
    bst<int> thetree;
    srand(time(NULL));

    for (unsigned int i = 0; i < 25; ++i)
    {
        int toinsert = rand()%10;
        cout<<endl<<"Inserting "<<toinsert<<endl;
        thetree.insert(toinsert);
        thetree.print(cout,thetree.root());
    }

    cout<<"Finished inserting!"<<endl;
    cout<<(thetree.balanced() ? "Balanced!" : "Not balanced!")<<endl;
    if(!thetree.balanced())
    {
        cout<<"balancing!"<<endl;
        thetree.balance();
        thetree.print(cout, thetree.root());
    }

    for (int i = 0; i < 10; ++i)
    {
        cout<<endl<<"Removing "<<i<<endl;
        thetree.remove(i, 10);
        thetree.print(cout, thetree.root());
        cout<<(thetree.balanced() ? "Balanced!" : "Not balanced!")<<endl;
        if(!thetree.balanced())
        {
            cout<<"balancing!"<<endl;
            thetree.balance();
            thetree.print(cout, thetree.root());
        }
    }

    cout<<"Success!"<<endl;
    return 0;
}
