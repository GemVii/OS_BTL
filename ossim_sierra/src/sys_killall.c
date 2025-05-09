// // // /*
// // //  * Copyright (C) 2025 pdnguyen of HCMC University of Technology VNU-HCM
// // //  */

// // // /* Sierra release
// // //  * Source Code License Grant: The authors hereby grant to Licensee
// // //  * personal permission to use and modify the Licensed Source Code
// // //  * for the sole purpose of studying while attending the course CO2018.
// // //  */

// // // #include "common.h"
// // // #include "syscall.h"
// // // #include "stdio.h"
// // // #include "libmem.h"

// // // int __sys_killall(struct pcb_t *caller, struct sc_regs* regs)
// // // {
// // //     char proc_name[100];
// // //     uint32_t data;

// // //     //hardcode for demo only
// // //     uint32_t memrg = regs->a1;
    
// // //     /* TODO: Get name of the target proc */
// // //     //proc_name = libread..
// // //     int i = 0;
// // //     data = 0;
// // //     while(data != -1){
// // //         libread(caller, memrg, i, &data);
// // //         proc_name[i]= data;
// // //         if(data == -1) proc_name[i]='\0';
// // //         i++;
// // //     }
// // //     printf("The procname retrieved from memregionid %d is \"%s\"\n", memrg, proc_name);

// // //     /* TODO: Traverse proclist to terminate the proc
// // //      *       stcmp to check the process match proc_name
// // //      */
// // //     //caller->running_list
// // //     //caller->mlq_ready_queu

// // //     /* TODO Maching and terminating 
// // //      *       all processes with given
// // //      *        name in var proc_name
// // //      */

// // //     return 0; 
// // // }



#include "common.h"
#include "syscall.h"
#include "stdio.h"
#include "string.h"
#include "libmem.h"

/* Sử dụng mảng procs và num_processes được định nghĩa ở os.c */
extern struct pcb_t *procs[];
extern int num_processes;

int __sys_killall(struct pcb_t *caller, struct sc_regs *regs)
{
    char proc_name[100];
    uint32_t data;
    uint32_t memrg = regs->a1;
    int i = 0;

    /* Đọc tên tiến trình từ vùng nhớ memrg */
    while (i < sizeof(proc_name)-1) {
        if (libread(caller, memrg, i, &data) != 0) 
            break;
        if (data == (uint32_t)-1 || data == 0) 
            break;
        proc_name[i++] = (char)data;
    }
    proc_name[i] = '\0';

    printf("[KILLALL] Retrieved name: \"%s\"\n", proc_name);

    int count = 0;
    /* Duyệt qua num_processes tiến trình hiện có */
    for (int j = 0; j < num_processes; j++) {
        if (procs[j] == NULL)
            continue;
        if (strcmp(procs[j]->path, proc_name) == 0) {
            printf("[KILLALL] Terminating PID %u (%s)\n",
                   procs[j]->pid, procs[j]->path);
            /* Mark process đã kết thúc */
            procs[j]->pc = procs[j]->code->size;
            count++;
        }
    }

    printf("[KILLALL] Total terminated: %d\n", count);
    return count;
}