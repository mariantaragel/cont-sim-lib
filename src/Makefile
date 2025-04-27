# Project: Continuous simulation library
# Author: Marián Tarageľ (xtarag01)
# Year: 2025

EXECUTABLE = main
LOGIN = xtarag01
SERVER = merlin.fit.vutbr.cz
SERVER_DIR = ~/SNT/project
ZIP_FILE = $(LOGIN).zip
TUMOR_OBJS = tumor.o sim.o rk4.o euler.o ode.o ab4.o integrator.o
HIV_OBJS = hiv.o sim.o rk4.o euler.o ode.o ab4.o integrator.o
TANK_OBJS = tank.o sim.o rk4.o euler.o ode.o ab4.o integrator.o

CXX = g++
CXXFLAGS = -Wall -Werror -pedantic -std=c++20

.PHONY = all tumor hiv tank clean pack upload

all: tumor hiv tank

tumor: $(TUMOR_OBJS)
	$(CXX) $(TUMOR_OBJS) -o tumor

hiv: $(HIV_OBJS)
	$(CXX) $(HIV_OBJS) -o hiv

tank: $(TANK_OBJS)
	$(CXX) $(TANK_OBJS) -o tank

tumor_plot:
	gnuplot ../plot_scripts/plot_tumor.gp

hiv_plot:
	gnuplot ../plot_scripts/plot_hiv.gp

tank_plot:
	gnuplot ../plot_scripts/plot_tank.gp

clean:
	rm -f tumor hiv tank *.o $(ZIP_FILE)

pack: $(ZIP_FILE)

$(ZIP_FILE): *.cpp *.hpp Makefile xtarag01.pdf
	zip $@ $^

upload: $(ZIP_FILE)
	scp $^ $(SERVER):$(SERVER_DIR)
	ssh $(LOGIN)@$(SERVER) \
		"cd $(SERVER_DIR) && unzip $^ && make"
