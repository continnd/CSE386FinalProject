// Targeting version 3.3 of GLSL. If the compiler does not support 
// 3.3 it will cause an error.
#version 330

// The rasterizer runs over all the pixels that are inside
// the point, line, or triangle. For each pixel the fragment shader is executed. 

// Usually the job of the fragment shader is to determine the 
// color of the fragment (pixel). In addition, the fragment shader 
// can discard the pixel altogether or change its Z value (which will
// impact the result of subsequent Z test).
out vec4 FragColor;
in vec3 Normal0;
in vec3 WorldPos0;

struct Material
{
	vec4 ambientMat;
	vec4 diffuseMat;
	vec4 specularMat;
	float specularExp;
	vec4 emissiveMat;
};

struct AmbientLight
{
	vec4 colorIntensity;
	bool enabled;
};

struct DirectionalLight
{
	vec4 colorIntensity;
	vec4 specularIntensity;
	vec3 direction;
	bool enabled;
};

struct PositionalLight
{
	vec4 colorIntensity;
	vec4 specularIntensity;
	vec3 position;
//	Attenuation atten;
	bool enabled;
};

struct SpotLight
{
	vec4 colorIntensity;
	vec4 specularIntensity;
	vec3 position;
	vec3 spotDirection;
	float spotCutoffCos;
//  Attenuation atten;
	bool enabled;
};

uniform Material object;
uniform AmbientLight ambLight;
uniform DirectionalLight directLight;
uniform PositionalLight posLight;
uniform SpotLight spLight;

layout (std140) uniform worldEyeBlock {
	vec3 worldEyePosition;
};

void main()
{
	vec4 totalAmbientLight = vec4(0.0f,0.0f,0.0f,0.0f);
	vec4 totalDirectionalLight = vec4(0.0f,0.0f,0.0f,0.0f);

	if(ambLight.enabled == true) {
		totalAmbientLight = object.ambientMat * ambLight.colorIntensity;
	}
	if(directLight.enabled == true) {
		//Directional
		float DiffuseFactor = max(dot(Normal0, normalize(directLight.direction)), 0.0f);

		totalDirectionalLight = DiffuseFactor * object.diffuseMat * directLight.colorIntensity;

		//Specular
		vec3 VertexToEye = normalize(worldEyePosition - WorldPos0);

		vec3 LightReflect = normalize(reflect(-directLight.direction, Normal0));

		float SpecularFactor = max(dot(VertexToEye, LightReflect), 0.0f);

		SpecularFactor = pow(SpecularFactor, object.specularExp);

		vec4 specularTerm = SpecularFactor * object.specularMat * directLight.specularIntensity;
		
		totalDirectionalLight += specularTerm;
	}

	vec4 totalPositionalLight = vec4(0.0f, 0.0f, 0.0f, 1.0f);

	// Point Light
	if(posLight.enabled == true) {

		// Find a unit vector that points at the 
		// light source
		vec3 directionToPosLight = normalize( posLight.position - WorldPos0 );
	
		// Diffuse
		float DiffuseFactor = max(dot(Normal0, directionToPosLight), 0.0f); 
		vec4 diffuseTerm  = DiffuseFactor * object.diffuseMat * posLight.colorIntensity;
		
		// Specular
		vec3 VertexToEye = normalize(worldEyePosition - WorldPos0);
		vec3 LightReflect = normalize( reflect(-directionToPosLight, Normal0) );
		float SpecularFactor = max( dot( VertexToEye, LightReflect ), 0.0f);
		SpecularFactor = pow(SpecularFactor, object.specularExp);
		vec4 specularTerm = SpecularFactor * object.specularMat * posLight.specularIntensity;
		totalPositionalLight = diffuseTerm + specularTerm; 
	}

	vec4 totalSpotLight = vec4(0.0f,0.0f,0.0f,1.0f);
	// SpotLight
	
	if(spLight.enabled == true) {
		vec3 LightToPixel = normalize(WorldPos0 - spLight.position); 
		float spotCosFactor = dot(LightToPixel, spLight.spotDirection); 
		if( spotCosFactor > spLight.spotCutoffCos ) {
			vec3 directionToSpotLight = - LightToPixel;
	
			// Diffuse
			float DiffuseFactor = max(dot(Normal0, directionToSpotLight), 0.0f); 
			vec4 diffuseTerm = DiffuseFactor * object.diffuseMat * spLight.colorIntensity;
	
			// Specular
			vec3 VertexToEye = normalize(worldEyePosition - WorldPos0);
			vec3 LightReflect = normalize(reflect(-directionToSpotLight, Normal0));
			float SpecularFactor = max(dot(VertexToEye, LightReflect), 0.0f);
			SpecularFactor = pow(SpecularFactor, object.specularExp);
			vec4 specularTerm = SpecularFactor * object.specularMat * spLight.specularIntensity;
	
			//Local Lighting 
			totalSpotLight = diffuseTerm + specularTerm;
	
			// Traditional method for attenuating illumination
			// near the edges of the cone
			// float falloff = pow( spotCosFactor, 50.0f );
			// Alternative method for attenuating illumination
			// near the edges of the cone
			float falloff = 1.0f - (1.0f - spotCosFactor) /	(1.0f - spLight.spotCutoffCos);
			totalSpotLight = falloff * totalSpotLight;
		}
	}
		
	// Set the fragment color to red.
	FragColor = totalDirectionalLight + totalAmbientLight + totalPositionalLight + object.emissiveMat + totalSpotLight;
}
