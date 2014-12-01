#ifndef ___UFO_H___
#define ___UFO_H___

#include "VisualObject.h"
#include "BuildShaderProgram.h"
#include "textureCoordinates.h"
#include "Cone.h"
#include "Sphere.h"

class UFO : public VisualObject
{
	public:

		/**
		 * Constructor for the UFO class. Created a visual object in the shape of a cube. Vertex
		 * positions are expressed relative to an origin that is located in the center of the cube.
		 * @param OpenGLApp - reference to the OpenGLApplicationBase object that holds the projection
		 *        and viewing transformations
		 * @param w - width of the cube. Default is 1 unit.
		 */
		UFO( GLfloat radius = 1.0f);
		~UFO();

		/*
		 * Renders the object using the visual object using the vertex array object that was created by
		 * the initialize method.
		 */
		virtual void draw();

		virtual void setShader(GLuint shaderProgram);

	protected:

		/**
		 * Builds the shader program.
		 */
		void setShaderValues();
		
		int numberOfIndices; // number of indices to be used during indexed rendering.
		
		GLuint ShaderProgram; // Identifier for the shader program

		const GLfloat r;
		Cone* top;
		Cone* bottom;
		Sphere* cockpit;
};

#endif // ___UFO_H___