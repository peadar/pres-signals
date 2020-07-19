.PHONY: clean all
.SUFFIXES: .htmlc .htmltxt .txt .gdb .htmlgdb .strace

CFLAGS += -g

TARGETS = basic htmlfilt basic.out.html basic.gdb.out.html basic-loop basic-loop.out.html basic-loop.gdb.out.html basic-sigframe.gdb.out.html basic.strace.html  \
basic.c.html \
basic-loop.c.html \
do_signal.c.html \
do_syscall_64.c.html \
exit_to_usermode_loop.c.html \
handle_signal.c.html \
htmlfilt.c.html \
prepare_exit_to_usermode.c.html \
setup_rt_frame.c.html \
syscall_return_slowpath.c.html \
basic-showrtact.gdb.out.html \
rt_sigreturn.c.html \
full.gdb.out.html \
full.c.html

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
	rm -f $(TARGETS) *.o *.out *.*.html
