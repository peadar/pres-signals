#!/usr/bin/python3
import pexpect
import sys
import gdb

proc = gdb.Gdb("./basic")
proc.runcmd("break signal_handler")
proc.runcmd("run")
proc.runcmd("where")
proc.runcmd("frame 1")
proc.runcmd("print $rip")
proc.runcmd("disas $1")
proc.quit()
