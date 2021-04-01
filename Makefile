.NULL: .exe

SOURCES = $(wildcard *.cpp)
HEADERS = $(wildcard *.h)
TARGETS = $(basename $(SOURCES))


INIT_SHADER = common/initshader.o

CXXOPTS = -mwin32 -g -std=c++2a
CXXDEFS = -DFREEGLUT_STATIC -DGLEW_STATIC
CXXINCS = -Iinclude

CXXFLAGS = $(CXXOPTS) $(CXXDEFS) $(CXXINCS)



LDOPTS =
LDDIRS =
LDLIBS = -lopengl32 -lglew32 -lfreeglut -lgdi32 -lwinmm

LDFLAGS = $(LDOPTS) $(LDDIRS) $(LDLIBS)

DIRT = $(wildcard *.o *.i *~ */*~ *.log)
#-----------------------------------------------------------------------------

.PHONY: Makefile

default all: $(TARGETS)

$(TARGETS): $(INIT_SHADER)

%: %.cpp
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@

#-----------------------------------------------------------------------------

%.i: %.cpp
	$(CXX) -E $(CXXFLAGS) $< | uniq > $@

#-----------------------------------------------------------------------------

clean:
	$(RM) $(DIRT)

rmtargets:
	$(RM) $(TARGETS)

clobber: clean rmtargets
