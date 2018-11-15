//
// Created by Olya Mayorova on 15.11.2018.
//
#include "File.cpp"
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;


//Cell----это ячейка памяти
class Disk {
    const int LIM = 20480;
    //20480-кол-во ячеек памяти по 18 Б в 360 кб
    File **memoryCells;

public:
    Disk() {
        //создаем динамический массив, где будут храниться ссылки на объекты типа File
        memoryCells = new File *[LIM];
        //инициализируем все ячейки памяти ссылкой на NULL, т.к. файлов еще не нет
        for (int i = 0; i < LIM; i++) {
            memoryCells[i] = nullptr;
        }
    }

    void addFile(string name, int size) {
        if (fileIsExist(name)) {
            cout << "File with such name is already exist!";
            return;
        } else {
            int indexOfFirstFreeCell = findFreeMemory(size);
            if (indexOfFirstFreeCell == -1) {
                cout << "Sorry, man, there is no free memory for your fat file!";
                return;
            } else {

                File *file = new File(name, size);

                //заполняем ссылками на файл свободное пространство
                for (int i = indexOfFirstFreeCell; i < indexOfFirstFreeCell + size; i++) {
                    memoryCells[i] = file;
                }
                cout<<"File is added!";
            }
        }
    }

    void deleteFile(string name) {
        int index = findIndexOfFirstCell(name);

        if (index == -1) {
            cout << "File with such name doesn't exist!";
            return;
        }
        else{
            File* file=memoryCells[index];
            //стираем все адреса начиная с первой ячейки файла(index) заканчивая последней (index + file->size)
            for(int i=index;i<index+file->size;i++){
                memoryCells[i]= nullptr;
            }
            delete file;
            cout<<"\nFile is deleted!";
        }
    }

    void clear(){
        for(int i=0;i<LIM;){
            if(memoryCells[i]!= nullptr){
                i+=memoryCells[i]->size;
                delete memoryCells[i];
            }
            else i++;
        }
    }

    void infoAboutMemory(){
        vector<string> listOfOccupiedCells;
        int countOfFreeCells=0;
        int countOfOccupiedCell=0;
        for(int i=0;i<LIM;i++){
            if(memoryCells[i] == nullptr) {
                countOfFreeCells++;
                if(countOfOccupiedCell!=0){
                    stringstream ss;
                    ss<<i-countOfOccupiedCell<<"-"<<i;
                    listOfOccupiedCells.push_back(ss.str());
                    countOfOccupiedCell=0;
                }
            }
            else {
                countOfOccupiedCell++;
            }
        }
        cout<<"All memory: 360 KB;"<<endl
            <<"Occupied memory: "<<(LIM-countOfFreeCells)*18<<" byte;"<<endl
            <<"Free memory: "<<countOfFreeCells*18<<" byte;"<<endl;
        cout<<"List of occupied interval:\n";
        for(auto interval: listOfOccupiedCells) cout<<interval<<endl;
    }

private:

    int findFreeMemory(int size) {
        int countOfFreeCells = 0;
        for (int i = 0; i < LIM; i++) {
            //считаем кол-во подряд идущих свободных ячеек
            if (memoryCells[i] == nullptr && countOfFreeCells<size) countOfFreeCells++;
            else {
                //проверяем, хватает ли насчитанных свободных ячеек для нашего файла
                if (countOfFreeCells >= size) {
                    //возвращаем адрес первой ячейки для записи
                    return i-countOfFreeCells;
                }
                countOfFreeCells = 0;
            }
        }
        //Не найдя места мы отправляем nullptr
        return -1;
    }

    int findIndexOfFirstCell(string name) {
        for (int i = 0; i < LIM; i++) {
            if(memoryCells[i]!=nullptr) cout<<memoryCells[i]->name;
            if (memoryCells[i] != nullptr && memoryCells[i]->name == name) return i;
        }
        return -1;
    }

    bool fileIsExist(string name) {
        for (int i = 0; i < LIM; i++) {
            if (memoryCells[i] != nullptr && memoryCells[i]->name == name) return true;
        }
        return false;
    }
};
