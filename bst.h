#ifndef BST
#define BST

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
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
        const size_t& root () const;

    TRAVERSAL_TYPE& traversal();
    const TRAVERSAL_TYPE& traversal() const;

    bool empty();
    size_t size();

    void clear();

    bool balanced();
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

    void print(ostream &outs, size_t r, size_t depth = 0);


private:
    vector<node<data_type> > thetree;
    TRAVERSAL_TYPE thetraversal;

    void insertHELPER (size_t &r, const data_type &d, size_t s);
    bool removeHELPER (size_t& r, const data_type &d, size_t s);
    bool removeMAX (size_t& r, data_type &d, size_t &s);

    void deallocate (size_t &r, size_t index);

    size_t &findparent(size_t index);

    int depth(size_t r);

    void tree_to_vine (size_t &root, int &size );
    void vine_to_tree ( size_t &root, int size );
    int FullSize ( int size );
    void compression ( size_t &root, int count );

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
    return thetree[0].child(1);
}

template <typename data_type>
const size_t& bst<data_type>::root () const
{
    return thetree[0].child(1);
}

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
    insertHELPER(thetree[0].child(1), d, s);
}

template <typename data_type>
void bst<data_type>::insertHELPER (size_t &r, const data_type &d, size_t s)
{
    if (r)
    {
        if (thetree[r] == d)
            thetree[r] += s;
        else
        {
            insertHELPER( thetree[r].child( thetree[r] < d ) , d, s );
        }
    }
    else
    {
        r = thetree.size();
        thetree.push_back(node<data_type> (d, s));
    }
}

template <typename data_type>
void bst<data_type>::deallocate (size_t &r,size_t index)
{
        if (r == thetree.size() - 1)
        {
            if (index != thetree.size() - 1)
            {
                thetree[index] = thetree[r];
                r = index;
            }
            thetree.pop_back();
        }
        else
        {
            deallocate(thetree[r].child(thetree[r] < (thetree[thetree.size() - 1])), index);
        }
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
        if (dlt != thetree.size() -1 )
            deallocate(root(), dlt);
        else
            thetree.pop_back();
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
                    if (temp != thetree.size() -1)
                        deallocate(root(),temp);
                    else
                        thetree.pop_back();
                    return true;
                }
                else
                {
                    return removeMAX(thetree[r].child(0), thetree[r].data(), thetree[r].count());
                }
        else
            return removeHELPER(thetree[r].child(thetree[r] < d), d, s);
    }
    else
        return false;
}


template <typename data_type>
bool bst<data_type>::remove(const data_type &d, size_t s )
{
    return removeHELPER(thetree[0].child(1), d, s);
}

template<typename data_type>
void bst<data_type>::print(ostream& outs, size_t r, size_t depth)
{
    if (r)
    {
        print (outs, thetree[r].child(0), depth + 4);
        outs << setw(depth)<< thetree[r]<<endl;
        print (outs, thetree[r].child(1), depth + 4);
    }
}

template <typename data_type>
int bst<data_type>::depth (size_t r)
{

    if(r)
        return 1 + max(depth(thetree[r].child(0)), depth(thetree[r].child(1)));
    else
        return 0;
}

template <typename data_type>
bool bst<data_type>::balanced()
{
    return (abs(depth(thetree[root()].child(0)) - depth(thetree[root()].child(1))) <= 1);
}

template <typename data_type>
void bst<data_type>::balance()
{
    int size = 0;
    size_t dummy = 0;
    tree_to_vine(dummy, size);
    vine_to_tree(dummy, size);
}

template <typename data_type>
void bst<data_type>::tree_to_vine ( size_t &root, int &size )
{
    size_t vineTail, remainder, tempPtr;
    vineTail = root;
    remainder = thetree[vineTail].child(1);
    size = 0;
    while ( remainder )
    {
        if ( !thetree[remainder].child(0) )
        {
            vineTail = remainder;
            remainder = thetree[remainder].child(1);
            size++;
        }
        else
        {
            tempPtr = thetree[remainder].child(0);
            thetree[remainder].child(0) = thetree[tempPtr].child(1);
            thetree[tempPtr].child(1) = remainder;
            remainder = tempPtr;
            thetree[vineTail].child(1) = tempPtr;
        }
    }
}

template<typename data_type>
int bst<data_type>::FullSize (int size)
{
    int Rtn = 1;
    while ( Rtn <= size )
        Rtn = Rtn + Rtn + 1;
    return Rtn/2;
}

template <typename data_type>
void bst<data_type>::vine_to_tree ( size_t &root, int size )
{
    int full_count = FullSize (size);
    compression(root, size - full_count);
    for ( size = full_count ; size > 1 ; size /= 2 )
        compression ( root, size / 2 );
}

template <typename data_type>
void bst<data_type>::compression ( size_t &root, int count )
{
    size_t scanner = root;

    for ( int j = 0; j < count; j++ )
    {
        size_t child = thetree[scanner].child(RIGHT);
        thetree[scanner].child(RIGHT) = thetree[child].child(RIGHT);
        scanner = thetree[scanner].child(RIGHT);
        thetree[child].child(RIGHT) = thetree[scanner].child(LEFT);
        thetree[scanner].child(LEFT) = child;
    }
}




#endif // BST
