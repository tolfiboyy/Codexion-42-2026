*This activity has been created as part of the 42 curriculum by asavidan.*

# Codexion

## Description

Codexion is a C multithreading simulation inspired by the dining philosophers problem. Each coder needs two neighboring dongles to compile, then alternates between debugging and refactoring. Dongles have a cooldown after use. The simulation ends when all coders complete the required number of compilations or one coder burns out.

A custom priority heap supports two scheduling policies:
- **FIFO:** oldest request first.
- **EDF:** earliest burnout deadline first (`last_compile_time + time_to_burnout`), with request order as a tie-breaker.

## Instructions

Compile with `make`, clean with `make clean` or `make fclean`, and rebuild with `make re`.

```bash
make
./codexion number_of_coders time_to_burnout time_to_compile time_to_debug time_to_refactor number_of_compiles_required dongle_cooldown scheduler
```

All durations and cooldowns are in milliseconds. The scheduler must be `fifo` or `edf`.

Example:

```bash
./codexion 5 1200 100 20 20 3 50 edf
```

## Blocking cases handled

- **Deadlocks:** both dongles are checked and reserved atomically, without holding one dongle while waiting for the other. This avoids the *hold-and-wait* condition from Coffman's deadlock conditions.
- **Concurrent reservations:** the manager mutex prevents two coders from reserving the same available dongle.
- **Starvation:** FIFO uses request order; EDF prioritizes earlier burnout deadlines. Arbitrating between competing requests reduces unfair access, although LIFO is not part of the mandatory implementation.
- **Cooldown:** each dongle tracks the earliest timestamp when it can be reserved again.
- **Burnout:** a dedicated monitor checks the time since each unfinished coder's last compilation start.
- **Logs:** a mutex serializes status messages to prevent interleaved output.

## Thread synchronization mechanisms

The simulation uses `pthread_create`, `pthread_join` and `pthread_mutex_t`:

- `gestion_mutex` protects the request heap and the availability/cooldown state of all dongles. Checking and reserving a pair happens in one critical section.
- Each coder's `time_mutex` protects `last_compile_time` and `finished`, which are shared with the monitor.
- `stop_mutex` protects the shared stop flag, allowing the monitor to signal workers to exit safely.
- `print_mutex` ensures each log line is written without interference from other threads.

Waiting threads periodically retry with `usleep`; no condition variables are used. The manager mutex is released before compilation, so independent coders can compile concurrently.

## Resources

- [POSIX threads overview — Linux man-pages](https://man7.org/linux/man-pages/man7/pthreads.7.html)
- [pthread_mutex_lock — Linux man-pages](https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html)
- [Deadlock — Coffman's conditions](https://en.wikipedia.org/wiki/Deadlock#Necessary_conditions)

**AI usage:** ChatGPT was used to clarify thread synchronization, discuss FIFO/EDF scheduling and heap operations, review potential edge cases, and suggest test scenarios. The implementation was developed and tested as part of the activity.
