#include <iostream>
#include <queue>
#include <string>
#include <windows.h>  // for vs

using namespace std;

/* ����ʵ��ѭ��˳����� */
template <typename T>
class CSeqQueue
{
public:
    CSeqQueue(int s = 20);
    ~CSeqQueue();
    bool isEmpty();
    int size();
    bool push(T t);
    T pop();
    T front();
    int maxsize();

private:
    int begin;
    int end;
    int MaxSize;
    int Length;
    T* queue;
};

template<typename T>
CSeqQueue<T>::CSeqQueue(int s) : MaxSize(s)
{
    begin = 0;
    end = 0;
    Length = 0;
    queue = new T[MaxSize];
}
template<typename T>
CSeqQueue<T>::~CSeqQueue()
{
    delete[] queue;
}
template<typename T>
bool CSeqQueue<T>::push(T n)
{
    if (Length == MaxSize)
    {
        throw "�����������������!";
        return false;
    }
    queue[end] = n;
    end = (end + 1) % MaxSize;
    Length++;
}
template<typename T>
T CSeqQueue<T>::pop()
{
    if (Length == 0)
    {
        throw "����Ϊ�գ����ܳ��ӣ�";
    }
    T data = queue[begin];
    begin = (begin + 1) % MaxSize;
    Length--;
    return data;
}
template<typename T>
T CSeqQueue<T>::front()
{
    if (Length == 0)
    {
        throw "����Ϊ�գ����ܵõ�����Ԫ�أ�";
    }
    return queue[begin];
}
template<typename T>
bool CSeqQueue<T>::isEmpty()
{
    return Length == 0;
}
template<typename T>
int CSeqQueue<T>::size()
{
    return Length ;
}
template<typename T>
int CSeqQueue<T>::maxsize()
{
    return MaxSize;
}

/* ģ�����з��� */
// ʹ��˳��洢�ṹ�洢���ж���
class CSeqBankQueue: public CSeqQueue<int>
{
public:
    CSeqBankQueue(int size) : Size(size)
    {
        Callnumber = 0;
    }
    int GetCallnumber()
    {
        if (isEmpty() && Callnumber == 0)
            Callnumber = 1;
        else
            Callnumber++;
        return Callnumber;
    }

private:
    int Size;
    int Callnumber;
};
// ���񴰿�
class ServiceWindow
{
public:
    CSeqBankQueue *BankQ = new CSeqBankQueue(20);
    void Serivice()
    {
        while (true)
        {
            Sleep(6000); // for vs
                if (!BankQ->isEmpty())
                {
                    cout << "��" << BankQ->front() << "�ŵ�" << 1 << "�Ŵ��ڣ�" << endl;
                }
        }
    }

};

class BankQueueApp
{
public:
    void main()
    {
        int count;
        cout << "��������п�����������" << endl;
        cin >> count;
        bankQueue = new CSeqBankQueue(count);
        ServiceWindow* serviceWindows = new ServiceWindow;
        serviceWindows->BankQ = bankQueue;
        while (true)
        {
            cout << "������������ȡ���룺" << endl;
            int num;
            cin >> num;
            if (bankQueue != NULL && bankQueue->size() < bankQueue->maxsize())
            {
                int callnumber = bankQueue->GetCallnumber();
                cout << "���ĺ����ǣ�" << callnumber << "����ǰ����" << bankQueue->size() << "λ����ȴ�" << endl;
                bankQueue->push(callnumber);
            }
            else
            {
                cout << "����ҵ��æ�����Ժ�������" << endl;
            }
        }
    }
private:
    CSeqBankQueue* bankQueue;
};

int main()
{
    BankQueueApp bankQueueApp;
    bankQueueApp.main();

    system("pause");
    return 0;
}