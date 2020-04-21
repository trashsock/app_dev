#include <stdio.h>
#include "sound.h"
#include <math.h>
#include "screen.h"

WAVheader readwavhdr(FILE *fp)
{
	WAVheader myh;
	fread(&myh, sizeof(myh), 1, fp);
	return myh;
}

void displayWAVhdr(WAVheader h)
{
	//printf("Chunk ID: ");
	gotoXY(1, 1);
/*	for(int i = 0; i < 4; i++)
		printf("%c", h.chunkID[i]);
	printf("\n"); */
	//printf("Chunk size: %d\n", h.chunkSize);
	//printf("Number of channels: %d\n", h.numChannels);
	set_fg_colour(CYAN);
	printf("Sample rate: %d\n", h.sampleRate);
	//printf("Block align: %d\n", h.blockAlign);
	//printf("Bits per sample: %d\n", h.bitsPerSample);
	double duration;
	duration = (double) h.subchunk2Size/h.byteRate;
	gotoXY(1, 70);
	set_fg_colour(MAGENTA);
	printf("Duration: %.3f seconds\n", duration);
}

void WAVdata(WAVheader h, FILE *fp)
{
	short samples[SIZE];
	int i, k;
	int count = 0, flag = 0;

	for(i = 0; i < BARS; ++i)
	{
		fread(samples, sizeof(samples), 1, fp);
		double sum = 0.0;
		for(k = 0; k < SIZE; k++)
		{
			sum = sum + samples[k]*samples[k];
		}
		//double dB = sqrt(sum/2000);
		double dB = 20*log10(sqrt(sum/SIZE));


#ifdef SDEBUG
		printf("dB[%d] = %f\n", i, dB);
#else
		if(dB > 70.00)
        {
            set_fg_colour(RED);
			if(flag == 0)
			{
				++count;
				flag = 0;
			}
        }
        else
		{
            reset_colours();
			if(flag == 1)
				flag = 0;
		}
		draw_bar(i+1, (int)dB/3);
#endif
	}
	reset_colours();
	gotoXY(1, 140);
	set_fg_colour(YELLOW);
	printf("Number of peaks: %d\n", count);
	reset_colours();
}
