
shl417: shl417.o
	g++ -o $@  $^ -lreadline
%.o: %.cpp %.h
	g++ -c -o $@ $<

.PHONY:clean

clean:
	rm *.o
