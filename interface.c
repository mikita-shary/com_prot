/* Logic_of_communication

|start byte|address byte|----------------------------------------> master to slave                                
                        |data byte | x12 |CRC|stop byte|---------> slave to master

*/

/******************************************************************************
* File Name          : inteface.с
* Author             : EXOPULSE Team
* Version            : v 0.0
*******************************************************************************/

/* Includes-------------------------------------------------------------------*/

#include "interface.h"

/* Global futction-------------------------------------------------------------*/

bool receive_pack(uint8_t sensor_data[SENS_DATA_SIZE])
{
  UART_Init(TX);

  send_byte((uint8_t)START_BYTE); //send start byte

  send_byte((uint8_t)COMMON_ADDRES + ADDRESS_1); //for sample device has address 1

  UART_Init(RX);

  for (uint8_t t = 0; t < SENS_DATA_SIZE; t++)
  { //receive data bytes
    sensor_data[t] = reseive_byte();
  }
  uint8_t *ptr = sensor_data;

  uint8_t crc_byte = reseive_byte(); //receive crc byte

  uint8_t stop_byte = reseive_byte(); //receive stop byte

  if (Crc8(ptr, SENS_DATA_SIZE) == crc_byte && stop_byte == STOP_BYTE)
  { // check crc and stop byte
    return 1;
  }
  else
    return 0;
}

void transmit_pack(uint8_t sensor_data[SENS_DATA_SIZE])
{

  uint8_t star_byte = reseive_byte(); //receive start byte

  uint8_t addres_byte = reseive_byte(); //receive address byte

  if (star_byte == START_BYTE && addres_byte == COMMON_ADDRES + ADDRESS_10)
  { //for example let it be number 10
    for (uint8_t t = 0; t < SENS_DATA_SIZE; t++)
    {
      send_byte(sensor_data[t]);
    }
    uint8_t *ptr = sensor_data;
    send_byte(Crc8(ptr, SENS_DATA_SIZE));
    send_byte(STOP_BYTE);
  }

  else
  {
    //sleep
  }
}

uint8_t Crc8(uint8_t *data, uint8_t len)
{
  uint8_t crc = 0xFF;

  while (len--)
    crc = Crc8Table[crc ^ *data++];

  return crc;
}

void pause()
{
  while (1)
  {
  };
}

/******************************* end of file **********************************/