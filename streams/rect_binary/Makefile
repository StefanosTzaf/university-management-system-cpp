EXEC = rect_stream

OBJS = rect_stream.o ../../rect/rect.o

CC = g++


ARGS =


$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)

clean:
	rm -f $(OBJS) $(EXEC)

run: $(EXEC)
	./$(EXEC) $(ARGS)
valgrind: $(EXEC)
	valgrind ./$(EXEC) $(ARGS)
