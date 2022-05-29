class Node
{
public:
    bool end;
    vector<int> next;
    Node()
    {
        end = false;
        next.resize(26, -1);
    }
};

class Trie
{
public:
    vector<Node *> tr;
    Trie()
    {
        tr.emplace_back(new Node());
    }

    void insert(string &s)
    {
        int p = 0;
        int pos;
        for (char ch : s)
        {
            pos = ch - 'a';
            if (tr[p]->next[pos] == -1)
            {
                tr[p]->next[pos] = tr.size();
                tr.emplace_back(new Node());
            }
            p = tr[p]->next[pos];
        }

        tr[p]->end = true;
    }

    bool search(string &s, int i, int p)
    {
        if (i == s.length())
        {
            return tr[p]->end;
        }
        //cout << "i:" << i << "\n";
        int next;
        char ch = s[i];
        if (ch != '.')
        {
            next = tr[p]->next[ch - 'a'];
            if (next == -1)
            {
                return false;
            }
            return search(s, i + 1, next);
        }

        for (int k = 0; k < 26; k++)
        {
            next = tr[p]->next[k];
            if (next != -1 && search(s, i + 1, next))
            {
                return true;
            }
        }

        return false;
    }
};

class WordDictionary
{
public:
    /** Initialize your data structure here. */
    Trie *t = nullptr;
    WordDictionary()
    {
        t = new Trie();
    }

    /** Adds a word into the data structure. */
    void addWord(string word)
    {
        t->insert(word);
    }

    /** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
    bool search(string word)
    {
        return t->search(word, 0, 0);
    }
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */