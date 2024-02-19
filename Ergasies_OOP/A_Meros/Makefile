#compiler
CC = g++

# Compile options. Το -I<dir> λέει στον compiler να αναζητήσει εκεί include files
#CFLAGS = -Wall  -g -I$(INCLUDE)
# Αρχεία .o


OBJS = person.o main.o secretary.o

# Το εκτελέσιμο πρόγραμμα
EXEC = classes

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC) 

clean:
	rm -f $(OBJS) $(EXEC)

run: $(EXEC)
	./$(EXEC) 

valgrind: $(EXEC)
	valgrind ./$(EXEC)