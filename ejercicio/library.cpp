#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

using namespace std;

struct ColorConsole
{
    static constexpr auto fg_blue = "\033[34m";
    static constexpr auto bg_white = "\033[47m";
};

struct ConsoleBox
{
    void new_text() {/*...*/}
    void set_text(const string &text) { cout << text << endl; }
};

ConsoleBox *consoleBox = new ConsoleBox;

// Función para cargar y mostrar el contenido de un archivo
void load_script(const char* filename, bool show_script = false)
{
    string script;
    ifstream file;

    try// Manejo de excepciones
    {
        // Intenta abrir el archivo
        file.open(filename);
        if (!file.is_open())
        {
            cerr << "Error de apertura de " << filename << endl;
            return;
        }
        // Lee el contenido del archivo y lo almacena en 'script'
        script.assign((istreambuf_iterator<char>(file)), (istreambuf_iterator<char>()));
        // Cierra el archivo después de la lectura
        file.close();

        // Muestra el contenido si show_script es verdadero
        if (show_script)
        {
            cout << ColorConsole::fg_blue << ColorConsole::bg_white;
            cout << script << endl;
        }
        // Actualiza la consola con el contenido del script
        consoleBox->new_text();
        consoleBox->set_text(script);
    }
    catch (const ifstream::failure &e)
    {
        cerr << "Error durante la lectura del archivo: " << e.what() << endl;
        if (file.is_open())
            file.close();
    }
    catch (const exception &e)
    {
        cerr << "Excepción general: " << e.what() << endl;
        if (file.is_open())
            file.close();
    }
    catch (...)
    {
        cerr << "Error desconocido durante la lectura del archivo" << endl;
        if (file.is_open())
            file.close();
    }
}

// Función para solicitar al usuario un nombre de archivo y cargarlo
void load_script()
{
    char filename[500];
    cout << "Archivo: ";
    // Lee el nombre del archivo
    cin >> filename;
    load_script(filename, true);// Carga el archivo y muestra su contenido

}

int main()
{
    load_script(); // Carga el archivo por defecto
    return 0;
}