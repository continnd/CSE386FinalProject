#include "Pyramid.h"
#include "Material.h"
#include "vertexStructs.h"

Pyramid::Pyramid(GLfloat w, GLfloat h)
	:VisualObject(), width( w ), height( h )
{
}

struct VertexData
{
	glm::vec3 m_pos;
	glm::vec4 m_color;
	VertexData() {}
	VertexData(glm::vec3 pos, glm::vec4 col)
	{
		m_pos = pos;
		m_color = col;
	}
};

void Pyramid:: initialize(){

	glUseProgram(shaderProgram);
	GLuint VBO;
	modelLocation = glGetUniformLocation(shaderProgram, "modelMatrix");

	assert(modelLocation != 0xFFFFFFFF);
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

	vector<VertexData> v;
	v.push_back( VertexData(v0,c0) );
	v.push_back( VertexData(v1,c1) );
	v.push_back( VertexData(v3,c3) );
	v.push_back( VertexData(v3,c3) );
	v.push_back( VertexData(v1,c1) );
	v.push_back( VertexData(v2,c2) );
	v.push_back( VertexData(v0,c0) );
	v.push_back( VertexData(v3,c3) );
	v.push_back( VertexData(v4,c4) );
	v.push_back( VertexData(v0,c0) );
	v.push_back( VertexData(v4,c4) );
	v.push_back( VertexData(v1,c1) );
	v.push_back( VertexData(v1,c1) );
	v.push_back( VertexData(v4,c4) );
	v.push_back( VertexData(v2,c2) );
	v.push_back( VertexData(v2,c2) );
	v.push_back( VertexData(v4,c4) );
	v.push_back( VertexData(v3,c3) );

	vector<pncVertexData> normals;

	glm::vec3 normal = findUnitNormal(v0, v1, v3);
	normals.push_back(pncVertexData(v0, normal, glm::vec4(1.0f, 0.0f, 1.0f, 0.0f)));
	normals.push_back(pncVertexData(v1, normal, glm::vec4(1.0f, 0.0f, 1.0f, 0.0f)));
	normals.push_back(pncVertexData(v3, normal, glm::vec4(1.0f, 0.0f, 1.0f, 0.0f)));

	glm::vec3 normal = findUnitNormal(v3, v1, v2);
	normals.push_back(pncVertexData(v3, normal, glm::vec4(1.0f, 0.0f, 1.0f, 0.0f)));
	normals.push_back(pncVertexData(v1, normal, glm::vec4(1.0f, 0.0f, 1.0f, 0.0f)));
	normals.push_back(pncVertexData(v2, normal, glm::vec4(1.0f, 0.0f, 1.0f, 0.0f)));

	glm::vec3 normal = findUnitNormal(v0, v3, v4);
	normals.push_back(pncVertexData(v0, normal, glm::vec4(1.0f, 0.0f, 1.0f, 0.0f)));
	normals.push_back(pncVertexData(v3, normal, glm::vec4(1.0f, 0.0f, 1.0f, 0.0f)));
	normals.push_back(pncVertexData(v4, normal, glm::vec4(1.0f, 0.0f, 1.0f, 0.0f)));

	glm::vec3 normal = findUnitNormal(v0, v4, v1);
	normals.push_back(pncVertexData(v0, normal, glm::vec4(1.0f, 0.0f, 1.0f, 0.0f)));
	normals.push_back(pncVertexData(v4, normal, glm::vec4(1.0f, 0.0f, 1.0f, 0.0f)));
	normals.push_back(pncVertexData(v1, normal, glm::vec4(1.0f, 0.0f, 1.0f, 0.0f)));

	glm::vec3 normal = findUnitNormal(v1, v4, v2);
	normals.push_back(pncVertexData(v1, normal, glm::vec4(1.0f, 0.0f, 1.0f, 0.0f)));
	normals.push_back(pncVertexData(v4, normal, glm::vec4(1.0f, 0.0f, 1.0f, 0.0f)));
	normals.push_back(pncVertexData(v2, normal, glm::vec4(1.0f, 0.0f, 1.0f, 0.0f)));

	glm::vec3 normal = findUnitNormal(v2, v4, v3);
	normals.push_back(pncVertexData(v2, normal, glm::vec4(1.0f, 0.0f, 1.0f, 0.0f)));
	normals.push_back(pncVertexData(v4, normal, glm::vec4(1.0f, 0.0f, 1.0f, 0.0f)));
	normals.push_back(pncVertexData(v3, normal, glm::vec4(1.0f, 0.0f, 1.0f, 0.0f)));

	numberOfIndices = v.size();

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, v.size() * sizeof(VertexData), &v[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(VertexData),0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer( 2, 4, GL_FLOAT, GL_FALSE, 
		sizeof(VertexData), 
		(const GLvoid*)sizeof(glm::vec3) );
	glEnableVertexAttribArray(2);
	//Initialize all childern
	VisualObject::initialize();
}

void Pyramid::draw(){
	glUseProgram(shaderProgram);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(modelAndFixed));
	glBindVertexArray( vertexArrayObject );
	glDrawArrays(GL_TRIANGLES,0,numberOfIndices);
	//Draw all children
	VisualObject::draw();
}