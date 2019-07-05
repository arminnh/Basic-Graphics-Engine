CXXFLAGS   = -Wall -Wextra -g3 -fstack-protector-all
LDFLAGS    =
EXECUTABLE = engine
EXTENSION  = cc
SOURCES    = $(shell find ./src/ -name '*.cc')
OBJECTS    = $(SOURCES:.cc=.o)
DEPFILES   = $(SOURCES:.cc=.d)

.PHONY: all
all: $(OBJECTS)
	$(CXX) $(LDFLAGS) $^ -o $(EXECUTABLE)

%.o: %.$(EXTENSION)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

-include $(DEPFILES)

.PHONY: clean
clean:
	$(RM) $(OBJECTS) $(DEPFILES) $(EXECUTABLE)
