#  Makefile for SIMLIB
#  ===================

# name of the compiler for C++ language
CXX?=g++

# installed library home:
SIMLIB_DIR=../src

# C++ compiler flags
CXXFLAGS  = -Wall -m64 -O2 -g -I$(SIMLIB_DIR)

# dependencies:
SIMLIB_DEPEND=$(SIMLIB_DIR)/simlib.so $(SIMLIB_DIR)/simlib.h

# Implicit rule to compile modules
% : %.cc
	@#$(CXX) $(CXXFLAGS) -static -o $@  $< $(SIMLIB_DIR)/simlib.a -lm
	$(CXX) $(CXXFLAGS) -o $@  $< $(SIMLIB_DIR)/simlib.so -lm

all: simulation

simulation: Stage.h Missile.h Booster.h Booster.cc Missile.cc simulation.cc $(SIMLIB_DEPEND)
	@#$(CXX) $(CXXFLAGS) -static -o $@ $^ $(SIMLIB_DIR)/simlib.a -lm
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SIMLIB_DIR)/simlib.a -lm

#
run: all
	./simulation

plot: run
	@./0-plot-all-ps.sh

clean:
	rm -f simulation *.o gmon.out

clean-data:
	rm -f *.dat *.out *.png *.ps reference-outputs/*.log

clean-all: clean clean-data

REFOUT=reference-outputs/*.dat reference-outputs/*.out reference-outputs/*.sh

pack:
	tar czf examples.tar.gz *.cc *.plt *.txt *.sh Makefile.* $(REFOUT)

