#include<iostream>
#include <fstream>
using namespace std;

class NodoAVL;
class AVLTree;

/// Clase cita ---------------------------------------------------------------------------------------------------------------------------------------
class Cita
{
    private:
        int dia;
        int mes;
        int anio;
        int hora;
        int minutos;
        string nombreMedico;
        int numConsultorio;
        int indice;
    public:
       Cita();
       void insertarDatosCita(int dia, int mes, int anio, int hora, int minutos, string nombreMedico, int numConsultorio);
       void mostrarDatos();
       void modificarCita();
       friend class Lista;
       friend class Paciente;
};

Cita::Cita()
{
    dia = 0;
    mes = 0;
    anio = 0;
    hora = 0;
    minutos = 0;
    nombreMedico = "";
    numConsultorio = 0;
}

void Cita::insertarDatosCita(int dia, int mes, int anio, int hora ,int minutos, string nombreMedico, int numConsultorio)
{
    this -> dia = dia;
    this -> mes = mes;
    this -> anio = anio;
    this -> hora = hora;
    this -> minutos = minutos;
    this -> nombreMedico = nombreMedico;
    this -> numConsultorio = numConsultorio;
    indice ++;
}

void Cita::mostrarDatos()
{
    cout << "Fecha (dd/mm/aa): " << dia << "/" << mes << "/" << anio << endl;
    cout << "Hora: " << hora << ":" << minutos<< endl;
    cout << "Medico: Dr. " << nombreMedico << endl;
    cout << "Consultorio: " << numConsultorio << endl;
}

void Cita::modificarCita(){
    int opc;
    do{
        cout << "Que desea modificar?" << endl;
        cout << "1) Dia" << endl;
        cout << "2) Mes" << endl;
        cout << "3) Anio" << endl;
        cout << "4) Hora" << endl;
        cout << "5) Medico" << endl;
        cout << "6) Consultorio" << endl;
        cout << "7) Salir" << endl;
        cout << "Opcion: ";
        cin >> opc;
        cout << endl;

        switch(opc){
            case 1:
                do{
                cout << "Ingrese el dia de la cita (DD): ";
                cin >> dia;
                if(dia>31 || dia<1)
                {
                    cout << "El dia no se encuentra dentro del rango, favor de ingresar un dato valido" << endl;
                }
                }while(dia>31 || dia<1);
                cout << endl;
                break;
            case 2:
                do{
                    cout << "Ingrese el mes de la cita (MM): ";
                    cin >> mes;

                    if(mes>12 || mes<1)
                        {
                            cout << "El mes no se encuentra dentro del rango, favor de ingresar un dato valido" << endl;
                        }

                }while(mes>12 || mes<1);
                cout << endl;
                break;
            case 3:
            do{
                cout << "Ingrese el anio de la cita (AAAA): ";
                cin >> anio;

                if(anio<2023)
                {
                    cout << "El anio no se encuentra dentro del rango, favor de ingresar un dato valido" << endl;
                }

                }while(anio<2023);
                cout << endl;
                break;

            case 4:
                do{
                    cout << "Ingrese unicamente la hora de la cita (formato de 24 hrs): ";
                    cin >> hora;

                    if(hora>23 || hora<0)
                    {
                        cout << "La hora no se encuentra dentro del rango, favor de ingresar un dato valido" << endl;
                    }

                }while(hora>23 || hora<0);

                do{
                    cout << "Ingrese unicamente el minuto de la cita: ";
                    cin >> minutos;

                    if(minutos>59 || minutos<0)
                    {
                        cout << "Los minutos no se encuentran dentro del rango, favor de ingresar un dato valido" << endl;
                    }

                }while(minutos>59 || minutos<0);
                cout << endl;
                break;

            case 5:
                cout << "Ingrese nombre del medico: ";
                cin >> nombreMedico;
                cout << endl;
                break;
            case 6:
                cout << "Ingrese numero de consultorio: ";
                cin >> numConsultorio;
                cout << endl;
                break;
            case 7:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Opcion no valida" << endl;
                break;
        }
    }while(opc != 7);
}

///Clase nodo lista ligada citas ------------------------------------------------------------------------------------------------------------------------------------

class Nodo
{
    public:
        //atributos
        Cita cita;
        Nodo* siguiente;
        //Constuctor
        Nodo(int dia, int mes, int anio, int hora, int minutos, string nombreMedico, int numConsultorio);
};

Nodo::Nodo(int dia, int mes, int anio, int hora, int minutos, string nombreMedico, int numConsultorio) ///RECIBE DATOS PARA CITA
{
    cita.insertarDatosCita(dia, mes, anio, hora, minutos, nombreMedico, numConsultorio);
    siguiente = nullptr;
}

///clase lista ------------------------------------------------------------------------------------------------------------------------------------

class Lista
{
    public:
        //atributos
        Nodo* raiz;
        int indice;
        //contructor
        Lista();
        //metodos
        bool esVacia();
        void insertarInicio(int dia, int mes, int anio, int hora, int minutos, string nombreMedico, int numConsultorio); ///TODOS RECIBEN DATOS PARA CITA
        void insertarFinal(int dia, int mes, int anio, int hora, int minutos, string nombreMedico, int numConsultorio);
        void insertarEnOrden(int dia, int mes, int anio, int hora, int minutos, string nombreMedico, int numConsultorio);
        int compararFechasYHoras(Nodo* nodo1, Nodo* nodo2);
        void eliminarInicio();
        void eliminarFinal();
        void mostrarLista();
        Cita obtenerCita(int indiceCita);
        friend class Cita;
        //void modificarCita(int indiceCita);
};
Cita Lista::obtenerCita(int indiceCita)
{
    Nodo *aux = raiz;
    while (aux != nullptr)
    {
        if (aux->cita.indice == indiceCita)
        {
            return aux->cita;
        }
        aux = aux->siguiente;
    }
    
    throw std::runtime_error("Cita no encontrada");
}

Lista::Lista()
{
    raiz = nullptr;
}

bool Lista::esVacia()
{
    return (raiz == nullptr);
}

void Lista::insertarInicio(int dia, int mes, int anio, int hora, int minutos, string nombreMedico, int numConsultorio)
{
    Nodo* nuevo = new Nodo(dia, mes, anio, hora, minutos, nombreMedico, numConsultorio);

    if (esVacia())
    {
        raiz = nuevo;
        nuevo->siguiente = nuevo;
    }
    else
    {
        Nodo* aux = raiz;

        while (aux->siguiente != raiz)
        {
            aux = aux->siguiente;
        }

        aux->siguiente = nuevo;
        nuevo->siguiente = raiz;
        raiz = nuevo;
    }
}

void Lista::insertarFinal(int dia, int mes, int anio, int hora, int minutos, string nombreMedico, int numConsultorio)
{
    Nodo* nuevo = new Nodo(dia, mes, anio, hora, minutos, nombreMedico, numConsultorio);

    if (esVacia())
    {
        raiz = nuevo;

    }
    else
    {
        Nodo* aux = raiz;

        while (aux->siguiente != raiz)
        {
            aux = aux->siguiente;
        }

        aux->siguiente = nuevo;
        nuevo->siguiente = raiz;
    }
}

void Lista::insertarEnOrden(int dia, int mes, int anio, int hora, int minutos, string nombreMedico, int numConsultorio)
{
    Nodo *nuevo = new Nodo(dia, mes, anio, hora, minutos, nombreMedico, numConsultorio);

    if (esVacia())
    {
        raiz = nuevo;
    }
    else
    {
        Nodo *actual = raiz;
        Nodo *anterior = nullptr;

        while (actual != nullptr && compararFechasYHoras(nuevo, actual) > 0)
        {
            anterior = actual;
            actual = actual->siguiente;
        }

        if (anterior == nullptr)
        {
            nuevo->siguiente = raiz;
            raiz = nuevo;
        }
        else
        {
            anterior->siguiente = nuevo;
            nuevo->siguiente = actual;
        }
    }

    // Asigna un índice único a la nueva cita
    nuevo->cita.indice = indice;
    indice++;
}

int Lista::compararFechasYHoras(Nodo* nodo1, Nodo* nodo2)
{

    // Compara las fechas (año, mes, día) de los nodos
    if (nodo1->cita.anio != nodo2->cita.anio)
    {
        return nodo1->cita.anio - nodo2->cita.anio;
    }
    else if (nodo1->cita.mes != nodo2->cita.mes)
    {
        return nodo1->cita.mes - nodo2->cita.mes;
    }
    else if (nodo1->cita.dia != nodo2->cita.dia)
    {
        return nodo1->cita.dia - nodo2->cita.dia;
    }
    else
    {
        // Comparamos las horas si las fechas son iguales
        if (nodo1->cita.hora < nodo2->cita.hora)
        {
            return -1;
            //caso donde ña primera hora es menor
        }
        else if (nodo1->cita.hora > nodo2->cita.hora)
        {
            return 1;
            //caso donde la segunda hora es mayor
        }
        else
        {
            // Si las fechas y horas son iguales, los nodos son considerados iguales
            return 0;
        }
    }
}


void Lista::eliminarInicio()
{
    if (esVacia())
    {
        cout << "\nLa lista esta vacia !!\n" << endl;
    }
    else
    {
        raiz = raiz->siguiente;

        Nodo* aux = raiz;

        while (aux->siguiente != raiz)
        {
            aux = aux->siguiente;
        }

        aux->siguiente = raiz;
        cout << "\nElemento Eliminado\n" << endl;
    }
}

void Lista::eliminarFinal()
{
    if (esVacia())
    {
        cout << "\nLa lista esta vacia !!" << endl;
    }
    else
    {
        Nodo* aux1 = raiz;
        Nodo* aux2 = raiz;

        while (aux1->siguiente != raiz)
        {
            aux2 = aux1;
            aux1 = aux1->siguiente;
        }
        aux2->siguiente = raiz;
        cout << "\nElemento Eliminado\n" << endl;
    }
}

void Lista::mostrarLista()
{
    Nodo* aux = raiz;

    if (!esVacia())
    {
        cout << "Citas: " << endl;

        while (aux->siguiente != nullptr)
        {
            aux->cita.mostrarDatos(); /// LLAMA A mostrarDatos() DE CITA
            cout << endl;
            aux = aux->siguiente;
        }

        aux->cita.mostrarDatos(); /// YA LO COMPROBE SI FUNCIONA
        cout << endl;
    }
    else
    {
        cout << endl << "No hay citas registradas. \n";
    }
}


///Clase paciente --------------------------------------------------------------------------------------------------------------------------------
class Paciente
{
    private:
        int nss;
        string nombre;
        string apellidoPaterno;
        string apellidoMaterno;
        char sexo;
        int edad;
        Lista *citas;
        int indice;
    public:
        Paciente();
        void insertarDatosPaciente(int nss, string nombre, string apellidoPaterno, string apellidoMaterno, char sexo, int edad);
        void insertarCitas(int dia, int mes, int anio, int hora, int minutos, string nombreMedico, int numConsultorio);
        void mostrarDatos();
        void modificarPaciente();
        Lista* getCitas(){return citas;};
        int obtenerNumCitas();
        friend class AVLTree;
};

Paciente::Paciente()
{
    nss = 0;
    nombre = "";
    apellidoPaterno = "";
    apellidoMaterno = "";
    sexo = ' ';
    edad = 0;
    citas = NULL;
}

void Paciente::insertarDatosPaciente(int nss, string nombre, string apellidoPaterno, string apellidoMaterno, char sexo, int edad)
{
    this -> nss = nss;
    this -> nombre = nombre;
    this -> apellidoPaterno = apellidoPaterno;
    this -> apellidoMaterno = apellidoMaterno;
    this -> sexo = sexo;
    this -> edad = edad;

    citas = new Lista();
}

void Paciente::insertarCitas(int dia, int mes, int anio, int hora, int minutos, string nombreMedico, int numConsultorio) ///DEBE RECIBIR DATOS PARA CITA
{
    citas->insertarEnOrden(dia, mes, anio, hora, minutos, nombreMedico, numConsultorio); ///DEBE LLAMAR AL METODO QUE INSERTA EN ORDEN DE LA LISTA
    indice ++;
}

void Paciente::mostrarDatos()
{
    cout << endl << "NSS: " << nss << endl;
    cout << "Nombre: " << nombre << " " << apellidoPaterno << " " << apellidoMaterno << endl;
    cout << "Sexo: " << sexo << endl;
    cout << "Edad: " << edad << endl;
    cout << "Citas: "<< indice << endl;
    citas->mostrarLista();
}



int Paciente::obtenerNumCitas(){
    return indice;
}

void Paciente::modificarPaciente(){
    int opc;
    do{
        cout << "Que desea modificar?" << endl;
        cout << "1) NSS" << endl;
        cout << "2) Nombre" << endl;
        cout << "3) Apellido Paterno" << endl;
        cout << "4) Apellido Materno" << endl;
        cout << "5) Sexo" << endl;
        cout << "6) Edad" << endl;
        cout << "7) Salir" << endl;
        cout << "Opcion: ";
        cin >> opc;
        cout << endl;

        switch(opc){
            case 1:
                cout << "Ingrese el NSS del paciente: ";
                cin >> nss;
                cout << endl;
                break;
            case 2:
                cout << "Ingrese el nombre del paciente: ";
                cin >> nombre;
                cout << endl;
                break;
            case 3:
                cout << "Ingrese el apellido paterno del paciente: ";
                cin >> apellidoPaterno;
                cout << endl;
                break;
            case 4:
                cout << "Ingrese el apellido materno del paciente: ";
                cin >> apellidoMaterno;
                cout << endl;
                break;
            case 5:
                do{
                    cout << "Ingrese sexo del paciente (M:masculino / F:femenino): ";
                    cin >> sexo;

                    if(sexo != 'F' && sexo != 'M' && sexo != 'f' && sexo != 'm')
                    {
                        cout << "Ingrese un dato valido" << endl;
                    }

                }while(sexo != 'F' && sexo != 'M' && sexo != 'f' && sexo != 'm');
                cout << endl;
                break;
            case 6:
                do{

                    cout << "Ingrese edad del paciente: ";
                    cin >> edad;

                    if(edad>100 || edad<0)
                    {
                        cout << "Edad fuera del rango, ingrese un dato valido" << endl;
                    }

                }while(edad>100 || edad<0);
                cout << endl;
                break;
            case 7:
                cout << "Salir..." << endl;
                break;
            default:
                cout << "Opcion no valida" << endl;
                break;
        }
    }while(opc != 7);
}


///Clase nodoAVL ------------------------------------------------------------------------------------------------------------------------------------

class NodoAVL
{
    public:
        //atributos
        Paciente paciente;  // Cambio: el nodo ahora tiene un objeto Paciente en lugar de solo un dato entero
        NodoAVL* izquierdo;
        NodoAVL* derecho;
        int altura;
        //constructores
        NodoAVL();
        NodoAVL(const Paciente& p) : paciente(p), izquierdo(nullptr), derecho(nullptr), altura(0) {}
};

///Clase AVL ----------------------------------------------------------------------------------------------------------------------------------------
class AVLTree
{
    private:
        NodoAVL* raiz;

        int altura(NodoAVL* nodo)
        {
            if (nodo == nullptr)
                return 0;
            return nodo->altura;
        }

        int maximo(int a, int b)
        {
            return (a > b) ? a : b;
        }

        int obtenerBalance(NodoAVL* nodo)
        {
            if (nodo == nullptr)
                return 0;
            return altura(nodo->izquierdo) - altura(nodo->derecho);
        }

        NodoAVL* rotacionDerecha(NodoAVL* y)
        {
            NodoAVL* x = y->izquierdo;
            NodoAVL* T2 = x->derecho;

            x->derecho = y;
            y->izquierdo = T2;

            y->altura = maximo(altura(y->izquierdo), altura(y->derecho)) + 1;
            x->altura = maximo(altura(x->izquierdo), altura(x->derecho)) + 1;

            return x;
        }

        NodoAVL* rotacionIzquierda(NodoAVL* x)
        {
            NodoAVL* y = x->derecho;
            NodoAVL* T2 = y->izquierdo;

            y->izquierdo = x;
            x->derecho = T2;

            x->altura = maximo(altura(x->izquierdo), altura(x->derecho)) + 1;
            y->altura = maximo(altura(y->izquierdo), altura(y->derecho)) + 1;

            return y;
        }

        NodoAVL* insertar(NodoAVL* nodo, const Paciente& paciente)
        {
            if (nodo == nullptr)
                return new NodoAVL(paciente);

            // Usar directamente paciente.nss para el ordenamiento
            if (paciente.nss < nodo->paciente.nss)
                nodo->izquierdo = insertar(nodo->izquierdo, paciente);
            else if (paciente.nss > nodo->paciente.nss)
                nodo->derecho = insertar(nodo->derecho, paciente);
            else
                return nodo; // No se permiten duplicados en este ejemplo

            return nodo;
        }

        void imprimirPreorden(NodoAVL* nodo)
        {
                if (nodo != nullptr)
                {
                    nodo->paciente.mostrarDatos();
                    imprimirPreorden(nodo->izquierdo);
                    imprimirPreorden(nodo->derecho);
                }
        }

        void imprimirInorden(NodoAVL* nodo)
        {
                if (nodo != nullptr)
                {
                    imprimirInorden(nodo->izquierdo);
                    nodo->paciente.mostrarDatos();  // Cambio: Mostrar los datos del paciente en lugar de solo el dato entero
                    imprimirInorden(nodo->derecho);
                }
        }

        void imprimirPostorden(NodoAVL* nodo)
        {
                if (nodo != nullptr)
                {
                    imprimirPostorden(nodo->izquierdo);
                    imprimirPostorden(nodo->derecho);
                    nodo->paciente.mostrarDatos();
                }
        }

        NodoAVL* buscarNodo(NodoAVL* nodo, int nss)
        {
                if (nodo == nullptr || nodo->paciente.nss == nss)
                    return nodo;

                if (nss < nodo->paciente.nss)
                    return buscarNodo(nodo->izquierdo, nss);

                return buscarNodo(nodo->derecho, nss);
        }

    public:

        AVLTree() : raiz(nullptr) {}

        void insertar(const Paciente& paciente)
        {
            raiz = insertar(raiz, paciente);
        }

        void imprimirPreorden()
        {
                cout << "Recorrido Preorden: " << endl;
                imprimirPreorden(raiz);
                cout << endl;
        }

        void imprimirInorden()
        {
                cout << "Recorrido Inorden: " << endl;
                imprimirInorden(raiz);
                cout << endl;
        }

        void imprimirPostorden()
        {
                cout << "Recorrido Postorden: " << endl;
                imprimirPostorden(raiz);
                cout << endl;
        }

        NodoAVL* buscarNodo(int nss)
        {
            return buscarNodo(raiz, nss);
        }

        bool insertarCita(int nss, int dia, int mes, int anio, int hora, int minutos, string nombreMedico, int numConsultorio)
        {
            NodoAVL* nodoPaciente = buscarNodo(nss);

            if (nodoPaciente != nullptr)
            {
                // Encontramos al paciente, ahora llamamos al método insertarCitas de la clase Paciente
                nodoPaciente->paciente.insertarCitas(dia, mes, anio, hora, minutos, nombreMedico, numConsultorio);
                return true;
            }

            return false; // No se encontró al paciente
        }

        bool esVacio()
        {
            return raiz == nullptr;
        }

        void eliminar(int nss1)
        {
            NodoAVL *Padre = nullptr;
            NodoAVL *puntPos = raiz;
            bool encontrado = false;

            if (!esVacio())
            {
                while (encontrado == false && puntPos != nullptr)
                    {
                    if (puntPos->paciente.nss == nss1)
                    {
                        encontrado = true;
                        cout << "Elemento encontrado" << endl;
                    }
                    else
                    {
                        Padre = puntPos;

                        if (nss1 > Padre->paciente.nss)
                        {
                            puntPos = Padre->derecho;
                        }
                        else
                        {
                            puntPos = Padre->izquierdo;
                        }
                    }
                }
            }

            if (encontrado == true)
            {
                if (raiz == puntPos && puntPos->derecho == nullptr && puntPos->izquierdo == nullptr)
                {
                    raiz = nullptr;
                } else {
                    if (puntPos->izquierdo == nullptr && puntPos->derecho == nullptr)
                    {
                        if (Padre->paciente.nss > puntPos->paciente.nss)
                        {
                            Padre->izquierdo = nullptr;
                        } else
                        {
                            Padre->derecho = nullptr;
                        }
                    }
                    else
                    {
                        if (puntPos->izquierdo != nullptr && puntPos->derecho != nullptr)
                        {
                            NodoAVL *aux = puntPos->izquierdo;
                            if (aux->derecho == nullptr)
                            {
                                if (aux->izquierdo == nullptr)
                                {
                                    puntPos->paciente = aux->paciente;
                                    puntPos->izquierdo = nullptr;
                                }
                                else
                                {
                                    puntPos->paciente = aux->paciente;
                                    puntPos->izquierdo = aux->izquierdo;
                                }
                            }
                            else
                            {
                                NodoAVL *aux2 = aux->derecho;
                                while (aux2->derecho != nullptr)
                                {
                                    aux = aux2;
                                    aux2 = aux2->derecho;
                                }

                                if (aux->izquierdo == nullptr)
                                {
                                    puntPos->paciente = aux2->paciente;
                                    aux->derecho = nullptr;
                                }
                                else
                                {
                                    puntPos->paciente = aux2->paciente;
                                    aux->derecho = aux2->izquierdo;
                                }
                            }
                            cout << "El nodo a eliminar tenía dos hijos y fue reemplazado por el elemento mayor del subárbol izquierdo" << endl;
                        }
                        else
                        {
                            if (puntPos->izquierdo == nullptr)
                            {
                                if (puntPos->paciente.nss > Padre->paciente.nss)
                                {
                                    Padre->derecho = puntPos->derecho;
                                }
                                else
                                {
                                    Padre->izquierdo = puntPos->derecho;
                                }
                            }
                            else
                            {
                                if (puntPos->paciente.nss > Padre->paciente.nss)
                                {
                                    Padre->derecho = puntPos->izquierdo;
                                }
                                else
                                {
                                    Padre->izquierdo = puntPos->izquierdo;
                                }
                            }
                        }
                    }
                }
            }
            else
            {
                cout << "Elemento no encontrado" << endl;
            }

            if (encontrado == true)
            {
                cout << "Elemento eliminado" << endl;
            }
        }

};

///Main --------------------------------------------------------------------------------------------------------------------------------------------
int main()
{
    int nss, edad;
    string nombre, apellidoPaterno, apellidoMaterno;
    char sexo;
    Paciente nuevoPaciente;
    NodoAVL *Pencontrar;
    AVLTree arbol;
    AVLTree avl;
    int numCita;

    int opc;
    do{
        cout << "------------------------------------" << endl;
        cout << "---------- HOSPITAL NESK -----------" << endl;
        cout << "------------------------------------" << endl;
        cout << " 1. Insertar" << endl;
        cout << " 2. Modificar" << endl;
        cout << " 3. Buscar" << endl;
        cout << " 4. Mostrar en preorden" << endl;
        cout << " 5. Mostrar en inorden" << endl;
        cout << " 6. Mostrar en postorden" << endl;
        cout << " 7. Exportar" << endl;
        cout << " 8. Eliminar" << endl;
        cout << " 9. Salir" << endl << endl;
        cout << " Opcion: ";
        cin >> opc;
        cout << endl;

        switch(opc)
        {
            case 1:

               ///Insertar paciente o cita

                do
                {
                    cout << " 1) Paciente" << endl;
                    cout << " 2) Cita" << endl;
                    cout << "\n Opcion: ";
                    cin >> opc;
                    cout << endl;

                }while(opc !=1 && opc !=2);

                if (opc == 1)
                {

                    // Solicitar datos del paciente
                    cout << "Ingrese NSS del paciente: ";
                    cin >> nss;

                    cout << "Ingrese nombre del paciente: ";
                    cin >> nombre;

                    cout << "Ingrese apellido paterno del paciente: ";
                    cin >> apellidoPaterno;

                    cout << "Ingrese apellido materno del paciente: ";
                    cin >> apellidoMaterno;

                    do{
                        cout << "Ingrese sexo del paciente (M:masculino / F:femenino): ";
                        cin >> sexo;

                        if(sexo != 'F' && sexo != 'M' && sexo != 'f' && sexo != 'm')
                        {
                            cout << "Ingrese un dato valido" << endl;
                        }

                    }while(sexo != 'F' && sexo != 'M' && sexo != 'f' && sexo != 'm');

                    do{

                        cout << "Ingrese edad del paciente: ";
                        cin >> edad;

                        if(edad>100 || edad<0)
                        {
                            cout << "Edad fuera del rango, ingrese un dato valido" << endl;
                        }

                    }while(edad>100 || edad<0);

                    cout << endl;
                    // Crear objeto Paciente
                    nuevoPaciente.insertarDatosPaciente(nss, nombre, apellidoPaterno, apellidoMaterno, sexo, edad);
                    arbol.insertar(nuevoPaciente);

                }
                else
                {
                    cout << "Ingrese NSS del paciente para la cita: ";
                    cin >> nss;

                    Pencontrar = arbol.buscarNodo(nss);

                    if (!(Pencontrar == nullptr))
                    {

                        int dia, mes, anio;
                        int hora, minutos;
                        string nombreMedico;
                        int numConsultorio;

                        do{
                            cout << "Ingrese el dia de la cita (DD): ";
                            cin >> dia;

                            if(dia>31 || dia<1)
                            {
                                cout << "El dia no se encuentra dentro del rango, favor de ingresar un dato valido" << endl;
                            }

                        }while(dia>31 || dia<1);

                        do{
                            cout << "Ingrese el mes de la cita (MM): ";
                            cin >> mes;

                            if(mes>12 || mes<1)
                            {
                                cout << "El mes no se encuentra dentro del rango, favor de ingresar un dato valido" << endl;
                            }

                        }while(mes>12 || mes<1);

                        do{
                            cout << "Ingrese el anio de la cita (AAAA): ";
                            cin >> anio;

                            if(anio<2023)
                            {
                                cout << "El anio no se encuentra dentro del rango, favor de ingresar un dato valido" << endl;
                            }

                        }while(anio<2023);

                        do{
                            cout << "Ingrese unicamente la hora de la cita (formato de 24 hrs): ";
                            cin >> hora;

                            if(hora>23 || hora<0)
                            {
                                cout << "La hora no se encuentra dentro del rango, favor de ingresar un dato valido" << endl;
                            }

                        }while(hora>23 || hora<0);

                        do{
                            cout << "Ingrese unicamente el minuto de la cita: ";
                            cin >> minutos;

                            if(minutos>59 || minutos<0)
                            {
                                cout << "Los minutos no se encuentran dentro del rango, favor de ingresar un dato valido" << endl;
                            }

                        }while(minutos>59 || minutos<0);

                        cout << "Ingrese nombre del medico: ";
                        cin >> nombreMedico;
                        cout << "Ingrese numero de consultorio: ";
                        cin >> numConsultorio;
                        cout << endl;

                        Pencontrar->paciente.insertarCitas(dia, mes, anio, hora, minutos, nombreMedico, numConsultorio);

                    } else {
                        cout << "Paciente no encontrado." << endl;
                    }
                }

                break;

        case 2:

            ///Moodifica al paciente o la cita

            do
            {
                cout << "1) Paciente" << endl;
                cout << "2) Cita" << endl;
                cout << "Opcion: ";
                cin >> opc;

            }while(opc !=1 && opc !=2);

            if (opc == 1)
            {
                cout << "Ingrese el NSS del paciente a modificar: ";
                cin >> nss;
                cout << endl;

                Pencontrar = arbol.buscarNodo(nss);

                if (!(Pencontrar == nullptr))
                {
                    Pencontrar->paciente.modificarPaciente();

                } else {
                    cout << "Paciente no encontrado." << endl;
                }
            }
            else
            {
                cout << "Ingrese el NSS del paciente: ";
                cin >> nss;
                cout << endl;

                Pencontrar = arbol.buscarNodo(nss);

                if (!(Pencontrar == nullptr))
                {
                    cout << "Ingresa el numero de cita "<<endl;
                    cin >> numCita;
                    Pencontrar->paciente.mostrarDatos();
                    Pencontrar->paciente.getCitas()->obtenerCita(numCita).modificarCita();
                } 
            }

            break;

        case 3:

            ///Busqueda del paciente con su DNS

            cout << "Ingrese el NSS del paciente: ";
            cin >> nss;
            cout << endl;

            Pencontrar = arbol.buscarNodo(nss);

            if (!(Pencontrar == nullptr))
            {
                Pencontrar->paciente.mostrarDatos();

            } else {
                cout << "Paciente no encontrado." << endl;
            }

            break;

        case 4:

            ///Imprime preorden
            arbol.imprimirPreorden();
            break;

        case 5:

            ///Imprime inorden
            arbol.imprimirInorden();

            break;

        case 6:

            /// Imprime postorden
            arbol.imprimirPostorden();
            break;

        case 7:

            ///Exportar a un archivo txt los datos de los pacientes

            {
                string nombreArchivo = "HospitalFCC.txt";
                ofstream archivo(nombreArchivo);

                if (archivo.is_open())
                {

                    streambuf* respaldo = cout.rdbuf();
                    cout.rdbuf(archivo.rdbuf());


                    avl.imprimirInorden();


                    cout.rdbuf(respaldo);

                    cout << "Exportado correctamente." <<endl;
                }
                else
                {
                    cerr << "Error al abrir el archivo." << endl;
                }


                archivo.close();
            }

            break;

        case 8:

            ///Eliminar un paciente
            cout << "Ingrese el DNS del paciente a eliminar: ";
            cin >> nss;
            cout << endl;

            arbol.eliminar(nss);

            break;

        case 9:

            ///Salir del programa
            cout << "Gracias por visitar el Hospital NASK >.<" << endl;
            break;
    }

    }while(opc != 9);


    return 0;
}
