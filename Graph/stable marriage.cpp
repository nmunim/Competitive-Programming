// sorted according to girl's preference

// boy[][],girl[][] lists partners in order of their preferences


int n,boy[1002][1002],girl[1002][1002],firstof[1002],engagedgirl[1002],ans[1002],whereboy[1002][1002];

void stablemarriage()
{
    queue<int>q;
    REP(i,1,n){q.push(i);firstof[i]=1;}
    MEM(engagedgirl,-1);
    REP(i,1,n)
    {
        REP(j,1,n)whereboy[i][boy[i][j]]=j;
    }
    while(!q.empty())
    {
        int curgirl=q.front();
        q.pop();
        int curboy=girl[curgirl][firstof[curgirl]];
        if(engagedgirl[curboy]!=-1)
        {
            if(whereboy[curboy][engagedgirl[curboy]]>whereboy[curboy][curgirl])
            {
                firstof[engagedgirl[curboy]]++;
                q.push(engagedgirl[curboy]);
                engagedgirl[curboy]=curgirl;
            }
            else
            {
                firstof[curgirl]++;
                q.push(curgirl);
            }
        }
        else engagedgirl[curboy]=curgirl;
    }
    REP(i,1,n)ans[engagedgirl[i]]=i;
}

