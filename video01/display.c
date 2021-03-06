#include "display.h"
#include "functions.h"
#include "vectors.h"
#include "io.h"

int abs(int a){
	if(a >=0){return a;}
	else {return -a;}
}
static inline unsigned int min(unsigned int a, unsigned int b, unsigned int c)
{
    unsigned int m = a;
    if (m > b) m = b;
    if (m > c) m = c;
    return m;
}
static inline unsigned int max(unsigned int a, unsigned int b, unsigned int c)
{
    unsigned int m = a;
    if (m < b) m = b;
    if (m < c) m = c;
    return m;
}


void inline setPixel(int x,int y, int color, int fb){
	if(x<640 && y<480){
	int offset;
	offset = GET32(0x40040020);
	offset += (x + (y*640))<<1;	
	if (fb) offset += 614400;
	color = color & 0xFFFF;
	PUT16(offset, color);
	}
}
void drawLine(int x0, int y0, int x1, int y1, unsigned int color, int fb) {
	if(x0 > 640){x0-=640;}
	if(x1 > 640){x1-=640;}
	if(y0 > 480){y0-=480;}
	if(y1 > 480){y1-=480;}
		int dx,dy,sx,sy,err,e2;
		dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
		dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
		err = (dx>dy ? dx : -dy)/2;

		for(;;){
			setPixel(x0,y0,color, fb);
			if (x0==x1 && y0==y1) break;
			e2 = err;
			if (e2 >-dx) { err -= dy; x0 += sx; }
			if (e2 < dy) { err += dx; y0 += sy; }
		}
	
}

/*void drawFilledRect(int x, int y, int width, int height, int color, int fb){
	unsigned int i,j;
	
		for(j= y+height; j >= y; j--){
			for(i= x+width; i>= x; i--){
				setPixel(i,j,color, fb);
			}
		}
	
	

}*/
void drawFastFilledRect(int x, int y, int width, int height, int color, int fb){
	int i,j,address;
	address = GET32(0x40040020);
	if (fb) address += 614400;
	address += (x+(y*640))<<1;
	
	for(j=y; j<y+height;j++){
		for(i=x;i<x+width;i++){
			PUT16(address,color);
			address +=2;
		}
	address += 1280 - (width<<1);
	}
}
void drawRect(int x, int y, int width, int height, int color, int fb){
	int i,address;
	address = GET32(0x40040020);
	if (fb) address += 614400;
	address += (x+(y*640)) <<1;
	
	for(i = x; i<x+width;i++){
		PUT16(address,color);
		address +=2;
	}
	address = GET32(0x40040020);
	address += (x+((y+height)*640)) <<1;
	for(i = x; i<=x+width;i++){
		PUT16(address,color);
		address +=2;
	}
	address = GET32(0x40040020);
	address += (x+(y*640)) <<1;
	for(i=y; i<y+height; i++){
		PUT16(address,color);
		address += 1280; //640 * length of color (2)
	}
	address = GET32(0x40040020);
	address += ((x+width)+(y*640)) <<1;
	for(i=y; i<=y+height; i++){
		PUT16(address,color);
		address += 1280; //640 * length of color (2)
	}
}
void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int color){
	x1 = x1 & 1023;
	x2 = x2 & 1023;
	x3 = x3 & 1023;
	y1 = y1 & 511;
	y2 = y2 & 511;
	y3 = y3 & 511;
	if(x1 >= 640) x1-=640;
	if(x2 >= 640) x2-=640;
	if(x3 >= 640) x3-=640;
	if(y1 >= 480) x1-=480;
	if(y2 >= 480) x1-=480;
	if(y3 >= 480) x1-=480;
	color = color &0xFFFF;
	int ymax,ymin,xmax,xmin;
    xmin = min(x1,x2,x3);
    xmax = max(x1,x2,x3);
    ymin = min(y1,y2,y3);
    ymax = max(y1,y2,y3);
    int y12,y23,y31;
	y12 = y1-y2;
	y23 = y2-y3;
	y31 = y3-y1;
	int x12,x23,x31;
	x12 = x1-x2;
	x23 = x2-x3;
	x31 = x3-x1;
    int c1, c2,c3;
    c1 = y12 * x1 - x12 * y1;
    c2 = y23 * x2 - x23 * y2;
    c3 = y31 * x3 - x31 * y3;
    int cy1, cy2, cy3;
    cy1 = c1 + x12 * ymin - y12 * xmin;
    cy2 = c2 + x23 * ymin - y23 * xmin;
    cy3 = c3 + x31 * ymin - y31 * xmin;
    int i,j, cx1, cx2, cx3;
    int address;
    address = GET32(0x40040020);
	address += (xmin+(ymin*640)) <<1;
	int dx;
	dx = 1280-((xmax-xmin)<<1);
    for(j = ymax-ymin; j!=0; j--){
    	cx1 = cy1;
    	cx2 = cy2;
    	cx3 = cy3;
    	for(i = xmax-xmin; i!=0; i--){
    		if(cx1 >=0 && cx2 >=0 && cx3 >0){
    			PUT16(address,color);
    		}
    		address += 2;
    		cx1 -= y12;
    		cx2 -= y23;
    		cx3 -= y31;
    		
    	}
    	address += dx;
    cy1 += x12;
    cy2 += x23;
    cy3 += x31;
    }
}
