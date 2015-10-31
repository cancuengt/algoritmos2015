#include <iostream>
#include <cstring>
#include <fstream>
#include <limits>

using namespace std;

    struct Empresa {
        char nombre[100];
        char nit[15];
    };


void openDBfile (string nombre, fstream &archivo) {
    archivo.open(nombre.c_str(), ios::out | ios::in | ios::binary);
    if (!archivo.is_open()) {
        // Si el archivo no está abierto lo crea, lo
        archivo.open(nombre.c_str(), ios::out | ios::in | ios::binary | ios::trunc);
    }
}

void verEmpresa(fstream &fEmpresa)
{
    Empresa empresa;

    cout << endl << "Datos de la empresa:" << endl;
    cout << "--------------------" << endl;

    fEmpresa.seekg (0, ios::end);
    if (fEmpresa.tellg() == 0) {
        cout << "¡No hay empresa registrada!" << endl;
    } else {
        fEmpresa.seekg (0);
        fEmpresa.read(reinterpret_cast<char *>(&empresa), sizeof(Empresa));
        cout << "Nombre: " << empresa.nombre << endl;
        cout << "NIT: " << empresa.nit << endl << endl << endl;
    }
}

void modificarEmpresa (fstream &fEmpresa)
{

    Empresa empresa;
    string valor;

    // Limpia el bufffer de entrada para poder leeer cadenas
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    fEmpresa.seekg (0, ios::end);
    if (fEmpresa.tellg() == 0) {
        cout << "¡No hay empresa registrada!" << endl;
        cout << "Ingresar los datos de la empresa: " << endl;

        cout << "Nombre: ";
        getline(cin,valor);
        strncpy(empresa.nombre,valor.c_str(),sizeof(empresa.nombre));
        empresa.nombre[sizeof(empresa.nombre)-1] = '\0';

        cout << "NIT: ";
        getline(cin,valor);
        strncpy(empresa.nit,valor.c_str(),sizeof(empresa.nit));
        empresa.nit[sizeof(empresa.nit)-1] = '\0';

    } else {
        fEmpresa.seekg (0);
        fEmpresa.read(reinterpret_cast<char *>(&empresa), sizeof(Empresa));
        cout << "Para modificar ingrese el nuevo valor, para no modificar deje vacio." << endl;
        cout << "Nombre (\"" << empresa.nombre << "\"): ";
        getline(cin,valor);
        if(valor.length()){
            strncpy(empresa.nombre,valor.c_str(),sizeof(empresa.nombre));
            empresa.nombre[sizeof(empresa.nombre)-1] = '\0';
        }
        cout << "NIT (\"" << empresa.nit << "\"): ";
        getline(cin,valor);
        if(valor.length()){
            strncpy(empresa.nit,valor.c_str(),sizeof(empresa.nit));
            empresa.nit[sizeof(empresa.nit)-1] = '\0';
        }
    }

    fEmpresa.seekg (0);
    fEmpresa.write(reinterpret_cast<char *>(&empresa), sizeof(Empresa));
    cout << "Datos escritos" << endl << endl;
}

void menuEmpresa (fstream &fEmpresa)
{
    int salir = 0;
    int menu;

    while (!salir) {
        cout << endl << endl << endl;
        cout << "Mantenimiento de Empresa" << endl;
        cout << "------------------------" << endl;
        cout << "  1- Modificar datos de la empresa" << endl;
        cout << "  2- Ver datos de la empresa" << endl;
        cout << "  3- Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> menu;
        switch (menu) {
            case 1: // Modificar datos de la empresa
                modificarEmpresa(fEmpresa);
                break;
            case 2: // Modificar datos de la empresa
                verEmpresa(fEmpresa);
                break;
            case 3:
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
        cout << endl << endl << endl;
        cout << "Mantenimiento de Departamentos" << endl;
        cout << "------------------------------" << endl;
        cout << "  1- Listar departamentos" << endl;
        cout << "  2- Agregar departamento" << endl;
        cout << "  3- Modificar departamento" << endl;
        cout << "  4- Eliminar departamento" << endl;
        cout << "  5- Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> menu;
        switch (!salir) {
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
        cout << endl << endl << endl;
        cout << "Mantenimiento de Puestos de Trabajo" << endl;
        cout << "-----------------------------------" << endl;
        cout << "  1- Listar puestos de trabajo" << endl;
        cout << "  2- Agregar puesto de trabajo" << endl;
        cout << "  3- Modificar puesto de trabajo" << endl;
        cout << "  4- Eliminar puesto de trabajo" << endl;
        cout << "  5- Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> menu;
        switch (!salir) {
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
        cout << endl << endl << endl;
        cout << "Mantenimiento de Empleados" << endl;
        cout << "--------------------------" << endl;
        cout << "  1- Listar empleados" << endl;
        cout << "  2- Agregar empleado" << endl;
        cout << "  3- Modificar empleado" << endl;
        cout << "  4- Eliminar empleado" << endl;
        cout << "  5- Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> menu;
        switch (!salir) {
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
        cout << endl << endl << endl;
        cout << "Mantenimiento de Evaluación de Trabajo" << endl;
        cout << "--------------------------------------" << endl;
        cout << "  1- Listar items de evaluación" << endl;
        cout << "  2- Agregar item de evaluación" << endl;
        cout << "  3- Modificar item de evaluación" << endl;
        cout << "  4- Eliminar item de evaluación" << endl;
        cout << "  5- Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> menu;
        switch (!salir) {
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
        cout << endl << endl << endl;
        cout << "Evaluación de desempeño" << endl;
        cout << "-----------------------------------" << endl;
        cout << "  1- Evaluar un empleado" << endl;
        cout << "  2- Evaluar por departamentos" << endl;
        cout << "  3- Evaluar todos los empleados" << endl;
        cout << "  4- Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> menu;
        switch (!salir) {
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

void informacion ()
{
    cout << endl << endl << endl;
    cout << "Proyecto Algoritmos Sección F 2015" << endl << endl;
    cout << "Acerca de..." << endl;
    cout << "+---------------------------------------------+" << endl;
    cout << "| Nombre                      | Carnet        |" << endl;
    cout << "+---------------------------------------------+" << endl;
    cout << "| Mario Soto Ovalle           | 900-15-16795  |" << endl;
    cout << "+---------------------------------------------+" << endl;
    cout << endl << endl;
}

int main()
{
    int salir = 0; // Salir del sistema
    int menu;

    // Variables de archivos
    fstream fEmpresa;

    // Abrir archivo como base de datos
    openDBfile("empresa.db",fEmpresa);

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
        cout << "  7) Evaluación de empleados" << endl;
        cout << "  8) Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> menu;

        switch (menu) {
            case 1: // Datos de empresa
                menuEmpresa(fEmpresa);
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
            case 7: // Evaluación de empleados
                informacion();
                break;
            case 8:  // Salir
                salir = 1; // Verdadero
                break;
            default:
                cout << "*** Opición inválida ***" << endl << endl;
        }
    }
    return 0;
}


