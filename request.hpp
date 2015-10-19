#pragma once
#ifndef REQUEST_H
#define REQUEST_H
#include "stopper.hpp"

class Request
{
public:
   int data;
   Request();
};

// возвращает NULL, если объект stopSignal указывает на необходимость остановки,
// либо указатель на память, которую в дальнейшем требуется удалить
Request *GetRequest(Stopper stopSignal) throw();

// обрабатывает запрос, но память не удаляет, завершает обработку досрочно,
// объект stopSignal указывает на необходимость остановки
void ProcessRequest(Request* request, Stopper stopSignal) throw();

#endif //REQUEST_H
