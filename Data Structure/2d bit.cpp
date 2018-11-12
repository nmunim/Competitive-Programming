
void update(int x , int y , int val)
{
    int y1;
    while (x <= max_x)
    {
        y1 = y;
        while (y1 <= max_y)
        {
            tree[x][y1] += val;
            y1 += (y1 & -y1);
        }
        x += (x & -x);
    }
}

int query(int x,int y)   // return sum from 1,1 to x,y.
{
    int sum= 0;
    while( x)
    {
        int y1 = y;
        while(y1)
        {
            sum += tree[x][y1];
            y1 -= y1 & -y1;
        }
        x -= x & -x;
    }
    return sum;
}
