#include <stdio.h>
#include <limits.h>
int MatrixChainOrder(int p[], int n)
{
 
    int i, j, k, L, q;
    int m[n][n];
    // cost is zero when multiplying one matrix.
    for (i = 1; i < n; i++)
        m[i][i] = 0;
 
    // L is chain length.
    for (L = 2; L < n; L++)
    {
        for (i = 1; i < n - L + 1; i++)
        {
            j = i + L - 1;
            m[i][j] = INT_MAX;
            for (k = i; k <= j - 1; k++)
            {
                q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j])
                    m[i][j] = q;
            }
        }
    }
 
    return m[1][n - 1];
}
int main()
{
    int n;
    printf("Enter the size of array:");
    scanf("%d",&n);
    int a[n];
    printf("Enter array elements:");
    for(int i=0;i<n;i++)
    {
	scanf("%d ",&a[i]);
    }
    printf("Minimum number of multiplications are: %d ",MatrixChainOrder(a,n));
    return 0;
}