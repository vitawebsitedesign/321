#include "Table.h"
using namespace std;

Table::Table() {
	tableName = '\0';
	attributes.clear();
	associations.clear();
	PK.clear();
	FK.clear();
}

Table::~Table() {
}

string Table::getTableName() {
	return tableName;
}

vector<Attribute> Table::getAttribute() {
	return attributes;
}

vector <Association> Table::getAssociation() {
	return associations;
}

Generalisation Table::getGeneralisation() {
	return generalisations;
}

void Table::setTableName(string newName) {
	tableName = newName;
}

void Table::setAttribute(Attribute newAttribute) {
	attributes.push_back(newAttribute);
}

void Table::setAssociation(Association newAssociations) {
	associations.push_back(newAssociations);
}

void Table::setGeneralisation(Generalisation newGeneralisations) {
	generalisations = newGeneralisations;
}

void Table::setPK() {
	vector<Attribute>::iterator ite = attributes.begin();
	string PK_ID;
	vector<Attribute> tmpPK;
	Attribute tmp_PK;
	while (ite != attributes.end()) {
		if (!ite->id.empty()) {
			{
				//check having PRIMARY key
				if (tmpPK.empty()) {
					//save the current ID name
					PK_ID = ite->id;
					tmp_PK.name = ite->name;
					tmp_PK.multiplicity = ite->multiplicity;
					tmpPK.push_back(tmp_PK);
				} else {
					//check having same ID then save this data.
					if (PK_ID == ite->id) {
						tmp_PK.name = ite->name;
						tmp_PK.multiplicity = ite->multiplicity;
						tmpPK.push_back(tmp_PK);
					}
				}
			}
		}
		ite++;
	}
	if (!tmpPK.empty()) {
		PK = tmpPK;
	}
}

void Table::setFK(ForeignKey F_K) {
	if (FK.empty()) {
		FK.push_back(F_K);
	} else {
		std::vector <ForeignKey>::iterator ite = FK.begin();
		bool needPush = false;
		while (ite != FK.end()) {
			if (ite->associationClassName == F_K.associationClassName &&
				ite->attributes.size() == F_K.attributes.size()) {
					vector<Attribute>::iterator F_KAttributeIte = F_K.attributes.begin();
					vector<Attribute>::iterator FKAttributeIte = ite->attributes.begin();
					int idx = 0;
					while (FKAttributeIte != ite->attributes.end()) {
						if (FKAttributeIte->name == F_KAttributeIte->name) {
							idx++;
						}
						FKAttributeIte++;
						F_KAttributeIte++;
					}
					if (idx != ite->attributes.size()) {
						needPush = true;
					}
			} else {
				needPush = true;
			}
			ite++;
		}
		FK.push_back(F_K);
	}
}

vector <Attribute> Table::getPK() {
	return PK;
}

vector <ForeignKey> Table::getFK() {
	return FK;
}

bool Table::hasGeneralisiation() {
	if (generalisations.className.size() != 0) {
		return true;
	}
	return false;
}

void Table::setAttribute(vector <Attribute> tmpAttributes) {
	Attribute tmpAtt;
	vector<Attribute>::iterator ite = tmpAttributes.begin();
	while (ite != tmpAttributes.end()) {
		tmpAtt = *ite;
		attributes.push_back(tmpAtt);
		ite++;
	}

}

void Table::setUnique() {

	vector <Attribute>::iterator Att_Ite = attributes.begin();
	Unique newUnique;
	while (Att_Ite != attributes.end()) {
		if (!hasPk(Att_Ite->name) && !Att_Ite->id.empty()) {
			if (uniques.empty()) {
				newUnique.Id = Att_Ite->id;
				newUnique.name.push_back(Att_Ite->name);
				uniques.push_back(newUnique);
			} else {
				vector<Unique>::iterator uniqueIte = uniques.begin();
				while (uniqueIte != uniques.end()) {
					if (uniqueIte->Id == Att_Ite->id) {
						uniqueIte->name.push_back(Att_Ite->name);
						break;
					}
					uniqueIte++;
				}
				if (uniqueIte == uniques.end()) {
					newUnique.Id = Att_Ite->id;
					newUnique.name.push_back(Att_Ite->name);
					uniques.push_back(newUnique);
				}
			}

		}

		Att_Ite++;
	}
}

vector<Unique> Table::getUnique() {
	return uniques;
}

bool Table::hasPk(string attName) {
	vector<Attribute>::iterator PK_Ite = PK.begin();
	while (PK_Ite != PK.end()) {
		if (PK_Ite->name == attName) {
			return true;
		}
		PK_Ite++;
	}
	return false;
}

void Table::changeNewAttributes(vector<Attribute> newAtt) {
	attributes.clear();
	attributes = newAtt;
}

void Table::deleteAttribute(string att) {
	vector<Attribute>::iterator attIte = attributes.begin();
	while (attIte != attributes.end()) {
		if (att == attIte->name) {
			attributes.erase(attIte);
			break;
		} else {
			attIte++;
		}

	}
}

bool Table::hasQuAttribute(string name){
	vector <Attribute>::iterator ite = attributes.begin();
	string newName = tableName.substr(0,2) + '_';
	newName += name;
	while (ite != attributes.end())
	{
		if(newName == ite->name && !ite->id.empty()){

			return true;
		}else if(newName == ite->name && ite->id.empty())
		{
			ite->id = "ID";
			return true;
		}
		ite++;
	}
	return false;
}
