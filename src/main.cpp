#include <iostream>
#include <GL/glut.h>
#include <stdlib.h>
#include <vector>

#include "ag.hpp"

#define HEADER_SIZE 13 //15
#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600
#define PIXEL_SIZE 1
#define PIXEL_SIZE_RELATIVE_TO_OPENGL 0.125

dataType img;
dataType imgproc;

void draw()
{
    glClear(GL_COLOR_BUFFER_BIT);

    float column = 1;
    float row = -1;
    int columnsCounter = 0;
    for (auto byte : imgproc)
    {
        float byteColor = (float)byte / 255.0;
        glColor3f(byteColor, byteColor, byteColor);

        glBegin(GL_POLYGON);

        glVertex2d(row, column);
        glVertex2d(row + PIXEL_SIZE_RELATIVE_TO_OPENGL, column);
        glVertex2d(row + PIXEL_SIZE_RELATIVE_TO_OPENGL, column - PIXEL_SIZE_RELATIVE_TO_OPENGL);
        glVertex2d(row, column - PIXEL_SIZE_RELATIVE_TO_OPENGL);

        row += PIXEL_SIZE_RELATIVE_TO_OPENGL;
        columnsCounter++;
        if (columnsCounter == 16)
        {
            columnsCounter = 0;
            row = -1;
            column -= PIXEL_SIZE_RELATIVE_TO_OPENGL;
        }

        glEnd();
    }

    glutSwapBuffers();
}

void update()
{

    avaliaPop(img);

    imgproc = elitismo(img.size());
    printPop(imgproc);

    draw();
}

void timer(int)
{
    glutPostRedisplay();

    update();

    glutTimerFunc(1000 / 15, timer, 0);
}

int main(int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Imagem");
    glClearColor(1.0, 1.0, 1.0, 1.0);

    FILE *fd = fopen("images/heart.pgm", "rb");
    if (fd == NULL)
    {
        std::cout << "Erro ao abrir imagem\n";
    }

    fseek(fd, 0, SEEK_END);
    long fileSize = ftell(fd);
    fseek(fd, HEADER_SIZE, SEEK_SET);

    unsigned char byte;

    while (ftell(fd) != fileSize)
    {
        fread(&byte, sizeof(unsigned char), 1, fd);
        img.push_back(byte);
    }
    fclose(fd);

    iniPop(img.size());
    glutDisplayFunc(draw);

    do
    {
        glClearColor(1.0, 1.0, 1.0, 1.0);
        avaliaPop(img);

        imgproc = elitismo(img.size());
        // printPop(imgproc);

        draw();
        glutPostRedisplay();

    } while (1);

    // glutTimerFunc(1000 / 15, timer, 0);
    glutMainLoop();
}