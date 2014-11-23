void drawChar(char c, int x, int y){
	if(c == '\x7f'){
		int x0,y0;
		delChar(x,y);
	}
	else DrawChar(c,x,y);
}
void delChar(int x, int y){
	int x0,y0;
	for(x0=x; x0<(x+8);x0++){
		for(y0=y; y0<(y+16);y0++){
			setPixel(x0,y0,0x0000);
		}
	}
}

void drawString(char str[], int x, int y){
	int x1,i;
	x1 = x;
	
	i = 0;
	while(str[i] != '\0'){
		if(str[i] == '\n'){
			x = x1;
			y += 16;
		}
		else{
			DrawChar(str[i], x,y);
			x+=8;
		}
		i++;
	}
}
