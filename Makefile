#cc=g++
#CFLAGS=-g -Wall
CUR_DIR=$(shell pwd)
#vpath %.o $(CUR_DIR)/temp
#vpath %.a $(CUR_DIR)/lib
VPATH = $(CUR_DIR)/bin:$(CUR_DIR)/src

.PHONY: all obj_o tar_bin
all : obj_o tar_bin
obj_o : 
	$(MAKE) -C $(CUR_DIR)/src||exit 1
tar_bin :
	$(MAKE) -C $(CUR_DIR)/bin||exit 1

