
	The Manual of Sleep Module
	
	This module is compatible with:
									Atmega48A/Atmega48PA,
									Atmega88A/Atmega88PA,
									Atmega168A/Atmega168PA,
									Atmega328/Atmega328P (Arduino Uno).

  Can work with other devices in the mega family,
  but without charge that works without some modifications in the code

  Marcelo H Moraes
  marceloh220@hotmail.com
  
  Sleep modes enable the application to shut down unused modules in the MCU, thereby saving power.
  The AVR provides various sleep modes allowing the user to tailor the power
  consumption to the application’s requirements.
   
  Module Sleep is a very useful module with method to offer the
  programmer several easy tools to control the reduce power features of microcontroller.
  
  This module provides...
  
  
  TO Config the sleeps features
  
  sleep(mode)			//Put the microcontroler in sleep in mode selected
  
  Accept modes are:
  IDLE to configure the sleep in idle mode
  ADCNOISE to configure the sleep in adc noise reduce mode
  POWERDOWN to configure the sleep in power down mode
  POWERSAVE to configure the sleep in power save mode
  STANDBY to configure the sleep in stanby mode
  STANDBYEXT to configure the sleep in extended standby mode
  
  In IDLE mode, the CPU and the flash program memory is turned off,
  but all others peripheral remain working, any interrupt can wake-up the CPU;
  
  In ADC NOISE mode, the CPU and the flash program memory is turned off,
  even the ports clock, but the internal peripherals remain working.
  The external interrupts INT0, INT1 and reset can wake-up the CPU, as well any internal peripheral interrupt.
  This mode reduce the i/o interference in read of ADC.
  
  In POWERDOWN mode, stop the CPU, the external oscillator and a most of internal peripherals,
  only remain working the watch dog timer (WDT), two-wire interface (TWI) and external peripheral INT0 and INT1.
  The CPU can be awake by INT0 and INT1 external interrupt, WDT interrupt, TWI address match, and external reset.
  This is the most severe sleep mode and provide the most energy savings.
  
  In POWERSAVE mode, mostly the same of POWERDOWN mode,
  but the timer2 remain working if configured in asynchronous mode.
  The CPU can be awake by INT0 and INT1 external interrupt, WDT interrupt,
  TWI address match, external reset and timer2 interrupt (if it is configured in asynchronous mode).
  
  In STANDBY mode, mostly the same of PWERDOWN mode, but the external oscillator remain working.
  The CPU can be awake by the same methods of POWERDOWN mode, and will be wake-up in 6 clock cycles.
  
  IN STANDBYEXT mode, mostly the same of POWERSAVE, but the external oscillator remain working.
  The CPU can be awake by the same methods of POWERSAVE mode, and will be wake-up in 6 clock cycles.
 
 
  TO enable and disable
  
  enable(hardware)				//Enable the hardware of microcontroller
  disable(hardware)				//Disable the hardware of microcontroller
  
  The hardware to control are:
  
  PRTIMER0 to disable or enable the timer 0
  PRTIMER1 to disable or enable the timer 1
  PRTIMER2 to disable or enable the timer 2
  PRADC to disable or enable the analog digital converter (ADC)
  PRTWI to disable or enable the two-wire interface (TWI)
  PRUSART to disable or enable the universal synchronous and asynchronous serial receiver and transmitter (USART)
  PRSPI to disable or enable the serial peripheral interface (SPI)
  SLEEP to disable or enable the sleep
  
	And this is the END.
