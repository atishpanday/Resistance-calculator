#ifndef COFACTOR
#define COFACTOR

void getCofactor(std::vector<std::vector<float>>& A, std::vector<std::vector<float>>& temp, int p, int q, int n)
{
    int i = 0, j = 0;
 
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if (row != p && col != q)
            {
                temp[i][j++] = A[row][col];
                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

#endif
