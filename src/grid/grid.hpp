#ifndef GRID_HPP
#define GRID_HPP

#include <memory>
#include <string>

//faster way to do it (cache coherent)
struct cell
{
  bool data;
  bool new_data;
};

class grid{
private:
  //grid dimensions
  int width;
  int height;
  //grid value
  std::unique_ptr<cell[]> cells;

public:
  //constructor
  grid(int width, int height);
  grid(int width, int height, std::string path);
  //initial state
  void from_csv(std::string path);
  //index array easily
  bool get_cell(int i, int j);
  //neighbords, sides/corners
  bool north(int i, int j);
  bool south(int i, int j);
  bool east(int i, int j);
  bool west(int i, int j);
  bool north_east(int i, int j);
  bool north_west(int i, int j);
  bool south_east(int i, int j);
  bool south_west(int i, int j);
  //return if live or dead
  bool new_state(int i, int j);
  //run 1 timestep
  void next_epoch();
  //run multiple epochs
  void iterate(unsigned int it);
  //post processing
  void print();
  void to_csv(std::string path);
  //debug
  void set_cell(bool state, int i, int j);
};

#endif
