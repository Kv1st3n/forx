# HexDumper
HexDumper is a simple CLI-based hexadecimal dumper written in C, similar to `xxd`, but simpler.  
Developed on macOS using clang (clang-1700.4.4.1).

>[!IMPORTANT]
> This project is built and tested on macOS using clang via Xcode Command Line Tools.  
> It may work on Linux with gcc but is not officially supported.

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
./hexDumper [flags] <file>
./hexDumper [flags]          # reads from stdin if no file is given
```

### Flags

| Flag | Description |
|------|-------------|
| `-h` | Hex dump a file or stdin |
| `-r` | Reverse mode — reconstruct binary from a hex dump |
| `-C` | Compact output (no ASCII column) |
| `-L` | Lowercase hex output |


### Examples

```zsh
# Dump a file
./hexDumper -h test.txt

# Read from stdin
echo "hello" | ./hexDumper -h

```

## Example Output
The output is divided into the memory offset, hex values (capitalized) and printable ASCII characters.

```zsh
# Example command
./hexDumper hexDumper.c

# Output
00000000  23 69 6E 63 6C 75 64 65  20 3C 73 74 64 69 6F 2E  |#include <stdio.|
00000010  68 3E 0A 23 69 6E 63 6C  75 64 65 20 3C 73 74 64  |h>.#include <std|
00000020  69 6E 74 2E 68 3E 0A 23  69 6E 63 6C 75 64 65 20  |int.h>.#include |
00000030  22 68 65 78 44 75 6D 70  65 72 2E 68 22 0A 23 69  |"hexDumper.h".#i|
00000040  6E 63 6C 75 64 65 20 3C  63 74 79 70 65 2E 68 3E  |nclude <ctype.h>|
00000050  0A 0A 23 64 65 66 69 6E  65 20 55 4E 55 53 45 44  |..#define UNUSED|
00000060  28 78 29 20 28 76 6F 69  64 29 28 78 29 0A 0A 76  |(x) (void)(x)..v|
00000070  6F 69 64 20 64 75 6D 70  48 65 78 28 46 49 4C 45  |oid dumpHex(FILE|
#continues...

```

## Build Commands

```zsh
# Compile
make

# Remove binary and object files
make clean
```


