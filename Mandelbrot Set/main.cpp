#include <iostream>

using namespace std;

// Console width in characters is 119
// Console height in characters is 29

void pan(float& xoff, float& yoff, float& zoom)
{
    cout << "Controls: axis(X/Y followed by a number), zoom(float number)\n";
    char dir;
    float moveby;
    float zoom_index;

    cin >> dir >> moveby;
    if(dir == 'X')
        xoff += moveby;
    else if(dir == 'Y')
        yoff += moveby;

    cin >> zoom_index;
    zoom = zoom_index;
    cout << endl;
}

// Draw the characters based on the number of iterations taken to get to infinity
void drawCharacter(int iterations, int max_iterations)
{
    float symbol_algo = 22.0f * 0.083f;

    // Character sequence .,~-=+'^"![*oqaOQH@G#
    // 22 characters

    if(iterations < symbol_algo)                                            cout << '.';
    else if(iterations >= symbol_algo && iterations < symbol_algo*2)        cout << ',';
    else if(iterations >= symbol_algo*2 && iterations < symbol_algo*3)      cout << '~';
    else if(iterations >= symbol_algo*3 && iterations < symbol_algo*4)      cout << '-';
    else if(iterations >= symbol_algo*4 && iterations < symbol_algo*5)      cout << '=';
    else if(iterations >= symbol_algo*5 && iterations < symbol_algo*6)      cout << '_';
    else if(iterations >= symbol_algo*6 && iterations < symbol_algo*7)      cout << "'";
    else if(iterations >= symbol_algo*7 && iterations < symbol_algo*8)      cout << '^';
    else if(iterations >= symbol_algo*8 && iterations < symbol_algo*9)      cout << '"';
    else if(iterations >= symbol_algo*9 && iterations < symbol_algo*10)     cout << '*';
    else if(iterations >= symbol_algo*10 && iterations < symbol_algo*11)    cout << '!';
    else if(iterations >= symbol_algo*11 && iterations < symbol_algo*12)    cout << '[';
    else if(iterations >= symbol_algo*12 && iterations < symbol_algo*13)    cout << 'o';
    else if(iterations >= symbol_algo*13 && iterations < symbol_algo*14)    cout << 'g';
    else if(iterations >= symbol_algo*14 && iterations < symbol_algo*15)    cout << 'a';
    else if(iterations >= symbol_algo*15 && iterations < symbol_algo*16)    cout << 'O';
    else if(iterations >= symbol_algo*16 && iterations < symbol_algo*17)    cout << 'Q';
    else if(iterations >= symbol_algo*17 && iterations < symbol_algo*18)    cout << 'H';
    else if(iterations >= symbol_algo*18 && iterations < symbol_algo*19)    cout << '@';
    else if(iterations >= symbol_algo*19 && iterations < symbol_algo*20)    cout << 'G';
    else if(iterations >= symbol_algo*20 && iterations < symbol_algo*21)    cout << '#';
    else                                                                    cout << ' ';
}

int main()
{
    /**< VARIABLES >**/
    long int x_offset = -20;
    long int y_offset = 0;
    float xm_offset = 0;
    float ym_offset = 0;
    float zoom = 1.25f;
    int max_iterations = 1000;
    float infinity = 2.0f;

    bool running = true;

    float width = 167, height = 43;
    float horizontal_boundry = width/2;
    float vertical_boundry = height/2;
    float h_mapping;
    float v_mapping;
    /**< !VARIABLES >**/

    // Loop needed for panning controls to work
    while (running)
    {
        // Zoom is calculated here, also the variables used for mapping the  and Y values later
        h_mapping = zoom*2.0f/horizontal_boundry;
        v_mapping = zoom/vertical_boundry;

        // Outer loop iterates over the Imaginary number line (the Y axis)
        for(int im=-vertical_boundry+y_offset; im<=vertical_boundry+y_offset; im++)
        {
            // Nested inner loop iterates over the Real number line (the X axis)
            for(int re=-horizontal_boundry+x_offset; re<=horizontal_boundry+x_offset; re++)
            {
                // Mapping the values from the console resolution to (-2, 2) times the zoom
                float zi = float(im) * v_mapping + ym_offset;
                float zr = float(re) * h_mapping + xm_offset;

                // The initial values are needed so they are stored for the calculations
                float x = 0.0f;
                float y = 0.0f;
                float const_zi = zi;
                float const_zr = zr;
                int iterations = 0;

                // This is where the magic happens. This loop iterates <max_iterations> times
                // and evaluates how many iterations it took for the complex number to reach infinity
                // or whether the number stayed within the set boundaries (infinity)
                while (x*x + y*y <= 4 && iterations < max_iterations)
                {
                    float tempx = x * x - y * y + const_zr;
                    y = 2 * x * y + const_zi;
                    x = tempx;
                    iterations++;
                }

                drawCharacter(iterations, max_iterations);
            }
            // Starts a new line every time the loop gets to the horizontal end of the console screen
            cout << endl;
        }

        // Print current coordinates
        cout << "X:" << horizontal_boundry * h_mapping + xm_offset;
        cout << " Y:" << vertical_boundry * v_mapping + ym_offset << endl;

        // Movement controls are in this function
        pan(xm_offset, ym_offset, zoom);
    }
    return 0;
}
