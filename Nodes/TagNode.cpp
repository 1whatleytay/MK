#include "TagNode.h"

#include <Parser.h>

TagNode::TagNode(Node *parent, Parser &parser) : Node(parent, Tag) {
    if (parser.nextSymbol() != '#') throw UnexpectedSymbol({ '#' }, parser.lastSymbol());

    tagName = parser.nextWord();
    tagValue = parser.untilNextSymbol('\n');
}
