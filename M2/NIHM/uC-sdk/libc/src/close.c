#include "reent.h"
#include "errno.h"
#include <fio.h>

int close(int fd) {
    if (!fio_is_open(fd)) {
        set_errno(EBADF);
        return -1;
    }
    
    return fio_close(fd);
}
