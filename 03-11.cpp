#include <string>

int main() {
    const std::string s = "Keep out!";
    for (auto &c : s) { /* ... */ }   // c is a reference to const char
}
