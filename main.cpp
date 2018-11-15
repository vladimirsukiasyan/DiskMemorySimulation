#include <iostream>
#include <string>
#include "Disk.cpp"
using namespace std;

int main() {
    int choice;
    Disk disk;
    while (true) {
        string name;
        string dimension;
        int size;

        cout<<"\n\nChoose an action:\n1. Information about memory\n2. Add file\n3. Delete file with name\n4. Exit\n";
        cin>>choice;
        switch (choice) {
            case 1: // data
                disk.infoAboutMemory();
                break;

            case 2: // add
                cout<<"Enter file's name,size and dimension (b-byte/kb-kilobyte):\t";
                cin>>name>>size>>dimension;
                if(dimension=="kb") size*=1024;
                disk.addFile(name, (size%18==0)? size/18 : size/18+1);
                break;

            case 3: //delete
                printf("Enter file's name:\t");
                cin>>name;
                disk.deleteFile(name);
                break;

            case 4: // Âûõîä
                disk.clear();
                return 0;
        }
    }
}


