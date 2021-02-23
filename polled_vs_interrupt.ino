/* Polling inputs vs interrupts */

#define BUTTON_PIN  8

int last_button_state;
int press_count=0;

void setup( void )
{
  Serial.begin(9600);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  last_button_state = HIGH;
}

void loop( void )
{
  int current_button_state;

  current_button_state = digitalRead(BUTTON_PIN);

  // Has our button state changed?
  if (current_button_state != last_button_state)
  {
    if (current_button_state == LOW)
    {
      press_count++;
      Serial.print("Button Pressed.  Count=");
      Serial.println(press_count);
    }
    else
    {
      Serial.println("Button Released.");
    }
    
  }  // end of "if new button state"
  
}
