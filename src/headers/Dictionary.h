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
        if (key == 2 || value->id == 2)
            std::cout << "Inserting Value " << value->id << " With Key " << key << std::endl;
        if (list->size() == 0)
        {

            List<Node> nodeList;
            nodeList.insertNode(value);
            Pair<int, List<Node>> *pair = new Pair<int, List<Node>>;
            pair->makePair(key, nodeList);

            list->insertNode(pair);
        }
        else
        {
            Pair<int, List<Node>> *ExistingPair = list->search(key);
            if (ExistingPair == NULL)
            {
                List<Node> nodeList;
                nodeList.insertNode(value);
                Pair<int, List<Node>> *pair = new Pair<int, List<Node>>;
                pair->makePair(key, nodeList);
                list->insertNode(pair);
            }
            else
            {
                ExistingPair->getValue().insertNode(value);
            }
        }
    }

    void printDictionary()
    {
        for (int i = 0; i < list->size(); ++i)
        {
            Pair<int, List<Node>> *pair = list->getNode(i);
            std::cout << "Group " << i << ": ";
            std::cout << pair->getKey() << ": ";
            List<Node> nodeList = pair->getValue();
            for (int j = 0; j < nodeList.size(); ++j)
            {
                Node *node = nodeList.getNode(j);
                std::cout << node->id << " ";
            }
            std::cout << std::endl;
        }
    }
};
