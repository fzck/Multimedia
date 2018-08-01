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


int main(){


    int N = 0;
    cout << "N: ";
    cin >> N;
    cout << endl;

    //SetPixel(mydc, x_centre,y_centre,RGB(255,255,0));



    system("CLS");

    while(true){

        //plotQuadBezierSeg(0,0,50,0,100,100);
        //drawRectangle(x1,y1,x2,y2);
        //drawOval(x,y,r1,r2,midX, midY);

        drawPolygon(N);



        string str;
        getline(cin,str);
        if(!str.empty()){
            exit(0);
        }
    }



    ReleaseDC(myconsole, mydc);

    return 0;
}
