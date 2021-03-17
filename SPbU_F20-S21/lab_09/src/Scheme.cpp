#include "Scheme.hpp"

Scheme::Scheme(int capacity) {
  figures_ = new Figure* [capacity];
  std::fill(figures_, figures_ + capacity, nullptr);
}

Scheme::~Scheme() {
  for(std::size_t i = 0; i < sz; i++)
    delete figures_[i];
  delete [] figures_;
  figures_ = nullptr;
}

void Scheme::push_back_figure(Figure* fg) {
  figures_[sz++] = fg;
}

void Scheme::remove_figure(int id) {
  int i = find_with_id(id);
  if(i != -1) {
    delete figures_[i];
    std::copy(figures_ + i + 1, figures_ + sz, figures_ + i);
    sz--;
  }
}

void Scheme::print_all_figures() {
  for(std::size_t i = 0; i < sz; i++)
    figures_[i]->print();
}

void Scheme::zoom_figure(int id, int factor) {
  int i = find_with_id(id);
  if(i != -1)
    figures_[i]->zoom(factor);
}

Figure* Scheme::is_inside_figure(int x, int y) {
  for(std::size_t i = 0; i < sz; i++) {
    if(figures_[i]->is_inside(x, y))
      return figures_[i];
  }
  return nullptr;
}

void Scheme::move(int id, int x, int y) {
  int i = find_with_id(id);
  if(i != -1)
    figures_[i]->move(x , y);
}

int Scheme::find_with_id(int id) {
  for(std::size_t i = 0; i < sz; i++)
    if(figures_[i]->get_id() == id)
      return i;
  return -1;
}
