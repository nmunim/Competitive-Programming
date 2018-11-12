
/// Minimum number of knight moves from (x,y) to (0,0) in non-negative infinite chessboard
int knight_move(int x, int y){
    int a, b, z, c, d;
    x = abs(x), y = abs(y);
    if (x < y) a = x, x = y, y = a;
    if (x == 2 && y == 2) return 4;
    if (x == 1 && y == 0) return 3;

    if (y == 0 || (y << 1) < x){
        c = y & 1;
        a = x - (c << 1), b = a & 3;
        return ((a - b) >> 1) + b + c;
    }
    else{
        d = x - ((x - y) >> 1);
        z = ((d % 3) != 0), c = (x - y) & 1;
        return ((d / 3) * 2) + c + (z * 2 * (1 - c));
    }
}

