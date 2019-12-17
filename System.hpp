#pragma once

#include "Dir.hpp"
#include "File.hpp"
#include <vector>
#include <iostream>

/**
 * Exception needed for handling the goToFolder() function
*/
class NoDirectoryExc : public std::exception {
    std::string what = "No directory found with the given name. Please try again with another name!\n";
public:
    std::string getWhat() { return what; };
};

/**
 * @brief Class for describing a virtual filesystem.
 * @details This class handles the stored folders and files.
*/
class System {
	Dir* currentFolder;
public:
	System();
    ~System();
	/**
	 * @brief Creates a Node* from a string.
	 * @details Searches the Node by the given name in the current folder and returns it as a pointer.
	 * @param ston The wanted Node's name.
	 * @note Only searches in the folder we are currently in.
	 * @return Node * - if it's found by name.
	 * @return nullptr - if it can't be found in the current folder.
	*/
    Node* stringToNode(std::string ston);

	/**
	 * Needed basic print to emulate the terminal.
	*/
	void printCore() const;

	/**
	 * @brief Checks if a Node exists with the given name.
	 * @details Goes through the children vector of the current Folder to search the for the Node with the given name.
	 * @param name The wanted Node's name.
	 * @note Only searches in the current folder!
	 * @return true - if the given Node is already in the vector.
	 * @return false - if the given Node isn't in the vector.
	*/
	bool alreadyExists(std::string name);
    
	/**
	 * @brief Goes back to the root
	*/
    void goToRoot();

	/**
	 * @brief Used at absolute path
	 * @details Gets an absolute access path as a parameter, after parsing it navigates through one by one until the path's end. Only navigates until the second last member then returns with the last member.
	 * @param absolut Absolute access path.
	 * @return Absolute access path's last member. For later elaboration.
	 * @warning NoDirectoryExc Throws an exception, if it can't navigate to the destination.
	 * @see NoDirectoryExc
	 * @brief Example:
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
	 * @brief Creates a folder.
	 * @param name folder's name.
	 * @note @param name can be absolute path.
	 * @details Puts a new Dir pointer in the children vector of the given currentFolder variable.
	*/
	void mkdir(std::string name);

	/**
	 * @brief Creates a file.
	 * @param name file's name.
	 * @note name can be absolute path.
	 * @details Puts a new File pointer in the children vector of the given currentFolder variable.
	*/
    void touch(std::string name);
	/**
	 * @brief Lists the Folder's content.
	 * @note If the name is empty, it lists the current folder.
	 * @note name can be absolute path.
	 * @param name folder's name.
	*/
	void ls(std::string name);
	/**
	 * @brief Sets the currentFolder to a folder with the name it got.
	 * @note name can be absolute path.
	 * @param name selected folder's name.
	 * 
	*/
	void cd(std::string name);
	/**
	 * @brief Moves up a folder in the tree.
	*/
	void cdBack();
	/**
	 * @brief Deletes a Node pointer from the children vector.
	 * @details In case of files, it always terminates. In case of folders, it only terminates, if the children vector of the given folder is empty. 
	 * @warning Only works with empty folders.
	 * @param name name of the to be deleted element.
	 * @note name can be absolute path.
	*/
	void rm(std::string name);
	/**
	 * @brief Same as rm, but works with non-emtpy folders.
	 * @details If the children vector of the given folder's isn't empty, then it invokes the function recursively on the vector's elements.
	 * Does this, until the children vector of the given folder isn't empty. Then it deletes the given folder as well.
	 * @param name the given element's name.
	 * @note name can be absolute path.
	*/
	void rmrf(std::string name);
	/**
	 * @brief Gives a file content.
	 * @param name the name/access path of the file.
	 * @param content The file's content.
	 * @note If the file doesn't exist then it creates it with the given content.
	*/
	void echo(std::string name, std::string content);
	/**
	 * @brief Moves the elements from one folder to another.
	 * @param move the element that is going to be moved
	 * @param dest destination folder
	 * @warning dest can only be a folder!
	 * @note move can be absolute path.
	*/
	void mv(std::string move, std::string dest);
};
