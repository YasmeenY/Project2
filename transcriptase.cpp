#include <iostream>
#include <string>
#include <fstream>
using namespace std;

//function to convert character from DNA to RNA(finding complement)
char DNAbase_to_mRNAbase(char dna){
    if(toupper(dna)=='A')
        return 'U';
    else if(toupper(dna)=='T')
        return 'A';
    else if(toupper(dna)=='C')
        return 'G';
    else if(toupper(dna)=='G')
        return 'C';
    else
        return ' ';
}

string DNA_to_mRNA(string input){
   string output="";//initialising output to empty string
   //looping through each value and converting
   for(int i = 0; i < input.size(); ++i) {
       output=output+DNAbase_to_mRNAbase(input[i]);
   }
   //returning converted string
   return output;
}
//main function
int main(){
    //open file
    ifstream fin("dna.txt");
    string strand;
    //if there is problem in opening file print error message
    if (fin.fail()) {
        cerr << "File cannot be read, opened, or does not exist.\n";
        exit(1);
    }
    //loop for each line untill end of file is reached
    while(getline(fin, strand)) {
        cout << DNA_to_mRNA(strand) << endl; //calling function to convert DNA to RNA
    }
    fin.close();//closing file
    return 0;
}
