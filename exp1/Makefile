INCLUDE_PATH = ./include
SRC_PATH = ./src

CC = g++
CCFLAGS = -I${INCLUDE_PATH} -std=c++17 -O2 -Wall -Wextra -Werror


target = ./a.out

target:
	${CC} ${SRC_PATH}/main.cc ${CCFLAGS} -o ${target}

all:
	make target
	${target}

clean:
	${RM} -f ${target}

.PHONY: all clean
