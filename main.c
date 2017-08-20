#include<windows.h>
#include <stdlib.h>
#include <C:\Users\elias edgardo\Downloads\GLUT\include\GL\glut.h>

int isRotated=0;
struct Board{
    int x,y;
    int squareSize;
    int isWhite;
    int squareNumber;
}chessboard={0,800,0,0,0};

struct Horse{
    int x,y;
    int padding;
    int horseSize;
}horses[8];

void start()
{
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,800,0,800);
    glClearColor(0.3,0.3,0.3,0.0);
}

void drawHorses(struct Horse horses[8])
{
    int useX;
    int useY;

    for(int i=0;i<8;i++)
    {
        horses[i].horseSize=chessboard.squareSize/2;
        horses[i].padding=chessboard.squareSize/4;

        useX=horses[i].x*chessboard.squareSize;
        useX+=horses[i].padding;

        useY=800-(horses[i].y*chessboard.squareSize)-horses[i].padding;
        glBegin(GL_QUADS);
        glColor3d(0.5,0,0);
        glVertex2d(useX,useY);
        glVertex2d(useX+horses[i].horseSize,useY);
        glVertex2d(useX+horses[i].horseSize,useY-horses[i].horseSize);
        glVertex2d(useX,useY-horses[i].horseSize);
        glEnd();

    }
}


void drawBoard(struct Board chessboard)
{
    for(int i=0;i<chessboard.squareNumber;i++)
    {
        for(int j=0;j<chessboard.squareNumber;j++)
        {
            if(chessboard.isWhite==0)
            {
                glColor3d(1,1,1);
                chessboard.isWhite=1;
            }
            else
            {
                glColor3d(0,0,0);
                chessboard.isWhite=0;
            }
            glBegin(GL_QUADS);
            glVertex2d(chessboard.x,chessboard.y);
            glVertex2d(chessboard.x+chessboard.squareSize,chessboard.y);
            glVertex2d(chessboard.x+chessboard.squareSize,chessboard.y-chessboard.squareSize);
            glVertex2d(chessboard.x,chessboard.y-chessboard.squareSize);
            glEnd();
            chessboard.x+=chessboard.squareSize;
        }
        if(i%2==0)chessboard.isWhite=1;
        if(i%2!=0)chessboard.isWhite=0;
        chessboard.x=0;
        chessboard.y-=chessboard.squareSize;
    }
}

void getUserData()
{
    int maxSize;
    while(chessboard.squareNumber<3)
    {
        printf("Ingrese el numero de cuadros del tablero: ");
        scanf("%d",&chessboard.squareNumber);
    }
    maxSize=800/chessboard.squareNumber;
    while(chessboard.squareSize>maxSize || chessboard.squareSize==0)
    {
        printf("Ingrese el tamanio de cada cuadro(px, el tamanio maximo es %d px): ",maxSize);
        scanf("%d",&chessboard.squareSize);
    }
    printf("Ahora ingrese las las posiciones x e y de cada caballo, tome la siguiente matriz de referencia\n\n");
    for(int i=0;i<chessboard.squareNumber;i++)
    {
        for(int j=0;j<chessboard.squareNumber;j++)
        {
            printf("(%d,%d)  ",j,i);
        }
        printf("\n\n");
    }
    printf("Separe por espacio las coordenadas X e Y\n");
    for(int i=0;i<8;i++)
    {
        horses[i].x=-1;
        horses[i].y=-1;
        while( (horses[i].x>chessboard.squareNumber-1 || horses[i].x==-1)
              || (horses[i].y>chessboard.squareNumber-1 || horses[i].y==-1) )
        {
        printf("Caballo %d: ", i+1);
        scanf("%d %d",&horses[i].x,&horses[i].y);
        for(int j=0;j<i;j++)
        {
            if(horses[j].x==horses[i].x && horses[j].y==horses[i].y)
            {
                horses[i].x=-1;
                horses[i].y=-1;
            }
        }

        }
    }

    printf("Desea que el tablero se rote -45?: (1=si, 0=no):  ");
    scanf("%d",&isRotated);
}

void screen()
{
    glClear(GL_COLOR_BUFFER_BIT);
    if(isRotated)
    {
        glRotated(45,0,0,1);
        glScalef(0.5,0.5,1.0);
        glTranslated(800,-400,0);
    }

    drawBoard(chessboard);
    drawHorses(horses);
    glFlush();
}

int main(int argc, char *argv[])
{
    getUserData();
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_SINGLE|GLUT_RGB );
    glutInitWindowSize(800,640);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Caballo de ajedrez");
    start();
    glutDisplayFunc(screen);
    glutMainLoop();
    return EXIT_SUCCESS;
}
