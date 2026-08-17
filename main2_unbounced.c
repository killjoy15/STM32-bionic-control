/* main.c - Вариант с антидребезгом и удержанием кнопки */
#include "main.h"

// Определения для кнопок
#define BUTTON1_PIN        GPIO_PIN_0
#define BUTTON1_PORT       GPIOA
#define BUTTON2_PIN        GPIO_PIN_1
#define BUTTON2_PORT       GPIOA

// Определения для управления мотором
#define MOTOR_IN1_PIN      GPIO_PIN_0
#define MOTOR_IN1_PORT     GPIOB
#define MOTOR_IN2_PIN      GPIO_PIN_1
#define MOTOR_IN2_PORT     GPIOB
#define MOTOR_ENABLE_PIN   GPIO_PIN_2
#define MOTOR_ENABLE_PORT  GPIOB

#define DEBOUNCE_DELAY     20  // Задержка антидребезга в мс

// Глобальные переменные для антидребезга
volatile uint32_t last_press_time = 0;
volatile uint8_t button_state = 0;  // 0 - ни одна не нажата, 1 - кнопка 1, 2 - кнопка 2

// Прототипы функций
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
void Motor_Forward(void);
void Motor_Backward(void);
void Motor_Stop(void);

void Motor_Forward(void)
{
    HAL_GPIO_WritePin(MOTOR_IN1_PORT, MOTOR_IN1_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTOR_IN2_PORT, MOTOR_IN2_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_ENABLE_PORT, MOTOR_ENABLE_PIN, GPIO_PIN_SET);
}

void Motor_Backward(void)
{
    HAL_GPIO_WritePin(MOTOR_IN1_PORT, MOTOR_IN1_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_IN2_PORT, MOTOR_IN2_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTOR_ENABLE_PORT, MOTOR_ENABLE_PIN, GPIO_PIN_SET);
}

void Motor_Stop(void)
{
    HAL_GPIO_WritePin(MOTOR_ENABLE_PORT, MOTOR_ENABLE_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_IN1_PORT, MOTOR_IN1_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_IN2_PORT, MOTOR_IN2_PIN, GPIO_PIN_RESET);
}

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    
    Motor_Stop();
    HAL_Delay(100);
    
    while (1)
    {
        uint32_t current_time = HAL_GetTick();
        
        // Проверяем кнопку 1 (вперед)
        if (HAL_GPIO_ReadPin(BUTTON1_PORT, BUTTON1_PIN) == GPIO_PIN_RESET)
        {
            // Антидребезг
            if (current_time - last_press_time > DEBOUNCE_DELAY)
            {
                last_press_time = current_time;
                Motor_Forward();
            }
        }
        // Проверяем кнопку 2 (назад)
        else if (HAL_GPIO_ReadPin(BUTTON2_PORT, BUTTON2_PIN) == GPIO_PIN_RESET)
        {
            if (current_time - last_press_time > DEBOUNCE_DELAY)
            {
                last_press_time = current_time;
                Motor_Backward();
            }
        }
        // Если ни одна кнопка не нажата - останавливаем мотор
        else
        {
            Motor_Stop();
        }
        
        HAL_Delay(10);
    }
}

static void MX_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    
    // Начальное состояние выходов
    HAL_GPIO_WritePin(GPIOB, MOTOR_IN1_PIN|MOTOR_IN2_PIN|MOTOR_ENABLE_PIN, GPIO_PIN_RESET);
    
    // Кнопки - входы с подтяжкой вверх
    GPIO_InitStruct.Pin = BUTTON1_PIN|BUTTON2_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    
    // Выходы для мотора
    GPIO_InitStruct.Pin = MOTOR_IN1_PIN|MOTOR_IN2_PIN|MOTOR_ENABLE_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void SystemClock_Config(void)
{
    // Конфигурация тактирования (генерируется CubeMX)
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
    
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }
    
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
    
    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
    {
        Error_Handler();
    }
}

void Error_Handler(void)
{
    __disable_irq();
    while (1)
    {
    }
}