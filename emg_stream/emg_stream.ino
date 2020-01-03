#include <ArduinoSTL.h>

using namespace std;

// Set of pins for anlaysis
const int pin5 = A5;
const int pin4 = A4;
const int pin3 = A3;
const int pin2 = A2;
const int pin1 = A1;
const int pin0 = A0;

unsigned long timer = 0;

// For signal processing
vector<int> pin5Values;
vector<int> pin5DenoisedValues;
vector<int> pin4Values;
vector<int> pin4DenoisedValues;
vector<int> pin3Values;
vector<int> pin3DenoisedValues;
vector<int> pin2Values;
vector<int> pin2DenoisedValues;
vector<int> pin1Values;
vector<int> pin1DenoisedValues;
vector<int> pin0Values;
vector<int> pin0DenoisedValues;

// Track uniform vector size
int size = 0;

// Initialize Pin Values
int pin5Value = 0;
int pin4Value = 0;
int pin3Value = 0;
int pin2Value = 0;
int pin1Value = 0;
int pin0Value = 0;

// Current denoised response from shield
int pin5DenoisedResponse = 0;
int pin4DenoisedResponse = 0;
int pin3DenoisedResponse = 0;
int pin2DenoisedResponse = 0;
int pin1DenoisedResponse = 0;
int pin0DenoisedResponse = 0;

// Flag to determine whether or not we are currently in an action
bool inAction = false;

const int lt = 10000;

void setup() {
   Serial.begin(9600);
}

void loop() {
  if (micros() > timer)
  {
    timer += lt;

    // Live denoising
    pin5Value = analogRead(pin5);
    pin4Value = analogRead(pin4);
    pin3Value = analogRead(pin3);
    pin2Value = analogRead(pin2);
    pin1Value = analogRead(pin1);
    pin0Value = analogRead(pin0);

    // Vector for live denoising/filtering, holds raw data
    pin5Values.insert(pin5Values.begin(), pin5Value);
    pin4Values.insert(pin4Values.begin(), pin4Value);
    pin3Values.insert(pin3Values.begin(), pin3Value);
    pin2Values.insert(pin2Values.begin(), pin2Value);
    pin1Values.insert(pin1Values.begin(), pin1Value);
    pin0Values.insert(pin0Values.begin(), pin0Value);

    // Vector for action values, holds denoised values
    pin5DenoisedValues.insert(pin5DenoisedValues.begin(), pin5DenoisedResponse);
    pin4DenoisedValues.insert(pin4DenoisedValues.begin(), pin4DenoisedResponse);
    pin3DenoisedValues.insert(pin3DenoisedValues.begin(), pin3DenoisedResponse);
    pin2DenoisedValues.insert(pin2DenoisedValues.begin(), pin2DenoisedResponse);
    pin1DenoisedValues.insert(pin1DenoisedValues.begin(), pin1DenoisedResponse);
    pin0DenoisedValues.insert(pin0DenoisedValues.begin(), pin0DenoisedResponse);


    // Serial Analysis
    Serial.print(pin5Value);
    Serial.print(",");
    Serial.print(pin4Value);
    Serial.print(",");
    Serial.print(pin3Value);
    Serial.print(",");
    Serial.print(pin2Value);
    Serial.print(",");
    Serial.print(pin1Value);
    Serial.print(",");
    Serial.println(pin0Value);

    // Tracks size of all vectors
    size +=1;

    // When we have enough data (n=3, for now, next, and before) denoise the response
    if (size > 4){

    // Denoised response using TKEO
      pin5DenoisedResponse = pin5Values.at(1)*pin5Values.at(1) - pin5Values.at(0)*pin5Values.at(2);
      pin4DenoisedResponse = pin4Values.at(1)*pin4Values.at(1) - pin4Values.at(0)*pin4Values.at(2);
      pin3DenoisedResponse = pin3Values.at(1)*pin3Values.at(1) - pin3Values.at(0)*pin3Values.at(2);
      pin2DenoisedResponse = pin2Values.at(1)*pin2Values.at(1) - pin2Values.at(0)*pin2Values.at(2);
      pin1DenoisedResponse = pin1Values.at(1)*pin1Values.at(1) - pin1Values.at(0)*pin1Values.at(2);
      pin0DenoisedResponse = pin0Values.at(1)*pin0Values.at(1) - pin0Values.at(0)*pin0Values.at(2);

      // Avoid overflow
      pin5Values.pop_back();
      pin4Values.pop_back();
      pin3Values.pop_back();
      pin2Values.pop_back();
      pin1Values.pop_back();
      pin0Values.pop_back();
      pin5DenoisedValues.pop_back();
      pin4DenoisedValues.pop_back();
      pin3DenoisedValues.pop_back();
      pin2DenoisedValues.pop_back();
      pin1DenoisedValues.pop_back();
      pin0DenoisedValues.pop_back();
    }
  }
}
