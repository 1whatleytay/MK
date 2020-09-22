#pragma once

#include <util/util.h>

#include <string>
#include <vector>
#include <functional>

class Parser;

class Node {
public:
    enum class Type {
        Code,
        Tag,
        Function,
        Command,
        Parameter,
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
    std::vector<std::shared_ptr<Node>> children;

    virtual void verify();
    virtual std::string getSource();
    Node *search(const std::function<bool(Node *node)> &query);
    Node *parentSearch(const std::function<bool(Node *node)> &query);

    explicit Node(Node *parent, Type type);
    virtual ~Node();
};

