CC = gcc
CFLAGS = -Wall -g -fPIC

SRC_DIR = .
BUILD_DIR = build
INC_DIR = include

.PHONY: all jncOS dirs clean gdb

#dirs 
all: sched

# Build library
#jncOS: dirs jncOS.so

sched: dirs $(BUILD_DIR)/priority.o

jncOS.so: $(BUILD_DIR)/jncOS.o $(BUILD_DIR)/priority.o
	$(CC) $(CFLAGS) -shared -o $@ $^ 

#jncOS.a: $(BUILD_DIR)/jncOS.o $(BUILD_DIR)/priority.o 
#	ar rcs $@ $^ 

$(BUILD_DIR)/jncOS.o: $(SRC_DIR)/jncOS.c $(INC_DIR)/jncOS.h 
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@ 

$(BUILD_DIR)/priority.o: $(SRC_DIR)/priority.c $(INC_DIR)/priority.h
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@
	$(CC) $(CFLAGS) -o $(SRC_DIR)/sched $(BUILD_DIR)/priority.o

dirs:
	@mkdir -p $(BUILD_DIR) $(INC_DIR)

#snakes:
#	$(CC) $(CFLAGS) -o snakes demos/randomsnakes.o demos/util.o lib64/libsnakes.so -L. -llwp -Wl,-rpath,. -lncurses -lrt

#hungrysnakes:
#	$(CC) $(CFLAGS) -o hungrysnakes demos/hungrysnakes.o demos/util.o lib64/libsnakes.so -L. -llwp -Wl,-rpath,. -lncurses -lrt

gdb: lwp_test
	gdb ./$<
	lay next

clean:
	rm -rf $(BUILD_DIR)/*.a $(BUILD_DIR)/*.so $(BUILD_DIR)/lwp_test $(BUILD_DIR)/*.o
	rm -rf  *.o *.a *.so core.* DETAIL* snakes hungrysnakes sched
