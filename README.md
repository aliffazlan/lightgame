# RAMSOC OWEEK Game

Ensure pins are correctly connected to the right ports

Button will glow when it is able to be pressed

Game will begin in the "IDLE" stage, press the button to start

Once pressed, a brief startup animation will play

After the startup animation finishes, the game begins and the button will light up

When the button is pressed, the light will slow down until it comes to a stop

## Serial Commands

| Command | Description                       |
| :-------- | :-------------------------------- |
| `SKILL` | Disables rigging, still wont land on untoggled colors though|
| `RIG_RED` | Forces the game to land on RED|
| `RIG_YELLOW` | Forces the game to land on YELLOW|
| `RIG_GREEN` | Forces the game to land on GREEN|
| `RIG_BLUE` | Forces the game to land on BLUE|
| `TOGGLE_RED` | Toggles being able to land on RED|
| `TOGGLE_YELLOW` | Toggles being able to land on YELLOW|
| `TOGGLE_GREEN` | Toggles being able to land on GREEN|
| `TOGGLE_BLUE` | Toggles being able to land on BLUE|

**NOTE**: Very important !!! Don't set up in such a way that no viable colors are possible (eg. toggling off all colors, rigging to win a disabled color, etc). Game will enter an infinite loop cuz im too lazy to setup checks :)