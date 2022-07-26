## CPD(Coherent Point Drift)Algorithm 

## fixed reference value
cpd::Matrix fixed = cpd::matrix_from_path("orig.csv");

## Rebuild model experimental values
cpd::Matrix moving = cpd::matrix_from_path("out.csv");
 
## Create a rigid transform object
cpd::Rigid rigid;
 
## Set this rigid transform allows scaling.
rigid.scale(true);

## Get rigid transformation results
cpd::RigidResult result = rigid.run(fixed, moving);
 
## Get transformation matrix
## Convert rigid transform result to 4*4 matrix
cpd::Matrix transform = result.matrix();
## Get matching scale
double rigdScale = result.scale;
## Get rotation matrix
cpd::Matrix rota = result.rotation;
## Get translation vector
cpd::Vector trans = result.translation;

## save data to txt file
fstream fs;
 fs.open("1.txt", ios::app);

fs << "Transform = :(转换矩阵)";
fs << endl;
fs << transform;
fs << endl;

fs << "Scale = :(匹配规模)";
fs << endl;
fs << rigdScale;
fs << endl;

fs << "Rotation = :(旋转矩阵)";
fs << endl;
fs << rota;
fs << endl;

fs << "Trans = :(平移向量)";
fs << endl;
fs << trans;
fs << endl;

fs.close();