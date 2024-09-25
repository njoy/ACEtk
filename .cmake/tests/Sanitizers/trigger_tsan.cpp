#include <thread>
#include <iostream>
#include <string>
#include <map>
#include <functional>

// thread sanitizer is only on unix-like platforms
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

using map_t = std::map<std::string, std::string>;

void threadfunc(map_t& m) {
  m["foo"] = "bar" + std::to_string(1);
}

int main() {
  auto child_pid = fork();
  if (child_pid == 0){
    map_t m;
    m["foo"] = "baz";
    std::thread t(threadfunc, std::ref(m));
    std::cout << "foo=" <<  m["foo"]; //BOOM
    t.join();
    return 0;
  }

  int exit_status;
  wait(&exit_status);

  return (not exit_status);
}
