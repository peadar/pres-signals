#include "common.h" // includes signal, unistd, stdio, errno, string, etc.
volatile _Bool done;
static void signal_handler(int signo) {
   printf("received signal %d ('%s'), current errno: %s\n", signo, strsignal(signo), strerror(errno));
   done = 1;
}

int main() {
   signal(SIGALRM, signal_handler);
   alarm(1);
   while (!done) {
      strlen("hello world");
   }
}
