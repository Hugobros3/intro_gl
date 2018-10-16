UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
LIBS=-lglfw -lGL -lGLEW -lm
BINARY=demo
else
LIBS=-lglfw3 -lopengl32 -lgdi32 -lglew32
BINARY=demo.exe
endif

all: $(BINARY)

$(BINARY): main.c
	gcc -std=c99 -o demo main.c ${LIBS}

clean:
	rm demo*
