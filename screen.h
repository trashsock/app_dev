#define ESC 0X1B
#define UNICODE		//for conditional compilation
#define BAR "\u2590"

enum FG_COL{BLACK = 30, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE};
#define bg(c) (c+10)		//marker definition (converting fg val to bg val)

#define DEBUG		//for conditional compilation

typedef struct
{ 
	int row;
	int col;
}Position;


void clrscr();
void set_fg_colour(int);
void set_bg_colour(int);
void set_fg_bg_colours(int, int);
void reset_colours();
void gotoXY(int, int);
void draw_bar(int, int);
void draw_rect(int, int, int, int);
Position get_screen_size(void);
