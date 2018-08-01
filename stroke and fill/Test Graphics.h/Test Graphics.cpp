#include<graphics.h>
#include<conio.h>
#include<dos.h>
#include<iostream>

using namespace std;

int main()
{
    // gm is Graphics mode which is a computer display
    // mode that generates image using pixels.
    // DETECT is a macro defined in "graphics.h" header file
    int gd = DETECT, gm;
 
    // location of left, top, right, bottom
    int x1 = 0, y1 = 0;
    int x2 = 200, y2 = 150;
 
    // initgraph initializes the graphics system
    // by loading a graphics driver from disk
    initgraph(&gd, &gm, NULL);
 
  	int ax = 100, ay = 0;
  	
  	int bx = 0, by = 0;
  	int cx = 0, cy = 90;
  	int dx = 30, dy = 60;
  	int ex = 50, ey = 40;
  	int fx = 70, fy = 20;
	int gx = 70, gy = 60;
	int hx = 50,hy = 40;
	int hx2 = 31, hy2 = 60;
	int ix = 30, iy = 20;
	int jx = 30, jy = 100;
	int kx = 100, ky = 100;
	 
	int gap1 = 20;
	int gap2 = 10;
	int gap3= 11;
  	
  	line(ax,ay,bx,by);	
	
	
	line(bx,by,cx,cy);
	
	
	line(cx,cy,dx,dy);

	
	line(dx,dy,ex,ey);

	
	line(ex,ey,fx,fy);

	
	line(fx,fy,gx,gy);
	
	
	line(gx,gy,hx,hy);


	line(hx,hy,ix,iy);
	
	
	line(ix,iy,jx,jy);

	
	line(jx,jy,kx,ky);
	
	
	line(kx,ky,ax,ay);

	
	int tax = ax, tay = ay;
	int tbx = bx, tby = by;
	int tcx = cx, tcy = cy;
	int tdx = dx, tdy = dy;
	int tex = ex, tey = ey;
	int tfx = fx, tfy = fy;
	int tgx = gx, tgy = gy;
	int thx = hx, thy = hy;
	int thx2 = hx2, thy2 = hy2;
	int tix = ix, tiy = iy;
	int tjx = jx, tjy = jy;
	int tkx = kx, tky = ky;
	
	
	
	
	int rax = ax, ray = ay;
	int rbx = bx, rby = by;
	int rcx = cx, rcy = cy;
	int rdx = dx, rdy = dy;
	int rex = ex, rey = ey;
	int rfx = fx, rfy = fy;
	int rgx = gx, rgy = gy;
	int rhx = hx, rhy = hy;
	int rix = ix, riy = iy;
	int rjx = jx, rjy = jy;
	int rkx = kx, rky = ky;
	


	int  ctr = 0;
	while(ctr < gap1){

	line(tax,tay,tbx,tby);
	line(tbx,tby,tcx,tcy);
	line(tcx,tcy,tdx,tdy);
	
	setcolor(GREEN);	
	line(rdx+1,rdy-1,tex,tey);
	line(tex,tey,tfx,tfy);
	line(rfx,rfy,tgx,tgy);
	line(rgx,rgy,thx,thy);
	line(tex,tey,tix,tiy);
	line(tix+1,tiy,thx2+1,thy2-1);
	
	setcolor(WHITE);
	line(thx2,thy2,tjx,tjy);
	line(tjx,tjy,tkx,tky);
	line(tkx,tky,rax,ray);
	tax--;
	tay++;
	tbx++;
	tby++;
	tcx++;
	tcy--;
	tdy--;

	rdy--;
	tfy++;
	rfx--; 
	rfy++;
	tgx--;
	tgy--;
	rgx--;
	rgy--; 
	thx++; 
	thy--;
	tiy++;
	rix++;	
	thx2++;
	thy2--;
	tjx++; tjy--;
	tkx--;tky--;
	rax--; ray++;
	
	ctr++;
	
	Sleep(10);
}


	setcolor(WHITE);
	line(tax,tay,tbx,tby);
	
	int tax_ = fx-1;
	int tay_ = fy;
	int tbx_ = ix+1;
	int tby_ = iy;
	int tdx_ = ex;
	int tdy_ = ey-1;
	int tdy2_ = ey-1;
	int tex_ = fx+1;
	int tey_ = fy;
	int tfx_ = gx+1;
	int tfy_ = gy+1;
	int c = 0;
	int d = 0;
	
	while (c < gap1){
	
		line(tax_,tay_,tbx_,tby_);
		line(tbx,tby,tcx,tcy);
		line(tcx,tcy,tdx,tdy);
		line(tdx_,tdy_,tax_,tay_);	
		line(tex_,tey_,tfx_,tfy_);
		line(tfx_,tfy_,tdx_,tdy2_+1);	
		line(tdx_,tdy_,tbx_,tby_);	
		line(tjx,tjy,tkx,tky);
		line(tkx,tky,rax,ray);
	
		tbx_++;
		tax_--;
		tdy2_++;
		c++;
		
		Sleep(10);

	
	}

	
	int x = 0;
	while(x < gap2){
		line(tax_,tay_,tbx_,tby_);
		line(tbx,tby,tcx,tcy);
		line(tcx,tcy,tdx,tdy);
		line(tdx_,tdy_,tax_,tay_);
		line(tex_,tey_,tfx_,tfy_);
		line(tfx_,tfy_,tdx_,tdy2_);	
		line(tdx_,tdy_,tbx_,tby_);
		line(tjx,tjy,tkx,tky);	
		tbx++; 
		tcx++;
		tcy--;
		tjy--;
		tky--;
	//line(tkx,tky,rax,ray-1);
	//rax--;
	
	
		x++;
			Sleep(10);
	}

	
	int i = 0;
	while(i < gap3){
		line(tax_,tay_,tbx_,tby_);
		line(tbx,tby,tcx,tcy);
		line(tcx,tcy,tdx,tdy);
		line(tdx_,tdy_,tax_,tay_);
		line(tex_,tey_,tfx_,tfy_);
		line(tfx_,tfy_,tdx_,tdy2_);	
		line(tdx_,tdy_,tbx_,tby_);
		line(tjx,tjy,tkx,tky);	
		line(tkx,tky,rax,ray);
		rax--;
		tkx--;
		tjy--;
		tky--;
		i++;
		
			Sleep(10);
		
	}



    getch();
 
    // closegraph function closes the graphics
    // mode and deallocates all memory allocated
    // by graphics system .
    closegraph();
 
    return 0;
}
