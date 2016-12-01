#include "loadsave.hpp"

#pragma warning(push, 0)
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/xml_oarchive.hpp> 
#include <boost/archive/xml_iarchive.hpp> 
#include <boost/serialization/nvp.hpp>
#include <boost/filesystem.hpp>
#pragma warning(pop)

#include <fstream>
#include <iostream>
#include "miscellaneous.hpp"
#include "exceptions.hpp"
#include "inputarchive.hpp"
#include "outputarchive.hpp"
#include "log.hpp"

void LoadSave::saveToXML(const Node& node, const std::string& dataFileName, const std::string& dataFileIdentifier) {
	//Misc::makeBackup(dataFileName); debug crashes...
	
	// TODO: Create directory if it is missing!
	try {
		std::ofstream ofs(dataFileName.c_str());
		OutputArchive outputArchive(ofs);
		Node fileNode(dataFileIdentifier);
		fileNode.addChild(node);
		outputArchive << fileNode;
		ofs.close();
	} catch(std::exception& e) {
		throw FileException("Could not save node " + dataFileIdentifier + " to XML " + dataFileName + ". (" + e.what() + ")");
	}
}

Node LoadSave::loadFromXML(const std::string& dataFileName, const std::string& dataFileIdentifier) {
	Node node;
	if(boost::filesystem::exists(dataFileName)) {
		std::ifstream ifs(dataFileName.c_str());
		InputArchive inputArchive(ifs);		
		inputArchive >> node;
		ifs.close();		
	} else {
		throw FileException("Could not load node " + dataFileIdentifier + ", file " + dataFileName + " not found.");
	}
	if(node.getChildren().size() == 0) {
		throw FileException("Could not load node " + dataFileIdentifier + ", file " + dataFileName + " invalid or empty.");
	}
	return node.getChildren().front();
}