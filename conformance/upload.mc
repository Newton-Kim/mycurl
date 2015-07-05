open localhost:8081/upload
verbose on
form name file1
form filename Lenna.png
header Content-Type multipart/form-data;boundary=----mycurl
header Content-Lenght 194
header Expect
post < Lenna.png
quit
