#include "sleep.h"

Sleep::Sleep()
{
	wdt_disable();
	extInt0_ = false;
	extInt1_ = false; 
	watchDogTimeOut_ = false; 

}


void Sleep::setSleepMode(int mode)
{
  sleepMode_ = mode;
}

// EXT_INT_0 = 0, EXT_INT_1 = 1, WATCHDOG_TIMER = 2

void Sleep::addWakeEvent(int interrupt,int intervalORMode)
{

	if(interrupt == 0)
	{
		extInt0_ = true;
		interruptMode_ = intervalORMode;
	}
	else if(interrupt == 1)
	{
		extInt1_ = true;
		interruptMode_ = intervalORMode;
	}
	else if(interrupt == WATCH_DOG_TIMER)
	{
		watchDogTimeOut_ = true;
		setWakeInterval(intervalORMode); 
	}

  	


}

/***********************************************************
 * 
 * setWakeInterval
 * 
 *  0=16ms, 1=32ms,2=64ms,3=128ms,4=250ms,5=500ms
 *  6=1 sec,7=2 sec, 8=4 sec, 9= 8sec
 ***********************************************************/
void Sleep::setWakeInterval(int interval) {
  
  cli();

  byte bb;
  int ww;
  if (interval > 9 ) interval=9;
  bb=interval & 7;
  if (interval > 7) bb|= (1<<5);
  bb|= (1<<WDCE);
  ww=bb;
  //Serial.println(ww);

  MCUSR &= ~(1<<WDRF);
  // start timed sequence
  WDTCSR |= (1<<WDCE) | (1<<WDE); //enable change 
  // set new watchdog timeout value
  WDTCSR = bb;
  WDTCSR |= (1<<WDIE);

  sei();

}	

void Sleep::sleepNow(int mode, int wakeEvent, int interval)
{
  setSleepMode(mode);
  addWakeEvent(wakeEvent);
  setWakeInterval(interval);
  sleepNow();

}

void Sleep::sleepNow()
{
	boolean wakeCheck = false; //did you forget to enable a wake state? 	
	
  set_sleep_mode(sleepMode_);
  sleep_enable();
  
  //attach interrupts if desired, if no interrupts then reset with watchdog
  if(extInt0_ == true)
  {
	detachInterrupt(0);
  	attachInterrupt(0,sleepHandler, interruptMode_);
	wakeCheck = true;
  }
  else if(extInt1_ == true)
  {
	detachInterrupt(1);
	attachInterrupt(1,sleepHandler, interruptMode_);
	wakeCheck = true;
  }
  else if(watchDogTimeOut_ == true)
  {
	wakeCheck = true; 
  }	
 
  
  if(wakeCheck == true)
  {
		wakeCheck = false; 
		sei(); //make sure interrupts are on!
  		sleep_mode();  //sleep now
  }
  else  //ERROR
  {
	return; 
  }
  //----------------------------- ZZZZZZ sleeping here----------------------
  sleep_disable(); //disable sleep, awake now

  
  if(extInt0_ == true)
  {
  	detachInterrupt(0);
	extInt0_ = false; 
  }
  else if(extInt1_ == true)
  {
	detachInterrupt(1);
	extInt1_ = false; 
  }

   


}  

void sleepHandler(void)
{
	
	
}

ISR(WDT_vect) 
{ 
 	wdt_reset();
}

