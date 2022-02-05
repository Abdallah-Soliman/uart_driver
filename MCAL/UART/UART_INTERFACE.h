/*
 * UART_INTERFACE.h
 *
 *  Created on: Feb 3, 2022
 *      Author: abdalah
 */

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

                       /*UATRT INIT*/
             void USART_VoidInit(uint8_t PORT ,uint8_t PIN_TX,uint8_t PIN_RX);

                      /*UART receive data*/
                uint8_t UART_U8GetData(uint8_t* au_ptr);



                        /*UART send data*/
                uint8_t UART_U8_SendData(uint8_t * au_ptr) ;



                            /*UART send buffer synchronous*/
                uint8_t UART_U8SendBufferSyn(uint8_t *au_ptr ,uint8_t size);



                             /*UART receive buffer synchronous*/
                uint8_t UART_U8ReciveBufferSyn(uint8_t *au_ptr ,uint8_t size );





                                 /***********UART receive buffer ****************/
            /********   Please before you use this function you must Enable global interrupt*********/
              uint8_t UART_U8ReciveBufferAsyn(uint8_t *au_ptr ,uint8_t size ,void (*Notification)(void));



#endif /* UART_INTERFACE_H_ */
