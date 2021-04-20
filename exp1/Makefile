INCLUDE_PATH = ./include
SRC_PATH = ./src
TARGET_PATH = ./target
DATA_PATH = ./data
target = ${TARGET_PATH}/a.out

CC = g++
CCFLAGS = -I${INCLUDE_PATH} -std=c++17 -O2 -Wall -Wextra -Werror

${target}:
	${CC} ${SRC_PATH}/main.cc ${CCFLAGS} -o ${target}
data:
	mkdir -p ${DATA_PATH}
	${CC} ${SRC_PATH}/generate.cc ${CCFLAGS} -o ${target}
	${target}
	${RM} ${target}
paint: 
	python ${SRC_PATH}/main.py
	code ${TARGET_PATH}/1.jpg
all:
	make clean && make data && make ${target}
	${target} && make paint
clean:
	${RM} -r ${target} ${DATA_PATH}

.PHONY: all clean data
