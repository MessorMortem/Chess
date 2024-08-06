#include <stdio.h>
#include <unistd.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

#include "Client.h"
#include "Bluetooth_scan.h"

int client_setup(void)
{
    char address[18];
    struct sockaddr_rc addr = { 0 };
    int s, status;

    bscan(address);

    // Инициализация сокета
    s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
    addr.rc_family = AF_BLUETOOTH;
    str2ba(address, &addr.rc_bdaddr);
    addr.rc_channel = (uint8_t) 1;

    // Установка соединения
    status = connect(s, (struct sockaddr *)&addr, sizeof(addr));
    if (status == 0) printf("Соединение установлено.\n");
    else { perror("Ошибка установки соединения"); return 1; }

    return s;
}

int client_read(int client)
{
    char symbol = 0;
    int buf = 0;
    int bytes_read = 0;
    do
    {
        bytes_read = read(client, &buf, sizeof(buf));
    }
    while(bytes_read <= 0);

    symbol = buf;

    return symbol;
}

void client_write(int client, int symbol)
{
    int status = 0;
    do
    {
        status = write(client, &symbol, sizeof(int));
    }
    while(status <= 0);
}

void client_close(int client)
{
    close(client);
}