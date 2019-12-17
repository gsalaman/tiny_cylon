  
// 74595 lines 
#define DATA_PIN  0      // maps to pin 5 on tiny
#define CLK_PIN   1      // ...pin 6
#define LATCH_PIN 2      // ...pin 7

// ADC line
#define SPEED_PIN   A3     // Maps to pin ... on tiny

// We have 8 output LEDs in our current incarnation.
#define OUTPUT_LINES 8

//==============================================================================================
// FUNCTION:  write bit.
//  
// Outputs a bit to the shift register and clocks it in.
//==============================================================================================
void write_bit(int bit)
{
  digitalWrite(DATA_PIN, bit);
  digitalWrite(CLK_PIN, HIGH);
  digitalWrite(CLK_PIN, LOW);
}

//==============================================================================================
// FUNCTION:  latch_data
//
// stores the current shift registers in the latch memorie  
//==============================================================================================
void latch_data( void )
{
  digitalWrite(LATCH_PIN, HIGH);
  digitalWrite(LATCH_PIN, LOW);
}

//==============================================================================================
// FUNCTION:  write_and_latch_byte
//
// Writes an entire byte to the shift register, and then latches the data.  Note this function
// goes MSB first.
//==============================================================================================
#define BITS_IN_BYTE 8
void write_and_latch_byte( int data )
{
  int temp_bit;
  int temp_data;
  int i;
  
  data &= 0xFF;
    
  temp_data = data;
  
  for (i = 0; i < BITS_IN_BYTE; i++)
  {
    // we only want the MSB
    temp_bit = temp_data & 0x80;
    temp_bit = temp_bit >> 7;
    write_bit(temp_bit);

    // now shift our byte to get the next bit
    temp_data = temp_data << 1;     
  }

  latch_data();
  
}

//==============================================================================================
// FUNCTION:  write_and_latch_byte_lsb_first
//
// Writes an entire byte to the shift register, and then latches the data.  Note this function
// goes LSB first.
//==============================================================================================
void write_and_latch_byte_lsb_first( int data )
{
  int temp_bit;
  int temp_data;
  int i;
  
  data &= 0xFF;
    
  temp_data = data;
  
  for (i = 0; i < BITS_IN_BYTE; i++)
  {
    // we only want the LSB
    temp_bit = temp_data & 0x01;
    write_bit(temp_bit);

    // now shift our byte to get the next bit
    temp_data = temp_data >> 1;     
  }

  latch_data();
  
}

//==============================================================================================
// FUNCTION:  setup
//==============================================================================================
void setup() 
{
  int i;
  
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLK_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);

  // Make sure all lines are low
  digitalWrite(DATA_PIN, LOW);
  digitalWrite(CLK_PIN, LOW);
  digitalWrite(LATCH_PIN, LOW);
  
  // make sure our shift register and latches are all 0.
  for (i=0; i<OUTPUT_LINES; i++)
  {
    write_bit(0);
  }
  latch_data();

  // now a quick LED test...write a 1 to all registers.
  for (i=0; i<OUTPUT_LINES; i++)
  {
    write_bit(1);
    latch_data();
    delay(500);
  }

  // ...and now put them back to all zeros before starting for real.
  for (i=0; i<OUTPUT_LINES; i++)
  {
    write_bit(0);
  }
    
  latch_data();

  delay(1000);
}

//==============================================================================================
// FUNCTION:  loop
//==============================================================================================
void loop() 
{
  static int  eye_pos = 0x01;
  static bool fwd = true;
  int         wait_ms;
  
  write_and_latch_byte(eye_pos);
  
  if (fwd)
  {
    if (eye_pos == 0x80)
    {
      eye_pos = eye_pos >> 1;
      fwd = false;
    }
    else
    {
      eye_pos = eye_pos << 1;
    }
  }
  else
  {
    if (eye_pos == 0x01)
    {
      eye_pos = eye_pos << 1;
      fwd = true;
    }
    else
    {
      eye_pos = eye_pos >> 1;
    }
  }

  // Analog read should give us a number between 0 and 1024. 
  // Use that as a number to determine update speed in ms.
  wait_ms = analogRead(SPEED_PIN);

  delay(wait_ms);
}
