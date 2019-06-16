#ifndef MK_NODE_H
#define MK_NODE_H

#include <Util.h>

#include <functional>

class Node {
public:
    enum Type {
        Code,
        Tag,
        Function,
        Command,
        Score,
        ModifyScore,
        Execute,
        ModifyTarget,
        Method,
        Player,
        Recipe,
    };

    Node *parent;
    Type type;
    std::vector<Node*> children;

    virtual void verify();
    virtual std::string getSource();
    Node *search(const std::function<bool(Node *node)> &query);
    Node *parentSearch(const std::function<bool(Node *node)> &query);

    explicit Node(Node *parent, Type type);
    virtual ~Node();
};

#endif //MK_NODE_H
