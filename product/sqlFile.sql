CREATE TABLE NEW_PE_EMAIL{
	PE_EMAIL		VARCHAR2(30),
	PE_SSNO		VARCHAR2(30) NOT NULL,
	CONSTRAINT NEW_PE_EMAIL_PK PRIMARY KEY(PE_EMAIL,PE_SSNO),
	CONSTRAINT NEW_PE_EMAIL_FK1 FOREIGN KEY(PE_SSNO) REFERENCES PERSON (PE_SSNO)
};

CREATE TABLE NEW_PE_PHONE{
	PE_PHONE		VARCHAR2(30),
	PE_SSNO		VARCHAR2(30) NOT NULL,
	CONSTRAINT NEW_PE_PHONE_PK PRIMARY KEY(PE_PHONE,PE_SSNO),
	CONSTRAINT NEW_PE_PHONE_FK1 FOREIGN KEY(PE_SSNO) REFERENCES PERSON (PE_SSNO)
};

CREATE TABLE PERSON{
	PE_SSNO		VARCHAR2(30) NOT NULL,
	PE_NAME		VARCHAR2(30) NOT NULL,
	PE_DATE_OF_BIRTH		VARCHAR2(30) NOT NULL,
	PE_ADDRESS		VARCHAR2(30) NOT NULL,
	PE_AGE		VARCHAR2(30) NOT NULL,
	PE_EMAIL		VARCHAR2(30),
	PE_PHONE		VARCHAR2(30),
	PE_COUNTRY		VARCHAR2(30),
	CONSTRAINT PERSON_PK PRIMARY KEY(PE_SSNO),
	CONSTRAINT PERSON_UNIQUE (Pe_name, Pe_date_of_birth, Pe_address)
};

