#include <cstdlib>
#include "application.h"

std::shared_ptr<Application> SP_APP;

int main(int argc, char** argv) {

    SP_APP = std::make_shared<Application>();    
    SP_APP->run();

    return EXIT_SUCCESS;
}