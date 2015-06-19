CORE=$(shell cat /proc/cpuinfo | grep processor | wc -l)
PROGRAM=mycurl
OBJS=src/mycurl.o \
	src/interpreter/mc-lang.o \
	src/interpreter/mc-scan.o \
	src/interpreter/command/mc-cmd-list.o \
	src/interpreter/command/mc-cmd-open.o \
	src/interpreter/command/mc-cmd-close.o \
	src/interpreter/command/mc-cmd-leave.o \
	src/interpreter/command/mc-cmd-quit.o \
	src/interpreter/command/mc-cmd-get.o \
	src/interpreter/command/mc-cmd-put.o \
	src/interpreter/command/mc-cmd-post.o \
	src/interpreter/command/mc-cmd-delete.o \
	src/interpreter/command/mc-cmd-header.o \
	src/interpreter/command/mc-cmd-verbose.o \
	src/performer/curl/mc-curl.o \
	src/performer/mc-curl-performer.o

CXXFLAGS=-g -O2 -Iinclude -Iperformer `pkg-config --cflags libcurl`
LIBS=`pkg-config --libs libcurl` -lreadline

all:
	$(MAKE) $(PROGRAM) -j$(CORE)

$(PROGRAM): $(OBJS)
	$(CXX) -o $@ $^ $(LIBS)

install: $(PROGRAM)
	install -m 755 $(PROGRAM) $(DIST_DIR)/usr/bin

clean:
	rm -f $(OBJS) $(PROGRAM)
