# A10 – Networking select()

## Overview
Non-blocking I/O multiplexing with `select()` (or `poll()`), enabling a single thread to manage multiple sockets.

## Code Walkthrough
Stub only; real code sets sockets non-blocking, builds fd_set, loops with select, handles readiness.

## Key Pitfalls
- Blocking accept()/recv() when not checking readiness.
- Failing to rebuild fd_set each loop iteration.

## Exercises
1. Implement echo server on localhost using select.
2. Track connected clients and broadcast messages.

## Further Reading
- BeeJ's Guide to Network Programming.
- Event loop designs (libuv, epoll, kqueue differences).
