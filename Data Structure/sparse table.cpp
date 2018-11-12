int M[100002][18];
void process()
  {
      int i, j;

  //initialize M for the intervals with length 1
      for (i = 0; i < n; i++)
          M[i][0] = i;
  //compute values from smaller to bigger intervals
      for (j = 1; 1 << j <= n; j++)
          for (i = 0; i + (1 << j) - 1 < n; i++)
              if (arr[M[i][j - 1]] < arr[M[i + (1 << (j - 1))][j - 1]])
                  M[i][j] = M[i][j - 1];
              else
                  M[i][j] = M[i + (1 << (j - 1))][j - 1];
  }

  int rmq(int i,int j)
  {
        int k=log2(j-i+1);
        return min(arr[M[i][k]],arr[M[j-(1<<k)+1][k]]);
  }
