# HexDumper
HexDumper is simple CLI-based hexadecimal dumper written in C. Developed on macOS using clang (clang-1700.4.4.1).

>[!IMPORTANT]
>This project is optimized for macOS using clang as compiler. 
>The build assumes that you have clang and make available via Xcode

## Installing

### Prerequisites
- Xcode Command Line
- Make

```zsh

git clone https://github.com/Kv1st3n/HexDumper.git

cd hexDumper

make

```

## Using Hex Dumper
The tool reads binary data from a file and outputs it in a formatted grid.

```zsh
# Basic usage
./hexDumper <filename>

#Example
./hexDumper hexDumper.c
```

### Build Commands
The included makefile handles the compilation process using clang. 


```zsh
# To compile the source
make

# To remove the binary and object (.o) files
make clean

```


## Example Output
The output is divided into the memory offset, hex values (capitalized) and printable ASCII characters.

```zsh
# Example command
./hexDumper hexDumper.c

# Output
00000000  23 69 6E 63 6C 75 64 65  20 3C 73 74 64 69 6F 2E  |#include <stdio.|
00000000  68 3E 0A 23 69 6E 63 6C  75 64 65 20 3C 73 74 64  |h>.#include <std|
00000000  69 6E 74 2E 68 3E 0A 23  69 6E 63 6C 75 64 65 20  |int.h>.#include |
00000000  22 68 65 78 44 75 6D 70  65 72 2E 68 22 0A 23 69  |"hexDumper.h".#i|
00000000  6E 63 6C 75 64 65 20 3C  63 74 79 70 65 2E 68 3E  |nclude <ctype.h>|
00000000  0A 0A 76 6F 69 64 20 64  75 6D 70 48 65 78 28 46  |..void dumpHex(F|
00000000  49 4C 45 20 2A 66 69 6C  65 29 20 7B 0A 0A 20 20  |ILE *file) {..  |
#continues...

```