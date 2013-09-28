#ifndef READ_H
#define READ_H
#include <string>
#include <vector>

struct Attribute {
    std::string name;
    std::string id;
    std::string multiplicity;
};

//class in association

struct Association_class {
    std::string name;
    std::string multiplicity;
    std::string role;
    std::vector <std::string> qualification;

};

//LINK in association

struct Linker {
    std::vector<std::string> attributes;
    std::vector<std::string> qualification;
    std::string nameOfAssociationClass;
};

struct Association {
    std::string nameOfAssociation;
    Association_class startTable;
    Association_class anotherTable;
    Linker link;
};

struct Generalisation {
    std::string className;
    std::string ISA;
    std::string type;
};

class Table {
public:
    Table();
    virtual ~Table();
    std::string getTableName();
    std::vector <Attribute> getAttribute();
    std::vector <Association> getAssociation();
	std::vector <Linker> getLink();
    std::vector <Generalisation> getGeneralisation();
    void setTableName(std::string);
    void setAttribute(Attribute);
    void setAssociation(Association);
    void setGeneralisation(Generalisation);

private:
    std::string tableName;
    std::vector <Attribute> attributes;
    std::vector <Association> associations;
	std::vector <Linker> linkers;
    std::vector <Generalisation> generalisations;
};

#endif	/* READ_H */