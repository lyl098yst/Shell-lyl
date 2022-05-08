CC = g++ 
DIR = ../commands/
SOURCE = $(filter-out cd.cpp, $(wildcard *.cpp))
TARGET = $(patsubst %.cpp, %, $(SOURCE)) 
COMPILE_FLAG = "-std=c++11"
all:$(TARGET)
 
$(TARGET) : % : %.o
	$(CC)  $^ -o  $(DIR)$@
%.o : %.cpp
	$(CC) ${COMPILE_FLAG} -c $< -o $@
 
.PHONY:all clean

clean:
	rm *.o
