
#include <PS2KeyAdvanced.h>
#include <PS2KeyMap.h>
#include <ps2dev.h>

#define DATAIN 4
#define CLKIN 3
#define DATAOUT 2
#define CLKOUT 5

PS2KeyAdvanced ps2in;
//PS2KeyMap keymap;
PS2dev ps2out(DATAOUT,CLKOUT);

uint16_t input;
unsigned char leds;

void setup()
{
Serial.begin(115200);
Serial.println("Init PS2 Input" ); ps2in.begin( DATAIN, CLKIN );
Serial.println("Init PS2 Output" ); ps2out.keyboard_init();
ps2in.setNoBreak( 1 ); // Disable Break codes (key release) from PS2KeyAdvanced
ps2in.setNoRepeat( 1 ); // and set no repeat on CTRL, ALT, SHIFT, GUI while outputting
//keymap.selectMap( (char *)"DE" ); Serial.print( "Keyboard set to " ); Serial.println( keymap.getMap( ) );
}

void loop()
{
input = ps2in.available();
if( input > 0 )
  {
  input = ps2in.read();
  Serial.print( "Value " );
  Serial.print( input, HEX );
  //input = keymap.remapKey( input );
  if( input > 0 )
    {
    if( ( input & 0xFF ) )
      {
      Serial.print( " mapped " );
      Serial.print( input, HEX );
      Serial.print( " - Status Bits " );
      Serial.print( input >> 8, HEX );
      Serial.print( "  input " );
      Serial.print( input & 0xFF, HEX );
      Serial.print( "  ( " );
      Serial.write( input & 0xFF );
      Serial.print( " )\n" );
      //ps2out.keyboard_mkbrk(input);
      }
   
  else
    Serial.println( " Keyboard protocol or function" );
  }
  else Serial.println();
  
//delay( 10 );


}
}
