// ------NOTE: MANAGE THE HEAP MEMORY IN OBJECTS.C FOR GENERATING OPJECTS
#include "context.h"
#include "shader.h"

char* vecSrc="../src/defaultVertexShader.glsl";
char* fragSrc="../src/defaultFragShader.glsl";

struct MandelbrotData{
  float _x, _y, _scale;
  int _maxIterations;
};

int
main(int argc, char **argv){
  // Setup context
  if(!initContext()) return -1;  
  
  // ---------SHADER------------
  char *verSrc  = "../src/defaultVertexShader.glsl";
  char *fragSrc = "../src/defaultFragShader.glsl";
  struct ShaderProgram shaderProg;
  generateShaderProgramVF(&shaderProg, verSrc, fragSrc);
  setInt(&shaderProg, "WIDTH", WIDTH);
  setInt(&shaderProg, "HEIGHT", HEIGHT);
  
  // -- generate the quad
  float vertices[] = {
		      1.f,  1.f, 0.0f, 
		      1.f, -1.f, 0.0f, 
		      -1.f, -1.f, 0.0f,
		      -1.f,  1.f, 0.0f  
  };
  unsigned int indices[] = {  
			    0, 1, 3,
			    1, 2, 3 
  };
  unsigned int VBO, VAO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  
  struct MandelbrotData data;
  data._x=0.f, data._y=0.f, data._scale=1.f, data._maxIterations=100;

  
  while(!contextShouldClose()){
    clearContext();

    
    float s=0.01*data._scale;
    //INPUT
    {
      //Reset buttons
      if(isKeyPress(GLFW_KEY_SPACE))
	data._x=0.f, data._y=0.f, data._scale=1.f, data._maxIterations=100;
      
      if(isKeyPress(GLFW_KEY_W))
	data._y+=s;
      if(isKeyPress(GLFW_KEY_S))
	data._y-=s;
      
      if(isKeyPress(GLFW_KEY_D))
	data._x+=s;
      if(isKeyPress(GLFW_KEY_A))
	data._x-=s;
      
      if(isKeyPress(GLFW_KEY_I))
	data._scale+=s;
      if(isKeyPress(GLFW_KEY_K))
	data._scale-=s;

      if(isKeyPress(GLFW_KEY_L))
	data._maxIterations+=10;
      if(isKeyPress(GLFW_KEY_J))
	if(data._maxIterations>10) data._maxIterations-=10;
    }

    setVec2(&shaderProg, "areaWidth", (vec2){-2.f*data._scale+data._x,
						  1.f*data._scale+data._x});
    setVec2(&shaderProg, "areaHeight",(vec2){-1.f*data._scale+data._y,
						  1.f*data._scale+data._y});
    setInt(&shaderProg, "maxIterations", data._maxIterations);

    
    useShaderProgram(&shaderProg);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    
    updateContext();
  }

  
  // free data
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  cleanContext();
  return 0;
}
