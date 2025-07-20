void Motor_Rotate_To_Angle(int8_t target_angle)
{
    const int8_t ANGLE_LIMIT_MIN = -45;
    const int8_t ANGLE_LIMIT_MAX = 45;

    char debug[50];

    if (target_angle > ANGLE_LIMIT_MAX) target_angle = ANGLE_LIMIT_MAX;
    if (target_angle < ANGLE_LIMIT_MIN) target_angle = ANGLE_LIMIT_MIN;

    sprintf(buffer, "Going to angle: %d\r\n", target_angle);
    HAL_UART_Transmit(&huart2, (uint8_t *)buffer, strlen(buffer), 100);

    int attempt = 0;

    while (1)
    {
        int8_t current_angle = Get_Actual_Angle();


        if (current_angle == -127)
        {
            HAL_UART_Transmit(&huart2, (uint8_t *)"Invalid ADC reading. Skipping movement.\r\n", 44, 100);
            break;
        }

        sprintf(debug, "Actual Angle: %d\r\n", current_angle);
        HAL_UART_Transmit(&huart2, (uint8_t *)debug, strlen(debug), 100);

        int8_t error = target_angle - current_angle;

        if (abs(error) <= 1)
        {
            sprintf(buffer, "Reached: %d\r\n\r\n", current_angle);
            HAL_UART_Transmit(&huart2, (uint8_t *)buffer, strlen(buffer), 100);
            break;
        }

        if (abs(error) > 180)
        {
            HAL_UART_Transmit(&huart2, (uint8_t *)"Movement too large!\r\n\r\n", 27, 100);
            return;
        }


        HAL_GPIO_WritePin(MOTOR_DIR_GPIO_Port, MOTOR_DIR_PIN1, (error < 0) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(MOTOR_DIR_GPIO_Port, MOTOR_DIR_PIN2, (error > 0) ? GPIO_PIN_SET : GPIO_PIN_RESET);

        uint16_t speed;
        uint16_t delay_ms;

        if (abs(error) > 20) {
            speed = 2000;
            delay_ms = 25;
        }
        else if (abs(error) > 10) {
            speed = 1500;
            delay_ms = 22;
        }
        else if (abs(error) > 5) {
            speed = 1300;
            delay_ms = 20;
        }
        else {
            speed = 1000;
            delay_ms = 17;
        }

        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, speed);
        HAL_Delay(delay_ms);


        HAL_GPIO_WritePin(MOTOR_DIR_GPIO_Port, MOTOR_DIR_PIN1, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(MOTOR_DIR_GPIO_Port, MOTOR_DIR_PIN2, GPIO_PIN_RESET);
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 0);
        HAL_Delay(50);

        attempt++;
        if (attempt > 25)
        {

            int8_t final_angle = Get_Actual_Angle();
            int8_t final_error = target_angle - final_angle;

            if (abs(final_error) <= 1)
            {
                sprintf(buffer, "Max attempts, but close enough: %d\r\n", final_angle);
                HAL_UART_Transmit(&huart2, (uint8_t *)buffer, strlen(buffer), 100);
            }
            else
            {
                HAL_UART_Transmit(&huart2, (uint8_t *)"Failed to reach target angle.\r\n", 34, 100);
            }
            break;
        }
    }
}