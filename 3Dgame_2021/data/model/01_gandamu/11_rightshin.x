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
 130;
 2.17348;-1.20162;-15.61645;,
 6.75882;-13.26683;-13.00625;,
 -10.78961;-11.73156;-13.00625;,
 -4.17870;-0.64586;-15.61645;,
 -18.54805;-32.85264;-17.41649;,
 -13.93609;-22.04465;-12.47758;,
 -14.94212;-24.56615;-20.89622;,
 -12.05641;-22.57692;-14.94726;,
 -12.31171;-21.80317;-18.34300;,
 -9.74857;-21.13606;-22.47732;,
 4.12793;-22.27297;-22.54610;,
 6.12122;-24.12348;-14.94744;,
 7.00997;-23.50312;-18.32350;,
 -23.27096;-162.89717;10.03316;,
 -23.27096;-162.89717;-11.30156;,
 -20.05293;-163.17874;13.32252;,
 -20.01113;-163.18240;-14.54413;,
 -10.41728;-164.02173;13.32252;,
 -10.45904;-164.01807;-14.54413;,
 -7.19921;-164.30330;10.03316;,
 -7.19921;-164.30330;-11.30161;,
 8.62829;-26.54840;-20.96783;,
 10.73176;-35.41426;-17.41649;,
 8.06795;-23.97211;-12.47966;,
 -11.01713;-0.04760;-10.41931;,
 -11.01713;-0.04760;11.14645;,
 -4.17870;-0.64586;-15.61645;,
 -4.52569;-0.61549;11.64642;,
 2.17348;-1.20162;-15.61645;,
 2.52048;-1.23199;11.64642;,
 9.01192;-1.79989;-10.41931;,
 9.01192;-1.79989;11.14645;,
 5.04877;-133.77215;28.73694;,
 9.71615;-134.21590;24.32898;,
 4.71982;-111.85012;22.69010;,
 2.03595;-111.56494;25.74626;,
 3.57894;-85.98533;19.24742;,
 0.33627;-85.88537;22.54719;,
 9.67391;-133.99351;-28.10132;,
 4.98927;-133.80232;-32.51205;,
 2.00013;-111.61214;-21.80531;,
 4.69689;-111.53689;-18.72778;,
 0.19709;-85.68943;-23.42725;,
 3.57894;-85.98533;-20.07052;,
 -16.41703;-11.23920;12.30322;,
 -11.00900;-11.71232;16.55660;,
 -11.00900;-11.71232;16.55660;,
 -18.05141;-32.89607;17.84844;,
 -14.76246;-33.18384;21.06638;,
 -10.78961;-11.73156;-13.00625;,
 -16.37360;-11.24301;-8.76809;,
 5.94650;-71.91714;17.18804;,
 2.68315;-71.63167;20.44629;,
 2.62155;-71.62628;-32.86749;,
 5.94649;-71.91714;-29.36926;,
 -29.98638;-130.70142;-32.51244;,
 -34.70469;-130.32954;-28.12114;,
 -25.90045;-109.17119;-18.74744;,
 -23.18556;-109.35037;-21.80571;,
 -23.18556;-109.35037;-21.80571;,
 -25.90045;-109.17119;-18.74744;,
 -20.28538;-83.89744;-19.88401;,
 -16.92840;-84.19116;-23.27711;,
 -34.63799;-130.15354;24.29571;,
 -30.04407;-130.73728;28.74345;,
 -23.22023;-109.40569;25.75268;,
 -25.83643;-108.91795;22.65715;,
 -23.22023;-109.40569;25.75268;,
 -17.01069;-84.37138;22.54768;,
 -20.28538;-83.89744;19.24743;,
 -17.01069;-84.37138;22.54768;,
 -16.91071;-69.91744;20.44629;,
 -20.17402;-69.63194;17.18805;,
 -16.92840;-84.19116;-23.27711;,
 -20.28538;-83.89744;-19.88401;,
 -20.17402;-69.63194;-29.58144;,
 -16.84481;-69.92320;-32.86749;,
 8.18856;-46.31062;-37.88341;,
 11.42863;-46.47661;-34.60576;,
 11.44183;-46.59524;19.46390;,
 8.19525;-46.31118;22.71906;,
 -21.18880;-43.74043;19.46302;,
 -17.94133;-44.02456;22.71906;,
 -14.76246;-33.18384;21.06638;,
 -17.94133;-44.02456;22.71906;,
 -16.91071;-69.91744;20.44629;,
 -17.93552;-44.02507;-37.88341;,
 -21.15513;-43.62581;-34.60576;,
 -14.05652;-24.25629;-32.24418;,
 -10.86322;-25.67743;-35.45684;,
 -21.15513;-43.62581;-34.60576;,
 -17.93552;-44.02507;-37.88341;,
 -16.84481;-69.92320;-32.86749;,
 -20.17402;-69.63194;-29.58144;,
 10.23518;-35.37086;17.84844;,
 6.94622;-35.08309;21.06637;,
 12.38616;-13.75915;12.30321;,
 6.98591;-13.28668;16.55660;,
 4.40570;-27.01329;-35.45684;,
 7.80540;-26.16978;-32.35070;,
 2.52048;-1.23199;11.64642;,
 12.34282;-13.75537;-8.76804;,
 -9.59180;-14.14753;-26.81216;,
 -1.53352;-4.32854;-24.94629;,
 -1.07292;-4.36879;-24.94629;,
 5.19568;-15.52094;-26.86217;,
 -13.56171;-21.95690;-25.65227;,
 7.72286;-23.73798;-25.74973;,
 -23.22023;-109.40569;25.75268;,
 -17.01069;-84.37138;22.54768;,
 -34.70469;-130.32954;-28.12114;,
 -30.04407;-130.73728;28.74345;,
 -16.91071;-69.91744;20.44629;,
 -17.94133;-44.02456;22.71906;,
 -14.76246;-33.18384;21.06638;,
 -13.93609;-22.04465;-12.47758;,
 -11.00900;-11.71232;16.55660;,
 -4.52569;-0.61549;11.64642;,
 -18.54805;-32.85264;-17.41649;,
 -14.94212;-24.56615;-20.89622;,
 -21.15513;-43.62581;-34.60576;,
 -12.05641;-22.57692;-14.94726;,
 -10.78961;-11.73156;-13.00625;,
 -7.19921;-164.30330;10.03316;,
 -7.19921;-164.30330;-11.30161;,
 -10.45904;-164.01807;-14.54413;,
 -20.01113;-163.18240;-14.54413;,
 -23.27096;-162.89717;-11.30156;,
 -20.05293;-163.17874;13.32252;,
 -10.41728;-164.02173;13.32252;;
 
 107;
 4;0,1,2,3;,
 3;4,5,6;,
 3;5,7,6;,
 3;7,8,6;,
 3;8,7,9;,
 3;7,2,9;,
 3;2,1,9;,
 3;9,1,10;,
 3;10,1,11;,
 3;11,12,10;,
 3;13,14,15;,
 3;14,16,15;,
 3;15,16,17;,
 3;16,18,17;,
 3;17,18,19;,
 3;18,20,19;,
 3;21,12,22;,
 3;12,11,22;,
 3;11,23,22;,
 3;24,25,26;,
 3;25,27,26;,
 3;26,27,28;,
 3;27,29,28;,
 3;28,29,30;,
 3;29,31,30;,
 4;32,33,34,35;,
 4;35,34,36,37;,
 4;38,39,40,41;,
 4;41,40,42,43;,
 4;27,25,44,45;,
 4;46,44,47,48;,
 4;24,26,49,50;,
 4;37,36,51,52;,
 4;43,42,53,54;,
 4;55,56,57,58;,
 4;59,60,61,62;,
 4;63,64,65,66;,
 4;66,67,68,69;,
 4;69,70,71,72;,
 4;73,74,75,76;,
 4;54,53,77,78;,
 4;52,51,79,80;,
 4;81,82,83,47;,
 4;84,81,72,85;,
 4;86,87,88,89;,
 4;90,91,92,93;,
 4;80,79,94,95;,
 4;95,94,96,97;,
 4;78,77,98,99;,
 4;97,96,31,100;,
 4;0,30,101,1;,
 4;89,88,102,103;,
 4;99,98,104,105;,
 4;103,102,106,9;,
 4;105,104,10,107;,
 4;34,41,43,36;,
 4;69,61,60,66;,
 4;40,58,73,42;,
 4;108,35,37,109;,
 4;34,33,38,41;,
 4;40,39,55,58;,
 4;66,60,110,63;,
 4;108,111,32,35;,
 4;81,90,93,72;,
 4;53,76,86,77;,
 4;51,54,78,79;,
 4;112,52,80,113;,
 4;47,4,90,81;,
 4;79,78,22,94;,
 4;113,80,95,114;,
 4;42,73,76,53;,
 4;72,93,61,69;,
 4;109,37,52,112;,
 4;36,43,54,51;,
 3;47,44,4;,
 3;44,50,4;,
 3;50,115,4;,
 3;22,23,94;,
 3;23,101,94;,
 3;101,96,94;,
 4;114,95,97,116;,
 4;44,25,24,50;,
 4;96,101,30,31;,
 4;116,97,100,117;,
 4;77,86,89,98;,
 3;88,106,102;,
 4;103,9,10,104;,
 3;105,107,99;,
 4;98,89,103,104;,
 3;118,119,120;,
 3;119,106,120;,
 3;106,88,120;,
 3;99,107,78;,
 3;78,107,22;,
 3;107,21,22;,
 4;121,115,50,122;,
 4;11,1,101,23;,
 4;8,9,106,119;,
 4;12,21,107,10;,
 4;38,33,123,124;,
 4;124,125,39,38;,
 4;55,39,125,126;,
 4;126,127,56,55;,
 4;63,110,14,13;,
 4;13,15,64,63;,
 4;32,111,128,129;,
 4;129,123,33,32;;
 
 MeshMaterialList {
  30;
  107;
  0,
  26,
  0,
  26,
  0,
  0,
  0,
  26,
  26,
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
  0,
  0,
  0,
  0,
  26,
  26,
  26,
  26,
  0,
  26,
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
  0,
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
  0;;
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
  122;
  -0.970090;0.242225;-0.015892;,
  0.965536;0.258594;-0.029481;,
  0.076405;-0.983170;0.165951;,
  0.136494;-0.964589;0.225691;,
  0.919390;0.156922;0.360691;,
  0.399000;0.158177;0.903205;,
  0.050865;-0.941324;-0.333648;,
  0.248031;-0.910767;-0.330127;,
  0.915640;0.181545;-0.358670;,
  0.393934;0.217758;-0.892971;,
  0.087157;0.996195;-0.000000;,
  0.087151;0.996195;-0.000000;,
  -0.881574;0.291531;0.371264;,
  -0.231196;0.325578;0.916814;,
  0.087152;0.996195;0.000000;,
  -0.324371;-0.029052;-0.945484;,
  -0.300615;0.952462;0.049470;,
  -0.867190;0.307532;-0.391669;,
  -0.876129;0.240609;-0.417739;,
  -0.349052;0.236121;-0.906868;,
  0.927982;-0.002603;0.372617;,
  0.397478;0.103358;0.911772;,
  0.353057;-0.316556;-0.880422;,
  0.915426;-0.176009;-0.361963;,
  -0.238971;-0.957425;-0.161959;,
  -0.512616;-0.840548;-0.175229;,
  -0.357309;0.285001;-0.889441;,
  -0.872197;0.338381;-0.353228;,
  -0.416866;-0.843251;0.339339;,
  -0.219866;-0.911339;0.348023;,
  -0.877628;0.314456;0.361781;,
  -0.364144;0.224946;0.903769;,
  -0.913410;0.158608;0.374867;,
  -0.371308;0.170503;0.912721;,
  -0.403863;-0.251884;-0.879459;,
  -0.931640;-0.016545;-0.363007;,
  0.326637;-0.420118;-0.846646;,
  0.879095;-0.319964;-0.353290;,
  0.380410;-0.046226;0.923662;,
  0.910010;-0.163589;0.380948;,
  -0.915809;0.117004;0.384192;,
  -0.373098;0.072836;0.924929;,
  -0.924128;-0.003375;0.382069;,
  -0.381554;0.020230;0.924125;,
  -0.369134;0.027646;-0.928965;,
  -0.942194;0.225089;-0.248205;,
  -0.389679;-0.359156;-0.848032;,
  -0.918655;-0.166356;-0.358328;,
  0.922215;-0.043792;0.384191;,
  0.380077;0.006951;0.924929;,
  0.971724;0.037813;0.233073;,
  0.372859;0.178788;0.910500;,
  0.960324;0.031458;-0.277107;,
  0.369855;-0.038287;-0.928300;,
  -0.886021;0.241614;0.395714;,
  -0.336062;0.240835;0.910528;,
  0.748972;0.281473;0.599845;,
  0.284382;0.280473;0.916767;,
  0.314399;-0.084941;-0.945483;,
  0.087152;0.996195;0.000000;,
  0.912703;0.211430;-0.349671;,
  0.324605;0.305357;-0.895203;,
  0.927039;-0.008933;-0.374859;,
  0.909522;0.100300;-0.403372;,
  0.087152;0.996195;0.000000;,
  0.087155;0.996195;0.000000;,
  -0.283590;0.385647;-0.877982;,
  -0.792025;0.451870;-0.410499;,
  0.341571;0.330350;-0.879885;,
  0.855162;0.308702;-0.416415;,
  -0.231795;0.515985;-0.824640;,
  -0.737724;0.537055;-0.409067;,
  0.815016;0.404153;-0.415223;,
  0.312301;0.468867;-0.826215;,
  -0.454348;0.875309;0.165535;,
  -0.095651;0.939731;-0.328262;,
  -0.849355;0.517629;0.103226;,
  -0.850847;0.525238;0.013564;,
  0.421728;0.899185;0.116666;,
  0.900576;0.430941;0.057026;,
  0.939912;0.335368;0.063986;,
  0.326985;0.927443;-0.181467;,
  0.907551;-0.193913;0.372491;,
  0.917929;-0.146496;-0.368707;,
  0.371235;0.447628;-0.813520;,
  -0.296829;0.507538;-0.808887;,
  -0.946635;0.218091;-0.237316;,
  -0.928526;-0.032352;0.369855;,
  -0.387182;-0.135467;0.911997;,
  0.354658;-0.200599;0.913224;,
  0.038953;0.737437;-0.674292;,
  -0.091270;0.956901;-0.275698;,
  -0.846007;0.170505;-0.505173;,
  -0.952156;0.158033;-0.261581;,
  0.961278;0.164734;0.220922;,
  0.966558;-0.010953;-0.256216;,
  0.110547;0.971927;0.207696;,
  0.917249;0.306021;0.254963;,
  0.087153;0.996195;-0.000000;,
  0.087158;0.996195;0.000000;,
  -0.139616;0.399982;0.905827;,
  -0.308901;0.399998;0.862892;,
  -0.831964;0.333597;-0.443338;,
  0.373963;0.340376;0.862726;,
  0.207109;0.369719;0.905767;,
  0.877256;0.184048;-0.443337;,
  -0.341188;0.301194;0.890434;,
  -0.641036;0.414897;0.645704;,
  0.707457;0.297829;0.640939;,
  0.392987;0.237603;0.888316;,
  0.160451;0.352787;-0.921844;,
  0.995029;-0.099563;-0.002064;,
  -0.901395;0.432996;-0.000968;,
  0.962894;0.269879;-0.000965;,
  0.014181;0.138479;0.990264;,
  0.872384;-0.488820;-0.001386;,
  0.255297;-0.587296;-0.768054;,
  -0.346772;-0.534598;-0.770684;,
  -0.043506;-0.494036;-0.868352;,
  -0.614266;-0.520014;-0.593517;,
  -0.944304;-0.329073;0.001155;,
  -0.038056;-0.438464;0.897943;;
  107;
  4;58,61,19,15;,
  3;0,17,77;,
  3;90,16,91;,
  3;16,74,77;,
  3;74,16,75;,
  3;92,93,93;,
  3;19,61,75;,
  3;75,61,81;,
  3;94,95,60;,
  3;96,78,81;,
  3;28,25,29;,
  3;25,24,29;,
  3;29,24,2;,
  3;24,6,2;,
  3;2,6,3;,
  3;6,7,3;,
  3;79,97,1;,
  3;97,60,1;,
  3;60,63,1;,
  3;14,11,98;,
  3;11,10,98;,
  3;98,10,99;,
  3;10,65,99;,
  3;99,65,59;,
  3;65,64,59;,
  4;89,82,4,5;,
  4;5,4,20,21;,
  4;83,84,9,8;,
  4;8,9,22,23;,
  4;100,101,12,13;,
  4;13,12,54,55;,
  4;102,15,19,18;,
  4;21,20,39,38;,
  4;23,22,36,37;,
  4;85,86,27,26;,
  4;26,27,35,34;,
  4;87,88,31,30;,
  4;30,31,33,32;,
  4;32,33,43,42;,
  4;34,35,47,46;,
  4;37,36,53,52;,
  4;38,39,48,49;,
  4;40,41,55,54;,
  4;41,40,42,43;,
  4;44,45,67,66;,
  4;45,44,46,47;,
  4;49,48,50,51;,
  4;51,50,56,57;,
  4;52,53,68,69;,
  4;57,56,103,104;,
  4;58,105,62,61;,
  4;66,67,71,70;,
  4;69,68,73,72;,
  4;106,107,76,106;,
  4;108,109,94,80;,
  4;4,8,23,20;,
  4;32,35,27,30;,
  4;9,26,34,22;,
  4;31,5,21,33;,
  4;4,82,83,8;,
  4;9,84,85,26;,
  4;30,27,86,87;,
  4;31,88,89,5;,
  4;40,45,47,42;,
  4;36,46,44,53;,
  4;39,37,52,48;,
  4;43,38,49,41;,
  4;54,0,45,40;,
  4;48,52,1,50;,
  4;41,49,51,55;,
  4;22,34,46,36;,
  4;42,47,35,32;,
  4;33,21,38,43;,
  4;20,23,37,39;,
  3;54,12,0;,
  3;12,18,0;,
  3;110,90,110;,
  3;1,63,50;,
  3;63,62,50;,
  3;62,111,50;,
  4;55,51,57,13;,
  4;12,112,102,18;,
  4;56,62,105,113;,
  4;13,57,104,100;,
  4;53,44,66,68;,
  3;67,76,71;,
  4;106,106,114,109;,
  3;72,80,69;,
  4;68,66,70,73;,
  3;0,77,45;,
  3;77,76,45;,
  3;76,67,45;,
  3;69,80,52;,
  3;52,80,1;,
  3;80,79,1;,
  4;92,17,18,19;,
  4;60,61,62,63;,
  4;74,75,76,77;,
  4;78,79,80,81;,
  4;83,82,115,115;,
  4;7,6,116,83;,
  4;117,116,6,118;,
  4;24,25,119,117;,
  4;87,86,25,120;,
  4;28,29,88,87;,
  4;89,88,29,121;,
  4;2,3,82,89;;
 }
 MeshTextureCoords {
  130;
  0.710360;0.250000;,
  0.673570;0.241360;,
  0.826430;0.241360;,
  0.789640;0.250000;,
  0.625000;0.524620;,
  0.752440;0.380220;,
  0.797500;0.316090;,
  0.875000;0.231880;,
  0.875000;0.228420;,
  0.832470;0.222400;,
  0.667310;0.222390;,
  0.625000;0.231940;,
  0.625000;0.228400;,
  0.404510;0.750000;,
  0.595910;0.750000;,
  0.375000;0.800060;,
  0.625000;0.800710;,
  0.375000;0.949940;,
  0.625000;0.949290;,
  0.404510;1.000000;,
  0.595910;1.000000;,
  0.625000;0.223310;,
  0.625000;0.225380;,
  0.625000;0.233520;,
  0.584510;0.500000;,
  0.416520;0.500000;,
  0.625000;0.414640;,
  0.375000;0.418970;,
  0.625000;0.335360;,
  0.375000;0.331030;,
  0.584510;0.250000;,
  0.416520;0.250000;,
  0.344650;0.051540;,
  0.395090;0.051490;,
  0.391100;0.073270;,
  0.352990;0.073350;,
  0.392810;0.124520;,
  0.340820;0.124250;,
  0.604840;0.051810;,
  0.655680;0.051490;,
  0.647200;0.073270;,
  0.608610;0.073740;,
  0.660430;0.124520;,
  0.606590;0.124520;,
  0.406660;0.508640;,
  0.375000;0.508070;,
  0.375000;0.508640;,
  0.395900;0.524620;,
  0.375000;0.521870;,
  0.625000;0.508040;,
  0.593450;0.508640;,
  0.390280;0.147390;,
  0.343770;0.147390;,
  0.656820;0.147390;,
  0.608600;0.147390;,
  0.844320;0.051550;,
  0.875000;0.050800;,
  0.875000;0.072290;,
  0.852800;0.073360;,
  0.625000;0.675700;,
  0.608930;0.676730;,
  0.606630;0.625480;,
  0.625000;0.625480;,
  0.395090;0.698240;,
  0.375000;0.714240;,
  0.375000;0.677930;,
  0.391100;0.676340;,
  0.375000;0.675800;,
  0.375000;0.625480;,
  0.392890;0.625480;,
  0.375210;0.625480;,
  0.375210;0.603020;,
  0.390280;0.602610;,
  0.839830;0.124520;,
  0.875000;0.124520;,
  0.875000;0.144820;,
  0.843140;0.147390;,
  0.649920;0.213390;,
  0.612380;0.213510;,
  0.388430;0.213390;,
  0.350130;0.213390;,
  0.388430;0.536610;,
  0.375000;0.535880;,
  0.375000;0.524620;,
  0.375000;0.537710;,
  0.375000;0.602610;,
  0.850080;0.213390;,
  0.875000;0.213490;,
  0.875000;0.217960;,
  0.836220;0.216510;,
  0.612380;0.536490;,
  0.625000;0.537660;,
  0.625000;0.602610;,
  0.609590;0.602610;,
  0.395900;0.225380;,
  0.346240;0.225380;,
  0.406660;0.241360;,
  0.328090;0.241360;,
  0.663820;0.216510;,
  0.625000;0.217920;,
  0.293970;0.250000;,
  0.593450;0.241360;,
  0.875000;0.219550;,
  0.758300;0.219380;,
  0.741760;0.219380;,
  0.625000;0.219550;,
  0.875000;0.220960;,
  0.625000;0.220930;,
  0.146880;0.073270;,
  0.159090;0.124240;,
  0.605060;0.698510;,
  0.155260;0.051490;,
  0.156230;0.147390;,
  0.149880;0.213390;,
  0.153760;0.225380;,
  0.625000;0.516470;,
  0.171980;0.241360;,
  0.206030;0.250000;,
  0.875000;0.225380;,
  0.875000;0.223330;,
  0.875000;0.215260;,
  0.625000;0.510170;,
  0.625000;0.508640;,
  0.404510;0.000000;,
  0.595910;0.000000;,
  0.675710;0.000000;,
  0.824290;-0.000000;,
  0.875000;0.000000;,
  0.175060;0.000000;,
  0.324940;0.000000;;
 }
}