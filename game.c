#include "neslib.h"
#define NTADR_A(x,y) (NAMETABLE_A|(((y)<<5)|(x)))
//exclusivo del archivo, empieza de cero, variable de poca cantidad
static unsigned char pad,spr,xx,yy,cary,buttona,donkeyx,donkeyy,carx,carm,gameover,pathc,c,pos,d0,d1,d2,align;
int i; //was static before
static unsigned char menu;
static unsigned char pressa;
static unsigned char pada;
static unsigned int time;
const unsigned char title[]={
	0x10,0x33,0x32,0x23,0x11,0x25,0x18,0x02,0x01,0x07
};

const unsigned char number[]={
	0x0c,0x27,0x34,0x35,0x36,0x37,0x08,0x09,0x0a,0x0b
};

const unsigned char press_a_scr[]={
	0x04,0x06,0x11,0x07,0x07,0x00,0x01
};

const unsigned char credits1[]={0x33,0x06,0x21,0x13,0x21,0x32,0x01,0x30,0x00,0x02,0x25,0x00,0x02,0x21,0x30,0x30,0x00,0x01,0x32,0x10,0x00,0x32,0x11,0x21,0x30};
const unsigned char credits2[]={0x04,0x21,0x03,0x33,0x00,0x0a,0x00,0x02,0x25,0x00,0x32,0x21,0x14,0x11,0x30,0x21,0x14,0x11};
const unsigned char credits3[]={0x22,0x34,0x31,0x11,0x00,0x02,0x25,0x00,0x06,0x33,0x10,0x06,0x21,0x13,0x33,0x27,0x37,0x0b,0x35};
const unsigned char credits4[]={0x32,0x11,0x07,0x00,0x04,0x33,0x06,0x14,0x00,0x02,0x25,0x00,0x06,0x33,0x10,0x06,0x21,0x13,0x33,0x27,0x37,0x0b,0x35};



const unsigned char gameovertext[]={
	0x13,0x01,0x31,0x11,0x00,0x33,0x16,0x11,0x06
};

const unsigned char exampletext[]={0x20,0x11,0x30,0x30,0x33,0x00,0x17,0x33,0x06,0x30,0x10};


//creando un arreglo de registro
//x,y,tile,colour


const unsigned char spr0[]={ //TITLE CAR
0,0,0x45,1, //0x45,0x44
8,0,0x44,1,
16,0,0x45,1,
8,8,0x44,1,
0,16,0x45,1,
8,16,0x44,1,
16,16,0x45,1,
128
};

const unsigned char spr1[]={//PLAYER CAR
0,0,0x46,1,
8,0,0x44,1,
16,0,0x47,1,
0,8,0x44,1,
8,8,0x44,1,
16,8,0x44,1,
0,16,0x45,1,
16,16,0x45,1,
128
};


const unsigned char spr2[]={//DONKEY
0,0,0x44,0,
8,0,0x44,0,
16,0,0x40,0,
0,8,0x54,0,
16,8,0x54,0,
128
};

const unsigned char path[]={
	0x2a,0x2b,0x3a,0x3b,0x19
};
const unsigned char spr3[]={//PATH
0,0,0x19,2,
8,0,0x1a,2,
16,0,0x1b,2,
24,0,0x1c,2,

0,8,0x29,2,
8,8,0x3a,2,
16,8,0x3b,2,
24,8,0x3c,2,

0,16,0x39,2,
8,16,0x3a,2,
16,16,0x3b,2,
24,16,0x3c,2,

0,24,0x49,2,
8,24,0x4a,2,
16,24,0x4b,2,
24,24,0x4c,2,

0,32,0x59,2,
8,32,0x5a,2,
16,32,0x5b,2,
24,32,0x5c,2,

0,40,0x69,2,
8,40,0x6a,2,
16,40,0x6b,2,
24,40,0x6c,2,

0,48,0x79,2,
8,48,0x7a,2,
16,48,0x7b,2,
24,48,0x7c,2,

0,56,0x89,2,
8,56,0x8a,2,
16,56,0x8b,2,
24,56,0x8c,2,

0,64,0x99,2,
8,64,0x9a,2,
16,64,0x9b,2,
24,64,0x9c,2,
128

};

const unsigned char map_game_map[240] = {
0, 0, 0, 0, 15, 14, 15, 0, 15, 14, 15, 0, 0, 0, 0, 0
,
0, 77, 0, 0, 15, 14, 15, 0, 15, 14, 15, 0, 0, 0, 0, 0
,
0, 0, 0, 0, 15, 14, 15, 0, 15, 14, 15, 0, 0, 0, 0, 0
,
0, 0, 0, 0, 15, 14, 15, 0, 15, 14, 15, 0, 0, 0, 0, 0
,
0, 0, 0, 0, 15, 14, 15, 0, 15, 14, 15, 0, 0, 0, 0, 0
,
0, 0, 0, 0, 15, 14, 15, 0, 15, 14, 15, 0, 0, 0, 0, 0
,
0, 0, 0, 0, 15, 14, 15, 0, 15, 14, 15, 0, 0, 0, 0, 0
,
0, 0, 0, 0, 15, 14, 15, 0, 15, 14, 15, 0, 0, 0, 0, 0
,
0, 0, 0, 0, 15, 14, 15, 0, 15, 14, 15, 0, 0, 0, 0, 0
,
0, 0, 0, 0, 15, 14, 15, 0, 15, 14, 15, 0, 0, 0, 0, 0
,
0, 0, 0, 0, 15, 14, 15, 0, 15, 14, 15, 0, 0, 0, 0, 0
,
0, 0, 0, 0, 15, 14, 15, 0, 15, 14, 15, 0, 0, 0, 0, 0
,
0, 0, 0, 0, 15, 14, 15, 0, 15, 14, 15, 0, 0, 0, 0, 0
,
0, 0, 0, 0, 15, 14, 15, 0, 15, 14, 15, 0, 0, 0, 0, 0
,
0, 0, 0, 0, 15, 14, 15, 0, 15, 14, 15, 0, 0, 0, 0, 0

};


//const unsigned char green_palette[8]={ //gameover pallete
	//0x0a,0x00,0x0a,0x0a, //0x20 //0x0f,0x06,0x15,0x36
	//0x0a,0x0a,0x0a,0x20
//};

const unsigned char palette[8]={ //background pallete
	0x0a,0x00,0x10,0x20,//0x0f,0x06,0x15,0x36
	0x0f,0x20,0xa,0x00 
}; //bg palette backup



const unsigned char bpalette[8]={ //background pallete
	0x10,0x20,0x0a,0x00,//0x0f,0x06,0x15,0x36
	0x0a,0x20,0x10,0x00
};

/*const unsigned char bpalette[8]={ //background pallete
	0x0a,0x0a,0x0a,0x2a,//0x0f,0x06,0x15,0x36
	0x0a,0x0a,0x0a,0x2a
};*/

const unsigned char paletto[16]={//spr pallete
	0x15,0x2d,0x25,0x1c, //donkey pallete
	0x0f,0x06,0x15,0x36, //title & car pallete
	0x0f,0x30,0x10,0x00, //terrain pallete (not made yet)
	0x0f,0x06,0x15,0x36 
};

void clear(){
	for(i=0;i<928;i++){ //1024 is funny bc it draws a nice floor decoration xdxxncsadfndhiufhn
	vram_adr(0x2000+i);
	vram_put(0x44);//29 before
	}

	};
	
void draw_green(){
	for(i=0;i<928;i++){
	vram_adr(0x2000+i);
	vram_put(0x00);
	}

	
};

void donkey_randomx(){
//for(i=0;i<carm+time;i++){
pos=rand8();
if (pos<=128){donkeyx=68+align;}else{donkeyx=132+align;}//if (time==0){donkeyx=68;}else{donkeyx=132;};if (time==1){donkeyx=132;}else{donkeyx=68;} //25 value //if (donkeyx < 100){donkeyx=132;}else{donkeyx=68;};
	//if (carm>2){carm=carm/2;}
	//if (i>=carm+time){time=carm/2;}
	//if (carm>=7){carm-=3;}else{carm-=1;}
//}
}

void draw_path(){
	ppu_off();
	//clear();
	draw_green();
	pal_bg(bpalette);
	clear();
		for (i=0;i<240;++i)//Empieza a calcular todo el mapa para dibujar los bloques
	{
		
		//sfx_play(1,0);
		if (map_game_map[i]==14)//si en el cuadro indicado esta un bloque entonces que lo dibuje
		{			// 0x2000 es el inicio de la pantalla. (i<<1)
		
			vram_adr(0x2000+(i<<1)+((i>>4)<<5)); 	  vram_put(path[0]);
			vram_adr(0x2000+((i<<1)+1)+((i>>4)<<5));  vram_put(path[1]);
			vram_adr(0x2000+((i<<1)+32)+((i>>4)<<5)); vram_put(path[2]);
			vram_adr(0x2000+((i<<1)+33)+((i>>4)<<5)); vram_put(path[3]);
		}
		
		
		
		if (map_game_map[i]==15)//si en el cuadro indicado esta un bloque entonces que lo dibuje
		{			// 0x2000 es el inicio de la pantalla. (i<<1)
		
		vram_adr(0x2000+(i<<1)+((i>>4)<<5)); 	  vram_put(path[4]);
		vram_adr(0x2000+((i<<1)+1)+((i>>4)<<5));  vram_put(path[4]);
		vram_adr(0x2000+((i<<1)+32)+((i>>4)<<5)); vram_put(path[4]);
		vram_adr(0x2000+((i<<1)+33)+((i>>4)<<5)); vram_put(path[4]);
		}
		

//		}
	ppu_on_all();
	
}

}

void draw_game_over(){
	ppu_off();
	
	//oam_clear();
	clear();
	
	for(i=0;i<sizeof(credits1)/sizeof(credits1[0]);i++){
		
	vram_adr(NTADR_A(i,5));
	vram_put(credits1[i]);
		
	}
	
		for(i=0;i<sizeof(credits2)/sizeof(credits2[0]);i++){
		
	vram_adr(NTADR_A(i,10));
	vram_put(credits2[i]);
		
	}
	
		for(i=0;i<sizeof(credits3)/sizeof(credits3[0]);i++){
		
	vram_adr(NTADR_A(i,15));
	vram_put(credits3[i]);
		
	}
	
		for(i=0;i<sizeof(credits4)/sizeof(credits4[0]);i++){
		
	vram_adr(NTADR_A(i,20));
	vram_put(credits4[i]);
		
	}
	
	for(i=0;i<sizeof(gameovertext)/sizeof(gameovertext[0]);i++){
	vram_adr(NTADR_A(i+10,2));
	vram_put(gameovertext[i]);
	}
	
	
	
	//for(i=0;i<120;i++){ //240
	//vram_adr(0x2000+(i<<1)+((i>>4)<<5));vram_put(0x00);
	//}
	
	ppu_on_all();
}

void add_number(){
	d0+=1;
	if (menu==2){
		d0=0;d1=0;d2=0;
	}
	if (d0>=10 && d1>=10){d2+=1;d1=0;d0=0;}
	if (d0>=10){d1+=1;d0=0;}
	
	ppu_off();
		vram_adr(0x2217);vram_put(number[d2]);
		vram_adr(0x2218);vram_put(number[d1]);
		vram_adr(0x2219);vram_put(number[d0]);
		ppu_on_all();
	
}

void main(void)
	{
	//SET THE ALIGNMENT FOR THE CAR AND DONKEY OBJECTS
	align=8;
		
	pada=0;
	pressa=0;
	menu=0;
	pal_spr(paletto);
	//pal_bg(palette); //pal_col(0,0x0a);//
	pal_bg(bpalette);
	xx=68+align;//100+32 to get the right position since we have the left position already
	yy=172;
	sfx_play(0,0);
	//set_vram_update(NULL);
	spr=0;
	carx=68+align;
	cary=140;
	donkeyx=68+align;
	donkeyy=0;
	carm=0;
	gameover=0;
	pathc=0;
	
	//just for view those draw patterns with vram
	c=0;
	/*	for (i=0;i<240;++i)//Empieza a calcular todo el mapa para dibujar los bloques
	{
		if (nivel1_map[i]==33)//si en el cuadro indicado esta un bloque entonces que lo dibuje
		{			// 0x2000 es el inicio de la pantalla. (i<<1)
			vram_adr(0x2000+(i<<1)+((i>>4)<<5)); 	  vram_put(metatile_bg[0]);
			vram_adr(0x2000+((i<<1)+1)+((i>>4)<<5));  vram_put(metatile_bg[1]);
			vram_adr(0x2000+((i<<1)+32)+((i>>4)<<5)); vram_put(metatile_bg[2]);
			vram_adr(0x2000+((i<<1)+33)+((i>>4)<<5)); vram_put(metatile_bg[3]);
		}
	}
	*/
	c=0;
	time=0;
	clear();
	ppu_on_all();
	//clear();
	pos=0;
	d0=0;
	d1=0;
	d2=0;
	while(1){
		//ppu_wait_frame();
		 //	spr=oam_spr(xx+8,yy,spr0[1],0,spr);spr=oam_spr(xx+16,yy,spr0[0],0,spr);spr=oam_spr(xx+8,yy+8,spr0[1],0,spr);spr=oam_spr(xx,yy+16,spr0[0],0,spr);spr=oam_spr(xx+8,yy+16,spr0[1],0,spr);spr=oam_spr(xx+16,yy+16,spr0[0],0,spr);
		time+=1;
		
		if (time >=254){time=0;}
		//if (time==0){time=1;}else{time=0;}
		
		switch(menu){
		case 0:
		spr=oam_meta_spr(carx,cary,spr,spr1);
		carx+=1;
		//if (carx>230){
		//	carx=0;
		//}
		pressa+=1;
		
		if (pressa>50){
		pressa=0;
		}
		
		for(i=0;i<10;i++){
		//generate that PATH terrain

		
		spr=oam_spr(100+8*i,10,title[i],1,spr);
		
		if (i<7 && pressa>25){
		spr=oam_spr(120+8*i,40,press_a_scr[i],1,spr);
		}
		
		};		
		
		if (pad&PAD_A){
			//sfx_play(-1,3);
			pal_col(0,0x2a);
			sfx_play(1,0);
			//seed_rng();
			carm=1;
			set_rand(time);
			donkey_randomx();
			draw_path();
			menu=1;
		}
		
		break;
		
		case 1:
		
		pathc+=1;
		if (pathc>=20){
			pathc=0;
		}
		
		donkeyy+=3;
		if (donkeyy>yy && donkeyy<yy+24 && donkeyx==xx){gameover=50;sfx_play(2,0);draw_game_over();menu=2;}
		if (donkeyy>=240){sfx_play(1,0);add_number();carm+=3;donkey_randomx();donkeyy=0;}
		spr=oam_meta_spr(xx,yy,spr,spr0);
		spr=oam_meta_spr(donkeyx,donkeyy,spr,spr2);
		spr=oam_meta_spr(donkeyx,donkeyy,spr,spr2);
		spr=oam_meta_spr(donkeyx,donkeyy,spr,spr2);
		spr=oam_meta_spr(donkeyx,donkeyy,spr,spr2);
		spr=oam_meta_spr(donkeyx,donkeyy,spr,spr2);
		spr=oam_meta_spr(donkeyx,donkeyy,spr,spr2);
		if (pad&PAD_A && !pada){
		if (xx<100){xx=132+align;}else{xx=68+align;} //time+=3;
		pada=1;
		}
		
		if (!pad&PAD_A){
		pada=0;
		}
		
		
		break;
		
		case 2:
		
		
		if (gameover>0){
		gameover-=1;
		
		}
		
		if (pad&PAD_A && gameover<=0){donkey_randomx();sfx_play(1,0);donkeyy=0;add_number();draw_path();menu=1;}//pal_bg(palette);
		break;
		};
		pad=pad_poll(0);
		
		//p+=1;
		ppu_wait_nmi();
		oam_hide_rest(spr);
	}
	
}

