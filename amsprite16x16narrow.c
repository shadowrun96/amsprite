/**
 * A primitive Amstrad sprite editor.
 * George Fountis (c) 2025
 * Generates hexadecimal values for assembler 'db' statements. 
*/


#include <stdio.h>
#include <ncurses.h>
int movepen(int* currenty, int* currentx, int newy, int newx, int* canvasx, int* canvasy, int canvas[16][16]);
int paint(int* currenty, int* currentx,  int canvas[16][16], int *canvasx, int *canvasy,int color);
int hexes(int canvas[16][16]);

int main() {

	initscr();
	noecho();
	curs_set(false);
	start_color();
	/* initialise colors that we will use */
	init_pair(1, COLOR_YELLOW, COLOR_YELLOW);
	init_pair(2, COLOR_RED, COLOR_RED);
	init_pair(3, COLOR_CYAN, COLOR_CYAN);
	init_pair(4, COLOR_BLUE, COLOR_BLUE);
	init_pair(5, COLOR_WHITE, COLOR_BLACK);

	/* select blue on blue */
	attron(COLOR_PAIR(4));

	mvprintw(0,0, "                \n");
	mvprintw(1,0, "                \n");
	mvprintw(2,0, "                \n");
	mvprintw(3,0, "                \n");
	mvprintw(4,0, "                \n");
	mvprintw(5,0, "                \n");
	mvprintw(6,0, "                \n");
	mvprintw(7,0, "                \n");
	mvprintw(8,0, "                \n");
	mvprintw(9,0, "                \n");
	mvprintw(10,0,"                \n");
	mvprintw(11,0,"                \n");
	mvprintw(12,0,"                \n");
	mvprintw(13,0,"                \n");
	mvprintw(14,0,"                \n");
	mvprintw(15,0,"                \n");
	
	int canvas[16][16] = { 
                               {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
                               {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
                               {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
                               {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
                               {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
                               {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
                               {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
                               {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
                               {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
                               {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
                               {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
                               {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
                               {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
                               {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
                               {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
                               {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4}
                             };

	int x,y,currcol;
	x = 0; y = 0;
	int canvasx = 0; int canvasy = 0;
	int ch;
	/* status bar */
	attron(COLOR_PAIR(1));
	mvprintw(y,x," ");
	
	attron(COLOR_PAIR(5));
	mvprintw(19,1,"use vim keys (h/j/k/l) for navigation, 'q' to quit.\n");
	mvprintw(20,1,"                                                                         ");
	mvprintw(20,1,"y,x=%d,%d",y,x);	

	attron(COLOR_PAIR(5));mvprintw(21,1,"1");attron(COLOR_PAIR(1));mvprintw(21,2," ");
	attron(COLOR_PAIR(5));mvprintw(21,3,"2");attron(COLOR_PAIR(2));mvprintw(21,4," ");
	attron(COLOR_PAIR(5));mvprintw(21,5,"3");attron(COLOR_PAIR(3));mvprintw(21,6," ");
	attron(COLOR_PAIR(5));mvprintw(21,7,"4");attron(COLOR_PAIR(4));mvprintw(21,8," ");
	/* keypresses */
	while ((ch = getch()) != 'q') 
	{
		switch(ch) {
		case 'l': /* right */
			movepen(&y,&x,y,x+1,&canvasx, &canvasy,canvas);
			break;
		case 'h': /* left  */
			movepen(&y,&x,y,x-1,&canvasx,&canvasy,canvas);
			break;	
		case 'k': /* up */
			movepen(&y,&x,y-1,x,&canvasx,&canvasy,canvas);
			break;
		case 'j': /* down */
			movepen(&y,&x,y+1,x,&canvasx,&canvasy,canvas);
			break;
		case '1': 
			paint(&y, &x, canvas, &canvasx, &canvasy, 1);
			hexes(canvas);
			break;
		case '2':
			paint(&y,&x, canvas, &canvasx, &canvasy,  2);
			hexes(canvas);
			break;
		case '3':
			paint(&y,&x, canvas, &canvasx, &canvasy, 3);
			hexes(canvas);
			break;
		case '4': 
			paint(&y,&x,canvas, &canvasx, &canvasy, 4);
			hexes(canvas);
			break;

		default:
		        break;	
		}

	}
	refresh();
	endwin();
/**
	for (int i = 0; i < 16; i++) {
		for (int j=0; j < 16; j++) {
			printf("%d", canvas[i][j]);
		}
	printf("\n");
	}
*/
}

int movepen(int *currenty, int *currentx, int newy, int newx, int *canvasx, int* canvasy, int canvas[16][16]) 
{
	
	if (newx >= 0 && newx <= 15 && newy >= 0 && newy <= 15) 
	{

	/* print at new x and y */

		attron(COLOR_PAIR(1));
		mvprintw(newy,newx," ");

		int currcol=canvas[*currenty][*currentx];		
		
		attron(COLOR_PAIR(currcol));
		mvprintw(*currenty,*currentx," ");

		attron(COLOR_PAIR(5));

		*currenty = newy;
		*currentx = newx;

		attron(COLOR_PAIR(5));
		mvprintw(20,1,"                                                                         ");
		mvprintw(20,1,"y,x=%d,%d",*currenty,*currentx);	
	}
}	


/* setting the color to the array canvas works, repainting correctly the canvas fails. */

int paint(int* currenty, int* currentx,  int canvas[16][16], int* canvasx, int* canvasy, int color) 
{

	attron(COLOR_PAIR(color));
	mvprintw(*currenty, *currentx, " ");
	canvas[*currenty][*currentx] = color;
}


int hexes(int canvas[16][16]) 
{

	int bit = 0;
	int pixel = 0;
	int byte = 0x00;
	int bytecount = 0;
	int bitmasks[4][4];
	int sprite[64] = {0}; 
	int s = -1;
	bitmasks[0][1] = 0x80; //yellow
	bitmasks[0][2] = 0x88; //cyan 
	bitmasks[0][3] = 0x08; //red
	bitmasks[0][4] = 0x00; // blue

	bitmasks[1][1] = 0x40;
        bitmasks[1][2] = 0x44;
	bitmasks[1][3] = 0x4;
	bitmasks[1][4] = 0x00;

	bitmasks[2][1] = 0x20;
	bitmasks[2][2] = 0x22;
	bitmasks[2][3] = 0x2;
	bitmasks[2][4] = 0x00;

	bitmasks[3][1] = 0x10;
	bitmasks[3][2] = 0x11;
	bitmasks[3][3] = 0x1;
	bitmasks[3][4] = 0x00;
	for (int k = 0; k < 16; k++) 
	{
	  for (int l=0; l < 16; l++) 
	  {

	    pixel = canvas[k][l];
      	    byte = byte | bitmasks[bit][pixel];

	  if (bit ==  3) 
	    {
		s = s + 1;
		attron(COLOR_PAIR(5));
		//bytecount++;
		 sprite[s] = byte;
		  //printf("&%x, ",byte);bit = 0; byte=0;
		  bit = 0; byte = 0; bytecount++;

	    }
	   else {  
	            bit++;
	    }

	  }

   	 }

/* display sprite data */
	int printdbx = 18;
	int printdby = 0;

	for (int sx = 0; sx < 64; sx++) {

	  mvprintw(printdby,printdbx,"&%x ",sprite[sx]);
	  printdbx = printdbx + 4;

	  if (printdbx == 34) { printdby = printdby + 1;printdbx = 18;}
	 
	}


}
