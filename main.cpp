#include <cstdlib>
#include <iostream>
#include <cstring>
#include <fstream>
#include <limits>
#include <iomanip>

using namespace std;

    struct Empresa {
        char nombre[100];
        char nit[15];
    };

    struct Empleados {
        int estado;
        char nombre[100];
        char codigo[15];
    };

    struct Departamentos {
        int estado;
        char nombre[100];
        char codigo[15];
    };

    struct Evaluacion {
        int estado;
        int numero;
        char descripcion[100];
        int e1; // Siempre
        int e2; // Algunas veces
        int e3; // Nunca
    };

    struct Puestos {
        int estado;
        char departamento[10];
        char codigo[10];
        char descripcion[100];
    };

void openDBfile (string nombre, fstream &archivo)
{
    archivo.open(nombre.c_str(), ios::out | ios::in | ios::binary);
    if (!archivo.is_open()) {
        // Si el archivo no está abierto lo crea
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

void verDepartamentos (fstream &fDepartamento)
{
    Departamentos departamento;
    int registros;
    int fsize;

    fDepartamento.seekg (0, ios::end);
    fsize = fDepartamento.tellg();

    cout << "Listado de departamentos" << endl;
    cout << "------------------------" << endl;

    if (fsize == 0) {
        cout << "¡No hay departamentos registrados!" << endl;
    } else {
        registros = fsize/sizeof(Departamentos);
        for(int i = 0; i < registros; i++) {
            fDepartamento.seekg (i * sizeof(Departamentos));
            fDepartamento.read(reinterpret_cast<char *>(&departamento), sizeof(Departamentos));
            if(departamento.estado) { // Solo toma en cuenta cuando estado > 0
                cout << "Codigo: " << departamento.codigo << endl;
                cout << "Nombre: " << departamento.nombre << endl << endl;
            }
        }
    }
}

void agregarDepartamento (fstream &fDepartamento)
{
    Departamentos departamento;
    string valor;

    // Limpia el bufffer de entrada para poder leeer cadenas
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    departamento.estado = 1;

    cout << "Código de departamento: ";
    getline(cin,valor);
    strncpy(departamento.codigo,valor.c_str(),sizeof(departamento.codigo));
    departamento.codigo[sizeof(departamento.codigo)-1] = '\0';

    cout << "Nombre del departamento: ";
    getline(cin,valor);
    strncpy(departamento.nombre,valor.c_str(),sizeof(departamento.nombre));
    departamento.nombre[sizeof(departamento.nombre)-1] = '\0';

    fDepartamento.seekg (0, ios::end);
    fDepartamento.write(reinterpret_cast<char *>(&departamento), sizeof(Departamentos));
    cout << "Datos escritos" << endl << endl;
}

void modificarDepartamento (fstream &fDepartamento)
{
    Departamentos departamento;
    string temp;
    int fsize;
    int i         = 0;
    int found     = 0;
    int registros = -1;

    // Limpia el bufffer de entrada para poder leeer cadenas
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    fDepartamento.seekg (0, ios::end);
    fsize = fDepartamento.tellg();

    cout << endl;
    cout << "Modificar departamento" << endl;
    cout << "----------------------" << endl;
    cout << "Código: ";
    getline(cin,temp);

    registros = fsize / sizeof(Empleados);
    while ( i < registros || found ) {
        fDepartamento.seekg (i * sizeof(Departamentos));
        fDepartamento.read(reinterpret_cast<char *>(&departamento), sizeof(Departamentos));
        if ( departamento.estado && (strcmp(temp.c_str(),departamento.codigo) == 0) ) {
            found = 1;
            break; // Hasta aqui, salir del ciclo
        }
        i++;
    }

    if (found) {
        cout << "Para modificar ingrese el nuevo valor, para no modificar deje vacio." << endl;
        cout << "Codigo (\"" << departamento.codigo << "\"): ";
        getline(cin,temp);
        if(temp.length()){
            strncpy(departamento.codigo,temp.c_str(),sizeof(departamento.codigo));
            departamento.codigo[sizeof(departamento.codigo)-1] = '\0';
        }
        cout << "Nombre (\"" << departamento.nombre << "\"): ";
        getline(cin,temp);
        if(temp.length()){
            strncpy(departamento.nombre,temp.c_str(),sizeof(departamento.nombre));
            departamento.nombre[sizeof(departamento.nombre)-1] = '\0';
        }
        fDepartamento.seekg (i * sizeof(Departamentos));
        fDepartamento.write(reinterpret_cast<char *>(&departamento), sizeof(Departamentos));
        cout << "Datos escritos" << endl << endl;
    }
}

void eliminarDepartamento (fstream &fDepartamento)
{
    Departamentos departamento;
    string temp;
    int fsize;
    int i         = 0;
    int registros = -1;

    // Limpia el bufffer de entrada para poder leeer cadenas
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    fDepartamento.seekg (0, ios::end);
    fsize = fDepartamento.tellg();

    cout << endl;
    cout << "Eliminar departamento" << endl;
    cout << "---------------------" << endl;
    cout << "Código: ";
    getline(cin,temp);

    registros = fsize / sizeof(Empleados);
    while ( i < registros ) {
        fDepartamento.seekg (i * sizeof(Departamentos));
        fDepartamento.read(reinterpret_cast<char *>(&departamento), sizeof(Departamentos));
        if ( departamento.estado && (strcmp(temp.c_str(),departamento.codigo) == 0) ) {
            departamento.estado = 0;
            fDepartamento.seekg (i * sizeof(Departamentos));
            fDepartamento.write(reinterpret_cast<char *>(&departamento), sizeof(Departamentos));
            cout << "Registro eliminado" << endl << endl;
            break; // Hasta aqui, salir del ciclo
        }
        i++;
    }
}

void menuDepartamentos (fstream &fDepartamento)
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
        switch (menu) {
            case 1: // Listar
                verDepartamentos(fDepartamento);
                break;
            case 2: // Agregar
                agregarDepartamento(fDepartamento);
                break;
            case 3: // Modificar
                modificarDepartamento(fDepartamento);
                break;
            case 4: // Eliminar
                eliminarDepartamento(fDepartamento);
                break;
            case 5:
                salir = 1;
                break;
            default:
                cout << "+++ Opición inválida +++" << endl << endl;
        }
    }
}

Departamentos buscarDepartamentos(fstream &fDepartamento, string codigo)
{
    Departamentos departamento;
    Departamentos resultado;
    int found = 0;
    int i     = 0;
    int registros;

    resultado.estado = 0;
    fDepartamento.seekg (0, ios::end);
    registros = fDepartamento.tellg() / sizeof(Departamentos);
    while ( i < registros ) {
        fDepartamento.seekg (i * sizeof(Departamentos));
        fDepartamento.read(reinterpret_cast<char *>(&departamento), sizeof(Departamentos));
        if ( strcmp(codigo.c_str(), departamento.codigo) == 0 ) {
            resultado = departamento;
            break; // Hasta aqui, salir del ciclo
        }
        i++;
    }
    return resultado;
}

void verPuestos(fstream &fPuestos, fstream &fDepartamento)
{
    Puestos puesto;
    int registros;
    int fsize;

    fPuestos.seekg (0, ios::end);
    fsize = fPuestos.tellg();

    cout << "Listado de puestos" << endl;
    cout << "------------------" << endl;

    if (fsize == 0) {
        cout << "¡No hay puestos registrados!" << endl;
    } else {
        registros = fsize / sizeof(Puestos);
        for(int i = 0; i < registros; i++) {
            fPuestos.seekg (i * sizeof(Puestos));
            fPuestos.read(reinterpret_cast<char *>(&puesto), sizeof(Puestos));
            if(puesto.estado) { // Solo toma en cuenta cuando estado > 0
                cout << "Codigo: " << puesto.codigo << endl;
                cout << "Descripción: " << puesto.descripcion << endl;
                cout << "Departamento: " << buscarDepartamentos(fDepartamento, string(puesto.departamento)).nombre << endl << endl;
            }
        }
    }
}

void agregarPuestos(fstream &fPuestos, fstream &fDepartamento)
{
    Departamentos departamento;
    Puestos       puesto;
    string valor;
    int registros;
    int fsize;
    int i;

    cout << "Agregar puesto de trabajo" << endl;
    cout << "-------------------------" << endl;

    fDepartamento.seekg (0, ios::end);
    if (fDepartamento.tellg() == 0) {
        cout << "¡No hay departamentos registrados!" << endl;
    } else {
        // Limpia el bufffer de entrada para poder leeer cadenas
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        cout << "Código del puesto: ";
        getline(cin,valor);
        strncpy(puesto.codigo,valor.c_str(),sizeof(puesto.codigo));
        puesto.codigo[sizeof(puesto.codigo)-1] = '\0';

        cout << "Descripción del puesto: ";
        getline(cin,valor);
        strncpy(puesto.descripcion, valor.c_str(), sizeof(puesto.descripcion));
        puesto.descripcion[sizeof(puesto.descripcion)-1] = '\0';

        cout << "Departamento: " << endl;
        fDepartamento.seekg (0, ios::end);
        registros = fDepartamento.tellg()/sizeof(Departamentos);
        for(i = 0; i < registros; i++) {
            fDepartamento.seekg (i * sizeof(Departamentos));
            fDepartamento.read(reinterpret_cast<char *>(&departamento), sizeof(Departamentos));
            if(departamento.estado) { // Solo toma en cuenta cuando estado > 0
                cout << setw(sizeof(departamento.codigo)) << departamento.codigo << " | " << departamento.nombre << endl;
            }
        }
        cout << "Ingrese el departamento: ";
        getline(cin, valor);
        strncpy(puesto.departamento, valor.c_str(), sizeof(puesto.departamento));
        puesto.departamento[sizeof(puesto.departamento)-1] = '\0';

        if(buscarDepartamentos(fDepartamento, puesto.departamento).estado) {
            fPuestos.seekg (0, ios::end);
            fPuestos.write(reinterpret_cast<char *>(&puesto), sizeof(Puestos));
            cout << "Datos escritos" << endl << endl;
        } else {
            cout << "No ha ingresado un departamento válido" << endl;
        }
    }
}

void modificarPuestos(fstream &fPuestos)
{

}

void eliminarPuestos(fstream &fPuestos)
{
}

void menuPuestos (fstream &fPuestos, fstream &fDepartamento)
{
    int salir = 0;
    int menu;

    while (!salir) {
        cout << endl << endl << endl;
        cout << "Mantenimiento de Puestos de trabajo" << endl;
        cout << "-----------------------------------" << endl;
        cout << "  1- Listar puestos de trabajo" << endl;
        cout << "  2- Agregar puesto de trabajo" << endl;
        cout << "  3- Modificar puesto de trabajo" << endl;
        cout << "  4- Eliminar puesto de trabajo" << endl;
        cout << "  5- Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> menu;
        switch (menu) {
            case 1: // Listar
                verPuestos(fPuestos, fDepartamento);
                break;
            case 2: // Agregar
                agregarPuestos(fPuestos, fDepartamento);
                break;
            case 3: // Modificar
                modificarPuestos(fPuestos);
                break;
            case 4: // Eliminar
                eliminarPuestos(fPuestos);
                break;
            case 5:
                salir = 1;
                break;
            default:
                cout << "+++ Opición inválida +++" << endl << endl;
        }
    }
}

void verEmpleados (fstream &fEmpleado)
{
    Empleados empleados;
    int registros;
    int fsize;

    fEmpleado.seekg (0, ios::end);
    fsize = fEmpleado.tellg();

    cout << "Datos del empleado" << endl;
    cout << "------------------" << endl;

    if (fsize == 0) {
        cout << "¡No hay empleados registrados!" << endl;
    } else {
        registros = fsize/sizeof(Empleados);
        for(int i = 0; i < registros; i++) {
            fEmpleado.seekg (i * sizeof(Empleados));
            fEmpleado.read(reinterpret_cast<char *>(&empleados), sizeof(Empleados));
            if(empleados.estado) { // Solo toma en cuenta cuando estado > 0
                cout << "Codigo: " << empleados.codigo << endl;
                cout << "Nombre: " << empleados.nombre << endl << endl;
            }
        }
    }
}

void agregarEmpleados (fstream &fEmpleado)
{
    Empleados empleados;
    string valor;

    // Limpia el bufffer de entrada para poder leeer cadenas
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    empleados.estado = 1;
    cout << "Ingrese el código asignado al nuevo empleado: ";
    getline(cin, valor);
    strncpy(empleados.codigo, valor.c_str(), sizeof(empleados.codigo));
    empleados.codigo[sizeof(empleados.codigo)-1] = '\0';

    cout << "Ingrese el nombre de nuevo empleado: ";
    getline(cin,valor);
    strncpy(empleados.nombre,valor.c_str(),sizeof(empleados.nombre));
    empleados.nombre[sizeof(empleados.nombre)-1] = '\0';

    fEmpleado.seekg (0, ios::end);
    fEmpleado.write(reinterpret_cast<char *>(&empleados), sizeof(Empleados));
    cout << "Datos escritos" << endl << endl;
}

void modificarEmpleados (fstream &fEmpleado)
{
    Empleados empleados;
    string temp;
    int fsize;
    int i         = 0;
    int found     = 0;
    int registros = -1;

    // Limpia el bufffer de entrada para poder leeer cadenas
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    fEmpleado.seekg (0, ios::end);
    fsize = fEmpleado.tellg();

    cout << endl;
    cout << "Modificar empleado" << endl;
    cout << "------------------" << endl;
    cout << "Código: ";
    getline(cin,temp);

    registros = fsize / sizeof(Empleados);
    while ( i < registros || found ) {
        fEmpleado.seekg (i * sizeof(Empleados));
        fEmpleado.read(reinterpret_cast<char *>(&empleados), sizeof(Empleados));
        if ( empleados.estado && (strcmp(temp.c_str(),empleados.codigo) == 0) ) {
            found = 1;
            break; // Hasta aqui, salir del ciclo
        }
        i++;
    }

    if (found) {
        cout << "Para modificar ingrese el nuevo valor, para no modificar deje vacio." << endl;
        cout << "Codigo (\"" << empleados.codigo << "\"): ";
        getline(cin,temp);
        if(temp.length()){
            strncpy(empleados.codigo,temp.c_str(),sizeof(empleados.codigo));
            empleados.codigo[sizeof(empleados.codigo)-1] = '\0';
        }
        cout << "Nombre (\"" << empleados.nombre << "\"): ";
        getline(cin,temp);
        if(temp.length()){
            strncpy(empleados.nombre,temp.c_str(),sizeof(empleados.nombre));
            empleados.nombre[sizeof(empleados.nombre)-1] = '\0';
        }
        fEmpleado.seekg (i * sizeof(Empleados));
        fEmpleado.write(reinterpret_cast<char *>(&empleados), sizeof(Empleados));
        cout << "Datos escritos" << endl << endl;
    }
}

void eliminarEmpleados (fstream &fEmpleado)
{
    Empleados empleados;
    string temp;
    int fsize;
    int i         = 0;
    int registros = -1;

    // Limpia el bufffer de entrada para poder leeer cadenas
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    fEmpleado.seekg (0, ios::end);
    fsize = fEmpleado.tellg();

    cout << endl;
    cout << "Eliminar empleado" << endl;
    cout << "-----------------" << endl;
    cout << "Código: ";
    getline(cin,temp);

    registros = fsize / sizeof(Empleados);
    while ( i < registros ) {
        fEmpleado.seekg (i * sizeof(Empleados));
        fEmpleado.read(reinterpret_cast<char *>(&empleados), sizeof(Empleados));
        if ( empleados.estado && (strcmp(temp.c_str(),empleados.codigo) == 0) ) {
            empleados.estado = 0;
            fEmpleado.seekg (i * sizeof(Empleados));
            fEmpleado.write(reinterpret_cast<char *>(&empleados), sizeof(Empleados));
            cout << "Registro eliminado" << endl << endl;
            break; // Hasta aqui, salir del ciclo
        }
        i++;
    }
}

void menuEmpleados (fstream &fEmpleado)
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
        switch (menu) {
            case 1: // Vizualizar datos de empleados
                verEmpleados(fEmpleado);
                break;
            case 2: // agregar datos de empleados
                agregarEmpleados(fEmpleado);
                break;
            case 3: // Modificar datos de la empresa
                modificarEmpleados(fEmpleado);
                break;
            case 4: // Eliminar
                eliminarEmpleados(fEmpleado);
                break;
            case 5:
                salir = 1;
                break;
            default:
                cout << "+++ Opición inválida +++" << endl << endl;
        }
    }
}

void verEvaluacion(fstream &fEvaluacion)
{
    Evaluacion evaluacion;
    int registros;
    int fsize;

    fEvaluacion.seekg (0, ios::end);
    fsize = fEvaluacion.tellg();

    cout << "Listado de puntos a evaluar" << endl;
    cout << "---------------------------" << endl;

    if (fsize == 0) {
        cout << "¡No hay puntos a evaluar!" << endl;
    } else {
        registros = fsize/sizeof(Empleados);
        for(int i = 0; i < registros; i++) {
            fEvaluacion.seekg (i * sizeof(Evaluacion));
            fEvaluacion.read(reinterpret_cast<char *>(&evaluacion), sizeof(Evaluacion));
            if(evaluacion.estado) { // Solo toma en cuenta cuando estado > 0
                cout << evaluacion.numero << ". " << evaluacion.descripcion << endl;
                cout << "Siempre " << evaluacion.e1 << "%   | Algunas veces " << evaluacion.e2 << "%   | Nunca " << evaluacion.e3 << "%" << endl << endl;
            }
        }
    }
}

void agregarEvaluacion(fstream &fEvaluacion)
{
    Evaluacion evaluacion;
    string valor;

    // Limpia el bufffer de entrada para poder leeer cadenas
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    evaluacion.estado = 1;
    cout << "Nombre del aspecto a evaluar: ";
    getline(cin,valor);
    strncpy(evaluacion.descripcion, valor.c_str(), sizeof(evaluacion.descripcion));
    evaluacion.descripcion[sizeof(evaluacion.descripcion)-1] = '\0';

    cout << "Ponderacion evaluación 1 (siempre)      : ";
    cin >> evaluacion.e1;

    cout << "Ponderacion evaluación 2 (algunas veces): ";
    cin >> evaluacion.e2;

    cout << "Ponderacion evaluación 3 (nunca)        : ";
    cin >> evaluacion.e3;

    if ((evaluacion.e1 + evaluacion.e2 + evaluacion.e3) == 100) {
        fEvaluacion.seekg (0, ios::end);
        evaluacion.numero = (fEvaluacion.tellg() / sizeof(Evaluacion)) + 1;
        fEvaluacion.write(reinterpret_cast<char *>(&evaluacion), sizeof(Evaluacion));
        cout << "Datos escritos. Registro " << evaluacion.numero << endl << endl;
    } else {
        cout << "Error: La ponderación evaluada no suma 100%. No se pueden escribir datos." << endl;
    }
}

void modificarEvaluacion(fstream &fEvaluacion)
{
    Evaluacion evaluacion;
    string temp;
    int e0;
    int fsize;
    int i         = 0;
    int found     = 0;
    int registros = -1;

    // Limpia el bufffer de entrada para poder leeer cadenas
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    fEvaluacion.seekg (0, ios::end);
    fsize = fEvaluacion.tellg();

    cout << endl;
    cout << "Modificar evaluación" << endl;
    cout << "--------------------" << endl;
    cout << "Número: ";
    cin >> e0;

    registros = fsize / sizeof(Evaluacion);
    while ( i < registros || found ) {
        fEvaluacion.seekg(i * sizeof(Evaluacion));
        fEvaluacion.read(reinterpret_cast<char *>(&evaluacion), sizeof(Evaluacion));
        if (evaluacion.numero == e0) {
            found = 1;
            break; // Hasta aqui, salir del ciclo
        }
        i++;
    }

    if (found) {
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Para modificar ingrese el nuevo valor, para no modificar deje vacio." << endl;
        cout << "Aspecto a evaluar (\"" << evaluacion.descripcion << "\"): ";
        getline(cin, temp);
        if(temp.length()){
            strncpy(evaluacion.descripcion, temp.c_str(), sizeof(evaluacion.descripcion));
            evaluacion.descripcion[sizeof(evaluacion.descripcion)-1] = '\0';
        }

        cout << "Ponderacion evaluación 1 \"siempre\" (" << evaluacion.e1 << "): ";
        getline(cin, temp);
        if(temp.length()){
            e0 = atoi(temp.c_str());
            if (evaluacion.e1 != 0) {
                evaluacion.e1 = e0;
            }
        }

        cout << "Ponderacion evaluación 2 \"algunas veces\" (" << evaluacion.e2 << "): ";
        getline(cin, temp);
        if(temp.length()){
            e0 = atoi(temp.c_str());
            if (evaluacion.e2 != 0) {
                evaluacion.e2 = e0;
            }
        }

        cout << "Ponderacion evaluación 3 \"nunca\" (" << evaluacion.e3 << "): ";
        getline(cin, temp);
        if(temp.length()){
            e0 = atoi(temp.c_str());
            if (evaluacion.e3 != 0) {
                evaluacion.e3 = e0;
            }
        }

        if ((evaluacion.e1 + evaluacion.e2 + evaluacion.e3) == 100) {
            fEvaluacion.seekg (i * sizeof(Evaluacion));
            fEvaluacion.write(reinterpret_cast<char *>(&evaluacion), sizeof(Evaluacion));
            cout << "Datos escritos." << endl << endl;
        } else {
            cout << "Error: La ponderación evaluada no suma 100%. No se pueden escribir datos." << endl;
        }
    }
}

void eliminarEvaluacion(fstream &fEvaluacion)
{
    Evaluacion evaluacion;
    string temp;
    int e0;
    int fsize;
    int i         = 0;
    int found     = 0;
    int registros = -1;

    // Limpia el bufffer de entrada para poder leeer cadenas
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    fEvaluacion.seekg (0, ios::end);
    fsize = fEvaluacion.tellg();

    cout << endl;
    cout << "Modificar evaluación" << endl;
    cout << "--------------------" << endl;
    cout << "Número: ";
    cin >> e0;

    registros = fsize / sizeof(Evaluacion);
    while ( i < registros || found ) {
        fEvaluacion.seekg(i * sizeof(Evaluacion));
        fEvaluacion.read(reinterpret_cast<char *>(&evaluacion), sizeof(Evaluacion));
        if (evaluacion.numero == e0) {
            evaluacion.estado = 0;
            fEvaluacion.seekg (i * sizeof(Evaluacion));
            fEvaluacion.write(reinterpret_cast<char *>(&evaluacion), sizeof(Evaluacion));
            cout << "Registro eliminado" << endl << endl;
            break; // Hasta aqui, salir del ciclo
        }
        i++;
    }
}

void menuEvaluacion (fstream &fEvaluacion)
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
        switch (menu) {
            case 1: // Listar
                verEvaluacion(fEvaluacion);
                break;
            case 2: // Agregar
                agregarEvaluacion(fEvaluacion);
                break;
            case 3: // Modificar
                modificarEvaluacion(fEvaluacion);
                break;
            case 4: // Eliminar
                eliminarEvaluacion(fEvaluacion);
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
    cout << "+--------------------------------------------------+" << endl;
    cout << "| Nombre                            | Carnet       |" << endl;
    cout << "+--------------------------------------------------+" << endl;
    cout << "| Mario Soto Ovalle                 | 900-15-16795 |" << endl;
    cout << "+--------------------------------------------------+" << endl;
    cout << "| Jonnathan L. Fernando Aldana Ruano| 900-14-22577 |" << endl;
    cout << "+--------------------------------------------------+" << endl;

    cout << endl << endl;
}

int main ()
{
    int salir = 0; // Salir del sistema
    int menu;

    // Variables de archivos
    fstream fEmpresa;
    fstream fEmpleado;
    fstream fDepartamento;
    fstream fEvaluacion;
    fstream fPuestos;

    // Abrir archivo como base de datos
    openDBfile("empresa.db",fEmpresa);
    openDBfile("empleado.db",fEmpleado);
    openDBfile("departamento.db",fDepartamento);
    openDBfile("evaluacion.db",fEvaluacion);
    openDBfile("puestos.db",fPuestos);

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
        cout << "  7) Información" << endl;
        cout << "  8) Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> menu;

        switch (menu) {
            case 1: // Datos de empresa
                menuEmpresa(fEmpresa);
                break;
            case 2: // Departamentos
                menuDepartamentos(fDepartamento);
                break;
            case 3: // Puestos de trabajo
                menuPuestos(fPuestos, fDepartamento);
                break;
            case 4: // Empleados
                menuEmpleados(fEmpleado);
                break;
            case 5: // Evaluaciones
                menuEvaluacion(fEvaluacion);
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

