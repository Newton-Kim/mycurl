CORE=$(shell cat /proc/cpuinfo | grep processor | wc -l)
PROGRAM=mycurl
version.h:
	echo "#pragma once" > $@
	echo "#define VERSION \"$(VERSION)\"" >> $@
mycurl.o:version.h
OBJS=mycurl.o \
	interpreter/mc-lang.o \
	interpreter/mc-scan.o \
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
	interpreter/command/mc-cmd-follow.o \
	performer/curl/mc-curl.o \
	performer/curl/mc-curl-file.o \
	performer/mc-curl-performer.o

CXXFLAGS=-g -O2 -I../include -Iperformer `pkg-config --cflags libcurl`
LIBS=`pkg-config --libs libcurl` -lreadline

all:
	$(MAKE) $(PROGRAM) -j$(CORE)

$(PROGRAM): $(OBJS)
	$(CXX) -o $@ $^ $(LIBS)

install: $(PROGRAM)
	install -d $(DIST_DIR)/usr/bin
	install -m 755 $(PROGRAM) $(DIST_DIR)/usr/bin

clean:
	rm -f $(OBJS) $(PROGRAM) version.h
