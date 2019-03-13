CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra
INC := -I include -I lib
LIB := -L lib
SRCDIR := src
OBJDIR := obj
TESTDIR := tests
TARGET := bin/solve
OUTFILE := data/*.json

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

$(TARGET): $(OBJECTS)
	@echo "Linking..."
	@echo "$(CXX) $^ -o $(TARGET) $(LIB)"; $(CXX) $^ -o $(TARGET) $(LIB)

$(OBJDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(OBJDIR)
	@echo "$(CXX) $(CXXFLAGS) $(INC) -c -o $@ $<"; $(CXX) $(CXXFLAGS) $(INC) -c -o $@ $<

clean:
	@echo "Cleaning..."; 
	@echo "$(RM) -r $(OBJDIR) $(TARGET) $(OUTFILE)"; $(RM) -r $(OBJDIR) $(TARGET) $(OUTFILE)

.PHONY: all build clean debug release