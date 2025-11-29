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

#ifndef _RENDERBOX_H_
#define _RENDERBOX_H_

#include "tobkit/widget.h"
#include "tobkit/button.h"
#include "tobkit/label.h"

#include "ntxm/song.h"

namespace tobkit {

#define RENDERBOX_WIDTH			150
#define RENDERBOX_HEIGHT		64
#define RENDERBOX_SAMPLING_FREQ		22000
#define RENDERBOX_CROP_SAMPLES_END	500
#define RENDERBOX_CROP_SAMPLES_START	100

// Set the buffer size to be just enough to record samples for one frame. Then,
// we will retrigger the capture again.
#define CAPTURE_BUFFER_SIZE (((RENDERBOX_SAMPLING_FREQ) / 4) + 1) * 4



class RenderBox: public Widget {
	public:
		// Constructor sets base variables
		RenderBox(u16 **_vram, void (*_onOk)(void), void (*_onBufferSwap)(void), void (*_playSong)(void), void (*_onStart)(void), void (*_onCancel)(void), Sample *_sample, Instrument *_instrument,
			    u8 _smpidx, u32 render_ms, bool ptnn);
		~RenderBox(void);
		
		// Drawing request
		void pleaseDraw(void);
		// Event calls
		void penDown(u8 px, u8 py);
		void penUp(u8 px, u8 py);
		void buttonPress(u16 button);
		void buttonRelease(u16 button);
		bool recording, btndown, startbtndown, ptnbuttondown;
		void startRecording(void);
		void stopRecording(u32 *buf, u32 n_s);
		bool stop = false;
			u32 pos = 0;
	u16 buf_i = 0;
		u32 getRenderMs(void) { return render_ms; }
		Sample *getSample(void);
		void setTheme(Theme *theme_, u16 bgcolor_);
		// u32 buffer_right[CAPTURE_BUFFER_SIZE * 2];
		u32 buffer_left[CAPTURE_BUFFER_SIZE * 2];
	private:
		void draw(void);
		
		

		void (*onOk)(void);
		void (*onCancel)(void);
		void (*playSong)(void);
		void (*onBufferSwap)(void);
		
		const char *title;
		Label *labelmsg, *labelmsg2, *labelrec;
		Button *buttonstart, *buttoncancel, *buttonpattern;
		Sample *sample;
		Instrument *instrument;
		u8 smpidx;
		s16 *sound_data;
		u32 render_ms;
};

};

#endif
