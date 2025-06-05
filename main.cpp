#include <iostream>
#include <conio.h>
#include <string>
#include <stack>
#include <queue>

using namespace std;

const int MAX_USUARIOS = 100;       // Máximo número de usuarios permitidos
const int CONSOLE_WIDTH = 80;       // Ancho de la consola para centrar texto

// Estructura para almacenar información de un usuario
struct usuario {
    string nombre;      // Nombre del usuario
    string contrasena;  // Contraseña del usuario
    string tipo;        // Tipo de usuario (cliente o admin)
};

usuario lista_usuarios[MAX_USUARIOS];  // Array para almacenar usuarios registrados
int numero_usuarios = 0;               // Contador de usuarios registrados

stack<string> pila_admins;     // Pila para almacenar nombres de administradores activos
queue<string> cola_clientes;   // Cola para almacenar nombres de clientes activos

/*  
* Nombre: texto_centrado  
* Descripción: Centra un texto en la consola basado en el ancho definido.  
* Parámetros: texto - cadena a centrar.  
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
* Descripción: Permite ingresar una contraseña ocultando los caracteres con asteriscos.  
* Parámetros: ninguno.  
* Retorna: string - contraseña ingresada por el usuario.  
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
* Descripción: Ordena los usuarios alfabéticamente por nombre usando ordenamiento de burbuja.  
* Parámetros: ninguno.  
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
* Descripción: Busca un usuario por nombre usando búsqueda binaria.  
* Parámetros: nombre - nombre del usuario a buscar.  
* Retorna: int - índice del usuario si se encuentra, -1 si no.  
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
* Descripción: Registra un nuevo usuario en el sistema.  
* Parámetros: ninguno.  
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
* Descripción: Muestra y maneja el menú de opciones para administradores.  
* Parámetros: nombre - nombre del administrador actual.  
* Retorna: nada.  
*/  
void menu_administrador(const string& nombre) {
    int opcion;

    do {
        cout << "\n";
        texto_centrado("------------ MENU DEL ADMIN ------------\n");
        texto_centrado("Bienvenido, " + nombre + ".\n");
        texto_centrado("1. Opción 1\n");
        texto_centrado("2. Opción 2\n");
        texto_centrado("3. Opción 3\n");
        texto_centrado("4. Opción 4\n");
        texto_centrado("5. Opción 5\n");
        texto_centrado("6. Cerrar sesión\n");
        texto_centrado("Seleccione una opción: ");
        cin >> opcion;
        texto_centrado("--------------------------------------------\n");

        switch (opcion) {
            case 1:
                texto_centrado("Ejecutando Opción 1...\n\n");
                break;
            case 2:
                texto_centrado("Ejecutando Opción 2...\n\n");
                break;
            case 3:
                texto_centrado("Ejecutando Opción 3...\n\n");
                break;
            case 4:
                texto_centrado("Ejecutando Opción 4...\n\n");
                break;
            case 5:
                texto_centrado("Ejecutando Opción 5...\n\n");
                break;
            case 6:
                texto_centrado("Sesión cerrada.\n\n");
                break;
            default:
                texto_centrado("Opción inválida.\n\n");
        }
    } while (opcion != 6);
}
/*  
* Nombre: menu_cliente  
* Descripción: Muestra y maneja el menú de opciones para clientes.  
* Parámetros: nombre - nombre del cliente actual.  
* Retorna: nada.  
*/  
void menu_cliente(const string& nombre) {
    int opcion;

    do {
        texto_centrado("--------------- MENU DEL CLIENTE ---------------\n");
        texto_centrado("Bienvenido, " + nombre +".\n");
        texto_centrado("1. Opción 1\n");
        texto_centrado("2. Opción 2\n");
        texto_centrado("3. Opción 3\n");
        texto_centrado("4. Cerrar sesión\n");
        texto_centrado("Seleccione una opción: ");
        cin >> opcion;
        texto_centrado("------------------------------------------------\n");

        switch (opcion) {
            case 1:
                texto_centrado("Ejecutando Opción 1...\n\n");
                break;
            case 2:
                texto_centrado("Ejecutando Opción 2...\n\n");
                break;
            case 3:
                texto_centrado("Ejecutando Opción 3...\n\n");
                break;
            case 4:
                texto_centrado("Sesión cerrada.\n\n");
                break;
            default:
                texto_centrado("Opción inválida.\n\n");
        }
    } while (opcion != 4);
}

/*  
* Nombre: iniciar_sesion  
* Descripción: Solicita usuario y contraseña y valida inicio de sesión.  
* Parámetros: ninguno.  
* Retorna: true si inicio de sesión exitoso, false en caso contrario.  
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
		        texto_centrado("Inicio de sesión exitoso.");
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
* Descripción: Muestra y maneja el menú principal del sistema.  
* Parámetros: ninguno.  
* Retorna: nada.  
*/  
void menu_principal() {
    int opcion;

    do {
        texto_centrado("--------------- MENU PRINCIPAL ---------------\n");
        texto_centrado("1. Registrar usuario\n");
        texto_centrado("2. Iniciar sesión\n");
        texto_centrado("3. Salir\n");
        texto_centrado("Seleccione una opción: ");

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
                texto_centrado("Opción inválida.\n");
        }
        cout << "\n";
    } while (opcion != 3);
}
/*  
* Nombre: main  
* Descripción: Función principal que inicia el programa. Predefine dos usuarios  
* (un administrador y un cliente) y lanza el menú principal.  
* Parámetros: ninguno.  
* Retorna: int - código de salida del programa.  
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


