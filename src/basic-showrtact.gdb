#!/usr/bin/python3
import pexpect
import sys
import gdb

proc = gdb.Gdb("./basic")
proc.runcmd("catch syscall rt_sigaction")
proc.runcmd("run")
proc.runcmd("p *(struct kernel_sigaction *)$rsi")
proc.quit()
