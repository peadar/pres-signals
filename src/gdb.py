import pexpect
import sys
class Gdb(object):
    def __init__(self, executable):
        self.child =pexpect.spawn("env TERM=dumb gdb -q %s" % executable, encoding="utf-8", echo=False)
        self.child.logfile = sys.stdout
        self.child.expect("(gdb)")

    def runcmd(self, cmd):
        self.child.sendline(cmd)
        self.child.expect("(gdb)")

    def quit(self):
        self.child.sendline("quit")


