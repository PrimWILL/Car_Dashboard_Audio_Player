#include "mbed.h"
#include "DHT22.h"
#include "Adafruit_SSD1306.h"
#include <stdio.h>

DigitalOut myled(LED1);
// an I2C sub class that provides a constructed default
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
DigitalOut led1(LED1);

Serial pc(USBTX, USBRX);

volatile int sensor = 0;

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

void task_myTicker(){
    uint16_t temp, humid;
    int human_sensor = motion;

    get_temp_humid(&temp, &humid);

    myGUI.clearDisplay(); // claer LCD display 
    setTextCursor(0, 0);

    myGUI.printf("Temp: %u Humid: %u\r\n", temp, humid);
    myGUI.display();

    if (detect_human(&human_sensor))
        myGUI.printf("Human Detected\r\n");
    else
        myGUI.printf("Human Not Detected\r\n");
    myGUI.display();    
}


int main(){
    pc.baud(9600);

    myTicker.attach(&task_myTicker, 3);
    // print temperature, humid, human detection to LCD Display per 3 seconds

    return 0;
}