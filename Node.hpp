//
//  Node.hpp
//  Terminal
//
//  Created by Gábor Horváth on 2019. 10. 28..
//  Copyright © 2019. Gábor Horváth. All rights reserved.
//

#ifndef Node_hpp
#define Node_hpp

#include <stdio.h>
#include <string>

/**
 * Szülő class a fajlok és mappák kezeléséhez
*/
class Node {
private:
    std::string name;
    Node* parent;
public:
    /**
     * @param name beállítja a node nevét
     * @param parent beállítja a node szülő mappáját.
    */
    Node(std::string name, Node* parent);
    /**
     * Getter függvény a szülő mappa mutatója számára.
    */
    Node* getParent() const;
    /**
     * Getter függvény a Node nevéhez.
    */
    std::string getName() const;
    /**
     * Csak a polifmorfizmus miatt kell.
    */
    virtual ~Node() = default; //csak a polimorfizmus végett
    
};

#endif /* Node_hpp */
