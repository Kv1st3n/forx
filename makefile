CC      = clang
CFLAGS  = -Wall -Wextra -fsanitize=address -g -Wpedantic \
          -Wformat=2 -Wno-unused-parameter -Wshadow \
          -Wwrite-strings -Wstrict-prototypes -Wold-style-definition \
          -Wredundant-decls -Wnested-externs -Wmissing-include-dirs
TARGET  = hexDumper
SRCS    = main.c hexDumper.c
OBJS    = $(SRCS:.c=.o)

ifeq ($(CC),gcc)
	CFLAGS += Wjump-misses-init -Wlogical-op
endif

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)