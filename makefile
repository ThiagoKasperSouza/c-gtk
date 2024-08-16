PROJECT_NAME = c-gtk
CC = gcc
SRC_DIR = ./src
LIB_DIR = ./lib

PKG_CFLAGS = $(shell pkg-config --cflags gtk4 hiredis)
PKG_LIBS = $(shell pkg-config --libs gtk4 hiredis) -lssl -lcrypto

$(PROJECT_NAME): $(SRC_DIR)/main.c
	$(CC) -I$(LIB_DIR) $(PKG_CFLAGS) -o $@ $< $(PKG_LIBS)

 
.PHONY: all clean