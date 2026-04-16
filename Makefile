CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic
INCLUDE = -Iinclude -Iexternal
SRCDIR = src
OBJDIR = build
TARGET = build/apartment_evaluator
WEB_TARGET = build/apartment_web

SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
WEB_SOURCES = $(filter-out $(SRCDIR)/main.cpp, $(SOURCES))
WEB_OBJECTS = $(WEB_SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

all: $(TARGET) $(WEB_TARGET)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(TARGET): $(OBJDIR) $(filter-out $(OBJDIR)/web_server.o, $(OBJECTS))
	$(CXX) $(CXXFLAGS) -o $@ $(filter-out $(OBJDIR)/web_server.o, $(OBJECTS))

$(WEB_TARGET): $(OBJDIR) $(WEB_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $(WEB_OBJECTS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

web: $(WEB_TARGET)
	./$(WEB_TARGET)

clean:
	rm -rf $(OBJDIR)/*.o $(TARGET) $(WEB_TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(OBJDIR)

.PHONY: all run clean
