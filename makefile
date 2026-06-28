CC      = clang
CXX     = clang++
CFLAGS  = -Wall -Wextra -g -Wpedantic \
          -Wformat=2 -Wno-unused-parameter -Wshadow \
          -Wwrite-strings -Wstrict-prototypes -Wold-style-definition \
          -Wredundant-decls -Wnested-externs -Wmissing-include-dirs \
          -I/opt/homebrew/opt/openssl/include \
          -Isrc \
          -Isrc/report \
          -Isrc/ui
CXXFLAGS = -Wall -Wextra -g -std=c++17 \
           -I/opt/homebrew/opt/openssl/include \
           -Isrc \
           -Isrc/report \
           -Isrc/ui \
           $(shell pkg-config --cflags gtkmm-4.0)
LDFLAGS  = -L/opt/homebrew/opt/openssl/lib -lssl -lcrypto \
           $(shell pkg-config --libs gtkmm-4.0)
TARGET   = forx

SRCS_C   = main.c \
           src/hexDumper.c \
           src/scanner.c \
           src/checksum.c

SRCS_CPP = src/report/file_handler.cpp \
           src/report/sigdb.cpp \
           src/ui/CustomButton.cpp \
           src/ui/CustomWindow.cpp \
           src/ui/ExportFiletype.cpp \
           src/ui/window.cpp

OBJS     = $(SRCS_C:.c=.o) $(SRCS_CPP:.cpp=.o)

ifeq ($(CC),gcc)
    CFLAGS += -Wjump-misses-init -Wlogical-op
endif

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

GTK_TEST_SRCS = src/ui/window.cpp \
                src/ui/CustomButton.cpp \
                src/ui/CustomWindow.cpp \
                src/ui/ExportFiletype.cpp

test_gtk: $(GTK_TEST_SRCS)
	$(CXX) $(CXXFLAGS) $(GTK_TEST_SRCS) $(LDFLAGS) -o test_gtk

.PHONY: clean run

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET) test_gtk
	find . -name "*.o" -delete