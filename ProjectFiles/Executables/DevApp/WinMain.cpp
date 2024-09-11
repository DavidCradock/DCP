#include <windows.h>
#include "../../StaticLibs/DavesCodeLib/DavesCodeLibrary.h"
#ifdef _DEBUG
#pragma comment(lib, "../../../Output/StaticLibs/DavesCodeLib_DEBUG.lib")
#else
#pragma comment(lib, "../../../Output/StaticLibs/DavesCodeLib.lib")
#endif

using namespace DCL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // Here we go! :)

    // We throw exceptions from DCL for critical, non-recoverable, execeptional circumstances, so here's a try/catch exception block which we wrap out main program loop inside.
    // With any unrecoverable errors, we catch them below in the catch (CException &exception) section of code near the bottom.
    try
    {
        // Create renderer manager
        CRendererManager* pRenderManager = new CRendererManager;
        ThrowIfMemoryNotAllocated(pRenderManager);

        // Create a renderer, in this case OpenGL
        CRendererBase* pRenderer = pRenderManager->init("opengl");

        // Initialise the renderer, creating a window and setting up the graphics API using default settings
        pRenderer->initialise();

        bool bWindowResized, bWindowMinimized, bWindowHasBeenAskedToClose = false;

        while (!bWindowHasBeenAskedToClose)
        {
            pRenderer->updateWindow(bWindowResized, bWindowMinimized, bWindowHasBeenAskedToClose);
        }

        // Shutdown the renderer, cleaning up the API and closing the window.
        pRenderer->shutdown();

        // Test the log class
        CLog logTest("logTest.txt");
        logTest.run_test();
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }
    // Here we catch any thrown exceptions and deal with them.
    catch (CException &exception)
    {
        // An exception has been thrown, we'll create a wide string from the error string contained within the exception so
        // that we can pass the thing to a simple MessageBox to let the user know what went wrong.
        std::wstring strw = StringUtils::stringToWide(exception.mstrException);
        MessageBox(NULL, strw.c_str(), L"Sorry, an exception has been thrown...", MB_OK);
    }
    return 0;
}