PROGRAM=mycurl
OBJS=mycurl.o \
	interpreter/mc-lang.o interpreter/mc-scan.o \
	interpreter/command/mc-cmd-list.o \
	interpreter/command/mc-cmd-open.o \
	interpreter/command/mc-cmd-close.o \
	interpreter/command/mc-cmd-leave.o \
	interpreter/command/mc-cmd-quit.o \
	interpreter/command/mc-cmd-get.o \
	interpreter/command/mc-cmd-put.o \
	interpreter/command/mc-cmd-post.o \
	interpreter/command/mc-cmd-delete.o \
	interpreter/command/mc-cmd-header.o \
	interpreter/command/mc-cmd-verbose.o \
	performer/curl/mc-curl.o \
	performer/mc-curl-performer.o

CXXFLAGS=-g -O2 -Iinclude -Iperformer `pkg-config --cflags libcurl`
LIBS=`pkg-config --libs libcurl`

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CXX) -o $@ $^ $(LIBS)

install: $(PROGRAM)
	install -m 755 $(PROGRAM) $(DIST_DIR)/usr/bin

clean:
	rm -f $(OBJS) $(PROGRAM)
