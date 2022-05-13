#include <iostream>
using namespace std;


template<class T>
struct Node
{
    T data;
    Node<T>* next;

    Node()
    {
        next = nullptr;
    }
    explicit Node(T item, Node<T>* ptr = nullptr)
    {
        data = item;
        next = ptr;
    }
};


template<class T>
class LinkList
{
public:
    LinkList();
    ~LinkList();
    void clear();
    LinkList<T>& operator=(const LinkList<T>& item);  //赋值运算符重载
    LinkList(const LinkList<T>& item);  //拷贝构造函数
    int size()const;
    bool empty()const;  //判表空
    void traverse();  //遍历表
    void replace(int position, const T& temp);  //替换指定位置的元素
    void remove(int position);  //删除指定位置的元素
    void insert(int position, const T& temp);  //在指定位置插入元素
    T get(int position);  //获取指定位置元素的值

protected:
    int count;
    Node<T>* head;
    Node<T>* back;
    Node<T>* set_position(int position)const;
};


template<class T>
LinkList<T>::LinkList()  //构造函数
{
    count = 0;
    head = back = nullptr;
}


template<class T>
LinkList<T>::~LinkList()  //析构函数
{
    Node<T>* p = head;
    while (p != nullptr)
    {
        head = head->next;
        delete p;
        p = head;
    }
    back = nullptr;
    count = 0;
}


template<class T>
void LinkList<T>::clear() {
    Node<T>* p = head;
    while (p != nullptr)
    {
        head = head->next;
        delete p;
        p = head;
    }
    back = nullptr;
    count = 0;
}


template <class T>
LinkList<T>::LinkList(const LinkList<T>& item)  //拷贝构造函数
{
    Node<T>* original_node = item.head;
    if (original_node == nullptr)
    {
        head = nullptr;
    }
    else
    {
        head = back = new Node<T>(original_node->data);
        while (original_node->next != nullptr)
        {
            original_node = original_node->next;
            back->next = new Node<T>(original_node->data);
            back = back->next;
        }
    }
    count = item.count;
}


template <class T>
LinkList<T>& LinkList<T>::operator=(const LinkList<T>& item)  //重载赋值运算符
{
    this->clear();
    if (nullptr == item.front) {
        head = back = nullptr;
        count = 0;
    }
    else {
        Node<T>* original_front = item.front;
        head = back = new Node<T>(original_front->entry);
        while (original_front->next != nullptr) {
            original_front = original_front->next;
            back->next = new Node<T>(original_front->entry);
            back = back->next;
        }
        count = item.count;
    }
    return *this;
}



template<class T>
int LinkList<T>::size()const
{
    return count;
}


template<class T>
bool LinkList<T>::empty()const
{
    return count == 0;
}


template<class T>
Node<T>* LinkList<T>::set_position(int position)const  //找到指定位置的元素
{
    Node<T>* target = head;
    for(int i = 0; i < position; ++i){
        target = target ->next;
    }
    return target;
}


template<class T>
void LinkList<T>::insert(int position, const T& temp)  //在指定位置插入元素
{

    auto following = new Node<T>;
    auto previous = new Node<T>;
    if (position < 0 || position > count)
    {
        throw"Range Error";
    }
    if (position > 0)
    {
        previous = set_position(position - 1);
        following = previous->next;
    }
    else  //position = 0
    {
        following = head;
    }
    auto new_node = new Node<T>(temp, following);
    if (new_node == nullptr)
    {
        throw"Overflow";
    }
    if (position == 0)
    {
        head = new_node;
        count++;
    }
    else
    {
        previous->next = new_node;
        count++;
    }
}


template<class T>
void LinkList<T>::remove(int position)  //删除指定位置的元素
{
    if (empty())
    {
        throw"Overflow";
    }
    if (position < 0 || position > count - 1)
    {
        throw"Range Error";
    }
    if (position > 0)
    {
        Node<T>* previous = set_position(position - 1);
        Node<T>* temp = previous->next;
        previous->next = temp->next;
        temp = nullptr;
        delete temp;
        count--;
    }
    else  //position = 0
    {
        if (count == 1){
            Node<T>* temp = head;
            head = back = nullptr;
            temp = nullptr;
            delete temp;
        }
        else{
            Node<T>* temp = head;
            head = head->next;
            temp = nullptr;
            delete temp;
        }
        count--;
    }
}


template<class T>
void LinkList<T>::replace(int position, const T& temp)  //替换指定位置的元素
{
    if (empty())
    {
        throw"Overflow";
    }
    if (position < 0 || position > count - 1)
    {
        throw"Range Error";
    }
    else
    {
        Node<T>* item = set_position(position);
        item->data = temp;
    }
}


template<class T>
void LinkList<T>::traverse()  //遍历链表
{
    Node<T>* ptr = head;
    while (ptr != nullptr)
    {
        cout << ptr->data << " ";
        ptr = ptr->next;
    }
    cout << endl;
}


template<class T>
T LinkList<T>::get(int position) {
    if (position < 0 || position > count - 1){
        throw"Range Error";
    }
    else{
        Node<T>* temp = set_position(position);
        return temp->data;
    }
}


int main()
{
    LinkList<int>temp;
    for (int i = 0; i < 10; i++)
    {
        temp.insert(0, i);
    }
    cout << temp.size() << endl;
    temp.traverse();
    temp.remove(1);
    cout << temp.size() << endl;
    temp.replace(1, 100);
    temp.traverse();


    system("pause");
    return 0;
}
