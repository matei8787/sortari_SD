#include<bits/stdc++.h>
#include <chrono>
using namespace std;
using namespace std::chrono;
vector<int> v;
const string INFILE = "date.in";
const string OUTFILE = "date.out";
namespace radix_sort
{
    const int BAZA = 10;
    int nr_max;
    void radix_sort(int putere = 1)
    {
        if ( putere > nr_max )
            return;
        vector<int> vf(BAZA+1, 0), v_nou(v.size()), indexi(BAZA+1, 0);
        for ( int x : v )
        {
            vf[(x/putere)%BAZA]++;
        }
        for ( int i = 1 ; i < BAZA ; i++ )
            vf[i] += vf[i-1];
        for ( int x : v )
        {
            int index = indexi[(x/putere)%BAZA];
            if ( (x/putere)%BAZA != 0 )
                index += vf[(x/putere)%BAZA-1];
            v_nou[index] = x;
            indexi[(x/putere)%BAZA]++;

        }
        for ( int i = 0 ; i < v_nou.size() ; i++ )
        {
            v[i] = v_nou[i];
        }
        radix_sort(putere*BAZA);
    }
    void make_nr_max()
    {
        nr_max = *max_element(v.begin(), v.end());
    }
    void sorteaza()
    {
        make_nr_max();
        radix_sort();
    }
}
namespace merge_sort{
    void interclaseaza(int start, int mid, int stop)
    {
        vector<int> v2(stop - start + 1);
        int i = start, j = mid + 1, k = 0;
        while ( i <= mid && j <= stop )
        {
            if ( v[i] < v[j] )
                v2[k++] = v[i++];
            else
                v2[k++] = v[j++];
        }
        while ( i <= mid )
            v2[k++] = v[i++];
        while ( j <= stop )
            v2[k++] = v[j++];
        j = 0;
        for ( int i = start ; i <= stop ; i++ )
        {
            v[i] = v2[j++];
        }
    }
    void smerge(int start, int stop)
    {
        if ( start == stop )
            return;
        int mij = start + ( stop - start ) / 2;
        smerge(start, mij);
        smerge(mij + 1, stop);
        interclaseaza(start, mij, stop);
    }
    void sorteaza()
    {
        smerge(0, v.size()-1);
    }
}
namespace heap_sort
{
    int fs(int nod){ return nod * 2 + 1; }
    int fd(int nod){ return nod * 2 + 2; }
    void heapuieste(int nod, int cate)
    {
        int st = fs(nod);
        int dr = fd(nod);
        int maxi = nod;
        if ( st < v.size() - cate && v[st] > v[maxi] )
            maxi = st;
        if ( dr < v.size() - cate && v[dr] > v[maxi] )
            maxi = dr;
        if ( maxi == nod )
            return;
        swap(v[maxi], v[nod]);
        heapuieste(maxi, cate);
    }
    void make_max_heap()
    {
        for ( int i = v.size() - 1 ; i >= 0 ; i-- )
        {
            heapuieste(i, 0);
        }
    }
    void sorteaza()
    {
        make_max_heap();
        for ( int i = v.size() - 1 ; i >= 1 ; i-- )
        {
            swap(v[0], v[i]);
            heapuieste(0, v.size() - i);
        }
    }
}
namespace quick_sort
{
    int pivoteaza(int st, int dr)
    {
        int pivot = v[st];
        while ( st < dr )
        {
            if ( v[st] > v[dr] )
                swap(v[st], v[dr]);
            if ( pivot == v[st] )
            {
                dr--;
            }
            else
            {
                st++;
            }
        }
        return st;
    }
    void quick(int st, int dr)
    {
        if ( st >= dr )
            return;
        int poz = pivoteaza(st, dr);
        quick(st, poz-1);
        quick(poz+1, dr);
    }
    void sorteaza()
    {
        quick(0, v.size() - 1);
    }
}
namespace shell_sort
{
    void sorteaza()
    {
        for ( int spatiu = v.size() / 2; spatiu > 0 ; spatiu /= 2 )
        {
            for ( int i = spatiu ; i < v.size() ; i++ )
            {
                int aux = v[i];
                int j;
                for ( j = i ; j >= spatiu && v[j-spatiu] > aux ; j -= spatiu )
                {
                    v[j] = v[j-spatiu];
                }
                v[j] = aux;
            }
        }
    }
}
namespace stalin_sort ///dar chiar sa mearga
{
    const int N = 1e3+5;
    int vectorul[N];
    int n;
    void sterge_element(int x)
    {
        for ( int i = x + 1 ; i <= n ; i++ )
        {
            vectorul[i-1] = vectorul[i];
        }
        n--;
    }
    void adauga_element(int poz, int x)
    {
        for ( int i =  n ; i >= poz ; i-- )
        {
            vectorul[i+1] = vectorul[i];
        }
        vectorul[poz] = x;
        n++;
    }
    void afisv(vector<int> v)
    {
        for ( int x : v )
        {
            cout<<x<<" ";
        }
        cout<<'\n';
    }
    void stalineste()
    {
        bool e_sortat = false;
        while ( !e_sortat )
        {
            e_sortat = true;
            for ( int i = 1 ; i < n ; i++ )
            {
                if ( vectorul[i] > vectorul[i+1] )
                {
                    swap(vectorul[i], vectorul[i+1]);
                    e_sortat = false;
                }
            }
        }
    }
    void sorteaza()
    {
        int i = 1;
        for ( int x : v )
        {
            vectorul[i++] = x;
        }
        n = i;
        vectorul[i] = INT_MAX;
        vectorul[0] = INT_MIN;
        stalineste();
        for ( i = 1 ; i < n ; i++ )
        {
            v[i-1] = vectorul[i];
        }
    }
}
namespace Bogoiala
{
    bool e_sortat()
    {
        for ( int i = 0 ; i < v.size() - 1 ; i++ )
        {
            if ( v[i] > v[i+1] )
                return false;
        }
        return true;
    }
    void afisv(vector<int> v)
    {
        for ( int x : v )
        {
            cout<<x<<" ";
        }
        cout<<'\n';
    }
    void bogo_sort()
    {
        while ( !e_sortat() )
        {
            shuffle(v.begin(), v.end(), default_random_engine{});
            afisv(v);
        }
    }
    void bozo_sort()
    {
        while ( !e_sortat() )
        {
            int a = rand() % v.size();
            int b = rand() % v.size();
            if ( a != b )
                swap(v[a], v[b]);
            afisv(v);
        }
    }
    void miracle_sort()
    {
        while ( !e_sortat() )
        {
            ///asteapta miracol sa se sorteze
        }
    }
    void shrodinger_sort()
    {
        cout<<"e sortat, doar ca nu ai ales universul bun in care sa traiesti";
        exit(0);
    }

}
void test_desc(int n, ofstream& out_file )
{
    out_file<<n<<'\n';
    for ( int i = n ; i >= 1 ; i-- )
    {
        out_file<<i<<" ";
    }
}
void test_cresc(int n, ofstream& out )
{
    out<<n<<'\n';
    for ( int i = 1 ; i <= n ; i++ )
    {
        out<<i<<" ";
    }
}
void test_bitonic(int n, ofstream& out )
{
    out<<n<<'\n';
    for ( int i = 1 ; i <= n / 2 ; i++ )
    {
        out<<i<<" ";
    }
    for ( int i = n / 2 + 1, j = n / 2 + 1 ; i <= n ; i++, j-- )
    {
        out<<j<<" ";
    }
}
void test_random(int n, int maxx, int seed, ofstream& out )
{
    srand(seed);
    out<<n<<'\n';
    for ( int i = 1 ; i <= n ; i++ )
    {
        out<<rand()%(maxx+1)<<" ";
    }
}
void genereaza_teste()
{
    string s = "test";
    string ext = ".in";
    ofstream f1(s + "1" + ext);
    test_cresc(250, f1); ///nmk mic
    ofstream f2(s + "2" + ext);
    test_cresc(1000000, f2); ///nmk mare
    ofstream f3(s + "3" + ext);
    test_desc(500, f3); ///tot mic
    ofstream f4(s + "4" + ext);
    test_desc(200000, f4); ///tot mare
    ofstream f5(s + "5" + ext);
    test_bitonic(1500, f5); ///bitonic mic
    ofstream f6(s + "6" + ext);
    test_bitonic(100000, f6); ///bitonic mare
    ofstream f7(s + "7" + ext);
    test_random(600, 1000000000, rand(), f7); ///random mic nr mari
    ofstream f8(s + "8" + ext);
    test_random(1000, 50, rand(), f8); ///random mic nr mici
    ofstream f9(s + "9" + ext);
    test_random(100000, 178, rand(), f9); ///random mare nr mici
    ofstream f(s + "10" + ext);
    test_random(100000, 1000000000, rand(), f); ///random mare nr mari
}
void copiaza(vector<int>& from, vector<int>& to)
{
    to.resize(from.size());
    for ( int i = 0 ; i < from.size() ; i++ )
        to[i] = from[i];
}
void testeaza(string sin)
{
    ifstream in(sin);
    int n;
    in>>n;
    vector<int> aux;
    for ( int i = 1 ; i <= n ; i++ )
    {
        int x;
        in>>x;
        aux.push_back(x);
    }
    copiaza(aux, v);
    auto start = high_resolution_clock::now();
    heap_sort::sorteaza();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Timp heap: " << duration.count()<<'\n';
    copiaza(aux, v);
    start = high_resolution_clock::now();
    radix_sort::sorteaza();
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout<< "Timp radix: " <<duration.count()<<'\n';
    copiaza(aux, v);
    start = high_resolution_clock::now();
    merge_sort::sorteaza();
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout<< "Timp merge: " <<duration.count()<<'\n';
    copiaza(aux, v);
    start = high_resolution_clock::now();
    quick_sort::sorteaza();
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout<< "Timp quick: " <<duration.count()<<'\n';
    copiaza(aux, v);
    start = high_resolution_clock::now();
    shell_sort::sorteaza();
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout<< "Timp shell: " <<duration.count()<<'\n';
    start = high_resolution_clock::now();
    copiaza(aux, v);
    stalin_sort::sorteaza();
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout<< "Timp bubble: " <<duration.count()<<'\n';
}
int main()
{
    genereaza_teste();
    int op;
    cout<<"Alege test:\n1)Crescator mic\n2)Crescator mare\n3)Descrescator mic\n4)Descrescator mare\n5)Bitonic mic\n6)Bitonic mare\n7)Random mic cu nr mari\n8)Random mic cu nr mici\n9)Random mare cu nr mici\n10)Random mare cu nr mari\n";
    cin>>op;
    string nr = "";
    if ( op == 10 )
        nr = "10";
    else
        nr = nr + (char)(op + '0');
    string in = "test" + nr + ".in";
    testeaza(in);
}
