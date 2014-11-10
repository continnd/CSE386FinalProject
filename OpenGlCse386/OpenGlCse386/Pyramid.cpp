#include "Pyramid.h"
#include "vertexStructs.h"

Pyramid::Pyramid(GLfloat w, GLfloat h)
	:VisualObject(), width( w ), height( h )
{
}

void Pyramid::setShaderValues() {
	// Bind the shader
	glUseProgram(shaderProgram);
	// Find the location of the model matrix uniform variable in the shader
	modelLocation = glGetUniformLocation(shaderProgram, "modelMatrix");
	assert(modelLocation != 0xFFFFFFFF);
	// Find the locations of the material properties in the Material struct called
	// object
	material.setUpMaterial( getUniformLocation( shaderProgram, "object.ambientMat"),
		getUniformLocation( shaderProgram, "object.diffuseMat"),
		getUniformLocation( shaderProgram, "object.specularMat"),
		getUniformLocation( shaderProgram, "object.specularExp"),
		getUniformLocation( shaderProgram, "object.emissiveMat" ),
		getUniformLocation( shaderProgram, "object.textureMapped"));
}

void Pyramid:: initialize(){

	setShaderValues();

	GLuint VBO;
	glGenVertexArrays (1, &vertexArrayObject);
	glBindVertexArray( vertexArrayObject );

	glm::vec3 v0 = glm::vec3( -width/2, -height/2, width/2);
	glm::vec3 v1 = glm::vec3( -width/2, -height/2, -width/2);
	glm::vec3 v2 = glm::vec3( width/2, -height/2, -width/2);
	glm::vec3 v3 = glm::vec3( width/2, -height/2, width/2);
	glm::vec3 v4 = glm::vec3( 0, height/2, 0);

	glm::vec4 c0 = glm::vec4( 0.0f, 0.5f, 0.0f, 1.0f);
	glm::vec4 c1 = glm::vec4( 1.0f, 0.0f, 0.0f, 1.0f);
	glm::vec4 c2 = glm::vec4( 0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 c3 = glm::vec4( 0.0f, 1.0f, 1.0f, 1.0f);
	glm::vec4 c4 = glm::vec4( 0.0f, 0.0f, 0.0f, 1.0f);

	vector<pncVertexData> v;

	glm::vec3 normal = findUnitNormal(v0, v1, v3);
	v.push_back(pncVertexData(v0, normal, c0));
	v.push_back(pncVertexData(v1, normal, c1));
	v.push_back(pncVertexData(v3, normal, c3));

	normal = findUnitNormal(v3, v1, v2);
	v.push_back(pncVertexData(v3, normal, c3));
	v.push_back(pncVertexData(v1, normal, c1));
	v.push_back(pncVertexData(v2, normal, c2));

	normal = findUnitNormal(v0, v3, v4);
	v.push_back(pncVertexData(v0, normal, c0));
	v.push_back(pncVertexData(v3, normal, c3));
	v.push_back(pncVertexData(v4, normal, c4));

	normal = findUnitNormal(v0, v4, v1);
	v.push_back(pncVertexData(v0, normal, c0));
	v.push_back(pncVertexData(v4, normal, c4));
	v.push_back(pncVertexData(v1, normal, c1));

	normal = findUnitNormal(v1, v4, v2);
	v.push_back(pncVertexData(v1, normal, c1));
	v.push_back(pncVertexData(v4, normal, c4));
	v.push_back(pncVertexData(v2, normal, c2));

	normal = findUnitNormal(v2, v4, v3);
	v.push_back(pncVertexData(v2, normal, c2));
	v.push_back(pncVertexData(v4, normal, c4));
	v.push_back(pncVertexData(v3, normal, c3));

	numberOfIndices = v.size();

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, v.size() * sizeof(pncVertexData), &v[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(pncVertexData),0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer( 2, 4, GL_FLOAT, GL_FALSE, 
		sizeof(pncVertexData), 
		(const GLvoid*)(sizeof(glm::vec3)*2) );
	glEnableVertexAttribArray(2);

	glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 
		sizeof(pncVertexData), 
		(const GLvoid*)sizeof(glm::vec3) );
	glEnableVertexAttribArray(1);

	//Initialize all childern
	VisualObject::initialize();
}

void Pyramid::draw(){
	glUseProgram(shaderProgram);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(modelAndFixed));
	glBindVertexArray( vertexArrayObject );
	material.setShaderMaterialProperties();
	glDrawArrays(GL_TRIANGLES,0,numberOfIndices);
	//Draw all children
	VisualObject::draw();
}