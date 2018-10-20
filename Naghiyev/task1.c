#include <stdio.h>

int main() {
    int summa[28] = {0};
    long biletiki = 0;
    for (int a = 0; a < 10; a++)
    {
        for (int j = 0; j< 10; j++)
        {
            for (int l = 0; l < 10; l++)
            {
                summa[a + j + l]++;
            }
        }
    }
    for (int a = 0; a < 28; a++)
    {
        biletiki += summa[a] * summa[a];
    }
    printf("chislo biletov: %u", biletiki);
    system("pause"); 
    return 0;
}
