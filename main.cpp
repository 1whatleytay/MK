#include <iostream>

#include "Builder.h"

int main(int count, char **args) {
    if (count <= 1) {
        logInfo("Usage: mk path/to/main");
        return 1;
    }

    try {
        Builder builder = Builder::fromFile(args[1]);
        builder.build();
    } catch (Exception &e) {
        logError(e.info());
        log("[Build Failed]");
    }

    return 0;
}
