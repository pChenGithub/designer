
all :
	make -C source $@

romfs:
	cp source/bin/appDamo ../intelab/out/bin/

