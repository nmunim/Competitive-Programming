// nlogn line sweep algorithm to find closest pair of points in a given set of points
//following code solves spoj CLOPPAIR


int n;

struct PT
{
    double xx,yy;
    int ind;
}p;

bool operator <(PT a,PT b)
{
    if(a.yy==b.yy)return a.xx<b.xx;
    return a.yy<b.yy;
}


bool comp(PT a,PT b)
{
    if(a.xx==b.xx)return a.xx<b.xx;
    return a.yy<b.yy;
}

typedef tree<
PT,
null_type,
less<PT>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;

double dist(PT a,PT b)
{
    return sqrt((a.xx-b.xx)*(a.xx-b.xx)+(a.yy-b.yy)*(a.yy-b.yy));
}

vector<PT> points;

ordered_set s;

int main()
{
    scanf("%d",&n);
    REP(i,0,n-1)
    {
        scanf("%lf %lf",&p.xx,&p.yy);
        p.ind=i;
        points.PB(p);
    }
    sort(ALL(points),comp);
    double minval=1e20;
    int ind1, ind2;
    int ptr=0;
    s.insert(points[0]);
    REP(i,1,n-1)
    {
        while(ptr<i && (points[i].xx-points[ptr].xx)>minval)
        {
            s.erase(points[ptr++]);
        }
        if(!s.empty())
        {
            p.xx=points[i].xx-minval;
            p.yy=points[i].yy-minval;
            int pos=s.order_of_key(p);
            while(pos<s.size())
            {
                auto it=s.find_by_order(pos);
                if((*it).yy>points[i].yy+minval)break;
                if(dist(*it,points[i])<minval)
                {
                    ind1=(*it).ind;
                    ind2=points[i].ind;
                    minval=dist(*it,points[i]);
                }

                pos++;
            }
        }

        s.insert(points[i]);
    }
    if(ind1>ind2)swap(ind1,ind2);
    printf("%d %d %.6f\n",ind1,ind2,minval);
    return 0;
}


