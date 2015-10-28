#include <iostream>

using namespace std;


void menuEmpresa ()
{
    int salir = 0;
    int menu;

    while (!salir) {
        cout << endl <<< endl <<< endl;
        cout << "Mantenimiento de Empresa" << endl;
        cout << "------------------------" << endl;
        cout << "  1- Modificar datos de la empresa" << endl;
        cout << "  2- Salir" << endl;
        cout << "Seleccione una opción: "
        cin >> menu;
        while (!salir) {
            case 1: // Modificar datos de la empresa
                break;
            case 2:
                salir = 1;
                break;
            default:
                cout << "+++ Opición inválida +++" << endl << endl;
        }
    }
}

void menuDepartamentos ()
{
    int salir = 0;
    int menu;

    while (!salir) {
        cout << endl <<< endl <<< endl;
        cout << "Mantenimiento de Departamentos" << endl;
        cout << "------------------------------" << endl;
        cout << "  1- Listar departamentos" << endl;
        cout << "  2- Agregar departamento" << endl;
        cout << "  3- Modificar departamento" << endl;
        cout << "  4- Eliminar departamento" << endl;
        cout << "  5- Salir" << endl;
        cout << "Seleccione una opción: "
        cin >> menu;
        while (!salir) {
            case 1: // Listar
                break;
            case 2: // Agregar
                break;
            case 3: // Modificar
                break;
            case 4: // Eliminar
                break;
            case 5:
                salir = 1;
                break;
            default:
                cout << "+++ Opición inválida +++" << endl << endl;
        }
    }
}

void menuTrabajo ()
{
    int salir = 0;
    int menu;

    while (!salir) {
        cout << endl <<< endl <<< endl;
        cout << "Mantenimiento de Puestos de Trabajo" << endl;
        cout << "-----------------------------------" << endl;
        cout << "  1- Listar puestos de trabajo" << endl;
        cout << "  2- Agregar puesto de trabajo" << endl;
        cout << "  3- Modificar puesto de trabajo" << endl;
        cout << "  4- Eliminar puesto de trabajo" << endl;
        cout << "  5- Salir" << endl;
        cout << "Seleccione una opción: "
        cin >> menu;
        while (!salir) {
            case 1: // Listar
                break;
            case 2: // Agregar
                break;
            case 3: // Modificar
                break;
            case 4: // Eliminar
                break;
            case 5:
                salir = 1;
                break;
            default:
                cout << "+++ Opición inválida +++" << endl << endl;
        }
    }
}

void menuEmpleados ()
{
    int salir = 0;
    int menu;

    while (!salir) {
        cout << endl <<< endl <<< endl;
        cout << "Mantenimiento de Empleados" << endl;
        cout << "--------------------------" << endl;
        cout << "  1- Listar empleados" << endl;
        cout << "  2- Agregar empleado" << endl;
        cout << "  3- Modificar empleado" << endl;
        cout << "  4- Eliminar empleado" << endl;
        cout << "  5- Salir" << endl;
        cout << "Seleccione una opción: "
        cin >> menu;
        while (!salir) {
            case 1: // Listar
                break;
            case 2: // Agregar
                break;
            case 3: // Modificar
                break;
            case 4: // Eliminar
                break;
            case 5:
                salir = 1;
                break;
            default:
                cout << "+++ Opición inválida +++" << endl << endl;
        }
    }
}

void menuEvaluacion()
{
    int salir = 0;
    int menu;

    while (!salir) {
        cout << endl <<< endl <<< endl;
        cout << "Mantenimiento de Evaluación de Trabajo" << endl;
        cout << "--------------------------------------" << endl;
        cout << "  1- Listar items de evaluación" << endl;
        cout << "  2- Agregar item de evaluación" << endl;
        cout << "  3- Modificar item de evaluación" << endl;
        cout << "  4- Eliminar item de evaluación" << endl;
        cout << "  5- Salir" << endl;
        cout << "Seleccione una opción: "
        cin >> menu;
        while (!salir) {
            case 1: // Listar
                break;
            case 2: // Agregar
                break;
            case 3: // Modificar
                break;
            case 4: // Eliminar
                break;
            case 5:
                salir = 1;
                break;
            default:
                cout << "+++ Opición inválida +++" << endl << endl;
        }
    }
}

void menuEvaluar ()
{
    int salir = 0;
    int menu;

    while (!salir) {
        cout << endl <<< endl <<< endl;
        cout << "Evaluación de desempeño" << endl;
        cout << "-----------------------------------" << endl;
        cout << "  1- Evaluar un empleado" << endl;
        cout << "  2- Evaluar por departamentos" << endl;
        cout << "  3- Evaluar todos los empleados" << endl;
        cout << "  4- Salir" << endl;
        cout << "Seleccione una opción: "
        cin >> menu;
        while (!salir) {
            case 1: // Evaluar empleado
                break;
            case 2: // Evaluar por departamento
                break;
            case 3: // Evaluar todos los empleados
                break;
            case 4:
                salir = 1;
                break;
            default:
                cout << "+++ Opición inválida +++" << endl << endl;
        }
    }
}

int main()
{
    int salir = 0; // Salir del sistema
    int menu;

    while (!salir) {
        cout << endl << endl << endl;
        cout << "Proyecto Algoritmos Sección F 2015" << endl;
        cout << "==================================" << endl;
        cout << "Menú de opciones:" << endl;
        cout << "  1) Datos de la empresa" << endl;
        cout << "  2) Departamentos de la empresa" << endl;
        cout << "  3) Puestos de trabajo" << endl;
        cout << "  4) Empleados" << endl;
        cout << "  5) Evaluaciones" << endl;
        cout << "  6) Evaluación de empleados" << endl;
        cout << "  7) Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> menu;

        switch (menu) {
            case 1: // Datos de empresa
                menuEmpresa();
                break;
            case 2: // Departamentos
                menuDepartamentos();
                break;
            case 3: // Puestos de trabajo
                menuTrabajo();
                break;
            case 4: // Empleados
                menuEmpleados();
                break;
            case 5: // Evaluaciones
                menuEvaluacion();
                break;
            case 6: // Evaluación de empleados
                menuEvaluar();
                break;
            case 7:  // Salir
                salir = 1; // Verdadero
                break;
            default:
                cout << "*** Opición inválida ***" << endl << endl;

        }
    }


    return 0;
}
