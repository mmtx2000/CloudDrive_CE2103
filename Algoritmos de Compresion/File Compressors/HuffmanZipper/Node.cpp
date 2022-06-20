

#include "Node.h"
/**
 *
 * @param character
 * @param frequency
 */
Node::Node(char character, int frequency) {

    this->left = this->right = nullptr;
    this->character = character;
    this->frequency = frequency;

}
/**
 *
 * @return
 */
int Node::getFrequency() const {
    return frequency;
}
/**
 *
 * @param left
 */
void Node::setLeft(Node *left) {
    Node::left = left;
}
/**
 *
 * @param right
 */
void Node::setRight(Node *right) {
    Node::right = right;
}
/**
 *
 * @return
 */
Node *Node::getLeft() const {
    return left;
}
/**
 *
 * @return
 */
char Node::getCharacter() const {
    return character;
}
/**
 *
 * @return
 */
Node *Node::getRight() const {
    return right;
}
/**
 *
 * @param character
 */
Node::Node(char character) {
    this->character=character;
    this->left = this->right = nullptr;

}
