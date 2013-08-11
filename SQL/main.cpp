/* 
 * File:   main.cpp
 * Describe: This is about the sql file create
 * Author: pj
 *
 */

#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <strstream>
#include <algorithm>
#include <cstring>
#include "tinystr.h"
#include "tinyxml.h"
#include "Table.h"

using namespace std;
void createSQL(map<string, Table>&);
bool readXML(map<string, Table>&);
void generateFKey(map<string, Table>&);
void generatePKey(map<string, Table>&);
bool isMultiplicity(Association_class&);
void analyGeneralisation(map<string, Table>&);
void editLink(map<string, Table>&, Association&);
void attributesAnalysis(map<string, Table>&);
void setUnique(map<string,Table>&);
void generateQualification(map<string,Table>&);

/*
 * 
 */

int main(int argc, char** argv) {
    map<string, Table> tables;
    if (readXML(tables)) {
        generatePKey(tables);
		setUnique(tables);
		generateQualification(tables);
        generateFKey(tables);
		analyGeneralisation(tables);
		attributesAnalysis(tables);
        createSQL(tables);
    }
    return 0;
}

bool readXML(map<string, Table>& tables) {
    TiXmlDocument *myDoc = new TiXmlDocument("information.xml");

    if (!myDoc->LoadFile()) {
        cout << myDoc->ErrorDesc() << endl;
        return false;
    } else
        myDoc->LoadFile();
    TiXmlElement* root = myDoc->RootElement();
    //the first layer loop
    for (TiXmlNode* firstNode = root->FirstChild(); firstNode;
            firstNode = firstNode->NextSibling()) {
        Table tmpTable;
        if (strcmp(firstNode->Value(), "class") == 0) {
            //the second layer loop
            for (TiXmlNode *secondNode = firstNode->FirstChild();
                    secondNode; secondNode = secondNode->NextSibling()) {
                if (strcmp(secondNode->Value(), "class_name") == 0) {
                    tmpTable.setTableName(secondNode->FirstChild()->Value());
                } else if (strcmp(secondNode->Value(), "attribute") == 0) {
                    Attribute tmpAttribute;
                    for (TiXmlNode *thirdNode = secondNode->FirstChild();
                            thirdNode; thirdNode = thirdNode->NextSibling()) {
                        if (strcmp(thirdNode->Value(), "attribute_name") == 0) {
                            if (thirdNode->FirstChild() != 0)
                                tmpAttribute.name = thirdNode->FirstChild()->Value();
								string name = tmpTable.getTableName();
								string newName = name.substr(0,2) + '_';
								newName += tmpAttribute.name;
								tmpAttribute.name = newName;

                        } else if (strcmp(thirdNode->Value(), "identifier") == 0) {
                            if (thirdNode->FirstChild() != 0) {
                                tmpAttribute.id = thirdNode->FirstChild()->Value();
                            }
                        } else if (strcmp(thirdNode->Value(), "multiplicity") == 0) {
                            if (thirdNode->FirstChild() != 0)
                                tmpAttribute.multiplicity = thirdNode->FirstChild()->Value();
                        }

                    }

                    tmpTable.setAttribute(tmpAttribute);
                }
            }
            tables.insert(make_pair(tmpTable.getTableName(), tmpTable));

        } else if (strcmp(firstNode->Value(), "association") == 0) {
            Association tmpAssociation;
            for (TiXmlNode *secondNode = firstNode->FirstChild();
                    secondNode; secondNode = secondNode->NextSibling()) {
                if (strcmp(secondNode->Value(), "nameOfAssociation") == 0) {
                    if (secondNode->FirstChild() != 0)
                        tmpAssociation.nameOfAssociation = secondNode->FirstChild()->Value();
                } else if (strcmp(secondNode->Value(), "class") == 0) {
                    Association_class tableValue;
                    for (TiXmlNode *thirdNode = secondNode->FirstChild();
                            thirdNode; thirdNode = thirdNode->NextSibling()) {
                        if (strcmp(thirdNode->Value(), "class_name") == 0) {
                            if (thirdNode->FirstChild() != 0)
                                tableValue.name = thirdNode->FirstChild()->Value();
                        } else if (strcmp(thirdNode->Value(), "multiplicity") == 0) {
                            if (thirdNode->FirstChild() != 0)
                                tableValue.multiplicity = thirdNode->FirstChild()->Value();
                        } else if (strcmp(thirdNode->Value(), "role") == 0) {
                            if (thirdNode->FirstChild() != 0)
                                tableValue.role = thirdNode->FirstChild()->Value();
                        } else {
                            if (thirdNode->FirstChild() != 0)
                                tableValue.qualification.push_back(thirdNode->
                                    FirstChild()->Value());
                        }
                    }
                    tmpAssociation.startTable = tableValue;
                } else if (strcmp(secondNode->Value(), "other_class") == 0) {
                    Association_class tableValue;
                    for (TiXmlNode *thirdNode = secondNode->FirstChild();
                            thirdNode; thirdNode = thirdNode->NextSibling()) {
                        if (strcmp(thirdNode->Value(), "class_name") == 0) {
                            tableValue.name = thirdNode->FirstChild()->Value();
                        } else if (strcmp(thirdNode->Value(), "multiplicity") == 0) {
                            if (thirdNode->FirstChild() != 0)
                                tableValue.multiplicity = thirdNode->FirstChild()->Value();
                        } else if (strcmp(thirdNode->Value(), "role") == 0) {
                            if (thirdNode->FirstChild() != 0)
                                tableValue.role = thirdNode->FirstChild()->Value();
                        } else {
                            if (thirdNode->FirstChild() != 0)
                                tableValue.qualification.push_back(thirdNode->
                                    FirstChild()->Value());
                        }
                    }
                    tmpAssociation.anotherTable = tableValue;
                } else if (strcmp(secondNode->Value(), "Link") == 0) {
                    Linker tmpLink;
                    TiXmlNode* thirdNode = secondNode->FirstChild();
                    for (; thirdNode; thirdNode = thirdNode->NextSibling()) {
                        if (strcmp(thirdNode->Value(), "link_attribute") == 0
                                && thirdNode->FirstChild() != 0) {
                            TiXmlNode* forthNode = thirdNode->FirstChild();
                            for (; forthNode; forthNode = forthNode->NextSibling()) {
                                if (forthNode->FirstChild() != NULL)
                                    tmpLink.attributes.push_back(forthNode->FirstChild()
                                        ->Value());
                            }
                        } else if (strcmp(thirdNode->Value(), "association_class") == 0
                                && thirdNode->FirstChild() != 0) {
                            TiXmlNode* forthNode = thirdNode->FirstChild();
                            for (; forthNode; forthNode = forthNode->NextSibling()) {
                                if (strcmp(forthNode->Value(), "nameOfAssociationClass") == 0) {
                                    if (strlen(forthNode->FirstChild()->Value()) > 0) {
                                        if (forthNode->FirstChild() != 0)
                                            tmpLink.nameOfAssociationClass = forthNode->FirstChild()
                                            ->Value();
                                    }
                                } else if (strcmp(forthNode->Value(), "qualification") == 0) {
                                    if (strlen(forthNode->FirstChild()->Value()) > 0) {
                                        if (forthNode->FirstChild() != 0)
                                            tmpLink.qualification.push_back(forthNode->FirstChild()
                                                ->Value());
                                    }
                                }
                            }
                        }
                    }
                    if (tmpLink.attributes.size() != 0 ||
                            tmpLink.nameOfAssociationClass != "" ||
                            tmpLink.qualification.size() != 0) {
                        tmpAssociation.link = tmpLink;
                    }
                }

            }
            map<string, Table>::iterator tableIte = tables.find(tmpAssociation.
                    startTable.name);
            if (tableIte != tables.end()) {
                tableIte->second.setAssociation(tmpAssociation);
				tableIte->second.setHasLink(true);
				tableIte = tables.find(tmpAssociation.anotherTable.name);
				tableIte->second.setHasLink(true);
            } else {
                cerr << "There is no table in this database.";
            }
        } else if (strcmp(firstNode->Value(), "generlisation") == 0) {
            TiXmlNode* secondNode = firstNode->FirstChild();
            Generalisation tmpGeneralisation;
            vector<string> tmpClassName;
            for (; secondNode; secondNode = secondNode->NextSibling()) {
                if (strcmp(secondNode->Value(), "class_name") == 0) {
                    if (secondNode->FirstChild() != 0)
                        tmpClassName.push_back(secondNode->FirstChild()->Value());
                } else if (strcmp(secondNode->Value(), "ISA") == 0) {
                    if (secondNode->FirstChild() != 0)
                        tmpGeneralisation.ISA = secondNode->FirstChild()->Value();
                } else if (strcmp(secondNode->Value(), "generalisation") == 0) {
                    if (secondNode->FirstChild() != 0)
                        tmpGeneralisation.type = secondNode->FirstChild()->Value();
                }
            }
            
            vector<string>::iterator classNameIter = tmpClassName.begin();
            while(classNameIter != tmpClassName.end()){
                tmpGeneralisation.className = *classNameIter;
                map<string, Table>::iterator tableIte = tables.find(tmpGeneralisation.className);
            if (tableIte != tables.end()) {
                tableIte->second.setGeneralisation(tmpGeneralisation);
                 } else {
                cerr << "There is no table in this database.";
                 }
                classNameIter++;
             }
        }                    
    }
    return true;
}

void generateFKey(map<string, Table>& tables) {
    map<string, Table>::iterator tableIte = tables.begin();
    vector<Table> linkers;
    ForeignKey foreignKey;
    while (tableIte != tables.end()) {
        if (!tableIte->second.getAssociation().empty()) {
            vector <Association> tmpAssociation =
                    tableIte->second.getAssociation();
            vector <Association>::iterator associationIter
                    = tmpAssociation.begin();

            while (associationIter != tmpAssociation.end()) {
                //these are all one-to-many.
                if (isMultiplicity(associationIter->startTable) &&
                        !isMultiplicity(associationIter->anotherTable)) {
                     map<string, Table>::iterator tmpTableIte = tables.find(
                            associationIter->anotherTable.name);
                     if(!tmpTableIte->second.getPK().empty()){
                        foreignKey.associationClassName =
                            associationIter->anotherTable.name;
                   
                        foreignKey.attributes = tmpTableIte->second.getPK();
                        tableIte->second.setFK(foreignKey);
						tableIte->second.setAttribute(foreignKey.attributes);
                        foreignKey.attributes.clear();
                        foreignKey.associationClassName.clear();
                     }
                } else if (!isMultiplicity(associationIter->startTable) &&
                        isMultiplicity(associationIter->anotherTable)) {
                    foreignKey.associationClassName = associationIter->startTable.name;
                    map<string, Table>::iterator tmpTableIte = tables.find(
                            associationIter->anotherTable.name);
                    if(!tableIte->second.getPK().empty()){
                        
                        foreignKey.attributes = tableIte->second.getPK();
                        tmpTableIte->second.setFK(foreignKey);
						tmpTableIte->second.setAttribute(foreignKey.attributes);
                        foreignKey.attributes.clear();
                        foreignKey.associationClassName.clear();
                    
                    }
                }//it is many to many,so I create a linker to set it as one to many
				else if (isMultiplicity(associationIter->startTable) &&
					isMultiplicity(associationIter->anotherTable)) {
						if (associationIter->link.nameOfAssociationClass.empty() &&
							tableIte->first == associationIter->startTable.name){
							Table newLink;
							string name = associationIter->startTable.name;
							string of = "_";
							name += of;
							name += associationIter->anotherTable.name;
							newLink.setTableName(name);

							//set the first FK and attributes
							map<string, Table>::iterator aTableIte = tables.find(
								associationIter->anotherTable.name);
							if (!aTableIte->second.getPK().empty()) {

								
								foreignKey.associationClassName = associationIter->anotherTable.name;
								foreignKey.attributes = aTableIte->second.getPK();
								newLink.setFK(foreignKey);
								vector <Attribute>::iterator attributeIte = foreignKey.attributes.begin();
								while(attributeIte != foreignKey.attributes.end()){
									attributeIte->id = "ID";
									attributeIte++;
								}
								newLink.setAttribute(foreignKey.attributes);
								foreignKey.attributes.clear();
								foreignKey.associationClassName.clear();

							}
							//set another FK and attributes
							map<string, Table>::iterator sTableIte = tables.find(associationIter->startTable.name);
							if (!sTableIte->second.getPK().empty()) {

								foreignKey.associationClassName = associationIter->startTable.name;
								foreignKey.attributes = sTableIte->second.getPK();
								newLink.setFK(foreignKey);
								vector <Attribute>::iterator attributeIte = foreignKey.attributes.begin();
								while(attributeIte != foreignKey.attributes.end()){
									attributeIte->id = "ID";
									attributeIte++;
								}
								newLink.setAttribute(foreignKey.attributes);	

								foreignKey.attributes.clear();
								foreignKey.associationClassName.clear();

							}
							newLink.setPK();
							linkers.push_back(newLink);

						}else
						{
							editLink(tables, *associationIter);
						}
				}//here is one-to-one model
                else {
                    //set another table's FK
                    foreignKey.associationClassName = associationIter->startTable.name;
                    map<string, Table>::iterator tmpTableIte = tables.find(
                            associationIter->anotherTable.name);
                    if (!tableIte->second.getPK().empty()) {

                        foreignKey.attributes = tableIte->second.getPK();
                        tmpTableIte->second.setFK(foreignKey);
                        tmpTableIte->second.setAttribute(foreignKey.attributes);
                        foreignKey.attributes.clear();
                        foreignKey.associationClassName.clear();
                    }
                    //set current table's FK
                    foreignKey.associationClassName = associationIter->anotherTable.name;
                    tmpTableIte = tables.find(associationIter->anotherTable.name);
                    if (!tmpTableIte->second.getPK().empty()) {

                        foreignKey.attributes = tmpTableIte->second.getPK();
                        tableIte->second.setFK(foreignKey);
                        tableIte->second.setAttribute(foreignKey.attributes);
                        foreignKey.attributes.clear();
                        foreignKey.associationClassName.clear();
                    }
                }
                associationIter++;
            }
        }
        tableIte++;
    }

    //insert new table into container
    vector<Table>::iterator linkIte = linkers.begin();
    while (linkIte != linkers.end()) {
        tables.insert(make_pair(linkIte->getTableName(), *linkIte));
        linkIte++;
    }
}

void createSQL(map<string, Table>& tables) {
    //-----------------------create sql file -----------------------------------
    ofstream fout("sqlFile.sql");
    //------------------all variables definiation-------------------------------
    toBeUp transUpper;
    map<string, Table>::iterator tableIte = tables.begin();
    vector<Attribute> tmpAttribute;
    vector<Attribute> tmpPk;
    vector <ForeignKey> tmpFK;
    vector <Unique> tmpUnique;
    //--------------------------------------------------------------------------

    while (tableIte != tables.end()) {
        //------------------generate table name---------------------------------
        string name = tableIte->first;
        //set table name to be bigger character
        transform(name.begin(), name.end(), name.begin(), transUpper);
        fout << "CREATE TABLE " << name << "{" << endl;

        //----------------generate Attributes-------------------------------
        tmpAttribute = tableIte->second.getAttribute();
        vector<Attribute>::iterator attributeIte = tmpAttribute.begin();
        while (attributeIte != tmpAttribute.end()) {

            string attributeName = attributeIte->name;
            //set attribute name to be bigger character
            transform(attributeName.begin(), attributeName.end(),
                    attributeName.begin(), transUpper);
            fout << "\t" << attributeName << "\t\tVARCHAR2(30)";

            if ((strcmp(attributeIte->multiplicity.c_str(), "[1]") == 0) ||
                    attributeIte->multiplicity.empty()) {
                fout << " NOT NULL,";
            } else {
                fout << ",";
            }

            fout << endl;


            attributeIte++;
        }

        //----------------generate PK-------------------------------
        if (!tableIte->second.getPK().empty()) {
            tmpPk = tableIte->second.getPK();
            vector<Attribute>::iterator PKIte = tmpPk.begin();
            fout << "\tCONSTRAINT " << name << "_PK PRIMARY KEY(";
            while (PKIte != tmpPk.end()) {
                string PKName = PKIte->name;
                transform(PKName.begin(), PKName.end(), PKName.begin(), transUpper);
                fout << PKName;
                PKIte++;
                if (PKIte == tmpPk.end()) {
                    if (tableIte->second.getFK().empty() &&
                            tableIte->second.getUnique().empty()) {
                        fout << ")" << endl;
                    } else {
                        fout << ")," << endl;
                    }
                } else {
                    fout << ",";
                }
            }
        }
        //----------------generate Unique---------------------------
        if (!tableIte->second.getUnique().empty()) {
            tmpUnique = tableIte->second.getUnique();
            vector<Unique>::iterator uniqueIte = tmpUnique.begin();
            int uniqueIdx = 1;
            while (uniqueIte != tmpUnique.end()) {
                fout << "\tCONSTRAINT " << name << "_UNIQUE";
                if (tmpUnique.size() != 1) {
                    fout << uniqueIdx;
                }
                fout << " (";
                vector<string>::iterator uniqueAttIte = uniqueIte->name.begin();
                while (uniqueAttIte != uniqueIte->name.end()) {
                    fout << *uniqueAttIte;
                    uniqueAttIte++;
                    if (uniqueAttIte == uniqueIte->name.end()) {
                        fout << ")";
                    } else {
                        fout << ", ";
                    }
                }

                uniqueIte++;
                if (uniqueIte != tmpUnique.end()) {
                    fout << "," << endl;
                }
            }
            if (!tableIte->second.getFK().empty()) {
                fout << endl;
                fout << ",";
            }
            fout << endl;
        }

        //----------------generate FK-------------------------------
        if (!tableIte->second.getFK().empty()) {
            tmpFK = tableIte->second.getFK();
            vector<ForeignKey>::iterator FKIte = tmpFK.begin();
            int FKIdx = 1;
            while (FKIte != tmpFK.end()) {
                string tablename = FKIte->associationClassName;
                transform(tablename.begin(), tablename.end(),
                        tablename.begin(), transUpper);
                string attName;
                vector<Attribute>::iterator FKAttributesIte = FKIte->attributes.begin();
                fout << "\tCONSTRAINT " << name << "_FK" << FKIdx << " FOREIGN KEY(";
                while (FKAttributesIte != FKIte->attributes.end()) {
                    attName = FKAttributesIte->name;
                    transform(attName.begin(), attName.end(),
                            attName.begin(), transUpper);
                    fout << attName;
                    FKAttributesIte++;
                    if (FKAttributesIte != FKIte->attributes.end()) {
                        fout << ",";
                    }
                }

                fout << ") REFERENCES " << tablename << " (";
                FKAttributesIte = FKIte->attributes.begin();
                while (FKAttributesIte != FKIte->attributes.end()) {
                    attName = FKAttributesIte->name;
                    transform(attName.begin(), attName.end(),
                            attName.begin(), transUpper);
                    fout << attName;
                    FKAttributesIte++;
                    if (FKAttributesIte != FKIte->attributes.end()) {
                        fout << ",";
                    } else {
                        fout << ")";
                    }
                }
                FKIdx++;
                FKIte++;
                if (FKIte != tmpFK.end()) {
                    fout << "," << endl;
                } else
                    fout << endl;
            }
        }


        fout << "};" << endl << endl;
        tableIte++;
    }
}

void generatePKey(map<string, Table>& tables) {
    map<string, Table>::iterator tableIte = tables.begin();
    while (tableIte != tables.end()) {
        tableIte->second.setPK();
        if (tableIte->second.hasGeneralisiation()) {

        }
        tableIte++;
    }

}

bool isMultiplicity(Association_class & table) {

    if (strcmp(table.multiplicity.c_str(), "[0..1]") == 0 || table.multiplicity.empty() ||
            strcmp(table.multiplicity.c_str(), "[1]") == 0) {
        return false;
    } else
        return true;

}

void analyGeneralisation(map<string, Table>& tables) {
    map<string, Table>::iterator ite = tables.begin();
    while (ite != tables.end()) {
        if (ite->second.hasGeneralisiation()) {
            map<string, Table>::iterator superClassIte = tables.find(
                    ite->second.getGeneralisation().ISA);
            vector<Attribute> attribute = superClassIte->second.getAttribute();
            vector<Attribute>::iterator attIte = attribute.begin();
            while (attIte != attribute.end()) {
                ite->second.setAttribute(*attIte);
                attIte++;
            }
            if (!superClassIte->second.getPK().empty()) {
                ForeignKey tmpFK;
                tmpFK.associationClassName = superClassIte->first;
                tmpFK.attributes = superClassIte->second.getPK();
                ite->second.setFK(tmpFK);
                ite->second.setPK();
            }

        }
        ite++;
    }
}

void editLink(map<string, Table>& tables, Association & association) {
    map<string, Table>::iterator linkerIte = tables.find(association.link.nameOfAssociationClass);

    //find startTable and set the fkey into the linker
    map<string, Table>::iterator startTableIte = tables.find(association.startTable.name);
    if (!startTableIte->second.getPK().empty()) {

        ForeignKey startTableFk;
        startTableFk.associationClassName = association.startTable.name;
        startTableFk.attributes = startTableIte->second.getPK();
        vector <Attribute>::iterator setIDIte = startTableFk.attributes.begin();
        while (setIDIte != startTableFk.attributes.end()) {
            setIDIte->id = "ID";
            setIDIte++;
        }
        linkerIte->second.setFK(startTableFk);
        linkerIte->second.setAttribute(startTableFk.attributes);

    }

    //find anotherTable and set the fkey into the linker
    map<string, Table>::iterator anotherTableIte = tables.find(association.anotherTable.name);
    if (!anotherTableIte->second.getPK().empty()) {

        ForeignKey anotherTableFK;
        anotherTableFK.associationClassName = association.anotherTable.name;
        anotherTableFK.attributes = anotherTableIte->second.getPK();
        vector <Attribute>::iterator setIDIte = anotherTableFK.attributes.begin();
        while (setIDIte != anotherTableFK.attributes.end()) {
            setIDIte->id = "ID";
            setIDIte++;
        }
        linkerIte->second.setFK(anotherTableFK);
        linkerIte->second.setAttribute(anotherTableFK.attributes);
    }

    linkerIte->second.setPK();


}

void attributesAnalysis(map<string, Table>& tables) {
    map<string, Table>::iterator tableIte = tables.begin();
    vector<Table> newTables;

    while (tableIte != tables.end()) {

        vector<Attribute> newAtt = tableIte->second.getAttribute();
        vector<Attribute>::iterator newAttIte = newAtt.begin();

        while (newAttIte != newAtt.end()) {
            Table newTable;
            string newName = "New_";
            if (strcmp(newAttIte->multiplicity.c_str(), "[0..1]") == 0 ||
                    strcmp(newAttIte->multiplicity.c_str(), "[1]") == 0) {
                newAttIte++;
                continue;
            }
            if (!newAttIte->multiplicity.empty()) {
                //cout << newAttIte->multiplicity << endl;
                newName += newAttIte->name;
                newTable.setTableName(newName);
                Attribute newAttribute;
                newAttribute = *newAttIte;
                newAttribute.id = "ID";

                //set foreign key
                ForeignKey newForeignKey;
                newForeignKey.associationClassName = tableIte->first;
                newForeignKey.attributes = tableIte->second.getPK();
                newTable.setFK(newForeignKey);


                //insert attributes into new table
                newTable.setAttribute(newAttribute);
                vector<Attribute> tablePK = tableIte->second.getPK();
                for (vector<Attribute>::iterator ite = tablePK.begin();
                        ite != tablePK.end(); ite++) {
                    ite->id = "ID";
                }
                newTable.setAttribute(tablePK);

                newTable.setPK();
                //insert newTable into a container.
                newTables.push_back(newTable);
            }
            newAttIte++;
        }
        tableIte++;
    }
    vector<Table>::iterator newTableIte = newTables.begin();

    //update original tables
    while (newTableIte != newTables.end()) {
        tables.insert(make_pair(newTableIte->getTableName(), *newTableIte));
        newTableIte++;
    }

}

void setUnique(map<string, Table>& tables) {
    map<string, Table>::iterator tableIte = tables.begin();
    while (tableIte != tables.end()) {
        tableIte->second.setUnique();
        tableIte++;
    }
}

//generate qualification

void generateQualification(map<string, Table>& tables) {
    map<string, Table>::iterator tabIte = tables.begin();
    while (tabIte != tables.end()) {
        vector <Association> assocation = tabIte->second.getAssociation();
        vector <Association>::iterator assIte = assocation.begin();
        while (assIte != assocation.end()) {
            if (!assIte->startTable.qualification.empty()) {
                map<string, Table>::iterator ite = tables.find(assIte->anotherTable.name);

                vector<string>::iterator qualifiIte = assIte->startTable.qualification.begin();
                while (qualifiIte != assIte->startTable.qualification.end()) {
                    if (ite->second.hasQuAttribute(*qualifiIte)) {
						
                        qualifiIte++;
                        continue;
                    } else {


                        Attribute newAtt;
                        newAtt.name = *qualifiIte;
                        if (ite->second.getPK().empty())
                            newAtt.id = "ID";
                        else {
                            if (ite->second.getUnique().empty()) {
                                newAtt.id = "ID2";
                            } else {
                                int size_ = ite->second.getUnique().size() + 2;
                                strstream str;
                                str << size_;
                                string idx;
                                newAtt.id = "ID";
                                str >> idx;
                                newAtt.id += idx;
                            }
                        }
                        ite->second.setAttribute(newAtt);
                    }
                    qualifiIte++;
                }
                if (ite->second.getPK().empty())
                    ite->second.setPK();
                else {
                    ite->second.setUnique();
                }
            } else if (!assIte->anotherTable.qualification.empty()) {
                map<string, Table>::iterator ite = tables.find(assIte->startTable.name);

                vector<string>::iterator qualifiIte = assIte->anotherTable.qualification.begin();
                while (qualifiIte != assIte->anotherTable.qualification.end()) {
                    if (ite->second.hasQuAttribute(*qualifiIte)) {
                        qualifiIte++;
                        continue;
                    } else {

                        Attribute newAtt;
                        newAtt.name = *qualifiIte;
                        if (ite->second.getPK().empty())
                            newAtt.id = "ID";
                        else {
                            if (ite->second.getUnique().empty()) {
                                newAtt.id = "ID2";
                            } else {
                                int size_ = ite->second.getUnique().size() + 2;
                                strstream str;
                                str << size_;
                                string idx;
                                newAtt.id = "ID";
                                str >> idx;
                                newAtt.id += idx;
                            }
                        }
                        ite->second.setAttribute(newAtt);
                    }
                    qualifiIte++;
                }
                if (ite->second.getPK().empty())
                    ite->second.setPK();
                else {
                    ite->second.setUnique();
                }
            }
            assIte++;
        }
        tabIte++;

    }
}