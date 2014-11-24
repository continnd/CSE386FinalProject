// Specifying version of GLSL. If the compiler does not support 
// this version of higher, an error will occur.
#version 330

#pragma optimize(off)
#pragma debug(on)

// Declare default precision - eliminates warnings (but can cause an error on some machines)
precision mediump float;

// Structure for holding general light properties
struct GeneralLight {
  
	vec4 ambientColor;		// ambient color of the light
	vec4 diffuseColor;		// diffuse color of the light
    vec4 specularColor;		// specular color of the light

	// Either the position or direction
	// if w = 0 then the light is directional and direction specified 
	// is the negative of the direction the light is shinning
	// if w = 1 then the light is positional
    vec4 positionOrDirection;    
					  
	// spotlight attributes
    vec3 spotDirection;		// the direction the cone of light is shinning    
	int isSpot;				// 1 if the light is a spotlight  
    float spotCutoffCos;	// Cosine of the spot cutoff angle
    float spotExponent;		// For gradual falloff near cone edge

	// attenuation coefficients
    float constant; 
    float linear;
    float quadratic;

	int enabled;			// 1 if light is "on"

};

// Structure for material properties
struct Material
{
	vec4 ambientMat;

	vec4 diffuseMat;

	vec4 specularMat;

	float specularExp;

	vec4 emissiveMat;

	bool textureMapped;
};

const int MaxLights = 8;

layout (std140) uniform LightBlock
{
 GeneralLight lights[MaxLights];
};


uniform Material object;

layout (std140) uniform worldEyeBlock
{
	vec3 worldEyePosition;
};

// Vertex attributes passed in by the vertex shader
in vec2 TexCoord0;
in vec3 Normal0;
in vec3 WorldPos0;

// Output color for the fragment (pixel)
out vec4 FragColor;

// Sampler to determine interpolated texture coordinates for the fragment 
uniform sampler2D gSampler;


vec4 calcLight( GeneralLight light, Material object )
{
	vec4 totalLight = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	if (light.enabled == 1) {
		vec4 totalAmbientLight = object.ambientMat * light.ambientColor;
		vec3 VertexToEye = normalize(worldEyePosition - WorldPos0);
		if (light.isSpot == 1) {
			vec3 LightToPixel = normalize(WorldPos0 - light.positionOrDirection.xyz);
			float spotCosFactor = dot(LightToPixel, light.spotDirection);
			if (spotCosFactor > light.spotCutoffCos) {
				float DiffuseFactor = max(dot(Normal0, -LightToPixel), 0.0f);
				vec4 diffuseTerm = DiffuseFactor * object.diffuseMat * light.diffuseColor;
				vec3 LightReflect = normalize(reflect(LightToPixel, Normal0));
				float SpecularFactor = max(dot(VertexToEye, LightReflect), 0.0f);
				SpecularFactor = pow(SpecularFactor, object.specularExp);
				vec4 specularTerm = SpecularFactor * object.specularMat * light.specularColor;
				totalLight += diffuseTerm + specularTerm;

				float falloff = 1.0f - (1.0f - spotCosFactor) / (1.0f - light.spotCutoffCos);
				totalLight *= falloff;
				totalLight += totalAmbientLight;
				return totalLight;
			}
			return totalLight;
		} else {
			totalLight += totalAmbientLight;
			float DiffuseFactor = max(dot(Normal0, light.positionOrDirection.xyz), 0.0f);
			vec4 diffuseTerm = DiffuseFactor * object.diffuseMat * light.diffuseColor;

			vec3 LightReflect = vec3( 0, 0, 0);
			// Directional
			if (light.positionOrDirection.w <1) {
				LightReflect = normalize(reflect(-light.positionOrDirection.xyz, Normal0));
				float SpecularFactor = max(dot(VertexToEye, LightReflect), 0.0f);
				SpecularFactor = pow(SpecularFactor, object.specularExp);
				vec4 specularTerm = SpecularFactor * object.specularMat * light.specularColor;
				totalLight += specularTerm + diffuseTerm;
			} else { // Positional
				vec3 directionToPosLight = normalize( light.positionOrDirection.xyz - WorldPos0);
				float DiffuseFactor = max(dot(Normal0, directionToPosLight), 0.0f);
				vec4 diffuseTerm = DiffuseFactor * object.diffuseMat * light.diffuseColor;
				totalLight += diffuseTerm;

				vec3 VertexToEye = normalize(worldEyePosition - WorldPos0);
				vec3 LightReflect = normalize(reflect(-directionToPosLight, Normal0));
				float SpecularFactor = max(dot(VertexToEye, LightReflect), 0.0f);
				SpecularFactor = pow(SpecularFactor, object.specularExp);
				vec4 specularTerm = SpecularFactor * object.specularMat * light.specularColor;

				totalLight += specularTerm;
				return totalLight;

			}
		}
	}

	return totalLight;
}



void main()
{
	
	Material texturedMaterial = object;
	if (object.textureMapped == true) {
		texturedMaterial.ambientMat = texture2D(gSampler, TexCoord0.st); 
		texturedMaterial.diffuseMat = texture2D(gSampler, TexCoord0.st); 
		texturedMaterial.specularMat = texture2D(gSampler, TexCoord0.st); }

	FragColor = object.emissiveMat;

	for (int i = 0; i < MaxLights; i++)  {
	
		FragColor += calcLight( lights[i], texturedMaterial );
	}

}