//pick's theorem

#include <bits/stdtr1c++.h>

using namespace std;

struct Point{
    long long x, y;
    Point(){}
    Point(long long x, long long y) : x(x), y(y){}
};

/// twice the area of polygon
long long double_area(Point poly[], int n){
    long long res = 0;
    for (int i = 0, j = n - 1; i < n; j = i++){
        res += ((poly[j].x + poly[i].x) * (poly[j].y - poly[i].y));
    }
    return abs(res);
}

/// number of lattice points strictly on polygon border
long long on_border(Point poly[], int n){
    long long res = 0;
    for (int i = 0, j = n - 1; i < n; j = i++){
        res += __gcd(abs(poly[i].x - poly[j].x), abs(poly[i].y - poly[j].y));
    }
    return res;
}

/// number of lattice points strictly inside polygon
long long interior(Point poly[], int n){
    long long res = 2 + double_area(poly, n) - on_border(poly, n);
    return res / 2;
}

int main(){
    Point ar[10];
    ar[0] = Point(0, 0);
    ar[1] = Point(3, 0);
    ar[2] = Point(3, 3);
    ar[3] = Point(0, 3);

    dbg(on_border(ar, 4)); /// 12
    dbg(interior(ar, 4)); /// 4
    return 0;
}
