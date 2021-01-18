/*
 * utils.c
 *
 *  Created on: 01-12-2020
 *      Author: felipe
 */

#include "fifo.h"


void fifo8_init(volatile fifo8_t *fifo, volatile uint8_t * const buffer, const uint8_t size)
{
    fifo->buffer = buffer;
    fifo->first = buffer;
    fifo->last = buffer;

    fifo->queued = 0;
    fifo->max_size = size;

    return;
}

bool fifo8_pull(volatile fifo8_t * const fifo, volatile uint8_t *byte)
{
    // Check if input FIFO has bytes to check
    if (0 < fifo->queued)
    {
        // Pull first byte of FIFO
        *byte = *fifo->first;
        --fifo->queued;

        // Move first pointer to next byte to check, checking end of buffer
        if (&fifo->buffer[fifo->max_size] == fifo->first)
        {
            fifo->first = fifo->buffer;
        }
        else
        {
            ++fifo->first;
        }

        return true;
    }

    return false;
}


void fifo8_push(volatile fifo8_t *fifo, const uint8_t byte)
{
    // Check if input FIFO is full
    if (fifo->max_size > fifo->queued)
    {
        // Not full, push byte
        *fifo->last = byte;
        ++fifo->queued;

        // Point last to next available address, checking end of buffer
        if (&fifo->buffer[fifo->max_size] == fifo->last)
        {
            fifo->last = fifo->buffer;
        }
        else
        {
            ++fifo->last;
        }
    }
    else
    {
        // FIFO is full, oldest byte (first) has to be overwritten
        // First and last byte pointing to same location
        // Move first byte to next one, checking end of buffer
        if (&fifo->buffer[fifo->max_size] == fifo->first)
        {
            fifo->first = fifo->buffer;
        }
        else
        {
            ++fifo->first;
        }

        // Push byte
        *fifo->last = byte;

        // Move last byte to same address of first byte
        // Should be processed before next new byte is pushed
        fifo->last = fifo->first;
    }

    return;
}

void fifo_flush(volatile fifo8_t *fifo)
{
    fifo->first = fifo->buffer;
    fifo->last = fifo->buffer;

    fifo->queued = 0;

    return;
}


/*** end of file ***/

