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
 154;
 0.00000;0.59673;0.00000;,
 0.08358;0.57638;-0.13005;,
 0.00000;0.57638;-0.15459;,
 0.00000;0.59673;0.00000;,
 0.14062;0.57638;-0.06422;,
 0.00000;0.59673;0.00000;,
 0.15302;0.57638;0.02200;,
 0.00000;0.59673;0.00000;,
 0.11683;0.57638;0.10123;,
 0.00000;0.59673;0.00000;,
 0.04355;0.57638;0.14833;,
 0.00000;0.59673;0.00000;,
 -0.04355;0.57638;0.14833;,
 0.00000;0.59673;0.00000;,
 -0.11683;0.57638;0.10123;,
 0.00000;0.59673;0.00000;,
 -0.15302;0.57638;0.02200;,
 0.00000;0.59673;0.00000;,
 -0.14062;0.57638;-0.06422;,
 0.00000;0.59673;0.00000;,
 -0.08358;0.57638;-0.13005;,
 0.00000;0.59673;0.00000;,
 0.00000;0.57638;-0.15459;,
 0.16146;0.51671;-0.25123;,
 0.00000;0.51671;-0.29864;,
 0.27165;0.51671;-0.12406;,
 0.29560;0.51671;0.04250;,
 0.22570;0.51671;0.19557;,
 0.08414;0.51671;0.28654;,
 -0.08414;0.51671;0.28654;,
 -0.22570;0.51671;0.19557;,
 -0.29560;0.51671;0.04250;,
 -0.27165;0.51671;-0.12406;,
 -0.16146;0.51671;-0.25123;,
 0.00000;0.51671;-0.29864;,
 0.22833;0.42180;-0.35530;,
 0.00000;0.42180;-0.42234;,
 0.38417;0.42180;-0.17545;,
 0.41804;0.42180;0.06010;,
 0.31918;0.42180;0.27657;,
 0.11899;0.42180;0.40523;,
 -0.11899;0.42180;0.40523;,
 -0.31918;0.42180;0.27657;,
 -0.41804;0.42180;0.06010;,
 -0.38417;0.42180;-0.17545;,
 -0.22833;0.42180;-0.35530;,
 0.00000;0.42180;-0.42234;,
 0.27965;0.29810;-0.43514;,
 0.00000;0.29810;-0.51725;,
 0.47051;0.29810;-0.21488;,
 0.51199;0.29810;0.07362;,
 0.39092;0.29810;0.33873;,
 0.14573;0.29810;0.49630;,
 -0.14573;0.29810;0.49630;,
 -0.39092;0.29810;0.33873;,
 -0.51199;0.29810;0.07361;,
 -0.47051;0.29810;-0.21488;,
 -0.27965;0.29810;-0.43514;,
 0.00000;0.29810;-0.51725;,
 0.31191;0.15405;-0.48534;,
 0.00000;0.15405;-0.57692;,
 0.52479;0.15405;-0.23966;,
 0.57105;0.15405;0.08210;,
 0.43601;0.15405;0.37780;,
 0.16254;0.15405;0.55356;,
 -0.16254;0.15405;0.55356;,
 -0.43601;0.15405;0.37780;,
 -0.57105;0.15405;0.08210;,
 -0.52479;0.15405;-0.23966;,
 -0.31191;0.15405;-0.48534;,
 0.00000;0.15405;-0.57692;,
 0.32291;-0.00054;-0.50246;,
 0.00000;-0.00054;-0.59727;,
 0.54330;-0.00054;-0.24812;,
 0.59119;-0.00054;0.08500;,
 0.45139;-0.00054;0.39113;,
 0.16827;-0.00054;0.57308;,
 -0.16827;-0.00054;0.57308;,
 -0.45139;-0.00054;0.39113;,
 -0.59119;-0.00054;0.08500;,
 -0.54330;-0.00054;-0.24812;,
 -0.32291;-0.00054;-0.50246;,
 0.00000;-0.00054;-0.59727;,
 0.31191;-0.15513;-0.48534;,
 0.00000;-0.15513;-0.57692;,
 0.52479;-0.15513;-0.23966;,
 0.57105;-0.15513;0.08210;,
 0.43601;-0.15513;0.37780;,
 0.16254;-0.15513;0.55356;,
 -0.16254;-0.15513;0.55356;,
 -0.43601;-0.15513;0.37780;,
 -0.57105;-0.15513;0.08210;,
 -0.52479;-0.15513;-0.23966;,
 -0.31191;-0.15513;-0.48534;,
 0.00000;-0.15513;-0.57692;,
 0.27965;-0.29918;-0.43514;,
 0.00000;-0.29918;-0.51725;,
 0.47051;-0.29918;-0.21488;,
 0.51199;-0.29918;0.07362;,
 0.39092;-0.29918;0.33873;,
 0.14573;-0.29918;0.49630;,
 -0.14573;-0.29918;0.49630;,
 -0.39092;-0.29918;0.33873;,
 -0.51199;-0.29918;0.07361;,
 -0.47051;-0.29918;-0.21488;,
 -0.27965;-0.29918;-0.43514;,
 0.00000;-0.29918;-0.51725;,
 0.22833;-0.42288;-0.35530;,
 0.00000;-0.42288;-0.42234;,
 0.38417;-0.42288;-0.17545;,
 0.41804;-0.42288;0.06010;,
 0.31918;-0.42288;0.27657;,
 0.11899;-0.42288;0.40523;,
 -0.11899;-0.42288;0.40523;,
 -0.31918;-0.42288;0.27657;,
 -0.41804;-0.42288;0.06010;,
 -0.38417;-0.42288;-0.17545;,
 -0.22833;-0.42288;-0.35530;,
 0.00000;-0.42288;-0.42234;,
 0.16146;-0.51779;-0.25123;,
 0.00000;-0.51779;-0.29864;,
 0.27165;-0.51779;-0.12406;,
 0.29560;-0.51779;0.04250;,
 0.22570;-0.51779;0.19557;,
 0.08414;-0.51779;0.28654;,
 -0.08414;-0.51779;0.28654;,
 -0.22570;-0.51779;0.19557;,
 -0.29560;-0.51779;0.04250;,
 -0.27165;-0.51779;-0.12406;,
 -0.16146;-0.51779;-0.25123;,
 0.00000;-0.51779;-0.29864;,
 0.08358;-0.57746;-0.13005;,
 0.00000;-0.57746;-0.15459;,
 0.14062;-0.57746;-0.06422;,
 0.15302;-0.57746;0.02200;,
 0.11683;-0.57746;0.10123;,
 0.04355;-0.57746;0.14833;,
 -0.04355;-0.57746;0.14833;,
 -0.11683;-0.57746;0.10123;,
 -0.15302;-0.57746;0.02200;,
 -0.14062;-0.57746;-0.06422;,
 -0.08358;-0.57746;-0.13005;,
 0.00000;-0.57746;-0.15459;,
 0.00000;-0.59781;-0.00000;,
 0.00000;-0.59781;-0.00000;,
 0.00000;-0.59781;-0.00000;,
 0.00000;-0.59781;-0.00000;,
 0.00000;-0.59781;-0.00000;,
 0.00000;-0.59781;-0.00000;,
 0.00000;-0.59781;-0.00000;,
 0.00000;-0.59781;-0.00000;,
 0.00000;-0.59781;-0.00000;,
 0.00000;-0.59781;-0.00000;,
 0.00000;-0.59781;-0.00000;;
 
 132;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,8;,
 3;11,12,10;,
 3;13,14,12;,
 3;15,16,14;,
 3;17,18,16;,
 3;19,20,18;,
 3;21,22,20;,
 4;2,1,23,24;,
 4;1,4,25,23;,
 4;4,6,26,25;,
 4;6,8,27,26;,
 4;8,10,28,27;,
 4;10,12,29,28;,
 4;12,14,30,29;,
 4;14,16,31,30;,
 4;16,18,32,31;,
 4;18,20,33,32;,
 4;20,22,34,33;,
 4;24,23,35,36;,
 4;23,25,37,35;,
 4;25,26,38,37;,
 4;26,27,39,38;,
 4;27,28,40,39;,
 4;28,29,41,40;,
 4;29,30,42,41;,
 4;30,31,43,42;,
 4;31,32,44,43;,
 4;32,33,45,44;,
 4;33,34,46,45;,
 4;36,35,47,48;,
 4;35,37,49,47;,
 4;37,38,50,49;,
 4;38,39,51,50;,
 4;39,40,52,51;,
 4;40,41,53,52;,
 4;41,42,54,53;,
 4;42,43,55,54;,
 4;43,44,56,55;,
 4;44,45,57,56;,
 4;45,46,58,57;,
 4;48,47,59,60;,
 4;47,49,61,59;,
 4;49,50,62,61;,
 4;50,51,63,62;,
 4;51,52,64,63;,
 4;52,53,65,64;,
 4;53,54,66,65;,
 4;54,55,67,66;,
 4;55,56,68,67;,
 4;56,57,69,68;,
 4;57,58,70,69;,
 4;60,59,71,72;,
 4;59,61,73,71;,
 4;61,62,74,73;,
 4;62,63,75,74;,
 4;63,64,76,75;,
 4;64,65,77,76;,
 4;65,66,78,77;,
 4;66,67,79,78;,
 4;67,68,80,79;,
 4;68,69,81,80;,
 4;69,70,82,81;,
 4;72,71,83,84;,
 4;71,73,85,83;,
 4;73,74,86,85;,
 4;74,75,87,86;,
 4;75,76,88,87;,
 4;76,77,89,88;,
 4;77,78,90,89;,
 4;78,79,91,90;,
 4;79,80,92,91;,
 4;80,81,93,92;,
 4;81,82,94,93;,
 4;84,83,95,96;,
 4;83,85,97,95;,
 4;85,86,98,97;,
 4;86,87,99,98;,
 4;87,88,100,99;,
 4;88,89,101,100;,
 4;89,90,102,101;,
 4;90,91,103,102;,
 4;91,92,104,103;,
 4;92,93,105,104;,
 4;93,94,106,105;,
 4;96,95,107,108;,
 4;95,97,109,107;,
 4;97,98,110,109;,
 4;98,99,111,110;,
 4;99,100,112,111;,
 4;100,101,113,112;,
 4;101,102,114,113;,
 4;102,103,115,114;,
 4;103,104,116,115;,
 4;104,105,117,116;,
 4;105,106,118,117;,
 4;108,107,119,120;,
 4;107,109,121,119;,
 4;109,110,122,121;,
 4;110,111,123,122;,
 4;111,112,124,123;,
 4;112,113,125,124;,
 4;113,114,126,125;,
 4;114,115,127,126;,
 4;115,116,128,127;,
 4;116,117,129,128;,
 4;117,118,130,129;,
 4;120,119,131,132;,
 4;119,121,133,131;,
 4;121,122,134,133;,
 4;122,123,135,134;,
 4;123,124,136,135;,
 4;124,125,137,136;,
 4;125,126,138,137;,
 4;126,127,139,138;,
 4;127,128,140,139;,
 4;128,129,141,140;,
 4;129,130,142,141;,
 3;132,131,143;,
 3;131,133,144;,
 3;133,134,145;,
 3;134,135,146;,
 3;135,136,147;,
 3;136,137,148;,
 3;137,138,149;,
 3;138,139,150;,
 3;139,140,151;,
 3;140,141,152;,
 3;141,142,153;;
 
 MeshMaterialList {
  1;
  132;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.000000;0.800000;0.790588;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\student\\Pictures\\3Dgame_2021\\Fotolia_68045745_XS.jpg";
   }
  }
 }
 MeshNormals {
  123;
  0.000000;1.000000;0.000001;,
  0.000000;0.966020;-0.258466;,
  0.139739;0.966021;-0.217432;,
  0.235110;0.966020;-0.107371;,
  0.255832;0.966021;0.036781;,
  0.195331;0.966021;0.169259;,
  0.072817;0.966021;0.247995;,
  -0.072817;0.966021;0.247995;,
  -0.195331;0.966021;0.169259;,
  -0.255832;0.966021;0.036781;,
  -0.235110;0.966020;-0.107371;,
  -0.139739;0.966021;-0.217432;,
  0.000000;0.866341;-0.499453;,
  0.270027;0.866342;-0.420164;,
  0.454323;0.866339;-0.207477;,
  0.494373;0.866339;0.071078;,
  0.377463;0.866340;0.327072;,
  0.140711;0.866340;0.479223;,
  -0.140711;0.866340;0.479223;,
  -0.377463;0.866340;0.327072;,
  -0.494373;0.866339;0.071078;,
  -0.454323;0.866339;-0.207477;,
  -0.270027;0.866342;-0.420164;,
  0.000000;0.707605;-0.706608;,
  0.382020;0.707607;-0.594434;,
  0.642754;0.707607;-0.293529;,
  0.699416;0.707605;0.100559;,
  0.534021;0.707606;0.462726;,
  0.199074;0.707606;0.677985;,
  -0.199074;0.707606;0.677985;,
  -0.534022;0.707605;0.462726;,
  -0.699417;0.707605;0.100559;,
  -0.642754;0.707608;-0.293529;,
  -0.382020;0.707607;-0.594434;,
  0.000000;0.500507;-0.865732;,
  0.468048;0.500512;-0.728299;,
  0.787494;0.500517;-0.359633;,
  0.856915;0.500517;0.123206;,
  0.654276;0.500514;0.566929;,
  0.243906;0.500518;0.830657;,
  -0.243906;0.500518;0.830657;,
  -0.654278;0.500515;0.566927;,
  -0.856915;0.500517;0.123204;,
  -0.787494;0.500517;-0.359634;,
  -0.468048;0.500512;-0.728299;,
  0.000000;0.259148;-0.965838;,
  0.522169;0.259150;-0.812515;,
  0.878556;0.259151;-0.401223;,
  0.956007;0.259149;0.137453;,
  0.729935;0.259148;0.632485;,
  0.272112;0.259147;0.926713;,
  -0.272112;0.259147;0.926713;,
  -0.729935;0.259150;0.632484;,
  -0.956007;0.259150;0.137451;,
  -0.878556;0.259150;-0.401223;,
  -0.522169;0.259150;-0.812515;,
  0.000000;-0.000000;-1.000000;,
  0.540638;-0.000000;-0.841255;,
  0.909632;-0.000000;-0.415415;,
  0.989822;0.000000;0.142313;,
  0.755754;0.000000;0.654856;,
  0.281736;-0.000000;0.959492;,
  -0.281736;-0.000000;0.959492;,
  -0.755754;0.000000;0.654856;,
  -0.989822;0.000000;0.142313;,
  -0.909632;-0.000000;-0.415415;,
  -0.540638;-0.000000;-0.841255;,
  0.000000;-0.259148;-0.965838;,
  0.522169;-0.259149;-0.812515;,
  0.878556;-0.259151;-0.401223;,
  0.956007;-0.259148;0.137453;,
  0.729935;-0.259147;0.632485;,
  0.272112;-0.259147;0.926714;,
  -0.272112;-0.259147;0.926714;,
  -0.729935;-0.259149;0.632484;,
  -0.956007;-0.259150;0.137451;,
  -0.878556;-0.259150;-0.401223;,
  -0.522169;-0.259149;-0.812515;,
  0.000000;-0.500507;-0.865732;,
  0.468048;-0.500511;-0.728299;,
  0.787495;-0.500516;-0.359633;,
  0.856915;-0.500516;0.123206;,
  0.654276;-0.500514;0.566929;,
  0.243906;-0.500518;0.830658;,
  -0.243906;-0.500518;0.830658;,
  -0.654278;-0.500515;0.566927;,
  -0.856916;-0.500516;0.123204;,
  -0.787495;-0.500516;-0.359634;,
  -0.468048;-0.500511;-0.728299;,
  0.000000;-0.707605;-0.706608;,
  0.382021;-0.707607;-0.594435;,
  0.642755;-0.707607;-0.293529;,
  0.699416;-0.707605;0.100559;,
  0.534021;-0.707606;0.462726;,
  0.199074;-0.707606;0.677985;,
  -0.199074;-0.707606;0.677985;,
  -0.534022;-0.707605;0.462726;,
  -0.699417;-0.707604;0.100559;,
  -0.642754;-0.707607;-0.293529;,
  -0.382021;-0.707607;-0.594435;,
  0.000000;-0.866341;-0.499454;,
  0.270027;-0.866342;-0.420164;,
  0.454322;-0.866340;-0.207477;,
  0.494373;-0.866339;0.071079;,
  0.377464;-0.866339;0.327073;,
  0.140711;-0.866340;0.479224;,
  -0.140711;-0.866340;0.479224;,
  -0.377464;-0.866339;0.327073;,
  -0.494373;-0.866339;0.071079;,
  -0.454322;-0.866340;-0.207477;,
  -0.270027;-0.866342;-0.420164;,
  0.000000;-0.966020;-0.258466;,
  0.139739;-0.966021;-0.217432;,
  0.235109;-0.966020;-0.107370;,
  0.255832;-0.966021;0.036782;,
  0.195332;-0.966021;0.169259;,
  0.072817;-0.966021;0.247995;,
  -0.072817;-0.966021;0.247995;,
  -0.195332;-0.966021;0.169259;,
  -0.255832;-0.966021;0.036782;,
  -0.235109;-0.966020;-0.107370;,
  -0.139739;-0.966021;-0.217432;,
  0.000000;-1.000000;0.000001;;
  132;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,8,7;,
  3;0,9,8;,
  3;0,10,9;,
  3;0,11,10;,
  3;0,1,11;,
  4;1,2,13,12;,
  4;2,3,14,13;,
  4;3,4,15,14;,
  4;4,5,16,15;,
  4;5,6,17,16;,
  4;6,7,18,17;,
  4;7,8,19,18;,
  4;8,9,20,19;,
  4;9,10,21,20;,
  4;10,11,22,21;,
  4;11,1,12,22;,
  4;12,13,24,23;,
  4;13,14,25,24;,
  4;14,15,26,25;,
  4;15,16,27,26;,
  4;16,17,28,27;,
  4;17,18,29,28;,
  4;18,19,30,29;,
  4;19,20,31,30;,
  4;20,21,32,31;,
  4;21,22,33,32;,
  4;22,12,23,33;,
  4;23,24,35,34;,
  4;24,25,36,35;,
  4;25,26,37,36;,
  4;26,27,38,37;,
  4;27,28,39,38;,
  4;28,29,40,39;,
  4;29,30,41,40;,
  4;30,31,42,41;,
  4;31,32,43,42;,
  4;32,33,44,43;,
  4;33,23,34,44;,
  4;34,35,46,45;,
  4;35,36,47,46;,
  4;36,37,48,47;,
  4;37,38,49,48;,
  4;38,39,50,49;,
  4;39,40,51,50;,
  4;40,41,52,51;,
  4;41,42,53,52;,
  4;42,43,54,53;,
  4;43,44,55,54;,
  4;44,34,45,55;,
  4;45,46,57,56;,
  4;46,47,58,57;,
  4;47,48,59,58;,
  4;48,49,60,59;,
  4;49,50,61,60;,
  4;50,51,62,61;,
  4;51,52,63,62;,
  4;52,53,64,63;,
  4;53,54,65,64;,
  4;54,55,66,65;,
  4;55,45,56,66;,
  4;56,57,68,67;,
  4;57,58,69,68;,
  4;58,59,70,69;,
  4;59,60,71,70;,
  4;60,61,72,71;,
  4;61,62,73,72;,
  4;62,63,74,73;,
  4;63,64,75,74;,
  4;64,65,76,75;,
  4;65,66,77,76;,
  4;66,56,67,77;,
  4;67,68,79,78;,
  4;68,69,80,79;,
  4;69,70,81,80;,
  4;70,71,82,81;,
  4;71,72,83,82;,
  4;72,73,84,83;,
  4;73,74,85,84;,
  4;74,75,86,85;,
  4;75,76,87,86;,
  4;76,77,88,87;,
  4;77,67,78,88;,
  4;78,79,90,89;,
  4;79,80,91,90;,
  4;80,81,92,91;,
  4;81,82,93,92;,
  4;82,83,94,93;,
  4;83,84,95,94;,
  4;84,85,96,95;,
  4;85,86,97,96;,
  4;86,87,98,97;,
  4;87,88,99,98;,
  4;88,78,89,99;,
  4;89,90,101,100;,
  4;90,91,102,101;,
  4;91,92,103,102;,
  4;92,93,104,103;,
  4;93,94,105,104;,
  4;94,95,106,105;,
  4;95,96,107,106;,
  4;96,97,108,107;,
  4;97,98,109,108;,
  4;98,99,110,109;,
  4;99,89,100,110;,
  4;100,101,112,111;,
  4;101,102,113,112;,
  4;102,103,114,113;,
  4;103,104,115,114;,
  4;104,105,116,115;,
  4;105,106,117,116;,
  4;106,107,118,117;,
  4;107,108,119,118;,
  4;108,109,120,119;,
  4;109,110,121,120;,
  4;110,100,111,121;,
  3;111,112,122;,
  3;112,113,122;,
  3;113,114,122;,
  3;114,115,122;,
  3;115,116,122;,
  3;116,117,122;,
  3;117,118,122;,
  3;118,119,122;,
  3;119,120,122;,
  3;120,121,122;,
  3;121,111,122;;
 }
 MeshTextureCoords {
  154;
  0.045450;0.000000;,
  0.090910;0.083330;,
  0.000000;0.083330;,
  0.136360;0.000000;,
  0.181820;0.083330;,
  0.227270;0.000000;,
  0.272730;0.083330;,
  0.318180;0.000000;,
  0.363640;0.083330;,
  0.409090;0.000000;,
  0.454550;0.083330;,
  0.500000;0.000000;,
  0.545450;0.083330;,
  0.590910;0.000000;,
  0.636360;0.083330;,
  0.681820;0.000000;,
  0.727270;0.083330;,
  0.772730;0.000000;,
  0.818180;0.083330;,
  0.863640;0.000000;,
  0.909090;0.083330;,
  0.954550;0.000000;,
  1.000000;0.083330;,
  0.090910;0.166670;,
  0.000000;0.166670;,
  0.181820;0.166670;,
  0.272730;0.166670;,
  0.363640;0.166670;,
  0.454550;0.166670;,
  0.545450;0.166670;,
  0.636360;0.166670;,
  0.727270;0.166670;,
  0.818180;0.166670;,
  0.909090;0.166670;,
  1.000000;0.166670;,
  0.090910;0.250000;,
  0.000000;0.250000;,
  0.181820;0.250000;,
  0.272730;0.250000;,
  0.363640;0.250000;,
  0.454550;0.250000;,
  0.545450;0.250000;,
  0.636360;0.250000;,
  0.727270;0.250000;,
  0.818180;0.250000;,
  0.909090;0.250000;,
  1.000000;0.250000;,
  0.090910;0.333330;,
  0.000000;0.333330;,
  0.181820;0.333330;,
  0.272730;0.333330;,
  0.363640;0.333330;,
  0.454550;0.333330;,
  0.545450;0.333330;,
  0.636360;0.333330;,
  0.727270;0.333330;,
  0.818180;0.333330;,
  0.909090;0.333330;,
  1.000000;0.333330;,
  0.090910;0.416670;,
  0.000000;0.416670;,
  0.181820;0.416670;,
  0.272730;0.416670;,
  0.363640;0.416670;,
  0.454550;0.416670;,
  0.545450;0.416670;,
  0.636360;0.416670;,
  0.727270;0.416670;,
  0.818180;0.416670;,
  0.909090;0.416670;,
  1.000000;0.416670;,
  0.090910;0.500000;,
  0.000000;0.500000;,
  0.181820;0.500000;,
  0.272730;0.500000;,
  0.363640;0.500000;,
  0.454550;0.500000;,
  0.545450;0.500000;,
  0.636360;0.500000;,
  0.727270;0.500000;,
  0.818180;0.500000;,
  0.909090;0.500000;,
  1.000000;0.500000;,
  0.090910;0.583330;,
  0.000000;0.583330;,
  0.181820;0.583330;,
  0.272730;0.583330;,
  0.363640;0.583330;,
  0.454550;0.583330;,
  0.545450;0.583330;,
  0.636360;0.583330;,
  0.727270;0.583330;,
  0.818180;0.583330;,
  0.909090;0.583330;,
  1.000000;0.583330;,
  0.090910;0.666670;,
  0.000000;0.666670;,
  0.181820;0.666670;,
  0.272730;0.666670;,
  0.363640;0.666670;,
  0.454550;0.666670;,
  0.545450;0.666670;,
  0.636360;0.666670;,
  0.727270;0.666670;,
  0.818180;0.666670;,
  0.909090;0.666670;,
  1.000000;0.666670;,
  0.090910;0.750000;,
  0.000000;0.750000;,
  0.181820;0.750000;,
  0.272730;0.750000;,
  0.363640;0.750000;,
  0.454550;0.750000;,
  0.545450;0.750000;,
  0.636360;0.750000;,
  0.727270;0.750000;,
  0.818180;0.750000;,
  0.909090;0.750000;,
  1.000000;0.750000;,
  0.090910;0.833330;,
  0.000000;0.833330;,
  0.181820;0.833330;,
  0.272730;0.833330;,
  0.363640;0.833330;,
  0.454550;0.833330;,
  0.545450;0.833330;,
  0.636360;0.833330;,
  0.727270;0.833330;,
  0.818180;0.833330;,
  0.909090;0.833330;,
  1.000000;0.833330;,
  0.090910;0.916670;,
  0.000000;0.916670;,
  0.181820;0.916670;,
  0.272730;0.916670;,
  0.363640;0.916670;,
  0.454550;0.916670;,
  0.545450;0.916670;,
  0.636360;0.916670;,
  0.727270;0.916670;,
  0.818180;0.916670;,
  0.909090;0.916670;,
  1.000000;0.916670;,
  0.045450;1.000000;,
  0.136360;1.000000;,
  0.227270;1.000000;,
  0.318180;1.000000;,
  0.409090;1.000000;,
  0.500000;1.000000;,
  0.590910;1.000000;,
  0.681820;1.000000;,
  0.772730;1.000000;,
  0.863640;1.000000;,
  0.954550;1.000000;;
 }
}
