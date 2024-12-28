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

#ifndef INCLUDED_LILACSAT_SEND_FILE_PDU_H
#define INCLUDED_LILACSAT_SEND_FILE_PDU_H

#include <lilacsat/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace lilacsat {

    /*!
     * \brief <+description of block+>
     * \ingroup lilacsat
     *
     */
    class LILACSAT_API send_file_pdu : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<send_file_pdu> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of lilacsat::send_file_pdu.
       *
       * To avoid accidental use of raw pointers, lilacsat::send_file_pdu's
       * constructor is in a private implementation
       * class. lilacsat::send_file_pdu::make is the public interface for
       * creating new instances.
       */
      static sptr make(const std::string& path, int pdu_len, int period, int terminal);
    };

  } // namespace lilacsat
} // namespace gr

#endif /* INCLUDED_LILACSAT_SEND_FILE_PDU_H */

