INCLUDE_PATH = ./include
SRC_PATH = ./src
TARGET_PATH = ./target
DATA_PATH = ./data
PICTURE_PATH = ./picture

TARGET = ${TARGET_PATH}/a.out
CC = g++
CCFLAGS = -I${INCLUDE_PATH} -std=c++17 -O2 -Wall -Wextra -Werror

${TARGET}:
	${CC} ${SRC_PATH}/main.cc ${CCFLAGS} -o ${TARGET}
data:
	mkdir -p ${DATA_PATH}
	${CC} ${SRC_PATH}/generate.cc ${CCFLAGS} -o ${TARGET}
	${TARGET}
	${RM} ${TARGET}
paint: 
	python ${SRC_PATH}/main.py
	code ${PICTURE_PATH}/1.jpg
all:
	make clean && make ${TARGET} && ${TARGET}
clean:
	mkdir -p ${TARGET_PATH}
	${RM} -r ${TARGET}
.PHONY: all clean data
