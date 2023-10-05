#include <algorithm>
#include<bits/stdc++.h>
using namespace std;

#define pb push_back

class Student{
    private:
        string _name;
        unsigned int _registration;
        vector<int> _subjects;

    public:
        Student(unsigned int registration, string name){
            _registration = registration;
            _name = name;
        }
        
        void subject_enrollment(unsigned int subject_id){
            if(find(_subjects.begin(), _subjects.end(), subject_id) == _subjects.end())
                _subjects.pb(subject_id);
        } 

        void print_student(){
            cout << "Student " << _name << "\n";
            cout << "id: " << _registration << "\n";
            cout << "Subjects: ";
            for(auto i: _subjects) cout << i << " ";
            cout << "\n";
        }
};

int main(){
    Student s = Student(123, "Iago");
    s.subject_enrollment(203);
    s.subject_enrollment(105);
    s.subject_enrollment(105);
    s.subject_enrollment(174);
    s.print_student();

    exit(0);
}
