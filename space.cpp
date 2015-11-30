#include <GL/glut.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
/*TODO
[*] - dibujar el espacio (tablero)
[*] - dibujar la nave protagonista
[*] - mover la nave de izquierda a derecha
[*] - mover automaticamente los enemigos
*/
static char label[100];
float tx = 0.0;
float ty = 0.0;
float pb = 0.0;

void inline drawString (char *s)
{
 unsigned int i;
 for (i=0; i<strlen(s); i++)
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, s[i]); //TIPO YA TAMAÑO DE LETRA
}

void keyboard(unsigned char key, int x, int y){
    switch (key) {
        case 27:
            exit(0);
            break;
    }//switch
}//keyboard

void arrowkey(int key, int x, int y){
    switch (key) {
        case GLUT_KEY_RIGHT:
            //system("canberra-gtk-play -f audio.ogg"); canberra-gtk-play --id blaster.wav
            if(tx < 0.70)
                tx += 0.05;
            printf("valor tx: %f\n", tx);
        break;

        case GLUT_KEY_LEFT:
        if(tx > -0.70)
            tx -= 0.05;
            printf("valor tx: %f\n", tx);
        break;
    }//switch
	glutPostRedisplay();
}//ArrowKey

void espacio(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
}//espacio

void nave(){
    glColor3f(1.0, 1.0, 1.0);
    //glTranslatef(tx, ty, 0);

    glBegin(GL_POLYGON);
        glVertex2f(-0.3 +tx, -0.8);
        glVertex2f(-0.3+tx, -0.9);
        glVertex2f(0.3+tx, -0.9);
        glVertex2f(0.3+tx, -0.8);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex2f(-0.1 +tx, -0.7);
        glVertex2f(-0.1+tx, -0.8);
        glVertex2f(0.1+tx, -0.8);
        glVertex2f(0.1+tx, -0.7);
    glEnd();
}//nave

void bala(){
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
        glVertex2f(-0.03, -0.7+pb);
        glVertex2f(-0.03, -0.77+pb);
        glVertex2f(0.03, -0.77+pb);
        glVertex2f(0.03, -0.7+pb);
    glEnd();
}//bala

void enemigo(){
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
        glVertex2f(0.0, 0.9-ty);
        glVertex2f(0.0, 1.0-ty);
        glVertex2f(0.1, 1.0-ty);
        glVertex2f(0.1, 0.9-ty);
    glEnd();
}//enemigo

void moverenemigo(){
    if(ty < 2.0){
        ty+=0.05;
    }
    else{
      ty=0.0;
    }
    //ty = 0.0;
    printf("ty: %f\n", ty);
    //glFlush();
}//moverenemigo

void moverbala(){
    if(pb < 2.0){
        pb+=0.05;
    }
    else{
      pb=0.0;
    }
    //pb = 0.0;
    printf("pb: %f\n", pb);
    //glFlush();
}//moverenemigo

void texto(){
 glColor3f(0.0, 1.0, 0.0);
 sprintf(label,"%s", "space Invaders 2");
 glRasterPos2f(-0.15, 0); //posision donde aparecera el texto
 drawString (label);
}

void display(void){
	//char nombre="space Invaders 2";

    espacio();
    nave();
    enemigo();
    bala();
    texto();

    glFlush();
   
}//display

void movbala(int v)
{
    glutTimerFunc(500,movbala,2);
    moverbala();
    bala();
    glutPostRedisplay();
}

void idle(int v)
{

    glutTimerFunc(500,idle,1);
    moverenemigo();
    enemigo();
    glutPostRedisplay();
}

int main(int argc, char **argv){
  glutInit(&argc, argv); //es la que echa andar openGL
  //Buffer simple
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB ); //inicia el modo de visualizacion del programa
  //glutInitWindowPosition(100, 120); //en donde aparecera la esquina sup izquierda
  glutInitWindowSize(440, 640); //tamaño de la ventana en ancho y alto, pixeles
  glutCreateWindow("Space Invaders GL"); //lanza la ventana
  //Llamada a la función de dibujado
  glutDisplayFunc(display); //OpenGL se refresca solito
  glutTimerFunc(500,idle,0); // idle es una funcion que se ejecuta cuando no hay otra cosa que hacer
  //Timer ejecuta a idle cada cierto tiempo en este caso 500 milisegundos
  //el 0 como parametro es un id de este proceso retardado

  //glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(arrowkey);

  glutMainLoop();
  return 0;
}//main