🚀 Summary of Everything We Discussed About Concurrent Writes in Multi-Threading 🚀
1️⃣ Can Two Threads Write to the Same Variable at the Exact Same Time?
No, because each CPU core executes one instruction at a time.
But if two threads run on different cores, they can attempt to write at the same moment → This creates a race condition where one write might be lost.
2️⃣ What Happens If Two Threads Try to Write at the Same Time?
✅ Case 1: Same Core (No Problem)
The CPU switches between threads (context switching).
One thread writes first, then the other reads the updated value before writing again.
No race condition because writes are serialized naturally by the core.
❌ Case 2: Different Cores (Race Condition)
Step	Core 1 (Thread 1)	Core 2 (Thread 2)	Memory (odd)
t0	Reads odd = 1000	Reads odd = 1000	1000
t1	Increments (1001)	Increments (1001)	1000
t2	Writes 1001 to memory	Writes 1001 to memory	1001 ❌ (Update lost!)
🚨 Problem:

Both threads read 1000, increment separately, and write back 1001, losing an increment.
3️⃣ How Does the CPU Decide Which Write Wins?        
When two cores try to write to the same variable, the CPU resolves conflicts using hardware mechanisms:  🥵

Cache Coherence (MESI Protocol) → Only one core can "own" the cache line; the other must wait. 
Memory Bus Arbitration → If both request memory at the same cycle, the CPU chooses one based on priority.
Memory Ordering Rules → The CPU may reorder writes for optimization.
Atomic Instructions (LOCK XADD) → Ensures only one thread updates at a time (used in std::atomic).
4️⃣ Does Hyper-Threading (SMT) Affect This?
Scenario	Race Condition?	Why?
Two Hyper-Threads on the Same Core	❌ No	They execute in alternating cycles, no true parallel writes.
Two Hyper-Threads on Different Cores	✅ Yes	They behave like independent cores with separate caches.
🚀 Hyper-Threads on the same core avoid race conditions, but across cores, it behaves like normal multi-threading.

5️⃣ How to Fix Lost Updates in Multi-Threading?
Method	Safe?	Fast?	When to Use?
Direct odd++ (No Sync)	❌ No	🚀 Fast but incorrect	Causes lost updates.
Using std::atomic	✅ Yes	⚡ Medium	Best for counters (odd++).
Using std::mutex	✅ Yes	❌ Slow	Best for modifying complex shared data.
🚀 Use std::atomic for counters, and std::mutex for protecting complex shared resources.

🚀 Final Takeaways
✅ Same-core threads cannot truly write at the same time, so no race conditions.
✅ Different-core threads can cause race conditions because they have separate caches.
✅ CPU cache coherence (MESI) decides which write is applied first.
✅ Hyper-Threads on the same core do not have race conditions because they take turns executing.
✅ Use std::atomic for fast, thread-safe counter updates.
✅ Use std::mutex if multiple threads modify the same complex data structure.

🔥 TL;DR: If multiple threads write to the same variable, use std::atomic to avoid lost updates. 🔥


# SUPERSCALING
1. Superscalar processors can issue multiple instructions per cycle using different functional units (e.g., ALU, FPU, Load/Store).
2. If one thread uses ALU while the other thread uses FPU, both execution units operate in parallel, enabling overall CPU usage to exceed 100%.
To test this, we need to pin the thread execution to a perticular logical core pair. 
[root@JPR-2YJCVQ3 c-]# lscpu --extended
CPU SOCKET CORE L1d:L1i:L2:L3 ONLINE
  0      0    0 0:0:0:0          yes
  1      0    0 0:0:0:0          yes
  2      0    1 1:1:1:0          yes
  3      0    1 1:1:1:0          yes
  4      0    2 2:2:2:0          yes
  5      0    2 2:2:2:0          yes
  6      0    3 3:3:3:0          yes
  7      0    3 3:3:3:0          yes
  8      0    4 4:4:4:0          yes
  9      0    4 4:4:4:0          yes
 10      0    5 5:5:5:0          yes
 11      0    5 5:5:5:0          yes
 12      0    6 6:6:6:0          yes
 13      0    6 6:6:6:0          yes
 14      0    7 7:7:7:0          yes
 15      0    7 7:7:7:0          yes
 16      0    8 8:8:8:0          yes
 17      0    8 8:8:8:0          yes
 18      0    9 9:9:9:0          yes
 19      0    9 9:9:9:0          yes





