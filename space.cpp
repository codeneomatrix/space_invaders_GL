#include <GL/glut.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "entidades.cpp"
#include <math.h>
//#include "mis_funciones.cpp"
/*TODO
[*] - dibujar el espacio (tablero)
[*] - dibujar la nave protagonista
[*] - mover la nave de izquierda a derecha
[*] - mover automaticamente los enemigos
[ ] - modificar las variables vida y puntuacion
[ ] - refactorizar el random que hace descender a los enemigos 
*/
static char label[100];
static char score[100];
static char vidas[100];
float tx = 0.0;
float ty = 0.0;
float pb = 0.0;
int cantidadEnemigos = 8;
World w1;
int puntuacion = 0;
int vida = 3;

World init(World world){
	/*world.mi_nave.x = 220;
	world.mi_nave.y = 5;
	world.mi_nave.anchura = 30;
	world.mi_nave.altura = 45;
	world.mi_nave.vidas = 5;
    */
	Nave_enemiga nave1;
		nave1.xinc = 50;
		nave1.x = -0.2;
		nave1.y = 0.7;
		nave1.anchura = 30;
		nave1.altura = 30;
		nave1.vidas = 1;
		nave1.existe = true;

	Nave_enemiga nave2;
		nave2.xinc = 115;
		nave2.x = -0.4;
		nave2.y = 0.7;
		nave2.anchura = 30;
		nave2.altura = 30;
		nave2.vidas = 1;
		nave2.existe = true;

	Nave_enemiga nave3;
		nave3.xinc = 115;
		nave3.x = -0.6;
		nave3.y = 0.7;
		nave3.anchura = 30;
		nave3.altura = 30;
		nave3.vidas = 1;
		nave3.existe = true;

	Nave_enemiga nave4;
		nave4.xinc = 115;
		nave4.x = -0.8;
		nave4.y = 0.7;
		nave4.anchura = 30;
		nave4.altura = 30;
		nave4.vidas = 1;
		nave4.existe = true;
	Nave_enemiga nave5;
		nave5.xinc = 115;
		nave5.x = 0.0;
		nave5.y = 0.7;
		nave5.anchura = 30;
		nave5.altura = 30;
		nave5.vidas = 1;
		nave5.existe = true;
	Nave_enemiga nave6;
		nave6.xinc = 115;
		nave6.x = 0.2;
		nave6.y = 0.7;
		nave6.anchura = 30;
		nave6.altura = 30;
		nave6.vidas = 1;
		nave6.existe = true;
	Nave_enemiga nave7;
		nave7.xinc = 115;
		nave7.x = 0.4;
		nave7.y = 0.7;
		nave7.anchura = 30;
		nave7.altura = 30;
		nave7.vidas = 1;
		nave7.existe = true;
	Nave_enemiga nave8;
		nave8.xinc = 115;
		nave8.x = 0.6;
		nave8.y = 0.7;
		nave8.anchura = 30;
		nave8.altura = 30;
		nave8.vidas = 1;
		nave8.existe = true;
	//las naves enemigas las cargamos a un vector de naves enemigas que se encuentra en
	//entidades.cpp

	world.naves_enemigas[0] = nave1;
	world.naves_enemigas[1] = nave2;
	world.naves_enemigas[2] = nave3;
	world.naves_enemigas[3] = nave4;
	world.naves_enemigas[4] = nave5;
	world.naves_enemigas[5] = nave6;
	world.naves_enemigas[6] = nave7;
	world.naves_enemigas[7] = nave8;
    //printf("llego hasta aqui\n");
	//printf("nave enemiga 0 es: %f\n", world.naves_enemigas[0].x);
	//printf("nave enemiga 1 es: %f\n", nave1.x);
		//usamos las estructuras del archivo entidades.h para
		//usarlas como si fueran objetos, instanciar n numero de objetos
		//y modificar sus propiedades de forma independiente
	return world;
}//init

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
            //printf("valor tx: %f\n", tx);
        break;

        case GLUT_KEY_LEFT:
        if(tx > -0.70)
            tx -= 0.05;
            //printf("valor tx: %f\n", tx);
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
        glVertex2f(-0.15 +tx, -0.8);
        glVertex2f(-0.15+tx, -0.85);
        glVertex2f(0.15+tx, -0.85);
        glVertex2f(0.15+tx, -0.8);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex2f(-0.05 +tx, -0.8);
        glVertex2f(-0.05+tx, -0.75);
        glVertex2f(0.05+tx, -0.75);
        glVertex2f(0.05+tx, -0.8);
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

void dibujar_enemigos(World world){
    float x, y;
    glColor3f(0.0, 1.0, 0.0);
    for(int i = 0; i < cantidadEnemigos; i++){
        x = world.naves_enemigas[i].x;
        y = world.naves_enemigas[i].y;
    	//printf("x: %f y: %f\n", x, y);
    glBegin(GL_POLYGON);
        glVertex2f(x, y);
    	//printf("x: %f y: %f\n", x, y);
        glVertex2f(x, y+0.1);
    	//printf("x: %f y: %f\n", x, y+0.1);
        glVertex2f(x+0.1, y+0.1);
        glVertex2f(x+0.1, y);
    glEnd();
    }//for
}//dibujar_enemigos
void moverenemigo(){
    if(ty < 2.0){
        ty+=0.05;
    }
    else{
      ty=0.0;
    }
    //ty = 0.0;
    //printf("ty: %f\n", ty);
    //glFlush();
}//moverenemigo

World Mover_Naves_Enemigas(World world) {
	//MOVIMIENTO DE LAS NAVES ENEMIGAS
	for (int i = 0; i < cantidadEnemigos; i++) {
        if(world.naves_enemigas[i].y > -1.0){
			float var = rand();
			var = var/10000000000;
            world.naves_enemigas[i].y -= var;
			printf("random: %f\n", var);
		}else{
            world.naves_enemigas[i].y = 0.7;
        }
		if (world.dcha == true) {
			world.naves_enemigas[i].x += 0.05;
			if (world.naves_enemigas[i].x >= 0.8) {
				world.dcha = false;
				world.izda = true;
			}
		}
		if (world.izda == true) {
			world.naves_enemigas[i].x -= 0.05;
			if (world.naves_enemigas[i].x <= -0.3) {
				world.dcha = true;
				world.izda = false;
			}
		}
		//printf("naves 0.x %f\n", world.naves_enemigas[0].x);
	}
	return world;
}//Mover_Naves_Enemigas

void moverbala(){
    if(pb < 2.0){
        pb+=0.05;
    }
    else{
      pb=0.0;
    }
    //pb = 0.0;
    //printf("pb: %f\n", pb);
    //glFlush();
}//moverenemigo

void texto(){
 glColor3f(0.0, 1.0, 0.0);
 sprintf(label,"%s", "space Invaders 2");
 sprintf(score,"%s %d", "Score:", puntuacion);
 sprintf(vidas, "%s %d", "Vidas:", vida);
 glRasterPos2f(-0.95, 0.95); //posision donde aparecera el texto
 drawString (label);
 glRasterPos2f(-0.95, 0.90); //posision donde aparecera el texto
 drawString (score);
 glRasterPos2f(-0.95, 0.85); //posision donde aparecera el texto
 drawString (vidas);
}

void display(void){
	//char nombre="space Invaders 2";

    espacio();
    nave();
    //enemigo();
    bala();
    texto();
    dibujar_enemigos(w1);
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

    glutTimerFunc(600,idle,1);
	w1 = Mover_Naves_Enemigas(w1);
	dibujar_enemigos(w1);
	//moverenemigo();
    //enemigo();
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
  //declarar una variable de tipo World y pasarsela a init como parámetro
  w1 = init(w1);
  //glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(arrowkey);

  glutMainLoop();
  return 0;
}//main
