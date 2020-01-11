#include <iostream>
#include <string>
#include <stack>

using namespace std;

/* 汉诺塔 */
class Solution_Hanoi{
public:
    void Move(int n, string a, string b, string c){
        if (n == 1){
            i += 1;
            cout << "移动第" << i << "次：" << a <<" -> " << c << endl;
        }
        else{
            Move(n - 1, a, c, b);
            Move(1, a, b, c);
            Move(n - 1, b, a, c);
        }       
    }
     
private:
    int i = 0;
};


/* 单链表实现栈 */
template <class T> class LinkStack
{
private:
    struct Node{
        T data;
        Node *next;
    };
    Node *head;
    // Node *p;
    int length;

public:
    LinkStack(){
        head = NULL;
        length = 0;
    }
    void push(T n){
        Node *q = new Node;
        q->data = n;
        if (head == NULL){
            q->next = head; // 往尾结点加下一个
            head = q; //新栈头
        }
        else{
            q->next = head;
            q->data = n;
        }
        length++;
    }
    int pop(){
        if (length <= 0 ){
            abort();
        }
        Node *q; //用来指向pop的数据的指针
        q = head;
        T data = head->data;

        head = head->next;
        length--;
        return data;
    }
    int size(){
        return length;
    }
    T StackTop(){
        return head->data;
    }
    bool isEmpty(){
        if (length == 0){
            return true;
        }
        else{
            return false;
        }
    }
    void clear(){
        while (length > 0){
            pop();
        }
    }
};

/* 车辆重排 */
class Coach{
public:
    // 车辆重排
    // p：入轨序列；
    // l: 序列长度
    // k：缓冲轨道数量；
    // return 重排是否成功
    bool RailRoad(int p[], int l, int k)
    {
        stack<int> *h = new stack<int> [k];

        int nowOut = 1; //下一次要输出的车厢号
        int minH = __INT_MAX__; //缓冲轨道中编号最小的车厢
        int minS = -1; //minH号车厢对应的缓冲轨道
        m_Nk = k;

        for (int i = 0; i < l; i++)
        {
            if (p[i] == nowOut)
            {
                cout << "移动车厢：" << p[i] << "从入轨到出轨；" << endl;
                nowOut++;
                //序列入轨后，缓冲轨道的车厢才有机会入轨
                while (minH == nowOut)
                {
                    Output(minH, minS, h);
                    nowOut++;
                }
            }
            else
            {
                //将p[i]送入某个缓冲轨道
                if (Input(p[i], minH, minS, h) == false)
                {
                    return false;
                }
            }
            
        }
        return true;
    }
    
    void Output(int &minH, int &minS, stack<int> *h)
    {
        h[minS].pop();
        cout << "移动车厢：" << minH <<  "从缓冲轨道" << minS << "到出轨；" << endl;
        // 搜索新的minH和minS
        minH = __INT_MAX__;
        minS = -1;
        for (int i=0; i < m_Nk; i++)
        {
            if (h[i].empty() == false && minH > h[i].top())
            {
                minH = h[i].top();
                minS = i;
            }
        }
    }

    //在一个缓冲轨道放入车厢c
    bool Input(int c, int &minH, int &minS, stack<int> *h)
    {
        int bestTrack = -1; //目前最优的可以放入车厢c的缓冲轨道；
        int bestTop = __INT_MAX__; //最优缓冲轨道的头辆车厢
        for (int i = 0; i < m_Nk; i++)
        {
            if (h[i].empty() == false)
            {
                int x = h[i].top();
                if (c < x && x < bestTop)
                {
                    bestTop = x;
                    bestTrack = i;
                }
            }
            else //如果缓冲轨道是空的，直接放进去
            {
                if (bestTrack == -1)
                {
                    bestTrack = i;
                    break;
                }
            }
        }
        if (bestTrack == -1)
        {
            return false;
        }
        else
        {
            h[bestTrack].push(c);
            cout << "移动车厢：" << c << "从入轨到缓冲轨道；" << bestTrack << endl;
            if (c < minH)
            {
                minH = c;
                minS = bestTrack;
            }
            return true;
        }
    }
private:
    int m_Nk;
};


int main(){
    string a = "a", b = "b", c = "c";
    Solution_Hanoi hanoi;
    hanoi.Move(3, a, b, c);

    cout <<endl << "---------------" << endl;

    Coach coa;
    int *p = new int [20]{3, 6, 9, 2, 4, 7, 1, 8, 5};
    int k = 1;
    bool result = coa.RailRoad(p, 9, k);
    while (result == false)
    {
        cout << "需要更多的缓冲轨道，请输入需要添加的数量：" << endl;
        int ad;
        cin >> ad;
        k = k + ad;
        result = coa.RailRoad(p, 9, k);
    }
    // system("pause");
    return 0;
}