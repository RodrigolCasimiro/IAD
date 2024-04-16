// Parameters



// Sets up pins
const int AnalogOut = A0;
const int AnalogIn  = A1;
const int PinOut = 3;
const int PinIn = 4;
const int PinPwm = 9; // PWM pin

// Declare variables
int comando;
int variable;
int analog_out_bit;
int n_muon;
double analog_out_val;
int time_dif = 0;
unsigned long timestamp; // Captura o timestamp do evento
unsigned long timestamp_ant = 0;
int det;
int num = 1;


// Serial and pin setup
void setup() {
	Serial.begin(9600);
	Serial.setTimeout(.1);
  analog_out_val = 2000; // mV
  analog_out_bit = (analog_out_val * 4095/ 5000);
	// pinMode(PinOut, OUTPUT);
	// pinMode(PinIn, INPUT);
	pinMode(AnalogIn, INPUT);
  // pinMode(PinPwm, OUTPUT); // Set the PWM pin as an output
  // analogWrite(PinPwm, 1); // Set the PWM duty cycle to approximately 5%
  // analogWriteResolution(12); // 12 bits
  // analogWrite(AnalogOut,analog_out_bit); // Value = (desired value / 5V) * 4095 (2^12-1)
  
  int timeStart = millis();
  // matrix.begin();
  timestamp_ant = millis() - timeStart;
}

void loop() {
  det = analogRead(AnalogIn); 
  // Serial.println(det);
  num = 1;
  time_dif = millis() - timestamp_ant;
  if (time_dif > 10000){
    num = num + 1;
    timestamp_ant = millis();
  }
  int threshold = num * 10;
  if (det > threshold) {
    Serial.print(threshold*5000/1024); // mV
    Serial.print(" ");
    Serial.println(det);
    delay(10);
  }

  if (!det){

    timestamp = millis();
    time_dif = timestamp - timestamp_ant;
    if (time_dif > 100){
      Serial.println(time_dif); // ignoramos as medicoes realizadas na primeira hora
      // displayAnimation();
      timestamp_ant = timestamp;
    }
  }
}