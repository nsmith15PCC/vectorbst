#ifndef NODE
#define NODE

#include <iostream>
#include <iomanip>

enum DIRECTION {LEFT, RIGHT};

using std::ostream;
using std::istream;
using std::setw;
using std::endl;

template <typename data_type>
class node
{
public:
    node(const data_type &D = data_type(), size_t C = 1);
    ~node();

    node(const node<data_type> &other);
    node<data_type>& operator=(const node<data_type> &other);
    node<data_type>& operator=(const data_type &other);

    data_type& data();
    const data_type& data() const;

    size_t& count();
    const size_t& count() const;

    size_t &child(bool which);
//    const size_t& child(bool which) const;

    node<data_type>& operator+=(size_t v);

    node<data_type>& operator-=(size_t v);

    int operator++();
    int operator++(int);

    int operator--();
    int operator--(int);

    //    // Traversals
    //    static void preorder(ostream& outs, node<data_type>* r, size_t indent = 0);

    //    static void inorder(ostream& outs, node<data_type>* r, size_t indent = 0);

    //    static void postorder(ostream& outs, node<data_type>* r, size_t indent = 0);

    //    static void (*trav_ptr[3])(ostream&, node<data_type>*, size_t);


    // Node to Node comparisons

    template <typename D>
    friend
    bool operator==(const node<D>& x, const node<D>& y);

    template <typename D>
    friend
    bool operator!=(const node<D>& x, const node<D>& y);

    template <typename D>
    friend
    bool operator<(const node<D>& x, const node<D>& y);

    template <typename D>
    friend
    bool operator>(const node<D>& x, const node<D>& y);

    template <typename D>
    friend
    bool operator<=(const node<D>& x, const node<D>& y);

    template <typename D>
    friend
    bool operator>=(const node<D>& x, const node<D>& y);


    // Node to Data Comparisons

    template <typename D>
    friend
    bool operator==(const node<D>& x, const D& y);

    template <typename D>
    friend
    bool operator!=(const node<D>& x, const D& y);

    template <typename D>
    friend
    bool operator<(const node<D>& x, const D& y);

    template <typename D>
    friend
    bool operator>(const node<D>& x, const D& y);

    template <typename D>
    friend
    bool operator<=(const node<D>& x, const D& y);

    template <typename D>
    friend
    bool operator>=(const node<D>& x, const D& y);


    // Data to Node Comparisons

    template <typename D>
    friend
    bool operator==(const D& x, const node<D>& y);

    template <typename D>
    friend
    bool operator!=(const D& x, const node<D>& y);

    template <typename D>
    friend
    bool operator<(const D& x, const node<D>& y);

    template <typename D>
    friend
    bool operator>(const D& x, const node<D>& y);

    template <typename D>
    friend
    bool operator<=(const D& x, const node<D>& y);

    template <typename D>
    friend
    bool operator>=(const D& x, const node<D>& y);


    // iostream

    template <typename D>
    friend
    istream& operator>>(istream& ins, node<D>& n);

    template <typename D>
    friend
    ostream& operator<<(ostream& outs, const node<D>& n);


private:
    data_type thedata;
    size_t thecount, children[2];
};


template <typename data_type>
node<data_type>::node(const data_type &D, size_t C)
{
    thedata = D;
    thecount = C;
    children[0] = children[1] = 0;
}

template <typename data_type>
node<data_type>::~node()
{
    thedata = data_type();
    thecount = 0;
    children[0] = children[1] = 0;
}

template <typename data_type>
node<data_type>::node(const node<data_type> &other)
{
    thedata = other.thedata;
    thecount = other.thecount;
    children[0] = other.children[0];
    children[1] = other.children[1];
}

template <typename data_type>
node<data_type>& node<data_type>::operator=(const node<data_type> &other)
{
    if (this != &other)
    {
        thedata = other.thedata;
        thecount = other.thecount;
        children[0] = other.children[0];
        children[1] = other.children[1];
    }
    return *this;
}

template <typename data_type>
node<data_type>& node<data_type>::operator=(const data_type &other)
{

    thedata = other;
    thecount = 1;
    children[0] = children[1] = 0;
    return *this;
}

template <typename data_type>
data_type& node<data_type>::data()
{
    return thedata;
}

template <typename data_type>
const data_type& node<data_type>::data() const
{
    return thedata;
}

template <typename data_type>
size_t& node<data_type>::count()
{
    return thecount;
}

template <typename data_type>
const size_t& node<data_type>::count() const
{

    return thecount;
}

template <typename data_type>
size_t &node<data_type>::child(bool which)
{
    return children[which];
}

//template <typename data_type>
//const size_t &node<data_type>::child(bool which) const
//{
//    return children[which];
//}

template <typename data_type>
node<data_type>& node<data_type>::operator+=(size_t v)
{
    thecount += v;
    return *this;
}

template <typename data_type>
node<data_type>& node<data_type>::operator-=(size_t v)
{
    thecount -= v;
    return *this;
}

template <typename data_type>
int node<data_type>::operator++()
{
    thecount++;
    return thecount;
}

template <typename data_type>
int node<data_type>::operator++(int)
{
    int temp = thecount;
    thecount++;
    return temp;
}

template <typename data_type>
int node<data_type>::operator--()
{
    thecount--;
    return thecount;
}

template <typename data_type>
int node<data_type>::operator--(int)
{
    int temp = thecount;
    thecount--;
    return temp;
}

//template <typename data_type>
//void node<data_type>::preorder(ostream& outs, node<data_type>* r, size_t indent)
//{
//    if (r)
//    {
//        outs<<setw(indent)<<""<<r->data()<<" ["<<r->count()<<"] "<<endl;
//        preorder(outs, r->children[LEFT], indent+4);
//        preorder(outs, r->children[RIGHT],indent+4);
//    }
//}

//template <typename data_type>
//void node<data_type>::inorder(ostream& outs, node<data_type>* r, size_t indent)
//{
//    if (r)
//    {
//        inorder(outs, r->children[LEFT], indent+4);
//        outs<<setw(indent)<<""<<r->data()<<" ["<<r->count()<<"] "<<endl;
//        inorder(outs, r->children[RIGHT], indent+4);
//    }
//}

//template <typename data_type>
//void node<data_type>::postorder(ostream& outs, node<data_type>* r, size_t indent)
//{
//    if (r)
//    {
//        postorder(outs, r->children[LEFT], indent+4);
//        postorder(outs, r->children[RIGHT], indent+4);
//        outs<<setw(indent)<<""<<r->data()<<" ["<<r->count()<<"] "<<endl;
//    }
//}

//template <typename data_type>
//void (*node<data_type>::trav_ptr[])(ostream&, node<data_type>*, size_t) = {&node<data_type>::preorder, &node<data_type>::inorder, &node<data_type>::postorder};


// Node to Node comparisons

template <typename D>
bool operator==(const node<D>& x, const node<D>& y)
{
    return x.thedata == y.thedata;
}

template <typename D>
bool operator!=(const node<D>& x, const node<D>& y)
{
    return x.thedata != y.thedata;
}

template <typename D>
bool operator<(const node<D>& x, const node<D>& y)
{
    return x.thedata < y.thedata;
}

template <typename D>
bool operator>(const node<D>& x, const node<D>& y)
{
    return x.thedata > y.thedata;
}

template <typename D>
bool operator<=(const node<D>& x, const node<D>& y)
{
    return x.thedata <= y.thedata;
}

template <typename D>
bool operator>=(const node<D>& x, const node<D>& y)
{
    return x.thedata >= y.thedata;
}


// Node to Data Comparisons

template <typename D>
bool operator==(const node<D>& x, const D& y)
{
    return x.thedata == y;
}

template <typename D>
bool operator!=(const node<D>& x, const D& y)
{
    return x.thedata != y;
}

template <typename D>
bool operator<(const node<D>& x, const D& y)
{
    return x.thedata < y;
}

template <typename D>
bool operator>(const node<D>& x, const D& y)
{
    return x.thedata > y;
}

template <typename D>
bool operator<=(const node<D>& x, const D& y)
{
    return x.thedata <= y;
}

template <typename D>
bool operator>=(const node<D>& x, const D& y)
{
    return x.thedata >= y;
}


// Data to Node Comparisons

template <typename D>
bool operator==(const D& x, const node<D>& y)
{
    return x == y.thedata;
}

template <typename D>
bool operator!=(const D& x, const node<D>& y)
{
    return x != y.thedata;
}

template <typename D>
bool operator<(const D& x, const node<D>& y)
{
    return x < y.thedata;
}

template <typename D>
bool operator>(const D& x, const node<D>& y)
{
    return x > y.thedata;
}

template <typename D>
bool operator<=(const D& x, const node<D>& y)
{
    return x <= y.thedata;
}

template <typename D>
bool operator>=(const D& x, const node<D>& y)
{
    return x >= y.thedata;
}


// iostream

template <typename D>
istream& operator>>(istream& ins, node<D>& n)
{
    D temp;
    ins >> temp;
    n = node<D>(temp);
    return ins;
}

template <typename D>
ostream& operator<<(ostream& outs, const node<D>& n)
{
    outs<<n.thedata << " ["<<n.thecount<<"], ";
    return outs;
}

#endif // NODE
