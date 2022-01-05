
#include <iostream>
#include<string>
#include<chrono>
using namespace std;

struct Data {
    string address;
    string name;
    string list[200];
};
struct Node {
    Node* next[200];
    Node* prev;
    Node* prev_l;
    Data dt;
};
struct LinkList {
    
    Node* head = nullptr;
    Node* tail[1000]; //toi da co 10 nhanh
    void insert(string nameParent, string address) 
    {
        Node* temp = head;
        //tao Node dau tien
        if (temp == nullptr)
        {
            //
            temp = new Node;
            temp->dt.address = address;
            temp->dt.name = address;
            temp->next[0] = nullptr;
            temp->prev = nullptr;
            head = temp;
            tail[0] = temp;
            tail[1] = nullptr;    
        }
        else
        {
            int k = 0, i, j;
            while (tail[k] != nullptr)
            {
                temp = tail[k];
                while (temp->prev != nullptr || temp->dt.name == nameParent)
                {
                    if (temp->dt.name == nameParent)
                    {
                        Node* x = new Node;
                        x->dt.address = temp->dt.address + address + "/";
                        x->dt.name = address;
                        x->prev = temp;
                        x->next[0] = nullptr;

                        i = 0;
                        while (temp->next[i] != nullptr)
                        {
                            i++;
                        }
                        temp->next[i] = x;
                        temp->next[i + 1] = nullptr;
                        j = 0;
                        if (i > 0) {
                            while (tail[j] != nullptr)
                            {
                                j++;
                            }
                            tail[j] = x;
                            tail[j + 1] = nullptr;
                        }
                        else
                            tail[k] = x;

                        //
                        j = 0;
                        while (temp->dt.list[j] != "")
                        {
                            j++;
                        }
                        temp->dt.list[j] = temp->next[j]->dt.address;
                        return;
                    }
                    temp = temp->prev;
                }
                k++;
            }
        }
    }
    
    Node* find(string url, int n)
    {
        Node* temp;

        int i = 0;
        while (i < n)
        {
            temp = tail[i];
            while (temp->prev != nullptr)
            {
                if (temp->dt.address == url)
                    return temp;
                temp = temp->prev;
            }
            i++;
        }
    }
};
void RandomStringGenerator(string code[], int codeLength)
{
    string box = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefjhijklmnopqrstuvwxyz0123456789";
    int boxLength = box.length();
    for (int i = 0; i < codeLength; i++)
    {
        code[0] = code[0] + box[rand() % boxLength];
    }
}
void InPut(LinkList*& l1, string url[], int q, int w, int r)
{
    l1 = new LinkList;
    l1->insert("", "https://");
    l1->insert("https://", "utex.hcmute.edu.vn");


    string a[1];
    a[0] = "utex.hcmute.edu.vn";

    url[0] = "https://utex.hcmute.edu.vn/";
    int k = 0;
    int h = 1;
    for (int i = 0; i < q; i++)
    {
        string b[1];
        RandomStringGenerator(b, 5);
        string* c = b;

        url[h] = url[k] + *c + '/';
        h++;
        int l = h - 1;
        l1->insert(*a, *c);
        for (int i = 0; i < w; i++)
        {
            string d[1];
            RandomStringGenerator(d, 8);
            string* e = d;
            url[h] = url[l] + *d + '/';
            h++;
            int n = h - 1;
            l1->insert(*c, *e);
            for (int i = 0; i < r; i++)
            {
                string t[1];
                RandomStringGenerator(t, 8);
                string* m = t;
                url[h] = url[n] + *t + '/';
                h++;
                l1->insert(*e, *m);
            }
        }
    }
}
int main()
{
    LinkList* l1;

    string url[2000];
    int a = 1;
    while (a <= 10)
    {
        l1 = new LinkList;
        int n = 100 * a;
        InPut(l1, url, 10, 10, a);
        double max = 0, min = 10, sum = 0;
        for (int i = 0; i < n; i++)
        {
            auto begin = std::chrono::high_resolution_clock::now();
            Node* x = l1->find(url[i], n);
            auto end = std::chrono::high_resolution_clock::now();
            auto result = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
            sum += result.count();
            if (result.count() < min)
                min = result.count();
            if (result.count() > max)
                max = result.count();
        }
        double avg = (double)sum / n;
        cout << "The number of URLs: " << n << endl;
        cout << "Max execution time: " << max * 1e-6 << endl;
        cout << "Min execution time: " << min * 1e-6 << endl;
        cout << "Average execution time: " << avg * 1e-6 << endl << endl;

        a++;
    }
    return 0;
}
