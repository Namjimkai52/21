
#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[]){
    if(argc < 2){
        cout << "Please input numbers to find average.";
        return 1;
    }
    int sum;
    for(int i = 1;i < argc ;++i){
        sum += atoi(argv[i]);
    }
    double avg = sum / (argc-1) ;
    cout << "---------------------------------" << endl;
    cout << "Average of " << argc-1 << " numbers = " << avg << endl;
    cout << "---------------------------------" << endl;
    return 0;
}