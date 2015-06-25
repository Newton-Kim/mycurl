CORE=$(shell cat /proc/cpuinfo | grep processor | wc -l)
TEST_SERVER=test-server
NGINX_CONF=nginx.conf
NGINX_DIR=nginx-1.9.2
NGINX=$(NGINX_DIR)/objs/nginx
WORK_DIR=tmp

all:

install:
	install -d $(DIST_DIR)/usr/share/mycurl
	install -m 644 *.mc $(DIST_DIR)/usr/share/mycurl

test: $(NGINX)

$(NGINX_DIR):
	tar -zxvf $(TEST_SERVER)/$@.tar.gz

$(NGINX_DIR)/Makefile:$(NGINX_DIR)
	cd $(NGINX_DIR) && ./configure

$(NGINX):$(NGINX_DIR)/Makefile
	cd $(NGINX_DIR) && $(MAKE) -j$(CORE)

$(WORK_DIR):
	mkdir $@
	mkdir $@/logs
	mkdir $@/html
	cp $(TEST_SERVER)/*.html $(WORK_DIR)/html

$(WORK_DIR)/$(NGINX_CONF): $(TEST_SERVER)/$(NGINX_CONF)
	cp $(TEST_SERVER)/$(NGINX_CONF) $(WORK_DIR)

test: test_start test_end

test_start: $(WORK_DIR) $(WORK_DIR)/$(NGINX_CONF)
	$(NGINX) -p $(WORK_DIR) -c $(NGINX_CONF)

test_end: $(WORK_DIR) $(WORK_DIR)/$(NGINX_CONF)
	$(NGINX) -p $(WORK_DIR) -c $(NGINX_CONF) -s stop

install:

clean:
	rm -rf $(NGINX_DIR) $(WORK_DIR)
