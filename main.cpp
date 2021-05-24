#include <iostream>

using namespace std;

class LinkedList;

class SuffixNode
{
public:
    LinkedList *listArray;
    int index;
    SuffixNode(LinkedList* l)
    {
        listArray = l;
        index = -1;
    };
    ~SuffixNode() {};
};

class LinkedListNode
{
public:
    char data;
    SuffixNode *cild;
    LinkedListNode *next;
    LinkedListNode()
    {
        next = NULL;
    };
    LinkedListNode(char c, SuffixNode *n)
    {
        cild = n;
        next = NULL;
        data = c;
    };
    ~LinkedListNode() {};
};

class LinkedList
{
public:
    LinkedList()
    {
        root = NULL;
    };
    ~LinkedList() {};
    SuffixNode* insertNodeList(char c, SuffixNode *n)
    {
        if(root == NULL)
        {
            root = new LinkedListNode(c,n);
            return n;
        }
        else
        {
            LinkedListNode *cur = root;
            LinkedListNode *prev = NULL;
            while(cur != NULL)
            {
                prev = cur;
                if(cur->data == c)
                    return cur->cild;
                cur = cur->next;
            }
            prev->next = new LinkedListNode(c,n);
            return prev->next->cild;
        }
    };
    SuffixNode* Search(char c)
    {
        LinkedListNode *cur = root;
        while(cur != NULL)
        {
            if(cur->data == c)
                return cur->cild;
            cur = cur->next;
        }
        return NULL;
    };
    void print()
    {
        LinkedListNode *cur = root;
        while(cur != NULL)
        {
            if(cur->cild->index != -1)
                cout<<cur->cild->index<<" ";
            else
                cur->cild->listArray->print();
            cur = cur->next;
        }
    };
private:
    LinkedListNode *root;
};

class SuffixTrie
{
public:
    SuffixTrie(char data[])
    {
        root = new SuffixNode(new LinkedList());
        insertNode(data);
    };
    ~SuffixTrie() {};
    void insertNode(char data[])
    {
        SuffixNode * cur;
        for(int i = 0; data[i] != '\0'; i++)
        {
            cur = root;
            for(int j = i; data[j] != '\0'; j++)
                cur = cur->listArray->insertNodeList(data[j],new SuffixNode(new LinkedList()));
            cur->index = i;
        }
    };
    void Search(char sub[])
    {
        SuffixNode * cur = root;
        for(int i = 0; sub[i] != '\0'; i++)
        {
            cur = cur->listArray->Search(sub[i]);
            if(cur == NULL)
                cout<<"Does not contain this suffix"<<endl;
        }
        cur->listArray->print();
        cout<<endl;
    };
private:
    SuffixNode *root;
};

int main()
{
    // Construct a suffix trie containing all suffixes of "bananabanaba$"

    //            0123456789012bananabanaba
    SuffixTrie t("bananabanaba$");

    t.Search("ana"); // Prints: 1 3 7
    t.Search("naba"); // Prints: 4 8

    return 0;
}
