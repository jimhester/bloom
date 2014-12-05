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
    std::string filename;

    Bloom(unsigned int capacity, double error_rate, const std::string filename, bool exists) {
      this->filename = filename;
      if (exists) {
        filter = new_scaling_bloom_from_file(capacity, error_rate, filename.c_str());
      }
      else {
        filter = new_scaling_bloom(capacity, error_rate, filename.c_str());
      }
    }
    ~Bloom() {
      free_scaling_bloom(filter);
      filter = NULL;
    }

    int add(std::string key, unsigned int id) {
      return scaling_bloom_add(filter, key.c_str(), key.length(), id);
    }

    bool contains(std::string key) {
      return scaling_bloom_check(filter, key.c_str(), key.length()) != 0;
    }

    int remove(std::string key, unsigned int id) {
      return scaling_bloom_remove(filter, key.c_str(), key.length(), id);
    }

};


RCPP_MODULE(Bloom){

  Rcpp::class_<Bloom>("Bloom")
    .constructor<unsigned int, double, std::string, bool>("constructor")

    .field_readonly("filename", &Bloom::filename, "disk location of bloom filter")
    .method("add", &Bloom::add, "add an element to the bloom filter")
    .method("contains", &Bloom::contains, "check if an element exists in the bloom filter")
    .method("remove", &Bloom::remove, "remove an element from the bloom filter")
    ;
}
