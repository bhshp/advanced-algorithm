INCLUDE_PATH = ./include
SRC_PATH = ./src
TARGET_PATH = ./target

TARGET = ${TARGET_PATH}/a.out
CC = g++
CCFLAGS = -I${INCLUDE_PATH} -std=c++17 -O3 -Wall -Wextra -Werror -m32

${TARGET}:
	${CC} ${SRC_PATH}/main.cc ${CCFLAGS} -o ${TARGET}
all:
	make clean && make ${TARGET} && ${TARGET}
clean:
	mkdir -p ${TARGET_PATH}
	${RM} -r ${TARGET}
.PHONY: all clean data
