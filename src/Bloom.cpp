// -*- mode: C++; c-indent-level: 4; c-basic-offset: 4; indent-tabs-mode: nil; -*-
//
// rcpp_module.cpp: Rcpp R/C++ interface class library -- Rcpp Module examples
//
// Copyright (C) 2010 - 2012  Dirk Eddelbuettel and Romain Francois
//
// This file is part of Rcpp.
//
// Rcpp is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// Rcpp is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Rcpp.  If not, see <http://www.gnu.org/licenses/>.

#include <Rcpp.h>
extern "C"
{
#include "dablooms.h"
}

class Bloom {
  private:
    scaling_bloom_t *filter;

  public:
    Bloom() { filter = NULL; }
    Bloom(unsigned int capacity, double error_rate, std::string filename) {
      filter = new_scaling_bloom(capacity, error_rate, filename.c_str());
    }
    ~Bloom() {
      free_scaling_bloom(filter);
      filter = NULL;
    }

    bool add(std::string key, unsigned int id) {
      return scaling_bloom_add(filter, key.c_str(), key.length(), id);
    }

    bool contains(std::string key) {
      return scaling_bloom_check(filter, key.c_str(), key.length()) != 0;
    }

    int check(std::string key) {
      return scaling_bloom_check(filter, key.c_str(), key.length());
    }

    bool remove(std::string key, unsigned int id) {
      return scaling_bloom_remove(filter, key.c_str(), key.length(), id);
    }
};

RCPP_MODULE(bloom){

  Rcpp::class_<Bloom>("bloom")
    .constructor()
    .constructor<unsigned int, double, std::string>("constructor")

    .method("add", &Bloom::add)
    .method("contains", &Bloom::contains)
    .method("check", &Bloom::check)
    .method("remove", &Bloom::remove)
    ;
}
