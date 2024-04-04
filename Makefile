CC = gcc
CFLAGS = -Wall -Werror
CPPFLAGS = -MMD
SrcDir = src
BinDir = bin
ObjDir = obj
Test_name = main-test	

MainSrc = $(wildcard $(SrcDir)/geometry/*.c)
LibSrc = $(wildcard $(SrcDir)/libgeometry/*.c)

TestDir = test
LibTarget = $(ObjDir)/libgeometry/libgeometry.a
Target = $(BinDir)/main
LibTestDir = thirdparty
TestTarget = $(BinDir)/$(Test_name)

all: $(Target)

$(Target): $(ObjDir)/geometry/main.o $(LibTarget)
	$(CC) $(CFLAGS) -o $@ $^ -lm

$(LibTarget): $(ObjDir)/libgeometry/circle.o
	ar rcs $@ $^

$(ObjDir)/geometry/main.o: $(MainSrc)
	$(CC) -c $(CFLAGS) $< $(CPPFLAGS) -o $@ -I $(SrcDir)/libgeometry/  

$(ObjDir)/libgeometry/circle.o: $(LibSrc)
	$(CC) -c $(CFLAGS) $< $(CPPFLAGS) -o $@ -I $(SrcDir)/libgeometry

.PHONY: clean

run:
	./$(Target)

test: $(TestTarget)
	$(BinDir)/$(Test_name)

$(TestTarget): $(ObjDir)/$(TestDir)/main.o $(ObjDir)/$(TestDir)/test.o
	$(CC) -I $(SrcDir)/libgeometry -I $(LibTestDir) $^ $(LibTarget) -o $(BinDir)/$(Test_name) -lm

$(ObjDir)/$(TestDir)/main.o: $(TestDir)/main.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -I $(LibTestDir) -c $< -o $@

$(ObjDir)/$(TestDir)/test.o: $(TestDir)/test.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -I $(SrcDir)/libgeometry -I $(LibTestDir) -c $< -o $@

clean:
	rm -rf $(ObjDir)/libgeometry/*.o $(ObjDir)/geometry/*.o $(Target)
	rm -rf $(ObjDir)/libgeometry/*.d $(ObjDir)/geometry/*.d
	rm -rf $(LibTarget)
	rm -rf $(ObjDir)/test/*.o $(ObjDir)/test/*.d
	rm -rf $(BinDir)/$(Test_name)
format: 
	clang-format -i  $(MainSrc) $(LibSrc)

-include $(ObjDir)/geometry/%.d $(ObjDir)/libgeometry/%.d $(ObjDir)/test/%.d