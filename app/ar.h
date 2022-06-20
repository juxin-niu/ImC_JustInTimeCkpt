
#ifndef APPS_AR_H_
#define APPS_AR_H_

#include <lib/math_lib/accel.h>
#include <lib/math_lib/mspmath/msp-math.h>
#include <stdint.h>

#define AR_NUM_WARMUP_SAMPLES   3       // Number of samples to discard before recording training set
#define AR_ACCEL_WINDOW_SIZE    3
#define AR_MODEL_SIZE           5
#define AR_SAMPLE_NOISE_FLOOR   10      // TODO: (This TODO is from InK) made up value
#define AR_SAMPLES_TO_COLLECT   32      // Number of classifications to complete in one experiment

typedef threeAxis_t_8 accelReading;
typedef accelReading accelWindow[AR_ACCEL_WINDOW_SIZE];

typedef struct {
    uint16_t meanmag;
    uint16_t stddevmag;
} ar_features_t;

typedef enum {
    CLASS_STATIONARY,
    CLASS_MOVING,
} ar_class_t;


typedef enum {
    MODE_IDLE = 3,
    MODE_TRAIN_STATIONARY = 2,
    MODE_TRAIN_MOVING = 1,
    MODE_RECOGNIZE = 0, // default
} ar_run_mode_t;


#endif /* APPS_AR_H_ */
