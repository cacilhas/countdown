CC?= clang
LD= $(CC)
RM= rm -f
INSTALL= install --mode=0755 --strip
DEST?= $(HOME)/.local/bin
SOURCES= $(shell echo $(wildcard *.c) | sed 's/\<main\.c\>//')
OBJECTS= $(SOURCES:.c=.o)
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


install: $(TARGET)
	$(INSTALL) $< $(DEST)/


uninstall:
	$(RM) $(DEST)/$(TARGET)


%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@
