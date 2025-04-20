# Project: Continuous simulation library
# Author: Marián Tarageľ (xtarag01)
# Year: 2025

EXECUTABLE = main
LOGIN = xtarag01
SERVER = merlin.fit.vutbr.cz
SERVER_DIR = ~/SNT/project
ZIP_FILE = $(LOGIN).zip
OBJS = $(EXECUTABLE).o sim.o rk4.o euler.o ode.o ab4.o integrator.o

CXX = g++
CXXFLAGS = -Wall -Werror -pedantic -g -std=c++20

.PHONY = all run clean pack upload

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CXX) $(OBJS) -o $(EXECUTABLE)

run: $(EXECUTABLE)
	./$(EXECUTABLE) $(ARGS)

clean:
	rm -f $(EXECUTABLE) *.o $(ZIP_FILE)

pack: $(ZIP_FILE)

$(ZIP_FILE): *.cpp *.hpp Makefile xtarag01.pdf
	zip $@ $^

upload: $(ZIP_FILE)
	scp $^ $(SERVER):$(SERVER_DIR)
	ssh $(LOGIN)@$(SERVER) \
		"cd $(SERVER_DIR) && unzip $^ && make"

gdb: $(EXECUTABLE)
	gdb -exec $(EXECUTABLE) --args $(ARGS)