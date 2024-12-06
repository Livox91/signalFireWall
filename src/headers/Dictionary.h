#include "Constant.h"
#include "Pair.h"
class Dictionary
{

public:
    List<Pair<int, List<Node>>> *list;
    Dictionary()
    {
        list = new List<Pair<int, List<Node>>>;
    }

    void insert(int key, Node *value)
    {

        for (int i = 0; i < list->size(); ++i)
        {
            Pair<int, List<Node>> *existingPair = list->getNode(i);
            if (existingPair == nullptr)
            {
                std::cerr << "Error: Null pair encountered at index " << i << std::endl;
                continue;
            }
            if (existingPair->getKey() == key)
            {
                existingPair->getValue().insertNode(value);
                return;
            }
        }
        Pair<int, List<Node>> *newPair = new Pair<int, List<Node>>;
        if (newPair == nullptr)
        {
            std::cerr << "Error: Memory allocation for new pair failed." << std::endl;
            return;
        }
        List<Node> nodeList;
        nodeList.insertNode(value);
        newPair->makePair(key, nodeList);
        list->insertNode(newPair);
        return;
    }

    void printDictionary()
    {
        for (int i = 0; i < list->size(); ++i)
        {
            Pair<int, List<Node>> *pair = list->getNode(i);
            std::cout << pair->getKey() << " : ";
            List<Node> nodeList = pair->getValue();
            Node *temp = nodeList.getHead();
            while (temp != NULL)
            {
                std::cout << temp->id << " ";
                temp = temp->getNext();
            }
            std::cout << std::endl;
        }
    }
};
