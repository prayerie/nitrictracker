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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "fxkeyboard.h"

using namespace tobkit;

/* ===================== PUBLIC ===================== */

FXKeyboard::FXKeyboard(u8 _x, u8 _y, uint16 **_vram, bool _visible)
	:Widget(_x, _y, FXKEYBOARD_WIDTH, FXKEYBOARD_HEIGHT, _vram, _visible),
	  caption(0)
{
	for (int i = 0; i < NUM_FXKEYS; ++i)
	{
		fxbuttons.at(i) = new FXButton(x + FXKEYBOARD_LMARGIN + (FXBUTTON_WIDTH * i), y + FXKEYBOARD_YMARGIN, _vram, true);
		fxbuttons.at(i)->setCaption(fxlabels.at(i));
		fxbuttons.at(i)->setSmallCaption("X");
		gui.registerWidget(fxbuttons.at(i));
	}

	setCategory(0);
}

FXKeyboard::~FXKeyboard()
{
	if (caption) ntxm_free(caption);

	for (int i = 0; i < NUM_FXKEYS; ++i)
	{
		delete fxbuttons.at(i);
	}
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



void FXKeyboard::setCategory(u8 newcat) {
	for (int i=0; i<NUM_FXKEYS; ++i)
	{
		FXButton *bt = fxbuttons.at(i);
		if (bt==0) continue;
		bt->setCategory(newcat);

		if (newcat == FX_CATEGORY_FT && i > 7)
			bt->disable();
		else if (newcat == FX_CATEGORY_VOL && i > 9)
			bt->disable();
		else
			bt->enable();
	}

	switch (newcat)
	{
		case FX_CATEGORY_NORMAL:
		setCaption("9xx: test caption hi :D");
		break;

		case FX_CATEGORY_E:
		setCaption("Exy: extended commands");
		break;

		case FX_CATEGORY_FT:
		setCaption("Xxy: sdfoghdfjghlshjdf");
		break;

		case FX_CATEGORY_VOL:
		setCaption("volume commands");
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

	drawString(caption, (FXKEYBOARD_WIDTH-20)/2 - getStringWidth(caption)/2, 2, theme->col_text_light, getStringWidth(caption));
	gui.revealAll();
	gui.draw();
}
