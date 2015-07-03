TEST_SERVER=test-server
NGINX_192_CONF=nginx-1.9.2.conf
NGINX_CONF=nginx.conf
WORK_DIR=tmp
NGINX_DIR=nginx-1.9.2
NGINX=$(NGINX_DIR)/objs/nginx

start: $(WORK_DIR) $(WORK_DIR)/$(NGINX_CONF) $(NGINX)
	$(NGINX) -p $(WORK_DIR) -c $(NGINX_CONF)

stop: $(WORK_DIR) $(WORK_DIR)/$(NGINX_CONF)
	$(NGINX) -p $(WORK_DIR) -c $(NGINX_CONF) -s $@

clean:
	rm -rf $(NGINX_DIR) $(WORK_DIR)

$(NGINX):$(NGINX_DIR)/Makefile
	cd $(NGINX_DIR) && $(MAKE) -j$(CORE)

$(NGINX_DIR): $(NGINX_DIR).tar.gz
	tar -zxvf $(TEST_SERVER)/$@.tar.gz

$(NGINX_DIR)/Makefile:$(NGINX_DIR)
	cd $(NGINX_DIR) && ./configure

$(WORK_DIR):
	mkdir $@
	mkdir $@/logs
	mkdir $@/html
	cp $(TEST_SERVER)/*.html $(WORK_DIR)/html

$(WORK_DIR)/$(NGINX_CONF): $(TEST_SERVER)/$(NGINX_192_CONF)
	cp $< $@

