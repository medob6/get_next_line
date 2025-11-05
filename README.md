# Get Next Line

A C function that reads and returns one line at a time from a file descriptor.

## Description

**get_next_line** is a project from the 42 curriculum that implements a function capable of reading a file line by line. The function uses a static variable to remember its position between calls, allowing efficient sequential reading of any file or standard input without loading the entire content into memory.

This project teaches fundamental concepts including:
- File descriptor manipulation
- Static variables in C
- Dynamic memory allocation
- Buffer management

## Function Prototype

```c
char *get_next_line(int fd);
```

### Parameters
- `fd`: The file descriptor to read from

### Return Value
- Returns the line that was read (including the newline character `\n` if present)
- Returns `NULL` when there's nothing left to read or an error occurs

## Usage

### Compilation

The function must be compiled with a defined buffer size:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
```

You can change `BUFFER_SIZE` to any positive integer value to adjust the reading buffer size.

### Example

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd;
    char    *line;

    fd = open("example.txt", O_RDONLY);
    if (fd == -1)
        return (1);
    
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    
    close(fd);
    return (0);
}
```

## Project Structure

```
.
├── get_next_line.c          # Main function implementation
├── get_next_line_utils.c    # Helper functions
└── get_next_line.h          # Header file
```

## Features

- ✅ Reads from file descriptors line by line
- ✅ Works with files, standard input, and redirections
- ✅ Handles various buffer sizes efficiently
- ✅ Memory efficient (doesn't load entire file)
- ✅ Handles lines with or without newline characters
- ✅ Returns NULL at EOF or on error

## Bonus Features

If the bonus part is implemented:
- ✅ Handles multiple file descriptors simultaneously
- ✅ Uses only one static variable
- ✅ Manages multiple files without losing track of each one's reading position

## Technical Details

### Allowed Functions
- `read`
- `malloc`
- `free`

### Key Concepts
- **Static Variables**: Preserve data between function calls
- **Buffer Management**: Efficient reading in chunks
- **Memory Management**: Proper allocation and deallocation to prevent leaks

## Notes

- The function behavior is undefined if the file pointed to by the file descriptor changes between calls while still having a current line to read
- Binary files are not guaranteed to work correctly
- The returned line must be freed by the caller to avoid memory leaks

## License

This project is part of the 42 school curriculum.

---

**Author**: [medob6](https://github.com/medob6)
