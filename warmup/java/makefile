ifeq ($(OS),Windows_NT) 
	RM = del /Q /F
	CP = copy /Y
endif

JCCFLAGS = -g
JCC = javac

.SUFFIXES: .java .class
.java.class:
	$(JCC) $(JCCFLAGS) $*.java

sources = $(wildcard *.java)
classes = $(sources:.java=.class)

all: program

program: $(classes)

clean:
	$(RM) *.class

jar: $(classes)
	jar cvf program.jar $(classes)

.PHONY: all program clean jar
