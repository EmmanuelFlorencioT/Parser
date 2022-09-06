#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Vertex{
    private:
    float x, y, z;

    public:
    Vertex(){
        x = y = z = 0;
    }
    Vertex(vector<float> c){
        if(c.size() == 3){
            x = c[0];
            y = c[1];
            z = c[2];
        }
    }
    void checkLocation(){
        cout << "x = " << x << endl;
        cout << "y = " << y << endl;
        cout << "z = " << z << endl;
    }
};

// void getRidHeader(fstream &file){
//     string trsh;

//     for(int i = 0; i < 3; i++)
//         getline(file, trsh);
// }

void getCoords(string line, vector<float> &coords){
    int begin = 2, j;
    string buff;

    for(int i = 0; i < 3; i++){
        for(j = begin; (line[j] != ' ' && j < line.size()); j++){
            buff+=line[j];
        }
        coords.push_back(stof(buff));
        buff.clear();
        begin = j + 1;
    }
}

int main(){
    fstream myFile;
    myFile.open("Cubo.obj", ios::in);
    vector <float> sepCoords; //Separate Coords
    vector <Vertex> vertices;

    // getRidHeader(myFile);

    if(myFile.is_open()){
        string s;
        while(getline(myFile, s)){
            if(s[0] == 'v'){
                getCoords(s, sepCoords);
                Vertex v(sepCoords);
                vertices.push_back(v);
                sepCoords.clear();
            }
        }

        myFile.close();
    }

    for(int i = 0; i < vertices.size(); i++){
        cout << "Vertex " << i << endl;
        vertices[i].checkLocation();
    }
}