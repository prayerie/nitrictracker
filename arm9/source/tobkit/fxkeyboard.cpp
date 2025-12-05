/*====================================================================
Copyright 2025 R Ferreira

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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "fxkeyboard.h"

using namespace tobkit;

/* ===================== PUBLIC ===================== */


FXKeyboard::FXKeyboard(u8 _x, u8 _y, uint16 **_vram, void (*_onFxKeypress)(u8 pressedValue, bool disabled), void (*_onParamChange)(u8 val), void (*_onParamSet)(void), void (*_onFxClear)(void), bool _visible)
	:Widget(_x, _y, FXKEYBOARD_WIDTH, FXKEYBOARD_HEIGHT, _vram, _visible),
	  caption(0), onFxKeypress(_onFxKeypress), onParamChange(_onParamChange), onParamSet(_onParamSet), onFxClear(_onFxClear)
{
	for (int i = 0; i < NUM_FXKEYS; ++i)
	{
		fxbuttons.at(i) = new FXButton(x + FXKEYBOARD_LMARGIN + ((FXBUTTON_WIDTH - 1) * i), y + FXKEYBOARD_YMARGIN, _vram, true);
		fxbuttons.at(i)->setCaption(fxlabels.at(i));
		fxbuttons.at(i)->setSmallCaption((i == 0 || (i <= 7 && i >= 5) || i == 0xa) ? "XY" : "XX");
		fxbuttons.at(i)->registerPushCallback(onFxKeypress);
		gui.registerWidget(fxbuttons.at(i));
	}

	labeleffectpar = new Label(186, 153, 38, 10, _vram, false, true);
	labeleffectpar->setCaption("param");
	gui.registerWidget(labeleffectpar);

	effectpar	= new DigitBox(186, 164, 35, 17, _vram, 0, 0, 255, 2);
	effectpar->registerChangeCallback(onParamChange);
	gui.registerWidget(effectpar);

	buttonseteffectpar = new Button(186, 180, 35, 10, _vram);
	buttonseteffectpar->setCaption("set");
	buttonseteffectpar->registerPushCallback(onParamSet);

	buttonmfx = new Button(2, y + 1, 22, 10, _vram);
	buttonmfx->setCaption("clr");
	buttonmfx->registerPushCallback(onFxClear);

	// buttonmpar = new Button(22, y + 2, 15, 10, vram);
	// buttonmpar->setCaption("-p");
	// buttonmpar->registerPushCallback(onParamSet);

	gui.registerWidget(buttonseteffectpar);
	gui.registerWidget(buttonmfx);
	//gui.registerWidget(buttonmpar);

	setCategory(0);
}

FXKeyboard::~FXKeyboard()
{
	if (caption) ntxm_free(caption);

	for (int i = 0; i < NUM_FXKEYS; ++i)
	{
		delete fxbuttons.at(i);
	}

	delete labeleffectpar;
	delete effectpar;
	delete buttonseteffectpar;
	delete buttonmfx;
	//delete buttonmpar;
}

void FXKeyboard::hide(void)
{
	Widget::hide();
	drawFullBox(0, 0, width, height, 0x0000); // show the piano
}
// Drawing request
void FXKeyboard::pleaseDraw(void) {
	draw();
}
		
// Event calls
void FXKeyboard::penDown(u8 x, u8 y)
{
	gui.penDown(x, y);
}

void FXKeyboard::penUp(u8 x, u8 y)
{
	gui.penUp(x, y);
}

void FXKeyboard::penMove(u8 x, u8 y) {
	gui.penMove(x, y);
}

void FXKeyboard::buttonPress(u16 button) {
	gui.buttonPress(button);
}

u8 FXKeyboard::getParam(void)
{
	return effectpar->getValue();
}

void FXKeyboard::setCategory(u8 newcat) {
	category = newcat;
	
	for (int i=0; i<NUM_FXKEYS; ++i)
	{
		FXButton *bt = fxbuttons.at(i);
		if (bt==0) continue;
		bt->setCategory(newcat);
		bt->setValue(values.at(i)[newcat]);

		if (newcat == FX_CATEGORY_FT /* && i > 7 */)
			bt->disable(); 
		else if (newcat == FX_CATEGORY_VOL /* && i > 9 */)
			bt->disable();
		else if (newcat == FX_CATEGORY_E && (i == 0 || (i > 6 && i < 0xC)))
		{
			bt->disable();
		}
		else
			bt->enable();
	}

	switch (newcat)
	{
		case FX_CATEGORY_NORMAL:
		setCaption("EFFECT COMMANDS");
		effectpar->setSingleDigit(false);
		break;

		case FX_CATEGORY_E:
		//setCaption("Exy: extended commands");
		setCaption("EXY: EXTENDED COMMANDS");
		effectpar->setSingleDigit(true);
		break;

		case FX_CATEGORY_FT:
		//setCaption("Xxy: sdfoghdfjghlshjdf");
		setCaption("DISABLED");
		effectpar->setSingleDigit(false);
		break;

		case FX_CATEGORY_VOL:
		//setCaption("volume commands");
		setCaption("DISABLED");
		effectpar->setSingleDigit(false);
		break;
	}
}


void FXKeyboard::setTheme(Theme *theme_, u16 bgcolor_)
{
	theme = theme_;
	bgcolor=bgcolor_;
	gui.setTheme(theme, theme->col_light_bg);
}

void FXKeyboard::setCaption(const char *_caption) {
	if (caption) ntxm_free(caption);
	caption = (char*)ntxm_cmalloc(strlen(_caption)+1);
	strcpy(caption, _caption);
	draw();
}

/* ===================== PRIVATE ===================== */

void FXKeyboard::draw(void) {
	if(!isExposed()) return;

	drawFullBox(0, 0, width, height, theme->col_bg); // hide the piano

	drawSmallString(caption, 5 + (FXKEYBOARD_WIDTH-20)/2 - (4 * strlen(caption)) / 2 - 6 /*todo: BAD!*/, 4, theme->col_text_light);
	gui.revealAll();
	gui.draw();
}
