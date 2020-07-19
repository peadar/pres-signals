#!/usr/bin/python3
import pexpect
import sys
import gdb

proc = gdb.Gdb("./full")
proc.runcmd("b signal_handler")
proc.runcmd("run")
proc.runcmd("p *si")
proc.runcmd("p *(ucontext_t *)v")
proc.quit()
