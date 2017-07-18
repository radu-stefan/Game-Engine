// NewTrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Vertex.h"
#include "Shaders.h"
#include <conio.h>
#include "Globals.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Camera.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include

using namespace std;


int Init ( ESContext *esContext )
{
	ResourceManager::getInstance()->Init();
	SceneManager::getInstance()->Init();

	return 0;
}

void Draw ( ESContext *esContext )
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	SceneManager::getInstance()->Draw(esContext);

	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );
}

void Update ( ESContext *esContext, float deltaTime )
{

	SceneManager::getInstance()->Update(esContext, deltaTime);

}

void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{
	//esContext->hWnd
	//getcursorstate
	//getkeyst
	//printf("%c\t",key);
	//atunci cand dam drumul la buton bIsPressed == 0;
	//printf("%d\n",bIsPressed);
	Camera *c = SceneManager::getInstance()->GetActiveCamera();
	if (key == '1') {
		SceneManager::getInstance()->activeCamera = 1;
	}
	if (key == '2') {
		SceneManager::getInstance()->activeCamera = 2;
	}
	if (key == 'W') {
		c->SetDirectie(-1);
		c->moveOz();
	}
	if (key == 'A') {
		c->SetDirectie(-1);
		c->moveOx();
	}
	if (key == 'D') {
		c->SetDirectie(1);
		c->moveOx();
		c->SetDirectie(-1);
	}
	if (key == 'S') {
		c->SetDirectie(1);
		c->moveOz();
		c->SetDirectie(-1);
	}
	if (key == 'Z') {
		c->SetDirectie(1);
		c->moveOy();
		c->SetDirectie(-1);
	}
	if (key == 'X') {
		c->SetDirectie(-1);
		c->moveOy();
		c->SetDirectie(1);
	}
	if (key == 'Q') {
		c->rotateOy();
	}
	if (key == 'E') {
		c->SetRotateSpeed(-c->GetRotateSpeed());
		c->rotateOy();
		c->SetRotateSpeed(-c->GetRotateSpeed());
	}
	if (key == 'L' && bIsPressed == 0) {

	}
}

void CleanUp()
{
	ResourceManager::getInstance()->freeResources();
	SceneManager::getInstance()->freeResources();
}

int _tmain(int argc, _TCHAR* argv[])
{
	//identifying memory leaks
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF ); 

	ESContext esContext;
    esInitContext ( &esContext );

	esCreateWindow ( &esContext, "Alpha", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if ( Init ( &esContext ) != 0 )
		return 0;

	esRegisterDrawFunc ( &esContext, Draw );
	esRegisterUpdateFunc ( &esContext, Update );
	esRegisterKeyFunc ( &esContext, Key);

	esMainLoop ( &esContext );
	
	//releasing OpenGL resources
	CleanUp();


	printf("Press any key...\n");
	_getch();

	
	return 0;
}

