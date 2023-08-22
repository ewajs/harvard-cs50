//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// Window's center coordinates
#define XCENTER WIDTH / 2
#define YCENTER HEIGHT / 2

// paddle's height and width
#define PHEIGHT HEIGHT / 40 // one 40th part of HEIGHT
#define PWIDTH WIDTH / 5 // one fifth of WIDTH

// paddle's Y position 20px margin from bottom (fixed)
#define PADDLEY HEIGHT - PHEIGHT - 40

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// space between bricks (in px)
#define BSPACE 5

// X margin between first and last brick and window's edge
#define XBMARGIN 10

// Y margin between top row of bricks
#define YBMARGIN 40

// dynamic brick width
#define BWIDTH (WIDTH - 2 * XBMARGIN - (COLS - 1) * BSPACE) / COLS

// dynamic brick height (so bricks take 1/5 of the window)
#define BHEIGHT (HEIGHT / 5 - (ROWS - 1) * BSPACE) / ROWS

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// velocity modulus
#define VMOD 4

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

// global variable
bool flank;

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // add it to the window
    add(window, ball);
    
    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);
    
    // add it to the window
    add(window, paddle);
    
    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // add it to the window
    add(window, label);
    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    // X axis velocity (initially random)
    double velocityX = drand48();
    printf("%f\n", velocityX);
    // Y axis velocity (so as velocity modulus is 1)
    double velocityY = sqrt(1 - velocityX * velocityX);
    

    velocityX = VMOD * velocityX;
    velocityY = VMOD * velocityY;
    
    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        // check for mouse event
        GEvent event = getNextEvent(MOUSE_EVENT);

        // if event is captured
        if (event != NULL)
        {
            // if it was mouse movement
            if (getEventType(event) == MOUSE_MOVED)
            {
                
                // get cursor coordinates
                double x = getX(event);
                // check that the paddle won't be out of bounds
                if (x > PWIDTH / 2 && x < WIDTH - PWIDTH / 2)
                {
                    // adjust so center will align
                    x = x - PWIDTH / 2;
                    
                    // set paddle's center location to cursor's
                    setLocation(paddle, x,PADDLEY);
                
                }
                // this is to solve an issue: if the mouse moves too fast
                // the paddle will get stuck before reaching the edge of 
                // the window, so if x is lower or higher than the limit, 
                // it should stay right at the edge.
                else if (x < PWIDTH / 2)
                {
                    // set paddle's center location to left edge (0)
                    setLocation(paddle, 0,PADDLEY);
                }
                else if (x > WIDTH - PWIDTH / 2)
                {
                    // set paddle's center to right edge (WIDTH - PWIDTH)
                    setLocation(paddle, WIDTH - PWIDTH,PADDLEY);
                }
            }
        }
        
        // move ball
        move(ball,velocityX, velocityY);

        // bounce off right edge of window
        if (getX(ball) + 2 * RADIUS >= WIDTH)
        {
            velocityX = -velocityX;
        }

        // bounce off left edge of window
        else if (getX(ball) <= 0)
        {
            velocityX = -velocityX;
        }
        
        // bounce off top edge of window
        else if (getY(ball) <= 0)
        {
            velocityY = -velocityY;
        }
        
        // hit bottom edge of window -> lose life, restart ball
        else if (getY(ball) + 2 * RADIUS >= HEIGHT)
        {
            
            lives--;
            velocityX = drand48();
            velocityY = sqrt(1 - velocityX * velocityX);
            velocityX = VMOD * velocityX;
            velocityY = VMOD * velocityY;
            setLocation(ball, XCENTER - RADIUS,  YCENTER - RADIUS);
            waitForClick();
        }
        
        // Look for a collision
        GObject object = detectCollision(window,ball);
        
        // check that the ball actually collided
        // this is very important, DO NOT REMOVE
        // if this is removed the program might crash
        // if the ball hasn't collided and you pass
        // NULL to strcmp it will try to acces a 
        // protected memory space and cause a Segmentation Fault!!
        if (object != NULL)
        {
            // if collided with paddle -> bounce vertically
            if (object == paddle)
            {
                velocityY = -velocityY;
            }
            
            // if collided with brick -> delete brick and bounce
            else if (!strcmp(getType(object), "GRect"))
            {
                removeGWindow(window, object);
                
                // detect which flank of the brick has been hit
                double xbrick = getX(object);
                double ybrick = getY(object);
                double xball = getX(ball);
                double yball = getY(ball);
                
                // if brick has been hit vertically
                if (ybrick + BHEIGHT >= yball || ybrick <= yball + 2 * RADIUS)
                {    
                    velocityY = -velocityY;
                }
                // else, it has been hit horizontally
                else
                {
                    velocityX = -velocityX;
                }
                
                // award a point and update
                points++;
                bricks--;
                updateScoreboard(window, label, points);
            }
        }
       
        pause(10);
    }
    
    // if the player won, congratulate him/her!
    if (bricks == 0)
    {
        setLabel(label, "PLAYER WON!");
    }
    
    // if player lost, notify him/her :(
    else if (lives == 0)
    {
        setLabel(label, "PLAYER LOST!");
    }
    
    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
    
    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
    
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    double brickY = YBMARGIN;
    char* colors[ROWS] = {"RED", "ORANGE", "GREEN", "BLUE", "CYAN"};
    for (int i = 0; i < ROWS; i++)
    {
        double brickX = XBMARGIN;
        for (int j = 0; j < COLS; j++)
        {
            GRect brick = newGRect(brickX, brickY, BWIDTH, BHEIGHT);
            setFilled(brick, true);
            setColor(brick, colors[i]);
            add(window, brick);
            brickX += BWIDTH + BSPACE; 
        }
        brickY += BHEIGHT + BSPACE;
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    double x = XCENTER - RADIUS;
    double y = YCENTER - RADIUS;
    GOval ball = newGOval(x, y, 2 * RADIUS, 2 * RADIUS);
    setFilled(ball, true);
    setColor(ball, "BLACK");
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    // set x so paddle's center aligns with window center
    double x = (HEIGHT - PWIDTH) / 2;
    // create paddle
    GRect paddle = newGRect(x,PADDLEY,PWIDTH, PHEIGHT);
    // set paddle to be filled black
    setFilled(paddle, true);
    setColor(paddle, "BLACK");

    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel label = newGLabel("0");
    setLocation(label, XCENTER - getWidth(label), YCENTER - getHeight(label));
    setFont(label, "*-*-36");
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
