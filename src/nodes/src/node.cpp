#include <nodes/node.h>

void Node::verify() {
    for (Node *node : children) { node->verify(); }
}

std::string Node::getSource() {
    return "";
}

Node* Node::search(const std::function<bool(Node *node)> &query) {
    for (const auto &child : children) {
        if (query(child)) return child;
    }
    return nullptr;
}

Node* Node::parentSearch(const std::function<bool(Node *node)> &query) {
    if (!parent) return nullptr;

    for (const auto &child : parent->children) {
        if (query(child)) return child;
    }

    return parent->parentSearch(query);
}

Node::Node(Node *parent, Type type) : parent(parent), type(type) { }
Node::~Node() {
    for (const auto &child : children) delete child;
}
