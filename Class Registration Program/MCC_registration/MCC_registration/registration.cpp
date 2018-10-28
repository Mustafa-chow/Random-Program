#include<iostream>
#include<fstream>
#include<string>
/* Mustafa Chowdhury, ITCS 2530, This program can used for registration process*/

using namespace std;

struct Student
{
	string StudentID;
	string FirstName;
	string LastName;
	string courses;

};
const int STUDENTSIZE = 100;

int FindStudent(string id, Student students[])
{
	int index = -1;
	ifstream infile;
	bool found = false;
	string line;
	int Pos = 0;
	int PrevPos=0;

	string::size_type Length;
	infile.open("registration.txt");
	int i=-1;
	if (infile.is_open())
	{
		while(!infile.eof())
		{
			i++;
			infile >> line;
			Length = line.size();											// all code get from file opareting sheet from class
			Pos = 0;
			PrevPos= 0;
			Pos = line.find(",", Pos);
			students[i].StudentID = line.substr(0, Pos);
			PrevPos = Pos;
			Pos =  line.find(",", PrevPos+1);
			students[i].FirstName = line.substr(PrevPos+1, (Pos-PrevPos)-1);
			PrevPos = Pos;
			Pos =  line.find(",", PrevPos+1);
			students[i].LastName = line.substr(PrevPos+1, (Pos-PrevPos)-1);
			PrevPos = Pos;
			Pos =  line.find("/n", PrevPos+1);
			students[i].courses = line.substr(PrevPos+1, (Pos-PrevPos)-1);
			if(students[i].StudentID== id)
			{
				cout << students[i].FirstName << " "<<students[i].LastName<<",  Welcome to the MCC Enrollment SYstem!"<<endl;
				found = true;

				index =i;
			}
		}
		i=i+1;
		if(!found)
		{

			students[i].StudentID = id;
			cout <<"Enter first Name: "<<endl;
			cin >>students[i].FirstName;
			//cout<<endl;
			cout <<"Enter last Name: "<<endl;
			cin >>students[i].LastName;
			//cout<<endl;
			students[i].courses="";
			index= i;
		}

	}
	else
	{
		cout <<"Error reading file"<<endl;


	}
	infile.close();

	return index;

}
void RegisterClass(int index, Student s[])
{
	string couseToRegesterFor;
	cout << "Enter the course you would like to regester for? "<<endl;
	cin >> couseToRegesterFor;
	bool done = false;
	ifstream infile;
	infile.open("Available_courses.txt");

	while(!infile.eof())
	{
		string course;
		infile>> course;
		cout<<course;
		if(course == couseToRegesterFor)
		{

			if (s[index].courses.find(couseToRegesterFor) == std::string::npos)//If do not found it
			{
				s[index].courses.append(course+",");
				cout << "Registration successful";



			}
			else
			{
				cout << "Registration Failed. Already registered."<<endl;


			}
			done=true;


		}



	}
	if (!done)
		cout << "Registration failed. Course not available"<<endl;

	infile.close();


}

string Replace(string starting ,string from,string to)
{
	int pos = starting.find(from);
	starting.replace(pos, to.length(), to);//Recurssion
	return starting;
}
void DropClass(int index, Student s[])
{
	string couseToDrop;
	cout << "Enter the course you would like to drop for? "<<endl;
	cin >> couseToDrop;
	if (s[index].courses.find(couseToDrop) == std::string::npos)//s[index].courses.find(couseToDrop) returns the first index
	{															// where couseToDrop is found in s[index].courses, if its not 
		cout<<"Course drop failed"<<endl;						//found then the function find returns std::string::npos
	}															//so if it returns std::string::npos then we know there is no course to drop
	else
	{
		size_t start_pos = s[index].courses.find(couseToDrop);
		s[index].courses = Replace(s[index].courses, couseToDrop, ",");
		cout << "Course dropped"<<endl;

	}

}


void ListRegestered(Student s[])
{
	//create a copy of the list so we do not loose our current students ID in the process of sorting
	Student copy[STUDENTSIZE];
	for (int i = 0; i < STUDENTSIZE; i++)
	{
		copy[i].courses = s[i].courses;
		copy[i].FirstName = s[i].FirstName;
		copy[i].LastName = s[i].LastName;
		copy[i].StudentID = s[i].StudentID;
	}




	//sort the records by last name
	for (int i = 0; i < STUDENTSIZE; i++)
	{
		for (int x = 0; x < STUDENTSIZE; x++)
		{
			if( copy[i].LastName<copy[x].LastName)
			{
				Student temp; //basic swap algorythem
				temp = copy[i];
				copy[i]=copy[x];
				copy[x]=temp;


			}
		}
	}



	string courseToSearch ;
	cout<<"Enter a course to view list of regestered students:"<<endl;
	cin >>courseToSearch;
	bool found = false;
	//Student currentStudent = currentStudent[i];
	for (int i = 0; i < STUDENTSIZE; i++)
	{
		if (copy[i].courses.find(courseToSearch) != std::string::npos)
		{
			cout << copy[i].LastName <<","<<copy[i].FirstName<<endl;
			found = true;

		}
	}
	if(!found)
	{
		cout <<"No students registered for "<<courseToSearch<<endl;
	}
}

void ExportSchedule(int index, Student s[])
{

	ofstream infile;
	infile.open(s[index].StudentID+".txt");
	if(infile.is_open())//If there is no error reading the file
	{

		cout << "Student ID: "<< s[index].StudentID<<endl;
		cout <<"Student Name: "<< s[index].FirstName<<" " << s[index].LastName<<endl;
		cout <<"Registered Courses: "<< s[index].courses<<endl;

		infile << "Student ID: "<< s[index].StudentID<<endl;
		infile <<"Student Name: "<< s[index].FirstName<<" " << s[index].LastName<<endl;
		infile <<"Registered Courses: "<< s[index].courses<<endl;
	}
	else
	{
		cout << "Error creating or opening "<<s[index].StudentID+".txt"<<endl;
	}
	infile.close();








}




int main()
{
	Student student [STUDENTSIZE];
	int selection = 0;
	int currentStudentNum = -1;
	Student currentStudent;

	cout <<"Enter Student Id: ";
	string tempID;
	cin >> tempID;
	while (tempID.length()!=9)
	{
		cout <<"that is an invalid student ID!"<<endl;
		cout <<"Enter Student Id: ";
		cin >> tempID;
	}
	currentStudentNum = FindStudent(tempID, student);


	while(selection !=5)
	{

		cout <<"1. Regester a cource"<<endl;
		cout << "2. Drop a cources"<<endl;
		cout << "3. View a list of regestered students"<<endl;
		cout <<"4. Export student schedule to a text file"<<endl;
		cout<<"5. Exit"<<endl;
		cin  >> selection;

		switch (selection)
		{
		case  1:
			RegisterClass(currentStudentNum, student);
			break;
		case  2:
			DropClass(currentStudentNum, student);
			break;
		case  3:
			ListRegestered( student);
			break;
		case  4:
			ExportSchedule(currentStudentNum, student);
			break;
		case  5:

			break;


		default:
			cout <<"Invalid seleciton"<<endl;
			break;
		}
	}

}