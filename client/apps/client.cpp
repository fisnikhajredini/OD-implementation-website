#include "Client.h"

int32_t main(int32_t argc, char **argv) {
    automotive::miniature::Client p(argc, argv);
    return p.runModule();
}

