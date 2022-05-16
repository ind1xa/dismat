#include <iostream>

using namespace std;

//pomoću formule za opće rješenje homogene rekurzivne relacije
double formula (double l1, double l2, double n, double p, int t) {
    if (t == 0) return n;
    if (t == 1) return p;
    //karakt. jedn.: x^2 - l1x - l2 = 0
    l1 = -l1;
    l2 = -l2;
    double rjJedn1 = (-l1 + sqrt(l1*l1 - 4 * l2)) /2;
    double rjJedn2 = (-l1 - sqrt(l1*l1 - 4 * l2)) /2;
    
    double alfa, beta;
    double determinanta = rjJedn2 - rjJedn1;
    if (abs(determinanta) > 10e-8) {
        alfa = (n*rjJedn2 - p)/determinanta;
        beta = (p - rjJedn1*n)/determinanta;
        return alfa * pow(rjJedn1, t) + beta * pow(rjJedn2, t);
    } else {
        alfa = n;
        if (abs(rjJedn1) < 10e-8) return 0;
        beta = (p-alfa*rjJedn1)/rjJedn1;
        return alfa * pow(rjJedn1, t) + beta *t* pow(rjJedn2, t);
    }
    return 0;
}

//računanjem odgovarajućeg člana niza rekurzivno
double rekurzivno (double l1, double l2, double n, double p, int t) {
    if (t == 0) {
        return n;
    } else if (t == 1) {
        return p;
    } else {
        return l1*rekurzivno(l1, l2, n, p, t-1) + l2*rekurzivno(l1, l2, n, p, t-2);
    }
}

int main (void) {
    double lambda1, lambda2, nulti, prvi;
    int trazeni;
    cout << "Unesite prvi koeficijent λ_1 rekurzivne relacije: " << endl;
    cin >> lambda1;
    cout << "Unesite drugi koeficijent λ_2 rekurzivne relacije: " << endl;
    cin >> lambda2;

    cout << "Unesite vrijednost nultog clana niza a_0: " << endl;
    cin >> nulti;
    cout << "Unesite vrijednost prvog clana niza a_1: " << endl;
    cin >> prvi;

    cout << "Unesite redni broj n trazenog clana niza: " << endl;
    cin >> trazeni;
    
    double rjFormulom = formula(lambda1, lambda2, nulti, prvi, trazeni);
    double rjRekurzivno = rekurzivno(lambda1, lambda2, nulti, prvi, trazeni);

    cout << "Vrijednost n-tog clana niza pomocu formule: " << rjFormulom << endl;
    cout << "Vrijednost n-tog clana niza iz rekurzije: " << rjRekurzivno << endl;
    return 0;
}
