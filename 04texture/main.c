#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <math.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

char* readShaderFile(char* filename);

int main(void)
{
	glfwInit(); // Initilalisation de glfw ( librairie de fenêtrage )

	//On demande OpenGL 3.3 à GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Crée une fenêtre GLFW de taille 640x480
	GLFWwindow* window = glfwCreateWindow(640, 480, "Demo OpenGL cslabs", NULL, NULL);

	// "active" OpenGL dans la fenêtre actuelle
	glfwMakeContextCurrent(window);

	glewInit(); //Initialisation de glew ( chargeur d'OpenGL )

	//Afficher la version et le driver utilisé ( par ex pour vérifier que elle correspond à celle demandée )
	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);

	// Spécifie 6 points chacun définit par deux coordonnées (x, y)
	float geometryData[] = {-1.0, -1.0, 1.0, -1.0, 1.0, 1.0,
							-1.0, -1.0, 1.0, 1.0, -1.0, 1.0};

	//Crée un buffer ( Vertex Buffer Object ) pour contenir ces données géométriques
	GLuint vbo;
	glGenBuffers(1, &vbo);

	// Sélectionne ce buffer (cf machine à états)
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// Envoie les données dans le buffer sélectionné ( 6 * 2 * 4 bytes )
	glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), geometryData, GL_STATIC_DRAW);

	// Crée un Vertex Array Object, qui stocke en fait une configuration spécifique de données à utiliser
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao); // Selectionne ce vao dans la machine à état

	// Active l'entrée d'attributs #0
	glEnableVertexAttribArray(0);

	// Re-séléctionne notre buffer contenant nos points, et spécifie comment ils sont rangés dedans.
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL); // L'entrée d'atributs 0 renverra des couples de 2 valeurs (x,y) au format float, depuis le buffer 'vbo'

	// Code source du vertex shader
	const char* vertexShaderText = readShaderFile("vertex.glsl");
	
	// Code source du fragment shader
	const char* fragmentShaderText = readShaderFile("fragment.glsl");

	// Crée un objet vertex shader, fournit la source et la compile
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderText, NULL);
	glCompileShader(vertexShader);

	// Crée un objet fragment shader, fournit la source et la compile
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderText, NULL);
	glCompileShader(fragmentShader);

	// Crée un programme shader qui utilise le vertex et fragment shader définit plus haut
	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	//On récupère l'emplacement de la variable uniforme "myColor"
	GLint myColorLocation = glGetUniformLocation(program, "myColor");
	printf("myColorLocation = %d\n", myColorLocation);

	//Idem pour 'myPosition'
	GLint myPositionLocation = glGetUniformLocation(program, "myPosition");
	printf("myPositionLocation = %d\n", myPositionLocation);

	float angle = 0.0F;
	
	//Active la synchronisation verticale
	glfwSwapInterval(1);
	
	int x, y, n;
	unsigned char* image_data = stbi_load("cslabs.png", &x, &y, &n, 4);
	printf("Image chargee avec succes: %dx%d\n", x, y);
	
	int image_size = x * y * 4;
	
	GLuint texture;
	glGenTextures(1, &texture);
	
	glBindTexture(GL_TEXTURE_2D, texture);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);

	//Tant que l'utilisateur ne requiert pas de fermer la fenêtre
	while (!glfwWindowShouldClose(window))
	{
		// Spécifie une couleur pour effacer l'écran, puis efface l'écran
		glClearColor(1.0F, 0.3F, 0.F, 1.0F);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(program); // En utilisant le shader 'program'

		//On envoie le vecteur (1,1,0,1) dans la variable uniforme "myColor"
		glUniform4f(myColorLocation, 1.0F, 1.0F, 0.0F, 1.0F);

		angle = angle + 0.01f;
		glUniform2f(myPositionLocation, sin(angle) * 0.4f, cos(angle) * 0.4f);

		glBindVertexArray(vao); // La configuration 'vao'
		glDrawArrays(GL_TRIANGLES, 0, 6); // Dessiner 6 points sous forme de triangles ( donc deux triangle formé de 3 pts chacuns )

		//Échange le buffer visible et celui de travail	( == montre l'image que l'on vient de créer )
		glfwSwapBuffers(window);

		//Vérifie si de nouveaux évênements se sont produits (ex: fenêtre fermée)
		glfwPollEvents();
	}

	//Tuer GLFW quand le programme se termine
	glfwTerminate();
	return 0;
}

// Lis un fichier texte
char* readShaderFile(char* filename) {
	char * buffer = 0;
	long length;
	FILE * f = fopen (filename, "rb");

	if(f) {
		fseek(f, 0, SEEK_END);
		length = ftell(f);
		fseek(f, 0, SEEK_SET);
		
		buffer = malloc(length);
		if(buffer) {
			fread(buffer, 1, length, f);
		}
		fclose(f);
	}
	
	return buffer;
}