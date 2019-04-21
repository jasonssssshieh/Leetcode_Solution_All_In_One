class tirenode{
public:
    //Words will only consist of lowercase English letters.
    tirenode(){
        children.resize(26, nullptr);
    }
    vector<tirenode*> children;
    bool isEnd = false;
};

class StreamChecker {
public:
    tirenode* root;
    string str = "";
    int maxLen = 0;
    StreamChecker(vector<string>& words) {
        root = new tirenode();
        if(!words.empty()){
            for(auto s : words){
                reverse(s.begin(), s.end());
                maxLen = max(maxLen, (int)s.size());
                auto r = root;
                for(int i = 0; i < s.size(); ++i){
                    int idx = s[i] - 'a';
                    if(r->children[idx] == nullptr){
                        r->children[idx] = new tirenode();
                    }
                    r = r->children[idx];
                }
                r->isEnd = true;
            }
        }
    }
    
    bool query(char letter) {
        if(str.size() > maxLen){
            str = str.substr(1);
        }
        auto r = root;
        str.push_back(letter);
        for(int i = str.size()-1; i >= 0; --i){
            int idx = str[i] - 'a';
            if(r->children[idx] == nullptr) return false;
            r = r->children[idx];
            if(r->isEnd) return true;
        }
        return r->isEnd;
    }
};

/**
 * Your StreamChecker object will be instantiated and called as such:
 * StreamChecker* obj = new StreamChecker(words);
 * bool param_1 = obj->query(letter);
 */
