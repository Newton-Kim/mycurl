PROGRAM=mycurl
OBJS=mycurl.o mc-lang.o mc-scan.o \
	command/mc-cmd-list.o \
	command/mc-cmd-open.o \
	command/mc-cmd-close.o \
	command/mc-cmd-leave.o \
	command/mc-cmd-quit.o \
	command/mc-cmd-get.o \
	command/mc-cmd-put.o \
	command/mc-cmd-post.o \
	command/mc-cmd-delete.o \
	command/mc-cmd-header.o \
	command/mc-cmd-verbose.o

CXXFLAGS=-g -O2 -I. -Iinclude

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CXX) -o $@ $^

clean:
	rm -f $(OBJS) $(PROGRAM)
