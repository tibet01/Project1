#include <iostream>
#include <math.h>
using namespace std;
struct num
{
    float x[11];
    float y[11];
};

int main()
{
    struct num num;
    float m = 0, mt, a, b;
    for (int i = 0; i < 10; i++)
    {
        scanf_s("%f,%f", &num.x[i], &num.y[i]);
    }
    for (int i = 0; i < 10; i++)
    {
        for (int j = i + 1; j < 10; j++)
        {
            mt = sqrt((num.x[i] - num.x[j]) * (num.x[i] - num.x[j]) + (num.y[i] - num.y[j]) * (num.y[i] - num.y[j]));
            if (mt > m)
            {
                m = mt;
                a = i;
                b = j;
            }
        }
    }
    cout << a + 1 << " and " << b + 1 << " max distance is " << m;
    return 0;
}
