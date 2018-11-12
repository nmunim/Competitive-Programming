// convex hull trick, lower envelop building
// always convert the problem to lowest value query type
// slope is inserted in decreasing order. If increasing order needed,
// replace < in bad function with >, and use ternary search for query
// pointer walk only works when after every update, a query is made and x value is non-decreasing
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int pointer;
vector<long long> M;
vector<long long> B;

//Returns true if either line l1 or line l3 is always better than line l2
bool bad(int l1,int l2,int l3)
{
    /*
    intersection(l1,l2) has x-coordinate (b1-b2)/(m2-m1)
    intersection(l1,l3) has x-coordinate (b1-b3)/(m3-m1)
    set the former greater than the latter, and cross-multiply to
    eliminate division
    */
    return (B[l3]-B[l1])*(M[l1]-M[l2])<(B[l2]-B[l1])*(M[l1]-M[l3]);
}

//Adds a new line (with lowest slope) to the structure
void add(long long m,long long b)
{
    M.push_back(m);
    B.push_back(b);
    while (M.size()>=3&&bad(M.size()-3,M.size()-2,M.size()-1))
    {
        M.erase(M.end()-2);
        B.erase(B.end()-2);
    }
}
//Returns the minimum y-coordinate of any intersection between a given vertical
//line and the lower envelope
long long query(long long x)
{
    if (pointer>=M.size())
        pointer=M.size()-1;
    while (pointer<M.size()-1&&
      M[pointer+1]*x+B[pointer+1]<M[pointer]*x+B[pointer])
        pointer++;
    return M[pointer]*x+B[pointer];
}
int main()
{
    long long cost;
    add(rect[0].second,0);
    //initially, the best line could be any of the lines in the envelope,
    //that is, any line with index 0 or greater, so set pointer=0
    pointer=0;
    for (int i=0; i<N; i++) //discussed in article
    {
        cost=query(rect[i].first);
        if (i<N)
            add(rect[i+1].second,cost);
    }
    printf("%lld\n",cost);
    return 0;
}
