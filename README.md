# bionic-control
bionic control system prototype

- 4 myo-sensors --> signal handling
- myo-signals combinations for fluent Degree of Freedom (DoF) control
- ML for activity recognition
- vector of 3 DoF
- more myo-sensors --> more DoF
- DoF must be multitreaded. For example, fingers must moving synchronously. Need to use RTOS or superloop will be enough?
- Создать класс Мотор. Каждый объект (мотор) должен отслеживать своё со стояние по току. Если идет превыжение допустимых значений, то ставится запрет на движение в эту сторону, разрешается только в обратную.





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
