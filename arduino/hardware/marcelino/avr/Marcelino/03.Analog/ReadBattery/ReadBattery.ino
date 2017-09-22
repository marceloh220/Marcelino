/*
 * Marcelo H Moraes
 * marceloh220@hotmail.com
 * 
 * Read the analog pin A0 of Arduino Uno board. 
 * And read A1 pin with the internal reference to determine the voltage of a lithium 3.3V battery.
 * With the internal reference voltage the measures becomes more precise.
 * 
 * The maximum value read in this mode is 1.1 V,
 * so that the battery monitoring is connected to the A1 pin through a voltage divider 1 / 4.7
 * formed by a resistor R1 = 47k and a resistor R2 of 10k
 *                    ______         ______
 *     Battery |-----|______|---o---|______|-----| GND
 *                      R1      |      R2
 *                      47K     o      10K
 *                              A1
 * 
 * Vout = Vin * R2/R1 => Vin = Vout * R1/R2
 * 
 * 
 * If the battery is the same as the vcc microcontroller,
 * using the internal reference voltage is a good practice to measure this voltage.
 * That way the voltage will be measured correct even if the battery lose your charge.
 * 
 * A simple sketch in Arduino using Marcelino cores.
 * 
 * For detail of the modules read the manual.
 * 
 */

Analog analog;              //Module Analog instantiate
Serial serial(9600);        //Module Serial instantiate
Delay delay;                //Module Delay instantiate

void setup() {
  //The Analog module initiate with a DEFAULT aref and prescale in 1/64
}

void loop() {

  word anyvalue = analog.read(A0);              //Read the analog pin A0 any value of 0 to 5V

  word battery = analog.read(A1, INTERNAL);     //Read the battery with temporary internal reference voltage

  //Using the equation:
  // Vinput = ADC * ( Aref / 1023 )
  
  double Vinput = battery * (1.1 / 1023);       //Calcule the input voltage

  //To convert the input voltage in battery voltage
  // Vbattery = Vinput * ( R1 / R2 )

  double Vbattery = Vinput * 4.7;               //Calcule the batery voltage

  serial.print("Any Value: ");
  serial.println(anyvalue);                     //Print A0 value read in serial monitor

  serial.print("Battery: ");
  serial.print(Vbattery);                       //Print battery voltage in serial monitor
  serial.println(" V");

  delay.ms(500);                                //Wait a time
  
}
