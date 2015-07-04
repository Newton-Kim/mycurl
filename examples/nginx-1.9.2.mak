TEST_SERVER=test-server
NGINX_192_CONF=nginx-1.9.2.conf
NGINX_CONF=nginx.conf
WORK_DIR=tmp
NGINX_DIR=nginx-1.9.2
NGINX=$(NGINX_DIR)/objs/nginx
NGINX_LUA_DIR=lua-nginx-module-0.9.16
NGINX_DEV_DIR=ngx_devel_kit-0.2.19

start: $(WORK_DIR) $(WORK_DIR)/$(NGINX_CONF) $(NGINX)
	$(NGINX) -p $(WORK_DIR) -c $(NGINX_CONF)

stop: $(WORK_DIR) $(WORK_DIR)/$(NGINX_CONF)
	$(NGINX) -p $(WORK_DIR) -c $(NGINX_CONF) -s $@

clean:
	rm -rf $(NGINX_DIR) $(WORK_DIR) $(NGINX_DEV_DIR) $(NGINX_LUA_DIR)

$(NGINX):$(NGINX_DIR)/Makefile
	cd $(NGINX_DIR) && $(MAKE) -j$(CORE)

$(NGINX_DIR): $(TEST_SERVER)/$(NGINX_DIR).tar.gz
$(NGINX_DEV_DIR): $(TEST_SERVER)/$(NGINX_DEV_DIR).tar.gz
$(NGINX_LUA_DIR): $(TEST_SERVER)/$(NGINX_LUA_DIR).tar.gz
$(NGINX_DIR) $(NGINX_DEV_DIR) $(NGINX_LUA_DIR):
	tar -zxvf $(TEST_SERVER)/$@.tar.gz

$(NGINX_DIR)/Makefile:$(NGINX_DIR) $(NGINX_DEV_DIR) $(NGINX_LUA_DIR)
	cd $(NGINX_DIR) && ./configure \
		--add-module=../$(NGINX_DEV_DIR) \
		--add-module=../$(NGINX_LUA_DIR) 

$(WORK_DIR):
	mkdir $@
	mkdir $@/logs
	mkdir $@/html
	cp $(TEST_SERVER)/*.html $(WORK_DIR)/html

$(WORK_DIR)/$(NGINX_CONF): $(TEST_SERVER)/$(NGINX_192_CONF)
	cp $< $@

