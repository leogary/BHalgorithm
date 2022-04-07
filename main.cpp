#include <cmath>
#include <iostream>
#include <map>
#include <random>
#include <string>
#include <vector>

#include "bh.hpp"

int main() {
    // freopen("C:\\c++\\out.txt", "r", stdin);
    freopen("D:\\c++\\c++\\Bhalgorithm\\out.csv", "w", stdout);
    int generation, population, funcid, dim = 30;
    std::string func;
    // std::cout << "0 Ackley 1 Rastrigin 2 Sphere 3 Rosenbrock 4 Michalewicz" << std::endl;
    // std::cout << "generation population functionid" << std::endl;
    std::cin >> generation >> population >> funcid;
    /*std::cout << "generation=" << generation << std::endl
              << " population=" << population << std::endl;*/
    std::cout << dim << std::endl;

    switch (funcid) {
        case 0:
            func = "Ackley";
            break;
        case 1:
            func = "Rastrigin";
            break;
        case 2:
            func = "Sphere";
            break;
        case 3:
            func = "Rosenbrock";
            break;
        case 4:
            func = "Michalewicz";
            break;
    }
    // std::cout << func << std::endl;
    bh test(population, generation, dim, func);
    test.start();
    // std::cout << "globalbestfit= " << test.globalbestfit << std::endl;
    // fclose(stdin);
    fclose(stdout);
}