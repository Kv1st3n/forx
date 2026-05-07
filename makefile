CC      = clang
CFLAGS  = -Wall -Wextra -fsanitize=address -g
TARGET  = hexDumper
SRCS    = main.c hexDumper.c
OBJS    = $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)