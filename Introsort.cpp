#include<iostream>
#include<random>
#include<ctime>
#include<cmath>

using namespace std;

#define M_LN2 0.69314718055994530942

template<typename Type>
int check(Type array[], int size,int choice) // funkcja sprawdzaj¹ca czy dobrze posrtowano tablicê
{
    for (int i =0; i<size-2;i++) {
        if (choice == 1 || choice == 2 || choice == 4) { // sprawdza czy posrtowano rosn¹co
            if (array[i + 1] >= array[i]) {
                continue;
            } else {
                return 0; // zwraca zero jak Ÿle tablica jest posrtowana
            }
        }
        if (choice ==3) {
            if (array[i + 1] <= array[i]) { // sprawdza czy posrtowano malej¹co
                continue;
            } else {
                return 0;
            }
        }

    }
    return 1; // zwraca jeden jak dobrze tablica jest posortowana
}
template <typename Type>
void InsertionSort(Type array[], int size,int choice) {
    int tmp;
    int j;
    for(int i = 1; i < size; ++i) {
        tmp = array[i];
        if (choice == 1 || choice == 2 || choice == 4) {
            for (j = i; j > 0 && tmp < array[j - 1]; --j) {
                array[j] = array[j - 1];
            }
            array[j] = tmp;
        }
        if (choice == 3) {
            for (j = i; j > 0 && tmp > array[j - 1]; --j) {
                array[j] = array[j - 1];
            }
            array[j] = tmp;
        }
    }
}
template <typename Type>
void heapify(Type array[], int size, int i , int choice)
{
    int largest = i;
    int left = 2 * i + 1; // lewy = 2*i + 1
    int right = 2 * i + 2; // prawy = 2*i + 2
    Type tmp = 0;
    if (choice == 1 || choice == 2 || choice ==4) { // posortowanie rosnąco
        if (left < size && array[left] > array[largest]) { // zamienia największą liczbe na wartoœæ lew¹, jeœli jest spe³niony warunek
            largest = left;
        }
        if (right < size && array[right] > array[largest]) { // zamienia najwiêksz¹ liczbê na wartoœæ praw¹, jeœli jest spe³niony warunek
            largest = right;
        }
    }
    if (choice == 3) { // posortowanie malej¹co
        if (left < size && array[left] < array[largest]) { // zamienia (tutaj najni¿sz¹) liczbê na wartoœæ lew¹, jeœli jest spe³niony warunek
            largest = left;
        }
        if (right < size && array[right] < array[largest]) { // zamienia (tutaj najni¿sz¹) liczbê na wartoœæ praw¹, jeœli jest spe³niony warunek
            largest = right;
        }
    }
    if (largest != i) { // jeœli najwiêksza/najni¿sza nie jest równa i zamienia miejscami
        tmp = array[i];
        array[i] = array[largest];
        array[largest] = tmp;
        heapify(array, size, largest, choice); // rekurencyjnie wywo³anie funkcji
    }
}

template <typename Type>
void heap_sort(Type array[], int size, int choice) // funkcja heapsort
{
    Type tmp = 0;
    for (int i = size / 2 - 1; i >= 0; i--) { // zamiana miejsc w tablicy
        heapify(array, size, i, choice);
    }
    for (int i = size - 1; i >= 0; i--) { //zamienia miejscami kolejne wartoœci
        tmp = array[0];
        array[0] = array[i];
        array[i] = tmp;
        heapify(array, i, 0, choice);
    }
}

template<typename Type>
int division(Type array[], int first, int last, int choice) // funckja dziel¹ca tablicê na 2 czêœci: na tablicê posiadaj¹c¹ mniejsze lub równe oraz na wiêksze lub równe liczby od tmp1
{
    Type tmp1 = array[(first+last)/2]; // obieramy tmp1
    Type tmp2 = 0; // do zamiany miejsc
    while (true) // petla nieskonczona, koñczy siê przy return
    {
        if (choice == 1 || choice == 2 || choice ==4) {  //sortowanie rosnace
            while (array[last] > tmp1) // dopoki elementy sa wieksze od tmp1
                last--;
            while (array[first] < tmp1) // dopoki elementy sa mniejsze od tmp1
                first++;
        }
        if(choice == 3) { // sortowanie malejace
            while (array[last] < tmp1) // dopoki elementy sa mniejsze od tmp1
                last--;
            while (array[first] > tmp1) // dopoki elementy sa wieksze od tmp1
                first++;
        }
        if (first < last) // zamieniamy miejscami gdy first < last
        {
            tmp2 = array[first];
            array[first] = array[last];
            array[last] = tmp2;
            first++;
            last--;
        }
        else { // zwracamy last jako punkt podzialu tablicy gdy first >= last
            return last;
        }
    }
}

template <typename Type>
void Mixed_sort(Type array[], int size, int depthLimit, int choice)
{
    int pivot = 0;
    if(depthLimit <=0 ) {
        heap_sort(array,size,choice);
        return;
    }
    pivot = division(array,0,size-1,choice);
    if(pivot > 9) {
        Mixed_sort(array,pivot,depthLimit-1,choice); //wywołanie rekuręcyjne dla lewj tablicy
    }
    if(size - 1 - pivot > 9) {
        Mixed_sort(array+pivot+1,size -1 -pivot,depthLimit-1,choice);
    }

}

template <typename Type>
void IntroSort (Type array[], int size,int choice) // funkcja sortuj¹ca
{
    int depth_limit = floor(2 * log(size)/M_LN2);// głębokość wywołania rekurencji
    Mixed_sort(array,size,depth_limit,choice); //wywo³anie funkcji Mixed_sort
    InsertionSort(array,size,choice);
}

int main()
{
    int size=0;
    int choice=0;
    int percentage = 99.7; // procent, ile liczb jest ju¿ posortowanych
    random_device rd;
    mt19937 gen(rd()); // generator losowych liczb
    uniform_int_distribution<> distr(0, 100); // przedzia³
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
            // utworzenie dynamicznej tablicy o okreœlonym rozmiarze
            for (int i = 0; i < size; i++) // wczytywanie losowych liczb do tablicy
            {
                array[i] = distr(gen);
            }
            /* cout << "Tablica przed sortowaniem" << endl;
             for (int i = 0; i < size; i++) {  // wypisanie tablicy przed posortowaniem
                 cout << array[i] << " ";
             } */
            clock_t timeBegin = clock();
            IntroSort(array, size, choice); // wywolanie funkcji sortujacej
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
        cout << "Czas dzialania programu: " << (time / CLOCKS_PER_SEC) << "s"; //pokazuje czas dzia³ania sortowania
    }
    else if (choice == 2) {
        for(int j =0; j<100;j++) {
            uniform_int_distribution<> distr1(0, percentage);
            for (int i = 0; i <size; i++) // wczytywanie liczb od 0 do ustawionego procentu (aby tylko dana czêœæ by³a posortowana)
            {
                array[i] = distr1(gen);
            }
            IntroSort(array, size, choice);
            uniform_int_distribution<> distr2(percentage, 100);
            for (int i = size - 1; i > (size * percentage / 100); i--)
            {
                array[i] = distr2(gen); //zast¹pienie liczb, aby tylko czêœæ by³a posortowana
            }
            /* cout << "Tablica przed sortowaniem" << endl;
            for (int i = 0; i < size; i++) {  // wypisanie tablicy przed posortowaniem
            cout << array[i] << " ";
            } */
            clock_t timeBegin = clock();
            IntroSort(array, size, choice); // wywolanie funkcji sortujacej
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
        cout << "Czas dzialania programu: " << (time/CLOCKS_PER_SEC) << "s"; //pokazuje czas dzia³ania sortowania
    }
    else if (choice == 4) {
        for(int j =0; j<100;j++) {
            for (int i = 0; i < size; i++) // wczytywanie losowych liczb do tablicy
            {
                array[i] = distr(gen);
            }
            IntroSort(array, size, 3);
            /* cout << "Tablica przed sortowaniem" << endl;
             for (int i = 0; i < size; i++) {  // wypisanie tablicy przed posortowaniem
                 cout << array[i] << " ";
             } */
            clock_t timeBegin = clock();
            IntroSort(array, size, choice); // wywolanie funkcji sortujacej
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
        cout << "Czas dzialania programu: " << (time/CLOCKS_PER_SEC) << "s"; //pokazuje czas dzia³ania sortowania
    } else {
        cout << "Nie ma takiej opcji:" << endl;
    }

    delete[] array; // usuniêcie tablicy, aby nie by³o wycieku
    return 0; //

}
