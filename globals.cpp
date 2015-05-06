#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)
#define red 1
#define black 2
#define white 3
// Function Declarations
void drawScene();
void update(int value);
void drawBox(float len);
void drawBall(float rad);
void drawTriangle();
void initRendering();
void handleResize(int w, int h);
void handleKeypress1(unsigned char key, int x, int y);
void handleKeypress2(int key, int x, int y);
void handleMouseclick(int button, int state, int x, int y);
void drawBorder(float len);
void drawTriangleAndOther();
void drawInnerPattern();
void generateCoin(int i);
void displayCoin();
void displayInholeCoin();
void handleMouseclick1(int,int);
void moveStriker(float distance);
void keyUp (unsigned char key, int x, int y);   
// Global Variablessh
int turn=1;
 struct timeval tim;  
    double t1;  
    double t2;  
int extrachance=0;
int Carrom_angle=0;
float ball_x = 1.3f;
float ball_y = 1.1f;
float ball_x1=1.3f;
float ball_y1=0.03f;
float ball_velx = 0.00f;
float speed=0;
float ball_velx1=0.0f;
float ball_vely = -0.05f;
float ball_vely1=0.04f;
float ball_rad = 0.15f;
float box_len = 5.0f;
float tri_x = 0.0f;
float tri_y = 0.0f;
float theta = 0.0f; 
float hole_x=2.3f;
float hole_y=2.3f;
float friction_coef=0.00006f;
int canMove=1;
int score=30;
int queen_inside=-3;
int score2=30;
int newchance=0;
int time1=0;
int time2=0;
short int max_chance=0;
