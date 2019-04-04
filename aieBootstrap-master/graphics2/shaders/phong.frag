//classic phong fragment shader
#version 410

in vec2 vTexCoord;
in vec4 vPosition;
in vec3 vNormal;

out vec4 FragColour;

uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;

uniform vec3 Ka;	//ambient material colour
uniform vec3 Kd;	//diffuse material colour
uniform vec3 Ks;	//specular material colour
uniform float specularPower; //material specular power

//first light + ambient
uniform vec3 Ia; 	//ambient light colour
uniform vec3 Id;	//diffuse light colour
uniform vec3 Is;	//specular light colour
uniform vec3 LightDirection;

//light2
uniform vec3 Id2;	//diffuse light colour 2 
uniform vec3 Is2;	//specular light colour 2
uniform vec3 LightDirection2;


uniform vec3 cameraPosition;


void main()
{
//ensure normal and light direction are normalised
vec3 N = normalize(vNormal);
vec3 L1 = normalize(LightDirection);
//light2
vec3 L2 = normalize(LightDirection2);


//texture
vec3 texDiffuse = texture(diffuseTexture, vTexCoord).rgb;
vec3 texSpecular = texture(specularTexture, vTexCoord).rgb;


//calculate lambert term(negate light direction)
float lambertTerm = max(0, min(1, dot(N, -L1)));
//light2
float lambertTerm2 = max(0, min(1, dot(N, -L2)));


//calculate view vector and reflection vector
vec3 V = normalize(cameraPosition - vPosition.xyz);
vec3 R = reflect (L1,N);
//light2
vec3 R2 = reflect (L2,N);


//calculate specular term
float specularTerm = pow(max(0, dot(R, V)), specularPower);
//light2
float specularTerm2 = pow(max(0, dot(R2, V)), specularPower);


//calculate each colour property
vec3 ambient = Ia * Ka;
vec3 diffuse = Id * Kd * texDiffuse * lambertTerm;
vec3 specular = Is * Ks * texSpecular * specularTerm;
//light2
vec3 diffuse2 = Id2 * Kd * texDiffuse * lambertTerm2;
vec3 specular2 = Is2 * Ks * texSpecular * specularTerm2;


//output final colour
FragColour = vec4(ambient + diffuse + specular, 1);
FragColour += vec4(ambient + diffuse2 + specular2,1);
}