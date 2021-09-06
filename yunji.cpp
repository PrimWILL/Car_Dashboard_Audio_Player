#include "mbed.h"
#include "motordriver.h"

#define C 262
#define D 294
#define E 330
#define F 349
#define G 392
#define A 440
#define B 494

Serial pc(USBTX, USBRX);

DigitalIn button1 (PA_14);
DigitalIn button2 (PB_7);
DigitalIn button3 (PC_4);

Motor mt(D11, PC_0);
PwmOut sound(PC_9);
DigitalOut myled(LED1);

Timeout myTimeout;

int x, y;
int school_bell[25] = { G, G, A, A, G, G, E, G, G, E, E, D, G, G, A, A, G, G, E, G, E, D, E, C };
int little_star[43] = { C, C, G ,G, A, A, G, F, F, E, E, D, D, C, G, G, F ,F ,E, E, D, G, G, F, F, E, E, D, C, C, G ,G, A, A, G, F, F, E, E, D, D, C};
int jingle_bell[26] = { E, E, E, E, E, E, E, G, C, D, E, F, F, F, F, F, E, E, E, E, D, D, E, D, G };
void task_myTimeout(){
	pc.printf("timeout! task activated\r\n");
}
	
void Jingle_Bell(){

		for(int i=0; i<3; i++){
					sound.period(1/(double)jingle_bell[i]);
          sound=0.5;
					wait(0.3);
				}
				wait(0.35);
				
				for(int i=3; i<6; i++){
					sound.period(1/(double)jingle_bell[i]);
          sound=0.5;
					wait(0.3);
				}
				wait(0.35);
				for(int i=6; i<11; i++){
					sound.period(1/(double)jingle_bell[i]);
          sound=0.5;
					wait(0.3);
				}
				wait(0.5);
				for(int i=11; i<23; i++){
					sound.period(1/(double)jingle_bell[i]);
          sound=0.5;
					wait(0.3);
				}
				wait(0.3);
				for(int i=23; i<26; i++){
					sound.period(1/(double)jingle_bell[i]);
          sound=0.5;
					wait(0.5);
				}
}
	
void Little_Star(){
	for(int i=0; i<7; i++){
					sound.period(1/(double)little_star[i]);
          sound=0.5;
					wait(0.3);
				}
				wait(0.35);
				
				for(int i=7; i<14; i++){
					sound.period(1/(double)little_star[i]);
          sound=0.5;
					wait(0.3);
				}
				wait(0.35);
				for(int i=14; i<21; i++){
					sound.period(1/(double)little_star[i]);
          sound=0.5;
					wait(0.3);
				}
				wait(0.35);
				for(int i=21; i<28; i++){
					sound.period(1/(double)little_star[i]);
          sound=0.5;
					wait(0.3);
				}
				wait(0.35);
				for(int i=28; i<35; i++){
					sound.period(1/(double)little_star[i]);
          sound=0.5;
					wait(0.3);
				}
				wait(0.35);
				for(int i=35; i<43; i++){
					sound.period(1/(double)little_star[i]);
          sound=0.5;
					wait(0.3);
				}
	
}
void School_bell(){
				for(int i=0; i<7; i++){
					sound.period(1/(double)school_bell[i]);
          sound=0.5;
					wait(0.3);
				}
				wait(0.4);
				
				for(int i=7; i<12; i++){
					sound.period(1/(double)school_bell[i]);
          sound=0.5;
					wait(0.3);
				}
				wait(0.5);
				for(int i=12; i<19; i++){
					sound.period(1/(double)school_bell[i]);
          sound=0.5;
					wait(0.3);
				}
				wait(0.4);
				for(int i=19; i<25; i++){
					sound.period(1/(double)school_bell[i]);
          sound=0.5;
					wait(0.3);
				}
}	
	
int main(){   
	int music=1;
   pc.baud(9600);
   while(1){
		 if(!button1){
			 pc.printf("button 1 is pressed!\r\n");
			 music--;
			 if(music<0){
				 pc.printf("No next song\n");
				 music++;
			 }
			 else {
				 mt.backward(0.2);
				 wait(0.8);
				 mt.stop();
			 }
			 if(music == 0){
					School_bell();					
				}
				else if(music == 1){
					Little_Star();
				}
				else if(music == 2){
					Jingle_Bell();
				}
			 
		 }
      
      if(!button2){      // sw9
				pc.printf("button 2 is pressed!\n");
				myTimeout.attach(&task_myTimeout, 5.0);				
      }
			
			if(!button3){
			 pc.printf("button 3 is pressed!\r\n");
			 music++;
				if(music>2){
				 pc.printf("No next song\n");
				 music--;
			 }
			 else {
				 mt.forward(0.2);
				 wait(0.8);
				 mt.stop();
			 }
				if(music == 0){
					School_bell();					
				}
				else if(music == 1){
					Little_Star();
				}
				else if(music == 2){
					Jingle_Bell();
				}
			 
		 }
			
				
   }
}
