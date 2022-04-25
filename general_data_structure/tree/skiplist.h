#include <random>
#include <cassert>

namespace hollin{
  template<typename K, typename V>
  struct Node{
    K key;
    V value;
    Node **forward;

    Node(int level, K key, V value){
      forward = new Node*[level];
      for(int i = 0; i < level; ++i){
        forward[i] = nullptr;
      }
      this->key = key;
      this->value = value;
    }

    ~Node(){
      delete []forward;
    }
  };

  template<typename K, typename V, class compare=std::less<K>>
  class SkipList{
    private:
      int level;
      int maxLevel;
      double P;
      Node<K, V> *header;

      int randomLevel(){
        int lvl = 1;
        while(1.0 * rand() / RAND_MAX < P && lvl < maxLevel){
          ++lvl;
        }
        return lvl;
      }

    public:
      SkipList(int maxLevel, double P): level(1), maxLevel(maxLevel), P(P), header(new Node<K, V>(maxLevel, -1, -1)){}

      V Search(K key){
        Node<K, V> *p = header;
        for(int i = level - 1; i >= 0; --i){
          // p->key < key <= p->forward[i]->key
          while(p->forward[i] != nullptr && compare()(p->forward[i]->key, key)){
            p = p->forward[i];
          }
        }
        // lowest level, original list
        return p->forward[0] != nullptr && p->forward[0]->key == key ? p->forward[0]->value : V{};
      }     

      bool Insert(K key, V value){
        Node<K, V> *update[maxLevel];
        for(int i = 0; i < maxLevel; ++i){
          update[i] = nullptr;
        }
        Node<K, V> *p = header;
        for(int i = level - 1; i >= 0; --i){
          // p->key < key <= p->forward[i]->key
          while(p->forward[i] != nullptr && compare()(p->forward[i]->key, key)){
            p = p->forward[i];
          }
          // 第i层的prev节点
          update[i] = p;
          assert(update[i] != nullptr);
        }

        if(p->forward[0] != nullptr && p->forward[0]->key == key){
          return false;
        }

        int newLevel = randomLevel();
        // 新建一个node
        Node<K, V> *x = new Node<K, V>(newLevel, key, value);
    
        // 多出来的level用header指向x
        if(level < newLevel){
          for(int i = newLevel - 1; i >= level; --i){
            header->forward[i] = x;
          }
        }

        // min(newLevel, level)十分重要，因为x的forward只有newLevel个元素
        // 自底向上修改每一层prev节点，指向x节点
        for(int i = 0; i < std::min(newLevel, level); ++i){
          x->forward[i] = update[i]->forward[i];
          update[i]->forward[i] = x;
        }

        level = std::max(newLevel, level);
        return true;
      }
      
      bool Delete(K key){
        Node<K, V> *update[maxLevel];
        for(int i = 0; i < maxLevel; ++i){
          update[i] = nullptr;
        }
        Node<K, V> *p = header;
        for(int i = level - 1; i >= 0; --i){
          while(p->forward[i] != nullptr && compare()(p->forward[i]->key, key)){
            p = p->forward[i];
          }
          update[i] = p;
          assert(update[i] != nullptr);
        }
        
        // 这里需要一个变量x！
        // 如果用p会出现update[i] == p的情况，程序crash
        Node<K, V> *x = p->forward[0];
        if(x == nullptr || x->key != key) return false;
        
        // 更新被删除节点上一个节点的指针
        for(int i = 0; i < level; ++i){
          if(update[i]->forward[i] != x) break;
          update[i]->forward[i] = x->forward[i];
        }
        
        delete x;

        // Delete可能导致level变化
        while(level > 0 && header->forward[level - 1] == nullptr){
          --level;
        }
        return true;
      }

      int Level(){
        return level;
      }

      ~SkipList(){
        delete header;
      }
  };
};
