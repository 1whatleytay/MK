#include "PlayerNode.h"

#include <Parser.h>

PlayerNode::PlayerNode(Node *parent, Parser &parser) : Node(parent, Player) {
    if (parser.nextWord() != "player") throw Unexpected("player", parser.lastWord());

    name = parser.nextWord();
}
