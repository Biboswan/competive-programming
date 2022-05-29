class Trie
{
public:
    /** Initialize your data structure here. */
    unordered_map<char, Trie *> c;
    bool end;

    Trie(bool end = false)
    {
        this->end = end;
    }

    /** Inserts a word into the trie. */
    void insert(string word)
    {
        int len = word.length();
        char ch;
        Trie *it = this;
        Trie *t = nullptr;
        for (int i = 0; i < len; i++)
        {
            ch = word[i];

            if (it->c.find(ch) == it->c.end())
            {
                if (i != len - 1)
                {
                    t = new Trie();
                }
                else
                {
                    t = new Trie(true);
                }

                it->c.insert({ch, t});
                it = t;
            }
            else
            {
                it = it->c[ch];
            }
        }

        it->end = true;
    }

    /** Returns if the word is in the trie. */
    bool search(string word)
    {
        int len = word.length();
        Trie *it = this;
        char ch;

        for (int i = 0; i < len; i++)
        {
            ch = word[i];

            if (it->c.find(ch) != it->c.end())
            {
                it = it->c[ch];
            }
            else
            {
                return false;
            }
        }

        return it->end;
    }

    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix)
    {
        int len = prefix.length();
        Trie *it = this;
        char ch;

        for (int i = 0; i < len; i++)
        {
            ch = prefix[i];

            if (it->c.find(ch) != it->c.end())
            {
                it = it->c[ch];
            }
            else
            {
                return false;
            }
        }

        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */