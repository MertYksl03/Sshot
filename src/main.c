// The runner

#include "app.h"

// Command line arguments can be added later for things like window size, dev mode, etc.
int main(void) {
    
    if (APP_INIT() != APP_SUCCESS) {
        return 1;
    }
    uint8_t status = APP_RUN();
    APP_QUIT();
    return status;
}