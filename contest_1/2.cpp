#include <cstring>
#include <iostream>

struct CmdFuncPair {
  char cmd[20];
  void (*func)(int&);
};

void deposit(int& savings);
void withdraw(int& savings);
void balance(int& savings);
void reset(int& savings);
void inc(int& savings);

int main() {
  int savings{0};
  char cmd[20];

  // const naming to function table
  const CmdFuncPair all_commands[] = {{"deposit", deposit},
                                      {"withdraw", withdraw},
                                      {"balance", balance},
                                      {"reset", reset},
                                      {"inc", inc}};
  const char stop_cmd[20]{"stop"};

  // event loop
  while (true) {
    std::cin >> cmd;
    if (std::strcmp(stop_cmd, cmd) == 0) {
      break;
    }
    for (const CmdFuncPair& cmd_func_pair : all_commands) {
      if (std::strcmp(cmd_func_pair.cmd, cmd) == 0) {
        cmd_func_pair.func(savings);
      }
    }
  }
  return 0;
}

void deposit(int& savings) {
  int sum{};
  std::cin >> sum;
  if (sum >= 0) {
    savings += sum;
  } else {
    std::cout << "error\n";
  }
}

void withdraw(int& savings) {
  int sum{};
  std::cin >> sum;
  if (savings < sum || sum < 0) {
    std::cout << "error\n";
  } else {
    savings -= sum;
  }
}
void balance(int& savings) { std::cout << savings << '\n'; }

void reset(int& savings) { savings = 0; }

void inc(int& savings) { savings += 1; }