//AQUI LAS FUNCIONES QUE USAREMOS EN LOGIC

void Calcular_Tiempo(World& world) {
	//AQUÍ CALCULO LOS FRAMES POR SEGUNDO DEL JUEGO
	if (getTime() - world.tiempoMilisegundos == 0) {
		world.tiempoMilisegundos++;
	}
	world.fps = (1000 / (getTime() - world.tiempoMilisegundos));
    world.tiempoMilisegundos = getTime();
	world.fpsString = int2string(world.fps);

	//ESTA PARTE CALCULA LAS HORAS, MINUTOS Y SEGUNDOS QUE HAN PASADO.
	world.tiempoSegundos = (getTime() / 1000) %60;
	world.tiempoMinutos = ((getTime() /1000) /60) %60;
	world.tiempoHoras = ((getTime() /1000) /60) /60;
} 

void Mover_Naves_Enemigas(World& world) {
	//MOVIMIENTO DE LAS NAVES ENEMIGAS
	for (int i = 0; i < world.naves1.size(); i++) {
		if (world.dcha == true) {
			world.naves1[i].x += 1;
			if (world.naves1[0].x >= 95) {
				world.dcha = false;
				world.izda = true;
			}
		}
		else if (world.izda == true) {
			if (world.naves1[0].x <= 5) {
				world.dcha = true;
				world.izda = false;
			}
			world.naves1[i].x -= 1;
		}
		if (world.naves1[i].x > world.naves1[i].xinc + 90) {
			world.naves1[i].x -= 1;
		}
		//despues de muchas horas queriendo extinguir a la humanidad, ya que la segunda
		//nave se bugeaba y destrozaba el movimiento de las demás naves, decidí
		//jugarmela un poco y hacer que el movimiento de la segunda nave estuviese directamente
		//ligada al movimiento de la primera, se que es una ñapa y que no se debería
		//hacer de esta manera, pero no consgo arreglarlo de otra.
		world.naves1[1].x = (world.naves1[0].x + world.naves1[1].xinc /2) + 5; 
	}
	for (int i = 0; i < world.naves2.size(); i++) {
		if (world.izda == true) {
			world.naves2[i].x += 1;
		}
		else if (world.dcha == true) {
			world.naves2[i].x -= 1;
		}
	}
	for (int i = 0; i < world.naves3.size(); i++) {
		if (world.dcha == true) {
			world.naves3[i].x += 1;
		}
		else if (world.izda == true) {
			world.naves3[i].x -= 1;
		}
	}
}

void Mover_Mi_Bala(World& world) {
	//AQUÍ MUEVE MI BALA Y CAMBIA EL VALOR BOOLEANO DE LA EXISTENCIA
	//DE LAS BALAS A FALSO CUANDO ALCANZA EL FINAL DE LA PANTALLA.
	for (int i = 0; i < world.disparos.size(); i++) {
		world.disparos[i].y += 8;
		if(world.disparos[i].y >= 430) {
			world.disparos[i].existe = false;
		}
	}
}

void Disparar_No_Continuo(World& world) {
	//CON ESTO SOLO PUEDES DISPARAR UNA VEZ CADA 420 MILISEGUNDOS.
	if ((world.tiempoMilisegundos - world.diferencial) >= 420) {
		world.diferencial = world.tiempoMilisegundos;
		world.hay_disparo = false;
	}
}

void Eliminar_Mis_Balas(World& world) {
	//AQUÍ ELIMINA CUALQUIER DISPARO CON SU VARIABLE BOOLEANA DE EXISTENCIA FALSA.
	for (int i = 0; i < world.disparos.size(); i++) {
		if(world.disparos[i].existe == false) {
			world.disparos.erase(world.disparos.begin() + i);
		}
	}
}

void Disparos_Primeros_Enemigos(World& world) {
	//CREA UN DISPARO EN UN ENEMIGO DE LA PRIMERA FILA ALEATORIO
	if(world.disparos_enemigos1.size()<3 && world.numero_enemigos1 != 0)
	{
		world.rand =(randomInt() % world.numero_enemigos1);
		if (world.naves1[world.rand].existe) {	
			Disparo_enemigo a;
			a.x=world.naves1[world.rand].x + world.naves1[world.rand].anchura/2;
			a.y=world.naves1[world.rand].y;
			a.altura = 10;
			a.anchura = 3;
			a.existe = true;
			world.disparos_enemigos1.push_back(a);
		}
	}
	//MUEVE LAS BALAS CREADAS
	for (int i = 0; i < world.disparos_enemigos1.size(); i++) {
		world.disparos_enemigos1[i].y -= 5;
		if(world.disparos_enemigos1[i].y <= -10) {
			world.disparos_enemigos1[i].existe = false;
		}
	}
	//ELIMINA LAS BALAS CREADAS
	for (int i = 0; i < world.disparos_enemigos1.size(); i++) {
		if(world.disparos_enemigos1[i].existe == false) {
			world.disparos_enemigos1.erase(world.disparos_enemigos1.begin() + i);
		}
	}
}

void Disparos_Segundos_Enemigos(World& world) {
	//CREA DOS DISPAROS EN DOS ENEMIGOS DE LA SEGUNDA FILA ALEATORIOS
	if(world.disparos_enemigos2.size()<4 && world.numero_enemigos2 != 0)
	{
		world.rand =(randomInt() % world.numero_enemigos2);
		if (world.naves2[world.rand].existe) {	
			Disparo_enemigo a;
			a.x=world.naves2[world.rand].x + world.naves2[world.rand].anchura/2;
			a.y=world.naves2[world.rand].y;
			a.altura = 10;
			a.anchura = 3;
			a.existe = true;
			world.disparos_enemigos2.push_back(a);
		}
	}
	//MUEVE ESOS DISPAROS
	for (int i = 0; i < world.disparos_enemigos2.size(); i++) {
		world.disparos_enemigos2[i].y -= 5;
		if(world.disparos_enemigos2[i].y <= -10) {
			world.disparos_enemigos2[i].existe = false;
		}
	}
	//BORRA LOS DISPAROS
	for (int i = 0; i < world.disparos_enemigos2.size(); i++) {
		if(world.disparos_enemigos2[i].existe == false) {
			world.disparos_enemigos2.erase(world.disparos_enemigos2.begin() + i);
		}
	}

	
}

void Disparos_Terceros_Enemigos(World& world) {
	
	//CREA TRES DISPAROS EN TRES ENEMIGOS DE LA TERCERA FILA ALEATORIOS
	if(world.disparos_enemigos3.size( )<6  && world.numero_enemigos3 != 0)
	{
		world.rand =(randomInt() % world.numero_enemigos3);
		if (world.naves3[world.rand].existe) {	
			Disparo_enemigo a;
			a.x=world.naves3[world.rand].x + world.naves3[world.rand].anchura/2;
			a.y=world.naves3[world.rand].y;
			a.altura = 10;
			a.anchura = 3;
			a.existe = true;
			world.disparos_enemigos3.push_back(a);
		}
	}
	//MUEVE LOS DISPAROS
	for (int i = 0; i < world.disparos_enemigos3.size(); i++) {
		world.disparos_enemigos3[i].y -= 5;
		if(world.disparos_enemigos3[i].y <= -10) {
			world.disparos_enemigos3[i].existe = false;
		}
	}
	//BORRA LOS DISPAROS
	for (int i = 0; i < world.disparos_enemigos3.size(); i++) {
		if(world.disparos_enemigos3[i].existe == false) {
			world.disparos_enemigos3.erase(world.disparos_enemigos3.begin() + i);
		}
	}
}

void Colision_Mi_Bala_Primeros_Enemigos(World& world) {
	//EVALUA LA COLISION DE MIS BALAS CON LOS ENEMIGOS DE LA PRIMERA FILA
	for(int m = 0; m < world.disparos.size(); m++) {
		for (int n = 0; n < world.naves1.size(); n++) {
			if(world.naves1[n].existe) {
				if(Colision((Obtener_Rectangulo(world.disparos[m])), Obtener_Rectangulo(world.naves1[n]))) {
					world.disparos[m].existe = false;
					world.naves1[n].existe = false;
				};
			}
		}
	}
}

void Colision_Mi_Bala_Segundos_Enemigos(World& world) {
	//EVALUA LA COLISION DE MIS BALAS CON LOS ENEMIGOS DE LA SEGUNDA FILA
	for(int m = 0; m < world.disparos.size(); m++) {
		for (int n = 0; n < world.naves2.size(); n++) {
			if(world.naves2[n].existe) {
				if(Colision((Obtener_Rectangulo(world.disparos[m])), Obtener_Rectangulo(world.naves2[n]))) {
					world.disparos[m].existe = false;
					if(world.naves2[n].vidas > 1) {
						world.naves2[n].vidas -= 1;
						break;
					}
					else {
						world.naves2[n].existe = false;
					}
				}
			}
		}
	}
}

void Colision_Mi_Bala_Terceros_Enemigos(World& world) {
	//EVALUA LA COLISION DE MIS BALAS CON LOS ENEMIGOS DE LA TERCERA FILA
	for(int m = 0; m < world.disparos.size(); m++) {
		for (int n = 0; n < world.naves3.size(); n++) {
			if(world.naves3[n].existe) {
				if(Colision((Obtener_Rectangulo(world.disparos[m])), Obtener_Rectangulo(world.naves3[n]))) {
					world.disparos[m].existe = false;
					if(world.naves3[n].vidas > 0) {
						world.naves3[n].vidas -= 1;
						break;
					}
					else {
						world.naves3[n].existe = false;
					}
				}
			}
		}
	}
}

void Colision_Primeros_Enemigos_Balas_Mi_Nave(World& world) {
	//EVALUAR LOS DISPAROS ENEMIGOS DE LA PRIMERA FILA CON MI NAVE
	for(int m = 0; m < world.disparos_enemigos1.size(); m++) {
		if(Colision((Obtener_Rectangulo(world.mi_nave)), Obtener_Rectangulo(world.disparos_enemigos1[m]))) {
			world.disparos_enemigos1[m].existe = false;
			world.mi_nave.vidas -= 1;	
			if(world.mi_nave.vidas < 0) {
				world.mi_nave.vidas = 0;
			}
		}
	}
}

void Colision_Segundos_Enemigos_Balas_Mi_Nave(World& world) {
	//EVALUAR LOS DISPAROS ENEMIGOS DE LA SEGUNDA FILA CON MI NAVE
	for(int m = 0; m < world.disparos_enemigos2.size(); m++) {
		if(Colision((Obtener_Rectangulo(world.mi_nave)), Obtener_Rectangulo(world.disparos_enemigos2[m]))) {
			world.disparos_enemigos2[m].existe = false;
			world.mi_nave.vidas -= 1;	
			if(world.mi_nave.vidas < 0) {
				world.mi_nave.vidas = 0;
			}
		}
	}
}

void Colision_Terceros_Enemigos_Balas_Mi_Nave(World& world) {
	//EVALUAR LOS DISPAROS ENEMIGOS DE LA TERCERA FILA CON MI NAVE
	for(int m = 0; m < world.disparos_enemigos3.size(); m++) {
		if(Colision((Obtener_Rectangulo(world.mi_nave)), Obtener_Rectangulo(world.disparos_enemigos3[m]))) {
			world.disparos_enemigos3[m].existe = false;
			world.mi_nave.vidas -= 1;	
			if(world.mi_nave.vidas < 0) {
				world.mi_nave.vidas = 0;
			} 
		}
	}
}

void Colision_Primeros_Enemigos_Balas_Escudos(World& world) {
	//EVALUA LOS DISPAROS ENEMIGOS DE LA PRIMERA FILA CON LOS ESCUDOS
	for(int m = 0; m < world.disparos_enemigos1.size(); m++) {
		for (int n = 0; n < world.escudos.size(); n++) {
			if(world.escudos[n].existe) {
				if(Colision((Obtener_Rectangulo(world.disparos_enemigos1[m])), Obtener_Rectangulo(world.escudos[n]))) {
					world.disparos_enemigos1[m].existe = false;
					world.escudos[n].existe = false;
				};
			}
		}
	}
}

void Colision_Segundos_Enemigos_Balas_Escudos(World& world) {
	//EVALUA LOS DISPAROS ENEMIGOS DE LA SEGUNDA FILA CON LOS ESCUDOS
	for(int m = 0; m < world.disparos_enemigos2.size(); m++) {
		for (int n = 0; n < world.escudos.size(); n++) {
			if(world.escudos[n].existe) {
				if(Colision((Obtener_Rectangulo(world.disparos_enemigos2[m])), Obtener_Rectangulo(world.escudos[n]))) {
					world.disparos_enemigos2[m].existe = false;
					world.escudos[n].existe = false;
				};
			}
		}
	}
}

void Colision_Terceros_Enemigos_Balas_Escudos(World& world) {
	//EVALUA LOS DISPAROS ENEMIGOS DE LA TERCERA FILA CON LOS ESCUDOS
	for(int m = 0; m < world.disparos_enemigos3.size(); m++) {
		for (int n = 0; n < world.escudos.size(); n++) {
			if(world.escudos[n].existe) {
				if(Colision((Obtener_Rectangulo(world.disparos_enemigos3[m])), Obtener_Rectangulo(world.escudos[n]))) {
					world.disparos_enemigos3[m].existe = false;
					world.escudos[n].existe = false;
				};
			}
		}
	}
}

void Colision_Mi_Bala_Escudos(World& world) {
	//EVALUA MIS DISPAROS CON LOS ESCUDOS
	for(int m = 0; m < world.disparos.size(); m++) {
		for (int n = 0; n < world.escudos.size(); n++) {
			if(world.escudos[n].existe) {
				if(Colision((Obtener_Rectangulo(world.disparos[m])), Obtener_Rectangulo(world.escudos[n]))) {
					world.disparos[m].existe = false;
					world.escudos[n].existe = false;
				};
			}
		}
	}
}

bool Colision(Rectangulo rect1, Rectangulo rect2) {
	//CALCULA SI ALGUN PUNTO DE UN RECTANGULO TOCA OTRO PUNTO DEL OTRO RECTANGULO
	bool enX = false;
	bool enY = false;

	if(rect1.p1.x<= rect2.p2.x && rect1.p1.x >= rect2.p1.x)
	enX = true;
	if(rect1.p2.x <= rect2.p2.x && rect1.p2.x  >= rect2.p1.x)
	enX = true;
	if(rect2.p1.x <= rect1.p2.x && rect2.p1.x  >= rect1.p1.x)
	enX = true;
	if(rect2.p2.x <= rect1.p2.x && rect2.p2.x  >= rect1.p1.x)
	enX = true;

	if(rect1.p1.y <= rect2.p1.y && rect1.p1.y >= rect2.p4.y)
	enY = true;
	if(rect1.p4.y <= rect2.p1.y && rect1.p4.y >= rect2.p4.y)
	enY = true;
	if(rect2.p1.y <= rect1.p1.y && rect2.p1.y >= rect1.p4.y)
	enY = true;
	if(rect2.p4.y <= rect1.p1.y && rect2.p4.y >= rect1.p4.y)
	enY = true;
	if(enX && enY)
	return true;

	return false;
}

Rectangulo Obtener_Rectangulo(Escudo a) {
	//CONVIERTE UN ESCUDO EN UN RECTANGULO
	Rectangulo z; 
	z.p1.x = a.x;
	z.p1.y = a.y;
	z.p2.x = a.x + a.anchura;
	z.p2.y = a.y;
	z.p3.x = a.x;
	z.p3.y = a.y - a.altura;
	z.p4.x = a.x + a.anchura;
	z.p4.y = a.y - a.altura;
	return z;
}

Rectangulo Obtener_Rectangulo(Disparo a) {
	//CONVIERTE UN MIS BALAS EN RECTANGULOS
	Rectangulo z; 
	z.p1.x = a.x;
	z.p1.y = a.y;
	z.p2.x = a.x + a.anchura;
	z.p2.y = a.y;
	z.p3.x = a.x;
	z.p3.y = a.y - a.altura;
	z.p4.x = a.x + a.anchura;
	z.p4.y = a.y - a.altura;
	return z;
}

Rectangulo Obtener_Rectangulo(Nave_enemiga a) {
	//CONVIERTE LAS NAVES ENEMIGAS EN RECTANGULOS
	Rectangulo z; 
	z.p1.x = a.x;
	z.p1.y = a.y;
	z.p2.x = a.x + a.anchura;
	z.p2.y = a.y;
	z.p3.x = a.x;
	z.p3.y = a.y - a.altura;
	z.p4.x = a.x + a.anchura;
	z.p4.y = a.y - a.altura;
	return z;
}

Rectangulo Obtener_Rectangulo(Nave a) {
	//CONVIERTE MI NAVE EN UN RECTANGULO
	Rectangulo z; 
	z.p1.x = a.x;
	z.p1.y = a.y;
	z.p2.x = a.x + a.anchura;
	z.p2.y = a.y;
	z.p3.x = a.x;
	z.p3.y = a.y - a.altura;
	z.p4.x = a.x + a.anchura;
	z.p4.y = a.y - a.altura;
	return z;
}

Rectangulo Obtener_Rectangulo(Disparo_enemigo a) {
	//CONVIERTE LOS DISPAROS ENEMIGOS EN RECTANGULOS
	Rectangulo z; 
	z.p1.x = a.x;
	z.p1.y = a.y;
	z.p2.x = a.x + a.anchura;
	z.p2.y = a.y;
	z.p3.x = a.x;
	z.p3.y = a.y - a.altura;
	z.p4.x = a.x + a.anchura;
	z.p4.y = a.y - a.altura;
	return z;
}

//AQUI LAS FUNCIONES QUE USAREMOS EN PAINT

void Pintar_Boxes(const World& world) {
	//PINTA EL GAMEBOX, INFOBOX...
	changeColor(BLUE);
	drawQuad (world.infoBox.x, world.infoBox.y, world.infoBox.anchura, world.infoBox.altura);
	changeColor(RED);
	drawQuad (world.gameBox.x, world.gameBox.y, world.gameBox.anchura, world.gameBox.altura);
	changeColor(BLACK);
	drawQuad (world.infoBox.x +1, world.infoBox.y + 1, world.infoBox.anchura -2, world.infoBox.altura -2);
	//EL COMENTARIO DE ABAJO ES PARA INCLUIR UNA FOTO DE FONDO, PERO ENTONCES NO SE VEN BIEN LAS
	//BALAS ENEMIGAS, EN EL CASO DE DESCOMENTAR ESE CODIGO, COMENTAR LA ULTIMA LINEA DE LA FUNCION
	//drawQuadTexture (world.gameBox.x +1, world.gameBox.y + 1, world.gameBox.anchura -2, world.gameBox.altura -2, "test.png");
	drawQuad (world.gameBox.x +1, world.gameBox.y + 1, world.gameBox.anchura -2, world.gameBox.altura -2);
}

void Pintar_Tiempo(const World& world) {
	//PINTA EL TIEMPO
	printText ( 25 , 465 , "Time: " , RED ); 
	printText ( 80 , 465 , int2string(world.tiempoHoras) + " :" , RED); 
	printText ( 115 , 465 , int2string(world.tiempoMinutos) + " :", RED); 
	printText ( 145 , 465 , int2string(world.tiempoSegundos), RED); 
}

void Pintar_FPS(const World& world) {
	//PINTA LOS FPS
	printText ( 175 , 465 , "Fps: ", RED);
	printText ( 225 , 465 , world.fpsString, RED);
}

void Pintar_Vidas(const World& world) {
	//PINTA LAS VIDAS QUE TE QUEDAN
	printText ( 350 , 465 , "Lifes: " , RED ); 
	printText ( 400 , 465 , int2string(world.mi_nave.vidas) , RED ); 
}

void Pintar_Estrellas(const World& world, vector <int> estrellas) {
	//PINTA LAS ESTRELLAS
	changeColor(WHITE);
	for (int i = 0; i < 500; i++){
		plot(estrellas[i], estrellas[i++]);	
	}
}

void Pintar_Un_Escudo(const World& world, Escudo a) {
	//PINTA UN ESCUDO
	drawQuadTexture(a.x, a.y, a.anchura, a.altura, "shield.png");
}

void Pintar_Escudos(const World& world) {
	//PINTA LOS ESCUDOS
	for(int i = 0; i < world.escudos.size(); i++) {
		if (world.escudos[i].existe) {
			Pintar_Un_Escudo(world, world.escudos[i]);
		}
	}
}

void Pintar_Mi_Nave(const World& world, Nave a) {
	//PINTA MI NAVE
	drawQuadTexture(a.x, a.y, a.anchura, a.altura, "ship1.png"); 
}


void Pintar_Nave1(const World& world, Nave_enemiga a) {
	//PINTA UN ENEMIGO DE LA PRIMERA FILA
	drawQuadTexture(a.x, a.y, a.anchura, a.altura, "enemy1.png");
}

void Pintar_Nave2(const World& world, Nave_enemiga a) {
	//PINTA UN ENEMIGO DE LA SEGUNDA FILA
	drawQuadTexture(a.x, a.y, a.anchura, a.altura, "enemy2.png");
}

void Pintar_Nave3(const World& world, Nave_enemiga a) {
	//PINTA UN ENEMIGO DE LA TERCERA FILA
	drawQuadTexture(a.x, a.y, a.anchura, a.altura, "enemy3.png");
}

void Pintar_Enemigos1(const World& world) {
	//PINTA LA PRIMERA FILA DE NAVES
	for(int i = 0; i < world.naves1.size(); i++ ) {
		if (world.naves1[i].existe) {
			Pintar_Nave1(world, world.naves1[i]);
		}
	}
}

void Pintar_Enemigos2(const World& world) {
	//PINTA LA SEGUNDA FILA DE NAVES
	for(int i = 0; i < world.naves2.size(); i++ ) {
		if (world.naves2[i].existe) {
			Pintar_Nave2(world, world.naves2[i]);
		}
	}
}

void Pintar_Enemigos3(const World& world) {
	//PINTA LA TERCERA FILA DE NAVES
	for(int i = 0; i < world.naves3.size(); i++ ) {
		if (world.naves3[i].existe) {
			Pintar_Nave3(world, world.naves3[i]);
		}
	}
}

void Pintar_Mis_Balas(const World& world) {
	//PINTA MIS DISPAROS
	for(int i = 0; i < world.disparos.size(); i++) {
		drawQuadTexture(world.disparos[i].x, world.disparos[i].y, 
		world.disparos[i].anchura,world.disparos[i].altura, "myshot.png");
	}
}

void Pintar_Primeros_Enemigos_Balas(const World& world) {
	//PINTA LOS DISPAROS DE LOS ENEMIGOS DE LA PRIMERA FILA
	for(int i = 0; i < world.disparos_enemigos1.size(); i++) {
		drawQuadTexture(world.disparos_enemigos1[i].x, world.disparos_enemigos1[i].y,
		world.disparos_enemigos1[i].anchura,world.disparos_enemigos1[i].altura, "enemyshot.png");
	}
}

void Pintar_Segundos_Enemigos_Balas(const World& world) {
	//PINTA LOS DISPAROS DE LOS ENEMIGOS DE LA SEGUNDA FILA
	for(int i = 0; i < world.disparos_enemigos2.size(); i++) {
		drawQuadTexture(world.disparos_enemigos2[i].x, world.disparos_enemigos2[i].y,
		world.disparos_enemigos2[i].anchura,world.disparos_enemigos2[i].altura, "enemyshot.png");
	}
}

void Pintar_Terceros_Enemigos_Balas(const World& world) {
	//PINTA LOS DISPAROS DE LOS ENEMIGOS DE LA TERCERA FILA
	for(int i = 0; i < world.disparos_enemigos3.size(); i++) {
		drawQuadTexture(world.disparos_enemigos3[i].x, world.disparos_enemigos3[i].y,
		world.disparos_enemigos3[i].anchura,world.disparos_enemigos3[i].altura, "enemyshot.png");
	}
}

void You_Win(const World& world) {
	//NOS DICE QUE HEMOS GANADO CUANDO NO QUEDAN NAVES ENEMIGAS
	if(!(world.naves1[0].existe || world.naves1[1].existe || world.naves1[2].existe || world.naves1[3].existe ||
		world.naves1[4].existe || world.naves1[5].existe || world.naves1[6].existe || world.naves2[0].existe ||
		world.naves2[1].existe || world.naves2[2].existe || world.naves2[3].existe || world.naves2[4].existe ||
		world.naves2[5].existe || world.naves2[6].existe || world.naves3[0].existe || world.naves3[1].existe ||
		world.naves3[2].existe || world.naves3[3].existe || world.naves3[4].existe || world.naves3[5].existe ||
		world.naves3[6].existe)) {
		printText ( 200 , 250 , "YOU WIN!" , RED ); 
	}

}

void Game_Over(const World& world) {
	//NOS DA GAME OVER CUANDO NO NOS QUEDAN VIDAS SI NO HEMOS GANADO ANTES
	if(world.naves1[0].existe || world.naves1[1].existe || world.naves1[2].existe || world.naves1[3].existe ||
		world.naves1[4].existe || world.naves1[5].existe || world.naves1[6].existe || world.naves2[0].existe ||
		world.naves2[1].existe || world.naves2[2].existe || world.naves2[3].existe || world.naves2[4].existe ||
		world.naves2[5].existe || world.naves2[6].existe || world.naves3[0].existe || world.naves3[1].existe ||
		world.naves3[2].existe || world.naves3[3].existe || world.naves3[4].existe || world.naves3[5].existe ||
		world.naves3[6].existe) {
		if(world.mi_nave.vidas <= 0) {
			printText ( 200 , 250 , "GAME OVER" , RED );
		}
	}
}
