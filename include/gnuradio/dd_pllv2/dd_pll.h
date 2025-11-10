/* -*- c++ -*- */
/*
 * Copyright 2025 Paulo Duta - PU4THZ.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DD_PLLV2_DD_PLL_H
#define INCLUDED_DD_PLLV2_DD_PLL_H

#include <gnuradio/dd_pllv2/api.h>
#include <gnuradio/sync_block.h>
#include <gnuradio/digital/constellation.h>

namespace gr {
namespace dd_pllv2 {

/*!
 * \brief <+description of block+>
 * \ingroup dd_pllv2
 *
 */
class DD_PLLV2_API dd_pll : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<dd_pll> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of dd_pllv2::dd_pll.
     *
     * To avoid accidental use of raw pointers, dd_pllv2::dd_pll's
     * constructor is in a private implementation
     * class. dd_pllv2::dd_pll::make is the public interface for
     * creating new instances.
     */
    static sptr make(float bw = 0.0628,
                     float damp = 1.0,
                     gr::digital::constellation_sptr constellation =
                        gr::digital::constellation_bpsk::make(),
                     float min_freq = -1.0,
                     float max_freq = 1.0);
};

} // namespace dd_pllv2
} // namespace gr

#endif /* INCLUDED_DD_PLLV2_DD_PLL_H */
