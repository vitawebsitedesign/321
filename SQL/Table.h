#ifndef READ_H
#define	READ_H
#include <string>
#include <vector>
#include <map>

struct Attribute {
	std::string name;
	std::string id;
	std::string multiplicity;

	friend bool operator==(Attribute& a1, Attribute & a2) {
		if (a1.name == a2.name) {
			return true;
		} else {
			return false;
		}
	};
};

struct Unique {
	std::vector <std::string> name;
	std::string Id;
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

struct ForeignKey {
	std::string associationClassName;
	std::vector <Attribute> attributes;

};

class toBeUp {
public:

	char operator()(char chr) {
		if (chr >= 'a' && chr <= 'z') {
			chr -= 32;
		}
		return chr;
	}

	std::string operator()(std::string& str) {
		for (int i = 0; i != str.size(); i++) {
			if (str[i] >= 'a' && str[i] <= 'z') {
				str[i] -= 32;
			} else {
				continue;
			}
		}
		return str;
	}
};

class Table {
public:
	Table();
	virtual ~Table();
	std::string getTableName();
	std::vector<Attribute> getAttribute();
	std::vector <Association> getAssociation();
	Generalisation getGeneralisation();
	void setTableName(std::string);
	void setAttribute(Attribute);
	void setAttribute(std::vector<Attribute>);
	void changeNewAttributes(std::vector<Attribute>);
	void setAssociation(Association);
	void setGeneralisation(Generalisation);
	void setPK();
	void setFK(ForeignKey);
	void deleteAttribute(std::string);
	std::vector <Attribute> getPK();
	std::vector <ForeignKey> getFK();
	void setUnique();
	std::vector<Unique> getUnique();
	bool hasGeneralisiation();
	bool hasQuAttribute(std::string);

	void setHasLink(bool val) {
		hasLink = val;
	};

	bool HasLinkVal() {
		return hasLink;
	};

private:
	std::string tableName;
	std::vector<Attribute> attributes;
	std::vector <Association> associations;
	Generalisation generalisations;
	std::vector <Attribute> PK;
	std::vector <ForeignKey> FK;
	std::vector <Unique> uniques;
	bool hasLink;

private:
	bool hasPk(std::string);

};

#endif	/* READ_H */