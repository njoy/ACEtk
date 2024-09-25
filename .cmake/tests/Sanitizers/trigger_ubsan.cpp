// thread sanitizer is only on unix-like platforms
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv) {
  auto child_pid = fork();

  if (child_pid == 0){
    int k = 0x7fffffff;
    k += argc; // BOOM
    return 0;
  }

  int exit_status;
  wait(&exit_status);

  return (not exit_status);
}
