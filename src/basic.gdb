#!/usr/bin/python3
import pexpect
import sys
import gdb

proc = gdb.Gdb("./basic")
proc.runcmd("break signal_handler")
proc.runcmd("run")
proc.runcmd("where")
proc.runcmd("kill")
proc.quit()
