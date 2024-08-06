#include <stdio.h>
#include <unistd.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

#include "Server.h"

int server_setup(int* s)
{
    struct sockaddr_rc loc_addr = { 0 }, rem_addr = { 0 };
    char buf[1024] = { 0 };
    int client;
    socklen_t opt = sizeof(rem_addr);

    // Инициализация локального сокета
    *s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
    loc_addr.rc_family = AF_BLUETOOTH;
    loc_addr.rc_bdaddr = *BDADDR_ANY;
    loc_addr.rc_channel = (uint8_t) 1;

    // Привязка локального сокета к каналу
    bind(*s, (struct sockaddr *)&loc_addr, sizeof(loc_addr));

    // Прослушивание входящих соединений
    listen(*s, 1);

    printf("Ожидание клиента...\n");

    // Принятие клиентского соединения
    client = accept(*s, (struct sockaddr *)&rem_addr, &opt);
    ba2str(&rem_addr.rc_bdaddr, buf);
    printf("Подключен клиент %s\n", buf);

    return client;
}

int server_read(int server)
{
    char symbol = 0;
    int buf = 0;
    int bytes_read = 0;

    do
    {
        bytes_read = read(server, &buf, sizeof(buf));
    }
    while(bytes_read <= 0);

    symbol = buf;

    return symbol;
}

void server_write(int server, int symbol)
{
    int status = 0;
    do
    {
        status = write(server, &symbol, sizeof(int));
    }
    while(status <= 0);
}

void server_close(int server, int s)
{
    // Закрытие соединений
    close(server);
    close(s);
}