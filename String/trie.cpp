#define MAX_NODE 100009

int node[MAX_NODE][26],root,nnode,isword[MAX_NODE];  // assuming only small case letters


void init()  //call before inserting any word into trie
{
    root=0;
    nnode=0;
    for(int i=0;i<26;i++)node[root][i]=-1;  // -1 means no edge for ('a'+i) th character
}

void insertword(string s)
{
    int len=s.size();
    int now=root;
    for(int i=0;i<len;i++)
    {
        if(node[now][s[i]-'a']==-1)
        {
            node[now][s[i]-'a']=++nnode;
            for(int j=0;j<26;j++)node[nnode][j]=-1;
        }
        now=node[now][s[i]-'a'];
    }
    isword[now]=1; //mark that a word ended here
}
