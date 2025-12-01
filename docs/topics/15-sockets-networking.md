# 15 – Sockets and Networking

Sockets provide bidirectional communication endpoints.

## Basics
- Create: `socket(AF_INET, SOCK_STREAM, 0)`
- Bind (server): associate with IP:port.
- Listen/Accept: queue connections as TCP server.
- Connect (client): establish to remote host.
- Send/Recv: transmit bytes.

## In `sockets.c`
Demonstrates initializing platform (Winsock on Windows), opening a socket, connecting or listening (simplified), and cleaning up.

## Cross‑Platform Notes
- Windows: `WSAStartup`, `closesocket`, `WSACleanup`.
- POSIX: no startup; use `close(fd)`.

## Error Handling
- Check return < 0; inspect `errno` or `WSAGetLastError()`.
- Partial sends: loop until all bytes sent.

## Pitfalls
- Blocking calls freezing UI; consider non‑blocking or timeouts.
- Not handling network byte order (`htonl`, `htons`, `ntohl`, `ntohs`).
