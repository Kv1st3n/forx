CC      = clang
CXX     = clang++
CFLAGS  = -Wall -Wextra -g -Wpedantic \
          -Wformat=2 -Wno-unused-parameter -Wshadow \
          -Wwrite-strings -Wstrict-prototypes -Wold-style-definition \
          -Wredundant-decls -Wnested-externs -Wmissing-include-dirs \
          -I/opt/homebrew/opt/openssl/include \
          -Isrc \
          -Isrc/report
CXXFLAGS = -Wall -Wextra -g -std=c++17 \
           -I/opt/homebrew/opt/openssl/include \
           -Isrc \
           -Isrc/report
LDFLAGS  = -L/opt/homebrew/opt/openssl/lib -lssl -lcrypto
TARGET   = forx

SRCS_C   = main.c \
           src/hexDumper.c \
           src/scanner.c \
           src/checksum.c

SRCS_CPP = src/report/file_handler.cpp \
           src/report/sigdb.cpp

OBJS     = $(SRCS_C:.c=.o) $(SRCS_CPP:.cpp=.o)


ifeq ($(CC),gcc)
    CFLAGS += -Wjump-misses-init -Wlogical-op
endif


GTK_CFLAGS  := $(shell pkg-config --cflags gtkmm-4.0)
GTK_LIBS    := $(shell pkg-config --libs gtkmm-4.0)


$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


# simply used to test the window
test_gtk: src/ui/window.cpp src/ui/CustomButton.cpp src/ui/CustomWindow.cpp
	$(CXX) $(CXXFLAGS) $(GTK_CFLAGS) \
	    src/ui/window.cpp \
	    src/ui/CustomButton.cpp \
        src/ui/CustomWindow.cpp \
	    $(GTK_LIBS) \
	    -o test_gtk


.PHONY: clean run

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET) test_gtk
	find . -name "*.o" -delete