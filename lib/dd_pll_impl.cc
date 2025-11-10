/* -*- c++ -*- */
/*
 * Copyright 2025 Paulo Duta - PU4THZ.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "dd_pll_impl.h"
#include <gnuradio/io_signature.h>
#include <cmath>

namespace gr {
  namespace dd_pllv2 {

    using input_type = gr_complex;
    using output_type = gr_complex;
    dd_pll::sptr
    dd_pll::make(float bw, float damp, gr::digital::constellation_sptr constellation, float min_freq, float max_freq)
    {
      return gnuradio::make_block_sptr<dd_pll_impl>(
        bw, damp, constellation, min_freq, max_freq);
    }


    /*
     * The private constructor
     */
    dd_pll_impl::dd_pll_impl(float bw, float damp, gr::digital::constellation_sptr constellation, float min_freq, float max_freq)
      : gr::sync_block("dd_pll",
              gr::io_signature::make(1 /* min inputs */, 1 /* max inputs */, sizeof(input_type)),
               gr::io_signature::makev(3, 3, {sizeof(output_type), sizeof(float), sizeof(float)})), d_bw(bw), d_damp(damp), d_min_freq(min_freq), d_max_freq(max_freq),
      d_phase(0.0f), d_freq(0.0f), d_prevgains{0.0f, 0.0f},
      d_constellation(constellation)
    {
      if (!d_constellation)
        throw std::invalid_argument("[dd_pll] Slicer constellation required.");

      updateGains();
    }

    /*
     * Our virtual destructor.
     */
    dd_pll_impl::~dd_pll_impl() {}

    gr_complex dd_pll_impl::Decision(const gr_complex &symbol)
    {
      unsigned int dec = d_constellation->decision_maker(&symbol);
      return d_constellation->points()[dec];
    }

    void dd_pll_impl::updateGains()
    {
      d_denom = static_cast<float>(d_constellation->points().size())
            + 2.0f * d_damp * d_bw + d_bw * d_bw;
      d_alpha = (4.0f * d_damp * d_bw) / d_denom;
      d_beta = (4.0f * d_bw * d_bw) / d_denom;
      d_phase = 0.0f;
      d_freq = 0.0f;
    }

    void dd_pll_impl::freq_limit()
    {
      if (d_freq > d_max_freq)
        d_freq = d_max_freq;
      else if (d_freq < d_min_freq)
        d_freq = d_min_freq;
    }

    void dd_pll_impl::wrap_phase()
    {
        const float two_pi = 2.0f * GR_M_PI;
        while (d_phase > two_pi)
          d_phase -= two_pi;
        while (d_phase < -two_pi)
          d_phase += two_pi;
    }

    int dd_pll_impl::work(int noutput_items,
                          gr_vector_const_void_star &input_items,
                          gr_vector_void_star &output_items)
    {
        const gr_complex *in = static_cast<const gr_complex*>(input_items[0]);
        gr_complex *out_stream = static_cast<gr_complex*>(output_items[0]); // complex output
        float *errors = static_cast<float*>(output_items[1]);              // error stream
        float *freqs = static_cast<float*>(output_items[2]);               // freq stream

        // if gains changed (you might expose setters later)
        if (d_prevgains[0] != d_bw || d_prevgains[1] != d_damp) {
            d_prevgains[0] = d_bw;
            d_prevgains[1] = d_damp;
            updateGains();
        }

        for (int i = 0; i < noutput_items; ++i) {
            // rotate input by current phase
            gr_complex rotated = in[i] * std::exp(gr_complex(0, -d_phase));

            // error: angle difference
            float err = std::arg(rotated) - std::arg(Decision(rotated));

            d_freq += d_beta * err;
            d_phase += d_freq + d_alpha * err;

            freq_limit();
            wrap_phase();

            out_stream[i] = rotated;
            errors[i] = err;
            freqs[i] = d_freq;
        }

        return noutput_items;
    }

  } /* namespace dd_pllv2 */
} /* namespace gr */
