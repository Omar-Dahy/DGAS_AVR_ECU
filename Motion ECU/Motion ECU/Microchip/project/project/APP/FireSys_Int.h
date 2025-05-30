

#ifndef FIRESYS_PRG_H_
#define FIRESYS_PRG_H_

typedef enum{
	fine,
	heat,
	fire
}Sys_status_t;


#define rightPass  12345

void FireSys_Init(void);
void heat_print(u16 heat);
void smoke_print(u32 smoke);
void FireSys_Runnable(void);

#endif /* FIRESYS_PRG_H_ */