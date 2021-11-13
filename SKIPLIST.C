#include<bits/stdc++.h>
#define Max_level 3
const float P = 0.5;

using namespace std;

struct skipnode
{
    int value;
    skipnode **for_arr;
    skipnode(int level, int &value)
    {
        for_arr = new skipnode * [level + 1];
        memset(for_arr, 0, sizeof(skipnode*) * (level + 1));
        this->value = value;
    }
    ~skipnode()
    {
        delete [] for_arr;
    }
};


struct skiplist
{
    skipnode *header;
    int value,level;
    skiplist()
    {
        header = new skipnode(Max_level,value);
        level = 0;
    }
    ~skiplist()
    {
        delete header;
    }
    void displayNodes();
    bool searchElement(int &);
    void deleteElement(int &);
    void insertElement(int &);
};

float frand()
{
    return (float) rand() / RAND_MAX;
}


int random_level()
{
    static bool first = true;
    if (first)
    {
        srand((unsigned)time(NULL));
        first = false;
    }
    int lvl = (int)(log(frand()) / log(1.-P));
    return lvl < Max_level ? lvl : Max_level;
}



void skiplist::insertElement(int &val)
{
    skipnode *curr = header;
    skipnode *update[Max_level+1];
    memset(update,0,sizeof(skipnode*)*(Max_level+1));

    for(int i = level;i>=0;i--)
    {
        while(curr->for_arr[i] != NULL && curr->for_arr[i]->value < val)
        {
            curr = curr->for_arr[i];
        }
        update[i]=curr;
    }
    curr = curr->for_arr[0];
    if (curr == NULL || curr->value != val)
    {
        int lvl = random_level();
        if (lvl > level)
        {
            for (int i = level + 1;i <= lvl;i++)
            {
                update[i] = header;
            }
            level = lvl;
        }
        curr = new skipnode(lvl, val);
        for (int i = 0;i <= lvl;i++)
        {
            curr->for_arr[i] = update[i]->for_arr[i];
            update[i]->for_arr[i] = curr;
        }
    }
}


 void skiplist::deleteElement(int &val)
{
    skipnode *x = header;
    skipnode *update[Max_level + 1];
    memset (update, 0, sizeof(skipnode*)*(Max_level + 1));
    for (int i = level;i >= 0;i--)
    {
        while (x->for_arr[i] != NULL && x->for_arr[i]->value < val)
        {
            x = x->for_arr[i];
        }
        update[i] = x;
    }
    x = x->for_arr[0];
    if (x->value == val)
    {
        for (int i = 0;i <= level;i++)
        {
            if (update[i]->for_arr[i] != x)
                break;
            update[i]->for_arr[i] = x->for_arr[i];
        }
        delete x;
        while (level > 0 && header->for_arr[level] == NULL)
        {
            level--;
        }
    }
}

bool skiplist::searchElement(int &s_value)
{
    skipnode *x = header;
    for (int i = level;i >= 0;i--)
    {
        while (x->for_arr[i] != NULL && x->for_arr[i]->value < s_value)
        {
            x = x->for_arr[i];
        }
    }
    x = x->for_arr[0];
    return x != NULL && x->value == s_value;
}


void skiplist::displayNodes()
{
    for (int i = 0;i <= level; i++)
    {
        	skipnode *x = header->for_arr[i];
        	cout<<"Level "<<i<<": ";
        	while (x != NULL) {
            		cout << x->value<<" ";
            		x = x->for_arr[i];
        	}
        	cout<<endl;
    }
}


int main()
{
    skiplist ss;
    int choice, n;
    cout<<"1.Insert Element"<<endl;
    cout<<"2.Delete Element"<<endl;
    cout<<"3.Search Element"<<endl;
    cout<<"4.Display List "<<endl;
    cout<<"5.Exit "<<endl;
    while (1)
    {

        cout<<"Enter your choice : ";
        cin>>choice;
        switch(choice)
        {

        case 1: cout<<"Enter the element to be inserted: ";
                cin>>n;
                ss.insertElement(n);
                break;

        case 2: cout<<"Enter the element to be deleted: ";
                cin>>n;
                if(!ss.searchElement(n))
                {
                     cout<<"Element not found"<<endl;
                     break;
                }
                ss.deleteElement(n);
                break;

        case 3:  cout<<"Enter the element to be searched: ";
                 cin>>n;
                 if(ss.searchElement(n))
                    cout<<"Element "<<n<<" is in the list"<<endl;
                 else
                    cout<<"Element not found"<<endl;
                 break;

        case 4:   cout<<"Elements in list are: "<<endl;
                  ss.displayNodes();
                  break;


        case 5:   exit(1);
                  break;

        default:
             cout<<" Invalid option"<<endl;
        }

        cout<<endl;
    }
    return 0;
}
