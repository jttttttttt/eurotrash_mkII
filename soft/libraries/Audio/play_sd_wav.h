/* Audio Library for Teensy 3.X
 * Copyright (c) 2014, Paul Stoffregen, paul@pjrc.com
 *
 * Development of this audio library was funded by PJRC.COM, LLC by sales of
 * Teensy and Audio Adaptor boards.  Please support PJRC's efforts to develop
 * open source software by purchasing Teensy or other PJRC products.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice, development funding notice, and this permission
 * notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef play_sd_wav_h_
#define play_sd_wav_h_

#include "AudioStream.h"
#include "SD.h"

// misc functions added
 
class AudioPlaySdWav : public AudioStream
{
public:
	AudioPlaySdWav(void) : AudioStream(0, NULL) { begin(); }
	void begin(void);
	bool open_and_parse(const char *filename);
	bool seek(uint32_t pos);
	void stop(void);
	void pause(void);
	void close(void);
	bool isPlaying(void);
	uint32_t positionMillis(void);
	uint32_t positionBytes(void);
	uint32_t lengthMillis(void);
	uint32_t lengthBytes(void);
	virtual void update(void);
private:
	File wavfile;
	bool consume(uint32_t size);
	bool parse_format(void);
	uint32_t header[6];		// temporary storage of wav header data
	uint32_t data_length;		// number of bytes remaining in current section
	uint32_t total_length;		// number of audio data bytes in file
	uint32_t bytes2millis;
	audio_block_t *block_left;
	audio_block_t *block_right;
	uint16_t block_offset;			// how much data is in block_left & block_right
	uint8_t buffer[512];			// buffer one block of data
	uint8_t pre_buffer[512];		// buffer one block of data for prefetch
	uint8_t pre_buffer_status;      // empty, header, or data
	uint16_t buffer_offset;			// where we're at consuming "buffer"
	uint16_t buffer_length;			// how much data is in "buffer" (512 until last read)
	uint8_t header_offset;			// number of bytes in header[]
	uint8_t state;
	uint8_t state_play;
	uint8_t state_parse;
	uint8_t wav_format;
	uint8_t leftover_bytes;
	uint32_t byte_offset;
	uint32_t prev_byte_offset;
};

#endif
