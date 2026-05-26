CC      = clang
CFLAGS  = -Wall -Wextra -g -Wpedantic \
          -Wformat=2 -Wno-unused-parameter -Wshadow \
          -Wwrite-strings -Wstrict-prototypes -Wold-style-definition \
          -Wredundant-decls -Wnested-externs -Wmissing-include-dirs \
          -I/opt/homebrew/opt/openssl/include \
		  -Isrc
LDFLAGS = -L/opt/homebrew/opt/openssl/lib -lssl -lcrypto
TARGET  = hexDumper
SRCS    = main.c src/hexDumper.c src/scanner.c src/checksum.c
OBJS    = $(SRCS:.c=.o)

ifeq ($(CC),gcc)
	CFLAGS += -Wjump-misses-init -Wlogical-op
endif

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)