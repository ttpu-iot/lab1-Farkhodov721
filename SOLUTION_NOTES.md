# Solution Notes - Lab 1 Exercises

## Issues Identified and Fixed

### Problem
The original code attempted to run all 6 exercises simultaneously in the `loop()` function. This caused severe conflicts:

1. **Exercise 4** (Light sensor → LED band) turned OFF all LEDs every 500ms
   - This broke **Exercise 1** (RED blink) - RED LED was constantly turned off
   - This broke **Exercise 2** (GREEN toggle) - GREEN state was overridden
   - This broke **Exercise 5** (YELLOW flash) - YELLOW flash was interrupted
   - This broke **Exercise 6** (BLUE control) - BLUE state was overridden

2. All exercises were competing for control of the same LEDs and pins

### Solution
Restructured the code to run **ONE exercise at a time** using preprocessor directives (`#define`).

## How to Use

### Selecting an Exercise

Open `src/esp32_lab1.ino` and find lines 4-12:

```cpp
// ============================================================
// SELECT WHICH EXERCISE TO RUN (uncomment only ONE)
// ============================================================
// #define EXERCISE_1  // Blink RED LED
// #define EXERCISE_2  // Button toggles GREEN
// #define EXERCISE_3  // Read light sensor
// #define EXERCISE_4  // Light sensor -> LED band
// #define EXERCISE_5  // Snapshot on button
#define EXERCISE_6  // Minimal serial control
```

**To run a different exercise:**
1. Comment out the currently active exercise (add `//` at the start)
2. Uncomment the exercise you want to run (remove `//`)
3. Save the file
4. Build and upload to your ESP32

**Example - To run Exercise 1:**
```cpp
#define EXERCISE_1  // Blink RED LED
// #define EXERCISE_2  // Button toggles GREEN
// #define EXERCISE_3  // Read light sensor
// #define EXERCISE_4  // Light sensor -> LED band
// #define EXERCISE_5  // Snapshot on button
// #define EXERCISE_6  // Minimal serial control
```

## Exercise Implementation Details

### Exercise 1: Blink RED LED ✓
- **Requirements:** Turn RED (D15) ON for 500ms, OFF for 500ms
- **Serial Output:** `RED ON` / `RED OFF`
- **Status:** Correctly implemented

### Exercise 2: Button toggles GREEN ✓
- **Requirements:** Press BUTTON (D14) to toggle GREEN (D4)
- **Serial Output:** `GREEN=1` or `GREEN=0` (only on state change)
- **Features:** Includes debouncing (50ms)
- **Status:** Correctly implemented

### Exercise 3: Read light sensor ✓
- **Requirements:** Read LIGHT (D33) every 500ms using `analogRead()`
- **Serial Output:** `raw=xxxx` (e.g., `raw=1835`)
- **Status:** Correctly implemented

### Exercise 4: Light sensor → LED band ✓
- **Requirements:** Turn on ONE LED based on light value (0-4095):
  - 0-1023 → BLUE (D22)
  - 1024-2047 → GREEN (D4)
  - 2048-3071 → YELLOW (D23)
  - 3072-4095 → RED (D15)
- **Serial Output:** `band=BLUE/GREEN/YELLOW/RED`
- **Status:** Correctly implemented (now in separate function)

### Exercise 5: Snapshot on button ✓
- **Requirements:** On BUTTON (D14) press, read LIGHT (D33) once
- **Serial Output:** `snapshot=xxxx`
- **Acknowledgment:** Flash YELLOW (D23) for 100ms
- **Features:** Includes debouncing (500ms between snapshots)
- **Status:** Correctly implemented

### Exercise 6: Minimal serial control ✓
- **Requirements:** 
  - Receive `'B'` → turn BLUE (D22) ON
  - Receive `'b'` → turn BLUE (D22) OFF
- **Serial Output:** `BLUE=1` or `BLUE=0`
- **Status:** Correctly implemented

## Pin Configuration

All exercises use the following pin assignments:
- RED LED: D15 (GPIO 15)
- GREEN LED: D4 (GPIO 4)
- BLUE LED: D22 (GPIO 22)
- YELLOW LED: D23 (GPIO 23)
- BUTTON: D14 (GPIO 14) with INPUT_PULLUP
- LIGHT SENSOR: D33 (GPIO 33) - Analog input

## Technical Notes

1. **Conditional Compilation:** Only the selected exercise's code is compiled, reducing memory usage
2. **Pin Initialization:** Only required pins for the selected exercise are initialized in `setup()`
3. **Variable Scope:** Each exercise's variables are only declared when that exercise is active
4. **No Conflicts:** Each exercise runs independently without interference from others

## Verification

To verify each exercise works correctly:

1. **Exercise 1:** Monitor serial output, should see `RED ON` and `RED OFF` alternating every 500ms
2. **Exercise 2:** Press button, monitor serial for `GREEN=0` and `GREEN=1` toggle
3. **Exercise 3:** Monitor serial output for `raw=xxxx` values every 500ms
4. **Exercise 4:** Vary light sensor input, monitor serial for `band=` messages and observe LED changes
5. **Exercise 5:** Press button, monitor for `snapshot=xxxx` and observe YELLOW flash
6. **Exercise 6:** Send 'B' and 'b' characters via serial, monitor for `BLUE=1` and `BLUE=0`
