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
[*] - refactorizar el random que hace descender a los enemigos
[ ] - reporte
[ ] - aplicacion terminada
[ ] - colision con nave protagonista
*/
static char label[100];
static char label2[100];
static char label3[100];
//static char continuar[100];
//static char juegoTerminado[100];
float tx = 0.0;
float ty = 0.0;
float pb = 0.0;
int cantidadEnemigos = 8;
World w1;
int puntuacion = 0;
int vidas = 0;
int disparo_actual = 0;
int cantidadBalas = 40;
//vars para posicion actual de nave principal
float ax, ay, bx, by, cx, cy, dx, dy;
//vars para pos actual de enemigo
float px, py;
//flujo del juego
bool vidaPerdida = false;

World init(World world){

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

	world.naves_enemigas[0] = nave1;
	world.naves_enemigas[1] = nave2;
	world.naves_enemigas[2] = nave3;
	world.naves_enemigas[3] = nave4;
	world.naves_enemigas[4] = nave5;
	world.naves_enemigas[5] = nave6;
	world.naves_enemigas[6] = nave7;
	world.naves_enemigas[7] = nave8;
    Disparo d1;
	d1.x = 0;
	d1.y = 0;
	d1.existe = false;

	for(int i = 0; i < cantidadBalas; i++){
		world.disparos[i] = d1;
	}//for
	return world;
}//init

void inline drawString (char *s){
	unsigned int i;
	for (i=0; i<strlen(s); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, s[i]); //TIPO YA TAMAÑO DE LETRA
}//inline


void espacio(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
}//espacio

void nave_principal(){
    glColor3f(1.0, 1.0, 1.0);
	//base
    glBegin(GL_POLYGON);
        glVertex2f(-0.15 +tx, -0.8); //A
        glVertex2f(-0.15+tx, -0.85);
        glVertex2f(0.15+tx, -0.85);
        glVertex2f(0.15+tx, -0.8); //B
    glEnd();
	//canion
    glBegin(GL_POLYGON);
        glVertex2f(-0.05 +tx, -0.8);
        glVertex2f(-0.05+tx, -0.75); //C
        glVertex2f(0.05+tx, -0.75); //D
        glVertex2f(0.05+tx, -0.8);
    glEnd();
	ax = -0.15 + tx;
	ay = -0.8;
	bx = 0.15 + tx;
	by = 0.15 + tx;
	cx = -0.05 + tx;
	cy = -0.75;
	dx = 0.05 + tx;
	dy = -0.75;
}//nave_principal

void dibujar_enemigos(World world){
    float x, y;
    glColor3f(0.0, 1.0, 0.0);
    for(int i = 0; i < cantidadEnemigos; i++){
		if(world.naves_enemigas[i].existe == true){
			x = world.naves_enemigas[i].x;
        	y = world.naves_enemigas[i].y;
    	glBegin(GL_POLYGON);
        	glVertex2f(x, y);
        	glVertex2f(x, y+0.1);
        	glVertex2f(x+0.1, y+0.1);
        	glVertex2f(x+0.1, y);
    	glEnd();
		}
    }//for
}//dibujar_enemigos

World mover_naves_enemigas(World world) {
	//MOVIMIENTO DE LAS NAVES ENEMIGAS
	for (int i = 0; i < cantidadEnemigos; i++) {
        if(world.naves_enemigas[i].y > -1.0){
			float var = rand() % 3;
			var = var / 100;
            world.naves_enemigas[i].y -= var;
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
	}
	return world;
}//mover_naves_enemigas

void dibujar_balas(World world){
    float x, y;
    for(int i = 0; i < cantidadBalas; i++){
		if(world.disparos[i].existe == true){
        	x = world.disparos[i].x;
        	y = world.disparos[i].y;
    		glColor3f(0.0, 0.0, 1.0);
			glBegin(GL_POLYGON);
        		glVertex2f(x, y);
        		glVertex2f(x, y+0.07);
        		glVertex2f(x+0.06, y+0.07);
        		glVertex2f(x+0.06, y);
    		glEnd();
		}//if
    }//for
}//dibujar_enemigos

World mover_balas(World world) {
	for (int i = 0; i < cantidadBalas; i++) {
		if(world.disparos[i].existe == true){
        	if(world.disparos[i].y > -1.0){
            	world.disparos[i].y += 0.07;
			}else{
            	world.disparos[i].existe = false;
        	}
		}//if
	}//for
	return world;
}//mover_naves_enemigas

World habilitar_balas(World world){
	if(disparo_actual == cantidadBalas)
		disparo_actual = 0; //resetear, por indice 0
	if(world.disparos[disparo_actual].existe == false){
		world.disparos[disparo_actual].x = tx;
		world.disparos[disparo_actual].y = -0.75;
		world.disparos[disparo_actual].existe = true;
		disparo_actual++;
		//printf("habilitar_balas x: %f\n", world.disparos[disparo_actual-1].x);
	}
	return world;
}//habilitar_balas


bool between(float px, float py){
	//px entre cx y dx && py <= cy
	if(px >= cx && px <= dx && py <= cy)
		return true;
	return false;
}//between

bool colision_enemigo_con_jugador(World world){
	for(int i = 0; i < cantidadEnemigos; i++){
			px = world.naves_enemigas[i].x;
			py = world.naves_enemigas[i].y;
			//printf("Enemigo %d px %f py %f\n", i, px, py);
			if( between(px, py) ){
				printf("enemigo %d tocó la nave\n", i);
				//vidaPerdida = true;
				return true;
			}
	}//for
	return false;
}//colision_enemigo_con_jugador

bool colision(float x1, float x2, float x3, float x4){
	int c1 = 0;
	int c2 = 0;
	if(x3 > x1 && x3 < x2){
		c1 = 1;
	}
	if(x4 > x1 && x4 < x2){
		c2 = 1;
	}
	if(c1 == 1 || c2 == 1)
		return true;
	return false;
	//return c1 && c2;
}//colision

World colision_disparo_con_enemigo(World world){
	for(int m = 0; m < cantidadBalas; m++) {
		for (int n = 0; n < cantidadEnemigos; n++) {
			if(world.naves_enemigas[n].existe == true) {
				if(colision(world.naves_enemigas[n].x, world.naves_enemigas[n].x + 0.1, world.disparos[m].x, world.disparos[m].x + 0.06) ){
					if(colision(world.naves_enemigas[n].y, world.naves_enemigas[n].y + 0.1, world.disparos[m].y, world.disparos[m].y + 0.07) ){
						//puts("entering colision");
						world.disparos[m].existe = false;
						world.naves_enemigas[n].existe = false;
						//puts("colision_disparo_con_enemigo");
						puntuacion += 10;
					}
				}
			}//if
		}//for
	}//for
	return world;
}//colision_disparo_con_enemigo

void texto(){
	glColor3f(0.0, 1.0, 0.0);
	sprintf(label,"%s", "space Invaders 2");
	sprintf(label2,"%s %d", "Score:", puntuacion);
	sprintf(label3, "%s %d", "Vidas:", vidas);
	glRasterPos2f(-0.95, 0.95); //posision donde aparecera el texto
	drawString (label);
	glRasterPos2f(-0.95, 0.90); //posision donde aparecera el texto
	drawString (label2);
	glRasterPos2f(-0.95, 0.85); //posision donde aparecera el texto
	drawString (label3);
}//texto

void gameOver(){
	glColor3f(1.0, 0.0, 0.0);
	if(vidas == 0){
		vidaPerdida = true;
		sprintf(label, "%s", "GAME OVER");
		sprintf(label2, "%s", "RESET? ENTER");
		sprintf(label3, "%s %d", "Vidas: ", vidas);
		glRasterPos2f(0.0, 0.0);
		drawString(label);
		glRasterPos2f(0.0, -0.1);
		drawString(label3);
		glRasterPos2f(0.0, -0.2);
		drawString(label2);
		vidas = 3;
		w1 = init(w1);
		puntuacion = 0;
	}else{
		vidaPerdida = true;
		sprintf(label, "%s", "¿continuar? ENTER");
		sprintf(label2, "%s %d", "Vidas restantes: ", vidas);
		glRasterPos2f(0.0, 0.0);
		drawString(label);
		glRasterPos2f(0.0, -0.1);
		drawString(label2);
		vidas--;
		w1 = init(w1);
	}
}//gameOver

void game_win(){
	glColor3f(1.0, 0.0, 0.0);
	vidaPerdida = true; //detener el flujo
	sprintf(label, "%s", "GANAS POR PUNTUACION");
	sprintf(label2, "%s", "RESET? ENTER");
	glRasterPos2f(0.0, 0.0);
	drawString(label);
	glRasterPos2f(0.0, -0.1);
	drawString(label2);
	vidas = 3;
	w1 = init(w1);
	puntuacion = 0;
}//game_win

void display(void){
    espacio();
    nave_principal();
    texto();
	//colision_enemigo_con_jugador(w1);
    dibujar_enemigos(w1);
	dibujar_balas(w1);
	//intentando colocar aqui la revision de colision con jugador
	if( colision_enemigo_con_jugador(w1) ){
		//vidaPerdida = true;
		gameOver();
		glFlush();
	}
	if(!vidaPerdida){
		glFlush();
	}
	if(puntuacion >= 60){
		game_win();
		glFlush();
	}
}//display

void idle(int v){
    glutTimerFunc(100,idle,1);
	w1 = mover_balas(w1);
	w1 = mover_naves_enemigas(w1);
	dibujar_enemigos(w1);
	dibujar_balas(w1);
	w1 = colision_disparo_con_enemigo(w1);
	if(!vidaPerdida)
    	glutPostRedisplay();
}//idle

void keyboard(unsigned char key, int x, int y){
    switch (key) {
        case 27:
            exit(0);
            break;
		case 32: //space bar
			w1 = habilitar_balas(w1);
			break;
		case 13:
			vidaPerdida = false;
			break;
    }//switch
}//keyboard

void arrowkey(int key, int x, int y){
    switch (key) {
        case GLUT_KEY_RIGHT:
            //system("canberra-gtk-play -f audio.ogg"); canberra-gtk-play --id blaster.wav
            if(tx < 0.70)
                tx += 0.05;
        break;
        case GLUT_KEY_LEFT:
        if(tx > -0.70)
            tx -= 0.05;
        break;
    }//switch
	glutPostRedisplay();
}//ArrowKey

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
