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
    void setVertexLoc(float data, int axis){
        switch (axis){
        case 0:
            x = data;
            break;
        case 1:
            y = data;
            break;
        case 2:
            z = data;
            break;
        default:
            break;
        }
    }
    void checkLocation(){
        cout << "x = " << x << endl;
        cout << "y = " << y << endl;
        cout << "z = " << z << endl;
    }
};

class SquareFace{
    private:
        Vertex a, b, c, d;
};

class TriangleFace{
    private:
        Vertex a, b, c;
};

void getCoords(string line, Vertex &v){
    int begin = 2, j;
    string buff;

    for(int i = 0; i < 3; i++){
        for(j = begin; (line[j] != ' ' && j < line.size()); j++){
            buff+=line[j];
        }
        v.setVertexLoc(stof(buff), i);
        buff.clear();
        begin = j + 1;
    }
}

int main(){
    fstream myFile;
    myFile.open("Cubo.obj", ios::in);
    vector <Vertex> vertices;

    if(myFile.is_open()){
        string s;
        while(getline(myFile, s)){
            if(s[0] == 'v'){
                Vertex temp;
                getCoords(s, temp);
                vertices.push_back(temp);
            }
        }

        myFile.close();
    }

    for(int i = 0; i < vertices.size(); i++){
        cout << "Vertex " << i << endl;
        vertices[i].checkLocation();
    }
}