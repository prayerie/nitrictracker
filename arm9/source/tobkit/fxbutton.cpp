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

#include "fxbutton.h"

using namespace tobkit;

/* ===================== PUBLIC ===================== */

FXButton::FXButton(u8 _x, u8 _y, uint16 **_vram, bool _visible, u8 _value)
	:Widget(_x, _y, FXBUTTON_WIDTH, FXBUTTON_HEIGHT, _vram, _visible),
	 penIsDown(false), caption(0), small_caption(0), category(0), value(_value)
{
	onPush = 0;
}

FXButton::~FXButton()
{
	if (caption) ntxm_free(caption);
	if (small_caption) ntxm_free(small_caption);
}

void FXButton::registerPushCallback(void (*onPush_)(u8 val)) {
	onPush = onPush_;
}
		
// Drawing request
void FXButton::pleaseDraw(void) {
	draw(0);
}
		
// Event calls
void FXButton::penDown(u8 x, u8 y)
{
	if (!enabled) return;
	penIsDown = true;
	draw(1);
}

void FXButton::penUp(u8 x, u8 y)
{
	if (!enabled) return;
	penIsDown = false;
	draw(0);
	if(onPush) {
		onPush(value);
	}
}

void FXButton::penMove(u8 x, u8 y) {

}

void FXButton::buttonPress(u16 button) {
	if(onPush)
		onPush(value);
}

void FXButton::setCaption(const char *_caption) {
	if (caption) ntxm_free(caption);
	caption = (char*)ntxm_cmalloc(strlen(_caption)+1);
	strcpy(caption, _caption);
}

void FXButton::setSmallCaption(const char *_small_caption) {
	if (small_caption) ntxm_free(small_caption);
	small_caption = (char*)ntxm_cmalloc(strlen(_small_caption)+1);
	strcpy(small_caption, _small_caption);
}

void FXButton::setCategory(u8 newcat)
{
	category = newcat;
	draw(penIsDown);
}

void FXButton::setValue(u8 newval)
{
	value = newval;
}

/* ===================== PRIVATE ===================== */

void FXButton::draw(u8 down) {
	if (!caption || !isExposed()) return;

	if (enabled)
	{
		if (down)
			drawVerticalGradient(theme->col_piano_full_col1, theme->col_piano_full_col2, 1, 1, width - 2, height - 2);
		else
			drawVerticalGradient(theme->col_piano_full_col2, theme->col_piano_full_col1, 1, 1, width - 2, height - 2);
		drawBox(1, 1, width-2, height-2, theme->col_piano_full_col2);
		
	} else {
		drawVerticalGradient(theme->col_dark_ctrl_disabled, theme->col_light_ctrl_disabled, 1, 1, width - 2, height - 2);
		drawBox(1, 1, width-2, height-2, theme->col_dark_ctrl_disabled);
	}

	drawBorder(theme->col_outline);

	// if (category == FX_CATEGORY_E)
	// {
	// 	const char label[3] = { 'E', caption[category], '\0' };
	// 	drawString(label, (width-getStringWidth(label))/2, height/2-7, theme->col_text_bt);
	// } else {
		
	// }

	const char label[2] = { caption[category], '\0' };
	drawString(label, (width-getStringWidth(label))/2, height/2-7, theme->col_text_bt);
	
	drawChar(GLYPH_3X5('X'), 3, 16, theme->col_pv_notes);
	drawChar(GLYPH_3X5('Y'), 7, 16, theme->col_pv_effect);
}
