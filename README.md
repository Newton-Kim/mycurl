# mycurl
mycurl is a simple interactive client based on libcurl written in C++. It has been developed to test a newly developed server or a feature of the server.
# License
MIT License(http//opensource.org/licenses/MIT)
# Usage
```
mycurl [option]... [script]...

Option
  -h, --help     shows this help screen.
  -v, --version  shows the version.
```

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
# mycul langugage
mycurl language is a language dedicated to the interaction with a user in the prompt.

### list command
  Usage list
    lists opend urls or alias
### open command
  Usage open url [! alias] 
  Option
    opens new url.
    it enters existing url if it is opened.
### close command
  Usage close
    closes current url.
  leave command
  Usage leave
    leave current url.
    the opened url is not closed.
### quit command
  Usage quit
    end this program.
### get command
  Usage get [> file] [- list]
  Option
    posts GET request to the server.
    > operator redirects the response body to the file if there is any.
    list has headers for the request. Default list is defhdr.
### put command
  Usage put [< file_in[number]][ > file_out][ - list]
  Option
    posts GET request to the server.
    < operator redirects the request body from the file if there is any.
    number specifies the size of the chunk.
    Transfer-Encodingchunked header is automatically attached when specified.
    > operator redirects the response body to the file if there is any.
    list has headers for the request. Default list is defhdr.
### post command
  Usage post [< file_in[number]][ > file_out][ - list]
  Option
    posts GET request to the server.
    < operator redirects the request body from the file if there is any.
    number specifies the size of the chunk.
    Transfer-Encodingchunked header is automatically attached when specified.
    > operator redirects the response body to the file if there is any.
    list has headers for the request. Default list is defhdr.
### delete command
  Usage delete [- list]
  Option
    posts DELETE request to the server.
    list has headers for the request. Default list is defhdr.
### header command
  Usage header key value [> list]
  Option
    sets a header to a list.
    Default list is defhdr.
### verbose command
  Usage verbose [on | off]
  Option
    turn on or off a verbose mode.
  it returns current mode of verbosness when no argument is given.
### follow command
  Usage follow [on | off]
  Option
    turn on or off a follow mode.
    it returns current mode of following location when no argument is given.

# Reporting bugs
mailto:newton.s.kim@gmail.com
