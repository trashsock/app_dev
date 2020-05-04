#include <stdio.h>
#include <unistd.h>
#include "screen.h"
#include "comm.h"
#include "sound.h"

int main()
{
	Position p = get_screen_size();		//displays screen size
	if(p.col < BARS)
		printf("Screen size isn't wide enough to display %d bars", BARS);
	clrscr();
		//can use wget command to fetch .WAV file from a URL
	FILE *fp = fopen("test.wav", "r");
	WAVheader h = readwavhdr(fp);
	displayWAVhdr(h);
	getchar();		//prompt
	WAVdata(h, fp);
	fclose(fp);

	return 0;
}
