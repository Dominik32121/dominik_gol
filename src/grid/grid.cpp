#include "grid.hpp"
#include <iostream>
#include <string>
#include <fstream>

//constructor
grid::grid(int width, int height)
{
  this->width = width;
  this->height = height;

  cells = std::make_unique<cell[]>(width*height);
}

grid::grid(int width, int height, std::string path)
{
  this->width = width;
  this->height = height;

  cells = std::make_unique<cell[]>(width*height);

  from_csv(path);
}
//initial state from csv file
void grid::from_csv(std::string path)
{
  std::ifstream file;
  file.open(path);
  //number of rows
  int lineno = 0;
  //for every row
  for (std::string line; getline(file, line); lineno++)
  {
    bool a;
    for (int i = 0; i < line.size(); i+=2)
    {
      //character to bool
      if (line[i] == '0'){cells[i/2 + width*lineno].data = 0;}
      else {cells[i/2 + width*lineno].data = 1;}
    }
  }
}
//index array easily
bool grid::get_cell(int i, int j)
{
  return cells[j + i*width].data;
}
//neighbors
bool grid::north(int i, int j)
{
  return get_cell((i - 1 + height) % height, j);
}

bool grid::south(int i, int j)
{
  return get_cell((i + 1) % height, j);
}

bool grid::east(int i, int j)
{
  return get_cell(i, (j + 1) % width);
}

bool grid::west(int i, int j)
{
  return get_cell(i, (j - 1 + width) % width);
}

bool grid::north_east(int i, int j)
{
  return get_cell((i - 1 + height) % height, (j + 1) % width);
}

bool grid::north_west(int i, int j)
{
  return get_cell((i - 1 + height) % height, (j - 1 + width) % width);
}

bool grid::south_east(int i, int j)
{
  return get_cell((i + 1) % height, (j + 1) % width);
}

bool grid::south_west(int i, int j)
{
  return get_cell((i + 1) % height, (j - 1 + width) % width);
}
//compute cell new state given neighbors
bool grid::new_state(int i, int j)
{
  int sum = north(i, j) + south(i, j) + east(i, j) + west(i, j) +
            north_east(i, j) + north_west(i, j) + south_east(i, j) +
            south_west(i, j);
  //evaluate condition
  if (get_cell(i, j))
  {
    if (sum > 3 || sum < 2){return 0;}
    else {return 1;}
  }
  else
  {
    if (sum == 3){return 1;}
    else {return 0;}
  }
}

//run one timesteo
void grid::next_epoch()
{
  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      cells[j + i*width].new_data = new_state(i,j);
    }
  }
  //update data array
  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      cells[j + i*width].data = cells[j + i*width].new_data;
    }
  }
}
//run multiple timesteps
void grid::iterate(unsigned int it)
{
  for (int i = 0; i < it; i++)
  {
    next_epoch();
    std::cout << std::endl;
    print();
  }
}
//post processing
void grid::print()
{
  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      std::cout << cells[j + i*width].data << ' ';
    }

    std::cout << std::endl;
  }
    std::cout << std::endl;
}

void grid::to_csv(std::string path)
{
  std::ofstream file;
  file.open(path);

  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      file << cells[j + i*width].data;
      if (j < (width -1)){file << ',';}
    }
    if (i < (height -1)){ file << std::endl;}
  }
}

void grid::set_cell(bool state, int i, int j)
{
  cells[j + i*width].data = state;
}
