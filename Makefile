#####################################################
#####VARIABLES
#####################################################

TARGET=main
CC=c++
CL=c++
OPTIONS=-Wall
FRAMEWORKS=-framework OpenGL
INCLUDES=-I/opt/local/include/
LIBS=-L/opt/local/lib/ -lglew -lglfw 
CFLAGS= $(OPTIONS) $(INCLUDES)
LFLAGS= $(OPTIONS) $(FRAMEWORKS) $(LIBS)
OBJS=main.o glee.o

#####################################################
#####TARGETS
#####################################################
all:$(TARGET)

$(TARGET):$(OBJS)
	$(CL) $(LFLAGS) $(OBJS) -o $(TARGET)

main.o:main.cpp glee.h
	$(CC) $(CFLAGS) -c main.cpp

glee.o:glee.cpp glee.h
	$(CC) $(CFLAGS) -c glee.cpp

clean:
	rm $(TARGET)
	rm *.o
	rm *.log

