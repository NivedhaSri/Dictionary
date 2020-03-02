#include <bits/stdc++.h>
#include<fstream>
#include<stdlib.h>
#include<string.h>

using namespace std;

const int ALPHABET_SIZE = 26;

#define ALPHABET_SIZE (26)

#define CHAR_TO_INDEX(c) ((int)c - (int)'a')
// trie node
struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];

    // isEndOfWord is true if the node represents
    // end of a word
    bool isEndOfWord;
};

// Returns new trie node (initialized to NULLs)
struct TrieNode *getNode(void)
{
    struct TrieNode *pNode =  new TrieNode;

    pNode->isEndOfWord = false;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = NULL;

    return pNode;
}

// If not present, inserts key into trie
// If the key is prefix of trie node, just
// marks leaf node
void insert(struct TrieNode *root, string key)
{
    struct TrieNode *pCrawl = root;

    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();

                pCrawl = pCrawl->children[index];
    }

    // mark last node as leaf
    pCrawl->isEndOfWord = true;
}

// Returns true if key presents in trie, else
// false
bool search(struct TrieNode *root, string key)
{
    struct TrieNode *pCrawl = root;

    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!pCrawl->children[index])
            return false;

        pCrawl = pCrawl->children[index];
    }

    return (pCrawl != NULL && pCrawl->isEndOfWord);
}
bool isLastNode(struct TrieNode* root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return 0;
    return 1;
}
void suggestionsRec(struct TrieNode* root, string currPrefix)
{
    // found a string in Trie with the given prefix
    if (root->isEndOfWord)
    {
        cout << currPrefix;
        cout << endl;
    }

    // All children struct node pointers are NULL
    if (isLastNode(root))
        return;

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (root->children[i])
        {
            currPrefix.push_back(97 + i);
            suggestionsRec(root->children[i], currPrefix);
        }
    }
}
int printAutoSuggestions(TrieNode* root, const string query)
{
    struct TrieNode* pCrawl = root;
    int level;
    int n = query.length();
    for (level = 0; level < n; level++)
    {
        int index = CHAR_TO_INDEX(query[level]);
        if (!pCrawl->children[index])
            return 0;

        pCrawl = pCrawl->children[index];
    }
    bool isWord = (pCrawl->isEndOfWord == true);
    bool isLast = isLastNode(pCrawl);
    if (isWord && isLast)
    {
        cout << query << endl;
        return -1;
    }
    if (!isLast)
    {
        string prefix = query;
        suggestionsRec(pCrawl, prefix);
        return 1;
    }
}
int compareFunction(string s1, string s2)
{

    int x = s1.compare(s2);

    if (x == 0)
       return 0;

}


int main()
{
    struct TrieNode *root = getNode();
    ifstream file;
    string word, t, q, filename,filename1;
     int n;                              //filename = "file.txt";
     filename = "file.txt";
    file.open(filename.c_str());
    while (file >> word)
    {

        insert(root, word);
    }
    do{
    cout<<"\n\tDICTIONARY\n1.Display\n2.Search\n3.Exit";
    cout<<"\nEnter your Choice:";
    cin>>n;
 if(n==1)
    {
        cout<<"\nenter the words to be displayed:";
        cin>>q;
        int comp = printAutoSuggestions(root, q);
    }
     if(n==2)
     {
       int m;
             filename1 = "data.txt";
            fstream file1;
             file1.open(filename1.c_str());
            cout<<"\nenter the word to be searched:";
            cin>>t;
              while(!file1.eof())
     {
          file1>>word;
     m=compareFunction(word,t);
        if (m==0)
        {
                getline(file1,word,'\n');
            cout<<word<<"\n";
        }
     }
     file.close();
            search(root,t )? cout<<"Word is found!!!" : cout<<"Word is not found!!!";
     }
      if(n==3)
      {
            exit(1);
      }
       if(n>3)
       {
           cout<<"\nWrong Choose!!";
       }
}while(n!=3);
    return 0;
}

