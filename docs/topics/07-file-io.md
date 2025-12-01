# File I/O

File: `src/examples/file_io.c`

What you’ll learn
- Open, read, write, and close files
- Text vs binary modes

Key syntax
- `FILE *f = fopen("name.txt", "w");`
- `fprintf(f, "Line %d\n", 42);`
- `fgets(line, sizeof line, f)` reads a line
- `fopen("file.bin", "wb"); fwrite(&obj, sizeof obj, 1, f);`

Pitfalls
- Always check `fopen` return value.
- Remember to `fclose` files; use one exit path to clean up.

Try it
- Write a struct as binary, then load it back and print.
