struct Box
{
	int x;
	int y;
	int anchura;
	int altura;
	//Color color;
};

struct Escudo {
	int x;
	int y;
	int altura;
	int anchura;
	bool existe;
};

struct Nave
{
	int x;
	int y;
	int anchura;
	int altura;
	int vidas;
};

struct Nave_enemiga
{
	int xinc;
	float x;
	float y;
	int anchura;
	int altura;
	int vidas;
	bool existe;
};

struct Disparo
{
	float x;
	float y;
	int anchura;
	int altura;
	bool existe;
};

struct Disparo_enemigo
{
	int x;
	int y;
	int anchura;
	int altura;
	bool existe;
};

struct Punto
{
	int x;
	int y;
};

struct Rectangulo
{
	Punto p1;
	Punto p2;
	Punto p3;
	Punto p4;
};

struct World
{
	Box infoBox;
	Box gameBox;

	//vector <int> coord;

	int tiempoHoras;
	int tiempoMinutos;
	int tiempoSegundos;
	int tiempoMilisegundos;

	int fps;
	char fpsString[100];

	Nave mi_nave;
//	vector <Disparo> disparos;
	Disparo disparos[40];

	bool hay_disparo;
	int diferencial;

	//vector <Nave_enemiga> naves1;
	//vector <Nave_enemiga> naves2;
	//vector <Nave_enemiga> naves3;
	Nave_enemiga naves_enemigas [7];
	int numero_enemigos1;
	int numero_enemigos2;
	int numero_enemigos3;

	bool dcha;
	bool izda;

	int rand;
	//vector <Disparo_enemigo> disparos_enemigos1;
	//vector <Disparo_enemigo> disparos_enemigos2;
	//vector <Disparo_enemigo> disparos_enemigos3;

	//vector <Escudo> escudos;

};
