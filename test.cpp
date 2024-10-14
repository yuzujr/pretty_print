#include "print.h"
using stdprint::print, stdprint::println;

int main() {
    print("this is pretty_print\n");
    for (int i = 0; i < 10; i++) {
        println("Hello, World! i: {}", i);
    }
    return 0;
}
