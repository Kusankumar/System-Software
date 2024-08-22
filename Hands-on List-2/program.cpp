#include<stdio.h>
#include<iostream>
#include<unistd.h>

int main(void){
  while(1){
    printf("Hi what's up?\n");
  }
}
/*
Output----------------------------------------------------------------------------
rch_status         environ            mem            personality   status
attr                exe                mountinfo      projid_map    syscall
autogroup           fd                 mounts         root          task
auxv                fdinfo             mountstats     sched         timens_offsets
cgroup              gid_map            net            schedstat     timers
clear_refs          io                 ns             sessionid     timerslack_ns
cmdline             ksm_merging_pages  numa_maps      setgroups     uid_map
comm                ksm_stat           oom_adj        smaps         wchan
coredump_filter     limits             oom_score      smaps_rollup
cpu_resctrl_groups  loginuid           oom_score_adj  stack
cpuset              map_files          pagemap        stat
cwd                 maps               patch_state    statm
*/
