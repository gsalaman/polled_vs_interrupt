/* Polling inputs vs interrupts */

/* Polled example....no delays */

#define BUTTON_PIN  3
#define LED_PIN     8

int  last_button_state;
int  press_count=0;

void setup( void )
{
  Serial.begin(9600);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  last_button_state = HIGH;

  Serial.println("Polled Button:  initialized");
}

void loop( void )
{
  int button_state;
  
  button_state = digitalRead(BUTTON_PIN);
  
  // Only count transitions from HIGH to LOW as presses.
  if ((last_button_state == HIGH) && (button_state == LOW))
  {
    press_count++;
    Serial.print(press_count);
    Serial.println(" button presses");
  }

  last_button_state = button_state;

  // We want our LED on when the button is pressed, and off when
  // it's not.  Since we've got a pull-up resistor, the line is LOW
  // when it's pressed and HIGH when it's not.
  digitalWrite(LED_PIN, !button_state);

}
