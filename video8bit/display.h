/* display.c */
int abs(int a);
void drawLine(int x0, int y0, int x1, int y1, unsigned int color, int fb);
void drawFastFilledRect(int x, int y, int width, int height, int color, int fb);
void drawRect(int x, int y, int width, int height, int color, int fb);
void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int color);
