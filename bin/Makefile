cc=g++
CFLAGS=-g -Wall
CUR_DIR=$(shell pwd)
vpath %.o $(CUR_DIR)/../temp
vpath %.a $(CUR_DIR)/../lib
VPATH = $(CUR_DIR):$(CUR_DIR)/../src
LIB_DIR = -L $(CUR_DIR)/../lib #须设置库目录
LIB_NAME=-lm -lm -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXxf86vm -lXinerama -lXcursor -lXi -ldl#须设置连接的库
target=zongtest
$(target): $(wildcard ../temp/*.o)
	$(cc) $^ $(LIB_DIR) $(LIB_NAME) -o $@
#.PHONY: all
#all : obj_o tar_bin
#obj_o :
#${str#*I}
