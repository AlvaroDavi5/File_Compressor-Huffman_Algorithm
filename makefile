
BIN_NAME=compressor

C_SOURCE=$(wildcard ./source/*.c)
H_SOURCE=$(wildcard ./include/*.h)

OBJ=$(subst .c,.o,$(subst source,object,$(C_SOURCE)))

CPL=gcc

CPL_FLAGS=-c   \
          -lm  \
          -W   \
          -Wall


VALGRIND_FLAGS=-s \
           --leak-check=full \
           --show-leak-kinds=all \
           --show-reachable=yes \
           --track-origins=yes \
           --verbose



run: all
	@ ./bin/${BIN_NAME}


valgrind: all
	@ clear
	@ valgrind ${VALGRIND_FLAGS} ./bin/${BIN_NAME} zip ./input/porque_aprender_programação.txt


diff: all
	@ echo ''
	@ diff -r ./input/porque_aprender_programação.txt ./output/uncompressed_file.txt --color=always


all: objectFolder ./bin/${BIN_NAME}
	@ echo " \033[1;32m  Done!  \033[0m "
	@ echo ''


objectFolder:
	@ mkdir -p input
	@ mkdir -p output
	@ mkdir -p object
	@ mkdir -p bin


./bin/${BIN_NAME}: ${OBJ}
	@ ${CPL} $^ -o $@
	@ echo " \033[0;33m  Building Binary \033[43;1;37m$@\033[0m\033[0;33m  \033[0m "
	@ echo ''


./object/%.o: ./source/%.c ./include/%.h
	@ ${CPL} $< ${CPL_FLAGS} -o $@ -I ./include
	@ echo " \033[0;35m  Generating compilation object \033[45;1;37m$@\033[0m\033[0;35m  \033[0m "
	@ echo ''


./object/main.o: ./source/main.c ${H_SOURCE}
	@ ${CPL} $< ${CPL_FLAGS} -o $@ -I ./include
	@ echo " \033[0;34m  Generating compilation object \033[44;1;37m$@\033[0m\033[0;34m  \033[0m "
	@ echo ''


clean:
	@ rm -rf ./object/*.o ./object/*.i ./object/*.s *~ ./bin/${BIN_NAME}
	@ rmdir object bin
	@ rm -rf ./output/*.txt ./temp/
	@ echo " \033[1;31m  Removing binary \033[41;1;37m./bin/${BIN_NAME}\033[0m\033[1;31m and compilation objects \033[41;1;37m${OBJ}\033[0m\033[1;31m and backup or output files  \033[0m "
	@ echo ''

