#include <cstring>
#include <iostream>

struct CmdFuncPair {
  char cmd[20];
  bool (*func)(char (& table)[10][5]);
};

bool clear(char (& table)[10][5]);
bool put(char (& table)[10][5]);
bool text(char (& table)[10][5]);
bool print(char (&table)[10][5]);
bool isPosValid(int x, int y);

int main() {
  char table[10][5]{};
  clear(table);

  char cmd[20];

  // const naming to function table
  const CmdFuncPair all_commands[] = {{"clear", clear},
                                      {"put", put},
                                      {"text", text},
                                      {"print", print}};
  const char stop_cmd[20]{"quit"};


  // event loop
  while (true) {
    std::cin >> cmd;
    if (std::strcmp(stop_cmd, cmd) == 0) {
      break;
    }
    for (const CmdFuncPair& cmd_func_pair : all_commands) {
      if (std::strcmp(cmd_func_pair.cmd, cmd) == 0) {
        bool is_valid = cmd_func_pair.func(table);
        if (!is_valid) {
          std::cout << "error\n";
        }
      }
    }
  }
  return 0;
}

bool isPosValid(int x, int y) {
  return x >= 0 && x <= 9 && y >= 0 && y <= 4;
}

bool clear(char (&table)[10][5]) {
  for (int x = 0; x < 10; ++x) {
    for (int y = 0; y < 5; ++y) {
      table[x][y] = ' ';
    }
  }
  return true;
}

bool put(char (&table)[10][5]) {
  int x{};
  int y{};
  char c{};
  std::cin >> x >> y >> c;
  if (isPosValid(x, y)) {
    table[x][y] = c;
    return true;
  }
  return false;
}

bool text(char (&table)[10][5]) {
  int x{};
  int y{};
  char word[10];
  std::cin >> x >> y >> word;

  int len{0};
  while (word[len] != '\0') {
    ++len;
  }

  if (isPosValid(x + len - 1, y)) {
    for (int i = 0; i < len; i++) {
      table[x + i][y] = word[i];
    }
    return true;
  }
  return false;
}

bool print(char (&table)[10][5]) {
  for (int y = 0; y < 5; ++y) {
    for (int x = 0; x < 10; ++x) {
      std::cout << table[x][y];
    }
    std::cout << '\n';
  }
  return true;
}