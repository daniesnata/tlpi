CC=clang
CSTD=-std=c99
PORT=-D_XOPEN_SOURCE=600
BUILD=${CSTD} ${PORT} -Wall -Wextra -g -O0
BUILD_LFS=${CSTD} ${PORT} -D_FILE_OFFSET_BITS=64 -Wall -Wextra -g -O0

LIB=lib/tlpi_hdr.h \
	lib/get_num.h lib/get_num.c \
	lib/ename.c \
	lib/error_functions.h lib/error_functions.c

all: copy seek t_getopt bad_exclusive_open t_readv ex-tee ex-large_file ex-5.2

copy: error_functions.o
	${CC} ${BUILD} bin/error_functions.o fileio/copy.c -o bin/copy

seek: error_functions.o get_num.o
	${CC} ${BUILD} bin/error_functions.o bin/get_num.o fileio/seek_io.c -o bin/seek

t_getopt: error_functions.o
	${CC} ${BUILD} bin/error_functions.o getopt/t_getopt.c -o bin/t_getopt

error_functions.o:
	${CC} ${BUILD} lib/error_functions.c -o bin/error_functions.o -c

error_functions_lfs.o:
	${CC} ${BUILD_LFS} lib/error_functions.c -o bin/error_functions_lfs.o -c

get_num.o:
	${CC} ${BUILD} lib/get_num.c -o bin/get_num.o -c

bad_exclusive_open:
	${CC} ${BUILD} fileio/bad_exclusive_open.c -o bin/bad_exclusive_open

t_readv: error_functions.o
	${CC} ${BUILD} bin/error_functions.o fileio/t_readv.c -o bin/t_readv

ex-tee:
	${CC} ${BUILD} exercises/tee.c -o bin/ex/tee

ex-large_file: error_functions_lfs.o
	${CC} ${BUILD_LFS} bin/error_functions_lfs.o exercises/large_file.c -o bin/ex/largefile

ex-5.2: error_functions.o
	${CC} ${BUILD} lib/error_functions.c exercises/ex_5_2.c -o bin/ex/ex_5_2

.PHONY: clean
clean:
	rm bin/** bin/ex/**
