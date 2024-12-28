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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "send_file_pdu_impl.h"

#include <thread>

namespace gr {
  namespace lilacsat {

    send_file_pdu::sptr
    send_file_pdu::make(const std::string& path, int pdu_len, int period, int terminal)
    {
      return gnuradio::get_initial_sptr
        (new send_file_pdu_impl(path, pdu_len, period, terminal));
    }


    /*
     * The private constructor
     */
    send_file_pdu_impl::send_file_pdu_impl(const std::string& path, int pdu_len, int period, int terminal)
      : gr::sync_block("send_file_pdu",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0))
    {
	d_out_port = pmt::mp("out");	      
      	message_port_register_out(d_out_port);
      	
      	
      	d_fp = fopen(path.data(), "rb");
      	d_pdu_len = pdu_len;
      	d_period = period;
      	d_terminal = terminal;
      	
      	d_thread = gr::thread::thread([this] {run(); });
    }
    
    void send_file_pdu_impl::run()
    {
    	uint8_t buffer[1024];
    	
    	while(1)
    	{    	
	    	std::this_thread::sleep_for(
	    	  std::chrono::milliseconds(static_cast<long>(d_period)));
	    	
	    	int len = fread(buffer, 1, d_pdu_len, d_fp);
	    	if(len == d_pdu_len)
	    	{
	    		send_file_pdu_impl::message_port_pub(send_file_pdu_impl::d_out_port, pmt::cons(pmt::make_dict(), pmt::init_u8vector(len, (const uint8_t *)buffer))); 
	    	}
    	}
    }

    /*
     * Our virtual destructor.
     */
    send_file_pdu_impl::~send_file_pdu_impl()
    {
    }

    int
    send_file_pdu_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      // <+OTYPE+> *out = (<+OTYPE+> *) output_items[0];

      // Do <+signal processing+>

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace lilacsat */
} /* namespace gr */

