/* -*- c++ -*- */
/*
 * Copyright 2025 Paulo Duta - PU4THZ.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DD_PLLV2_DD_PLL_IMPL_H
#define INCLUDED_DD_PLLV2_DD_PLL_IMPL_H

#include <gnuradio/dd_pllv2/dd_pll.h>
#include <gnuradio/digital/constellation.h>
#include <gnuradio/math.h>
#include <vector>

namespace gr {
namespace dd_pllv2 {

    class dd_pll_impl : public dd_pll
    {
     private:
      // Parameters
      float d_bw;
      float d_damp;
      float d_min_freq;
      float d_max_freq;

      // State
      float d_phase;
      float d_freq;

      // Gains
      float d_denom;
      float d_alpha;
      float d_beta;
      float d_prevgains[2];

      // Constellation
      gr::digital::constellation_sptr d_constellation;

      // Internal helpers
      void updateGains();
      gr_complex Decision(const gr_complex &symbol);
      void freq_limit();
      void wrap_phase();

     public:
      dd_pll_impl(float bw, float damp, gr::digital::constellation_sptr constellation, float min_freq, float max_freq);
    ~dd_pll_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
    };

    } // namespace dd_pllv2
    } // namespace gr

#endif /* INCLUDED_DD_PLLV2_DD_PLL_IMPL_H */
