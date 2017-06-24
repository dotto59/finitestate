#include <SimpleTimer.h>

#include <FiniteState.h>
// ***********************************************
// MACCHINA A STATI FINITI
// ***********************************************
FiniteState fsm;
// Stati del robot
#define S_START 1
#define S_FLASH 2
#define S_STEADY 3
#define S_LED2 4
// Condizioni del robot
#define C_BUTTON 0
#define C_LED2_OFF 1
// Action del robot
#define A_LED_OFF 0
#define A_LED_ON 1
#define A_FLASH 2
#define A_LED2_ON 3

// ***********************************************
// COSTANTI E MACRO
// ***********************************************
// Pin
#define LED 13
#define LED2 12
#define BUTTON 7

// ***********************************************
// VARIABILI
// ***********************************************
int blink = 0;
int led = LOW;

// ***********************************************
// OGGETTI GLOBALI
// ***********************************************
const int BREAK = fsm.BREAK;
const int NONE = fsm.NONE;
// the timer object
SimpleTimer timer;
int tmrBlink = -1;
int tmrSingle = -1;

// ***********************************************
void setup() {  
  Serial.begin(115200);
  delay(500);

  // Definizione degli stati
  // Stato START, evento BUTTON, azione FLASH, parametro 200, nuovo stato FLASH
  fsm.Write(S_START, C_BUTTON, A_FLASH, 200, S_FLASH);
  // Stato FLASH, evento BUTTON, azione LED_ON, parametro 0, nuovo stato STEADY
  fsm.Write(S_FLASH, C_BUTTON, A_LED_ON, 0, S_STEADY);
  // Stato STEADY, evento BUTTON, azione LED2_ON, parametro 5000, nuovo stato LED2
  fsm.Write(S_STEADY, C_BUTTON, A_LED2_ON, 5000, S_LED2);
  // Stato LED2, evento LED2_OFF, azione LED_OFF, parametro 0, nuovo stato START
  fsm.Write(S_LED2, C_LED2_OFF, A_LED_OFF, 0, S_START); 
  // Stato LED2, evento BUTTON, azione LED_OFF, parametro 0, nuovo stato HALT
  fsm.Write(S_LED2, C_BUTTON, A_LED_OFF, 0, fsm.HALT); 
  
  // Inizia dal primo stato
  fsm.Set(S_START);
  Serial.print("Stato iniziale=");
  Serial.println(fsm.State);
  
  pinMode(LED, OUTPUT);  
  pinMode(LED2, OUTPUT);  
  pinMode(BUTTON, INPUT);
  
}

// ***********************************************
void loop() {
  // Ciclo di esecuzione degli stati
  while ( fsm.State != fsm.HALT && fsm.Next() != BREAK ) {
    // Verifica se è presente una condizione per cambiare stato
    if ( TestCondition() ) {
      DoAction();
      fsm.SetNext();
      Serial.print("STATO: ");
      Serial.println(fsm.State);
      break;
    }
  }

  // Altre azioni
  DoWork();
  
}

boolean TestCondition() {
  static int val0 = 0;
  int btn;
  
  switch ( fsm.Condition() ) {
    case C_BUTTON:
      btn = digitalRead(BUTTON);
      if ((btn == HIGH) && (val0 == LOW)) {
        val0 = btn;
        delay(200);
        return true;
      }
      val0 = btn;
      return false;

    case C_LED2_OFF:
        return (digitalRead(LED2) == LOW);
      
  }
  return false;
}

void DoAction() {
  switch ( fsm.Action() ) {
    
    case A_LED_OFF:
      blink = 0;
      digitalWrite(LED, LOW);
      return;
      
    case A_LED_ON:
      if ( tmrBlink != -1 ) {
        timer.deleteTimer(tmrBlink);
        tmrBlink = -1;
      }
      digitalWrite(LED, HIGH);
      digitalWrite(LED2, LOW);
      return;
      
    case A_FLASH:
      blink = fsm.Param();
      digitalWrite(LED, HIGH);
      digitalWrite(LED2, LOW);
      if ( tmrSingle != -1 ) {
        timer.deleteTimer(tmrSingle);
        tmrSingle = -1;
      }
      tmrBlink = timer.setInterval(blink, BlinkLed);
      return;
      
    case A_LED2_ON:
      blink = fsm.Param();
      digitalWrite(LED, LOW);
      digitalWrite(LED2, HIGH);
      if ( tmrBlink != -1 ) {
        timer.deleteTimer(tmrBlink);
        tmrBlink = -1;
      }
      tmrSingle = timer.setTimeout(blink, Led2Off);
      return;
  }
  return;
}

void DoWork() {
  timer.run();
}

void BlinkLed() {
  digitalWrite(LED, !digitalRead(LED));
}

void Led2Off() {
  digitalWrite(LED2, LOW);
}

