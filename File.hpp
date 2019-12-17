#ifndef File_hpp
#define File_hpp

#include <stdio.h>
#include <string>
#include "Node.hpp"
#include "Dir.hpp"

/**
 * @brief Class a fájlok leírásához
 * @details ez a class arra való, hogy fájlokat is képesek legyünk tárolni.
*/
class File : public Node {
    std::string name;
    Dir* parent;
    std::string content;
public:
    /**
     * @brief Konstruktor a fájl classhoz.
     * 
     * @param name a fájl neve
     * @param parent a fájlt tartalmazo mappa mutatója
     * @param content a fájl tartlma
    */
    File(std::string name, Dir* parent, std::string content="");
    /**
     * Getter függvény a fájl nevéhez.
    */
    std::string getName();
    /**
     * Getter függvény a fájl szűlőmappájának mutatójához.
    */
    Dir* getParent();
    /**
     * Getter függvény a fájl tartalmának eléréséhez.
    */
    std::string getContent();
    /**
     * Setter, ami beállítja a fájl tartalmát.
     * @param content A kapott stringet állítja be a fájl tartalmának.
    */
    void setContent(std::string content);
};

#endif /* File_hpp */
