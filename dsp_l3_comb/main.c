#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "msp432_boostxl_init.h"
#include "msp432_arm_dsp.h"

uint16_t processSample(uint16_t x) {
    static float32_t taps[9];

    // white noise
    float32_t input = adc14_to_f32(0x1800 + rand() % 0x1000);

    // test signal
    // float32_t input = adc14_to_f32(x);

    uint32_t i;
    for (i=0; i<8; i++)
        taps[8-i] = taps[7-i];
    taps[0] = input;

    return f32_to_dac14(taps[0] - taps[8]);
}

#include <stdio.h>

int main(void) {
    WDT_A_hold(WDT_A_BASE);

    msp432_boostxl_init_intr(FS_32000_HZ, BOOSTXL_J1_2_IN, processSample);
    msp432_boostxl_run();

    return 1;
}
