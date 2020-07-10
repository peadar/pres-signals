#include "common.h" // includes signal, unistd, stdio, errno, string, etc.
static void signal_handler(int signo) {
   printf("received signal %d ('%s'), current errno: %s\n", signo, strsignal(signo), strerror(errno));
}
int main() {
   signal(SIGALRM, signal_handler);
   alarm(1);
   int rc = pause();
   printf("pause returned %d, errno is %s\n", rc, strerror(errno));
}
