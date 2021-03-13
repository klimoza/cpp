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
  for(std::size_t i = 0; i < sz; i++) {
    if(figures_[i]->get_id() == id) {
      delete figures_[i];
      std::copy(figures_ + i + 1, figures_ + sz, figures_ + i);
      sz--;
      break;
    }
  }
}

void Scheme::print_all_figures() {
  for(std::size_t i = 0; i < sz; i++)
    figures_[i]->print();
}

void Scheme::zoom_figure(int id, int factor) {
  for(std::size_t i = 0; i < sz; i++) {
    if(figures_[i]->get_id() == id) {
      figures_[i]->zoom(factor);
      break;
    }
  }
}

Figure* Scheme::is_inside_figure(int x, int y) {
  for(std::size_t i = 0; i < sz; i++) {
    if(figures_[i]->is_inside(x, y))
      return figures_[i];
  }
  return nullptr;
}

void Scheme::move(int id, int x, int y) {
  for(std::size_t i = 0; i < sz; i++) {
    if(figures_[i]->get_id() == id) {
      figures_[i]->move(x, y);
      break;
    }
  }
}
