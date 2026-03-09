SRC_DIR = src
INC_DIR = include
BUILD_DIR = build

CC = g++
CFLAGS = -Wall -g -I$(INC_DIR)

EXEC = University

OBJS = $(BUILD_DIR)/person.o $(BUILD_DIR)/main.o $(BUILD_DIR)/secretary.o \
       $(BUILD_DIR)/student.o $(BUILD_DIR)/professor.o $(BUILD_DIR)/course.o \
       $(BUILD_DIR)/semester.o $(BUILD_DIR)/files.o

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC) $(CFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(EXEC)

run: $(EXEC)
	./$(EXEC)

valgrind: $(EXEC)
	valgrind -s ./$(EXEC)