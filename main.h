#ifdef _WIN32
#include<windows.h>
#endif // _WIN32

#include <GLFW/glfw3.h>
#include<cstring>
#include"Engine.h"

#define B 1
#define W 2     //B is black,W is white
const int width=800;
const int heith=600;

GLFWwindow* window;
Bmp black,white1,white2,board,reset,win,lose;
int chess[21][21]={0};
int markb[21][21]={0},markw[21][21]={0};
short int stop=0;//stop mark

void Bitblack(int x,int y);
void Bitwhite(int x,int y);
void Render();
void file();
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
int ifwin(int x,int y,int a,int b,int p);
