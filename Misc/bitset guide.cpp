#include <bits/stdc++.h>
using namespace std;

int main()
{
    // bitmask is indexed from 0 from least significant bit
    // all and to_ullong is c++11 feature, ulong can be used instead of ullong

    // declaring
    bitset<6>bb;

    // input
    cin>>bb;

    // check if all or any or none of bb is 1
    cout<<bb.all()<<" "<<bb.any()<<" "<<bb.none()<<"\n";

    //count number of 1's
    cout<<bb.count()<<" "<<bb.size()-bb.count()<<"\n";

    // flip all or single bit
    bb.flip();
    cout<<bb<<"\n";
    cout<<bb.flip(2)<<"\n";

    // operator[]
    bb[1]=bb[0]=0;
    cout<<bb[0]<<" "<<bb<<"\n";

    // reset or set all bits
    bb.reset();
    cout<<bb<<"\n";
    bb.set();
    cout<<bb<<"\n";

    // to unsigned long long int
    cout<<bb.to_ullong()<<"\n";

    // bitwise operators
    bb&=bb<<2;
    cout<<bb<<"\n";

    // find first set bit, returns bb.size() if there is none
    cout<<bb._Find_first()<<"\n";

    //get next set bit after a certain index, returns bb.size() if there is none
    cout<<bb._Find_next(3)<<"\n";

    return 0;
}
