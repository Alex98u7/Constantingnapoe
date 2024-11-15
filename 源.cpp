#include<windows.h>
#include<iostream>
#include<math.h>
#include <GL/glut.h>
#define GI 9.8
#define PI 3.14
int xp = 0;
int yp = 130;
int canjump = 1;
int canfall = 0;
int xspeed = 0;
float yspeed = 0;
float dy=130;
int jud3 = 0;
int dir = 1;
int xplat = 0;
int canmove = 1;
int startswig(0);
float angle = 0;
int gameover = 0;
int getpixel(int x, int y,float,float,float);
void Init()
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
}
void Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, (double)w,0 , (double)h);
}
void character(int x,int y)
{
	glColor3f(0.0, 0.0, 0.0);
	glRectf(x, y, x+10, y+10);
}
void swig2(int x,int y)
{
	glColor3f(1.0, 0, 0);
	glBegin(GL_POLYGON);
		glVertex2f(x, y);
		glVertex2f(x+5*cos(angle+PI/2), y + 5 * sin(angle + PI / 2));
		glVertex2f(x+5*cos(angle+PI/2) + 40 * cos(angle), y + 5 * sin(angle + PI / 2)+40*sin(angle));
		glVertex2f(x+ 40 * cos(angle), y +40*sin(angle));
		glEnd();
		glFlush();  
	angle = angle + PI / 180;
}
void bk()
{

	glColor3f(0.5, 0.5, 0.5);
	glRectf(0, 0, 1280, 100);
	glRectf(100, 100, 150, 150);
		glRectf(200, 220,240, 230);
		glRectf(400, 250, 480, 260);
		glRectf(600, 400, 650, 410);
		glRectf(650, 100, 660, 410);
		glColor3f(0.0, 0.0, 1.0);
		glRectf(xplat+250, 250,xplat+280, 260);
		glColor3f(0.0, 1.0, 0.0);
		glRectf(520, xplat+250,550, xplat+260);
		glFlush();
	
	
}
void keyboard(unsigned char key, int x, int y)
{
	// 获取键盘输入
	switch (key) {
	case 'a':
		if (getpixel(xp - 1, yp+5, 1, 1, 1))
		{
			xp -= 10;
			xspeed = -10;
		}
		break;
	case 32:
		if(canjump)
		yspeed=40.0;
	
		break;
	case 'd':
		if (getpixel(xp +11, yp+5, 1, 1, 1))
		{
			xp += 10;
			xspeed = 10;
		}
		break;
	case 0x1b:
		exit(0);
	default:
		break;
	}
	// 重新绘制图形
	glutPostRedisplay();
}
int getpixel(int x, int y,float r,float g,float b)
{
	// 定义颜色值
	GLfloat expectedColor[3] = { r, g, b };
	GLubyte pixel[3];
	glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &pixel);
	// 转换颜色值为RGB格式
	GLfloat actualColor[3];
	actualColor[0] = pixel[0] / 255.0f;
	actualColor[1] = pixel[1] / 255.0f;
	actualColor[2] = pixel[2] / 255.0f;
	// 对比颜色值
	if (memcmp(actualColor, expectedColor, sizeof(expectedColor)) == 0) {
		return 1;
	}
	else 
	{
		return 0;
	}
}
void judge()
{
	if (getpixel(xp, yp, 1, 0, 0)|| getpixel(xp+10, yp, 1, 0, 0) || getpixel(xp+10, yp+10, 1, 0, 0) || getpixel(xp, yp+10, 1, 0, 0) )
	{
		gameover = 1;
	}
	if (gameover)
	{
		exit(0);
	}
	if ((xplat <= 0 && dir < 0) || (xplat >= 100 && dir > 0))
	{
		dir = -dir;
	}
	xplat += 2 * dir;
	    int i;
		jud3 = 0;
		
		
			for (i = yp - 1; i >= yp - 1 + yspeed; )
			{
				if (!getpixel(xp, i, 1, 1, 1))
				{
					jud3 = 1;
					i++;
					break;
				}
				i--;
			}
			
			if (jud3 == 1)
			{
				yspeed = 0;
				yp = i ;
				canjump = 1;
			}
			else
			{
				xp += xspeed;
				yp += yspeed;
				yspeed -= 10;
				canjump = 0;
			}
		
		if (getpixel(xp + 5, yp - 1,0,0,1))
		{
			xp += 2*dir;
		}
	    if (getpixel(xp + 5, yp - 1,0,1,0))
		{
			yp += 2*dir;
		}
	
	
}
void timefunction(int value)
{
	glutSwapBuffers();
	judge();
	glutPostRedisplay();
	glutTimerFunc(100, timefunction, 1);
}

void myDisplay(void)
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	character(xp, yp);
	swig2(700, 150);
	bk();
}
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);//初始化glut 
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(100, 100);//1显示窗口左上角初始位置
	glutInitWindowSize(1280, 960);//显示窗口大小
	glutCreateWindow("FirstDemo");// 显示窗口的名称   
	Init();
	glutReshapeFunc(Reshape);
	glutDisplayFunc(myDisplay);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(20, timefunction, 1);
	// 进入主循环
	glutMainLoop();
	return 0;
}