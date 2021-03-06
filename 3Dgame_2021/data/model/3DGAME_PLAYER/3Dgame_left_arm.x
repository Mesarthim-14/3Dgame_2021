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
 30;
 -0.09384;-4.27539;-1.62020;,
 -0.21543;4.25977;-1.49189;,
 -1.54942;4.37765;-0.96846;,
 -1.42784;-4.15749;-1.09674;,
 -1.83498;-4.24879;0.20383;,
 -1.95657;4.28638;0.33214;,
 -1.16270;4.24507;1.38955;,
 -1.04113;-4.29011;1.26125;,
 -0.24144;4.21257;1.62554;,
 -0.11990;-4.32261;1.49726;,
 1.13553;4.10974;1.27246;,
 1.71045;4.22915;0.13364;,
 1.83205;-4.30601;0.00534;,
 1.25710;-4.42543;1.14417;,
 1.23294;4.15893;-1.04521;,
 1.35450;-4.37623;-1.17347;,
 -0.08911;-5.73477;-0.68426;,
 -0.08225;-5.73509;-0.03568;,
 0.63340;-5.74625;-0.07441;,
 0.45427;-5.77258;-0.51670;,
 1.18363;5.67438;0.22973;,
 0.77029;5.57497;1.16429;,
 -1.21358;5.74951;0.43910;,
 -0.73257;5.72150;1.28813;,
 -0.13109;5.68448;1.52144;,
 -0.58956;-5.69054;-0.48790;,
 -0.74233;-5.72480;0.00005;,
 -0.44448;-5.74026;0.39674;,
 -0.09886;-5.75248;0.48528;,
 0.41770;-5.79106;0.35283;;
 
 31;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;6,8,9,7;,
 4;10,11,12,13;,
 4;9,8,10,13;,
 4;14,1,0,15;,
 4;12,11,14,15;,
 4;2,5,4,3;,
 4;16,17,18,19;,
 3;1,14,2;,
 3;14,11,2;,
 3;11,5,2;,
 3;20,21,22;,
 3;22,21,23;,
 3;21,24,23;,
 4;11,10,21,20;,
 4;10,8,24,21;,
 4;8,6,23,24;,
 4;6,5,22,23;,
 4;5,11,20,22;,
 4;0,3,25,16;,
 4;3,4,26,25;,
 4;4,7,27,26;,
 4;7,9,28,27;,
 4;9,13,29,28;,
 4;13,12,18,29;,
 4;12,15,19,18;,
 4;15,0,16,19;,
 4;18,17,28,29;,
 4;16,25,26,17;,
 4;28,17,26,27;;
 
 MeshMaterialList {
  13;
  31;
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6;;
  Material {
   0.400000;0.400000;0.400000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.385600;0.524000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.627000;0.000000;0.082000;1.000000;;
   4.000000;
   0.460000;0.460000;0.460000;;
   0.300960;0.000000;0.039360;;
  }
  Material {
   0.586400;0.411200;0.244800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.627000;0.000000;0.082000;1.000000;;
   4.000000;
   0.460000;0.460000;0.460000;;
   0.300960;0.000000;0.039360;;
  }
  Material {
   0.627000;0.000000;0.082000;1.000000;;
   4.000000;
   0.460000;0.460000;0.460000;;
   0.300960;0.000000;0.039360;;
  }
  Material {
   0.800000;0.793600;0.078400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.790400;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.652800;0.348000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.304000;0.153600;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.426400;0.034400;0.034400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.091200;0.091200;0.091200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.476800;0.382400;0.060000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  42;
  -0.676087;-0.020701;0.736531;,
  -0.634436;-0.094428;-0.767186;,
  0.571896;-0.102455;-0.813903;,
  0.731149;0.000161;0.682218;,
  -0.635491;0.318703;0.703263;,
  0.697128;0.297624;0.652252;,
  0.534292;0.320922;-0.782011;,
  -0.587527;0.345486;-0.731746;,
  -0.003859;-0.044800;-0.998989;,
  0.016165;0.312188;-0.949883;,
  0.056369;0.275888;0.959536;,
  0.036412;-0.014501;0.999232;,
  -0.976935;-0.105090;-0.185889;,
  -0.938799;0.343062;-0.031066;,
  0.932840;0.330133;-0.144295;,
  0.945784;-0.103145;-0.307983;,
  -0.041903;-0.991399;-0.123988;,
  -0.076214;-0.997051;-0.009009;,
  -0.090564;-0.992993;0.075912;,
  -0.092965;-0.994485;0.048551;,
  -0.068805;-0.996296;-0.051572;,
  0.047363;0.998874;0.002801;,
  0.456741;0.782131;0.423861;,
  0.442975;0.895766;-0.037101;,
  0.348335;0.808947;-0.473570;,
  0.038499;0.901660;-0.430728;,
  -0.327220;0.854418;-0.403605;,
  -0.393521;0.919312;0.002628;,
  -0.361905;0.835342;0.413797;,
  0.042328;0.998715;0.027880;,
  -0.077612;-0.996628;0.026644;,
  -0.076640;-0.995357;0.058239;,
  -0.057784;-0.998238;0.013470;,
  -0.047820;-0.998832;0.006855;,
  -0.019680;-0.996905;-0.076118;,
  -0.636693;-0.189413;-0.747492;,
  -0.860983;-0.263474;-0.435075;,
  -0.008362;-0.105543;-0.994380;,
  0.579085;-0.223978;-0.783897;,
  0.791451;-0.307108;-0.528480;,
  0.069099;-0.067084;0.995352;,
  0.071271;0.538634;0.839520;;
  31;
  4;10,11,3,5;,
  4;14,15,2,6;,
  4;2,8,9,6;,
  4;1,12,13,7;,
  4;9,8,1,7;,
  4;0,11,10,4;,
  4;13,12,0,4;,
  4;3,15,14,5;,
  4;21,29,27,28;,
  3;30,31,32;,
  3;31,33,32;,
  3;33,34,32;,
  3;16,17,20;,
  3;20,17,19;,
  3;17,18,19;,
  4;12,1,35,36;,
  4;1,8,37,35;,
  4;8,2,38,37;,
  4;2,15,39,38;,
  4;40,40,40,40;,
  4;10,5,22,41;,
  4;5,14,23,22;,
  4;14,6,24,23;,
  4;6,9,25,24;,
  4;9,7,26,25;,
  4;7,13,27,26;,
  4;13,4,28,27;,
  4;4,10,41,28;,
  4;27,29,25,26;,
  4;21,22,23,29;,
  4;25,29,23,24;;
 }
 MeshTextureCoords {
  30;
  0.375000;0.225440;,
  0.375000;0.225710;,
  0.375000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.625000;0.250000;,
  0.625000;0.225710;,
  0.625000;0.225710;,
  0.625000;0.202060;,
  0.500000;0.202060;,
  0.500000;0.202060;,
  0.625000;0.202060;,
  0.375000;0.202060;,
  0.375000;0.202060;,
  0.375000;0.225440;,
  0.500000;0.227000;,
  0.500000;0.202060;,
  0.375000;0.202060;,
  0.500000;0.202060;,
  0.625000;0.202060;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.625000;0.225710;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.625000;0.225710;,
  0.625000;0.202060;;
 }
}
