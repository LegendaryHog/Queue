#include "Queue.h"

size_t que_num = 0;
FILE*  logfile = NULL;

int Q_Ctor (queue* que)
{
    que->data     = (data_t*) calloc (CAPACITY_0, sizeof (data_t));
    que->capacity = CAPACITY_0;
    que->size     = 0;
    que->head     = 0;
    que->tail     = 0;
    que->ctored   = 1;

    que_num++;

    if (que_num == 1)
    {
        logfile = fopen ("logfile.txt", "w");
    }

    return NO_ERR;
}

int Q_Dtor (queue* que)
{
    if (que->ctored != 1)
    {
        fprintf (logfile, "You can't destrust queue, which you didn't construct\n, addres of queue: %p\n", que);
        return ERR;
    }
    que_num--;
    if (que_num == 0)
    {
        fclose (logfile);
    }

    free (que->data);

    return NO_ERR;
}

int Q_Resize (queue* que, int mode)
{
    if (mode == UP)
    {
        que->capacity *= 2;
        if (que->head >= que->tail)
        {
            que->data = (data_t*) realloc (que->data, que->capacity * sizeof (data_t));
            for (size_t i = que->capacity/2; i < que->capacity; i++)
            {
                que->data[i] = 0;
            }
            return NO_ERR;
        }
        else
        {
            data_t* tmp_data = (data_t*) calloc (que->capacity, sizeof (data_t));

            memcpy (tmp_data, que->data, (que->head + 1)  * sizeof (data_t));

            memcpy (tmp_data + que->tail + que->capacity/2, que->data + que->tail, (que->size - que->head - 1) * sizeof (data_t));

            free (que->data);

            que->data = tmp_data;

            que->tail += que->capacity/2;

            return NO_ERR;
        }
    }
    else
    {
        que->capacity /= 2;
        if (que->head >= que->tail)
        {
            data_t* tmp_data = (data_t*) calloc (que->capacity, sizeof (data_t));

            memcpy (tmp_data, que->data + que->tail, que->size * sizeof (data_t));

            free (que->data);

            que->data = tmp_data;

            que->head -= que->tail;
            que->tail  = 0;

            return NO_ERR;
        }
        else
        {
            memcpy (que->data + que->tail - que->capacity, que->data + que->tail, (2*que->capacity - que->tail)*sizeof (data_t));

            que->tail -= que->capacity;

            que->data = (data_t*) realloc (que->data, que->capacity * sizeof (data_t));

            return NO_ERR;
        }
    }
}

int Q_Push_Front (queue* que, double push)
{
    if (que->size == que->capacity)
    {
        Q_Resize (que, UP);
    }

    if (que->size != 0)
    {
        que->head = (que->head + 1)%que->capacity;
    }

    que->data[que->head] = push;
    que->size++;

    return NO_ERR;
}

int Q_Push_Back (queue* que, double push)
{
    if (que->size == que->capacity)
    {
        Q_Resize (que, UP);
    }

    if (que->size != 0)
    {
        que->tail = (que->tail + que->capacity - 1)%que->capacity;
    }
    que->data[que->tail] = push;
    que->size++;

    return NO_ERR;
}

double Q_Pop_Front (queue* que)
{
    if (que->size <= que->capacity/2 - 3 && que->capacity/2 >= CAPACITY_0)
    {
        Q_Resize (que, DOWN);
    }

    if (que->size == 0)
    {
        fprintf (logfile, "Queue underflow\n");
    }
    que->size--;
    double pop = que->data[que->head];
    que->data[que->head] = 0;
    que->head = (que->head + que->capacity - 1)%que->capacity;
    return pop;
}

double Q_Pop_Back (queue* que)
{
    if (que->size <= que->capacity/2 - 3 && que->capacity/2 >= CAPACITY_0)
    {
        Q_Resize (que, DOWN);
    }

    if (que->size == 0)
    {
        fprintf (logfile, "Queue underflow\n");
    }
    que->size--;
    double pop = que->data[que->tail];
    que->data[que->tail] = 0;
    que->tail = (que->tail + 1)%que->capacity; 
    return pop;
}

int Q_Dump (queue* que)
{
    fprintf (logfile, "Queue [%p]:\n", que);
    if (que == NULL)
    {
        return ERR;
    }
    
    fprintf (logfile, "\tcapacity = %zd\n\tsize = %zd\n\thead = %zd\n\ttail = %zd\n", que->capacity, que->size, que->head, que->tail);
    fprintf (logfile, "\tdata [%p]:\n", que->data);

    if (que->data == NULL)
    {
        return ERR;
    }

    for (size_t i = 0; i < que->capacity; i++)
    {
        if ((i < que->head && i > que->tail && que->head >= que->tail) || ((i > que->tail || i < que->head) && que->head < que->tail))
        {
            fprintf (logfile, "\t\t*[%3zd] = %lf\n", i, que->data[i]);
        }
        else if (i == que->head && i == que->tail)
        {
            fprintf (logfile, "\t\t>[%3zd] = %lf<head/tail pop\n", i, que->data[i]);
        }
        else if (i == que->head)
        {
            fprintf (logfile, "\t\t>[%3zd] = %lf<head pop\n", i, que->data[i]);
        }
        else if (i == que->tail)
        {
            fprintf (logfile, "\t\t>[%3zd] = %lf<tail pop\n", i, que->data[i]);
        }
        else
        {
            fprintf (logfile, "\t\t [%3zd] = %lf\n", i, que->data[i]);
        }
    }
    return NO_ERR;
}