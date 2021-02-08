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
 52;
 1.31558;0.61719;-0.22973;,
 1.47762;0.61719;1.47402;,
 1.53234;0.17709;1.47402;,
 1.53234;0.17709;-0.51603;,
 -1.89794;1.10241;1.47402;,
 0.32699;1.10241;1.47402;,
 0.41036;1.10241;-1.06665;,
 -1.48104;1.10241;-0.51602;,
 -1.48104;0.17709;1.47402;,
 -1.42630;0.61719;1.47402;,
 -1.26430;0.61719;-0.22972;,
 -1.48104;0.17709;-0.51602;,
 0.32699;-1.05068;3.46402;,
 -1.48104;-1.05068;3.46402;,
 1.53233;-1.05068;3.46402;,
 -1.48104;-1.05068;1.47402;,
 1.53234;-1.05068;1.47402;,
 -1.48104;-1.05068;-0.51602;,
 1.53234;-1.05068;-0.51603;,
 -1.48104;-1.05068;-3.92490;,
 0.32699;-1.05068;-3.92490;,
 1.53234;-1.05068;-3.92490;,
 -1.26430;0.61719;-0.22972;,
 0.28363;0.61719;-0.22973;,
 0.32700;0.17709;-0.51603;,
 -1.48104;0.17709;-0.51602;,
 -1.48104;0.17709;3.46402;,
 0.32699;0.17709;3.46402;,
 0.28362;0.61719;3.17776;,
 -1.26430;0.61719;3.17776;,
 1.53234;-1.05068;1.47402;,
 1.53234;-1.05068;-0.51603;,
 0.32699;0.17709;-3.92490;,
 -1.48104;0.17709;-3.92490;,
 -1.48104;-1.05068;-0.51602;,
 -1.48104;-1.05068;3.46402;,
 0.32699;-1.05068;3.46402;,
 1.53234;0.17709;-3.92490;,
 -1.48104;0.17709;3.46402;,
 -1.26430;0.61719;3.17776;,
 0.41034;1.10241;4.01464;,
 -1.48104;1.10241;3.46402;,
 1.53233;0.17709;3.46402;,
 1.31557;0.61719;3.17776;,
 1.53233;-1.05068;3.46402;,
 1.53233;1.10241;3.46402;,
 1.94922;1.10241;1.47401;,
 1.53234;1.10241;-0.51603;,
 0.41036;1.10241;-1.06665;,
 -1.48104;1.10241;-0.51602;,
 0.41034;1.10241;4.01464;,
 -1.48104;1.10241;3.46402;;
 
 40;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 3;12,13,14;,
 3;13,15,14;,
 3;14,15,16;,
 3;15,17,16;,
 3;16,17,18;,
 3;17,19,18;,
 3;18,19,20;,
 3;20,21,18;,
 4;22,23,24,25;,
 4;26,27,28,29;,
 4;2,30,31,3;,
 4;32,20,19,33;,
 4;15,8,11,34;,
 4;35,36,27,26;,
 4;17,25,33,19;,
 4;25,24,32,33;,
 4;3,31,21,37;,
 4;38,8,15,13;,
 4;39,9,8,38;,
 4;40,5,4,41;,
 4;42,2,1,43;,
 4;44,30,2,42;,
 4;45,46,5,40;,
 4;6,5,46,47;,
 4;3,24,23,0;,
 4;32,24,3,37;,
 4;21,20,32,37;,
 4;27,36,44,42;,
 4;43,28,27,42;,
 4;41,4,9,39;,
 4;10,9,4,7;,
 4;48,23,22,49;,
 4;0,23,48,47;,
 4;46,1,0,47;,
 4;43,1,46,45;,
 4;50,28,43,45;,
 4;29,28,50,51;;
 
 MeshMaterialList {
  13;
  40;
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11;;
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
  52;
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.989155;0.144886;0.024113;,
  0.995206;0.096474;-0.016053;,
  -0.995206;0.096475;-0.016050;,
  0.000001;0.284364;0.958716;,
  0.000004;0.000000;-1.000000;,
  1.000000;0.000000;-0.000000;,
  -0.989442;0.144931;0.000000;,
  0.989442;0.144929;0.000002;,
  -0.000001;0.879007;-0.476809;,
  0.000002;0.000000;-1.000000;,
  0.000001;0.284365;0.958716;,
  0.000001;0.545250;0.838274;,
  -0.984623;-0.174695;0.000001;,
  -0.980020;-0.173880;-0.096577;,
  -0.000001;0.545306;-0.838237;,
  0.980019;-0.173878;-0.096585;,
  0.984623;-0.174694;0.000003;,
  0.980019;-0.173875;0.096590;,
  0.000001;0.545250;0.838274;,
  -0.000002;0.545305;-0.838238;,
  -0.000001;0.879007;-0.476810;,
  1.000000;0.000000;0.000003;,
  1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  -1.000000;0.000000;-0.000001;,
  0.000001;0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;-0.000001;,
  -0.989154;0.144889;0.024104;,
  -1.000000;0.000000;0.000000;,
  -0.980020;-0.173877;0.096579;,
  1.000000;0.000000;0.000004;,
  -0.000000;0.879007;-0.476809;,
  -0.000001;0.545307;-0.838236;,
  0.000001;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.284365;0.958716;,
  0.000001;0.545250;0.838273;,
  -0.506452;-0.742228;0.438867;,
  -0.798718;-0.601706;0.000001;,
  -0.506447;-0.742243;-0.438848;,
  0.033313;-0.753043;-0.657127;,
  -0.118316;-0.737843;-0.664521;,
  0.184168;-0.750715;-0.634436;,
  0.533881;-0.736723;-0.414982;,
  0.798723;-0.601699;0.000003;,
  0.533889;-0.736706;0.415002;,
  0.033316;-0.753018;0.657156;,
  0.184176;-0.750689;0.634465;,
  -0.118319;-0.737817;0.664550;;
  40;
  4;17,18,9,3;,
  4;0,0,0,0;,
  4;8,14,15,4;,
  3;0,0,0;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  4;21,16,10,22;,
  4;5,12,20,13;,
  4;9,23,24,3;,
  4;11,11,6,6;,
  4;25,8,4,26;,
  4;27,28,12,5;,
  4;26,4,29,29;,
  4;22,10,0,0;,
  4;3,24,7,7;,
  4;30,8,25,31;,
  4;32,14,8,30;,
  4;0,0,0,0;,
  4;2,9,18,19;,
  4;33,23,9,2;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;34,10,16,35;,
  4;0,10,34,0;,
  4;36,11,11,36;,
  4;12,28,37,38;,
  4;39,20,12,38;,
  4;40,41,14,32;,
  4;15,14,41,42;,
  4;43,43,44,42;,
  4;45,43,43,46;,
  4;47,18,17,46;,
  4;19,18,47,48;,
  4;49,49,50,48;,
  4;51,49,49,40;;
 }
 MeshTextureCoords {
  52;
  0.625000;0.224210;,
  0.500000;0.224210;,
  0.500000;0.191880;,
  0.625000;0.191880;,
  0.500000;0.500000;,
  0.500000;0.350000;,
  0.625000;0.350000;,
  0.625000;0.500000;,
  0.500000;0.558120;,
  0.500000;0.525790;,
  0.625000;0.525790;,
  0.625000;0.558120;,
  0.375000;0.900000;,
  0.375000;0.750000;,
  0.375000;1.000000;,
  0.500000;0.750000;,
  0.500000;1.000000;,
  0.875000;0.000000;,
  0.625000;1.000000;,
  0.875000;0.000000;,
  0.725000;0.000000;,
  0.625000;0.000000;,
  0.875000;0.224210;,
  0.725000;0.224210;,
  0.725000;0.191880;,
  0.875000;0.191880;,
  0.125000;0.191880;,
  0.275000;0.191880;,
  0.275000;0.224210;,
  0.125000;0.224210;,
  0.500000;0.000000;,
  0.625000;0.000000;,
  0.725000;0.191880;,
  0.875000;0.191880;,
  0.625000;0.750000;,
  0.125000;0.000000;,
  0.275000;0.000000;,
  0.625000;0.191880;,
  0.375000;0.558120;,
  0.375000;0.525790;,
  0.375000;0.350000;,
  0.375000;0.500000;,
  0.375000;0.191880;,
  0.375000;0.224210;,
  0.375000;0.000000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.725000;0.250000;,
  0.875000;0.250000;,
  0.275000;0.250000;,
  0.125000;0.250000;;
 }
}