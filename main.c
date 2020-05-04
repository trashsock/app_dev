#include <stdio.h>
#include <unistd.h>
#include "screen.h"
#include "comm.h"
#include "sound.h"

int main()
{
	//int peakval;
	//double maxdb;
	Position p = get_screen_size();		//displays screen size
	char postdata[100];
	//sprintf(postdata, "Peaks=%d&Max_dB=%d", peaks, db_val);
	//sendpost(URL, postdata);
	if(p.col < BARS)
		printf("Screen size isn't wide enough to display %d bars", BARS);
	clrscr();
	//can use wget command to fetch WAV file from a URL
	FILE *fp = fopen("test.wav", "r");
	WAVheader h = readwavhdr(fp);
	displayWAVhdr(h);
	getchar();
	WAVdata(h, fp);
	fclose(fp);
	sprintf(postdata, "Peaks=%d&Max_dB=%lf", peaks, db_val);
    sendpost(URL, postdata);

	return 0;
}
