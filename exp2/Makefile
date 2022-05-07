INCLUDE_PATH = ./include
SRC_PATH = ./src
TARGET_PATH = ./target

TARGET = ${TARGET_PATH}/a.out
SMALL_TEMP_IMAGE = ${TARGET_PATH}/1.ppm
BIG_TEMP_IMAGE = ${TARGET_PATH}/2.ppm

SMALL_TARGET_IMAGE = ${TARGET_PATH}/1.jpg
BIG_TARGET_IMAGE = ${TARGET_PATH}/2.jpg

BI_SMALL_TEMP_IMAGE = ${TARGET_PATH}/3.ppm
BI_BIG_TEMP_IMAGE = ${TARGET_PATH}/4.ppm

BI_SMALL_TARGET_IMAGE = ${TARGET_PATH}/3.jpg
BI_BIG_TARGET_IMAGE = ${TARGET_PATH}/4.jpg

CC = g++
CCFLAGS = -I${INCLUDE_PATH} -std=c++17 -O2 -Wall -Wextra -pedantic-errors -Werror

${TARGET}:
	${CC} ${SRC_PATH}/main.cc ${CCFLAGS} -o ${TARGET}
all:
	make clean && make ${TARGET} && ${TARGET}
	make picture # && code ${SMALL_TARGET_IMAGE} && code ${BIG_TARGET_IMAGE} && code ${BI_SMALL_TARGET_IMAGE} && code ${BI_BIG_TARGET_IMAGE}
picture:
	python -c "import cv2;cv2.imwrite('${SMALL_TARGET_IMAGE}', cv2.imread('${SMALL_TEMP_IMAGE}'))"
	python -c "import cv2;cv2.imwrite('${BIG_TARGET_IMAGE}', cv2.imread('${BIG_TEMP_IMAGE}'))"
	python -c "import cv2;cv2.imwrite('${BI_SMALL_TARGET_IMAGE}', cv2.imread('${BI_SMALL_TEMP_IMAGE}'))"
	python -c "import cv2;cv2.imwrite('${BI_BIG_TARGET_IMAGE}', cv2.imread('${BI_BIG_TEMP_IMAGE}'))"
clean:
	mkdir -p ${TARGET_PATH}
	${RM} -r ${TARGET} ${TARGET_PATH}/*.ppm ${TARGET_PATH}/*.jpg
.PHONY: all clean picture
