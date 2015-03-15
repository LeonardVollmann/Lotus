#include "core/engine.h"
#include "maths/math.h"

#include <iostream>

int main()
{
    using namespace lotus;
    using namespace lotus::maths;
    
    vec3f x(1.0f, 0.0f, 0.0f);
    vec3f y(0.0f, 1.0f, 0.0f);
    vec3f z = x.cross(y);
    
    std::cout << z.getX() << ", " << z.getY() << ", " << z.getZ() << std::endl;
    
    Engine engine(60, 600, 400, "Lotus Engine");
    engine.start();
    
    return 0;
}