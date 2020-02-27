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

// Recursive function to print auto-suggestions for given
// node.
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
            // append current character to currPrefix string
            currPrefix.push_back(97 + i);

            // recur over the rest
            suggestionsRec(root->children[i], currPrefix);
        }
    }
}

// print suggestions for given query prefix.
int printAutoSuggestions(TrieNode* root, const string query)
{
    struct TrieNode* pCrawl = root;

    // Check if prefix is present and find the
    // the node (of last level) with last character
    // of given string.
    int level;
    int n = query.length();
    for (level = 0; level < n; level++)
    {
        int index = CHAR_TO_INDEX(query[level]);

        // no string in the Trie has this prefix
        if (!pCrawl->children[index])
            return 0;

        pCrawl = pCrawl->children[index];
    }

    // If prefix is present as a word.
    bool isWord = (pCrawl->isEndOfWord == true);

    // If prefix is last node of tree (has no
    // children)
    bool isLast = isLastNode(pCrawl);

    // If prefix is present as a word, but
    // there is no subtree below the last
    // matching node.
    if (isWord && isLast)
    {
        cout << query << endl;
        return -1;
    }

    // If there are are nodes below last
    // matching character.
    if (!isLast)
    {
        string prefix = query;
        suggestionsRec(pCrawl, prefix);
        return 1;
    }
}
int compareFunction(string s1, string s2)
{
    // comparing both using inbuilt function
    int x = s1.compare(s2);

    if (x = 0)
       return 0;

}

// Driver
int main()
{
    // Input keys (use only 'a' through 'z'
    // and lower case)

    //int n = sizeof(keys)/sizeof(keys[0]);

    struct TrieNode *root = getNode();
    ifstream file;
    string word, t, q, filename,filename1;
    int n;

    // filename of the file
    filename = "file.txt";
   // filename1="Book1.csv";
    // opening file
    file.open(filename.c_str());

    // extracting words form the file
    while (file >> word)
    {
    // Construct trie
    //for (int i = 0; i < n; i++)
        //cout<<word<<endl;
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
        file1.close();
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
