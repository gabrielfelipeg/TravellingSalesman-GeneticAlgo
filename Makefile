CC=g++
CFLAGS = -std=c++17
DEPS = src/*.h

SRCS = $(shell find src -name *.cpp)
OBJS := $(addsuffix .o,$(basename $(SRCS)))

all: run

src/%.o: src/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

run: $(OBJS)
	$(CC) -o $@ $^

clean: 
	rm -rf $(OBJS)
	rm -f run