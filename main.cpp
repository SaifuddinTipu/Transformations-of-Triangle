
/*
------------------------------------------
TRANSFORMATIONS OF TRIANGLE
------------------------------------------
Copyright:
------------------------------------------
Md. Saifuddin Tipu
Dept of Software Engineering,
University Malaysia Sarawak
------------------------------------------
*/

#include <stdio.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <GL/glut.h>
#include <GL/freeglut.h>

using namespace std;

int pntX1, pntY1, choice = 0, edges = 3, type, choose = 0;
vector<int> pntX;
vector<int> pntY;
int transX, transY;
double scaleX, scaleY;
int PivotX, PivotY;
double angle, angleRad;

void DrawCoordinate();
void DrawGrid();
void drawTriangle();
void drawTriangleTranslate(int x, int y);
void drawTriangleScale(double x, double y);
void RotationCounterClockwise(int x, int y, double angleRad);
void RotationClockwise(int x, int y, double angleRad);
void ResizeHandler(void);
void myDisplay(void);
void reshape ( int width, int height );

double round(double d)
{
	return floor(d + 0.5);
}
void DrawCoordinate()
{
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
        glVertex2f(-10, 0);
        glVertex2f(10, 0);
        glVertex2f(0, -10);
        glVertex2f(0, 10);
    glEnd();
}

void DrawGrid()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPolygonMode(GL_FRONT, GL_LINE);
    glColor3f(0.75f, 0.75f, 0.75f);
    int xsize=0,ysize=0;
    for(int j=0;j<20;j++)
    {

        xsize=0;
        for(int i=0;i<20;i++)
        {
               glBegin(GL_POLYGON);
               glVertex3f(10.0+xsize, 10.0+ysize, 0.0);
               glVertex3f(-10.0+xsize, 10.0+ysize, 0.0);
               glVertex3f(-10.0+xsize, -10.0+ysize, 0.0);
               glVertex3f(10.0+xsize, -10.0+ysize, 0.0);
            glEnd();
         xsize+=1.0;
     }
     ysize+=1.0;
     }
}
void drawTriangle()
{
	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 0.0, 0.0);
	for (int i = 0; i < edges; i++)
	{
		glVertex2i(pntX[i], pntY[i]);
	}
	glEnd();
}


void drawTriangleTranslate(int x, int y)
{
	glBegin(GL_TRIANGLES);
	glColor3f(0.0, 1.0, 0.0);
	for (int i = 0; i < edges; i++)
	{
		glVertex2i(pntX[i] + x, pntY[i] + y);
	}
	glEnd();
}

void drawTriangleScale(double x, double y)
{
	glBegin(GL_TRIANGLES);
	glColor3f(0.0, 0.0, 1.0);
	for (int i = 0; i < edges; i++)
	{
		glVertex2i((round(pntX[i] + transX) * x), (round(pntY[i] + transY)* y));
	}
	glEnd();
}

void RotationCounterClockwise(int x, int y, double angleRad)
{
	glBegin(GL_TRIANGLES);
	glColor3f(0.0, 0.0, 1.0);
	for (int i = 0; i < edges; i++)
	{
		glVertex2i(round(((pntX[i] + x)* cos(angleRad)) - ((pntY[i] + y) * sin(angleRad))), round(((pntX[i] + x) * sin(angleRad)) + ((pntY[i] + y) * cos(angleRad))));
	}
	glEnd();
}

void RotationClockwise(int x, int y, double angleRad)
{
	glBegin(GL_TRIANGLES);
	glColor3f(0.0, 0.0, 1.0);
	for (int i = 0; i < edges; i++)
	{
		glVertex2i(round(((pntY[i] + y) * sin(angleRad)) + ((pntX[i] + x) * cos(angleRad))), round(((pntY[i] + y) * cos(angleRad)) - ((pntX[i] + x) * sin(angleRad))));
	}
	glEnd();
}
void ResizeHandler(void)
{
	glPointSize(4.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-10.0, 10.0, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;

}
void reshape ( int width, int height )
{
    glViewport(0,0,width,height);

}
void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);

	DrawGrid();
	DrawCoordinate();
	if (choice == 1)
	{
		drawTriangle();
		drawTriangleTranslate(transX, transY);
	}
	else if (choice == 2)
	{
		drawTriangle();
		drawTriangleScale(scaleX, scaleY);
	}
	else if (choice == 3)
	{
		drawTriangle();
		if(type == 1)
        {
            RotationCounterClockwise(PivotX, PivotY, angleRad);
        }
		else if(type == 2)
        {
            RotationClockwise(PivotX, PivotY, angleRad);
        }
	}
    glutSwapBuffers();
glFlush();

}

int main(int argc, char** argv)
{
    cout << "=========================================================" <<endl;
    cout << "|               TRANSFORMATIONS OF TRIANGLE             |" <<endl;
    cout << "=========================================================" <<endl;
    a:
    for (int i = 0; i < edges; i++)
	{
		cout << "Enter co-ordinates for vertex  " << i + 1 << " : "; cin >> pntX1 >> pntY1;
		pntX.push_back(pntX1);
		pntY.push_back(pntY1);
	}

    b:
    cout << "Enter your choice:\n" << endl;
    cout << "===================" <<endl;
    cout << "|1. Translation   |" << endl;
    cout << "|2. Scaling       |" << endl;
    cout << "|3. Rotation      |" << endl;
    cout << "===================" <<endl;
    cout << "Type: ";
    cin >> choice;

    if(choice == 1)
    {
        cout << "Enter the Translation factor for X and Y: "; cin >> transX >> transY;
        cout << "\n";
    }

    else if(choice == 2)
    {
        cout << "Enter the Reference point for X and Y (Type(0,0) for origin):"; cin >> transX >> transY;
        cout << "Enter the Scaling factor for X and Y: "; cin >> scaleX >> scaleY;
        cout << "\n";
    }

    else if(choice == 3)
    {
        cout << "Select Rotation Type: "<<endl;
        cout << "===========================" <<endl;
        cout << "|  1. Counter-Clockwise   |"<<endl;
        cout << "|  2. Clockwise           |"<<endl;
        cout << "===========================" <<endl;
        cout << " Choose: ";
        cin>>type;
        cout << "Enter the Pivot Point for X and Y(Origin(0, 0)): "; cin >> PivotX >> PivotY;
        cout << "Enter the angle for rotation: ";
        cin >> angle;
        cout << "\n";
        angleRad = angle * 3.1416 / 360;
    }
    else
    {
        cout << "Invalid Entry...!!! Try Again...\n" <<endl;
        goto b;
    }
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(640, 640);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("Transformation of Triangle (ASSIGNMENT 1)");
	glutDisplayFunc(myDisplay);
	ResizeHandler();
	glutReshapeFunc(reshape);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
	glutMainLoop();
	cout << "YOUR GLUT WINDOW IS CLOSED...!!!" <<endl;
	cout << "--------------------------------\n" <<endl;
	c:
	do
    {
        cout << "Do You Want to Continue? TYPE: \n 1. YES\n 2. NO" <<endl;
        cout << "ENTER: ";
        cin >> choose;
        switch(choose)
        {
        case 1:
            goto a;
            break;
        case 2:
            cout << "You Exited the Terminal...!\nThank You..." <<endl;
            return EXIT_SUCCESS;
            break;
        }
    }while(choose != 2);
        goto c;
}
