EXEC = rect

OBJS = main.o rect.o

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
