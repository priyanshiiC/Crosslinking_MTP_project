#include<iostream>
#include<fstream>
#include<string>
#include<set>
#include<vector>
#include<math.h>
using namespace std;

// successful in storing to be deleted Cl atoms(in delC) & H atoms (in delH)

struct atom
    {
    int atomNo;  
    int sec;
    int type;
    int charge;
    float x;               //defines a structure of atom
    float y;
    float z;
    string hash;
    string s1;
    string s2;

    };
    struct bond
    {
        int bondNo;
        int type;                //defines a structure of bonds
        int atom1;
        int atom2;

    };
    float dist(struct atom a1, struct atom a2)
{
    float xd, yd, zd;
    xd = a1.x - a2.x;
    yd = a1.y - a2.y;                 // function for checking the distance
    zd = a1.z - a2.z;
    float d;
    d = (xd)*(xd)+(yd)*(yd)+(zd)*(zd);
    return d;
}

int main ()

{
    

    ifstream atomsFile ;
    atomsFile.open ("AfterNPT.txt");            //reading a file atoms.txt that contains the information about the atoms
    string line;
    vector <atom> atoms, atom6 ,atom7 ,atom8 , oldatoms, delCl ,delH;

    while (getline(atomsFile,line))
    {
        
        vector<string> v;
        string s="";
        for(int i=0;i<line.size();i++)
        {
            if(line[i]==' ')                            //storing information of atoms from text in a structure    
            {
                v.push_back(s);
                s="";
            }
            else
            {
                s+=line[i];
            }
        }
        v.push_back(s);
        struct atom temp;
        temp.atomNo =stoi(v[0]);
        temp.sec = stoi(v[1]);
        temp.type=stoi(v[2]);
        temp.charge=stoi(v[3]);
        temp.x=stof(v[4]);
        temp.y=stof(v[5]);
        temp.z= stof(v[6]);
        temp.hash = v[7];
        temp.s1 = v[8];
        temp.s2 =  v[9];

        atoms.push_back(temp);
        if(v[2]=="4")
        {
            atom7.push_back(temp);    //stores N atoms in atom7
        }
        if(v[2]=="1")
        { 
            atom6.push_back(temp);   // stores C atoms in atom6
        }
    }
    atomsFile.close();

    ifstream bondsFile ;
    bondsFile.open ("bonds.txt");   // reads information from the bonds.txt file 
    string line1;
    vector <bond> bonds ,bond6 ,oldbonds;  

    while (getline(bondsFile,line1))
    {
        
        vector<string> v;
        string s="";
        for(int i=0;i<line1.size();i++)   //stores the information of bonds in struture bonds
        {
            if(line1[i]==' ')
            {
                v.push_back(s);
                s="";
            }
            else 
            {
                s+=line1[i];
            }
        }
        v.push_back(s);
        struct bond temp;
        temp.bondNo = stoi(v[0]);
        temp.type=stoi(v[1]);
        temp.atom1=stoi(v[2]);
        temp.atom2=stoi(v[3]);
        bonds.push_back(temp);
        if (v[1]=="2")             //stores C-Cl bonds in bond6
        {bond6.push_back(temp);}
       
    }
    
    bondsFile.close();
    
    for (int j=0;j <bond6.size() ;j++)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
    {
        int c=bond6[j].atom1;
       
            for (int i =0; i<atoms.size();i++)
            { 
                if(c==atoms[i].atomNo)
                {   struct atom temp;
                    temp.atomNo = atoms[i].atomNo;   //stores C(of carboxyl group) atoms linked to Cl in atom8
                    temp.sec= atoms[i].sec;
                    temp.type =atoms[i].type;
                    temp.charge=atoms[i].charge;
                    temp.x=atoms[i].x;
                    temp.y=atoms[i].y;
                    temp.z=atoms[i].z;
                    temp.hash=atoms[i].hash;
                    temp.s1=atoms[i].s1;
                    temp.s2=atoms[i].s2;
                
                atom8.push_back(temp);
                }
            }
    }
int l=bonds.size();
oldatoms=atoms;
oldbonds=bonds;

    for (int i =0;i<atom8.size();i++)
    {
        for(int j=0 ;j<atom7.size() ;j++)
        {
            if( (((atom8[i].type==1) && (atom7[j].type==4) && dist(atom8[i],atom7[j])<=10*10))) 
            {   struct bond temp;
            l=l+1;
                temp.bondNo=l;
                temp.type=6;                    //ckeck distance to form bonds between C of carboxyl group and N atoms
                temp.atom1=atom8[i].atomNo;
                temp.atom2=atom7[j].atomNo;
                atom7[j].type = 6;
                bonds.push_back(temp);    //update bonds structure with new formed bonds of type 6 here

                
                int x =atom8[i].atomNo;
                for (int k=0 ;k<oldbonds.size();k++)
                { 
                    if((oldbonds[k].type==2)&&(oldbonds[k].atom1==x))
                    {   int y=oldbonds[k].atom2;
                    
                        

                        for(int m=0;m<atoms.size();m++)
                        {
                            if(atoms[m].atomNo==y)
                            {
                                struct atom temp;
                                temp.atomNo = atoms[m].atomNo;
                                temp.sec= atoms[m].sec;
                                temp.type =atoms[m].type;
                                temp.charge=atoms[m].charge;
                                temp.x=atoms[m].x;
                                temp.y=atoms[m].y;
                                temp.z=atoms[m].z;
                                temp.hash=atoms[m].hash;
                                temp.s1=atoms[m].s1;
                                temp.s2=atoms[m].s2;
                            
                                delCl.push_back(temp);  //storesto be  deleted Cl atoms
                                
                            }
                        }
                        
                        
                    }
                }
                int z=atom7[j].atomNo;
                for (int k=0 ;k<oldbonds.size();k++)
                { 
                    if((oldbonds[k].type==6)&&(oldbonds[k].atom1==z))
                    {   int y=oldbonds[k].atom2;
                        k=k+1;

                        for(int m=0;m<atoms.size();m++)
                        {
                            if(atoms[m].atomNo==y)
                            {
                                struct atom temp;
                                temp.atomNo = atoms[m].atomNo;
                                temp.sec= atoms[m].sec;
                                temp.type =atoms[m].type;
                                temp.charge=atoms[m].charge;
                                temp.x=atoms[m].x;
                                temp.y=atoms[m].y;
                                temp.z=atoms[m].z;
                                temp.hash=atoms[m].hash;
                                temp.s1=atoms[m].s1;
                                temp.s2=atoms[m].s2;
                            
                                delH.push_back(temp); //stores to be deleted H atoms
                                
                            }
                        }
                    }
                    
                }

                
        
                break;
            }


            
        }

    }
    
    
    cout << l<<"\n" ;
    
      cout<<bonds.size()<<endl;
     
               
           for (int i=0; i<atoms.size();i++)
                 {
                     cout <<atoms[i].atomNo << "  ";
                     cout << atoms[i].sec << "  ";
                     cout << atoms[i].type << "  ";
                     cout << atoms[i].charge<< "  ";
                     cout << atoms[i].x<< "  ";
                     cout << atoms[i].y<< "  ";
                     cout << atoms[i].z<<"  ";
                     cout << atoms[i].hash<< "  ";
                     cout << atoms[i].s1<< "  ";  // prints delH ,just to check
                     cout <<atoms[i].s2<< " " << "\n";
                
                }        
     cout <<delH.size()<<"\n";  
    
               
              
                
              
    return 0;
}