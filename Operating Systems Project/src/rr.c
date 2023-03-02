#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
} process;

//queue operations
char queue_is_empty (const int *);
int queue_extract_front (int *, int);
void queue_append (int, int *, int);

void RR (const process* proc, int length, int q){
    int time = 0, j = 1, current_process, remaining_time[length + 1], queue[length];
    char check_finished;

    //array initialization
    for (int h = 1; h < length + 1; h++) remaining_time[h] = proc[h - 1].burst_time;
    //queue initialization
    for (int h = 0; h < length; h++) queue[h] = -1;
    //wait until the first process arrives
    while (proc[0].arrival_time > time) time++;
    //insert the first process to the queue
    queue[0] = proc[0].pid;

    while (!queue_is_empty(queue)){
        //run the process for q units of time or until it finishes
        current_process = queue_extract_front(queue, length);
        check_finished = 0;
        for (int i = 0; i < q && !check_finished; i++) {
            printf("%d\n", current_process);
            if (--remaining_time[current_process] == 0) check_finished = 1;

            //newly arrived processes are added to the queue
            if (j < length && proc[j].arrival_time == ++time) {
                queue_append(proc[j].pid, queue, length);
                //this variable tracks how many unique processes have been added to the queue
                //it prevents duplicates and potential overflow of the queue array
                j++;
            }
        }
        //if the previous process didn't finish in the given time, append it to the queue
        if (!check_finished) queue_append(current_process, queue, length);
    }
}

int main() {

    /* read in data - DO NOT EDIT (START) */
    int n;
    int quantum;
    scanf("%d", &n);
    scanf("%d", &quantum);
    process *arr;
    arr = malloc(n * sizeof(process));
    for (int i = 0; i < n ; ++i) {
        scanf("%d", &arr[i].pid);
        scanf("%d", &arr[i].arrival_time);
        scanf("%d", &arr[i].burst_time);
    }
    /* read in data - DO NOT EDIT (END) */

    RR(arr, n, quantum);

    free(arr);
    return 0; /* DO NOT EDIT THIS LINE */
}

char queue_is_empty (const int* queue){
    //a queue position is labeled "empty" if it stores -1
    //a queue is empty if its front is empty
    if (queue[0] == -1) return 1;
    else return 0;
}
int queue_extract_front (int* queue, int length){
    //get the front of the queue
    int ret = queue[0];
    //left shift the entire table by one
    for (int i = 0; i < length - 1; i++) queue[i] = queue[i + 1];
    //label the end as empty
    queue[length - 1] = -1;
    return ret;
}
void queue_append(int element, int* queue, int length){
    int i;
    //find the first empty spot, checking from front to back
    for (i = 0; i < length; i++) if (queue[i] == -1) {
        //if the queue has available space, append the given element
        queue[i] = element;
        return;
    }
}