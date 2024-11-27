

#include <avr/io.h>
#include <util/delay.h>
#include "timebase.h"
#include "app.h"

int main(void){
  
  Timebase_Init(1000);
  App_Setup();
  
  while(1){
  
    while(1){
	  App_Main_Loop();
	  Timebase_Main_Loop_Executables();
	}
	
  }
}