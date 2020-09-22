#include <iostream>

#include "builder.h"

#define NO_CATCH

int main(int count, char **args) {
    if (count <= 1) {
        logInfo("Usage: mk path/to/main");
        return 1;
    }

#ifndef NO_CATCH
    try {
#endif
        Builder builder = Builder::fromFile(args[1]);
        builder.build();
        log("[Build Done]");
#ifndef NO_CATCH
    } catch (Exception &e) {
        logError(e.info());
        log("[Build Failed]");
    }
#endif

    return 0;
}
