VERSION=1.0.0
DIST_DIR=dist
all install:
	$(MAKE) -C src $@ VERSION=$(VERSION)
	$(MAKE) -C examples $@
	$(MAKE) -C debian $@ VERSION=$(VERSION)

clean:
	$(MAKE) -C src $@ VERSION=$(VERSION)
	$(MAKE) -C examples $@
	$(MAKE) -C debian $@ VERSION=$(VERSION)
	rm -rf $(DIST_DIR)

test: all
	$(MAKE) -C examples $@

$(DIST_DIR):
	mkdir -p $@

deb: $(DIST_DIR)
	$(MAKE) install DIST_DIR=../$<
	$(MAKE) -C debian $@ DIST_DIR=../$< VERSION=$(VERSION)
