*This project has been created as part of the 42 curriculum by wkerdad.*

## Description

Codexion is a concurrent programming simulation that models a team of coders sharing a limited pool of hardware dongles to perform work cycles. Each coder thread repeatedly compiles (requiring two dongles), debugs, and refactors. The simulation ends when all coders complete their required number of compiles or when any coder exceeds its burnout deadline while waiting for resources. The project explores classic concurrency challenges — deadlock, starvation, race conditions — through the metaphor of a shared development environment, supporting both FIFO and Earliest Deadline First (EDF) scheduling policies for resource allocation.

## Instructions

### Compilation

```sh
make
```

Clean object files with `make clean`, remove the binary with `make fclean`, or rebuild with `make re`.

### Execution

```sh
./codexion <number_of_coders> <time_to_burnout> <time_to_compile> <time_to_debug> <time_to_refactor> <number_of_compiles_required> <dongle_cooldown> <scheduler>
```

| Argument | Description |
|---|---|
| `number_of_coders` | Number of coder threads |
| `time_to_burnout` | Max wait time (ms) before a coder burns out |
| `time_to_compile` | Duration (ms) of a compile session |
| `time_to_debug` | Duration (ms) of a debug session |
| `time_to_refactor` | Duration (ms) of a refactor session |
| `number_of_compiles_required` | Compiles each coder must complete |
| `dongle_cooldown` | Cooldown (ms) after a dongle is released |
| `scheduler` | `fifo` or `edf` |

**Example:**

```sh
./codexion 5 1000 200 150 100 3 500 edf
```

## Resources

- **POSIX Threads Programming** (Lawrence Livermore National Laboratory) — comprehensive guide to pthreads, mutexes, and condition variables.
- **"Operating Systems: Three Easy Pieces"** by Remzi H. Arpaci-Dusseau and Andrea C. Arpaci-Dusseau — chapters on concurrency, locks, condition variables, and deadlock.
- **Dijkstra's Dining Philosophers Problem** — the classic resource-allocation problem that inspired the dongle-sharing model used in this project.
- **Coffman's Conditions** (E. G. Coffman, 1971) — the four necessary conditions for deadlock, used as a reference for deadlock prevention strategies.
- **IEEE Std 1003.1 (POSIX)** — specification for pthreads, mutexes, condition variables, and timed waits.

**AI usage:** AI-based tools (Claude and ChatGPT) were used as a sounding board during the design phase to discuss concurrency patterns (deadlock prevention, EDF scheduling, condition variable usage) and to review edge cases. AI also assisted in identifying potential race conditions, debugging segmentation faults, and generating code sketches for the queue and scheduling logic. No AI-generated code was used verbatim; all implementations were written and validated manually.

## Blocking cases handled

- **Deadlock prevention (Coffman's conditions):** Circular wait is broken by asymmetric dongle assignment — even-numbered coders acquire dongles in reverse order (left first, then right) relative to odd-numbered coders. No coder ever holds one dongle while waiting for another in a cycle.
- **Single-coder self-deadlock:** When only one coder exists, the left and right dongle are the same resource. The code detects this case and enters a polling loop (`usleep(50)`) instead of attempting to lock the same dongle twice.
- **Starvation prevention:** The EDF scheduler prioritizes coders whose burnout deadline is closest, ensuring no coder is perpetually overtaken. The FIFO scheduler provides fair, ordered access.
- **Dongle cooldown handling:** After releasing a dongle, a cooldown period (`dongle_cooldown`) is enforced via a timestamp (`available_at`). Waiting coders block on a `pthread_cond_timedwait` until the cooldown expires, preventing immediate re-acquisition.
- **Burnout detection:** A dedicated monitor thread continuously checks each coder's wait time against `time_to_burnout`. As soon as a coder exceeds its deadline, the simulation is terminated cleanly. The monitor also detects when all coders have finished successfully.
- **Log serialization:** All console output is protected by `print_msg_mutex`, preventing interleaved messages from concurrent threads.
- **Graceful shutdown:** When the simulation ends (burnout or completion), all threads detect the `simulation_done` flag during their polling loops, release any held dongles, and exit their routines without deadlocking on cleanup.

## Thread synchronization mechanisms

- **`pthread_mutex_t`:** Every shared variable — coder state, compile counter, dongle ownership, availability timestamps, simulation flags — is guarded by a dedicated mutex. Thread-safe getter/setter functions (`get_bool`, `set_int`, `increment_int`, etc.) encapsulate lock/unlock operations, eliminating race conditions.
- **`pthread_cond_t` (condition variables):** Each dongle has a condition variable used to signal coders waiting for that dongle. Coders call `pthread_cond_timedwait` with an absolute timeout computed from the dongle's `available_at` timestamp, waking precisely when the resource becomes available. A `pthread_cond_broadcast` is issued when a dongle is released, notifying all waiters to re-evaluate.
- **Custom event system (queues):** Each dongle maintains a singly linked list of waiters (`t_dongle_wait`). New requests are inserted according to the scheduling policy — FIFO appends to the tail; EDF inserts by ascending deadline. The queue itself is protected by `queue_mutex` per dongle.
- **Startup barrier:** All coder threads spin-wait on the `all_th_rd` flag (guarded by `all_th_rd_mutex`) until the main thread has finished creating every thread. This ensures all coders begin the simulation simultaneously, avoiding early-bird advantages.
- **Polling sleep (`ft_usleep`):** A custom sleep implementation that wakes every 500 microseconds to check the `simulation_done` flag, allowing threads to exit promptly when the simulation terminates.
- **Monitor thread:** A single monitor thread iterates through all coders, reading their state (via thread-safe getters) to detect burnout or completion. It serializes the termination decision, guaranteeing that only one thread sets `simulation_done` and logs the outcome.
