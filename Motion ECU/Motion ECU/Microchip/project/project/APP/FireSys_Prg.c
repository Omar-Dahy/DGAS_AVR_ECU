
#include "StdTypes.h"
#define  F_CPU   8000000
#include <util/delay.h>
#include "DIO_Int.h"
#include "KeyPad_Int.h"
#include "ADC_Int.h"
#include "LCD_Int.h"
#include "Sensors_Int.h"
#include "FireSys_Int.h"
#include "MOTOR_Int.h"

#define yellow_led   PINC0
#define red_led      PINC1
#define M_input1       PINC2
#define M_input2       PINC3

static u8 heat_flag=0;
u8 k=NO_KEY;
s32 password=0;

void FireSys_Init(void)
{
	
}


void heat_print(u16 heat)
{
	LCD_SetCursor(1,1);
	LCD_WriteString((u8*)"HEAT : "  );
	LCD_SetCursor(1,9);
	LCD_WriteNumber(heat/10);
	LCD_WriteChar('.');
	LCD_WriteNumber(heat%10);
}

u32 smoke_Percenage (u32 smoke)
{
	u32 smoke_Percenage=((smoke*100)/1150);
	return	smoke_Percenage;
}
void smoke_print(u32 smoke)
{
	
	LCD_SetCursor(2,1);
	LCD_WriteString((u8*)"SMOKE : "  );
	u32 smoke_Percentage=smoke_Percenage(smoke);
	
	LCD_SetCursor(2,9);
	LCD_WriteNumber(smoke_Percentage);

	LCD_WriteChar('%');

}
void FireSys_Runnable(void)
{
	
	Sys_status_t status=fine;
	u16 heat=Temp_Read_Multi(Sensor2);
	u32 smoke;
	u8 flag=0;

	if (heat<450)
	{
		status=fine;
		
	}
	else
	{
		status=heat;
	}
	
	
	if(status==fine)
	{
		
		heat_print(heat);
		DIO_WritePin(yellow_led,LOW);
		DIO_WritePin(red_led,LOW);
		DIO_WritePin(M_input1,LOW);
		DIO_WritePin(M_input2,LOW);
		
		LCD_SetCursor(2,1);
		LCD_WriteString((u8*)"                ");
	}
	
	else
	{
		smoke=Pressure_Read();
		
		heat_print(heat);
		
		smoke_print(smoke);
		DIO_WritePin(yellow_led,HIGH);
		
		if(smoke>575)
		{
			status=fire;
			heat_flag=1;
		}
		
	}
	if(status==fire)

	{
		
		DIO_WritePin(yellow_led,HIGH);
		DIO_WritePin(red_led,HIGH);
		MOTOR_CW(M1);
		while(heat_flag==1)
		{
			smoke=Pressure_Read();
			heat=Temp_Read_Multi(Sensor2);
			if (flag==0)
			{
				
				heat_print(heat);
				smoke_print(smoke);
			}
			
			k=KeyPad_GetKey();
			
			
			if(k!=NO_KEY)
			{
				if(k=='=')
				{
					flag=1;
					LCD_Clear();
					LCD_SetCursor(1,1);
					LCD_WriteString((u8*)"enter ur passwrd");
					LCD_SetCursor(2,1);
					
				}
				else if ((k>='0')&&(k<='9'))
				{
					password=password*10+k-'0';
					LCD_WriteChar('*');
					
				}
				
				
				else if (k=='c')
				{
					if(password!=rightPass)
					{
						password=0;
						LCD_SetCursor(2,1);
						LCD_WriteString((u8*)"Wrong Password!");
						_delay_ms(1000);
						LCD_Clear();
						
						flag=0;
					}
					else
					{
						password=0;
						LCD_Clear();
						_delay_ms(10);
						heat_flag=0;
						status=fine;
					}
				}
				
				
			}
		}
		
	}
}