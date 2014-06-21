//gcc -Os -finline-small-functions oggplay.c -ffunction-sections -fdata-sections -fmerge-all-constants -Wl,--gc-sections,-s -o oggplay -lm
#define STB_VORBIS_NO_PUSHDATA_API
#define STB_VORBIS_NO_INLINE_DECODE

#include "stb_vorbis.c"
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/soundcard.h>
#define OUTSIZE 4096
static inline void write2(char *msg){
	write(2,msg,strlen(msg));
}

int main(int argc, char **argv){
	int error,
	value = AFMT_S16_LE,
	channels = 2,
	pcm = open("/dev/dsp", O_WRONLY);
	if (pcm < 0)
		write2("cannot get fd\n");
	if (ioctl(pcm, SNDCTL_DSP_SETFMT, &value) < 0)
		write2("cannot set audio format: %s\n");
	if (ioctl(pcm, SNDCTL_DSP_CHANNELS, &channels) < 0)
				write2("cannot set channels\n");
while (--argc) {
    short sbuffer[OUTSIZE];
    int sample_rate=0, n, error;
 
    stb_vorbis *v = stb_vorbis_open_filename(argv[argc], &error, NULL);
    if (!v) { 
		write2("Couldn't open "); write2(argv[argc]); write2("\n");
	}
	while (0 != (n=stb_vorbis_get_frame_short_interleaved(v, channels, sbuffer, OUTSIZE))){
		if (sample_rate!=v->sample_rate){
			sample_rate=v->sample_rate;
			if (ioctl(pcm, SNDCTL_DSP_SPEED, &sample_rate) < 0)
				write2("cannot set sample rate");
		}
		(void) write(pcm,sbuffer,n*sizeof(short)*channels);
	}
	stb_vorbis_close(v);
}
close(pcm);
return 0;
}
