TEST_SERVER=test-server
NGINX_192_CONF=nginx-1.2.9.conf
NGINX_CONF=nginx.conf
WORK_DIR=tmp
NGINX_DIR=nginx-1.2.9
NGINX=$(NGINX_DIR)/objs/nginx
NGINX_UPLOAD_DIR=nginx_upload_module-2.2.0

start: $(WORK_DIR) $(WORK_DIR)/$(NGINX_CONF) $(NGINX)
	$(NGINX) -p $(WORK_DIR) -c $(NGINX_CONF)

stop: $(WORK_DIR) $(WORK_DIR)/$(NGINX_CONF)
	$(NGINX) -p $(WORK_DIR) -c $(NGINX_CONF) -s $@

clean:
	rm -rf  $(NGINX_DIR) $(NGINX_UPLOAD_DIR) $(WORK_DIR)

$(NGINX):$(NGINX_DIR)/Makefile
	cd $(NGINX_DIR) && $(MAKE) -j$(CORE)

$(NGINX_DIR): $(TEST_SERVER)/$(NGINX_DIR).tar.gz
$(NGINX_UPLOAD_DIR): $(TEST_SERVER)/$(NGINX_UPLOAD_DIR).tar.gz
$(NGINX_DIR) $(NGINX_UPLOAD_DIR):
	tar -zxvf $<

$(NGINX_DIR)/Makefile:$(NGINX_DIR) $(NGINX_UPLOAD_DIR)
	export CFLAGS=-Wno-unused-parameter && cd $(NGINX_DIR) && ./configure --add-module=../$(NGINX_UPLOAD_DIR)

$(WORK_DIR):
	mkdir $@
	mkdir $@/logs
	mkdir $@/html
	cp $(TEST_SERVER)/*.html $(WORK_DIR)/html

$(WORK_DIR)/$(NGINX_CONF): $(TEST_SERVER)/$(NGINX_192_CONF)
	cp $< $@

