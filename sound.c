#include <stdio.h>
#include "sound.h"
#include <math.h>
#include "screen.h"
#include "comm.h"

WAVheader readwavhdr(FILE *fp)
{
	WAVheader myh;
	fread(&myh, sizeof(myh), 1, fp);
	return myh;
}

void displayWAVhdr(WAVheader h)
{
	gotoXY(1, 1);
	double duration;
	duration = (double) h.subchunk2Size/h.byteRate;		//calculates duration of .wav file
	printf("Duration: %.3f seconds\n", duration);		//max 3 decimal places
}

void WAVdata(WAVheader h, FILE *fp)
{
	short samples[SIZE];
	int i, k;
	int flag = 0, peaks = 0;
	double db_val = 0.0;
	char postdata[100];

	for(i = 0; i < BARS; ++i)
	{
		fread(samples, sizeof(samples), 1, fp);		//reads sample from file
		double sum = 0.0;
		for(k = 0; k < SIZE; k++)
		{
			sum = sum + samples[k]*samples[k];
		}
		
		double dB = 20*log10(sqrt(sum/SIZE));		//calculates decibel value
		
		if(dB > db_val)
			db_val = dB;


#ifdef SDEBUG
		printf("dB[%d] = %f\n", i, dB);
#else
		if(dB > 70.00)
        {
            set_fg_colour(RED);		//sets bar colour as red for decibel value over 70 dB
			if(flag == 0)
			{
				++peaks;
				flag = 0;
			}
        }
        else
		{
            reset_colours();
			if(flag == 1)
				flag = 0;
		}
		draw_bar(i+1, (int)dB/3);		//draws bars
#endif
	}
	reset_colours();
	gotoXY(1, 70);
	printf("Number of peaks: %d\n", peaks);
	gotoXY(1, 125);
	printf("Maximum decibel value: %.3f\n", db_val); 	//max 3 decimal places
	reset_colours();

	//sending information to sound.php (will be recorded in project.log)
	sprintf(postdata, "Peaks=%d&Max_dB=%lf", peaks, db_val);
    sendpost(URL, postdata);
}
