#include "read.h"
using namespace std;

Table::Table() {
    tableName = '\0';
    attributes.clear();
    associations.clear();
    generalisations.clear();
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

vector <Linker> Table::getLink() {
    return linkers;
}

vector <Generalisation> Table::getGeneralisation() {
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
    generalisations.push_back(newGeneralisations);
}