OS=$(shell grep DISTRIB_ID /etc/lsb-release | sed 's/DISTRIB_ID=//')
SIZE=$(shell du -d 0 $(DIST_DIR) | cut -f1)
RELEASE=$(shell grep DISTRIB_RELEASE /etc/lsb-release | sed 's/DISTRIB_RELEASE=//')
ARCH=$(shell uname -p)
DEB_ARCH=$(shell dpkg-architecture -qDEB_BUILD_ARCH)
PKG=../mycurl-v$(VERSION)-$(OS)-$(RELEASE)-$(ARCH).deb

all:

install:

clean:
	rm -rf $(DIST_DIR) $(PKG)

deb: $(PKG)

$(PKG): $(DIST_DIR) $(DIST_DIR)/DEBIAN/control
	fakeroot dpkg-deb --build $< $@
	lintian $@

$(DIST_DIR)/DEBIAN:
	mkdir -p $@

$(DIST_DIR)/DEBIAN/control: control.in $(DIST_DIR)/DEBIAN
	sed "s#@version@#$(VERSION)#g; \
                s#@arch@#$(DEB_ARCH)#g; \
                s#@size@#$(SIZE)#g; \
        " < $< > $@

