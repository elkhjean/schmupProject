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
	int x[32];
	int y[32];
	int arrLength;
};
void interrupts_and_timers_init( void );
void gameWork( void );
void initialize_player_sprite();
/* Declare functions from gameFunctions.c */
void set_bit(int x, int y, uint8_t map[]);
void clr_bit(int x, int y, uint8_t map[]);
void move_sprite(int x, int y, struct object *obj, uint8_t mapFrom[], uint8_t mapTo[]);
void fire_projectile(struct object *obj, int isPlayer);
int projectile_hit(struct object *obj, uint8_t map[]);
void clr_display(uint8_t map[]);
void reset_sprite(struct object *obj, int spriteOriginXs[], int spriteOriginYs[]);
//int projectile_hit(int* x, int* y, int len);
void update_projectile_maps();
/* Declare arrays containing coordinates for graphical objects from graphics.h*/
extern int playerSpriteYs[];
extern int playerSpriteXs[];

extern enemySpriteYs[];
extern enemySpriteXs[];


extern uint8_t playerProjectileMap[512];
extern uint8_t enemyProjectileMap[512];

void enemy_advance(int x, int y, int i);
void enemy_move_sideways();
void set_active_on(struct object *obj);
void enemy_encounter(int x, int y, struct object *obj);
void spawn_enemies(struct object obj[]);

void main_menu();
extern int runGame; 
void start_game();
