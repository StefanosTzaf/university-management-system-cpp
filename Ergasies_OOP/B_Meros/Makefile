#compiler
CC = g++

# Compile options. Το -I<dir> λέει στον compiler να αναζητήσει εκεί include files
#CFLAGS = -Wall  -g -I$(INCLUDE)
# Αρχεία .o


OBJS = person.o main.o secretary.o student.o professor.o course.o semester.o files.o

# Το εκτελέσιμο πρόγραμμα
EXEC = University

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)

clean:
	rm -f $(OBJS) $(EXEC)

run: $(EXEC)
	./$(EXEC) 

valgrind: $(EXEC)
	valgrind -s ./$(EXEC)