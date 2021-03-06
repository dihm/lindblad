/*
Copyright 2014 Dominic Meiser

This file is part of lindblad.

lindblad is free software: you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation, either version 3 of the License, or (at your
option) any later version.

lindblad is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License along
with lindblad.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef COUPLING_HPP
#define COUPLING_HPP

#include <Amplitude.hpp>

namespace Lindblad {
namespace Detail {

class Coupling {
 public:
  Coupling(int m, int n, Amplitude g) : m(m), n(n), g(g) {}
  void apply(int dim, const Amplitude *A, Amplitude *B) const;
  bool isDiagonal() const { return m == n; }
  Amplitude getCouplingStrength() const { return g; }
  int getRow() const { return m; }
  int getCol() const { return n; }

 private:
  int m;
  int n;
  Amplitude g;
};

}
}

#endif

