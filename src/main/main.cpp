#include <iostream>
#include <string>
#include "../grid/grid.hpp"



int main()
{

grid Domain(5, 5, "result.csv");

Domain.iterate(5);
Domain.iterate(5);
return 0;
}
