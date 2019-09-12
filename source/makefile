
PWD=$(shell `pwd`)
CC ?= gcc
EXE_PATH = bin

INC= -I./include

SRC_SRC = $(wildcard src/*.c)
SRC_SENSORS = $(wildcard sensors/*.c sensors/sensors/*.c)
SRC_EVENT = $(wildcard event/*.c)
SRC_TRANSFERS = $(wildcard transfers/*.c transfers/mqtt/*.c)
SRC_LOG = $(wildcard log/*.c)
SRC_DRIVER = $(wildcard driver/*.c)

all: $(EXE_PATH) $(EXE_PATH)/appDamo

$(EXE_PATH)/filetest: example/filetest.c $(SRC_LOG)
	$(CC) $(INC) $^ -o $@

$(EXE_PATH)/appDamo: example/appDamo.c $(SRC_SRC) $(SRC_SENSORS) $(SRC_EVENT) $(SRC_TRANSFERS) $(SRC_DRIVER)
	$(CC) $(INC) $^ -o $@ -lpthread

$(EXE_PATH)/ipc_test: example/ipc_test.c $(SRC_SRC)
	$(CC) $(INC) $^ -o $@

$(EXE_PATH)/sensorsMain: example/sensorsMain.c $(SRC_SRC) $(SRC_SENSORS)
	$(CC) $(INC) $^ -o $@


$(EXE_PATH):
	mkdir $(EXE_PATH) -p


clean:
	rm $(EXE_PATH) -rf
