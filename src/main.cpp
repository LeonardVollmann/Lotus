#include "core/engine.h"

#include <iostream>

int main()
{
    lotus::Engine engine(60, 600, 400, "Lotus Engine");
    engine.start();
}