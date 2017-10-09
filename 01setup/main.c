#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdbool.h>

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

	//Tant que l'utilisateur ne requiert pas de fermer la fenêtre
	while (!glfwWindowShouldClose(window))
	{
		// Spécifie une couleur pour effacer l'écran, puis efface l'écran
		glClearColor(0.0F, 0.5F, 1.0F, 1.0F);
		glClear(GL_COLOR_BUFFER_BIT);

		//Échange le buffer visible et celui de travail	( == montre l'image que l'on vient de créer )
		glfwSwapBuffers(window);

		//Vérifie si de nouveaux évênements se sont produits (ex: fenêtre fermée)
		glfwPollEvents();
	}

	//Tuer GLFW quand le programme se termine
	glfwTerminate();
	return 0;
}
