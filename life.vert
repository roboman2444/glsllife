varying vec2 texCoord;
varying vec2 offsetCoord;
void main(){
//	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex; //The order in which you times matrices and vertices is IMPORTANT.
	gl_Position = gl_Vertex; // faster... dont need the viewprojection anyway
    	texCoord = gl_MultiTexCoord0.xy;
	offsetCoord = texCoord + vec2(-0.00125,  -0.00166666666);
}
