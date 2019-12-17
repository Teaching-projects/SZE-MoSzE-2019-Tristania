#pragma	once

#include "Node.hpp"
#include <string>
#include <iostream>
#include <vector>
/** @brief Class a mappák leírásához */
class Dir : public Node{
private:
    /**
     * Ez tárolja a mappában lévő többi elemet
    */
    std::vector<Node*> children;
public:
    /**
     * @param name  Beállítja a mappa nevét.
     * @param parent Beállítja a mappa szülőjét.
    */
    Dir(std::string name, Dir* parent);
    /**
     * @brief Getter függvény a mappa tartalmának lekéréséhez.
     * 
     * @return Vector ami tartalmazza a gyerekeket.
    */
    std::vector<Node*> getChildren();
    /**
     * @brief Vissza ad egy gyereket a children vectorból.
     * 
     * @return Node* - Első elemet adja vissza a children vectorból.
     * @return Nullptr - Ha üres a children vector.
    */
    Node* getChild();

    /**
     * @brief Setter függvény a children vectorhoz
     * 
     * @param vector kapott vectort beállítja a class children vectorjának.
    */
    void setChildren(std::vector<Node*> vector);
    
    /**
     * @brief Egy Node pointer hozzáadása a children vectorhoz.
     * 
     * @param child Ezt a paramétert adja hozzá a mappa children vectorjához.
    */
    void addChild(Node* child);
    /**
     *  Az összes elem listázása std::cout-ra ami a children vectorban található.
    */
    void listChildren();

    /**
     * @brief Azt vizsgálja, hogy az adott mappának van-e gyereke.
     * 
     * @return true - ha a children vectorban van legalább 1 elem.
     * @return false - ha a children vector üres.
    */
    bool hasChildren();
};
