#include "mbed.h"
#include "motordriver.h"
#include "DHT22.h"
#include "Adafruit_SSD1306.h"
#include <stdio.h>

#define C 262
#define D 294
#define E 330
#define F 349
#define G 392
#define A 440
#define B 494

Serial pc(USBTX, USBRX);

DigitalIn button1 (PA_14);
InterruptIn button2 (PB_7);
DigitalIn button3 (PC_4);
 
Motor mt(D11, PC_0);
PwmOut sound(PC_9);
DigitalOut myled(LED1);

class I2CPreInit : public I2C{
    public:
    I2CPreInit(PinName sda, PinName scl) : I2C(sda, scl){
        frequency(400000);
        start(); // Adafruit logo
    };
};

I2C myI2C(I2C_SDA, I2C_SCL);
Adafruit_SSD1306_I2c myGUI(myI2C, D13, 0x78, 64, 128);

DHT22 sensor (PB_2);

DigitalIn motion(D5);

Timeout myTimeout;
Ticker myTicker;
Ticker myTicker2;

volatile int human_sensor = 0;

int school_bell[25] = { G, G, A, A, G, G, E, G, G, E, E, D, G, G, A, A, G, G, E, G, E, D, E, C };
int little_star[43] = { C, C, G ,G, A, A, G, F, F, E, E, D, D, C, G, G, F ,F ,E, E, D, G, G, F, F, E, E, D, C, C, G ,G, A, A, G, F, F, E, E, D, D, C};
int jingle_bell[26] = { E, E, E, E, E, E, E, G, C, D, E, F, F, F, F, F, E, E, E, E, D, D, E, D, G };
int playing=0;	
int music=1;

void Jingle_Bell();
void Little_Star();
void School_Bell();
void Music_Start();
void task_myTimeout();
void task_myTicker();

void task_myTicker();
void get_temp_humid();
void detect_human();
void task_myTicker2();	
	
void BUTTON_ISR(){
	pc.printf("button2 is pressed!\r\n");
		
		if(playing==0){
			pc.printf("music is stop now, start music!\r\n");
			wait(0.3);
			Music_Start();
		}
		else if(playing==1){
			pc.printf("Stop in 2s!!!\r\n");
			myTimeout.attach(&task_myTimeout, 2);
			//playing=0;
		}
}
	
int main(){   
	pc.baud(9600);
	//myTicker.attach(&task_myTicker, 0.5);
	button2.rise(&BUTTON_ISR);
	myTicker2.attach(&task_myTicker2, 1);
	
	while(1){
		//pc.printf("\n<<playing = %d\r\n\n", playing);

		if(!button1){
			pc.printf("button 1 is pressed!\r\n");
			music--;

			mt.backward(0.2);
			wait(0.8);
			mt.stop();
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

void task_myTimeout(){
	pc.printf("timeout!");
	playing=0;
	sound.period(0);
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
void get_temp_humid(uint16_t* temp, uint16_t* humid) {
    float h = 0.0f, c = 0.0f;

    sensor.sample();
    c = sensor.getTemperature();
    h = sensor.getHumidity();

    *temp = (uint16_t)(c/10);
    *humid = (uint16_t)(h/10);
}

bool detect_human(int* human_sensor) {
    if (human_sensor) {
        *human_sensor = 0;
        return true;
    }
    return false;
}

void task_myTicker2(){
	pc.printf("ticker2\r\n");
    uint16_t temp, humid;
    int human_sensor = motion;

    get_temp_humid(&temp, &humid);

    myGUI.clearDisplay(); // claer LCD display 
    myGUI.setTextCursor(0, 0);

    myGUI.printf("Temp: %u Humid: %u\r\n", temp, humid);
    myGUI.display();

    if (detect_human(&human_sensor))
        myGUI.printf("Human Detected\r\n");
    else
        myGUI.printf("Human Not Detected\r\n");
    myGUI.display();    
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
