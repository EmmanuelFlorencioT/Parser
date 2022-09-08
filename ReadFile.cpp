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

class Face{
    private:
        int nVer = 0;
        vector <Vertex> ver;
    
    public:
        void setNumVer(int n){
            nVer = n;
        }
        void addVertex(Vertex data){
            ver.push_back(data);
        }
        void checkVertices(){
            for(int i = 0; i < nVer; i++){
                cout << "V" << i+1 << ":\n";
                ver[i].checkLocation();
            }
        }
};

void readVertexCoords(string line, Vertex &v){
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

void readFaceVertices(string line, vector<int> &index){
    int begin = 2, j;
    string buff;

    while(begin < line.size()){
        for(j = begin; (line[j] != ' ' && j < line.size()); j++){
            buff+=line[j];
        }
        index.push_back(stoi(buff)-1);
        buff.clear();
        begin = j + 1;
    }
}

void pairFaceVertices(vector<Vertex> ver, vector<int> index, Face &f){
    f.setNumVer(index.size());
    for(int i = 0; i < index.size(); i++){
        f.addVertex(ver[index[i]]);
    }
}

void printRealIndex(vector<int> index){
    for(int i = 0; i < index.size(); i++){
        cout << index[i] << " ";
    }
    cout << endl;
}

int main(){
    fstream myFile;
    myFile.open("Cubo.obj", ios::in);
    vector <Vertex> vertices;
    vector <Face> faces;

    if(myFile.is_open()){
        string s;
        while(getline(myFile, s)){
            if(s[0] == 'v'){
                Vertex tempV;
                readVertexCoords(s, tempV);
                vertices.push_back(tempV);
            }
            if(s[0] == 'f'){
                vector <int> indices;
                Face tempF;
                readFaceVertices(s, indices);
                // printRealIndex(indices);
                pairFaceVertices(vertices, indices, tempF);
                faces.push_back(tempF);
            }
        }

        myFile.close();
    }

    for(int i = 0; i < faces.size(); i++){
        cout << "Face " << i << "\n";
        faces[i].checkVertices();
        cout << "----------------\n";
    }
}