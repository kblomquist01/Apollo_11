/*************************************************************
 * 1. Name: https://prod.liveshare.vsengsaas.visualstudio.com/join?4EA646C847464CA7C37D25BEA34779DEEC67
 *      -your name-
 * 2. Assignment Name:
 *      Practice 02: Physics simulator
 * 3. Assignment Description:
 *      Compute how the Apollo lander will move across the screen
 * 4. What was the hardest part? Be as specific as possible.
 *      -a paragraph or two about how the assignment went for you-
 * 5. How long did it take for you to complete the assignment?
 *      -total time in hours: reading the assignment, submitting, etc.
 **************************************************************/

#include <iostream>  // for CIN and COUT
using namespace std;

#define WEIGHT   15103.000   // Weight in KG
#define GRAVITY     -1.625   // Vertical acceleration due to gravity, in m/s^2
#define THRUST   45000.000   // Thrust of main engine, in Newtons (kg m/s^2)

/***************************************************
 * COMPUTE DISTANCE
 * Apply inertia to compute a new position using the distance equation.
 * The equation is:
 *     s = s + v t + 1/2 a t^2
 * INPUT
 *     s : original position, in meters
 *     v : velocity, in meters/second
 *     a : acceleration, in meters/second^2
 *     t : time, in seconds
 * OUTPUT
 *     s : new position, in meters
 **************************************************/
 // your function goes here
double computeDistance(double s, double v, double a, double t) {
    return s + v * t + 0.5 * a * (t * t);
}
 /**************************************************
  * COMPUTE ACCELERATION
  * Find the acceleration given a thrust and mass.
  * This will be done using Newton's second law of motion:
  *     f = m * a
  * INPUT
  *     f : force, in Newtons (kg * m / s^2)
  *     m : mass, in kilograms
  * OUTPUT
  *     a : acceleration, in meters/second^2
  ***************************************************/
  // your function goes here
  double computeAcceleration(double f, double m)
  {
      double a = f / m;
      return a;
  }

  /***********************************************
   * COMPUTE VELOCITY
   * Starting with a given velocity, find the new
   * velocity once acceleration is applied. This is
   * called the Kinematics equation. The
   * equation is:
   *     v = v + a t
   * INPUT
   *     v : velocity, in meters/second
   *     a : acceleration, in meters/second^2
   *     t : time, in seconds
   * OUTPUT
   *     v : new velocity, in meters/second
   ***********************************************/
   // your function goes here
double computeVelocity(double v, double a, double t) {
    return v + a * t;
}

   /***********************************************
    * COMPUTE VERTICAL COMPONENT
    * Find the vertical component of a velocity or acceleration.
    * The equation is:
    *     cos(a) = y / total
    * This can be expressed graphically:
    *      x
    *    +-----
    *    |   /
    *  y |  / total
    *    |a/
    *    |/
    * INPUT
    *     a : angle, in radians
    *     total : total velocity or acceleration
    * OUTPUT
    *     y : the vertical component of the total
    ***********************************************/
    // your function goes here
int findVerticalComponent(double a, double total) {
    return cos(a) * total;
}
    /***********************************************
     * COMPUTE HORIZONTAL COMPONENT
     * Find the horizontal component of a velocity or acceleration.
     * The equation is:
     *     sin(a) = x / total
     * This can be expressed graphically:
     *      x
     *    +-----
     *    |   /
     *  y |  / total
     *    |a/
     *    |/
     * INPUT
     *     a : angle, in radians
     *     total : total velocity or acceleration
     * OUTPUT
     *     x : the vertical component of the total
     ***********************************************/
     // your function goes here
double findHorizontalComponent(double a, double total) {
    return sin(a) * total;
}
     /************************************************
      * COMPUTE TOTAL COMPONENT
      * Given the horizontal and vertical components of
      * something (velocity or acceleration), determine
      * the total component. To do this, use the Pythagorean Theorem:
      *    x^2 + y^2 = t^2
      * where:
      *      x
      *    +-----
      *    |   /
      *  y |  / total
      *    | /
      *    |/
      * INPUT
      *    x : horizontal component
      *    y : vertical component
      * OUTPUT
      *    total : total component
      ***********************************************/
      // your function goes here
double findTotalComponent(double x, double y) {
    double total = (pow(x, 2) + pow(y, 2));
    return sqrt(total);
}

      /*************************************************
       * RADIANS FROM DEGEES
       * Convert degrees to radians:
       *     radians / 2pi = degrees / 360
       * INPUT
       *     d : degrees from 0 to 360
       * OUTPUT
       *     r : radians from 0 to 2pi
       **************************************************/
       // your function goes here
double radiansFromDegrees(double d) {
    // d / 360 
    return (d / 360) * 2 * 3.14159265;
}
       /**************************************************
        * PROMPT
        * A generic function to prompt the user for a double
        * INPUT
        *      message : the message to display to the user
        * OUTPUT
        *      response : the user's response
        ***************************************************/
        double prompt(string message)
        {
            double response;

            cout << message;
            cin >> response;

            return response;
        }

        /****************************************************************
         * 5 SECONDS
         * Calculates the next 5 seconds for the rover
         ****************************************************************/
        void fiveSeconds(double dx, double dy, double y, double x, double aDegrees, double t, double currentTime) {

            double aRadians = radiansFromDegrees(aDegrees);            // Angle in radians
            double accelerationThrust = computeAcceleration(THRUST, WEIGHT);  // Acceleration due to thrust 
            double ddxThrust = findHorizontalComponent(aRadians, THRUST);           // Horizontal acceleration due to thrust
            double ddyThrust = findVerticalComponent(aRadians, THRUST);           // Vertical acceleration due to thrust
            double ddx = computeAcceleration(ddxThrust, WEIGHT);       //-2.105;          // Total horizontal acceleration
            double ddy = computeAcceleration(ddyThrust, WEIGHT) + GRAVITY;  //0.48;               // Total vertical acceleration
            double v;                   // Total velocity

            for (int _ = 0; _ < 5; _++) {
                // your code goes here
                dx = computeVelocity(dx, ddx, t);
                dy = computeVelocity(dy, ddy, t);
                x = computeDistance(x, dx, ddx, t);
                y = computeDistance(y, dy, ddy, t);
                v = findTotalComponent(dx, dy);
                // Output
                cout.setf(ios::fixed | ios::showpoint);
                cout.precision(2);
                cout << "\tNew position:   (" << x << ", " << y << ")m\n";
                cout << "\tNew velocity:   (" << dx << ", " << dy << ")m/s\n";
                cout << "\tTotal velocity:  " << v << "m/s\n\n";
            }
        }
        /****************************************************************
         * MAIN
         * Prompt for input, compute new position, and display output
         ****************************************************************/
int main()
{
    // Prompt for input and variables to be computed
    double dx = prompt("What is your horizontal velocity (m/s)? ");
    double dy = prompt("What is your vertical velocity (m/s)? ");
    double y = prompt("What is your altitude (m)? ");
    double x = prompt("What is your position (m)? ");
    double aDegrees = prompt("What is the angle of the LM where 0 is up (degrees)? ");
    double t = 1;//prompt("What is the time interval (s)? ");
    double currentTime = 0;

    

    return 0;
}