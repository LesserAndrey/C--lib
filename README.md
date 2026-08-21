# C--lib 🐺

**C-- Functions in C**

A library of C-- functions for the C language.

## Philosophy

C on steroids. Mascot — Wolf. 🐺

## Features

- `cmm_say` / `cmm_say_bang` — text output
- `cmm_strlen`, `cmm_strupper`, `cmm_strlower` — string functions
- `cmm_strfind`, `cmm_strdel` — search and delete
- `cmm_term_color` — colored output
- `cmm_term_input_with` — masked input (passwords!)
- `cmm_say_work` — updatable output
- `cmm_mem_alloc` — memory management
- And much more!

## Usage

```c
#include "cmm.h"

int main() {
    cmm_say_bang("Hello, World!");
    return 0;
}
```
## Compilation
```bash
gcc main.c cmm.c -o program
./program
```

## Author

Andrey, 10 years old. Creator of the C-- lang.

## License

MIT
