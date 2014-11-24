#include "Cube.h"
#include "vertexStructs.h"
#include "Material.h"

#include <vector>

#include "vertexStructs.h"

Cube::Cube( GLfloat w, GLfloat h, GLfloat d)
	:VisualObject( ),width(w), height(h), depth(d)
{
}
 
void Cube::setShaderValues()
{
	glUseProgram(shaderProgram);

	modelLocation = glGetUniformLocation(shaderProgram, "modelMatrix");
	assert(modelLocation != 0xFFFFFFFF);

	material.setUpMaterial( getUniformLocation( shaderProgram, "object.ambientMat"),
						 getUniformLocation( shaderProgram, "object.diffuseMat"),
						 getUniformLocation( shaderProgram, "object.specularMat"),
						 getUniformLocation( shaderProgram, "object.specularExp"),
						 getUniformLocation( shaderProgram, "object.emissiveMat" ),
						 getUniformLocation( shaderProgram, "object.textureMapped") );


} // end buildShaders


void Cube::initialize()
{
	GLfloat hW = width/2.0f;
	GLfloat hH = height/2.0f;
	GLfloat hD = depth/2.0f;

	setShaderValues();

	vector<pntVertexData> v;

	vec3 v0 = vec3( -hW, -hH, hD);
	vec3 v1 =  vec3( -hW, -hH, -hD);
	vec3 v2 = vec3( hW, -hH, -hD); 
	vec3 v3 = vec3( hW, -hH, hD);
	vec3 v4 = vec3( -hW, hH, hD);
	vec3 v5 = vec3( -hW, hH, -hD);
	vec3 v6 = vec3( hW, hH, -hD);
	vec3 v7 = vec3(hW, hH, hD);

	vec2 t0 = vec2(0.0f, 0.0f);
	vec2 t1 = vec2(1.0f, 0.0f);
	vec2 t2 = vec2(1.0f, 1.0f);
	vec2 t3 = vec2(0.0f, 1.0f);

	vec3 normal;

	// 0 4 1
	// 1 4 5
	// 3 2 6
	// 3 6 7
	// 0 3 7
	// 0 7 4
	// 1 5 2
	// 2 5 6
	// 4 7 5
	// 4 6 5
	// 0 2 3
	// 0 1 2

	normal = findUnitNormal(v0, v4, v1);
	v.push_back(pntVertexData(v0, normal, t1));
	v.push_back(pntVertexData(v4, normal, t2));
	v.push_back(pntVertexData(v1, normal, t0));

	normal = findUnitNormal(v1, v4, v5);
	v.push_back(pntVertexData(v1, normal, t0));
	v.push_back(pntVertexData(v4, normal, t2));
	v.push_back(pntVertexData(v5, normal, t3));

	normal = findUnitNormal(v3, v2, v6);
	v.push_back(pntVertexData(v3, normal, t0));
	v.push_back(pntVertexData(v2, normal, t1));
	v.push_back(pntVertexData(v6, normal, t2));

	normal = findUnitNormal(v3, v6, v7);
	v.push_back(pntVertexData(v3, normal, t0));
	v.push_back(pntVertexData(v6, normal, t2));
	v.push_back(pntVertexData(v7, normal, t3));

	normal = findUnitNormal(v0, v3, v7);
	v.push_back(pntVertexData(v0, normal, t0));
	v.push_back(pntVertexData(v3, normal, t1));
	v.push_back(pntVertexData(v7, normal, t2));

	normal = findUnitNormal(v0, v7, v4);
	v.push_back(pntVertexData(v0, normal, t0));
	v.push_back(pntVertexData(v7, normal, t2));
	v.push_back(pntVertexData(v4, normal, t3));

	normal = findUnitNormal(v1, v5, v2);
	v.push_back(pntVertexData(v1, normal, t0));
	v.push_back(pntVertexData(v5, normal, t3));
	v.push_back(pntVertexData(v2, normal, t1));

	normal = findUnitNormal(v2, v5, v6);
	v.push_back(pntVertexData(v2, normal, t1));
	v.push_back(pntVertexData(v5, normal, t3));
	v.push_back(pntVertexData(v6, normal, t2));

	normal = findUnitNormal(v4, v7, v6);
	v.push_back(pntVertexData(v4, normal, t0));
	v.push_back(pntVertexData(v7, normal, t1));
	v.push_back(pntVertexData(v6, normal, t2));

	normal = findUnitNormal(v4, v6, v5);
	v.push_back(pntVertexData(v4, normal, t0));
	v.push_back(pntVertexData(v6, normal, t2));
	v.push_back(pntVertexData(v5, normal, t3));

	normal = findUnitNormal(v0, v2, v3);
	v.push_back(pntVertexData(v0, normal, t3));
	v.push_back(pntVertexData(v2, normal, t1));
	v.push_back(pntVertexData(v3, normal, t2));

	normal = findUnitNormal(v0, v1, v2);
	v.push_back(pntVertexData(v0, normal, t3));
	v.push_back(pntVertexData(v1, normal, t0));
	v.push_back(pntVertexData(v2, normal, t1));

	GLuint VBO;

	glGenVertexArrays (1, &vertexArrayObject); 
	glBindVertexArray( vertexArrayObject );

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, v.size() * sizeof(pntVertexData), &v[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(pntVertexData), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(pntVertexData), (const GLvoid*)sizeof(vec3));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer( 2, 4, GL_FLOAT, GL_FALSE, sizeof(pntVertexData), (const GLvoid*)(sizeof(glm::vec3)*2) );
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(pntVertexData), (const GLvoid*)(2 * sizeof(vec3)) ); 
	glEnableVertexAttribArray(3);

	numberOfIndices = v.size();
	v.clear();

	VisualObject::initialize();

} // end initialize

// Preform drawing operations
void Cube::draw()
{
	glUseProgram(shaderProgram);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(modelAndFixed));

	material.setShaderMaterialProperties();
	
	glBindVertexArray(vertexArrayObject);

	glEnable (GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glDrawArrays(GL_TRIANGLES, 0, numberOfIndices );

    glDisable (GL_BLEND);

	// Draw all children
	VisualObject::draw();

} // end draw

