/*====================================================================
Copyright 2006 Tobias Weyand

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    https://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
======================================================================*/

#include <stdlib.h>
#include <stdio.h>

#include "tobkit/digitbox.h"

using namespace tobkit;

/* ===================== PUBLIC ===================== */

DigitBox::DigitBox(u8 _x, u8 _y, u8 _width, u8 _height, uint16 **_vram, u8 _value, u8 _min, u8 _max, u8 _digits)
	:Widget(_x, _y, _width, _height, _vram),
	value(_value), min(_min), max(_max), digits(_digits), btnstate(0)
{
	onChange = 0;
}	

// Drawing request
void DigitBox::pleaseDraw(void) {
	draw();
}

// Event calls
void DigitBox::penDown(u8 px, u8 py) {
	
	u8 oldvalue = value;
	
	if((px>x)&&(px<x+width/2)&&(py>y)&&(py<y+9)) {
		btnstate = 1;
		if(value<max) value+=0x10;
	} else if((px>x)&&(px<x+width/2)&&(py>y+9)&&(py<y+18)) {
		btnstate = 2;
		if(value>min) value-=0x10;
	} else if((px>x)&&(px>x+width/2)&&(py>y)&&(py<y+9)) {
		btnstate = 3;
		if(value<max) value++;
	} else if((px>x)&&(px>x+width/2)&&(py>y+9)&&(py<y+18)) {
		btnstate = 4;
		if(value>min) value--;
	}
	
	if(value!=oldvalue) {
		onChange(value);
		draw();
	}
}

void DigitBox::penUp(u8 px, u8 py) {
	
	btnstate = 0;
	draw();
}

void DigitBox::setValue(u8 val)
{
	s32 oldval = value;
	
	if(val > max)
		value = max;
	else if (val < min)
		value = min;
	else
		value = val;

	if(oldval != value)
	{
		if(onChange!=0)
			onChange(val);
		if(isExposed())
			draw();
	}
}

u8 DigitBox::getValue(void)
{
	return value;
}

// Callback registration
void DigitBox::registerChangeCallback(void (*onChange_)(u8)) {
	onChange = onChange_;
}

/* ===================== PRIVATE ===================== */

void DigitBox::draw(void)
{
	// Number display
	drawFullBox(9, 1, width-9, height-1, theme->col_lighter_bg);
	
	char numberstr[5];
	char formatstr[] = "%02x";
	// Set no of digits (hacky, but there's no other way)
	// formatstr[1] = digits+48;
	
	snprintf(numberstr, sizeof(numberstr), formatstr, value);
	drawString(numberstr, 11, 5, theme->col_text_value);

	// Probably quite dumb but avoids code duplication lol
	for (int k = 0; k < 2; ++k)
	{
		u8 offset = k * (width - 9);
		// Upper Button
		if(btnstate==1 + 2 * k) {
			drawGradient(theme->col_dark_ctrl, theme->col_light_ctrl, 1+offset, 1, 8, 8);
		} else {
			drawGradient(theme->col_light_ctrl, theme->col_dark_ctrl, 1+offset, 1, 8, 8);
		}
		
		// This draws the up-arrow
		int_fast8_t i,j;
		for(j=0;j<3;j++) {
			for(i=-j;i<=j;++i) {
				drawPixel(4+i+offset, j+3, theme->col_text_bt);
			}
		}
		
		drawBox(0+offset, 0, 9, 9, theme->col_outline);
		
		// Lower Button
		if(btnstate==2 + 2 * k) {
			drawGradient(theme->col_dark_ctrl, theme->col_light_ctrl, 1+offset, 8, 8, 8);
		} else {
			drawGradient(theme->col_light_ctrl, theme->col_dark_ctrl, 1+offset, 8, 8, 8);
		}
		
		// This draws the down-arrow
		for(j=2;j>=0;j--) {
			for(i=-j;i<=j;++i) {
				drawPixel(4+i+offset, -j+13, theme->col_text_bt);
			}
		}
		
		drawBox(0+offset, 8, 9, 9, theme->col_outline);
	}
	
	
	
	// Border
	drawBorder(theme->col_outline);
	
}
