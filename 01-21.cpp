#include <iostream>
#include "Sales_item.h"

int main() {
    Sales_item item1, item2;
    std::cout << "Please enter two items with a same ISBN..." << std::endl;
    std::cin >> item1 >> item2;
    std::cout << "Their sum is" << std::endl;
    std::cout << item1 +item2 << std::endl;    
}
