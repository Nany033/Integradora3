#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <sstream>

using namespace std;

struct Bitacora {
    string mes;
    int dia;
    string hora;
    string ipOrigen;
    int puerto;
    string razonFalla;
};

void leerArchivo(const string& bitacora, vector<Bitacora>& bitacora1, map<string, int>& accesosIP) {
    ifstream archivo(bitacora);

    if (!archivo) {
        cerr << "No se pudo abrir el archivo." << endl;
        return;
    }

    map<string, int> meses = {{"Jan", 1}, {"Feb", 2}, {"Mar", 3}, {"Apr", 4}, {"May", 5}, {"Jun", 6}, {"Jul", 7}, {"Aug", 8}, {"Sep", 9}, {"Oct", 10}, {"Nov", 11}, {"Dec", 12}};

    string mes, hora, ip, razonFalla;
    int dia, puerto;

    while (archivo >> mes >> dia >> hora >> ip >> puerto >> razonFalla) {
        Bitacora b;
        b.mes = meses[mes];
        b.dia = dia;
        b.hora = hora;
        b.ipOrigen = ip + ":" + to_string(puerto);
        b.razonFalla = razonFalla;

        bitacora1.push_back(b);

        // Incrementar el contador de accesos para esta IP
        accesosIP[ip]++;
    }

    archivo.close();
}

int main() {
    string bitacora = "bitacora.txt";
    vector<Bitacora> bitacora1;
    map<string, int> accesosIP;

    leerArchivo(bitacora, bitacora1, accesosIP);

    set<pair<int, string>> bstAccesosIP(accesosIP.begin(), accesosIP.end());

    cout << "Las 5 direcciones IP con más accesos son:" << endl;

    int count = 0;
    for (auto it = bstAccesosIP.rbegin(); it != bstAccesosIP.rend() && count < 5; ++it, ++count) {
        cout << "IP: " << it->second << ", Accesos: " << it->first << endl;
    }

    return 0;
}
