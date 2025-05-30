/*
 * File   :  mcal_external_interrupt.c
 * https://www.linkedin.com/in/ahmed-shawada/
 * Created: 12/9/2024 11:08:10 PM
 * Author: AhmedShawada
 */ 

#include "mcal_external_interrupt.h"

/* Pointer to function to hold the callbacks for INTx */

static InterruptHandler INT0_InterruptHandler  = NULL;
static InterruptHandler INT1_InterruptHandler  = NULL;
static InterruptHandler INT2_InterruptHandler  = NULL;

/***************************Helper_Function***************************/

static Std_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Edge_Init(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Pin_Init(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Clear_Flag(const interrupt_INTx_t *int_obj);

static Std_ReturnType Interrupt_INTx_SetInterruptHandler (const interrupt_INTx_t *int_obj);
static Std_ReturnType INT0_SetInterruptHandler (void (*InterruptHandler) (void));
static Std_ReturnType INT1_SetInterruptHandler (void (*InterruptHandler) (void));
static Std_ReturnType INT2_SetInterruptHandler (void (*InterruptHandler) (void));





/**
 * @brief Initialize the external interrupt INT0, INT1 and INT2
 * @param int_obj  Pointer to the Interrupt configuration object
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType Interrupt_INTx_Init(const interrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    
    else
    {
        /*Disable the External Interrupt */
        ret = Interrupt_INTx_Disable(int_obj);
        
        /*Clear Interrupt Flag : External Interrupt did not occur */
        ret |= Interrupt_INTx_Clear_Flag(int_obj);
        
        /*Configure External Interrupt Edge */
		ret |= Interrupt_INTx_Edge_Init(int_obj);
        
        /*Configure External Interrupt I/O Pin */
        ret |= Interrupt_INTx_Pin_Init(int_obj);
        
        /*Configure External Interrupt CallBack */
        ret |= Interrupt_INTx_SetInterruptHandler(int_obj);
		
        /*Enable the External Interrupt */
        ret |= Interrupt_INTx_Enable(int_obj);
		
    }
    
    return ret;
}



/**
 * @brief DeInitialize the interrupt module
 * @param int_obj  Pointer to the Interrupt configuration object
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType Interrupt_INTx_DeInit(const interrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    
    else
    {
		/*Disable the External Interrupt */
        ret = Interrupt_INTx_Disable(int_obj);
    }
    return ret; 
    
}




/**
 * @brief Enable the INTx interrupt source
 * @param int_obj  Pointer to the Interrupt configuration object
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static Std_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t *int_obj)
{
	Std_ReturnType ret = E_OK;
	
	if (NULL == int_obj)
	{
		ret = E_NOT_OK;
	} 
	else
	{
		switch(int_obj->source)
		{
			case INTERRUPT_EXTERNAL_INT0 :
			
				INTERRUPT_GlobalInterruptEnable();
				EXT_INT0_InterruptEnable();
				ret = E_OK;
				break;
				
			case INTERRUPT_EXTERNAL_INT1 :
			
				INTERRUPT_GlobalInterruptEnable();
				EXT_INT1_InterruptEnable();
				ret = E_OK;
				break;
				
			case INTERRUPT_EXTERNAL_INT2 :
			
				INTERRUPT_GlobalInterruptEnable();
				EXT_INT2_InterruptEnable();
				ret = E_OK;
				break;
				
			default :
				ret = E_NOT_OK;
		}
		
	}
	return ret;
	
}

/**
 * @brief  
 * @param int_obj  Pointer to the Interrupt configuration object
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static Std_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t *int_obj)
{ 
	Std_ReturnType ret = E_OK;
	
	if (NULL == int_obj)
	{
		ret = E_NOT_OK;
	}
	else
	{
		switch(int_obj->source)
		{
			case INTERRUPT_EXTERNAL_INT0 :
			EXT_INT0_InterruptDisable();
			ret = E_OK;
			break;
			
			case INTERRUPT_EXTERNAL_INT1 :
			EXT_INT1_InterruptDisable();
			ret = E_OK;
			break;
	
			case INTERRUPT_EXTERNAL_INT2 :
			EXT_INT2_InterruptDisable();
			ret = E_OK;
			break;
			
			default :
			ret = E_NOT_OK;
		}
	}
	return ret;
}


/**
 * @brief  
 * @param int_obj  Pointer to the Interrupt configuration object
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static Std_ReturnType Interrupt_INTx_Edge_Init(const interrupt_INTx_t *int_obj)
{
	Std_ReturnType ret = E_NOT_OK;
	if(NULL == int_obj)
	{
		ret = E_NOT_OK;
	}
	
	else
	{
		switch(int_obj->source)
		{
			case INTERRUPT_EXTERNAL_INT0 :
			if(INTERRUPT_FALLING_EDGE == int_obj->edge)
			{
				EXT_INT0_FallingEdgeSet();
			}
			else if(INTERRUPT_RISING_EDGE == int_obj->edge)
			{
				EXT_INT0_RisingEdgeSet();
			}
			else{ /* Nothing */ }
			ret = E_OK;
			break;
			
			
			case INTERRUPT_EXTERNAL_INT1 :
			if(INTERRUPT_FALLING_EDGE == int_obj->edge)
			{
				EXT_INT1_FallingEdgeSet();
			}
			else if(INTERRUPT_RISING_EDGE == int_obj->edge)
			{
				EXT_INT1_RisingEdgeSet();
			}
			else{ /* Nothing */ }
			ret = E_OK;
			break;
			
			
			case INTERRUPT_EXTERNAL_INT2 :
			if(INTERRUPT_FALLING_EDGE == int_obj->edge)
			{
				EXT_INT2_FallingEdgeSet();
			}
			else if(INTERRUPT_RISING_EDGE == int_obj->edge)
			{
				EXT_INT2_RisingEdgeSet();
			}
			else{ /* Nothing */ }
			ret = E_OK;
			break;
			
			default :
			ret = E_NOT_OK;
		}
	}
	return ret;
}


/**
 * @brief  
 * @param int_obj  Pointer to the Interrupt configuration object
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static Std_ReturnType Interrupt_INTx_Pin_Init(const interrupt_INTx_t *int_obj)
{
	Std_ReturnType ret = E_NOT_OK;
	if(NULL == int_obj)
	{
		ret = E_NOT_OK;
	}
	
	else
	{
		/* Initialize the MCU Pin for INTx with the needed configurations */
		ret = gpio_pin_direction_intialize(&(int_obj->mcu_pin));
	}
	
	return ret;
}

/**
 * @brief  
 * @param int_obj  Pointer to the Interrupt configuration object
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static Std_ReturnType Interrupt_INTx_Clear_Flag(const interrupt_INTx_t *int_obj)
{
	Std_ReturnType ret = E_NOT_OK;
	if(NULL == int_obj)
	{
		ret = E_NOT_OK;
	}
	
	else
	{
		switch(int_obj->source)
		{
			case INTERRUPT_EXTERNAL_INT0 :
			EXT_INT0_InterruptFlagClear();
			ret = E_OK;
			break;
			
			case INTERRUPT_EXTERNAL_INT1 :
			EXT_INT1_InterruptFlagClear();
			ret = E_OK;
			break;
			
			
			case INTERRUPT_EXTERNAL_INT2 :
			EXT_INT2_InterruptFlagClear();
			ret = E_OK;
			break;
			
			default :
			ret = E_NOT_OK;
		}
	}
}


/**
 * @brief  
 * @param InterruptHandler
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static Std_ReturnType INT0_SetInterruptHandler (void (*InterruptHandler) (void))
{
   Std_ReturnType ret = E_NOT_OK;
    if(NULL == InterruptHandler)
    {
        ret = E_NOT_OK;
    }
   
    else
    {
        /* Set Default Interrupt Handler for INT0 External Interrupt : Application ISR */
        INT0_InterruptHandler = InterruptHandler;
        ret = E_OK;
    }
   return ret; 
}


/**
 * @brief  
 * @param InterruptHandler
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static Std_ReturnType INT1_SetInterruptHandler (void (*InterruptHandler) (void))
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == InterruptHandler)
    {
        ret = E_NOT_OK;
    }
   
    else
    {
        /* Set Default Interrupt Handler for INT1 External Interrupt : Application ISR */
        INT1_InterruptHandler = InterruptHandler;
        ret = E_OK;
    }
   return ret;
}

/**
 * @brief  
 * @param InterruptHandler
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static Std_ReturnType INT2_SetInterruptHandler (void (*InterruptHandler) (void))
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == InterruptHandler)
    {
        ret = E_NOT_OK;
    }
   
    else
    {
        /* Set Default Interrupt Handler for INT2 External Interrupt : Application ISR */
        INT2_InterruptHandler = InterruptHandler;
        ret = E_OK;
    }
   return ret;
}

/**
 * @brief  
 * @param int_obj  Pointer to the Interrupt configuration object
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static Std_ReturnType Interrupt_INTx_SetInterruptHandler (const interrupt_INTx_t *int_obj)
{
   Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
   
    else
    {
        switch(int_obj->source)
       {
           case INTERRUPT_EXTERNAL_INT0 :
               ret = INT0_SetInterruptHandler(int_obj->EXT_InterruptHandler);
               
               break;
               
           case INTERRUPT_EXTERNAL_INT1 :
               ret = INT1_SetInterruptHandler(int_obj->EXT_InterruptHandler);
               
               break;
               
               
           case INTERRUPT_EXTERNAL_INT2 :
               ret = INT2_SetInterruptHandler(int_obj->EXT_InterruptHandler);
               
               break;
               
           default :
               ret = E_NOT_OK;
       }
    }
   return ret;
}


/**
 * External Interrupt 0 MCAL Helper function 
 */
void INT0_ISR (void)
{
    /* The INT0 external interrupt occurred (must be cleared in software) */
    EXT_INT0_InterruptFlagClear();
    
    /* Code : To be executed from MCAL Interrupt Context */
    
    /* Application Callback function gets called every time this ISR executes */
    if(INT0_InterruptHandler)
    { 
        INT0_InterruptHandler();
    }
    
    else{ /* Nothing */ }
}

/**
 * External Interrupt 1 MCAL Helper function 
 */
void INT1_ISR (void)
{
    /* The INT1 external interrupt occurred (must be cleared in software) */
    EXT_INT1_InterruptFlagClear();
    
    /* Code : To be executed from MCAL Interrupt Context */
    
    /* Application Callback function gets called every time this ISR executes */
    if(INT1_InterruptHandler)
    { 
        INT1_InterruptHandler();
    }
    
    else{ /* Nothing */ }
}

/**
 * External Interrupt 2 MCAL Helper function 
 */
void INT2_ISR (void)
{
    /* The INT2 external interrupt occurred (must be cleared in software) */
    EXT_INT2_InterruptFlagClear();
    
    /* Code : To be executed from MCAL Interrupt Context */
    
    /* Application Callback function gets called every time this ISR executes */
    if(INT2_InterruptHandler)
    { 
        INT2_InterruptHandler();
    }
    
    else{ /* Nothing */ }
}