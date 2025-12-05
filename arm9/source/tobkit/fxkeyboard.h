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

#ifndef FXKEYBOARD_H
#define FXKEYBOARD_H

#include "tobkit/widget.h"
#include "fxbutton.h"
#include "tobkit/button.h"
#include "tobkit/digitbox.h"
#include "tobkit/label.h"
#include "tobkit/gui.h"
#include "tobkit/button.h"

#define FXKEYBOARD_WIDTH			13 * 16 + 16 // extra space to occlude the piano
#define FXKEYBOARD_HEIGHT			31 		+ 9

#define FXKEYBOARD_LMARGIN			2
#define FXKEYBOARD_YMARGIN			12

#define NUM_FXKEYS					15

namespace tobkit {

	
class FXKeyboard: public Widget {
	public:
		FXKeyboard(u8 _x, u8 _y, u16 **_vram, void (*onFxKeypress)(u8 pressedValue, bool disabled), void (*_onParamChange)(u8 val), void (*_onParamSet)(void), void (*_onFxClear)(void), bool _visible=true);
	
		~FXKeyboard();

		
		// Drawing request
		void pleaseDraw(void);
		// Event calls
		void penDown(u8 x, u8 y);
		void penUp(u8 x, u8 y);
		void penMove(u8 x, u8 y);
		void buttonPress(u16 button);
		
		void setCaption(const char *caption);
		void setCategory(u8 newcat);
		u8 getCategory(void) { return category; } // todo Not in the header file ..
		void setTheme(Theme *theme_, u16 bgcolor_);

		u8 getParam(void);
		u8 getLastCmd(void) { return last_cmd; }
		// void reveal(void);
		// void show(void);
		void hide(void);
		void setCaptionFor(u8 val) { 
			last_cmd = val; // TODO HACKY
			if (category == FX_CATEGORY_NORMAL)
				setCaption(captions[val & 0x0F]);
			else if (category == FX_CATEGORY_E)
				setCaption(E_captions[val & 0x0F]); // todo hacky remove this lol

		 } // todo move outside of header!
	private:
		FXButton *fx0, *fx1, *fx2, *fx3, *fx4, *fx5, *fx6, *fx7, *fx8, *fx9, *fxa, *fxb, *fxc, *fxd, *fxf;
		DigitBox *effectpar;
		Label *labeleffectpar;
		Button *buttonseteffectpar, *buttonmfx, *buttonmpar;
		std::vector<FXButton*> fxbuttons = { fx0, fx1, fx2, fx3, fx4, fx5, fx6, fx7, fx8, fx9, fxa, fxb, fxc, fxd, fxf };
		std::vector<const char*> fxlabels = { "00G+", "11H-", "22KD", "33LL", "44PM", "55RP", "66TR", "77XS", "88 U", "99 V", "aa  ", "bb  ", "cc  ", "dd  ", "fe  ",};
		// the fx command each key will input per category
		// todo this probably needs changing(?)
		std::vector<const char*> values = { "\x00\xE0\xff\xff", "\x01\xE1\xff\xff", "\x02\xE2\xff\xff", "\x03\xE3\xff\xff",
											"\x04\xE4\xff\xff", "\x05\xE5\xff\xff", "\x06\xE6\xff\xff", "\x07\xE7\xff\xff",
											"\x08\xE8\xff\xff", "\x09\xE9\xff\xff", "\x0a\xEA\xff\xff", "\x0b\xEB\xff\xff",
											"\x0c\xEC\xff\xff", "\x0d\xED\xff\xff", "\x0f\xEE\xff\xff" }; // todo MAKE LESS MESSY BEFORE PR!!
		const char *captions[16] = { "0XY: ARPEGGIO", "1XX: PORTAMENTO UP", "2XX: PORTAMENTO DOWN",
									 "3XX: PORTAMENTO TO NOTE", "4XY: VIBRATO", "5XY: PORTAMENTO TO NOTE \x60 VOLUME SLIDE",
									 "6XY: VIBRATO WITH VOLUME SLIDE", "7XY: TREMOLO", "8XY: SET NOTE PANNING POSITION", 
									 "9XX: SAMPLE OFFSET", "AXY: VOLUME SLIDE", "BXX: JUMP TO ORDER", "CXX: SET NOTE VOLUME", "DXX: PATTERN BREAK", "UNUSED", "FXX: SET SONG SPEED \x60 BPM"}; // 0x60 because GLYPH_3X5 subtracts 55 for ascii. this is shit and fix it before pr lol
		const char *E_captions[15] = {"E0X: AMIGA LED FILTER TOGGLE", "E1X: FINE PORTAMENTO UP", 
									  "E2X: FINE PORTAMENTO DOWN", "E3X: GLISSANDO CONTROL",
									  "E4X: VIBRATO CONTROL", "E5X: SET NOTE FINETUNE", 
									  "E6X: PATTERN LOOP", "E7X: TREMOLO CONTROL", 
									  "E8X: SET NOTE PANNING POSITION", "E9X: RETRIGGER NOTE",
									  "EAX: FINE VOLUME SLIDE UP", "EBX: FINE VOLUME SLIDE DOWN",
									  "ECX: NOTE CUT", "EDX: NOTE DELAY", "EEX: PATTERN DELAY", /*"EFX: FUNK IT"*/ };
		void (*onFxKeypress)(u8 val, bool disabled);
		void (*onParamChange)(u8 val);
		void (*onParamSet)(void);
		void (*onFxClear)(void);
		void draw(void);
		char *caption;
		GUI gui;

		inline void drawChar(u8 c, u8 cx, u8 cy, u16 col)
		{
			u8 i,j;
			for(j=0;j<5;++j) {
				for(i=0;i<3;++i) {
					u16 pixelidx = 3*GLYPH_3X5_COUNT*j+3*c+i;
					if(font_3x5_raw[pixelidx/8]&BIT(pixelidx%8)) {
						//*(*vram+SCREEN_WIDTH*(2+cy*8+j)+1+cx*4+i) = col;
						*(*vram+SCREEN_WIDTH*(y+cy+j)+x+cx+i) = col;
					}
				}
			}
		}

		inline void drawSmallString(const char *message, u8 sx, u8 sy, u16 col)
		{
			size_t n_chars = strlen(message);
			for (int c = 0; c < n_chars; ++c)
			{
				char _c = message[c];
				if (_c == ' ') continue;

				drawChar(GLYPH_3X5(_c), sx + c * (GLYPH_3X5_W(_c)), sy, col);
			}
		}

		u8 category = 0;
		u8 last_cmd = 0;
};

};

#endif
