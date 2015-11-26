#include <GL/glut.h>
#include <stdio.h>
/*TODO
[ ] - dibujar el espacio (tablero)
[ ] - dibujar la nave protagonista
[ ] - mover la nave de izquierda a derecha
*/

float tx = 0.0;
float ty = 0.0;

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
}//nave

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
    glFlush();
}//moverenemigo

void display(void){
    espacio();
    nave();
    enemigo();
    moverenemigo();

    glFlush();
}//display

int main(int argc, char **argv){
  glutInit(&argc, argv); //es la que echa andar openGL
  //Buffer simple
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB ); //inicia el modo de visualizacion del programa
  //glutInitWindowPosition(100, 120); //en donde aparecera la esquina sup izquierda
  glutInitWindowSize(440, 640); //tamaño de la ventana en ancho y alto, pixeles
  glutCreateWindow("Space Invaders GL"); //lanza la ventana
  //Llamada a la función de dibujado
  glutDisplayFunc(display); //OpenGL se refresca solito

  //glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(arrowkey);

  glutMainLoop();
  return 0;
}//main
