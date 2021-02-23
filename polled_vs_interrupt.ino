/* Polling inputs vs interrupts */

/* Simple interrupts:  use HW pins...must be 2 or 3 on Uno. */

#define BUTTON_PIN  3
#define LED_PIN     8

volatile bool button_state;
volatile int  press_count=0;

void setup( void )
{
  Serial.begin(9600);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  button_state = HIGH;
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), button_isr, CHANGE);
}

void button_isr(void)
{
  button_state = digitalRead(BUTTON_PIN);
  
  // Only count transitions from HIGH to LOW as presses.
  if (button_state == LOW)
  {
    press_count++;
  }

  // We want our LED on when the button is pressed, and off when
  // it's not.  Since we've got a pull-up resistor, the line is LOW
  // when it's pressed and HIGH when it's not.
  digitalWrite(LED_PIN, !button_state);

  // Only count transitions from HIGH to LOW as presses.
  if (button_state == LOW)
  {
    press_count++;
  }

}

void loop( void )
{
   Serial.print(press_count);
   Serial.println(" button presses");

   delay(1000);
}
