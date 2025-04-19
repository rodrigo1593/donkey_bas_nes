// Funciones dependientes del hardware de NES programadas por Shiru (shiru@mail.ru)
// Siéntanse libres de hacer lo que quieran con este código, considérenlo Dominio público

// establece las paletas del fondo y los sprites, los datos son una matriz de 32 bytes

void __fastcall__ pal_all(const char *data);

// establece solo la paleta de colores del fondo, los datos son una matriz de 16 bytes

void __fastcall__ pal_bg(const char *data);

// establecer solo la paleta de colores de los sprites, los datos son una matriz de 16 bytes

void __fastcall__ pal_spr(const char *data);

// establece una entrada de la paleta de colores, el índice es 0..31

void __fastcall__ pal_col(unsigned char index,unsigned char color);

// restablecer la paleta de colores a $ 0f ( 15 en sistema hexadecimal)

void __fastcall__ pal_clear(void);

// establece el brillo virtual tanto para los sprites como para el fondo, 0 es negro, 4 es normal, 8 es blanco

void __fastcall__ pal_bright(unsigned char bright);

// establecer brillo virtual solo para los sprites

void __fastcall__ pal_spr_bright(unsigned char bright);

// establecer brillo virtual solo para fondo de los sprites

void __fastcall__ pal_bg_bright(unsigned char bright);



// Espera al siguiente fotograma de TV en tiempo real, 50 Hz para PAL, 60 Hz para NTSC

void __fastcall__ ppu_wait_nmi(void);

// espera el marco virtual, siempre es de 50 Hz, marco a marco en PAL, salto de marcos en NTSC

void __fastcall__ ppu_wait_frame(void);

// apaga el renderizado, nmi sigue habilitado cuando el renderizado está deshabilitado

void __fastcall__ ppu_off(void);

// enciende la visualizacion del fondo y los sprites

void __fastcall__ ppu_on_all(void);

// enciende solo la visualizacion del fondo

void __fastcall__ ppu_on_bg(void);

// enciende solo la visualizacion de los sprites

void __fastcall__ ppu_on_spr(void);

// establece la PPU_MASK directamente

void __fastcall__ ppu_mask(unsigned char mask);

// obtiene el sistema de video actual, 0 para PAL, no 0 para NTSC

unsigned char __fastcall__ ppu_system(void);



// borra el búfer OAM ocultando todos los sprites

void __fastcall__ oam_clear(void);

// establece el modo de visualización de sprites, 0 para sprites de 8x8, 1 para sprites de 8x16

void __fastcall__ oam_size(unsigned char size);

// establece el sprite en el búfer OAM, chrnum es el tile, attr es atributo, sprid está compensado en OAM en bytes
// devuelve sprid + 4, que está compensado por un siguiente sprite

unsigned char __fastcall__ oam_spr(unsigned char x,unsigned char y,unsigned char chrnum,unsigned char attr,unsigned char sprid);

// Establece el metasprite en el búfer OAM
// metasprite es una matriz de caracteres sin signo constante, contiene cuatro bytes por sprite
// por orden: desplazamiento x, desplazamiento y, tile, atributo
// x = 128 representa el final de un metasprite
// Devuelve sprid + 4, que está compensado por un siguiente sprite


unsigned char __fastcall__ oam_meta_spr(unsigned char x,unsigned char y,unsigned char sprid,const unsigned char *data);

// oculta todos los sprites restantes del desplazamiento dado

void __fastcall__ oam_hide_rest(unsigned char sprid);



// reproduce una música en formato FamiTone

void __fastcall__ music_play(unsigned char song);

// detiene la musica

void __fastcall__ music_stop(void);

// pausa y reanuda la música

void __fastcall__ music_pause(unsigned char pause);

// reproduce el efecto de sonido FamiTone en el canal 0..3

void __fastcall__ sfx_play(unsigned char sound,unsigned char channel);

// reproduce una muestra DPCM, 1..63

void __fastcall__ sample_play(unsigned char sample);



// inicia el controlador de encuesta y banderas de retorno como PAD_LEFT, etc.,
//la entrada es el número de pad (0 para el jugador 1 y 1 para el jugador 2)

unsigned char __fastcall__ pad_poll(unsigned char pad);

// inicia el controlador de encuesta en modo de disparo, una bandera se establece solo al presionar el botón, no al mantenerlo presionado
// si necesita sondear el pad en modo normal y disparador, sondearlo en el
// modo de activación para primero, luego use pad_state

unsigned char __fastcall__ pad_trigger(unsigned char pad);

// obtiene el estado anterior del pad sin puertos de sondeo

unsigned char __fastcall__ pad_state(unsigned char pad);


// establece el desplazamiento, incluidos los bits superiores
// siempre se aplica al comienzo de un cuadro de pantalla de TV, no en la llamada a la función

void __fastcall__ scroll(unsigned int x,unsigned int y);

// establece el desplazamiento después de la división de pantalla invocada por el sprite 0 hit
// advertencia: ¡todo el tiempo de la CPU entre la llamada a la función y el punto de división real se desperdiciará!
// advertencia: el ciclo del programa debe encajar en el tiempo del marco, no se debe utilizar ppu_wait_frame
// de lo contrario, se insertarán marcos vacíos sin división, lo que dará como resultado una pantalla con saltos
// advertencia: solo el desplazamiento X se puede cambiar en esta versión

void __fastcall__ split(unsigned int x,unsigned int y);


// selecciona el banco chr actual para los sprites, 0..1

void __fastcall__ bank_spr(unsigned char n);

// seleccionar el banco chr actual para el fondo, 0..1

void __fastcall__ bank_bg(unsigned char n);



// obtiene un número aleatorio entre 0..255 o entre 0..65535

unsigned char __fastcall__ rand8(void);
unsigned int  __fastcall__ rand16(void);

// establece el rango aleatorio

void __fastcall__ set_rand(unsigned int seed);



// cuando la visualización está habilitada, el acceso a vram solo se puede realizar con este sistema de actualización de vram
// la función establece un puntero al búfer de actualización que contiene datos y direcciones
// en un formato especial. Permite escribir bytes no secuenciales, así como horizontales o
// secuencias verticales de tablas de nombres.
// El puntero del búfer se puede cambiar durante el renderizado, pero solo tiene efecto en un nuevo marco
// el número de bytes transferidos está limitado por el tiempo vblank
// para deshabilitar las actualizaciones, llame a esta función con el puntero NULL

// el formato de datos de actualización es el siguiente:
// MSB, LSB, byte para una escritura no secuencial
// MSB | NT_UPD_HORZ, LSB, LEN, [bytes] para una secuencia horizontal
// MSB | NT_UPD_VERT, LSB, LEN, [bytes] para una secuencia vertical
// NT_UPD_EOF para marcar el final del búfer

// la longitud de estos datos debe ser inferior a 256 bytes

void __fastcall__ set_vram_update(unsigned char *buf);

// todas las siguientes funciones de vram solo funcionan cuando la pantalla está deshabilitada

// realiza una serie de escrituras en VRAM, el mismo formato que para set_vram_update, pero las escrituras se realizan de inmediato

void __fastcall__ flush_vram_update(unsigned char *buf);

// establece el puntero de vram para escribir operaciones si necesitas escribir algunos datos en vram

void __fastcall__ vram_adr(unsigned int adr);

// coloca un byte en la dirección de vram actual, funciona solo cuando el renderizado está desactivado

void __fastcall__ vram_put(unsigned char n);

// llena un bloque con un byte en la dirección de vram actual, funciona solo cuando el renderizado está desactivado

void __fastcall__ vram_fill(unsigned char n,unsigned int len);

// establece el autoincremento de vram, 0 para +1 y no 0 para +32

void __fastcall__ vram_inc(unsigned char n);

// lee un bloque de la dirección actual de vram, funciona solo cuando el renderizado está desactivado

void __fastcall__ vram_read(unsigned char *dst,unsigned int size);

// escribe un bloque en la dirección actual de vram, funciona solo cuando el renderizado está desactivado

void __fastcall__ vram_write(unsigned char *src,unsigned int size);


// descomprime los datos RLE en la dirección actual de vram, que se usa principalmente para tablas de nombres

void __fastcall__ vram_unrle(const unsigned char *data);



// como una memcpy normal, pero no devuelve nada

void __fastcall__ memcpy(void *dst,void *src,unsigned int len);

// como memset, pero no devuelve nada

void __fastcall__ memfill(void *dst,unsigned char value,unsigned int len);

// retraso para N fotogramas

void __fastcall__ delay(unsigned char frames);



#define PAD_A			0x01
#define PAD_B			0x02
#define PAD_SELECT		0x04
#define PAD_START		0x08
#define PAD_UP			0x10
#define PAD_DOWN		0x20
#define PAD_LEFT		0x40
#define PAD_RIGHT		0x80

#define OAM_FLIP_V		0x80
#define OAM_FLIP_H		0x40
#define OAM_BEHIND		0x20

#define MAX(x1,x2)		((x1)<(x2)?(x2):(x1))
#define MIN(x1,x2)		((x1)<(x2)?(x1):(x2))

#define MASK_SPR		0x10
#define MASK_BG			0x08
#define MASK_EDGE_SPR	0x04
#define MASK_EDGE_BG	0x02

#define NAMETABLE_A		0x2000
#define NAMETABLE_B		0x2400
#define NAMETABLE_C		0x2800
#define NAMETABLE_D		0x2c00

#define NULL			0
#define TRUE			1
#define FALSE			0

#define NT_UPD_HORZ		0x40
#define NT_UPD_VERT		0x80
#define NT_UPD_EOF		0xff

// macro para calcular la dirección de la tabla de nombres de X, Y en tiempo de compilación

#define NTADR_A(x,y) 	(NAMETABLE_A|(((y)<<5)|(x)))
#define NTADR_B(x,y) 	(NAMETABLE_B|(((y)<<5)|(x)))
#define NTADR_C(x,y) 	(NAMETABLE_C|(((y)<<5)|(x)))
#define NTADR_D(x,y) 	(NAMETABLE_D|(((y)<<5)|(x)))

// macro para obtener MSB y LSB

#define MSB(x)			(((x)>>8))
#define LSB(x)			(((x)&0xff))