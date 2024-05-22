CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude
SRCDIR = src
BINDIR = bin

SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c, $(BINDIR)/%.o, $(SRCS))
TARGET = $(BINDIR)/download-monitor.exe

.PHONY: all clean run

all: $(BINDIR) $(TARGET)

$(BINDIR):
	if not exist $(BINDIR) mkdir $(BINDIR)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

$(BINDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	$(TARGET)

clean:
	if exist $(BINDIR) rmdir /s /q $(BINDIR)


