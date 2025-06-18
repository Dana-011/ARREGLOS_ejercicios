#include <iostream>
#include <string>
#include <stack>
#include <queue>
using namespace std;

const int MAX_PLATOS = 100;
const int MAX_PEDIDOS = 100;
const int MAX_VENTAS = 100;

struct Plato {
    int codigo;
    string nombre;
    int tiempoPreparacion;
    double precio;
};

struct Pedido {
    int codigoPlato;
    int cantidad;
};

struct Venta {
    int codigoPlato;
    int cantidad;
    double monto;
};

Plato lista_platos[MAX_PLATOS];
int num_platos = 0;

queue<Pedido> cola_pedidos;
Venta registro_ventas[MAX_VENTAS];
int num_ventas = 0;

void texto_centrado(string texto) {
    int espacios = 30;
    for (int i = 0; i < espacios; i++) cout << " ";
    cout << texto << endl;
}

void registrar_plato() {
    if (num_platos >= MAX_PLATOS) {
        cout << "No se pueden registrar m‡s platos." << endl;
        return;
    }
    Plato p;
    cout << "Ingrese el codigo del plato (numero entero): ";
    cin >> p.codigo;
    cin.ignore();

    cout << "Ingrese el nombre del plato: ";
    getline(cin, p.nombre);

    cout << "Ingrese el tiempo de preparacion (minutos): ";
    cin >> p.tiempoPreparacion;

    cout << "Ingrese el precio del plato: ";
    cin >> p.precio;

    lista_platos[num_platos++] = p;
    cout << "Plato registrado con exito." << endl;
}

void ordenar_platos() {
    for (int i = 0; i < num_platos - 1; i++) {
        for (int j = 0; j < num_platos - i - 1; j++) {
            if (lista_platos[j].nombre > lista_platos[j + 1].nombre) {
                Plato temp = lista_platos[j];
                lista_platos[j] = lista_platos[j + 1];
                lista_platos[j + 1] = temp;
            }
        }
    }
}

int busqueda_binaria(string nombre) {
    int low = 0, high = num_platos - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (lista_platos[mid].nombre == nombre)
            return mid;
        else if (lista_platos[mid].nombre < nombre)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

void agregar_pedido() {
    Pedido p;
    cout << "Ingrese codigo del plato a pedir: ";
    cin >> p.codigoPlato;
    cout << "Ingrese cantidad: ";
    cin >> p.cantidad;
    cola_pedidos.push(p);
    cout << "Pedido agregado a la cola." << endl;
}

void procesar_pedido() {
    if (cola_pedidos.empty()) {
        cout << "No hay pedidos para procesar." << endl;
        return;
    }
    Pedido p = cola_pedidos.front();
    cola_pedidos.pop();

    bool encontrado = false;
    for (int i = 0; i < num_platos; i++) {
        if (lista_platos[i].codigo == p.codigoPlato) {
            double monto = p.cantidad * lista_platos[i].precio;
            if (num_ventas < MAX_VENTAS) {
                registro_ventas[num_ventas].codigoPlato = p.codigoPlato;
                registro_ventas[num_ventas].cantidad = p.cantidad;
                registro_ventas[num_ventas].monto = monto;
                num_ventas++;
            }

            cout << "Pedido procesado: " << p.cantidad << " x " << lista_platos[i].nombre
                 << " Total: " << monto << endl;
            encontrado = true;
            break;
        }
    }
    if (!encontrado) {
        cout << "Plato con codigo " << p.codigoPlato << " no encontrado." << endl;
    }
}

void mostrar_menu() {
    cout << "------- MENU DE PLATOS -------" << endl;
    for (int i = 0; i < num_platos; i++) {
        cout << lista_platos[i].codigo << " - " << lista_platos[i].nombre
             << " Tiempo: " << lista_platos[i].tiempoPreparacion << " min"
             << " Precio: " << lista_platos[i].precio << endl;
    }
    cout << "-----------------------------" << endl;
}

int main() {
    int opcion;
    do {
        cout << "\nPPLATo" << endl;
        cout << "1. Registrar plato" << endl;
        cout << "2. Mostrar menu ordenado" << endl;
        cout << "3. Buscar plato por nombre" << endl;
        cout << "4. Agregar pedido" << endl;
        cout << "5. Procesar pedido" << endl;
        cout << "6. Salir" << endl;
        cout << "Seleccione opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                registrar_plato();
                break;
            case 2:
                ordenar_platos();
                mostrar_menu();
                break;
            case 3: {
                string nombreBuscar;
                cout << "Ingrese nombre del plato a buscar: ";
                cin.ignore();
                getline(cin, nombreBuscar);
                int resultado = busqueda_binaria(nombreBuscar);
                if (resultado != -1) {
                    cout << "Plato encontrado: " << lista_platos[resultado].nombre
                         << " Codigo: " << lista_platos[resultado].codigo
                         << " Precio: " << lista_platos[resultado].precio << endl;
                } else {
                    cout << "Plato no encontrado." << endl;
                }
                break;
            }
            case 4:
                agregar_pedido();
                break;
            case 5:
                procesar_pedido();
                break;
            case 6:
                cout << "Saliendo" << endl;
                break;
            default:
                cout << "Opcion invalida" << endl;
        }
    } while (opcion != 6);

    return 0;
}
