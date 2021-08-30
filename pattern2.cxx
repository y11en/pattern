#include <string>
#include <iostream>

struct Player { 
  std::string name;
  int hitpoints;
  int coins; 
};

void get_hint(const Player& p) {
  std::cout<< p.name<< " -- ";
  inspect(p) {
    is [hitpoints: 1]             => std::cout<< "You're almost destroyed.\n";
    is [hitpoints: 10, coins: 10] => std::cout<< "I need the hints from you!\n";
    is [coins: 10]                => std::cout<< "Get more coins!\n";
    is [hitpoints: 10]            => std::cout << "Get more hitpoints!\n";
    [name: n] => {
      if (n != "The Bruce Dickenson")
        std::cout << "Get more hitpoints and ammo!\n";
      else
        std::cout << "More cowbell!\n";
    }
  }
}

int main() {
  get_hint({ "George Washington", 1000, 500 });
  get_hint({ "Julius Caeser", 1, 1000 });
  get_hint({ "Oliver Twist", 100, 10 });
}