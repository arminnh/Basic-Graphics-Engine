CXXFLAGS   = -Wall -Wextra -g3 -fstack-protector-all
LDFLAGS    =
EXECUTABLE = bin/engine
EXTENSION  = cc
SOURCES    = $(shell find ./src/ -name '*.cc')
OBJECTS    = $(SOURCES:.cc=.o)
DEPFILES   = $(SOURCES:.cc=.d)

allclean: all clean

.PHONY: all
all: $(OBJECTS)
	mkdir -p bin
	$(CXX) $(LDFLAGS) $^ -o $(EXECUTABLE)

# create depfiles
%.d: %.$(EXTENSION)
	$(CXX) $(CXXFLAGS) -MM $< -o $@

-include $(DEPFILES)

.PHONY: clean
clean:
	find . -name '*.o' -delete
	find . -name '*.d' -delete
	find . -name '*~'  -delete
