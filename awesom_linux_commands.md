htop

# thread monitoring commands
![thread monitoring](image.png)


# types of context switch and how to monitor them
![types of context switch and how to monitor them](image-1.png)

pidstat -w 1
perf stat -e sched:sched_migrate_task -a -- sleep 5
perf stat -e syscalls:sys_enter -a -- sleep 5
