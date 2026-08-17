# bionic-control

This code implements motor control based on button presses:

Button 1 (PA0): motor rotates forward while the button is pressed

Button 2 (PA1): motor rotates backward while the button is pressed

Both buttons released: motor stopped

The code includes debouncing to prevent false triggers and is ready for use in STM32CubeIDE.


STM32CubeMX GPIO Configuration:

PA0 - GPIO_Input (Button 1) - Pull-up

PA1 - GPIO_Input (Button 2) - Pull-up

PB0 - GPIO_Output (Motor IN1) - Push-Pull

PB1 - GPIO_Output (Motor IN2) - Push-Pull

PB2 - GPIO_Output (Motor Enable) - Push-Pull
