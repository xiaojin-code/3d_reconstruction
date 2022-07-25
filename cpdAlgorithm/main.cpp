#include <iostream>
#include <fstream>
#include <fgt.hpp>
#include <cpd/rigid.hpp>
#include <cpd/version.hpp>

using namespace std;


int main()
{
    cpd::Matrix fixed = cpd::matrix_from_path("orig.csv");
    cpd::Matrix moving = cpd::matrix_from_path("out.csv");
    cpd::Rigid rigid;
    rigid.scale(true);

    cpd::RigidResult result = rigid.run(fixed, moving);
    cpd::Matrix transform = result.matrix();
    double rigdScale = result.scale;

    cpd::Matrix rota = result.rotation;
    cpd::Vector trans = result.translation;

    fstream fs;
    fs.open("1.txt", ios::app);

    fs << "Transform = :";
    fs << endl;
    fs << transform;
    fs << endl;

    fs << "Scale = :";
    fs << endl;
    fs << rigdScale;
    fs << endl;

    fs << "Rotation = :";
    fs << endl;
    fs << rota;
    fs << endl;

    fs << "Trans = :";
    fs << endl;
    fs << trans;
    fs << endl;

    fs.close();

//    cout << "Transform = :" << endl;
//    std::cout << transform << std::endl;

//    cout << "Scale = :" << endl;
//    cout << rigdScale << endl;

//    cout << "Rotation = :" << endl;
//    cout << rota << endl;

//    cout << "Trans = :" << endl;
//    cout << trans << endl;

//    cpd::version();

    return 0;
}
