#include "am_bsp.h"
#include "am_util_delay.h"
#include "am_devices_led.h"

#include "tensorflow/lite/micro/micro_error_reporter.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/micro/micro_mutable_op_resolver.h"
#include "tensorflow/lite/micro/system_setup.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/core/api/error_reporter.h"

namespace {
tflite::ErrorReporter* error_reporter = nullptr;
}  // namespace

int main(int argc, char* argv[]) {
    am_devices_led_array_init(am_bsp_psLEDs, AM_BSP_NUM_LEDS);
    am_devices_led_array_out(am_bsp_psLEDs, AM_BSP_NUM_LEDS, 0x00000000);

    TF_LITE_REPORT_ERROR(error_reporter, "setup");

    int delay_time = 1000;

    int leds[4] = { 
            AM_BSP_LED_YELLOW,
            AM_BSP_LED_GREEN,
            AM_BSP_LED_BLUE,
            AM_BSP_LED_RED,
     };
    
    for(int idx = 0; idx < 4; idx++)
        am_devices_led_off(am_bsp_psLEDs, leds[idx]);

    int loopid = 0;

    while(true) {
        TF_LITE_REPORT_ERROR(error_reporter, "loop: %d", loopid++);
        for(int idx = 0; idx < 4; idx++)
        {
            am_devices_led_on(am_bsp_psLEDs, leds[idx]);
            am_util_delay_ms(delay_time);
            am_devices_led_off(am_bsp_psLEDs, leds[idx]);
        }
    }
}