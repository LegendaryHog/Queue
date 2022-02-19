#include "Queue.h"

int main (void)
{
    queue* que = (queue*) calloc (1, sizeof (queue));

    Q_Ctor (que);
    Q_Dump (que);
    for (int i = 0; i < 100; i++)
    {
        Q_Push_Front (que, 10 + (double)i);
        Q_Dump (que);
    }

    Q_Dump (que);

    printf ("%lf\n", Q_Pop_Front (que));

    Q_Dump (que);

    for (int i = 0; i < 50; i++)
    {
        Q_Pop_Back (que);
    }

    for (int i = 0; i < 50; i++)
    {
        Q_Push_Front (que, 20);
    }

    Q_Dump (que);

    Q_Dtor (que);
    free (que);

    return 0;
}