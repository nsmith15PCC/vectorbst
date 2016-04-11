#ifndef BST
#define BST

#include <iostream>
#include <vector>
#include <algorithm>
#include "node.h"

using std::cout;
using std::swap;
using std::max;
using std::vector;
using std::ostream;
using std::istream;

enum TRAVERSAL_TYPE {PREORDER, INORDER, POSTORDER};
enum BSTERRORS {EMPTY};

template <typename data_type>
class bst
{
public:
    bst(TRAVERSAL_TYPE t = INORDER);
    ~bst();

    bst(const bst<data_type> &other);
    bst<data_type>& operator=(const bst<data_type> &other);

    size_t &root();
//    const size_t& root () const;

    TRAVERSAL_TYPE& traversal();
    const TRAVERSAL_TYPE& traversal() const;

    bool empty();
    size_t size();

    void clear();

    bool balanced() const;
    void balance();

    vector<node<data_type> >& thevector ();


    void insert(const data_type &d, size_t s = 1);
    bool remove(const data_type &d, size_t s = 1);

    size_t find (const data_type &d);

    template <typename D>
    friend
    istream& operator>>(istream& ins, bst<D> &b);

    template <typename D>
    friend
    ostream& operator<<(ostream& outs, const bst<D> &b);

    void print(ostream &outs, size_t r);


private:
    vector<node<data_type> > thetree;
    TRAVERSAL_TYPE thetraversal;

    void insertHELPER (size_t &r, const data_type &d, size_t s);
    bool removeHELPER (size_t& r, const data_type &d, size_t s);
    bool removeMAX (size_t& r, data_type &d, size_t &s);

    void deallocate (size_t index);

    size_t &findparent(size_t index);
};

template <typename data_type>
bst<data_type>::bst(TRAVERSAL_TYPE t)
{
    thetraversal = t;
    thetree = vector<node<data_type> >();
    thetree.push_back(node<data_type>());
}

template <typename data_type>
bst<data_type>::~bst()
{
    thetree.clear();
}

template <typename data_type>
bst<data_type>::bst(const bst<data_type> &other)
{
    thetree = other.thetree;
    thetraversal = other.thetraversal;
}

template <typename data_type>
bst<data_type>& bst<data_type>::operator=(const bst<data_type> &other)
{
    if (this != &other)
    {
        clear();
        thetree = other.thetree;
        thetraversal = other.thetraversal;
    }
}

template <typename data_type>
size_t &bst<data_type>::root ()
{
    return thetree[0].child(0);
}

//template <typename data_type>
//const size_t& bst<data_type>::root () const
//{
//    return thetree[0].child(0);
//}

template <typename data_type>
TRAVERSAL_TYPE& bst<data_type>::traversal()
{
    return thetraversal;
}

template <typename data_type>
const TRAVERSAL_TYPE& bst<data_type>::traversal() const
{
    return thetraversal;
}

template <typename data_type>
bool bst<data_type>::empty()
{
    return thetree.empty();
}

template <typename data_type>
size_t bst<data_type>::size()
{
    return thetree.size()-1;
}

template <typename data_type>
void bst<data_type>::clear()
{
    thetree.clear();
    thetree.push_back(node<data_type>());
}

template <typename data_type>
vector<node<data_type> >& bst<data_type>::thevector()
{
    return thetree;
}

template <typename data_type>
void bst<data_type>::insert(const data_type &d, size_t s)
{

    insertHELPER(thetree[0].child(0), d, s);

//    if (root() == 0)
//    {
//        thetree.push_back(node<data_type> (d,s));
//        root() = thetree.size() - 1;
//        return;
//    }

}

template <typename data_type>
void bst<data_type>::insertHELPER (size_t &r, const data_type &d, size_t s)
{
    cout<<"R = "<<r<<endl;
    if (r == 0)
    {
        cout<<"r = "<<r<<endl;
        thetree.push_back(node<data_type> (d, s));
        r = (thetree.size() - 1);
        cout<<"r = "<<r<<endl;
    }
    else
    {
        if (thetree[r] == d)
            thetree[r] += s;
        else
        {
            cout<<"Moving to " <<thetree[r].child( thetree[r] < d )<<endl;
            insertHELPER( thetree[r].child( thetree[r] < d ) , d, s );
        }
    }
}

template <typename data_type>
void bst<data_type>::deallocate (size_t index)
{
    size_t end = thetree.size()  - 1, parent = root();
    if (index == end)
    {
        thetree.pop_back();
        return;
    }
    while (parent && thetree[parent].child((DIRECTION)(thetree[parent] < thetree[end])) != end)
        parent = thetree[parent].child((DIRECTION)(thetree[parent] < thetree[end]));
    thetree[index] = thetree[end];
    thetree[parent].child((DIRECTION)(thetree[parent] < thetree[end])) = index;
    thetree.pop_back();
}

template <typename data_type>
bool bst<data_type>::removeMAX (size_t& r, data_type &d, size_t &s)
{
    if (thetree[r].child(1))
        return removeMAX(thetree[r].child(1), d, s);
    else
    {
        d = thetree[r].data();
        s = thetree[r].count();
        size_t dlt = r;
        r = thetree[r].child(0);
        deallocate(dlt);
        return true;
    }
}


template <typename data_type>
bool bst<data_type>::removeHELPER (size_t& r, const data_type &d, size_t s)
{
    if (r)
    {
        if (thetree[r] == d)
            if (s < thetree[r].count())
            {
                thetree[r] -= s;
                return true;
            }
            else
                if (! thetree[r].child(0))
                {
                    size_t temp = r;
                    r = thetree[r].child(1);
                    deallocate(temp);
                    return true;
                }
                else
                {
                    return removeMAX(thetree[r].child(0), thetree[r].data(), thetree[r].count());
                }
    }
    else
        return false;
}


template <typename data_type>
bool bst<data_type>::remove(const data_type &d, size_t s )
{
    return removeHELPER(thetree[0].child(0), d, s);
}

template<typename data_type>
void bst<data_type>::print(ostream& outs, size_t r)
{
    if (r)
    {
        outs << thetree[r];
        print (outs, thetree[r].child(0));
        print (outs, thetree[r].child(1));
    }

}

//bool balanced() const;
//void balance();





#endif // BST
