INCLUDE_PATH = ./include
SRC_PATH = ./src
TARGET_PATH = ./target

TARGET = ${TARGET_PATH}/a.out
TEMP_IMAGE = ${TARGET_PATH}/out.ppm
TARGET_IMAGE = ${TARGET_PATH}/out.jpg
CC = g++
CCFLAGS = -I${INCLUDE_PATH} -std=c++17 -O2 -Wall -Wextra -Werror -pedantic-errors

${TARGET}:
	${CC} ${SRC_PATH}/main.cc ${CCFLAGS} -o ${TARGET}
all:
	make clean && make ${TARGET} && ${TARGET} && make picture && code ${TARGET_IMAGE}
picture: ${TARGET} ${TEMP_IMAGE}
	python -c "import cv2;cv2.imwrite('${TARGET_IMAGE}', cv2.imread('${TEMP_IMAGE}'))"
clean:
	mkdir -p ${TARGET_PATH}
	${RM} -r ${TARGET} ${TEMP_IMAGE} ${TARGET_IMAGE}
.PHONY: all clean picture
