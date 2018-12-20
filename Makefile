VPATH = ./src
CXXFLAGS =  -I "./include" -I "c:\freeglut\include"
CXXLIBDIR = -L "c:\freeglut\lib" 

assignment1:main.cpp
	g++ main.cpp $(CXXFLAGS) -o main.exe $(CXXLIBDIR)  -lopengl32 -lfreeglut -lglu32
	
clean:

	rm -f main.exe
	rm -f main.o