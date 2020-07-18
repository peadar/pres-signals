.PHONY: clean all
.SUFFIXES: .htmlc .htmltxt .txt .gdb .htmlgdb .strace

CFLAGS += -g

TARGETS = basic htmlfilt basic.c.html basic.out.html basic.gdb.out.html basic-loop basic-loop.out.html basic-loop.gdb.out.html basic-loop.c.html basic-sigframe.gdb.out.html basic.strace.html

all: $(TARGETS)


%.html: % htmlfilt
	./htmlfilt < $< > $@

%.out: %
	./$< > $@ 2>&1
%.strace: %
	strace -s8 ./$< 2> $@ > /dev/null

%: %.o
	$(CC) -o $@ $<

clean:
	rm -f $(TARGETS) *.o *.out
