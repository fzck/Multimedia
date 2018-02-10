
#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <iostream>
#include <cmath>
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


int main(){

    double x1, y1, x2, y2, r1, r2;

    cout << "x1: ";
    cin >> x1;
    cout << endl;
    cout << "y1: ";
    cin >> y1;
    cout << endl;
    cout << "x2: ";
    cin >> x2;
    cout << endl;
    cout << "y2: ";
    cin >> y2;
    cout << endl;
    cout << "r1: ";
    cin >> r1;
    cout << endl;
    cout << "r2: ";
    cin >> r2;
    cout << endl;


    double x = min(x1,x2);
    double y = min(y1,y2);
    double midX = (x1+x2)/2, midY = (y1+y2)/2;

    system("CLS");

    while(true){

        drawRectangle(x1,y1,x2,y2);
        drawOval(x,y,r1,r2,midX, midY);

        string str;
        getline(cin,str);
        if(!str.empty()){
            exit(0);
        }
    }

    ReleaseDC(myconsole, mydc);

    return 0;
}
