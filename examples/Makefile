CORE=$(shell cat /proc/cpuinfo | grep processor | wc -l)
TEST_SERVER=test-server
NGINX_DIR=nginx-1.9.2
NGINX=$(NGINX_DIR)/objs/nginx

all: $(NGINX)

$(NGINX_DIR):
	tar -zxvf $(TEST_SERVER)/$@.tar.gz

$(NGINX_DIR)/Makefile:$(NGINX_DIR)
	cd $(NGINX_DIR) && ./configure

$(NGINX):$(NGINX_DIR)/Makefile
	cd $(NGINX_DIR) && $(MAKE) -j$(CORE)

install:

clean:
	rm -rf $(NGINX_DIR) $(NGINX_UPLOAD_DIR)
