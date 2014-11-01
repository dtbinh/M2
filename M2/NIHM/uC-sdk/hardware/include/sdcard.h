#pragma once

#include <decl.h>
#include <gpio.h>
#include <ssp.h>

typedef struct {
    // these are to be filled by caller
    pin_t cs;
    ssp_t ssp;
    // these are read-only publics
    int got_timeout:1, error_state:1;
    // these should remain opaque
    int v2:1, sdhc:1;
} sdcard_t;

BEGIN_DECL

int sdcard_init(sdcard_t * sdcard);
int sdcard_read(sdcard_t * sdcard, uint8_t * data, unsigned int block);

END_DECL
