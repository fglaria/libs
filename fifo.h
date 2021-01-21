/** \file utils.h
 *  \brief FIFO library header file
 *  This library enables use of buffers as circular FIFOs
 *
 *  \date 01/12/2020
 *  \author Felipe Glaria
 */

#ifndef _FIFO_H_
#define _FIFO_H_

#include <stdint.h>
#include <stdbool.h>

//*****************************************************************************
// defines
//*****************************************************************************


//*****************************************************************************
// typedefs
//*****************************************************************************

/** \struct fifo8_t
 *  Structure to use uint8_t buffer as FIFO
 */
typedef struct {
    volatile uint8_t *buffer;
    volatile uint8_t *first;
    volatile uint8_t *last;
    volatile uint8_t queued;
    volatile uint8_t max_size;
} fifo8_t;


//*****************************************************************************
// globals
//*****************************************************************************


//*****************************************************************************
// the function prototypes
//*****************************************************************************

/** \brief Function to initialize fifo8_t to use uint8_t buffer as FIFO
 *
 * \param fifo      Pointer to fifo8_t structure
 * \param buffer    Buffer to uint8_t buffer to use as FIFO
 * \param max_size  Size of buffer
 */
void fifo8_init(volatile fifo8_t * const fifo, volatile uint8_t * const buffer, const uint8_t size);

/** \brief Function to get byte on FIFO
 *
 * \param fifo      Pointer to fifo8_t structure
 * \param byte      Pointer to byte to write output
 *
 * \return  true if byte was pulled from FIFO; false if no byte on FIFO
 */
bool fifo8_pull(volatile fifo8_t * const fifo, volatile uint8_t *byte);

/** \brief Function to push byte on FIFO
 *
 * \param fifo      Pointer to fifo8_t structure
 * \param byte      Byte to push on FIFO
 */
void fifo8_push(volatile fifo8_t * const fifo, const uint8_t byte);

/** \brief Function to flush fifo
 *
 * \param fifo      Pointer to fifo8_t structure to flush
 */
void fifo8_flush(volatile fifo8_t * const fifo);


#endif /* _FIFO_H_ */

/*** end of file ***/

