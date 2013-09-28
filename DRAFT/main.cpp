#include <windows.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <map>
#include <cstring>
#include "gl/glut.h"
#include "read.h"
#include "tinystr.h"
#include "tinyxml.h"
#include "glext.h"


using namespace std;

struct tmpclass
{
	int x[10];	// x-coord of class
	int y[10];	// y-coord of class
	int w[10];	// wide of class(the longest attribute+multiplicity+id)
	int l[10];	// length of class(number of attribute+classname)
	int right[10];
	int down[10];
	int up[10];
	int left[10];
};


int worldX =0;
int worldY =0;
int wordHeight= 12;
int wordLength= 5;
string tmpString[10];
tmpclass *tclass = new tmpclass;

bool readXML(map<string, Table>&);
bool save_screenshot(string, int, int);
void ArrowLefttoRight(int, int, int, int, int, int, int, int, bool, string, string, string, string, string, vector<string>&);
void ArrowRighttoLeft(int, int, int, int, int, int, int, int, bool, string, string, string, string, string, vector<string>&);
void ArrowToptoBottom(int, int, int, int, int, int, int, int, bool, string, string, string, string, string, vector<string>&);
void ArrowBottomtoTop(int, int, int, int, int, int, int, int, bool, string, string, string, string, string, vector<string>&);

void DoubleArrowLefttoRight(int, int, int, int, int, int, int, int, string, string, string, string, string);
void DoubleArrowRighttoLeft(int, int, int, int, int, int, int, int, string, string, string, string, string);
void DoubleArrowToptoBottom(int, int, int, int, int, int, int, int, string, string, string, string, string);
void DoubleArrowBottomtoTop(int, int, int, int, int, int, int, int, string, string, string, string, string);

void CircumRighttoTop(int, int, int, int, bool, string, string, string, string, string, vector<string>&);
void CircumRighttoBottom(int, int, int, int, bool, string, string, string, string, string, vector<string>&);
void CircumLefttoTop(int, int, int, int, bool, string, string, string, string, string, vector<string>&);
void CircumLefttoBottom(int, int, int, int, bool, string, string, string, string, string, vector<string>&);

void QualificationLefttoRight(int, int, int, int, int, int, int, int, string, string, string, string, string, vector<string>&);
void QualificationLeftfromRight(int, int, int, int, int, int, int, int, string, string, string, string, string, vector<string>&);
void QualificationRighttoLeft(int, int, int, int, int, int, int, int, string, string, string, string, string, vector<string>&);
void QualificationRightfromLeft(int, int, int, int, int, int, int, int, string, string, string, string, string, vector<string>&);
void QualificationToptoBottom(int, int, int, int, int, int, int, int, string, string, string, string, string, vector<string>&);
void QualificationTopfromBottom(int, int, int, int, int, int, int, int, string, string, string, string, string, vector<string>&);
void QualificationBottomtoTop(int, int, int, int, int, int, int, int, string, string, string, string, string, vector<string>&);
void QualificationBottomfromTop(int, int, int, int, int, int, int, int, string, string, string, string, string, vector<string>&);

void AssociationLefttoRight(int, int, int, int, int, int, int, int, int, string, string, string, string, string, string);
void AssociationRighttoLeft(int, int, int, int, int, int, int, int, int, string, string, string, string, string, string);
void AssociationToptoBottom(int, int, int, int, int, int, int, int, int, string, string, string, string, string, string);
void AssociationBottomtoTop(int, int, int, int, int, int, int, int, int, string, string, string, string, string, string);

void GeneralizationLefttoRight(int, int, int, int, int, int, int, int,string);
void GeneralizationRighttoLeft(int, int, int, int, int, int, int, int,string);
void GeneralizationToptoBottom(int, int, int, int, int, int, int, int,string);
void GeneralizationBottomtoTop(int, int, int, int, int, int, int, int,string);

void Class(int, int, int, int);
void LinkClassVR(int, int, int, int);
void LinkClassVL(int, int, int, int);
void LinkClassC(int, int, int, int);
void myMenu(int);
void draw();
/*test print function*/
bool testprintQstart(string&,vector<string>&);
void testprintlinkq(vector<string>&);
int longest(string&);
int attnum(string&);
void printattributes(string&,int, int, int, int);
bool attcompare(string&,string&);
void printqua(int,int,int,int,string);

void ArrowLefttoRight(int x1, int y1, int l1, int n1, int x2, int y2, int l2, int n2, bool linkattribute, string assname, string startrole, string startmulti, string endrole, string endmulti, vector<string>&attribute)
{
	glLineWidth(1);
	int xa,ya,xb,yb;
	xa = x1+(l1+1)*wordLength;
	ya = y1+2*(n1+1)/3*wordHeight;
	xb = x2;
	yb = y2+2*(n2+1)/3*wordHeight;
    glBegin(GL_LINES);
        glVertex2f(xa, ya);
        glVertex2f(xb, yb);
    glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex2f(xb-25,yb-5+20);
		glVertex2f(xb-20,yb+20);
		glVertex2f(xb-25,yb+5+20);
    glEnd();
	int len, j;
	glRasterPos2f(xb-30-assname.size()*wordLength, yb+15);
	len = assname.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, assname[j]);
	}
	glRasterPos2f(xa+5, ya-10);
	len = startrole.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, startrole[j]);
	}
	glRasterPos2f(xa+5, yb+5);
	len = startmulti.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, startmulti[j]);
	}
	glRasterPos2f(xb-5-endrole.size()*wordLength, yb-10);
	len = endrole.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, endrole[j]);
	}
	glRasterPos2f(xb-endmulti.size()*wordLength, yb+5);
	len = endmulti.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, endmulti[j]);
	}
	if (linkattribute == true)
	{
		int xn,yn;
		xn = xb-(xb-xa)/2;
		yn = ya+(ya-yb)/2;
		glLineWidth (1.0);
		glEnable(GL_LINE_STIPPLE);
		glLineStipple (1, 0x0F0F);  
		glBegin(GL_LINES);  
        glVertex2f (xn,yn); glVertex2f (xn,yn-20); 
		glEnd();
		glDisable(GL_LINE_STIPPLE);
		int longestname = 0;
		int count = 0;
		string att;
		vector<string>::iterator it = attribute.begin ();
		if((int)attribute.size()!=0)
		{
			while(it!=attribute.end ())
			{
				att = *it; 
				it++;
				if (longestname < att.length())
				longestname = att.length();
				count++;
			}
			int tmpx,tmpy;
			tmpx = xn-longestname/2*wordLength;
			tmpy = yn-5-2*wordHeight;
			
			it = attribute.begin ();
			while(it!=attribute.end ())
			{
				tmpy = tmpy - wordHeight;
				att = *it; 
				it++;
				len = att.size();
				glRasterPos2f(tmpx,tmpy);
				for (j = 0; j < len; j++) 
				{
					glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, att[j]);
				}
			}
		}

		LinkClassC(xn,yn-20,longestname,count);
	}
}
void ArrowRighttoLeft(int x1, int y1, int l1, int n1, int x2, int y2, int l2, int n2, bool linkattribute, string assname, string startrole, string startmulti, string endrole, string endmulti, vector<string>&attribute)
{
	glLineWidth(1);
	int xa,ya,xb,yb;
	xa = x1;
	ya = y1+2*(n1+1)/3*wordHeight;
	xb = x2+(l2+1)*wordLength;
	yb = y2+2*(n2+1)/3*wordHeight;
    glBegin(GL_LINES);
        glVertex2f(xa, ya);
        glVertex2f(xb, yb);
    glEnd();
	glBegin(GL_TRIANGLES);
		glVertex2f(xb+5,yb-5+20);
		glVertex2f(xb,yb+20);
		glVertex2f(xb+5,yb+5+20);
    glEnd();
	int len, j;
	glRasterPos2f(xb+10, yb+15);
	len = assname.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, assname[j]);
	}
	glRasterPos2f(xa-5-startrole.size()*wordLength, ya-10);
	len = startrole.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, startrole[j]);
	}
	glRasterPos2f(xa-5-startmulti.size()*wordLength, ya+5);
	len = startmulti.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, startmulti[j]);
	}
	glRasterPos2f(xb+5, yb-10);
	len = endrole.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, endrole[j]);
	}
	glRasterPos2f(xb+5, yb+5);
	len = endmulti.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, endmulti[j]);
	}
	if (linkattribute == true)
	{
		int xn,yn;
		xn = xb-(xb-xa)/2;
		yn = ya+(ya-yb)/2;
		glLineWidth (1.0);
		glEnable(GL_LINE_STIPPLE);
		glLineStipple (1, 0x0F0F);  
		glBegin(GL_LINES);  
        glVertex2f (xn,yn); glVertex2f (xn,yn-20); 
		glEnd();
		glDisable(GL_LINE_STIPPLE);
		int longestname = 0;
		int count = 0;
		string att;
		vector<string>::iterator it = attribute.begin ();
		if((int)attribute.size()!=0)
		{
			while(it!=attribute.end ())
			{
				att = *it; 
				it++;
				if (longestname < att.length())
				longestname = att.length();
				count++;
			}
			int tmpx,tmpy;
			tmpx = xn-longestname/2*wordLength;
			tmpy = yn-5-2*wordHeight;
			
			it = attribute.begin ();
			while(it!=attribute.end ())
			{
				tmpy = tmpy - wordHeight;
				att = *it; 
				it++;
				len = att.size();
				glRasterPos2f(tmpx,tmpy);
				for (j = 0; j < len; j++) 
				{
					glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, att[j]);
				}
			}
		}

		LinkClassC(xn,yn-20,longestname,count);
	}
	
}
void ArrowToptoBottom(int x1, int y1, int l1, int n1, int x2, int y2, int l2, int n2, bool linkattribute, string assname, string startrole, string startmulti, string endrole, string endmulti, vector<string>&attribute)
{
	glLineWidth(1);
	int xa,ya,xb,yb;
	xa = x1+(l1+1)*wordLength/2;
	ya = y1;
	xb = x2+(l2+1)*wordLength/2;
	yb = y2+(n2+1)*wordHeight;
    glBegin(GL_LINES);
        glVertex2f(xa, ya);
        glVertex2f(xb, yb);
    glEnd();
	glBegin(GL_LINES);
        glVertex2f(xb+5, yb+5);
        glVertex2f(xb, yb);
    glEnd();
		glBegin(GL_TRIANGLES);
		glVertex2f(xb-5-20,yb+45);
		glVertex2f(xb-20,yb+40);
		glVertex2f(xb+5-20,yb+45);
    glEnd();
	int len, j;
	glRasterPos2f(xb-20-assname.size()*wordLength, yb+50);
	len = assname.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, assname[j]);
	}
	glRasterPos2f(xa-5-startrole.size()*wordLength, ya-10);
	len = startrole.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, startrole[j]);
	}
	glRasterPos2f(xa+5, ya-10);
	len = startmulti.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, startmulti[j]);
	}
	glRasterPos2f(xb-5-endrole.size()*wordLength, yb+10);
	len = endrole.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, endrole[j]);
	}
	glRasterPos2f(xb+5, yb+10);
	len = endmulti.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, endmulti[j]);
	}

	if (linkattribute == true)
	{
		int xn,yn;
		xn = xb-(xb-xa)/2;
		yn = ya-(ya-yb)/2;
		glLineWidth (1.0);
		glEnable(GL_LINE_STIPPLE);
		glLineStipple (1, 0x0F0F);  
		glBegin(GL_LINES);  
        glVertex2f (xn,yn); glVertex2f (xn+20,yn); 
		glEnd();
		glDisable(GL_LINE_STIPPLE);
		int longestname = 0;
		int count = 0;
		string att;
		vector<string>::iterator it = attribute.begin ();
		if((int)attribute.size()!=0)
		{
			while(it!=attribute.end ())
			{
				att = *it; 
				it++;
				if (longestname < att.length())
				longestname = att.length();
				count++;
			}
			int tmpx,tmpy;
			tmpx = xn+longestname*wordLength-5;
			tmpy = yn+1*wordHeight-3;
			
			it = attribute.begin ();
			while(it!=attribute.end ())
			{
				tmpy = tmpy - wordHeight;
				att = *it; 
				it++;
				len = att.size();
				glRasterPos2f(tmpx,tmpy);
				for (j = 0; j < len; j++) 
				{
					glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, att[j]);
				}
			}
		}

		LinkClassVR(xn+20,yn,longestname,count);
	}

	
}
void ArrowBottomtoTop(int x1, int y1, int l1, int n1, int x2, int y2, int l2, int n2, bool linkattribute, string assname, string startrole, string startmulti, string endrole, string endmulti, vector<string>&attribute)
{
	glLineWidth(1);
	int xa,ya,xb,yb;
	xa = x1+(l1+1)*wordLength/2;
	ya = y1+(n1+1)*wordHeight;
	xb = x2+(l2+1)*wordLength/2;
	yb = y2;
    glBegin(GL_LINES);
        glVertex2f(xa, ya);
        glVertex2f(xb, yb);
    glEnd();
	glBegin(GL_TRIANGLES);
		glVertex2f(xb-5-20,yb-35);
		glVertex2f(xb-20,yb-30);
		glVertex2f(xb+5-20,yb-35);
    glEnd();
	int len, j;
	glRasterPos2f(xb-20-assname.size()*wordLength, yb-50);
	len = assname.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, assname[j]);
	}
	glRasterPos2f(xa-5-startrole.size()*wordLength, ya+10);
	len = startrole.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, startrole[j]);
	}
	glRasterPos2f(xa+5, ya+10);
	len = startmulti.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, startmulti[j]);
	}
	glRasterPos2f(xb-5-endrole.size()*wordLength, yb-10);
	len = endrole.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, endrole[j]);
	}
	glRasterPos2f(xb+5, yb-10);
	len = endmulti.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, endmulti[j]);
	}
		if (linkattribute == true)
	{
		int xn,yn;
		xn = xb-(xb-xa)/2;
		yn = ya-(ya-yb)/2;
		glLineWidth (1.0);
		glEnable(GL_LINE_STIPPLE);
		glLineStipple (1, 0x0F0F);  
		glBegin(GL_LINES);  
        glVertex2f (xn,yn); glVertex2f (xn+20,yn); 
		glEnd();
		glDisable(GL_LINE_STIPPLE);
		int longestname = 0;
		int count = 0;
		string att;
		vector<string>::iterator it = attribute.begin ();
		if((int)attribute.size()!=0)
		{
			while(it!=attribute.end ())
			{
				att = *it; 
				it++;
				if (longestname < att.length())
				longestname = att.length();
				count++;
			}
			int tmpx,tmpy;
			tmpx = xn+longestname*wordLength-5;
			tmpy = yn+1*wordHeight-3;
			
			it = attribute.begin ();
			while(it!=attribute.end ())
			{
				tmpy = tmpy - wordHeight;
				att = *it; 
				it++;
				len = att.size();
				glRasterPos2f(tmpx,tmpy);
				for (j = 0; j < len; j++) 
				{
					glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, att[j]);
				}
			}
		}

		LinkClassVR(xn+20,yn,longestname,count);
	}
	
}

void DoubleArrowLefttoRight(int x1, int y1, int l1, int n1, int x2, int y2, int l2, int n2, string assname, string startrole, string startmulti, string endrole, string endmulti)
{
	glLineWidth(1);
	int xa,ya,xb,yb;
	xa = x1+(l1+1)*wordLength;
	ya = y1;
	xb = x2;
	yb = y2;
    glBegin(GL_LINES);
        glVertex2f(xa, ya);
        glVertex2f(xb, yb);
    glEnd();
	glBegin(GL_TRIANGLES);
		glVertex2f(xb-25,yb-5+20);
		glVertex2f(xb-20,yb+20);
		glVertex2f(xb-25,yb+5+20);
    glEnd();

	int len, j;
	glRasterPos2f(xb-30-assname.size()*wordLength, yb+15);
	len = assname.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, assname[j]);
	}
	glRasterPos2f(xa+5, ya-10);
	len = startrole.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, startrole[j]);
	}
	glRasterPos2f(xa+5, yb+5);
	len = startmulti.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, startmulti[j]);
	}
	glRasterPos2f(xb-5-endrole.size()*wordLength, yb-10);
	len = endrole.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, endrole[j]);
	}
	glRasterPos2f(xb-endmulti.size()*wordLength, yb+5);
	len = endmulti.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, endmulti[j]);
	}
	
}
void DoubleArrowRighttoLeft(int x1, int y1, int l1, int n1, int x2, int y2, int l2, int n2, string assname, string startrole, string startmulti, string endrole, string endmulti)
{
	glLineWidth(1);
	int xa,ya,xb,yb;
	xa = x1;
	ya = y1;
	xb = x2+(l2+1)*wordLength;
	yb = y2;
    glBegin(GL_LINES);
        glVertex2f(xa, ya);
        glVertex2f(xb, yb);
    glEnd();
	glBegin(GL_TRIANGLES);
		glVertex2f(xb+5,yb-5+20);
		glVertex2f(xb,yb+20);
		glVertex2f(xb+5,yb+5+20);
    glEnd();
	int len, j;
	glRasterPos2f(xb+10, yb+15);
	len = assname.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, assname[j]);
	}
	glRasterPos2f(xa-5-startrole.size()*wordLength, ya-10);
	len = startrole.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, startrole[j]);
	}
	glRasterPos2f(xa-5-startmulti.size()*wordLength, ya+5);
	len = startmulti.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, startmulti[j]);
	}
	glRasterPos2f(xb+5, yb-10);
	len = endrole.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, endrole[j]);
	}
	glRasterPos2f(xb+5, yb+5);
	len = endmulti.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, endmulti[j]);
	}
	
}
void DoubleArrowToptoBottom(int x1, int y1, int l1, int n1, int x2, int y2, int l2, int n2, string assname, string startrole, string startmulti, string endrole, string endmulti)
{
	glLineWidth(1);
	int xa1,ya1,xb1,yb1;
	xa1 = x1+(l1+1)*wordLength;
	ya1 = y1;
	xb1 = x2+(l2+1)*wordLength;
	yb1 = y2+(n2+1)*wordHeight;
    glBegin(GL_LINES);
        glVertex2f(xa1, ya1);
        glVertex2f(xb1, yb1);
    glEnd();
		glBegin(GL_TRIANGLES);
		glVertex2f(xb1-5-20,yb1+35);
		glVertex2f(xb1-20,yb1+30);
		glVertex2f(xb1+5-20,yb1+35);
    glEnd();
		int len, j;
	glRasterPos2f(xb1-assname.size()*wordLength+20, yb1+40);
	len = assname.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, assname[j]);
	}
	glRasterPos2f(xa1+5, ya1-20);
	len = startrole.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, startrole[j]);
	}
	glRasterPos2f(xa1-startmulti.size()*wordLength, ya1-20);
	len = startmulti.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, startmulti[j]);
	}
	glRasterPos2f(xb1+5, yb1+20);
	len = endrole.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, endrole[j]);
	}
	glRasterPos2f(xb1-endmulti.size()*wordLength, yb1+20);
	len = endmulti.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, endmulti[j]);
	}
	
}
void DoubleArrowBottomtoTop(int x1, int y1, int l1, int n1, int x2, int y2, int l2, int n2, string assname, string startrole, string startmulti, string endrole, string endmulti)
{
	glLineWidth(1);
	int xa,ya,xb,yb;
	xa = x1+(l1+1)*wordLength;
	ya = y1+(n1+1)*wordHeight;
	xb = x2+(l2+1)*wordLength;
	yb = y2;
    glBegin(GL_LINES);
        glVertex2f(xa, ya);
        glVertex2f(xb, yb);
    glEnd();
	glBegin(GL_TRIANGLES);
		glVertex2f(xb-5-20,yb-25);
		glVertex2f(xb-20,yb-20);
		glVertex2f(xb+5-20,yb-25);
    glEnd();
		int len, j;
	glRasterPos2f(xb-assname.size()*wordLength+20, yb-40);
	len = assname.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, assname[j]);
	}
	glRasterPos2f(xa+5, ya+20);
	len = startrole.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, startrole[j]);
	}
	glRasterPos2f(xa-startmulti.size()*wordLength, ya+20);
	len = startmulti.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, startmulti[j]);
	}
	glRasterPos2f(xb+5, yb-20);
	len = endrole.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, endrole[j]);
	}
	glRasterPos2f(xb-endmulti.size()*wordLength, yb-20);
	len = endmulti.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, endmulti[j]);
	}
}

void CircumRighttoTop(int x1, int y1, int l1, int n1, bool linkattribute, string assname, string startrole, string startmulti, string endrole, string endmulti, vector<string>&attribute)
{
	glLineWidth(1);
	int xa,ya,xb,yb;
	xa = x1+(l1+1)*wordLength;
	ya = y1+(n1+1)/2*wordHeight;
	xb = x1+(l1+1)*wordLength/2;
	yb = y1+(n1+1)*wordHeight;
	 glBegin(GL_LINES);
        glVertex2f(xa, ya);
		glVertex2f(xa+20, ya);
    glEnd();
	glBegin(GL_LINES);
		glVertex2f(xa+20, ya);
		glVertex2f(xa+20, yb+20);
    glEnd();
	glBegin(GL_LINES);
		glVertex2f(xa+20, yb+20);
		glVertex2f(xb, yb+20);
	glEnd();
	glBegin(GL_LINES);
		glVertex2f(xb, yb+20);
        glVertex2f(xb, yb);
	glEnd();
	int xa1,ya1;
	xa1 = xb;
	ya1 = yb+40;
	glBegin(GL_TRIANGLES);
		glVertex2f(xa1,ya1);
		glVertex2f(xa1+5,ya1-5);
		glVertex2f(xa1+5,ya1+5);
    glEnd();
	int len, j;
	glRasterPos2f(xa1+6, ya1-5);
	len = assname.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, assname[j]);
	}
	glRasterPos2f(xa+5, ya+10);
	len = startrole.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, startrole[j]);
	}
	glRasterPos2f(xa+5, ya-10);
	len = startmulti.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, startmulti[j]);
	}
	glRasterPos2f(xb-15, yb+10);
	len = endmulti.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, endmulti[j]);
	}
	glRasterPos2f(xb+5, yb+10);
	len = endrole.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, endrole[j]);
	}
		if (linkattribute == true)
	{
		int xn,yn;
		xn = xa+20;
		yn = ya-(ya-yb)/2;
		glLineWidth (1.0);
		glEnable(GL_LINE_STIPPLE);
		glLineStipple (1, 0x0F0F);  
		glBegin(GL_LINES);  
        glVertex2f (xn,yn); glVertex2f (xn+20,yn); 
		glEnd();
		glDisable(GL_LINE_STIPPLE);
		int longestname = 0;
		int count = 0;
		string att;
		vector<string>::iterator it = attribute.begin ();
		if((int)attribute.size()!=0)
		{
			while(it!=attribute.end ())
			{
				att = *it; 
				it++;
				if (longestname < att.length())
				longestname = att.length();
				count++;
			}
			int tmpx,tmpy;
			tmpx = xn+wordLength+20;
			tmpy = yn+4;
			
			it = attribute.begin ();
			while(it!=attribute.end ())
			{
				tmpy = tmpy - wordHeight;
				att = *it; 
				it++;
				len = att.size();
				glRasterPos2f(tmpx,tmpy);
				for (j = 0; j < len; j++) 
				{
					glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, att[j]);
				}
			}
		}

		LinkClassVR(xn+20,yn,longestname,count);
	}
}
void CircumRighttoBottom(int x1, int y1, int l1, int n1, bool linkattribute, string assname, string startrole, string startmulti, string endrole, string endmulti, vector<string>&attribute)
{
	glLineWidth(1);
	int xa,ya,xb,yb;
	xa = x1+(l1+1)*wordLength;
	ya = y1+(n1+1)/2*wordHeight;
	xb = x1+(l1+1)*wordLength/2;
	yb = y1;
	 glBegin(GL_LINES);
        glVertex2f(xa, ya);
		glVertex2f(xa+20, ya);
    glEnd();
	glBegin(GL_LINES);
		glVertex2f(xa+20, ya);
		glVertex2f(xa+20, yb-20);
    glEnd();
	glBegin(GL_LINES);
		glVertex2f(xa+20, yb-20);
		glVertex2f(xb, yb-20);
	glEnd();
	glBegin(GL_LINES);
		glVertex2f(xb, yb-20);
        glVertex2f(xb, yb);
	glEnd();
	int xa1,ya1;
	xa1 = xb;
	ya1 = yb-40;
	glBegin(GL_TRIANGLES);
		glVertex2f(xa1,ya1);
		glVertex2f(xa1+5,ya1+5);
		glVertex2f(xa1+5,ya1-5);
    glEnd();
	int len, j;
	glRasterPos2f(xa1+6, ya1-5);
	len = assname.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, assname[j]);
	}
	glRasterPos2f(xa+5, ya+10);
	len = startrole.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, startrole[j]);
	}
	glRasterPos2f(xa+5, ya-10);
	len = startmulti.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, startmulti[j]);
	}
	glRasterPos2f(xb-15, yb-10);
	len = endmulti.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, endmulti[j]);
	}
	glRasterPos2f(xb+5, yb-10);
	len = endrole.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, endrole[j]);
	}
		if (linkattribute == true)
	{
		int xn,yn;
		xn = xa+20;
		yn = ya-(ya-yb)/2;
		glLineWidth (1.0);
		glEnable(GL_LINE_STIPPLE);
		glLineStipple (1, 0x0F0F);  
		glBegin(GL_LINES);  
        glVertex2f (xn,yn); glVertex2f (xn+20,yn); 
		glEnd();
		glDisable(GL_LINE_STIPPLE);
		int longestname = 0;
		int count = 0;
		string att;
		vector<string>::iterator it = attribute.begin ();
		if((int)attribute.size()!=0)
		{
			while(it!=attribute.end ())
			{
				att = *it; 
				it++;
				if (longestname < att.length())
				longestname = att.length();
				count++;
			}
			int tmpx,tmpy;
			tmpx = xn+wordLength+20;
			tmpy = yn+4;
			
			it = attribute.begin ();
			while(it!=attribute.end ())
			{
				tmpy = tmpy - wordHeight;
				att = *it; 
				it++;
				len = att.size();
				glRasterPos2f(tmpx,tmpy);
				for (j = 0; j < len; j++) 
				{
					glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, att[j]);
				}
			}
		}

		LinkClassVR(xn+20,yn,longestname,count);
	}
}
void CircumLefttoTop(int x1, int y1, int l1, int n1, bool linkattribute, string assname, string startrole, string startmulti, string endrole, string endmulti, vector<string>&attribute)
{
	glLineWidth(1);
	int xa,ya,xb,yb;
	xa = x1;
	ya = y1+(n1+1)/2*wordHeight;
	xb = x1+(l1+1)*wordLength/2;
	yb = y1+(n1+1)*wordHeight;
	 glBegin(GL_LINES);
        glVertex2f(xa, ya);
		glVertex2f(xa-20, ya);
    glEnd();
	glBegin(GL_LINES);
		glVertex2f(xa-20, ya);
		glVertex2f(xa-20, yb+20);
    glEnd();
	glBegin(GL_LINES);
		glVertex2f(xa-20, yb+20);
		glVertex2f(xb, yb+20);
	glEnd();
	glBegin(GL_LINES);
		glVertex2f(xb, yb+20);
        glVertex2f(xb, yb);
	glEnd();
	int xa1,ya1;
	xa1 = xb;
	ya1 = yb+40;
	glBegin(GL_TRIANGLES);
		glVertex2f(xa1,ya1);
		glVertex2f(xa1-5,ya1-5);
		glVertex2f(xa1-5,ya1+5);
    glEnd();
	int len, j;
	glRasterPos2f(xa1-assname.size()*wordLength-5, ya1-5);
	len = assname.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, assname[j]);
	}
	glRasterPos2f(xa-startrole.size()*wordLength, ya+10);
	len = startrole.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, startrole[j]);
	}
	glRasterPos2f(xa-startmulti.size()*wordLength, ya-10);
	len = startmulti.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, startmulti[j]);
	}
	glRasterPos2f(xb-15, yb+10);
	len = endmulti.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, endmulti[j]);
	}
	glRasterPos2f(xb+5, yb+10);
	len = endrole.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, endrole[j]);
	}
		if (linkattribute == true)
	{
		int xn,yn;
		xn = x1-20;
		yn = ya-(ya-yb)/2;
		glLineWidth (1.0);
		glEnable(GL_LINE_STIPPLE);
		glLineStipple (1, 0x0F0F);  
		glBegin(GL_LINES);  
        glVertex2f (xn,yn); glVertex2f (xn-20,yn); 
		glEnd();
		glDisable(GL_LINE_STIPPLE);
		int longestname = 0;
		int count = 0;
		string att;
		vector<string>::iterator it = attribute.begin ();
		if((int)attribute.size()!=0)
		{
			while(it!=attribute.end ())
			{
				att = *it; 
				it++;
				if (longestname < att.length())
				longestname = att.length();
				count++;
			}
			int tmpx,tmpy;
			tmpx = xn-20-longestname*wordLength;
			tmpy = yn+4;
			
			it = attribute.begin ();
			while(it!=attribute.end ())
			{
				tmpy = tmpy - wordHeight;
				att = *it; 
				it++;
				len = att.size();
				glRasterPos2f(tmpx,tmpy);
				for (j = 0; j < len; j++) 
				{
					glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, att[j]);
				}
			}
		}

		LinkClassVL(xn-20,yn,longestname,count);
	}
}
void CircumLefttoBottom(int x1, int y1, int l1, int n1, bool linkattribute, string assname, string startrole, string startmulti, string endrole, string endmulti, vector<string>&attribute)
{
	glLineWidth(1);
	int xa,ya,xb,yb;
	xa = x1;
	ya = y1+(n1+1)/2*wordHeight;
	xb = x1+(l1+1)*wordLength/2;
	yb = y1;
	 glBegin(GL_LINES);
        glVertex2f(xa, ya);
		glVertex2f(xa-20, ya);
    glEnd();
	glBegin(GL_LINES);
		glVertex2f(xa-20, ya);
		glVertex2f(xa-20, yb-20);
    glEnd();
	glBegin(GL_LINES);
		glVertex2f(xa-20, yb-20);
		glVertex2f(xb, yb-20);
	glEnd();
	glBegin(GL_LINES);
		glVertex2f(xb, yb-20);
        glVertex2f(xb, yb);
	glEnd();
	int xa1,ya1;
	xa1 = xb;
	ya1 = yb-40;
	glBegin(GL_TRIANGLES);
		glVertex2f(xa1,ya1);
		glVertex2f(xa1-5,ya1-5);
		glVertex2f(xa1-5,ya1+5);
    glEnd();
	int len, j;
	glRasterPos2f(xa1-assname.size()*wordLength-5, ya1-5);
	len = assname.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, assname[j]);
	}
	glRasterPos2f(xa-startrole.size()*wordLength, ya+10);
	len = startrole.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, startrole[j]);
	}
	glRasterPos2f(xa-startmulti.size()*wordLength, ya-10);
	len = startmulti.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, startmulti[j]);
	}
	glRasterPos2f(xb-15, yb-10);
	len = endmulti.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, endmulti[j]);
	}
	glRasterPos2f(xb+5, yb-10);
	len = endrole.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, endrole[j]);
	}
		if (linkattribute == true)
	{
		int xn,yn;
		xn = x1-20;
		yn = ya-(ya-yb)/2;
		glLineWidth (1.0);
		glEnable(GL_LINE_STIPPLE);
		glLineStipple (1, 0x0F0F);  
		glBegin(GL_LINES);  
        glVertex2f (xn,yn); glVertex2f (xn-20,yn); 
		glEnd();
		glDisable(GL_LINE_STIPPLE);
		int longestname = 0;
		int count = 0;
		string att;
		vector<string>::iterator it = attribute.begin ();
		if((int)attribute.size()!=0)
		{
			while(it!=attribute.end ())
			{
				att = *it; 
				it++;
				if (longestname < att.length())
				longestname = att.length();
				count++;
			}
			int tmpx,tmpy;
			tmpx = xn-longestname*wordLength-20;
			tmpy = yn+4;
			
			it = attribute.begin ();
			while(it!=attribute.end ())
			{
				tmpy = tmpy - wordHeight;
				att = *it; 
				it++;
				len = att.size();
				glRasterPos2f(tmpx,tmpy);
				for (j = 0; j < len; j++) 
				{
					glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, att[j]);
				}
			}
		}

		LinkClassVL(xn-20,yn,longestname,count);
	}
}

void QualificationLefttoRight(int x1, int y1, int l1, int n1, int x2, int y2, int l2, int n2, string assname, string startrole, string startmulti, string endrole, string endmulti, vector<string>&qualification)
{
	string qua;
	vector<string>::iterator it = qualification.begin ();
	if((int)qualification.size()!=0)
		{
			while(it!=qualification.end ())
			{
				qua = *it; 
				it++;
			}	
		}
	int l3 = qua.length();
	glLineWidth(1);
	int xa,ya,xb,yb;
	xa = x1+(l1+1)*wordLength;
	ya = y1+(n1+1)/2*wordHeight;
	xb = x2;
	yb = y2+(n2+1)/2*wordHeight;
	glBegin(GL_LINE_LOOP);
		glVertex2f(xa,ya);
		glVertex2f(xa,ya+wordHeight);
		glVertex2f(xa+(l3+2)*wordLength,ya+wordHeight);
		glVertex2f(xa+(l3+2)*wordLength,ya);
	glEnd();
    glBegin(GL_LINES);
        glVertex2f(xa+l3*wordLength, ya);
        glVertex2f(xb, yb);
    glEnd();
	glBegin(GL_TRIANGLES);
		glVertex2f(xb-5-30,yb-5+20);
		glVertex2f(xb-30,yb+20);
		glVertex2f(xb-5-30,yb+5+20);
    glEnd();
	int len,j;
	len = qua.size();
	glRasterPos2f(xa+1,ya+5);
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, qua[j]);
	}
	glRasterPos2f(xb-32-assname.size()*wordLength, yb+17);
	len = assname.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, assname[j]);
	}
	glRasterPos2f(xa+5, ya-15);
	len = startrole.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, startrole[j]);
	}
	glRasterPos2f(xa+5, yb-10);
	len = startmulti.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, startmulti[j]);
	}
	glRasterPos2f(xb-5-endrole.size()*wordLength, yb-15);
	len = endrole.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, endrole[j]);
	}
	glRasterPos2f(xb-endmulti.size()*wordLength, yb-10);
	len = endmulti.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, endmulti[j]);
	}
	glBegin(GL_QUADS);
		glColor3f(1,1,1);
		glVertex2f(xb+1,y2+n2*wordHeight-1);
		glVertex2f(xb+1,y2+n2*wordHeight-wordHeight+1);
		glVertex2f(xb+l2*wordLength,y2+n2*wordHeight-wordHeight+1);
		glVertex2f(xb+l2*wordLength,y2+n2*wordHeight-1);
	glEnd();
	glColor3f(0,0,0);
}
void QualificationLeftfromRight(int x1, int y1, int l1, int n1, int x2, int y2, int l2, int n2, string assname, string startrole, string startmulti, string endrole, string endmulti, vector<string>&qualification)
{
	string qua;
	vector<string>::iterator it = qualification.begin ();
	if((int)qualification.size()!=0)
		{
			while(it!=qualification.end ())
			{
				qua = *it; 
				it++;
			}	
		}
	int l3 = qua.length();
	glLineWidth(1);
	int xa,ya,xb,yb;
	xa = x1+(l1+1)*wordLength;
	ya = y1+(n1+1)/2*wordHeight;
	xb = x2;
	yb = y2+(n2+1)/2*wordHeight;
	glBegin(GL_LINE_LOOP);
		glVertex2f(xb,yb);
		glVertex2f(xb,yb+wordHeight);
		glVertex2f(xb-(l3+2)*wordLength,yb+wordHeight);
		glVertex2f(xb-(l3+2)*wordLength,yb);
	glEnd();
    glBegin(GL_LINES);
        glVertex2f(xa, ya);
        glVertex2f(xb-(l3+2)*wordLength, yb);
    glEnd();
	glBegin(GL_TRIANGLES);
		glVertex2f(xa+30+5,ya-5+20);
		glVertex2f(xa+30,ya+20);
		glVertex2f(xa+30+5,ya+5+20);
    glEnd();
	int len,j;
	len = qua.size();
	glRasterPos2f(xb-(l3+1)*wordLength,yb+5);
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, qua[j]);
	}
	glRasterPos2f(xa+assname.size()*wordLength, ya+17);
	len = assname.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, assname[j]);
	}
	glRasterPos2f(xa+5, ya-20);
	len = startrole.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, startrole[j]);
	}
	glRasterPos2f(xa+5, ya-10);
	len = startmulti.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, startmulti[j]);
	}
	glRasterPos2f(xb-(l3+2)*wordLength-endrole.length()*wordLength, yb-20);
	len = endrole.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, endrole[j]);
	}
	glRasterPos2f(xb-(l3+2)*wordLength-endmulti.length()*wordLength, yb-10);
	len = endmulti.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, endmulti[j]);
	}
	glBegin(GL_QUADS);
		glColor3f(1,1,1);
		glVertex2f(x1+1,y1+n1*wordHeight-1);
		glVertex2f(x1+1,y1+n1*wordHeight-wordHeight+1);
		glVertex2f(x1+l1*wordLength+1,y1+n1*wordHeight-wordHeight+1);
		glVertex2f(x1+l1*wordLength+1,y1+n1*wordHeight-1);
	glEnd();
	glColor3f(0,0,0);
	
}
void QualificationRighttoLeft(int x1, int y1, int l1, int n1, int x2, int y2, int l2, int n2, string assname, string startrole, string startmulti, string endrole, string endmulti, vector<string>&qualification)
{
	string qua;
	vector<string>::iterator it = qualification.begin ();
	if((int)qualification.size()!=0)
		{
			while(it!=qualification.end ())
			{
				qua = *it; 
				it++;
			}	
		}
	int l3 = qua.length()+2;
	glLineWidth(1);
	int xa,ya,xb,yb;
	xa = x1;
	ya = y1+(n1+1)/2*wordHeight;
	xb = x2+(l2+1)*wordLength;
	yb = y2+(n2+1)/2*wordHeight;
	glBegin(GL_LINE_LOOP);
		glVertex2f(xa,ya);
		glVertex2f(xa,ya+wordHeight);
		glVertex2f(xa-l3*wordLength,ya+wordHeight);
		glVertex2f(xa-l3*wordLength,ya);
	glEnd();
    glBegin(GL_LINES);
        glVertex2f(xa, ya);
        glVertex2f(xb, yb);
    glEnd();
	glBegin(GL_TRIANGLES);
		glVertex2f(xb+25,yb-5+20);
		glVertex2f(xb+20,yb+20);
		glVertex2f(xb+25,yb+5+20);
    glEnd();
	int len,j;
	len = qua.size();
	glRasterPos2f(xa-qua.length()*wordLength-5,ya+5);
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, qua[j]);
	}
	glRasterPos2f(xb+30, yb+17);
	len = assname.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, assname[j]);
	}
	glRasterPos2f(xa-l3*wordLength-startrole.length()*wordLength, ya-20);
	len = startrole.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, startrole[j]);
	}
	glRasterPos2f(xa-l3*wordLength-startmulti.length()*wordLength, ya-10);
	len = startmulti.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, startmulti[j]);
	}
	glRasterPos2f(xb+10, yb-20);
	len = endrole.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, endrole[j]);
	}
	glRasterPos2f(xb+10, yb-10);
	len = endmulti.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, endmulti[j]);
	}
	glBegin(GL_QUADS);
		glColor3f(1,1,1);
		glVertex2f(x2+1,y2+n2*wordHeight-1);
		glVertex2f(x2+1,y2+n2*wordHeight-wordHeight+1);
		glVertex2f(x2+l2*wordLength+1,y2+n2*wordHeight-wordHeight+1);
		glVertex2f(x2+l2*wordLength+1,y2+n2*wordHeight-1);
	glEnd();
	glColor3f(0,0,0);
}
void QualificationRightfromLeft(int x1, int y1, int l1, int n1, int x2, int y2, int l2, int n2, string assname, string startrole, string startmulti, string endrole, string endmulti, vector<string>&qualification)
{
	string qua;
	vector<string>::iterator it = qualification.begin ();
	if((int)qualification.size()!=0)
		{
			while(it!=qualification.end ())
			{
				qua = *it; 
				it++;
			}	
		}
	int l3 = qua.length()+2;
	glLineWidth(1);
	int xa,ya,xb,yb;
	xa = x1;
	ya = y1+(n1+1)/2*wordHeight;
	xb = x2+(l2+1)*wordLength;
	yb = y2+(n2+1)/2*wordHeight;
	glBegin(GL_LINE_LOOP);
		glVertex2f(xb,yb);
		glVertex2f(xb,yb+wordHeight);
		glVertex2f(xb+l3*wordLength,yb+wordHeight);
		glVertex2f(xb+l3*wordLength,yb);
	glEnd();
    glBegin(GL_LINES);
        glVertex2f(xa, ya);
        glVertex2f(xb+l3*wordLength, yb);
    glEnd();
	glBegin(GL_TRIANGLES);
		glVertex2f(xb+20+5,yb-5+20);
		glVertex2f(xb+20,yb+20);
		glVertex2f(xb+20+5,yb+5+20);
    glEnd();
	int len,j;
	len = qua.size();
	glRasterPos2f(xb+2,yb+5);
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, qua[j]);
	}
	glRasterPos2f(xb+30, yb+17);
	len = assname.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, assname[j]);
	}
	glRasterPos2f(xa-20-startrole.length(), ya-20);
	len = startrole.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, startrole[j]);
	}
	glRasterPos2f(xa-20-startmulti.length(), ya-10);
	len = startmulti.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, startmulti[j]);
	}
	glRasterPos2f(xb+l3*wordLength+10, yb-20);
	len = endrole.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, endrole[j]);
	}
	glRasterPos2f(xb+l3*wordLength+10, yb-10);
	len = endmulti.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, endmulti[j]);
	}
	glBegin(GL_QUADS);
		glColor3f(1,1,1);
		glVertex2f(x1+1,y1+n1*wordHeight-1);
		glVertex2f(x1+1,y1+n1*wordHeight-wordHeight+1);
		glVertex2f(x1+l1*wordLength+1,y1+n1*wordHeight-wordHeight+1);
		glVertex2f(x1+l1*wordLength+1,y1+n1*wordHeight-1);
	glEnd();
	glColor3f(0,0,0);
	
}
void QualificationToptoBottom(int x1, int y1, int l1, int n1, int x2, int y2, int l2, int n2, string assname, string startrole, string startmulti, string endrole, string endmulti, vector<string>&qualification)
{
	string qua;
	vector<string>::iterator it = qualification.begin ();
	if((int)qualification.size()!=0)
		{
			while(it!=qualification.end ())
			{
				qua = *it; 
				it++;
			}	
		}
	int l3 = qua.length()+2;
	glLineWidth(1);
	int xa,ya,xb,yb;
	xa = x1+(l1+1)*wordLength/2;
	ya = y1;
	xb = x2+(l2+1)*wordLength/2;
	yb = y2+(n2+1)*wordHeight;
	glBegin(GL_LINE_LOOP);
		glVertex2f(xa,ya);
		glVertex2f(xa,ya-wordHeight);
		glVertex2f(xa+l3*wordLength,ya-wordHeight);
		glVertex2f(xa+l3*wordLength,ya);
	glEnd();
    glBegin(GL_LINES);
        glVertex2f(xa, ya-wordHeight);
        glVertex2f(xb, yb);
    glEnd();
		glBegin(GL_TRIANGLES);
		glVertex2f(xb-5-20,yb+5);
		glVertex2f(xb-20,yb);
		glVertex2f(xb+5-20,yb+5);
    glEnd();
	int len,j;
	len = qua.size();
	glRasterPos2f(xa+1,ya-7);
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, qua[j]);
	}
	glRasterPos2f(xb-assname.size()*wordLength, yb+17);
	len = assname.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, assname[j]);
	}
	glRasterPos2f(xa+5, ya-30);
	len = startrole.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, startrole[j]);
	}
	glRasterPos2f(xa+5, ya-20);
	len = startmulti.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, startmulti[j]);
	}
	glRasterPos2f(xb, yb+30);
	len = endrole.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, endrole[j]);
	}
	glRasterPos2f(xb, yb+20);
	len = endmulti.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, endmulti[j]);
	}
	glBegin(GL_QUADS);
		glColor3f(1,1,1);
		glVertex2f(x2+1,y2+n2*wordHeight-1);
		glVertex2f(x2+1,y2+n2*wordHeight-wordHeight+1);
		glVertex2f(x2+l2*wordLength+1,y2+n2*wordHeight-wordHeight+1);
		glVertex2f(x2+l2*wordLength+1,y2+n2*wordHeight-1);
	glEnd();
	glColor3f(0,0,0);
}
void QualificationTopfromBottom(int x1, int y1, int l1, int n1, int x2, int y2, int l2, int n2, string assname, string startrole, string startmulti, string endrole, string endmulti, vector<string>&qualification)
{
	string qua;
	vector<string>::iterator it = qualification.begin ();
	if((int)qualification.size()!=0)
		{
			while(it!=qualification.end ())
			{
				qua = *it; 
				it++;
			}	
		}
	int l3 = qua.length();
	glLineWidth(1);
	int xa,ya,xb,yb;
	xa = x1+(l1+1)*wordLength/2;
	ya = y1;
	xb = x2+(l2+1)*wordLength/2;
	yb = y2+(n2+1)*wordHeight;
	glBegin(GL_LINE_LOOP);
		glVertex2f(xb,yb);
		glVertex2f(xb,yb+wordHeight);
		glVertex2f(xb+(l3+2)*wordLength,yb+wordHeight);
		glVertex2f(xb+(l3+2)*wordLength,yb);
	glEnd();
    glBegin(GL_LINES);
        glVertex2f(xa, ya);
        glVertex2f(xb+(l3+2)*wordLength, yb+wordHeight);
    glEnd();
	glBegin(GL_TRIANGLES);
		glVertex2f(xb-5-20,yb+10);
		glVertex2f(xb-20,yb+5);
		glVertex2f(xb+5-20,yb+10);
    glEnd();
	int len,j;
	len = qua.size();
	glRasterPos2f(xb+1,yb+5);
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, qua[j]);
	}
	glRasterPos2f(xb-assname.size()*wordLength, yb+17);
	len = assname.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, assname[j]);
	}
	glRasterPos2f(xa+5, ya-20);
	len = startrole.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, startrole[j]);
	}
	glRasterPos2f(xa+5, ya-10);
	len = startmulti.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, startmulti[j]);
	}
	glRasterPos2f(xb, yb+30);
	len = endrole.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, endrole[j]);
	}
	glRasterPos2f(xb, yb+20);
	len = endmulti.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, endmulti[j]);
	}
	glBegin(GL_QUADS);
		glColor3f(1,1,1);
		glVertex2f(x1+1,y1+n1*wordHeight-1);
		glVertex2f(x1+1,y1+n1*wordHeight-wordHeight+1);
		glVertex2f(x1+l1*wordLength+1,y1+n1*wordHeight-wordHeight+1);
		glVertex2f(x1+l1*wordLength+1,y1+n1*wordHeight-1);
	glEnd();
	glColor3f(0,0,0);
	
}
void QualificationBottomtoTop(int x1, int y1, int l1, int n1, int x2, int y2, int l2, int n2, string assname, string startrole, string startmulti, string endrole, string endmulti, vector<string>&qualification)
{
	string qua;
	vector<string>::iterator it = qualification.begin ();
	if((int)qualification.size()!=0)
		{
			while(it!=qualification.end ())
			{
				qua = *it; 
				it++;
			}	
		}
	int l3 = qua.length()+2;
	glLineWidth(1);
	int xa,ya,xb,yb;
	xa = x1+(l1+1)*wordLength/2;
	ya = y1+(n1+1)*wordHeight;
	xb = x2+(l2+1)*wordLength/2;
	yb = y2;
	glBegin(GL_LINE_LOOP);
		glVertex2f(xa,ya);
		glVertex2f(xa,ya+wordHeight);
		glVertex2f(xa+l3*wordLength,ya+wordHeight);
		glVertex2f(xa+l3*wordLength,ya);
	glEnd();
    glBegin(GL_LINES);
        glVertex2f(xa+l3*wordLength,ya+wordHeight);
        glVertex2f(xb, yb);
    glEnd();
	glBegin(GL_TRIANGLES);
		glVertex2f(x2-5,yb-5);
		glVertex2f(x2,yb);
		glVertex2f(x2+5,yb-5);
    glEnd();
	int len,j;
	len = qua.size();
	glRasterPos2f(xa+1,ya+5);
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, qua[j]);
	}
	glRasterPos2f(x2-assname.length()*wordLength/2 , yb-15);
	len = assname.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, assname[j]);
	}
	glRasterPos2f(xa+5, ya+30);
	len = startrole.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, startrole[j]);
	}
	glRasterPos2f(xa+5, ya+20);
	len = startmulti.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, startmulti[j]);
	}
	glRasterPos2f(xb, yb-30);
	len = endrole.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, endrole[j]);
	}
	glRasterPos2f(xb, yb-20);
	len = endmulti.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, endmulti[j]);
	}
	glBegin(GL_QUADS);
		glColor3f(1,1,1);
		glVertex2f(x2+1,y2+n2*wordHeight-1);
		glVertex2f(x2+1,y2+n2*wordHeight-wordHeight+1);
		glVertex2f(x2+l2*wordLength+1,y2+n2*wordHeight-wordHeight+1);
		glVertex2f(x2+l2*wordLength+1,y2+n2*wordHeight-1);
	glEnd();
	glColor3f(0,0,0);
}
void QualificationBottomfromTop(int x1, int y1, int l1, int n1, int x2, int y2, int l2, int n2, string assname, string startrole, string startmulti, string endrole, string endmulti, vector<string>&qualification)
{
	string qua;
	vector<string>::iterator it = qualification.begin ();
	if((int)qualification.size()!=0)
		{
			while(it!=qualification.end ())
			{
				qua = *it; 
				it++;
			}	
		}
	int l3 = qua.length()+2;
	glLineWidth(1);
	int xa,ya,xb,yb;
	xa = x1+(l1+1)*wordLength/2;
	ya = y1+(n1+1)*wordHeight;
	xb = x2+(l2+1)*wordLength/2;
	yb = y2;
	glBegin(GL_LINE_LOOP);
		glVertex2f(xb,yb);
		glVertex2f(xb,yb-wordHeight);
		glVertex2f(xb+l3*wordLength,yb-wordHeight);
		glVertex2f(xb+l3*wordLength,yb);
	glEnd();
    glBegin(GL_LINES);
        glVertex2f(xa, ya);
        glVertex2f(xb, yb-wordHeight);
    glEnd();
		glBegin(GL_TRIANGLES);
		glVertex2f(x2-5,yb-5);
		glVertex2f(x2,yb);
		glVertex2f(x2+5,yb-5);
    glEnd();
	int len,j;
	len = qua.size();
	glRasterPos2f(xb+1,yb-7);
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, qua[j]);
	}
	glRasterPos2f(x2-assname.length()*wordLength/2 , yb-15);
	len = assname.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, assname[j]);
	}
	glRasterPos2f(xa+5, ya+30);
	len = startrole.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, startrole[j]);
	}
	glRasterPos2f(xa+5, ya+20);
	len = startmulti.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, startmulti[j]);
	}
	glRasterPos2f(xb, yb-30);
	len = endrole.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, endrole[j]);
	}
	glRasterPos2f(xb, yb-20);
	len = endmulti.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, endmulti[j]);
	}
	glBegin(GL_QUADS);
		glColor3f(1,1,1);
		glVertex2f(x1+1,y1+n1*wordHeight-1);
		glVertex2f(x1+1,y1+n1*wordHeight-wordHeight+1);
		glVertex2f(x1+l1*wordLength+1,y1+n1*wordHeight-wordHeight+1);
		glVertex2f(x1+l1*wordLength+1,y1+n1*wordHeight-1);
	glEnd();
	glColor3f(0,0,0);
}

void AssociationLefttoRight(int x1, int y1, int l1, int n1, int x2, int y2, int l2, int n2, string assname, string startrole, string startmulti, string endrole, string endmulti, string classname, bool qualification,vector<string>&qua)
{
	glLineWidth(1);
	int xa,ya,xb,yb;
	xa = x1+(l1+1)*wordLength;
	ya = y1+(n1+1)/2*wordHeight;
	xb = x2;
	yb = y2+(n2+1)/2*wordHeight;
    glBegin(GL_LINES);
        glVertex2f(xa, ya);
        glVertex2f(xb, yb);
    glEnd();
	glBegin(GL_TRIANGLES);
		glVertex2f(xb-5,yb-5+20);
		glVertex2f(xb,yb+20);
		glVertex2f(xb-5,yb+5+20);
    glEnd();
	int len, j;
	glRasterPos2f(xb-30-assname.size()*wordLength, yb+15);
	len = assname.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, assname[j]);
	}
	glRasterPos2f(xa+5, ya+10);
	len = startrole.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, startrole[j]);
	}
	glRasterPos2f(xa+5, yb-10);
	len = startmulti.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, startmulti[j]);
	}
	glRasterPos2f(xb-5-endrole.size()*wordLength, yb+10);
	len = endrole.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, endrole[j]);
	}
	glRasterPos2f(xb-endmulti.size()*wordLength, yb-10);
	len = endmulti.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, endmulti[j]);
	}
	int tmplong = longest(classname);
	int tmpnum = attnum(classname);
	int xn,yn,xn1,yn1;
	xn = xb-(xb-xa)/2;
	yn = ya+(ya-yb)/2;
	int record;
	int count = 0;
		for(int c=0;c<10;c++)
			{
				if(tmpString[c] == classname)
				{
					count = 1;
					record = c;
					break;
				}
				if(tmpString[c]==(""))
				{
					if (count != 1)
					{
						tmpString[c] = classname;
						record = c;
						break;
					}
				}
			}
			if (count == 1)
			{
				int xa,ya;
				xa = tclass->x[record];
				ya = tclass->y[record];
				glLineWidth (1.0);
				glEnable(GL_LINE_STIPPLE);
				glLineStipple (1, 0x0F0F);  
				glBegin(GL_LINES);
				glVertex2f (xn,yn); glVertex2f (xa,ya);
				glEnd();
				glDisable(GL_LINE_STIPPLE);
			}
			else {
				xn1 = xn - (tmplong*wordLength)/2;
				yn1 = yn-20-(tmpnum+1)*wordHeight;
				tclass->x[record] = xn1;
				tclass->y[record] = yn1;
				tclass->w [record] = tmplong;
				tclass->l [record] = tmpnum;
				tclass->right [record] = 0;
				tclass->down [record] = 0;
				tclass->up [record] = 0;
				tclass->left [record] = 0;
				glLineWidth (1.0);
				glEnable(GL_LINE_STIPPLE);
				glLineStipple (1, 0x0F0F);  
				glBegin(GL_LINES);  
				glVertex2f (xn,yn); glVertex2f (xn,yn-20); 
				glEnd();
				glDisable(GL_LINE_STIPPLE);
				LinkClassC(xn,yn-20,tmplong,tmpnum);
				printattributes(classname,xn1,yn1,tmplong,tmpnum);
			}

		
	
		if (qualification == true)
		{
			string quali;
				vector<string>::iterator iq = qua.begin ();
				while(iq!=qua.end())
				{
					quali = *iq;
					iq++;
				}
				int lon = quali.length();
				int num = 1;
				int tmpx = xa+20;
				int tmpy = ya;
			printqua(tmpx,tmpy,lon,num,quali);
			glBegin(GL_QUADS);
			glColor3f(1,1,1);
			glVertex2f(tmpx-wordLength-1,tmpy-wordHeight-20-1);
			glVertex2f(tmpx-wordLength-1,tmpy-2*wordHeight-20+1);
			glVertex2f(tmpx+lon*wordLength+1,tmpy-20-2*wordHeight+1);
			glVertex2f(tmpx+lon*wordLength+1,tmpy-wordHeight-20-1);
			glEnd();
			glColor3f(0,0,0);
		}
}
void AssociationRighttoLeft(int x1, int y1, int l1, int n1, int x2, int y2, int l2, int n2, string assname, string startrole, string startmulti, string endrole, string endmulti, string classname, bool qualification,vector<string>&qua)
{
	glLineWidth(1);
	int xa,ya,xb,yb;
	xa = x1;
	ya = y1+(n1+1)/2*wordHeight;
	xb = x2+(l2+1)*wordLength;
	yb = y2+(n2+1)/2*wordHeight;
    glBegin(GL_LINES);
        glVertex2f(xa, ya);
        glVertex2f(xb, yb);
    glEnd();
	glBegin(GL_TRIANGLES);
		glVertex2f(xb+5,yb-5+20);
		glVertex2f(xb,yb+20);
		glVertex2f(xb+5,yb+5+20);
    glEnd();
	int len, j;
	glRasterPos2f(xb+10, yb+15);
	len = assname.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, assname[j]);
	}
	glRasterPos2f(xa-5-startrole.size()*wordLength, ya+10);
	len = startrole.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, startrole[j]);
	}
	glRasterPos2f(xa-5-startmulti.size()*wordLength, ya-10);
	len = startmulti.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, startmulti[j]);
	}
	glRasterPos2f(xb+5, yb+10);
	len = endrole.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, endrole[j]);
	}
	glRasterPos2f(xb+5, yb-10);
	len = endmulti.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, endmulti[j]);
	}
	int tmplong = longest(classname);
	int tmpnum = attnum(classname);
		int xn,yn,xn1,yn1;
		xn = xb-(xb-xa)/2;
		yn = ya+(ya-yb)/2;
	int record;
	int count = 0;
		for(int c=0;c<10;c++)
			{
				if(tmpString[c] == classname)
				{
					count = 1;
					record = c;
					break;
				}
				if(tmpString[c]==(""))
				{
					if (count != 1)
					{
						tmpString[c] = classname;
						record = c;
						break;
					}
				}
			}
			if (count == 1)
			{
				int xa,ya;
				xa = tclass->x[record];
				ya = tclass->y[record];
				glLineWidth (1.0);
				glEnable(GL_LINE_STIPPLE);
				glLineStipple (1, 0x0F0F);  
				glBegin(GL_LINES);
				glVertex2f (xn,yn); glVertex2f (xa,ya);
				glEnd();
				glDisable(GL_LINE_STIPPLE);
			}
			else {
				xn1 = xn - (tmplong*wordLength)/2;
				yn1 = yn-20-(tmpnum+1)*wordHeight;
				tclass->x[record] = xn1;
				tclass->y[record] = yn1;
				tclass->w [record] = tmplong;
				tclass->l [record] = tmpnum;
				tclass->right [record] = 0;
				tclass->down [record] = 0;
				tclass->up [record] = 0;
				tclass->left [record] = 0;
				glLineWidth (1.0);
				glEnable(GL_LINE_STIPPLE);
				glLineStipple (1, 0x0F0F);  
				glBegin(GL_LINES);  
				glVertex2f (xn,yn); glVertex2f (xn,yn-20); 
				glEnd();
				glDisable(GL_LINE_STIPPLE);
				LinkClassC(xn,yn-20,tmplong,tmpnum);
				printattributes(classname,xn1,yn1,tmplong,tmpnum);
			}
		if (qualification == true)
		{
			string quali;
				vector<string>::iterator iq = qua.begin ();
				while(iq!=qua.end())
				{
					quali = *iq;
					iq++;
				}
				int lon = quali.length();
				int num = 1;
				int tmpx = xb+20;
				int tmpy = ya;
			printqua(tmpx,tmpy,lon,num,quali);
			glBegin(GL_QUADS);
			glColor3f(1,1,1);
			glVertex2f(tmpx-wordLength-1,tmpy-wordHeight-20-1);
			glVertex2f(tmpx-wordLength-1,tmpy-2*wordHeight-20+1);
			glVertex2f(tmpx+lon*wordLength+1,tmpy-20-2*wordHeight+1);
			glVertex2f(tmpx+lon*wordLength+1,tmpy-wordHeight-20-1);
			glEnd();
			glColor3f(0,0,0);
		}
}
void AssociationToptoBottom(int x1, int y1, int l1, int n1, int x2, int y2, int l2, int n2, string assname, string startrole, string startmulti, string endrole, string endmulti, string classname, bool qualification,vector<string>&qua)
{
	glLineWidth(1);
	int xa,ya,xb,yb;
	xa = x1+(l1+1)*wordLength/2;
	ya = y1;
	xb = x2+(l2+1)*wordLength/2;
	yb = y2+(n2+1)*wordHeight;
    glBegin(GL_LINES);
        glVertex2f(xa, ya);
        glVertex2f(xb, yb);
    glEnd();
		glBegin(GL_TRIANGLES);
		glVertex2f(xb-5-20,yb+5);
		glVertex2f(xb-20,yb);
		glVertex2f(xb+5-20,yb+5);
    glEnd();
	int len, j;
	glRasterPos2f(xb-20-assname.size()*wordLength, yb+10);
	len = assname.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, assname[j]);
	}
	glRasterPos2f(xa-5-startrole.size()*wordLength, ya-10);
	len = startrole.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, startrole[j]);
	}
	glRasterPos2f(xa+5, ya-10);
	len = startmulti.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, startmulti[j]);
	}
	glRasterPos2f(xb-5-endrole.size()*wordLength, yb+10);
	len = endrole.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, endrole[j]);
	}
	glRasterPos2f(xb+5, yb+10);
	len = endmulti.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, endmulti[j]);
	}
	int tmplong = longest(classname);
	int tmpnum = attnum(classname);
		int xn,yn,xn1,yn1;
		xn = xb-(xb-xa)/2;
		yn = ya-(ya-yb)/2;
	int record;
	int count = 0;
		for(int c=0;c<10;c++)
			{
				if(tmpString[c] == classname)
				{
					count = 1;
					record = c;
					break;
				}
				if(tmpString[c]==(""))
				{
					if (count != 1)
					{
						tmpString[c] = classname;
						record = c;
						break;
					}
				}
			}
			if (count == 1)
			{
				int xa,ya;
				xa = tclass->x[record];
				ya = tclass->y[record];
				glLineWidth (1.0);
				glEnable(GL_LINE_STIPPLE);
				glLineStipple (1, 0x0F0F);  
				glBegin(GL_LINES);
				glVertex2f (xn,yn); glVertex2f (xa,ya);
				glEnd();
				glDisable(GL_LINE_STIPPLE);
			}
			else {
				xn1 = xn+20 ;
				yn1 = yn-tmpnum*wordHeight;
				tclass->x[record] = xn1;
				tclass->y[record] = yn1;
				tclass->w [record] = tmplong;
				tclass->l [record] = tmpnum;
				tclass->right [record] = 0;
				tclass->down [record] = 0;
				tclass->up [record] = 0;
				tclass->left [record] = 0;
				glLineWidth (1.0);
				glEnable(GL_LINE_STIPPLE);
				glLineStipple (1, 0x0F0F);  
				glBegin(GL_LINES);  
			    glVertex2f (xn,yn); glVertex2f (xn+20,yn); 
				glEnd();
				glDisable(GL_LINE_STIPPLE);
				LinkClassVR(xn+20,yn,tmplong,tmpnum);
				printattributes(classname,xn1,yn1,tmplong,tmpnum);
			}
		if (qualification == true)
		{
			string quali;
				vector<string>::iterator iq = qua.begin ();
				while(iq!=qua.end())
				{
					quali = *iq;
					iq++;
				}
				int lon = quali.length();
				int num = 1;
				int tmpx = xn-lon*wordLength;
				int tmpy = yn;
			printqua(tmpx,tmpy,lon,num,quali);
			glBegin(GL_QUADS);
			glColor3f(1,1,1);
			glVertex2f(tmpx+lon*wordLength+20+1,tmpy-1);
			glVertex2f(tmpx+lon*wordLength+20+1,tmpy-wordHeight+1);
			glVertex2f(tmpx+2*lon*wordLength+20+1,tmpy-wordHeight+1);
			glVertex2f(tmpx+2*lon*wordLength+20+1,tmpy-1);
			glEnd();
			glColor3f(0,0,0);
		}
}
void AssociationBottomtoTop(int x1, int y1, int l1, int n1, int x2, int y2, int l2, int n2, string assname, string startrole, string startmulti, string endrole, string endmulti, string classname, bool qualification,vector<string>&qua)
{
	glLineWidth(1);
	int xa,ya,xb,yb;
	xa = x1+(l1+1)*wordLength/2;
	ya = y1+(n1+1)*wordHeight;
	xb = x2+(l2+1)*wordLength/2;
	yb = y2;
    glBegin(GL_LINES);
        glVertex2f(xa, ya);
        glVertex2f(xb, yb);
    glEnd();
		glBegin(GL_TRIANGLES);
		glVertex2f(xb-5-20,yb-5);
		glVertex2f(xb-20,yb);
		glVertex2f(xb+5-20,yb-5);
    glEnd();
	int len, j;
	glRasterPos2f(xb-20-assname.size()*wordLength, yb-12);
	len = assname.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, assname[j]);
	}
	glRasterPos2f(xa-5-startrole.size()*wordLength, ya+10);
	len = startrole.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, startrole[j]);
	}
	glRasterPos2f(xa+5, ya+10);
	len = startmulti.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, startmulti[j]);
	}
	glRasterPos2f(xb-5-endrole.size()*wordLength, yb-10);
	len = endrole.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, endrole[j]);
	}
	glRasterPos2f(xb+5, yb-10);
	len = endmulti.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, endmulti[j]);
	}
	int tmplong = longest(classname);
	int tmpnum = attnum(classname);
		int xn,yn,xn1,yn1;
		xn = xb-(xb-xa)/2;
		yn = ya-(ya-yb)/2;
	int record;
	int count = 0;
		for(int c=0;c<10;c++)
			{
				if(tmpString[c] == classname)
				{
					count = 1;
					record = c;
					break;
				}
				if(tmpString[c]==(""))
				{
					if (count != 1)
					{
						tmpString[c] = classname;
						record = c;
						break;
					}
				}
			}
			if (count == 1)
			{
				int xa,ya;
				xa = tclass->x[record];
				ya = tclass->y[record];
				glLineWidth (1.0);
				glEnable(GL_LINE_STIPPLE);
				glLineStipple (1, 0x0F0F);  
				glBegin(GL_LINES);
				glVertex2f (xn,yn); glVertex2f (xa,ya);
				glEnd();
				glDisable(GL_LINE_STIPPLE);
			}
			else {
				xn1 = xn+20 ;
				yn1 = yn-tmpnum*wordHeight;
				tclass->x[record] = xn1;
				tclass->y[record] = yn1;
				tclass->w [record] = tmplong;
				tclass->l [record] = tmpnum;
				tclass->right [record] = 0;
				tclass->down [record] = 0;
				tclass->up [record] = 0;
				tclass->left [record] = 0;
				glLineWidth (1.0);
				glEnable(GL_LINE_STIPPLE);
				glLineStipple (1, 0x0F0F);  
				glBegin(GL_LINES);  
				glVertex2f (xn,yn); glVertex2f (xn+20,yn); 
				glEnd();
				glDisable(GL_LINE_STIPPLE);
				LinkClassVR(xn+20,yn,tmplong,tmpnum);
				printattributes(classname,xn1,yn1,tmplong,tmpnum);
			}
		if (qualification == true)
		{
			string quali;
				vector<string>::iterator iq = qua.begin ();
				while(iq!=qua.end())
				{
					quali = *iq;
					iq++;
				}
				int lon = quali.length();
				int num = 1;
				int tmpx = xn-lon*wordLength;
				int tmpy = yn;
			printqua(tmpx,tmpy,lon,num,quali);
			glBegin(GL_QUADS);
			glColor3f(1,1,1);
			glVertex2f(tmpx+lon*wordLength+20+1,tmpy-1);
			glVertex2f(tmpx+lon*wordLength+20+1,tmpy-wordHeight+1);
			glVertex2f(tmpx+2*lon*wordLength+20+1,tmpy-wordHeight+1);
			glVertex2f(tmpx+2*lon*wordLength+20+1,tmpy-1);
			glEnd();
			glColor3f(0,0,0);
		}
}

void GeneralizationLefttoRight(int x1, int y1, int l1, int n1, int x2, int y2, int l2, int n2, string type)
{
	glLineWidth(1);
	int xa,ya,xb,yb;
	xa = x1+(l1+1)*wordLength;
	ya = y1+2*(n1+1)/3*wordHeight;
	xb = x2;
	yb = y2+2*(n2+1)/3*wordHeight;
    glBegin(GL_LINES);
        glVertex2f(xa, ya);
        glVertex2f(xb, yb);
    glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex2f(xb-5,yb-5);
		glVertex2f(xb,yb);
		glVertex2f(xb-5,yb+5);
    glEnd();
	int len, j;
	glRasterPos2f(xa+10, ya-10);
	len = type.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, type[j]);
	}
}
void GeneralizationRighttoLeft(int x1, int y1, int l1, int n1, int x2, int y2, int l2, int n2, string type)
{
	glLineWidth(1);
	int xa,ya,xb,yb;
	xa = x1;
	ya = y1+2*(n1+1)/3*wordHeight;
	xb = x2+(l2+1)*wordLength;
	yb = y2+2*(n2+1)/3*wordHeight;
    glBegin(GL_LINES);
        glVertex2f(xa, ya);
        glVertex2f(xb, yb);
    glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex2f(xb+5,yb-5);
		glVertex2f(xb,yb);
		glVertex2f(xb+5,yb+5);
    glEnd();
	int len, j;
	glRasterPos2f(xa+10, ya-10);
	len = type.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, type[j]);
	}
}
void GeneralizationToptoBottom(int x1, int y1, int l1, int n1, int x2, int y2, int l2, int n2, string type)
{
	glLineWidth(1);
	int xa,ya,xb,yb;
	xa = x1+(l1+1)*wordLength/2;
	ya = y1;
	xb = x2+(l2+1)*wordLength/2;
	yb = y2+(n2+1)*wordHeight;
    glBegin(GL_LINES);
        glVertex2f(xa, ya);
        glVertex2f(xb, yb);
    glEnd();
	glBegin(GL_LINES);
        glVertex2f(xb+5, yb+5);
        glVertex2f(xb, yb);
    glEnd();
		glBegin(GL_LINE_LOOP);
		glVertex2f(xb-5,yb+5);
		glVertex2f(xb,yb);
		glVertex2f(xb+5,yb+5);
    glEnd();
	int len, j;
	glRasterPos2f(xa-type.size()*wordLength, ya-10);
	len = type.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, type[j]);
	}
}
void GeneralizationBottomtoTop(int x1, int y1, int l1, int n1, int x2, int y2, int l2, int n2, string type)
{
	glLineWidth(1);
	int xa,ya,xb,yb;
	xa = x1+(l1+1)*wordLength/2;
	ya = y1+(n1+1)*wordHeight;
	xb = x2+(l2+1)*wordLength/2;
	yb = y2;
    glBegin(GL_LINES);
        glVertex2f(xa, ya);
        glVertex2f(xb, yb);
    glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex2f(xb-5,yb-5);
		glVertex2f(xb,yb);
		glVertex2f(xb+5,yb-5);
    glEnd();
	int len, j;
	glRasterPos2f(xa-type.size()*wordLength, ya+10);
	len = type.size();
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, type[j]);
	}	
}

void Class(int x1, int y1 ,int l, int n)
{
	glLineWidth(1);
	int x2,y2,yn;
	x2 = x1 + (l+1)*wordLength;
	y2 = y1 + (n+1)*wordHeight;
	yn = y1 + n*wordHeight;
	glBegin(GL_LINE_LOOP);
		glVertex2f(x1,y1);
		glVertex2f(x1,y2);
		glVertex2f(x2,y2);
		glVertex2f(x2,y1);
	glEnd();
	glBegin(GL_LINES);
        glVertex2f(x1, yn);
        glVertex2f(x2, yn);
    glEnd();
}

void LinkClassC(int x1, int y1 ,int l, int n)
{
	glLineWidth(1);
	int x2,y2,yn;
	x2 = x1 + (l+1)*wordLength/2;
	x1 = x1 - (l+1)*wordLength/2;
	y2 = y1 - (n+1)*wordHeight;
	yn = y1 - wordHeight;
	glBegin(GL_LINE_LOOP);
		glVertex2f(x1,y1);
		glVertex2f(x1,y2);
		glVertex2f(x2,y2);
		glVertex2f(x2,y1);
	glEnd();
	glBegin(GL_LINES);
        glVertex2f(x1, yn);
        glVertex2f(x2, yn);
    glEnd();	
}

void LinkClassVR(int x1, int y1 ,int l, int n)
{
	glLineWidth(1);
	int x2,y2,yn;
	y2 = y1 - (n+1)*wordHeight/2;
	y1 = y1 + (n+1)*wordHeight/2;
	x2 = x1 + (l+1)*wordLength;
	yn = y1 - wordHeight;
	glBegin(GL_LINE_LOOP);
		glVertex2f(x1,y1);
		glVertex2f(x1,y2);
		glVertex2f(x2,y2);
		glVertex2f(x2,y1);
	glEnd();
	glBegin(GL_LINES);
        glVertex2f(x1, yn);
        glVertex2f(x2, yn);
    glEnd();	
}

void LinkClassVL(int x1, int y1 ,int l, int n)
{
	glLineWidth(1);
	int x2,y2,yn;
	y2 = y1 - (n+1)*wordHeight/2;
	y1 = y1 + (n+1)*wordHeight/2;
	x2 = x1 - (l+1)*wordLength;
	yn = y1 - wordHeight;
	glBegin(GL_LINE_LOOP);
		glVertex2f(x1,y1);
		glVertex2f(x1,y2);
		glVertex2f(x2,y2);
		glVertex2f(x2,y1);
	glEnd();
	glBegin(GL_LINES);
        glVertex2f(x1, yn);
        glVertex2f(x2, yn);
    glEnd();	
}

void myMenu(int value)
{  
    switch(value)
    {
        case 1: 
			{
				save_screenshot("graphic.tga", 1024, 768);
			break;
			}
        case 2:
        {
            exit(1);
            break;
        }
        default: break;
    };
}


void draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0,0,0);
	map<string, Table> tables, associations;
    if (readXML(tables)) {
        map<string, Table>::iterator ite = tables.begin();
		map<string, Table>::iterator aite = associations.begin();
        vector<Attribute> tmpAtt;
		vector<Association> tmpAss, tmpQua;
		vector<Linker>tmpLink;
		vector<Generalisation>tmpGen;
		int noOfAttributes =0;		
		int lestAttributes =0;
		int startrecord = 0;
		int endrecord = 0;
		int attributesnum = 0;
		int gennum=0;
        while (ite != tables.end()) 
		{
			tmpAss = ite->second.getAssociation();
			vector<Association>::iterator asIte = tmpAss.begin();
				string tmpassname;
				string tmpstartclassname;
				string tmpendclassname;
				while(asIte!=tmpAss.end())
				{
					int count=0;
					tmpassname = asIte->nameOfAssociation;
					tmpstartclassname = asIte->startTable.name;
					/*startclass*/
					lestAttributes = asIte->startTable.name.length();
					bool print = false;
					for(int c=0;c<10;c++)
					{
						if(tmpString[c] == tmpstartclassname)
						{
							count = 1;
							startrecord = c;
							break;
						}
						if(tmpString[c]==(""))
						{
							if (count != 1)
							{
								tmpString[c] = tmpstartclassname;
								startrecord = c;
								break;
							}
						}
					}
					if (count == 0)
					{
						lestAttributes =  longest(tmpstartclassname);
						attributesnum = attnum(tmpstartclassname);
						print = true;
						tclass->w [startrecord] = lestAttributes;
						tclass->l [startrecord] = attributesnum;
						tclass->right [startrecord] = 0;
						tclass->down [startrecord] = 0;
						tclass->up [startrecord] = 0;
						tclass->left [startrecord] = 0;
					}	
					else{
						worldX = tclass->x [startrecord];
						worldY = tclass->y [startrecord];
					}
					string startmulticity, startrole;
					startmulticity = asIte->startTable.multiplicity;
					startrole = asIte->startTable.role;
					char tmpm[10] = {0};
					strcpy(tmpm, startmulticity.c_str ());
					for(int i=0; i<10; ++i)
					{
						if(tmpm[i] == '['||tmpm[i] == ']')
							tmpm[i] = ' ';
					}
					startmulticity = tmpm;
					if (print == true)
					{	
						int tmpx,tmpy,tmpw,tmpn;
						worldY = worldY+ 200;
						worldX = worldX+ 200;
						tmpx = worldX ;
						tmpy = worldY;
						tclass->x [startrecord]  = tmpx;
						tclass->y [startrecord]  = tmpy;
						tmpw = tclass->w [startrecord];
						tmpn = tclass->l [startrecord];
						Class(tmpx,tmpy,tmpw,tmpn);
						printattributes(tmpstartclassname,tmpx,tmpy,tmpw,tmpn);
					}
					/*endclass*/	
					tmpendclassname = asIte->anotherTable.name;
					lestAttributes = asIte->anotherTable.name.length();
					count = 0;
					bool print1 = false;
					for(int c=0;c<10;c++)
					{
						if(tmpString[c] == tmpendclassname)
						{
							count = 1;
							endrecord = c;
							break;
						}
						if(tmpString[c]==(""))
						{
							if (count != 1)
								tmpString[c] = tmpendclassname;
								endrecord = c;
								break;
						}
					}
					if (count == 0)
					{
				
						lestAttributes =  longest(tmpendclassname);
						attributesnum = attnum(tmpendclassname);
						print1 = true;
						tclass->w [endrecord] = lestAttributes;
						tclass->l [endrecord] = attributesnum;
						tclass->right [endrecord] = 0;
						tclass->down [endrecord] = 0;
						tclass->up [endrecord] = 0;
						tclass->left [endrecord] = 0;
					}
					else 
						{
							worldX = tclass->x [endrecord];
							worldY = tclass->y [endrecord];
						}
					string endmulticity, endrole;
					endmulticity = asIte->anotherTable.multiplicity;
					endrole = asIte->anotherTable.role;
					char tmpn[10] = {0};
					strcpy(tmpn, endmulticity.c_str ());
					for(int i=0; i<10; ++i)
					{
						if(tmpn[i] == '['||tmpn[i] == ']')
							tmpn[i] = ' ';
					}
					endmulticity = tmpn;
					if (print1 == true)
					{
						if (tclass->right [startrecord] == 0)
						{
							worldX = worldX +150;
						}
						else if (tclass->down [startrecord] == 0)
						{
								worldY = worldY - 100;
						}
						else if (tclass->up [startrecord] == 0)
						{
								worldY = worldY + 100;
						}
						else if  (tclass->left [startrecord] == 0)
						{
								worldX = worldX - 150;
						}
						

						int tmpx,tmpy,tmpw,tmpn;
						tmpx = worldX ;
						tmpy = worldY;
						tclass->x [endrecord]  = tmpx;
						tclass->y [endrecord]  = tmpy;
						tmpw = tclass->w [endrecord];
						tmpn = tclass->l [endrecord];
						Class(tmpx,tmpy,tmpw,tmpn);
						printattributes(tmpendclassname,tmpx,tmpy,tmpw,tmpn);
					}
					vector <string>::iterator ittes = asIte->startTable.qualification.begin();
					vector <string>::iterator itte = asIte->anotherTable.qualification.begin();
				
					tmpLink = ite->second.getLink();
					vector<Linker>::iterator liIte = tmpLink.begin();
					bool tmplink = false;
			
					if(!asIte->link.attributes.empty())
					{
						tmplink = true;
					}
					if((asIte->anotherTable.qualification.empty())&&(asIte->startTable.qualification.empty())&&(asIte->link.nameOfAssociationClass.empty()))
					{
						if (tmpstartclassname == tmpendclassname)
						{
							if ( tclass->right [startrecord] == 0 && tclass->down [startrecord] == 0)
							{
								CircumRighttoBottom(tclass->x [startrecord],tclass->y [startrecord],tclass->w [startrecord],tclass->l [startrecord],tmplink ,tmpassname,startrole,startmulticity,endrole,endmulticity,asIte->link.attributes);			
								tclass->right [startrecord] = 1;
								tclass->down [startrecord] = 1;
							}
						else if  ( tclass->right [startrecord] == 0 && tclass->up [startrecord] == 0)
						{
							CircumRighttoTop(tclass->x [startrecord],tclass->y [startrecord],tclass->w [startrecord],tclass->l [startrecord],tmplink ,tmpassname,startrole,startmulticity,endrole,endmulticity,asIte->link.attributes);
							tclass->right [startrecord] = 1;
							tclass->up [startrecord] = 1;
						}
						else if ( tclass->left [startrecord] == 0 && tclass->up [startrecord] == 0)
						{
							CircumLefttoTop(tclass->x [startrecord],tclass->y [startrecord],tclass->w [startrecord],tclass->l [startrecord],tmplink ,tmpassname,startrole,startmulticity,endrole,endmulticity,asIte->link.attributes);
							tclass->left [startrecord] = 1;
							tclass->up [startrecord] = 1;
						}
						else if ( tclass->left [startrecord] == 0 && tclass->down [startrecord] == 0)
						{
							CircumLefttoBottom(tclass->x [startrecord],tclass->y [startrecord],tclass->w [startrecord],tclass->l [startrecord],tmplink ,tmpassname,startrole,startmulticity,endrole,endmulticity,asIte->link.attributes);
							tclass->left [startrecord] = 1;
							tclass->down [startrecord] = 1;
						}
					}	
					if ((tclass->x [endrecord] - tclass->x [startrecord])>0 )
					{
						if(tclass->right [startrecord] == 0 && tclass->left [endrecord] == 0)
						{
							ArrowLefttoRight(tclass->x [startrecord],tclass->y [startrecord],tclass->w [startrecord],tclass->l [startrecord],tclass->x [endrecord],tclass->y [endrecord],tclass->w [endrecord],tclass->l [endrecord],tmplink ,tmpassname,startrole,startmulticity,endrole,endmulticity,asIte->link.attributes);
							tclass->right [startrecord] = 1;
							tclass->left [endrecord] = 1;
						}
						else if (tclass->right [startrecord] == 1 && tclass->left [endrecord] == 1)
						{
							DoubleArrowLefttoRight(tclass->x [startrecord],tclass->y [startrecord],tclass->w [startrecord],tclass->l [startrecord],tclass->x [endrecord],tclass->y [endrecord],tclass->w [endrecord],tclass->l [endrecord] ,tmpassname,startrole,startmulticity,endrole,endmulticity);
						}
					}
					else if ((tclass->y [endrecord] - tclass->y [startrecord])>0 )
					{
						if(tclass->up [startrecord] == 0 && tclass->down [endrecord] == 0 )
						{
							ArrowBottomtoTop(tclass->x [startrecord],tclass->y [startrecord],tclass->w [startrecord],tclass->l [startrecord],tclass->x [endrecord],tclass->y [endrecord],tclass->w [endrecord],tclass->l [endrecord],tmplink ,tmpassname,startrole,startmulticity,endrole,endmulticity,asIte->link.attributes);
							tclass->up [startrecord] = 1;
							tclass->down [endrecord] = 1;
						}
						else if (tclass->up [startrecord] == 1 && tclass->down [endrecord] == 1 )
						{
							DoubleArrowBottomtoTop(tclass->x [startrecord],tclass->y [startrecord],tclass->w [startrecord],tclass->l [startrecord],tclass->x [endrecord],tclass->y [endrecord],tclass->w [endrecord],tclass->l [endrecord] ,tmpassname,startrole,startmulticity,endrole,endmulticity);
						}
					}
					else if ((tclass->y [endrecord] - tclass->y [startrecord])<0  )
					{
						if(tclass->down [startrecord] == 0 && tclass->up [endrecord] == 0)
						{
							ArrowToptoBottom(tclass->x [startrecord],tclass->y [startrecord],tclass->w [startrecord],tclass->l [startrecord],tclass->x [endrecord],tclass->y [endrecord],tclass->w [endrecord],tclass->l [endrecord],tmplink ,tmpassname,startrole,startmulticity,endrole,endmulticity,asIte->link.attributes);
							tclass->down [startrecord] = 1;
							tclass->up [endrecord] = 1;
						}
						else if (tclass->down [startrecord] == 1 && tclass->up [endrecord] == 1 )
						{
							DoubleArrowToptoBottom(tclass->x [startrecord],tclass->y [startrecord],tclass->w [startrecord],tclass->l [startrecord],tclass->x [endrecord],tclass->y [endrecord],tclass->w [endrecord],tclass->l [endrecord] ,tmpassname,startrole,startmulticity,endrole,endmulticity);
						}
					}
					else if ((tclass->x [endrecord] - tclass->x [startrecord])<0 )
					{
						if(tclass->left [startrecord] == 0 && tclass->right [endrecord] == 0)
						{
							ArrowRighttoLeft(tclass->x [startrecord],tclass->y [startrecord],tclass->w [startrecord],tclass->l [startrecord],tclass->x [endrecord],tclass->y [endrecord],tclass->w [endrecord],tclass->l [endrecord],tmplink ,tmpassname,startrole,startmulticity,endrole,endmulticity,asIte->link.attributes);
							tclass->left [startrecord] = 1;
							tclass->right [endrecord] = 1;
						}
						else if (tclass->left [startrecord] == 1 && tclass->right [endrecord] == 1 )
						{
							DoubleArrowRighttoLeft(tclass->x [startrecord],tclass->y [startrecord],tclass->w [startrecord],tclass->l [startrecord],tclass->x [endrecord],tclass->y [endrecord],tclass->w [endrecord],tclass->l [endrecord] ,tmpassname,startrole,startmulticity,endrole,endmulticity);
						}
					}
				}
				else if(asIte->link.nameOfAssociationClass.empty())
				{		//qualification ono
					if (testprintQstart(tmpendclassname,asIte->startTable.qualification)== true)
					{
						if ((tclass->x [endrecord] - tclass->x [startrecord])>0 )
						{
							if(tclass->right [startrecord] == 0 && tclass->left [endrecord] == 0)
							{	
								QualificationLefttoRight(tclass->x [startrecord],tclass->y [startrecord],tclass->w [startrecord],tclass->l [startrecord],tclass->x [endrecord],tclass->y [endrecord],tclass->w [endrecord],tclass->l [endrecord],tmpassname,startrole,startmulticity,endrole,endmulticity,asIte->startTable.qualification);
								tclass->right [startrecord] = 1;
								tclass->left [endrecord] = 1;
							}
						}
						else if ((tclass->y [endrecord] - tclass->y [startrecord])>0 )
						{
							if(tclass->up [startrecord] == 0 && tclass->down [endrecord] == 0 )
							{
								QualificationBottomtoTop(tclass->x [startrecord],tclass->y [startrecord],tclass->w [startrecord],tclass->l [startrecord],tclass->x [endrecord],tclass->y [endrecord],tclass->w [endrecord],tclass->l [endrecord],tmpassname,startrole,startmulticity,endrole,endmulticity,asIte->startTable.qualification);
								tclass->up [startrecord] = 1;
								tclass->down [endrecord] = 1;
							}		
						}
						else if ((tclass->y [endrecord] - tclass->y [startrecord])<0  )
						{
							if(tclass->down [startrecord] == 0 && tclass->up [endrecord] == 0)
							{
								QualificationToptoBottom(tclass->x [startrecord],tclass->y [startrecord],tclass->w [startrecord],tclass->l [startrecord],tclass->x [endrecord],tclass->y [endrecord],tclass->w [endrecord],tclass->l [endrecord],tmpassname,startrole,startmulticity,endrole,endmulticity,asIte->startTable.qualification);
								tclass->down [startrecord] = 1;
								tclass->up [endrecord] = 1;
							}
						}
						else if ((tclass->x [endrecord] - tclass->x [startrecord])<0 )
						{
							if(tclass->left [startrecord] == 0 && tclass->right [endrecord] == 0)
							{
								QualificationRighttoLeft(tclass->x [startrecord],tclass->y [startrecord],tclass->w [startrecord],tclass->l [startrecord],tclass->x [endrecord],tclass->y [endrecord],tclass->w [endrecord],tclass->l [endrecord],tmpassname,startrole,startmulticity,endrole,endmulticity,asIte->startTable.qualification);
								tclass->left [startrecord] = 1;
								tclass->right [endrecord] = 1;
							}
						}
					}
					else if (testprintQstart(tmpstartclassname,asIte->anotherTable.qualification)== true)
					{
						if ((tclass->x [endrecord] - tclass->x [startrecord])>0 )
						{
							if(tclass->right [startrecord] == 0 && tclass->left [endrecord] == 0)
							{	
								QualificationLeftfromRight(tclass->x [startrecord],tclass->y [startrecord],tclass->w [startrecord],tclass->l [startrecord],tclass->x [endrecord],tclass->y [endrecord],tclass->w [endrecord],tclass->l [endrecord],tmpassname,startrole,startmulticity,endrole,endmulticity,asIte->anotherTable.qualification);
								tclass->right [startrecord] = 1;
								tclass->left [endrecord] = 1;
							}
						}
						else if ((tclass->y [endrecord] - tclass->y [startrecord])>0 )
						{
							if(tclass->up [startrecord] == 0 && tclass->down [endrecord] == 0 )
							{
								QualificationBottomfromTop(tclass->x [startrecord],tclass->y [startrecord],tclass->w [startrecord],tclass->l [startrecord],tclass->x [endrecord],tclass->y [endrecord],tclass->w [endrecord],tclass->l [endrecord],tmpassname,startrole,startmulticity,endrole,endmulticity,asIte->anotherTable.qualification);
								tclass->up [startrecord] = 1;
								tclass->down [endrecord] = 1;
							}		
						}
						else if ((tclass->y [endrecord] - tclass->y [startrecord])<0  )
						{
							if(tclass->down [startrecord] == 0 && tclass->up [endrecord] == 0)
							{
								QualificationTopfromBottom(tclass->x [startrecord],tclass->y [startrecord],tclass->w [startrecord],tclass->l [startrecord],tclass->x [endrecord],tclass->y [endrecord],tclass->w [endrecord],tclass->l [endrecord],tmpassname,startrole,startmulticity,endrole,endmulticity,asIte->anotherTable.qualification);	
								tclass->down [startrecord] = 1;
								tclass->up [endrecord] = 1;
							}
						}
						else if ((tclass->x [endrecord] - tclass->x [startrecord])<0 )
						{
							if(tclass->left [startrecord] == 0 && tclass->right [endrecord] == 0)
							{
								QualificationRightfromLeft(tclass->x [startrecord],tclass->y [startrecord],tclass->w [startrecord],tclass->l [startrecord],tclass->x [endrecord],tclass->y [endrecord],tclass->w [endrecord],tclass->l [endrecord],tmpassname,startrole,startmulticity,endrole,endmulticity,asIte->anotherTable.qualification);
								tclass->left [startrecord] = 1;
								tclass->right [endrecord] = 1;
							}
						}
					}
				}

				else
				{	//(repeatable)  association class
					string assclassname;
					bool qual;
					assclassname = asIte->link .nameOfAssociationClass;
					if(!asIte->link.qualification.empty())
					{
						qual = true;
					}
					else {
						qual = false;
					}
					if ((tclass->x [endrecord] - tclass->x [startrecord])>0 )
					{
						if(tclass->right [startrecord] == 0 && tclass->left [endrecord] == 0)
						{	
							AssociationLefttoRight(tclass->x [startrecord],tclass->y [startrecord],tclass->w [startrecord],tclass->l [startrecord],tclass->x [endrecord],tclass->y [endrecord],tclass->w [endrecord],tclass->l [endrecord],tmpassname,startrole,startmulticity,endrole,endmulticity,assclassname, qual,asIte->link.qualification);
							tclass->right [startrecord] = 1;
							tclass->left [endrecord] = 1;
						}
					}
					else if ((tclass->y [endrecord] - tclass->y [startrecord])>0 )
					{
						if(tclass->up [startrecord] == 0 && tclass->down [endrecord] == 0 )
						{
							AssociationBottomtoTop(tclass->x [startrecord],tclass->y [startrecord],tclass->w [startrecord],tclass->l [startrecord],tclass->x [endrecord],tclass->y [endrecord],tclass->w [endrecord],tclass->l [endrecord],tmpassname,startrole,startmulticity,endrole,endmulticity,assclassname, qual,asIte->link.qualification);
							tclass->up [startrecord] = 1;
							tclass->down [endrecord] = 1;
						}
						
					}
					else if ((tclass->y [endrecord] - tclass->y [startrecord])<0  )
					{
						if(tclass->down [startrecord] == 0 && tclass->up [endrecord] == 0)
						{
							AssociationToptoBottom(tclass->x [startrecord],tclass->y [startrecord],tclass->w [startrecord],tclass->l [startrecord],tclass->x [endrecord],tclass->y [endrecord],tclass->w [endrecord],tclass->l [endrecord],tmpassname,startrole,startmulticity,endrole,endmulticity,assclassname, qual,asIte->link.qualification);
							tclass->down [startrecord] = 1;
							tclass->up [endrecord] = 1;
						}
					}
					else if ((tclass->x [endrecord] - tclass->x [startrecord])<0 )
					{
						if(tclass->left [startrecord] == 0 && tclass->right [endrecord] == 0)
						{
							AssociationRighttoLeft(tclass->x [startrecord],tclass->y [startrecord],tclass->w [startrecord],tclass->l [startrecord],tclass->x [endrecord],tclass->y [endrecord],tclass->w [endrecord],tclass->l [endrecord],tmpassname,startrole,startmulticity,endrole,endmulticity,assclassname, qual,asIte->link.qualification);
							tclass->left [startrecord] = 1;
							tclass->right [endrecord] = 1;
						}
					}
				}
				asIte++;				
			}

			tmpGen = ite->second.getGeneralisation();
			vector<Generalisation>::iterator genIte = tmpGen.begin();

			int genp, genc;
			string type, parentclassname, childclassname; 
			int countp =0;
			int countc = 0;

			while(genIte!=tmpGen.end())
			{
				bool printp= false;
				bool printc= false;
				parentclassname = genIte->ISA;
				childclassname = genIte->className;
				type = genIte->type;
				genIte++;
				gennum= gennum+1;
				for(int c=0;c<10;c++)
				{
					if(tmpString[c] == parentclassname)
					{
						countp = 1;
						genp = c;
						break;
					}
					if(tmpString[c]==(""))
					{
						if (countp != 1)
						{
						tmpString[c] = parentclassname;
						genp = c;
						break;
						}
					}
				}
				for(int c=0;c<10;c++)
				{
					if(tmpString[c] == childclassname)
					{
						countc = 1;
						genc = c;
						break;
					}
					if(tmpString[c]==(""))
					{
						if (countc != 1)
						{
						tmpString[c] = childclassname;
						genc = c;
						break;
						}
					}
				}
				/*print parent class*/
					if (countp == 0)
					{
						lestAttributes =  longest(parentclassname);
						attributesnum = attnum(parentclassname);
						printp = true;
						tclass->w [genp] = lestAttributes;
						tclass->l [genp] = attributesnum;
						tclass->right [genp] = 0;
						tclass->down [genp] = 0;
						tclass->up [genp] = 0;
						tclass->left [genp] = 0;
					}	
					else{
						worldX = tclass->x [genp];
						worldY = tclass->y [genp];
					}
					if (printp == true)
					{	
						int tmpx,tmpy,tmpw,tmpn;
						worldY = worldY+ 200;
						worldX = worldX+ 200;
						tmpx = worldX ;
						tmpy = worldY;
						tclass->x [genp]  = tmpx;
						tclass->y [genp]  = tmpy;
						tmpw = tclass->w [genp];
						tmpn = tclass->l [genp];
						Class(tmpx,tmpy,tmpw,tmpn);
						printattributes(parentclassname,tmpx,tmpy,tmpw,tmpn);
					}
					/*print child class*/
					if (countc == 0)
					{
						lestAttributes =  longest(childclassname);
						attributesnum = attnum(childclassname);
						printc = true;
						tclass->w [genc] = lestAttributes;
						tclass->l [genc] = attributesnum;
						tclass->right [genc] = 0;
						tclass->down [genc] = 0;
						tclass->up [genc] = 0;
						tclass->left [genc] = 0;
					}	
					else{
						worldX = tclass->x [genc];
						worldY = tclass->y [genc];
					}
					if (printc == true)
					{	
						int tmpx,tmpy,tmpw,tmpn;

						if(tclass->down [genp] == 2)
						{
							worldY = worldY-100;
							worldX = worldX+50*(gennum-2);
							tclass->down [genp] =2;
						}
						else if(tclass->up [genp] == 2)
						{
							worldY = worldY+100;
							worldX = worldX+50*(gennum-2);
							tclass->up [genp] =2;
						}
						else if(tclass->right [genp] == 2)
						{
							worldY = worldY+50*(gennum-2);
							worldX = worldX+100;
							tclass->right [genp] = 2;
						}
						else if(tclass->left [genp] == 2  )
						{
							worldY = worldY+50*(gennum-2);
							worldX = worldX-100;
							tclass->left [genp] =2;
						}
						else if(tclass->down [genp] == 0||tclass->down [genp] == 2)
						{
							worldY = worldY-100;
							worldX = worldX+50*(gennum-2);
							tclass->down [genp] =2;
						}
						else if(tclass->up [genp] == 0||tclass->up [genp] == 2)
						{
							worldY = worldY+100;
							worldX = worldX+50*(gennum-2);
							tclass->up [genp] =2;
						}
						else if(tclass->right [genp] == 0||tclass->right [genp] == 2)
						{
							worldY = worldY+50*(gennum-2);
							worldX = worldX+100;
							tclass->right [genp] = 2;
						}
						else if(tclass->left [genp] == 0 ||tclass->left [genp] == 2  )
						{
							worldY = worldY+50*(gennum-2);
							worldX = worldX-100;
							tclass->left [genp] =2;
						}
						tmpx = worldX ;
						tmpy = worldY;
						tclass->x [genc]  = tmpx;
						tclass->y [genc]  = tmpy;
						tmpw = tclass->w [genc];
						tmpn = tclass->l [genc];
						Class(tmpx,tmpy,tmpw,tmpn);
						printattributes(childclassname,tmpx,tmpy,tmpw,tmpn);
					}

					if ((tclass->y [genp] - tclass->y [genc])>0 )
					{
						{
							GeneralizationBottomtoTop(tclass->x [genc],tclass->y [genc],tclass->w [genc],tclass->l [genc],tclass->x [genp],tclass->y [genp],tclass->w [genp],tclass->l [genp],type);
							tclass->up [genc] = 1;
							tclass->down [genp] = 1;
						}
					}
					else if ((tclass->y [genp] - tclass->y [genc])<0  )
					{
						{
							GeneralizationToptoBottom(tclass->x [genc],tclass->y [genc],tclass->w [genc],tclass->l [genc],tclass->x [genp],tclass->y [genp],tclass->w [genp],tclass->l [genp],type);
							tclass->down [genc] = 1;
							tclass->up [genp] = 1;
						}
					}
					else if ((tclass->x [genp] - tclass->x [genc])<0 )
					{
						{
							GeneralizationRighttoLeft(tclass->x [genc],tclass->y [genc],tclass->w [genc],tclass->l [genc],tclass->x [genp],tclass->y [genp],tclass->w [genp],tclass->l [genp],type);
							tclass->left [genc] = 1;
							tclass->right [genp] = 1;
						}
					}
					else if ((tclass->x [genp] - tclass->x [genc])>0 )
					{
						{
							GeneralizationLefttoRight(tclass->x [genc],tclass->y [genc],tclass->w [genc],tclass->l [genc],tclass->x [genp],tclass->y [genp],tclass->w [genp],tclass->l [genp],type);
							tclass->right [genc] = 1;
							tclass->left [genp] = 1;
						}
					}
			}



			
			tmpAtt.clear();
			tmpAss.clear();
			tmpGen.clear ();
            ite++;
		}
		map<string, Table>::iterator it = tables.begin ();
		map<string, Table>::iterator it2 = tables.begin ();
		vector<Attribute> tmpA;
		vector<string> str;
		string tmpname[10];
		bool same = false;
		bool same1 = false;
		string name;
		int a = 0;
		while(it!=tables.end ())
		{
			str.push_back (it->second .getTableName ());
			for (int m = 0; m<10; m++ )
			{
			name = tmpString[m];
			if(it->second .getTableName () == name)
			{
				same1 = true;
			}
			}
			if (same1 == false)
			{
				tmpname[a] = it->second .getTableName();
				same = true;
				it2 = it;
				a++;
			}
			it++;
		}
		if(same == true)
		{	
			for (int m = 0; m<a; m++ )
			{
				string name = tmpname[m];
				worldX = worldX+200;
				worldY = worldY+100;
				int tmpx = worldX;
				int tmpy = worldY;
				lestAttributes =  longest(name);
				attributesnum = attnum(name);
				Class(tmpx,tmpy,lestAttributes,attributesnum);
				printattributes(name,tmpx,tmpy,lestAttributes,attributesnum);
			}
		
		}
    }
	glFlush();
	worldX = 0;
	worldY = 0;
	for (int m = 0; m<10; m++ )
	{
		tmpString[m].clear();
	}
	save_screenshot("graphic.tga", 1024, 768);
}


bool readXML(map<string, Table>& tables) {
    TiXmlDocument *myDoc = new TiXmlDocument("information.xml");

    if (!myDoc->LoadFile()) {
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
                        if (strcmp(thirdNode->Value(), "link_attribute") == 0 && thirdNode->FirstChild() != 0) 
						{          
							TiXmlNode* tempNode = thirdNode->FirstChild();
								for (; tempNode; tempNode = tempNode->NextSibling()) {
									tmpLink.attributes.push_back(tempNode->FirstChild()->Value());
								}
                        } else if(strcmp(thirdNode->Value(), "association_class") == 0 
							&& thirdNode->FirstChild() != 0) {
                            TiXmlNode* forthNode = thirdNode->FirstChild();
							for (; forthNode; forthNode = forthNode->NextSibling())
							{
								if (strcmp(forthNode->Value(), "qualification") == 0) {
									if (strlen(forthNode->FirstChild()->Value()) > 0) {
										if (forthNode->FirstChild() != 0)
											tmpLink.qualification.push_back(forthNode->FirstChild()
												->Value());
									}
								} else if (strcmp(forthNode->Value(), "nameOfAssociationClass") == 0) 
								{
									if (strlen(forthNode->FirstChild()->Value()) > 0) {
										if (forthNode->FirstChild() != 0)
											tmpLink.nameOfAssociationClass = forthNode->FirstChild()->Value();
									}
                                }
                            } 
                         }
                    }
					if(tmpLink.attributes.size() != 0 ||
						tmpLink.nameOfAssociationClass.size() != 0 ||
						tmpLink.qualification.size() != 0){
                    tmpAssociation.link = tmpLink;
					}
                }

            }
            map<string, Table>::iterator tableIte = tables.find(tmpAssociation.
                    startTable.name);
            if (tableIte != tables.end()) {
                tableIte->second.setAssociation(tmpAssociation);
            } else {
                cerr << "There is no table in this database.";
            }
        } else if (strcmp(firstNode->Value(), "generlisation") == 0) {
            TiXmlNode* secondNode = firstNode->FirstChild();
            Generalisation tmpGeneralisation;
			vector<string> tempclass;
            for (; secondNode; secondNode = secondNode->NextSibling()) {
                if (strcmp(secondNode->Value(), "class_name") == 0) {
                    if (secondNode->FirstChild() != 0)
                        tempclass.push_back ( secondNode->FirstChild()->Value());
                } else if (strcmp(secondNode->Value(), "ISA") == 0) {
                    if (secondNode->FirstChild() != 0)
                        tmpGeneralisation.ISA = secondNode->FirstChild()->Value();
                } else if (strcmp(secondNode->Value(), "generalisation") == 0) {
                    if (secondNode->FirstChild() != 0)
                        tmpGeneralisation.type = secondNode->FirstChild()->Value();
                }
            }
			vector<string>::iterator ic = tempclass.begin ();
			while(ic != tempclass.end ())
			{
				tmpGeneralisation.className = *ic;
				map<string, Table>::iterator tableIte = tables.find(tmpGeneralisation.className);
				if (tableIte != tables.end())
				{
					tableIte->second.setGeneralisation(tmpGeneralisation);
				} 
				else {
		            cerr << "There is no table in this database.";
			    }
				ic++;
			}
		}
    }
    return true;
}

bool testprintQstart(string& classname,vector<string>&q)
{
	vector<string>::iterator it = q.begin ();
	if((int)q.size()!=0)
	{
		while(it!=q.end ())
		{
				string qualification;
				qualification = *it;
				if(attcompare(classname,qualification)==true)
				{
					return true;
					break;
				}
			it++;
		}
	}
	return false;
}


int quanum(vector<string>& q)
{
	int count=0;
	vector<string>::iterator iq = q.begin ();
		while(iq!=q.end())
		{
			count++;
			iq++;
		}
		return count;
}


void printqua(int x, int y, int l,int n, string q)
{
	glRasterPos2f(x, y);
	glBegin(GL_LINE_LOOP);
		glVertex2f(x,y);
		glVertex2f(x,y+wordHeight);
		glVertex2f(x+l*wordLength,y+wordHeight);
		glVertex2f(x+l*wordLength,y);
	glEnd();
	glRasterPos2f(x+2, y+5);
	int len = q.size();
	int j;
	for (j = 0; j < len; j++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, q[j]);
	}
}



void printattributes(string& name, int tmpx, int tmpy, int tmpw, int tmpn)
{
	map<string, Table> tmp;
    readXML(tmp);
	map<string, Table>::iterator it = tmp.begin ();
	map<string, Table>::iterator it2 = tmp.begin ();
	vector<Attribute> tmpA;
	vector<string> str;
	bool same = false;
	while(it!=tmp.end ())
	{
		str.push_back (it->second .getTableName ());
		if(it->second .getTableName () == name)
		{
			same = true;
			it2 = it;
		}
		it++;
	}
	if(same == true)
	{	
		tmpx = tmpx+5;
		tmpy = tmpy+tmpn*wordHeight+4;
		glRasterPos2f(tmpx, tmpy);
		int len;
		len = name.size();
		int j;
		for (j = 0; j < len; j++) 
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, name[j]);
		}
		tmpA= it2->second .getAttribute ();
		vector<Attribute>::iterator ita = tmpA.begin ();
		int longestname = name.length();
		int count = 0;
		if(it2->second .getAttribute ().size() !=0)
		{
			while(ita!=tmpA.end ())
			{
				int lestAttributes = 0;
				lestAttributes = ita->name.length()+ita->multiplicity.length()+ita->id.length()+3;
				if(lestAttributes>longestname)
				longestname = lestAttributes;	
				ita++;
				count++;
			}
			ita = tmpA.begin();
			while(ita!=tmpA.end ())
			{
				string tmpAttribute;
				tmpAttribute = ita->name + " " + ita->multiplicity + "  " + ita->id; 
				tmpy = tmpy - wordHeight;
				glRasterPos2f(tmpx, tmpy);
				len = tmpAttribute.size();
				int j;
				for (j = 0; j < len; j++) 
				{
					glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, tmpAttribute[j]);
				}
				ita++;
			}
		}
	}
}


int longest(string& name)
{
	map<string, Table> tmp;
    readXML(tmp);
	map<string, Table>::iterator it = tmp.begin ();
	map<string, Table>::iterator it2 = tmp.begin ();
	vector<Attribute> tmpA;
	vector<string> str;
	bool same = false;
	while(it!=tmp.end ())
	{
		str.push_back (it->second .getTableName ());
		if(it->second .getTableName () == name)
		{
			same = true;
			it2 = it;
		}
		it++;
	}
	if(same == true)
	{				
		tmpA= it2->second .getAttribute ();
		vector<Attribute>::iterator ita = tmpA.begin ();
		int longestname = name.length();
		if(it2->second .getAttribute ().size() !=0)
		{
			while(ita!=tmpA.end ())
			{
				int lestAttributes = 0;
				lestAttributes = ita->name.length()+ita->multiplicity.length()+ita->id.length()+3;
				if(lestAttributes>longestname)
				longestname = lestAttributes;	
				ita++;
			}
		}
		return longestname;
	}
	return 0;
}


int attnum(string& name)
{
	map<string, Table> tmp;
    readXML(tmp);
	map<string, Table>::iterator it = tmp.begin ();
	map<string, Table>::iterator it2 = tmp.begin ();
	vector<Attribute> tmpA;
	vector<string> str;
	bool same = false;
	while(it!=tmp.end ())
	{
		str.push_back (it->second .getTableName ());
		if(it->second .getTableName () == name)
		{
			same = true;
			it2 = it;
		}
		it++;
	}
	if(same == true)
	{				
		tmpA= it2->second .getAttribute ();
		vector<Attribute>::iterator ita = tmpA.begin ();
		int count = 0;
		int longestname = name.length();
		if(it2->second .getAttribute ().size() !=0)
		{
			while(ita!=tmpA.end ())
			{
				int lestAttributes = 0;
				lestAttributes = ita->name.length()+ita->multiplicity.length()+ita->id.length()+3;
				if(lestAttributes>longestname)
				longestname = lestAttributes;	
				ita++;
				count++;
			}
		}
		return count;
	}
	return 0;
}

bool attcompare(string& name,string& attributename)
{
	map<string, Table> tmp;
    readXML(tmp);
	map<string, Table>::iterator it = tmp.begin ();
	map<string, Table>::iterator it2 = tmp.begin ();
	vector<Attribute> tmpA;
	vector<string> str;
	bool same = false;
	while(it!=tmp.end ())
	{
		str.push_back (it->second .getTableName ());
		if(it->second .getTableName () == name)
		{
			same = true;
			it2 = it;
		}
		it++;
	}
	if(same == true)
	{				
		tmpA= it2->second .getAttribute ();
		vector<Attribute>::iterator ita = tmpA.begin ();
		int count = 0;
		int longestname = name.length();
		if(it2->second .getAttribute ().size() !=0)
		{
			while(ita!=tmpA.end ())
			{
				string tmpAttribute;
				tmpAttribute = ita->name;
				if (attributename ==  tmpAttribute)
				{
					return true;
					break;
				}
				ita++;
			}
		}
		return false;
	}
	return false;
}

bool save_screenshot(string filename, int w, int h)
{	
  //This prevents the images getting padded 
 // when the width multiplied by 3 is not a multiple of 4
  glPixelStorei(GL_PACK_ALIGNMENT, 1);
 
  int nSize = w*h*3;
  // First let's create our buffer, 3 channels per Pixel
  char* dataBuffer = (char*)malloc(nSize*sizeof(char));
 
  if (!dataBuffer) return false;
 
   // Let's fetch them from the backbuffer	
   // We request the pixels in GL_BGR format, thanks to Berzeger for the tip
   glReadPixels((GLint)0, (GLint)0,
		(GLint)w, (GLint)h,
		 GL_BGR, GL_UNSIGNED_BYTE, dataBuffer);
 
   //Now the file creation
   FILE *filePtr = fopen(filename.c_str(), "wb");
   if (!filePtr) return false;
 
 
   unsigned char TGAheader[12]={0,0,2,0,0,0,0,0,0,0,0,0};
   unsigned char header[6] = { w%256,w/256,
			       h%256,h/256,
			       24,0};
   // We write the headers
   fwrite(TGAheader,	sizeof(unsigned char),	12,	filePtr);
   fwrite(header,	sizeof(unsigned char),	6,	filePtr);
   // And finally our image data
   fwrite(dataBuffer,	sizeof(GLubyte),	nSize,	filePtr);
   fclose(filePtr);
 
  return true;
}

int main(int argc, char** argv) 
{
	glutInitWindowSize(1024, 768);	
    glutInitWindowPosition(0, 0);    
	
    glutCreateWindow("CSCI321");
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); 


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,1024.0,0.0,768.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutDisplayFunc(draw);
    glutCreateMenu(myMenu);
    glutAddMenuEntry("Save", 1);
    glutAddMenuEntry("Quit", 2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMainLoop(); 
	system("pause");
	return 0;
}
