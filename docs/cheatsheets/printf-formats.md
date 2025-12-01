# printf / scanf Formats (Common)

- `%d` / `%i`: int
- `%u`: unsigned int
- `%ld` / `%lld`: long / long long
- `%zu`: size_t
- `%f` / `%lf`: double (printf treats %f as double)
- `%e` / `%g`: scientific / compact
- `%c`: char
- `%s`: C string (char*)
- `%p`: pointer (void*)
- `%%`: literal percent

Width / precision
- `%8d` width 8
- `%.2f` two decimals
- `%08x` zero-pad hex to width 8

Scanf notes
- `scanf("%d", &x);` needs address
- Use length modifiers: `%lld` for long long, `%zu` for size_t (C99+)
