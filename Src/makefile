# PROG from ../makefile

CXX      := g++
CXXFLAGS := -std=c++11 -Wall
LD       := g++
program  := ../${PROG}

OBJS := $(subst .cpp,.o,$(wildcard *.cpp))

.PHONY: all release debug clean

all: debug

-include $(subst .o,.d,${OBJS})

release: CXXFLAGS += -O2 -DNDEBUG
debug: CXXFLAGS += -g
release debug: ${program}

${program}: ${OBJS}
	${LD} -o $@ $^

%.o: %.d

%.d: %.cpp
	${CXX} ${CXXFLAGS} -MM -MT "$(subst .d,.o,$@) $@" $< > $@

clean:
	rm *.{d,o}
