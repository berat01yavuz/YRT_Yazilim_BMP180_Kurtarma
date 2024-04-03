// UART'a altitude ve pressure değerleri 0.5 saniye aralıklarla iletiliyor

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usart.h"
#include "stdio.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
int32_t pressure ;
			 float  r, c;
				  float altitude_m;
	char buffer[1000];

    char depo[100];
  int anlikdeger = 0; 
  int maksdeger = 0; 
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal,
};
/* Definitions for myTask02 */
osThreadId_t myTask02Handle;
const osThreadAttr_t myTask02_attributes = {
  .name = "myTask02",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void bmp180_data(void *argument);
void kurtarma(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(bmp180_data, NULL, &defaultTask_attributes);

  /* creation of myTask02 */
  myTask02Handle = osThreadNew(kurtarma, NULL, &myTask02_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_bmp180_data */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_bmp180_data */
void bmp180_data(void *argument)
{
  /* USER CODE BEGIN bmp180_data */


  /* Infinite loop */
  for(;;)
  {

		pressure = BMP180_GetPressure();
		  r = pressure / 101325.0;
		  c = 1.0 / 5.255;
			altitude_m = (1 - pow(r, c)) * 44330.77;

			 sprintf(buffer, "Pressure: %d Pa\nAltitude: %f\n", (int) pressure, (float)altitude_m);


			 HAL_UART_Transmit(&huart2, buffer, strlen(buffer), 100);

       anlikdeger = altitude_m ;
if(maksdeger<anlikdeger){
  maksdeger = anlikdeger;

}

    osDelay(500);
  }
  /* USER CODE END bmp180_data */
}

/* USER CODE BEGIN Header_kurtarma */
/**
* @brief Function implementing the myTask02 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_kurtarma */
void kurtarma(void *argument)
{
  /* USER CODE BEGIN kurtarma */


  /* Infinite loop */
  for(;;)
  {
	  if(maksdeger - anlikdeger > 1){
	     HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
	    }
    osDelay(10);
  }
  /* USER CODE END kurtarma */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

