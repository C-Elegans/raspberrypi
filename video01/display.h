/* display.c */
void setPixel(int x, int y, int color);
void drawLine(int x0, int y0, int x1, int y1, unsigned int color);
void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int color);
void drawRect(int x, int y, int width, int height, int color);
void drawFilledRect(int x, int y, int width, int height, int color);
void drawFastFilledRect(int x, int y, int width, int height, int color);
extern int multiplylookup[640];
