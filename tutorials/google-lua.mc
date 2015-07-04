%%-lua respcb
curl = mycurl.open('www.google.com')
resp = curl::get()
%%
open www.google.com #open a curl handle for google.com
#get a page from www.google.com
get > respcb
#close the handle
quit
