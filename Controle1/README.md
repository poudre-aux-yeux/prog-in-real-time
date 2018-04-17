# Énoncé

Sur mon Arduino sont branchés un potentiomètre sur le pin A0 et un contrôleur de moteur sur le pin  (compatible PWM). Ce contrôleur permet, à partir d'un signal PWM de faire tourner +/- vite un moteur électrique (en d'autres termes, si le PWM est à 0% le moteur ne tourne pas, à 50% le moteur tourne à la moitié de sa vitesse maximale et à 100% le moteur tourne au maximum de sa vitesse).

On veut que la vitesse du moteur varie avec celle du potentiomètre mais avec une accéleération contrôlée d'environ 10% par seconde. Par exemple si mon moteur tourne à 10% et que d'un coup, la nouvelle consigne liée au potentiomètre passe à 50%, alors le minicontrôleur devra progressivement faire accélérer le moteur pendant 4 secondes.

Rappels :

N'oubliez pas que le convertisseur analogique-numérique de l'ATMEGA328P est 10-bits et que le générateur PWM est 8-bits.

byte, int, long, float, char  
void setup()  
void loop()  
pinMode(pin, mode)  
digitalWrite(pin, etat)  
Serial.begin(vitesse)  
Serial.print(message)  
analogRead(pin)  
analogWrite(pin, valeur)  
millis()  
microseconds()

```c++
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
```
