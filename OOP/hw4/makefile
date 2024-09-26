CC = g++
CFLAGS = -Wall -std=c++11
SOURCES = pdlist pdadd pdremove pdshow
OBJECTS = $(SOURCES:=.o) entity.o diary.o
all: $(SOURCES)
$(SOURCES): %: %.o entity.o diary.o
	$(CC) $(CFLAGS) $^ -o $@
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@
entity.o: entity.cpp 
	$(CC) $(CFLAGS) -c entity.cpp -o entity.o
diary.o: diary.cpp 
	$(CC) $(CFLAGS) -c diary.cpp -o diary.o
clean:
	rm -f $(OBJECTS) 
	
