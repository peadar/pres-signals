#define _GNU_SOURCE
#include "common.h" // includes signal, unistd, etc...
static void signal_handler(int signo, siginfo_t *si, void *v) {
   struct ucontext_t *uc = v;
   printf("received signal %d ('%s'), current errno: %s\n", signo,
           strsignal(signo), strerror(errno));
   fflush(stdout);
}
int main() {
   struct sigaction sa;

   memset(&sa, 0, sizeof sa);
   sa.sa_sigaction = signal_handler;
   sa.sa_flags = SA_SIGINFO;
   sigaction(SIGALRM, &sa, NULL);
   alarm(1);
   int rc = pause();
   printf("pause returned %d, errno is %s\n", rc, strerror(errno));
}
