#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int empty(struct queue_t * q) {
        if (q == NULL) return 1;
	return (q->size == 0);
}

void enqueue(struct queue_t * q, struct pcb_t * proc) {
        /* TODO: put a new process to queue [q] */
        if (q == NULL || proc == NULL) 
        {
                return ;
        }

        if(q->size < MAX_QUEUE_SIZE)
        {
                q->proc[q->size] = proc;
                q->size++;
        }
}

struct pcb_t * dequeue(struct queue_t * q) {
        /* TODO: return a pcb whose prioprity is the highest
         * in the queue [q] and remember to remove it from q
         * */
        if(empty(q))    return NULL;

#ifdef MLQ_SCHED
        struct pcb_t *res = q->proc[0];
        for(int i = 0;i < q->size - 1;i++)
        {
                q->proc[i] = q->proc[i + 1];
        }
        q->size--;
#elif
        int best = 0;
        for (int i = 1; i < q->size; i++)
        {
                if (q->proc[i]->prio < q->proc[best]->prio)
                        best = i;
        }
        struct pcb_t *proc = q->proc[best];
        for (int i = best + 1; i < q->size; i++)
                q->proc[i - 1] = q->proc[i];
        q->size--;
return proc;
#endif
        
	return res;
}
void remove_from_queue(struct queue_t *q, struct pcb_t *proc)
{
        if (q == NULL || proc == NULL || q->size == 0)
        {
                printf("bug roi null pointer roi");
                return;
        }

#ifdef MLQ_SCHED
        for (int i = 0; i < q->size; i++)
        {
                if (q->proc[i] == proc)
                {
                        for (int j = i; j < q->size - 1; j++)
                        {
                                q->proc[j] = q->proc[j + 1];
                        }
                        q->size--;
                        return;
                }
        }
#endif
}
