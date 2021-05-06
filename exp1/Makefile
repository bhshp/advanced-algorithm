INCLUDE_PATH = ./include
SRC_PATH = ./src
TARGET_PATH = ./target
PICTURE_PATH = ./picture

TARGET = ${TARGET_PATH}/a.out
CC = g++
CCFLAGS = -I${INCLUDE_PATH} -std=c++17 -O2 -Wall -Wextra -Werror

${TARGET}:
	${CC} ${SRC_PATH}/main.cc ${CCFLAGS} -o ${TARGET}
paint: 
	python ${SRC_PATH}/main.py
	code ${PICTURE_PATH}/1.jpg
all:
	make clean && make ${TARGET} && ${TARGET}
clean:
	mkdir -p ${TARGET_PATH}
	${RM} -r ${TARGET} ${TARGET_PATH}/*.txt
.PHONY: all clean data
