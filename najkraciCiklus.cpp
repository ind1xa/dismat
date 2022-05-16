#include <iostream>
#include <algorithm>

using namespace std;

bool biliSvugdje(int vrhovi[], int size) {
    for (int i = 0; i < size; i++) {
        if (vrhovi[i] != 1) return false;
    }
    return true;
}

int main (void) {
    int n, a, b;
    cout << "Unesite redom, odvojene razmakom, parametre n, a i b: ";
    cin >> n >> a >> b;

    int matrica[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrica[i][j] = 0;
        }
    }
    int vrhovi[n];
    for (int i = 0; i < n; i++) vrhovi[i] = 0;
    for (int k = 0; k < n; k++) {
        for (int l = k+1; l < n; l++) {
            matrica[k][l] = (a * (k+1) + b * (l+1)) * (a * (k+1) + b * (l+1)) + 1;
            matrica[l][k] = (a * (k+1) + b * (l+1)) * (a * (k+1) + b * (l+1)) + 1;
        }
    }
    
    for (int i = 0 ; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "  " << matrica[i][j] << " ";
        }
        cout << endl;
    }

    int poh = 0, min, mojvrh1, mojvrh2;
    min = matrica[0][1];
    for (int k = 0; k < n; k++) {
        for (int l = k+1; l < n; l++) {
            if (matrica[k][l] <= min) {
                min = matrica[k][l];
                mojvrh1 = k;
                mojvrh2 = l;
            }
        }
    }
    //cout << "Pocinjem od vrhova " << mojvrh1 << " i " << mojvrh2 << " tezine " << min << endl;
    poh += min;
    vrhovi[mojvrh1] = 1;
    vrhovi[mojvrh2] = 1;
    int novivrh, starivrh;
    while (!biliSvugdje(vrhovi, n)) {
        for (int i = 0; i < n; i++) {
            if (matrica[mojvrh1][i] != 0 && vrhovi[i] == 0) min = matrica[mojvrh1][i];
            if (matrica[mojvrh2][i] != 0 && vrhovi[i] == 0) min = matrica[mojvrh2][i];
        }
        for (int j = 0; j < n; j++) {
            if (matrica[mojvrh1][j] != 0 && vrhovi[j] == 0 && matrica[mojvrh1][j] <= min) {
                min = matrica[mojvrh1][j];
                starivrh = mojvrh1;
                novivrh = j;
            }
            if (matrica[mojvrh2][j] != 0 && vrhovi[j] == 0 && matrica[mojvrh2][j] <= min) {
                min = matrica[mojvrh2][j];
                starivrh = mojvrh2;
                novivrh = j;
            }
        }
        vrhovi[novivrh] = 1;
        poh += min;
        //cout << "Dalje idem sa vrha " << starivrh << " na " << novivrh << " tezinom " << min << endl;
        if (mojvrh1 == starivrh) mojvrh1 = novivrh;
        if (mojvrh2 == starivrh) mojvrh2 = novivrh;
    }
    //cout << "Za kraj spajam " << mojvrh1 << " i " << mojvrh2 << " tezinom " << matrica[mojvrh1][mojvrh2] << endl;
    poh += matrica[mojvrh1][mojvrh2];

    //----------------------------------

    int isc = 0;
    int sizeIsc = 1;
    for (int i = 1; i < n; i++) {
        sizeIsc *= i;
    }
    int iscRezultati[sizeIsc];
    int perms[n];
    for (int i = 0; i < n; i++) {
        perms[i] = i;
    }
    sort(perms, perms + n);
    for (int i = 0; i < n; i++) vrhovi[i] = 0;
    for (int i = 0; i < sizeIsc; i++) {
        isc = 0;
        for (int j = 0; j < n-1; j++) {
            isc += matrica[perms[j]][perms[j+1]];
        }
        isc += matrica[perms[0]][perms[n-1]];
        iscRezultati[i] = isc;
        next_permutation(perms, perms + n);
    }

    min = iscRezultati[0];
    for (int i = 0; i < sizeIsc; i++) {
        if (iscRezultati[i] < min) min = iscRezultati[i];
    }
    isc = min;

    cout << "Pohlepni algoritam nalazi ciklus duljine " << poh << endl;
    cout << "Iscrpni algoritam nalazi ciklus duljine " << isc << endl;
    if (poh == isc) cout << "Pohlepni algoritam na ovom grafu daje optimalno rješenje!";
    else cout << "Pohlepni algoritam na ovom grafu ne daje optimalno rješenje!";
}
