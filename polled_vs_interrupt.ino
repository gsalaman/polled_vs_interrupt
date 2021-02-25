/* Polling inputs vs interrupts */

/* Single Pin change interrupt example. */

#define BUTTON_PIN  7
#define LED_PIN     8

int  press_count=0;

void configure_isrs( void )
{
  // On the Uno, we have 3 blocks of pin change interrupts.
  // One ISR tells us if a pin from D0 to D7 changes,
  // another tells us if a pin from A0 to A5 changes, 
  // and finally  the last tells us if a pin  from D8 to D13 changes.

  // There are three "mask" registers, one for each of those ISRs, to tell which
  // pins in that ISR to pay attention to.  A "one" means we care about that pin;
  // a zero means we don't (and we won't get the corresponding ISR for a change on 
  // that pin.

  // PCMSK0 controls D8 to D13 like this:
  // | X | X | D13 | D12 | D11| D10 | D9 | D8 |

  // PCMSK1 controls A0 to A5 like this:
  // | X | X | A5 | A4 | A3 | A2 | A1 | A0 |

  // PCMSK2 controls D7  to D0 like this:
  // | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |

  // In this sketch, we only care about changes on pin 7, so we want to set PCMSK2
  PCMSK2 = B10000000;

  //PCIFR = B00000000;
  
  // PCICR is the Uno's "Pin Change Interrupt Control Register"
  // Bit zero turns on the ISR for Pins D8 to D15
  // Bit one  turns on the ISR for pins A0 to A5
  // Bit two turns on the ISR for pins D0 to D7

  // Since we want pin 7, we enable the ISR in bit two
  PCICR = B00000100;

  // Finally, I'm gonna do a double-check here...these registers are set for pin 7, 
  // Which was #defined at the top of our file.  I want to make sure someone didn't 
  // change that #define using a little pre-processor check
  #if (BUTTON_PIN != 7)
  #error "Someone changed BUTTON_PIN!!!"
  #endif
}

ISR(PCINT2_vect)
{
  int pin7_val;

  pin7_val = digitalRead(BUTTON_PIN);

    press_count++;
  
  // the invert is because pin7 is active low
  digitalWrite(LED_PIN, !pin7_val); 
}

void setup( void )
{
  Serial.begin(9600);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  configure_isrs();

  Serial.println("Single pin change ISR example initialized");
}

void loop( void )
{

  Serial.print("Button presses: ");
  Serial.println(press_count);

  delay(1000);

}
