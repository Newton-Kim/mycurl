CORE=$(shell cat /proc/cpuinfo | grep processors | wc -l)
TEST_SERVER=test-server
NGINX_192_CONF=nginx-1.2.9.conf
NGINX_CONF=nginx.conf
WORK_DIR=tmp
NGINX_DIR=nginx-1.2.9
NGINX=$(NGINX_DIR)/objs/nginx
NGINX_UPLOAD_DIR=nginx_upload_module-2.2.0
NGINX_LUA_DIR=lua-nginx-module-0.9.16
NGINX_DEV_DIR=ngx_devel_kit-0.2.19

start: $(WORK_DIR) $(WORK_DIR)/$(NGINX_CONF) $(NGINX)
	$(NGINX) -p $(WORK_DIR) -c $(NGINX_CONF)

stop: $(WORK_DIR) $(WORK_DIR)/$(NGINX_CONF)
	$(NGINX) -p $(WORK_DIR) -c $(NGINX_CONF) -s $@

clean:
	rm -rf $(NGINX_DIR) $(NGINX_UPLOAD_DIR) $(WORK_DIR) $(NGINX_DEV_DIR) $(NGINX_LUA_DIR)

server: $(NGINX)

$(NGINX):$(NGINX_DIR)/Makefile
	cd $(NGINX_DIR) && $(MAKE) -j$(CORE)

$(NGINX_DIR): $(TEST_SERVER)/$(NGINX_DIR).tar.gz
$(NGINX_DEV_DIR): $(TEST_SERVER)/$(NGINX_DEV_DIR).tar.gz
$(NGINX_LUA_DIR): $(TEST_SERVER)/$(NGINX_LUA_DIR).tar.gz
$(NGINX_UPLOAD_DIR): $(TEST_SERVER)/$(NGINX_UPLOAD_DIR).tar.gz
$(NGINX_DIR) $(NGINX_UPLOAD_DIR) $(NGINX_DEV_DIR) $(NGINX_LUA_DIR):
	tar -zxvf $<

$(NGINX_DIR)/Makefile:$(NGINX_DIR) $(NGINX_UPLOAD_DIR) $(NGINX_DEV_DIR) $(NGINX_LUA_DIR)
	export CFLAGS=-Wno-unused-parameter && \
	cd $(NGINX_DIR) && ./configure \
		--add-module=../$(NGINX_UPLOAD_DIR) \
		--add-module=../$(NGINX_DEV_DIR) \
		--add-module=../$(NGINX_LUA_DIR) 

$(WORK_DIR):
	mkdir $@
	mkdir $@/logs
	mkdir $@/html
	mkdir $@/tmp
	cd $@/tmp && mkdir 1 2 3 4 5 6 7 8 9 0
	cp $(TEST_SERVER)/*.html $(WORK_DIR)/html

$(WORK_DIR)/$(NGINX_CONF): $(TEST_SERVER)/$(NGINX_192_CONF)
	cp $< $@

