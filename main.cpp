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
    cout<<"Inserting "<<toinsert<<endl;
    thetree.insert(toinsert);
//    cout<<"Root = "<<thetree.root()<<endl;
    for (size_t j = 0; j < thetree.thevector().size(); ++j)
    {
        cout<<"index "<<j<<", data="<<thetree.thevector()[j].data()<<", left = "<<thetree.thevector()[j].child(LEFT)<<", right = "
           <<thetree.thevector()[j].child(RIGHT)<<endl;
    }
}


for (size_t i = 0; i < thetree.thevector().size(); ++i)
{
    cout<<"index "<<i<<", data="<<thetree.thevector()[i].data()<<", left = "<<thetree.thevector()[i].child(LEFT)<<", right = "
       <<thetree.thevector()[i].child(RIGHT)<<endl;
}
thetree.print(cout, thetree.root());
    return 0;
}
