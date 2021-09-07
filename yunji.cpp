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
Ticker myTicker;

int music=1;
int x, y;
int school_bell[25] = { G, G, A, A, G, G, E, G, G, E, E, D, G, G, A, A, G, G, E, G, E, D, E, C };
int little_star[43] = { C, C, G ,G, A, A, G, F, F, E, E, D, D, C, G, G, F ,F ,E, E, D, G, G, F, F, E, E, D, C, C, G ,G, A, A, G, F, F, E, E, D, D, C};
int jingle_bell[26] = { E, E, E, E, E, E, E, G, C, D, E, F, F, F, F, F, E, E, E, E, D, D, E, D, G };
int playing=0;	

	
void Jingle_Bell();
void Little_Star();
void School_Bell();
void Music_Start();

void task_myTimeout(){
	pc.printf("timeout!");
	playing=0;
	sound.period(0);
	sound=0;
}

void task_myTicker(){
	//pc.printf("tricker!\r\n");
			pc.printf("\n<<playing = %d\r\n\n", playing);

	if(!button2){
		pc.printf("button2 is pressed!\r\n");
		
		if(playing==0){
			pc.printf("music is stop now, start music!\r\n");
			Music_Start();
		}
		if(playing==1){
			pc.printf("Stop in 2s!!!\r\n");
			myTimeout.attach(&task_myTimeout, 2);
			//playing=0;
		}
	}
}

int main(){   
	pc.baud(9600);
	myTicker.attach(&task_myTicker, 0.3);

	while(1){
		if(!button1){
			pc.printf("button 1 is pressed!\r\n");
			music--;

			mt.backward(0.2);
			wait(0.8);
			mt.stop();
			Music_Start();
		}
		if(!button2){
			Music_Start();
		}
		if(!button3){
			pc.printf("button 3 is pressed!\r\n");
			music++;
			
			mt.forward(0.2);
			wait(0.8);
			mt.stop();	
			Music_Start();			
		}		
	}
}

void Music_Start(){
	music%=3;
	if(music == 0) School_Bell();
	else if(music == 1) Little_Star();
	else if(music == 2) Jingle_Bell();
}	
void Jingle_Bell(){
	playing=1;
	pc.printf("2 : Jingble bell\r\n");
	for(int i=0; i<3; i++){
		sound.period(1/(double)jingle_bell[i]);
		sound=0.5;
		wait(0.3);
		if(playing==0) return;
	}
	wait(0.35);

	for(int i=3; i<6; i++){
		sound.period(1/(double)jingle_bell[i]);
		wait(0.3);
		if(playing==0) return;
	}
	wait(0.35);
	
	for(int i=6; i<11; i++){
		sound.period(1/(double)jingle_bell[i]);
		wait(0.3);
		if(playing==0) return;
	}
	wait(0.5);
	
	for(int i=11; i<23; i++){
		sound.period(1/(double)jingle_bell[i]);
		wait(0.3);
		if(playing==0) return;
	}
	wait(0.3);
	
	for(int i=23; i<26; i++){
		sound.period(1/(double)jingle_bell[i]);
		wait(0.5);
		if(playing==0) return;
	}
	playing=0;
	return;
}
	
void Little_Star(){
	playing=1;
	pc.printf("1 : Little_Start\r\n");
	for(int i=0; i<7; i++){
		sound.period(1/(double)little_star[i]);
		sound=0.5;
		wait(0.3);
		if(playing==0) return;
	}
	wait(0.35);

	for(int i=7; i<14; i++){
		sound.period(1/(double)little_star[i]);
		wait(0.3);
		if(playing==0) return;
	}
	wait(0.35);
	
	for(int i=14; i<21; i++){
		sound.period(1/(double)little_star[i]);
		wait(0.3);
		if(playing==0) return;
	}
	wait(0.35);
	
	for(int i=21; i<28; i++){
		sound.period(1/(double)little_star[i]);
		wait(0.3);
		if(playing==0) return;
	}
	wait(0.35);
	
	for(int i=28; i<35; i++){
		sound.period(1/(double)little_star[i]);
		wait(0.3);
		if(playing==0) return;
	}
	wait(0.35);
	
	for(int i=35; i<43; i++){
		sound.period(1/(double)little_star[i]);
		wait(0.3);
		if(playing==0) return;
	}
	playing=0;
	return;
}

void School_Bell(){
	playing=1;
	pc.printf("0 : School bell\r\n");
	for(int i=0; i<7; i++){
		sound.period(1/(double)school_bell[i]);
		sound=0.5;
		wait(0.3);
		if(playing==0) return;
	}
	wait(0.4);

	for(int i=7; i<12; i++){
		sound.period(1/(double)school_bell[i]);
		wait(0.3);
		if(playing==0) return;
	}
	wait(0.5);
	
	for(int i=12; i<19; i++){
		sound.period(1/(double)school_bell[i]);
		wait(0.3);
		if(playing==0) return;
	}
	wait(0.4);
	
	for(int i=19; i<25; i++){
		sound.period(1/(double)school_bell[i]);
		wait(0.3);
		if(playing==0) return;
	}
	playing=0;
	return;
}	
