#include <stdio.h>
#include <stdlib.h>

// 定義鏈表節點結構
typedef struct node_s {
    int machine;
    int time;
    struct node_s* next;
} node_t;

// 定義工序結構
typedef struct {
    node_t* head; // 工序鏈表的頭
    node_t* tail; // 工序鏈表的尾
    int num_ops; // 工序數量
} job_t;

// 定義機器的可用時間結構
typedef struct {
    int available_time;
} machine_t;

// 函數宣告
int MAX(int a, int b) { return (a > b) ? (a) : (b);};


// 新增工序到工作
void add_operation(job_t* job, int machine, int time) {
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    new_node->machine = machine;
    new_node->time = time;
    new_node->next = NULL;

    if (job->head == NULL) {
        job->head = new_node;
    } else {
        job->tail->next = new_node;
    }
    job->tail = new_node;
    job->num_ops++;
}

// 工序排程
int schedule_jobs(job_t jobs[], int job_count, machine_t machines[], int machine_count) {
    int job_completion_times[job_count];
    for (int i = 0; i < job_count; i++) {
        job_completion_times[i] = 0;
    }

    int completed_jobs = 0;
    int earliest_completion_time;
    int selected_job;
    node_t* selected_op;

    while (completed_jobs < job_count) {
        earliest_completion_time = -1;
        selected_job = -1;
        selected_op = NULL;

        for (int i = 0; i < job_count; i++) {
            if (jobs[i].head == NULL) {
                continue; // 工作已經完成
            }

            node_t* op = jobs[i].head;
            int machine = op->machine;
            int start_time = MAX(job_completion_times[i], machines[machine].available_time);
            int completion_time = start_time + op->time;

            if (earliest_completion_time == -1 || completion_time < earliest_completion_time) {
                earliest_completion_time = completion_time;
                selected_job = i;
                selected_op = op;
            }
        }

        // 排程選定的工序
        int machine = selected_op->machine;
        machines[machine].available_time = earliest_completion_time;
        jobs[selected_job].head = selected_op->next;
        if (jobs[selected_job].head == NULL) {
            completed_jobs++;
            job_completion_times[selected_job] = earliest_completion_time;
        } else {
            job_completion_times[selected_job] = earliest_completion_time;
        }

        free(selected_op);
    }

    int total_completion_time = 0;
    for (int i = 0; i < job_count; i++) {
        total_completion_time += job_completion_times[i];
    }

    return total_completion_time;
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    // 初始化工作和機器
    job_t jobs[M];
    machine_t machines[N];
    
    for (int i = 0; i < M; i++) {
        jobs[i].head = NULL;
        jobs[i].tail = NULL;
        jobs[i].num_ops = 0;

        int P;
        scanf("%d", &P);
        for (int j = 0; j < P; j++) {
            int machine, time;
            scanf("%d %d", &machine, &time);
            add_operation(&jobs[i], machine, time);
        }
    }

    for (int i = 0; i < N; i++) {
        machines[i].available_time = 0;
    }

    int total_completion_time = schedule_jobs(jobs, M, machines, N);
    printf("%d\n", total_completion_time);

    return 0;
}