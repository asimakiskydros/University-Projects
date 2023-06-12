#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
} process;

void FCFS (const process* proc, int length){
    int remaining_time[length];

    //array initialization
    for (int h = 0; h < length; h++) remaining_time[h] = proc[h].burst_time;
    //linearly complete every arrived process
    for (int i = 0; i < length; i++)
        while(remaining_time[i]-- > 0) printf("%d\n", proc[i].pid);
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
    FCFS(arr, n);

    free(arr);
    return 0; /* DO NOT EDIT THIS LINE */
}
