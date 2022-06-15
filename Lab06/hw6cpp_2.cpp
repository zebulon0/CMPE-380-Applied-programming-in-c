//////////////////////////////////////////////////////////////////////////////
// Linear Least Squares Curve Fitting - student file
//  This program fits a line to the data points in the
//  file provided on the command line (one data point per line of text in the
//  file).
// 03/16/2016   R. Repka    Added Reset class
// 02/20/2016   R. Repka    Added include file hint
// 10/30/2018   R. Repka    Added Reset() method call for students
// 08/11/2019   R. Repka    Added MOVE_IO_CLOSE macro feature
// 10/24/2019   R. Repka    Added read lines
//////////////////////////////////////////////////////////////////////////////
#include <fstream>
#include <list>
using namespace std;
#include <iostream>
#include "Timers.h"         

// add IO and calculation repeat value constant definition macros here




//////////////////////////////////////////////////////////////////////////////
// Class declaration for determining the "best" line for a given set of X-Y
// data points.
//////////////////////////////////////////////////////////////////////////////
class LinearFit
  {
   public:
     // Constructor
     LinearFit(void);
     
     // Reset the data structures
     void Reset(void);

     // Accepts a single X-Y data point and adds it to the collection of points
     // used to determine the line.
     void AddPoint(double X, double Y);

     // Returns the number of data points collected
     int GetNumberOfPoints(void);

     // Returns the constant 'B' in Y = A * X + B
     double GetConstant(void);

     // Returns the coefficient to the linear term 'A' in Y = A * X + B
     double GetLinearCoefficient(void);
   private:
     // Computes the coefficients (when needed)
     void ComputeCoefficients(void);

     // X data list
     list<double> Data_X;

     // Y data list
     list<double> Data_Y;

     // The constant 'B'
     double B;

     // The coefficient to the linear term 'A'
     double A;

     // Flag indicating that the coefficients have been computed
     int CoefficientsComputed;
  }; // LinearFit Class

//////////////////////////////////////////////////////////////////////////////
//  Constructor
//////////////////////////////////////////////////////////////////////////////
LinearFit::LinearFit(void)
  {
   // Initialize the flag indicating that the coefficients have not been computed
   CoefficientsComputed = 0;
  } // Constructor
   
   
//////////////////////////////////////////////////////////////////////////////
//  Resets the data structure
//////////////////////////////////////////////////////////////////////////////
void LinearFit::Reset(void)
  {
   // Initialize the flag indicating that the coefficients have not been computed
   CoefficientsComputed = 0;
  } // Reset()
 
  
//////////////////////////////////////////////////////////////////////////////
//  AddPoint() - Accepts a single point and adds it to the lists
//////////////////////////////////////////////////////////////////////////////
void LinearFit::AddPoint(double X, double Y)
  {
   // Store the data point into the lists
   Data_X.push_back(X);
   Data_Y.push_back(Y);
  } // AddPoint()
   
//////////////////////////////////////////////////////////////////////////////
//  GetNumberOfPoints() - Returns the number of points collected
//////////////////////////////////////////////////////////////////////////////
int LinearFit::GetNumberOfPoints(void)
  {
   return Data_X.size();
  } // GetNumberOfPoints()
   
//////////////////////////////////////////////////////////////////////////////
//  ComputeCoefficients() - Calculate the value of the linear coefficient
// 'A' and the constant term 'B' in Y = A * X + B
//////////////////////////////////////////////////////////////////////////////
void LinearFit::ComputeCoefficients(void)
  {
   // Declare and initialize sum variables
   double S_XX = 0.0;
   double S_XY = 0.0;
   double S_X  = 0.0;
   double S_Y  = 0.0;

   // Iterators
   list<double>::const_iterator lcv_X, lcv_Y;

   // Compute the sums
   lcv_X = Data_X.begin();
   lcv_Y = Data_Y.begin();
   while ((lcv_X != Data_X.end()) && (lcv_Y != Data_Y.end()))
     {
      S_XX += (*lcv_X) * (*lcv_X);
      S_XY += (*lcv_X) * (*lcv_Y);
      S_X  += (*lcv_X);
      S_Y  += (*lcv_Y);
 
     // Iterate
      lcv_X++; lcv_Y++;
     } // while()
 
   // Compute the line intercept 
   B = (((S_XX * S_Y) - (S_XY * S_X)) / ((Data_X.size() * S_XX) - (S_X * S_X)));

   
   // Compute the slope of the line
   A = (((Data_X.size() * S_XY) - (S_X * S_Y)) / ((Data_X.size() * S_XX) - (S_X * S_X)));

   // Indicate that the Coefficients have been computed
   CoefficientsComputed = 1;
  } // ComputeCoefficients()

//////////////////////////////////////////////////////////////////////////////
//  GetConstant() - Calculate the value of the constant 'B' in Y = A * X + B
//////////////////////////////////////////////////////////////////////////////
double LinearFit::GetConstant(void)
  {
   if (0 == CoefficientsComputed)
     {
      ComputeCoefficients();
     } // if()

   return B;
  } // GetConstant()
   
//////////////////////////////////////////////////////////////////////////////
//  GetLinearCoefficient() - Calculate the value of the linear coefficient
// 'A' in Y = A * X + B
//////////////////////////////////////////////////////////////////////////////
double LinearFit::GetLinearCoefficient(void)
  {
   if (0 == CoefficientsComputed)
     {
      ComputeCoefficients();
     } // if()

   return A;
  } // GetLinearCoefficient()

//////////////////////////////////////////////////////////////////////////////
// Main program to fit a line to the data.
//////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
  {
   // Insert your data and calc timing macro definitions here
   #ifdef EN_TIME
   DECLARE_TIMER(DataTimer);
   DECLARE_TIMER(CalcTimer);
   #endif  
   
   // Declare a pointer to the LinearFit object
   LinearFit *DataSet = NULL;
   
   // Data line counter
   int lines = 0; 
   
   // Check that a command line argument was provided
   if (1 != argc)
     {
      // Boolean variable to indicate all data has been read.
      bool Done;

      // Declare an input stream
      ifstream InputFile;

      // Variables to hold the constant and linear coefficients of the line
      double A, B;

     // Insert your data timer start loops here
      #ifdef EN_TIME
      START_TIMER(DataTimer);
      DECLARE_REPEAT_VAR(data_repeat);
      BEGIN_REPEAT_TIMING(200, data_repeat);
      #endif
            
      // Attach the input stream to the command line argument (it should be a
      // filename).
      InputFile.open(argv[1]);

      // Instantiate and object for determining the line
      DataSet = new LinearFit;

      // Read all of the data from the file
      do {
         // Temporary variables to hold data read from file
         double X, Y;
   
         // Read the X-Y data point
         InputFile >> X >> Y;
         lines++;
   
         // If read did not go beyond end-of-file, add it to the data set
         if (!InputFile.eof()) 
           {
            // Add the data point
            DataSet->AddPoint(X, Y);
            Done = false;
           } // if()
         else
           {
            // Set the flag indicating that all the data is gone
            Done = true;
           } // if...else()
        } while (!Done);

         // Disconnect the input file from the stream inside the timing loop
         #ifdef MOVE_IO_CLOSE
         InputFile.close();
         InputFile.clear();
         #endif
         
      // Insert your closing data timing loop here and 
      // print the results 
      #ifdef EN_TIME
      END_REPEAT_TIMING;
      STOP_TIMER(DataTimer);
      PRINT_TIMER(DataTimer);
      PRINT_RTIMER(DataTimer, 200);
      

      // Insert your starting cal timing loop here
      START_TIMER(CalcTimer);
      DECLARE_REPEAT_VAR(calc_repeat);
      BEGIN_REPEAT_TIMING(40000, calc_repeat);
      #endif

      // Calculate the coefficients of the best linear fit
      A = DataSet->GetLinearCoefficient();
      B = DataSet->GetConstant();
      DataSet->Reset();
                                
      // Insert your closing calc timing loop here and 
      // print the results 
      #ifdef EN_TIME
      END_REPEAT_TIMING;
      STOP_TIMER(CalcTimer);
      PRINT_TIMER(CalcTimer);
      PRINT_RTIMER(CalcTimer, 40000);
      #endif
 
      
      
      // Destroy the data set object
      delete DataSet;
      DataSet = NULL;
      
      // Print out the line that fits the data set.
      cout << lines << " data lines processed, ";
      cout << "the best least squares line is: Y = " << A << " * X + " << B << endl;

     } // if (1 == argc)
   else
     { 
      // Display program usage information
      cout << "Fits a line to data points" << endl;
      cout << "(C++ Version) Usage: " << argv[0] << " Filename" << endl;
     } // if...else()

   return 0; 
  } // main()
