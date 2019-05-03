#include "noc.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *router(void *arg)
{
    pthread_mutex_lock(&mutex);
    int id = *((int *) arg);

    for (int i = 0; i < num_lines; i++) {
        if (pe.x[id] != src.x[i] || pe.y[id] != src.y[i]) {
            continue;
        }
        else {
            while (src.x[i] != tgt.x[i]) {
                if (tgt.x[i] > pe.x[id]) {
                    src.x[i] += 1;
                    right[id] = right[id] + 1;
                    printf("Router %d%d sent message to East (%d%d).\n", src.x[i - 1], src.y[i - 1], src.x[i], src.y[i]);
                }
                else if (tgt.x[i] < pe.x[id]) {
                    src.x[i] -= 1;
                    left[id] = left[id] + 1;
                    printf("Router %d%d sent message to West (%d%d).\n", src.x[i + 1], src.y[i + 1], src.x[i], src.y[i]);  
                }
            }
            while (src.y[i] != tgt.y[i]) {
                if (tgt.y[i] > pe.y[id]) {
                    src.y[i] += 1;
                    top[id] = top[id] + 1;
                    printf("Router %d%d sent message sent to North (%d%d).\n", src.x[i - 1], src.y[i - 1], src.x[i], src.y[i]);  
                }
                else if (tgt.y[i] < pe.y[id]) {
                    src.y[i] -= 1;
                    bottom[id] = bottom[id] + 1;
                    printf("Router %d%d sent message sent to South (%d%d).\n", src.x[i + 1], src.y[i + 1], src.x[i], src.y[i]);  
                }
            }

            count_mes[id] = count_mes[id] + 1;
        }
    }

    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

void *processor(void *arg)
{
    pthread_mutex_lock(&mutex);

    for (int i = 0; i < num_lines; i++) {
        for (int j = 0; j < num_lines; j++) {
            if (pe.x[j] == tgt.x[i] && pe.y[j] == tgt.y[i]) {
                printf("Processor %d%d: %s\n", pe.x[j], pe.y[j], data.str[i]);
            }
        }
    }

    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}
