/************************************************************************************
 * 	
 * 	Name    : Triggertrap TriggerTrap.h                         
 * 	Author  : Noah Shibley, NoMi Design                         
 * 	Date    : July 10th 2011                                    
 * 	Version : 0.1                                              
 * 	Notes   : Triggertrap Interface Class        
 * 
 * 			  Code for Triggertrap device (TTv1) and Triggertrap Shield (TT-K)                      
 * 
 * 	Copyright (c) 2011 NoMi Design All right reserved.
 * 
 * 	This file is part of Triggertrap. See Triggertrap.com for more information.
 * 
 * 		    Triggertrap is free software: you can redistribute it and/or modify
 * 		    it under the terms of the GNU General Public License as published by
 * 		    the Free Software Foundation, either version 3 of the License, or
 * 		    (at your option) any later version.
 * 
 * 		    Triggertrap is distributed in the hope that it will be useful,
 * 		    but WITHOUT ANY WARRANTY; without even the implied warranty of
 * 		    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * 		    GNU General Public License for more details.
 * 
 * 		    You should have received a copy of the GNU General Public License
 * 		    along with Triggertrap.  If not, see <http://www.gnu.org/licenses/>.
 * 
 ***********************************************************************************/

#ifndef TRIGGER_TRAP_H
#define TRIGGER_TRAP_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"    
#else
#include "WProgram.h"
#endif

#include "TTConfig.h"
#include "utility/TTUI.h"
#include "utility/trigger.h"
#include <utility/TTUI.h>
#include <utility/laser.h>
#include <utility/light.h>
#include <utility/trigger.h>
#include <utility/sound.h>
#include <utility/timeLapse.h>
#include <utility/flipflop.h>
#include <auxiliary.h>

	const int LASER_TRIG = 0;
	const int SOUND_TRIG = 1;
	const int LIGHT_TRIG = 2;
	const int TIMELAPSE_TRIG = 3; 
	const int AUX_TRIG= 4;
	const int FLIPFLOP_TRIG= 5;


class TriggerTrap {

public:

	
	TriggerTrap();
	void setup();
	void update();
	boolean trigger();
	int triggerMode();

private:

	//the UI object, and the sensor objects
	TTUI tui;
	Laser laser;
	Light light;
	Sound mic; 
	Aux aux;
	TimeLapse timeLapse;
	FlipFlop flipFlop;

};

#endif

