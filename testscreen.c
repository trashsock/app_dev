#include <stdio.h>
#include <unistd.h>
#include "screen.h"
#include "comm.h"

int main()
{
	Position cur = get_screen_size();
	char postdata[100];
	sprintf(postdata, "row=%d&col=%d&id=e1900278", cur.row, cur.col);
	sendpost(URL, postdata); 
	gotoXY(1, 1);
	printf("Screen size: row = %d, col = %d\n", cur.row, cur.col);
	printf("Today we will make some animation. Press any key to continue\n");
	getchar();
	getchar();
	int fore, back;
	float step = (float)cur.col/cur.row;
	for(int i = 1; i < 51; i++)
	{
		fore = (i+1)%8+BLACK;
		back = (i+2)%8+BLACK; 
		set_fg_bg_colours(fore, bg(back)); 
		//set_bg_colour(BLACK);
		clrscr();
		draw_rect(10, 10, 5, 30);
		gotoXY(cur.row-i, (i-1)*step+1);
		printf("HELLO\n");
		usleep(250000);	//sleep(1);
	}
	getchar();
	reset_colours();
	clrscr();
	printf("Colour is set back to default\n");
	getchar();
/*
	clrscr();
	set_fg_colour(CYAN);
	gotoXY(14, 35);
	printf("Hello world!\n");
	getchar();
	draw_bar(30, 30);
	draw_bar(50, 30);
	getchar();
	reset_colours();
	printf("This text is displayed in default colour\n");
*/
}
