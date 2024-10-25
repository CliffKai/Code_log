#include<unordered_map>
#include<vector>

using namespace std;

class RandomizedSet {
private:
    unordered_map<int,bool> hash;
    vector<int> Arr;
public:
    RandomizedSet() {

    }
    
    bool insert(int val) {
        if(hash[val] == true)
        {
            return false;
        }
        hash[val] = true;
        Arr.push_back(val);
        return true;
    }
    
    bool remove(int val) {
        if(hash[val] == false)
        {
            return false;
        }
        Arr.erase(std::remove(Arr.begin(),Arr.end(),val));
        hash.erase(val);
        return true;
    }
    
    int getRandom() {
        int size = Arr.size();
        int ran = rand()%size;
        return Arr[ran];
    }
};
