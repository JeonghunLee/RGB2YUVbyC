CC = gcc
CFLAGS = -W -WALL


all:
	@echo ------------------------------------------
	@echo  RGB To YUV Build
	@echo ------------------------------------------
	$(CC) rgb2yuv.c -o rgb2yuv


clean:
	@echo ------------------------------------------
	@echo  RGB To YUV  Clean
	@echo ------------------------------------------
	@rm -rf rgb2yuv 



