#include<iostream>
#include<random>
#include<ctime>

using namespace std;

template<typename Type>
int check(Type array[], int size,int choice) // funkcja sprawdzaj�ca czy dobrze posrtowano tablic�
{
    for (int i =0; i<size-2;i++) {
        if (choice == 1 || choice == 2 || choice == 4) { // sprawdza czy posrtowano rosn�co
            if (array[i + 1] >= array[i]) {
                continue;
            } else {
                return 0; // zwraca zero jak �le tablica jest posrtowana
            }
        }
        if (choice ==3) {
            if (array[i + 1] <= array[i]) { // sprawdza czy posrtowano malej�co
                continue;
            } else {
                return 0;
            }
        }

    }
    return 1; // zwraca jeden jak dobrze tablica jest posortowana
}

template <typename Type>
void merge(Type array[], int start, int middle, int last, int choice) { // funkcja sortuj�ca
    Type *tmp_array = new Type[(last - start + 1)]; // utworzenie tablicy pomocniczej o odpowiednim rozmiarze
    int i = start;
    int j = middle +1; // zmienne pomocnicze
    int k = 0;
    if (choice == 1|| choice ==2 || choice == 4) { // posortowanie rosn�co
        while (i <= middle && j <= last) {
            if (array[j] < array[i]) { // zapisanie do tablicy pomocniczej warto�ci mniejszej
                tmp_array[k] = array[j];
                j++;
            } else {
                tmp_array[k] = array[i]; // zapisanie do tablicy pomocniczej warto�ci mniejszej
                i++;
            }
            k++;
        }
    }
    if (choice == 3) { // posortowanie malej�co
        while (i <= middle && j <= last) {
            if (array[j] > array[i]) { // zapisanie do tablicy pomocniczej warto�ci wi�kszej
                tmp_array[k] = array[j];
                j++;
            } else {
                tmp_array[k] = array[i]; // zapisanie do tablicy pomocniczej warto�ci wi�kszej
                i++;
            }
            k++;
        }
    }

    if (i <= middle) {
        while (i <= middle) {
            tmp_array[k] = array[i]; //przypisanie do nast�pnych indeks�w tablicy pomocniczej warto�ci wi�kszych (lub mniejszych), por�wnywalnych wcze�niej
            i++;
            k++;
        }
    } else {
        while (j <= last) {
            tmp_array[k] = array[j]; //przypisanie do nast�pnych indeks�w tablicy pomocniczej warto�ci wi�kszych (lub mniejszych), por�wnywalnych wcze�niej
            j++;
            k++;
        }
    }

    for (i = 0; i <= last - start; i++) { // zamiana miejsc w tablicy g��wnej
        array[start + i] = tmp_array[i];
    }

    delete [] tmp_array;  // usuni�cie tablicy, aby nie by�o wycieku
}
template <typename Type>
void merge_sort(Type array[], int start, int last, int choice) // funckja dziel�ca tablic� na cz�ci
{
    int middle = 0;

    if (start != last)
    {
        middle = (start + last) / 2; // dzielenie tablicy na cz�ci
        merge_sort(array, start, middle, choice); //dzielenie tablicy na cz�ci dop�ki pocz�tek indeksu tablicy nie jest r�wny ko�cowy, pierwsza cz��
        merge_sort(array, middle + 1, last, choice); // druga cz��
        merge(array, start, middle, last, choice); //wywo�anie funkcji sortuj�cej. Na pocz�tku sortuje cz�ci podzielone, a nast�pnie ca�o�� tablicy
    }
}

int main()
{
    int size=0;
    int choice=0;
    int percentage = 95; // procent, ile liczb jest ju� posortowanych
    random_device rd;
    mt19937 gen(rd()); // generator losowych liczb
    uniform_int_distribution<> distr(0, 100); // przedzia�
    cout << "Wprowadz  rozmiar tablicy:  ";
    cin >> size;
    cout << "Wybierz tryb sortowania:" << endl << "1. Sortowanie rosnaco losowych liczb" << endl
         << "2.Sortowanie tablicy z czesciowo posortowanymi danymi " << endl
         << "3.Sortowanie malejaco losowych liczb " << endl
         << "4.Sortowanie rosnaco, liczb posortowanych malejaco";
    cin >> choice;
    auto *array = new double[size];
    float time = 0;
    if (choice == 1 || choice == 3) {
        for (int j = 0; j < 100; j++) { // sortowanie 100 tablic
            // utworzenie dynamicznej tablicy o okre�lonym rozmiarze
            for (int i = 0; i < size; i++) // wczytywanie losowych liczb do tablicy
            {
                array[i] = distr(gen);
            }
            /* cout << "Tablica przed sortowaniem" << endl;
             for (int i = 0; i < size; i++) {  // wypisanie tablicy przed posortowaniem
                 cout << array[i] << " ";
             } */
            clock_t timeBegin = clock();
            merge_sort(array, 0, size - 1, choice); // wywolanie funkcji sortujacej
            clock_t timeEnd = clock();
            time += timeEnd - timeBegin;
            /* cout << endl << "Tablica po posortowaniu:" << endl;
             for (int i = 0; i < size; i++) {  // wypisanie tablicy po sortowaniu
                 cout << array[i] << " ";
             } */
            if (check(array, size, choice) == 1) {
                cout << "Posortowano zgodnie" << endl;
            } else {
                cout << "Posortowano niezgodnie" << endl;
                break;
            }
        }
        cout << "Czas dzialania programu: " << (time / CLOCKS_PER_SEC) << "s"; //pokazuje czas dzia�ania sortowania
    }
    else if (choice == 2) {
        for(int j =0; j<100;j++) {
            uniform_int_distribution<> distr1(0, percentage);
            for (int i = 0; i <size; i++) // wczytywanie liczb od 0 do ustawionego procentu (aby tylko dana cz�� by�a posortowana)
            {
                array[i] = distr1(gen);
            }
            merge_sort(array, 0, size - 1, choice);
            uniform_int_distribution<> distr2(percentage, 100);
            for (int i = size - 1; i > (size * percentage / 100); i--)
            {
                array[i] = distr2(gen); //zast�pienie liczb, aby tylko cz�� by�a posortowana
            }
            /* cout << "Tablica przed sortowaniem" << endl;
            for (int i = 0; i < size; i++) {  // wypisanie tablicy przed posortowaniem
            cout << array[i] << " ";
            } */
            clock_t timeBegin = clock();
            merge_sort(array, 0, size - 1, choice); // wywolanie funkcji sortujacej
            clock_t timeEnd = clock();
            time += timeEnd - timeBegin;
            /*cout << endl << "Tablica po posortowaniu:" << endl;
            for (int i = 0; i < size; i++) {  // wypisanie tablicy po sortowaniu
            cout << array[i] << " ";
            } */
            if (check(array, size, choice) == 1) {
                cout << "Posortowano zgodnie" << endl;
            } else {
                cout << "Posortowano niezgodnie" << endl;
                break;
            }
        }
        cout << "Czas dzialania programu: " << (time/CLOCKS_PER_SEC) << "s"; //pokazuje czas dzia�ania sortowania
    }
    else if (choice == 4) {
        for(int j =0; j<100;j++) {
            for (int i = 0; i < size; i++) // wczytywanie losowych liczb do tablicy
            {
                array[i] = distr(gen);
            }
            merge_sort(array, 0, size - 1, 3);
            /* cout << "Tablica przed sortowaniem" << endl;
             for (int i = 0; i < size; i++) {  // wypisanie tablicy przed posortowaniem
                 cout << array[i] << " ";
             } */
            clock_t timeBegin = clock();
            merge_sort(array, 0, size - 1, choice); // wywolanie funkcji sortujacej
            clock_t timeEnd = clock();
            time += timeEnd - timeBegin;
            /* cout << endl << "Tablica po posortowaniu:" << endl;
             for (int i = 0; i < size; i++) {  // wypisanie tablicy po sortowaniu
                 cout << array[i] << " ";
             } */
            if (check(array, size, choice) == 1) {
                cout << "Posortowano zgodnie" << endl;
            } else {
                cout << "Posortowano niezgodnie" << endl;
                break;
            }
        }
        cout << "Czas dzialania programu: " << (time/CLOCKS_PER_SEC) << "s"; //pokazuje czas dzia�ania sortowania
    } else {
        cout << "Nie ma takiej opcji:" << endl;
    }

    delete[] array; // usuni�cie tablicy, aby nie by�o wycieku
    return 0; //

}
