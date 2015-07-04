NGINX_MAK=nginx-1.2.9.mak

all:

install:

server start stop:
	$(MAKE) -f test-server/$(NGINX_MAK) $@

clean:
	$(MAKE) -f test-server/$(NGINX_MAK) $@
	rm -f localhost-get.html

test: start test01 end

test01: localhost-get.html
	@echo $@......
	@diff $< tmp/html/index.html

localhost-get.html: get.mc
	$(MYCURL) $<
