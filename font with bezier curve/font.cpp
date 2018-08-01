#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <iostream>
#include <cmath>
#include <assert.h>
using namespace std;

HWND myconsole = GetConsoleWindow();
HDC mydc = GetDC(myconsole);

void drawRectangle(double x1, double y1, double x2, double y2){

    double x = min(x1,x2);
    double y = min(y1,y2);
    double width = abs(x1-x2);
    double height = abs(y1-y2);

    for (int i = 0, j = x; i < width; i++){
        SetPixel(mydc,j++,y1,RGB(0,255,0));
    }
    for (int i = 0, j = x; i < width; i++){
        SetPixel(mydc,j++,y2,RGB(0,255,0));
    }
    for (int i = 0, j = y; i < height; i++){
        SetPixel(mydc,x1,j++,RGB(0,255,0));
    }
    for (int i = 0, j = y; i < height; i++){
        SetPixel(mydc,x2,j++,RGB(0,255,0));
    }

}


void drawOval(double x, double y, double r1, double r2, double midX, double midY){
    double angle1, angle2, a1, b1, a2, b2;
    int noOfLines = 2000;

    for (int i = 0; i < noOfLines; i++){
        angle1 = i * (2 * M_PI/noOfLines);
        angle2 = (i + 1) * (2 * M_PI/noOfLines);
        a1 = x + r1*cos(angle1);
        b1 = y + r2*sin(angle1);
        a2 = x + r1*cos(angle2);
        b2 = y + r2*sin(angle2);
        SetPixel(mydc,a1 + midX - x,b1 + midY - y,RGB(0,255,0));
        SetPixel(mydc,a2 + midX - x,b2 + midY - y,RGB(0,255,0));
    }

}
//Retrieved from http://members.chello.at/~easyfilter/bresenham.html
void plotLine(int x0, int y0, int x1, int y1)
{
   int dx =  abs(x1-x0), sx = x0<x1 ? 1 : -1;
   int dy = -abs(y1-y0), sy = y0<y1 ? 1 : -1;
   int err = dx+dy, e2; /* error value e_xy */

   for(;;){  /* loop */
      SetPixel(mydc, x0,y0, RGB(0,255,0));
      if (x0==x1 && y0==y1) break;
      e2 = 2*err;
      if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
      if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
   }
}

void plotQuadBezierSeg(int x0, int y0, int x1, int y1, int x2, int y2)
{ /* plot a limited quadratic Bezier segment */
  int sx = x2-x1, sy = y2-y1;
  long xx = x0-x1, yy = y0-y1, xy; /* relative values for checks */
  double dx, dy, err, cur = xx*sy-yy*sx; /* curvature */
  assert(xx*sx <= 0 && yy*sy <= 0); /* sign of gradient must not change */
  if (sx*(long)sx+sy*(long)sy > xx*xx+yy*yy) { /* begin with longer part */
    x2 = x0; x0 = sx+x1; y2 = y0; y0 = sy+y1; cur = -cur; /* swap P0 P2 */
  }
  if (cur != 0) { /* no straight line */
    xx += sx; xx *= sx = x0 < x2 ? 1 : -1; /* x step direction */
    yy += sy; yy *= sy = y0 < y2 ? 1 : -1; /* y step direction */
    xy = 2*xx*yy; xx *= xx; yy *= yy; /* differences 2nd degree */
    if (cur*sx*sy < 0) { /* negated curvature? */
      xx = -xx; yy = -yy; xy = -xy; cur = -cur;
    }
    dx = 4.0*sy*cur*(x1-x0)+xx-xy; /* differences 1st degree */
    dy = 4.0*sx*cur*(y0-y1)+yy-xy;
    xx += xx; yy += yy; err = dx+dy+xy; /* error 1st step */
    do {
      SetPixel(mydc, x0,y0,RGB(0,255,0)); /* plot curve */
      if (x0 == x2 && y0 == y2) return; /* last pixel -> curve finished */
      y1 = 2*err < dx; /* save value for test of y step */
      if (2*err > dy) { x0 += sx; dx -= xy; err += dy += yy; } /* x step */
      if ( y1 ) { y0 += sy; dy -= xy; err += dx += xx; } /* y step */
    } while (dy < 0 && dx > 0); /* gradient negates -> algorithm fails */
  }
  plotLine(x0,y0, x2,y2); /* plot remaining part to end */
}

void plotQuadBezier(int x0, int y0, int x1, int y1, int x2, int y2)
{ /* plot any quadratic Bezier curve */
  int x = x0-x1, y = y0-y1;
  double t = x0-2*x1+x2, r;
  if ((long)x*(x2-x1) > 0) { /* horizontal cut at P4? */
    if ((long)y*(y2-y1) > 0) /* vertical cut at P6 too? */
      if (fabs((y0-2*y1+y2)/t*x) > abs(y)) { /* which first? */
        x0 = x2; x2 = x+x1; y0 = y2; y2 = y+y1; /* swap points */
      } /* now horizontal cut at P4 comes first */
    t = (x0-x1)/t;
    r = (1-t)*((1-t)*y0+2.0*t*y1)+t*t*y2; /* By(t=P4) */
    t = (x0*x2-x1*x1)*t/(x0-x1); /* gradient dP4/dx=0 */
    x = floor(t+0.5); y = floor(r+0.5);
    r = (y1-y0)*(t-x0)/(x1-x0)+y0; /* intersect P3 | P0 P1 */
    plotQuadBezierSeg(x0,y0, x,floor(r+0.5), x,y);
    r = (y1-y2)*(t-x2)/(x1-x2)+y2; /* intersect P4 | P1 P2 */
    x0 = x1 = x; y0 = y; y1 = floor(r+0.5); /* P0 = P4, P1 = P8 */
  }
  if ((long)(y0-y1)*(y2-y1) > 0) { /* vertical cut at P6? */
    t = y0-2*y1+y2; t = (y0-y1)/t;
    r = (1-t)*((1-t)*x0+2.0*t*x1)+t*t*x2; /* Bx(t=P6) */
    t = (y0*y2-y1*y1)*t/(y0-y1); /* gradient dP6/dy=0 */
    x = floor(r+0.5); y = floor(t+0.5);
    r = (x1-x0)*(t-y0)/(y1-y0)+x0; /* intersect P6 | P0 P1 */
    plotQuadBezierSeg(x0,y0, floor(r+0.5),y, x,y);
    r = (x1-x2)*(t-y2)/(y1-y2)+x2; /* intersect P7 | P1 P2 */
    x0 = x; x1 = floor(r+0.5); y0 = y1 = y; /* P0 = P6, P1 = P7 */
  }
  plotQuadBezierSeg(x0,y0, x1,y1, x2,y2); /* remaining part */
}

void drawPolygon(int N){
    int x[100];
    int y[100];
    int x_centre = 200;
    int y_centre = 200;
    int r = 75;
    int n = 0;

    while(n < N){
        x[n] = r * cos(2*M_PI*n/N ) + x_centre;
        y[n] = r * sin(2*M_PI*n/N ) + y_centre;
        SetPixel(mydc, x[n],y[n],RGB(0,255,255));
        n++;
    }

    plotLine(x[N-1],y[N-1],x[0],y[0]);
    int c = 0;
    int next = 0;

    while(c <= N-1){
        if(next == N-1){
            break;
        }
        next = c + 1;
        plotLine(x[c],y[c],x[next],y[next]);
        c++;
    }

}


void G(){

        plotQuadBezier(20,20,50,0,100,20);
        plotQuadBezier(20,20,0,55,20,120);
        //plotQuadBezier(20,120,60,140,100,120);
        plotQuadBezier(100,120,110,100,100,70);

        //plotLine(20,20,100,20);
        //plotLine(20,20,20,120);
        plotLine(20,120,100,120);
        //plotLine(100,120,100,70);

        //plotLine(100,70,60,70);
        plotQuadBezier(100,70,80,60,60,70);

        plotLine(60,70,60,80);
        plotLine(60,80,90,80);
        plotLine(90,80,90,110);

        plotLine(90,110,30,110);
        plotLine(30,110,30,30);

        plotLine(30,30,100,30);
        plotLine(100,30,100,20);
}
void r(){
        //plotLine(120,70,120,120);
        plotQuadBezier(120,70,110,95,120,120);

        plotLine(120,120,130,120);

        plotLine(130,120,130,80);
        plotLine(130,80,160,80);
        plotLine(160,80,160,70);
        //plotLine(160,70,120,70); //top
        plotQuadBezier(160,70,140,60,120,70);
}
void a(){

        plotLine(180,70,180,80);
        plotLine(180,80,210,80);
        plotLine(210,80,210,90);
        plotLine(210,90,180,90);
        plotLine(180,90,180,120);
        plotLine(180,120,220,120);
        //plotLine(220,120,220,70);
        plotQuadBezier(220,120,230,95,220,70);
        //plotLine(220,70,180,70);
        plotQuadBezier(220,70,200,60,180,70);
}

void p(){
        //plotLine(240,70,280,70);
        plotQuadBezier(240,70,260,60,280,70);

        plotLine(280,70,280,120);
        plotLine(280,120,250,120);
        plotLine(250,120,250,160);
        plotLine(250,160,240,160);
        //plotLine(240,160,240,70);
        plotQuadBezier(240,160,230,115,240,70);

}

void h(){
   plotLine(300,20,310,20);
        plotLine(310,20,310,70);
        plotLine(310,70,350,70);
        plotLine(350,70,350,120);
        plotLine(350,120,340,120);
        plotLine(340,120,340,80);
        plotLine(340,80,310,80);
        plotLine(310,80,310,120);
        plotLine(310,120,300,120);
        plotLine(300,120,300,20);

}

void i(){
     plotLine(370,70,380,70);
        plotLine(380,70,380,80);
        plotLine(380,80,370,80);
        plotLine(370,80,370,70);

        plotLine(370,90,380,90);
        plotLine(380,90,380,120);
        plotLine(380,120,370,120);
        plotLine(370,120,370,90);

}

void c(){
 plotLine(400,70,440,70);
        plotLine(440,70,440,80);
        plotLine(440,80,410,80);
        plotLine(410,80,410,110);
        plotLine(410,110,440,110);
        plotLine(440,110,440,120);
        plotLine(440,120,400,120);
        plotLine(400,120,400,70);

}

void s(){

        plotLine(460,70,500,70);
        plotLine(500,70,500,80);
        plotLine(500,80,470,80);
        plotLine(470,80,470,90);
        plotLine(470,90,500,90);
        plotLine(500,90,500,120);
        plotLine(500,120,460,120);
        plotLine(460,120,460,110);
        plotLine(460,110,490,110);
        plotLine(490,110,490,100);
        plotLine(490,100,460,100);
        plotLine(460,100,460,70);

}



int main(){

/*
    int N = 0;
    cout << "N: ";
    cin >> N;
    cout << endl;

    //SetPixel(mydc, x_centre,y_centre,RGB(255,255,0));

*/

    system("CLS");

    while(true){

        //plotQuadBezierSeg(0,0,50,0,100,100);
        //drawRectangle(x1,y1,x2,y2);
        //drawOval(x,y,r1,r2,midX, midY);
        //drawPolygon(N);

        /*
        plotLine(20,20,100,20);
        plotLine(20,20,20,120);
        plotLine(20,120,100,120);
        plotLine(100,120,100,70);

        plotLine(100,70,60,70);
        plotLine(60,70,60,80);
        plotLine(60,80,90,80);
        plotLine(90,80,90,110);

        plotLine(90,110,30,110);
        plotLine(30,110,30,30);

        plotLine(30,30,100,30);
        plotLine(100,30,100,20);

        //R
        plotLine(120,70,120,120);
        plotLine(120,120,130,120);

        plotLine(130,120,130,80);
        plotLine(130,80,160,80);
        plotLine(160,80,160,70);
        plotLine(160,70,120,70);

        //a
        plotLine(180,70,180,80);
        plotLine(180,80,210,80);
        plotLine(210,80,210,90);
        plotLine(210,90,180,90);
        plotLine(180,90,180,120);
        plotLine(180,120,220,120);
        plotLine(220,120,220,70);
        plotLine(220,70,180,70);


        //p
        plotLine(240,70,280,70);
        plotLine(280,70,280,120);
        plotLine(280,120,250,120);
        plotLine(250,120,250,160);
        plotLine(250,160,240,160);
        plotLine(240,160,240,70);


        //h
        plotLine(300,20,310,20);
        plotLine(310,20,310,70);
        plotLine(310,70,350,70);
        plotLine(350,70,350,120);
        plotLine(350,120,340,120);
        plotLine(340,120,340,80);
        plotLine(340,80,310,80);
        plotLine(310,80,310,120);
        plotLine(310,120,300,120);
        plotLine(300,120,300,20);

        //i
        plotLine(370,70,380,70);
        plotLine(380,70,380,80);
        plotLine(380,80,370,80);
        plotLine(370,80,370,70);

        plotLine(370,90,380,90);
        plotLine(380,90,380,120);
        plotLine(380,120,370,120);
        plotLine(370,120,370,90);

        //c
        plotLine(400,70,440,70);
        plotLine(440,70,440,80);
        plotLine(440,80,410,80);
        plotLine(410,80,410,110);
        plotLine(410,110,440,110);
        plotLine(440,110,440,120);
        plotLine(440,120,400,120);
        plotLine(400,120,400,70);

        //s
        plotLine(460,70,500,70);
        plotLine(500,70,500,80);
        plotLine(500,80,470,80);
        plotLine(470,80,470,90);
        plotLine(470,90,500,90);
        plotLine(500,90,500,120);
        plotLine(500,120,460,120);
        plotLine(460,120,460,110);
        plotLine(460,110,490,110);
        plotLine(490,110,490,100);
        plotLine(490,100,460,100);
        plotLine(460,100,460,70);

        */
        G();
        r();
        a();
        p();
        /*
        h();
        i();
        c();
        s();
        */

        string str;
        getline(cin,str);
        if(!str.empty()){
            exit(0);
        }
    }



    ReleaseDC(myconsole, mydc);

    return 0;
}
