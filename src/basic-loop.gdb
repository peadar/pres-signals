#!/bin/python
import pexpect
import sys
import gdb

proc = gdb.Gdb("./basic-loop")
proc.runcmd("break signal_handler")
proc.runcmd("run")
proc.runcmd("where")
proc.runcmd("kill")
proc.quit()
