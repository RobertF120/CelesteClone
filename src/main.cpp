// ######################################################################################################
//                                          Platform Globals
// ######################################################################################################
static bool running = true;

// ######################################################################################################
//                                          Platform Functions
// ######################################################################################################
bool platform_create_window(int width, int height, char* title);
void platform_update_window();


// ######################################################################################################
//                                         windows platform 
// ######################################################################################################
#ifdef _WIN32
#define WIN32_LEAN_MEAN
#define NOMINMAX
#include <windows.h>


// ######################################################################################################
//                                         windows Globals
// ######################################################################################################
static HWND window;



// ######################################################################################################
//                                       Platform Implementations
// ######################################################################################################
LRESULT CALLBACK windows_window_callback(HWND window, UINT msg,WPARAM wParam, LPARAM LParam)
{
    LRESULT result = 0;

    switch(msg){
        case WM_CLOSE:
        {
            running = false;
            break;
        }
    
    
        default:
        {
            // Let windows hadle the default input for now
            result = DefWindowProcA(window, msg, wParam, LParam);
        }   
    
    }

    return result;

    

}



bool platform_create_window(int width, int height, char* title){
    HINSTANCE instance = GetModuleHandleA(0);

    WNDCLASS wc = {};
    wc.hInstance = instance;
    wc.hIcon = LoadIcon(instance, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);  // this mean we decide the look of the cursor(arrow)
    wc.lpszClassName = title;                  // This not the title, just a unique identifier(id)
    wc.lpfnWndProc = windows_window_callback;  // callback for input into the Window

    if(!RegisterClassA(&wc)){
        return false;
    }
    
    // WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBox
    int dwStyle = WS_OVERLAPPEDWINDOW;


     window = CreateWindowExA(0,title,       // this reference lpszClassName from wc
                                    title,      // this it the actual Title 
                                    dwStyle,
                                    100,
                                    100,
                                    width,
                                    height,
                                    NULL,         //parent
                                    NULL,        //menu
                                    instance,
                                    NULL);    //lpParm

    if (window == NULL){
        return false;
    }

    ShowWindow(window, SW_SHOW);

    return true;

}
void platform_update_window(){
    MSG msg;

    while(PeekMessageA(&msg, window,0,0, PM_REMOVE)){
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }
}

#endif


int main(){
    platform_create_window(1200, 720, "Celesteclone");

    while(running){
        //update
        platform_update_window();
    }
    return 0;
}