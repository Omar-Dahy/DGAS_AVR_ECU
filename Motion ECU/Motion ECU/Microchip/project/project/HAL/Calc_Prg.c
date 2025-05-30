
#include "StdTypes.h"
#include "Calc_Int.h"
#include "KeyPad_Int.h"
#include "LCD_Int.h"
# define F_CPU 8000000UL
#include <util/delay.h>


void CALCULATOR(void)
{
	static u8 flag=0;
	
	
	if(flag==0){
		CALCULATOR_Init();
		LCD_WriteString((u8 *)"Casio Calculator");
		_delay_ms(3000);
		LCD_Clear();
		flag=1;
	}
	parameters();
}


void CALCULATOR_Init(void)
{
	LCD_Clear();
	
}

void parameters(void)
{
	u8 flag1=0,flag2=0,flag3=0,flag4=0,finish=0;
	u8 k=NO_KEY, operator=NO_KEY;
	s32 num1=0,num2=0;
	while((finish==0)){
		k=KeyPad_GetKey();
		
		if(flag4==0){
			if(k!=NO_KEY)
			{
				if((k>='0')&&(k<='9'))
				{
					if((flag2==0))
					{
						num1=num1*10+k-'0';
						flag1=1;
						
					}
					else if(flag2==1)
					{
						num2=num2*10+k-'0';
						flag3=1;
						
					}
					
					LCD_WriteChar(k);
				}
				else if(k=='=')
				{
					if(flag3==1)
					{
						num1=operation(num1,num2,operator);
						LCD_SetCursor(2,1);
						LCD_WriteNumber(num1);
						flag4=1;
						//Calculation_Second( num1);
						
					}
					
				}
				else if(k=='C')
				{
					num1=0;
					num2=0;
					flag1=0;
					flag2=0;
					flag3=0;
					flag4=0;
					finish=0;
					LCD_Clear();
				}
				else
				{
					if(flag1==1&&flag2!=1)
					{
						operator=k;
						LCD_WriteChar(k);
						
						flag2=1;
						
					}
				}
			}
		}
		else if(flag4==1)
		{
			if(k!=NO_KEY)
			{
				if((k>='0')&&(k<='9'))
				{
					num1=k-'0';
					num2=0;
					flag1=0;
					flag2=0;
					flag3=0;
					flag4=0;
					finish=0;
					LCD_Clear();
					LCD_SetCursor(1,1);
					LCD_WriteChar(k);
				}
				else if(k=='C')
				{
					num1=0;
					num2=0;
					flag1=0;
					flag2=0;
					flag3=0;
					flag4=0;
					finish=0;
					LCD_Clear();
				}
				else if(k=='=')
				{
					
				}
				else
				{
					num2=0;
					flag1=1;
					flag2=1;
					flag3=0;
					flag4=0;
					finish=0;
					LCD_Clear();
					LCD_SetCursor(1,1);
					LCD_WriteNumber(num1);
					LCD_WriteChar(k);
					operator=k;
				}
			}
		}
	}
}







s32 operation(s32 n1,s32 n2,u8 operator)
{
	

	s32 result=0;
	switch(operator)
	{
		case '+':
		result= (n1+n2);
		break;
		case '-':
		result= (n1-n2);
		break;
		case '/':
		result= (n1/n2);
		break;
		case '*':
		result= (n1*n2);
		break;
		default:
		break;
		
	}

	return result;
}