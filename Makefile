SHLIB = libshellshared.so
STLIB = libshellstatic.a

CFLAGS = -fpic

OBJS = shell.o

all: $(SHLIB) $(STLIB)

shared: $(SHLIB)

static: $(STLIB)

$(SHLIB): $(OBJS)
	gcc -shared $(OBJS) -o $(SHLIB)

$(STLIB): $(OBJS)
	ar rcs $(STLIB) $(OBJS)

shell.o: shell.c shell.h
	gcc -c $(CFLAGS) shell.c

.PHONY: clean

clean:
	rm -f $(OBJS) $(SHLIB) $(STLIB)