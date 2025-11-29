/*
 * NitroTracker - An FT2-style tracker for the Nintendo DS
 *
 *                                by Tobias Weyand (0xtob)
 *
 * http://nitrotracker.tobw.net
 * http://code.google.com/p/nitrotracker
 */

/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "lowpassbox.h"

#include <nds.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "ntxm/instrument.h"
#include "ntxm/fifocommand.h"

using namespace tobkit;

/* ===================== PUBLIC ===================== */

// Constructor sets base variables
LowpassBox::LowpassBox(u16 **_vram, void (*_onOk)(void), void (*_onCancel)(void))
	:Widget((SCREEN_WIDTH-NORMALIZEBOX_WIDTH)/2, (SCREEN_HEIGHT-NORMALIZEBOX_HEIGHT)/2,
		NORMALIZEBOX_WIDTH, NORMALIZEBOX_HEIGHT, _vram),
	onOk(_onOk), onCancel(_onCancel)
{
	title = "lowpass filter";
	
	nspercent = new NumberSlider(x+(NORMALIZEBOX_WIDTH-64)/2, y+20, 64, 17, _vram, 12000, 50, 20000);
	
	labelpercent = new Label(x+(NORMALIZEBOX_WIDTH-32)/2 + 64, y+25, 25, 12, _vram, false);
	labelpercent->setCaption("Hz");
	
	buttonok = new Button(x+(NORMALIZEBOX_WIDTH-50)/2 - 27, y+40, 50, 14, _vram);
	buttonok->setCaption("ok");
	buttonok->registerPushCallback(_onOk);
	
	buttoncancel = new Button(x+(NORMALIZEBOX_WIDTH-50)/2 + 27, y+40, 50, 14, _vram);
	buttoncancel->setCaption("cancel");
	buttoncancel->registerPushCallback(_onCancel);
	
	gui.registerWidget(nspercent, 0);
	gui.registerWidget(labelpercent, 0);
	gui.registerWidget(buttonok, 0);
	gui.registerWidget(buttoncancel, 0);
}

LowpassBox::~LowpassBox(void)
{
	delete buttonok;
	delete buttoncancel;
}

// Drawing request
void LowpassBox::pleaseDraw(void)
{
	draw();
}

// Event calls
void LowpassBox::penDown(u8 px, u8 py) {
	gui.penDown(px, py);
}

void LowpassBox::penUp(u8 px, u8 py) {
	gui.penUp(px, py);
}

void LowpassBox::penMove(u8 px, u8 py) {
	gui.penMove(px, py);
}

s16 LowpassBox::getValue(void)
{
	return nspercent->getValue();
}

void LowpassBox::show(void)
{
	gui.showAll();
	Widget::show();
}

void LowpassBox::reveal(void)
{
	Widget::reveal();
	gui.revealAll();
}

void LowpassBox::setTheme(Theme *theme_, u16 bgcolor_)
{
	theme = theme_;
	bgcolor=bgcolor_;
	gui.setTheme(theme, theme->col_light_bg);
}

/* ===================== PRIVATE ===================== */

void LowpassBox::draw(void)
{
	drawGradient(theme->col_list_highlight1, theme->col_list_highlight2, 1, 1, width - 2, 15);
	drawHLine(1, 16, width - 2, theme->col_outline);
	drawFullBox(1, 17, width - 2, NORMALIZEBOX_HEIGHT-17, theme->col_light_bg);
	drawBorder(theme->col_outline);
	
	u8 titlewidth = getStringWidth(title)+5;
	drawString(title, (NORMALIZEBOX_WIDTH-titlewidth)/2, 2, theme->col_text, titlewidth+5);
	
	gui.draw();
}
