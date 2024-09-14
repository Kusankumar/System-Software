/*
============================================================================
Name : Q2.c
Author : Sonu Kumar Mahto

Description--------------------------
Write a simple program to execute in an infinite loop at the background. Go to /proc directory and identify all the process related information in the corresponding proc directory.


Date: 30th Aug, 2024.
============================================================================*/

#include<stdio.h>
#include<stdio.h>
#include<unistd.h>

int main(void){
  while(1){
    printf("Hi what's up?\n");
  }
}
/*
Output----------------------------------------------------------------------------
sonu2030@sonu152:/proc/3961$ ls
arch_status         fd                 net            setgroups
attr                fdinfo             ns             smaps
autogroup           gid_map            numa_maps      smaps_rollup
auxv                io                 oom_adj        stack
cgroup              ksm_merging_pages  oom_score      stat
clear_refs          ksm_stat           oom_score_adj  statm
cmdline             limits             pagemap        status
comm                loginuid           patch_state    syscall
coredump_filter     map_files          personality    task
cpu_resctrl_groups  maps               projid_map     timens_offsets
cpuset              mem                root           timers
cwd                 mountinfo          sched          timerslack_ns

*/
