# HexDumper
HexDumper (name will change) is a simple CLI-based tool for hexadecimal dumping and file identification written in C. 
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

| Flag | Description | Notes |
|------|-------------|-------------|
| `-h` | Hex dump a file or stdin | Implemented | 
| `-r` | Reverse mode — reconstruct binary from a hex dump | Implemented | 
| `-C` | Compact output (no ASCII column) | Implemented | 
| `-L` | Lowercase hex output | Implemented | 
| `-o` | Outputs a file containing the dump | Implemented | 
| `-i` | File type identifier | Implemented | 
| `-d` | Directory scanner | Implemented | 

### Todos
| Task | Description | Notes | Status |
|------|-------------|-------------|------|
| Cleanup | Overall cleanup of code | Including proper comments | WIP |
| Checksum | Print MD5 and SHA256 of the file | Not yet implemented | WIP |
| GUI | Make a GUI for the tool| Not yet implemented | Not started |


### Examples

```zsh
# Dump a file
./hexDumper -h test.txt

# Read from stdin
echo "hello" | ./hexDumper -h

# Dump a file and create a new file containing the dump
./hexDumper -h -o dump.txt test.txt 

# Revert a dumped hex file to its original ASCII text
./hexDumper -r -o recovered.txt dump.txt

# Use lower case flag
./hexDumper -h -L -o  dump2.txt test.png 

# If you want to get byte size for the hexdump
./hexDumper -h -o dump.txt -B hexDumper.c

```

## Example Output
The output is divided into the memory offset, hex values (capitalized) and printable ASCII characters.

```zsh
# Example command
./hexDumper -h -o dump.txt hexDumper.c

# Output
00000000  23 69 6E 63 6C 75 64 65  20 3C 73 74 64 69 6F 2E  |#include <stdio.|
00000010  68 3E 0A 23 69 6E 63 6C  75 64 65 20 3C 73 74 64  |h>.#include <std|
00000020  69 6E 74 2E 68 3E 0A 23  69 6E 63 6C 75 64 65 20  |int.h>.#include |
00000030  22 68 65 78 44 75 6D 70  65 72 2E 68 22 0A 23 69  |"hexDumper.h".#i|
00000040  6E 63 6C 75 64 65 20 3C  63 74 79 70 65 2E 68 3E  |nclude <ctype.h>|
00000050  0A 23 69 6E 63 6C 75 64  65 20 3C 73 74 72 69 6E  |.#include <strin|
00000060  67 2E 68 3E 0A 0A 76 6F  69 64 20 64 75 6D 70 48  |g.h>..void dumpH|
00000070  65 78 28 46 49 4C 45 20  2A 66 69 6C 65 2C 20 46  |ex(FILE *file, F|
#continues...

# Example command with compact (-C)
./hexDumper -h -C -o dump.txt hexDumper.c

# Output
00000000  23 69 6E 63 6C 75 64 65  20 3C 73 74 64 69 6F 2E 
00000010  68 3E 0A 23 69 6E 63 6C  75 64 65 20 3C 73 74 64 
00000020  69 6E 74 2E 68 3E 0A 23  69 6E 63 6C 75 64 65 20 
00000030  22 68 65 78 44 75 6D 70  65 72 2E 68 22 0A 23 69 
00000040  6E 63 6C 75 64 65 20 3C  63 74 79 70 65 2E 68 3E 
00000050  0A 23 69 6E 63 6C 75 64  65 20 3C 73 74 72 69 6E 
00000060  67 2E 68 3E 0A 0A 76 6F  69 64 20 64 75 6D 70 48 
00000070  65 78 28 46 49 4C 45 20  2A 66 69 6C 65 2C 20 46 
#continues...
# Will end with this if -B is includes
2351 bytes


# Example command with directory scan (-d)
./hexDumper -d /testdir -o
/testdir/test.zip: Type: ZIP

```

## Build Commands

```zsh
# Compile
make

# Remove binary and object files
make clean
```


