# This is a makefile for compiling your whole project.
# It is used to compile all the source files in the src directory and link them together.
# It is also used to clean up the build directory and remove all the object files and the executable.
# The makefile is used to compile the project using the gcc compiler.

# Things to explore:
# - Linux, MacOS, WSL for Windows
# - Makefile variables
# - Makefile rules
# - Makefile targets
# - Makefile dependencies
# - Makefile commands

# ---------------------- Example makefile for a C project ----------------------

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iheader

SRC_DIR = c
OBJ_DIR = build

SRCS = main.c $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(notdir $(SRCS)))

TARGET = rs-nimons
TARGET_DIR = build

main: $(TARGET_DIR)/$(TARGET)
	@echo "Build complete."

# Compile .c files to .o in build/ (handle main.c separately)
$(OBJ_DIR)/main.o: main.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Link all .o files into the executable
$(TARGET_DIR)/$(TARGET): $(OBJS)
	@mkdir -p $(TARGET_DIR)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf build
	rm -f *.o *.out *.exe *.a *.so *.dll *.dSYM *.pdb *.ilk *.idb *.lib *.exp
