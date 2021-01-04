xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 39;
 -10.49922;-0.00514;-9.83462;,
 -10.49922;-0.00514;9.59703;,
 -8.55517;-0.00514;-11.77930;,
 -8.55517;-0.00514;11.54169;,
 8.65880;-0.00514;11.54169;,
 8.65880;-0.00514;-11.77930;,
 10.60291;-0.00514;9.59703;,
 10.60291;-0.00514;-9.83462;,
 -9.66163;-31.78291;8.66963;,
 -9.66163;-31.78291;-8.90724;,
 -7.71912;-31.78291;10.61606;,
 -7.71913;-31.78291;-10.85367;,
 7.82280;-31.78291;-10.85367;,
 7.82280;-31.78291;10.61606;,
 9.76530;-31.78291;-8.90724;,
 9.76530;-31.78291;8.66963;,
 7.82280;-31.78291;10.61606;,
 9.76530;-31.78291;8.66963;,
 11.59478;-18.37034;10.69240;,
 9.65123;-18.37034;12.63787;,
 8.65880;-0.00514;11.54169;,
 9.76530;-31.78291;-8.90724;,
 7.82280;-31.78291;-10.85367;,
 9.65131;-18.37034;-12.87542;,
 11.59475;-18.37034;-10.93010;,
 8.65880;-0.00514;-11.77930;,
 -11.49107;-18.37034;10.69249;,
 -9.54763;-18.37034;12.63787;,
 -9.54763;-18.37034;12.63787;,
 -9.54765;-18.37034;-12.87542;,
 -11.49107;-18.37034;-10.93010;,
 -11.49107;-18.37034;-10.93010;,
 -9.54765;-18.37034;-12.87542;,
 -7.71913;-31.78291;-10.85367;,
 -9.66163;-31.78291;-8.90724;,
 -8.55517;-0.00514;-11.77930;,
 -9.54763;-18.37034;12.63787;,
 -8.55517;-0.00514;11.54169;,
 -7.71912;-31.78291;10.61606;;
 
 28;
 3;0,1,2;,
 3;1,3,2;,
 3;3,4,2;,
 3;2,4,5;,
 3;4,6,5;,
 3;6,7,5;,
 3;8,9,10;,
 3;9,11,10;,
 3;11,12,10;,
 3;10,12,13;,
 3;12,14,13;,
 3;14,15,13;,
 4;16,17,18,19;,
 4;19,18,6,20;,
 4;21,22,23,24;,
 4;24,23,25,7;,
 4;3,1,26,27;,
 4;28,26,8,10;,
 4;0,2,29,30;,
 4;31,32,33,34;,
 4;18,24,7,6;,
 4;26,1,0,30;,
 4;23,32,35,25;,
 4;36,19,20,37;,
 4;18,17,21,24;,
 4;23,22,33,32;,
 4;26,30,9,8;,
 4;36,38,16,19;;
 
 MeshMaterialList {
  30;
  28;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  26,
  26,
  26,
  0,
  0,
  26,
  26,
  26,
  26,
  26,
  26,
  26,
  26,
  26,
  26,
  26,
  26,
  26,
  26,
  26,
  26;;
  Material {
   0.400000;0.400000;0.400000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.080000;0.080000;0.080000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.752000;0.160000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.080000;0.080000;0.080000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.048000;0.048000;0.048000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.632000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.336000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.048000;0.048000;0.048000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.048000;0.048000;0.048000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.048000;0.048000;0.048000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.048000;0.048000;0.048000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.048000;0.048000;0.048000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.632000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.632000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.632000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.632000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.336000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.336000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.336000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.336000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.048000;0.048000;0.048000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.780800;0.796800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.008000;0.008000;0.008000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.368000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  26;
  0.000000;-1.000000;-0.000000;,
  0.923108;-0.054510;0.380657;,
  0.381321;-0.056798;0.922696;,
  0.923107;-0.054510;-0.380659;,
  0.381320;-0.056797;-0.922697;,
  0.000000;1.000000;0.000000;,
  -0.923109;-0.054510;0.380654;,
  -0.381324;-0.056798;0.922695;,
  -0.381323;-0.056798;-0.922696;,
  -0.923109;-0.054510;-0.380656;,
  0.374518;-0.187951;0.907971;,
  0.909705;-0.180458;0.373993;,
  0.921647;0.072526;0.381192;,
  0.381459;0.075589;0.921290;,
  0.909704;-0.180459;-0.373996;,
  0.374516;-0.187949;-0.907972;,
  0.381458;0.075588;-0.921290;,
  0.921646;0.072527;-0.381194;,
  -0.381464;0.075590;0.921288;,
  -0.921648;0.072527;0.381188;,
  -0.909706;-0.180459;0.373993;,
  -0.374518;-0.187952;0.907970;,
  -0.921648;0.072526;-0.381189;,
  -0.381463;0.075588;-0.921288;,
  -0.374517;-0.187949;-0.907972;,
  -0.909705;-0.180458;-0.373995;;
  28;
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  4;10,11,1,2;,
  4;2,1,12,13;,
  4;14,15,4,3;,
  4;3,4,16,17;,
  4;18,19,6,7;,
  4;7,6,20,21;,
  4;22,23,8,9;,
  4;9,8,24,25;,
  4;1,3,17,12;,
  4;6,19,22,9;,
  4;4,8,23,16;,
  4;7,2,13,18;,
  4;1,11,14,3;,
  4;4,15,24,8;,
  4;6,9,25,20;,
  4;7,21,10,2;;
 }
 MeshTextureCoords {
  39;
  0.604150;0.500000;,
  0.395850;0.500000;,
  0.625000;0.476970;,
  0.375000;0.476970;,
  0.375000;0.273030;,
  0.625000;0.273030;,
  0.395850;0.250000;,
  0.604150;0.250000;,
  0.397660;0.750000;,
  0.602330;0.750000;,
  0.375000;0.775000;,
  0.625000;0.775000;,
  0.625000;0.975000;,
  0.375000;0.975000;,
  0.602330;1.000000;,
  0.397660;1.000000;,
  0.350000;0.000000;,
  0.397660;0.000000;,
  0.394060;0.143320;,
  0.353950;0.143320;,
  0.351970;0.250000;,
  0.602330;0.000000;,
  0.650000;-0.000000;,
  0.646050;0.143320;,
  0.605940;0.143320;,
  0.648030;0.250000;,
  0.394060;0.606680;,
  0.375000;0.605480;,
  0.375000;0.611850;,
  0.625000;0.605540;,
  0.605940;0.606680;,
  0.875000;0.141700;,
  0.853950;0.143320;,
  0.850000;0.000000;,
  0.875000;0.000000;,
  0.851970;0.250000;,
  0.146050;0.143320;,
  0.148030;0.250000;,
  0.150000;0.000000;;
 }
}