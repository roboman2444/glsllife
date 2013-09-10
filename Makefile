CC = gcc
LDFLAGS = -lGL -lGLU -lGLEW `sdl-config --libs`  -lm
CFLAGS = -Wall -O3 `sdl-config --cflags`
OBJECTS = glsllife.o sdlstuff.o glstuff.o shaderstuff.o filestuff.o texture.o

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

glsllife: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)
clean:
	@echo cleaning oop
	@rm -f $(OBJECTS)
	@rm -f glsllife
