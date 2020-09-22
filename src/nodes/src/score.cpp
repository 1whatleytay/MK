#include "ScoreNode.h"

#include <Parser.h>

std::string ScoreNode::createScore() {
    return "scoreboard objectives add " + scoreName + " " + scoreType + "\n";
}

// TODO: ScoreNode::build checks for identical scores

ScoreNode::ScoreNode(Node *parent, Parser &parser) : Node(parent, Score) {
    if (parser.nextWord() != "score") throw Unsupported("Score-less score");
    scoreName = parser.nextWord();

    if (parser.nextSymbol() == ':') {
        scoreType = parser.untilNextSymbol(';');
    } else {
        scoreType = "dummy";
    }
}
