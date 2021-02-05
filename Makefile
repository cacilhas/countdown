ifeq ($(shell id -u), 0)
PREFIX= /usr/local
else
PREFIX= $(HOME)/.local
endif

CC?= clang
LD= $(CC)
MD= mkdir -p
RM= rm -f
INSTALL= install --mode=0755 --strip
SOURCES= $(shell echo $(wildcard *.c) | sed 's/\<main\.c\>//')
OBJECTS= $(SOURCES:.c=.o)
DEST?= $(PREFIX)/bin
TARGET= countdown

CFLAGS= -D_XOPEN_SOURCE_EXTENDED $(shell pkg-config --cflags ncursesw) -fblocks --std=c99 -Wall
LIBS= $(shell pkg-config --libs ncursesw) -lBlocksRuntime
TEST_LIBS= $(LIBS) $(shell pkg-config --libs cunit)

#-------------------------------------------------------------------------------
.PHONY: clean mrproper install uninstall


all: $(TARGET)


clean:
	$(RM) *.o


mrproper: clean
	$(RM) $(TARGET)


$(TARGET): main.o $(OBJECTS)
	$(LD) $^ $(LIBS) -o $@


$(DEST):
	$(MD) $@


install: $(TARGET)
	$(INSTALL) $< $(DEST)/


uninstall:
	$(RM) $(DEST)/$(TARGET)


%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@
