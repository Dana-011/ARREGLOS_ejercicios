#include <iostream>
#include <conio.h>
#include <string>
#include <stack>
#include <queue>

using namespace std;

const int MAX_USUARIOS = 100;       // M�ximo n�mero de usuarios permitidos
const int CONSOLE_WIDTH = 80;       // Ancho de la consola para centrar texto

// Estructura para almacenar informaci�n de un usuario
struct usuario {
    string nombre;      // Nombre del usuario
    string contrasena;  // Contrase�a del usuario
    string tipo;        // Tipo de usuario (cliente o admin)
};

usuario lista_usuarios[MAX_USUARIOS];  // Array para almacenar usuarios registrados
int numero_usuarios = 0;               // Contador de usuarios registrados

stack<string> pila_admins;     // Pila para almacenar nombres de administradores activos
queue<string> cola_clientes;   // Cola para almacenar nombres de clientes activos

/*  
* Nombre: texto_centrado  
* Descripci�n: Centra un texto en la consola basado en el ancho definido.  
* Par�metros: texto - cadena a centrar.  
* Retorna: nada.  
*/  
void texto_centrado(string texto) {
    int espacios = 40;
    for (int i = 0; i < espacios; i++) {
        cout << " ";
    }
    cout << texto;
}

/*  
* Nombre: ingresar_contrasena  
* Descripci�n: Permite ingresar una contrase�a ocultando los caracteres con asteriscos.  
* Par�metros: ninguno.  
* Retorna: string - contrase�a ingresada por el usuario.  
*/  
string ingresar_contrasena() {
    char c;
    string contrasena = "";
    int largo = 0;

    while (true) {
        c = _getch();
        if (c == 13) break;

        if (c == 8 && largo > 0) {
            cout << "\b \b";
            largo--;
            contrasena = contrasena.substr(0, largo);
        }
        else if (c != 8 && largo < 8) {
            contrasena += c;
            largo++;
            cout << '*';
        }
    }
    return contrasena;
}

/*  
* Nombre: ordenar_usuarios  
* Descripci�n: Ordena los usuarios alfab�ticamente por nombre usando ordenamiento de burbuja.  
* Par�metros: ninguno.  
* Retorna: nada.  
*/  
void ordenar_usuarios() {
    for (int i = 0; i < numero_usuarios - 1; i++) {
        for (int j = 0; j < numero_usuarios - i - 1; j++) {
            if (lista_usuarios[j].nombre > lista_usuarios[j + 1].nombre) {
                usuario temp = lista_usuarios[j];
                lista_usuarios[j] = lista_usuarios[j + 1];
                lista_usuarios[j + 1] = temp;
            }
        }
    }
}

/*  
* Nombre: buscar_usuario  
* Descripci�n: Busca un usuario por nombre usando b�squeda binaria.  
* Par�metros: nombre - nombre del usuario a buscar.  
* Retorna: int - �ndice del usuario si se encuentra, -1 si no.  
*/  
int buscar_usuario(const string& nombre) {
    int inicio = 0;
    int fin = numero_usuarios - 1;

    while (inicio <= fin) {
        int medio = (inicio + fin) / 2;
        if (lista_usuarios[medio].nombre == nombre) {
            return medio;
        } else if (lista_usuarios[medio].nombre < nombre) {
            inicio = medio + 1;
        } else {
            fin = medio - 1;
        }
    }
    return -1;
}
/*  
* Nombre: registrar_usuario  
* Descripci�n: Registra un nuevo usuario en el sistema.  
* Par�metros: ninguno.  
* Retorna: nada.  
*/  
void registrar_usuario() {
    string nombre, contrasena;
    int opcion;

    cout << "\n";
    texto_centrado("--------------- REGISTRO DE USUARIO ---------------");
    cout << "\n\n";

    texto_centrado("Ingrese nombre de usuario: ");
    cin.ignore();
    getline(cin, nombre);

    texto_centrado("Ingrese contrasena (max 8 caracteres): ");
    contrasena = ingresar_contrasena();

    do {
        cout << "\n";
        texto_centrado("Seleccione tipo (1. Cliente, 2. Administrador): ");
        cin >> opcion;
    } while (opcion != 1 && opcion != 2);

    string tipo = (opcion == 1) ? "cliente" : "admin";

    lista_usuarios[numero_usuarios].nombre = nombre;
    lista_usuarios[numero_usuarios].contrasena = contrasena;
    lista_usuarios[numero_usuarios].tipo = tipo;
    numero_usuarios++;

    ordenar_usuarios();

    cout << "\n";
    texto_centrado("Usuario registrado exitosamente!");
    cout << "\n\n";
}

/*  
* Nombre: menu_administrador  
* Descripci�n: Muestra y maneja el men� de opciones para administradores.  
* Par�metros: nombre - nombre del administrador actual.  
* Retorna: nada.  
*/  
void menu_administrador(const string& nombre) {
    int opcion;

    do {
        cout << "\n";
        texto_centrado("------------ MENU DEL ADMIN ------------\n");
        texto_centrado("Bienvenido, " + nombre + ".\n");
        texto_centrado("1. Opci�n 1\n");
        texto_centrado("2. Opci�n 2\n");
        texto_centrado("3. Opci�n 3\n");
        texto_centrado("4. Opci�n 4\n");
        texto_centrado("5. Opci�n 5\n");
        texto_centrado("6. Cerrar sesi�n\n");
        texto_centrado("Seleccione una opci�n: ");
        cin >> opcion;
        texto_centrado("--------------------------------------------\n");

        switch (opcion) {
            case 1:
                texto_centrado("Ejecutando Opci�n 1...\n\n");
                break;
            case 2:
                texto_centrado("Ejecutando Opci�n 2...\n\n");
                break;
            case 3:
                texto_centrado("Ejecutando Opci�n 3...\n\n");
                break;
            case 4:
                texto_centrado("Ejecutando Opci�n 4...\n\n");
                break;
            case 5:
                texto_centrado("Ejecutando Opci�n 5...\n\n");
                break;
            case 6:
                texto_centrado("Sesi�n cerrada.\n\n");
                break;
            default:
                texto_centrado("Opci�n inv�lida.\n\n");
        }
    } while (opcion != 6);
}
/*  
* Nombre: menu_cliente  
* Descripci�n: Muestra y maneja el men� de opciones para clientes.  
* Par�metros: nombre - nombre del cliente actual.  
* Retorna: nada.  
*/  
void menu_cliente(const string& nombre) {
    int opcion;

    do {
        texto_centrado("--------------- MENU DEL CLIENTE ---------------\n");
        texto_centrado("Bienvenido, " + nombre +".\n");
        texto_centrado("1. Opci�n 1\n");
        texto_centrado("2. Opci�n 2\n");
        texto_centrado("3. Opci�n 3\n");
        texto_centrado("4. Cerrar sesi�n\n");
        texto_centrado("Seleccione una opci�n: ");
        cin >> opcion;
        texto_centrado("------------------------------------------------\n");

        switch (opcion) {
            case 1:
                texto_centrado("Ejecutando Opci�n 1...\n\n");
                break;
            case 2:
                texto_centrado("Ejecutando Opci�n 2...\n\n");
                break;
            case 3:
                texto_centrado("Ejecutando Opci�n 3...\n\n");
                break;
            case 4:
                texto_centrado("Sesi�n cerrada.\n\n");
                break;
            default:
                texto_centrado("Opci�n inv�lida.\n\n");
        }
    } while (opcion != 4);
}

/*  
* Nombre: iniciar_sesion  
* Descripci�n: Solicita usuario y contrase�a y valida inicio de sesi�n.  
* Par�metros: ninguno.  
* Retorna: true si inicio de sesi�n exitoso, false en caso contrario.  
*/  
bool iniciar_sesion() {
    string nombre, contrasena;
    int intentos = 0;
    bool exito = false;

    while (intentos < 3 && !exito) {
        cout << "\n";
        texto_centrado("--------------- INICIO DE SESION ---------------\n");
        texto_centrado("Nombre de usuario: ");
        cin.ignore();
        getline(cin, nombre);

        texto_centrado("Contrasena: ");
        contrasena = ingresar_contrasena();

        int indice = -1;
        for (int i = 0; i < numero_usuarios; i++) {
            if (lista_usuarios[i].nombre == nombre) {
                indice = i;
                break;
            }
        }

        if (indice != -1) {
		    if (lista_usuarios[indice].contrasena == contrasena) {
		        cout << "\n";
		        texto_centrado("Inicio de sesi�n exitoso.");
		        cout << "\n";
		
		        if (lista_usuarios[indice].tipo == "cliente") {
		            cola_clientes.push(nombre);
		            cout << "\n";
		            texto_centrado("Accediste como CLIENTE.");
		            cout << "\n";
		            menu_cliente(nombre);
		        } else {
		            pila_admins.push(nombre);
		            cout << "\n";
		            texto_centrado("Accediste como ADMINISTRADOR.");
		            menu_administrador(nombre);
		        }
		
		        exito = true;
		    } else {
		        intentos++;
		        cout << "\n";
		        texto_centrado("Contrasena incorrecta.\n");
		
		        if (intentos == 1) texto_centrado("Intento 1 de 3.\n");
		        else if (intentos == 2) texto_centrado("Intento 2 de 3.\n");
		        else texto_centrado("Intento 3 de 3.\n");
		
		        cout << "\n";
		    }
		} else {
		    intentos++;
		    cout << "\n";
		    texto_centrado("Usuario no encontrado.\n");
		
		    if (intentos == 1) texto_centrado("Intento 1 de 3.\n");
		    else if (intentos == 2) texto_centrado("Intento 2 de 3.\n");
		    else texto_centrado("Intento 3 de 3.\n");
		
		    cout << "\n";
	        }
    }

    if (!exito) {
        texto_centrado("Demasiados intentos. Saliendo...");
        cout << "\n";
    }

    return exito;
}

/*  
* Nombre: menu_principal  
* Descripci�n: Muestra y maneja el men� principal del sistema.  
* Par�metros: ninguno.  
* Retorna: nada.  
*/  
void menu_principal() {
    int opcion;

    do {
        texto_centrado("--------------- MENU PRINCIPAL ---------------\n");
        texto_centrado("1. Registrar usuario\n");
        texto_centrado("2. Iniciar sesi�n\n");
        texto_centrado("3. Salir\n");
        texto_centrado("Seleccione una opci�n: ");

        cin >> opcion;

        switch (opcion) {
            case 1:
                registrar_usuario();
                break;
            case 2:
                iniciar_sesion();
                break;
            case 3:
                texto_centrado("Saliendo del programa...\n");
                break;
            default:
                texto_centrado("Opci�n inv�lida.\n");
        }
        cout << "\n";
    } while (opcion != 3);
}
/*  
* Nombre: main  
* Descripci�n: Funci�n principal que inicia el programa. Predefine dos usuarios  
* (un administrador y un cliente) y lanza el men� principal.  
* Par�metros: ninguno.  
* Retorna: int - c�digo de salida del programa.  
*/  
int main() {
    setlocale(LC_ALL, "Spanish");
    lista_usuarios[0].nombre = "admin";
    lista_usuarios[0].contrasena = "admin123";
    lista_usuarios[0].tipo = "admin";

    lista_usuarios[1].nombre = "brayan";
    lista_usuarios[1].contrasena = "123";
    lista_usuarios[1].tipo = "cliente";

    numero_usuarios = 2;

    ordenar_usuarios(); 
    ordenar_usuarios();
    menu_principal();
    return 0;
}


