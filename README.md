# Dash.ino
Arduino Library for RAKWireless Dash Internet Button

## Features

This lib brings functions for:
 - Keep state of Keys
 - Key event handler
 - Keep state of LEDs
 - LEDs brightness via PWM (8 levels)
 - State, Color definitions
 - Battery state
 - Reset, Shut off

## Good to now

### Default functions
  1. Press Key2 longer than 5sec to reset
  2. Press Key4 longer than 5sec to shut off (press any key to restart)

### Key event implementation
- Interrupt not possible as now all keys support it
- Instead using a Timer 'polling' current keys
