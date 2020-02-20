#include <iostream>
#include <string>
#include <cmath>
#include <stdlib.h>
#include <time.h>

double points[10];
double fitness[10];
double epsilon = 0.01;
double a = 0.7;


double MaximizingFunction(double x)
{
  return (4+(2*x) + (2*sin(20*x)) - (4*(x*x)));
}

double CalculateSumOfFitnesses(double* arr)
{
  double sum = 0.0;
  for(int i = 0; i < 10; i++)
  {
    sum = sum + arr[i];
  }

  return sum;
}

double Crossover(double x, double y)
{
  return ((a*x) + ((1-a)*y));
}

int main()
{
  srand(time(NULL)); //generate random seed

  //setting point values
  for(int i = 0; i < 10; i++)
  {
    points[i] = 0.01*i*10;
  }

  //Generation generator
  for(int j = 0; j < 15; j++)
  {
    std::cout << "\nGeneration: " << j << '\n';

    //calculates fitness described from the maximizing function
    for(int i = 0; i < 10; i++)
    {
      fitness[i] = MaximizingFunction(points[i]);
    }

    //prints out the points and their fitnesses
    for(int i = 0; i < 10; i++)
    {
      std::cout << points[i] << " with fitness: " << fitness[i] << '\n';
    }

    double sum = CalculateSumOfFitnesses(fitness); //total sum of fitnesses
    int randomNum = rand() % (int)sum; //threshold. The fitness that makes tempSum > randomNum
    double tempSum = 0;
    double chosenOne; //the point whose fitness pushes over the randomNum. This is how I'm calculating probability

    //figure out the chosen individual for repro to next generation
    for(int i = 0; i < 10; i++)
    {
      tempSum = tempSum + fitness[i];
      if(tempSum > randomNum)
      {
        chosenOne = points[i];
        break;
      }
    }

    double chanceForMutation;
    //mutation
    for(int i = 0; i < 10; i++)
    {
      if(points[i] != chosenOne)
      {
        chanceForMutation = (rand() % 100)+1;
        if(chanceForMutation <= 30)
        {
          points[i] = points[i] - epsilon;
          if(points[i] < 0)
          {
            points[i] = 0;
          }
        }

        else if(chanceForMutation > 30 && chanceForMutation <= 70)
        {
          points[i] = points[i];
        }

        else
        {
          points[i] = points[i] + epsilon;
          if(points[i] > 1)
          {
            points[i] = 1;
          }
        }
        points[i] = Crossover(points[i], points[9-i]); //performs the crossover operation
        fitness[i] = MaximizingFunction(points[i]); //recalculates the fitness after mutation and crossover
      }
    }

    std::cout << "\n\nNEW POINTS\n";

    //prints the new set of points and their
    for(int i = 0; i < 10; i++)
    {
      std::cout << points[i] << " with fitness: " << fitness[i] << '\n';
    }
  }

  return 0;
}
