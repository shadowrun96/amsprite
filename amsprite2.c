#include <stdio.h>
#include <ncurses.h>
#define SPRITE_ROWS 16
#define SPRITE_COLS 16
int movepen(int* peny, int* penx, int newpeny, int newpenx, int *spritex, int *spritey, int spritepens[16][16]);

int paint(int *peny, int *penx, int spritepens[16][16], int *spritex, int *spritey,int pencolor);
int hexes(int canvas[16][16]);
int main() {
	initscr();
	noecho();
	curs_set(false);
	start_color();

	/* the array that holds the sprite pens */
	int spritepens[SPRITE_ROWS][SPRITE_COLS];
	
	/* penx, peny are the coords for the pen on the screen, while
	 * spritex, spritey are the internal coords of the pen, in the sprite array
	 */
	int penx, peny, spritex, spritey;
	penx = 0; peny = 0; spritex = 0; spritey = 0;
	int ch; /* get key */
	/* initialise colors */

       	init_pair(1, COLOR_YELLOW, COLOR_YELLOW);
        init_pair(2, COLOR_RED, COLOR_RED);
        init_pair(3, COLOR_CYAN, COLOR_CYAN);
        init_pair(4, COLOR_BLUE, COLOR_BLUE);
        init_pair(5, COLOR_WHITE, COLOR_BLACK);
	
	/* select blue on blue */
	attron(COLOR_PAIR(4));

	/* print a 16x16 square that will hold the sprite
	 * but on the X-axis, we print 32 spaces so its a perfect square 
	 * since the console cursor is a rectangle*/
	for (int r = 0; r < 16; r++) 
		mvprintw(r,0, "                                ");

	/* the internal representation of the sprite's XY pen colors */


	for (spritex = 0; spritex < 16; spritex++) {
		for (spritey = 0; spritey < 16;spritey++) {
			spritepens[spritex][spritey] = 4;
		}
	}
	spritex = 0; spritey = 0;

	/* print pen cursor at 0,0 */
	attron(COLOR_PAIR(1));
	mvprintw(0,0,"  ");
	/* keypresses */
	while ((ch = getch()) != 'q') 
	{
		switch(ch) {
		case 'l': /* right */
			movepen(&peny,&penx,peny,penx+2,&spritex, &spritey, spritepens);	// update external display x coord
			break;
		case 'h':
			movepen(&peny,&penx,peny,penx-2,&spritex, &spritey, spritepens);	// ditto
			break;	
		case 'k': /* up */
			movepen(&peny,&penx,peny-1,penx,&spritex, &spritey, spritepens);
			break;
		case 'j': /* down */
			movepen(&peny,&penx,peny+1,penx,&spritex, &spritey, spritepens);
			break;
		case '1': 
			paint(&peny, &penx, spritepens, &spritex, &spritey, 1);
			hexes(spritepens);
			break;
		case '2':
			paint(&peny,&penx, spritepens, &spritex, &spritey,  2);
			hexes(spritepens);
			break;
		case '3':
			paint(&peny,&penx, spritepens, &spritex, &spritey, 3);
			hexes(spritepens);
			break;
		case '4': 
			paint(&peny,&penx,spritepens, &spritex, &spritey, 4);
			hexes(spritepens);
			break;
		default:
		        break;	

		}

	}

	/* debug */
	refresh();
	endwin();
	/* debug */
}

int movepen(int *peny, int *penx, int newpeny, int newpenx, int *spritex, int *spritey, int spritepens[16][16]) 
{

	if (newpenx >= 0 && newpenx <= 31 && newpeny >= 0 && newpeny <= 15)
        	{
			
			/* move to new XY and print */	
			attron(COLOR_PAIR(1));
	                mvprintw(newpeny,newpenx,"  ");
			/* repaint previous position with stored pen*/
        	        int currcol=spritepens[*spritey][*spritex];
                	attron(COLOR_PAIR(currcol));
                	mvprintw(*peny,*penx,"  ");
			/* update screen pen and internal array pen coords */
			if (newpeny > *peny) 
			{ 
				*peny = newpeny;
                		*spritey +=1;
			} else if (newpeny < *peny) 
			{
				*peny = newpeny;
				*spritey -=1;
			}

			if (newpenx > *penx) 
			{
				*penx = newpenx;
				*spritex +=1;
			} else if (newpenx < *penx)
			{
				*penx = newpenx;
				*spritex -=1;
			}

			/* print status bar */
                	attron(COLOR_PAIR(5));
                	mvprintw(20,1,"                            ");
                	mvprintw(20,1,"peny,penx=%d,%d  ",*peny,*penx);
			mvprintw(21,1,"spritey,spritex=%d,%d  ", *spritey, *spritex);

       	}
}
int paint(int *peny, int *penx, int spritepens[16][16], int *spritex, int *spritey, int pencolor) {

	attron(COLOR_PAIR(pencolor));
	mvprintw(*peny,*penx,"  ");
	spritepens[*spritey][*spritex] = pencolor;
}
int hexes(int spritepens[16][16]) {

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
  
            pixel = spritepens[k][l];
            byte = byte | bitmasks[bit][pixel];

          if (bit ==  3)
                  {
	                s = s + 1;
                        attron(COLOR_PAIR(5));
		        sprite[s] = byte;
		        bit = 0; byte = 0; bytecount++;
		  }
		  else {
		        bit++;
		       }
		  }
		 }
	/* display sprite data */
       int printdbx = 34;
       int printdby = 0;
       for (int sx = 0; sx < 64; sx++) {
         mvprintw(printdby,printdbx,"&%x ",sprite[sx]);
         printdbx = printdbx + 4;
         if (printdbx == 50) { printdby = printdby + 1;printdbx = 34;}
       }

}


