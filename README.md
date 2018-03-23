# Dash.ino
Arduino Library for RAKWireless Dash Internet Button

## Features

This lib brings functions for:
 - Keep state of Keys
 - Key event handler
 - Keep state of LEDs
 - LEDs brightness via PWM (8 levels)
 - State & Color constant definitions
 - Battery state
 - Reset, Shut off

## Installation

To install this library, just place this entire folder as a subfolder in your
Arduino/lib/targets/libraries folder.

When installed, this library should look like:

```
Arduino/lib/targets/libraries/Dash              (this library's folder)
Arduino/lib/targets/libraries/Dash/Dash.cpp     (the library implementation file)
Arduino/lib/targets/libraries/Dash/Dash.h       (the library description file)
Arduino/lib/targets/libraries/Dash/keywords.txt (the syntax coloring file)
Arduino/lib/targets/libraries/Dash/examples     (the examples in the "open" menu)
Arduino/lib/targets/libraries/Dash/README.md    (this file)
```

## Development
--------------------------------------------------------------------------------

After this library is installed, you just have to start the Arduino application.
You may see a few warning messages as it's built.

To use this library in a sketch, go to the Sketch | Import Library menu and
select Test.  This will add a corresponding line to the top of your sketch:
#include <Dash.h>

To stop using this library, delete that line from your sketch.

Geeky information:
After a successful build of this library, a new file named "Dash.o" will appear
in "Arduino/lib/targets/libraries/Dash". This file is the built/compiled library
code.

If you choose to modify the code for this library (i.e. "Dash.cpp" or "Dash.h"),
then you must first 'unbuild' this library by deleting the "Dash.o" file. The
new "Dash.o" with your code will appear after the next press of "verify"


## Good to know

### Default functions
  1. Press Key2 longer than 5sec to reset
  2. Press Key4 longer than 5sec to shut off (press any key to restart)

### Key event implementation
- Interrupt not possible as now all keys support it
- Instead using a Timer 'polling' current keys
