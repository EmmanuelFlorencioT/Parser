#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Vertex{
    public:
    float x, y, z;

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
    public:
        int nVer = 0;
        vector <Vertex> ver;

        void checkVertices(){
            for(int i = 0; i < nVer; i++){
                cout << "V" << i+1 << ":\n";
                ver[i].checkLocation();
            }
        }
};

class Object{
    public:
        vector<Vertex> vertices;
        vector<Face> faces;
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
    f.nVer = index.size();
    for(int i = 0; i < index.size(); i++){
        f.ver.push_back(ver[index[i]]);
    }
}

// void printRealIndex(vector<int> index){
//     for(int i = 0; i < index.size(); i++){
//         cout << index[i] << " ";
//     }
//     cout << endl;
// }

int main(){
    fstream myFile;
    myFile.open("CuboMultiObj.obj", ios::in);
    Object objAux;
    vector <Object> obj;
    bool notFirst = false; //Dismiss the first 'o' from the file

    obj.clear();

    if(myFile.is_open()){
        string s;
        while(getline(myFile, s)){
            if(s[0] == 'v'){
                Vertex tempV;
                readVertexCoords(s, tempV);
                objAux.vertices.push_back(tempV);
            }
            if(s[0] == 'f'){
                vector <int> indices;
                Face tempF;
                readFaceVertices(s, indices);
                // printRealIndex(indices);
                pairFaceVertices(objAux.vertices, indices, tempF);
                objAux.faces.push_back(tempF);
            }
            if(s[0] == 'o'){
                if(notFirst){
                    //Push the Nth object into the structure
                    obj.push_back(objAux);

                    //Clear our vectors for next object
                    objAux.faces.clear();
                    objAux.vertices.clear();
                } else
                    notFirst = true;
            }
        }
        obj.push_back(objAux); //Save last object in the file

        myFile.close();
    }

    for(int i = 0; i < obj.size(); i++){
        cout << "Object " << i+1 << endl;
        for(int j = 0; j < obj[i].faces.size(); j++){
            cout << "Face " << j+1 << endl;
            obj[i].faces[j].checkVertices();
            cout << "----------------\n";
        }
        cout << "*******************\n";
    }

    // for(int i = 0; i < facesAux.size(); i++){
    //     cout << "Face " << i << "\n";
    //     facesAux[i].checkVertices();
    //     cout << "----------------\n";
    // }
}