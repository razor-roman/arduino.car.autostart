// with voltage divider
/*
 * SIMPLE ARDUINO CAR TACHOMETER
 */

const int REV_LIMITER_RPM             = 5800;

const int NUMBER_OF_CYLINDERS = 4;
const int LED_UPDATE_INTERVAL = 200;

/*
 * Last led state update time in ms, used to calculate the time from last update
 */
unsigned long lastUpdateTime  = 0;

/*
 * Amount of spark fires in a single interval
 */
volatile int sparkFireCount            = 0;

/*
 * Rpm value from last update
 * Used to average the last 2 rpms for smoother output
 */
int lastRpmValue              = 0;

/*
 * Blinking rev limiter state
 */
bool revLimiterOn             = false;

/*
 *
 */





// 4 stroke engine fires every spark in 2 revolutions
// so calculate at what degree interval sparks fires and divide 360 by it,
// to find the number of fires per rotation
const int FIRES_PER_REV = (360 / (720 / NUMBER_OF_CYLINDERS));
volatile int averagedRpm;
void tachometer() {
  if ((millis() - lastUpdateTime) > LED_UPDATE_INTERVAL) {

    // multiply the amount the spark fires in one interval by the number of intervals per
    // second, to find the amount in one second
    // then multiply the amount in one second by 60, to find the spark fires in one minute and
    // divide the result by the number of fires per revolution to find the rpm
    int currentRpm = (sparkFireCount * (1000 / LED_UPDATE_INTERVAL) * 60) / FIRES_PER_REV;
    // average the current and last rpm for smoother results
    averagedRpm = (currentRpm + lastRpmValue) / 2;
    sparkFireCount = 0;
    lastUpdateTime = millis();
    lastRpmValue = currentRpm;
  }

}

void incrementRpmCount () {
  sparkFireCount++;
  tachometer();
}
