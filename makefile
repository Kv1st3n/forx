CC      = clang
CXX		= clang++
CFLAGS  = -Wall -Wextra -g -Wpedantic \
          -Wformat=2 -Wno-unused-parameter -Wshadow \
          -Wwrite-strings -Wstrict-prototypes -Wold-style-definition \
          -Wredundant-decls -Wnested-externs -Wmissing-include-dirs \
          -I/opt/homebrew/opt/openssl/include \
		  -Isrc
CXXFLAGS = $(CFLAGS) -std=c++17
LDFLAGS = -L/opt/homebrew/opt/openssl/lib -lssl -lcrypto
TARGET  = hexDumper
SRCS_C    = main.c src/hexDumper.c src/scanner.c src/checksum.c
SRCS_CPP = src/report/test.cpp
OBJS    = $(SRCS_C:.c=.o) $(SRCS_CPP:.cpp=.o)

ifeq ($(CC),gcc)
	CFLAGS += -Wjump-misses-init -Wlogical-op
endif

$(TARGET): $(OBJS)
	$(CXX) $(CFLAGS) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)