varying vec2 texCoord;
//varying vec2 neighborCoord[8];
void main(){
//	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex; //The order in which you times matrices and vertices is IMPORTANT.
	gl_Position = gl_Vertex; // faster... dont need the viewprojection anyway
    	texCoord = gl_MultiTexCoord0.xy;
/*
	neighborCoord[0] = texCoord + vec2(0.00125,	 0.00166666666);
	neighborCoord[1] = texCoord + vec2(0.00125,	 0.0);
	neighborCoord[2] = texCoord + vec2(0.00125,	-0.00166666666);
	neighborCoord[3] = texCoord + vec2(0.0,		 0.00166666666);
	neighborCoord[4] = texCoord + vec2(0.0,		-0.00166666666);
	neighborCoord[5] = texCoord + vec2(-0.00125,	 0.00166666666);
	neighborCoord[6] = texCoord + vec2(-0.00125,	 0.0);
	neighborCoord[7] = texCoord + vec2(-0.00125,	-0.00166666666);
*/
}
