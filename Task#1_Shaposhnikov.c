#include <stdio.h>
int main()
    {
        int s[28], i, j, k, res;
        for (i=0; i<28; ++i)
        {
            s[i]=0;
        }
        for (i=0; i<10; ++i)
            {
                for (j=0; j<10; ++j)
                {
                    for (k=0; k<10; ++k)
                        {
                            ++s[i+j+k];
                        }
                }
            }
        res=0;
        for (i=0; i<28; ++i)
            {

                res+=s[i]*s[i];
            }
        printf("%d", res);
        return 0;
    }
