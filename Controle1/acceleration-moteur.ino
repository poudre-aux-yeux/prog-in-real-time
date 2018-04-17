#define PIN_MOTOR 9
#define PIN_POT A0
#define INCREMENT_TIME (1000.0/(0.1*255))

void setup() {
    pinMode(PIN_POT, INPUT);
    pinMode(PIN_MOTOR, OUTPUT);
    analogWrite(PIN_MOTOR, 0);
}

void loop() {
    int consigne = map(analoRead(PIN_POT), 0, 1023, 0, 255);

    static int previous = 0;
    static unsigned long refTime = millis();

    if(millis()>= (refTime + INCREMENT_TIME)) {
        refTime = millis();
        if (consigne > previous) analogWrite(PIN_MOTOR, ++previous);
        elseif(consigne < previous) analogWrite(PIN_MOTOR, --previous);
    }
}
