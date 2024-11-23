#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <chrono>
#include <thread>
#include <unordered_set>
#include <iomanip>

using namespace std;

struct Proceso {
    string nombreProgramador;
    char operacion;
    int dato1;
    int dato2;
    int tiempoMaximo;
    int numeroPrograma;
};

struct Lote {
    vector<Proceso> procesos;
};

void capturarProceso(vector<Proceso>& procesos, unordered_set<int>& ids) {
    Proceso p;
    cout << "\nNombre del Programador: ";
    cin >> p.nombreProgramador;

    do {
        cout << "Operacion a realizar (+, -, *, /, %): ";
        cin >> p.operacion;
    } while (p.operacion != '+' && p.operacion != '-' && p.operacion != '*' && p.operacion != '/' && p.operacion != '%');

    cout << "Dato 1: ";
    cin >> p.dato1;

    do {
        cout << "Dato 2: ";
        cin >> p.dato2;
        if ((p.operacion == '/' || p.operacion == '%') && p.dato2 == 0) {
            cout << "Dato 2 no puede ser 0 para esta operacion, ingrese otro numero.\n";
        }
    } while ((p.operacion == '/' || p.operacion == '%') && p.dato2 == 0);

    do {
        cout << "Tiempo Maximo Estimado (en segundos): ";
        cin >> p.tiempoMaximo;
    } while (p.tiempoMaximo <= 0);

    do {
        cout << "Numero de Programa (ID unico): ";
        cin >> p.numeroPrograma;
    } while (ids.find(p.numeroPrograma) != ids.end());

    ids.insert(p.numeroPrograma);
    procesos.push_back(p);
}

void mostrarProcesosEnColumnas(const vector<Proceso>& procesos) {
    const int anchoColumna = 25; // Ajusta el ancho de cada columna

    // Encabezados
    cout << left << setw(anchoColumna) << "Proceso:";
    for (size_t i = 0; i < procesos.size(); ++i) {
        cout << left << setw(anchoColumna) << ("Proceso #" + to_string(i + 1));
    }
    cout << endl;

    // Nombre del Programador
    cout << left << setw(anchoColumna) << "Nombre:";
    for (const auto& p : procesos) {
        cout << left << setw(anchoColumna) << p.nombreProgramador;
    }
    cout << endl;

    // Operacion
    cout << left << setw(anchoColumna) << "Operacion:";
    for (const auto& p : procesos) {
        cout << left << setw(anchoColumna) << p.operacion;
    }
    cout << endl;

    // Dato 1
    cout << left << setw(anchoColumna) << "Dato 1:";
    for (const auto& p : procesos) {
        cout << left << setw(anchoColumna) << p.dato1;
    }
    cout << endl;

    // Dato 2
    cout << left << setw(anchoColumna) << "Dato 2:";
    for (const auto& p : procesos) {
        cout << left << setw(anchoColumna) << p.dato2;
    }
    cout << endl;

    // Tiempo Maximo Estimado
    cout << left << setw(anchoColumna) << "Tiempo Maximo:";
    for (const auto& p : procesos) {
        cout << left << setw(anchoColumna) << p.tiempoMaximo;
    }
    cout << endl;

    // Numero de Programa
    cout << left << setw(anchoColumna) << "Numero Programa:";
    for (const auto& p : procesos) {
        cout << left << setw(anchoColumna) << p.numeroPrograma;
    }
    cout << endl;
}

void ejecutarProcesosEnColumnas(const vector<Proceso>& procesos) {
    const int anchoColumna = 25; // Ajusta el ancho de cada columna

    // Encabezados
    cout << left << setw(anchoColumna) << "\nEjecutando Proceso:";
    for (size_t i = 0; i < procesos.size(); ++i) {
        cout << left << setw(anchoColumna) << ("Proceso #" + to_string(i + 1));
    }
    cout << endl;

    // Nombre del Programador
    cout << left << setw(anchoColumna) << "Nombre del Programador:";
    for (const auto& p : procesos) {
        cout << left << setw(anchoColumna) << p.nombreProgramador;
    }
    cout << endl;

    // Operacion
    cout << left << setw(anchoColumna) << "Operacion:";
    for (const auto& p : procesos) {
        cout << left << setw(anchoColumna) << p.operacion;
    }
    cout << endl;

    // Tiempo Maximo Estimado
    cout << left << setw(anchoColumna) << "Tiempo Maximo Estimado:";
    for (const auto& p : procesos) {
        cout << left << setw(anchoColumna) << p.tiempoMaximo;
    }
    cout << endl;

    // Numero de Programa
    cout << left << setw(anchoColumna) << "Numero de Programa:";
    for (const auto& p : procesos) {
        cout << left << setw(anchoColumna) << p.numeroPrograma;
    }
    cout << endl;

    // Simulación de ejecución del tiempo para cada proceso
    for (int sec = 0; sec < procesos[0].tiempoMaximo; ++sec) {
        // Primera columna con el texto completo
        cout << left << setw(anchoColumna) << ("Tiempo transcurrido:     " + to_string(sec + 1) + " seg");

        // Las demás columnas solo con el tiempo
        for (size_t i = 1; i < procesos.size(); ++i) {
            cout << left << setw(anchoColumna) << (to_string(sec + 1) + " seg");
        }
        cout << endl;
    }

    // Tiempo restante
    cout << left << setw(anchoColumna) << "Tiempo restante:";
    for (size_t i = 0; i < procesos.size(); ++i) {
        cout << left << setw(anchoColumna) << "0 seg";
    }
    cout << endl;

    // Resultado de la operacion
    cout << left << setw(anchoColumna) << "Resultado:";
    for (const auto& p : procesos) {
        int resultado;
        switch (p.operacion) {
            case '+': resultado = p.dato1 + p.dato2; break;
            case '-': resultado = p.dato1 - p.dato2; break;
            case '*': resultado = p.dato1 * p.dato2; break;
            case '/': resultado = p.dato1 / p.dato2; break;
            case '%': resultado = p.dato1 % p.dato2; break;
        }
        cout << left << setw(anchoColumna) << resultado;
    }
    cout << endl;
}

void mostrarLoteLateral(const Lote& lote, int numeroLote) {
    cout << "\nLote #" << numeroLote << "\n" << endl;

    // Encabezados
    cout << left << setw(20) << "Proceso" << setw(20) << "Nombre" << setw(20) << "Operacion" << setw(20) << "Dato 1" << setw(20) << "Dato 2" << setw(20) << "Tiempo Maximo" << setw(20) << "Numero Programa" << endl;

    for (size_t i = 0; i < lote.procesos.size(); ++i) {
        const Proceso& p = lote.procesos[i];
        cout << left << setw(20) << ("Proceso #" + to_string(i + 1))
             << setw(20) << p.nombreProgramador
             << setw(20) << p.operacion
             << setw(20) << p.dato1
             << setw(20) << p.dato2
             << setw(20) << p.tiempoMaximo
             << setw(20) << p.numeroPrograma
             << endl;
    }
}

int main() {
    vector<Proceso> procesos;
    unordered_set<int> ids;
    int n;

    cout << "Introduce el numero de procesos: ";
    cin >> n;

    for (int i = 0; i < n; ++i) {
        capturarProceso(procesos, ids);
    }

    queue<Lote> lotes;
    Lote loteActual;

    for (const auto& proceso : procesos) {
        if (loteActual.procesos.size() == 5) {
            lotes.push(loteActual);
            loteActual.procesos.clear();
        }
        loteActual.procesos.push_back(proceso);
    }

    if (!loteActual.procesos.empty()) {
        lotes.push(loteActual);
    }

    auto start = chrono::steady_clock::now();
    int numeroLote = 1;

    while (!lotes.empty()) {
        Lote lote = lotes.front();
        lotes.pop();

        mostrarLoteLateral(lote, numeroLote);
        numeroLote++;

        ejecutarProcesosEnColumnas(lote.procesos);

        cout << "\nLotes pendientes: " << lotes.size() << endl;
    }

    auto end = chrono::steady_clock::now();
    auto diff = end - start;
    cout << "\nContador Global: " << chrono::duration<double>(diff).count() << " segundos" << endl;

    cout << "\nTodos los procesos han sido ejecutados. Pausando programa..." << endl;
    cin.get();
    cin.get();

    return 0;
}

