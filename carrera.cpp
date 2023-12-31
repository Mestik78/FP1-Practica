#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int LONG_CARRETERA = 10;
const int CHAR_LINEA_HORIZONTAL = 205; // ˭
const int CHAR_ESQUINA_SUPERIOR_IZQUIERDA = 201; // ╔═
const int CHAR_ESQUINA_SUPERIOR_DERECHA = 187; // ═╗
const int CHAR_ESQUINA_INFERIOR_IZQUIERDA = 200; // ╚═
const int CHAR_ESQUINA_INFERIOR_DERECHA = 188; // ═╝
const int CHAR_LINEA_VERTICAL = 186; // ║
const int CHAR_COCHE = 63; //254 // ■
const int CHAR_CLAVO = 193; // ┴
const int CHAR_SORPRESA = 63; // ?
const int CHAR_NORMAL = 32; // ‘ ‘

bool DEBUG = false;
int MAX_PASOS = 3;

typedef enum {NORMAL, SORPRESA, CLAVO} tTipoPosicion;
typedef tTipoPosicion tCarretera[LONG_CARRETERA];

void dibujarLinea(int posIni, int PosFin, int ascii);
void dibujarLineaHorizontalSuperior();
void dibujarLineaHorizontalInferior();
void dibujarCarril(int posCoche, tCarretera carretera);
void dibujarCarretera(int posCoche, tCarretera carretera);

bool haLlegado(int posCoche);
int pideNumPasos();

bool esSorpresa(int posCoche, tCarretera carretera);
bool esClavo(int posCoche, tCarretera carretera);
int buscaSiguientePosSorpresa(int posCoche, tCarretera carretera);

int avanza(int posCoche);

void simulaCarrera(tCarretera carretera);

int main()
{
	srand(time(NULL));

	tCarretera carretera = {
		NORMAL, NORMAL, CLAVO, SORPRESA, NORMAL,
		SORPRESA, NORMAL, CLAVO, NORMAL, SORPRESA
	};

	bool repetir = true;
	while (repetir) {
		simulaCarrera(carretera);
		cout << "FIN DE LA SIMULACION" << endl;
		cout << "¿Quieres repetir? (S o N): ";
		string respuesta;
		respuesta = getchar();
		if (respuesta != "S" && respuesta != "s") {
			repetir = false;
		}
	}
	
}

void simulaCarrera(tCarretera carretera) {
	int posCoche = 0;
	int tiempoPinchadoRestante = 0;
	dibujarCarretera(posCoche, carretera);

	while (not haLlegado(posCoche)) {
		if (tiempoPinchadoRestante == 0) {
			posCoche = avanza(posCoche);

			if (esClavo(posCoche, carretera)) {
				tiempoPinchadoRestante = 2;
				cout << "Has pinchado... estaras" << tiempoPinchadoRestante << "pasos sin moverte" << endl;
			}
			if (esSorpresa(posCoche, carretera)) {
				dibujarCarretera(posCoche, carretera);
				posCoche = buscaSiguientePosSorpresa(posCoche, carretera);
			}
		}
		else {
			cout << "Te queda un paso menos..." << endl;
			char a;
			a = getchar();
			tiempoPinchadoRestante--;
		}

		dibujarCarretera(posCoche, carretera);
	}
	return;
}

int avanza (int posCoche) {
	if (!DEBUG) {
		cout << "Pulsa enter para continuar" << endl;
		char a;
		a = getchar();
		posCoche += 1 + rand() % MAX_PASOS;
	} else {
		posCoche += pideNumPasos();
		if (posCoche < 0) {
			posCoche = 0;
		}
		if (posCoche > LONG_CARRETERA) {
			posCoche = LONG_CARRETERA;
		}
	}
	return posCoche;
}

void dibujarLinea(int posIni, int posFin, int ascii)
{
	for (int i = posIni; i < posFin; i++)
	{
		cout << char(ascii);
	}
}
void dibujarLineaHorizontalSuperior()
{
	cout << char(CHAR_ESQUINA_SUPERIOR_IZQUIERDA);
	dibujarLinea(0, LONG_CARRETERA, CHAR_LINEA_HORIZONTAL);
	cout << char(CHAR_ESQUINA_SUPERIOR_DERECHA);
	cout << endl;
}
void dibujarPosiciones()
{
	cout << char(CHAR_LINEA_VERTICAL);
	for (int i = 0; i < LONG_CARRETERA; i++)
	{
		cout << i%10;
	}
	cout << char(CHAR_LINEA_VERTICAL);
	cout << endl;
}
void dibujarLineaHorizontalInferior()
{
	cout << char(CHAR_ESQUINA_INFERIOR_IZQUIERDA);
	dibujarLinea(0, LONG_CARRETERA, CHAR_LINEA_HORIZONTAL);
	cout << char(CHAR_ESQUINA_INFERIOR_DERECHA);
	cout << endl;
}
void dibujarCarril(int posCoche, tCarretera carretera)
{
	cout << char(CHAR_LINEA_VERTICAL);
	for (int i = 0; i < LONG_CARRETERA; i++)
	{
		switch (carretera[i]) {
			case NORMAL:
				cout << char(CHAR_NORMAL);
			break;
			case CLAVO:
				cout << char(CHAR_CLAVO);
			break;
			case SORPRESA:
				cout << char(CHAR_SORPRESA);
			break;
		}
		cout << char(carretera[i]);
	}
	cout << char(CHAR_LINEA_VERTICAL);
	cout << endl;

	cout << char(CHAR_LINEA_VERTICAL);
	dibujarLinea(0, posCoche, CHAR_NORMAL);
	cout << char(CHAR_COCHE);
	dibujarLinea(posCoche + 1, LONG_CARRETERA , CHAR_NORMAL);
	cout << char(CHAR_LINEA_VERTICAL);
	cout << endl;


}
void dibujarCarretera(int posCoche, tCarretera carretera)
{
	dibujarLineaHorizontalSuperior();
	dibujarPosiciones();
	dibujarCarril(posCoche, carretera);
	dibujarLineaHorizontalInferior();
}
	
bool haLlegado(int posCoche) {
	return posCoche >= LONG_CARRETERA;
}

int pideNumPasos() {
	int pasos;
	cout << "Dame el numero de pasos a avanzar o retroceder: ";
	cin >> pasos;
	return pasos;
}

bool esSorpresa(int posCoche, tCarretera carretera) {
	return carretera[posCoche] == SORPRESA;
}

bool esClavo(int posCoche, tCarretera carretera) {
	return carretera[posCoche] == CLAVO;
}

int buscaSiguientePosSorpresa(int posCoche, tCarretera carretera) {
	int siguienteSorpresa = -1;
	int primeraSorpresa = -1;

	for (int i = 0; i < LONG_CARRETERA; i++)
	{
		if (carretera[i] == SORPRESA) {
			if (primeraSorpresa == -1) {
				primeraSorpresa = i;
			}
			if (i > posCoche && siguienteSorpresa == -1) {
				siguienteSorpresa = i;
			}
		}
	}

	if (siguienteSorpresa == -1) {
		siguienteSorpresa = primeraSorpresa;
	}
	
	return siguienteSorpresa;
}
