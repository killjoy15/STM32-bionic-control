# bionic-control

Этот код реализует управление мотором с удержанием кнопки:

Кнопка 1 (PA0): мотор вращается вперед, пока кнопка нажата

Кнопка 2 (PA1): мотор вращается назад, пока кнопка нажата

Обе кнопки отпущены: мотор остановлен

Код включает антидребезг для предотвращения ложных срабатываний и полностью готов к использованию в STM32CubeIDE.


Настройка в STM32CubeMX:

GPIO Configuration:

PA0 - GPIO_Input (Button 1) - Pull-up

PA1 - GPIO_Input (Button 2) - Pull-up

PB0 - GPIO_Output (Motor IN1) - Push-Pull

PB1 - GPIO_Output (Motor IN2) - Push-Pull

PB2 - GPIO_Output (Motor Enable) - Push-Pull
