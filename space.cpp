#include <GL/glut.h>
/*TODO
[ ] - dibujar el espacio (tablero)
[ ] - dibujar la nave protagonista
[ ] - mover la nave de izquierda a derecha
*/

void keyboard(unsigned char key, int x, int y){
    switch (key) {
        case 27:
            exit(0);
            break;
    }//switch
}//keyboard

void espacio(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
}//espacio

void nave(){
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
        glVertex2f(-0.3, -0.8);
        glVertex2f(-0.3, -0.9);
        glVertex2f(0.3, -0.9);
        glVertex2f(0.3, -0.8);
    glEnd();
}//nave

void display(void){
    espacio();
    nave();
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
  //glutSpecialFunc(arrowkey);

  glutMainLoop();
  return 0;
}//main
