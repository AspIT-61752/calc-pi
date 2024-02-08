#include <stdio.h>
#include <math.h>
#include <time.h>

#define DELTA_X 0.001
#define RADIUS 1.0

long timediff(clock_t t1, clock_t t2) {
    long elapsed;
    elapsed = ((double)t2 - t1) / CLOCKS_PER_SEC * 1000;
    return elapsed;
}

int main(int argc, char *argv[])
{
    double x, y, delta_x, Area, pi;

    printf("argc: %d\n", argc);
    printf("argv[0]: %s\n", argv[0]);
    printf("argv[1]: %s\n", argv[1]);

    // If there isn't an argument, use the default value
    if (argc < 2)
    {
        delta_x = DELTA_X;
        printf("Using default samples: %.7f\n", delta_x);
    }
    else
    {
        // double atof(char* string); converts string to float
        double samples = atof(argv[1]);

        // If the input samplerate is less than 100, use the default value
        if (samples < 100)
        {
            delta_x = DELTA_X; // default value (1000)
            printf("Unsupported sample size: %f\n", samples);
            printf("Using default samples: %f\n", 1./delta_x);
        }
        else
        {
            // double atof(char* string); converts string to float
            delta_x = 1. / samples;
            printf("Samples: %s, delta_x: %.7f\n", argv[1], delta_x);
        }
    }
    
    // Area calculation here:
    
    // area of circle: A = pi*r^2
    // pi = A / r^2
    // r = 1.0
    // Pythagorean theorem for a circle: x^2 + y^2 = r^2
    // https://youtu.be/Nar9Gt8x7Fc 


    // x^2 + y^2 = r^2 
    // = x^2 - x^2 + y^2 = r^2 - x^2 
    // = y^2 = r^2 - x^2
    // y = sqrt(r^2 − x^2)
    // y = sqrt(1^2 - x^2)
    // y = sqrt(1 - x^2)

    // integral of sqrt(1 - x^2) dx from 0 to 1 is pi/4
    // ∫ from 0 to 1 √(r2 - x2) dx ; Straight from Google "find the area of quarter circle using integral" https://www.physicsforums.com/threads/definite-integral-of-a-quarter-circle.658403/
    // center of the circle is 0,0 (x, y)
    // x -> 1
    // for x = 0; to 1; x += dx;
    // Area_q = sqrt(1−x^2) * dx

    clock_t start, end;
    long elapsedTime;

    // Time stamp start
    start = clock();

    unsigned int counter = 0; // Debugging 
    for (x = 0.0; x < RADIUS; x += delta_x) // Iterate over x from 0 to RADIUS
    {
        counter++; // Debugging 
        // Calculate y for the quarter circle
        y = sqrt(RADIUS * RADIUS - x * x);

        // Calculate the area of the quarter circle
        Area += y * delta_x;        
    }

    // Time stamp end
    end = clock();

    elapsedTime = timediff(start, end);

    // Prints the time taken in minutes, seconds and milliseconds
    printf("Time taken: %ld ms\n", elapsedTime);

    // These doesn't work if it's too short 
    printf("Time taken: %.3f sec\n", (double)elapsedTime / 1000);
    // printf("Time taken: %.2ld min\n", elapsedTime / 60000);

    pi = Area * 4.; // Extend from the quadrant to the whole circle
    printf("pi is about = %.21lf\n", pi);
    // Pi = 3.14159265359 ...
    
    printf("counter = %d\n", counter); // Debugging 

    return 0;
}