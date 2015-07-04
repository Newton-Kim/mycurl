VERSION=1.2.0
DIST_DIR=dist
all install:
	$(MAKE) -C src $@ VERSION=$(VERSION)
	$(MAKE) -C conformance $@
	$(MAKE) -C tutorials $@
	$(MAKE) -C debian $@ VERSION=$(VERSION)

clean:
	$(MAKE) -C src $@ VERSION=$(VERSION)
	$(MAKE) -C conformance $@
	$(MAKE) -C tutorials $@
	$(MAKE) -C debian $@ VERSION=$(VERSION)
	rm -rf $(DIST_DIR)

test start stop server:
	$(MAKE) -C conformance $@

$(DIST_DIR):
	mkdir -p $@

deb: $(DIST_DIR)
	$(MAKE) install DIST_DIR=../$<
	$(MAKE) -C debian $@ DIST_DIR=../$< VERSION=$(VERSION)
