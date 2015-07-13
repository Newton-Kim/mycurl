CORE=$(shell cat /proc/cpuinfo | grep processor | wc -l)
PROGRAM=mycurl
COPYRIGHT=copyright
COPYRIGHT_IN=$(COPYRIGHT).in
CHANGELOG=changelog
CHANGELOG_IN=$(CHANGELOG).in
CHANGELOG_GZ=$(CHANGELOG).gz
MANPAGE=$(PROGRAM).1
MANPAGE_GZ=$(MANPAGE).gz
MAKE_DEPS=Makefile.deps
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
	interpreter/command/mc-cmd-verbose.o \
	interpreter/command/mc-cmd-follow.o \
	curl/mc-curl.o \
	curl/mc-curl-file.o \
	performer/stackframe/mc-curl-performer-connection.o \
	performer/stackframe/mc-curl-performer-header.o \
	performer/stackframe/mc-curl-performer-form.o \
	performer/mc-curl-performer-factory.o \
	performer/mc-curl-performer.o

SRCS=${OBJS:.o=.cc}

include $(MAKE_DEPS)

INCLUDES=-I../include -Iperformer -Icurl `pkg-config --cflags libcurl`
CXXFLAGS=-g -O2 $(INCLUDES)
LIBS=`pkg-config --libs libcurl` -lreadline

all: $(MAKE_DEPS)
	$(MAKE) $(PROGRAM) -j$(CORE)

$(MAKE_DEPS): $(SRCS) version.h
	$(CXX) -MM $(INCLUDES) $^ > $(MAKE_DEPS)

$(PROGRAM): $(OBJS)
	$(CXX) -o $@ $^ $(LIBS)

install: $(PROGRAM) $(COPYRIGHT) $(CHANGELOG_GZ) $(MANPAGE_GZ)
	install -d $(DIST_DIR)/usr/bin
	install -m 755 -s $(PROGRAM) $(DIST_DIR)/usr/bin
	install -d $(DIST_DIR)/usr/share/doc/$(PROGRAM)
	install -m 644 $(COPYRIGHT) $(DIST_DIR)/usr/share/doc/$(PROGRAM)
	install -m 644 $(CHANGELOG_GZ) $(DIST_DIR)/usr/share/doc/$(PROGRAM)
	install -d $(DIST_DIR)/usr/share/man/man1
	install -m 644 $(MANPAGE_GZ) $(DIST_DIR)/usr/share/man/man1

$(COPYRIGHT): $(COPYRIGHT_IN)
	sed "s#@program@#$(PROGRAM)#g; s#@year@#`date +%Y`#g;" < $< > $@

$(CHANGELOG_GZ): $(CHANGELOG)
$(MANPAGE_GZ): $(MANPAGE)

$(CHANGELOG_GZ) $(MANPAGE_GZ):
	gzip -9 $<

$(CHANGELOG): $(CHANGELOG_IN)
	cp $< $@

$(MANPAGE): $(PROGRAM)
	help2man ./$< > $@

clean:
	rm -f $(OBJS) $(PROGRAM) $(COPYRIGHT) $(CHANGELOG_GZ) $(MANPAGE_GZ) $(MAKE_DEPS) version.h
