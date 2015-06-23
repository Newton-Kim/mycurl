# mycurl
mycurl is a simple interactive client based on libcurl written in C++. It has been developed to test a newly developed server or a feature of the server.
# How to install
```
make
sudo make install
```
# Tutorial
Just type 'mycurl' then you will see following prompt.
```
mycurl> 
```
You can get a ontent from a server and close.
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
You don't get the home page of Goole because it is redirected.
```
open www.google.com
follow on
get
```
If you want to see the log, you switch on verbose.
```
open www.google.com
get
verbose on
leave
```
