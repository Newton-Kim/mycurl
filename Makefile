PROGRAM=mycurl
OBJS=mycurl.o mc-lang.o mc-scan.o

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CXX) -o $@ $^

clean:
	rm -f $(OBJS) $(PROGRAM)
