// OpenGL_TRIANGLE_ConsoleApplication.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "math.h"

#include "stdafx.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define GL_PI 3.1415f



enum
{
	EXIT                            // wyj�cie
};

// Wielko�� obrot�w
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

static GLboolean iCull, iDepth, iOutline;

using namespace std;
// Funkcja wykonuje wszystkie konieczne inicjalizacje kontekstu renderowania
void SetupRC()
{
	// Czarne t�o
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// Kolor rysuj�cy - zielony
	glColor3f(0.0f, 1.0f, 0.0f);
	// Model cieniowania kolor�w - p�aski
	glShadeModel(GL_FLAT);
	// Wielok�ty o nawini�ciu zgodnym z ruchem wskaz�wek zegara traktowane s�
	// jako skierowane do przodu. Takie ustawienie jest konieczne, poniewa�
	// korzystamy z wachlarzy tr�jk�t�w.
	glFrontFace(GL_CW);
}
// Wywo�ywana w celu przerysowania sceny
void RenderScene(void)
{
	GLfloat x, y, angle; // Przechowuj� warto�ci wsp�rz�dnych i k�ta
	int iPivot = 1; // Do oznaczania zamiennych kolor�w
					// Wyczyszczenie okna i bufora g��bi
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// W��czenie lub wy��czenie mechanizmu eliminowania ukrytych powierzchni
	if (iCull)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);
	// W��czenie lub wy��czenie mechanizmu sprawdzania g��bi
	if (iDepth)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);
	// Je�eli ten znacznik b�dzie ustawiony, to wielok�ty zwr�cone
	// ty�em do widza b�d� rysowane tylko w postaci szkieletu
	if (iOutline)
		glPolygonMode(GL_BACK, GL_LINE);
	else
		glPolygonMode(GL_BACK, GL_FILL);
	// Zapisanie stanu macierzy i wykonanie obrotu
	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	// Rozpocz�cie rysowania wachlarza tr�jk�t�w
	glBegin(GL_TRIANGLE_FAN);
	// Czubek stoka jest wsp�lnym wierzcho�kiem wszystkich tr�jk�t�w z wachlarza
	// wysuni�tym do g�ry w osi z. W ten spos�b zamiast ko�a powstanie sto�ek.
	glVertex3f(0.0f, 0.0f, 75.0f);
	// Wykonujemy obr�t w oko�o i oznaczamy w r�wnych odst�pach wierzcho�ki
	// tworz�ce wachlarz tr�jk�t�w.
	for (angle = 0.0f; angle < (2.0001f*GL_PI); angle += (GL_PI / 5.0f))
	{
		// Wyliczenie wsp�rz�dnych x i y kolejnego wierzcho�ka
		x = 50.0f*sin(angle);
		y = 50.0f*cos(angle);
		// Wybieranie koloru - zielony lub czerwony
		if ((iPivot % 2) == 0)
			glColor3f(0.0f, 1.0f, 0.0f);
		else
			glColor3f(1.0f, 0.0f, 0.0f);
		// Inkrementacja zmiennej okrelaj�cej rodzaj koloru
		iPivot++;
		// Definiowanie kolejnego wierzcho�ka w wachlarzu tr�jk�t�w
		glVertex2f(x, y);
	}
	// Zakoczenie rysowania tr�jk�t�w sto�ka
	glEnd();
	// Rozpocz�cie rysowania kolejnego wachlarza tr�jk�t�w
	// zakrywaj�cego podstaw stoka
	glBegin(GL_TRIANGLE_FAN);
	// �rodek wachlarza znajduje si� na pocz�tku uk�adu wsp�rz�dnych
	glVertex2f(0.0f, 0.0f);
	for (angle = 0.0f; angle < (2.0001f*GL_PI); angle += (GL_PI / 5.0f))
	{
		// Wyliczenie wsp�rz�dnych x i y kolejnego wierzcho�ka
		x = 50.0f*sin(angle);
		y = 50.0f*cos(angle);
		cout >> y >> endl;
		cout >> endl;
		// Wybieranie koloru - zielony lub czerwony
		if ((iPivot % 2) == 0)
			glColor3f(0.0f, 1.0f, 0.0f);
		else
			glColor3f(1.0f, 0.0f, 0.0f);
		// Inkrementacja zmiennej okrelaj�cej rodzaj koloru
		iPivot++;
		// Definiowanie kolejnego wierzcho�ka w wachlarzu tr�jk�t�w
		glVertex2f(x, y);
	}
	// Zakoczenie rysowania tr�jk�t�w podstawy stoka
	glEnd();
	// Odtworzenie macierzy przekszta�ce�
	glPopMatrix();
	// Wys�anie polece� do wykonania
	glutSwapBuffers();
}

void SpecialKeys(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
		xRot -= 5.0f;
	if (key == GLUT_KEY_DOWN)
		xRot += 5.0f;
	if (key == GLUT_KEY_LEFT)
		yRot -= 5.0f;
	if (key == GLUT_KEY_RIGHT)
		yRot += 5.0f;
	if (key > 356.0f)
		xRot = 0.0f;
	if (key < -1.0f)
		xRot = 355.0f;
	if (key > 356.0f)
		yRot = 0.0f;
	if (key < -1.0f)
		yRot = 355.0f;
	// Od�wie�enie zawarto�ci okna
	glutPostRedisplay();
}
void ChangeSize(int w, int h)
{
	GLfloat nRange = 100.0f;
	// Zabezpieczenie przed dzieleniem przez zero
	if (h == 0)
		h = 1;
	// Ustalenie wymiar�w widoku na zgodnych z wymiarami okna
	glViewport(0, 0, w, h);
	// Ponowne ustawienie stosu macierzy rzutowania
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Utworzenie przestrzeni ograniczaj�cej (lewo, prawo, d�, g�ra, blisko, daleko)
	if (w <= h)
		glOrtho(-nRange, nRange, -nRange*h / w, nRange*h / w, -nRange, nRange);
	else
		glOrtho(-nRange*w / h, nRange*w / h, -nRange, nRange, -nRange, nRange);
	// Ponowne ustawienie stosu macierzy rzutowania
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Menu(int value)
{
	switch (value)
	{
		//
	case GL_CULL_FACE:
		iCull = !iCull;
		glutSetWindowTitle("Stozek - GL_CULL_FACE");
		RenderScene();
		break;

		//
	case GL_DEPTH_TEST:
		iDepth = !iDepth;
		glutSetWindowTitle("Stozek - GL_DEPTH_TEST");
		RenderScene();
		break;

		//
	case GL_LINE:
		iOutline = true;
		glutSetWindowTitle("Stozek - GL_LINE");
		RenderScene();
		break;

		//
	case GL_FILL:
		iOutline = false;
		glutSetWindowTitle("Stozek - GL_LINE");
		RenderScene();
		break;

		// wyj�cie
	case EXIT:
		exit(0);
	}
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Triangles Constructing Fan Example");
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(SpecialKeys);
	glutDisplayFunc(RenderScene);
	SetupRC();
	// utworzenie podmenu - Prymitywy
	int MenuPrimitive = glutCreateMenu(Menu);
	glutAddMenuEntry("GL_CULL_FACE", GL_CULL_FACE);
	glutAddMenuEntry("GL_DEPTH_TEST", GL_DEPTH_TEST);
	glutAddMenuEntry("Polygon mode LINE", GL_LINE);
	glutAddMenuEntry("Polygon mode FILL", GL_FILL);
	glutAddMenuEntry("Wyjecie", EXIT);

	// okre�lenie przycisku myszki obs�uguj�cego menu podr�czne
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();
	return 0;
}

