// set_symmetric_difference example
/*#include <iostream>     // std::cout
#include <algorithm>    // std::set_symmetric_difference, std::sort
#include <vector>       // std::vector

int main () {
    int first[] = {5,10,15,20,25};
    int second[] = {50,40,30,20,10};
    std::vector<int> v(5);                      // 0  0  0  0  0  0  0  0  0  0
    std::vector<int>::iterator it;

    std::sort (first,first+5);     //  5 10 15 20 25
    std::sort (second,second+5);   // 10 20 30 40 50

    it=std::set_symmetric_difference (first, first+5, second, second+5, v.begin());
    //  5 15 25 30 40 50  0  0  0  0

    std::cout << "The symmetric difference has " << (v.size()) << " elements:\n";
    for (it=v.begin(); it!=v.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';

    return 0;
}*/