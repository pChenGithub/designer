
NVDIR=$(ROOTDIR)/lib/libnvram
PWD=$(shell `pwd`)
CC ?= gcc
EXE_PATH = bin

INC += -I$(NVDIR) -I./include -I/home/linux/test/out_mips/include -I../../intelab/HMI -I$(ROOTDIR)/$(LINUXDIR)/drivers/char
CFLAGS += -L/home/linux/test/out_mips/lib -L../../intelab/MSGService -lmsg_service -L/home/linux/intelab/intelab_trunk_2.0/lib/libnvram \
		  -L../../common -lunc_comm -L../../msc_comm -lumsc_comm

SRC_SRC = $(wildcard src/*.c)
SRC_SENSORS = $(wildcard sensors/*.c sensors/sensors/*.c)
SRC_HUMAN = $(wildcard humans/*.c)
SRC_EVENT = $(wildcard event/*.c)
SRC_TRANSFERS = $(wildcard transfers/*.c transfers/mqtt/*.c)
SRC_LOG = $(wildcard log/*.c)
SRC_DRIVER = $(wildcard driver/*.c)
SRC_PRO = $(wildcard producers/*.c)

all: $(EXE_PATH) $(EXE_PATH)/appDamo

$(EXE_PATH)/filetest: example/filetest.c $(SRC_LOG)
	$(CC) $(INC) $^ -o $@

$(EXE_PATH)/appDamo: example/appDamo.c $(SRC_SRC) $(SRC_SENSORS) \
	$(SRC_EVENT) $(SRC_TRANSFERS) $(SRC_DRIVER) $(SRC_HUMAN) $(SRC_PRO)
	$(CC) $(INC) $(CFLAGS) $^ -o $@ -lpthread -lcurl -lnvram

$(EXE_PATH)/ipc_test: example/ipc_test.c $(SRC_SRC)
	$(CC) $(INC) $^ -o $@

$(EXE_PATH)/sensorsMain: example/sensorsMain.c $(SRC_SRC) $(SRC_SENSORS)
	$(CC) $(INC) $^ -o $@


$(EXE_PATH):
	mkdir $(EXE_PATH) -p


clean:
	rm $(EXE_PATH) -rf
