/* -*- c++ -*- */
/*
 * Copyright 2024 gr-lilacsat author.
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_LILACSAT_SEND_FILE_PDU_IMPL_H
#define INCLUDED_LILACSAT_SEND_FILE_PDU_IMPL_H

#include <lilacsat/send_file_pdu.h>

#include <stdio.h>

namespace gr {
  namespace lilacsat {

    class send_file_pdu_impl : public send_file_pdu
    {
     private:
      pmt::pmt_t d_out_port;
      FILE *d_fp;
      int d_pdu_len;
      int d_period;
      int d_terminal;
      void run();
      gr::thread::thread d_thread;

     public:
      send_file_pdu_impl(const std::string& path, int pdu_len, int period, int terminal);
      ~send_file_pdu_impl();

      // Where all the action really happens
      int work(
              int noutput_items,
              gr_vector_const_void_star &input_items,
              gr_vector_void_star &output_items
      );
    };

  } // namespace lilacsat
} // namespace gr

#endif /* INCLUDED_LILACSAT_SEND_FILE_PDU_IMPL_H */

