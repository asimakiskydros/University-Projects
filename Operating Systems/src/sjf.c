#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
} process;

void SJFnp (const process* proc, int length){
    int time = 0, i = 0, remaining_time[length], finished_processes = 0;

    //array initialization
    for (int h = 0; h < length; h++) remaining_time[h] = proc[h].burst_time;
    //wait until the first process arrives
    while (proc[0].arrival_time > time) time++;

    while (finished_processes < length){
        while(remaining_time[i]-- > 0){
            printf("%d\n", proc[i].pid);
            time++;
        }
        finished_processes++;
        remaining_time[i] = INT_MAX;
        //find the process that ends sooner to be selected next
        for (int j = 0; j < length; j++)
            if (proc[j].arrival_time <= time && remaining_time[j] < remaining_time[i]) i = j;
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

    SJFnp(arr, n);

    free(arr);
    return 0; /* DO NOT EDIT THIS LINE */
}
