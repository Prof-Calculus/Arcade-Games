#include <iostream.h>
#include <graphics.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <alloc.h>
#include <fstream.h>
#include <dos.h>
#include <iomanip.h>


const int  Breadth = 1*2,NumElements = 10;
int choice;

    struct datas
    {
	char name[23];
	    int score;
    }score_data;
void textgraph(char string1[15] ,char string2[15] ,int no);

void textgraph(char string1[15] ,char string2[15] ,int no)
{

   clearviewport();
   int length1,length2,height1,height2,i;
   length1=textwidth(string1);
   length2=textwidth(string2);
   height1=textheight(string1);
   height2=textheight(string2);
   settextstyle(0,0,0);
   i=0;
   if(no==1)
   {
      while(length1+100<getmaxy())
      {
	settextstyle(0,1,i);
	outtextxy(getmaxx()/2,(getmaxy()/2)-(length1/2),string1);
	delay(150);
	clearviewport();
	settextstyle(0,0,i);
	outtextxy((getmaxx()/2)-(length1/2),getmaxy()/2,string1);
	delay(150);
	clearviewport();
	 ++i;
	length1=textwidth(string1);
      }
    }
    if(no==2)
    {
      settextstyle(0,0,4);
      while(i<=getmaxx()-200)
      {
      clearviewport();
      outtextxy(getmaxx()-i-length1,(getmaxy()/2)-(height1),string1);
      outtextxy(+i,(getmaxy()/2)-(height2),string2);
      delay(150);
      i+=10;
      }

    }

}

class cubefield
{
	     public:
	     int x,y,mx,my,sizec,count,countlev,cubex,cubey,maxy;
	 int minx,miny,midx,score;
	     int cube_positions[NumElements][Breadth];
	     int cubes_in_a_line[3];
	     int initposn[NumElements][Breadth];
	     int pausetime, size;
	     int wait;
	     int maxwait;
	     int cubesize;
	     long int deviation;
	     int changecolor;              //changes color of trees
	     char num[10],level[10];        //for converting level & scores to string
	     char c;
    void intialise()
    {
		    maxwait=17;                            //apparent width of a one
		    minx=200;                            //top left of road
		miny=300;                           //top left of road
		    mx=getmaxx()-minx;                 //top right of road
		    my=miny+maxwait*NumElements;       //bottom point of road
		    cubesize=10;
		x=(mx-minx)/2+minx;               //initial x cordinate of cursor
		    y=miny+(maxwait*(NumElements-2));
		    midx=(mx-minx)/2+minx;
		    score=0;
		    pausetime=100;
		    countlev=1;
		    maxy=getmaxy();
		    wait=1;                            //variable to move cubes in a band called maxwait
		    deviation=0;
		//changecolor=1;
		    cubex=cubey=10;
		    for(int i=0;i<NumElements;++i)
			  for(int j=0;j<Breadth;j=j+2)
			  {
				cube_positions[i][j]=(-2);
				initposn[i][j]=(-2);
				if(i==0)
				cubes_in_a_line[j]=(-2); // initializing this only once
			 }
    }
	int downward()
	{
	      setbkcolor(BLACK);
		  setcolor(WHITE);
	      setlinestyle(0,0,0);

	      score=0;            //intialvalue of score is zero
		  int m,n;
		  m=200;
		  n=300;
		  int slowdown=0;
		  void *saucer;

	     clearviewport();//to remove cout

	     triangle(x,y);
		 drawpic();


		 setfillstyle(SOLID_FILL,getbkcolor());
		 bar(getmaxx()-100,0,getmaxx(),10);
		 outtextxy(getmaxx()-100,0,"score ");

		 setfillstyle(SOLID_FILL,getbkcolor());
		 bar(0,0,100,10);
		 outtextxy(0,0,"level ");
		 putlevel();


		   do
		   {

			 slowdown=slowdown+1;
		     if(slowdown==6)
			 {
			   n=n+30;	   //drawing  trees on either side
			       m=minx-((n-miny)*1);
			       if(n>=300 && n<359)
				   {
			      drawtree(m,n,1);
			      drawtree(getmaxx()-m,n,1);
		   }
			       if(n>=359 && n<418)
				   {
			      drawtree(m,n,2);
			      drawtree(getmaxx()-m,n,2);
		   }
				   if(n>=418 && n<477)
				   {
			      drawtree(m,n,3);
			      drawtree(getmaxx()-m,n,3);
		   }
			 }
			 if(slowdown==7)  //reduces the speed of moving trees
				slowdown=0;
		     if(n>=477)
			 {
		       n=miny;
			       ++changecolor;
	     }

		     for(int j=NumElements-1;j>=0;--j)
		     {
			for(int i=0;i<Breadth;i=i+2)
			    {
				      if(cube_positions[j][i]>0)
				      {
				       cubex=cube_positions[j][i];                                        //cubex ,cubey takes the present position of cube
				       cubey=cube_positions[j][i+1];

				       size = imagesize(cubex,cubey-4,cubex+cubesize+4,cubey+cubesize);     //stores the image  in memory
				       saucer =malloc( size );
				       getimage(cubex,cubey-4,cubex+cubesize+4,cubey+cubesize,saucer);
				       putimage(cubex,cubey-4,saucer,XOR_PUT);                             //removes the present image of cube
				       free(saucer);


			      cubey=cubey+1;                                       //the differential movement in vertical direction is 1
				  if(initposn[j][i]>=minx && initposn[j][i]<=26+minx) //the following 'if' statements sets the deviation of cubes in horizontal direction, based on the place from wher they orginated
				      cubex=cubex+2;
				  else if(initposn[j][i]>=26+minx && initposn[j][i]<=26*2+minx)
				     cubex=cubex+2;
				  else if(initposn[j][i]>=26*2+minx && initposn[j][i]<=26*3+minx)
				     cubex=cubex+1;
				  else if(initposn[j][i]>=26*3+minx && initposn[j][i]<=26*4+minx)
				     cubex=cubex+1;
			      else if(initposn[j][i]>=26*4+minx && initposn[j][i]<=26*5+minx)
				     cubex=cubex+0;
				  else if(initposn[j][i]>=26*5+minx && initposn[j][i]<=26*6+minx)
				     cubex=cubex-1;
				  else if(initposn[j][i]>=26*6+minx && initposn[j][i]<=26*7+minx)
				     cubex=cubex-1;
				  else if(initposn[j][i]>=26*7+minx && initposn[j][i]<=26*8+minx)
				     cubex=cubex-2;
				  else if(initposn[j][i]>=26*8+minx && initposn[j][i]<=26*9+minx)
				     cubex=cubex-2;
				  else
				 cubex=cubex+0;

				  if(wait<maxwait)  //if the cube(or cube position )  is in a particular element then it is stored in the same element
					      {
					    cube_positions[j][i]=cubex;
						    cube_positions[j][i+1]=cubey;
					      }

						  if(j!=NumElements-1)
						  {

						       if(wait==maxwait)
						       {
							    cube_positions[j+1][i]=cubex;
							    cube_positions[j+1][i+1]=cubey;
							    initposn[j][i]=initposn[j-1][i];
						       }
				   putimage(cubex,cubey-4,saucer,1);//puting
			     }

			   }//closes if condition

		     }//2nd for loop

		  }//1st for loop

			  for(int k=0;k<Breadth;k+=2)
			  {
		    if(wait==maxwait)
			    {
			      do
			      {
			      cubes_in_a_line[k]=random(mx);       //creates new cubes position
			      }while(cubes_in_a_line[k]<minx);

			      setfillstyle(SOLID_FILL ,YELLOW);     //creates new cubes
			      bar3d(cubes_in_a_line[k],miny,cubes_in_a_line[k]+cubesize,miny+cubesize,4,1);
			      cube_positions[0][k]=cubes_in_a_line[k];
			      cube_positions[0][k+1]=miny;
			      initposn[0][k]=cubes_in_a_line[k];
			    }
			 }

		delay (35-(countlev*5));        //increases the level
			    ++wait;
			    if(wait>maxwait)
			    wait=1;


		  c='/0';
		  if(kbhit())
		  c=getch();
		  if(c=='o')
		  exit(1);
		  side();
		  ++score;
		  putscore();

		   if(score>=(countlev*500))
		   {   if(countlev<=9)
		      {
			   ++countlev;
			   putlevel();
		      }
		   }

	  }while( check() );
	  clearviewport();
	  setbkcolor(RED);
	  textgraph("! OUT !"," ",1);

	  setbkcolor(getbkcolor());
	  return score;
    }


    void drawpic()
    {
		setfillstyle(SOLID_FILL,CGA_WHITE);
		bar(0,0,getmaxx(),miny-6);

		setfillstyle(SOLID_FILL,WHITE);
		pieslice(100,100,0,360,20);
		pieslice(120,100,0,360,20);
		pieslice(140,120,0,360,30);
		pieslice(500,120,0,360,20);
		pieslice(520,100,0,360,20);
		pieslice(540,120,0,360,30);

	   int *poly=new int[8];
	   poly[0] = 0;
	   poly[1] =miny-6 ;

	   poly[2] = minx;
	   poly[3] = miny-6;

	   poly[4] = 0;
	   poly[5] = getmaxy();

	   poly[7] = 0;
	   poly[8] =miny-6 ;

	   setfillstyle(SOLID_FILL,GREEN);
	   fillpoly(3, poly);


	   poly[0] = mx;
	   poly[1] =miny-6 ;

	   poly[2] = getmaxx();
	   poly[3] = miny-6;

	   poly[4] = getmaxx();
	   poly[5] = getmaxy();


	   poly[7] = 0;
	   poly[8] =miny-6 ;

	   setfillstyle(SOLID_FILL,EGA_GREEN);
	   fillpoly(3, poly);

	   delete[] poly;

    }

    void drawtree(int bottomx,int bottomy,int big)
    {

	setfillstyle(SOLID_FILL,BROWN);
	bar( bottomx-10, bottomy-(15*( big+1)), bottomx, bottomy);

	 if(changecolor%2==0)
	 {
	  setfillstyle(SOLID_FILL,GREEN);
	  pieslice(  bottomx-10,   bottomy-(15*( big+1)), 0, 360,5*( big+1));
	 }
	 else
	 {
	    setfillstyle(SOLID_FILL,LIGHTGREEN);
	    pieslice(  bottomx-10,   bottomy-(15*( big+1)), 0, 360,5*( big+1));
	 }
    }

    void triangle(int l,int m)
    {
	line(l,m,l-10,m+10);
	line(l,m,l+10,m+10);
	line(l-cubesize,m+10,l+cubesize,m+10);
    }

    void movecursor(int  m)
    {
	 setcolor(getbkcolor());
	 triangle(x,y);                  //ersases old cursor 
	 x=x+m;
	 setcolor(WHITE);
	 triangle(x,y);                   //draws new cursor
    }

    void side()
    {
	    switch(c)       //movement using cursor keys
	    {
		  case 77:{if(x>=mx)movecursor(0);else movecursor(2);}break;
		  case 75:{if(x<=minx)movecursor(0);else movecursor(-2);}break;
		  case 'p':{pause();}
	    }
    }


    void pause()
	{                                   //for passing during the game
		char inp='/0';
		while(inp!='p')
		{
			delay(50);
			inp=getch();
		}
	}


     int check()                   //checks cursor & cube meets or not
    {

	    for(int i=0;i<Breadth;i=i+2)
	{
	     if( cube_positions[NumElements-3][i+1]+cubesize>=y)
		{
		 if(cube_positions[NumElements][i]+cubesize>=x && cube_positions[NumElements][i]+cubesize<=x-cubesize)
		      {return 0;}
		 if( cube_positions[NumElements-3][i]>=x-cubesize && cube_positions[NumElements-3][i]<=x+cubesize )
		      {return 0;}
		    }
		if( cube_positions[NumElements-2][i]==x+cubesize || cube_positions[NumElements-3][i]+cubesize==x-cubesize )
		    {return 0;}
	}
	return 1;
    }


    void putscore()           //puts the score
    {
	setfillstyle(SOLID_FILL,getbkcolor());
	bar(getmaxx()-40,0,getmaxx(),10);
	itoa(score,num,10);
	outtextxy(getmaxx()-40,0,num);
    }


    void putlevel()         //put the level
    {
	setfillstyle(SOLID_FILL,getbkcolor());
	bar(60,0,100,10);
	itoa(countlev,level,10);
	outtextxy(60,0,level);
    }


  };

 class run
{
	int b,l,x,y,result,count;
	float i;
	char c;
	public:
	run()
	{
		x=getmaxx()/2;
		y=getmaxy()/2;
		l=x*2;
		b=y*2;
		count=0;

		randomize();
		i=1;
        clearviewport();

	}
	int move1()    // lest means 1. right na 2. both sides na 0.
	{

		randomize();
		do
		   {
			int poly[8];
			int p=random(3);
			y=getmaxy()/2;

			int rand,posn;
			rand=random(5);

		do
		{
			setfillstyle(0, 1);
			bar(0,0,getmaxx(),getmaxy());

				char s[25];
                itoa(count,s,10);
				outtextxy((getmaxx()-50),15,s);


			setlinestyle(3,4,3);
			line(x,2*y,x,y);
			draw(p);

			poly[0] = int(x-i);/* 1st vertex */
			poly[1] = y;

			poly[2] = int(x+i); /* 2nd */
			poly[3] = y;

			poly[4] = x+150; /* 3rd */
			poly[5] = 2*y;

			poly[6] = x-150;
			poly[7] = 2*y;

			setfillstyle(8, 8);
			fillpoly(4, poly);

			y=y+2;
			if( y<(b-45) )
//just to ensure that the input is there only when the bar is near the end. he input anywhere
				if(kbhit())
					result=0;

				 i=i+0.65;
		}while(y<(b-10));

		   if(!kbhit())
		   {
			result=0;
			   }
		   else
		   {
			c=getch();
			result=input(p,c);
		   }
		   count++;
		   i=1;
		}while(result);
		return count;

	}
void draw(int g)
	{
		if(g==0)
		{
			setlinestyle(3,4,3);
			line(0,y,2*x,y);
			line(0,y,2*x,y);
			line(0,int(y+(i/2)) ,2*x,int(y+(i/2)) );
			setfillstyle(8, 8);
			bar(0,int(y),2*x,int(y+(i/2)));//use i for zooming effect
		}
		else if(g==1)
		{
			setlinestyle(3,4,3);
			line(0,y,x,y);
			line(0,y,int(x+i),y);
			line(0,int(y+(i/2)) ,int(x+i),int(y+(i/2)) );
			setfillstyle(8, 8);
			bar(0,int(y),int(x+i),int(y+(i/2)));

		}
		else if(g==2)
		{
			setlinestyle(3,4,3);
			line(x,y,2*x,y);
			line(int(x-i),y,2*x,y);
			line(int(x-i),int(y+(i/2)) ,2*x,int(y+(i/2)) );
			setfillstyle(8, 8);
			bar(int(x-i),int(y),2*x,int(y+(i/2)));
		}
	}

void turn(int a)
{

	int m;
	if(a==2)
		m=getmaxx();
	else
		m=0;		      //m is maxx
	int n=getmaxy();

	int x=getmaxx()/2;
	int y=n/2;

	while((doit(m-1)))      //adding one would have occurred in the loop. im checking for nxt loop only
	{
		setfillstyle(0, 1);
			bar(0,0,getmaxx(),getmaxy());

		if(a==2)
		{
			line((m),(n)-2,x,(2*y)-2);

			int poly[8];

			setlinestyle(3,4,3);

			poly[0] = x-10;/* 1st vertex */
			poly[1] = 2*y;

			poly[2] = m-5; /* 2nd */
			poly[3] = n-2;

			poly[4] = m+15; /* 3rd */
			poly[5] = n-2;

			poly[6] = x+10;
			poly[7] = 2*y-5;

			setfillstyle(8, 8);
			fillpoly(4, poly);


			if(kbhit())
				delay(50);
			m=m-15;
		}
		else if(a==1)
		{
			line(m,(n)-2,x,(2*y)-2);

			int poly[8];

			poly[0] = x-10;/* 1st vertex */
			poly[1] = 2*y;

			poly[2] = m+5; /* 2nd */
			poly[3] = n-2;

			poly[4] = m+15; /* 3rd */
			poly[5] = n-2;

			poly[6] = x+10;
			poly[7] = 2*y-5;

			setfillstyle(8, 8);
			fillpoly(4, poly);


			if(kbhit())
				delay(50);
			m=m+15;
		}

	      n=n-5;
	}
}
int doit (int m)             //only for turning
{
	if(m<x-5||m>x+5)
	return 1;
	else
	return 0;
}
int input(int a,char b)
{
	if(b=='a')
//turning check

		{
			if(a==1||a==0)
			{
				turn(1);
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else if(b=='d')
		{
			if((a==2||a==0))
			{
				turn(2);
				return 1;
			}
			    else
			{
				return 0;
			    }
		}
		else
		{
			return 0;
		}
	}

    };

    class scores : public cubefield , public run
    {
	public:

	char filename[10],game;
	char playername[23];
	int score;
	int midx,midy;
	int txtht;
	int back;

      //char msg[];
	scores()
	{
	       txtht=8;
	       midx=getmaxx()/2;
	       midy=getmaxy()/2;
	       strcpy(playername,"check ");
	       back=0;
	// CODES : 1-cubefield.2-templerun
	}

    int menu()
    {
	 int option;
	 int option1=0;//create or open account
	 int option3=0;//exist is made false for  profile to be shown
	 int exit=0;
	 while(exit==0)
	 {
	    clearviewport();
		option=select_game();
	    slide2();
		clearviewport();
		do
		{
		option1=aboutaccount();//either to open or create account
		clearviewport();
		account_selection(option1);
		clearviewport();
	   }while(back);

	     //profile
	     while(option3!=1)//option3 ==1 to quit
	     {

			option3 = game_menu();
		if(option3==3){output_scores();option3=0;clearviewport();}
		else if(option3==4){option3=1;clearviewport();}//if back is pressed profile will not show
		else if(option3==2)
		    {
		       if(::choice==1)
			   {
		   clearviewport();
			       intialise();
			       score=downward();
			       update_scores(score);
		   option3=0;//return back to profile
			      clearviewport();
			  }
			  else if(::choice==2)
			  {
		   clearviewport();
			       score=move1();
			       update_scores(score);
			       option3=0;//return back to profile
			       clearviewport();
			   }
			   cin.get();
		   }
	   }
	   option3=0;//making show profile true

	 }
    }

    int game_menu()
    {
			setbkcolor(LIGHTGREEN);
			char c5='a';//some random charecter

			 clearviewport();
			 border();
			 setcolor(RED);
			 settextstyle(0,0,3);
			     outtextxy(midx-textwidth("MENU")/2,100,"MENU");
			 settextstyle(0,0,3);
			     outtextxy(midx-textwidth("WELCOME")/2,45-textheight(playername)/2,"WELCOME  ");
			     outtextxy(midx-textwidth(playername)/2,50,playername);
			 setlinestyle(0,0,0);
			 settextstyle(0,0,0);
	    char msg1[]="START GAME ";
	    char msg2[]="DISPLAY SCORE";
	    char msg3[]="BACK";


	 int c12=1;
		 char as;
		 int minypos=midy-50;
		 int maxypos=midy+50;
		 int ypos=midy-60;
		 int xpos=midx-textwidth(msg2)+30;
				 outtextxy(midx-textwidth(msg1)/2,midy-50,msg1);
				 outtextxy(midx-textwidth(msg2)/2,midy,msg2);
				 outtextxy(midx-textwidth(msg3)/2,midy+50,msg3);
				 setcolor(WHITE);
				 rectangle(xpos,ypos,xpos+150,ypos+20);
				 as=getch();
				 while(as!=13)
				 {

				    switch(as)       //movement using cursor keys
				    {
				     case 72:{   if(ypos>=minypos) {moverect(xpos,ypos,-50);--c12;} }break;
				     case 80:{   if(ypos+11<=maxypos) {moverect(xpos,ypos,50);++c12;}  }break;
				   }
				  as=getch();
				}
			clearviewport();
			sound(2);sound(2);delay(110);
			settextstyle(0,0,0);
			setcolor(WHITE);

             sound(2);
            setbkcolor(BLACK);

				     if(c12==1)//''
					       return 2;
				     else if(c12==2)
						return 3;
				     else if(c12==3)
					 return 4;

   }

	int select_game()
	{

			     setbkcolor(LIGHTRED);
		  //Ist slide
			     //1-cubefield. 2 run
			     char c1='\0';        // c is charecter input in slide_1
			     circle(100,200,10);
				 setlinestyle(0,0,7);
				 line(97,210,110,280);//body

				 line(100,229,70,221);//hands
				 line(100,229,68,240);


				 line(110,278,82,303);//I
				 line(110,278,125,307);//II
				 line(83,303,88,326);//III
				 line(125,308,144,322);//IV

				 setlinestyle(3,4,5);//sledge
				 line(112,327,68,327);

				 setlinestyle(3,8,2);//handle
				 line(68,240,68,330);

				 setlinestyle(2,10,1);//wheels
				 circle(73,335,5);
				 circle(110,335,5);
				 line(73,330,73,340);
				 line(110,330,110,340);

				 setfillstyle(1,0);//first set bgrnd colour
				 bar(115,308,151,336);
				 line(125,308,144-2,322-1);
				 delay(10);
	    setcolor(BLUE);
	    settextstyle(0,0,0);
	    setlinestyle(0,0,0);
	    border();
	    char msg4[]="ARCADE GAMES";
	    char msg1[]="CUBE FIELD";
	    char msg2[]="ROAD RUNNER";
	    char msg3[]="EXIT";

		 int c12=1;
		 char as;
		 int minypos=midy-50;
		 int maxypos=midy+50;
		 int ypos=midy-60;
		 int xpos=midx-textwidth(msg2)+20;
				  setcolor(WHITE);
				  settextstyle(0,0,2);
				  outtextxy(midx-textwidth(msg4)/2,50,msg4);
				  settextstyle(0,0,0);
				  setcolor(BLUE);
				  outtextxy(midx-textwidth(msg1)/2,midy-50,msg1);
				  outtextxy(midx-textwidth(msg2)/2,midy,msg2);
				  outtextxy(midx-textwidth(msg3)/2,midy+50,msg3);
				  setcolor(WHITE);
				  rectangle(xpos,ypos,xpos+150,ypos+20);
				  as=getch();
				  while(as!=13)
				 {

				    switch(as)       //movement using cursor keys
				    {
				     case 72:{   if(ypos>=minypos) {moverect(xpos,ypos,-50);--c12;} }break;
				     case 80:{   if(ypos+11<=maxypos) {moverect(xpos,ypos,50);++c12;}  }break;
				    }
				  as=getch();
				}
		      clearviewport();

			sound(2);sound(2);
				     if(c12==1)//''
					       { ::choice=1;}
				     else if(c12==2)
						{ ::choice=2;}
				     else if(c12==3)
					 exit(1);

	  setbkcolor(BLACK);

	if (::choice==1)
			strcpy(filename,"cube.dat");
		else if(::choice==2)
			strcpy(filename,"run.dat");
	return 0;

    }
void moverect(int xp,int &yp,int m)
{
	 setcolor(getbkcolor());
	 rectangle(xp,yp,xp+150,yp+20);
	 yp=yp+m;
	 setcolor(WHITE);
	 rectangle(xp,yp,xp+150,yp+20);
  }
void blinke(int x,int y,char string[30])
{
     settextstyle(0,0,0);
      while(!kbhit())
      {
      setcolor(WHITE);
      outtextxy(x,y,string);
      delay(50);
      setcolor(getbkcolor());
      outtextxy(x,y,string);
      delay(50);
      }
      setcolor(WHITE);
}
void border()
{
     rectangle(10,10,getmaxx()-10,getmaxy()-10);
}

    void slide2()
    {
	     clearviewport();
	     border();
	    setbkcolor(BLUE);
	    settextstyle(0,0,0);
	    if(::choice==1)
		{
			textgraph("CUBE   ","FIELD",2);
			border();
            delay(100);
			setcolor(WHITE);
			 settextstyle(0,0,0);
			 rectangle(160,10,600,100);
	    outtextxy(170,20,"Captain Tsubasa's is on a mission in planet Ranklop.");
	    outtextxy(170,30,"When his space ship was sighted by the enemies");
	    outtextxy(170,40,"Tsubasa abandoned his spaceship and jumped down.");
	    outtextxy(170,50,"As the pilot you are caught in the spaceship.");
	    outtextxy(170,60,"Guide the through the field. to land safely.");
	    outtextxy(170,70,"BEWARE the enemies are building blocks at you");
	    outtextxy(170,80,"Try to  move  safely");
		}
		 else
		 {
			textgraph("ROAD","RUNNER",2);
			border();
			delay(100);
			 settextstyle(0,0,0);
			 setlinestyle(0,0,0);
			 setcolor(WHITE);
			 rectangle(160,10,600,100);
	       outtextxy(170,20,"Captain Tsubasa's is on a mission in planet Ranklop.");
		outtextxy(170,30,"When his space ship was sighted by the enemies,");
		outtextxy(170,40,"Tsubasa abandoned his spaceship and took his scooty.");
		outtextxy(170,50,"But his hand was shot. Quickly as his associate,you got");
		outtextxy(170,60,"control of the scooty. Drive it to safety.mind you");
		outtextxy(170,70,"cannot control the speed. Try to be on track.");
		outtextxy(170,80,"Death awaits on either side");
		 }

		settextstyle(0,0,0);
		blinke(getmaxx()/2-100,getmaxy()-50,"Press any key to continue");

		clearviewport();

    }

    void account_selection(int ans)
    {
         border();
	  char c5;
	  char c=' ';
	  int i=0;
	    setbkcolor(BLUE);
	    char temp[23]=" ";
	    char msg1[]="ENTER NAME <minimum 4 characters>";
	    char msg2[]="THIS NAME EXISTS ALREADY ";
	    char msg3[]="SUCCESFULLY WRITTEN";
	    char msg4[]="THIS NAME DOES NOT EXIST";
	    char msg5[]=" < press r to re-enter the name, press   'n' to go back> ";
	    setcolor(LIGHTGRAY);
	   do//this is common to both open and create account this is accepting the name for first time
	    {
		  clearviewport();
		  border();
		  settextstyle(0,0,2);
		  if(ans==1) outtextxy(midx-textwidth("\n\n\n\WELCOME BACK\n\n\n ")/2,textheight("\n\n\n\WELCOME BACK\n\n\n ")/2,"\n\n\n\WELCOME BACK\n\n\n ");
		  settextstyle(0,0,0);
		  outtextxy(midx-textwidth(msg1)/2,midy,msg1);
		  c=getch();
		  while(c!=13 && i<=22)
		  {
		    temp[i]=c;
		    ++i;
		    temp[i+1]='\0';
		    setcolor(BLUE);
		    bar(midx-textwidth(temp),midy-12,midx,midy);
		    setcolor(LIGHTGRAY);
		    outtextxy(midx-textwidth(temp),midy-12,temp);
		    c=getch();
		  }
		  temp[i+1]='\0';
		  strcpy(playername,temp);



		}while(!validname());


	    //CODE 1-open account 2-create account

	   if(ans ==2)
	   {
		       while(!validacc() && (!back))//this will proceed only if such a name doesnot exist
		  {
			    do
		       {
			    clearviewport();
			    border();
			    settextstyle(0,0,0);
			    outtextxy(midx-textwidth(msg2)/2,midy,msg2);
			    outtextxy(midx-textwidth(msg5)/2,midy-10,msg5);
			    settextstyle(0,0,0);

			    c5=getch();
			    if(c5=='r')
			    {
				    clearviewport();
				    border();
				    settextstyle(0,0,0);
				    outtextxy(midx-textwidth(msg1)/2,midy,msg1);

		  c=getch();
		  while(c!=13 && i<=22)
		  {
		    temp[i]=c;
		    ++i;
		    temp[i+1]='\0';
		    setcolor(BLUE);
		    bar(midx-textwidth(temp),midy-12,midx,midy);
		    setcolor(LIGHTGRAY);
		    outtextxy(midx-textwidth(temp),midy-12,temp);
		    c=getch();
		  }
		  temp[i+1]='\0';
		  strcpy(playername,temp);
			     }
			else if(c5=='n')
			back=1;//he will go to open account ,create account slide*/
	 }while(!validname() && (!back));
	  }

			  //creating account
				    fstream file(filename,ios::binary|ios::out|ios::app);
					    if(!file)
					      {
						     cerr<<"error in creating account";
						     cin.get();
					      }

				      score_data.score=0;
				      strcpy(score_data.name,playername);
				      file.seekp(0,ios::end);
				      file.write((char*)&score_data,sizeof(score_data));
				      clearviewport();
				      outtextxy(midx-textwidth(msg3),midy,msg3);
				      file.close();
	 }


	 if(ans==1)
	 {
	    while(validacc() && (!back) ) //this will proceed only if such a name exists
		    {
			    do
			    {
			    clearviewport();
			    border();
			    settextstyle(0,0,0);
			    outtextxy(midx-textwidth(msg4)/2,midy,msg4);
			    outtextxy(midx-textwidth(msg5)/2,midy-10,msg5);

			    c5=getch();
			    if(c5=='r')
			    {
			      clearviewport();
			      settextstyle(0,0,0);
			      outtextxy(midx-textwidth(msg1),midy,msg1);

		  c=getch();
		  while(c!=13 && i<=22)
		  {
		    temp[i]=c;
		    ++i;
		    temp[i+1]='\0';
		    setcolor(BLUE);
		    bar(midx-textwidth(temp),midy-12,midx,midy);
		    setcolor(LIGHTGRAY);
		    outtextxy(midx-textwidth(temp),midy-12,temp);
		    c=getch();
		  }
		  temp[i+1]='\0';
		  strcpy(playername,temp);
			    }

			  else if(c5=='n')
			  back=1;//he will go to open account ,create account slide
		   }while(!validname() && (!back));
			 }
	     }
       return ;
    }
 int aboutaccount()
      {
		   //SLIDE II
	    back=0;
	    int selection=0;
	    setbkcolor(BLUE);

	    char msg1[]="OPEN ACCOUNT";
	    char msg2[]="CREATE ACCOUNT";
	    char msg4[]="ACCOUNT TYPE";

		 int c12=1;
		 char as;// as is charecter input in slide_2
		 int minypos=midy-50;
		 int maxypos=midy+50;
		 int ypos=midy-60;
		 int xpos=midx-textwidth("CREATE ACCOUNT")/2-20;
		 setcolor(WHITE);
         border();
			 settextstyle(0,0,0);
				 outtextxy(getmaxx()-350,50,msg4);
			 outtextxy(midx-textwidth(msg1)/2,midy-50,msg1);
			     outtextxy(midx-textwidth(msg2)/2,midy+50,msg2);

				 rectangle(xpos,ypos,xpos+150,ypos+20);
				 as=getch();
				 while(as!=13)
				 {

				    switch(as)       //movement using cursor keys
				    {
				     case 72:{   if(ypos>=minypos) {moverect(xpos,ypos,-100);--c12;} }break;
				     case 80:{   if(ypos+11<=maxypos) {moverect(xpos,ypos,100);++c12;}  }break;
				   }
				  as=getch();
				}
		      clearviewport();

			sound(2);sound(2);
				     if(c12==1)//''
					       selection=1;
				     else if(c12==2)
						   selection=2;
	return selection;
    }

int validacc()
{
	//checking validity
	       int validaccount=1;


	    fstream fi(filename,ios::binary|ios::in|ios::app);
			if(!fi)
			   {
		   cerr<<"error: in file in valid account";
				   cin.get();
				   exit(1);
			   }
			do
			    {
				   fi.read((char*)&score_data,sizeof(score_data));

				     if(!(strcmp(score_data.name,playername)))
				  {
					validaccount=0;
				  }
			    }while(!fi.eof()) ;
			   fi.close();
			   if(validaccount==0)
			    return 0;
			   else
			    return 1;

}

int validname()
{
	return (strlen(playername)>=4)?1:0;
}

int update_scores(int points)
{
    clearviewport();
    border();
	long reckpos=0;
	char temp[20]="   ";
	int highscore=0;
	itoa(points,temp,20);
	outtextxy(midx,midy,temp);

	int gamemax=0;//if it is 1 then score is high score  if it is 0 then not a high score

	fstream file(filename,ios::binary|ios::out|ios::in);

		if(!file)
	    {cerr<<"error in updating scores";   exit(0);}

		reckpos=file.tellg();
	       file.read((char*)&score_data,sizeof(score_data));
		while(!file.eof())
		{
           if(score_data.score>highscore)
             highscore=score_data.score;




		if(!strcmp(score_data.name,playername))
			{
		       if(score_data.score<points)
				{
					gamemax=1;
				       file.seekp(reckpos,ios::beg);
				       score_data.score=points;
				       file.write((char*)&score_data,sizeof(score_data));
				       file.close();
				       return 0;
			       }
			    }
		reckpos=file.tellg();
		file.read((char*)&score_data,sizeof(score_data));
		}
	       file.close();
         
	      if(points>=highscore)
	      {blinke(midx,midy-12,"GRAND HIGH SCORE"); gamemax=0;}
          
          
          if(gamemax==1)
	      blinke(midx,midy-12,"YOUR HIGH SCORE");



	       cin.get();
	       return 0;
     }

    int output_scores()
    {
	settextstyle(0,0,0);
	
	
	  int tempsc=0;
	  int change=0;  //changes y cordinate during output
	  char strscore[10]; 
	  strcpy(strscore," ");
	  clearviewport();
	  setbkcolor(BLUE);
	  setcolor(WHITE);
      border();
	   fstream fi(filename,ios::binary|ios::in|ios::app);
			if(!fi)
			   {
			   cerr<<"error: in file in output scores";
				   cin.get();
				   exit(1);
			   }
				   if(::choice==1)
				  outtextxy(midx,10,"CUBEFIELD SCORES");
				   else if(::choice==2)
				   outtextxy(midx,10,"ROAD RUNNER SCORES");

				   outtextxy(midx-50,30,"NAME");
				   outtextxy(midx+50,30,"SCORE");


				   fi.read((char*)&score_data,sizeof(score_data));
			    while(!fi.eof())
			    {

				   settextstyle(0,0,0);
				   change+=10;
				   outtextxy(midx-50,40+change,score_data.name);
				   tempsc=score_data.score;
				   itoa(tempsc,strscore,10);
				   outtextxy(midx+50,40+change,strscore);

				  fi.read((char*)&score_data,sizeof(score_data));
			    }






			    fi.close();
			    cin.get();
			   clearviewport();

		return 0;
    }
};

    int main()
    {
	 // request auto detection
    	int gdriver = DETECT, gmode, errorcode;
    
	// initialize graphics and local variables
	initgraph(&gdriver, &gmode, "..\\bgi");
    
	// read result of initialization
        errorcode = graphresult();
        if (errorcode != grOk)  // an error occurred
        {
           printf("Graphics error: %s\n", grapherrormsg(errorcode));
           printf("Press any key to halt:");
           getch();
           exit(1); // terminate with an error code
        }
     scores s;
     cubefield c;
     run t;
        
     s.menu();
    
    cout<<"Thank you for playing";
        cin.get();
    return 0;
    }
