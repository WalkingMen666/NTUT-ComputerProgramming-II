#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// 定义工序结构体
typedef struct {
    int machine;
    int time;
    int start_time;
} Operation;

// 定义工作结构体
typedef struct {
    int id;
    int num_operations;
    Operation* operations;
    int completion_time;
} Job;

// 获取最早完成时间最小的工序
int get_next_operation(Job jobs[], int num_jobs, int machine_availability[]) {
    int min_completion_time = INT_MAX;
    int selected_job_index = -1;
    int selected_operation_index = -1;

    for (int i = 0; i < num_jobs; i++) {
        Job *job = &jobs[i];
        // 查找第一个未排程的工序
        int operation_index = -1;
        for (int j = 0; j < job->num_operations; j++) {
            if (job->operations[j].start_time == -1) {
                operation_index = j;
                break;
            }
        }
        if (operation_index == -1) continue; // 所有工序都已经排程了

        Operation *op = &job->operations[operation_index];
        int prev_completion_time = operation_index > 0 ? job->operations[operation_index - 1].start_time + job->operations[operation_index - 1].time : 0;
        int start_time = machine_availability[op->machine] > prev_completion_time ? machine_availability[op->machine] : prev_completion_time;
        int completion_time = start_time + op->time;

        if (completion_time < min_completion_time || (completion_time == min_completion_time && job->id < jobs[selected_job_index].id)) {
            min_completion_time = completion_time;
            selected_job_index = i;
            selected_operation_index = operation_index;
        }
    }

    return selected_job_index;
}

int main() {
    int num_machines, num_jobs;
    scanf("%d %d", &num_machines, &num_jobs);

    Job jobs[num_jobs];
    int machine_availability[num_machines];
    for (int i = 0; i < num_machines; i++) machine_availability[i] = 0;

    // 读取所有工作的工序
    for (int i = 0; i < num_jobs; i++) {
        jobs[i].id = i;
        jobs[i].completion_time = 0;
        scanf("%d", &jobs[i].num_operations);
        jobs[i].operations = (Operation *) malloc(jobs[i].num_operations * sizeof(Operation));
        for (int j = 0; j < jobs[i].num_operations; j++) {
            int machine, time;
            scanf("%d %d", &machine, &time);
            jobs[i].operations[j].machine = machine;
            jobs[i].operations[j].time = time;
            jobs[i].operations[j].start_time = -1; // 尚未排程
        }
    }

    // 按照规则进行排程
    int total_completion_time = 0;
    for (int i = 0; i < num_jobs; i++) {
        for (int j = 0; j < jobs[i].num_operations; j++) {
            int next_job_index = get_next_operation(jobs, num_jobs, machine_availability);
            Job *job = &jobs[next_job_index];
            Operation *op = NULL;
            for (int k = 0; k < job->num_operations; k++) {
                if (job->operations[k].start_time == -1) {
                    op = &job->operations[k];
                    break;
                }
            }

            int prev_completion_time = op == job->operations ? 0 : job->operations[op - job->operations - 1].start_time + job->operations[op - job->operations - 1].time;
            op->start_time = machine_availability[op->machine] > prev_completion_time ? machine_availability[op->machine] : prev_completion_time;
            machine_availability[op->machine] = op->start_time + op->time;

            // 更新工作完成时间
            if (op == &job->operations[job->num_operations - 1]) {
                job->completion_time = op->start_time + op->time;
                total_completion_time += job->completion_time;
            }
        }
    }

    printf("%d\n", total_completion_time);

    for (int i = 0; i < num_jobs; i++) {
        free(jobs[i].operations);
    }

    return 0;
}
