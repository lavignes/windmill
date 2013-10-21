CC = g++
CFLAGS = -DGLEW_STATIC -g -Wall -Wextra -Werror -Wno-unused-parameter -Wno-unused-result -Wno-unused-function
LDFLAGS = -lglut -lGLEW -lGL

SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)

BIN = windmill

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) -o $(BIN) 

%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(OBJS) $(BIN)
