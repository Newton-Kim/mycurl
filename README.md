# mycurl
mycurl is a simple interactive client based on libcurl written in C++. It has been developed to test a newly developed server or a feature of the server.
# How to install
make
sudo make install
# Tutorial
## How to start
Just type 'mycurl' then you will see following prompt
```
mycurl> 
```

## Downloading a content
You can get a ontent from a server and close
```
open www.google.com
get
close
```

You may want to leave the connection to reuse or do another work with the address.
```
open www.google.com
get
leave
```
