#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

class Sarki;
class CalmaListesi;
template <typename T>
class Node;
template <typename T>
class Kuyruk;
template <typename T>
class Vector;
template <typename T>
struct NodeS;
template <typename T>
class Stack;

class Sarki
{
public:
    std::string sarkiID;
    std::string sarkiAdi;
    std::string sarkiciAdi;
    int dinlenmeSayisi;
    int oynatmaSuresi;
    int dinlenmeSurePuani;

    Sarki(std::string &id, std::string &sarkiAdi, std::string &sarkiciAdi) : sarkiID(id), sarkiAdi(sarkiAdi), sarkiciAdi(sarkiciAdi), dinlenmeSurePuani(0), oynatmaSuresi(0) {}
    Sarki() {}
    operator std::string() const
    {
        return sarkiID + "," + sarkiAdi + "," + sarkiciAdi;
    }
    friend std::ostream &operator<<(std::ostream &os, const Sarki &sarki)
    {
        os << sarki.sarkiID + "," + sarki.sarkiAdi + "," + sarki.sarkiciAdi;
        return os;
    }
    bool operator==(const Sarki &other) const
    {
        return ((sarkiID == other.sarkiID) && (sarkiAdi == other.sarkiAdi) && (sarkiciAdi == other.sarkiciAdi));
    }

    std::string ToString()
    {
        return sarkiID + "," + sarkiAdi + "," + sarkiciAdi;
    }

};
template <typename T>
class Kuyruk
{
public:
    Node<T> *front;
    Node<T> *rear;
    int size;

    Kuyruk() : front(nullptr), rear(nullptr), size(0) {}

    ~Kuyruk()
    {
        while (!isEmpty())
        {
            dequeue();
        }
    }
    bool isEmpty() const
    {
        return size == 0;
    }

    void enqueue(const T &data)
    {
        Node<T> *newNode = new Node<T>(data);
        if (isEmpty())
        {
            newNode->next = nullptr;
            front = rear = newNode;
        }
        else
        {
            newNode->next = nullptr;
            rear->next = newNode;
            rear = newNode;
        }
        size++;
    }

    void dequeue()
    {
        if (isEmpty())
        {
            std::cerr << "Hata: Kuyruk boş, çıkarma işlemi yapılamaz!" << std::endl;
            return;
        }
        Node<T> *temp = front;
        front = front->next;
        delete temp;
        size--;
        if (isEmpty())
        {
            rear = nullptr;
        }
    }

    T &begin() const
    {
        if (isEmpty())
        {
            std::cerr << "Hata: Kuyruk boş, baş elemanı yok!" << std::endl;
            return front->data;
        }
        return front->data;
    }
    T &end() const
    {
        if (isEmpty())
        {
            std::cerr << "Hata: Kuyruk boş, son elemanı yok!" << std::endl;
            return rear->data;
        }
        return rear->data;
    }

    int getSize() const
    {
        return size;
    }
    void print()
    {
        Node<T> *temp = front;
        while (temp != nullptr)
        {
            std::cout << temp->data.ToString() << std::endl;
            temp = temp->next;
        }
        std::cout << std::endl;
    }
    bool operator!=(const Kuyruk<T> &other) const
    {
        // İki kuyruğun boyutları farklıysa, kesinlikle farklıdırlar
        if (getSize() != other.getSize())
        {
            return true;
        }

        // Kuyrukların elemanlarını karşılaştırma
        Node<T> *current1 = front;
        Node<T> *current2 = other.front;
        while (current1 != nullptr && current2 != nullptr)
        {
            if (current1->data != current2->data)
            {
                return true;
            }
            current1 = current1->next;
            current2 = current2->next;
        }

        // Kuyrukların içerikleri aynıysa, aynıdırlar
        return false;
    }
    
};
class CalmaListesi
{
public:
    Kuyruk<Sarki> sarkilar;
    std::string listAdi;
    int sarkiSayisi;
    int id;

    CalmaListesi() : sarkiSayisi(0) {}
    CalmaListesi(std::string const ad) : listAdi(ad), sarkiSayisi(0) {}
    operator std::string() const
    {
        return id + "," + listAdi;
    }

    friend std::ostream &operator<<(std::ostream &os, const CalmaListesi &liste)
    {
        os << liste.id + "," + liste.listAdi;
        return os;
    }
    bool operator==(const CalmaListesi &other) const
    {
        return ((id == other.id));
    }
    std::string ToString()
    {
        return id + "," + listAdi;
    }
};

template <typename T>
class Node
{
public:
    T data;
    Node *next;

    Node(const T &data) : data(data), next(nullptr) {}

    bool operator!=(const Node<T> &other) const
    {
        return data != other.data;
    }
};



template <typename T>
class Vector
{
private:
    T *array;
    int capacity;
    int size;

public:
    Vector() : array(nullptr), capacity(0), size(0) {}

    Vector(int initialCapacity) : capacity(initialCapacity), size(0)
    {
        array = new T[capacity];
    }

    ~Vector()
    {
        delete[] array;
    }

    void pushBack(const T &element)
    {
        if (size >= capacity)
        {

            int newCapacity = (capacity == 0) ? 1 : capacity * 2;
            T *tempArray = new T[newCapacity];

            for (int i = 0; i < size; ++i)
            {
                tempArray[i] = array[i];
            }

            delete[] array;
            array = tempArray;
            capacity = newCapacity;
        }

        array[size++] = element;
    }

    T &operator[](int index)
    {
        if (index >= size)
        {
            throw std::out_of_range("Index out of range!");
        }
        return array[index];
    }

    int getSize() const
    {
        return size;
    }
};

template <typename T>
struct NodeS
{
    T data;
    NodeS *next;

    NodeS(const T &data) : data(data), next(nullptr) {}
};

template <typename T>
class Stack
{
private:
    NodeS<T> *top;
    int size;

public:
    Stack() : top(nullptr), size(0) {}

    ~Stack()
    {
        while (!isEmpty())
        {
            pop();
        }
    }

    bool isEmpty() const
    {
        return size == 0;
    }

    void push(const T &data)
    {
        NodeS<T> *newNode = new NodeS<T>(data);
        newNode->next = top;
        top = newNode;
        size++;
    }

    void pop()
    {
        if (isEmpty())
        {
            std::cerr << "Hata: Yığın boş, çıkarma işlemi yapılamaz!" << std::endl;
            return;
        }
        NodeS<T> *temp = top;
        top = top->next;
        delete temp;
        size--;
    }

    T &Top() const
    {
        if (isEmpty())
        {
            throw std::out_of_range("Hata: Yığın boş, en üstte eleman yok!");
        }
        return top->data;
    }

    int getSize() const
    {
        return size;
    }
};

Kuyruk<Sarki> tumSarkilar;
Kuyruk<CalmaListesi> calmaListeleri;
Kuyruk<Sarki> favoriSarkilar;


void readDataAndEnqueue(Kuyruk<Sarki> &queue, const std::string &filename);
void calmaListesiOlustur();
void calmaListesiGoster();
void calmaListesindenOynat();
void favoriSarkilariBelirle();
void favoriSarkilariGoster();

int main()
{
    srand(time(0));
    readDataAndEnqueue(tumSarkilar, "sarkilar.txt");

    std::cout << "Tum sarkilar:" << std::endl;
    tumSarkilar.print();

    while (true)
    {
        std::cout << "1. Calma Listesi Olustur" << std::endl;
        std::cout << "2. Calma Listesini Goster" << std::endl;
        std::cout << "3. Calma Listesini Oynat" << std::endl;
        std::cout << "4. Favori Sarkilari Belirle" << std::endl;
        std::cout << "5. Favori Sarkilari Goster" << std::endl;
        std::cout << "-1 Cik" << std::endl;
        int secim;
        std::cout << "Secim: ";
        std::cin >> secim;
        if (secim == -1)
        {
            break;
        }
        if (secim == 1)
        {
            calmaListesiOlustur();
        }
        else if (secim == 2)
        {
            calmaListesiGoster();
        }
        else if (secim == 3)
        {
            calmaListesindenOynat();
        }
        else if (secim == 4)
        {
            favoriSarkilariBelirle();
        }
        else if (secim == 5)
        {
            favoriSarkilariGoster();
        }
        else 
            std::cout << "Yanlis girdiniz. Tekrar Deneyiniz."<<std::endl;
    }

    return 0;
}

void readDataAndEnqueue(Kuyruk<Sarki> &queue, const std::string &filename)
{
    std::ifstream file(filename, std::ios::in);
    if (!file.is_open())
    {
        std::cerr << "Hata: Dosya açılamadı!" << std::endl;
        return;
    }

    std::string line;
    int n = 0;
    while (std::getline(file, line))
    {
        if (n != 0) // İlk satır başlık olduğu için atlanabilir
        {
            std::istringstream iss(line);
            std::string order, song, singer;

            if (std::getline(iss, order, ',') && std::getline(iss, song, ',') && std::getline(iss, singer))
            {
                Sarki sarki(order, song, singer);
                queue.enqueue(sarki);
            }
            else
            {
                std::cerr << "Hata: Dosya biçimi yanlış!" << std::endl;
                break;
            }
        }
        n++;
    }

    file.close();
}

void calmaListesiOlustur()
{
    std::string ad;
    std::cout << "Calma listesi adi giriniz: ";
    std::cin >> ad;
    CalmaListesi yeniListe(ad);
    while (true)
    {
        int secim;
        std::cout << "Eklemek istediginiz sarkilarin id'lerini giriniz. Cikis icin -1 giriniz: " << std::endl;
        std::cin >> secim;
        if (secim == -1)
        {
            break;
        }
        else
        {
            Sarki gecici = tumSarkilar.begin();
            Sarki geciciSarki;
            Node<Sarki> *geciciNode = tumSarkilar.front;
            while (geciciNode != nullptr)
            {
                if (geciciNode->data.sarkiID == std::to_string(secim))
                {
                    // geciciSarki.sarkiAdi = geciciNode->data.sarkiAdi;
                    // geciciSarki.sarkiciAdi = geciciNode->data.sarkiciAdi;
                    // geciciSarki.dinlenmeSayisi = geciciNode->data.dinlenmeSayisi;
                    // geciciSarki.sarkiID = std::to_string(yeniListe.sarkiSayisi+1);
                    // yeniListe.sarkilar.enqueue(geciciSarki);
                    yeniListe.sarkilar.enqueue(geciciNode->data);

                    yeniListe.sarkiSayisi++;
                }
                geciciNode = geciciNode->next;
            }

        }
    }
    yeniListe.id = calmaListeleri.getSize()+1;
    calmaListeleri.enqueue(yeniListe);
}

void calmaListesiGoster()
{
    Node<CalmaListesi> *node= calmaListeleri.front;
    while(node!= nullptr)
    {
        std::cout<<node->data.id<<" "<<node->data.listAdi<<std::endl;
        node = node->next;
    }
    std::cout<<"Sarkilari Gostermek icin Calma Listesinin numarasini cikmak icin -1 giriniz: ";
    int secim;
    std::cin>>secim;
    if(secim==-1)
        return;
    else if (secim>calmaListeleri.getSize())
        return;
    else    
    {
        Node<CalmaListesi> *liste = calmaListeleri.front;
        while(liste != nullptr)
        {
            if(liste->data.id == secim)
                break;

            liste = liste->next; 
        }

        Node<Sarki> *list = liste->data.sarkilar.front;
        while(list != nullptr)
        {
            std::cout<<list->data.sarkiID<<" "<<list->data.sarkiAdi<<" "<<list->data.sarkiciAdi<<std::endl;
            list = list->next;
        }
    }
    std::cout<<std::endl;

}

void calmaListesindenOynat()
{
    Node<CalmaListesi> *node= calmaListeleri.front;
    while(node!= nullptr)
    {
        std::cout<<node->data.id<<" "<<node->data.listAdi<<std::endl;
        node = node->next;
    }
    std::cout << "Calma listesi seciniz (Cikis : -1) :";
    int secim;
    std::cin >> secim;
    if (secim == -1)
    {
        return;
    }
    else
    {
        Node<CalmaListesi> *liste = calmaListeleri.front;
        while (liste != nullptr)
        {
            if (liste->data.id == secim)
            {
                liste->data.sarkilar.print();
                break;
            }
            liste = liste->next;
        }
        std::cout << "Calma Listesi Oynatiliyor." << std::endl;

        Node<Sarki> *sarki = liste->data.sarkilar.front;
        Node<Sarki> *gecici = tumSarkilar.front;
        while (sarki != nullptr)
        {
            while (gecici != nullptr)
            {
                if (sarki->data == gecici->data)
                {
                    break;
                }
                gecici = gecici->next;
            }
            gecici->data.dinlenmeSayisi++;
            gecici->data.oynatmaSuresi += rand() % 100 + 1;
            sarki->data = gecici->data;
            std::cout<< sarki->data.sarkiAdi <<" "<<sarki->data.sarkiciAdi<<" sarkisi " << sarki->data.oynatmaSuresi <<" saniye sureyle oynatildi."<<std::endl;
            sarki = sarki->next;
        }

        std::cout<<"Calma Listesi Oynatildi."<<std::endl;
    }
}

void favoriSarkilariBelirle()
{
    Node<Sarki> *sarki = tumSarkilar.front;
    Sarki sarkilar[tumSarkilar.getSize()];
    for (int i = 0; i < tumSarkilar.getSize(); i++)
    {
        if (sarki->data.dinlenmeSayisi <= 0)
            sarki->data.dinlenmeSurePuani = 0;
        else if (sarki->data.dinlenmeSayisi < 100)
            sarki->data.dinlenmeSurePuani = 1;
        else if (sarki->data.dinlenmeSayisi >= 100 && sarki->data.dinlenmeSayisi < 500)
            sarki->data.dinlenmeSurePuani = 2;
        else if (sarki->data.dinlenmeSayisi >= 500 && sarki->data.dinlenmeSayisi < 1000)
            sarki->data.dinlenmeSurePuani = 3;
        else if (sarki->data.dinlenmeSayisi >= 1000 && sarki->data.dinlenmeSayisi < 5000)
            sarki->data.dinlenmeSurePuani = 4;
        else if (sarki->data.dinlenmeSayisi >= 5000 && sarki->data.dinlenmeSayisi < 10000)
            sarki->data.dinlenmeSurePuani = 5;
        else if (sarki->data.dinlenmeSayisi >= 10000)
            sarki->data.dinlenmeSurePuani = 6;

        sarkilar[i] = sarki->data;
        sarki = sarki->next;
    }
    for (int i = 0; i < tumSarkilar.getSize(); i++)
    {
        for (int j = 0; j < tumSarkilar.getSize(); j++)
        {
            if (((sarkilar[i].dinlenmeSayisi>6 ? 6:sarkilar[i].dinlenmeSayisi) + sarkilar[i].dinlenmeSurePuani) > ((sarkilar[j].dinlenmeSayisi>6 ? 6:sarkilar[j].dinlenmeSayisi) + sarkilar[j].dinlenmeSurePuani))
            {
                Sarki temp = sarkilar[i];
                sarkilar[i] = sarkilar[j];
                sarkilar[j] = temp;
            }
        }
    }

    for (int i = 0; i<tumSarkilar.getSize(); i++)
    {
        favoriSarkilar.enqueue(sarkilar[i]);
    }
}

void favoriSarkilariGoster()
{
    Node<Sarki> *sarki = favoriSarkilar.front;
    int n = 1;
    while(n<=10)
    {
        std::cout<<n<<": "<< sarki->data.sarkiAdi <<", "<<sarki->data.sarkiciAdi<<std::endl;
        sarki = sarki->next;
        n++;
    }
}
