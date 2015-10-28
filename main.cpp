#include <iostream>

using namespace std;


void menu ()
{
    cout << endl << endl << endl;
    cout << "Proyecto Algoritmos Sección F 2015" << endl;
    cout << "==================================" << endl;
    cout << "Menú de opciones:" << endl;
    cout << " 1) Datos de la empresa" << endl;
    cout << " 2) Departamentos de la empresa" << endl;
    cout << " 3) Puestos de trabajo" << endl;
    cout << " 4) Empleados" << endl;
    cout << " 5) Evaluación de empleados" << endl;
    cout << " 6) Salir" << endl;
    cout << "Seleccione una opción: ";

}

int main()
{
    int salir = 0; // Salir del sistema
    int menu;

    while (!salir) {
        menu();
        cin >> menu;
        switch (menu) {
            case 1: // Datos de empresa
                break;
            case 2: // Departamentos
                break;
            case 3: // Puestos de trabajo
                break;
            case 4: // Empleados
                break;
            case 5: // Evaluación de empleados
                break;
            case 6: salir = 1; // Verdadero
                break;
            default:
                cout << "*** Opición inválida ***" << endl << endl;

        }
    }


    return 0;
}
