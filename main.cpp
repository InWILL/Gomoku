#include"main.h"
#include<iostream>
using namespace std;

int main(void)
{
    file();
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    window = glfwCreateWindow(width, heith, "五子棋", NULL,NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    gluOrtho2D(0, (GLdouble) width, 0, (GLdouble) heith);
    glEnable(GL_COLOR_LOGIC_OP);
    glClearColor(1.0f,1.0f,1.0f,1.0f);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetKeyCallback(window, key_callback);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        Render();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void Bitblack(int x,int y)
{
    glLogicOp(GL_AND);
    glRasterPos2i(x, y);
    glDrawPixels(black.ImageWidth, black.ImageHeight,
         GL_BGR_EXT, GL_UNSIGNED_BYTE, black.PixelData);
}

void Bitwhite(int x,int y)
{
    glLogicOp(GL_AND);
    glRasterPos2i(x, y);
    glDrawPixels(white1.ImageWidth, white1.ImageHeight,
         GL_BGR_EXT, GL_UNSIGNED_BYTE, white1.PixelData);

    glLogicOp(GL_OR);
    glRasterPos2i(x,y);
    glDrawPixels(white2.ImageWidth, white2.ImageHeight,
         GL_BGR_EXT, GL_UNSIGNED_BYTE, white2.PixelData);
}

void Render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLogicOp(GL_COPY);
    glRasterPos2i(0, 0);
    glDrawPixels(board.ImageWidth, board.ImageHeight,
         GL_BGR_EXT, GL_UNSIGNED_BYTE, board.PixelData);

    glLogicOp(GL_COPY);
    glRasterPos2i(650,550);
    glDrawPixels(reset.ImageWidth, reset.ImageHeight,
         GL_BGR_EXT, GL_UNSIGNED_BYTE, reset.PixelData);

    for(int a=1;a<=19;a++)
        for(int b=1;b<=19;b++)
        {
            switch(chess[a][20-b])
            {glfwSetKeyCallback(window, key_callback);
            case 1:
                Bitblack(9+(a-1)*30.7,9+(b-1)*30.7);
                break;
            case 2:
                Bitwhite(9+(a-1)*30.7,9+(b-1)*30.7);
                break;
            }
        }
    switch(stop)
    {
    case B:
        glRasterPos2i(600,400);
        glDrawPixels(win.ImageWidth, win.ImageHeight,
         GL_BGR_EXT, GL_UNSIGNED_BYTE, win.PixelData);
         break;
    case W:
        glRasterPos2i(600,400);
        glDrawPixels(lose.ImageWidth, lose.ImageHeight,
         GL_BGR_EXT, GL_UNSIGNED_BYTE, lose.PixelData);
         break;
    }
}

void file()
{
    Read("棋盘.bmp",board);
    Read("黑棋.bmp",black);
    Read("白棋1.bmp",white1);
    Read("白棋2.bmp",white2);
    Read("reset.bmp",reset);
    Read("win.bmp",win);
    Read("lose.bmp",lose);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    double x,y;
    int x1,y1,x2,y2,x3,y3,bestb=0,bestw=0;
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS&&stop==0)
     {
          glfwGetCursorPos(window,&x,&y);
        x1=(int)((x+20)/30.7);
        y1=(int)((y+20)/30.7);
        if(0<x1&&x1<20&&0<y1&&y1<20&&chess[x1][y1]==0)
        {
          chess[x1][y1]=1;
            if(ifwin(x1,y1,-1,-1,B)+ifwin(x1,y1,1,1,B)>=4||
                ifwin(x1,y1,0,-1,B)+ifwin(x1,y1,0,1,B)>=4||
                ifwin(x1,y1,-1,0,B)+ifwin(x1,y1,1,0,B)>=4||
                ifwin(x1,y1,-1,1,B)+ifwin(x1,y1,1,-1,B)>=4) stop=B;

            for(int a=1;a<=19;a++)
            for(int b=1;b<=19;b++)
            {
                if(chess[a][b]!=0){markb[a][b]=0;markw[a][b]=0;}
                if(chess[a][b]==0)
                {
                    markb[a][b]=max(max(ifwin(a,b,-1,-1,B)+ifwin(a,b,1,1,B),ifwin(a,b,0,-1,B)+ifwin(a,b,0,1,B)),max(ifwin(a,b,-1,0,B)+ifwin(a,b,1,0,B),ifwin(a,b,-1,1,B)+ifwin(a,b,1,-1,B)))*10;
                    markw[a][b]=max(max(ifwin(a,b,-1,-1,W)+ifwin(a,b,1,1,W),ifwin(a,b,0,-1,W)+ifwin(a,b,0,1,W)),max(ifwin(a,b,-1,0,W)+ifwin(a,b,1,0,W),ifwin(a,b,-1,1,W)+ifwin(a,b,1,-1,W)))*10;
                    if(markb[a][b]>bestb) {bestb=markb[a][b];x2=a;y2=b;}
                    if(markw[a][b]>bestw) {bestw=markw[a][b];x3=a;y3=b;}
                }
            }

        if(bestb>bestw) {x1=x2;y1=y2;}else {x1=x3;y1=y3;}
        if(stop==0)
        {
            chess[x1][y1]=2;
            if(ifwin(x1,y1,-1,-1,W)+ifwin(x1,y1,1,1,W)>=4||
                ifwin(x1,y1,0,-1,W)+ifwin(x1,y1,0,1,W)>=4||
                ifwin(x1,y1,-1,0,W)+ifwin(x1,y1,1,0,W)>=4||
                 ifwin(x1,y1,-1,1,W)+ifwin(x1,y1,1,-1,W)>=4) stop=W;
        }
        }
     }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
    {
        for(int a=0;a<=19;a++)
            for(int b=0;b<=19;b++)
            {
                chess[a][b]=0;
                markb[a][b]=0;
                markw[a][b]=0;
            }
        stop=0;
    }
}

int ifwin(int x,int y,int a,int b,int p)
{
    if (x+a==0||x+a==20||y+b==0||y+b==20) return 0;
    if(chess[x+a][y+b]==p)
            return ifwin(x+a,y+b,a,b,p)+1;
        else return 0;
}
