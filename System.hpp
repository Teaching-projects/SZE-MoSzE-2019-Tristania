#pragma once

#include "Dir.hpp"
#include "File.hpp"
#include <vector>
#include <iostream>

/**
 * A goToFolder() függvény lekezeléséhez szükéges exception.
*/
class NoDirectoryExc : public std::exception {
    std::string what = "No directory found with the given name. Please try again with another name!\n";
public:
    std::string getWhat() { return what; };
};

/**
 * @brief Class egy virtuális fájlrendszer leírásához.
 * @details Ez egy olyan class ami kezeli a tárolt mappákat és fájlokat.
*/
class System {
	Dir* currentFolder;
public:
	System();
    ~System();
	/**
	 * @brief Stringből létrehoz egy Node *.
	 * @details az aktuális mappában megkeresi név alapján az adott Node-ot és vissza adja azt pointerként.
	 * @param ston A keresett Node neve.
	 * @note Csak az aktuális mappában keres.
	 * @return Node * - ha megtalálta név alapján.
	 * @return nullptr - ha nem található az aktuális mappában.
	*/
    Node* stringToNode(std::string ston);

	/**
	 * Terminál emulálásához szükséges alap kiiratás.
	*/
	void printCore() const;

	/**
	 * @brief Ellenőrzni létezik-e már az adott nevű Node.
	 * @details Az aktuális mappa children vectorján végig megy, majd megkeresi az adott nevű Node-t.
	 * @param name A keresett Node neve.
	 * @note Csak az aktuális mappában keres!
	 * @return true - ha az adott Node már benne van a vectorban.
	 * @return false - ha az adott Node még nincs benne a vectorban.
	*/
	bool alreadyExists(std::string name);
    
	/**
	 * @brief Vissza megy a gyökér-be
	*/
    void goToRoot();

	/**
	 * @brief Abszolut elérési útnál használandó
	 * @details Paraméterként kap egy abszolut elérési utat, parseolás után egyesével végig navigál az utvonal végéig. Az elérési útból csak az utolso elötti tagik navigál majd vissza adja az utolsó tagot.
	 * @param absolut Abszolut elérési út.
	 * @return Abszolut elérési út utolsó tagja. Későbbi feldolgozás érdekében.
	 * @warning NoDirectoryExc exceptiont dob ha nem sikerül elnavigálni a célig.
	 * @see NoDirectoryExc
	 * @brief Példa:
	 * @code 
	 * 	std::string working;
	 * 	try{ 
	 * 		working = goToFolder("absolut/path/to/file"); 
	 * 	} catch(NoDirException e) { 
	 * 		std::cout << e.getWhat() << std::endl; 
	 * 	}
	 * @endcode
	 * @post working = file
	*/
    std::string goToFolder(std::string absolut);

	/**
	 * @brief Létrehoz egy mappát
	 * @param name A mappa neve
	 * @note @param name lehet absolut path is
	 * @details Az adott currentFolder változó children vectorába tesz bele egy uj Dir mutatót
	*/
	void mkdir(std::string name);

	/**
	 * @brief Létrehoz egy fájlt.
	 * @param name A fájl neve.
	 * @note name Lehet absolut path is.
	 * @details Az adott currentFolder változó children vectorában tesz bele egy uj File mutatót.
	*/
    void touch(std::string name);
	/**
	 * @brief Listázza az mappa tartalmát
	 * @note Ha a name üres az aktuális mappát listázza ki.
	 * @note name lehet absolut path is
	 * @param name mappa neve
	*/
	void ls(std::string name);
	/**
	 * @brief A currentFolder-t beállitja a kapott navű mappára.
	 * @note name lehet absolut path is.
	 * @param name Kiválasztott mappa neve.
	 * 
	*/
	void cd(std::string name);
	/**
	 * @brief Feljebb lép egy mappával a fában.
	*/
	void cdBack();
	/**
	 * @brief Kitöröl egy Node mutatot a children vectorból
	 * @details Fájlok esetén midnig lefut. Mappák esetén csak akkor fut le, ha a kapott mappának a children vectora üres.
	 * @warning Csak üres mappára működik.
	 * @param name törölni kívánt elem neve.
	 * @note name lehet absolut apth is.
	*/
	void rm(std::string name);
	/**
	 * @brief Ugyan az mint az rm csak nem működik nem üres mappára is.
	 * @details ha az adott mappa children vectora nem üres akkor a vector elemeire rekurzivan meghivja saját magát. Addig csinálja amíg az addot
	 * mappa children vectora nem üres. Ekkor törli az adott mappát is.
	 * @param name Az adott elem neve.
	 * @note name Lehet absolut path is.
	*/
	void rmrf(std::string name);
	/**
	 * @brief Fájlhoz ad tartalmat
	 * @param name A fájl neve/elérési utja
	 * @param content A fájl kivánt tartalma
	 * @note ha nem létezik a fájl és még nicsn olyan nevű fájl akkor létrehozza a kívánt tartalommal.
	*/
	void echo(std::string name, std::string content);
	/**
	 * @brief Átmozgatja az elemeket egyik mappából a másikba
	 * @param move mozgatni kívánt elem
	 * @param dest cél mappa
	 * @warning A dest csak mappa lehet!
	 * @note move lehet absolut path is.
	*/
	void mv(std::string move, std::string dest);
};
