PWD=$(shell `pwd`)
CC ?= gcc
EXE_PATH = bin

INC= -I./include

SRC_SRC = $(wildcard src/*.c)
SRC_SENSORS = $(wildcard sensors/*.c)

all: $(EXE_PATH) $(EXE_PATH)/sensorsMain $(EXE_PATH)/ipc_test

$(EXE_PATH)/ipc_test: example/ipc_test.c $(SRC_SRC)
	$(CC) $(INC) $^ -o $@


$(EXE_PATH)/sensorsMain: example/sensorsMain.c $(SRC_SRC) $(SRC_SENSORS)
	$(CC) $(INC) $^ -o $@


$(EXE_PATH):
	mkdir $(EXE_PATH) -p


clean:
	rm $(EXE_PATH) -rf
