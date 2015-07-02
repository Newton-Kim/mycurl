CORE=$(shell cat /proc/cpuinfo | grep processor | wc -l)
NGINX_MAK=nginx-1.9.2.mak

all:

install:
	install -d $(DIST_DIR)/usr/share/mycurl
	install -m 644 *.mc $(DIST_DIR)/usr/share/mycurl

start stop clean:
	$(MAKE) -f $(NGINX_MAK) $@

test: start end

	
