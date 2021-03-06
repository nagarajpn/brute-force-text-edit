CC=g++
CFLAGS=-c -Wall -w
LDFLAGS=-lncurses
SOURCES=main.cpp cursor.cpp preline.cpp line.cpp header.cpp pane.cpp fileType.cpp 
OBJS=$(SOURCES:.cpp=.o)
EXE=bts

all: $(SOURCES) $(EXE)
	
$(EXE): $(OBJS) 
	$(CC) $(OBJS) $(LDFLAGS) -o $@ 

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(OBJS) $(EXE)



