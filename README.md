# Get_Next_Line

<img src="banner.svg" alt="GET_NEXT_LINE banner" />

## 📘 Overview

`get_next_line` is a project from the 42 curriculum that challenges students to implement a function capable of reading a file, one line at a time, from a given file descriptor. The goal is to handle input efficiently, manage memory properly, and gracefully handle edge cases — including different buffer sizes, incomplete lines, and multiple simultaneous file descriptors (bonus part).

This repository includes:
- ✅ A mandatory version that reads from a single file descriptor.
- ✨ A bonus version that supports reading from **multiple file descriptors** simultaneously.

## 🚀 Features

- Read line-by-line from any valid file descriptor.
- Supports standard input (`stdin`) and regular files.
- Custom buffer size via `BUFFER_SIZE` macro.
- Handles files with or without newline endings.
- Optimized for memory: no leaks or dangling pointers.
- Robust error handling for invalid descriptors and read failures.

## 🌟 Bonus Features

- Full support for **multiple file descriptors** simultaneously.
- Keeps the reading state isolated between FDs.
- Uses a static structure per FD to optimize memory and tracking.

## 🛠 Requirements

- A C compiler (e.g., `gcc`)
- Must compile using: `-D BUFFER_SIZE=xx`
- Should work for:
  - Standard input or files
  - Any buffer size (`BUFFER_SIZE >= 1`)
  - Files with/without newline endings
- **No memory leaks allowed**
- **Bonus**: Different file descriptors must not interfere with each other.

## ⚙️ How to Use

```bash
git clone https://github.com/Nouvack/Get_Next_Line.git
cd Get_Next_Line
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl
./gnl
```

### 📄 Example (main.c)

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd = open("example.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return 0;
}
```

### Bonus Example

```c
#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd1 = open("file1.txt", O_RDONLY);
    int fd2 = open("file2.txt", O_RDONLY);

    char *line1 = get_next_line(fd1);
    char *line2 = get_next_line(fd2);

    printf("File1: %s", line1);
    printf("File2: %s", line2);

    free(line1);
    free(line2);
    close(fd1);
    close(fd2);
    return 0;
}
```

## 🧪 Testing Scenarios

| Test Case | Description | Expected |
|-----------|-------------|----------|
| Valid File | Reads line-by-line | Each line, including `\n` |
| `stdin` Input | Manual typing | Dynamic input works |
| Empty File | No content | Returns `NULL` immediately |
| Invalid FD | e.g., -1 | Returns `NULL` and handles error |
| No newline | File ends without `\n` | Still returns last line |
| BUFFER_SIZE=1 | Extreme chunking | Still works correctly |
| BUFFER_SIZE=1000000 | Huge buffer | No crash, correct result |
| Bonus FDs | Two files open | Keeps context per FD |

## 🧠 What I Learned

- 📌 Static variables for persistent state across calls
- 🧵 Memory management and avoiding leaks (Valgrind friendly)
- 📁 Working with file descriptors and low-level I/O
- 🔧 Modular and reusable code structure
- 🧪 Handling real-world edge cases

## 🧑‍💻 Author

**Name:** Noam Novack  
**GitHub:** [Nouvack](https://github.com/Nouvack)  
**42 Login:** nsantand

## 🙌 Acknowledgments

Special thanks to 42 School for providing hands-on projects that sharpen low-level programming skills.

This project was developed as part of the 42 Common Core program.  
Proudly coded with love and `malloc()`.

---

![GNL Diagram](https://upload.wikimedia.org/wikipedia/commons/thumb/1/1b/C_File_IO.svg/1200px-C_File_IO.svg.png)
