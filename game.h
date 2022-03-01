/* Declare display-related functions from displayFunctions.c */
void display_image(int x, const uint8_t *data);
void display_init(void);
void display_string(int line, char *s);
void display_update(void);
uint8_t spi_send_recv(uint8_t data);
void quicksleep(int cyc);
void setup( void );
/* Declare bitmap array containing font */
extern const uint8_t const font[128*8];
/* Declare bitmap array containing display background from displayFunctions.c */
extern uint8_t display[512];
/* Declare text buffer for display output from displayFunctions.c */
extern char textbuffer[4][16];
/* Declare enable_interrupt function from vector.s */
void enable_interrupt(void);
/* Declare functions and initializer from ioFunctions.c */
void ioInit(void);
int getbtns(void);
int getsw(void);
/* Declare initializers, functions and structs from gameWork.c */
struct object {
	int* x;
	int* y;
	int arrLength;
};
void interrupts_and_timers_init( void );
void gameWork( void );
/* Declare functions from gameFunctions.c */
void set_bit(int x, int y, uint8_t objectBits[]);
void clr_bit(int x, int y, uint8_t objectBits[]);
void move_sprite(int x, int y, struct object *obj);
/* Declare arrays containing coordinates for graphical objects from graphics.h*/
extern int playerSpriteYs[];
extern int playerSpriteXs[];

