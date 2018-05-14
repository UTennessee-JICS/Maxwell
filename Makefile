# Makefile for the FE proto-code

# We specify the application name
target = test

# We specify if we want to compile in debug mode
debug-mode = off

CXX = g++

#Define the compile and link flags depending the debug level
ifeq ($(debug-mode),on)
  compile-flags = -g -Wall -c -DDEBUG
  obj-ext = go
  link-flags = -g -Wall -DDEBUG
  mode = DEBUG
else
  compile-flags = -O3 -c
  obj-ext = o
  link-flags = -O3
  mode = OPTIMIZED
endif

appsources  := $(shell echo *.cpp)
appincludes := $(wildcard *.h)
appobjects  := $(appsources:%.cpp=%.$(obj-ext) )

libsources  := $(shell echo lib/source/*.cpp)
libobjects  := $(libsources:lib/source/%.cpp=lib/source/%.$(obj-ext) )

LIBSRCDIR	:= lib/src

%.$(obj-ext):  $(LIBSRCDIR)/%.cpp %.cpp *.h 
	@echo "=== Compiling application in "$(mode)" mode ===="$(<F)
	$(CXX) $(compile-flags) $< -o $@

$(target): $(libobjects) $(appobjects) Makefile
	@echo "==== Linking "$(target)" ==== "
	$(CXX) -o $@ $(appobjects) $(libobjects) $(link-flags)
	$(CXX) $(link-flags) -o $(target) $(appobjects) $(libobjects)

main.$(obj-ext): main.cpp
	@echo "$(libsources)"
	@echo "=== Compiling application in "$(mode)" mode ====main.cpp"
	$(CXX) $(compile-flags) main.cpp -o main.$(obj-ext)

#-include lib/Makefile.dep
#Makefile.dep:
#	$(CC) $(compile-flags) -MM *.[ch] > lib/Makefile.dep


.PHONY:  run clean-data clean clean-lib

run: $(target)
	@echo "==== Running "$(target)" in "$(mode)" mode ===="
	./$(target)

clean-data:
	rm -f *gpl

clean: clean-data
	rm -f $(target) $(appobjects)

clean-lib: clean
	rm -f $(libobjects)
