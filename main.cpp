#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct Avion {
    int placa;
    char aerolinea[30];
    int capPasajeros;
};

const int MAX_AVIONES = 100; // Límite máximo de aviones
Avion aviones[MAX_AVIONES];
int numAviones = 0;

void leerAvion(Avion& a) {
    cout << "Placa: ";
    cin >> a.placa;
    cout << "Aerolinea: ";
    cin.ignore(); // para limpiar el buffer de entrada
    cin.getline(a.aerolinea, 30);
    cout << "Capacidad de pasajeros: ";
    cin >> a.capPasajeros;
}

void mostrarAvion(const Avion& a) {
    cout << "Placa: " << a.placa << " Aerolinea: " << a.aerolinea << " Capacidad de pasajeros: " << a.capPasajeros << endl;
}

void cargarAvionesDesdeArchivo() {
    ifstream archivo("aviones.bin", ios::binary);
    if (!archivo) return;
    while (archivo.read((char*)&aviones[numAviones], sizeof(Avion)) && numAviones < MAX_AVIONES) {
        numAviones++;
    }
    archivo.close();
}

void guardarAvionesEnArchivo() {
    ofstream archivo("aviones.bin", ios::binary | ios::trunc);
    for (int i = 0; i < numAviones; i++) {
        archivo.write((char*)&aviones[i], sizeof(Avion));
    }
    archivo.close();
}

void registrarAvion() {
    if (numAviones < MAX_AVIONES) {
        leerAvion(aviones[numAviones]);
        numAviones++;
        guardarAvionesEnArchivo();
    } else {
        cout << "No se pueden registrar más aviones, capacidad máxima alcanzada." << endl;
    }
}

void mostrarTodosLosAviones() {
    for (int i = 0; i < numAviones; i++) {
        mostrarAvion(aviones[i]);
    }
}

void buscarAvionPorPlaca() {
    int placa;
    cout << "Ingrese la placa del avion: ";
    cin >> placa;
    for (int i = 0; i < numAviones; i++) {
        if (aviones[i].placa == placa) {
            mostrarAvion(aviones[i]);
            return;
        }
    }
    cout << "Avion no encontrado." << endl;
}

void buscarAvionesPorAerolinea() {
    char aerolinea[30];
    cout << "Ingrese la aerolinea: ";
    cin.ignore();
    cin.getline(aerolinea, 30);
    bool encontrado = false;
    for (int i = 0; i < numAviones; i++) {
        if (strcmp(aviones[i].aerolinea, aerolinea) == 0) {
            mostrarAvion(aviones[i]);
            encontrado = true;
        }
    }
    if (!encontrado) {
        cout << "No se encontraron aviones para la aerolinea " << aerolinea << "." << endl;
    }
}

void ordenarYMostrarAvionesPorPlaca() {
    for (int i = 0; i < numAviones - 1; i++) {
        for (int j = 0; j < numAviones - i - 1; j++) {
            if (aviones[j].placa > aviones[j + 1].placa) {
                Avion temp = aviones[j];
                aviones[j] = aviones[j + 1];
                aviones[j + 1] = temp;
            }
        }
    }
    mostrarTodosLosAviones();
}

void ordenarYMostrarAvionesPorCapacidad() {
    for (int i = 0; i < numAviones - 1; i++) {
        for (int j = 0; j < numAviones - i - 1; j++) {
            if (aviones[j].capPasajeros > aviones[j + 1].capPasajeros) {
                Avion temp = aviones[j];
                aviones[j] = aviones[j + 1];
                aviones[j + 1] = temp;
            }
        }
    }
    mostrarTodosLosAviones();
}

void eliminarAvionPorPlaca() {
    int placa;
    cout << "Ingrese la placa del avion a eliminar: ";
    cin >> placa;
    for (int i = 0; i < numAviones; i++) {
        if (aviones[i].placa == placa) {
            for (int j = i; j < numAviones - 1; j++) {
                aviones[j] = aviones[j + 1];
            }
            numAviones--;
            guardarAvionesEnArchivo();
            cout << "Avion eliminado." << endl;
            return;
        }
    }
    cout << "Avion no encontrado." << endl;
}

void editarAvionPorPlaca() {
    int placa;
    cout << "Ingrese la placa del avion a editar: ";
    cin >> placa;
    for (int i = 0; i < numAviones; i++) {
        if (aviones[i].placa == placa) {
            cout << "Ingrese la nueva aerolinea: ";
            cin.ignore();
            cin.getline(aviones[i].aerolinea, 30);
            cout << "Ingrese la nueva capacidad de pasajeros: ";
            cin >> aviones[i].capPasajeros;
            guardarAvionesEnArchivo();
            cout << "Avion editado." << endl;
            return;
        }
    }
    cout << "Avion no encontrado." << endl;
}

void menu() {
    cargarAvionesDesdeArchivo();
    int opcion;
    do {
        cout << "\n--- Menu ---\n";
        cout << "1. Registrar avion\n";
        cout << "2. Mostrar todos los aviones\n";
        cout << "3. Buscar avion por placa\n";
        cout << "4. Buscar aviones por aerolinea\n";
        cout << "5. Ordenar aviones por placa\n";
        cout << "6. Ordenar aviones por capacidad\n";
        cout << "7. Eliminar avion por placa\n";
        cout << "8. Editar avion por placa\n";
        cout << "9. Salir\n";
        cout << "Ingrese una opcion: ";
        cin >> opcion;
        switch(opcion) {
            case 1:
                registrarAvion();
                break;
            case 2:
                mostrarTodosLosAviones();
                break;
            case 3:
                buscarAvionPorPlaca();
                break;
            case 4:
                buscarAvionesPorAerolinea();
                break;
            case 5:
                ordenarYMostrarAvionesPorPlaca();
                break;
            case 6:
                ordenarYMostrarAvionesPorCapacidad();
                break;
            case 7:
                eliminarAvionPorPlaca();
                break;
            case 8:
                editarAvionPorPlaca();
                break;
            case 9:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opcion invalida, intente nuevamente.\n";
        }
    } while(opcion != 9);
}

int main() {
    menu();
    return 0;
}
