/*
 * ElecticHeat.c
 *
 * Created: 26.12.2017 15:39:35
 * Author : mike
 */ 

#define BAUD 9600
#define MAXDEVICES 6

#define SENS_INDEV  	0; // внутренний 
#define SENS_IN 		1; // обратка (вход в котел)
#define SENS_OUT		2; // подача (выход из котла)
#define SENS_INDOOR		3; // помещение (основное управление)
#define SENS_OUTDOOR	4; // улица
#define SENS_EXT		5; // дополнительный ТТ котел (для насоса)

#include <stdio.h>
#include <avr/io.h>
#include <avr/eeprom.h>
#include <util/delay.h>
#include "uart.h"
#include "onewire.h"

FILE usart_str = FDEV_SETUP_STREAM(USART0_write, NULL, _FDEV_SETUP_WRITE); 

uint8_t t1 EEMEM = 24;

void print_address(unsigned char* address) {
	printf("\r- %.2X %.2X %.2X %.2X %.2X %.2X %.2X %.2X", address[0],address[1],address[2],address[3],address[4],address[5],address[6],address[7]);
}


// поиск всех устройств на шине
uint8_t search_ow_devices(uint8_t *owDevices){
	uint8_t	i;
   	uint8_t	id[OW_ROMCODE_SIZE];
   	uint8_t	diff, sensors_count;

	sensors_count = 0;

	for( diff = OW_SEARCH_FIRST; diff != OW_LAST_DEVICE && sensors_count < MAXDEVICES ; ){ 
		OW_FindROM( &diff, &id[0] );

      	if( diff == OW_PRESENCE_ERR ) break;
      	if( diff == OW_DATA_ERR )	break;
      	for (i=0;i<OW_ROMCODE_SIZE;i++)
         	(&owDevices[sensors_count * 8])[i] = id[i];
		
		sensors_count++;
    }
	return sensors_count;
}


// Процедура подключения (записи) датчиков - последовательное подключение.
// Обязательные:
// 1. Внутренний датчик (контроль) - без отключения
// 2. Датчик обратки
// 3. Датчик подачи
// 4. Датчик помещения (управление температурой)
// 
//
// Вспомогательные
// 5. Датчик ТТ котла (печь) - для включения насоса, при отключенном эл. котле
// 6. Датчик уличной температуры
// 7. Датчик давления в системе

void set_sensors(uint8_t *sens_num, uint8_t *sens_out){
	
	uint8_t owDevicesIDs[MAXDEVICES][8];
	uint8_t nDevices = search_ow_devices(owDevicesIDs[0]);

	printf("\r---------- Found %d devices ----------", nDevices);
	
	for(uint8_t i=0; i<nDevices;i++){
		print_address(owDevicesIDs[i]);
	}
	
	
		
}


int main(void){
	stdout = &usart_str; // указываем, куда будет выводить printf 
	
	//eeprom_busy_wait();
	//eeprom_write_byte(&t1, 10);
	

//	_delay_ms(1500);

	//eeprom_busy_wait();		
	uint8_t tt = 0;
	//tt = eeprom_read_byte(&t1);
	//printf("\r%d", tt);
	
	_delay_ms(1500);
	
	USART_init();
	
	set_sensors(0, 0);
	
	//return 0;
    /* Replace with your application code */
    while (1){
		set_sensors(0, 10);
		_delay_ms(1500);
		// Gettime
		// Меаsure
		// Change freq
		/*
		t1 = 0;
		t2 = 1;
		t3 = 2;
		t4 = 3;
		
		t1 = t2+t3+t4;
		t2 = t4-t1;
*/		
		
		
    }
	
	
}
