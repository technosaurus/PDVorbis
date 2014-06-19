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
	value = AFMT_S16_LE ,
	pcm = open("/dev/dsp", O_WRONLY);
	if (pcm < 0)
		write2("cannot get fd\n");
	if (ioctl(pcm, SNDCTL_DSP_SETFMT, &value) < 0)
		write2("cannot set audio format: %s\n");

while (--argc) {
    short *decoded;
    int channels, len, sample_rate;
    len = stb_vorbis_decode_filename(argv[argc], &channels, &sample_rate, &decoded);
    len *= channels;
    if (ioctl(pcm, SNDCTL_DSP_CHANNELS, &channels) < 0)
		write2("cannot set channels");
    if (ioctl(pcm, SNDCTL_DSP_SPEED, &sample_rate) < 0)
		write2("cannot set sample rate");
	while (len>0){
		int out=write(pcm,decoded,OUTSIZE);
		decoded+=out>>1;
		len -= out;
	}
}
close(pcm);
return 0;
}
