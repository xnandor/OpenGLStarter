#####################################################
#####VARIABLES
#####################################################

TARGET=test
CC=c++
OPTIONS=
FRAMEWORKS=-framework OpenGL
INCLUDES=-I/opt/local/include/
LIBS=-L/opt/local/lib/ -lglew -lglfw 
CFLAGS=-o $(TARGET) $(FRAMEWORKS) $(INCLUDES) $(LIBS)

#####################################################
#####TARGETS
#####################################################
all:$(TARGET)
	make $(TARGET)

$(TARGET):test.cpp
	$(CC) $(OPTIONS) $(CFLAGS) test.cpp

clean:
	rm test

